//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_AUTOREN_H__831C14C1_3834_11D3_8A66_0020351F15C0__INCLUDED_
#define AFX_AUTOREN_H__831C14C1_3834_11D3_8A66_0020351F15C0__INCLUDED_

// Autoren.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAutoren 

class CAutoren : public CDialog
{
	// Konstruktion
public:
	CAutoren(CWnd* pParent = NULL);   // Standardkonstruktor
	
	// Dialogfelddaten
	//{{AFX_DATA(CAutoren)
	enum { IDD = IDD_AUTOREN };
	// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA
	
	
	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAutoren)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
	
	// Implementierung
protected:
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CAutoren)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_AUTOREN_H__831C14C1_3834_11D3_8A66_0020351F15C0__INCLUDED_
