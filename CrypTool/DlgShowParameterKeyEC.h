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
