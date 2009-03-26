/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// AscEdit.cpp: Implementierungsdatei
//

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
