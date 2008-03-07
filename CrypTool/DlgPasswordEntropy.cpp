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
#include "DlgPasswordEntropy.h"
#include ".\dlgpasswordentropy.h"


// CDlgPasswordEntropy-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgPasswordEntropy, CDialog)

CDlgPasswordEntropy::CDlgPasswordEntropy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordEntropy::IDD, pParent)
{
	stringPasswordBitLength = "";
	stringPasswordAlphabet = "";
	stringPasswordLength = "";
	stringPasswordExample = "";
	useCrypToolAlphabet = false;

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
	DDX_Control(pDX, IDC_EDIT_PASSWORDBITLENGTH, editControlPasswordBitLength);
}


BEGIN_MESSAGE_MAP(CDlgPasswordEntropy, CDialog)
	ON_BN_CLICKED(ID_GENERATEPASSWORD, OnBnClickedGeneratepassword)
	ON_EN_CHANGE(IDC_EDIT_PASSWORDBITLENGTH, EditPasswordBitLengthChanged)
	ON_EN_CHANGE(IDC_EDIT_PASSWORDALPHABET, EditPasswordAlphabetChanged)
	ON_BN_CLICKED(IDC_CHECK_USECRYPTOOLALPHABET, CheckUseCrypToolAlphabetChanged)
	ON_BN_CLICKED(ID_TEXTOPTIONS, OnBnClickedTextoptions)
END_MESSAGE_MAP()


// CDlgPasswordEntropy-Meldungshandler

void CDlgPasswordEntropy::OnBnClickedGeneratepassword()
{
	// before generating the password, we need both the password bit length and the alphabet
	if(stringPasswordBitLength.IsEmpty() || stringPasswordAlphabet.IsEmpty()) {
		MessageBox("TODO: missing parameters", "CrypTool", MB_ICONINFORMATION);
		return;
	}

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

	// generate a "random" password and make it visible
	stringPasswordExample = "";
	
	for(int i=0; i<(int)(passwordCharactersNeeded); i++) {
		int index = rand() % stringPasswordAlphabet.GetLength();
		stringPasswordExample +=  stringPasswordAlphabet[index];
	}

	UpdateData(false);
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

	// clear result fields
	stringPasswordLength = "";
	stringPasswordExample = "";

	UpdateData(false);

	// set cursor position to the end of the input
	editControlPasswordBitLength.SetSel(stringPasswordBitLength.GetLength(), stringPasswordBitLength.GetLength());
}

void CDlgPasswordEntropy::EditPasswordAlphabetChanged()
{
	UpdateData(true);

	// if the alphabet is changed, disable the "use CrypTool alphabet" check box
	useCrypToolAlphabet = false;
	// make sure there are no double entries
	CString validAlphabet;
	for(int i=0; i<stringPasswordAlphabet.GetLength(); i++) {
		if(stringPasswordAlphabet.Find(stringPasswordAlphabet[i], i+1) == -1) {
			validAlphabet += stringPasswordAlphabet[i];
		}
	}
	stringPasswordAlphabet = validAlphabet;

	// clear result fields
	stringPasswordLength = "";
	stringPasswordExample = "";

	UpdateData(false);
}

void CDlgPasswordEntropy::CheckUseCrypToolAlphabetChanged()
{
	UpdateData(true);

	// use the CrypTool alphabet if desired
	if(useCrypToolAlphabet) stringPasswordAlphabet = theApp.TextOptions.m_alphabet;
	else stringPasswordAlphabet = "";

	// clear result fields
	stringPasswordLength = "";
	stringPasswordExample = "";

	UpdateData(false);
}

void CDlgPasswordEntropy::OnBnClickedTextoptions()
{
	// allow the user to change the CrypTool alphabet
	CString oldAlphabet = theApp.TextOptions.m_alphabet;
	theApp.TextOptions.DoModal();
	stringPasswordAlphabet = theApp.TextOptions.m_alphabet;
	
	// clear result fields if the alphabet has changed
	if(oldAlphabet != theApp.TextOptions.m_alphabet) {
        stringPasswordLength = "";
		stringPasswordExample = "";
	}

	UpdateData(false);
}
