#if !defined(AFX_DLGTIPSANDTRICKS_H__DD18F6C2_8F64_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_DLGTIPSANDTRICKS_H__DD18F6C2_8F64_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTipsAndTricks.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgTipsAndTricks 

class CDlgTipsAndTricks : public CDialog
{
// Konstruktion
public:
	CDlgTipsAndTricks(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgTipsAndTricks)
	enum { IDD = IDD_DIALOG_TIPPS_AND_TRICKS };
	BOOL	m_DoNotShowThisAgain;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgTipsAndTricks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgTipsAndTricks)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGTIPSANDTRICKS_H__DD18F6C2_8F64_11D5_BB4A_000777640932__INCLUDED_
