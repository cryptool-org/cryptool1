// DlgSelHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgSelHash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelHash 


CDlgSelHash::CDlgSelHash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelHash::IDD, pParent), m_nIDFirst(IDC_MD2), m_nIDLast(IDC_RIPEMD160), m_nIDHash(0)
{
	//{{AFX_DATA_INIT(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgSelHash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelHash, CDialog)
	//{{AFX_MSG_MAP(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSelHash 

BOOL CDlgSelHash::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//if(!m_nIDHash) m_nIDHash = IDC_MD2;
	CheckRadioButton(m_nIDFirst, m_nIDLast, m_nIDHash);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSelHash::OnOK() 
{
	m_nIDHash = GetCheckedRadioButton( m_nIDFirst, m_nIDLast );

	CDialog::OnOK();
}

BOOL CDlgSelHash::InitHashID(int nIDHash)
{
	if((nIDHash >= m_nIDFirst) && (nIDHash <= m_nIDLast))
	{
		m_nIDHash = nIDHash;
		return TRUE;
	}
	return FALSE;
}

int CDlgSelHash::GetHashID()
{
	return m_nIDHash;	
}

