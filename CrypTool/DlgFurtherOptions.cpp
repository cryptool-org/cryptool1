// DlgFurtherOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFurtherOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFurtherOptions 


CDlgFurtherOptions::CDlgFurtherOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFurtherOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFurtherOptions)
	m_ShowIntroDialogue = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgFurtherOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFurtherOptions)
	DDX_Check(pDX, IDC_CHECK1, m_ShowIntroDialogue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFurtherOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgFurtherOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFurtherOptions 

void CDlgFurtherOptions::OnOK() 
{
	UpdateData(true);
	
	// In CrypTool.INI ablegen, ob der Intro-Dialogue beim nächsten Start wieder aufgerufen werden soll
	this->m_ShowIntroDialogue ? theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 1) : theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 0);
	
	CDialog::OnOK();
}

BOOL CDlgFurtherOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Soll Intro-Screen angezeigt werden? (Momentane Einstellung aus INI-Datei holen)
	if(theApp.GetProfileInt("Settings", "DH_IntroDialogue", 1))
	{
		this->m_ShowIntroDialogue = true;
		UpdateData(false);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
