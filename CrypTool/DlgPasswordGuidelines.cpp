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

// DlgPasswordGuidelines.cpp : implementation file

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPasswordGuidelines.h"
#include "CrypToolTools.h"
#include ".\dlgpasswordguidelines.h"
#include "DialogeMessage.h"

// our default special character set (see DlgTextOptions.cpp)
extern char *defaultSpecialCharacters;

CDlgPasswordGuidelines::CDlgPasswordGuidelines(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordGuidelines::IDD, pParent)
{

}

CDlgPasswordGuidelines::~CDlgPasswordGuidelines()
{

}

void CDlgPasswordGuidelines::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PASSWORD_LENGTH, stringMinimumLength);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_DIGITS, stringMinimumDigits);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_SPECIAL, stringMinimumSpecial);
	DDX_Text(pDX, IDC_EDIT_PASSWORD_SPECIAL_GROUP, stringSpecialGroup);
}

BOOL CDlgPasswordGuidelines::OnInitDialog()
{
	CDialog::OnInitDialog();

	// some default values
	unsigned long minimumLength;
	unsigned long minimumDigits;
	unsigned long minimumSpecial;
	unsigned long buffer = 1024;
	char *specialGroup = new char[buffer+1]; 

	// try to read guidelines from registry 
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_READ, IDS_REGISTRY_SETTINGS, "PasswordGuidelines" ) == ERROR_SUCCESS )
	{
		// if we cannot read a variable, we stick to a specific default value (see below)

		if(!CT_READ_REGISTRY(minimumLength, "MinimumLength")) {
			minimumLength = 8;
		}
		if(!CT_READ_REGISTRY(minimumDigits, "MinimumDigits")) {
			minimumDigits = 1;
		}
		if(!CT_READ_REGISTRY(minimumSpecial, "MinimumSpecial")) {
			minimumSpecial = 1;
		}
		if(!CT_READ_REGISTRY(specialGroup, "SpecialGroup", buffer)) {
			memset(specialGroup, 0, buffer+1);
			memcpy(specialGroup, defaultSpecialCharacters, strlen(defaultSpecialCharacters));
		}

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	_itoa(minimumLength, pc_str, 10);
	stringMinimumLength = pc_str;
  _itoa(minimumDigits, pc_str, 10);
	stringMinimumDigits = pc_str;
	_itoa(minimumSpecial, pc_str, 10);
	stringMinimumSpecial = pc_str;
	stringSpecialGroup = specialGroup;

	delete specialGroup;

	UpdateData(false);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgPasswordGuidelines::OnBnClickedOk()
{
	UpdateData(true);

	// do some conversion stuff...
	int minimumLength = atoi(stringMinimumLength.GetBuffer());
	int minimumDigits = atoi(stringMinimumDigits.GetBuffer());
	int minimumSpecial = atoi(stringMinimumSpecial.GetBuffer());

	if ( minimumSpecial > 0 && !stringSpecialGroup.GetLength() )
	{
		Message(IDS_PQMERROR_NO_SPECIALCHARACTERS, MB_ICONSTOP);
		return;
	}

	// try to write guidelines into registry
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "PasswordGuidelines" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY((int)(minimumLength), "MinimumLength");
		CT_WRITE_REGISTRY((int)(minimumDigits), "MinimumDigits");
		CT_WRITE_REGISTRY((int)(minimumSpecial), "MinimumSpecial");
		CT_WRITE_REGISTRY((CString)(stringSpecialGroup), "SpecialGroup");
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	OnOK();
}

BEGIN_MESSAGE_MAP(CDlgPasswordGuidelines, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_DEFAULT, OnBnClickedDefault)
END_MESSAGE_MAP()

void CDlgPasswordGuidelines::OnBnClickedDefault()
{
	// this is the hard-coded default for password guidelines
	stringMinimumLength = "8";
	stringMinimumDigits = "1";
	stringMinimumSpecial = "1";
	stringSpecialGroup = defaultSpecialCharacters;

	UpdateData(false);
}
