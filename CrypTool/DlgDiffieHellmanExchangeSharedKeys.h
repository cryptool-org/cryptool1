#if !defined(AFX_DLGDIFFIEHELLMANEXCHANGESHAREDKEYS_H__33449F33_E641_11D6_A898_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANEXCHANGESHAREDKEYS_H__33449F33_E641_11D6_A898_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanExchangeSharedKeys.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanExchangeSharedKeys 

class CDlgDiffieHellmanExchangeSharedKeys : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanExchangeSharedKeys(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanExchangeSharedKeys)
	enum { IDD = IDD_DIFFIEHELLMAN_EXCHANGESHAREDKEYS };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanExchangeSharedKeys)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanExchangeSharedKeys)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANEXCHANGESHAREDKEYS_H__33449F33_E641_11D6_A898_00025532117A__INCLUDED_
