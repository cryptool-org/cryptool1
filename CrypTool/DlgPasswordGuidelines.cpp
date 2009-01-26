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

// DlgPasswordGuidelines.cpp : implementation file

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPasswordGuidelines.h"
#include "CrypToolTools.h"
#include ".\dlgpasswordguidelines.h"
#include "DialogeMessage.h"

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
	unsigned long minimumLength = 8;
	unsigned long minimumDigits = 1;
	unsigned long minimumSpecial = 1;
	unsigned long buffer = 1024;
	char *specialGroup = new char[buffer+1];
	memset(specialGroup, 0, buffer+1);
	memcpy(specialGroup, "^°!\"§$%&/()=?´`\\<>|,;:.-_#\'+*~@", 31); 

	// try to read guidelines from registry 
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_READ, IDS_REGISTRY_SETTINGS, "PasswordGuidelines" ) == ERROR_SUCCESS )
	{
		CT_READ_REGISTRY(minimumLength, "MinimumLength");
		CT_READ_REGISTRY(minimumDigits, "MinimumDigits");
		CT_READ_REGISTRY(minimumSpecial, "MinimumSpecial");
		CT_READ_REGISTRY(specialGroup, "SpecialGroup", buffer);
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
	stringSpecialGroup = "^°!\"§$%&/()=?´`\\<>|,;:.-_#\'+*~@";

	UpdateData(false);
}
