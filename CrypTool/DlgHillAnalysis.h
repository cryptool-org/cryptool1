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
#ifndef AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
#define AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_

// TextEingabeHillAngriff.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHillAnaylsis 

class CDlgHillAnaylsis : public CDialog
{
// Konstruktion
public:
	int bis;
	int von;
	CDlgHillAnaylsis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgHillAnaylsis)
	enum { IDD = IDD_HILL_ANALYSIS };
	CComboBox	m_DimensionVon;
	CComboBox	m_DimensionBis;
	CString	m_EingabeFeld;
	int		m_Klartext;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHillAnaylsis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHillAnaylsis)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDimVon();
	afx_msg void OnSelchangeDimBis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
