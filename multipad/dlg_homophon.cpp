// dlg_homophon.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "dlg_homophon.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld dlg_homophon 


dlg_homophon::dlg_homophon(FILE *f,FILE *g,CWnd* pParent /*=NULL*/)
	: CDialog(dlg_homophon::IDD, pParent)
{
	homophone= new class Homophone(f,g);

	//{{AFX_DATA_INIT(dlg_homophon)
	m_input = _T("");
	m_passphrase = _T("");
	m_verschl = 0;
	//}}AFX_DATA_INIT
	homophone->SetInput("");
	m_passphrase=homophone->GetPassphrase();

}


void dlg_homophon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_homophon)
	DDX_Control(pDX, IDC_PASSPHRASE, m_passphrasec);
	DDX_Control(pDX, IDC_INPUT, m_inputc);
	DDX_Text(pDX, IDC_INPUT, m_input);
	DDV_MaxChars(pDX, m_input, 100);
	DDX_Text(pDX, IDC_PASSPHRASE, m_passphrase);
	DDX_Radio(pDX, IDC_VERSCHL, m_verschl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_homophon, CDialog)
	//{{AFX_MSG_MAP(dlg_homophon)
	ON_EN_UPDATE(IDC_INPUT, OnChangeInput)
	ON_BN_CLICKED(IDC_VERSCHL, OnVerschl)
	ON_BN_CLICKED(IDC_ENTSCHL, OnVerschl)
	ON_EN_UPDATE(IDC_PASSPHRASE, OnUpdatePassphrase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten dlg_homophon 

void dlg_homophon::OnChangeInput() 
{
	char temp[256];
	int i,j;

	UpdateData(TRUE);
	j=0;
	for(i=0;i<m_input.GetLength();i++)
	{
		if(AppConv.IsInAlphabet(m_input[i]))
		{
			if(!theApp.TextOptions.m_Case)
				temp[j++]=toupper(m_input[i]);
			else
				temp[j++]=m_input[i];
		}
	}
	temp[j]=0;
	m_inputc.GetSel(i,j);
	m_input=temp;
	UpdateData(FALSE);
	UpdateData(TRUE);
	m_inputc.SetSel(i,j);
	homophone->SetInput(temp);
	m_passphrase=homophone->GetPassphrase();
	UpdateData(FALSE);
}

void dlg_homophon::OnVerschl() 
{
	UpdateData(TRUE);
	if(m_verschl==0)
	{
		m_inputc.SetReadOnly(FALSE);
		m_passphrasec.SetReadOnly(FALSE);
	}
	else
	{
		m_inputc.SetReadOnly(TRUE);
		m_passphrasec.SetReadOnly(FALSE);
		m_passphrase.Empty();
	}
	UpdateData(FALSE);
}

void dlg_homophon::OnUpdatePassphrase() 
{
	UpdateData(TRUE);
	homophone->SetPassphrase(m_passphrase.GetBuffer(0));
	UpdateData(FALSE);
}
}
}
