// DlgOptionsStartoptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"

#include "DlgOptionsStartoptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsStartoptions 


CDlgOptionsStartoptions::CDlgOptionsStartoptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsStartoptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsStartoptions)
	m_how_to_start = FALSE;
	m_sample_text_file = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsStartoptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsStartoptions)
	DDX_Check(pDX, IDC_CHECK1, m_how_to_start);
	DDX_Check(pDX, IDC_CHECK2, m_sample_text_file);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsStartoptions, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsStartoptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsStartoptions 

BOOL CDlgOptionsStartoptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(true);
	m_how_to_start = !int(theApp.GetProfileInt("Settings", "NoTipps", FALSE));
	m_sample_text_file = int(theApp.GetProfileInt("Settings", "SampleTextFile", FALSE));	
	UpdateData(false);
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgOptionsStartoptions::OnOK() 
{
	UpdateData(true);
	theApp.WriteProfileInt("Settings","NoTipps", int(!m_how_to_start));
	theApp.WriteProfileInt("Settings","SampleTextFile", int(m_sample_text_file));
	UpdateData(false);
	
	CDialog::OnOK();
}
