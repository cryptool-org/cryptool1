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


// CDlgCrtSecretSharingOptions-Dialogfeld

class CDlgCrtSecretSharingOptions : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrtSecretSharingOptions)

public:
	CDlgCrtSecretSharingOptions(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtSecretSharingOptions();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int m_anzahl;
	int m_need;
	int calcmode;
	CString m_x;
	CString m_y;
	CEdit m_control_x;
	CEdit m_control_y;

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeCrtSecretsharingedit3();
	afx_msg void OnEnChangeCrtSecretsharingedit4();
};
