// DlgDiffieHellmanIntro.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanIntro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanIntro 


CDlgDiffieHellmanIntro::CDlgDiffieHellmanIntro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanIntro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanIntro)
	m_Check_NoShow = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanIntro)
	DDX_Check(pDX, IDC_CHECK_NOSHOW, m_Check_NoShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanIntro, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanIntro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanIntro 

void CDlgDiffieHellmanIntro::OnOK() 
{
	UpdateData(true);
	
	// In CrypTool.INI ablegen, ob der Intro-Dialogue beim nächsten Start wieder aufgerufen werden soll
	this->m_Check_NoShow ? theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 0) : theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 1);
	
	CDialog::OnOK();
}
