#if !defined(AFX_DIALOGPLAYFAIR_H__10147001_4D8C_11D4_A042_002035F23D41__INCLUDED_)
#define AFX_DIALOGPLAYFAIR_H__10147001_4D8C_11D4_A042_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

// DialogPlayfair.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPlayfair 

class CChEdit : public CEdit
{
// Konstruktion
public:
	CChEdit();
	void SetAlg(class Playfair *alg,class CDialogPlayfair *dia)
	{
		m_Alg=alg;
		m_Dia=dia;
	}

public:
	virtual ~CChEdit();
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CChEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT, CPoint);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	class Playfair *m_Alg;
	class CDialogPlayfair *m_Dia;
};

class CMyEdit : public CEdit
{
// Konstruktion
public:
	CMyEdit();

	void SetAlg(class Playfair *alg) { m_Alg=alg; }

public:
	virtual ~CMyEdit();
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CChEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	class Playfair *m_Alg;
};

class CDialogPlayfair : public CDialog
{
// Konstruktion
public:
	CDialogPlayfair(const char *infile,const char *outfile,int,int,CWnd* pParent = NULL);   // Standardkonstruktor
	int Display();		// zeigt Dialog an
	void OnSechs();		// auf 5x5 oder 6x6 Matrix einstellen
	void OnDec();		// Ver- oder Entschlüsseln
	void OnCheck();		// Doppelte ignorieren oder nicht
	void OnUpdate();	// sobald ein neues Zeichen eingegeben wurde (Passwort, Matrix, oder Klartextvorgabe)
	void UpdatePassword();
	char *GetData();
	class Playfair *getAlg() const { return m_Alg; }
	int getDec() const { return m_Dec; }
	class CChEdit *getEinfeld(int i, int j) { return &m_einfeld[i][j]; }

	void InitListBox();
	void UpdateListBox();

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
	void OnAnalyse();	// Schalter Häufigkeitsanalyse [abgeschaltet TG]
	void OnManAnalyse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
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

	int m_sechs,m_Dec;
	CFont m_Font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPLAYFAIR_H__10147001_4D8C_11D4_A042_002035F23D41__INCLUDED_
