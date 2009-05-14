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

#if !defined(AFX_DLGOPTIONSSIGNATUREATTACK_H__A1F6ED92_B4D2_11D6_9DD2_000629718A52__INCLUDED_)
#define AFX_DLGOPTIONSSIGNATUREATTACK_H__A1F6ED92_B4D2_11D6_9DD2_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsSignatureAttack.h : Header-Datei
//

// #define _OPT_SIG_ATT_STANDARD_BITLENGTH	"16"
#define _OPT_SIG_ATT_STANDARD_BITLENGTH	16
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSignatureAttack 

class CDlgOptionsSignatureAttack : public CDialog
{
// Konstruktion
public:
	CDlgOptionsSignatureAttack(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsSignatureAttack)
	enum { IDD = IDD_OPTIONS_SIGNATURE_ATTACK };
	CButton	m_control_att_print;
	CButton	m_control_att_unprint;
	CButton	m_control_mod_method;
	CEdit	m_control_bitlength;
	CStatic	m_control_bitlength_range;
	CButton	m_control_check1;
	CButton	m_control_check3;
	CButton	m_control_check2;
	CButton	m_control_md2;
	int		m_hashalgorithm;
	CString	m_bitlength;
	int		m_mod_method;
	int		m_att_method;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsSignatureAttack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsSignatureAttack)
	virtual BOOL OnInitDialog();
	afx_msg void OnMD2();
	afx_msg void OnMD4();
	afx_msg void OnMD5();
	afx_msg void OnSHA();
	afx_msg void OnSHA_1();
	afx_msg void OnRIPEMD_160();
	virtual void OnOK();
	afx_msg void OnResetToDefault();
	afx_msg void OnCheck2();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetTextBitlengthRange();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGOPTIONSSIGNATUREATTACK_H__A1F6ED92_B4D2_11D6_9DD2_000629718A52__INCLUDED_
