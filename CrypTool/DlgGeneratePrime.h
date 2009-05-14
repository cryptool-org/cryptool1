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

#if !defined(AFX_DLGGENERATEPRIME_H__2CAA32A7_4FBA_4E0E_B4CD_7B609014B5A9__INCLUDED_)
#define AFX_DLGGENERATEPRIME_H__2CAA32A7_4FBA_4E0E_B4CD_7B609014B5A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGeneratePrime.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgGeneratePrime 

class CDlgGeneratePrime : public CDialog
{
// Konstruktion
public:
	CDlgGeneratePrime(CWnd* pParent = NULL);   // Standardkonstruktor
	BOOL GetRandomPrime( CString &OutStr, GeneratePrimes &P );

// Dialogfelddaten
	//{{AFX_DATA(CDlgGeneratePrime)
	enum { IDD = IDD_GENERATEPRIME };
	CEdit	m_control_edit2;
	CEdit	m_control_edit1;
	CButton	m_control_button_generate;
	CButton	m_control_button_accept;
	int		m_radio1;
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit5;
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgGeneratePrime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgGeneratePrime)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGenerate();
	afx_msg void OnButtonAccept();
	afx_msg void OnEndDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGGENERATEPRIME_H__2CAA32A7_4FBA_4E0E_B4CD_7B609014B5A9__INCLUDED_
