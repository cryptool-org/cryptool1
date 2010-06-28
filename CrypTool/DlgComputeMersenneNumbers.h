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

#ifndef _DLGCOMPUTEMERSENNENUMBERS_
#define _DLGCOMPUTEMERSENNENUMBERS_

#include "afxwin.h"

class CDlgComputeMersenneNumbers : public CDialog
{
	DECLARE_DYNAMIC(CDlgComputeMersenneNumbers)

public:
	CDlgComputeMersenneNumbers(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgComputeMersenneNumbers();

// Dialog Data
	enum { IDD = IDD_COMPUTE_MERSENNE_NUMBERS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCompute();
};

#endif