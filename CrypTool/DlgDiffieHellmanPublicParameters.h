#if !defined(AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanPublicParameters.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanPublicParameters 

class CDlgDiffieHellmanPublicParameters : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanPublicParameters(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanPublicParameters)
	enum { IDD = IDD_DIFFIEHELLMAN_PUBLICPARAMETERS };
	CEdit	m_PrimeControl;
	CEdit	m_GeneratorControl;
	CString	m_Generator;
	CString	m_Prime;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanPublicParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanPublicParameters)
	virtual void OnOK();
	afx_msg void OnGeneratePrime();
	afx_msg void OnGenerateGenerator();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_
