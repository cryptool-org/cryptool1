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
#ifndef AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_
#define AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_

// DlgSubstAna.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSubstitutionAnalysis 

class CDlgOptionsSubstitutionAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgOptionsSubstitutionAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsSubstitutionAnalysis)
	enum { IDD = IDD_OPTIONS_SUBSTITUTION_ANALYSIS };
	CButton	m_ctrl_storedKey;
	CButton	m_control2;
	CButton	m_control1;
	int		m_radio1;
	BOOL	m_check1;
	BOOL	m_check2;
	int		m_storedKey;
	CButton m_buttonSelectWordlistGerman;
	CButton m_buttonSelectWordlistEnglish;
	CString m_editWordlistGerman;
	CString m_editWordlistEnglish;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsSubstitutionAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsSubstitutionAnalysis)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck2();
	afx_msg void OnCheck1();
	afx_msg void OnRadio2();
	afx_msg void OnCheck3();
	afx_msg void OnRadio1();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnButtonSelectWordlistGerman();
	afx_msg void OnButtonSelectWordlistEnglish();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_
