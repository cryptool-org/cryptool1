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
