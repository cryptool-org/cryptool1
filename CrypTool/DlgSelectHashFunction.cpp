// SelctAHashfunction.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSelectHashFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHashFunction 


CDlgSelectHashFunction::CDlgSelectHashFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectHashFunction::IDD, pParent)
{
	m_deactivateMD4 = false;
	m_selectedHashFunction = 0;
	//{{AFX_DATA_INIT(CDlgSelectHashFunction)
	m_selectedHashFunctionMD2 = 0;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	//}}AFX_DATA_INIT
}


void CDlgSelectHashFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectHashFunction)
	DDX_Control(pDX, IDC_RADIO2, m_selectedHashFunctionMD4Ctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_selectedHashFunctionMD2);
	DDX_Radio(pDX, IDC_RADIO2, m_selectedHashFunctionMD4);
	DDX_Radio(pDX, IDC_RADIO3, m_selectedHashFunctionMD5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectHashFunction, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectHashFunction)
	ON_BN_CLICKED(IDC_RADIO1, OnSelectedMD2)
	ON_BN_CLICKED(IDC_RADIO2, OnSelectedMD4)
	ON_BN_CLICKED(IDC_RADIO3, OnSelectedMD5)
	ON_BN_CLICKED(IDC_RADIO4, OnSelectSHA)
	ON_BN_CLICKED(IDC_RADIO5, OnSelectedSHA_1)
	ON_BN_CLICKED(IDC_RADIO6, OnSelectedRIPEMD_160)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgSelectHashFunction 

void CDlgSelectHashFunction::OnSelectedMD2() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	UpdateData();
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunction = 0;
	UpdateData(FALSE);	
}

void CDlgSelectHashFunction::OnSelectedMD4() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	UpdateData();
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunction = 1;
	UpdateData(FALSE);		
}

void CDlgSelectHashFunction::OnSelectedMD5() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	UpdateData();
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;	
	UpdateData(FALSE);		
	m_selectedHashFunction = 2 + m_selectedHashFunctionMD5;
}

void CDlgSelectHashFunction::OnSelectSHA() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	OnSelectedMD5();
}

void CDlgSelectHashFunction::OnSelectedSHA_1() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	OnSelectedMD5();	
}

void CDlgSelectHashFunction::OnSelectedRIPEMD_160() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	OnSelectedMD5();	
}

BOOL CDlgSelectHashFunction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen
	if ( m_deactivateMD4 )
	{
		m_selectedHashFunctionMD4Ctrl.EnableWindow(false);		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

