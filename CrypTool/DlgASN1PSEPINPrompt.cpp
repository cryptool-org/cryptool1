// DlgASN1PSEPINPrompt.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgASN1PSEPINPrompt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgASN1PSEPINPrompt 


CDlgASN1PSEPINPrompt::CDlgASN1PSEPINPrompt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgASN1PSEPINPrompt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgASN1PSEPINPrompt)
	m_PIN = _T("");
	//}}AFX_DATA_INIT
}


void CDlgASN1PSEPINPrompt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgASN1PSEPINPrompt)
	DDX_Text(pDX, IDC_EDIT1, m_PIN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgASN1PSEPINPrompt, CDialog)
	//{{AFX_MSG_MAP(CDlgASN1PSEPINPrompt)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgASN1PSEPINPrompt 
