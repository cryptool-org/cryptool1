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
	CStatic	m_HeadingControl;
	CStatic	m_TextCtl;
	CString	m_Test;
	CString	m_HeadingText;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanSetSecrets)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanSetSecrets)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANSETSECRETS_H__450BA49B_E599_11D6_A897_00025532117A__INCLUDED_
