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
#include "asymmetric.h"

#define EC_KEYFILE_IDSTRING "EC"
#define RSA_KEYFILE_IDSTRING "RSA"
#define DSA_KEYFILE_IDSTRING "DSA"

#define MAX_RSA_MODULSIZE theApp.SecudeLib.MaxBits
#define MIN_RSA_MODULSIZE 301

#define PSEUDO_MASTER_CA_PINNR "1111"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAsymKeyCreat 

class CDlgAsymKeyCreat : public CDialog
{
// Konstruktion
public:
	CDlgAsymKeyCreat(CWnd* pParent = NULL);   // Standardkonstruktor

	~CDlgAsymKeyCreat();

// Dialogfelddaten
	//{{AFX_DATA(CDlgAsymKeyCreat)
	enum { IDD = IDD_DIALOG_KEY_CREAT_ASYM };
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
	CString	m_ec_dom_par_editbox;
	//}}AFX_DATA

	EcDomParamAcAsString ecParamString;
	EcDomParam_ac_ptr curveParameter; // The Domain Parameter of the selected elliptic Curve
	int rsa_modul; // The selected RSA modul size in bits 
	int dsa_prime; // The selected DSA prime size in bits

private:

	int base;
	CString curveID;


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgAsymKeyCreat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung		

protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgAsymKeyCreat)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// eigene Methoden

	void UpdateEcListBox(EcDomParam_ac_ptr curveParameterPtr, EcDomParamAcAsString *ecParamString, CString curveID);
	void CreateAsymKeys(); // Create asymmetric keypair

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DlgAsymKeyCreat_H__9BB28A3E_A60A_11D2_8881_00C04F795E28__INCLUDED_
