//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
#define AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_

// TextEingabeHillAngriff.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHillAnaylsis 

class CDlgHillAnaylsis : public CDialog
{
// Konstruktion
public:
	int bis;
	int von;
	CDlgHillAnaylsis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgHillAnaylsis)
	enum { IDD = IDD_HILL_ANALYSIS };
	CComboBox	m_DimensionVon;
	CComboBox	m_DimensionBis;
	CString	m_EingabeFeld;
	int		m_Klartext;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgHillAnaylsis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgHillAnaylsis)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDimVon();
	afx_msg void OnSelchangeDimBis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
