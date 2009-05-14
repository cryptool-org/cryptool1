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

// DlgSideChannelAttackVisualizationHEPreparationsRequest3.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSideChannelAttackVisualizationHEPreparationsRequest3.h"

// CDlgSideChannelAttackVisualizationHEPreparationsRequest3 dialog

IMPLEMENT_DYNCREATE(CDlgSideChannelAttackVisualizationHEPreparationsRequest3, CDialog)

CDlgSideChannelAttackVisualizationHEPreparationsRequest3::CDlgSideChannelAttackVisualizationHEPreparationsRequest3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSideChannelAttackVisualizationHEPreparationsRequest3::IDD, pParent)
	, radioChoice1(false)
	, radioChoice2(false)
	, radioChoice3(false)
{
}

CDlgSideChannelAttackVisualizationHEPreparationsRequest3::~CDlgSideChannelAttackVisualizationHEPreparationsRequest3()
{
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnInitDialog()
{
	// check first radio button initially
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_1);
	// set booleans accordingly for later usage (after dialog is closed)
	this->radioChoice1 = true;
	this->radioChoice2 = false;
	this->radioChoice3 = false;

	CDialog::OnInitDialog();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEPreparationsRequest3, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_1, OnBnClickedRadioChoice1)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_2, OnBnClickedRadioChoice2)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_3, OnBnClickedRadioChoice3)
END_MESSAGE_MAP()

// CDlgSideChannelAttackVisualizationHEPreparationsRequest3 message handlers
void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedOk()
{
	CDialog::OnOK();
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedRadioChoice1()
{
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_1);
	this->radioChoice1 = true;
	this->radioChoice2 = false;
	this->radioChoice3 = false;
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedRadioChoice2()
{
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_2);
	this->radioChoice1 = false;
	this->radioChoice2 = true;
	this->radioChoice3 = false;
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedRadioChoice3()
{
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_3);
	this->radioChoice1 = false;
	this->radioChoice2 = false;
	this->radioChoice3 = true;
}