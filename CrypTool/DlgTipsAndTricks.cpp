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

// DlgTipsAndTricks.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgTipsAndTricks.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgTipsAndTricks 


CDlgTipsAndTricks::CDlgTipsAndTricks(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTipsAndTricks::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTipsAndTricks)
	m_DoNotShowThisAgain = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgTipsAndTricks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTipsAndTricks)
	DDX_Check(pDX, IDC_CHECK2, m_DoNotShowThisAgain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTipsAndTricks, CDialog)
	//{{AFX_MSG_MAP(CDlgTipsAndTricks)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgTipsAndTricks 
