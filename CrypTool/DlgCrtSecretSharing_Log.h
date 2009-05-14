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

#pragma once


#include "afxwin.h"
#include "SizingDialog.h"
#ifndef baseCTestDlg
#define baseCTestDlg CSizingDialog
#endif
// CDlgCrtSecretSharing_Log-Dialogfeld

class CDlgCrtSecretSharing_Log : public baseCTestDlg
{
	DECLARE_DYNAMIC(CDlgCrtSecretSharing_Log)

public:
	CDlgCrtSecretSharing_Log(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtSecretSharing_Log();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_log;
	int m_need;
	int m_anzahl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCrtSecretsharingLogSave();
};
