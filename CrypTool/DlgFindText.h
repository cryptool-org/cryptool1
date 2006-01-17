#if !defined(AFX_DLGFINDTEXT_H__94A7CB7E_6FAC_4CA5_B549_AFACBF9F2AC8__INCLUDED_)
#define AFX_DLGFINDTEXT_H__94A7CB7E_6FAC_4CA5_B549_AFACBF9F2AC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFindText.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFindText 

class CDlgFindText : public CDialog
{
// Konstruktion
public:
	CDlgFindText(CWnd* pParent = NULL);   // Standardkonstruktor
	char *str_ttf;

// Dialogfelddaten
	//{{AFX_DATA(CDlgFindText)
	enum { IDD = IDD_FIND_TEXT };
	CEdit	m_CtrlSearchText;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFindText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFindText)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGFINDTEXT_H__94A7CB7E_6FAC_4CA5_B549_AFACBF9F2AC8__INCLUDED_
