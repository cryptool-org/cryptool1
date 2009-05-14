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

#ifndef _DLGPASSWORDGUIDELINES_
#define _DLGPASSWORDGUIDELINES_


// CDlgPasswordGuidelines-Dialogfeld

class CDlgPasswordGuidelines : public CDialog
{
public:
	CDlgPasswordGuidelines(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPasswordGuidelines();

// Dialog Data
	enum { IDD = IDD_PASSWORD_GUIDELINES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()

protected:
	CString stringMinimumLength;
	CString stringMinimumDigits;
	CString stringMinimumSpecial;
	CString stringSpecialGroup;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedDefault();
};

#endif