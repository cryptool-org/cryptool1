// DlgDiffieHellmanCreateSharedKey.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanCreateSharedKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanCreateSharedKey 


CDlgDiffieHellmanCreateSharedKey::CDlgDiffieHellmanCreateSharedKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanCreateSharedKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanCreateSharedKey)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanCreateSharedKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanCreateSharedKey)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanCreateSharedKey, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanCreateSharedKey)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanCreateSharedKey 
