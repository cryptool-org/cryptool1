// DlgParamRandSECUDE.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgParamRandSECUDE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgParamRandSECUDE 


DlgParamRandSECUDE::DlgParamRandSECUDE(CWnd* pParent /*=NULL*/)
	: CDialog(DlgParamRandSECUDE::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgParamRandSECUDE)
	LoadString(AfxGetInstanceHandle(),IDS_STRING_RAND_SECUDE,pc_str,STR_LAENGE_STRING_TABLE);
	m_MessageSecude = pc_str;
	//}}AFX_DATA_INIT
}


void DlgParamRandSECUDE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgParamRandSECUDE)
	DDX_Text(pDX, IDC_EDIT1, m_MessageSecude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgParamRandSECUDE, CDialog)
	//{{AFX_MSG_MAP(DlgParamRandSECUDE)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgParamRandSECUDE 
