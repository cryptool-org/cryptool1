//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#ifndef AFX_DLGSHOWPUBECKEYS_H__A9338987_441D_11D3_876A_00C04F795E36__INCLUDED_
#define AFX_DLGSHOWPUBECKEYS_H__A9338987_441D_11D3_876A_00C04F795E36__INCLUDED_

// DlgShowPubEcKeys.h : Header-Datei
//


#include "s_ecFp.h" // elliptic curve stuff
#include "asymmetric.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowPubEcKeys 

class CDlgShowPubEcKeys : public CDialog
{
// Konstruktion
public:
	CDlgShowPubEcKeys(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgShowPubEcKeys(CString UserId, CString name, CString firstname, CString creattime, CString cID, EcDomParam_ac_ptr ecParam, CWnd* pParent = NULL);


// Dialogfelddaten
	//{{AFX_DATA(CDlgShowPubEcKeys)
	enum { IDD = IDD_DIALOG_EC_PUB_PARAM };
	CEdit	m_InfoKeyCreatedByCtrl;
	CEdit	m_TextKeyCreatDateCtrl;
	CEdit	m_TextKeyTypeCtrl;
	CEdit	m_TextKeyOwnerCtrl;
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

	// Eigene Klassenvariablen

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
	//{{AFX_VIRTUAL(CDlgShowPubEcKeys)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

	void CDlgShowPubEcKeys::UpdateEcListBox();

// Implementierung
protected:

	CFont m_Font;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowPubEcKeys)
	afx_msg void OnOctalRadio();
	afx_msg void OnDecimalRadio();
	afx_msg void OnHexRadio();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSHOWPUBECKEYS_H__A9338987_441D_11D3_876A_00C04F795E36__INCLUDED_
