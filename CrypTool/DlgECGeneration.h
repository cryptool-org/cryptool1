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


#if !defined(AFX_GENECKURVE_H__8C9BF111_07D1_11D5_8898_00062919F268__INCLUDED_)
#define AFX_GENECKURVE_H__8C9BF111_07D1_11D5_8898_00062919F268__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenEcKurve.h : Header-Datei
//

// #include "Ber_Ell_Kurve.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgECGeneration 

class CDlgECGeneration : public CDialog
{
// Konstruktion
public:
	char line[256];
	CDlgECGeneration(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgECGeneration)
	enum { IDD = IDD_EC_GENERATION };
/*
	CEdit	m_control_edit2;
	CListCtrl	m_listview;
	CEdit	m_control_edit1;
	CButton	m_control_button_gen;
	CButton	m_control_button_accept;
	CString	m_edit1;
	int		m_radio1;
	int		m_radio3;
	int		m_edit_random_seed;
*/
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgECGeneration)
	protected:
/*
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
*/
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgECGeneration)
/*
	afx_msg void OnCheck1();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGen();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
*/
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Liste_leeren();
//	Ber_Ell_Kurve BEK;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_GENECKURVE_H__8C9BF111_07D1_11D5_8898_00062919F268__INCLUDED_
