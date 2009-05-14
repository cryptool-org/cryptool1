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

// SelectPasteDecoding.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "SelectPasteDecoding.h"

static int m_decode_type = 0;

// CSelectPasteDecoding dialog

IMPLEMENT_DYNCREATE(CSelectPasteDecoding, CDialog)

CSelectPasteDecoding::CSelectPasteDecoding(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectPasteDecoding::IDD, pParent)
{
}

CSelectPasteDecoding::~CSelectPasteDecoding()
{
}

void CSelectPasteDecoding::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_decode_type);
}

BOOL CSelectPasteDecoding::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CSelectPasteDecoding, CDialog)
END_MESSAGE_MAP()


int CSelectPasteDecoding::selectPasteDecoding(void)
{
	CSelectPasteDecoding dlg;
	if ( IDOK != dlg.DoModal() )
		return -1;

	return m_decode_type;
}