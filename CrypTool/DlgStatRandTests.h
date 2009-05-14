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

#if !defined(AFX_DLG_TESTS_H__2330231D_80B3_11D5_A856_00025532117A__INCLUDED_)
#define AFX_DLG_TESTS_H__2330231D_80B3_11D5_A856_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RandomTest.h"
// Dlg_Tests.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFreqTest 

class CDlgFreqTest : public CDialog
{
// Konstruktion
public:
	BOOL LoadAlphaList();
	char tmpStr[128];
	UINT tupel;
	void Set_Poker_Flag ( BOOL n);
	void SetCurrentTest( Zufallsgenerator_Tests * currTest);
	Zufallsgenerator_Tests * currentTest;
	CDlgFreqTest(CWnd* pParent = NULL);   // Standardkonstruktor
	void SetAlternativeWindowText(LPCTSTR s_title);

// Dialogfelddaten
	//{{AFX_DATA(CDlgFreqTest)
	enum { IDD = IDD_FRQ_TEST };
	CComboBox	m_TupelCombo_Ctrl;
	CStatic	m_TupelStatic_Ctrl;
	CButton	m_Default_2_Ctrl;
	CEdit	m_Testlang_Ctrl;
	CEdit	m_Offset_Ctrl;
	CComboBox	m_AlphaCombo_Ctrl;
	CStatic	m_Bitmap_Ctrl2;
	CStatic	m_Bitmap_Ctrl;
	CString	m_Ergebnis;
	ULONG	m_Offset;
	ULONG	m_Lang;
	BOOL	m_Default;
	BOOL	m_Default_2;
	CString	m_Info_Static;
	//}}AFX_DATA

	CString alpha;

	const char *infile;
	const char *oldTitle;

	void init(const char *, const char *);
	const char *Get_infile() { return infile; }
	const char *Get_oldTitle() { return oldTitle; }

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFreqTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFreqTest)
	afx_msg void OnButtonFreqtest();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboAlpha();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnSelchangeTupelcombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL poker_flag;
    char s_alternativeWindowText[127];
public:
	afx_msg void OnStnClickedInfoStatic();
};


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRunsTest 

class CDlgRunsTest : public CDialog
{

// Konstruktion
public:
	void init( const char *infile_, const char *OldTitle_);
	CDlgRunsTest(CWnd* pParent = NULL);   // Standardkonstruktor
	void SetAlternativeWindowText(LPCTSTR s_title);
    BOOL LoadAlphaList();
// Dialogfelddaten
	//{{AFX_DATA(CDlgRunsTest)
	enum { IDD = IDD_RUNS_TEST };
	CString	m_InfoStatic_LongRun;
	CEdit	m_Longrunlang_Ctrl;
	CEdit	m_Runlang_Ctrl;
	CEdit	m_Testlang_Ctrl;
	CEdit	m_Offset_Ctrl;
	CStatic	m_Run_Kre_Ctrl;
	CStatic	m_Run_Hak_Ctrl;
	CStatic	m_Longrun_Kre_Ctrl;
	CStatic	m_Longrun_Hak_Ctrl;
	CComboBox	m_AlphaBox_Ctrl;
	BOOL	m_Default_Run;
	BOOL	m_Random;
	BOOL	m_Default_Longrun;
	CString	m_Run_Ergebnis;
	CString	m_Longrun_Ergebnis;
	UINT	m_Offset;
	UINT	m_Testlang;
	UINT	m_Runlang;
	UINT	m_Longrunlang;
	CString	m_InfoStatic_Run;
	//}}AFX_DATA

	const char *infile;
	const char *oldTitle;
	CString alpha;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRunsTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRunsTest)
	afx_msg void OnTestbutton();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	char s_alternativeWindowText[127];
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFIPSTest140_1 

class CDlgFIPSTest140_1 : public CDialog
{
// Konstruktion
public:
	void SetAlternativeWindowText(LPCTSTR s_title);
	void init ( const char *Infile_, const char *OldTitle_ );
	CDlgFIPSTest140_1(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgFIPSTest140_1)
	enum { IDD = IDD_FIPS_PUB_140_1 };
	CButton	m_BatterieTest_Ctrl;
	CStatic	m_Run_Kre_Ctrl;
	CStatic	m_Run_Hak_Ctrl;
	CStatic	m_Poker_Kre_Ctrl;
	CStatic	m_Poker_Hak_Ctrl;
	CStatic	m_Mono_Kre_Ctrl;
	CStatic	m_Mono_Hak_Ctrl;
	CStatic	m_Long_Kre_Ctrl;
	CStatic	m_Long_Hak_Ctrl;
	CStatic	m_Fips_Kre_Ctrl;
	CStatic	m_Fips_Hak_Ctrl;
	CString	m_Entropie_Static;
	CString	m_Longrun_Static;
	CString	m_Monobit_Static;
	CString	m_Pokertest_Static;
	CString	m_Runstest_Static;
	CString	m_Batterie_Static;
	//}}AFX_DATA

	const char *infile;
	const char *oldTitle;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFIPSTest140_1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFIPSTest140_1)
	afx_msg void OnBatterietest();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char s_alternativeWindowText[127];
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_TESTS_H__2330231D_80B3_11D5_A856_00025532117A__INCLUDED_
