// DlgTipsAndTricks.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgTipsAndTricks.h"
#include "iostream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgTipsAndTricks 


CDlgTipsAndTricks::CDlgTipsAndTricks(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTipsAndTricks::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTipsAndTricks)
	m_DoNotShowThisAgain = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgTipsAndTricks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTipsAndTricks)
	DDX_Check(pDX, IDC_CHECK2, m_DoNotShowThisAgain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTipsAndTricks, CDialog)
	//{{AFX_MSG_MAP(CDlgTipsAndTricks)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgTipsAndTricks 
