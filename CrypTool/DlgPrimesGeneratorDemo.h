#if !defined(AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_)
#define AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrimesGenerator.h : Header-Datei
//

#include "IntegerArithmetic.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPrimesGeneratorDemo 

class CDlgPrimesGeneratorDemo : public CDialog
{

public:
	CDlgPrimesGeneratorDemo(CWnd* pParent = NULL);   // Standardkonstruktor
	BOOL GetRandomPrime( CString &OutStr, GeneratePrimes &P );

// Dialogfelddaten
	//{{AFX_DATA(CDlgPrimesGeneratorDemo)
	enum { IDD = IDD_PRIMES_GENERATOR_DEMO };
	CEdit	m_control_edit2;
	CEdit	m_control_edit1;
	CButton	m_control_button_generate;
	CButton	m_control_button_accept;
	CEdit	m_control_edit4;
	CEdit	m_control_edit3;
	int		m_radio1;
	int		m_radio4;
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit4;
	CString	m_edit5;
	CString	m_edit6;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgPrimesGeneratorDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgPrimesGeneratorDemo)
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGenerate();
	afx_msg void OnButtonAccept();
	afx_msg void OnEndDialog();
	afx_msg void OnUpdateEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_
