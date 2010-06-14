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
#include "EvoZahlenHai.h"
#include "afxwin.h"


// CGameSummary-Dialogfeld

class CGameSummary : public CDialog
{
	DECLARE_DYNAMIC(CGameSummary)

public:
	CGameSummary(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGameSummary();

// Dialogfelddaten
	enum { IDD = IDD_GAME_SUMMARY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl gameFinished;
	afx_msg void OnBnClickedOk();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	void gameAnalyse();
	void init(EvoZahlenHai &hai, CString exePath, CString summaryName, int proofed2 = 0, int bestKnown2 = 0, int bestValue = 0);
	CButton radioEdit1;
	CButton radioEdit2;
	int radio1;
	int radio2;


	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
