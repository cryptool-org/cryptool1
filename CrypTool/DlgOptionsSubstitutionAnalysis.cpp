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

//////////////////////////////////////////////////////////////////
// DlgSubstAna.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsSubstitutionAnalysis.h"
#include "FileTools.h"
#include "Cryptography.h"
#include "KeyRepository.h"

extern char *Eingabedatei;
extern char *Pfad;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSubstitutionAnalysis 


CDlgOptionsSubstitutionAnalysis::CDlgOptionsSubstitutionAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsSubstitutionAnalysis::IDD, pParent)
{
	
}


void CDlgOptionsSubstitutionAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsSubstitutionAnalysis)
	
	DDX_Control(pDX, IDC_RADIO_ANALYSIS_AUTOMATIC, m_controlRadioAnalysisAutomatic);
	DDX_Control(pDX, IDC_RADIO_ANALYSIS_MANUAL, m_controlRadioAnalysisManual);
	DDX_Control(pDX, IDC_RADIO_ANALYSIS_AUTOMATIC_GERMAN, m_controlRadioAnalysisAutomaticGerman);
	DDX_Control(pDX, IDC_RADIO_ANALYSIS_AUTOMATIC_ENGLISH, m_controlRadioAnalysisAutomaticEnglish);
	DDX_Control(pDX, IDC_EDIT_WORDLIST_GERMAN, m_controlEditAnalysisAutomaticWordlistGerman);
	DDX_Control(pDX, IDC_EDIT_WORDLIST_ENGLISH, m_controlEditAnalysisAutomaticWordlistEnglish);
	DDX_Text(pDX, IDC_EDIT_WORDLIST_GERMAN, m_editWordlistGerman);
	DDX_Text(pDX, IDC_EDIT_WORDLIST_ENGLISH, m_editWordlistEnglish);
	DDX_Control(pDX, IDC_BUTTON_SELECT_WORDLIST_GERMAN, m_buttonSelectWordlistGerman);
	DDX_Control(pDX, IDC_BUTTON_SELECT_WORDLIST_ENGLISH, m_buttonSelectWordlistEnglish);
	DDX_Control(pDX, IDC_STATIC_ANALYSIS_AUTOMATIC_OPTION1, m_controlStaticAnalysisAutomaticOption1);
	DDX_Control(pDX, IDC_CHECK_ANALYSIS_AUTOMATIC_OPTION1, m_controlCheckAnalysisAutomaticOption1);
	DDX_Control(pDX, IDC_STATIC_ANALYSIS_AUTOMATIC_OPTION2, m_controlStaticAnalysisAutomaticOption2);
	DDX_Control(pDX, IDC_CHECK_ANALYSIS_AUTOMATIC_OPTION2, m_controlCheckAnalysisAutomaticOption2);
	DDX_Control(pDX, IDC_CHECK_ANALYSIS_MANUAL_OPTION1, m_controlCheckAnalysisManualOption1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsSubstitutionAnalysis, CDialog)
	ON_BN_CLICKED(IDC_RADIO_ANALYSIS_AUTOMATIC, OnRadioAnalysisAutomatic)
	ON_BN_CLICKED(IDC_RADIO_ANALYSIS_MANUAL, OnRadioAnalysisManual)
	ON_BN_CLICKED(IDC_RADIO_ANALYSIS_AUTOMATIC_GERMAN, OnRadioAnalysisAutomaticGerman)
	ON_BN_CLICKED(IDC_RADIO_ANALYSIS_AUTOMATIC_ENGLISH, OnRadioAnalysisAutomaticEnglish)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_WORDLIST_GERMAN, OnButtonSelectWordlistGerman)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_WORDLIST_ENGLISH, OnButtonSelectWordlistEnglish)
	ON_BN_CLICKED(IDC_CHECK_ANALYSIS_AUTOMATIC_OPTION1, OnCheckAnalysisAutomaticOption1)
	ON_BN_CLICKED(IDC_CHECK_ANALYSIS_AUTOMATIC_OPTION2, OnCheckAnalysisAutomaticOption2)
	ON_BN_CLICKED(IDC_CHECK_ANALYSIS_MANUAL_OPTION1, OnCheckAnalysisManualOption1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsSubstitutionAnalysis 


BOOL CDlgOptionsSubstitutionAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// initialize some state variables: by default we activate
	// the AUTOMATIC analysis in ENGLISH, and all other options 
	// are unchecked
	analysisModeAutomatic = true;
	analysisAutomaticGerman = false;
	analysisAutomaticOption1 = false;
	analysisAutomaticOption2 = false;
	analysisManualOption1 = false;

	// initialize wordlist files (DE and EN)
	CString pathToWordlistFiles;
	CString stringFileName;
	if(Pfad) {
		pathToWordlistFiles = Pfad;
		pathToWordlistFiles.Append("\\words\\");
		pathToWordlistFiles.Replace("\\\\", "\\");
	}
	// flomar, July 2012: file names for word lists are hard-coded on purpose
	// to avoid redundancy, as they are identical for all languages anyway
	m_editWordlistGerman = pathToWordlistFiles + "SubstitutionAnalysisMethod2-de.txt";
	m_editWordlistEnglish = pathToWordlistFiles + "SubstitutionAnalysisMethod2-en.txt";

	// make sure the default word list files do exist, otherwise dump a warning
	CFileStatus wordlistFileStatus;
	if(!CFile::GetStatus(m_editWordlistGerman, wordlistFileStatus)) {
		CString message; 
		message.Format(IDS_STRING_SUBSTITUTION_ANALYSIS_MISSING_WORDLIST_GERMAN, m_editWordlistGerman);
		AfxMessageBox(message, MB_ICONWARNING);

	}
	if(!CFile::GetStatus(m_editWordlistEnglish, wordlistFileStatus)) {
		CString message; 
		message.Format(IDS_STRING_SUBSTITUTION_ANALYSIS_MISSING_WORDLIST_ENGLISH, m_editWordlistEnglish);
		AfxMessageBox(message, MB_ICONWARNING);
	}

	// flomar, 07/25/2012: unless we're running a German version, select English by default

	// TODO/FIXME: replace this quick-and-dirty approach with something more elegant; the 
	// problem right now is that I don't know how to determine the language of the resource 
	// file (the one CrypTool was COMPILED with) at runtime, thus I introduced an additional 
	// resource string (IDS_CRYPTOOL_RUNTIME_LANGUAGE_STRING) for each language; note that 
	// calls to "GetUserDefaultUILanguage()" or similar functions will give you the SYSTEM 
	// language, not the CRYPTOOL language (which is statically set at compile time)
	CString runtimeLanguage;
	runtimeLanguage.Format(IDS_CRYPTOOL_RUNTIME_LANGUAGE_STRING);
	if(runtimeLanguage == "German") {
		analysisAutomaticGerman = true;
	}
	else {
		analysisAutomaticGerman = false;
	}

	UpdateData(false);

	// update the GUI
	updateButtons();

	return TRUE;  
}

void CDlgOptionsSubstitutionAnalysis::OnRadioAnalysisAutomatic() {
	if(!analysisModeAutomatic) {
		analysisModeAutomatic = true;
	}
	updateButtons();
}

void CDlgOptionsSubstitutionAnalysis::OnRadioAnalysisManual() {
	if(analysisModeAutomatic) {
		analysisModeAutomatic = false;
	}
	updateButtons();
}

void CDlgOptionsSubstitutionAnalysis::OnRadioAnalysisAutomaticGerman() {
	if(!analysisAutomaticGerman) {
		analysisAutomaticGerman = true;
	}
	updateButtons();
}

void CDlgOptionsSubstitutionAnalysis::OnRadioAnalysisAutomaticEnglish() {
	if(analysisAutomaticGerman) {
		analysisAutomaticGerman = false;
	}
	updateButtons();
}

void CDlgOptionsSubstitutionAnalysis::OnButtonSelectWordlistGerman() {
	OPENFILENAME ofn;
	char fname[257], ftitle[128];
	const char* s_FileFilter = "text files (*.txt)\0*.txt\0all files\0*.*;*\0\0";

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_CHOOSE_REF_FILENAME, pc_str, STR_LAENGE_STRING_TABLE);
	ofn.lpstrTitle = pc_str;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofn.lpstrFile = fname;
	sprintf(fname, "*.txt");
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;
	ofn.lpstrFilter = s_FileFilter;

	// set initial directory to be the directory in which the last wordlist file was found
	if(m_editWordlistGerman.GetLength() != 0) {
		// delete everything after the last backslash ('\')
		int index = m_editWordlistGerman.ReverseFind('\\');
		if(index != -1) {
			CString directory = m_editWordlistGerman;
			directory.Delete(index, directory.GetLength() - index);
			ofn.lpstrInitialDir = directory;
		}
	}

	ftitle[0] = 0;
	ofn.nMaxFileTitle = sizeof(ftitle)-1;
	if(!GetOpenFileName(&ofn)) return;
	if(fname[0]==0) return;
	
	UpdateData(TRUE);
	m_editWordlistGerman = fname;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnButtonSelectWordlistEnglish() {
	OPENFILENAME ofn;
	char fname[257], ftitle[128];
	const char* s_FileFilter = "text files (*.txt)\0*.txt\0all files\0*.*;*\0\0";

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_CHOOSE_REF_FILENAME, pc_str, STR_LAENGE_STRING_TABLE);
	ofn.lpstrTitle = pc_str;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofn.lpstrFile = fname;
	sprintf(fname, "*.txt");
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;
	ofn.lpstrFilter = s_FileFilter;

	// set initial directory to be the directory in which the last wordlist file was found
	if(m_editWordlistEnglish.GetLength() != 0) {
		// delete everything after the last backslash ('\')
		int index = m_editWordlistEnglish.ReverseFind('\\');
		if(index != -1) {
			CString directory = m_editWordlistEnglish;
			directory.Delete(index, directory.GetLength() - index);
			ofn.lpstrInitialDir = directory;
		}
	}

	ftitle[0] = 0;
	ofn.nMaxFileTitle = sizeof(ftitle)-1;
	if(!GetOpenFileName(&ofn)) return;
	if(fname[0]==0) return;
	
	UpdateData(TRUE);
	m_editWordlistEnglish = fname;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnCheckAnalysisAutomaticOption1() {
	if(analysisAutomaticOption1) {
		// deactivating the first options implicitly deactivates the second option
		analysisAutomaticOption1 = false;
		analysisAutomaticOption2 = false;
	}
	else {
		analysisAutomaticOption1 = true;
	}
	// update the GUI
	updateButtons();
}

void CDlgOptionsSubstitutionAnalysis::OnCheckAnalysisAutomaticOption2() {
	if(analysisAutomaticOption2) {
		analysisAutomaticOption2 = false;
	}
	else {
		// activating the second option implicitly activates the first option
		analysisAutomaticOption1 = true;
		analysisAutomaticOption2 = true;
	}
	// update the GUI
	updateButtons();
}

void CDlgOptionsSubstitutionAnalysis::OnCheckAnalysisManualOption1() {
	if(analysisManualOption1) {
		analysisManualOption1 = false;
	}
	else {
		analysisManualOption1 = true;
	}
	// update the GUI
	updateButtons();
}

void CDlgOptionsSubstitutionAnalysis::updateButtons() {

	UpdateData(true);

	// these are ALWAYS enabled
	m_controlRadioAnalysisAutomatic.EnableWindow(true);
	m_controlRadioAnalysisManual.EnableWindow(true);
	
	// the following ones are CONDITIONALLY enabled
	m_controlRadioAnalysisAutomaticGerman.EnableWindow(analysisModeAutomatic);
	m_controlRadioAnalysisAutomaticEnglish.EnableWindow(analysisModeAutomatic);
	m_controlStaticAnalysisAutomaticOption1.EnableWindow(analysisModeAutomatic);
	m_controlCheckAnalysisAutomaticOption1.EnableWindow(analysisModeAutomatic);
	m_controlStaticAnalysisAutomaticOption2.EnableWindow(analysisModeAutomatic);
	m_controlCheckAnalysisAutomaticOption2.EnableWindow(analysisModeAutomatic);
	m_buttonSelectWordlistGerman.EnableWindow(analysisModeAutomatic);
	m_buttonSelectWordlistEnglish.EnableWindow(analysisModeAutomatic);
	
	// some enabling, showing and hiding
	m_controlEditAnalysisAutomaticWordlistGerman.ShowWindow(analysisAutomaticGerman ? SW_SHOW : SW_HIDE);
	m_controlEditAnalysisAutomaticWordlistGerman.EnableWindow(analysisModeAutomatic);
	m_controlEditAnalysisAutomaticWordlistEnglish.ShowWindow(!analysisAutomaticGerman ? SW_SHOW : SW_HIDE);
	m_controlEditAnalysisAutomaticWordlistEnglish.EnableWindow(analysisModeAutomatic);
	m_buttonSelectWordlistGerman.ShowWindow(analysisAutomaticGerman ? SW_SHOW : SW_HIDE);
	m_buttonSelectWordlistEnglish.ShowWindow(!analysisAutomaticGerman ? SW_SHOW : SW_HIDE);

	// some checking and unchecking
	m_controlRadioAnalysisAutomatic.SetCheck(analysisModeAutomatic ? 1 : 0);
	m_controlRadioAnalysisManual.SetCheck(!analysisModeAutomatic ? 1 : 0);
	m_controlRadioAnalysisAutomaticGerman.SetCheck(analysisAutomaticGerman ? 1 : 0);
	m_controlRadioAnalysisAutomaticEnglish.SetCheck(!analysisAutomaticGerman ? 1 : 0);
	m_controlCheckAnalysisAutomaticOption1.SetCheck(analysisAutomaticOption1 ? 1 : 0);
	m_controlCheckAnalysisAutomaticOption2.SetCheck(analysisAutomaticOption2 ? 1 : 0);
	
	// special handling (check for a pre-defined key in the key store)
	LoadString(AfxGetInstanceHandle(), IDS_ANALYSIS_SUBSTITUTION, pc_str, STR_LAENGE_STRING_TABLE);
	CString keystoreKey;
	bool doesKeyExist = false;
	if(PasteKey(pc_str, keystoreKey)) {
		if(!keystoreKey.IsEmpty()) {
			doesKeyExist = true;
		}
	}
	m_controlCheckAnalysisManualOption1.EnableWindow(!analysisModeAutomatic && doesKeyExist);
	m_controlCheckAnalysisManualOption1.SetCheck(analysisManualOption1 && doesKeyExist ? 1 : 0);

	// scroll to the end of the word list file names
	m_controlEditAnalysisAutomaticWordlistGerman.SetSel(0, -1);
	m_controlEditAnalysisAutomaticWordlistGerman.SetSel(-1);
	m_controlEditAnalysisAutomaticWordlistEnglish.SetSel(0, -1);
	m_controlEditAnalysisAutomaticWordlistEnglish.SetSel(-1);
	
	UpdateData(false);
}