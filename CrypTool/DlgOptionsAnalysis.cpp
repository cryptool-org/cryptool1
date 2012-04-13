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
// OptionsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsAnalysis.h"
#include "CrypToolTools.h"

extern char *Pfad;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsAnalysis 


CDlgOptionsAnalysis::CDlgOptionsAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsAnalysis::IDD, pParent)
	, i_alphabetOptions(0)
{
	//{{AFX_DATA_INIT(CDlgOptionsAnalysis)
	m_CKey = TRUE;
	m_CKorr = TRUE;
	m_CHist = TRUE;
	m_VKey = TRUE;
	m_VLen = TRUE;
	m_VKorr = TRUE;
	m_VBase = FALSE;
	m_BFEntropyWindow = 128;
	m_VigenereAnalysisSchroedelExtensiveLogging = FALSE;
	m_VigenereAnalysisSchroedelDictionaryFile = "";
	m_VigenereAnalysisSchroedelDigramsFile = "";
	m_VigenereAnalysisSchroedelTrigramsFile = "";
	//}}AFX_DATA_INIT
	i_alphabetOptions = 0;
}

static long GetWindowTextAsLong(CWnd *wnd)
{
	CString text;
	wnd->GetWindowText(text);
	return atol(text);
}

void CDlgOptionsAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX); 
	//{{AFX_DATA_MAP(CDlgOptionsAnalysis)
	DDX_Check(pDX, IDC_CHECK1, m_CKey);
	DDX_Check(pDX, IDC_CHECK2, m_CKorr);
	DDX_Check(pDX, IDC_CHECK3, m_CHist);
	DDX_Check(pDX, IDC_CHECK6, m_VKey);
	DDX_Check(pDX, IDC_CHECK7, m_VLen);
	DDX_Check(pDX, IDC_CHECK8, m_VKorr);
	DDX_Check(pDX, IDC_CHECK4, m_VBase);
	DDX_Text(pDX, IDC_EDIT_ENTROPY_WINDOW, m_BFEntropyWindow);
	DDX_Check(pDX, IDC_CHECK_EXTENSIVE_LOGGING, m_VigenereAnalysisSchroedelExtensiveLogging);
	DDX_Control(pDX, IDC_EDIT_DICTIONARY_FILE, controlEditDictionaryFile);
	DDX_Control(pDX, IDC_EDIT_DIGRAMS_FILE, controlEditDigramsFile);
	DDX_Control(pDX, IDC_EDIT_TRIGRAMS_FILE, controlEditTrigramsFile);
	DDX_Text(pDX, IDC_EDIT_DICTIONARY_FILE, m_VigenereAnalysisSchroedelDictionaryFile);
	DDX_Text(pDX, IDC_EDIT_DIGRAMS_FILE, m_VigenereAnalysisSchroedelDigramsFile);
	DDX_Text(pDX, IDC_EDIT_TRIGRAMS_FILE, m_VigenereAnalysisSchroedelTrigramsFile);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_RADIO1, i_alphabetOptions);
}


BEGIN_MESSAGE_MAP(CDlgOptionsAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsAnalysis)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_DICTIONARY_FILE, OnButtonSearchDictionaryFile)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_DIGRAMS_FILE, OnButtonSearchDigramsFile)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_TRIGRAMS_FILE, OnButtonSearchTrigramsFile)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE_STANDARD, OnBnClickedButtonRestoreStandard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CDlgOptionsAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// try to read settings for Vigenere analysis by Schroedel from registry
	readSettingsVigenereAnalysisSchroedel();

	return TRUE;
}

void CDlgOptionsAnalysis::OnOK()
{
	UpdateData(true);

	// flomar, 05/31/2010
	// we moved the check for valid values from MFC-based macros into this 
	// function, because for some reason MFC displayed error messages twice;
	// we call CDialog::OnOK() only if values are within the valid range
	const unsigned int minimumNumberOfCharactersForEntropyTest = 2;
	const unsigned int maximumNumberOfCharactersForEntropyTest = 4096;
	if(m_BFEntropyWindow < minimumNumberOfCharactersForEntropyTest || m_BFEntropyWindow > maximumNumberOfCharactersForEntropyTest) {
		CString message;
		message.Format(IDS_STRING_VALID_RANGE_OF_CHARACTERS_FOR_ENTROPY_TEST, minimumNumberOfCharactersForEntropyTest, maximumNumberOfCharactersForEntropyTest);
		AfxMessageBox(message, MB_ICONINFORMATION);
		return;
	}
	
	// try to write settings for Vigenere analysis by Schroedel to registry
	writeSettingsVigenereAnalysisSchroedel();

	CDialog::OnOK();
}

void CDlgOptionsAnalysis::OnButtonSearchDictionaryFile()
{
	UpdateData(true);

	LoadString(AfxGetInstanceHandle(),IDS_VIGENERE_ANALYSIS_SCHROEDEL_CHOOSE_DICTIONARY_FILE,pc_str,STR_LAENGE_STRING_TABLE);
	
	CString title = pc_str;
	CString chosenFile = chooseFileThroughDialog(title, m_VigenereAnalysisSchroedelDictionaryFile);

	if(chosenFile.GetLength() == 0) return;
	// at this point we should have the full path to the desired file
	m_VigenereAnalysisSchroedelDictionaryFile = chosenFile;

	UpdateData(false);
}

void CDlgOptionsAnalysis::OnButtonSearchDigramsFile()
{
	UpdateData(true);

	LoadString(AfxGetInstanceHandle(),IDS_VIGENERE_ANALYSIS_SCHROEDEL_CHOOSE_DIGRAMS_FILE,pc_str,STR_LAENGE_STRING_TABLE);
	
	CString title = pc_str;
	CString chosenFile = chooseFileThroughDialog(title, m_VigenereAnalysisSchroedelDigramsFile);

	if(chosenFile.GetLength() == 0) return;
	// at this point we should have the full path to the desired file
	m_VigenereAnalysisSchroedelDigramsFile = chosenFile;

	UpdateData(false);
}

void CDlgOptionsAnalysis::OnButtonSearchTrigramsFile()
{
	UpdateData(true);

	LoadString(AfxGetInstanceHandle(),IDS_VIGENERE_ANALYSIS_SCHROEDEL_CHOOSE_TRIGRAMS_FILE,pc_str,STR_LAENGE_STRING_TABLE);
	
	CString title = pc_str;
	CString chosenFile = chooseFileThroughDialog(title, m_VigenereAnalysisSchroedelTrigramsFile);

	if(chosenFile.GetLength() == 0) return;
	// at this point we should have the full path to the desired file
	m_VigenereAnalysisSchroedelTrigramsFile = chosenFile;

	UpdateData(false);
}

CString CDlgOptionsAnalysis::chooseFileThroughDialog(const CString title, const CString defaultFile)
{
	CString chosenFile = "";

	OPENFILENAME ofn;
	char fname[257], ftitle[128];
	const char* s_FileFilter = "text files (*.txt)\0*.txt\0all files\0*.*;*\0\0";

	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrTitle = title;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofn.lpstrFile = fname;
	sprintf(fname, "*.txt");
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;
	ofn.lpstrFilter = s_FileFilter;

	// set initial directory to be the directory in which the last file [the default file] was found
	if(defaultFile.GetLength() != 0) {
		// delete everything after the last backslash ('\')
		int index = defaultFile.ReverseFind('\\');
		if(index != -1) {
			CString directory = defaultFile;
			directory.Delete(index, directory.GetLength() - index);
			ofn.lpstrInitialDir = directory;
		}
	}

	ftitle[0] = 0;
	ofn.nMaxFileTitle = sizeof(ftitle)-1;

	if(!GetOpenFileName(&ofn)) return chosenFile;
	if(fname[0]==0) return chosenFile;
	chosenFile=fname;
	
	return chosenFile;
}

void CDlgOptionsAnalysis::readSettingsVigenereAnalysisSchroedel()
{
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "VigenereAnalysisSchroedel" ) == ERROR_SUCCESS )
	{
		UpdateData(true);
		
		unsigned long u_extensiveLogging = 0;
		CT_READ_REGISTRY_DEFAULT(u_extensiveLogging, "ExtensiveLogging", 0);

		const unsigned long maxBufferSize = 4096;
		unsigned long bufferSize;

		char c_dictionaryFile[maxBufferSize];
		memset(c_dictionaryFile, 0, maxBufferSize);
		CString pathToDefaultDictionaryFile;
		pathToDefaultDictionaryFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
		pathToDefaultDictionaryFile = CString(Pfad) + pathToDefaultDictionaryFile;
		const char *c_dictionaryFileDefault = (const char*)(LPCTSTR)(pathToDefaultDictionaryFile);
		bufferSize = maxBufferSize - 1;
		CT_READ_REGISTRY_DEFAULT(c_dictionaryFile, "DictionaryFile", c_dictionaryFileDefault, bufferSize);

		char c_digramsFile[maxBufferSize];
		memset(c_digramsFile, 0, maxBufferSize);
		CString pathToDefaultDigramsFile;
		pathToDefaultDigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
		pathToDefaultDigramsFile = CString(Pfad) + pathToDefaultDigramsFile;
		const char *c_digramsFileDefault = (const char*)(LPCTSTR)(pathToDefaultDigramsFile);
		bufferSize = maxBufferSize - 1;
		CT_READ_REGISTRY_DEFAULT(c_digramsFile, "DigramsFile", c_digramsFileDefault, bufferSize);

		char c_trigramsFile[maxBufferSize];
		memset(c_trigramsFile, 0, maxBufferSize);
		CString pathToDefaultTrigramsFile;
		pathToDefaultTrigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
		pathToDefaultTrigramsFile = CString(Pfad) + pathToDefaultTrigramsFile;
		const char *c_trigramsFileDefault = (const char*)(LPCTSTR)(pathToDefaultTrigramsFile);
		bufferSize = maxBufferSize - 1;
		CT_READ_REGISTRY_DEFAULT(c_trigramsFile, "TrigramsFile", c_trigramsFileDefault, bufferSize);

		m_VigenereAnalysisSchroedelExtensiveLogging = (BOOL)u_extensiveLogging;
		m_VigenereAnalysisSchroedelDictionaryFile = (CString)c_dictionaryFile;
		m_VigenereAnalysisSchroedelDigramsFile = (CString)c_digramsFile;
		m_VigenereAnalysisSchroedelTrigramsFile = (CString)c_trigramsFile;

		UpdateData(false);
	}
}

void CDlgOptionsAnalysis::writeSettingsVigenereAnalysisSchroedel()
{
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "VigenereAnalysisSchroedel" ) == ERROR_SUCCESS )
	{
		UpdateData(true);
	
		CT_WRITE_REGISTRY((unsigned long)m_VigenereAnalysisSchroedelExtensiveLogging, "ExtensiveLogging");
		CT_WRITE_REGISTRY(m_VigenereAnalysisSchroedelDictionaryFile, "DictionaryFile");
		CT_WRITE_REGISTRY(m_VigenereAnalysisSchroedelDigramsFile, "DigramsFile");
		CT_WRITE_REGISTRY(m_VigenereAnalysisSchroedelTrigramsFile, "TrigramsFile");

		UpdateData(false);
	}
}
void CDlgOptionsAnalysis::OnBnClickedButtonRestoreStandard()
{
	// Caesar and Vigenere related settings
	m_CKey = true;
	m_CKorr = true;
	m_CHist = true;
	m_VKey = true;
	m_VLen = true;
	m_VKorr = true;
	m_VBase = false;
	m_BFEntropyWindow = 128;
	i_alphabetOptions = 0;

	// settings for new Vigenere (Schroedel) analysis
	m_VigenereAnalysisSchroedelExtensiveLogging = false;
	// get settings from resource file
	CString pathToDefaultDictionaryFile;
	pathToDefaultDictionaryFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
	pathToDefaultDictionaryFile = CString(Pfad) + pathToDefaultDictionaryFile;
	CString pathToDefaultDigramsFile;
	pathToDefaultDigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
	pathToDefaultDigramsFile = CString(Pfad) + pathToDefaultDigramsFile;
	CString pathToDefaultTrigramsFile;
	pathToDefaultTrigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
	pathToDefaultTrigramsFile = CString(Pfad) + pathToDefaultTrigramsFile;
	// apply settings
	m_VigenereAnalysisSchroedelDictionaryFile = pathToDefaultDictionaryFile;
	m_VigenereAnalysisSchroedelDigramsFile = pathToDefaultDigramsFile;
	m_VigenereAnalysisSchroedelTrigramsFile = pathToDefaultTrigramsFile;

	UpdateData(false);
}
