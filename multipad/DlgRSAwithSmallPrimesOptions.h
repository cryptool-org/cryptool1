#if !defined(AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_)
#define AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRSAwithSmallPrimesOptions.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSAwithSmallPrimesOptions 

class CDlgRSAwithSmallPrimesOptions : public CDialog
{
// Konstruktion
public:
	void MsgBlockLength();
	CDlgRSAwithSmallPrimesOptions(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgRSAwithSmallPrimesOptions)
	enum { IDD = IDD_RSA_WITH_SMALL_PRIMES_OPTIONS };
	CEdit	m_BlockLengthCtrl;
	CEdit	m_alphabetControl;
	CString	m_alphabet;
	int		m_numberBasis;
	int		m_TextOptions;
	UINT	m_BlockLength;
	int     m_Bitlength;
	CString	m_MaxBlockLength;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRSAwithSmallPrimesOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRSAwithSmallPrimesOptions)
	afx_msg void OnTextOptionsASCII();
	afx_msg void OnTextOptionsAlphabet();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAlphabet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_
