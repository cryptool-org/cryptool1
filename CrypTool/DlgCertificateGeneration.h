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


#if !defined(AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_)
#define AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCertTutorial.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCertificateGeneration 

#include "PSEDemo.h"

class CDlgCertificateGeneration : public CDialog
{
// Konstruktion
public:
	CDlgCertificateGeneration(CWnd* pParent = NULL);   // Standardkonstruktor
	BOOL m_PSEIsExtern;

	void InitRSA(CPSEDemo* Cert);
protected:
	CPSEDemo* m_Cert;
private:
	long	m_lTime;

// Dialogfelddaten
	//{{AFX_DATA(CDlgCertificateGeneration)
	enum { IDD = IDD_CERTIFICATE_GENERATION };
	CEdit	m_CtrlPINv;
	CEdit	m_CtrlPIN;
	CEdit	m_CtrlFirstName;
	CEdit	m_CtrlName;
	CEdit	m_CtrlKeyID;
	CButton	m_CtrlOK;
	CString	m_sDName;
	CString	m_sFirstName;
	CString	m_sKeyID;
	CString	m_sName;
	CString	m_sUserID;
	CString	m_sBitLength;
	CString	m_sPIN;
	CString	m_sPINv;
	CString	m_sKeyPublic;
	CString	m_sModN;
	//}}AFX_DATA
	

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCertificateGeneration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCertificateGeneration)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	virtual void OnOK();
	afx_msg void OnPseImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_
