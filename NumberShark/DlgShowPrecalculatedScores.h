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

#ifndef _DLGSHOWPRECALCULATEDSCORES_H_
#define _DLGSHOWPRECALCULATEDSCORES_H_

#include "afxwin.h"
#include "MFC-ZahlenHaiDlg.h"

// CDlgShowPrecalculatedScores dialog

class CDlgShowPrecalculatedScores : public CDialog
{
	DECLARE_DYNAMIC(CDlgShowPrecalculatedScores)

public:
	CDlgShowPrecalculatedScores(CWnd* pParent = NULL);   // standard constructor
	CDlgShowPrecalculatedScores(std::map<int, GameDataBlock> _mapProved, std::map<int, GameDataBlock> _mapBestKnown, CWnd* pParent = NULL);
	virtual ~CDlgShowPrecalculatedScores();

// Dialog Data
	enum { IDD = IDD_SHOW_PRECALCULATED_SCORES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedShowSequence();

protected:
	CString intro;

	// flomar, 05/03/2010
	// see MFC-ZahlenHailDlg.h for details
	std::map<int, GameDataBlock> mapProved;
	std::map<int, GameDataBlock> mapBestKnown;

	CListCtrl controlListPrecalculatedScores;
};

#endif