//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DIALOGLAENGE_H__EA9CF03B_22EC_11D3_8D66_00C04F795E36__INCLUDED_
#define AFX_DIALOGLAENGE_H__EA9CF03B_22EC_11D3_8D66_00C04F795E36__INCLUDED_

// DialogLaenge.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogLaenge 

class CDialogLaenge : public CDialog
{
// Konstruktion
public:
	CDialogLaenge(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogLaenge)
	enum { IDD = IDD_DIALOG_SCHLUESSELLAENGE };
	UINT	m_laenge;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDialogLaenge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogLaenge)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGLAENGE_H__EA9CF03B_22EC_11D3_8D66_00C04F795E36__INCLUDED_
