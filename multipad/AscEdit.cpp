// AscEdit.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "AscEdit.h"

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
	busy = 1;
	if((VK_BACK == nChar) || strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", nChar))
		CEdit::OnChar(nChar, nRepCnt, nFlags);
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
