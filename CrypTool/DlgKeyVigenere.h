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
#ifndef AFX_DIALOGVIENEREKEY_H__EA9CF03D_22EC_11D3_8D66_00C04F795E36__INCLUDED_
#define AFX_DIALOGVIENEREKEY_H__EA9CF03D_22EC_11D3_8D66_00C04F795E36__INCLUDED_

// DialogVienereKey.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyVigenereAnalyisis 

class CDlgKeyVigenereAnalyisis : public CDialog
{
// Konstruktion
public:
	CDlgKeyVigenereAnalyisis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyVigenereAnalyisis)
	enum { IDD = IDD_KEY_ANALYSIS };
	CEdit	m_text_ctl;
	CString	m_Str;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyVigenereAnalyisis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyVigenereAnalyisis)
	afx_msg void OnUpdateEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGVIENEREKEY_H__EA9CF03D_22EC_11D3_8D66_00C04F795E36__INCLUDED_
