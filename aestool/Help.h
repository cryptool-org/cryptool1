#if !defined(AFX_HELP_H__A215EA40_8C80_4A45_98EC_556A23EEA225__INCLUDED_)
#define AFX_HELP_H__A215EA40_8C80_4A45_98EC_556A23EEA225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Help.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHelp 

class CHelp : public CDialog
{
// Konstruktion
public:
	CHelp(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CHelp)
	enum { IDD = IDD_HELP };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CHelp)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HELP_H__A215EA40_8C80_4A45_98EC_556A23EEA225__INCLUDED_
