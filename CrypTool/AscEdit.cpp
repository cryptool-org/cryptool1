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
#include "CrypToolApp.h"
#include "AscEdit.h"
#include "ChrTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAscEdit

CAscEdit::CAscEdit()
{
	busy = 0;
	m_mode = 0;
}

CAscEdit::~CAscEdit()
{
}


BEGIN_MESSAGE_MAP(CAscEdit, CEdit)
	//{{AFX_MSG_MAP(CAscEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAscEdit 

void CAscEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int s,e;
	char line[256];

	busy = 1;
	if(0==LineLength())
		m_mode = 0;
	if((VK_BACK == nChar) || (3 == nChar) || (22 == nChar)) // Backspace
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	else if(m_mode == 0) { // start mode 
		if(MyIsAlpha(nChar)) {
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			m_mode = 1;
		}
		else if(isdigit(nChar)) {
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			m_mode = 2;
		}
	}
	else if(m_mode == 1) { // Alpha Mode
		if ( MAX_PERM_LENGTH <= LineLength() )
		{
			LimitText(MAX_PERM_LENGTH);
			if(MyIsAlpha(nChar))
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			LimitText(0);
		}
		else if(MyIsAlpha(nChar))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else { // Numeric Mode
		if(isdigit(nChar))
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		else if(nChar == ',') {
			GetSel(s, e);
			GetLine(0, line, 255);
			if((s==0) || (line[s-1]!=','))
				CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	busy = 0;
}

/*void CAscEdit::OnChange() 
{
	int i, k, s, e;
	char *p;

	if(busy) return;
	busy = 1;
	SetRedraw(FALSE);
	GetSel(s, e);
	i = LineLength(0);
	p = (char *) malloc(i+3);
	i = GetLine(0, p, i+2);
	for(k=0; k<i; k++) {
		if(!strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", p[k])) {
			memcpy(p+k, p+k+1, i-k);
			k--;
			i--;
			if(k<s) s--;
			if(k<e) e--;
		}
	}
	SetWindowText(p);
	SetSel(s,e);
	free(p);
	SetRedraw(TRUE);
	Invalidate();
	busy = 0;
}*/
