#if !defined(AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_)
#define AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCertTutorial.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCertificateGeneration 

#include "PSEDemo.h"

class CDlgCertificateGeneration : public CDialog
{
// Konstruktion
public:
	CDlgCertificateGeneration(CWnd* pParent = NULL);   // Standardkonstruktor
	BOOL m_PSEIsExtern;

	void InitRSA(CPSEDemo* Cert);
protected:
	CPSEDemo* m_Cert;
private:
	long	m_lTime;

// Dialogfelddaten
	//{{AFX_DATA(CDlgCertificateGeneration)
	enum { IDD = IDD_CERTIFICATE_GENERATION };
	CEdit	m_CtrlName;
	CButton	m_CtrlOK;
	CString	m_sDName;
	CString	m_sFirstName;
	CString	m_sKeyID;
	CString	m_sName;
	CString	m_sUserID;
	CString	m_sBitLength;
	CString	m_sPIN;
	CString	m_sPINv;
	CString	m_sKeyPublic;
	CString	m_sModN;
	//}}AFX_DATA
	

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCertificateGeneration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCertificateGeneration)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	virtual void OnOK();
	afx_msg void OnPseImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGCERTTUTORIAL_H__73C6A6D9_05B6_11D6_8A83_000255320F1C__INCLUDED_
