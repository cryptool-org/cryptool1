// DlgDiffieHellmanSetSecrets.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanSetSecrets.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSetSecrets 


CDlgDiffieHellmanSetSecrets::CDlgDiffieHellmanSetSecrets(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSetSecrets::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanSetSecrets)
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanSetSecrets::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanSetSecrets)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanSetSecrets, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanSetSecrets)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanSetSecrets 

void CDlgDiffieHellmanSetSecrets::OnOK() 
{
	UpdateData(true);
	
	CDialog::OnOK();
}
