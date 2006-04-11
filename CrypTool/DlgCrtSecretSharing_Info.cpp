// DlgCrtSecretSharing_Info.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCrtSecretSharing_Info.h"
#include ".\dlgcrtsecretsharing_info.h"

// Aus DH-Intro.cpp eingefügt
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// DlgCrtSecretSharing_Info-Dialogfeld

IMPLEMENT_DYNAMIC(DlgCrtSecretSharing_Info, CDialog)
DlgCrtSecretSharing_Info::DlgCrtSecretSharing_Info(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCrtSecretSharing_Info::IDD, pParent)
	, m_checkInfo(FALSE)
{
}

DlgCrtSecretSharing_Info::~DlgCrtSecretSharing_Info()
{
}

void DlgCrtSecretSharing_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_checkInfo);
}


BEGIN_MESSAGE_MAP(DlgCrtSecretSharing_Info, CDialog)
END_MESSAGE_MAP()




