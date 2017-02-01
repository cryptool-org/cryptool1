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
#include "CrypToolTools.h"
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
	UpdateData(false);
	// we also start with an empty number
	stringNumber.Empty();
	// update both, the number representation and the number itself
	updateNumberRepresentation();
	updateNumber();
	// make changes visible
	UpdateData(false);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CDlgLengthOfANumber, CDialog)
	ON_BN_CLICKED(IDC_RADIO_BINARY, updateNumberRepresentation)
	ON_BN_CLICKED(IDC_RADIO_OCTAL, updateNumberRepresentation)
	ON_BN_CLICKED(IDC_RADIO_DECIMAL, updateNumberRepresentation)
	ON_BN_CLICKED(IDC_RADIO_HEXADECIMAL, updateNumberRepresentation)
	ON_EN_CHANGE(IDC_EDIT_NUMBER, updateNumber)
END_MESSAGE_MAP()

void CDlgLengthOfANumber::updateNumberRepresentation()
{
	// acquire the old representation
	numberRepresentationOld = numberRepresentation;
	// make sure we're working with the current data
	UpdateData(true);
	// convert number to new representation
	BaseRepr(stringNumber, getBase(numberRepresentationOld), getBase(numberRepresentation));
	// make changes visible
	UpdateData(false);
}

void CDlgLengthOfANumber::updateNumber()
{
	// make sure we're working with the current data
	UpdateData(true);
	// remove invalid (non-alphabet) characters from the number
	const int base = getBase(numberRepresentation);
	if(base == 2) stringNumber = removeNonAlphabetCharacters(stringNumber, "01");
	if(base == 8) stringNumber = removeNonAlphabetCharacters(stringNumber, "01234567");
	if(base == 10) stringNumber = removeNonAlphabetCharacters(stringNumber, "0123456789");
	if(base == 16) stringNumber = removeNonAlphabetCharacters(stringNumber, "0123456789ABCDEF");
	// convert number to different representations
	CString stringNumberBinary = stringNumber;
	CString stringNumberOctal = stringNumber;
	CString stringNumberDecimal = stringNumber;
	CString stringNumberHexadecimal = stringNumber;
	BaseRepr(stringNumberBinary, base, 2);
	BaseRepr(stringNumberOctal, base, 8);
	BaseRepr(stringNumberDecimal, base, 10);
	BaseRepr(stringNumberHexadecimal, base, 16);
	// calculate number lengths for each representation
	CString stringNumberBinaryLength;
	CString stringNumberOctalLength;
	CString stringNumberDecimalLength;
	CString stringNumberHexadecimalLength;
	stringNumberBinaryLength.Format("%d", stringNumberBinary.GetLength());
	stringNumberOctalLength.Format("%d", stringNumberOctal.GetLength());
	stringNumberDecimalLength.Format("%d", stringNumberDecimal.GetLength());
	stringNumberHexadecimalLength.Format("%d", stringNumberHexadecimal.GetLength());
	// update number lengths for each representation
	CWnd *windowBinary = GetDlgItem(IDC_STATIC_BINARY);
	if(windowBinary) windowBinary->SetWindowText(stringNumberBinaryLength);
	CWnd *windowOctal = GetDlgItem(IDC_STATIC_OCTAL);
	if(windowOctal) windowOctal->SetWindowText(stringNumberOctalLength);
	CWnd *windowDecimal = GetDlgItem(IDC_STATIC_DECIMAL);
	if(windowDecimal) windowDecimal->SetWindowText(stringNumberDecimalLength);
	CWnd *windowHexadecimal = GetDlgItem(IDC_STATIC_HEXADECIMAL);
	if(windowHexadecimal) windowHexadecimal->SetWindowText(stringNumberHexadecimalLength);
	// update the dialog
	UpdateData(false);
}

int CDlgLengthOfANumber::getBase(const int _numberRepresentation) const
{
	if(_numberRepresentation == 0) return 2;
	if(_numberRepresentation == 1) return 8;
	if(_numberRepresentation == 2) return 10;
	return 16;
}