// DlgDiffieHellmanSetPublicParameters.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanSetPublicParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSetPublicParameters 


CDlgDiffieHellmanSetPublicParameters::CDlgDiffieHellmanSetPublicParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSetPublicParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanSetPublicParameters)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanSetPublicParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanSetPublicParameters)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanSetPublicParameters, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanSetPublicParameters)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanSetPublicParameters 
