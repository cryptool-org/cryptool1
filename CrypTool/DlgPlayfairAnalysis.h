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

#include "PlayfairAnalysis.h"

/////////////////////////////////////////////////////////////////////////////
//
// Dialogfeld CDlgPlayfairAnalysis 
//

class CChEdit : public CEdit
{
// Konstruktion
public:
	CChEdit();
	void SetAlg(class CPlayfairAnalysis *alg,class CDlgPlayfairAnalysis *dia)
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
	class CPlayfairAnalysis *m_Alg;
	class CDlgPlayfairAnalysis *m_Dia;
};


/////////////////////////////////////////////////////////////////////////////
//
// Fenster CPlayfairEdit 
//

class CPlayfairEdit : public CEdit
{
	class CPlayfairAnalysis *m_Alg;
	BOOL			m_mode_ovr;
// Konstruktion
public:
	CPlayfairEdit();
	void SetAlg(class CPlayfairAnalysis *alg) { m_Alg=alg; }
// Attribute
public:
	int				m_TextWasPreformatted;
// Operationen
public:

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CPlayfairEdit)
	public:
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CPlayfairEdit();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CPlayfairEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditPaste();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//
//
//

class CDlgPlayfairAnalysis : public CDialog
{
/******* Ge�ndert Mark Santiago, Henrik Koy: Scroll Management */
	UINT m_nSBCode;
	int  m_nPos;
	BOOL m_bHScroll;
	int  m_iSMax;
	int  m_iPos;
/***************************************************************/
// Konstruktion
public:
	CDlgPlayfairAnalysis(const char *infile,const char *outfile,int,int,CWnd* pParent = NULL);   // Standardkonstruktor
	int Display();		// zeigt Dialog an
	void OnSechs();		// auf 5x5 oder 6x6 Matrix einstellen
	void OnCheck();		// Doppelte ignorieren oder nicht
	void OnUpdate();	// sobald ein neues Zeichen eingegeben wurde (Passwort, Matrix, oder Klartextvorgabe)
	void UpdatePassword();
	char *GetData();
	class CPlayfairAnalysis *getAlg() const { return m_Alg; }
	bool getDec() { return ((bool) m_Dec); }
	class CChEdit *getEinfeld(int i, int j) { return &m_einfeld[i][j]; }

	void InitListBox();

	void SetupListBox();
	int  SetupAnalysisWindow();
	void UpdateListBox();

	char getMatrixElement (int i, int j) { return m_mat[i][j][0]; }

	// Dialogfelddaten
	//{{AFX_DATA(CDlgPlayfairAnalysis)
	enum { IDD = IDD_PLAYFAIR_ANALYSIS };
	CScrollBar          m_ctrlScroll;
	int                 m_iScroll;
	CPlayfairEdit		m_txtfeld;
	CString             m_cipher;
	CString             m_password;
	CEdit               m_ciphfeld;
	CEdit               m_pwfeld;
	CListCtrl           m_listview;
	int					m_use;
	int					m_TextWasPreformatted;
	int                 m_ActualiseExpectedPlaintext;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgPlayfairAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void ScrollRange( int length_in_characters = 0);
	void ScrollPos(int iPos);
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgPlayfairAnalysis)
	virtual BOOL OnInitDialog();
	afx_msg void OnAnalyse();
	afx_msg void OnManAnalyse();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnChangeEditPlaintext();
	afx_msg void OnCheckTextWasPreformatted();
	afx_msg void OnSynchronise();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int size;
	char digbuf[MAXSHOWLETTER+2];
	CString m_mat[6][6];
	class CPlayfairAnalysis *m_Alg;
	class CChEdit	m_einfeld[6][6];
	int m_sechs,m_Dec;
	CFont m_Font;

	bool is6x6possible;
	bool isinvalidoccured;
};


#endif // AFX_DIALOGPLAYFAIR_H__10147001_4D8C_11D4_A042_002035F23D41__INCLUDED_


