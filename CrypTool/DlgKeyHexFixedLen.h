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

#if !defined(AFX_DLGKEYHEXFIXEDLEN_H__F8863501_0F96_11D7_B75D_005056C00001__INCLUDED_)
#define AFX_DLGKEYHEXFIXEDLEN_H__F8863501_0F96_11D7_B75D_005056C00001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyHexFixedLen.h : Header-Datei
//
#include "HexEdit.h"
#include "ToolTipButton.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHexFixedLen 

class CDlgKeyHexFixedLen : public CDialog
{
// Konstruktion
public:
	virtual CString GetKeyFormatted();
	virtual bool ModeIsDecrypt();
	virtual int GetKeyByteLength();
	virtual char * GetKeyBytes();
	virtual void Init(CString title, int keylenmin, int keylenmax, int keylenstep, int parity_check = 0);
	CDlgKeyHexFixedLen(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHexFixedLen)
	enum { IDD = IDD_KEY_HEX_FIXED_LEN };
	CHexEdit	m_key_ctl;
	CComboBox	m_key_len_ctl;
	int		m_key_len_index;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHexFixedLen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CToolTipButton m_paste_key;
	CString m_title; // must be set via Init(...) on InitDialog
	int m_keylenmin, m_keylenmax, m_keylenstep; // must be set via Init(...) on InitDialog
	CFont m_font; // font for m_key_ctl
	bool m_modeisdecrypt; // available after DoModal has finished
	CString m_key_formatted; // available after DoModal has finished
	int m_parity_check;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHexFixedLen)
	afx_msg void OnChangeKeyLen();
	virtual BOOL OnInitDialog();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGKEYHEXFIXEDLEN_H__F8863501_0F96_11D7_B75D_005056C00001__INCLUDED_
