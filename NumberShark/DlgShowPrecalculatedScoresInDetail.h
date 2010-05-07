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

#ifndef _DLGSHOWPRECALCULATEDSCORESINDETAIL_H_
#define _DLGSHOWPRECALCULATEDSCORESINDETAIL_H_

#include "afxwin.h"
#include "MFC-ZahlenHaiDlg.h"

// CDlgShowPrecalculatedScoresInDetail dialog

class CDlgShowPrecalculatedScoresInDetail : public CDialog
{
	DECLARE_DYNAMIC(CDlgShowPrecalculatedScoresInDetail)

public:
	CDlgShowPrecalculatedScoresInDetail(CWnd* pParent = NULL);   // standard constructor
	CDlgShowPrecalculatedScoresInDetail(std::map<int, GameDataBlock> _mapPrecalculatedScores, CWnd* pParent = NULL);
	virtual ~CDlgShowPrecalculatedScoresInDetail();

// Dialog Data
	enum { IDD = IDD_SHOW_PRECALCULATED_SCORES_IN_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	std::map<int, GameDataBlock> mapPrecalculatedScores;
	std::map<int, GameDataBlock>::iterator mapPrecalculatedScoresIter;

	CString textPrecalculatedScores;
};

#endif