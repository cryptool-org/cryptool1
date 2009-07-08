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

// DlgVigenereAnalysisSchroedel.cpp : implementation file
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgVigenereAnalysisSchroedel.h"

#include <iostream>
#include <fstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CDlgVigenereAnalysisSchroedel dialog

IMPLEMENT_DYNAMIC(CDlgVigenereAnalysisSchroedel, CDialog)

CDlgVigenereAnalysisSchroedel::CDlgVigenereAnalysisSchroedel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVigenereAnalysisSchroedel::IDD, pParent)
	, ciphertext(_T(""))
	, plaintext(_T(""))
	, key(_T(""))
	, edit1(_T(""))
	, theAnalysis(0)
{
	theAnalysis = new VigenereAnalysisSchroedel(this);
}

CDlgVigenereAnalysisSchroedel::~CDlgVigenereAnalysisSchroedel()
{
	if(theAnalysis) delete theAnalysis;
}

void CDlgVigenereAnalysisSchroedel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_CIPHERTEXT, ciphertext);
	DDX_Text(pDX, IDC_EDIT_PLAINTEXT, plaintext);
	DDX_Text(pDX, IDC_EDIT_KEY, key);
	DDX_Text(pDX, IDC_EDIT1, edit1);
}


BEGIN_MESSAGE_MAP(CDlgVigenereAnalysisSchroedel, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgVigenereAnalysisSchroedel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgVigenereAnalysisSchroedel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgVigenereAnalysisSchroedel::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDlgVigenereAnalysisSchroedel message handlers

void CDlgVigenereAnalysisSchroedel::OnBnClickedButton1()
{
	// TODO
}

void CDlgVigenereAnalysisSchroedel::OnBnClickedButton2()
{
	UpdateData(true);

	CString s;

	s = edit1;

	// TODO

	/*
	procedure TForm1.Button2Click(Sender: TObject);
var s : String;
begin
  s := edit1.Text;
  cipher.Text := Copy( s, 1, Pos( ';', s )-1);
  delete( s, 1, Pos( ';', s ));
  plaintext.Text := Copy( s, 1, Pos( ';', s )-1);
  delete( s, 1, Pos( ';', s ));
  cipherkey.Text := s;

end;
	*/
}

void CDlgVigenereAnalysisSchroedel::OnBnClickedButton3()
{
	// TODO
}



/****************************************
		BEGIN VIGENERE ANALYSIS SCHROEDEL
****************************************/

const CString cPosAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const CString cPosVigenere = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
const CString klartext     = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const CString alphabet     = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";

VigenereAnalysisSchroedel::VigenereAnalysisSchroedel(CDlgVigenereAnalysisSchroedel *dlg) {
	theDialog = dlg;
}

VigenereAnalysisSchroedel::~VigenereAnalysisSchroedel() {
	theDialog = 0;
}

void VigenereAnalysisSchroedel::setStatus(CString str) {
	/*
		flomar, 06/25/2009
		This is a logging-dummy: in the original Pascal version this function 
		informs the user about all sorts of status messages via the GUI; we have 
		to figure out a way to transform this into the C++ (dialog) world.
	*/
}

void VigenereAnalysisSchroedel::output(CString str) {
	/*
		flomar, 06/25/2009
		This is a logging-dummy: in the original Pascal version this function 
		informs the user about all sorts of status messages via the GUI; we have 
		to figure out a way to transform this into the C++ (dialog) world.
	*/
}

void VigenereAnalysisSchroedel::readTriDigrams() {
	
	CString s;

	maxDi = 0;
	setStatus("Loading Digrams...");

	// create a handle for the input file
	std::ifstream fileInputDigrams;
	fileInputDigrams.open("digramsAtBeginningOfWords.txt");
	if(!fileInputDigrams) return;

	for(int i=0; i<26; i++) {
		for(int o=0; o<26; o++) {
			std::string s2;
			getline(fileInputDigrams, s2);
			s = s2.c_str();
			s.Delete(s.Find(';'));
			cDigram[i][o] = atoi(s.GetBuffer());
			maxDi = maxDi + atoi(s.GetBuffer());
		}
	}

	// close input file
	fileInputDigrams.close();


	maxTri = 0;
	setStatus("Loading Trigrams...");

	// create a handle for the input file
	std::ifstream fileInputTrigrams;
	fileInputTrigrams.open("trigramsAtBeginningOfWords.txt");
	if(!fileInputTrigrams) return;

	for(int i=0; i<26; i++) {
		for(int o=0; o<26; o++) {
			for(int l=0; l<26; l++) {
				std::string s2;
				getline(fileInputTrigrams, s2);
				s = s2.c_str();
				s.Delete(s.Find(';'));
				cTrigram[i][o][l] = atoi(s.GetBuffer());
				maxTri = maxTri + atoi(s.GetBuffer());
			}
		}
	}

	// close input file
	fileInputTrigrams.close();

	setStatus("Digrams and Trigrams loaded.");
}

void VigenereAnalysisSchroedel::firstChar() {
	// TODO
}

void VigenereAnalysisSchroedel::secondChar() {
	// TODO
}

void VigenereAnalysisSchroedel::solveTrigram() {
	
	CString s;
	CString key, text, cipher;
	CString cKey, cText;

	// FIXME: isn't this unnecessary in C++?
	for(int i=0; i<1000; i++) {
		solvers[i][0] = "";
		solvers[i][1] = "";
		solvers[i][2] = "";
		solvers[i][3] = "";
	}

	for(int i=0; i<cPairs; i++) {
		key = pairs[i][0];
		text = pairs[i][1];
    // TODO: cipher := Form1.cipher.Text;

    // Try first key
    cKey = "";
    cText = "";
    setStatus("Reading dictionary");

		for(xDict=0; xDict<dictCount; xDict++) {
			s = dict[xDict];
			
			if(s.Find(key) == 0) {
				if(s.GetLength() > key.GetLength()) {
					if(cKey.Find(s[3]) == -1) {
						cKey = cKey + s[3];
					}
				}
			}
			if(s.Find(text) == 0) {
				if(s.GetLength() > text.GetLength()) {
					if(cText.Find(s[3]) == -1) {
						cText = cText + s[3];
					}
				}
			}
		}
	}
}

void VigenereAnalysisSchroedel::readDict() {

	CString s;

	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open("dict.txt");
	if(!fileInput) return;

	dictCount = 0;

	while(!fileInput.eof()) {
		std::string s2;
		getline(fileInput, s2);
		s = s2.c_str();
		s.Trim();
		// TODO: s= trim(ansiuppercase(s));
		if(s.Find('%') == 0) {
			for(int i=s.GetLength(); i>0; i--) {
				CString temp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
				if(temp.Find(s[i]) == 0) {
					s.Delete(i);
					s.Insert(i, ' ');
				}
				if(!s.IsEmpty()) {
					dictCount++;
					dict[dictCount] = s.Trim();
				}
			}
		}
	}

	// close input file
	fileInput.close();

}

void VigenereAnalysisSchroedel::outputSave(CString a1, CString a2, CString a3, CString a4, CString a5, CString a6, CString a7) {

	// create a handle for the output file
	std::ofstream fileOutput;
	fileOutput.open("statistics.txt", ios_base::app);
	if(!fileOutput) return;

	fileOutput << a1 << std::endl;
	fileOutput << a2 << std::endl;
	fileOutput << a3 << std::endl;
	fileOutput << a4 << "/" << a5 << std::endl;
	fileOutput << a6 << "/" << a7 << std::endl;

	// close output file
	fileOutput.close();


	// create a handle for the output file
	fileOutput.open("statistics.csv", ios_base::app);
	if(!fileOutput) return;

	fileOutput << a1 << ";" << a2 << ";" << a3 << ";" << a5 << ";" << a6 << ";" << a7 << std::endl;
	
	// close output file
	fileOutput.close();

}

CString VigenereAnalysisSchroedel::encryptText(CString text, CString key) {

	while(text.Find(' ') > 0) {
		text.Delete(0, 1);
	}

	while(key.GetLength() < text.GetLength()) {
		key = key + key;
	}
	key.Delete(text.GetLength(), key.GetLength() - text.GetLength());

	CString encryptedText;

	for(int i=0; i<text.GetLength(); i++) {
		for(int o=0; o<26; o++) {
			if(key[i] == vigenere[o]) {
				encryptedText = encryptedText + vigenere[o + klartext.Find(text[i])];
			}
		}
	}

	return encryptedText;
}

CString VigenereAnalysisSchroedel::decryptText(CString text, CString key) {

	while(key.GetLength() < text.GetLength()) {
		key = key + key;
	}
	key.Delete(text.GetLength(), key.GetLength() - text.GetLength());

	CString decryptedText;

	for(int i=0; i<text.GetLength(); i++) {
		for(int o=0; o<26; o++) {
			if(key[i] == vigenere[o]) {
				decryptedText = decryptedText + klartext[o + vigenere.Find(text[i])];
			}
		}
	}

	return decryptedText;
}

int VigenereAnalysisSchroedel::rateString(CString str, CString key) {

	CString s, lowords, tmp, start;

	int o, z;

	int check[1000];
	CString words[1000];
	CString match[100][5];

	// check the first 100 characters only
	if(str.GetLength() > 100) {
		str.Delete(100, str.GetLength() - 100);
	}

	// find all words matching somehow
	for(int i=0; i<1000; i++) {
		words[i] = "";
	}

	for(int i=0, o=0; i<dictCount; i++) {
		s = dict[i];
		if(str.Find(s) > 0) {
			o++;
			words[o] = s;
			lowords = lowords + (char)(13) + s;
		}
	}

	for(int i=0; i<1000; i++) {
		check[i] = 0;
	}

	for(int i=0; i<o; i++) {
		tmp = str;
		do {
			if(tmp.Find(words[i]) > 0) {
				z = tmp.Find(words[i]);
				for(int l=0; l<words[i].GetLength(); l++) {
					check[tmp.Find(words[i]) + l - 1]++;
				}
				for(int l=0; l<words[i].GetLength(); l++) {
					tmp.Delete(z + l - 1, 1);
					tmp.Insert(z + l - 1, '~');
				}
			}
		}
		while(tmp.Find(words[i]) > 0);
	}

	for(int i=0; i<o; i++) {
		s = s + (char)(13) + words[i];
	}

	// number of words
	o = 0;
	start = "";
	subRate = 0;

	for(int i=0; i<str.GetLength(); i++) {
		subRate = subRate + check[i];
		if(check[i] > 0) {
			start = start + itoa(check[i], 0, 10);
		}
		else {
			start = start + " ";
		}
		if(check[i] == 0) {
			o -= 2;
		}
		if(check[i] > 0) {
			o += 1;
		}
	}

	if(o > maxRating) {
		for(int l=0; l<100; l++) {
			solveRating = 0;
			solveText = "";
			solveKey = "";
			solveCount = 0;
		}
	}

	if(o >= maxRating) {
		solveCount++;
		maxRating = o;
		solveRating = o;
		solveText = str;
		solveKey = key;
	}

	return o;
}

CString VigenereAnalysisSchroedel::fillLeft(CString was, int wie) {
	while(was.GetLength() < wie) {
		was.Insert(0, ' ');
	}
	return was;
}

/****************************************
		END VIGENERE ANALYSIS SCHROEDEL
****************************************/