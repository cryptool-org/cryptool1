//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#ifndef AFX_DLGSHOWPRIVECKEYS_H__A9338988_441D_11D3_876A_00C04F795E36__INCLUDED_
#define AFX_DLGSHOWPRIVECKEYS_H__A9338988_441D_11D3_876A_00C04F795E36__INCLUDED_

// DlgShowPrivEcKeys.h : Header-Datei
//


#include "s_ecFp.h" // elliptic curve stuff
#include "AsymmetricEncryption.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowPrivateKeyEC 

class CDlgShowPrivateKeyEC : public CDialog
{
// Konstruktion
public:
	CDlgShowPrivateKeyEC(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgShowPrivateKeyEC(CString User, CString name, CString firstname, CString creattime, CString cID, EcDomParam_ac_ptr ecParam, CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowPrivateKeyEC)
	enum { IDD = IDD_SHOW_PRIVATEKEY_EC };
	CEdit	m_InfoKeyCreatedByCtrl;
	CEdit	m_TextKeyCreatDateCtrl;
	CEdit	m_TextKeyTypeCtrl;
	CEdit	m_TextKeyOwnerCtrl;
	CListCtrl	m_privKey_listview;
	CListCtrl	m_pubKey_listview;
	CListCtrl	m_dom_param_listview;
	CString	m_ec_dom_par_editbox;
	CString	m_InfoKeyCreatedBy;
	CString	m_InfoKeyType;
	CString	m_InfoCreatTime;
	CString	m_TextKeyOwner;
	CString	m_TextKeyType;
	CString	m_TextKeyCreatDate;
	//}}AFX_DATA

	EcDomParamAcAsString ecParamString;
	EcDomParam_ac_ptr curveParameter; // The Domain Parameter of the selected elliptic Curve
	CString UserId;
	CString curveID;
	CString Name;
	CString Firstname;
	CString CreatTime;
	int base;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowPrivateKeyEC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont m_Font;
	void UpdateEcListBox();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowPrivateKeyEC)
	afx_msg void OnOctalRadio();
	afx_msg void OnDecimalRadio();
	afx_msg void OnHexRadio();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSHOWPRIVECKEYS_H__A9338988_441D_11D3_876A_00C04F795E36__INCLUDED_
