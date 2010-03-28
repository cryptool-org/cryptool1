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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "ChrTools.h"
#include "DialogeMessage.h"
#include "DlgTextOptions.h"
#include "ScintillaDoc.h"
#include "ScintillaView.h"

// we will need this below
char *defaultSpecialCharacters = ".,:;!?()-+*/[]{}@_><#~=\\\"&%$�";

// Verzeichnis, in dem CT gerade l�uft (siehe CrypToolApp.cpp)
extern char *Pfad; // Dangerous, do not write on Pfad


void CDlgTextOptions::SetDefaultOptions()
{
	keepCharactersNotPresentInAlphabetUnchanged = TRUE;
	alphabet = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	distinguishUpperLowerCase = FALSE;
	space = FALSE;
	upperCase = FALSE;
	lowerCase = FALSE;
	punctuation = FALSE;
	digits = FALSE;
	keepUpperLowerCaseInformation = FALSE;
	umlauts = FALSE;

	keepUpperLowerCaseInformation = TRUE;
	ignoreCase = 1;

	LoadString(NULL,IDS_STRING_STANDARD_REF_TEXT,pc_str,STR_LAENGE_STRING_TABLE);
	referenceFile = (!Pfad) ? _T("") : Pfad;
	referenceFile += _T("\\");
	referenceFile.Append(pc_str);
	int pos = referenceFile.ReverseFind('\\');
	title= referenceFile.Mid(pos+1);
}


CDlgTextOptions::CDlgTextOptions(CWnd* pParent)
	: CDialog(CDlgTextOptions::IDD, pParent)
{
	SetDefaultOptions();
}


void CDlgTextOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CDlgTextOptions)
	DDX_Control(pDX, IDC_TEXTOPTIONS_ALPHABET, informationAlphabetSize);
	DDX_Control(pDX, IDC_EDIT_REFERENCE_FILE, controlEditReferenceFile);
	DDX_Control(pDX, IDC_EDIT_ALPHABET, controlEditAlphabet);
	DDX_Check(pDX, IDC_CHECK_KEEP_CHARACTERS_NOT_PRESENT_IN_ALPHABET_UNCHANGED, keepCharactersNotPresentInAlphabetUnchanged);
	DDX_Text(pDX, IDC_EDIT_ALPHABET, alphabet);
	DDX_Check(pDX, IDC_CHECK_DISTINGUISH_UPPER_LOWER_CASE, distinguishUpperLowerCase);
	DDX_Check(pDX, IDC_CHECK_SPACE, space);
	DDX_Check(pDX, IDC_CHECK_UPPER_CASE, upperCase);
	DDX_Check(pDX, IDC_CHECK_LOWER_CASE, lowerCase);
	DDX_Check(pDX, IDC_CHECK_PUNCTUATION, punctuation);
	DDX_Check(pDX, IDC_CHECK_DIGITS, digits);
	DDX_Check(pDX, IDC_CHECK_KEEP_UPPER_LOWER_CASE_INFORMATION, keepUpperLowerCaseInformation);
	DDX_Check(pDX, IDC_CHECK_UMLAUTS, umlauts);
	DDX_Text(pDX, IDC_EDIT_REFERENCE_FILE, referenceFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTextOptions, CDialog)

	//{{AFX_MSG_MAP(CDlgTextOptions)
	ON_EN_UPDATE(IDC_EDIT_ALPHABET, OnUpdateEditAlphabet)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE_STANDARD, OnButtonRestoreStandard)
	ON_BN_CLICKED(IDC_CHECK_DISTINGUISH_UPPER_LOWER_CASE, OnCheckDistinguishUpperLowerCase)
	ON_BN_CLICKED(IDC_CHECK_UPPER_CASE, OnCheckUpperCase)
	ON_BN_CLICKED(IDC_CHECK_LOWER_CASE, OnCheckLowerCase)
	ON_BN_CLICKED(IDC_CHECK_SPACE, OnCheckSpace)
	ON_BN_CLICKED(IDC_CHECK_PUNCTUATION, OnCheckPunctuation)
	ON_BN_CLICKED(IDC_CHECK_DIGITS, OnCheckDigits)
	ON_BN_CLICKED(IDC_CHECK_KEEP_UPPER_LOWER_CASE_INFORMATION, OnCheckKeepUpperLowerCaseInformation)
	ON_BN_CLICKED(IDC_CHECK_UMLAUTS, OnCheckUmlauts)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_REFERENCE_FILE, OnButtonSearchReferenceFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgTextOptions  

#define ALLOWED_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890.,:;!?()-+*/[]{}@_><#~=\\\"&%$�������"

const CString &CDlgTextOptions::getAlphabet()
{
	return alphabet;
}

CString &CDlgTextOptions::refAlphabet()
{
	return alphabet;
}

void CDlgTextOptions::getAlphabetWithOptions(CString &AlphabetWithOptions)
{
	AlphabetWithOptions = alphabet;
	if ( !distinguishUpperLowerCase )
	{
		for (int i=0; i<alphabet.GetLength(); i++)
		{
			if ( (alphabet[i] >= 'A' && alphabet[i] <= 'Z') && (0 > alphabet.Find(alphabet[i] + ('a'-'A'))) )
				AlphabetWithOptions += (char)(alphabet[i] + ('a'-'A'));
			if ( (alphabet[i] >= 'a' && alphabet[i] <= 'z') && (0 > alphabet.Find(alphabet[i] - ('a'-'A'))) )
				AlphabetWithOptions += (char)(alphabet[i] - ('a'-'A'));
		}
	}
}

void CDlgTextOptions::OnUpdateEditAlphabet() 
{
	int i, SS, SE;
	unsigned char c, set[256];
	CString Old;

	controlEditAlphabet.GetSel(SS, SE);
	Old = alphabet;

	UpdateData(TRUE);

	if(!distinguishUpperLowerCase) {
		for(i=0;i<alphabet.GetLength();i++) {
			if(MyIsLower(alphabet[i])) {
				distinguishUpperLowerCase=TRUE;
				keepUpperLowerCaseInformation = FALSE;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SWITCH_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
				theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONINFORMATION);
				break;
			}
		}
	}

	memset(set,0,sizeof(set));
	for(i=0;i<alphabet.GetLength();i++) {
		c = alphabet[i];
		if(set[c]) {
			alphabet = Old;
			controlEditAlphabet.SetSel(SS, SE);
			MessageBeep(MB_ICONEXCLAMATION);
			break;
		}
		set[c]=1;
	}
	if(alphabet.GetLength() != alphabet.SpanIncluding(ALLOWED_CHARS).GetLength()) {
			alphabet = Old;
			controlEditAlphabet.SetSel(SS, SE);
			MessageBeep(MB_ICONEXCLAMATION);
	}
	controlEditAlphabet.GetSel(SS, SE);
	updateCheckState();
	controlEditAlphabet.SetSel(SS, SE);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnButtonRestoreStandard() 
{
	UpdateData(TRUE);
	SetDefaultOptions();
	UpdateData(FALSE);
	updateCheckState();
	updateAlphabetHeading();
}

BOOL CDlgTextOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// save information to return to settings in case user exits the dialog with the Cancel button
	oldKeepCharactersNotPresentInAlphabetUnchanged = keepCharactersNotPresentInAlphabetUnchanged;
	oldKeepUpperLowerCaseInformation = keepUpperLowerCaseInformation;
	oldDistinguishUpperLowerCase = distinguishUpperLowerCase;
	oldAlphabet = alphabet;
	oldReferenceFile = referenceFile;

	updateCheckState();

	controlEditReferenceFile.SetFocus();
	controlEditReferenceFile.SetSel(0,-1);

	updateAlphabetHeading();

	return TRUE;
}

void CDlgTextOptions::OnCancel() 
{
	// get back to initial settings
	keepCharactersNotPresentInAlphabetUnchanged = oldKeepCharactersNotPresentInAlphabetUnchanged;
	keepUpperLowerCaseInformation = oldKeepUpperLowerCaseInformation;
	distinguishUpperLowerCase = oldDistinguishUpperLowerCase;
	alphabet = oldAlphabet;
	referenceFile = oldReferenceFile;

	CDialog::OnCancel();
}

void CDlgTextOptions::OnCheckDistinguishUpperLowerCase()
{
	int i, r;
	UpdateData(TRUE);

	// if both check boxes are selected, print an information message
	if(keepUpperLowerCaseInformation && distinguishUpperLowerCase) {
		Message(IDS_TEXTOPTIONS_KEEP_UPPERCASE_LOWERCASE, MB_ICONINFORMATION);
		this->distinguishUpperLowerCase = true;
		this->keepUpperLowerCaseInformation = false;
		UpdateData(false);
	}

	if(!distinguishUpperLowerCase) {
		alphabet.MakeUpper();
		for(i=0;i<alphabet.GetLength();i++) {
			r = alphabet.ReverseFind(alphabet[i]);
			if(r>i) alphabet = alphabet.Left(r) + alphabet.Right(alphabet.GetLength() - r - 1);
		}
	}
	else {
		keepUpperLowerCaseInformation = FALSE;
	}
	updateCheckState();
	updateAlphabetHeading();
}

void CDlgTextOptions::OnOK() 
{
	UpdateData(TRUE);

	if(distinguishUpperLowerCase) ignoreCase = 0;
	else ignoreCase = 1;

	AppConv.SetAlphabet(alphabet.GetBuffer(257), ignoreCase);
	CWnd m_wndMDIClient;
	CMDIFrameWnd *m_MDIFrameWnd = (CMDIFrameWnd*)theApp.m_MainWnd;
	int ret = m_wndMDIClient.Attach(m_MDIFrameWnd->m_hWndMDIClient);
	ASSERT(ret != 0);
	CWnd *pWndCurrentChild = m_wndMDIClient.GetWindow(GW_CHILD);
	while (pWndCurrentChild) {
		if (pWndCurrentChild->IsKindOf(RUNTIME_CLASS(CMDIChildWnd))) {
			TRACE0("CMDIChildWnd");
			CView *cview = ((CMDIChildWnd*)pWndCurrentChild)->GetActiveView();
			if (cview && cview->IsKindOf(RUNTIME_CLASS(CScintillaView)))
				((CScintillaView*)cview)->RefreshAlphabet();
		}

		pWndCurrentChild = (CMDIChildWnd*)pWndCurrentChild->GetWindow(GW_HWNDNEXT);
	}
	m_wndMDIClient.Detach();
	CDialog::OnOK();
}

void CDlgTextOptions::OnCheckUpperCase()
{
	char c;
	int i;

	if(upperCase != 1) {
		for(c='A';c<='Z';c++) {
			if(-1 == alphabet.Find(c))
				alphabet += c;
		}
		upperCase = 1;
	}
	else {
		for(c='A';c<='Z';c++) {
			if(-1 != (i=alphabet.Find(c)))
				alphabet = alphabet.Left(i) + alphabet.Right(alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		}
		upperCase = 0;

		// if umlauts were part of the alphabet, remove them
		alphabet.Remove('�');
		alphabet.Remove('�');
		alphabet.Remove('�');
	}
	UpdateData(FALSE);

	updateCheckState();
	updateAlphabetHeading();
}


void CDlgTextOptions::OnCheckLowerCase()
{
	char c;
	int i;

	if(1 != lowerCase) {
		for(c='a';c<='z';c++) {
			if(-1 == alphabet.Find(c))
				alphabet += c;
		}
		distinguishUpperLowerCase = TRUE;
		keepUpperLowerCaseInformation = FALSE;
		lowerCase = 1;
	}
	else {
		for(c='a';c<='z';c++) {
			if(-1 != (i=alphabet.Find(c)))
				alphabet = alphabet.Left(i) + alphabet.Right(alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		}
		lowerCase = 0;

		// if umlauts were part of the alphabet, remove them
		alphabet.Remove('�');
		alphabet.Remove('�');
		alphabet.Remove('�');

	}
	UpdateData(FALSE);

	updateCheckState();
	updateAlphabetHeading();
}

void CDlgTextOptions::OnCheckUmlauts()
{
	// if not checked, add umlauts
	if(umlauts != 1) {
		// caps
		if(upperCase) {
			if(alphabet.Find('�') == -1) alphabet += '�';
			if(alphabet.Find('�') == -1) alphabet += '�';
			if(alphabet.Find('�') == -1) alphabet += '�';
		}
		// non-caps
		if(lowerCase) {
			if(alphabet.Find('�') == -1) alphabet += '�';
			if(alphabet.Find('�') == -1) alphabet += '�';
			if(alphabet.Find('�') == -1) alphabet += '�';
		}
		umlauts = 1;

		// set umlauts to "0" if we have neither upper nor lower case checked
		if(!upperCase && !lowerCase) {
			umlauts = 0;
		}
	}
	// else: remove umlauts (caps and non-caps)
	else {
		alphabet.Remove('�');
		alphabet.Remove('�');
		alphabet.Remove('�');
		alphabet.Remove('�');
		alphabet.Remove('�');		
		alphabet.Remove('�');		
		umlauts = 0;
	}

	UpdateData(false);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnCheckSpace()
{
	int i;

	if(space == FALSE) {
		if(-1 == alphabet.Find(' '))
			alphabet += ' ';
		space = TRUE;
	}
	else {
		if(-1 != (i=alphabet.Find(' ')))
			alphabet = alphabet.Left(i) + alphabet.Right(alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		space = FALSE;
	}
	UpdateData(FALSE);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnCheckPunctuation()
{
	char *s;
	int i;

	if(punctuation != 1) {
		for(s=defaultSpecialCharacters ;*s;s++) {
			if(-1 == alphabet.Find(*s))
				alphabet += *s;
		}
		punctuation = 1;
	}
	else {
		for(s=defaultSpecialCharacters;*s;s++) {
			if(-1 != (i=alphabet.Find(*s)))
				alphabet = alphabet.Left(i) + alphabet.Right(alphabet.GetLength() - i - 1); // ein Zeichen gefunden
		}
		punctuation = 0;
	}
	UpdateData(FALSE);
	updateAlphabetHeading();
}


void CDlgTextOptions::updateCheckState()
{
	char c, *s;
	int OK;

	// update upper case
	OK = 0;
	for(c='A';c<='Z';c++) {
		if(-1 == alphabet.Find(c))
			OK |= 1;
		else
			OK |= 2;
	}
	switch(OK) {
	case(1): upperCase = 0;
		break;
	case(2): upperCase = 1;
		break;
	case(3): upperCase = 2;
	}

	// update space 
	if(-1 == alphabet.Find(' '))
			space = FALSE;
		else
			space = TRUE;
	
	// update lower case
	OK = 0;
	for(c='a';c<='z';c++) {
		if(-1 == alphabet.Find(c))
			OK |= 1;
		else
			OK |= 2;
	}
	switch(OK) {
	case(1): lowerCase = 0;
		break;
	case(2): lowerCase = 1;
		break;
	case(3): lowerCase = 2;
	}


	// update punctuation
	OK = 0;
	for(s=defaultSpecialCharacters;*s;s++) {
		if(-1 == alphabet.Find(*s))
			OK |= 1;
		else
			OK |= 2;
	}
	switch(OK) {
	case(1): punctuation = 0;
		break;
	case(2): punctuation = 1;
		break;
	case(3): punctuation = 2;
	}

	// update digits
	OK = 0;
	for(c='0';c<='9'; c++) {
		if(-1 == alphabet.Find(c))
			OK |= 1;
		else
			OK |= 2;
	}

	switch(OK) {
	case(1): digits = 0;
		break;
	case(2): digits = 1;
		break;
	case(3): digits = 2;
	}

	// update umlauts
	OK = 0;
	CString allUmlauts;
	if(upperCase) allUmlauts.Append("���");
	if(lowerCase) allUmlauts.Append("���");
	for(int i=0; i<allUmlauts.GetLength(); i++) {
		if(alphabet.Find(allUmlauts[i]) == -1) OK |= 1;
		else OK |= 2;
	}

	switch(OK) {
		case 1:
			umlauts = 0;
			break;
		case 2:
			umlauts = 1;
			break;
		case 3:
			umlauts = 2;
			break;
		default:
			umlauts = 0;
			break;
	}

	UpdateData(FALSE);
}

void CDlgTextOptions::OnCheckDigits()
{
	char c;
	int i;

	if(digits != 1) {
		for(c='0';c<='9';c++) {
			if(-1 == alphabet.Find(c))
				alphabet += c;
		}
		digits = 1;
	}
	else {
		for(c='0';c<='9';c++) {
			if(-1 != (i=alphabet.Find(c)))
				alphabet = alphabet.Left(i) + alphabet.Right(alphabet.GetLength() - i - 1);
		}
		digits = 0;
	}
	UpdateData(FALSE);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnCheckKeepUpperLowerCaseInformation()
{
	UpdateData(TRUE);	

	// if both check boxes are selected, print an information message
	if(keepUpperLowerCaseInformation && distinguishUpperLowerCase) {
		Message(IDS_TEXTOPTIONS_KEEP_UPPERCASE_LOWERCASE, MB_ICONINFORMATION);
		this->distinguishUpperLowerCase = false;
		this->keepUpperLowerCaseInformation = true;
		UpdateData(false);
	}

	updateAlphabetHeading();
}

void CDlgTextOptions::OnButtonSearchReferenceFile() 
{
	OPENFILENAME ofn;
	char fname[257], ftitle[128];
	const char* s_FileFilter = "text files (*.txt)\0*.txt\0all files\0*.*;*\0\0";

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_CHOOSE_REF_FILENAME,pc_str,STR_LAENGE_STRING_TABLE);
	ofn.lpstrTitle = pc_str;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofn.lpstrFile = fname;
	sprintf(fname, "*.txt");
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;
	ofn.lpstrFilter = s_FileFilter;

	// set initial directory to be the directory in which the last reference file was found
	if(referenceFile.GetLength() != 0) {
		// delete everything after the last backslash ('\')
		int index = referenceFile.ReverseFind('\\');
		if(index != -1) {
			CString directory = referenceFile;
			directory.Delete(index, directory.GetLength() - index);
			ofn.lpstrInitialDir = directory;
		}
	}

	ftitle[0] = 0;
	ofn.nMaxFileTitle = sizeof(ftitle)-1;
	if(!GetOpenFileName(&ofn)) return;
	if(fname[0]==0) return;
	
	UpdateData(TRUE);
	referenceFile=fname;
	title = ofn.lpstrFileTitle;
	UpdateData(FALSE);
	controlEditReferenceFile.SetFocus();
	controlEditReferenceFile.SetSel(0,-1);
	GotoDlgCtrl( GetDlgItem(IDC_BUTTON_SEARCH_REFERENCE_FILE));
}

void CDlgTextOptions::updateAlphabetHeading()
{
	LoadString(AfxGetInstanceHandle(),IDS_TEXTOPTIONS_HEADER_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
	char line[256];
	sprintf(line, pc_str, alphabet.GetLength());
	informationAlphabetSize.SetWindowText(line);
}