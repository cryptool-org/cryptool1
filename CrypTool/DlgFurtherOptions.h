#if !defined(AFX_DLGFURTHEROPTIONS_H__8D7D8771_29E6_11D7_A8C6_00025532117A__INCLUDED_)
#define AFX_DLGFURTHEROPTIONS_H__8D7D8771_29E6_11D7_A8C6_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFurtherOptions.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFurtherOptions 

class CDlgFurtherOptions : public CDialog
{
// Konstruktion
public:
	CDlgFurtherOptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgFurtherOptions)
	enum { IDD = IDD_OPTIONS_FURTHEROPTIONS };
	BOOL	m_ShowIntroDialogue;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFurtherOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFurtherOptions)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGFURTHEROPTIONS_H__8D7D8771_29E6_11D7_A8C6_00025532117A__INCLUDED_
