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

#ifndef AFX_DIALOGLAENGEBIN_H__EA9CF03C_22EC_11D3_8D66_00C04F795E36__INCLUDED_
#define AFX_DIALOGLAENGEBIN_H__EA9CF03C_22EC_11D3_8D66_00C04F795E36__INCLUDED_

// DialogLaengeBin.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBinKeyLength 

class CDlgBinKeyLength : public CDialog
{
// Konstruktion
public:
	char m_c;
	CString m_title; // dialogue title
	CDlgBinKeyLength(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgBinKeyLength)
	enum { IDD = IDD_BIN_KEYLENGTH };
	CEdit	m_Ctl;
	CString	m_Char;
	UINT	m_laenge;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgBinKeyLength)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgBinKeyLength)
	afx_msg void OnChangeEdit2();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGLAENGEBIN_H__EA9CF03C_22EC_11D3_8D66_00C04F795E36__INCLUDED_
