#if !defined(AFX_DLGCERTTUTORIAL_H__5C53BF66_DE56_11D5_8A5D_000255320F1C__INCLUDED_)
#define AFX_DLGCERTTUTORIAL_H__5C53BF66_DE56_11D5_8A5D_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCertTutorial.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCertTutorial 

#include "TutorialCert.h"

class CDlgCertTutorial : public CDialog
{
// Konstruktion
public:
	CDlgCertTutorial(CWnd* pParent = NULL);   // Standardkonstruktor
	void InitRSA(CTutorialCert* Cert);
protected:
	CTutorialCert* m_Cert;


// Dialogfelddaten
	//{{AFX_DATA(CDlgCertTutorial)
	enum { IDD = IDD_DIALOG_CERT_TUTORIAL };
	CString	m_sFirstName;
	CString	m_sHash;
	CString	m_sHashEnc;
	CString	m_sName;
	CString	m_sModN;
	CString	m_sKeyPublic;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCertTutorial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCertTutorial)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGCERTTUTORIAL_H__5C53BF66_DE56_11D5_8A5D_000255320F1C__INCLUDED_
