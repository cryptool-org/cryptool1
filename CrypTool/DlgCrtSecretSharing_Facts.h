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


// CDlgCrtSecretSharing_Facts-Dialogfeld

class CDlgCrtSecretSharing_Facts : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrtSecretSharing_Facts)

public:
	CDlgCrtSecretSharing_Facts(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtSecretSharing_Facts();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING_FACTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString m_min_k;
	CString m_max_kminus1;
	CString m_w;
	CString m_s;
	CString m_a;
	CString m_s_;
	int m_need;
	int m_anzahl;
	CString m_log;
	afx_msg void OnBnClickedCrtShowlog();
	afx_msg void OnBnClickedOk();
	CString m_CrtFacts1;
	CString m_CrtFacts2;
};
