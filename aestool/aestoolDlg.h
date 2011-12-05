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


// aestoolDlg.h : Header-Datei
// $Id$

#if !defined(AFX_AESTOOLDLG_H__A8D430F4_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_)
#define AFX_AESTOOLDLG_H__A8D430F4_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HexEdit1.h"
#include "aestoolcrypto.h"
#include "EditDropFilename.h"

#define PROGNAME "aestool.exe"

/////////////////////////////////////////////////////////////////////////////
// CAestoolDlg Dialogfeld


class CAestoolDlg : public CDialog
{
// Konstruktion
public:

	int DoDecrypt();
	int DoEncrypt ( void );
	CString CAestoolDlg::defaultDstName(SrcInfo *si, InfoBlock *ib,bool selfextracting = true);

	CString m_CMD_inKey;
	CString m_CMD_inName;
	CString m_CMD_outName;
	SrcInfo m_SrcInfo;
	int m_Format; // EXE or AES, controlled by radio button, see OnRadioFormat
	CString EXEName;
	CAestoolDlg(CString key,CString in,CString out,CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CAestoolDlg)
	enum { IDD = IDD_AESTOOL_DIALOG };
	CStatic	m_CStaticTitle;
	CButton	m_CButtonOK;
	CButton	m_CRadioExe;
	CButton	m_CRadioAes;
	CEditDropFilename	m_CEditSrc;
	
	// this is our control for HEX input
	CHexEdit	m_CHEditKey;
	// this is our control for ASCII input
	CEdit m_EditKey;
	// this is our memory for ASCII input (the derived password is stored here after PKCS#5-application)
	unsigned char *m_derivedPassword;
	unsigned int m_derivedPasswordLength;

	CButton	m_CButtonSrc;
	int		m_RadioFormat;
	int m_checkShowPassword;
	int m_checkEnterPasswordAsHex;
	int m_checkSecurelyDeleteSourceFileAfterEncryption;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAestoolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CAestoolDlg)
	virtual BOOL OnInitDialog();
	afx_msg	void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSucheSrc();
	virtual void OnOK();
	afx_msg void OnRadioFormat();
	afx_msg void OnHelp();
	afx_msg void EnDisableOK();
	afx_msg void EnDisableCheckSecurelyDeleteSourceFileAfterEncryption();
	afx_msg void OnChangeSrc();
	afx_msg void OnCheckShowPassword();
	afx_msg void OnCheckEnterPasswordAsHex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void securelyDeleteSourceFile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_AESTOOLDLG_H__A8D430F4_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_)
