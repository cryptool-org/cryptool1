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


// DlgHillOptions dialog

class DlgHillOptions : public CDialog
{
	DECLARE_DYNAMIC(DlgHillOptions)

	DlgHillOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgHillOptions();

	unsigned long useFirstCharFromAlph;
   unsigned long m_offset;
	CString       m_ownCharForPadding;

   void readRegistry();
   void writeRegistry();

   friend class keyHillBase;

// Dialog Data
	enum { IDD = IDD_Hill_Options };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()

	BOOL OnInitDialog();
   afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeEdit2();
public:
   afx_msg void OnBnClickedOffset0();
   afx_msg void OnBnClickedOffset1();
};
