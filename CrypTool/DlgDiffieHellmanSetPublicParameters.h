#if !defined(AFX_DLGDIFFIEHELLMANSETPUBLICPARAMETERS_H__216F5BDD_06A8_11D7_A8B6_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANSETPUBLICPARAMETERS_H__216F5BDD_06A8_11D7_A8B6_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanSetPublicParameters.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSetPublicParameters 

class CDlgDiffieHellmanSetPublicParameters : public CDialog
{
// Konstruktion
public:
	CString Heading;
	CDlgDiffieHellmanSetPublicParameters(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanSetPublicParameters)
	enum { IDD = IDD_DIFFIEHELLMAN_SETPUBLIC };
	CStatic	m_HeadingControl;
	CString	m_HeadingText;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanSetPublicParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanSetPublicParameters)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANSETPUBLICPARAMETERS_H__216F5BDD_06A8_11D7_A8B6_00025532117A__INCLUDED_
