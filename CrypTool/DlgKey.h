//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef DIA1_H
#define DIA1_H
// dia1.h : header file
//

#include "KeyRepository.h"
#define MAX_VIGENERE	1024

/////////////////////////////////////////////////////////////////////////////
// CDlgKey dialog

class CDlgKey : public CDialog
{
// Construction
	CBitmapButton m_Paste;

public:
	char strTitle[KEYDATA_HASHSTRING_LENGTH];
	void SetAlternativeWindowText(LPCTSTR s_title);
	long m_Decrypt;
	int len;

	CDlgKey( int maxlen, CWnd* pParent = NULL);   // standard constructor

	virtual char *	GetData( void );
	virtual int		GetLen( void );
	virtual int		Display();
// Dialog Data
	//{{AFX_DATA(CDlgKey)
	enum { IDD = IDD_KEY };
	CButton	m_EncryptionButton;
	CButton	m_DecryptionButton;
	CEdit	m_text_ctl;
	CString	m_text;
	CString	m_static_text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgKey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgKey)
	afx_msg void OnUpdateEdit1();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
    char s_alternativeWindowText[127];

};

#endif // DIA1_H
