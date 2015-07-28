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
#include "DlgLengthOfANumber.h"

CDlgLengthOfANumber::CDlgLengthOfANumber(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLengthOfANumber::IDD, pParent)
{
	
}

CDlgLengthOfANumber::~CDlgLengthOfANumber()
{

}

void CDlgLengthOfANumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_BINARY, numberRepresentation);
	DDX_Text(pDX, IDC_EDIT_NUMBER, stringNumber);
}

BOOL CDlgLengthOfANumber::OnInitDialog()
{
	CDialog::OnInitDialog();
	// by default we start with decimal representation (binary = 0, octal = 1, decimal = 2, hexadecimal = 3)
	numberRepresentation = 2;
	// we also start with an empty number
	stringNumber.Empty();
	// initially update number lengths
	updateNumberLengths();
	// make changes visible
	UpdateData(false);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CDlgLengthOfANumber, CDialog)
	ON_BN_CLICKED(IDC_RADIO_BINARY, OnClickedRadioButtonNumberRepresentation)
	ON_BN_CLICKED(IDC_RADIO_OCTAL, OnClickedRadioButtonNumberRepresentation)
	ON_BN_CLICKED(IDC_RADIO_DECIMAL, OnClickedRadioButtonNumberRepresentation)
	ON_BN_CLICKED(IDC_RADIO_HEXADECIMAL, OnClickedRadioButtonNumberRepresentation)
	ON_EN_CHANGE(IDC_EDIT_NUMBER, OnChangedNumber)
END_MESSAGE_MAP()

void CDlgLengthOfANumber::OnClickedRadioButtonNumberRepresentation()
{
	UpdateData(true);
	// convert the number to the specified number representation (2, 8, 10, 16)
	switch(numberRepresentation) {
	// binary
	case 0:
		convertNumberToRepresentation(2);
		break;
	// octal
	case 1:
		convertNumberToRepresentation(8);
		break;
	// decimal
	case 2:
		convertNumberToRepresentation(10);
		break;
	// hexadecimal
	case 3:
		convertNumberToRepresentation(16);
		break;
	default:
		break;
	}
	// update number lengths for each representation
	updateNumberLengths();
}

void CDlgLengthOfANumber::OnChangedNumber()
{
	// update number lengths for each representation
	updateNumberLengths();
}

void CDlgLengthOfANumber::convertNumberToRepresentation(const int _base)
{
	// TODO/FIXME
	stringNumber.Empty();
	if(_base == 2) stringNumber = "BINARY";
	if(_base == 8) stringNumber = "OCTAL";
	if(_base == 10) stringNumber = "DECIMAL";
	if(_base == 16) stringNumber = "HEXADECIMAL";

	// make sure the GUI is updated properly
	OnChangedNumber();
	// make changes visible
	UpdateData(false);
}

void CDlgLengthOfANumber::updateNumberLengths()
{
	// calculate new number lengths
	const int lengthBinary = calculateNumberLength(2);
	const int lengthOctal = calculateNumberLength(8);
	const int lengthDecimal = calculateNumberLength(10);
	const int lengthHexadecimal = calculateNumberLength(16);
	// acquire static text objects
	CWnd *windowBinary = GetDlgItem(IDC_STATIC_BINARY);
	CWnd *windowOctal = GetDlgItem(IDC_STATIC_OCTAL);
	CWnd *windowDecimal = GetDlgItem(IDC_STATIC_DECIMAL);
	CWnd *windowHexadecimal = GetDlgItem(IDC_STATIC_HEXADECIMAL);
	// update static text objects (the actual number lengths)
	if(windowBinary) {
		CString windowText;
		windowText.Format("%d", lengthBinary);
		windowBinary->SetWindowText(windowText);
	}
	if(windowOctal) {
		CString windowText;
		windowText.Format("%d", lengthOctal);
		windowOctal->SetWindowText(windowText);
	}
	if(windowDecimal) {
		CString windowText;
		windowText.Format("%d", lengthDecimal);
		windowDecimal->SetWindowText(windowText);
	}
	if(windowHexadecimal) {
		CString windowText;
		windowText.Format("%d", lengthHexadecimal);
		windowHexadecimal->SetWindowText(windowText);
	}
	// make changes visible
	UpdateData(false);
}

int CDlgLengthOfANumber::calculateNumberLength(const int _base)
{
	// TODO/FIXME
	return 0;
}