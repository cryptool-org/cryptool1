#if !defined(AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_)
#define AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSA_mit_kleinenPZ.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RSA_mit_kleinenPZ 

class RSA_mit_kleinenPZ : public CDialog
{
// Konstruktion
public:
	
	void CheckEdit_Input(CString &,int&,int&);
	RSA_mit_kleinenPZ(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(RSA_mit_kleinenPZ)
	enum { IDD = IDD_DIALOG_RSA_MIT_KLEINEN_PRIMZAHLEN };
	CButton	m_verschluesseln;
	CButton	m_pz_generieren;
	CButton	m_entschluesseln;
	CEdit	m_control_eingabe_pz_q;
	CEdit	m_control_eingabe_pz_p;
	CString	m_eingabe_pz_p;
	CString	m_eingabe_pz_q;
	CString	m_oeffentliche_param_pq;
	CString	m_text_eingabe;
	CString	m_text_locherung;
	CString	m_verschluesselter_text;
	CString	m_oeffentl_schluessel_e;
	CString	m_geheimer_schluessel_d;
	CString	m_geheime_param;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(RSA_mit_kleinenPZ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(RSA_mit_kleinenPZ)
	afx_msg void OnUpdateEINGABEPZp();
	afx_msg void OnUpdateEINGABEPZq();
	afx_msg void OnUpdateEditOeffentlicheParam();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_
