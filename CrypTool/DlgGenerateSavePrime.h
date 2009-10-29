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

#include "resource.h"

#pragma once


// CDlgGenerateSavePrime-Dialogfeld

class CDlgGenerateSavePrime : public CDialog
{
	DECLARE_DYNAMIC(CDlgGenerateSavePrime)

public:
	CDlgGenerateSavePrime(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgGenerateSavePrime();

// Dialogfelddaten
	enum { IDD = IDD_GENERATE_SAVE_PRIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	UINT m_Bitlength;
	CString m_Prime;
	CButton m_ctrlTakePrime;

	BOOL generateGermainPrime();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedGeneratePrime();
};
