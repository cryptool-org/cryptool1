// Dlg_homophone.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "Dlg_homophone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_homophone 


Dlg_homophone::Dlg_homophone(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_homophone::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_homophone)
	m_key = _T("");
	m_crypt = 0;
	//}}AFX_DATA_INIT
}


void Dlg_homophone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_homophone)
	DDX_Text(pDX, IDC_EDIT1, m_key);
	DDX_Radio(pDX, IDC_RADIO1, m_crypt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_homophone, CDialog)
	//{{AFX_MSG_MAP(Dlg_homophone)
	ON_BN_CLICKED(IDC_ERZEUGEN, OnErzeugen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten Dlg_homophone 

void Dlg_homophone::OnErzeugen() 
{
	HB.Generate_key();		
}

bool Dlg_homophone::Is_key()
{
	return(!(m_key.IsEmpty()));
}

int Dlg_homophone::Display()
{
	return(DoModal());
}

int Dlg_homophone::Get_crypt()
{
	return(m_crypt);
}

CString Dlg_homophone::Get_Key()
{
	CString c;
	for(int i=0;i<=255;i++)
	{
		itoa(HB.Get_key(i),c.GetBuffer(800),10);
	}
	HB.Get_key(
}
