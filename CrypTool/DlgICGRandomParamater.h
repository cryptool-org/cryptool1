/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
