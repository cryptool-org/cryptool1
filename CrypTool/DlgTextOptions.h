//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#ifndef AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_
#define AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_



// TextOptions.h : Header-Datei
//


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgTextOptions 


class CDlgTextOptions : public CDialog
{
// Konstruktion

public:
	CString m_StrTitle;
	int m_IgnoreCase;
	CDlgTextOptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgTextOptions)
	enum { IDD = IDD_RSADEMO_OPTIONS };
	CEdit	m_CtrlRefFile;
	CButton	m_CaseControl;
	CEdit	m_alphacontrol;
	BOOL	m_Format;
	CString	m_alphabet;
	BOOL	m_Case;
	BOOL	m_LeerVal;
	int		m_GrossVal;
	int		m_KleinVal;
	int		m_SatzVal;
	int		m_ZahlVal;
	BOOL	m_ConvertCase;
	CString	m_trenn;
	BOOL	m_addx;
	CString	m_StrRefFile;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgTextOptions)

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL



// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgTextOptions)
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnCheck2();
	virtual void OnOK();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnButtonTextoptionenSucheReferenzdatei();
	afx_msg void OnUpdateEditTextoptionenReferenzdatei();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int UpdateTags();
	CString OldAlphabet;
	BOOL	OldFormat;
	BOOL	OldCase;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.


#endif // AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_



