//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DIALOGLAENGE_H__EA9CF03B_22EC_11D3_8D66_00C04F795E36__INCLUDED_
#define AFX_DIALOGLAENGE_H__EA9CF03B_22EC_11D3_8D66_00C04F795E36__INCLUDED_

// DialogLaenge.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyLength 

class CDlgKeyLength : public CDialog
{
// Konstruktion
public:
	CDlgKeyLength(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyLength)
	enum { IDD = IDD_KEYLENGTH };
	UINT	m_laenge;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyLength)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyLength)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGLAENGE_H__EA9CF03B_22EC_11D3_8D66_00C04F795E36__INCLUDED_
