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

// DlgDiffieHellmanIntro.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanIntro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanIntro 


CDlgDiffieHellmanIntro::CDlgDiffieHellmanIntro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanIntro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanIntro)
	m_Check_NoShow = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanIntro)
	DDX_Check(pDX, IDC_CHECK_NOSHOW, m_Check_NoShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanIntro, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanIntro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanIntro 

