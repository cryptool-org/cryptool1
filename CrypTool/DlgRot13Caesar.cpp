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

// DlgRot13Caesar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgRot13Caesar.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRot13Caesar 


CDlgRot13Caesar::CDlgRot13Caesar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRot13Caesar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRot13Caesar)
	//}}AFX_DATA_INIT
}


void CDlgRot13Caesar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRot13Caesar)
	DDX_Control(pDX, IDC_TO, controlEditTargetAlphabet);
	DDX_Control(pDX, IDC_FROM, controlEditSourceAlphabet);
	DDX_Control(pDX, ID_ENCRYPT, controlButtonEncryption);
	DDX_Control(pDX, ID_DECRYPT, controlButtonDecryption);
	DDX_Control(pDX, IDC_DIST, controlEditDistance);
	DDX_Control(pDX, IDC_KEY, controlEditAlphabeticKey);
	DDX_Control(pDX, IDC_EDIT_ALPHCODE, controlEditNumericKey);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MESSAGE_ROT13, controlEditMessageROT13);
	DDX_Control(pDX, IDC_EDIT1, controlEditShowAlphabetSizeAndMapping);

	DDX_Control(pDX, IDC_RADIO1, controlRadioButtonCaesar);
	DDX_Control(pDX, IDC_RADIO2, controlRadioButtonROT13);
	DDX_Control(pDX, IDC_RADIO3, controlRadioButtonKeyOffsetZero);
	DDX_Control(pDX, IDC_RADIO4, controlRadioButtonKeyOffsetOne);
	DDX_Control(pDX, IDC_RADIO5, controlRadioButtonAlphabetic);
	DDX_Control(pDX, IDC_RADIO6, controlRadioButtonNumeric);

	DDX_Text(pDX, IDC_KEY, alphabeticKey);
	DDX_Text(pDX, IDC_EDIT_ALPHCODE, numericKey);
	DDX_Text(pDX, IDC_FROM, alphabet);
	DDX_Text(pDX, IDC_TO, targetAlphabet);
	
}


BEGIN_MESSAGE_MAP(CDlgRot13Caesar, CDialog)
	//{{AFX_MSG_MAP(CDlgRot13Caesar)
	ON_BN_CLICKED(IDC_RADIO1, onUpdateGUI)
	ON_BN_CLICKED(IDC_RADIO2, onUpdateGUI)
	ON_BN_CLICKED(IDC_RADIO3, onUpdateGUI)
	ON_BN_CLICKED(IDC_RADIO4, onUpdateGUI)
	ON_BN_CLICKED(IDC_RADIO5, onUpdateGUI)
	ON_BN_CLICKED(IDC_RADIO6, onUpdateGUI)
	ON_EN_UPDATE(IDC_KEY, onUpdateGUI)
	ON_EN_UPDATE(IDC_EDIT_ALPHCODE, onUpdateGUI)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(ID_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_TxtOpt, onTextOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRot13Caesar 

BOOL CDlgRot13Caesar::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// some assertions for debug mode
	VERIFY(controlBitmapButtonPaste.AutoLoad(IDC_PASTE_KEY,this));
	VERIFY(font.CreatePointFont(100,"Courier New"));
	// set monospace font for alphabet display
	controlEditSourceAlphabet.SetFont(&font);
	controlEditTargetAlphabet.SetFont(&font);
	controlEditAlphabeticKey.SetFont(&font);

	// set the limit for the alphabetic key length
	controlEditAlphabeticKey.SetLimitText(1);
	// set the limit for the numeric key length (depends on the length of the alphabet)
	controlEditNumericKey.SetLimitText(getDigitsOfAlphabetLength());

	// some default settings
	controlRadioButtonCaesar.SetCheck(TRUE);
	controlRadioButtonKeyOffsetZero.SetCheck(TRUE);
	controlRadioButtonAlphabetic.SetCheck(TRUE);
	char charDefaultKey = theApp.TextOptions.getAlphabet()[0];
	CString strDefaultKey;
	strDefaultKey += charDefaultKey;
	controlEditAlphabeticKey.SetWindowText(strDefaultKey);

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	controlBitmapButtonPaste.SetToolTipText(&buttonPasteText);

	// update the graphical user interface (main update function)
	onUpdateGUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

CaesarKey CDlgRot13Caesar::checkPasteKeyVariant(int SID)
{
	CaesarKey theKey;
	CString theKeyString;
	LoadString(AfxGetInstanceHandle(),SID,pc_str,STR_LAENGE_STRING_TABLE);
	if (PasteKey(pc_str, theKeyString)) {
		// what we get here is a string of the form "A, KEY OFFSET: 0" or "B, KEY OFFSET: 1" (and so 
		// on), so we separate the actual key (i.e. "A" or "B") from the key offset (i.e. "0" or "1").
		CString key = theKeyString; key.Delete(1, key.GetLength()-1);
		CString offset = theKeyString; offset.Delete(0, offset.GetLength()-1);
		// copy key and offset into Caesar key structure
		if (0 <= theApp.TextOptions.getAlphabet().Find(key))
			theKey.key = key.GetBuffer(key.GetLength())[0];
		theKey.offset = _ttoi(offset);
	}
	return theKey;
}

void CDlgRot13Caesar::OnPasteKey() 
{
	CaesarKey theKey;
	// check for Caesar key
	theKey = checkPasteKeyVariant(IDS_CRYPT_CAESAR);
	// check for ROT13 key, if it's not a Caesar key
	if(!theKey.key) theKey = checkPasteKeyVariant(IDS_CRYPT_ROT13);
	
	// display error message if it's neither a Caesar nor a ROT13 key
	if(!theKey.key) {
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_BAD_KEY,pc_str,255);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
	}
	// if the key is valid, enable/disable the respective GUI elements ("simulate" user input)...
	else {
		controlRadioButtonAlphabetic.EnableWindow(TRUE);
		controlRadioButtonNumeric.EnableWindow(FALSE);
		controlEditAlphabeticKey.SetWindowText(CString(theKey.key));
		CString key = _T(" ");
		key.SetAt(0, theKey.key);
		controlEditNumericKey.SetWindowText(calculateNumericKeyFromAlphabeticKey(key));
		if(theKey.offset) {
			controlRadioButtonKeyOffsetZero.SetCheck(0);
			controlRadioButtonKeyOffsetOne.SetCheck(1);
		}
		else {
			controlRadioButtonKeyOffsetZero.SetCheck(1);
			controlRadioButtonKeyOffsetOne.SetCheck(0);
		}
	}

	// ...and update the GUI
	onUpdateGUI();
}

void CDlgRot13Caesar::OnEncrypt() 
{
	modeDecryption = false;
	OnOK();
}

void CDlgRot13Caesar::OnDecrypt() 
{
	modeDecryption = true;
	OnOK();	
}

void CDlgRot13Caesar::onTextOptions()
{
	theApp.TextOptions.DoModal();
	
	controlEditSourceAlphabet.SetWindowText(theApp.TextOptions.getAlphabet());

	onUpdateGUI();
}
int CDlgRot13Caesar::getDigitsOfAlphabetLength()
{
	int length = theApp.TextOptions.getAlphabet().GetLength();
	CString str;
	str.Format("%d",length);

	return str.GetLength();

}

void CDlgRot13Caesar::onUpdateGUI()
{
	// caution: ROT13 is only available if the alphabet consists of an even number of characters
	if(theApp.TextOptions.getAlphabet().GetLength() % 2) {
		controlRadioButtonCaesar.SetCheck(TRUE);
		controlRadioButtonROT13.SetCheck(FALSE);
		controlRadioButtonCaesar.EnableWindow(TRUE);
		controlRadioButtonROT13.EnableWindow(FALSE);
		// notify the user
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_INFO_NEGATIVE,pc_str,STR_LAENGE_STRING_TABLE);
		controlEditMessageROT13.SetWindowText(pc_str);
	}
	else {
		if(controlRadioButtonCaesar.GetCheck() == BST_CHECKED) controlRadioButtonROT13.SetCheck(FALSE);
		else controlRadioButtonROT13.SetCheck(TRUE);
		controlRadioButtonCaesar.EnableWindow(TRUE);
		controlRadioButtonROT13.EnableWindow(TRUE);
	}

	UpdateData(TRUE);

	// determine which mode we're in (Caesar or ROT13)
	if(controlRadioButtonCaesar.GetCheck() == BST_CHECKED) modeCaesar = true;
	else modeCaesar = false;

	// determine which type of key input the user has chosen (alphabetic or numeric)
	if(controlRadioButtonAlphabetic.GetCheck() == BST_CHECKED) alphabeticKeyInput = true;
	else alphabeticKeyInput = false;

	// determine which key offset is to be used (zero or one)
	if(controlRadioButtonKeyOffsetZero.GetCheck() == BST_CHECKED) keyOffsetZero = true;
	else keyOffsetZero = false;

	// now do the actual GUI update...

	// *** CAESAR mode ***
	if(modeCaesar) {
		// encryption type: Caesar
		typeEncryption = IDS_STRING_CAESAR;
		// enable alphabetic key radio button, enable numeric key radio button
		controlRadioButtonAlphabetic.EnableWindow(TRUE);
		controlRadioButtonNumeric.EnableWindow(TRUE);
		if(alphabeticKeyInput) {
			// enable alphabetic key input field, disable numeric key input field
			controlEditAlphabeticKey.EnableWindow(TRUE);
			controlEditNumericKey.EnableWindow(FALSE);
			// in case the given alphabetic key is invalid (not found in alphabet), we have two options:
			//   option 1: we check if the upper/lower case equivalent of the key is valid
			//   option 2: we default to an empty key
			if(theApp.TextOptions.getAlphabet().Find(alphabeticKey) == -1) {
				CString tempKey = alphabeticKey;
				if(theApp.TextOptions.getAlphabet().Find(tempKey.MakeUpper()) != -1) alphabeticKey.MakeUpper();
				else if(theApp.TextOptions.getAlphabet().Find(tempKey.MakeLower()) != -1) alphabeticKey.MakeLower();
				else alphabeticKey = "";

			}
			// in case the given alphabetic key is invalid (missing), we default to an empty key
			if(alphabeticKey.IsEmpty()) {
				alphabeticKey = "";
			}
			// calculate the according numeric key
			numericKey = calculateNumericKeyFromAlphabeticKey(alphabeticKey);
		}
		else {
			// disable alphabetic key input field, enable numeric key input field
			controlEditAlphabeticKey.EnableWindow(FALSE);
			controlEditNumericKey.EnableWindow(TRUE);
			int integerNumericKey = _ttoi(numericKey);
			// if we have an invalid key (either below zero or larger than the length of the alphabet), default to an empty key
			if(integerNumericKey < 0 || integerNumericKey > theApp.TextOptions.getAlphabet().GetLength()) alphabeticKey = "";
			// calculate the according alphabetic key
			else alphabeticKey = calculateAlphabeticKeyFromNumericKey(numericKey);
		}
	}
	// *** ROT13 mode ***
	else {
		// encryption type: ROT13
		typeEncryption = IDS_STRING_ROT13;
		// disable alphabetic key radio button, disable numeric key radio button
		controlRadioButtonAlphabetic.EnableWindow(FALSE);
		controlRadioButtonNumeric.EnableWindow(FALSE);
		// disable alphabetic key input field, disable numeric key input field
		controlEditAlphabeticKey.EnableWindow(FALSE);
		controlEditNumericKey.EnableWindow(FALSE);

		// set numeric key to half the size of the alphabet
		int integerNumericKey = theApp.TextOptions.getAlphabet().GetLength() / 2;
		numericKey.Format("%d", integerNumericKey);
		// set alphabetic key accordingly
		alphabeticKey = calculateAlphabeticKeyFromNumericKey(numericKey);
	}

	// display the Caesar distance
	controlEditDistance.SetWindowText(numericKey);

	// display the alphabet
	alphabet = theApp.TextOptions.getAlphabet();

	// calculate the target alphabet (the shifted one) if there's a valid key
	if(!alphabeticKey.IsEmpty() && !numericKey.IsEmpty()) {
		int integerNumericKey = _ttoi(numericKey);
		int integerAlphabetSize = theApp.TextOptions.getAlphabet().GetLength();
		char *stringTargetAlphabet = new char[integerAlphabetSize+1];
		memset(stringTargetAlphabet, 0, integerAlphabetSize+1);
		for(int i=0; i<integerAlphabetSize; i++) {
			stringTargetAlphabet[i] = theApp.TextOptions.getAlphabet()[(integerNumericKey + i) % integerAlphabetSize];
		}
		targetAlphabet = stringTargetAlphabet;
		delete stringTargetAlphabet;
	}
	else {
		targetAlphabet = "";
	}

	// display the paste key button only if there's a valid key in the key store
	if(checkPasteKeyVariant(IDS_CRYPT_CAESAR).key || checkPasteKeyVariant(IDS_CRYPT_ROT13).key)
		controlBitmapButtonPaste.EnableWindow(TRUE);
	else controlBitmapButtonPaste.EnableWindow(FALSE);

	// display alphabet size and how the alphabet is mapped (user notification)
	LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_CASE,pc_str,STR_LAENGE_STRING_TABLE);
	char l_str[1024];
	sprintf(l_str, pc_str, theApp.TextOptions.getAlphabet().GetLength());
	controlEditShowAlphabetSizeAndMapping.SetWindowText(l_str);

	// display encrypt and decrypt buttons only if there's a valid key and an alphabet
	if(!alphabeticKey.IsEmpty() && !numericKey.IsEmpty() && !targetAlphabet.IsEmpty()) {
		controlButtonEncryption.EnableWindow(TRUE);
		controlButtonDecryption.EnableWindow(TRUE);
	}
	else {
		controlButtonEncryption.EnableWindow(FALSE);
		controlButtonDecryption.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

CString CDlgRot13Caesar::calculateNumericKeyFromAlphabeticKey(CString alphabeticKey) 
{
	CString result = "";
	if(alphabeticKey.IsEmpty()) return result;
	int position = theApp.TextOptions.getAlphabet().Find(alphabeticKey);
	// we do have a valid position, that means the alphabetic key is part of the alphabet
	if(position != -1) {
		// but if the key offset is not zero, we have to increase the numeric key by one and 
		// make sure we stay within valid boundaries (% alphabet length)
		if(!keyOffsetZero) {
			position++;
			position = position % theApp.TextOptions.getAlphabet().GetLength();
		}
		result.Format("%d", position);
	}
	return result;	
}

CString CDlgRot13Caesar::calculateAlphabeticKeyFromNumericKey(CString numericKey)
{
	CString result = "";
	int position = _ttoi(numericKey);
	// we do have a valid position, that means the position is within the alphabet range
	if(position < theApp.TextOptions.getAlphabet().GetLength()) {
		// but if the key offset is not zero, we have to decrease the numeric key by one unless
		// it is already zero
		if(!keyOffsetZero) {
			if(position <= 0) position = theApp.TextOptions.getAlphabet().GetLength() - 1;
			else position--;
		}
		result = theApp.TextOptions.getAlphabet()[position];
	}
	return result;
}