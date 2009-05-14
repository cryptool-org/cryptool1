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
