// DlgDiffieHellmanFinalInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgDiffieHellmanFinalInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanFinalInfo 


CDlgDiffieHellmanFinalInfo::CDlgDiffieHellmanFinalInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanFinalInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanFinalInfo)
		// HINWEIS: Der Klassen-Assistent f�gt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanFinalInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanFinalInfo)
		// HINWEIS: Der Klassen-Assistent f�gt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanFinalInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanFinalInfo)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgDiffieHellmanFinalInfo 
