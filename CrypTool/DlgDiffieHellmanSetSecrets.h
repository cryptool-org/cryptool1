#if !defined(AFX_DLGDIFFIEHELLMANSETSECRETS_H__450BA49B_E599_11D6_A897_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANSETSECRETS_H__450BA49B_E599_11D6_A897_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanSetSecrets.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSetSecrets 

class CDlgDiffieHellmanSetSecrets : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanSetSecrets(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanSetSecrets)
	enum { IDD = IDD_DIFFIEHELLMAN_SETSECRETS };
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanSetSecrets)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanSetSecrets)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANSETSECRETS_H__450BA49B_E599_11D6_A897_00025532117A__INCLUDED_
