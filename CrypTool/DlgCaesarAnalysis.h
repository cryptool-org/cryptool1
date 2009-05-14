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
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DIALOKEYCAESAR_H__03B5CD0D_8856_11D3_8779_00C04F795E36__INCLUDED_
#define AFX_DIALOKEYCAESAR_H__03B5CD0D_8856_11D3_8779_00C04F795E36__INCLUDED_

// DialoKeyCaesar.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCaesarAnalysis 

class CDlgCaesarAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgCaesarAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgCaesarAnalysis)
	enum { IDD = IDD_CAESAR_ANALYSIS };
	CEdit	m_text_ctl;
	CString	m_string;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCaesarAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCaesarAnalysis)
	afx_msg void OnUpdateEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// intializes the dialog
	virtual BOOL OnInitDialog();
	// this function creates the remark regarding the key offset
	CString createKeyOffsetRemark();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOKEYCAESAR_H__03B5CD0D_8856_11D3_8779_00C04F795E36__INCLUDED_
