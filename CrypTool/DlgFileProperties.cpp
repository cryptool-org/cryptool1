// DlgFileProperties.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFileProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFileProperties 


CDlgFileProperties::CDlgFileProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFileProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFileProperties)
	m_filename = _T("");
	m_fileType = _T("");
	m_fileSize = _T("");
	//}}AFX_DATA_INIT
	m_title = _T("");
}


void CDlgFileProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFileProperties)
	DDX_Control(pDX, IDC_BUTTON1, m_ShowKey);
	DDX_Control(pDX, IDC_BUTTON2, m_ShowFatherWindow);
	DDX_Text(pDX, IDC_EDIT1, m_filename);
	DDX_Text(pDX, IDC_EDIT132, m_fileType);
	DDX_Text(pDX, IDC_EDIT2, m_fileSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFileProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgFileProperties)
	ON_BN_CLICKED(IDC_BUTTON2, OnShowFather)
	ON_BN_CLICKED(IDC_BUTTON1, OnShowKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFileProperties 

void CDlgFileProperties::OnShowFather() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

void CDlgFileProperties::OnShowKey() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

BOOL CDlgFileProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgFileProperties::copyFileInfos(CString contentName, CString title)
{
	char str[20];
	m_filename = contentName;
	CFile file;
	file.Open(m_filename, CFile::modeRead );
	_i64toa(file.GetLength(), str, 10);
	m_fileSize = str;
	m_title = title;
}
