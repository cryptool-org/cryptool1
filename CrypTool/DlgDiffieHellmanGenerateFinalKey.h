#if !defined(AFX_DLGDIFFIEHELLMANGENERATEFINALKEY_H__33449F34_E641_11D6_A898_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANGENERATEFINALKEY_H__33449F34_E641_11D6_A898_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanGenerateFinalKey.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanGenerateFinalKey 

class CDlgDiffieHellmanGenerateFinalKey : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanGenerateFinalKey(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanGenerateFinalKey)
	enum { IDD = IDD_DIFFIEHELLMAN_GENERATEFINALKEY };
	CStatic	m_HeadingControl;
	CString	m_HeadingText;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanGenerateFinalKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanGenerateFinalKey)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANGENERATEFINALKEY_H__33449F34_E641_11D6_A898_00025532117A__INCLUDED_
