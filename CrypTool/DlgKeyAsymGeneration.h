/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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
// Programmiert von Bartol Filipovic, 1999-2000
// Deutsche Bank AG Frankfurt - IT Security,
//////////////////////////////////////////////////////////////////

#include "resource.h"
#ifndef AFX_DlgAsymKeyCreat_H__9BB28A3E_A60A_11D2_8881_00C04F795E28__INCLUDED_
#define AFX_DlgAsymKeyCreat_H__9BB28A3E_A60A_11D2_8881_00C04F795E28__INCLUDED_

// DlgAsymKeyCreat.h : Header-Datei
//

#include "s_ecFp.h"
#include "AsymmetricEncryption.h"

#define EC_KEYFILE_IDSTRING "EC"
#define RSA_KEYFILE_IDSTRING "RSA"
#define DSA_KEYFILE_IDSTRING "DSA"

#define MAX_RSA_MODULSIZE theApp.SecudeLib.MaxBits
#define MIN_RSA_MODULSIZE 301

#define PSEUDO_MASTER_CA_PINNR "1111"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyAsymGeneration 

class CDlgKeyAsymGeneration : public CDialog
{
// Konstruktion
public:
	CDlgKeyAsymGeneration(CWnd* pParent = NULL);   // Standardkonstruktor

	~CDlgKeyAsymGeneration();

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyAsymGeneration)
	enum { IDD = IDD_KEYASYM_GENERATION };
	CListCtrl	m_dom_param_listview;
	CEdit	m_ctrl5;
	CButton	m_ShowKeypairButton;
	CButton	m_hexadecimal_radio;
	CButton	m_decimal_radio;
	CButton	m_octal_radio;
	CButton	m_RSARadio;
	CButton	m_ECRadio;
	CButton	m_DSARadio;
	CComboBox	m_ec_combo;
	CComboBox	m_dsa_combo;
	CComboBox	m_rsa_combo;
	CEdit	m_ctrl4;
	CEdit	m_ctrl3;
	CEdit	m_ctrl2;
	CEdit	m_ctrl1;
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit4;
	CString	m_rsa_modul_str;
	CString	m_dsa_prime_str;
	CString	m_ec_dom_par_str;
	int		m_verfahren;
	int		m_zahlensystem;
	BOOL	m_ShowKeypair;
	CString	m_user_keyinfo;
	CString	m_ec_dom_par_description;
	//}}AFX_DATA

	EcDomParamAcAsString ecParamString;
	EcDomParam_ac_ptr curveParameter; // The Domain Parameter of the selected elliptic Curve
	int rsa_modul; // The selected RSA modul size in bits 
	int dsa_prime; // The selected DSA prime size in bits

private:

	int base;
	CString curveID;


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgKeyAsymGeneration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung		

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyAsymGeneration)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeEcCombo();
	afx_msg void OnRSARadio();
	afx_msg void OnDSARadio();
	afx_msg void OnECRadio();
	afx_msg void OnDecimalRadio();
	afx_msg void OnOctalRadio();
	afx_msg void OnHexRadio();
	afx_msg void OnButtonP12import();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditLv();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// eigene Methoden

	void UpdateEcListBox(EcDomParam_ac_ptr curveParameterPtr, EcDomParamAcAsString *ecParamString, 
	                     CString curveID, BOOL WindowActive = TRUE);
	void CreateAsymKeys(); // Create asymmetric keypair
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DlgAsymKeyCreat_H__9BB28A3E_A60A_11D2_8881_00C04F795E28__INCLUDED_
