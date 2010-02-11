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


// Help.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "aestool.h"
#include "Help.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHelp 


CHelp::CHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelp)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelp)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelp, CDialog)
	//{{AFX_MSG_MAP(CHelp)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CHelp::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set the default dialog title (i.e. "Help for AES-Tool 2.5.1")
	CString title;
	title.Format(IDS_STRING_AES_TOOL_HELP_PREFIX, CAestoolApp::getAESToolVersionString());
	SetWindowText(title);

	return true;
}

#pragma warning( push )
#pragma warning( disable : 4100)
BOOL CHelp::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// do nothing - no help on help	
	return true;
}
#pragma warning( pop ) 
