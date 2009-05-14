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

// GameRules2.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "GameRules2.h"


// GameRules2-Dialogfeld

IMPLEMENT_DYNCREATE(GameRules2, CDHtmlDialog)

GameRules2::GameRules2(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(GameRules2::IDD, GameRules2::IDH, pParent)
{
}

GameRules2::~GameRules2()
{
}

void GameRules2::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL GameRules2::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

BEGIN_MESSAGE_MAP(GameRules2, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(GameRules2)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// GameRules2-Meldungshandler

HRESULT GameRules2::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

HRESULT GameRules2::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}
