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

// DLG_param.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowKeyParameter.h"
#include "DlgHybridEncryptionDemo.h"
#include "s_ecconv.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyParameter 


CDlgShowKeyParameter::CDlgShowKeyParameter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKeyParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowKeyParameter)
	m_radio = 1;
	m_titel = _T("");
	//}}AFX_DATA_INIT
	disableOkButton = false;
}


void CDlgShowKeyParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowKeyParameter)
	DDX_Control(pDX, IDOK, m_ctrlOK);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Text(pDX, IDC_TITEL, m_titel);
	DDV_MaxChars(pDX, m_titel, 100);
	DDX_Text(pDX, IDC_EDIT_MODUL, m_modul);
	DDX_Text(pDX, IDC_EDIT_EXPONENT, m_exponent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowKeyParameter, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKeyParameter)
	ON_BN_CLICKED(IDC_RADIO1, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO2, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO3, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowKeyParameter 

void CDlgShowKeyParameter::OnUpdate() 
{
	UpdateData(TRUE);

	char *p_modul;
	char *p_exponent;

	switch (m_radio)
	{
	case 0:
		ln_to_string(m_data[0].data,&p_modul,8);
		ln_to_string(m_data[1].data,&p_exponent,8);
		break;
	case 1:
		ln_to_string(m_data[0].data,&p_modul,10);
		ln_to_string(m_data[1].data,&p_exponent,10);
		break;
	case 2:
		ln_to_string(m_data[0].data,&p_modul,16);
		ln_to_string(m_data[1].data,&p_exponent,16);
		break;
	}
	
	// assign calculated values to modul and exponent
	m_modul = p_modul;
	m_exponent = p_exponent;
	// free allocated memory
	free(p_modul);
	free(p_exponent);

	UpdateData(FALSE);
}

void CDlgShowKeyParameter::settitel(char *a)
{
	m_titel=a;
}

BOOL CDlgShowKeyParameter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//disableOKButton wird in CDlgHybridEncryptionDemo auf true gesetzt.
	//dieser Abschnitt modifiziert den Dialog für die Anzeige bei der
	//Hybridverschlüsselung
    if(disableOkButton)
	{
		CDlgHybridEncryptionDemo dlg;
		m_ctrlOK.ShowWindow(false);
		SetWindowText(m_Title);
	}

	disableOkButton = false;
	
	OnUpdate();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
} 