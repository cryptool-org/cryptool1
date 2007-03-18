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

// DlgPasswordQualityMeter.cpp

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPasswordQualityMeter.h"

IMPLEMENT_DYNAMIC(CDlgPasswordQualityMeter, CDialog)
CDlgPasswordQualityMeter::CDlgPasswordQualityMeter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordQualityMeter::IDD, pParent)
{
	password = "";
	showPassword = false;
	passwordQualityKeePass = "";
	passwordQualityMozilla = "";
	passwordQualityPGP = "";
	passwordQualityAverage = "";
}

CDlgPasswordQualityMeter::~CDlgPasswordQualityMeter()
{
}

void CDlgPasswordQualityMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPasswordQualityMeter)
	DDX_Check(pDX, IDC_CHECK_SHOWPASSWORD, showPassword);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, controlEditPassword);
	DDX_Control(pDX, IDC_PROGRESS_KEEPASS, controlQualityKeePass);
	DDX_Control(pDX, IDC_PROGRESS_MOZILLA, controlQualityMozilla);
	DDX_Control(pDX, IDC_PROGRESS_PGP, controlQualityPGP);
	DDX_Control(pDX, IDC_PROGRESS_AVERAGE, controlQualityAverage);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, password);
	DDX_Text(pDX, IDC_QUALITY_KEEPASS, passwordQualityKeePass);
	DDX_Text(pDX, IDC_QUALITY_MOZILLA, passwordQualityMozilla);
	DDX_Text(pDX, IDC_QUALITY_PGP, passwordQualityPGP);
	DDX_Text(pDX, IDC_QUALITY_AVERAGE, passwordQualityAverage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPasswordQualityMeter, CDialog)
	//{{AFX_MSG_MAP(CDlgPasswordQualityMeter)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, EditPasswordChanged)
	ON_BN_CLICKED(IDC_CHECK_SHOWPASSWORD, OnShowPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgPasswordQualityMeter-Meldungshandler

BOOL CDlgPasswordQualityMeter::OnInitDialog()
{
	CDialog::OnInitDialog();

	// some inits
	controlQualityKeePass.SetRange(0, 100);
	controlQualityKeePass.SetStep(1);
	controlQualityKeePass.SetPos(0);
	controlQualityMozilla.SetRange(0, 100);
	controlQualityMozilla.SetStep(1);
	controlQualityMozilla.SetPos(0);
	controlQualityPGP.SetRange(0, 100);
	controlQualityPGP.SetStep(1);
	controlQualityPGP.SetPos(0);
	controlQualityAverage.SetRange(0, 100);
	controlQualityAverage.SetStep(1);
	controlQualityAverage.SetPos(0);

	UpdateData(false);

	return FALSE;
}

void CDlgPasswordQualityMeter::OnShowPassword()
{
	UpdateData(true);

	if(showPassword)
		controlEditPassword.SetPasswordChar('*');
	else
		controlEditPassword.SetPasswordChar(0);
}

void CDlgPasswordQualityMeter::EditPasswordChanged()
{
	UpdateData(true);

	// todo...
	controlQualityKeePass.StepIt();
	controlQualityKeePass.StepIt();

	UpdateData(false);
}