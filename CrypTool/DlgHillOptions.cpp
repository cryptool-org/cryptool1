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
	, m_FirstCharFromAlph(_T(""))
	, m_ownCharForPadding(_T(""))
{
}

DlgHillOptions::~DlgHillOptions()
{
}

void DlgHillOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_FirstCharFromAlph);
	DDX_Text(pDX, IDC_EDIT2, m_ownCharForPadding);
}
BOOL DlgHillOptions::OnInitDialog()
{
	m_FirstCharFromAlph = theApp.TextOptions.getAlphabet()[0];

	firstPosNull = 1;
	useFirstCharFromAlph = 1;
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		char cFirstCharFromAlph[1024];
		CString strAlph = theApp.TextOptions.getAlphabet()[0];
		strncpy(cFirstCharFromAlph,strAlph.GetBuffer(0),strAlph.GetLength());
		cFirstCharFromAlph[strAlph.GetLength()] = '\0';
		unsigned long u_length = 1024;
		
		CT_READ_REGISTRY_DEFAULT(firstPosNull, "OrdChrOffset", firstPosNull);
		CT_READ_REGISTRY_DEFAULT(useFirstCharFromAlph, "PaddingDefaultChr", useFirstCharFromAlph);
		CT_READ_REGISTRY(cFirstCharFromAlph,"PaddingOwnChr",u_length);

		m_ownCharForPadding = cFirstCharFromAlph;

		UpdateData(false);

		CT_CLOSE_REGISTRY();
	}

	if(firstPosNull == 1)
		CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO3);
	if(firstPosNull == 0)
		CheckRadioButton(IDC_RADIO3, IDC_RADIO4, IDC_RADIO4);

	if(useFirstCharFromAlph == 1)
	{
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	}
	if(useFirstCharFromAlph == 0)
	{
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	}

	return TRUE;
}

BEGIN_MESSAGE_MAP(DlgHillOptions, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO3, EnableFirstPosNull)
	ON_BN_CLICKED(IDC_RADIO4, DisableFirstPosNull)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
END_MESSAGE_MAP()


// DlgHillOptions message handlers

void DlgHillOptions::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
void DlgHillOptions::OnOK()
{
	UpdateData(true);

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(firstPosNull), "OrdChrOffset");
		CT_WRITE_REGISTRY(unsigned long(useFirstCharFromAlph), "PaddingDefaultChr");
		CT_WRITE_REGISTRY(m_ownCharForPadding,"PaddingOwnChr");
		CT_CLOSE_REGISTRY();
	}

	UpdateData(false);
	CDialog::OnOK();
}

void DlgHillOptions::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
void DlgHillOptions::EnableFirstPosNull()
{
	UpdateData(true);
	firstPosNull = 1;
	UpdateData(false);
}
void DlgHillOptions::DisableFirstPosNull()
{
	UpdateData(true);
	firstPosNull = 0;
	UpdateData(false);
}

void DlgHillOptions::OnBnClickedRadio1()
{
	UpdateData(true);
    useFirstCharFromAlph = 1;
	UpdateData(false);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
}

void DlgHillOptions::OnBnClickedRadio2()
{
	UpdateData(true);
	useFirstCharFromAlph = 0;
	UpdateData(false);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->SetFocus();
}

void DlgHillOptions::OnEnChangeEdit2()
{
	UpdateData(true);
	if(isInAlph(m_ownCharForPadding))
	{
		if(m_ownCharForPadding.GetLength() == 1)
		{
			MyToUpper(m_ownCharForPadding);
		}
		else
		{
			MyToUpper(m_ownCharForPadding);
			m_ownCharForPadding = m_ownCharForPadding[0];
		}
	}
	else
	{
		m_ownCharForPadding.Empty();
	}
	UpdateData(false);
}
bool DlgHillOptions::isInAlph(CString strChar)
{
	MyToUpper(strChar);
	for(int i=0; i<theApp.TextOptions.getAlphabet().GetLength();i++)
	{
		if(strChar == theApp.TextOptions.getAlphabet()[i])
			return true;
	}
	return false;
}
