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
#include "DlgFormatTextDocument.h"

#include <iostream>
#include <fstream>
#include ".\dlgformattextdocument.h"

IMPLEMENT_DYNAMIC(CDlgFormatTextDocument, CDialog)
CDlgFormatTextDocument::CDlgFormatTextDocument(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFormatTextDocument::IDD, pParent)
{
	// initialization
	removeNonAlphabetCharacters = 0;
	convertToUppercase = 0;
	convertToLowercase = 0;
	divideInBlocks = 0;
	blockSize = "5";
}

CDlgFormatTextDocument::~CDlgFormatTextDocument()
{

}

void CDlgFormatTextDocument::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHECK_REMOVE_NON_ALPHABET_CHARACTERS, removeNonAlphabetCharacters);
	DDX_Check(pDX, IDC_CHECK_CONVERT_TO_UPPERCASE, convertToUppercase);
	DDX_Check(pDX, IDC_CHECK_CONVERT_TO_LOWERCASE, convertToLowercase);
	DDX_Check(pDX, IDC_CHECK_DIVIDE_IN_BLOCKS, divideInBlocks);
	DDX_Text(pDX, IDC_EDIT_BLOCK_SIZE, blockSize);
}

CString CDlgFormatTextDocument::format(CString fileName)
{
	CString result;
	CFile infile;

	// try to open the desired file
	if(!infile.Open(fileName, CFile::modeRead)) {
		infile.Close();
		result = "";
		return result;
	}
	
	// apply the contents of the file to the result variable
	const int bufferSize = 1024;
	char buffer[bufferSize + 1];
	while(true) {
		memset(buffer, 0, bufferSize + 1);
		int count = infile.Read(buffer, bufferSize);
		result += buffer;
		if(count < bufferSize) break;
	}

	// CHECK 1: remove non-alphabet characters
	if(removeNonAlphabetCharacters) {
		CString newResult;
		for(int i=0; i<result.GetLength(); i++) {
			if(theApp.TextOptions.getAlphabet().Find(result[i]) != -1) {
				newResult += result[i];
			}
		}
		result = newResult;
	}

	// CHECK 2: convert to uppercase
	if(convertToUppercase) {
		result.MakeUpper();
	}

	// CHECK 3: convert to lowercase
	if(convertToLowercase) {
		result.MakeLower();
	}

	// CHECK 4: divide in blocks
	if(divideInBlocks) {
		// first of all, remove all newline characters and spaces
		result.Remove('\r');
		result.Remove('\n');
		result.Remove(' ');
		// then create blocks of the desired size
		int integerBlockSize = atoi(blockSize.GetBuffer());
		if(integerBlockSize < 1) integerBlockSize = 0;
		for(int i=integerBlockSize; i<result.GetLength(); i+=(integerBlockSize+1)) {
			result.Insert(i, ' ');
		}
	}
	
	// close the file
	infile.Close();

	// return the result variable
	return result;
}

BEGIN_MESSAGE_MAP(CDlgFormatTextDocument, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_REMOVE_NON_ALPHABET_CHARACTERS, OnBnClickedCheckRemoveNonAlphabetCharacters)
	ON_BN_CLICKED(IDC_CHECK_CONVERT_TO_UPPERCASE, OnBnClickedCheckConvertToUppercase)
	ON_BN_CLICKED(IDC_CHECK_CONVERT_TO_LOWERCASE, OnBnClickedCheckConvertToLowercase)
	ON_BN_CLICKED(IDC_CHECK_DIVIDE_IN_BLOCKS, OnBnClickedCheckDivideInBlocks)
	ON_BN_CLICKED(ID_TEXTOPTIONS, &CDlgFormatTextDocument::OnBnClickedTextoptions)
END_MESSAGE_MAP()

void CDlgFormatTextDocument::OnBnClickedOk()
{
	UpdateData(true);
	OnOK();
}

void CDlgFormatTextDocument::OnBnClickedCheckRemoveNonAlphabetCharacters()
{
	UpdateData(true);
}

void CDlgFormatTextDocument::OnBnClickedCheckConvertToUppercase()
{
	UpdateData(true);
	// deactivate "convert to lowercase" check box if necessary
	if(convertToUppercase == 1 && convertToLowercase == 1) 
		convertToLowercase = 0;
	UpdateData(false);
}

void CDlgFormatTextDocument::OnBnClickedCheckConvertToLowercase()
{
	UpdateData(true);
	// deactivate "convert to uppercase" check box if necessary
	if(convertToLowercase == 1 && convertToUppercase == 1)
		convertToUppercase = 0;
	UpdateData(false);
}

void CDlgFormatTextDocument::OnBnClickedCheckDivideInBlocks()
{
	UpdateData(true);
	// activate/deactivate edit field for block size+
	if(divideInBlocks) GetDlgItem(IDC_EDIT_BLOCK_SIZE)->EnableWindow(TRUE);
	else GetDlgItem(IDC_EDIT_BLOCK_SIZE)->EnableWindow(FALSE);
	UpdateData(false);
}

void CDlgFormatTextDocument::OnBnClickedTextoptions()
{
	// allow the user to change the CrypTool alphabet
	theApp.TextOptions.DoModal();
}
