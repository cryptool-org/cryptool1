#if !defined(AFX_DLGDIFFIEHELLMANFINALINFO_H__980C0D6F_6BF0_11D7_A8DB_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANFINALINFO_H__980C0D6F_6BF0_11D7_A8DB_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanFinalInfo.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanFinalInfo 

class CDlgDiffieHellmanFinalInfo : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanFinalInfo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanFinalInfo)
	enum { IDD = IDD_DIFFIEHELLMAN_FINALINFO };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanFinalInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanFinalInfo)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANFINALINFO_H__980C0D6F_6BF0_11D7_A8DB_00025532117A__INCLUDED_
