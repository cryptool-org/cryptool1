// DlgRSAwithSmallPrimesOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRSAwithSmallPrimesOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSAwithSmallPrimesOptions 


CDlgRSAwithSmallPrimesOptions::CDlgRSAwithSmallPrimesOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRSAwithSmallPrimesOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRSAwithSmallPrimesOptions)
	m_alphabetOptionExample = FALSE;
	m_alphabet = _T("");
	m_inputOption = -1;
	m_numberBasis = -1;
	//}}AFX_DATA_INIT
}


void CDlgRSAwithSmallPrimesOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRSAwithSmallPrimesOptions)
	DDX_Control(pDX, IDC_EDIT1, m_alphabetControl);
	DDX_Check(pDX, IDC_CHECK1, m_alphabetOptionExample);
	DDX_Text(pDX, IDC_EDIT1, m_alphabet);
	DDX_Radio(pDX, IDC_RADIO1, m_inputOption);
	DDX_Radio(pDX, IDC_RADIO3, m_numberBasis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRSAwithSmallPrimesOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgRSAwithSmallPrimesOptions)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRSAwithSmallPrimesOptions 
