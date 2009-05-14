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

// SelectCopyEncoding.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SelectCopyEncoding.h"

static int m_encode_type = 0;

// CSelectCopyEncoding dialog

IMPLEMENT_DYNAMIC(CSelectCopyEncoding, CDialog)
CSelectCopyEncoding::CSelectCopyEncoding(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectCopyEncoding::IDD, pParent)
{
}

CSelectCopyEncoding::~CSelectCopyEncoding()
{
}

void CSelectCopyEncoding::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_encode_type);
}


BEGIN_MESSAGE_MAP(CSelectCopyEncoding, CDialog)
END_MESSAGE_MAP()


// CSelectCopyEncoding message handlers

BOOL CSelectCopyEncoding::OnInitDialog(void)
{
	CDialog::OnInitDialog();
	return TRUE;
}

int CSelectCopyEncoding::selectCopyEncoding(void)
{
	CSelectCopyEncoding dlg;
	if ( IDOK != dlg.DoModal() )
		return -1;

	return m_encode_type;
}
