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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBruteForceAES 

#if !defined(AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_)
#define AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBruteForceAES 

class CDlgBruteForceAES : public CDialog, public CProgressModel
{
// Konstruktion
public:
	CDlgBruteForceAES(CWnd* pParent = NULL);   // Standardkonstruktor

	char m_data[256/8*2+1];
	int m_mask[256/8*2+1];
	int m_state; // -1: initially, 1: after first Step, 0: after last Step
	int m_len;
	int m_text_len;
	int m_parity_check;
	CString m_alg;
	int Display(char *titel,int keylenmin,int keylenmax, int keylenstep, int _parity_check = 0);
	int GetLen();
	int GetBinlen();
	int GetSearchBitLen();
	char *GetData();
	void GetDataInt(char *);
	int Step(); // set next key if not finished, otherwise return false
	virtual double getProgress(); // 0.0 <= result <= 1.0

// Dialogfelddaten
	//{{AFX_DATA(CDlgBruteForceAES)
	enum { IDD = IDD_BRUTEFORCE };
	CComboBox	m_keylen_ctl;
	CHexEdit m_text_ctl;
	int		m_keylenindex;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgBruteForceAES)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	char m_hexinc['F'];
	int m_keylenmin, m_keylenmax, m_keylenstep; // see CryptPar
	CFont m_font; // font for m_text_ctl
	CString m_text; // m_text_ctl content
	void UpdateDataMask();
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgBruteForceAES)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeKeyLen();
	virtual void OnOK();
	afx_msg void OnSetfocusHexEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_AESSUCHE_H__D6167951_518F_11D4_A04D_002035F23D41__INCLUDED_
