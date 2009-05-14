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

// DlgSelHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSelHash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelHash 


CDlgSelHash::CDlgSelHash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelHash::IDD, pParent), m_nIDHash(0)
{
	//{{AFX_DATA_INIT(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgSelHash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelHash, CDialog)
	//{{AFX_MSG_MAP(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSelHash 

BOOL CDlgSelHash::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(m_sHashAlg=="MD2")	m_nIDHash = IDC_MD2;
	else if(m_sHashAlg=="MD5") m_nIDHash = IDC_MD5;
	else if(m_sHashAlg=="SHA") m_nIDHash = IDC_SHA;
	else if(m_sHashAlg=="SHA-1") m_nIDHash = IDC_SHA_1;
	else if(m_sHashAlg=="RIPEMD-160") m_nIDHash = IDC_RIPEMD160;
	else m_nIDHash = 0;
	CheckRadioButton(IDC_MD2, IDC_RIPEMD160, m_nIDHash);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSelHash::OnOK() 
{
	m_nIDHash = GetCheckedRadioButton( IDC_MD2, IDC_RIPEMD160 );
	switch(m_nIDHash)
	{
		case IDC_MD2: m_sHashAlg = "MD2"; break;
		case IDC_MD5: m_sHashAlg = "MD5"; break;
		case IDC_SHA: m_sHashAlg = "SHA"; break;
		case IDC_SHA_1: m_sHashAlg = "SHA-1"; break;
		case IDC_RIPEMD160: m_sHashAlg = "RIPEMD-160"; break;
		default: m_sHashAlg.Empty();
	}

	CDialog::OnOK();
}
