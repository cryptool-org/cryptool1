//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
#define AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_

// TextEingabeHillAngriff.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CTextEingabeHillAngriff 

class CTextEingabeHillAngriff : public CDialog
{
// Konstruktion
public:
	int bis;
	int von;
	CTextEingabeHillAngriff(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CTextEingabeHillAngriff)
	enum { IDD = IDD_DIALOG_TEXTEINGABE_HILL_ANGRIFF };
	CComboBox	m_DimensionVon;
	CComboBox	m_DimensionBis;
	CString	m_EingabeFeld;
	int		m_Klartext;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CTextEingabeHillAngriff)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CTextEingabeHillAngriff)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDimVon();
	afx_msg void OnSelchangeDimBis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_TEXTEINGABEHILLANGRIFF_H__154D9E9D_8504_11D2_8D33_00C04F795E36__INCLUDED_
