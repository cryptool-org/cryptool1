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

// DlgAutoSubstitutionAnalysisAlgorithmChoice.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgAutoSubstitutionAnalysisAlgorithmChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAutoSubstitutionAnalysisAlgorithmChoice 


CDlgAutoSubstitutionAnalysisAlgorithmChoice::CDlgAutoSubstitutionAnalysisAlgorithmChoice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoSubstitutionAnalysisAlgorithmChoice::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	m_algChoice = 1;
	//}}AFX_DATA_INIT
}


void CDlgAutoSubstitutionAnalysisAlgorithmChoice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoSubstitutionAnalysisAlgorithmChoice, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoSubstitutionAnalysisAlgorithmChoice)
	ON_BN_CLICKED(IDC_ALG_DIGRAM, OnAlgDigram)
	ON_BN_CLICKED(IDC_ALG_WORD, OnAlgWord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgAutoSubstitutionAnalysisAlgorithmChoice 

void CDlgAutoSubstitutionAnalysisAlgorithmChoice::OnAlgDigram() 
{
	m_algChoice = 1;
	CheckRadioButton (IDC_ALG_DIGRAM, IDC_ALG_WORD, IDC_ALG_DIGRAM);
}

void CDlgAutoSubstitutionAnalysisAlgorithmChoice::OnAlgWord() 
{
	m_algChoice = 2;
	CheckRadioButton (IDC_ALG_DIGRAM, IDC_ALG_WORD, IDC_ALG_WORD);
}

int CDlgAutoSubstitutionAnalysisAlgorithmChoice::DoModal() 
{
	return CDialog::DoModal();
}

BOOL CDlgAutoSubstitutionAnalysisAlgorithmChoice::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckRadioButton (IDC_ALG_DIGRAM, IDC_ALG_WORD, IDC_ALG_DIGRAM);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
