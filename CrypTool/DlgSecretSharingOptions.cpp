// DlgSecretSharingOptions.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSecretSharingOptions.h"
#include "DlgSecretSharingSetup.h"


// CDlgSecretSharingOptions-Dialogfeld

CDlgSecretSharingOptions::CDlgSecretSharingOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecretSharingOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSecretSharingOptions)
	m_limit = _T("30");
	m_prime = _T("10000");
	//}}AFX_DATA_INIT
}

CDlgSecretSharingOptions::~CDlgSecretSharingOptions()
{
}

void CDlgSecretSharingOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LIMIT, m_limit);
	DDX_Text(pDX, IDC_EDIT_PRIME, m_prime);
}


BEGIN_MESSAGE_MAP(CDlgSecretSharingOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgSecretSharingOptions)
	ON_BN_CLICKED(IDOK, OnButtonOk)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()


// CDlgSecretSharingOptions-Meldungshandler

void CDlgSecretSharingOptions::OnButtonOk()
{
	OnOK();
}
