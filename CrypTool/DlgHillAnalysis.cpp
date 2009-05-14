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
// TextEingabeHillAngriff.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHillAnalysis.h"
#include "HillEncryption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHillAnaylsis 


CDlgHillAnaylsis::CDlgHillAnaylsis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHillAnaylsis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHillAnaylsis)
	m_EingabeFeld = _T("");
	m_Klartext = 0;
	//}}AFX_DATA_INIT
}


void CDlgHillAnaylsis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHillAnaylsis)
	DDX_Control(pDX, IDC_DIM_VON, m_DimensionVon);
	DDX_Control(pDX, IDC_DIM_BIS, m_DimensionBis);
	DDX_Text(pDX, IDC_EDIT1, m_EingabeFeld);
	DDX_Radio(pDX, IDC_RADIO1, m_Klartext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHillAnaylsis, CDialog)
	//{{AFX_MSG_MAP(CDlgHillAnaylsis)
	ON_CBN_SELCHANGE(IDC_DIM_VON, OnSelchangeDimVon)
	ON_CBN_SELCHANGE(IDC_DIM_BIS, OnSelchangeDimBis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgHillAnaylsis 

BOOL CDlgHillAnaylsis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	// Combo-Boxen fuer Bereich der Schluesselsuche initialisieren
	for (int i=1; i<=HILL_MAX_DIM_GROSS; i++)
	{
		CString cs;
		cs.Format("%d", i);
		m_DimensionVon.AddString(cs);
		m_DimensionBis.AddString(cs);
	}

	// Standartmaessig alle Dimensionen beruecksichtigen
	m_DimensionVon.SetCurSel(0);
	m_DimensionBis.SetCurSel(HILL_MAX_DIM_GROSS-1);
	von = 1;
	bis = HILL_MAX_DIM_GROSS;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgHillAnaylsis::OnSelchangeDimVon() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	von = m_DimensionVon.GetCurSel() + 1;
	if (von > bis)
	{
		bis = von;
		m_DimensionBis.SetCurSel(bis-1);
	}
}

void CDlgHillAnaylsis::OnSelchangeDimBis() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	bis = m_DimensionBis.GetCurSel() + 1;
	if (bis < von)
	{
		von = bis;
		m_DimensionVon.SetCurSel(von-1);
	}
} 
