// DlgShowHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgShowHash.h"
#include "crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowHash 


CDlgShowHash::CDlgShowHash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowHash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowHash)
	m_HashStr = _T("");
	//}}AFX_DATA_INIT
}


void CDlgShowHash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowHash)
	DDX_Text(pDX, IDC_EDIT1, m_HashStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowHash, CDialog)
	//{{AFX_MSG_MAP(CDlgShowHash)
	ON_BN_CLICKED(IDOK, OnShowHashInDesktop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowHash 

void CDlgShowHash::OnShowHashInDesktop() 
{
	CDialog::OnOK();
}

BOOL CDlgShowHash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	SetWindowText(title);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgShowHash::SetHash(OctetString &hash, const char * method )
{
	sprintf(title, "%s-Hash", method);
	m_HashStr = "";
	for (unsigned int i=0; i<hash.noctets; i++)
	{
		unsigned char x = hash.octets[i];
		char c1, c2;
		if (( x % 16 ) < 10 ) c2 = '0' + (x % 16); else c2 = 'A' + (x % 16) -10;
		x /= 16;
		if ( x < 10 ) c1 = '0' + x; else c1 = 'A' + x -10; 
		m_HashStr += c1;
		m_HashStr += c2;
		if (i < hash.noctets+1) m_HashStr += ' ';
	}
}
