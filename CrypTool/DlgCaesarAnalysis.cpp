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
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DialoKeyCaesar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCaesarAnalysis.h"
// #include "DlgPrimesGeneratorDemo.h" // ## Weg 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCaesarAnalysis 


CDlgCaesarAnalysis::CDlgCaesarAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCaesarAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCaesarAnalysis)
	m_string = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCaesarAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCaesarAnalysis)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_string);
	DDV_MaxChars(pDX, m_string, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCaesarAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgCaesarAnalysis)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCaesarAnalysis 

void CDlgCaesarAnalysis::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.getIgnoreCase())
	{
		m_string.MakeUpper();
	}

	for(k=i=0;i<m_string.GetLength();i++) {
		c = m_string[i];
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

	m_string = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
}

BOOL CDlgCaesarAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();

	// display the remark regarding the key offset
	GetDlgItem(IDC_EDIT_KEY_OFFSET_REMARK)->SetWindowText(createKeyOffsetRemark());

	return FALSE;
}

CString CDlgCaesarAnalysis::createKeyOffsetRemark()
{
	// memory allocation
	char result[STR_LAENGE_STRING_TABLE+1];
	memset(result, 0, STR_LAENGE_STRING_TABLE+1);
	char derivedKey[2];
	memset(derivedKey, 0, 2);
	char alternativeKey[2];
	memset(alternativeKey, 0, 2);
	// build the remark string based on the resource string, the derived key and the alternative key
	LoadString(AfxGetInstanceHandle(), IDS_CAESAR_ANALYSIS_REMARK, pc_str, STR_LAENGE_STRING_TABLE);
	memcpy(derivedKey, m_string.GetBuffer(), 1);

	// get the alternative key
	int pos = theApp.TextOptions.getAlphabet().Find(derivedKey);
	// take the "next" character in the alphabet after the derived key
	int newPos = (pos + 1) % theApp.TextOptions.getAlphabet().GetLength();
	memcpy(alternativeKey, (const char*)theApp.TextOptions.getAlphabet() + newPos, 1);

	// mix it all together
	sprintf(result, pc_str, derivedKey, alternativeKey);
	// return the resulting string
	CString theResult = result;
	return theResult;
}