// DlgDiffieHellmanExchangeSharedKeys.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanExchangeSharedKeys.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanExchangeSharedKeys 


CDlgDiffieHellmanExchangeSharedKeys::CDlgDiffieHellmanExchangeSharedKeys(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanExchangeSharedKeys::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanExchangeSharedKeys)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanExchangeSharedKeys::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanExchangeSharedKeys)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanExchangeSharedKeys, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanExchangeSharedKeys)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanExchangeSharedKeys 
