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

// DlgShowHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowHash.h"
#include "Cryptography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowHash 


CDlgShowHash::CDlgShowHash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowHash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowHash)
	m_HashStr = _T("");
	//}}AFX_DATA_INIT
}


void CDlgShowHash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowHash)
	DDX_Text(pDX, IDC_EDIT1, m_HashStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowHash, CDialog)
	//{{AFX_MSG_MAP(CDlgShowHash)
	ON_BN_CLICKED(IDOK, OnShowHashInDesktop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowHash 

void CDlgShowHash::OnShowHashInDesktop() 
{
	CDialog::OnOK();
}

BOOL CDlgShowHash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	SetWindowText(title);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgShowHash::SetHash( OctetString &hash, const char *Title, const char * method )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName2(title, sizeof(title), pc_str, Title, method );
	m_HashStr = "";
	for (unsigned int i=0; i<hash.noctets; i++)
	{
		unsigned char x = hash.octets[i];
		char c1, c2;
		if (( x % 16 ) < 10 ) c2 = '0' + (x % 16); else c2 = 'A' + (x % 16) -10;
		x /= 16;
		if ( x < 10 ) c1 = '0' + x; else c1 = 'A' + x -10; 
		m_HashStr += c1;
		m_HashStr += c2;
		if (i < hash.noctets+1) m_HashStr += ' ';
	}
}
