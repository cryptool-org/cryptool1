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
		// HINWEIS: Der Klassen-Assistent f�gt hier Datenelemente ein
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CSplash)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSplash)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_SPLASH_H__7B21028B_3F82_11D5_8B0B_0010A4F6E7D5__INCLUDED_
