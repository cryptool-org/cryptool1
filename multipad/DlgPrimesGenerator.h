#if !defined(AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_)
#define AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_

#include "Primes_and_random_numbers.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrimesGenerator.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// obere Schranke für RSA-Modul

const long c_MaxPrime_high=LONG_MAX/2-1;
const long c_MaxPrime_low=c_MaxPrime_high-127;

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgPrimesGenerator 

class DlgPrimesGenerator : public CDialog
{
	
	// Konstruktion
public:
	long Get_Random_Value(CString,CString);
	long Get_Prime2();
	long Get_Prime1();
	char line[256];
	double Get_Value(CString);
	DlgPrimesGenerator(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DlgPrimesGenerator)
	enum { IDD = IDD_DIALOG_PRIMES_GENERATOR };
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
	//{{AFX_VIRTUAL(DlgPrimesGenerator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgPrimesGenerator)
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonGenerate();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnUpdateEdit3();
	afx_msg void OnUpdateEdit4();
	virtual void OnCancel();
	afx_msg void OnButtonAccept();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Primes_and_random_numbers Parn;
	void CheckEdit_Input(CString &, int &, int &);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGPRIMESGENERATOR_H__0F161EA1_E56B_11D4_80D9_000629C93170__INCLUDED_
