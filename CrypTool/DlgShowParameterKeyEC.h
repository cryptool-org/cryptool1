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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
//
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#ifndef AFX_DlgEcKeysCreat_H__5ED8C31D_2D4B_11D3_8D68_00C04F795E36__INCLUDED_
#define AFX_DlgEcKeysCreat_H__5ED8C31D_2D4B_11D3_8D68_00C04F795E36__INCLUDED_

// DlgEcKeysCreat.h : Header-Datei
//


#include "DlgKeyAsymGeneration.h"
#include "s_ecFp.h" // elliptic curve stuff


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowParameterKeyEC 

class CDlgShowParameterKeyEC : public CDialog
{
// Konstruktion
public:
	CDlgShowParameterKeyEC(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgShowParameterKeyEC(EcDomParam_ac_ptr curveParameter, EcDomParamAcAsString* ecParamString, CString curveID, CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowParameterKeyEC)
	enum { IDD = IDD_SHOW_PARAMETER_KEY_EC };
	CListCtrl	m_privKey_listview;
	CListCtrl	m_pubKey_listview;
	CListCtrl	m_dom_param_listview;
	CButton	m_GenNewKeyPair;
	CString	m_ec_dom_par_editbox;
	//}}AFX_DATA

	// Eigene Klassenvariablen

	EcDomParamAcAsString *ecParamString;
	EcDomParam_ac_ptr curveParameter; // The Domain Parameter of the selected elliptic Curve
	int base;
	CString curveID;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowParameterKeyEC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	void UpdateEcListBox(EcDomParam_ac_ptr curveParameter, EcDomParamAcAsString *ecParamString);

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowParameterKeyEC)
	afx_msg void OnOctalRadio();
	afx_msg void OnDecimalRadio();
	afx_msg void OnHexRadio();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnNewKeyPair();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DlgEcKeysCreat_H__5ED8C31D_2D4B_11D3_8D68_00C04F795E36__INCLUDED_
