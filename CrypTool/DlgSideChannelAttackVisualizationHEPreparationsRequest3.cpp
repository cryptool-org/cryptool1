/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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