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




