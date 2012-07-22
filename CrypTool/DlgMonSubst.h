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

#include "afxwin.h"
#if !defined(AFX_DLGMONSUBST_H__3570C2DB_B992_412D_BAAD_AC0520646674__INCLUDED_)
#define AFX_DLGMONSUBST_H__3570C2DB_B992_412D_BAAD_AC0520646674__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMonSubst.h : Header-Datei
//

#include "ToolTipButton.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgMonSubst 

class CDlgMonSubst : public CDialog
{
// Konstruktion
	CToolTipButton m_Paste;
	CFont m_font;

public:
	CDlgMonSubst(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgMonSubst();
	int   m_cryptDirection;

	// this returns the key (well, rather the complete mapping than just "the key")
	CString getKey() { return m_stringTo; };
	
	CString typeOfEncryption;
// Dialogfelddaten
	//{{AFX_DATA(CDlgMonSubst)
	enum { IDD = IDD_KEY_MONSUBST };
	CEdit	m_CtrlTo;
	CEdit	m_CtrlFrom;
	CEdit	m_CtrlKey;
	CEdit m_CtrlKeyOffset;
	CString m_stringTo;
	CString m_stringFrom;
	CString m_stringKey;
	CString m_stringKeyOffset;
	int m_RadioChooseKeyVariant;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgMonSubst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgMonSubst)
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	afx_msg void OnEncrypt();
	afx_msg void OnDecrypt();
	afx_msg void ComputeSubstKeyMapping();
	afx_msg void OnBnClickedRadioSubstFillAscendingOrder();
	afx_msg void OnBnClickedRadioAtbash();
	afx_msg void OnBnClickedRadioSubstFillDescendingOrder();
	afx_msg void OnBnClickedButtonTextoptions();
	afx_msg void OnChangedKeyOffset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
	int  CheckPasteKeyVariant(int SID, CString &keyStr);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGMONSUBST_H__3570C2DB_B992_412D_BAAD_AC0520646674__INCLUDED_
