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

#include "stdafx.h"
#include "ToolTipButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CToolTipButton::CToolTipButton() {

}

CToolTipButton::~CToolTipButton() {

}


BEGIN_MESSAGE_MAP(CToolTipButton, CBitmapButton)

END_MESSAGE_MAP()

void CToolTipButton::SetToolTipText(CString *spText, BOOL bActivate) {
	if (spText == NULL) return;

	InitToolTip();

	if (m_ToolTip.GetToolCount() == 0) {
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, (LPCTSTR)*spText, rectBtn, 1);
	}

	m_ToolTip.UpdateTipText((LPCTSTR)*spText, this, 1);
	m_ToolTip.Activate(bActivate);
}

void CToolTipButton::InitToolTip() {
	if (m_ToolTip.m_hWnd == NULL) {
		m_ToolTip.Create(this);
		m_ToolTip.Activate(TRUE);
	}
}

BOOL CToolTipButton::PreTranslateMessage(MSG* pMsg) {
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);		
	return CBitmapButton::PreTranslateMessage(pMsg);
}