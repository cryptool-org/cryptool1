//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
#define AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_

// About.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAbout 

class CDlgAbout : public CDialog
{
	// Konstruktion
public:
	CDlgAbout(CWnd* pParent = NULL);   // Standardkonstruktor
	
	// Dialogfelddaten
	//{{AFX_DATA(CDlgAbout)
	enum { IDD = IDD_ABOUT };
	CStatic	m_cryptoolTxt_ctrl;
	CString	m_secude;               // Versionsstring der SecudeLib
	CString	m_cryptoolTxt;
	//}}AFX_DATA
	
	
	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgAbout)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
	
	// Implementierung
protected:
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgAbout)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
