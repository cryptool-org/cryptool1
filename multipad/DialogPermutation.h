#if !defined(AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_)
#define AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPermutation.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPermutation 

class CDialogPermutation : public CDialog
{
// Konstruktion
public:
	int m_Dec;
	int MakePerm(CString *Pin, int p[26], int pinv[26]);
	int m_P1[26];
	int m_P1inv[26];
	int m_P1len;
	int m_P2[26];
	int m_P2inv[26];
	int m_P2len;
	CDialogPermutation(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogPermutation)
	enum { IDD = IDD_DIALOG_PERMUTATION };
	CString	m_Perm1;
	CString	m_Perm2;
	CString m_PastedKey;
	CEdit   m_PastedKeyCtrl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDialogPermutation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogPermutation)
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_
