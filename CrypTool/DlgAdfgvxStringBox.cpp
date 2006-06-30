// DlgAdfgvxStringBox.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAdfgvxStringBox.h"
#include ".\dlgadfgvxstringbox.h"

// DlgAdfgvxStringBox-Dialogfeld

IMPLEMENT_DYNAMIC(DlgAdfgvxStringBox, CDialog)
DlgAdfgvxStringBox::DlgAdfgvxStringBox(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAdfgvxStringBox::IDD, pParent)
	, input(_T(""))

{
}

DlgAdfgvxStringBox::~DlgAdfgvxStringBox()
{
}

void DlgAdfgvxStringBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input);
	DDV_MaxChars(pDX, input, 36);
}


BEGIN_MESSAGE_MAP(DlgAdfgvxStringBox, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

BOOL DlgAdfgvxStringBox::OnInitDialog()
{
	GetDlgItem(IDC_EDIT1)->SetFocus();
	return TRUE;
}

// DlgAdfgvxStringBox-Meldungshandler

void DlgAdfgvxStringBox::OnBnClickedOk()
{
	UpdateData(true);
	DlgAdfgvxStringBox::OnCancel();
}

void DlgAdfgvxStringBox::OnOK()
{
	DlgAdfgvxStringBox::OnBnClickedOk();
}


CString DlgAdfgvxStringBox::GetInput()
{
	return input;
}

