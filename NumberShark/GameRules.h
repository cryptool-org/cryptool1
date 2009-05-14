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
#include "afxwin.h"
#include "afxcmn.h"

// GameRules-Dialogfeld

class GameRules : public CDialog
{
	DECLARE_DYNAMIC(GameRules)

public:
	GameRules(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~GameRules();

// Dialogfelddaten
	enum { IDD = IDD_GAME_RULES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();
	CRichEditCtrl richEdit;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
