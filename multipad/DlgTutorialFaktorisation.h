#if !defined(AFX_DLGTUTORIALFAKTORISATION_H__7EFC6C45_6316_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_DLGTUTORIALFAKTORISATION_H__7EFC6C45_6316_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTutorialFaktorisation.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgTutorialFaktorisation 

class DlgTutorialFaktorisation : public CDialog
{
// Konstruktion
public:
	DlgTutorialFaktorisation(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DlgTutorialFaktorisation)
	enum { IDD = IDD_DIALOG_ZAHL_FAKTORISIEREN };
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(DlgTutorialFaktorisation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgTutorialFaktorisation)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGTUTORIALFAKTORISATION_H__7EFC6C45_6316_11D5_BB4A_000777640932__INCLUDED_
