//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
#define AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_

// About.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CAbout 

class CAbout : public CDialog
{
	// Konstruktion
public:
	CAbout(CWnd* pParent = NULL);   // Standardkonstruktor
	
	// Dialogfelddaten
	//{{AFX_DATA(CAbout)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_secude;               // Versionsstring der SecudeLib
	//}}AFX_DATA
	
	
	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAbout)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
	
	// Implementierung
protected:
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CAbout)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
