#if !defined(AFX_DLGDIFFIEHELLMANCREATESHAREDKEY_H__33449F32_E641_11D6_A898_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANCREATESHAREDKEY_H__33449F32_E641_11D6_A898_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanCreateSharedKey.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanCreateSharedKey 

class CDlgDiffieHellmanCreateSharedKey : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanCreateSharedKey(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanCreateSharedKey)
	enum { IDD = IDD_DIFFIEHELLMAN_CREATESHAREDKEY };
	CStatic	m_HeadingControl;
	CString	m_HeadingText;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanCreateSharedKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanCreateSharedKey)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANCREATESHAREDKEY_H__33449F32_E641_11D6_A898_00025532117A__INCLUDED_
