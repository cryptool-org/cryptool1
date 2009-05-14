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


// KeyEdit.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "KeyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyEdit

CKeyEdit::CKeyEdit()
{
}

CKeyEdit::~CKeyEdit()
{
}


BEGIN_MESSAGE_MAP(CKeyEdit, CEdit)
	//{{AFX_MSG_MAP(CKeyEdit)
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CKeyEdit 

void CKeyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKeyEdit::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
/*	if(nFlags & (1<<13)) {
		switch(nChar) {
		case('p'):
		case('P'): m_Param_NCtrl.SetFocus();
			return;
		case('a'):
		case('A'): m_Param_bCtrl.SetFocus();
			return;
		}
	}	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
*/	
	CEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
