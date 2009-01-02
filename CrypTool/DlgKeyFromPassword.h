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


#if !defined(AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_)
#define AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Schluessel_gen.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyFromPassword 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileTools.h"
#include "s_ecconv.h"
#include "SecudeLib.h"
#include "KeyFromPasswordPKCS5.h"	// Hinzugefügt von der Klassenansicht

class CDlgKeyFromPassword : public CDialog
{
// Konstruktion
public:
	void CheckEdit (CString & m_edit, int & sels, int & sele);
	CDlgKeyFromPassword(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyFromPassword)
	enum { IDD = IDD_KEY_FROM_PASSWORD };
	CEdit	m_control_zaehler;
	CEdit	m_control_dkLen;
	CEdit	m_control_schluessel;
	CEdit	m_control_passwort;
	CString	m_schluessel;
	CString	m_passwort;
	int		m_radio1;
	CString	m_salt;
	CString	m_dkLen;
	CString	m_zaehler;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyFromPassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyFromPassword)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONGenerieren();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnBUTTONcancel();
	afx_msg void OnBUTTONUebernehmen();
	afx_msg void OnUpdateEdit4();
	afx_msg void OnUpdateEdit5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CKeyFromPasswordPKCS5 SG;

public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_
