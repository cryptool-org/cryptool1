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
#include "IntegerArithmetic.h"
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
	DDX_Text(pDX, IDC_STATIC_BINARY, stringNumberLengthBinary);
	DDX_Text(pDX, IDC_STATIC_OCTAL, stringNumberLengthOctal);
	DDX_Text(pDX, IDC_STATIC_DECIMAL, stringNumberLengthDecimal);
	DDX_Text(pDX, IDC_STATIC_HEXADECIMAL, stringNumberLengthHexadecimal);
	DDX_Text(pDX, IDC_EDIT_NUMBER, stringNumber);
	DDX_Control(pDX, IDC_RADIO_BINARY, wndBinary);
	DDX_Control(pDX, IDC_RADIO_OCTAL, wndOctal);
	DDX_Control(pDX, IDC_RADIO_DECIMAL, wndDecimal);
	DDX_Control(pDX, IDC_RADIO_HEXADECIMAL, wndHexadecimal);
	DDX_Control(pDX, IDC_EDIT_NUMBER, editNumberControl);
}

BOOL CDlgLengthOfANumber::OnInitDialog()
{
	CDialog::OnInitDialog();
	// by default we start with zero in decimal representation
	numberRepresentation = 2;
	stringNumber = "0";
	stringNumberFormula = "0";
	UpdateData(false);
	// update both, the number representation and the number itself
	updateNumberRepresentation();
	updateNumber();
	// set the focus onto the edit number field, and select everything
	editNumberControl.SetFocus();
	editNumberControl.SetSel(0, -1);
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
	// copy internal string number when switching from decimal and to decimal
	if(getBase(numberRepresentationOld) == 10) {
		stringNumber = stringNumberFormula;
	}
	// convert number to new representation
	BaseRepr(stringNumber, getBase(numberRepresentationOld), getBase(numberRepresentation));
	// make changes visible
	UpdateData(false);
	// avoid inconsistencies
	updateNumber();
	// set the focus onto the edit number field, and select end
	editNumberControl.SetFocus();
	editNumberControl.SetSel(stringNumber.GetLength(), -1);
}

void CDlgLengthOfANumber::updateNumber()
{
	// make sure we're working with the current data
	UpdateData(true);
	// acquire input base and selection indices (start and end)
	const int base = getBase(numberRepresentation);
	int selection_start = -1;
	int selection_end = -1;
	editNumberControl.GetSel(selection_start, selection_end);
	// make a copy of the original input for later
	const CString stringNumberOld = stringNumber;
	// convert input to upper case so we don't run into trouble with hex characters
	stringNumber = stringNumber.MakeUpper();
	// remove all invalid characters
	if(base == 2) stringNumber = removeNonAlphabetCharacters(stringNumber, "01");
	if(base == 8) stringNumber = removeNonAlphabetCharacters(stringNumber, "01234567");
	if(base == 10) stringNumber = removeNonAlphabetCharacters(stringNumber, "0123456789+-*^()");
	if(base == 16) stringNumber = removeNonAlphabetCharacters(stringNumber, "0123456789ABCDEF");
	// initialize the formula variable
	stringNumberFormula = CString();
	// for decimal numbers we need to check if the formula is valid; 
	// if it is not, we do some magic with the interface so that the 
	// user cannot put it into invalid state, and don't show a result
	bool validFormula = true;
	if(base == 10) {
		CString formula = stringNumber;
		CString formulaClean = CString();
		int index = -1;
		const bool checkedFormula = CheckFormula(formula, base, formulaClean, index);
		const bool evaluatedFormula = EvalFormula(formula, index, true);
		validFormula = checkedFormula && evaluatedFormula;
		stringNumberFormula = validFormula ? formula : CString();
	}
	// convert numbers to different representations, and calculate 
	// lengths for each representation if evaluation was successful; 
	// otherwise display some default values to indicate problems
	if(validFormula && stringNumber.GetLength() > 0) {
		CString stringNumberBinary = base == 10 ? stringNumberFormula : stringNumber;
		CString stringNumberOctal = base == 10 ? stringNumberFormula : stringNumber;
		CString stringNumberDecimal = base == 10 ? stringNumberFormula : stringNumber;
		CString stringNumberHexadecimal = base == 10 ? stringNumberFormula : stringNumber;
		BaseRepr(stringNumberBinary, base, 2);
		BaseRepr(stringNumberOctal, base, 8);
		BaseRepr(stringNumberDecimal, base, 10);
		BaseRepr(stringNumberHexadecimal, base, 16);
		stringNumberLengthBinary.Format("%d", stringNumberBinary.GetLength());
		stringNumberLengthOctal.Format("%d", stringNumberOctal.GetLength());
		stringNumberLengthDecimal.Format("%d", stringNumberDecimal.GetLength());
		stringNumberLengthHexadecimal.Format("%d", stringNumberHexadecimal.GetLength());
	}
	else {
		stringNumberLengthBinary = "-";
		stringNumberLengthOctal = "-";
		stringNumberLengthDecimal = "-";
		stringNumberLengthHexadecimal = "-";
	}
	wndBinary.EnableWindow(validFormula && stringNumber.GetLength() > 0);
	wndOctal.EnableWindow(validFormula && stringNumber.GetLength() > 0);
	wndDecimal.EnableWindow(validFormula && stringNumber.GetLength() > 0);
	wndHexadecimal.EnableWindow(validFormula && stringNumber.GetLength() > 0);
	// update the dialog
	UpdateData(false);
	// reset cursor (if characters were removed)
	if(stringNumberOld != stringNumber) {
		const int selection = min(max(selection_start, selection_end), stringNumber.GetLength());
		editNumberControl.SetSel(selection, selection);
	}
}

int CDlgLengthOfANumber::getBase(const int _numberRepresentation) const
{
	_ASSERT(_numberRepresentation >= 0);
	_ASSERT(_numberRepresentation <= 3);
	if(_numberRepresentation == 0) return 2;
	if(_numberRepresentation == 1) return 8;
	if(_numberRepresentation == 2) return 10;
	if(_numberRepresentation == 3) return 16;
	return -1;
}