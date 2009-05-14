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

// DlgSideChannelAttackVisualizationHEPreparationsRequest1.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSideChannelAttackVisualizationHEPreparationsRequest1.h"

// CDlgSideChannelAttackVisualizationHEPreparationsRequest1 dialog

IMPLEMENT_DYNCREATE(CDlgSideChannelAttackVisualizationHEPreparationsRequest1, CDialog)

CDlgSideChannelAttackVisualizationHEPreparationsRequest1::CDlgSideChannelAttackVisualizationHEPreparationsRequest1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSideChannelAttackVisualizationHEPreparationsRequest1::IDD, pParent)
	, radioChoice1(false)
	, radioChoice2(false)
{
}

CDlgSideChannelAttackVisualizationHEPreparationsRequest1::~CDlgSideChannelAttackVisualizationHEPreparationsRequest1()
{
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CDlgSideChannelAttackVisualizationHEPreparationsRequest1::OnInitDialog()
{
	// check first radio button initially
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_2, IDC_RADIO_CHOICE_1);
	// set booleans accordingly for later usage (after dialog is closed)
	this->radioChoice1 = true;
	this->radioChoice2 = false;

	CDialog::OnInitDialog();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEPreparationsRequest1, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_1, OnBnClickedRadioChoice1)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_2, OnBnClickedRadioChoice2)
END_MESSAGE_MAP()

// CDlgSideChannelAttackVisualizationHEPreparationsRequest1 message handlers


void CDlgSideChannelAttackVisualizationHEPreparationsRequest1::OnBnClickedOk()
{
	CDialog::OnOK();
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest1::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest1::OnBnClickedRadioChoice1()
{
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_2, IDC_RADIO_CHOICE_1);
	this->radioChoice1 = true;
	this->radioChoice2 = false;
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest1::OnBnClickedRadioChoice2()
{
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_2, IDC_RADIO_CHOICE_2);
	this->radioChoice1 = false;
	this->radioChoice2 = true;
}