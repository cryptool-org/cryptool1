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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPasswordQualityMeter.h"

#include "passwordqualitymeter.h"
#include "passwordchecker.h"
#include "DlgPasswordGuidelines.h"

// Verzeichnis, in dem CT gerade läuft (siehe CrypToolApp.cpp)
extern char *Pfad;

// CDlgPasswordQualityMeter-Dialogfeld

CDlgPasswordQualityMeter::CDlgPasswordQualityMeter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordQualityMeter::IDD, pParent)
	, passwordLength(0)
{
	password = "";
	showPassword = true;
	
	intQualityKeePass = 0;
	intQualityMozilla = 0;
	intQualityPGP = 0;
	intQualityCrypTool = 0;
	passwordLength = 0;

	stringQualityKeePass = "";
	stringQualityMozilla = "";
	stringQualityPGP = "";
	stringQualityCrypTool = "";

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
	DDX_Text(pDX, IDC_QUALITY_CRYPTOOL, stringQualityCrypTool);

	DDX_Control(pDX, IDC_PROGRESS_KEEPASS, controlQualityKeePass);
	DDX_Control(pDX, IDC_PROGRESS_MOZILLA, controlQualityMozilla);
	DDX_Control(pDX, IDC_PROGRESS_PGP, controlQualityPGP);
	DDX_Control(pDX, IDC_PROGRESS_CRYPTOOL, controlQualityCrypTool);

	DDX_Control(pDX, IDC_PICTURE_QUALITY, controlPictureQuality);

	DDX_Text(pDX, IDC_EDIT_PASSWORD_RESISTANCE, passwordResistance);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, passwordEditCtrl);
	DDX_Control(pDX, IDC_EDIT1, passwordLengthEditCtrl);
	DDX_Text(pDX, IDC_EDIT1, passwordLength);
}

BOOL CDlgPasswordQualityMeter::OnInitDialog()
{
	CDialog::OnInitDialog();

	// this workaround forces to update the password quality display
	EditPasswordChanged();

	UpdateUserInterface();
	
	return FALSE;
}

void CDlgPasswordQualityMeter::EditPasswordChanged()
{
	UpdateData(true);
	// FIXME: removal of chars <= #32 currently required (CRACKLIB)
	int i = 0;
	int nStart, nEnd;
	passwordEditCtrl.GetSel(nStart, nEnd);
	while ( 1 )
	{
		if ( (unsigned char)password[i] <= ' ' )
		{
			if 	( nStart > i ) nStart--;
			if  ( nEnd > i ) nEnd--;
			password.Delete(i);
		}
		else
			i++;
		if ( i >= password.GetLength() )
			break;
	};
	passwordLength = password.GetLength();
	UpdateData(false);
	passwordEditCtrl.SetSel(nStart, nEnd);

	intQualityKeePass = passwordQualityKeePass(password);
	intQualityMozilla = passwordQualityMozilla(password);
	intQualityPGP = passwordQualityPGP(password);

	UpdateUserInterface();
}

void CDlgPasswordQualityMeter::UpdateUserInterface()
{
	// assemble full path of dictionary 
	char dictionaryPath[STR_LAENGE_STRING_TABLE+1];
	char fullDictionaryPath[STR_LAENGE_STRING_TABLE+1];
    LoadString(AfxGetInstanceHandle(), IDS_PQM_CRACKLIB_DICTIONARY_PATH, dictionaryPath, STR_LAENGE_STRING_TABLE);
	sprintf(fullDictionaryPath, "%s%s", Pfad, dictionaryPath);

	// parameters for depth analysis (the CrypTool version)
	double theCrypToolPasswordEntropy = 0.0;
	std::string theCrypToolPasswordComponents;

    // check password against dictionary attacks (with cracklib)
	char *result = checkPassword(password.GetBuffer(), fullDictionaryPath, !showPassword, &theCrypToolPasswordEntropy, &theCrypToolPasswordComponents);
	if(result) {
		passwordResistance = result;
	}
	else {
		// construct and display error message for user
		if(!displayedDictionaryNotFoundMessage) {
			char tempMessage[STR_LAENGE_STRING_TABLE+1];
			LoadString(AfxGetInstanceHandle(), IDS_PQM_NO_CRACKLIB_DICTIONARY, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(tempMessage, pc_str, fullDictionaryPath, fullDictionaryPath, fullDictionaryPath, fullDictionaryPath);
			MessageBox(tempMessage, "CrypTool", MB_ICONINFORMATION);
			passwordResistance = tempMessage;
			// make sure this "annoying" pop-up message is displayed only once
			displayedDictionaryNotFoundMessage = true;
		}
		// update the GUI
		UpdateData(false);
	}

	// first scale down quality values if necessary
	if(intQualityKeePass >= 100) intQualityKeePass = 100;
	if(intQualityMozilla >= 100) intQualityMozilla = 100;
	if(intQualityPGP >= 100) intQualityPGP = 100;
	// for the CrypTool approach we assume an entropy of 128 bits equals a quality of 100
	intQualityCrypTool = (int)floor((theCrypToolPasswordEntropy / 128) * 100);
	if(intQualityCrypTool >= 100) intQualityCrypTool = 100;
		
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
	_itoa(intQualityCrypTool, pc_str, 10);
	stringQualityCrypTool = pc_str;
	stringQualityCrypTool.Append(" %");

	// CAUTION: for the entropy display, assume a maximum of 128 bit for each approach,
	//			but exclude Mozilla since the algorithm is not entropy-based
	char tempString[STR_LAENGE_STRING_TABLE+1];

	// update (string) entropy display
	int intEntropyKeePass = intQualityKeePass * 128 / 100;
	LoadString(AfxGetInstanceHandle(), IDS_PQM_BIT, tempString, STR_LAENGE_STRING_TABLE);
	sprintf(pc_str, " (%d %s)", intEntropyKeePass, tempString);
	stringQualityKeePass.Append(pc_str);
	int intEntropyPGP = intQualityPGP * 128 / 100;
	LoadString(AfxGetInstanceHandle(), IDS_PQM_BIT, tempString, STR_LAENGE_STRING_TABLE);
	sprintf(pc_str, " (%d %s)", intEntropyPGP, tempString);
	stringQualityPGP.Append(pc_str);
	int intEntropyCrypTool = intQualityCrypTool * 128 / 100;
	LoadString(AfxGetInstanceHandle(), IDS_PQM_BIT, tempString, STR_LAENGE_STRING_TABLE);
	sprintf(pc_str, " (%d %s)", intEntropyCrypTool, tempString);
	stringQualityCrypTool.Append(pc_str);

	// update (progress bar) quality display
	controlQualityKeePass.SetRange(0, 100);
	controlQualityKeePass.SetPos(intQualityKeePass);
	controlQualityMozilla.SetRange(0, 100);
	controlQualityMozilla.SetPos(intQualityMozilla);
	controlQualityPGP.SetRange(0, 100);
	controlQualityPGP.SetPos(intQualityPGP);
	controlQualityCrypTool.SetRange(0, 100);
	controlQualityCrypTool.SetPos(intQualityCrypTool);
		
	// set focus to password edit field
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetFocus();


	// base the visual password rating on the average of KeePass, Mozilla, PGP and CrypTool
	int intAverageQuality = (intQualityKeePass + intQualityMozilla + intQualityPGP + intQualityCrypTool) / 4;
    
	// we start with a "poor" visual password rating
	this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_POOR), _T("GIF"));
	if(25 < intAverageQuality && intAverageQuality <= 50)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_LOW), _T("GIF"));
	if(50 < intAverageQuality && intAverageQuality <= 75)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_AVERAGE), _T("GIF"));
	if(75 < intAverageQuality && intAverageQuality <= 90)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_HIGH), _T("GIF"));
	if(90 < intAverageQuality && intAverageQuality <= 100)
		this->controlPictureQuality.Load(MAKEINTRESOURCE(IDR_GIF_PQM_QUALITY_GREAT), _T("GIF"));
	this->controlPictureQuality.Draw();

	// flomar, 01/24/2012: we want to dynamically show/hide the comment about 
	// the restriction of CrypTool's password evaluation to 32 characters 
	// (hidden as long as the password is <=32 characters long, shown otherwise)
	CWnd *windowCrypToolQualityComment = GetDlgItem(IDC_QUALITY_CRYPTOOL_COMMENT);
	if(windowCrypToolQualityComment) {
		windowCrypToolQualityComment->ShowWindow(password.GetLength() <= 32 ? SW_HIDE : SW_SHOW);
	}

	UpdateData(false);
}

BEGIN_MESSAGE_MAP(CDlgPasswordQualityMeter, CDialog)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, EditPasswordChanged)
	ON_BN_CLICKED(IDC_CHECK_SHOWPASSWORD, OnBnClickedCheckShowpassword)
	ON_BN_CLICKED(ID_CONFIGURE_PASSWORD_GUIDELINES, OnBnClickedConfigurePasswordGuidelines)
END_MESSAGE_MAP()



// CDlgPasswordQualityMeter-Meldungshandler

void CDlgPasswordQualityMeter::OnBnClickedCheckShowpassword()
{
	UpdateData(true);

	if(showPassword) ((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetPasswordChar(0);
	else ((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetPasswordChar('*');

	UpdateUserInterface();
}

void CDlgPasswordQualityMeter::OnBnClickedConfigurePasswordGuidelines()
{
	CDlgPasswordGuidelines dlg;
	dlg.DoModal();
	// user might be confused if we don't update the UI immediately
	UpdateUserInterface();
}

void CDlgPasswordQualityMeter::setPassword(const CString &_password)
{
	// set the new password
	password = _password;
}