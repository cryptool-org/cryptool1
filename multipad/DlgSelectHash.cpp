// DlgSelectHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgSelectHash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHash 

CDlgSelectHash::CDlgSelectHash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectHash::IDD, pParent), m_nIDFirst(IDC_MD2), m_nIDLast(IDC_RIPEMD160), m_nIDHash(0)
{
	//{{AFX_DATA_INIT(CDlgSelectHash)
	//}}AFX_DATA_INIT

}


void CDlgSelectHash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectHash)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectHash, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectHash)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSelectHash 

BOOL CDlgSelectHash::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(!m_nIDHash) m_nIDHash = IDC_MD2;
	CheckRadioButton(m_nIDFirst, m_nIDLast, m_nIDHash);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSelectHash::OnOK() 
{
	m_nIDHash = GetCheckedRadioButton( m_nIDFirst, m_nIDLast );

	CDialog::OnOK();
}

BOOL CDlgSelectHash::InitHashID(int nIDHash)
{
	if((nIDHash >= m_nIDFirst) && (nIDHash <= m_nIDLast))
	{
		m_nIDHash = nIDHash;
		return TRUE;
	}
	return FALSE;
}

int CDlgSelectHash::GetHashID()
{
	return m_nIDHash;	
}
