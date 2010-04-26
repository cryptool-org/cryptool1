/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

// DlgFindAndReplace.cpp
#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFindAndReplace.h"
#include "CrypToolView.h"
#include "ScintillaWnd.h"
#include "ScintillaDoc.h"
#include "ScintillaView.h"
#include "HexEditCtrlView.h"
#include ".\dlgfindandreplace.h"

// this function returns true if the input string (which is the output string also) 
// could be converted from hex to ascii; in case the hex string contains a zero byte (00),
// the string is cut off at that place and the function returns false
bool tryToConvertHexStringToAsciiString(CString &text) {
	// this is the string to be returned
	CString result = "";
	for(int i=0; i<text.GetLength(); i+=2) {
		// conversion from hex to ascii
		char hex[5];
		hex[0] = '0';
		hex[1] = 'x';
		hex[2] = text[i+0];
		hex[3] = text[i+1];
		hex[4] = 0;
		// in case we have a zero byte (00), return false
		if(hex[2] == '0' && hex[3] == '0') {
            text = result;
			return false;
		}
		// append the new character to the result string
		result.AppendChar(strtol(hex, 0, 16));
	}
	// assign the result string and return true
	text = result;
	return true;
}
void convertHexToAscii(const char *_hex, char **_ascii, int &_asciiLength)
{	
	// allocate memory for output parameters
	_asciiLength = (strlen(_hex) + 1) / 2;
	*_ascii = new char[_asciiLength + 1];
	memset(*_ascii, 0, _asciiLength+1);
	// convert from hex to ascii
	for(unsigned int i=0; i<strlen(_hex); i+=2) {
		char buffer[5];
		buffer[0] = '0';
		buffer[1] = 'x';
		buffer[2] = _hex[i+0];
		buffer[3] = _hex[i+1];
		buffer[4] = 0;
		// fill the result string _ascii
		char temp = strtol(buffer, 0, 16);
		char tempString[2];
		tempString[0] = temp;
		tempString[1] = '\0';
		memcpy(*_ascii + i/2, tempString, 1);
	}
}
void convertAsciiToHex(const char *_ascii, const int &_asciiLength, char **_hex)
{
	// allocate memory for output parameters
	*_hex = new char[_asciiLength*2 + 1];
	memset(*_hex, 0, _asciiLength*2 + 1);
	// convert from ascii to hex
	for(int i=0; i<_asciiLength; i++) {
		sprintf(*_hex + 2*i, "%02x", (unsigned char)_ascii[i]);
	}
}

IMPLEMENT_DYNAMIC(CDlgFindAndReplace, CDialog)
CDlgFindAndReplace::CDlgFindAndReplace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFindAndReplace::IDD, pParent)
	, textFind(_T(""))
	, textReplace(_T(""))
	, checkCaseSensitive(FALSE)
	, checkFindBackwards(FALSE)
	, checkRegularExpressions(FALSE)
	, created(FALSE)
{
}
CDlgFindAndReplace::~CDlgFindAndReplace()
{
}
void CDlgFindAndReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIND_HEX, textFindHex);
	DDX_Text(pDX, IDC_EDIT_REPLACE_HEX, textReplaceHex);
	DDX_Check(pDX, IDC_CHECK_CASE_SENSITIVE, checkCaseSensitive);
	DDX_Check(pDX, IDC_CHECK_FIND_BACKWARDS, checkFindBackwards);
	DDX_Check(pDX, IDC_CHECK_REGULAR_EXPRESSIONS, checkRegularExpressions);
	DDX_Control(pDX, IDC_RADIO_TEXT_MODE, radioButtonControlText);
	DDX_Control(pDX, IDC_RADIO_HEX_MODE, radioButtonControlHex);
	DDX_Control(pDX, IDC_EDIT_FIND_HEX, hexEditControlFind);
	DDX_Control(pDX, IDC_EDIT_REPLACE_HEX, hexEditControlReplace);
}

BEGIN_MESSAGE_MAP(CDlgFindAndReplace, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE, OnBnClickedButtonReplace)
	ON_BN_CLICKED(IDC_BUTTON_REPLACE_ALL, OnBnClickedButtonReplaceAll)
	ON_BN_CLICKED(IDC_RADIO_TEXT_MODE, OnBnClickedRadioTextMode)
	ON_BN_CLICKED(IDC_RADIO_HEX_MODE, OnBnClickedRadioHexMode)
END_MESSAGE_MAP()

// CDlgFindAndReplace message handlers
void CDlgFindAndReplace::OnBnClickedButtonFind()
{
	DoFindReplace(false, false);
}
void CDlgFindAndReplace::OnBnClickedButtonReplace()
{
	DoFindReplace(true, false);
}
void CDlgFindAndReplace::OnBnClickedButtonReplaceAll()
{
	DoFindReplace(true, true);
}
void CDlgFindAndReplace::DoFindReplace(bool replace, bool all)
{
	UpdateData(true);
	CWnd *pWndTmp = theApp.GetMainWnd(); ASSERT(pWndTmp); // CMainFrame
	pWndTmp = pWndTmp->GetTopWindow(); ASSERT(pWndTmp); // ?? CWnd
	pWndTmp = pWndTmp->GetTopWindow(); // CMDIChildWnd
	// do nothing if there's no window opened (prevent segmentation faults)
	if (!pWndTmp) 
		return;
	CWnd *pWndView = pWndTmp->GetTopWindow(); // CView
	if (pWndView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
	{
		DoFindReplaceScintilla(pWndView->GetTopWindow(), replace, all);
	}
	else if (pWndView->IsKindOf(RUNTIME_CLASS(CHexEditCtrlView)))
	{
		// flomar, 04/25/2010
		// originally, we were preventing the execution of regular expressions here, 
		// because that's not supported for hex; however, we're preventing regular 
		// expressions now via the user interface (regex cannot be activated for hex)
		DoFindReplaceHexEdit(pWndView->GetTopWindow(), replace, all);
	} 
}
void CDlgFindAndReplace::DoFindReplaceScintilla(CWnd *pWnd, bool replace, bool all)
{
	UpdateData(true);
	#define MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING	1024
	// initialize memory
	int lengthFindString = 0;
	int lengthReplaceString = 0;
	char findString[MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1];
    char replaceString[MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1];
    memset(findString, 0, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1);
	memset(replaceString, 0, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1);
	// if we're in text mode...
	if(radioButtonControlText.GetCheck() == 1) {
		// retrieve input from scintilla control
		lengthFindString = FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETLENGTH);
		if(lengthFindString > MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING)
			lengthFindString = MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING;
		lengthReplaceString = FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETLENGTH);
		if(lengthReplaceString > MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING)
			lengthReplaceString = MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING;
        // get the ascii value from the scintilla input control
		FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETTEXT, (WPARAM)lengthFindString+1, (LPARAM)findString);
		FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETTEXT, (WPARAM)lengthReplaceString+1, (LPARAM)replaceString);
	}
	// if we're in hex mode...
	else {
		// remove whitespaces from input
		CString tempFindHex = textFindHex;
		CString tempReplaceHex = textReplaceHex;
		tempFindHex.Remove(' ');
		tempReplaceHex.Remove(' ');
		// convert input
		char *tempFindString;
		char *tempReplaceString;
		convertHexToAscii(tempFindHex.GetBuffer(), &tempFindString, lengthFindString);
		convertHexToAscii(tempReplaceHex.GetBuffer(), &tempReplaceString, lengthReplaceString);
		// copy input, delete temporary memory
		memcpy(findString, tempFindString, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING);
		memcpy(replaceString, tempReplaceString, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING);
		delete tempFindString;
		delete tempReplaceString;
	}
	// if there are null bytes in the find term, abort the search and notify the user
	for(int i=0; i<lengthFindString; i++) {
		if(findString[i] == 0) {
			LoadString(AfxGetInstanceHandle(), IDS_FIND_AND_REPLACE_NULL_BYTE_IN_FIND_STRING, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
			return;
		}
	}
	// ...do the same for the replace term
	for(int i=0; i<lengthReplaceString; i++) {
		if(replaceString[i] == 0) {
			LoadString(AfxGetInstanceHandle(), IDS_FIND_AND_REPLACE_NULL_BYTE_IN_REPLACE_STRING, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
			return;
		}
	}
    
	ASSERT(pWnd);
	CScintillaWnd *pWindow = (CScintillaWnd*)pWnd;
	CString msg;
	int searchflags = 0;
	if (checkCaseSensitive) searchflags |= SCFIND_MATCHCASE;
	if (checkRegularExpressions) searchflags |= SCFIND_REGEXP;
	pWindow->SetSearchflags(searchflags);
	char *ttf = findString;
	char *ttr = replaceString;

	// store current cursor position (and selection) for future use
	long pStart = pWindow->GetSelectionStart();
	long pEnd   = pWindow->GetSelectionEnd();

	// *** REPLACE (SINGLE REPLACE) ***
	if (replace && !all)
	{
		// forward search (and single replace)
		if(!checkFindBackwards)
		{
			if ( pStart == pEnd && !pWindow->SearchForward(ttf) )
			{
				msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
				MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
				return;
			}
			pWindow->ReplaceSearchedText(ttr);
			if(!pWindow->SearchForward(ttf))
			{
				msg.Format(IDS_FINDANDREPLACE_TEXT_FINISHED);
				MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
				return;
			}
		}
		// backward search (and single replace)
		else
		{
			if ( pStart == pEnd && !pWindow->SearchBackward(ttf) )
			{
				msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
				MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
				return;
			}
			pWindow->ReplaceSearchedText(ttr);
			if(!pWindow->SearchBackward(ttf))
			{
				msg.Format(IDS_FINDANDREPLACE_TEXT_FINISHED);
				MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
				return;
			}
		}
	}
	// *** REPLACE (MULTIPLE REPLACE) ***
	else if (replace && all)
	{
		int noCnt = pWindow->ReplaceAll(ttf, ttr, FALSE);
		// how often was the desired text replaced?
		if(!noCnt)
		{
			msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}
		else
		{
            msg.Format(IDS_FINDANDREPLACE_TEXTOCCURANCESREPLACED, noCnt);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}
	}
	// *** SEARCH ONLY (NO REPLACE) ***
	else	
	{	
		// forward search
		if(!checkFindBackwards)
		{
			if(!pWindow->SearchForward(ttf)) { // FIXME: truncates at \0
				// flomar, 04/26/2010
				// we should try searching from the beginning of the document (wrap-around search)
				pWindow->SendMessage(SCI_SETSEL, 0, 0);
				if(!pWindow->SearchForward(ttf)) {
					msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
					MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
					return;
				}
			}
		}
		// backward search
		else
		{
			if(!pWindow->SearchBackward(ttf)) {
				// flomar, 04/26/2010
				// we should try searching from the end of the document (wrap-around search)
				pWindow->SendMessage(SCI_SETSEL, -1, -1);
				if(!pWindow->SearchBackward(ttf)) {
					msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
					MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
					return;
				}
			}
		}
	}
	textFind.ReleaseBuffer(); ttf = 0;
	textReplace.ReleaseBuffer(); ttr = 0;
}
void CDlgFindAndReplace::DoFindReplaceHexEdit(CWnd *pWnd, bool replace, bool all)
{
	UpdateData(true);
	#define MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING	1024
	// initialize memory
	int lengthFindString = 0;
	int lengthReplaceString = 0;
	char findString[MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1];
    char replaceString[MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1];
    memset(findString, 0, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1);
	memset(replaceString, 0, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING + 1);
	// if we're in text mode...
	if(radioButtonControlText.GetCheck() == 1) {
		// retrieve input from scintilla control
		lengthFindString = FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETLENGTH);
		if(lengthFindString > MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING)
			lengthFindString = MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING;
		lengthReplaceString = FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETLENGTH);
		if(lengthReplaceString > MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING)
			lengthReplaceString = MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING;
        // get the ascii value from the scintilla input control
		FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETTEXT, (WPARAM)lengthFindString+1, (LPARAM)findString);
		FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETTEXT, (WPARAM)lengthReplaceString+1, (LPARAM)replaceString);
	}
	// if we're in hex mode...
	else {
		// remove whitespaces from input
		CString tempFindHex = textFindHex;
		CString tempReplaceHex = textReplaceHex;
		tempFindHex.Remove(' ');
		tempReplaceHex.Remove(' ');
		// convert input
		char *tempFindString;
		char *tempReplaceString;
		convertHexToAscii(tempFindHex.GetBuffer(), &tempFindString, lengthFindString);
		convertHexToAscii(tempReplaceHex.GetBuffer(), &tempReplaceString, lengthReplaceString);
		// copy input, delete temporary memory
		memcpy(findString, tempFindString, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING);
		memcpy(replaceString, tempReplaceString, MAXIMUM_LENGTH_OF_FIND_AND_REPLACE_STRING);
		delete tempFindString;
		delete tempReplaceString;
	}
	ASSERT(pWnd);
	CHexEditBase *pWindow = (CHexEditBase*)pWnd;
	CString msg;
	int searchflags = 0;
	if (checkCaseSensitive) searchflags |= HE_FIND_MATCHCASE;
	if (checkFindBackwards) searchflags |= HE_FIND_BACKWARDS;
	
	LPCSTR pfind = (LPCSTR)findString;
	int findlen = lengthFindString;
	LPCSTR preplace = (LPCSTR)replaceString;
	int replacelen = lengthReplaceString; 
	
	// *** REPLACE (SINGLE REPLACE) ***
	if (replace && !all)
	{
		if (!pWindow->Search(pfind, findlen, searchflags | HE_FIND_NOSKIP)) {
			msg.Format(IDS_FINDANDREPLACE_TEXT_FINISHED);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}
		pWindow->ReplaceSelection(preplace,replacelen);
		if (!pWindow->Search(pfind, findlen, searchflags | HE_FIND_NOSKIP)) {
			msg.Format(IDS_FINDANDREPLACE_TEXT_FINISHED);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}
	}
	// *** REPLACE (MULTIPLE REPLACE) ***
	else if (replace && all)
	{
		int noCnt = pWindow->ReplaceAll(pfind, findlen, preplace, replacelen, searchflags);
		// how often was the desired text replaced?
		if(!noCnt)
		{
			msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}
		else
		{
            msg.Format(IDS_FINDANDREPLACE_TEXTOCCURANCESREPLACED, noCnt);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}
	}
	// *** SEARCH ONLY (NO REPLACE) ***
	else
	{
		if(!pWindow->Search(pfind, findlen, searchflags))
		{
			msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}
	}
}
BOOL CDlgFindAndReplace::OnInitDialog()
{
	CDialog::OnInitDialog();
	// create our two Scintilla windows
	handleScintillaWindowFind = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 71, 57, 300, 20, *this, NULL, NULL, NULL);
    handleScintillaWindowReplace = CreateWindowEx(WS_EX_CLIENTEDGE, "Scintilla", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN, 71, 89, 300, 20, *this, NULL, NULL, NULL);
	// initializations (partly taken from CScintillaWnd::Init, May 19th, 2008)
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETREADONLY, (WPARAM)FALSE);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETHSCROLLBAR, (WPARAM)FALSE);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETMODEVENTMASK, (WPARAM)SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETMODEVENTMASK, (WPARAM)SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETEOLMODE, 0, 0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETVIEWEOL, TRUE, 0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, 0, SC_MARK_CIRCLE);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETWRAPMODE,1);
    FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETWRAPVISUALFLAGS,1);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETMARGINWIDTHN, 0, 0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETWRAPMODE,0,0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETMARGINWIDTHN, 2, 0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETMARGINWIDTHN, 1, 0);
    FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETINDENTATIONGUIDES, TRUE, 0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETTABWIDTH,3,0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETINDENT,3,0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETCARETPERIOD,400,0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETMODEVENTMASK, SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT, 0);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_SETMARGINSENSITIVEN, 2, TRUE);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
	FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
    FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
    FromHandle(handleScintillaWindowFind)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETREADONLY, (WPARAM)FALSE);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETHSCROLLBAR, (WPARAM)FALSE);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETMODEVENTMASK, (WPARAM)SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETMODEVENTMASK, (WPARAM)SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETEOLMODE, 0, 0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETVIEWEOL, TRUE, 0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, 0, SC_MARK_CIRCLE);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETWRAPMODE,1);
    FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETWRAPVISUALFLAGS,1);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETMARGINWIDTHN, 0, 0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETWRAPMODE,0,0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETMARGINWIDTHN, 2, 0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETMARGINWIDTHN, 1, 0);
    FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETINDENTATIONGUIDES, TRUE, 0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETTABWIDTH,3,0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETINDENT,3,0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETCARETPERIOD,400,0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETMODEVENTMASK, SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT, 0);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_SETMARGINSENSITIVEN, 2, TRUE);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
	FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
    FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
    FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
	// we're in text mode (not hex) by default
	radioButtonControlText.SetCheck(1);
	updateMode();
	UpdateData(false);

	return TRUE;
}

BOOL CDlgFindAndReplace::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	//CDialog::OnNotify(wParam, lParam, pResult);
	// catch notification from Scintilla windows
	NMHDR *lpnmhdr = (LPNMHDR)(lParam);
	
	char *theTextFind = 0;
	int theTextFindLength = 0;
	char *theTextReplace = 0;
	int theTextReplaceLength = 0;
	// the Scintilla "find" window
	if(lpnmhdr->hwndFrom == handleScintillaWindowFind) {
		switch(lpnmhdr->code) {
			case SCN_MODIFIED:
				// TODO: retrieve new content, update history and synchronize hex field
				theTextFindLength = FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETLENGTH);
				theTextFindLength++;
				theTextFind = new char[theTextFindLength + 1];
				memset(theTextFind, 0, theTextFindLength);
				FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETTEXT, (WPARAM)theTextFindLength, (LPARAM)theTextFind);
				// assign new value
				textFind = theTextFind;
                return TRUE;
				break;
			default:
				break;
		}
	}
	// the Scintilla "replace" window
	if(lpnmhdr->hwndFrom == handleScintillaWindowReplace) {
		switch(lpnmhdr->code) {
			case SCN_MODIFIED:
				// TODO: retrieve new content, update history and synchronize hex field
				theTextReplaceLength = FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETLENGTH);
				theTextReplaceLength++;
				theTextReplace = new char[theTextReplaceLength + 1];
				memset(theTextReplace, 0, theTextReplaceLength);
				FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETTEXT, (WPARAM)theTextReplaceLength, (LPARAM)theTextReplace);
				// assign new value
				textReplace = theTextReplace;
                return TRUE;
				break;
			default:
				break;
		}
	}
	return FALSE;
}
void CDlgFindAndReplace::show()
{
	if(!created)
	{
		Create(IDD_FIND_AND_REPLACE);
		created = true;
	}

	// set focus to either the hex or the text input field
	if(radioButtonControlText.GetCheck()) {
		::SetFocus(handleScintillaWindowFind);
	}
	else {
		hexEditControlFind.SetFocus();
	}

	ShowWindow(SW_SHOW);
}
void CDlgFindAndReplace::OnCancel() 
{
	ShowWindow(SW_HIDE);
}
// user clicked the "text mode" radio button
void CDlgFindAndReplace::OnBnClickedRadioTextMode()
{
	updateMode();
}
// user clicked the "hex mode" radio button
void CDlgFindAndReplace::OnBnClickedRadioHexMode()
{
	updateMode();
}
void CDlgFindAndReplace::updateMode()
{
	UpdateData(true);
	// we're in text mode...
	if(radioButtonControlText.GetCheck()) {
		// enable text-related input fields
		FromHandle(handleScintillaWindowFind)->EnableWindow(true);
		FromHandle(handleScintillaWindowFind)->ShowWindow(SW_SHOW);
		FromHandle(handleScintillaWindowReplace)->EnableWindow(true);
		FromHandle(handleScintillaWindowReplace)->ShowWindow(SW_SHOW);
		// disable hex-related input fields	
		GetDlgItem(IDC_EDIT_FIND_HEX)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_FIND_HEX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->ShowWindow(SW_HIDE);
		// enable regular expressions check box
		GetDlgItem(IDC_CHECK_REGULAR_EXPRESSIONS)->EnableWindow(true);
		// ****************************************************
		// synchronize the input fields (copy from hex -> text)
		CString temp;
		char *ascii;
		int asciiLength;
		// *** FIND FIELD *************************************
		// remove all whitespaces
		temp = textFindHex;
		temp.Remove(' ');
		// convert hex to ascii
		convertHexToAscii(temp.GetBuffer(), &ascii, asciiLength);
		// make scintilla input control display the calculated ascii value 
		FromHandle(handleScintillaWindowFind)->SendMessage(SCI_CLEARALL);
		FromHandle(handleScintillaWindowFind)->SendMessage(SCI_ADDTEXT, (WPARAM)asciiLength, (LPARAM)ascii);
		// clean up memory
		delete ascii;
		// *** REPLACE FIELD **********************************
		// remove all whitespaces
		temp = textReplaceHex;
		temp.Remove(' ');
		// convert hex to ascii
		convertHexToAscii(temp.GetBuffer(), &ascii, asciiLength);
		// make scintilla input control display the calculated ascii value
		FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_CLEARALL);
		FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_ADDTEXT, (WPARAM)asciiLength, (LPARAM)ascii);
		// clean up memory
		delete ascii;
		::SetFocus(handleScintillaWindowFind);  
	}
	// we're in hex mode...
	if(radioButtonControlHex.GetCheck()) {
		// enable hex-related input fields
		GetDlgItem(IDC_EDIT_FIND_HEX)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_FIND_HEX)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->ShowWindow(SW_SHOW);
		// disable text-related input fields
		FromHandle(handleScintillaWindowFind)->EnableWindow(false);
		FromHandle(handleScintillaWindowFind)->ShowWindow(SW_HIDE);
		FromHandle(handleScintillaWindowReplace)->EnableWindow(false);
		FromHandle(handleScintillaWindowReplace)->ShowWindow(SW_HIDE);
		// disable regular expressions check box and (important!) uncheck it
		GetDlgItem(IDC_CHECK_REGULAR_EXPRESSIONS)->EnableWindow(false);
		checkRegularExpressions = false;
		// ****************************************************
		// synchronize the input fields (copy from text -> hex)
		CString temp;
		char *hex;
		char *ascii;
		int asciiLength;
		int estimatedStringLengthHex;
		
		// *** FIND FIELD *************************************
		// get the length of the text in the scintilla control
		asciiLength = FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETLENGTH);
		ascii = new char[asciiLength+1];
		memset(ascii, 0, asciiLength+1);
		// get the ascii value from the scintilla input control
		FromHandle(handleScintillaWindowFind)->SendMessage(SCI_GETTEXT, (WPARAM)asciiLength+1, (LPARAM)ascii);
		// convert ascii to hex
		convertAsciiToHex(ascii, asciiLength, &hex);
		// insert a white space after each two characters
		temp = hex;
		estimatedStringLengthHex = temp.GetLength() + (temp.GetLength() / 2) - 1 + (temp.GetLength() % 2);
		for(int i=2; i<estimatedStringLengthHex; i+=3)
			temp.Insert(i, ' ');
		// make the hex control display the calculated hex value
		textFindHex = temp;
		// transform new hex value to uppercase
		textFindHex.MakeUpper();
		// clean up memory
		delete hex;
		delete ascii;
		
		// *** REPLACE FIELD **********************************
		// get the length of the text in the scintilla control
		asciiLength = FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETLENGTH);
		ascii = new char[asciiLength+1];
		memset(ascii, 0, asciiLength+1);
		// get the ascii value from the scintilla input control
		FromHandle(handleScintillaWindowReplace)->SendMessage(SCI_GETTEXT, (WPARAM)asciiLength+1, (LPARAM)ascii);
		// convert ascii to hex
		convertAsciiToHex(ascii, asciiLength, &hex);
		// insert a white space after each two characters
		temp = hex;
		estimatedStringLengthHex = temp.GetLength() + (temp.GetLength() / 2) - 1 + (temp.GetLength() % 2);
		for(int i=2; i<estimatedStringLengthHex; i+=3)
			temp.Insert(i, ' ');		
		// make the hex control display the calculated hex value
		textReplaceHex = temp;
		// transform new hex value to uppercase
		textReplaceHex.MakeUpper();
		// clean up memory
		delete hex;
		delete ascii;
		GetDlgItem(IDC_EDIT_FIND_HEX)->SetFocus();  
	}

	// set focus to either the hex or the text input field
	if(radioButtonControlText.GetCheck()) {
		::SetFocus(handleScintillaWindowFind);
	}
	else {
		hexEditControlFind.SetFocus();
	}

	UpdateData(false);
}