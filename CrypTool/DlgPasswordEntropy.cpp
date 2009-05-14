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
#include "DlgPasswordEntropy.h"
#include "DlgPasswordQualityMeter.h"

const CString constStringNonConfusableCharactersWrittenTransmission = "abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPRSTUVWXYZ23456789";
const CString constStringNonConfusableCharactersTelephonicTransmission = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
const CString constStringWLANAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+,-./:=?@[]^_{}~";

// CDlgPasswordEntropy-Dialogfeld

CDlgPasswordEntropy::CDlgPasswordEntropy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordEntropy::IDD, pParent)
{
	stringPasswordBitLength = "";
	stringPasswordAlphabet = theApp.TextOptions.getAlphabet();
	stringPasswordLength = "";
	stringPasswordExample = "";
	useCrypToolAlphabet = true;
	useNonConfusableCharactersWrittenTransmission = false;
	useNonConfusableCharactersTelephonicTransmission = false;
	useWLANAlphabet = false;

	// initialize pseudo-random number generator
	srand((unsigned)time(NULL));
}

CDlgPasswordEntropy::~CDlgPasswordEntropy()
{
}

void CDlgPasswordEntropy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PASSWORDBITLENGTH, stringPasswordBitLength);
	DDX_Text(pDX, IDC_EDIT_PASSWORDALPHABET, stringPasswordAlphabet);
	DDX_Text(pDX, IDC_EDIT_PASSWORDLENGTH, stringPasswordLength);
	DDX_Text(pDX, IDC_EDIT_PASSWORDEXAMPLE, stringPasswordExample);
	DDX_Check(pDX, IDC_CHECK_USECRYPTOOLALPHABET, useCrypToolAlphabet);
	DDX_Check(pDX, IDC_CHECK_USENONCONFUSABLECHARACTERS_WRITTENTRANSMISSION, useNonConfusableCharactersWrittenTransmission);
	DDX_Check(pDX, IDC_CHECK_USENONCONFUSABLECHARACTERS_TELEPHONICTRANSMISSION, useNonConfusableCharactersTelephonicTransmission);
	DDX_Check(pDX, IDC_CHECK_USEWLANALPHABET, useWLANAlphabet);
	DDX_Control(pDX, IDC_EDIT_PASSWORDBITLENGTH, editControlPasswordBitLength);
	DDX_Control(pDX, IDC_EDIT_PASSWORDALPHABET, editControlPasswordAlphabet);
}

BOOL CDlgPasswordEntropy::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set the focus to bit length input field
	GetDlgItem(IDC_EDIT_PASSWORDBITLENGTH)->SetFocus();

	// update the GUI
	updateGUI();
	
	return FALSE;
}

BEGIN_MESSAGE_MAP(CDlgPasswordEntropy, CDialog)
	ON_BN_CLICKED(ID_GENERATEPASSWORD, OnBnClickedGeneratepassword)
	ON_EN_CHANGE(IDC_EDIT_PASSWORDBITLENGTH, EditPasswordBitLengthChanged)
	ON_EN_CHANGE(IDC_EDIT_PASSWORDALPHABET, EditPasswordAlphabetChanged)
	ON_BN_CLICKED(IDC_CHECK_USECRYPTOOLALPHABET, CheckBoxesAlphabetChanged)
	ON_BN_CLICKED(IDC_CHECK_USENONCONFUSABLECHARACTERS_WRITTENTRANSMISSION, CheckBoxesAlphabetChanged)
	ON_BN_CLICKED(IDC_CHECK_USENONCONFUSABLECHARACTERS_TELEPHONICTRANSMISSION, CheckBoxesAlphabetChanged)
	ON_BN_CLICKED(IDC_CHECK_USEWLANALPHABET, CheckBoxesAlphabetChanged)
	ON_BN_CLICKED(ID_TEXTOPTIONS, OnBnClickedTextoptions)
	ON_BN_CLICKED(ID_MEASUREPASSWORDQUALITY, OnBnClickedMeasurepasswordquality)
END_MESSAGE_MAP()


// CDlgPasswordEntropy-Meldungshandler

void CDlgPasswordEntropy::OnBnClickedGeneratepassword()
{
	// before generating the password, we need both the password bit length and the alphabet
	if(stringPasswordBitLength.IsEmpty() || stringPasswordAlphabet.IsEmpty()) {
		LoadString(AfxGetInstanceHandle(), IDS_PQM_ENTROPY_NOT_ALL_INPUT_PARAMETERS_SET, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// get the desired password length
	int passwordCharactersNeeded = atoi((const char*)(stringPasswordLength));

	// generate a "random" password and make it visible
	stringPasswordExample = "";
	for(int i=0; i<(int)(passwordCharactersNeeded); i++) {
		int index = rand() % stringPasswordAlphabet.GetLength();
		stringPasswordExample +=  stringPasswordAlphabet[index];
	}

	// set the focus to bit length input field
	GetDlgItem(IDC_EDIT_PASSWORDBITLENGTH)->SetFocus();

	// update the GUI
	updateGUI();

	UpdateData(false);
}

void CDlgPasswordEntropy::OnBnClickedTextoptions()
{
	// allow the user to change the CrypTool alphabet
	CString oldAlphabet = theApp.TextOptions.getAlphabet();
	theApp.TextOptions.DoModal();

	// don't do anything if check box for CrypTool alphabet is not checked
	if(!useCrypToolAlphabet) return;
	// else: assign the new alphabet
	else stringPasswordAlphabet = theApp.TextOptions.getAlphabet();
	
	// clear result fields if the alphabet has changed
	if(oldAlphabet != theApp.TextOptions.getAlphabet()) {
        stringPasswordLength = "";
		stringPasswordExample = "";
	}

	// update the GUI
	updateGUI();

	UpdateData(false);

	// update the required password length
	updatePasswordLength();

	// set the focus to bit length input field
	GetDlgItem(IDC_EDIT_PASSWORDBITLENGTH)->SetFocus();
}

void CDlgPasswordEntropy::EditPasswordBitLengthChanged() 
{
	UpdateData(true);

	// allow digits only
	CString validBitLength;
	for(int i=0; i<stringPasswordBitLength.GetLength(); i++) {
		if(stringPasswordBitLength[i] >= '0' && stringPasswordBitLength[i] <= '9')
			validBitLength += stringPasswordBitLength[i];
	}
	stringPasswordBitLength = validBitLength;

	// update the GUI
	updateGUI();

	UpdateData(false);

	// update the required password length
	updatePasswordLength();

	// set cursor position to the end of the input
	editControlPasswordBitLength.SetSel(stringPasswordBitLength.GetLength(), stringPasswordBitLength.GetLength());
}

void CDlgPasswordEntropy::EditPasswordAlphabetChanged()
{
	UpdateData(true);

	// make sure there are no double entries
	CString validAlphabet;
	for(int i=0; i<stringPasswordAlphabet.GetLength(); i++) {
		if(stringPasswordAlphabet.Find(stringPasswordAlphabet[i], i+1) == -1) {
			validAlphabet += stringPasswordAlphabet[i];
		}
	}
	stringPasswordAlphabet = validAlphabet;

	// clear result field
	stringPasswordExample = "";

	// update the GUI
	updateGUI();

	UpdateData(false);

	// update the required password length
	updatePasswordLength();

	// set cursor position to the end of the input
	editControlPasswordAlphabet.SetSel(stringPasswordAlphabet.GetLength(), stringPasswordAlphabet.GetLength());
}

void CDlgPasswordEntropy::CheckBoxesAlphabetChanged()
{
	UpdateData(true);

	// get the old alphabet before any changes by the user
	CString oldAlphabet = stringPasswordAlphabet;
	// create a variable for the new (changed) alphabet
	CString newAlphabet = "";

	// compute alphabet union sets

	if(useCrypToolAlphabet) {
		// assign new alphabet if necessary
		if(newAlphabet.IsEmpty()) newAlphabet = theApp.TextOptions.getAlphabet();
		newAlphabet = computeAlphabetUnionSet(newAlphabet, theApp.TextOptions.getAlphabet());
	}
	if(useNonConfusableCharactersWrittenTransmission) {
		// assign new alphabet if necessary
		if(newAlphabet.IsEmpty()) newAlphabet = constStringNonConfusableCharactersWrittenTransmission;
		newAlphabet = computeAlphabetUnionSet(newAlphabet, constStringNonConfusableCharactersWrittenTransmission);
	}
	if(useNonConfusableCharactersTelephonicTransmission) {
		// assign new alphabet if necessary
		if(newAlphabet.IsEmpty()) newAlphabet = constStringNonConfusableCharactersTelephonicTransmission;
		newAlphabet = computeAlphabetUnionSet(newAlphabet, constStringNonConfusableCharactersTelephonicTransmission);
	}
	if(useWLANAlphabet) {
		// assign new alphabet if necessary
		if(newAlphabet.IsEmpty()) newAlphabet = constStringWLANAlphabet;
		newAlphabet = computeAlphabetUnionSet(newAlphabet, constStringWLANAlphabet);
	}

	// at this point, NO check box is checked anymore, so use the old alphabet
	if(	!useCrypToolAlphabet &&	!useNonConfusableCharactersWrittenTransmission && !useNonConfusableCharactersTelephonicTransmission && !useWLANAlphabet) {
		newAlphabet = oldAlphabet;
	}

	// update alphabet and clear result field if the alphabet has changed
	if(newAlphabet != oldAlphabet) {
		stringPasswordAlphabet = newAlphabet;
		stringPasswordExample = "";
	}

	// show text options button only if "use CrypTool alphabet" check box is checked
	if(useCrypToolAlphabet) GetDlgItem(ID_TEXTOPTIONS)->EnableWindow(true);
	else GetDlgItem(ID_TEXTOPTIONS)->EnableWindow(false);

	// update the GUI
	updateGUI();

	UpdateData(false);

	// update the required password length
	updatePasswordLength();
}

void CDlgPasswordEntropy::updatePasswordLength()
{
	UpdateData(true);

	// figure out how many bits of entropy we get with ONE CHARACTER, given the assumption 
	// that each password character is independently and randomly chosen from the alphabet
	double bitsPerCharacter = log2((double)(stringPasswordAlphabet.GetLength()));

	// now compute how many characters we need to get the desired entropy
	double passwordLengthInBitsDesired = (double)(atoi(stringPasswordBitLength.GetBuffer()));
	double passwordCharactersNeeded = ceil(passwordLengthInBitsDesired/bitsPerCharacter);

	// make the number of characters needed for the password visible to the user
	char buffer[16];
	memset(buffer, 0, 16);
	sprintf(buffer, "%d", (int)(passwordCharactersNeeded));
	stringPasswordLength = buffer;

	// make sure a password of zero length is impossible
	if(stringPasswordLength == "0") {
		stringPasswordLength = "";
		stringPasswordExample = "";
	}

	// update the GUI
	updateGUI();

	UpdateData(false);
}

CString CDlgPasswordEntropy::computeAlphabetUnionSet(const CString alphabetOne, const CString alphabetTwo)
{
	// variable for return value
	CString result;
	// remove all characters from result alphabet that are NOT part of alphabet two
	for(int i=0; i<alphabetOne.GetLength(); i++) {
		if(alphabetTwo.Find(alphabetOne[i]) != -1) {
			result.AppendChar(alphabetOne[i]);
		}
	}
	return result;
}

void CDlgPasswordEntropy::updateGUI()
{
	// if there is no password, disable "measure password quality" button
	if(this->stringPasswordExample.GetLength() == 0)
		GetDlgItem(ID_MEASUREPASSWORDQUALITY)->EnableWindow(false);
	// else: show the button
	else
		GetDlgItem(ID_MEASUREPASSWORDQUALITY)->EnableWindow(true);
}

void CDlgPasswordEntropy::OnBnClickedMeasurepasswordquality()
{
	// create a password quality meter dialog
	CDlgPasswordQualityMeter dialog;
	// initialize it with the given password
	dialog.setPassword(stringPasswordExample);
	// show the dialog
	dialog.DoModal();
}