#if !defined(AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_)
#define AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPermutation.h : Header-Datei
//
#include "AscEdit.h"
#include "Cryptography.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutation 

// #define MAX_PERM_LENGTH <Innerhalb der Datei AscEdit.h defniert>

class CDlgKeyPermutation : public CDialog
{
	CBitmapButton m_Paste;
	// Konstruktion
public:
	int MakePermInt(CString *Pin, int p[], int pinv[]);
	CString makeASCII( CString &line);
	int PrintPerm(char *dest, int *perm, int len);
	int m_Dec;
	int MakePerm(CString *Pin, int p[MAX_PERM_LENGTH], int pinv[MAX_PERM_LENGTH]);
	int m_P1[MAX_PERM_LENGTH];
	int m_P1inv[MAX_PERM_LENGTH];
	int m_P1len;
	int m_P2[MAX_PERM_LENGTH];
	int m_P2inv[MAX_PERM_LENGTH];
	int m_P2len;
	CDlgKeyPermutation(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyPermutation)
	enum { IDD = IDD_KEY_PERMUTATION };
	CButton	m_Decrypt;
	CButton	m_Encrypt;
	CAscEdit	m_CPerm2;
	CAscEdit	m_CPerm1;
	CString	m_Perm1;
	CString	m_Perm2;
	CString	m_P1out;
	CString	m_P2out;
	int		m_P1InSeq;
	int		m_P1OutSeq;
	int		m_P2InSeq;
	int		m_P2OutSeq;
	int		m_P1Perm;
	int		m_P2Perm;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyPermutation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyPermutation)
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnPasteKey();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_
