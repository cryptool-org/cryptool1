// DlgRandParamICG.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRandParamICG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandParamICG 


DlgRandParamICG::DlgRandParamICG(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRandParamICG::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRandParamICG)
	m_Param_a = 0;
	m_Param_b = 0;
	m_Param_N = 0;
	//}}AFX_DATA_INIT
}


void DlgRandParamICG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRandParamICG)
	DDX_Control(pDX, IDC_EDIT1, m_Param_aCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_Param_a);
	DDX_Text(pDX, IDC_EDIT2, m_Param_b);
	DDX_Text(pDX, IDC_EDIT3, m_Param_N);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRandParamICG, CDialog)
	//{{AFX_MSG_MAP(DlgRandParamICG)
	ON_BN_CLICKED(IDC_STATIC_GPA, OnStaticGp_a)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgRandParamICG 


void DlgRandParamICG::OnStaticGp_a() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Param_aCtrl.SetFocus();
}
