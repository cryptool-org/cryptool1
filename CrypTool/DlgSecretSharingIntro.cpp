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

// DlgSecretSharingIntro.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgSecretSharingIntro.h"
#include ".\dlgsecretsharingintro.h"
#include "CrypToolTools.h"


// CDlgSecretSharingIntro-Dialogfeld

CDlgSecretSharingIntro::CDlgSecretSharingIntro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecretSharingIntro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSecretSharingIntro)
	m_hide_intro = FALSE;
	//}}AFX_DATA_INIT
}

CDlgSecretSharingIntro::~CDlgSecretSharingIntro()
{
}

void CDlgSecretSharingIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSecretSharingIntro)
	DDX_Check(pDX, IDC_CHECK_HIDEINTRO, m_hide_intro);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgSecretSharingIntro, CDialog)
	//{{AFX_MSG_MAP(CDlgSecretSharingIntro)
	ON_BN_CLICKED(IDOK, OnOk)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()


// CDlgSecretSharingIntro-Meldungshandler

void CDlgSecretSharingIntro::OnOk()
{

	UpdateData(true);

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "SecretSharing" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(!m_hide_intro), "ShowIntroShamir");
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}
	UpdateData(false);

	CDialog::OnOK();
}
