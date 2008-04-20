/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/

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

// global vector for previously used FIND terms
std::vector<CString> termsFind;
// global vector for previously used REPLACE terms
std::vector<CString> termsReplace;

// this function returns true if the input string (which is the output string also) 
// could be converted from hex to ascii; in case the hex string contains a zero byte (00),
// the string is cut off at that place and the function returns false
bool convertHexStringToAsciiString(CString &text) {
	// this is the string to be returned
	CString result = "";

	for(int i=0; i<text.GetLength(); i+=2) {
		char hex[5];
		hex[0] = '0';
		hex[1] = 'x';
		hex[2] = text[i+0];
		hex[3] = text[i+1];
		hex[4] = 0;
		result.AppendChar(strtol(hex, 0, 16));
	}

	text = result;

	return true;
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
	DDX_CBString(pDX, IDC_COMBO_FIND, textFind);
	DDX_CBString(pDX, IDC_COMBO_REPLACE, textReplace);
	DDX_Text(pDX, IDC_EDIT_FIND_HEX, textFindHex);
	DDX_Text(pDX, IDC_EDIT_REPLACE_HEX, textReplaceHex);
	DDX_Check(pDX, IDC_CHECK_CASE_SENSITIVE, checkCaseSensitive);
	DDX_Check(pDX, IDC_CHECK_FIND_BACKWARDS, checkFindBackwards);
	DDX_Check(pDX, IDC_CHECK_REGULAR_EXPRESSIONS, checkRegularExpressions);
	DDX_Control(pDX, IDC_COMBO_FIND, comboBoxControlFind);
	DDX_Control(pDX, IDC_COMBO_REPLACE, comboBoxControlReplace);
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
	// store find term
	addFindTerm(textFind);
	addReplaceTerm(textReplace);

	// return if there is no search term in the selected mode
	if(	(textFind.GetLength() == 0 && radioButtonControlText.GetCheck() == 1) ||
		(textFindHex.GetLength() == 0 && radioButtonControlHex.GetCheck() == 1) ) 
		return;
	
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
		// prevent activation of search of regular expressions in hex edit
		CString msg;
		if(checkRegularExpressions)
		{
			msg.Format(IDS_FINDANDREPLACE_NOREGULAREXPRESSIONS_IN_HEX);
			MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
			return;
		}

		DoFindReplaceHexEdit(pWndView->GetTopWindow(), replace, all);
	} 

	// update find and replace terms
	insertOldFindAndReplaceTerms();
}

void CDlgFindAndReplace::DoFindReplaceScintilla(CWnd *pWnd, bool replace, bool all)
{
	// these are the strings used to search and replace text
	CString stringFind;
	CString stringReplace;

	// before we start the search, we have to figure out which mode is set:
	// if we're in hex mode, we need to convert the hex input in text
	// if we're in text mode, we don't need to make any adjustments
	if(radioButtonControlHex.GetCheck() == 1) {
		// assign the user input
		stringFind = textFindHex;
		stringReplace = textReplaceHex;
		// we need to remove space characters from the input
		stringFind.Remove(' ');
		stringReplace.Remove(' ');
		// now convert the hex string into an ascii string, and notify the user that, 
		// in case the input contains zero bytes (00), the input is cut off
		if(!convertHexStringToAsciiString(stringFind)) {
			// TODO
			MessageBox("TODO: find string was cut off");
		}
		if(!convertHexStringToAsciiString(stringReplace)) {
			// TODO
			MessageBox("TODO: replace string was cut off");
		}
	}
	else {
		// assign the user input 
		stringFind = textFind;
		stringReplace = textReplace;
	}

	ASSERT(pWnd);

	CScintillaWnd *pWindow = (CScintillaWnd*)pWnd;
	CString msg;
	int searchflags = 0;
	if (checkCaseSensitive) searchflags |= SCFIND_MATCHCASE;
	if (checkRegularExpressions) searchflags |= SCFIND_REGEXP;
	pWindow->SetSearchflags(searchflags);
	char *ttf = stringFind.GetBuffer();
	char *ttr = stringReplace.GetBuffer();

	// *** REPLACE (SINGLE REPLACE) ***
	if (replace && !all)
	{
		long pStart = pWindow->GetSelectionStart();
		long pEnd   = pWindow->GetSelectionEnd();

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
				msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
				MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
				return;
			}
		}
		// backward search
		else
		{
			if(!pWindow->SearchBackward(ttf)) {
				msg.Format(IDS_FINDANDREPLACE_TEXTNOTFOUND);
				MessageBox(msg, "CrypTool", MB_ICONINFORMATION);
				return;
			}
		}
	}
	textFind.ReleaseBuffer(); ttf = 0;
	textReplace.ReleaseBuffer(); ttr = 0;
}

void CDlgFindAndReplace::DoFindReplaceHexEdit(CWnd *pWnd, bool replace, bool all)
{
	// these are the strings used to search and replace text
	CString stringFind;
	CString stringReplace;

	// before we start the search, we have to figure out which mode is set:
	// if we're in hex mode, we need to convert the hex input in text
	// if we're in text mode, we don't need to make any adjustments
	if(radioButtonControlHex.GetCheck() == 1) {
		// assign the user input
		stringFind = textFindHex;
		stringReplace = textReplaceHex;
		// we need to remove space characters from the input
		stringFind.Remove(' ');
		stringReplace.Remove(' ');
		// now convert the hex string into an ascii string, and notify the user that, 
		// in case the input contains zero bytes (00), the input is cut off
		if(!convertHexStringToAsciiString(stringFind)) {
			// TODO
			MessageBox("TODO: find string was cut off");
		}
		if(!convertHexStringToAsciiString(stringReplace)) {
			// TODO
			MessageBox("TODO: find string was cut off");
		}
	}
	else {
		// assign the user input 
		stringFind = textFind;
		stringReplace = textReplace;
	}

	ASSERT(pWnd);

	CHexEditBase *pWindow = (CHexEditBase*)pWnd;
	CString msg;
	int searchflags = 0;
	if (checkCaseSensitive) searchflags |= HE_FIND_MATCHCASE;
	if (checkFindBackwards) searchflags |= HE_FIND_BACKWARDS;
	
	LPCSTR pfind = (LPCSTR)stringFind;
	int findlen = stringFind.GetLength();
	LPCSTR preplace = (LPCSTR)stringReplace;
	int replacelen = stringReplace.GetLength();

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

// add FIND term to vector (no doubled entries)
void CDlgFindAndReplace::addFindTerm(CString _term)
{
	// FM, 12.03.2007 ATTENTION: insertion is done in REVERSED order now, 
	// that means new entries are inserted AT THE BEGINNING of the list

	// look for existing entries...
	std::vector <CString>::iterator Iter;

	for(Iter = termsFind.begin(); Iter != termsFind.end(); Iter++)
		if(*Iter == _term) 
		{   // if the term is in history then erase it (because it will be inserted at first place)
			termsFind.erase(Iter);
			break;
		}
	// ...or insert new one
	termsFind.insert(termsFind.begin(), _term);
}

// add REPLACE term to vector (no doubled entries)
void CDlgFindAndReplace::addReplaceTerm(CString _term)
{
	// FM, 12.03.2007 ATTENTION: insertion is done in REVERSED order now, 
	// that means new entries are inserted AT THE BEGINNING of the list

	std::vector <CString>::iterator Iter;
	// look for existing entries...
	for(Iter=termsReplace.begin(); Iter != termsReplace.end(); Iter++)
		if( *Iter == _term) 
		{
			termsReplace.erase(Iter);
			break;
		}
	// ...or insert new one
	termsReplace.insert(termsReplace.begin(), _term);
}

BOOL CDlgFindAndReplace::OnInitDialog()
{
	CDialog::OnInitDialog();

	insertOldFindAndReplaceTerms();

	// we're in text mode (not hex) by default
	radioButtonControlText.SetCheck(1);
	updateMode();

	UpdateData(false);

	return TRUE;
}

void CDlgFindAndReplace::insertOldFindAndReplaceTerms()
{
	// remove former entries in both boxes
	comboBoxControlFind.ResetContent();
	comboBoxControlReplace.ResetContent();

	// insert former FIND terms into combo box...
	for(unsigned int i=0; i<termsFind.size(); i++)
		comboBoxControlFind.InsertString(-1, termsFind[i]);
	// insert former REPLACE terms into combo box...
	for(unsigned int j=0; j<termsReplace.size(); j++)
		comboBoxControlReplace.InsertString(-1, termsReplace[j]);

	// select the last FIND term in the combox box
	if(termsFind.size() > 0) comboBoxControlFind.SelectString(-1, *termsFind.begin());
    // select the last REPLACE term in the combo box
	if(termsReplace.size() > 0) comboBoxControlReplace.SelectString(-1, *termsReplace.begin());
}

void CDlgFindAndReplace::show()
{
	if(!created)
	{
		Create(IDD_FIND_AND_REPLACE);
		created = true;
	}

	insertOldFindAndReplaceTerms();

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
		GetDlgItem(IDC_COMBO_FIND)->EnableWindow(true);
		GetDlgItem(IDC_COMBO_FIND)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBO_REPLACE)->EnableWindow(true);
		GetDlgItem(IDC_COMBO_REPLACE)->ShowWindow(SW_SHOW);
		// disable hex-related input fields	
		GetDlgItem(IDC_EDIT_FIND_HEX)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_FIND_HEX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->EnableWindow(false);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->ShowWindow(SW_HIDE);
	}

	// we're in hex mode...
	if(radioButtonControlHex.GetCheck()) {
		// enable hex-related input fields
		GetDlgItem(IDC_EDIT_FIND_HEX)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_FIND_HEX)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->EnableWindow(true);
		GetDlgItem(IDC_EDIT_REPLACE_HEX)->ShowWindow(SW_SHOW);
		// disable text-related input fields
		GetDlgItem(IDC_COMBO_FIND)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_FIND)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_REPLACE)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_REPLACE)->ShowWindow(SW_HIDE);
	}

	UpdateData(false);
}