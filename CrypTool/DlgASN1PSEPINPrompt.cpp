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

// DlgASN1PSEPINPrompt.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgASN1PSEPINPrompt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgASN1PSEPINPrompt 


CDlgASN1PSEPINPrompt::CDlgASN1PSEPINPrompt(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgASN1PSEPINPrompt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgASN1PSEPINPrompt)
	m_PIN = _T("");
	//}}AFX_DATA_INIT
}


void CDlgASN1PSEPINPrompt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgASN1PSEPINPrompt)
	DDX_Text(pDX, IDC_EDIT1, m_PIN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgASN1PSEPINPrompt, CDialog)
	//{{AFX_MSG_MAP(CDlgASN1PSEPINPrompt)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgASN1PSEPINPrompt 
