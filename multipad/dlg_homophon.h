#if !defined(AFX_DLG_HOMOPHON_H__0465EAB1_9543_11D4_BEA7_0006291976BD__INCLUDED_)
#define AFX_DLG_HOMOPHON_H__0465EAB1_9543_11D4_BEA7_0006291976BD__INCLUDED_

#include "homophon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_homophon.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld dlg_homophon 

class dlg_homophon : public CDialog
{
// Konstruktion
public:
	dlg_homophon(FILE *,FILE*,CWnd* pParent = NULL);   // Standardkonstruktor
	class Homophone *homophone;
// Dialogfelddaten
	//{{AFX_DATA(dlg_homophon)
	enum { IDD = IDD_HOMOPHON };
	CEdit	m_passphrasec;
	CEdit	m_inputc;
	CString	m_input;
	CString	m_passphrase;
	int		m_verschl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(dlg_homophon)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(dlg_homophon)
	afx_msg void OnChangeInput();
	afx_msg void OnVerschl();
	afx_msg void OnUpdatePassphrase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_HOMOPHON_H__0465EAB1_9543_11D4_BEA7_0006291976BD__INCLUDED_
#endif // AFX_DLG_HOMOPHON_H__0465EAB1_9543_11D4_BEA7_0006291976BD__INCLUDED_
#endif // AFX_DLG_HOMOPHON_H__0465EAB1_9543_11D4_BEA7_0006291976BD__INCLUDED_
