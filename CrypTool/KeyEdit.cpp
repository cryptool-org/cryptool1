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
