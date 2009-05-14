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

//////////////////////////////////////////////////////////////////
// DialogVienereKey.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyVigenere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyVigenereAnalyisis 


CDlgKeyVigenereAnalyisis::CDlgKeyVigenereAnalyisis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyVigenereAnalyisis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyVigenereAnalyisis)
	m_Str = _T("");
	//}}AFX_DATA_INIT
}


void CDlgKeyVigenereAnalyisis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyVigenereAnalyisis)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_Str);
	DDV_MaxChars(pDX, m_Str, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyVigenereAnalyisis, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyVigenereAnalyisis)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyVigenereAnalyisis  
void CDlgKeyVigenereAnalyisis::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.getIgnoreCase()) m_Str.MakeUpper();

	for(k=i=0;i<m_Str.GetLength();i++) {
		c = m_Str[i];
		if(AppConv.IsInAlphabet(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		}
	}

	m_Str = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
}
