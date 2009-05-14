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

#if !defined(AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_)
#define AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGenRandomData.h : Header-Datei
//
#include "HexEdit.h"
#include "IntegerArithmetic.h"
#include "DlgX2ModNRandomParamater.h"
#include "DlgLCGRandomParameter.h"
#include "DlgICGRandomParamater.h"
#include "DlgShowProgress.h"
#include "afxwin.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRandomGenerator 

typedef struct
{
	int		m_SelGenerator;
	long	m_DataSize;
	CString m_seed;
	int     m_PrintInternalStates;

	// X^2 (mod N) Generator
	CX2ModNGenerator rnd_x2modN;
	CDlgX2ModNRandomParamater DRPXN;

	// LCG Generator
	LinearCongruenceGenerator DLCG;
	CDlgLCGRandomParameter DRP_LCG;

	// EICG Generator
	InverseCongruenceGenerator DICG;
	CDlgICGRandomParamater DRP_ICG;

} RandPar;

class CDlgRandomGenerator : public CDialog
{
// Konstruktion
public:


// ============================================
	//char outfile[128];

	CDlgRandomGenerator(CWnd* pParent = NULL);   // Standardkonstruktor
	

	//friend UINT GenRandomDataThread( PVOID pParam ); // Thread-Version

// Dialogfelddaten
	//{{AFX_DATA(CDlgRandomGenerator)
	enum { IDD = IDD_RANDOM_GENERATOR };
	CButton	m_CtrlSecudeGenerator;
	CHexEdit	m_seed_ctrl;
	int		m_SelGenerator;
	CString m_seed;
	long	m_DataSize;
	int     m_PrintInternalStates;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRandomGenerator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	RandPar* m_pPara;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRandomGenerator)
	afx_msg void OnSelGenParam();
	afx_msg void OnGenRandomData();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedRadio1();
	CButton m_ctrlSetInternalStates;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGGENRANDOMDATA_H__87703501_3308_11D5_92F3_00B0D0161C45__INCLUDED_
