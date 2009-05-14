/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

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

