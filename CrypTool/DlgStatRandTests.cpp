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

// Dlg_Tests.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "CrypToolTools.h"
#include "DlgStatRandTests.h"
#include "RandomTest.h"
#include "ParseIniFile2.h"
#include "DialogeMessage.h"
#include ".\dlgstatrandtests.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEFAULT_TUPEL 2

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFreqTest 


CDlgFreqTest::CDlgFreqTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFreqTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFreqTest)
	m_Ergebnis = _T("");
	m_Offset = 0;
	m_Lang = 1024;
	m_Default = TRUE;
	m_Default_2 = FALSE;
	m_Info_Static = _T("");
	infile = NULL;
	oldTitle = NULL;
	//}}AFX_DATA_INIT
	currentTest = 0;	
	s_alternativeWindowText[0]=0;
	poker_flag = FALSE;
	tupel = 3;
}


void CDlgFreqTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFreqTest)
	DDX_Control(pDX, IDC_TUPELCOMBO, m_TupelCombo_Ctrl);
	DDX_Control(pDX, IDC_TUPEL_STATIC, m_TupelStatic_Ctrl);
	DDX_Control(pDX, IDC_CHECK2, m_Default_2_Ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_Testlang_Ctrl);
	DDX_Control(pDX, IDC_EDIT1, m_Offset_Ctrl);
	DDX_Control(pDX, IDC_COMBO_ALPHA, m_AlphaCombo_Ctrl);
	DDX_Control(pDX, IDC_BITMAP_2, m_Bitmap_Ctrl2);
	DDX_Control(pDX, IDC_BITMAP_1, m_Bitmap_Ctrl);
	DDX_Text(pDX, IDC_STATIC_ERGEBNIS, m_Ergebnis);
	DDX_Text(pDX, IDC_EDIT1, m_Offset);
	DDX_Text(pDX, IDC_EDIT2, m_Lang);
	DDX_Check(pDX, IDC_CHECK1, m_Default);
	DDX_Check(pDX, IDC_CHECK2, m_Default_2);
	DDX_Text(pDX, IDC_INFO_STATIC, m_Info_Static);
	//}}AFX_DATA_MAP
}


void CDlgFreqTest::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}

BOOL CDlgFreqTest::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (s_alternativeWindowText[0])
		SetWindowText(s_alternativeWindowText);

	UpdateData(TRUE);
	m_Offset_Ctrl.EnableWindow(FALSE);
	m_Testlang_Ctrl.EnableWindow(FALSE);
	CParseIniFile2 iniFile;
	CParseIniFile2::CStringList AlphaList;
	int combolist_stringindex;

	if ( poker_flag == TRUE )
	{
		m_TupelCombo_Ctrl.EnableWindow( TRUE );
		m_TupelStatic_Ctrl.EnableWindow( TRUE );
		m_TupelCombo_Ctrl.SetCurSel( DEFAULT_TUPEL );
	}
	else if ( poker_flag == FALSE )
	{
		m_TupelCombo_Ctrl.EnableWindow( FALSE );
		m_TupelStatic_Ctrl.EnableWindow( FALSE );
	}

	if (iniFile.GetAlphaList(AlphaList) == -1)
	{
	}
	else
	{
		// Laden von dem Alpha-Parametern in ComboBox!!!
		// no problems due opening IniFile 
		while ( !AlphaList.IsEmpty()){
			m_AlphaCombo_Ctrl.AddString(AlphaList.RemoveHead()); // Add alpha to combobox-list
		}	

		if (!iniFile.GetDefaultAlpha(alpha))
		{
			// A alpha is in the iniFile specified as default alpha 
			combolist_stringindex = m_AlphaCombo_Ctrl.SelectString( -1, alpha);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgFreqTest::init (const char *Infile_, const char *OldTitle_)
{
	infile = Infile_;
	oldTitle = OldTitle_;
	CStdioFile file;
	file.Open(infile, CFile::modeRead);
	ASSERT(file.GetLength() < ULONG_MAX);
	m_Lang = (ULONG)file.GetLength();
	file.Close();
}

BEGIN_MESSAGE_MAP(CDlgFreqTest, CDialog)
	//{{AFX_MSG_MAP(CDlgFreqTest)
	ON_BN_CLICKED(IDC_BUTTON_FREQTEST, OnButtonFreqtest)
	ON_CBN_SELCHANGE(IDC_COMBO_ALPHA, OnSelchangeComboAlpha)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_CBN_SELCHANGE(IDC_TUPELCOMBO, OnSelchangeTupelcombo)
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_INFO_STATIC, OnStnClickedInfoStatic)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFreqTest 

void CDlgFreqTest::OnButtonFreqtest() 
{
	SHOW_HOUR_GLASS
	UpdateData(TRUE);
	
	CParseIniFile2 iniFile;

	if ( poker_flag == TRUE ) 
	{
		currentTest->tupel = tupel;
		UINT potenz = 1;
		for (UINT pot = 0; pot < tupel; pot++) potenz *= 2;
		currentTest->Set_degr(potenz - 1);
		if ((potenz - 1) == 15) currentTest->Set_degr( 11 ); //Keine verfügbare Daten für weiter Freiheitsgraden
															 //verfügbar - Tupelgröse auf 4 begrentzt
	}

// 	Freq_Test test;
	if ( !currentTest ) 
	{
		// Fehlermeldung
		return;
	}
	currentTest->Set_infile(Get_infile());
	currentTest->Set_oldtitle(Get_oldTitle());
	if ((!(currentTest->SetOffset(m_Offset) && currentTest->SetTestLength(m_Lang)) && (m_Default == FALSE)) || (m_Lang <=0))
	{
		m_Bitmap_Ctrl2.ShowWindow(FALSE);
		m_Bitmap_Ctrl.ShowWindow(TRUE);
		m_Info_Static = _T("");
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_FALSCHE_OFFSET_DIALOG, pc_str, STR_LAENGE_STRING_TABLE);
		m_Ergebnis = pc_str;
		UpdateData(FALSE);
		Message(IDS_STRING_TESTS_FALSCHE_OFFSET, MB_ICONEXCLAMATION);
	}
	else
	{
		double parameter = iniFile.GetAlphaParam(alpha, currentTest->Get_degr());
		if ( 0 > parameter) return;
		currentTest->Set_DefParam(parameter);
		if (m_Default == TRUE) currentTest->def=TRUE;
		else if (m_Default == FALSE) currentTest->def=FALSE;

		if (m_Default_2 == TRUE) currentTest->def2=TRUE;
		else if (m_Default_2 == FALSE) currentTest->def2=FALSE;

		UpdateData(TRUE);
		currentTest->test();
		UpdateData(FALSE);

		if(!currentTest->GetResult())
		{
			m_Bitmap_Ctrl2.ShowWindow(FALSE);
			m_Bitmap_Ctrl.ShowWindow(TRUE);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_NICHT_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
			char tmpStr_2[128];
			sprintf(tmpStr_2, pc_str, tmpStr);
			m_Ergebnis = tmpStr_2;
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_INFO, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(tmpStr_2, pc_str, currentTest->Get_DefParam(), currentTest->Get_test_ergeb());
			m_Info_Static = tmpStr_2;
			UpdateData(FALSE);
		}
		else
		{
			m_Bitmap_Ctrl.ShowWindow(FALSE);
			m_Bitmap_Ctrl2.ShowWindow(TRUE);
			UpdateData(TRUE);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
			char tmpStr_2[128];
			sprintf(tmpStr_2, pc_str, tmpStr);
			m_Ergebnis = tmpStr_2;
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_INFO, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(tmpStr_2, pc_str, currentTest->Get_DefParam(), currentTest->Get_test_ergeb());
			m_Info_Static = tmpStr_2;
			UpdateData(FALSE);
		}
	}
	HIDE_HOUR_GLASS
}

void CDlgFreqTest::OnSelchangeComboAlpha() 
{
	// Show parameters of the selected alpha
	// The parameters are loaded from the file 'initializing_file_2'

	CParseIniFile2 iniFile;

	m_AlphaCombo_Ctrl.GetLBText(m_AlphaCombo_Ctrl.GetCurSel(), alpha);
}
	


void CDlgFreqTest::OnCheck1() 
{
	if ( m_Default == TRUE )
	{
		m_Offset_Ctrl.EnableWindow(TRUE);
		m_Testlang_Ctrl.EnableWindow(TRUE);
		m_Default = FALSE;
	}
	else if ( m_Default == FALSE )
	{
		CStdioFile file;
		file.Open(infile, CFile::modeRead);
		UpdateData(TRUE);
		m_Offset = 0;
		ASSERT(file.GetLength() < ULONG_MAX);
		m_Lang = (ULONG)file.GetLength();
		UpdateData(FALSE);
		file.Close();
		m_Offset_Ctrl.EnableWindow(FALSE);
		m_Testlang_Ctrl.EnableWindow(FALSE);
		m_Default = TRUE;
	}
}

void CDlgFreqTest::OnCheck2() 
{
	if ( m_Default_2 == TRUE ) 	m_Default_2 = FALSE;
	else if ( m_Default_2 == FALSE ) m_Default_2 = TRUE;
}

void CDlgFreqTest::SetCurrentTest(Zufallsgenerator_Tests *currTest)
{
	currentTest = currTest;
}

void CDlgFreqTest::Set_Poker_Flag( BOOL n )
{
	poker_flag = n;
}

void CDlgFreqTest::OnSelchangeTupelcombo() 
{
	tupel = m_TupelCombo_Ctrl.GetCurSel() + 1;
}



/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRunsTest 


CDlgRunsTest::CDlgRunsTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRunsTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRunsTest)
	m_Default_Run = TRUE;
	m_Random = FALSE;
	m_Default_Longrun = TRUE;
	m_Run_Ergebnis = _T("");
	m_Longrun_Ergebnis = _T("");
	m_Offset = 0;
	m_Testlang = 0;
	m_Runlang = 3;
	m_Longrunlang = 34;
	m_InfoStatic_Run = _T("");
	m_InfoStatic_LongRun = _T("");
	//}}AFX_DATA_INIT
	s_alternativeWindowText[0]=0;
}

BOOL CDlgRunsTest::OnInitDialog()
{

	CDialog::OnInitDialog();

	if (s_alternativeWindowText[0])
		SetWindowText(s_alternativeWindowText);

//	m_AlphaBox_Ctrl.EnableWindow(FALSE);
	m_Offset_Ctrl.EnableWindow(FALSE);
	m_Testlang_Ctrl.EnableWindow(FALSE);
	m_Runlang_Ctrl.EnableWindow(FALSE);
	m_Longrunlang_Ctrl.EnableWindow(FALSE);
	m_Longrun_Kre_Ctrl.ShowWindow(FALSE);
	m_Longrun_Hak_Ctrl.ShowWindow(FALSE);
	m_Run_Kre_Ctrl.ShowWindow(FALSE);
	m_Run_Hak_Ctrl.ShowWindow(FALSE);

	CParseIniFile2 iniFile;
	CParseIniFile2::CStringList AlphaList;
	int combolist_stringindex;

	if (iniFile.GetAlphaList(AlphaList) == -1)
	{
	}
	else
	{
		// Laden von dem Alpha-Parametern in ComboBox!!!
		// no problems due opening IniFile 
		while ( !AlphaList.IsEmpty()){
			m_AlphaBox_Ctrl.AddString(AlphaList.RemoveHead()); // Add alpha to combobox-list
		}	

		if (!iniFile.GetDefaultAlpha(alpha))
		{
			// A alpha is in the iniFile specified as default alpha 
			combolist_stringindex = m_AlphaBox_Ctrl.SelectString( -1, alpha);
		}
	}

	return TRUE;
}

void CDlgRunsTest::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}

void CDlgRunsTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRunsTest)
	//DDX_Control(pDX, IDC_INFO_STATIC_LONGRUN, m_InfoStatic_LongRun);
	DDX_Control(pDX, IDC_EDIT6, m_Longrunlang_Ctrl);
	DDX_Control(pDX, IDC_EDIT5, m_Runlang_Ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_Testlang_Ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_Offset_Ctrl);
	DDX_Control(pDX, IDC_ERFOLGNICHT_RUN, m_Run_Kre_Ctrl);
	DDX_Control(pDX, IDC_ERFOLG_RUN, m_Run_Hak_Ctrl);
	DDX_Control(pDX, IDC_ERFOLGNICHT_LONGRUN, m_Longrun_Kre_Ctrl);
	DDX_Control(pDX, IDC_ERFOLG_LONGRUN, m_Longrun_Hak_Ctrl);
	DDX_Control(pDX, IDC_COMBO1, m_AlphaBox_Ctrl);
	DDX_Check(pDX, IDC_CHECK2, m_Default_Run);
	DDX_Check(pDX, IDC_CHECK3, m_Random);
	DDX_Check(pDX, IDC_CHECK1, m_Default_Longrun);
	DDX_Text(pDX, IDC_RUN_ERGEBNIS, m_Run_Ergebnis);
	DDX_Text(pDX, IDC_LONGRUN_ERGEBNIS, m_Longrun_Ergebnis);
	DDX_Text(pDX, IDC_EDIT2, m_Offset);
	DDX_Text(pDX, IDC_EDIT4, m_Testlang);
	DDX_Text(pDX, IDC_EDIT5, m_Runlang);
	DDX_Text(pDX, IDC_EDIT6, m_Longrunlang);
	DDX_Text(pDX, IDC_INFO_STATIC_RUN, m_InfoStatic_Run);
	DDX_Text(pDX, IDC_INFO_STATIC_LONGRUN, m_InfoStatic_LongRun);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRunsTest, CDialog)
	//{{AFX_MSG_MAP(CDlgRunsTest)
	ON_BN_CLICKED(IDC_TESTBUTTON, OnTestbutton)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRunsTest 

void CDlgRunsTest::OnTestbutton() 
{
	UpdateData(TRUE);

	Runs_Test RT_test;
	Long_Run_Test LR_test;

	if (m_Default_Longrun == TRUE) LR_test.def=TRUE;
	else if (m_Default_Longrun == FALSE) LR_test.def=FALSE;

	if (m_Default_Run == TRUE) RT_test.def=TRUE;
	else if (m_Default_Run == FALSE) RT_test.def=FALSE;

	CStdioFile file;
	file.Open(infile, CFile::modeRead);

	ASSERT(file.GetLength() < ULONG_MAX);
	unsigned long l_filelength = (unsigned long)file.GetLength();
	if (((m_Longrunlang > l_filelength) && (m_Default_Longrun == FALSE)) || ((m_Longrunlang <= 0) && (m_Default_Longrun == FALSE)))
	{
		file.Close();
		m_Longrun_Hak_Ctrl.ShowWindow(FALSE);
		m_Longrun_Kre_Ctrl.ShowWindow(TRUE);
		m_InfoStatic_LongRun = _T("");
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_FALSCHE_LONGRUNLAENGE_DIALOG, pc_str, STR_LAENGE_STRING_TABLE);
		m_Longrun_Ergebnis = pc_str;
		UpdateData(FALSE);
		Message(IDS_STRING_TESTS_FALSCHE_LONGRUNLAENGE, MB_ICONEXCLAMATION, l_filelength);
	}
	else
	{
		file.Close();

		LR_test.Set_infile(infile);
		LR_test.Set_oldtitle(oldTitle);
		UpdateData(TRUE);
		LR_test.longrun_lang = m_Longrunlang;
		UpdateData(FALSE);
		LR_test.test();
		if ( LR_test.GetResult() == TRUE )
		{
			char tmpStr[128];
			UpdateData(TRUE);
			m_Run_Ergebnis = _T("");
			m_Longrun_Hak_Ctrl.ShowWindow(TRUE);
			m_Longrun_Kre_Ctrl.ShowWindow(FALSE);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TEST_LONGRUN_BESTANDEN, tmpStr, STR_LAENGE_STRING_TABLE);
			
		//	sprintf(tmpStr, pc_str, "Longrun Test");
			m_Longrun_Ergebnis = tmpStr;
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_INFO_LONGRUN, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(tmpStr, pc_str, m_Longrunlang, LR_test.longest_run_final);
			m_InfoStatic_LongRun = tmpStr;
			UpdateData(FALSE);
		}
		else if ( LR_test.GetResult() == FALSE )
		{
				char tmpStr[128];
			UpdateData(TRUE);
			m_Run_Ergebnis = _T("");
			m_Longrun_Hak_Ctrl.ShowWindow(FALSE);
			m_Longrun_Kre_Ctrl.ShowWindow(TRUE);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TEST_LONGRUN_NICHT_BESTANDEN, tmpStr, STR_LAENGE_STRING_TABLE);
		
			//sprintf(tmpStr, pc_str, "Longrun Test");
			m_Longrun_Ergebnis = tmpStr;
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_INFO_LONGRUN, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(tmpStr, pc_str, m_Longrunlang, LR_test.longest_run_final);
			m_InfoStatic_LongRun = tmpStr;
			UpdateData(FALSE);
		}
	}

	SHOW_HOUR_GLASS
	UpdateData(TRUE);
	
	CParseIniFile2 iniFile;

	RT_test.def2 = m_Random;
	RT_test.Set_runlang( m_Runlang );
	RT_test.Set_infile(infile);
	RT_test.Set_oldtitle(oldTitle);

	if (((!(RT_test.SetOffset(m_Offset) && RT_test.SetTestLength(m_Testlang)) && ((m_Default_Run == FALSE) /*&& (m_Testlang <= 0)*/)) || ((m_Default_Run == FALSE) && (m_Runlang == 0))) || (m_Testlang <= 0))
	{
		m_Run_Hak_Ctrl.ShowWindow(FALSE);
		m_Run_Kre_Ctrl.ShowWindow(TRUE);
		m_InfoStatic_Run = _T("");
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_FALSCHE_OFFSET_DIALOG, pc_str, STR_LAENGE_STRING_TABLE);
		m_Run_Ergebnis = pc_str;
		UpdateData(FALSE);
		Message(IDS_STRING_TESTS_FALSCHE_OFFSET, MB_ICONEXCLAMATION);
	}
	else
	{
		RT_test.Set_degr( m_Runlang );
		double parameter = iniFile.GetAlphaParam(alpha, RT_test.Get_degr());
		if ( 0 > parameter) return;
		RT_test.Set_DefParam(parameter);
		RT_test.test();

		if(!RT_test.GetResult())
		{
			char tmpStr[128];
			m_Run_Hak_Ctrl.ShowWindow(FALSE);
			m_Run_Kre_Ctrl.ShowWindow(TRUE);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TEST_RUNS_NICHT_BESTANDEN, tmpStr, STR_LAENGE_STRING_TABLE);
			
		//	sprintf(tmpStr, pc_str, "Run Test");
			m_Run_Ergebnis = tmpStr;
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_INFO, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(tmpStr, pc_str, RT_test.Get_DefParam(), RT_test.Get_test_ergeb());
			m_InfoStatic_Run = tmpStr;
			UpdateData(FALSE);
		}
		else
		{
			char tmpStr[128];
			m_Run_Kre_Ctrl.ShowWindow(FALSE);
			m_Run_Hak_Ctrl.ShowWindow(TRUE);
			UpdateData(TRUE);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TEST_RUNS_BESTANDEN, tmpStr, STR_LAENGE_STRING_TABLE);
			
		//	sprintf(tmpStr, pc_str, "Run Test");
			m_Run_Ergebnis = tmpStr;
			LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_INFO, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(tmpStr, pc_str, RT_test.Get_DefParam(), RT_test.Get_test_ergeb());
			m_InfoStatic_Run = tmpStr;
			UpdateData(FALSE);
		}
	}
	HIDE_HOUR_GLASS
}

void CDlgRunsTest::init(const char *Infile_, const char *OldTitle_)
{
	infile = Infile_;
	oldTitle = OldTitle_;
	CStdioFile file;
	file.Open(infile, CFile::modeRead);
	ASSERT(file.GetLength() < ULONG_MAX);
	m_Testlang = (unsigned long)file.GetLength();
	file.Close();
}

void CDlgRunsTest::OnSelchangeCombo1() 
{
	CParseIniFile2 iniFile;

	m_AlphaBox_Ctrl.GetLBText(m_AlphaBox_Ctrl.GetCurSel(), alpha);
}

void CDlgRunsTest::OnCheck2() // 1
{
	if ( m_Default_Run == TRUE )
	{
		m_Offset_Ctrl.EnableWindow(TRUE);
		m_Testlang_Ctrl.EnableWindow(TRUE);
		m_Runlang_Ctrl.EnableWindow(TRUE);
		m_Default_Run = FALSE;
	}
	else if ( m_Default_Run == FALSE )
	{
		CStdioFile file;
		file.Open(infile, CFile::modeRead);
		UpdateData(TRUE);
		m_Offset = 0;
		m_Runlang = 3;
		ASSERT(file.GetLength() < ULONG_MAX);
		m_Testlang = (unsigned long)file.GetLength();
		UpdateData(FALSE);
		file.Close();
		m_Offset_Ctrl.EnableWindow(FALSE);
		m_Testlang_Ctrl.EnableWindow(FALSE);
		m_Runlang_Ctrl.EnableWindow(FALSE);
		m_Default_Run = TRUE;
	}

}

void CDlgRunsTest::OnCheck3() // 2
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if ( m_Random == TRUE ) 	m_Random = FALSE;
	else if ( m_Random == FALSE ) m_Random = TRUE;
}


void CDlgRunsTest::OnCheck1() 
{
	if ( m_Default_Longrun == TRUE ) 	
	{
		m_Longrunlang_Ctrl.EnableWindow(TRUE);
		m_Default_Longrun = FALSE;
	}
	else if ( m_Default_Longrun == FALSE )
	{
		UpdateData(TRUE);
		m_Longrunlang = 34;
		UpdateData(FALSE);
		m_Longrunlang_Ctrl.EnableWindow(FALSE);
		m_Default_Longrun = TRUE;
	}
}

BOOL CDlgRunsTest::LoadAlphaList()
{
	CParseIniFile2 iniFile;
	CParseIniFile2::CStringList AlphaList;

	if (iniFile.GetAlphaList(AlphaList) == -1) return FALSE;
	else									   return TRUE;
}





/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFIPSTest140_1 


CDlgFIPSTest140_1::CDlgFIPSTest140_1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFIPSTest140_1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFIPSTest140_1)
	m_Entropie_Static = _T("");
	m_Longrun_Static = _T("");
	m_Monobit_Static = _T("");
	m_Pokertest_Static = _T("");
	m_Runstest_Static = _T("");
	m_Batterie_Static = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFIPSTest140_1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFIPSTest140_1)
	DDX_Control(pDX, IDC_BATTERIETEST, m_BatterieTest_Ctrl);
	DDX_Control(pDX, IDC_BMP_RUN_KRE, m_Run_Kre_Ctrl);
	DDX_Control(pDX, IDC_BMP_RUN_HAK, m_Run_Hak_Ctrl);
	DDX_Control(pDX, IDC_BMP_POKER_KRE, m_Poker_Kre_Ctrl);
	DDX_Control(pDX, IDC_BMP_POKER_HAK, m_Poker_Hak_Ctrl);
	DDX_Control(pDX, IDC_BMP_MONO_KRE, m_Mono_Kre_Ctrl);
	DDX_Control(pDX, IDC_BMP_MONO_HAK, m_Mono_Hak_Ctrl);
	DDX_Control(pDX, IDC_BMP_LONG_KRE, m_Long_Kre_Ctrl);
	DDX_Control(pDX, IDC_BMP_LONG_HAK, m_Long_Hak_Ctrl);
	DDX_Control(pDX, IDC_BMP_FIPS_KRE, m_Fips_Kre_Ctrl);
	DDX_Control(pDX, IDC_BMP_FIPS_HAK, m_Fips_Hak_Ctrl);
	DDX_Text(pDX, IDC_ENTROPIE_STATIC, m_Entropie_Static);
	DDX_Text(pDX, IDC_TEXT_LONG, m_Longrun_Static);
	DDX_Text(pDX, IDC_TEXT_MONO, m_Monobit_Static);
	DDX_Text(pDX, IDC_TEXT_POKER, m_Pokertest_Static);
	DDX_Text(pDX, IDC_TEXT_RUN, m_Runstest_Static);
	DDX_Text(pDX, IDC_TEXT_BATTERIE, m_Batterie_Static);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFIPSTest140_1, CDialog)
	//{{AFX_MSG_MAP(CDlgFIPSTest140_1)
	ON_BN_CLICKED(IDC_BATTERIETEST, OnBatterietest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFIPSTest140_1 

void CDlgFIPSTest140_1::OnBatterietest() 
{
	UINT tests = 0;

	// Entropie Steuerelemente
	UpdateData(TRUE);
	char tmpStr[128];
	LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_FIPS_ENTROPIE, pc_str, STR_LAENGE_STRING_TABLE);

	char str_entropyBin[20];
	double_fmt(EntropyBin_mod(infile, oldTitle), str_entropyBin, 3);
	sprintf(tmpStr, pc_str, str_entropyBin);
	m_Entropie_Static = tmpStr;
	UpdateData(FALSE);

	// Mono-Bit-Test Steuerelemente
	Freq_Test FREQT;
	FREQT.def = TRUE;
	FREQT.def2 = FALSE;
	FREQT.Set_infile(infile);
	FREQT.Set_oldtitle(oldTitle);
	FREQT.SetTestLength(2500);
	FREQT.fips = TRUE;
	FREQT.test();
	if ((FREQT.einsen > 9654) && (FREQT.einsen < 10346))
	{
		
		m_Mono_Hak_Ctrl.ShowWindow(TRUE);
		m_Mono_Kre_Ctrl.ShowWindow(FALSE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Mono-Bit Test");
		m_Monobit_Static = tmpStr;
		UpdateData(FALSE);
		tests++;
	}
	else
	{
		m_Mono_Hak_Ctrl.ShowWindow(FALSE);
		m_Mono_Kre_Ctrl.ShowWindow(TRUE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_NICHT_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Mono-Bit Test");
		m_Monobit_Static = tmpStr;
		UpdateData(FALSE);
	}

	// Longrun-Test Steuerelemente
	Long_Run_Test LRT;
	LRT.def = TRUE;
	LRT.def2 = FALSE;
	LRT.Set_infile(infile);
	LRT.Set_oldtitle(oldTitle);
	LRT.SetTestLength(2500);
	LRT.fips = TRUE;
	LRT.test();
	if (LRT.GetResult())
	{
		m_Long_Hak_Ctrl.ShowWindow(TRUE);
		m_Long_Kre_Ctrl.ShowWindow(FALSE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Longrun Test");
		m_Longrun_Static = tmpStr;
		UpdateData(FALSE);
		tests++;
	}
	else
	{
		m_Long_Hak_Ctrl.ShowWindow(FALSE);
		m_Long_Kre_Ctrl.ShowWindow(TRUE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_NICHT_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Longrun Test");
		m_Longrun_Static = tmpStr;
		UpdateData(FALSE);
	}

	// Poker-Test Steuerelemente
	Poker_Test POKT;
	POKT.def = TRUE;
	POKT.def2 = FALSE;
	POKT.Set_infile(infile);
	POKT.Set_oldtitle(oldTitle);
	POKT.tupel = 4;
	POKT.SetTestLength(2500);
	POKT.fips = TRUE;
	POKT.test();
	if ((POKT.tmp_Test_Ergebnis > 1.03) && (POKT.tmp_Test_Ergebnis < 57.4))
	{
		m_Poker_Hak_Ctrl.ShowWindow(TRUE);
		m_Poker_Kre_Ctrl.ShowWindow(FALSE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Poker-Test");
		m_Pokertest_Static = tmpStr;
		UpdateData(FALSE);
		tests++;
	}
	else
	{
		m_Poker_Hak_Ctrl.ShowWindow(FALSE);
		m_Poker_Kre_Ctrl.ShowWindow(TRUE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_NICHT_BESTANDEN,pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Poker Test");
		m_Pokertest_Static = tmpStr;
		UpdateData(FALSE);
	}

	// Runs-Test Steuerelemente
	Runs_Test RUNT;
	RUNT.def = TRUE;
	RUNT.def2 = FALSE;
	RUNT.Set_infile(infile);
	RUNT.Set_oldtitle(oldTitle);
	RUNT.SetTestLength(2500);
	RUNT.fips = TRUE;

	// Die FIPS-PUB-140-1 Run Test Modifizierung
	long luck = 0, block = 0, summe = 0;
	for (int i = 1; i <= 33; i++)
	{
		if (i < 6)
		{
			block = RUNT.zaehle_luck_block(i, TRUE, infile, 0, 2500);
			luck = RUNT.zaehle_luck_block(i, FALSE, infile, 0, 2500);
			
			if((i == 1) && ((block >= 2267) && (block <= 2733)))
			{
				if((i == 1) && ((luck >= 2267) && (luck <= 2733))) summe++;
			}
			if((i == 2) && ((block >= 1079) && (block <= 1421)))
			{
				if((i == 2) && ((luck >= 1079) && (luck <= 1421))) summe++;
			}
			if((i == 3) && ((block >= 502) && (block <= 748)))
			{
				if((i == 3) && ((luck >= 502) && (luck <= 748))) summe++;
			}
			if((i == 4) && ((block >= 223) && (block <= 402)))
			{
				if((i == 4) && ((luck >= 223) && (luck <= 402))) summe++;
			}
			if((i == 5) && ((block >= 90) && (block <= 223)))
			{
				if((i == 5) && ((luck >= 90) && (luck <= 223))) summe++;
			}
		}

		
		if (i == 6)
		{
			block = 0;
			luck = 0;
		}

		if ((i >= 6) || (i == 6))
		{
			block += RUNT.zaehle_luck_block(i, TRUE, infile, 0, 2500);
			luck += RUNT.zaehle_luck_block(i, FALSE, infile, 0, 2500);
		}
	}
	if ((block >= 90) && (block <= 223))
	{
		if ((luck >= 90) && (luck <= 223)) summe++;
	}

	if (summe == 6)
	{
		m_Run_Hak_Ctrl.ShowWindow(TRUE);
		m_Run_Kre_Ctrl.ShowWindow(FALSE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Runs Test");
		m_Runstest_Static = tmpStr;
		UpdateData(FALSE);
		tests++;
	}
	else
	{
		m_Run_Hak_Ctrl.ShowWindow(FALSE);
		m_Run_Kre_Ctrl.ShowWindow(TRUE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_ERGEBNIS_NICHT_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "Runs Test");
		m_Runstest_Static = tmpStr;
		UpdateData(FALSE);
	}


	// Test-Baterie Steuerelemente
	if ( tests == 4 )
	{
		m_Fips_Hak_Ctrl.ShowWindow(TRUE);
		m_Fips_Kre_Ctrl.ShowWindow(FALSE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_BATTERIE_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "FIPS-PUB-140-1");
		m_Batterie_Static = tmpStr;
		UpdateData(FALSE);
	}
	else
	{
		m_Fips_Hak_Ctrl.ShowWindow(FALSE);
		m_Fips_Kre_Ctrl.ShowWindow(TRUE);
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(), IDS_STRING_TESTS_BATTERIE_NICHT_BESTANDEN, pc_str, STR_LAENGE_STRING_TABLE);
		char tmpStr[128];
		sprintf(tmpStr, pc_str, "FIPS-PUB-140-1");
		m_Batterie_Static = tmpStr;
		UpdateData(FALSE);
	}
}

BOOL CDlgFIPSTest140_1::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (s_alternativeWindowText[0])
		SetWindowText(s_alternativeWindowText);

	m_Fips_Hak_Ctrl.ShowWindow(FALSE);
	m_Long_Hak_Ctrl.ShowWindow(FALSE);
	m_Mono_Hak_Ctrl.ShowWindow(FALSE);
	m_Poker_Hak_Ctrl.ShowWindow(FALSE);
	m_Run_Hak_Ctrl.ShowWindow(FALSE);
	
	m_Fips_Kre_Ctrl.ShowWindow(FALSE);
	m_Long_Kre_Ctrl.ShowWindow(FALSE);
	m_Mono_Kre_Ctrl.ShowWindow(FALSE);
	m_Poker_Kre_Ctrl.ShowWindow(FALSE);
	m_Run_Kre_Ctrl.ShowWindow(FALSE);
	m_BatterieTest_Ctrl.ShowWindow(FALSE);

	CDlgFIPSTest140_1::OnBatterietest();

	return TRUE;
}

void CDlgFIPSTest140_1::init(const char *Infile_, const char *OldTitle_)
{
	infile = Infile_;
	oldTitle = OldTitle_;
}

void CDlgFIPSTest140_1::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}


BOOL CDlgFreqTest::LoadAlphaList()
{
	CParseIniFile2 iniFile;
	CParseIniFile2::CStringList AlphaList;

	if (iniFile.GetAlphaList(AlphaList) == -1) return FALSE;
	else									   return TRUE;
}

void CDlgFreqTest::OnStnClickedInfoStatic()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
}

