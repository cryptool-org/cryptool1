//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_
#define AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_

// DlgSubstAna.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSubstAna 

class CDlgSubstAna : public CDialog
{
// Konstruktion
public:
	CDlgSubstAna(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSubstAna)
	enum { IDD = IDD_DIALOG_ANALYSE_OPT_MONO };
	CButton	m_control2;
	CButton	m_control1;
	int		m_radio1;
	BOOL	m_check1;
	BOOL	m_check2;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSubstAna)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSubstAna)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck2();
	afx_msg void OnCheck1();
	afx_msg void OnRadio2();
	afx_msg void OnCheck3();
	afx_msg void OnRadio1();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSUBSTANA_H__A504DEF7_F0A2_11D2_8D5B_00C04F795E36__INCLUDED_
