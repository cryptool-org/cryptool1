//////////////////////////////////////////////////////////////////

// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main

//////////////////////////////////////////////////////////////////

#ifndef AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_

#define AFX_TEXTOPTIONS_H__85C21241_18D7_11D3_8D64_00C04F795E36__INCLUDED_



// TextOptions.h : Header-Datei

//



/////////////////////////////////////////////////////////////////////////////

// Dialogfeld CTextOptions 



class CTextOptions : public CDialog

{

// Konstruktion

public:

	int m_IgnoreCase;

	CTextOptions(CWnd* pParent = NULL);   // Standardkonstruktor



// Dialogfelddaten

	//{{AFX_DATA(CTextOptions)

	enum { IDD = IDD_DIALOG_TEXTOPTIONEN };

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

	//}}AFX_DATA





// Überschreibungen

	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen

	//{{AFX_VIRTUAL(CTextOptions)

	protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	//}}AFX_VIRTUAL



// Implementierung

protected:



	// Generierte Nachrichtenzuordnungsfunktionen

	//{{AFX_MSG(CTextOptions)

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



