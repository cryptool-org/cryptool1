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

// propPage1.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "propPage1.h"
#include "ZahlenHaiOptionen.h"
#include ".\proppage1.h"


// propPage1-Dialogfeld

IMPLEMENT_DYNAMIC(propPage1, CPropertyPage)
propPage1::propPage1()
	: CPropertyPage(propPage1::IDD)
{
}

propPage1::~propPage1()
{
}

void propPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, tabctrl);
}


BEGIN_MESSAGE_MAP(propPage1, CPropertyPage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// propPage1-Meldungshandler

void propPage1::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	*pResult = 0;
}

BOOL propPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  hier zusätzliche Initialisierung hinzufügen.
	//tabctrl.InsertItem(CDialog *dlg,"Hallo", IDD_DIALOG1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
