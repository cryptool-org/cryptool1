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

#if !defined(AFX_DLGRANDOMPARAMETERLCG_H__B38FEE81_37E8_11D5_92F9_00B0D0161C45__INCLUDED_)
#define AFX_DLGRANDOMPARAMETERLCG_H__B38FEE81_37E8_11D5_92F9_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRandomParameterLCG.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgLCGRandomParameter 

class CDlgLCGRandomParameter : public CDialog
{
// Konstruktion
public:
	CDlgLCGRandomParameter(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgLCGRandomParameter)
	enum { IDD = IDD_LCG_RANDOMPARAMETER };
	CEdit	m_control_LinParam_N;
	CEdit	m_control_LinParam_b;
	CEdit	m_control_LinParam_a;
	CString	m_LinParam_a;
	CString	m_LinParam_b;
	CString	m_LinParam_N;
	//}}AFX_DATA

	CString Get_a() { return m_LinParam_a; }
	CString Get_b() { return m_LinParam_b; }
	CString Get_N() { return m_LinParam_N; }

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgLCGRandomParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgLCGRandomParameter)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRANDOMPARAMETERLCG_H__B38FEE81_37E8_11D5_92F9_00B0D0161C45__INCLUDED_
