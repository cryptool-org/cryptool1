#if !defined(AFX_DLG_FAKTORISIEREN_H__2F4A1B74_13B1_11D5_889F_00062919F268__INCLUDED_)
#define AFX_DLG_FAKTORISIEREN_H__2F4A1B74_13B1_11D5_889F_00062919F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Faktorisieren.h : Header-Datei
//

#include "Primfaktor_Zerlegung.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_Faktorisieren 

class Dlg_Faktorisieren : public CDialog
{
// Konstruktion
public:
	Dlg_Faktorisieren(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Dlg_Faktorisieren)
	enum { IDD = IDD_DIALOG_Faktorisieren };
	CEdit	m_control_2erfaktor;
	CEdit	m_control_lastcofaktor;
	CEdit	m_control_lastprime;
	CEdit	m_control_prim4;
	CEdit	m_control_prim3;
	CEdit	m_control_coprim2;
	CEdit	m_control_coprim1;
	CEdit	m_control_prim2;
	CEdit	m_control_prim1;
	CEdit	m_control_eingabe;
	CString	m_edit1_eingabe;
	CString	m_edit_prim1;
	CString	m_edit_prim2;
	CString	m_edit_coprim1;
	CString	m_edit_coprim2;
	int		m_radio1;
	CString	m_edit_prim3;
	CString	m_edit_prim4;
	int		m_lastprime;
	int		m_lastcofaktor;
	int		m_radio7;
	CString	m_edit_2erfaktor;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Dlg_Faktorisieren)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Dlg_Faktorisieren)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnBUTTONFaktorisieren();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnUpdateEdit3();
	afx_msg void OnUpdateEdit4();
	afx_msg void OnUpdateEdit5();
	afx_msg void OnUpdateEdit6();
	afx_msg void OnUpdateEdit7();
	afx_msg void OnUpdateEdit8();
	afx_msg void OnUpdateEdit9();
	afx_msg void OnUpdateEdit10();
	afx_msg void OnButtonOk();
	afx_msg void OnBUTTONcancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Primfaktor_Zerlegung PFAKT;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_FAKTORISIEREN_H__2F4A1B74_13B1_11D5_889F_00062919F268__INCLUDED_
