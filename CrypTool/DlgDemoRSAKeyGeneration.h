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


#if !defined(AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_)
#define AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgKeyTutorial.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDemoRSAKeyGeneration 

#include "PSEDemo.h"

class CDlgDemoRSAKeyGeneration : public CDialog
{
// Konstruktion
public:
	CDlgDemoRSAKeyGeneration(CWnd* pParent = NULL);   // Standardkonstruktor

	void InitRSA(CPSEDemo* Cert);

protected:
	//CBitmap m_bmpCheck;
	//CBitmap m_bmpNoCheck;
	CBitmapButton m_ButtonInfo;

private:
	CPSEDemo* m_Cert; // Zertifikat
	CString m_sPrime_p_OLD;
	CString m_sPrime_q_OLD;
	CString m_sKeyPublic_OLD;

// Dialogfelddaten
	//{{AFX_DATA(CDlgDemoRSAKeyGeneration)
	enum { IDD = IDD_DEMO_RSAKEY_GENERATION };
	CStatic	m_BitLengthCtrl;
	CStatic	m_CheckPrimeCtrl;
	CStatic	m_CheckPublicCtrl;
	CEdit	m_KeyPublicCtrl;
	CButton	m_ButtonOKCtrl;
	CString	m_sPrime_p;
	CString	m_sPrime_q;
	CString	m_sKeyPublic;
	CString	m_sKeyPrivate;
	CString	m_sModN;
	CString	m_sPhiN;
	CString	m_sCheckPrime;
	CString	m_sCheckPublic;
	CString	m_sBitLength;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDemoRSAKeyGeneration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDemoRSAKeyGeneration)
	virtual BOOL OnInitDialog();
	afx_msg void OnGeneratePrime();
	afx_msg void OnUpdateParameter();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGKEYTUTORIAL_H__73C6A6D7_05B6_11D6_8A83_000255320F1C__INCLUDED_
