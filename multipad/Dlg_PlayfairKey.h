#if !defined(AFX_DLG_PLAYFAIRKEY_H__B5942C33_4DBD_11D4_A048_002035F23D41__INCLUDED_)
#define AFX_DLG_PLAYFAIRKEY_H__B5942C33_4DBD_11D4_A048_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////


// Dlg_PlayfairKey.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlg_PlayfairKey 

class CDlg_PlayfairKey : public CDialog
{
	CBitmapButton m_Paste;
	// Konstruktion
public:
	~CDlg_PlayfairKey();
	CDlg_PlayfairKey(const char *infile,const char *outfile,int,int,CWnd* pParent = NULL);   // Standardkonstruktor
	char *GetData();
	int Display();

	class Playfair *m_Alg;
	int m_Dec;

// Dialogfelddaten
	//{{AFX_DATA(CDlg_PlayfairKey)
	enum { IDD = IDD_DIALOG_KEY_PLAYFAIR };
	int		m_use;
	int		m_sechs;
	CString m_text;
	CEdit	m_text_ctl;
	int		m_preformat;
	CButton m_prec;
	CString m_mat[6][6];
	CButton m_matc[11];
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlg_PlayfairKey)
	protected:
	// virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_PlayfairKey)
	afx_msg void OnSechs();
	afx_msg void OnCheck();
	afx_msg void OnChange();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_PLAYFAIRKEY_H__B5942C33_4DBD_11D4_A048_002035F23D41__INCLUDED_
