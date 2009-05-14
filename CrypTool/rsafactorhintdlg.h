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

// RSAFactorHintDlg.h : Header-Datei
//
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
#include "FileTools.h"
using namespace std;
#endif
#undef sub
#undef normalize
#undef trunc
#if !defined(AFX_RSAFACTORHINTDLG_H__871211EB_6F71_48AF_BD4B_DA7DBA6CE19A__INCLUDED_)
#define AFX_RSAFACTORHINTDLG_H__871211EB_6F71_48AF_BD4B_DA7DBA6CE19A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define NTL_NO_MIN_MAX
#include "FactorHint.h"
#include "ZZ_helpers.h"
/////////////////////////////////////////////////////////////////////////////
// CRSAFactorHintDlg Dialogfeld

class CRSAFactorHintDlg : public CDialog
{
// Konstruktion
public:
	ZZ GetDlgItemZZ(int ID, int base);
	CRSAFactorHintDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	static UINT thrFunction (LPVOID pParam);
// Dialogfelddaten
	//{{AFX_DATA(CRSAFactorHintDlg)
	enum { IDD = IDD_RSAFACTORHINT };
	int		m_msbLsb;
	int		m_base;
	int		m_bitsOfN;
	int		m_choice;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CRSAFactorHintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CRSAFactorHintDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadionumber();
	afx_msg void OnRadiohex();
	afx_msg void OnRadio3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancelattack();
	afx_msg void OnStart();
	afx_msg void OnRandom();
	afx_msg void OnKillfocusEditn();
	afx_msg void OnChangeEditbitsofn();
	afx_msg void updateNP();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
	afx_msg void OnButtonclose();
	afx_msg void OnButtonlog();
	afx_msg void OnRadiochoice();
	afx_msg void OnChangeEditn();
	afx_msg void OnChangeEditbitsofp();
	afx_msg void OnChangeEditb();
	afx_msg void OnRadiolsb();
	afx_msg void OnButtondefault();
	afx_msg void OnChangeGuessP();
	afx_msg void OnKillfocusGuessP();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ZZ m_GuessP;
	ZZ m_N;
	void updateP();
	ZZ m_p;
	void updateDim();
	void disableEnable(bool v);
	long elapsedTime;

	FactorHint fh;
	CWinThread* pThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_RSAFACTORHINTDLG_H__871211EB_6F71_48AF_BD4B_DA7DBA6CE19A__INCLUDED_)
