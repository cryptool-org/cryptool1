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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPasswordQualityMeter.h"

#include "passwordqualitymeter.h"
#include ".\dlgpasswordqualitymeter.h"

#include "passwordchecker.h"

// Verzeichnis, in dem CT gerade läuft (siehe CrypToolApp.cpp)
extern char *Pfad;

// CDlgPasswordQualityMeter-Dialogfeld

CDlgPasswordQualityMeter::CDlgPasswordQualityMeter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordQualityMeter::IDD, pParent)
{
	password = "";
	showPassword = true;
	
	intQualityKeePass = 0;
	intQualityMozilla = 0;
	intQualityPGP = 0;

	stringQualityKeePass = "";
	stringQualityMozilla = "";
	stringQualityPGP = "";

	displayedDictionaryNotFoundMessage = false;
}

CDlgPasswordQualityMeter::~CDlgPasswordQualityMeter()
{

}

void CDlgPasswordQualityMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PASSWORD, password);
	DDX_Check(pDX, IDC_CHECK_SHOWPASSWORD, showPassword);
	
	DDX_Text(pDX, IDC_QUALITY_KEEPASS, stringQualityKeePass);
	DDX_Text(pDX, IDC_QUALITY_MOZILLA, stringQualityMozilla);
	DDX_Text(pDX, IDC_QUALITY_PGP, stringQualityPGP);
	
	DDX_Control(pDX, IDC_PROGRESS_KEEPASS, controlQualityKeePass);
	DDX_Control(pDX, IDC_PROGRESS_MOZILLA, controlQualityMozilla);
	DDX_Control(pDX, IDC_PROGRESS_PGP, controlQualityPGP);
	
	DDX_Control(pDX, IDC_PICTURE_QUALITY, controlPictureQuality);

	DDX_Text(pDX, IDC_EDIT_PASSWORD_RESISTANCE, passwordResistance);
}

BOOL CDlgPasswordQualityMeter::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateUserInterface();
	
	return FALSE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CDlgPasswordQualityMeter::EditPasswordChanged()
{
	UpdateData(true);

	intQualityKeePass = passwordQualityKeePass(password);
	intQualityMozilla = passwordQualityMozilla(password);
	intQualityPGP = passwordQualityPGP(password);

	UpdateUserInterface();
}

void CDlgPasswordQualityMeter::UpdateUserInterface()
{
	// first scale down quality values if necessary
	if(intQualityKeePass >= 100) intQualityKeePass = 100;
	if(intQualityMozilla >= 100) intQualityMozilla = 100;
	if(intQualityPGP >= 100) intQualityPGP = 100;
		
	// update (string) quality display
	_itoa(intQualityKeePass, pc_str, 10);
	stringQualityKeePass = pc_str;
	stringQualityKeePass.Append(" %");
	_itoa(intQualityMozilla, pc_str, 10);
	stringQualityMozilla = pc_str;
	stringQualityMozilla.Append(" %");
	_itoa(intQualityPGP, pc_str, 10);
	stringQualityPGP = pc_str;
	stringQualityPGP.Append(" %");
	
	// update (progress bar) quality display
	controlQualityKeePass.SetRange(0, 100);
	controlQualityKeePass.SetPos(intQualityKeePass);
	controlQualityMozilla.SetRange(0, 100);
	controlQualityMozilla.SetPos(intQualityMozilla);
	controlQualityPGP.SetRange(0, 100);
	controlQualityPGP.SetPos(intQualityPGP);
		
	// set focus to password edit field
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetFocus();


	// base the visual password rating on the average of KeePass, Mozilla and PGP
	int intQualityCrypTool = (intQualityKeePass + intQualityMozilla + intQualityPGP) / 3;
    
	// we start with a "poor" visual password rating
	this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_POOR), _T("GIF"));
	if(25 < intQualityCrypTool && intQualityCrypTool <= 50)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_LOW), _T("GIF"));
	if(50 < intQualityCrypTool && intQualityCrypTool <= 75)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_AVERAGE), _T("GIF"));
	if(75 < intQualityCrypTool && intQualityCrypTool <= 90)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_HIGH), _T("GIF"));
	if(90 < intQualityCrypTool && intQualityCrypTool <= 100)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_GREAT), _T("GIF"));
	this->controlPictureQuality.Draw();

	// check password against dictionary attacks (with cracklib)
	LoadString(AfxGetInstanceHandle(), IDS_PQM_CRACKLIB_DICTIONARY_PATH, pc_str, STR_LAENGE_STRING_TABLE);
	char *result = checkPassword(password.GetBuffer(), pc_str, 0);
	if(result) {
		passwordResistance = result;
	}
	else {
		// construct and display error message for user
		if(!displayedDictionaryNotFoundMessage) {
			char tempMessage[STR_LAENGE_STRING_TABLE+1];
			char tempPath[STR_LAENGE_STRING_TABLE+1];
			char fullPath[STR_LAENGE_STRING_TABLE+1];
			memset(tempMessage, 0, STR_LAENGE_STRING_TABLE+1);
			memset(tempPath, 0, STR_LAENGE_STRING_TABLE+1);
			memset(fullPath, 0, STR_LAENGE_STRING_TABLE+1);
			LoadString(AfxGetInstanceHandle(), IDS_PQM_NO_CRACKLIB_DICTIONARY, pc_str, STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(), IDS_PQM_CRACKLIB_DICTIONARY_PATH, tempPath, STR_LAENGE_STRING_TABLE);
			sprintf(fullPath, "%s%s", Pfad, tempPath);
			sprintf(tempMessage, pc_str, fullPath);
			MessageBox(tempMessage, "CrypTool", MB_ICONINFORMATION);
			passwordResistance = tempMessage;
			// make sure this "annoying" pop-up message is displayed only once
			displayedDictionaryNotFoundMessage = true;
		}
	}

	UpdateData(false);
}

BEGIN_MESSAGE_MAP(CDlgPasswordQualityMeter, CDialog)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, EditPasswordChanged)
	ON_BN_CLICKED(IDC_CHECK_SHOWPASSWORD, OnBnClickedCheckShowpassword)
END_MESSAGE_MAP()



// CDlgPasswordQualityMeter-Meldungshandler

void CDlgPasswordQualityMeter::OnBnClickedCheckShowpassword()
{
	UpdateData(true);

	if(showPassword) ((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetPasswordChar(0);
	else ((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetPasswordChar('*');

	UpdateUserInterface();
}