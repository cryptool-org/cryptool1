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



// Verzeichnis, in dem CT gerade läuft (siehe CrypToolApp.cpp)
extern char *Pfad; // Dangerous, do not write on Pfad
char *defaultSpecialCharacters = ".,:;!?()-+*/[]{}@_><#~=\\\"&%$§";

/////////////////////////////////////////////////////////////////////////////
// TOOLS

const CString ALLOWED_CHARS      (_T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890.,:;!?()-+*/[]{}@_><#~=\\\"&%$§ÄÖÜäöü") );
const CString UPPERCASE_CHARS    (_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ") );
const CString LOWERCASE_CHARS    (_T("abcdefghijklmnopqrstuvwxyz") );
const CString SPECIAL_CHARS      (_T(defaultSpecialCharacters) );
const CString DIGIT_CHARS        (_T("0123456789") );
const CString LOWERCASE_UMLAUTS  (_T("äöü"));
const CString UPPERCASE_UMLAUTS  (_T("ÄÖÜ"));

int check_charset( const CString &alphabet, const CString &charset )
{
   int flags = 0, i;
   for ( i=0; i<charset.GetLength(); i++ )
      if ( 0 > alphabet.Find( charset[i] ) )
         flags |= 1;
      else
         flags |= 2;

   if ( flags & 2 )  return ( flags & 1 ) ? 2 : 1;
   else              return 0;
}

void complete_alphabet( CString &alphabet, const CString &charset )
{
   for ( int i=0; i<charset.GetLength(); i++ )
      if ( 0 > alphabet.Find( charset[i] ) ) alphabet += charset[i];
}

void remove_charset( CString &alphabet, const CString &charset )
{
   for ( int i=0; i<charset.GetLength(); i++ )
      alphabet.Remove( charset[i] );
}

void CDlgTextOptions::updateAlphabetHeading()
{
	LoadString(AfxGetInstanceHandle(),IDS_TEXTOPTIONS_HEADER_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
	char line[256];
	sprintf(line, pc_str, alphabet.GetLength());
	informationAlphabetSize.SetWindowText(line);
}

////////////////////////////////////////////////////////////////////
// CLASS API FUNCTIONS
const CString &CDlgTextOptions::getAlphabet()
{
	return alphabet;
}

int CDlgTextOptions::setAlphabet( CString &new_alphabet )
{
   for ( int i=0; i<new_alphabet.GetLength(); i++ )
      if ( 0 > ALLOWED_CHARS.Find( new_alphabet[i] ) )
         return 0;

   alphabet = new_alphabet;
   updateCheckState();
   return 1;
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

///////////////////////////////////////////////////////////////////////////////
void CDlgTextOptions::SetDefaultOptions()
{
	keepCharactersNotPresentInAlphabetUnchanged = TRUE;
	alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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

////////////////////////////////////////////////////////////////////////
//  WINDOWS DIALOG CONTROL
BOOL CDlgTextOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// save information to return to settings in case user exits the dialog with the Cancel button
	oldKeepCharactersNotPresentInAlphabetUnchanged  = keepCharactersNotPresentInAlphabetUnchanged;
	oldKeepUpperLowerCaseInformation                = keepUpperLowerCaseInformation;
	oldDistinguishUpperLowerCase                    = distinguishUpperLowerCase;
	oldAlphabet                                     = alphabet;
	oldReferenceFile                                = referenceFile;

	updateCheckState();
   UpdateData(FALSE);
	controlEditReferenceFile.SetFocus();
	controlEditReferenceFile.SetSel(0,-1);
	updateAlphabetHeading();

	return TRUE;
}

void CDlgTextOptions::OnCancel() 
{
	// get back to initial settings
	keepCharactersNotPresentInAlphabetUnchanged  = oldKeepCharactersNotPresentInAlphabetUnchanged;
	keepUpperLowerCaseInformation                = oldKeepUpperLowerCaseInformation;
	distinguishUpperLowerCase                    = oldDistinguishUpperLowerCase;
	alphabet                                     = oldAlphabet;
	referenceFile                                = oldReferenceFile;

	CDialog::OnCancel();
}

void CDlgTextOptions::OnOK() 
{
	UpdateData(TRUE);

   ignoreCase = (distinguishUpperLowerCase) ? 0 : 1;
	AppConv.SetAlphabet(alphabet.GetBuffer(257), ignoreCase);

   // UPDATE SCINTILLA ALPHABET HIGHLIGHTING
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

//////////////////////////////////////////////////////////////////////////////
//  WINDOWS DIALOG UPDATE FUNCTIONS 
void CDlgTextOptions::OnUpdateEditAlphabet() 
{
	int i, SS, SE;
	unsigned char c, set[256];
	CString Old;

	controlEditAlphabet.GetSel(SS, SE);
	Old = alphabet;

	UpdateData(TRUE);

   for (int i=0; i<alphabet.GetLength() && !(lowerCase && upperCase); i++)
   {
      if ( 0 <= UPPERCASE_CHARS.Find( alphabet[i] ) ) upperCase = 1;
      if ( 0 <= LOWERCASE_CHARS.Find( alphabet[i] ) ) lowerCase = 1;
      if ( 0 <= UPPERCASE_UMLAUTS.Find( alphabet[i] ) ) { upperCase = 1; umlauts = 1; }
      if ( 0 <= LOWERCASE_UMLAUTS.Find( alphabet[i] ) ) { lowerCase = 1; umlauts = 1; }
   }

   // Set distinguishUpperLowerCase = TRUE -- if (lowerCase && upperCase)
	if( !distinguishUpperLowerCase && (lowerCase && upperCase) ) 
   {
		distinguishUpperLowerCase     = TRUE;
		keepUpperLowerCaseInformation = FALSE;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SWITCH_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONINFORMATION);
	}

   // AVOID doublette chars 
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

   // AVOID not allowed chars
   if(alphabet.GetLength() != alphabet.SpanIncluding(ALLOWED_CHARS).GetLength()) {
		alphabet = Old;
		controlEditAlphabet.SetSel(SS, SE);
		MessageBeep(MB_ICONEXCLAMATION);
	}

   controlEditAlphabet.GetSel(SS, SE);
	updateCheckState();
   UpdateData(FALSE);
	controlEditAlphabet.SetSel(SS, SE);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnButtonRestoreStandard() 
{
	UpdateData(TRUE);
	SetDefaultOptions();
	UpdateData(FALSE);
	updateCheckState();
   UpdateData(FALSE);
	updateAlphabetHeading();
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
   UpdateData(FALSE);
   updateAlphabetHeading();
}

/////////////////////////////////////////////////////////////////
void CDlgTextOptions::OnCheckKeepUpperLowerCaseInformation()
{
	UpdateData(TRUE);	

   if ( upperCase && lowerCase )
   {
      // FIXME: MESSAGE
      keepUpperLowerCaseInformation = FALSE;
      UpdateData( FALSE );
      return;
   }
	// if both check boxes are selected, print an information message
	if(keepUpperLowerCaseInformation && distinguishUpperLowerCase) {
		Message(IDS_TEXTOPTIONS_KEEP_UPPERCASE_LOWERCASE, MB_ICONINFORMATION);
		this->distinguishUpperLowerCase = false;
		this->keepUpperLowerCaseInformation = true;
		UpdateData(false);
	}

	updateAlphabetHeading();
}


////////////////////////////////////////////////////////////////
//    CHECKBOXES FOR CHARSETS
void CDlgTextOptions::OnCheckUpperCase()
{
	if ( !upperCase ) {
      complete_alphabet( alphabet, UPPERCASE_CHARS );
      if ( umlauts ) complete_alphabet( alphabet, UPPERCASE_UMLAUTS );
	}
	else {
      remove_charset( alphabet, UPPERCASE_CHARS );
      remove_charset( alphabet, UPPERCASE_UMLAUTS );
	}
   upperCase = !upperCase;

   UpdateData( FALSE );
   OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnCheckLowerCase()
{
	if ( !lowerCase ) {
      complete_alphabet( alphabet, LOWERCASE_CHARS );
      if ( umlauts ) complete_alphabet( alphabet, LOWERCASE_UMLAUTS );
   }
	else {
      remove_charset( alphabet, LOWERCASE_CHARS );
      remove_charset( alphabet, LOWERCASE_UMLAUTS );
	}
   lowerCase = !lowerCase;

   UpdateData( FALSE );
   OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnCheckUmlauts()
{
	if ( !umlauts ) {
      if ( lowerCase ) complete_alphabet( alphabet, LOWERCASE_UMLAUTS );
      if ( upperCase ) complete_alphabet( alphabet, UPPERCASE_UMLAUTS );
	}
	else {
      remove_charset( alphabet, LOWERCASE_UMLAUTS );
      remove_charset( alphabet, UPPERCASE_UMLAUTS );
	}
   umlauts = !umlauts;

   UpdateData(FALSE);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnCheckSpace()
{
	if ( !space ) 
      complete_alphabet( alphabet, _T(" ") );
	else 
      remove_charset( alphabet, _T(" ") );
   space = !space;

	UpdateData(FALSE);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnCheckPunctuation()
{
	if ( !punctuation ) 
      complete_alphabet( alphabet, SPECIAL_CHARS );
	else 
      remove_charset( alphabet, SPECIAL_CHARS );
   punctuation = !punctuation;

	UpdateData(FALSE);
	updateAlphabetHeading();
}

void CDlgTextOptions::OnCheckDigits()
{
	if ( !digits ) 
      complete_alphabet( alphabet, DIGIT_CHARS );
	else 
      remove_charset( alphabet, DIGIT_CHARS );
   digits = !digits;

	UpdateData(FALSE);
	updateAlphabetHeading();
}

void CDlgTextOptions::updateCheckState()
{
   CString allUmlauts;
   if(upperCase) allUmlauts.Append(UPPERCASE_UMLAUTS);
   if(lowerCase) allUmlauts.Append(LOWERCASE_UMLAUTS);
   umlauts     = check_charset( alphabet, allUmlauts );

   upperCase   = check_charset( alphabet, (umlauts) ? UPPERCASE_CHARS + UPPERCASE_UMLAUTS : UPPERCASE_CHARS );
   lowerCase   = check_charset( alphabet, (umlauts) ? LOWERCASE_CHARS + LOWERCASE_UMLAUTS : LOWERCASE_CHARS );
   space       = check_charset( alphabet, _T(" "));
   punctuation = check_charset( alphabet, SPECIAL_CHARS );
   digits      = check_charset( alphabet, DIGIT_CHARS );
}


