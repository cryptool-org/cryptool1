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
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////

#ifndef AFX_DLGMONO_H__D7708DFF_AEAD_11D2_8D42_00C04F795E36__INCLUDED_
#define AFX_DLGMONO_H__D7708DFF_AEAD_11D2_8D42_00C04F795E36__INCLUDED_

#include "ToolTipButton.h"

// DlgMono.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeySubstitution 

//#include "MyCEdit.h"

class CDlgKeySubstitution : public CDialog
{
	CToolTipButton m_Paste;

	// Konstruktion
public:
	CDlgKeySubstitution(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeySubstitution)
	enum { IDD = IDD_KEY_SUBSTITUTION };
	CEdit	m_edit2;
	CString	m_edit;
	//}}AFX_DATA
	int m_check;


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeySubstitution)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeySubstitution)
	afx_msg void OnChangeEdit1();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGMONO_H__D7708DFF_AEAD_11D2_8D42_00C04F795E36__INCLUDED_
