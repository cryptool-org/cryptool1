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
		
		// TODO if not shortRun.checked Then solveTrigram;
		// TODO Memo1.Lines.SaveToFile("result.txt");

	}
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
		while(t.Find(' ') != -1) {
			t.Delete(t.Find(' '), 1);
			s = s + " " + t.Trim();
		}
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

	while(s.Find(' ') != - 1) {
		// do autorun
		do {
			
			k.Delete(0, k.Find(' '));
			k.Delete(k.Find(' '), 100);

			k = (char*)(p.GetBuffer()) + rand() % p.GetLength();
			k.Delete(50, k.GetLength() - 50);
			k.Delete(0, k.Find(' '));
			k.Delete(k.Find(' '), 100);
			k.Trim();

		} while(k.GetLength() < 5);
	}

	k = theAnalysis->dict[rand() % theAnalysis->dictCount];

	t = s;
	t.Delete(20, t.GetLength() - 20);

	// only full words
	while(t[t.GetLength()] != ' ') {
		t.Delete(t.GetLength(), 1);
	}
	t.Trim();

	ciphertext = "";

	// TODO progressbar1.Position := o - Length( s );

	theAnalysis->setStatus("Autorun: " + k + "/" + t);

	if(k.GetLength() > 4 && s.Find(' ') > 2) {
		plaintext = t;
		key = k;
		OnBnClickedButton1();
	}

	s.Delete(0, s.Find(' '));
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

		s = s + fText + '-' + fKey + (char)(9);
		o++;
		pairs[o][0] = fText;
		pairs[o][1] = fKey;
		score[o][0] = 0;
		score[o][1] = 0;
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
			}
		}
	}

	s = "";
	i = 0;

	for(o=0; o<cPairs; o++) {
		if(score[o][0] == -1) {
			i++;
			s = s + pairs[o][0] + "-" + pairs[o][1] + (char)(9);
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
		}
	}

	for(int i=0; i<cPairs; i++) {
		pairs[i][0] = "";
		pairs[i][1] = "";
		score[i][0] = 0;
		score[i][1] = 0;
	}

	cPairs = 0;

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

				if(l>0) {
					lText = sText[sText.GetLength()];
					lKey = sKey[sKey.GetLength()];
			
					if(n == 2) {
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

					if(n == 3) {
						tDigramFactor = cTrigram[cPosAlphabet.Find(sText[0])][cPosAlphabet.Find(sText[1])][cPosAlphabet.Find(fText)];
						kDigramFactor = cTrigram[cPosAlphabet.Find(sKey[0])][cPosAlphabet.Find(sKey[1])][cPosAlphabet.Find(fKey)];
			
						if(tDigramFactor = 0) {
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

				s = s + sText + fText + "-" + sKey + fKey + (char)(9);
			}

			output(s);
		}

		CString iStr; iStr.Format("%d", i);
		output("Count: " + iStr);
    cPairs = i;

		if(n == 2) {
			remain = cPairs;
			output("Remove dups:");
			for(l=0; l<cPairs; l++) {
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
					s = s + pairs[o][0] + "-" + pairs[o][1] + (char)(9);
				}
			}
			output(s);
			CString iStr; iStr.Format("%d", i);
			output("Count: " + iStr);
			CString remainStr; remainStr.Format("%d", remain-i);
			output("Remain: " + remainStr);

			setStatus("Deleting dups from internal list...");

			o = 0;
			for(int l=0; l<cPairs;l++) {
				if(score[l][0] != -1) {
					o++;
					_pairs[o][0] = pairs[l][0];
					_pairs[o][1] = pairs[l][1];
					_score[o][0] = _score[l][0];
					_score[o][1] = _score[l][1];
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

			if(n == 2) Remain2 = cPairs;
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
			s = s + pairs[i][0] + "-" + pairs[i][1] + "/" + score1Str + "-" + score2Str + (char)(9);
			output(s);
		}

		// weight and sort
		o = 0;

		if(n == 2) {
			maxProzent = 10;
		}
		if(n == 3) {
			maxProzent = 10;
		}

		setStatus("Discard underperformer");
		for(int l=0; l<cPairs; l++) {
			// sort out
			if(score[l][0] >= maxProzent && score[l][1] >= maxProzent) {
				o++;
				_pairs[o][0] = pairs[l][0];
				_pairs[o][1] = pairs[l][1];
				_score[o][0] = score[l][0];
				_score[o][1] = score[l][1];
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

		if(n == 2) Remain2 = cPairs;

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
			CString score1Str; score1Str.Format(score[i][0]);
			CString score2Str; score2Str.Format(score[i][1]);
			s = s + pairs[i][0] + "-" + pairs[i][1] + "/" + score1Str + "-" + score2Str + (char)(9);
			output(s);
		}

		output("Scorers in leading digram/trigram statistic - sorted");
		s = "";
		aktPos = 0;

		for(int o=0; o<cPairs; o++) {
			// TODO If AnsiUpperCase( pairs[o,1]) = AnsiUpperCase( Copy( Form1.plainText.Text, 1, n )) Then aktPos := o;
      // TODO If AnsiUpperCase( pairs[o,1]) = AnsiUpperCase( Copy( Form1.cipherKey.Text, 1, n )) Then aktPos := o;
			// TODO s := s + inttostr(o) + '. ' + pairs[o, 1] + '-' + pairs[o, 2] + #9;
		}

		if(n == 2) Pos2 = aktPos;
		if(n == 3) Pos3 = aktPos;

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
		s.MakeUpper();
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