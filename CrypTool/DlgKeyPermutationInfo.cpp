// DlgKeyPermutationInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyPermutationInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutationInfo 


CDlgKeyPermutationInfo::CDlgKeyPermutationInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyPermutationInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyPermutationInfo)
	m_Inverse1 = _T("");
	m_Permutation1 = _T("");
	m_Permutation2 = _T("");
	m_Inverse2 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgKeyPermutationInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyPermutationInfo)
	DDX_Control(pDX, IDOK, m_button_control);
	DDX_Text(pDX, IDC_EDIT2, m_Inverse1);
	DDX_Text(pDX, IDC_EDIT1, m_Permutation1);
	DDX_Text(pDX, IDC_EDIT3, m_Permutation2);
	DDX_Text(pDX, IDC_EDIT4, m_Inverse2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyPermutationInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyPermutationInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyPermutationInfo 

BOOL CDlgKeyPermutationInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// TODO: Zusätzliche Initialisierung hier einfügen

	SetWindowText(LPCTSTR(m_dialogue_title));
	m_button_control.SetWindowText(LPCTSTR(m_button_title));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
