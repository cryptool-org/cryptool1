// DlgParamRandSECUDE.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgRandomParameterSECUDE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRandomParameterSECUDE 


CDlgRandomParameterSECUDE::CDlgRandomParameterSECUDE(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRandomParameterSECUDE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRandomParameterSECUDE)
	LoadString(AfxGetInstanceHandle(),IDS_STRING_RAND_SECUDE,pc_str,STR_LAENGE_STRING_TABLE);
	m_MessageSecude = pc_str;
	//}}AFX_DATA_INIT
}


void CDlgRandomParameterSECUDE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRandomParameterSECUDE)
	DDX_Text(pDX, IDC_EDIT1, m_MessageSecude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRandomParameterSECUDE, CDialog)
	//{{AFX_MSG_MAP(CDlgRandomParameterSECUDE)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRandomParameterSECUDE 
