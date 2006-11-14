// DlgHillOptions.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHillOptions.h"
#include ".\dlghilloptions.h"
#include "CrypToolTools.h"

// DlgHillOptions dialog

IMPLEMENT_DYNAMIC(DlgHillOptions, CDialog)
DlgHillOptions::DlgHillOptions(CWnd* pParent /*=NULL*/)
	: CDialog(DlgHillOptions::IDD, pParent)
{
}

DlgHillOptions::~DlgHillOptions()
{
}

void DlgHillOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BOOL DlgHillOptions::OnInitDialog()
{
	firstPosNull = 1;
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ) == ERROR_SUCCESS)
	{
		
		CT_READ_REGISTRY_DEFAULT(firstPosNull, "firstPosNull", firstPosNull);
		
		UpdateData(false);

		CT_CLOSE_REGISTRY();
	}

	if(firstPosNull == 1)
		CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO3);
	if(firstPosNull == 0)
		CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO4);

	return TRUE;
}

BEGIN_MESSAGE_MAP(DlgHillOptions, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO3, EnableFirstPosNull)
	ON_BN_CLICKED(IDC_RADIO4, DisableFirstPosNull)
END_MESSAGE_MAP()


// DlgHillOptions message handlers

void DlgHillOptions::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
void DlgHillOptions::OnOK()
{

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(firstPosNull), "firstPosNull");
		CT_CLOSE_REGISTRY();
	}
	CDialog::OnOK();
}

void DlgHillOptions::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
void DlgHillOptions::EnableFirstPosNull()
{
	firstPosNull = 1;
}
void DlgHillOptions::DisableFirstPosNull()
{
	firstPosNull = 0;
}
