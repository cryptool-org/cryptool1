#if !defined(AFX_SPLASH_H__7B21028B_3F82_11D5_8B0B_0010A4F6E7D5__INCLUDED_)
#define AFX_SPLASH_H__7B21028B_3F82_11D5_8B0B_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Splash.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSplash 

class CSplash : public CDialog
{
// Konstruktion
public:
	CSplash(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSplash)
	enum { IDD = IDD_SPLASH };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSplash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSplash)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SPLASH_H__7B21028B_3F82_11D5_8B0B_0010A4F6E7D5__INCLUDED_
