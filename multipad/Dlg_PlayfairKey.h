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
// Konstruktion
public:
	~CDlg_PlayfairKey();
	CDlg_PlayfairKey(const char *infile,const char *outfile,int,int,CWnd* pParent = NULL);   // Standardkonstruktor
	char *GetData();
	int Display();

	class Playfair *m_Alg;
// Dialogfelddaten
	//{{AFX_DATA(CDlg_PlayfairKey)
	enum { IDD = IDD_DIALOG_KEY_PLAYFAIR };
	int		m_Dec;
	int		m_use;
	int		m_sechs;
	CString m_text;
	CEdit	m_text_ctl;
	CString m_mat[6][6];
	CButton m_matc[11];
	int		m_preformat;
	CButton m_prec;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlg_PlayfairKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlg_PlayfairKey)
	afx_msg void OnSechs();
	afx_msg void OnCheck();
	afx_msg void OnDec();
	afx_msg void OnChange();
	afx_msg void OnUpdateEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLG_PLAYFAIRKEY_H__B5942C33_4DBD_11D4_A048_002035F23D41__INCLUDED_
