// DlgDiffieHellmanGenerateFinalKey.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanGenerateFinalKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanGenerateFinalKey 


CDlgDiffieHellmanGenerateFinalKey::CDlgDiffieHellmanGenerateFinalKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanGenerateFinalKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanGenerateFinalKey)
		// HINWEIS: Der Klassen-Assistent f�gt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanGenerateFinalKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanGenerateFinalKey)
		// HINWEIS: Der Klassen-Assistent f�gt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanGenerateFinalKey, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanGenerateFinalKey)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgDiffieHellmanGenerateFinalKey 
