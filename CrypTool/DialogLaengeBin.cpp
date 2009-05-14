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

// DialogLaengeBin.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DialogLaengeBin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBinKeyLength 


CDlgBinKeyLength::CDlgBinKeyLength(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinKeyLength::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinKeyLength)
	m_Char = _T("00");
	m_laenge = 0;
	//}}AFX_DATA_INIT
}


void CDlgBinKeyLength::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinKeyLength)
	DDX_Control(pDX, IDC_EDIT2, m_Ctl);
	DDX_Text(pDX, IDC_EDIT2, m_Char);
	DDV_MaxChars(pDX, m_Char, 2);
	DDX_Text(pDX, IDC_EDIT1, m_laenge);
	DDV_MinMaxUInt(pDX, m_laenge, 1, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBinKeyLength, CDialog)
	//{{AFX_MSG_MAP(CDlgBinKeyLength)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgBinKeyLength 

void CDlgBinKeyLength::OnChangeEdit2() 
{
	int i;
	char c;

	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	for(i=0;i<m_Char.GetLength();i++) {
		c=m_Char[i];
		if(!((('0'<=c) && (c <='9'))||(('A'<=c)&&(c<='F')))) m_Ctl.Undo();
	}
}

void CDlgBinKeyLength::OnOK() 
{
	int i;
	char c;

	m_c = 0;

	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	for(i=0;i<m_Char.GetLength();i++) {
		c = m_Char[i];
		if(('0'<=c) && (c<='9')) m_c = m_c*16 + (c-'0');
		if(('A'<=c) && (c<='F')) m_c = m_c*16 + (c-'A') + 10;
	}
	
	CDialog::OnOK();
}

BOOL CDlgBinKeyLength::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_title.GetLength())
		SetWindowText(m_title);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
