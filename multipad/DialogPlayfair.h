#if !defined(AFX_DIALOGPLAYFAIR_H__10147001_4D8C_11D4_A042_002035F23D41__INCLUDED_)
#define AFX_DIALOGPLAYFAIR_H__10147001_4D8C_11D4_A042_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPlayfair.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPlayfair 

class CChEdit : public CEdit
{
// Konstruktion
public:
	CChEdit();
	void SetAlg(class Playfair *alg,class CDialogPlayfair *dia);
public:
	virtual ~CChEdit();
	class Playfair *m_Alg;
	class CDialogPlayfair *m_Dia;
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CChEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT, CPoint);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

class CMyEdit : public CEdit
{
// Konstruktion
public:
	CMyEdit();
	void SetAlg(class Playfair *alg);

public:
	virtual ~CMyEdit();
	class Playfair *m_Alg;
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CChEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

class CDialogPlayfair : public CDialog
{
// Konstruktion
public:
	CDialogPlayfair(const char *infile,const char *outfile,int,int,CWnd* pParent = NULL);   // Standardkonstruktor
	int Display();
	void OnSechs();
	void OnDec();
	void OnCheck();
	void OnUpdate();
	void UpdatePassword();
	char *GetData();
	int size;
	char digbuf[302];
	CString m_mat[6][6];
	int m_use;
	CString m_mytxt;
	CString m_cipher,m_password;
	class Playfair *m_Alg;
	class CChEdit	m_einfeld[6][6];
	class CEdit m_ciphfeld,m_pwfeld;
	class CMyEdit m_txtfeld;
	CListCtrl m_listview;
	void InitListBox();
	void UpdateListBox();

	int m_sechs,m_Dec;
	CFont m_Font;

	// Dialogfelddaten
	//{{AFX_DATA(CDialogPlayfair)
	enum { IDD = IDD_DIALOG_PLAYFAIR };
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogPlayfair)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogPlayfair)
	virtual BOOL OnInitDialog();
	void OnAnalyse();
	void OnManAnalyse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPLAYFAIR_H__10147001_4D8C_11D4_A042_002035F23D41__INCLUDED_
