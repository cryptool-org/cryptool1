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

#if !defined(AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_)
#define AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRandParamICG.h : Header-Datei
//

#include "KeyEdit.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgICGRandomParamater 

class CDlgICGRandomParamater : public CDialog
{
// Konstruktion
public:
	CDlgICGRandomParamater(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgICGRandomParamater)
	enum { IDD = IDD_ICG_RANDOMPARAMETER };
	CStatic	m_StaticGPA;
	CKeyEdit	m_PrimLang_Ctrl;
	CKeyEdit	m_Param_NCtrl;
	CKeyEdit	m_Param_bCtrl;
	CKeyEdit	m_Param_aCtrl;
	CString	m_Param_a;
	CString	m_Param_b;
	CString	m_Param_N;
	UINT	m_PrimLang;
	//}}AFX_DATA

	void Set( CString a, CString b, CString N )
	{ m_Param_a = a; m_Param_b = b; m_Param_N = N; }
	void SetPrimLang ( UINT Laenge ) { m_PrimLang = Laenge; }
	CString Get_a() { return m_Param_a; }
	CString Get_b() { return m_Param_b; }
	CString Get_N() { return m_Param_N; }

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgICGRandomParamater)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgICGRandomParamater)
	afx_msg void OnStaticGp_a();
	afx_msg void OnPrimbutton();
	afx_msg void OnStaticGpc();
	afx_msg void OnStaticGpp();
	afx_msg void OnStaticGpl();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRANDPARAMICG_H__9267A190_7C16_11D5_A850_00025532117A__INCLUDED_
