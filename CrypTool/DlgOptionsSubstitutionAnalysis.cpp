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
	//{{AFX_DATA_INIT(CDlgOptionsSubstitutionAnalysis)
	m_radio1 = 0;
	m_check1 = FALSE;
	m_check2 = FALSE;
	m_storedKey = -1;
	//}}AFX_DATA_INIT
}


void CDlgOptionsSubstitutionAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsSubstitutionAnalysis)
	DDX_Control(pDX, IDC_RADIO4, m_ctrl_storedKey);
	DDX_Control(pDX, IDC_CHECK2, m_control2);
	DDX_Control(pDX, IDC_CHECK1, m_control1);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Radio(pDX, IDC_RADIO4, m_storedKey);
	DDX_Control(pDX, IDC_BUTTON_SELECT_WORDLIST_GERMAN, m_buttonSelectWordlistGerman);
	DDX_Control(pDX, IDC_BUTTON_SELECT_WORDLIST_ENGLISH, m_buttonSelectWordlistEnglish);
	DDX_Text(pDX, IDC_EDIT_WORDLIST_GERMAN, m_editWordlistGerman);
	DDX_Text(pDX, IDC_EDIT_WORDLIST_ENGLISH, m_editWordlistEnglish);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsSubstitutionAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsSubstitutionAnalysis)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_WORDLIST_GERMAN, OnButtonSelectWordlistGerman)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_WORDLIST_ENGLISH, OnButtonSelectWordlistEnglish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsSubstitutionAnalysis 


BOOL CDlgOptionsSubstitutionAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Default-Einstellung ist englischer Klartext mit reiner Pattern Suche
	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
	m_control2.EnableWindow(FALSE);	
	
	LoadString(AfxGetInstanceHandle(),IDS_ANALYSIS_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
	if ( IsKeyEmpty( pc_str ))
	{
		m_ctrl_storedKey.EnableWindow(TRUE);
	}
	else
	{
		m_ctrl_storedKey.EnableWindow(FALSE);
	}

	// initialize wordlist files (DE and EN)
	CString pathToWordlistFiles;
	CString stringFileName;
	if(Pfad) {
		pathToWordlistFiles = Pfad;
		pathToWordlistFiles.Append("\\words\\");
		pathToWordlistFiles.Replace("\\\\", "\\");
	}
	m_editWordlistGerman = pathToWordlistFiles + "substitution-de.txt";
	m_editWordlistEnglish = pathToWordlistFiles + "substitution-en.txt";

	UpdateData(false);

	return TRUE;  
}

void CDlgOptionsSubstitutionAnalysis::OnCheck2() 
{
	// Wenn der Knopf "erweiterte Analyse" gewählt wird:
	// Diese Option schließt die Option "'e' als häufigstes Zeichen logisch ein, so daß 
	// diese Option automatsich auch angewählt wird.
	// Ferner muß ausgeschlossen werden, daß der Benutzer eine erweiterte Analyse für
	// englischen Klartext gewählt hat, da das derzeit vom Programm noch nicht unterstützt
	// wird.
	UpdateData(TRUE);
	m_check1=true;
	UpdateData(FALSE);	
}

void CDlgOptionsSubstitutionAnalysis::OnCheck1() 
{
	// Wenn die Option "'e' als häufigstes Zeichen" geändert wird, muß die Option
	// "erweiterte Analyse" automatisch abgeschaltet werden, damit es nicht vorkommt,
	// daß die zweite ohne die erste Option ausgewählt wurde
	UpdateData(TRUE);
	if ( false == m_check1 )
		m_check2=false;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData();
	m_control1.EnableWindow();
	m_control2.EnableWindow();
	m_storedKey = -1;
	m_buttonSelectWordlistGerman.EnableWindow(TRUE);
	m_buttonSelectWordlistEnglish.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio2() 
{
	// Wird englischer Klartext gewählt, so muß die Option "erweiterte Analyse" abgeschaltet werden
	UpdateData();
	m_control1.EnableWindow();
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	m_storedKey = -1;
	m_buttonSelectWordlistGerman.EnableWindow(TRUE);
	m_buttonSelectWordlistEnglish.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio3() 
{
	UpdateData();
	m_check1 = false;
	m_control1.EnableWindow(FALSE);
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	m_storedKey = -1;
	m_buttonSelectWordlistGerman.EnableWindow(FALSE);
	m_buttonSelectWordlistEnglish.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnRadio4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData();
	m_check1 = false;
	m_control1.EnableWindow(FALSE);
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	m_storedKey = 0;
	m_radio1    = -1;
	m_buttonSelectWordlistGerman.EnableWindow(FALSE);
	m_buttonSelectWordlistEnglish.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnButtonSelectWordlistGerman() {
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
	m_editWordlistGerman=fname;
	UpdateData(FALSE);
}

void CDlgOptionsSubstitutionAnalysis::OnButtonSelectWordlistEnglish() {
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
	m_editWordlistEnglish=fname;
	UpdateData(FALSE);
}