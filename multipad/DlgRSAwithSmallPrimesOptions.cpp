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
	m_alphabet = _T(" ABCDEFGHIJLMNOPQRSTUVWXYZ");
	m_inputOption = 0;
	m_numberBasis = 0;
	m_TextOptions = 0;
	//}}AFX_DATA_INIT
}


void CDlgRSAwithSmallPrimesOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRSAwithSmallPrimesOptions)
	DDX_Text(pDX, IDC_EDIT1, m_alphabet);
	DDX_Control(pDX, IDC_EDIT1, m_alphabetControl);
	DDX_Radio(pDX, IDC_RADIO1, m_inputOption);
	DDX_Radio(pDX, IDC_RADIO3, m_numberBasis);
	DDX_Radio(pDX, IDC_RADIO7, m_TextOptions);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRSAwithSmallPrimesOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgRSAwithSmallPrimesOptions)
	ON_BN_CLICKED(IDC_RADIO1, OnEncryptText)
	ON_BN_CLICKED(IDC_RADIO2, OnEncryptNumbers)
	ON_BN_CLICKED(IDC_RADIO7, OnTextOptionsASCII)
	ON_BN_CLICKED(IDC_RADIO8, OnTextOptionsAlphabet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRSAwithSmallPrimesOptions 

void CDlgRSAwithSmallPrimesOptions::OnEncryptText() 
{
	UpdateData(true);
	if ( 1 == m_TextOptions ) m_alphabetControl.EnableWindow( TRUE );
	UpdateData(false);
}

void CDlgRSAwithSmallPrimesOptions::OnEncryptNumbers() 
{
	UpdateData(true);
	m_alphabetControl.EnableWindow( FALSE );	
	UpdateData(false);
}

void CDlgRSAwithSmallPrimesOptions::OnTextOptionsASCII() 
{
	UpdateData(true);
	m_alphabetControl.EnableWindow( FALSE );	
	UpdateData(false);
}

void CDlgRSAwithSmallPrimesOptions::OnTextOptionsAlphabet() 
{
	UpdateData(true);
	if ( 0 == m_inputOption ) m_alphabetControl.EnableWindow( TRUE );
	UpdateData(false);
}

BOOL CDlgRSAwithSmallPrimesOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_alphabetControl.EnableWindow( FALSE );	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
