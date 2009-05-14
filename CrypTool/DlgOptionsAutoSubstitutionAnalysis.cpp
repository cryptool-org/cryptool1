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

// DlgOptionsAutoSubstitutionAnalysis.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgOptionsAutoSubstitutionAnalysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsAutoSubstitutionAnalysis 



CDlgOptionsAutoSubstitutionAnalysis::CDlgOptionsAutoSubstitutionAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsAutoSubstitutionAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsAutoSubstitutionAnalysis)
	m_space_in_alphabet = FALSE;
	m_nogui = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsAutoSubstitutionAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsAutoSubstitutionAnalysis)
	DDX_Check(pDX, IDC_ALPHABET_SPACE_CHECK, m_space_in_alphabet);
	DDX_Check(pDX, IDC_NOGUI, m_nogui);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsAutoSubstitutionAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsAutoSubstitutionAnalysis)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsAutoSubstitutionAnalysis 
