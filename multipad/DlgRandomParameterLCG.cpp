// DlgRandomParameterLCG.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRandomParameterLCG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandomParameterLCG 


DlgRandomParameterLCG::DlgRandomParameterLCG(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRandomParameterLCG::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRandomParameterLCG)
	m_LinParam_a = 0;
	m_LinParam_b = 0;
	m_Modul_N = 0;
	//}}AFX_DATA_INIT
}


void DlgRandomParameterLCG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRandomParameterLCG)
	DDX_Text(pDX, IDC_EDIT1, m_LinParam_a);
	DDX_Text(pDX, IDC_EDIT2, m_LinParam_b);
	DDX_Text(pDX, IDC_EDIT3, m_Modul_N);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRandomParameterLCG, CDialog)
	//{{AFX_MSG_MAP(DlgRandomParameterLCG)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgRandomParameterLCG 
