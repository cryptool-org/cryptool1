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
#include "afxcmn.h"


// CListResults dialog

class CListResults : public CDialog
{
	DECLARE_DYNAMIC(CListResults)

public:
	CListResults(const int &_numberOfBytesForEntropyCalculation, CWnd* pParent = NULL);   // standard constructor
	virtual ~CListResults();
	void LoadList(struct candidate *candidate_list, int listSize);

// Dialog Data
	enum { IDD = IDD_LIST_RESULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	struct candidate *clist;
		   int        clist_size;
		   int		  nItem;

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl resultListCtrl;
	virtual BOOL OnInitDialog();
	CString headerStr;
	afx_msg void OnBnClickedOk();
	char *get_keyhex();
	int numberOfBytesForEntropyCalculation;

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	RECT initialRectDialog;
	RECT initialRectList;
	RECT initialRectButtonOK;
	RECT initialRectButtonCancel;
};
