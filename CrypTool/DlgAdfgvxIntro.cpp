// DlgAdfgvxIntro.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAdfgvxIntro.h"
#include ".\dlgadfgvxintro.h"
#include "CrypToolTools.h"


// DlgAdfgvxIntro-Dialogfeld

IMPLEMENT_DYNAMIC(DlgAdfgvxIntro, CDialog)
DlgAdfgvxIntro::DlgAdfgvxIntro(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAdfgvxIntro::IDD, pParent)
	, noIntro(FALSE)
{
}

DlgAdfgvxIntro::~DlgAdfgvxIntro()
{
}

void DlgAdfgvxIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, noIntro);
}


BEGIN_MESSAGE_MAP(DlgAdfgvxIntro, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
END_MESSAGE_MAP()


// DlgAdfgvxIntro-Meldungshandler

void DlgAdfgvxIntro::OnBnClickedCheck1()
{
	UpdateData(true);

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "ADFGVX" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(noIntro), "ShowIntro");
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}
	UpdateData(false);
}
