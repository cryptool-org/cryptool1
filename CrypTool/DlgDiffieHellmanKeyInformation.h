#if !defined(AFX_DLGDIFFIEHELLMANKEYINFORMATION_H__DCD4E30B_94D6_4732_ABD6_6932BEAD9BEF__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANKEYINFORMATION_H__DCD4E30B_94D6_4732_ABD6_6932BEAD9BEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDiffieHellmanKeyInformation.h : Header-Datei
//
#include "DiffieHellmanLogFile.h"
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanKeyInformation 

class CDlgDiffieHellmanKeyInformation : public CDialog
{
// Konstruktion
public:
	CDlgDiffieHellmanKeyInformation(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgDiffieHellmanKeyInformation(std::string,std::string,DiffieHellmanLogFile*,CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanKeyInformation)
	enum { IDD = IDD_DIFFIEHELLMAN_KEY };
	CString	m_SessionKeyAlice;
	CString	m_SessionKeyBob;
	double	m_BitLengthAlice;
	double	m_BitLengthBob;
	CString	m_Verification;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanKeyInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanKeyInformation)
	afx_msg void OnShowlogtext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DiffieHellmanLogFile *pLogFile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANKEYINFORMATION_H__DCD4E30B_94D6_4732_ABD6_6932BEAD9BEF__INCLUDED_
