#if !defined(AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_)
#define AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Schluessel_gen.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyFromPassword 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileTools.h"
#include "s_ecconv.h"
#include "SecudeLib.h"
#include "KeyFromPasswordPKCS5.h"	// Hinzugef�gt von der Klassenansicht

class CDlgKeyFromPassword : public CDialog
{
// Konstruktion
public:
	void CheckEdit (CString & m_edit, int & sels, int & sele);
	CDlgKeyFromPassword(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyFromPassword)
	enum { IDD = IDD_KEY_FROM_PASSWORD };
	CEdit	m_control_zaehler;
	CEdit	m_control_dkLen;
	CEdit	m_control_schluessel;
	CEdit	m_control_passwort;
	CString	m_schluessel;
	CString	m_passwort;
	int		m_radio1;
	CString	m_salt;
	CString	m_dkLen;
	CString	m_zaehler;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgKeyFromPassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyFromPassword)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONGenerieren();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnBUTTONcancel();
	afx_msg void OnBUTTONUebernehmen();
	afx_msg void OnUpdateEdit4();
	afx_msg void OnUpdateEdit5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CKeyFromPasswordPKCS5 SG;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_
