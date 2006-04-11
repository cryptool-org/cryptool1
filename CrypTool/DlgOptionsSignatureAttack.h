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


#if !defined(AFX_DLGOPTIONSSIGNATUREATTACK_H__A1F6ED92_B4D2_11D6_9DD2_000629718A52__INCLUDED_)
#define AFX_DLGOPTIONSSIGNATUREATTACK_H__A1F6ED92_B4D2_11D6_9DD2_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptionsSignatureAttack.h : Header-Datei
//

// #define _OPT_SIG_ATT_STANDARD_BITLENGTH	"16"
#define _OPT_SIG_ATT_STANDARD_BITLENGTH	16
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSignatureAttack 

class CDlgOptionsSignatureAttack : public CDialog
{
// Konstruktion
public:
	CDlgOptionsSignatureAttack(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsSignatureAttack)
	enum { IDD = IDD_OPTIONS_SIGNATURE_ATTACK };
	CButton	m_control_att_print;
	CButton	m_control_att_unprint;
	CButton	m_control_mod_method;
	CEdit	m_control_bitlength;
	CStatic	m_control_bitlength_range;
	CButton	m_control_check1;
	CButton	m_control_check3;
	CButton	m_control_check2;
	CButton	m_control_md2;
	int		m_hashalgorithm;
	CString	m_bitlength;
	int		m_mod_method;
	int		m_att_method;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsSignatureAttack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsSignatureAttack)
	virtual BOOL OnInitDialog();
	afx_msg void OnMD2();
	afx_msg void OnMD4();
	afx_msg void OnMD5();
	afx_msg void OnSHA();
	afx_msg void OnSHA_1();
	afx_msg void OnRIPEMD_160();
	virtual void OnOK();
	afx_msg void OnResetToDefault();
	afx_msg void OnCheck2();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetTextBitlengthRange();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGOPTIONSSIGNATUREATTACK_H__A1F6ED92_B4D2_11D6_9DD2_000629718A52__INCLUDED_
