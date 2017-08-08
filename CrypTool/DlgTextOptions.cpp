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

extern char *Pfad;

int check_charset(const CString &alphabet, const CString &charset) {
   int flags = 0, i;
   for ( i=0; i<charset.GetLength(); i++ )
      if ( 0 > alphabet.Find( charset[i] ) )
         flags |= 1;
      else
         flags |= 2;

   if ( flags & 2 )  return ( flags & 1 ) ? 2 : 1;
   else              return 0;
}

void complete_alphabet(CString &alphabet, const CString &charset) {
   for ( int i=0; i<charset.GetLength(); i++ )
      if ( 0 > alphabet.Find( charset[i] ) ) alphabet += charset[i];
}

void remove_charset(CString &alphabet, const CString &charset) {
   for ( int i=0; i<charset.GetLength(); i++ )
      alphabet.Remove( charset[i] );
}

//////////////////////////////////////
// FUNCTIONS FOR CDlgTextOptions CLASS
//////////////////////////////////////

CDlgTextOptions::CDlgTextOptions(CWnd* pParent) :
	CDialog(CDlgTextOptions::IDD, pParent) {
	
}

CDlgTextOptions::~CDlgTextOptions() {

}

void CDlgTextOptions::initialize() {
	restoreDefaultOptions();
}

const CString &CDlgTextOptions::getAlphabet() const {
	return options.alphabet;
}

CString &CDlgTextOptions::getAlphabetReference() {
	return options.alphabet;
}

CString CDlgTextOptions::getAlphabetWithOptions() const {
	// TODO/FIXME: Don't we want to apply *ALL* options instead of just upper/lower case?!?
	CString alphabetWithOptions = options.alphabet;
	if(!options.distinguishUpperLowerCase) {
		for(int i=0; i<options.alphabet.GetLength(); i++) {
			if((options.alphabet[i] >= 'A' && options.alphabet[i] <= 'Z') && (0 > options.alphabet.Find(options.alphabet[i] + ('a'-'A')))) {
				alphabetWithOptions += (char)(options.alphabet[i] + ('a'-'A'));
			}
			if((options.alphabet[i] >= 'a' && options.alphabet[i] <= 'z') && (0 > options.alphabet.Find(options.alphabet[i] - ('a'-'A')))) {
				alphabetWithOptions += (char)(options.alphabet[i] - ('a'-'A'));
			}
		}
	}
	return alphabetWithOptions;
}

bool CDlgTextOptions::setAlphabet(const CString &_alphabet) {
	for(int i=0; i<_alphabet.GetLength(); i++) {
		if(getAllowedCharacters().Find(_alphabet[i]) < 0) {
			return false;
		}
	}
	options.alphabet = _alphabet;
	updateCheckState();
	return true;
}

CString CDlgTextOptions::getReferenceFilePath() const {
	return options.referenceFile;
}

CString CDlgTextOptions::getReferenceFileName() const {
	const int position = options.referenceFile.ReverseFind('\\');
	const CString name = options.referenceFile.Mid(position + 1);
	return name;
}

CString CDlgTextOptions::getAllowedCharacters() const {
	return CString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890.,:;!?()-+*/[]{}@_><#~=\\\"&%$§ÄÖÜäöü");
}

CString CDlgTextOptions::getUpperCaseCharacters() const {
	return CString("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

CString CDlgTextOptions::getLowerCaseCharacters() const {
	return CString("abcdefghijklmnopqrstuvwxyz");
}

CString CDlgTextOptions::getSpecialCharacters() const {
	return CString(".,:;!?()-+*/[]{}@_><#~=\\\"&%$§");
}

CString CDlgTextOptions::getDigitCharacters() const {
	return CString("0123456789");
}

CString CDlgTextOptions::getUpperCaseUmlautCharacters() const {
	return CString("ÄÖÜ");
}

CString CDlgTextOptions::getLowerCaseUmlautCharacters() const {
	return CString("äöü");
}

BOOL CDlgTextOptions::OnInitDialog() {
	CDialog::OnInitDialog();
	// Copy the "current options" to the "old options" to allow a reset of the 
	// options to their old values when the user closes the dialog using "Cancel".
	copyOptions(options, optionsOld);
	// Update the user interface.
	updateReferenceFiles(options);
	updateButtonOK();
	updateCheckState();
	UpdateData(FALSE);
	controlEditReferenceFile.SetFocus();
	controlEditReferenceFile.SetSel(0,-1);
	updateEditAlphabetHeading();
	return TRUE;
}

void CDlgTextOptions::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_KEEP_CHARACTERS_NOT_PRESENT_IN_ALPHABET_UNCHANGED, options.keepCharactersNotPresentInAlphabetUnchanged);
	DDX_Check(pDX, IDC_CHECK_KEEP_UPPER_LOWER_CASE_INFORMATION, options.keepUpperLowerCaseInformation);
	DDX_Check(pDX, IDC_CHECK_DISTINGUISH_UPPER_LOWER_CASE, options.distinguishUpperLowerCase);
	DDX_Check(pDX, IDC_CHECK_UPPER_CASE, options.alphabetUpperCase);
	DDX_Check(pDX, IDC_CHECK_LOWER_CASE, options.alphabetLowerCase);
	DDX_Check(pDX, IDC_CHECK_SPACE, options.alphabetSpace);
	DDX_Check(pDX, IDC_CHECK_PUNCTUATION, options.alphabetSpecial);
	DDX_Check(pDX, IDC_CHECK_DIGITS, options.alphabetDigits);
	DDX_Check(pDX, IDC_CHECK_UMLAUTS, options.alphabetUmlauts);
	DDX_Control(pDX, IDC_TEXTOPTIONS_ALPHABET, controlEditAlphabetHeading);
	DDX_Control(pDX, IDC_EDIT_ALPHABET, controlEditAlphabet);
	DDX_Text(pDX, IDC_EDIT_ALPHABET, options.alphabet);
	DDX_Control(pDX, IDC_EDIT_REFERENCE_FILE, controlEditReferenceFile);
	DDX_Text(pDX, IDC_EDIT_REFERENCE_FILE, options.referenceFile);
	DDX_Control(pDX, IDC_COMBO_SELECT_REFERENCE_FILE, controlComboBoxSelectReferenceFile);
}

BEGIN_MESSAGE_MAP(CDlgTextOptions, CDialog)
	ON_BN_CLICKED(IDC_CHECK_KEEP_CHARACTERS_NOT_PRESENT_IN_ALPHABET_UNCHANGED, OnCheckKeepCharactersNotPresentInAlphabetUnchanged)
	ON_BN_CLICKED(IDC_CHECK_KEEP_UPPER_LOWER_CASE_INFORMATION, OnCheckKeepUpperLowerCaseInformation)
	ON_BN_CLICKED(IDC_CHECK_DISTINGUISH_UPPER_LOWER_CASE, OnCheckDistinguishUpperLowerCase)
	ON_BN_CLICKED(IDC_CHECK_UPPER_CASE, OnCheckUpperCase)
	ON_BN_CLICKED(IDC_CHECK_LOWER_CASE, OnCheckLowerCase)
	ON_BN_CLICKED(IDC_CHECK_SPACE, OnCheckSpace)
	ON_BN_CLICKED(IDC_CHECK_PUNCTUATION, OnCheckSpecial)
	ON_BN_CLICKED(IDC_CHECK_DIGITS, OnCheckDigits)
	ON_BN_CLICKED(IDC_CHECK_UMLAUTS, OnCheckUmlauts)
	ON_EN_UPDATE(IDC_EDIT_ALPHABET, OnUpdateEditAlphabet)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_REFERENCE_FILE, OnButtonSearchReferenceFile)
	ON_CBN_SELENDOK(IDC_COMBO_SELECT_REFERENCE_FILE, OnComboSelectReferenceFile)
	ON_BN_CLICKED(IDOK, OnButtonOK)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE_STANDARD, OnButtonRestoreStandard)
	ON_BN_CLICKED(IDCANCEL, OnButtonCancel)
END_MESSAGE_MAP()

void CDlgTextOptions::OnCheckKeepCharactersNotPresentInAlphabetUnchanged() {
	UpdateData(true);
	// TODO/FIXME
	UpdateData(false);
}

void CDlgTextOptions::OnCheckKeepUpperLowerCaseInformation() {
	UpdateData(true);
	if(options.alphabetUpperCase && options.alphabetLowerCase) {
		options.keepUpperLowerCaseInformation = 0;
		UpdateData(false);
		return;
	}
	else if(options.keepUpperLowerCaseInformation && options.distinguishUpperLowerCase) {
		Message(IDS_TEXTOPTIONS_KEEP_UPPERCASE_LOWERCASE, MB_ICONINFORMATION);
		options.distinguishUpperLowerCase = 0;
		options.keepUpperLowerCaseInformation = 1;
		UpdateData(false);
		OnCheckDistinguishUpperLowerCase();
	}
	updateEditAlphabetHeading();
}

void CDlgTextOptions::OnCheckDistinguishUpperLowerCase() {
	UpdateData(true);
	if(options.keepUpperLowerCaseInformation && options.distinguishUpperLowerCase) {
		Message(IDS_TEXTOPTIONS_KEEP_UPPERCASE_LOWERCASE, MB_ICONINFORMATION);
		options.distinguishUpperLowerCase = 1;
		options.keepUpperLowerCaseInformation = 0;
		UpdateData(false);
	}
	int i, r;
	if(!options.distinguishUpperLowerCase) {
		options.alphabet.MakeUpper();
		for(i=0;i<options.alphabet.GetLength();i++) {
			r = options.alphabet.ReverseFind(options.alphabet[i]);
			if(r>i) options.alphabet = options.alphabet.Left(r) + options.alphabet.Right(options.alphabet.GetLength() - r - 1);
		}
	}
	else {
		options.keepUpperLowerCaseInformation = 0;
	}
	updateCheckState();
	updateEditAlphabetHeading();
	UpdateData(false);
}

void CDlgTextOptions::OnCheckUpperCase() {
	UpdateData(true);
	if(options.alphabetUpperCase == 1) {
		complete_alphabet(options.alphabet, getUpperCaseCharacters());
		if(options.alphabetUmlauts) {
			complete_alphabet(options.alphabet, getUpperCaseUmlautCharacters());
		}
	}
	else {
		options.alphabetUpperCase = 0;
		remove_charset(options.alphabet, getUpperCaseCharacters());
		remove_charset(options.alphabet, getUpperCaseUmlautCharacters());
	}
	UpdateData(false);
	OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnCheckLowerCase() {
	UpdateData(true);
	if(options.alphabetLowerCase == 1) {
		complete_alphabet(options.alphabet, getLowerCaseCharacters());
		if(options.alphabetUmlauts) {
			complete_alphabet(options.alphabet, getLowerCaseUmlautCharacters());
		}
	}
	else {
		options.alphabetLowerCase = 0;
		remove_charset(options.alphabet, getLowerCaseCharacters());
		remove_charset(options.alphabet, getLowerCaseUmlautCharacters());
	}
	UpdateData(false);
	OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnCheckSpace() {
	UpdateData(true);
	if(options.alphabetSpace == 1) {
		complete_alphabet(options.alphabet, " ");
	}
	else {
		options.alphabetSpace = 0;
		remove_charset(options.alphabet, " ");
	}
	UpdateData(false);
	OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnCheckSpecial() {
	UpdateData(true);
	if(options.alphabetSpecial == 1) {
		complete_alphabet(options.alphabet, getSpecialCharacters());
	}
	else {
		options.alphabetSpecial = 0;
		remove_charset(options.alphabet, getSpecialCharacters());
	}
	UpdateData(false);
	OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnCheckDigits() {
	UpdateData(true);
	if(options.alphabetDigits == 1) {
		complete_alphabet(options.alphabet, getDigitCharacters());
	}
	else {
		options.alphabetDigits = 0;
		remove_charset(options.alphabet, getDigitCharacters());
	}
	UpdateData(false);
	OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnCheckUmlauts() {
	UpdateData(true);
	if(options.alphabetUmlauts == 1) {
		if(options.alphabetUpperCase) {
			complete_alphabet(options.alphabet, getUpperCaseUmlautCharacters());
		}
		if(options.alphabetLowerCase) {
			complete_alphabet(options.alphabet, getLowerCaseUmlautCharacters());
		}
	}
	else {
		options.alphabetUmlauts = 0;
		remove_charset(options.alphabet, getUpperCaseUmlautCharacters());
		remove_charset(options.alphabet, getLowerCaseUmlautCharacters());
	}
	UpdateData(false);
	OnUpdateEditAlphabet();
}

void CDlgTextOptions::OnUpdateEditAlphabet() {
	int i, SS, SE;
	unsigned char c, set[256];
	CString Old;
	controlEditAlphabet.GetSel(SS, SE);
	Old = options.alphabet;
	UpdateData(TRUE);
	for (int i=0; i<options.alphabet.GetLength() && !(options.alphabetUpperCase && options.alphabetLowerCase); i++) {
		if ( 0 <= getUpperCaseCharacters().Find( options.alphabet[i] ) ) options.alphabetUpperCase = 1;
		if ( 0 <= getLowerCaseCharacters().Find( options.alphabet[i] ) ) options.alphabetLowerCase = 1;
		if ( 0 <= getUpperCaseUmlautCharacters().Find( options.alphabet[i] ) ) { options.alphabetUpperCase = 1; options.alphabetUmlauts = 1; }
		if ( 0 <= getLowerCaseUmlautCharacters().Find( options.alphabet[i] ) ) { options.alphabetLowerCase = 1; options.alphabetUmlauts = 1; }
	}
	if( !options.distinguishUpperLowerCase && (options.alphabetLowerCase) ) {
		options.distinguishUpperLowerCase = 1;
		options.keepUpperLowerCaseInformation = 0;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SWITCH_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_NOTE,pc_str1,STR_LAENGE_STRING_TABLE);
		theApp.m_MainWnd->MessageBox(pc_str,pc_str1,MB_OK | MB_ICONINFORMATION);
	}
	// AVOID doublette chars 
	memset(set,0,sizeof(set));
	for(i=0;i<options.alphabet.GetLength();i++) {
		c = options.alphabet[i];
		if(set[c]) {
			options.alphabet = Old;
			controlEditAlphabet.SetSel(SS, SE);
			MessageBeep(MB_ICONEXCLAMATION);
			break;
		}
		set[c]=1;
	}
	// AVOID not allowed chars
	if(options.alphabet.GetLength() != options.alphabet.SpanIncluding(getAllowedCharacters()).GetLength()) {
		options.alphabet = Old;
		controlEditAlphabet.SetSel(SS, SE);
		MessageBeep(MB_ICONEXCLAMATION);
	}
	controlEditAlphabet.GetSel(SS, SE);
	updateCheckState();
	UpdateData(FALSE);
	controlEditAlphabet.SetSel(SS, SE);
	updateEditAlphabetHeading();
}

void CDlgTextOptions::OnButtonSearchReferenceFile() {
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
	// Set initial directory to be the directory in which the last reference file was found.
	CFileStatus fileStatus;
	if(CFile::GetStatus(options.referenceFile, fileStatus)) {
		const int index = options.referenceFile.ReverseFind('\\');
		if(index != -1) {
			CString directory = options.referenceFile;
			directory.Delete(index, directory.GetLength() - index);
			ofn.lpstrInitialDir = directory;
		}
	}
	ftitle[0] = 0;
	ofn.nMaxFileTitle = sizeof(ftitle)-1;
	if(!GetOpenFileName(&ofn)) return;
	if(fname[0] == 0) return;
	UpdateData(TRUE);
	options.referenceFiles[0].path = fname;
	options.referenceFile = options.referenceFiles[0].path;
	options.referenceFileIndex = 0;
	controlComboBoxSelectReferenceFile.SetCurSel(0);
	UpdateData(FALSE);
	controlEditReferenceFile.SetFocus();
	controlEditReferenceFile.SetSel(0,-1);
	GotoDlgCtrl( GetDlgItem(IDC_BUTTON_SEARCH_REFERENCE_FILE));
	updateButtonOK();
}

void CDlgTextOptions::OnComboSelectReferenceFile() {
	UpdateData(true);
	const int index = controlComboBoxSelectReferenceFile.GetCurSel();
	const ReferenceFile referenceFile = options.referenceFiles[index];
	options.referenceFileIndex = index;
	options.referenceFile = referenceFile.path;
	UpdateData(false);
	controlEditReferenceFile.SetSel(0, -1);
	updateButtonOK();
}

void CDlgTextOptions::OnButtonOK() {
	UpdateData(true);
	// Update AppConverter instace w/r/t the alphabet.
	const int ignoreCase = getIgnoreCase() ? 1 : 0;
	AppConv.SetAlphabet(options.alphabet.GetBuffer(257), ignoreCase);
	// Update Scintilla w/r/t the alphabet.
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

void CDlgTextOptions::OnButtonRestoreStandard() {
	UpdateData(true);
	restoreDefaultOptions();
	UpdateData(false);
	updateCheckState();
	UpdateData(false);
	updateEditAlphabetHeading();
	controlEditReferenceFile.SetSel(0,-1);
	controlComboBoxSelectReferenceFile.SetCurSel(options.referenceFileIndex);
	updateButtonOK();
}

void CDlgTextOptions::OnButtonCancel() {
	// Copy the "old options" to the "current options".
	copyOptions(optionsOld, options);
	// Then close the dialog as usual.
	CDialog::OnCancel();
}

void CDlgTextOptions::restoreDefaultOptions() {
	// Initialize defaults for the "current options".
	options.keepCharactersNotPresentInAlphabetUnchanged = 1;
	options.keepUpperLowerCaseInformation = 1;
	options.distinguishUpperLowerCase = 0;
	options.alphabetUpperCase = 1;
	options.alphabetLowerCase = 0;
	options.alphabetSpace = 0;
	options.alphabetSpecial = 0;
	options.alphabetDigits = 0;
	options.alphabetUmlauts = 0;
	options.alphabet = getUpperCaseCharacters();
	initializeReferenceFiles(options);
}

void CDlgTextOptions::updateEditAlphabetHeading() {
	// Update the edit alphabet heading with the number of characters in the alphabet.
	LoadString(AfxGetInstanceHandle(),IDS_TEXTOPTIONS_HEADER_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
	char line[256];
	sprintf(line, pc_str, options.alphabet.GetLength());
	controlEditAlphabetHeading.SetWindowText(line);
}

void CDlgTextOptions::updateCheckState() {
	const int uppercase_umlauts = check_charset(options.alphabet, getUpperCaseUmlautCharacters());
	const int lowercase_umlauts = check_charset(options.alphabet, getLowerCaseUmlautCharacters());
	options.alphabetUpperCase = check_charset(options.alphabet, uppercase_umlauts ? getUpperCaseCharacters() + getUpperCaseUmlautCharacters() : getUpperCaseCharacters());
	options.alphabetLowerCase = check_charset(options.alphabet, lowercase_umlauts ? getLowerCaseCharacters() + getLowerCaseUmlautCharacters() : getLowerCaseCharacters());
	options.alphabetSpace = check_charset(options.alphabet, " ");
	options.alphabetSpecial = check_charset(options.alphabet, getSpecialCharacters());
	options.alphabetDigits = check_charset(options.alphabet, getDigitCharacters());
	CString umlauts;
	umlauts.Append(options.alphabetUpperCase ? getUpperCaseUmlautCharacters() : "");
	umlauts.Append(options.alphabetLowerCase ? getLowerCaseUmlautCharacters() : "");
	options.alphabetUmlauts = check_charset(options.alphabet, umlauts);
}

void CDlgTextOptions::updateButtonOK() {
	// The OK button must not be active (as in: clickable) if the selected 
	// language reference file is invalid (as in: not readable).
	CFileStatus fileStatus;
	const bool referenceFileIsValid = CFile::GetStatus(options.referenceFile, fileStatus) == 1;
	CWnd *windowButtonOK = GetDlgItem(IDOK);
	ASSERT(windowButtonOK);
	windowButtonOK->EnableWindow(referenceFileIsValid);
}

void CDlgTextOptions::initializeReferenceFiles(CDlgTextOptions::Options &_options) {
	// flomar, 2017/07/24: Here we initialize the available language reference files. The 
	// supported languages are DE, EN, ES, FR, GR, LA, PL, RU, SR. Additional languages 
	// will need to be implemented explicitly.
	_options.referenceFiles.clear();
	_options.referenceFileIndex = -1;
	_options.referenceFile = "";
	ASSERT(_options.referenceFiles.size() == 0);
	ASSERT(_options.referenceFileIndex = -1);
	ASSERT(_options.referenceFile.GetLength() == 0);
	ASSERT(Pfad);
	// Initialize some local variables.
	CString crypToolRuntimeLanguage;
	crypToolRuntimeLanguage.LoadStringA(IDS_CRYPTOOL_RUNTIME_LANGUAGE_STRING);
	CString pathToReferenceFiles;
	pathToReferenceFiles = Pfad;
	pathToReferenceFiles.Append("\\reference\\");
	pathToReferenceFiles.Replace("\\\\", "\\");
	CFileStatus fileStatus;
	// Here we initialize the entry for the custom reference file which should always be 
	// present. Other entries (see supported languages above) are only added if the 
	// corresponding language files do actually exist.
	ReferenceFile referenceFileCustom;
	referenceFileCustom.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_CUSTOM);
	referenceFileCustom.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_CUSTOM);
	_options.referenceFiles.push_back(referenceFileCustom);
	_options.referenceFileIndex = 0;
	_options.referenceFile = referenceFileCustom.path;
	// German
	ReferenceFile referenceFileGerman;
	referenceFileGerman.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_GERMAN);
	referenceFileGerman.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_GERMAN);
	referenceFileGerman.path = pathToReferenceFiles + referenceFileGerman.path;
	if(CFile::GetStatus(referenceFileGerman.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileGerman);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "German") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileGerman.path;
		}
	}
	// English
	ReferenceFile referenceFileEnglish;
	referenceFileEnglish.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_ENGLISH);
	referenceFileEnglish.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_ENGLISH);
	referenceFileEnglish.path = pathToReferenceFiles + referenceFileEnglish.path;
	if(CFile::GetStatus(referenceFileEnglish.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileEnglish);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "English") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileEnglish.path;
		}
	}
	// Spanish
	ReferenceFile referenceFileSpanish;
	referenceFileSpanish.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_SPANISH);
	referenceFileSpanish.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_SPANISH);
	referenceFileSpanish.path = pathToReferenceFiles + referenceFileSpanish.path;
	if(CFile::GetStatus(referenceFileSpanish.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileSpanish);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "Spanish") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileSpanish.path;
		}
	}
	// French
	ReferenceFile referenceFileFrench;
	referenceFileFrench.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_FRENCH);
	referenceFileFrench.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_FRENCH);
	referenceFileFrench.path = pathToReferenceFiles + referenceFileFrench.path;
	if(CFile::GetStatus(referenceFileFrench.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileFrench);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "French") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileFrench.path;
		}
	}
	// Greek
	ReferenceFile referenceFileGreek;
	referenceFileGreek.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_GREEK);
	referenceFileGreek.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_GREEK);
	referenceFileGreek.path = pathToReferenceFiles + referenceFileGreek.path;
	if(CFile::GetStatus(referenceFileGreek.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileGreek);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "Greek") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileGreek.path;
		}
	}
	// Latin
	ReferenceFile referenceFileLatin;
	referenceFileLatin.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_LATIN);
	referenceFileLatin.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_LATIN);
	referenceFileLatin.path = pathToReferenceFiles + referenceFileLatin.path;
	if(CFile::GetStatus(referenceFileLatin.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileLatin);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "Latin") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileLatin.path;
		}
	}
	// Polish
	ReferenceFile referenceFilePolish;
	referenceFilePolish.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_POLISH);
	referenceFilePolish.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_POLISH);
	referenceFilePolish.path = pathToReferenceFiles + referenceFilePolish.path;
	if(CFile::GetStatus(referenceFilePolish.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFilePolish);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "Polish") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFilePolish.path;
		}
	}
	// Russian
	ReferenceFile referenceFileRussian;
	referenceFileRussian.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_RUSSIAN);
	referenceFileRussian.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_RUSSIAN);
	referenceFileRussian.path = pathToReferenceFiles + referenceFileRussian.path;
	if(CFile::GetStatus(referenceFileRussian.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileRussian);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "Russian") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileRussian.path;
		}
	}
	// Serbian
	ReferenceFile referenceFileSerbian;
	referenceFileSerbian.name.LoadString(IDS_LANGUAGEREFERENCEFILE_LANGUAGENAME_SERBIAN);
	referenceFileSerbian.path.LoadString(IDS_LANGUAGEREFERENCEFILE_FILENAME_SERBIAN);
	referenceFileSerbian.path = pathToReferenceFiles + referenceFileSerbian.path;
	if(CFile::GetStatus(referenceFileSerbian.path, fileStatus)) {
		_options.referenceFiles.push_back(referenceFileSerbian);
		if(_options.referenceFileIndex == 0 && crypToolRuntimeLanguage == "Serbian") {
			_options.referenceFileIndex = _options.referenceFiles.size() - 1;
			_options.referenceFile = referenceFileSerbian.path;
		}
	}
}

void CDlgTextOptions::updateReferenceFiles(const CDlgTextOptions::Options &_options) {
	while(controlComboBoxSelectReferenceFile.GetCount() > 0) {
		controlComboBoxSelectReferenceFile.DeleteString(controlComboBoxSelectReferenceFile.GetCount() - 1);
	}
	for(int i=0; i<_options.referenceFiles.size(); i++) {
		const ReferenceFile referenceFile = _options.referenceFiles[i];
		controlComboBoxSelectReferenceFile.AddString(referenceFile.name);
	}
	controlComboBoxSelectReferenceFile.SetCurSel(_options.referenceFileIndex);
}

void CDlgTextOptions::copyOptions(const CDlgTextOptions::Options &_optionsSource, CDlgTextOptions::Options &_optionsTarget) {
	_optionsTarget.keepCharactersNotPresentInAlphabetUnchanged = _optionsSource.keepCharactersNotPresentInAlphabetUnchanged;
	_optionsTarget.keepUpperLowerCaseInformation = _optionsSource.keepUpperLowerCaseInformation;
	_optionsTarget.distinguishUpperLowerCase = _optionsSource.distinguishUpperLowerCase;
	_optionsTarget.alphabetUpperCase = _optionsSource.alphabetUpperCase;
	_optionsTarget.alphabetLowerCase = _optionsSource.alphabetLowerCase;
	_optionsTarget.alphabetSpace = _optionsSource.alphabetSpace;
	_optionsTarget.alphabetSpecial = _optionsSource.alphabetSpecial;
	_optionsTarget.alphabetDigits = _optionsSource.alphabetDigits;
	_optionsTarget.alphabetUmlauts = _optionsSource.alphabetUmlauts;
	_optionsTarget.alphabet = _optionsSource.alphabet;
	_optionsTarget.referenceFiles = _optionsSource.referenceFiles;
	_optionsTarget.referenceFileIndex = _optionsSource.referenceFileIndex;
	_optionsTarget.referenceFile = _optionsSource.referenceFile;
}
