#if !defined(AFX_DLG_PARAM_H__91FFB993_588B_11D4_A054_002035F23D41__INCLUDED_)
#define AFX_DLG_PARAM_H__91FFB993_588B_11D4_A054_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLG_param.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyParameter 

struct param
{
	char titel[10];
	L_NUMBER data[MAXLGTH];
};

class CDlgShowKeyParameter : public CDialog
{
// Konstruktion
public:
	bool disableOkButton;
	CDlgShowKeyParameter(CWnd* pParent = NULL);   // Standardkonstruktor

	int m_entries;
	struct param m_data[10];
	void addentry(char *,L_NUMBER *);
	void settitel(char *);

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowKeyParameter)
	enum { IDD = IDD_SHOW_KEY_PARAMETER };
	CButton	m_ctrlOK;
	CListCtrl	m_listctrl;
	int		m_radio;
	CString	m_titel;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowKeyParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void UpdateListBox();
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowKeyParameter)
	afx_msg void OnUpdate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_PARAM_H__91FFB993_588B_11D4_A054_002035F23D41__INCLUDED_
