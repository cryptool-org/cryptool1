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

// RSABloemerMayDlg.h : Header-Datei
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
#if !defined(AFX_RSABLOEMERMAYDLG_H__2FCC9F46_5273_43AA_B181_9B96D9DC2FD4__INCLUDED_)
#define AFX_RSABLOEMERMAYDLG_H__2FCC9F46_5273_43AA_B181_9B96D9DC2FD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define NTL_NO_MIN_MAX



#include "BloemerMayAttack.h"



/////////////////////////////////////////////////////////////////////////////
// CRSABloemerMayDlg Dialogfeld

class CRSABloemerMayDlg : public CDialog
{
// Konstruktion
public:
	CRSABloemerMayDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	BloemerMayAttack sa;
	static UINT thrFunction (LPVOID pParam);
// Dialogfelddaten
	//{{AFX_DATA(CRSABloemerMayDlg)
	enum { IDD = IDD_RSABLOEMERMAY};
	int		m_m;
	CString	m_N;
	CString	m_e;
	CString	m_d;
	CString	m_P;
	CString	m_Q;
	CString	m_delta;
	CString	m_BitsOfN;
	int		m_choice;
	CString	m_maxdelta;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CRSABloemerMayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CRSABloemerMayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnRandom();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancelattack();
	afx_msg void OnChangeEditm();
	afx_msg void OnKillfocusEditdelta();
	afx_msg void OnCancel();
	afx_msg void OnChangeEditn();
	afx_msg void OnChangeEdite();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnButtondefault();
	afx_msg void OnButtonlog();
	afx_msg void OnRadiochoice();
	afx_msg void OnChangeEditd();
	afx_msg void OnChangeEditbitsofn();
	afx_msg void OnChangeEditdelta();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	double CStringToDouble(CString c);
	CString doubleToCString(double v);
	void checkStartButton();
	void enableDisable(bool v);
	ZZ GetDlgItemZZ(int ID, int base);
	long elapsedTime;
	CWinThread* pThread;

	void errorMessageBox(long ID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_RSABLOEMERMAYDLG_H__2FCC9F46_5273_43AA_B181_9B96D9DC2FD4__INCLUDED_)
