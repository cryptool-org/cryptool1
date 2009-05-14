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

// RSAStereotypedMSGDlg.h : Header-Datei
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
#define NTL_NO_MIN_MAX
#include "ZZ_helpers.h"
#include "StereotypedAttack.h"	// Hinzugefügt von der Klassenansicht
#if !defined(AFX_RSASTEREOTYPEDMSGDLG_H__F8A45C43_D105_4E33_A9D5_487CDD6679EA__INCLUDED_)
#define AFX_RSASTEREOTYPEDMSGDLG_H__F8A45C43_D105_4E33_A9D5_487CDD6679EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/////////////////////////////////////////////////////////////////////////////
// CRSAStereotypedMSGDlg Dialogfeld

class CRSAStereotypedMSGDlg : public CDialog
{
// Konstruktion
public:
	void checkParameters();
	void updateCipher();
	CRSAStereotypedMSGDlg(CWnd* pParent = NULL);	// Standard-Konstruktor
	static UINT thrFunction (LPVOID pParam);
// Dialogfelddaten
	//{{AFX_DATA(CRSAStereotypedMSGDlg)
	enum { IDD = IDD_RSASTEREOTYPED };
	CSpinButtonCtrl	m_spinLengthControl;
	CSpinButtonCtrl	m_spinPosControl;
	int		m_baseOfCipher;
	CString	m_cipher;
	int		m_bitsOfN;
	int		m_h;
	CString	m_N;
	CString	m_e;
	int		m_choice;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CRSAStereotypedMSGDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CRSAStereotypedMSGDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditplain();
	afx_msg void OnChangeEditlength();
	afx_msg void OnChangeEditpos();
	afx_msg void OnChangeEditn();
	afx_msg void OnChangeEdite();
	afx_msg void OnButtonencrypt();
	afx_msg void OnRadionumber();
	afx_msg void OnRadiohex();
	afx_msg void OnKillfocusEditcipher();
	afx_msg void OnChangeEdith();
	afx_msg void OnUpdateEditcipher();
	afx_msg void OnButtonstart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtoncancelattack();
	virtual void OnOK();
	afx_msg void OnRandom();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
	afx_msg void OnButtonlog();
	afx_msg void OnRadiochoice();
	afx_msg void OnButtondelete();
	afx_msg void OnChangeEditplainfull();
	afx_msg void OnKillfocusEdite();
	afx_msg void OnKillfocusEditn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void enableDisable(bool b);
	StereotypedAttack sa;
	void SetDlgItemZZ(int ID, ZZ value, int base, int group);
	ZZ GetDlgItemZZ(int ID, int base);
	void CheckEncryptButton();
	void updatePreview();
	void UpdateSliders();
	CWinThread* pThread;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_RSASTEREOTYPEDMSGDLG_H__F8A45C43_D105_4E33_A9D5_487CDD6679EA__INCLUDED_)
