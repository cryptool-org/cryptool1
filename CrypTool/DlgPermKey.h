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
#ifndef _DLG_PERMKEY_H
#define _DLG_PERMKEY_H

#include "afxwin.h"
#include "resource.h"
#include "automated_permanalysis.h"

// CDlgPermKey dialog

class CDlgPermKey : public CDialog
{
	DECLARE_DYNAMIC(CDlgPermKey)

public:
	CDlgPermKey(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPermKey();
	void setPermKey1(const permkey *key, int dataType);

// Dialog Data
	enum { IDD = IDD_AUTOMATED_PERM_ANALYSIS_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int inDir1, permDir1, outDir1;
	int inDir2, permDir2, outDir2;
	int m_dataType;
	CString m_permKey1;
	CString m_inDir1;
	CString m_permDir1;
	CString m_outDir1;
	afx_msg void OnBnClickedCopyKey();
};

#endif