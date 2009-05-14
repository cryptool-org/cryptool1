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

#if !defined(AFX_GENECKURVE_H__8C9BF111_07D1_11D5_8898_00062919F268__INCLUDED_)
#define AFX_GENECKURVE_H__8C9BF111_07D1_11D5_8898_00062919F268__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenEcKurve.h : Header-Datei
//

// #include "Ber_Ell_Kurve.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgECGeneration 

class CDlgECGeneration : public CDialog
{
// Konstruktion
public:
	char line[256];
	CDlgECGeneration(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgECGeneration)
	enum { IDD = IDD_EC_GENERATION };
/*
	CEdit	m_control_edit2;
	CListCtrl	m_listview;
	CEdit	m_control_edit1;
	CButton	m_control_button_gen;
	CButton	m_control_button_accept;
	CString	m_edit1;
	int		m_radio1;
	int		m_radio3;
	int		m_edit_random_seed;
*/
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgECGeneration)
	protected:
/*
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
*/
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgECGeneration)
/*
	afx_msg void OnCheck1();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGen();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
*/
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Liste_leeren();
//	Ber_Ell_Kurve BEK;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_GENECKURVE_H__8C9BF111_07D1_11D5_8898_00062919F268__INCLUDED_
