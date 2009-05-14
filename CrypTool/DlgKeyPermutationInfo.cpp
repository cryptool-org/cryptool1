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

// DlgKeyPermutationInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyPermutationInfo.h"
#include ".\dlgkeypermutationinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutationInfo 


CDlgKeyPermutationInfo::CDlgKeyPermutationInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyPermutationInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyPermutationInfo)
	m_Inverse1 = _T("");
	m_Permutation1 = _T("");
	m_Permutation2 = _T("");
	m_Inverse2 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgKeyPermutationInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyPermutationInfo)
	DDX_Control(pDX, IDOK, m_button_control);
	DDX_Text(pDX, IDC_EDIT2, m_Inverse1);
	DDX_Text(pDX, IDC_EDIT1, m_Permutation1);
	DDX_Text(pDX, IDC_EDIT3, m_Permutation2);
	DDX_Text(pDX, IDC_EDIT4, m_Inverse2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyPermutationInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyPermutationInfo)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDBACK, OnBnClickedBack)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyPermutationInfo 

BOOL CDlgKeyPermutationInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// TODO: Zusätzliche Initialisierung hier einfügen

	SetWindowText(LPCTSTR(m_dialogue_title));
	m_button_control.SetWindowText(LPCTSTR(m_button_title));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgKeyPermutationInfo::OnBnClickedBack()
{
	EndDialog(IDBACK);
}
