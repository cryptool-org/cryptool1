#if !defined(AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_)
#define AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Schluessel_gen.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_Schluessel_gen 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fileutil.h"
#include "s_ecconv.h"
#include "SecudeLib.h"
#include "Schluessel_gen.h"	// Hinzugefügt von der Klassenansicht

class Dlg_Schluessel_gen : public CDialog
{
// Konstruktion
public:
	void CheckEdit (CString & m_edit, int & sels, int & sele);
	Dlg_Schluessel_gen(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(Dlg_Schluessel_gen)
	enum { IDD = IDD_DIALOG_Schluessel_gen };
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


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(Dlg_Schluessel_gen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(Dlg_Schluessel_gen)
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
	Schluessel_gen SG;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_SCHLUESSEL_GEN_H__4BA93F41_1E11_11D5_88AA_00062919F268__INCLUDED_
