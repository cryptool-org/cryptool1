// DlgKollision.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgKollision.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKollision 


CDlgKollision::CDlgKollision(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKollision::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKollision)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgKollision::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKollision)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKollision, CDialog)
	//{{AFX_MSG_MAP(CDlgKollision)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKollision  