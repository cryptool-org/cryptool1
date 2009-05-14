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

// GameRules.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "GameRules.h"
#include ".\gamerules.h"
#include <richedit.h>

// GameRules-Dialogfeld

IMPLEMENT_DYNAMIC(GameRules, CDialog)
GameRules::GameRules(CWnd* pParent /*=NULL*/)
	: CDialog(GameRules::IDD, pParent)
{
}

GameRules::~GameRules()
{
}

void GameRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, richEdit);
}

BEGIN_MESSAGE_MAP(GameRules, CDialog)
	
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


void GameRules::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnOK();
}

void GameRules::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	//Die Spielbeschreibung/Regeln werden in ein RichEdit Feld geschrieben.
	//Text kann jetzt herauskopiert werden
	CString rules;
	rules.LoadString(IDS_RULES);
	CString rules2;
	rules2.LoadString(IDS_RULES_2);
	richEdit.SetWindowText(rules + rules2);
	
	
	// TODO: Fügen Sie hier Ihren Meldungsbehandlungscode ein.
}
