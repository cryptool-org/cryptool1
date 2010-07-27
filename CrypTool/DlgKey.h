/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

//////////////////////////////////////////////////////////////////
#ifndef DIA1_H
#define DIA1_H
// dia1.h : header file
//

#include "KeyRepository.h"
#include "ToolTipButton.h"

#define MAX_VIGENERE	1024

/////////////////////////////////////////////////////////////////////////////
// CDlgKey dialog

class CDlgKey : public CDialog
{
// Construction
	CToolTipButton m_Paste;

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
	CButton m_TextOptionsButton;
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
	afx_msg void OnTextOptions();
	virtual BOOL OnInitDialog();
	afx_msg void OnPasteKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
    char s_alternativeWindowText[127];

private:
	BOOL IsKeyInAlphabet (CString key, CString alphabet);
};

#endif // DIA1_H
