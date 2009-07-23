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

#include <cstdlib>
#include <time.h>

// for file locations relativ to CrypTool
extern char *Pfad;

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
	, autorunFileName(_T(""))
	, theAnalysis(0)
{
	theAnalysis = new VigenereAnalysisSchroedel(this);

	// fill Vigenere array
	CString s;
	CString t;
	s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  s = s + s;
	for(int i=0; i<26; i++) {
		t = s;
		t.Delete(0, i+1);
		this->theAnalysis->vigenere[i] = t.Left(26);
	}

	// specify autorun filename
	autorunFileName = CString(Pfad) + "autorun.txt";

	// read dictionary
	this->theAnalysis->readDict();
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
	DDX_Text(pDX, IDC_EDIT_AUTORUN_FILE_NAME, autorunFileName);
}


BEGIN_MESSAGE_MAP(CDlgVigenereAnalysisSchroedel, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgVigenereAnalysisSchroedel::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgVigenereAnalysisSchroedel::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgVigenereAnalysisSchroedel::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDlgVigenereAnalysisSchroedel message handlers

void CDlgVigenereAnalysisSchroedel::OnBnClickedButton1()
{
	UpdateData(true);

	// TODO theAnalysis->startzeit = Date + Time;
	
	theAnalysis->maxRating = 0;
	theAnalysis->solveCount = 0;

	if(ciphertext.GetLength() >= 3) {
		// Memo1.Clear
		ciphertext = ciphertext.MakeUpper();
		theAnalysis->readTriDigrams();

		theAnalysis->setStatus("Initializing");
		for(int i=0; i<17575; i++) {
			theAnalysis->pairs[i][0] = "";
			theAnalysis->pairs[i][1] = "";
			theAnalysis->score[i][0] = 0;
			theAnalysis->score[i][1] = 0;
		}

		theAnalysis->output("Cipher to break: " + ciphertext);
		theAnalysis->output(" ");

		theAnalysis->firstChar();
		theAnalysis->secondChar();
		
		theAnalysis->solveTrigram();

		// TODO if not shortRun.checked Then solveTrigram;
		// TODO Memo1.Lines.SaveToFile("result.txt");

	}

	UpdateData(false);
}

void CDlgVigenereAnalysisSchroedel::OnBnClickedButton2()
{
	UpdateData(true);

	CString s;

	s = edit1;

	ciphertext = s.Left(s.Find(';'));
	s.Delete(0, s.Find(';') + 1);
	
	plaintext = s.Left(s.Find(';'));
	s.Delete(0, s.Find(';') + 1);

	key = s;

	UpdateData(false);
}

void CDlgVigenereAnalysisSchroedel::OnBnClickedButton3()
{
	UpdateData(true);

	CString s;
	CString t;
	std::string tTemp;

	// create a handle for autorun file
	std::ifstream fileAutorun;
	fileAutorun.open(autorunFileName);
	if(!fileAutorun) return;

	while(!fileAutorun.eof()) {
		getline(fileAutorun, tTemp);
		t = tTemp.c_str();
		theAnalysis->setStatus("PREPARING AUTORUN TEXT: " + t);
		t.MakeUpper();
		for(int i=t.GetLength(); i>0; i--) {
			if(CString("ABCDEFGHIJKLMNOPQRSTUVWXYZ ").Find(t[i]) == -1) {
				t.SetAt(i, ' ');
			}	
		}
		t.Remove(' ');
		s = s + " " + t.Trim();
	}
	
	s.Delete(0, 1);

	// close autorun file
	fileAutorun.close();

	CString p;
	int o;
	CString k;

	p = s;
	o = s.GetLength();

	// TODO progressbar1.Max = o;

	while(s.Find(' ') != -1) {
		k = theAnalysis->dict[rand() % theAnalysis->dictCount];

		t = s.Left(20);
		t.Trim();

		// TODO: does this make sense? (besides being unstable anyway)

		// only full words
//		while(t[t.GetLength()-1] != ' ') {
//			t.Delete(t.GetLength()-1, 1);
//		}
		

		//ciphertext = "";

		// TODO progressbar1.Position := o - Length( s );

		theAnalysis->setStatus("Autorun: " + k + "/" + t);

		if(s.Find(' ') > 2) {
			plaintext = t;
			key = k;
			OnBnClickedButton1();
		}

		s.Delete(0, s.Find(' ') + 1);
	}

	UpdateData(false);
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
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);

	// some init stuff
	memset(cDigram, 0, 4*26*26);
	memset(cTrigram, 0, 4*26*26*26);
	memset(score, 0, 4*26*26*26*2);
	memset(_score, 0, 4*26*26*26*2);

	// open result file
	CString pathToFileResult;
	pathToFileResult = Pfad;
	pathToFileResult += "result.txt";
	fileResult.open(pathToFileResult, ios_base::trunc);
	if(!fileResult) return;
}

VigenereAnalysisSchroedel::~VigenereAnalysisSchroedel() {
	theDialog = 0;

	// close the result file
	fileResult.close();
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

	fileResult.write(str.GetBuffer(), str.GetLength());
	fileResult.write("\r\n", 2);
}

void VigenereAnalysisSchroedel::readTriDigrams() {
	
	CString s;

	maxDi = 0;
	setStatus("Loading Digrams...");

	// create a handle for the input file
	std::ifstream fileInputDigrams;
	CString pathToDigrams;
	pathToDigrams = Pfad;
	pathToDigrams += "digramsAtBeginningOfWords.txt";
	fileInputDigrams.open(pathToDigrams);
	if(!fileInputDigrams) return;

	for(int i=0; i<26; i++) {
		for(int o=0; o<26; o++) {
			std::string s2;
			getline(fileInputDigrams, s2);
			s = s2.c_str();
			s.Delete(0, s.Find(';') + 1);
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
	CString pathToTrigrams;
	pathToTrigrams = Pfad;
	pathToTrigrams += "trigramsAtBeginningOfWords.txt";
	fileInputTrigrams.open(pathToTrigrams);
	if(!fileInputTrigrams) return;

	for(int i=0; i<26; i++) {
		for(int o=0; o<26; o++) {
			for(int l=0; l<26; l++) {
				std::string s2;
				getline(fileInputTrigrams, s2);
				s = s2.c_str();
				s.Delete(0, s.Find(';') + 1);
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
	
	char actChar;
	char fText, fKey;
	CString s;
	int i, o;

	setStatus("Create all pairs for the first cipher");
	actChar = this->theDialog->ciphertext[0];
	output("First character of cipher: " + actChar);
  output("============================");
  output(" ");
  output("Possible pairs:");

	s = "";
	o = 0;

	for(int i=0; i<26; i++) {
		fText = cPosAlphabet[i];
		fKey = cPosVigenere[ cPosAlphabet.Find(actChar) + 26 - i];
		cipherPos = cPosAlphabet.Find(actChar) + 26 - i;

		while(cipherPos > 25) {
			cipherPos = cipherPos - 25;
		}

		s = s + fText + "-" + fKey + " ";


		pairs[o][0] = fText;
		pairs[o][1] = fKey;
		score[o][0] = 0;
		score[o][1] = 0;
		o++;
		cPairs = o;
	}

	output(s);
	CString sStr; sStr.Format("%d", o);
	output("Count: " + sStr);
	output(" ");

	remain = cPairs;
	output("Remove dups:");
	for(int l=0; l<cPairs-1; l++) {
		for(o=l+1; o<cPairs; o++) {
			if(pairs[l][0] == pairs[o][1]) {
				score[o][0] = -1;
				score[o][1] = -1;
				remain--;
			}
		}
	}

	s = "";
	i = 0;

	for(o=0; o<cPairs; o++) {
		if(score[o][0] == -1) {
			i++;
			s = s + pairs[o][0] + "-" + pairs[o][1] + " ";
		}
	}
	output(s);
	CString iStr; iStr.Format("%d", i);
	output("Count: " + iStr);
	CString remainStr; remainStr.Format("%d", remain);
	output("Remain: " + remainStr);
	output(" ");

	setStatus("Deleting dups from internal list...");
	o = 0;
	for(int l=0; l<cPairs; l++) {
		if(score[l][1] != -1) {
			_pairs[o][0] = pairs[l][0];
			_pairs[o][1] = pairs[l][1];
			_score[o][0] = score[l][0];
			_score[o][1] = score[l][1];
			o++;
		}
	}

	// flomar: HACK: that way we avoid the endless loop
	cPairs = remain;

	for(int i=0; i<cPairs; i++) {
		pairs[i][0] = "";
		pairs[i][1] = "";
		score[i][0] = 0;
		score[i][1] = 0;
	}

	// TODO cPairs = 0;

	for(int i=0; i<cPairs; i++) {
		pairs[i][0] = _pairs[i][0];
		pairs[i][1] = _pairs[i][1];
		score[i][0] = _score[i][0];
		score[i][1] = _score[i][1];
	}

	output(" ");
	output("###############");
	output(" ");
}

void VigenereAnalysisSchroedel::secondChar() {

	char actChar, lText, lKey, fText, fKey;
	int i,o,l,n,m;
	CString s, sText, sKey;
	int tDigramFactor, kDigramFactor;

	Pos2 = 0;
	Pos3 = 0;
	Remain2 = 0;
	Remain3 = 0;

	for(int n=1; n<3; n++) {
		actChar = this->theDialog->ciphertext[n];
		CString nStr; nStr.Format("%d", n+1);
		output(nStr + ". character of cipher: " + actChar);
		output("================");
		output("Possible pairs:");
		
		i=0;
		for(l=0; l<cPairs; l++) {
			s = "";
			for(o=0; o<26; o++) {
				fText = cPosAlphabet[o];
				fKey = cPosVigenere[cPosAlphabet.Find(actChar) + 26 - o];

				sText = _pairs[l][0];
				sKey = _pairs[l][1];

				if(l>=0) {
					lText = sText[sText.GetLength() - 1];
					lKey = sKey[sKey.GetLength() - 1];
			
					if(n == 1) {
						tDigramFactor = cDigram[cPosAlphabet.Find(sText)][cPosAlphabet.Find(fText)];
						kDigramFactor = cDigram[cPosAlphabet.Find(sKey)][cPosAlphabet.Find(fKey)];

						if(tDigramFactor == 0) {
							if(sText == 'A') tDigramFactor = 20;
							if(sText == 'I') tDigramFactor = 20;
							CString temp = "AM AN AS AT BE BY DO GO HE IF IN IS IT ME MY NO OF OK ON SO TO UP US";
							if(temp.Find(sText + fText) != -1) tDigramFactor = 100;
						}

						if(kDigramFactor == 0) {
							if(sKey == 'A') kDigramFactor = 20;
							if(sKey == 'I') kDigramFactor = 20;
							CString temp = "AM AN AS AT BE BY DO GO HE IF IN IS IT ME MY NO OF OK ON SO TO UP US";
							if(temp.Find(sKey + fKey) != -1) kDigramFactor = 100;
						}
					}

					if(n == 2) {
						tDigramFactor = cTrigram[cPosAlphabet.Find(sText[0])][cPosAlphabet.Find(sText[1])][cPosAlphabet.Find(fText)];
						kDigramFactor = cTrigram[cPosAlphabet.Find(sKey[0])][cPosAlphabet.Find(sKey[1])][cPosAlphabet.Find(fKey)];
			
						if(tDigramFactor == 0) {
							if(sText[0] == 'A') {
								CString temp = "AM AN AS AT BE BY DO GO HE IF IN IS IT ME MY NO OF OK ON SO TO UP US";
								if(temp.Find(sText[1] + fText) != -1) tDigramFactor = 100;
							}
							if(sText[0] == 'I') {
								CString temp = "AM AN AS AT BE BY DO GO HE IF IN IS IT ME MY NO OF OK ON SO TO UP US";
								if(temp.Find(sText[1] + fText) != -1) tDigramFactor = 100;
							}
							CString temp = "AM AN AS AT BE BY DO GO HE IF IN IS IT ME MY NO OF OK ON SO TO UP US";
							if(temp.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
						}

						if(kDigramFactor == 0) {
							if(sKey[0] == 'A') {
								CString temp = "AM AN AS AT BE BY DO GO HE IF IN IS IT ME MY NO OF OK ON SO TO UP US";
								if(temp.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
							}
							if(sKey[0] == 'I') {
								CString temp = "AM AN AS AT BE BY DO GO HE IF IN IS IT ME MY NO OF OK ON SO TO UP US";
								if(temp.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
							}
						}	
					}

					pairs[i][0] = sText + fText;
					pairs[i][1] = sKey + fKey;
					score[i][0] = tDigramFactor;
					score[i][1] = kDigramFactor;
				}				

				i++;

				s = s + sText + fText + "-" + sKey + fKey + " ";
			}

			output(s);
		}

		CString iStr; iStr.Format("%d", i);
		output("Count: " + iStr);
    cPairs = i;

		if(n == 1) {
			remain = cPairs;
			output("Remove dups:");
			for(l=0; l<cPairs-1; l++) {
				for(o=l+1; o<cPairs; o++) {
					if(pairs[l][0] == pairs[o][1]) {
						score[o][0] = -1;
						score[o][1] = -1;
					}
				}
			}

			s = "";
			i = 0;

			for(o=0; o<cPairs; o++) {
				if(score[o][0] == -1) {
					i++;
					remain--;
					s = s + pairs[o][0] + "-" + pairs[o][1] + " ";
				}
			}
			output(s);
			CString iStr; iStr.Format("%d", i);
			output("Count: " + iStr);
			CString remainStr; remainStr.Format("%d", remain);
			output("Remain: " + remainStr);

			setStatus("Deleting dups from internal list...");

			o = 0;
			for(int l=0; l<cPairs;l++) {
				if(score[l][0] != -1) {
					_pairs[o][0] = pairs[l][0];
					_pairs[o][1] = pairs[l][1];
					_score[o][0] = score[l][0];
					_score[o][1] = score[l][1];
					o++;
				}
			}

			for(int i=0; i<cPairs; i++) {
				pairs[i][0] = "";
				pairs[i][1] = "";
				score[i][0] = 0;
				score[i][1] = 0;
			}

			cPairs = o;

			for(int i=0; i<cPairs; i++) {
				pairs[i][0] = _pairs[i][0];
				pairs[i][1] = _pairs[i][1];
				score[i][0] = _score[i][0];
				score[i][1] = _score[i][1];
			}

			if(n == 1) Remain2 = cPairs;
		}

		setStatus("Sorting");
		for(int i=0; i<cPairs; i++) {
			for(int o=0; o<cPairs-1; o++) {
				if(score[o][0] + score[o][1] < score[o+1][0] + score[o+1][1]) {
					s = pairs[o][0];
					pairs[o][0] = pairs[o+1][0];
					pairs[o+1][0] = s;
					s = pairs[o][1];
					pairs[o][1] = pairs[o+1][1];
					pairs[o+1][1] = s;
					l = score[o][0];
					score[o][0] = score[o+1][0];
					score[o+1][0] = l;
					l = score[o][1];
					score[o][1] = score[o+1][1];
					score[o+1][1] = l;
				}
			}
		}

		setStatus("Sorting");
		for(int i=0; i<cPairs; i++) {
			for(int o=0; o<cPairs-1; o++) {
				if(score[o][0] + score[o][1] < score[o+1][0] + score[o+1][1]) {
					s = pairs[o][0];
					pairs[o][0] = pairs[o+1][0];
					pairs[o+1][0] = s;
					s = pairs[o][1];
					pairs[o][1] = pairs[o+1][1];
					pairs[o+1][1] = s;
					l = score[o][0];
					score[o][0] = score[o+1][0];
					score[o+1][0] = l;
					l = score[o][1];
					score[o][1] = score[o+1][1];
					score[o+1][1] = l;
				}
			}
		}

		output("Sorted list by score - all remaining");
		s = "";
		for(int i=0; i<cPairs; i++) {
			CString score1Str; score1Str.Format("%d", score[i][0]);
			CString score2Str; score2Str.Format("%d", score[i][1]);
			s = pairs[i][0] + "-" + pairs[i][1] + "/" + score1Str + "-" + score2Str + " ";
			output(s);
		}

		// weight and sort
		o = 0;

		if(n == 1) {
			maxProzent = 10;
		}
		if(n == 2) {
			maxProzent = 10;
		}

		setStatus("Discard underperformer");
		for(int l=0; l<cPairs; l++) {
			// sort out
			if(score[l][0] >= maxProzent && score[l][1] >= maxProzent) {
				_pairs[o][0] = pairs[l][0];
				_pairs[o][1] = pairs[l][1];
				_score[o][0] = score[l][0];
				_score[o][1] = score[l][1];
				o++;
			}
		}

		for(int i=0; i<cPairs; i++) {
			pairs[i][0] = "";
			pairs[i][1] = "";
			score[i][0] = 0;
			score[i][1] = 0;
		}

		cPairs = o;

		for(int i=0; i<cPairs; i++) {
			pairs[i][0] = _pairs[i][0];
			pairs[i][1] = _pairs[i][1];
			score[i][0] = _score[i][0];
			score[i][1] = _score[i][1];
		}

		if(n == 1) Remain2 = cPairs;

		setStatus("Sorting");

		for(int i=0; i<cPairs; i++) {
			for(int o=0; o<cPairs-1; o++) {
				if(score[o][0] + score[o][1] < score[o+1][0] + score[o+1][1]) {
					s = pairs[o][0];
					pairs[o][0] = pairs[o+1][0];
					pairs[o+1][0] = s;
					s = pairs[o][1];
					pairs[o][1] = pairs[o+1][1];
					pairs[o+1][1] = s;
					l = score[o][0];
					score[o][0] = score[o+1][0];
					score[o+1][0] = l;
					l = score[o][1];
					score[o][1] = score[o+1][1];
					score[o+1][1] = l;
				}
			}
		}

		output("Sorted list by score - after discarding");
		s = "";

		for(int i=0; i<cPairs; i++) {
			CString score1Str; score1Str.Format("%d", score[i][0]);
			CString score2Str; score2Str.Format("%d", score[i][1]);
			s = pairs[i][0] + "-" + pairs[i][1] + "/" + score1Str + "-" + score2Str + " ";
			output(s);
		}

		output("Scorers in leading digram/trigram statistic - sorted");
		s = "";
		aktPos = 0;

		for(int o=0; o<cPairs; o++) {
			// *** TODO *** CHECK THIS SECTION!!!! (THINK ABOUT THE "n+1" THINGY)
			if(pairs[o][0].MakeUpper() == this->theDialog->plaintext.Left(n+1).MakeUpper()) aktPos = o;
			if(pairs[o][0].MakeUpper() == this->theDialog->ciphertext.Left(n+1).MakeUpper()) aktPos = o;
			CString oStr; oStr.Format("%d", o);
			s = s + oStr + ". " + pairs[o][0] + "-" + pairs[o][1] + " ";
		}

		if(n == 1) Pos2 = aktPos;
		if(n == 2) Pos3 = aktPos;

		output(s);
		CString cPairsStr; cPairsStr.Format("%d", cPairs);
		output("Remain: " + cPairsStr);
		Remain3 = cPairs;

		// print current position
		if(!this->theDialog->plaintext.IsEmpty()) {
			CString aktPosStr; aktPosStr.Format("%d", aktPos);
			output("Current position in ranking: " + aktPosStr);
		}

		output("########################");
	}

		/* TODO ********** OUTPUT ***************


  outPut( Form1.cipher.Text );
  outPut( AnsiUpperCase( Form1.plainText.Text ));
  output( AnsiUpperCase( Form1.cipherKey.Text ));
  output( 'Length : ' + IntToStr( Length( form1.cipher.Text )));
  output( 'Digram : ' + inttoStr( pos2 ) + '/' + inttoStr( remain2 ));
  output( 'Trigram: ' + inttoStr( pos3 ) + '/' + inttoStr( remain3 ));

  outputSave( Form1.cipher.Text,
              AnsiUpperCase( Form1.plainText.Text ),
              AnsiUpperCase( Form1.cipherKey.Text ),
              inttoStr( pos2 ),
              inttoStr( remain2 ),
              inttoStr( pos3 ),
              inttoStr( remain3 ));

  form1.listbox1.Items.Add( inttoStr( pos2 ) +'/' +
              inttoStr( remain2 ) + ' -- ' +
              inttoStr( pos3 ) + '/' +
              inttoStr( remain3 ));

  form1.ListBox1.Selected[ form1.ListBox1.Items.Count -1 ] := TRUE;


End;


		*/
}

void VigenereAnalysisSchroedel::solveTrigram() {
	
	CString s;
	CString key, text, cipher;
	CString cKey, cText;
	CString rKey, rText;

	int x = 0;
	int theRate = 0;

	bool found = false;

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
		cipher = theDialog->ciphertext;

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



		if(cKey.GetLength() > 0 && cText.GetLength() > 0) {
			for(int o=0; o<cKey.GetLength(); o++) {
				for(int l=0; l<cText.GetLength(); l++) {
					CString cTextStr; cTextStr.AppendChar(cText[l]);
					CString cKeyStr; cKeyStr.AppendChar(cKey[o]);
					CString cCipherStr; cCipherStr.AppendChar(cipher[3]);
					if(encryptText(cTextStr, cKeyStr) == cCipherStr) {
						rKey = "";
						rText = "";
						for(xDict=0; xDict<dictCount; xDict++) {
							if(dict[xDict].GetLength() <= this->theDialog->ciphertext.GetLength()) {
								if(dict[xDict].Find(key + cKey[o]) == 0 || dict[xDict].Find(text + cText[l]) == 0) {
									theRate = rateString(decryptText(this->theDialog->ciphertext, dict[xDict]), dict[xDict]);
									if(theRate >= decryptText(this->theDialog->ciphertext, dict[xDict]).GetLength() * 0.01) {
										
										CString strTheRate; strTheRate.Format("%d", theRate);
										CString strTheSubRate; strTheSubRate = "0";

										CString outputStr;
										outputStr += "-----> [";
										outputStr.AppendChar(cKey[o]);
										outputStr += "]+[";
										outputStr.AppendChar(cText[l]);
										outputStr += "]=";
										outputStr.AppendChar(cipher[3]);
										outputStr += " => ";
										outputStr.Append(key);
										outputStr.AppendChar(cKey[o]);
										outputStr += " / ";
										outputStr.Append(text);
										outputStr.AppendChar(cText[l]);
										outputStr += " => ";
										outputStr.Append(dict[xDict]);
										outputStr += " <=> ";
										outputStr.Append(decryptText(this->theDialog->ciphertext, dict[xDict]));
										outputStr += " (";
										outputStr.Append(strTheRate);
										outputStr += ")";

										output(outputStr);
										
										solvers[x][0] = dict[xDict];
										solvers[x][1] = decryptText(this->theDialog->ciphertext, dict[xDict]);
										solvers[x][2] = strTheRate;
                    solvers[x][3] = strTheSubRate;
										x++;
										
										if(maxRating < theRate) maxRating = theRate;

										if(theRate >= 10) {
											output("-------> Key (Rate " + strTheRate + "): " + dict[xDict] + " = " + decryptText(this->theDialog->ciphertext, dict[xDict]));
											output("### POSSIBLE SOLVER ###");
										}
									}
								}
							}
							if(found) break;
						}
						if(found) break;
					}
					if(found) break;
				}
				if(found) break;
			}
			if(found) break;
		}
	}

	// TODO: endezeit = Date + Time
	if(!found) {
		output(" ");
		output("Checking all possible solutions with dictionary for heighest rating:");
		output(" ");
		output("############################################");
		output("HIGHEST RATING");
		output("############################################");
		CString strLength; strLength.Format("%d", this->theDialog->ciphertext.GetLength());
		CString strCipher; strCipher = this->theDialog->ciphertext;
		CString strRating; strRating.Format("%d", maxRating);
		for(int i=0; i<x; i++) {
			if(solveRating < atoi(solvers[i][2].GetBuffer())) {
				solveRating = atoi(solvers[i][2].GetBuffer());
				solveKey = solvers[i][0];
				solveText = solvers[i][1];
			}
			if(maxRating == atoi(solvers[i][2])) {
				output(solvers[i][3] + " " + solvers[i][0] + " / " + solvers[i][1]);
			}
		}

		for(int i=0; i<cPairs; i++) {
			key = pairs[i][0];
			text = pairs[i][1];

			if(solveKey.Find(key) == 0 || solveText.Find(key) == 0) {
				output(" ");
				CString iStr; iStr.Format("%d", i);
				output("Position after sorting was: " + iStr);
			}
		}

		// TODO		output( 'TIME: ' + formatDateTime( 'nn:ss', endezeit - startzeit ));

		for(int i=0; i<x; i++) {
			if(solvers[i][0] == this->theDialog->ciphertext) {
				solveKey = solvers[i][0];
			}
			if(solvers[i][1] == this->theDialog->ciphertext) {
				solveKey = solvers[i][1];
			}
		}
    output(" ");
	}

	// TODO: see original delphi code

}

void VigenereAnalysisSchroedel::readDict() {

	setStatus("Reading dictionary");

	CString s;

	// create a handle for the input file
	std::ifstream fileInput;
	CString pathToDictionary;
	pathToDictionary = Pfad;
	pathToDictionary += "dict.txt";
	fileInput.open(pathToDictionary);
	if(!fileInput) return;

	dictCount = 0;

	while(!fileInput.eof()) {
		std::string s2;
		getline(fileInput, s2);
		s = s2.c_str();
		s.Trim();
		s.MakeUpper();
		if(s.Find('%') == -1) {
			for(int i=s.GetLength(); i>0; i--) {
				CString temp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
				if(temp.Find(s[i]) == -1) {
					s.Delete(i);
					s.Insert(i, ' ');
				}
			}
		}
		if(!s.IsEmpty()) {
			dict[dictCount++] = s.Trim();
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
			if(key[i] == vigenere[o][0]) {
				// TODO flomar encryptedText = encryptedText + vigenere[o + klartext.Find(text[i])];
				encryptedText.AppendChar(vigenere[o][klartext.Find(text[i])]);
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
				decryptedText = decryptedText + klartext[vigenere[o].Find(text[i])];
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
			words[o++] = s;
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