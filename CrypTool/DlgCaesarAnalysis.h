//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DIALOKEYCAESAR_H__03B5CD0D_8856_11D3_8779_00C04F795E36__INCLUDED_
#define AFX_DIALOKEYCAESAR_H__03B5CD0D_8856_11D3_8779_00C04F795E36__INCLUDED_

// DialoKeyCaesar.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCaesarAnalysis 

class CDlgCaesarAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgCaesarAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgCaesarAnalysis)
	enum { IDD = IDD_CAESAR_ANALYSIS };
	CEdit	m_text_ctl;
	CString	m_string;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgCaesarAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgCaesarAnalysis)
	afx_msg void OnUpdateEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOKEYCAESAR_H__03B5CD0D_8856_11D3_8779_00C04F795E36__INCLUDED_
