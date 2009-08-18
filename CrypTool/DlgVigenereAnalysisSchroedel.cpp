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

// for file locations relative to CrypTool
extern char *Pfad;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/****************************************
		BEGIN VIGENERE ANALYSIS SCHROEDEL
****************************************/

const CString cPosAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const CString cPosVigenere = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
const CString klartext     = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const CString alphabet     = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";

VigenereAnalysisSchroedel::VigenereAnalysisSchroedel(const CString _ciphertextFileName, const CString _title) {

	ciphertextFileName = _ciphertextFileName;
	title = _title;

	abort = false;

	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);

	// some init stuff
	memset(cDigram, 0, 4*26*26);
	memset(cTrigram, 0, 4*26*26*26);
	memset(score, 0, 4*26*26*26*2);
	memset(_score, 0, 4*26*26*26*2);

	// fill Vigenere array
	CString s;
	CString t;
	s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  s = s + s;
	for(int i=0; i<26; i++) {
		t = s;
		t.Delete(0, i+1);
		vigenere[i] = t.Left(26);
	}

	maxRating = 0;
	solveCount = 0;

	for(int i=0; i<17575; i++) {
		pairs[i][0] = "";
		pairs[i][1] = "";
		score[i][0] = 0;
		score[i][1] = 0;
	}
}

VigenereAnalysisSchroedel::~VigenereAnalysisSchroedel() {
	
}

void VigenereAnalysisSchroedel::setStatus(CString str) {
	
	// TODO

}

void VigenereAnalysisSchroedel::output(CString str) {
	
	result.Append(str);
	result.Append("\r\n");

}

int VigenereAnalysisSchroedel::readTriDigrams() {
	
	// watch out for user cancellation
	if(abort) return -1;

	CString s;

	maxDi = 0;
	setStatus("Loading Digrams...");

	// create a handle for the input file
	std::ifstream fileInputDigrams;
	CString pathToDigrams;
	pathToDigrams.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
	pathToDigrams = CString(Pfad) + pathToDigrams;
	fileInputDigrams.open(pathToDigrams);
	if(!fileInputDigrams) return -1;

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
	pathToTrigrams.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
	pathToTrigrams = CString(Pfad) + pathToTrigrams;
	fileInputTrigrams.open(pathToTrigrams);
	if(!fileInputTrigrams) return -1;
	
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

	progress = 0.10;

	return 0;
}

int VigenereAnalysisSchroedel::firstChar() {
	
	// watch out for user cancellation
	if(abort) return -1;

	char actChar;
	char fText, fKey;
	CString s;
	int i, o;

	setStatus("Create all pairs for the first cipher");
	actChar = ciphertext[0];
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

	progress = 0.12;

	return 0;
}

int VigenereAnalysisSchroedel::secondChar() {

	// watch out for user cancellation
	if(abort) return -1;

	char actChar, lText, lKey, fText, fKey;
	int i,o,l,n,m;
	CString s, sText, sKey;
	int tDigramFactor, kDigramFactor;

	Pos2 = 0;
	Pos3 = 0;
	Remain2 = 0;
	Remain3 = 0;

	for(int n=1; n<3; n++) {
		actChar = ciphertext[n];
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
				if(score[o][0] * score[o][1] < score[o+1][0] * score[o+1][1]) {
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
				if(score[o][0] * score[o][1] < score[o+1][0] * score[o+1][1]) {
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
			//if(pairs[o][0].MakeUpper() == plaintext.Left(n+1).MakeUpper()) aktPos = o;
			if(pairs[o][0].MakeUpper() == ciphertext.Left(n+1).MakeUpper()) aktPos = o;
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
		/*if(!plaintext.IsEmpty()) {
			CString aktPosStr; aktPosStr.Format("%d", aktPos);
			output("Current position in ranking: " + aktPosStr);
		}*/

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

	progress = 0.15;

	return 0;
}

int VigenereAnalysisSchroedel::solveTrigram() {

	// watch out for user cancellation
	if(abort) return -1;

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

	/* 
		ATTENTION: In order to display the analysis progress, we assume that 
		up until this point, 15% of the analysis is finished; furthermore we 
		assume that AFTER the following loop, 90% of the analysis is finished; 
		therefore, the loop covers 75% of the overall analysis,	the progress 
		is gradually increased with each loop (see loopProgress)
	*/
	const double loopProgress = (double)(0.75) / (double)(cPairs); 

	for(int i=0; i<cPairs; i++, progress += loopProgress) {
		
		// watch out for user cancellation
		if(abort) return -1;
		
		key = pairs[i][0];
		text = pairs[i][1];
		cipher = ciphertext;

    // Try first key
    cKey = "";
    cText = "";
    setStatus("Reading dictionary");

		for(xDict=0; xDict<dictCount; xDict++) {

			// watch out for user cancellation
			if(abort) return -1;

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
					
					// watch out for user cancellation
					if(abort) return -1;
					
					CString cTextStr; cTextStr.AppendChar(cText[l]);
					CString cKeyStr; cKeyStr.AppendChar(cKey[o]);
					CString cCipherStr; cCipherStr.AppendChar(cipher[3]);
					if(encryptText(cTextStr, cKeyStr) == cCipherStr) {
						rKey = "";
						rText = "";
						for(xDict=0; xDict<dictCount; xDict++) {

							// watch out for user cancellation
							if(abort) return -1;

							if(dict[xDict].GetLength() <= ciphertext.GetLength()) {
								if(dict[xDict].Find(key + cKey[o]) == 0 || dict[xDict].Find(text + cText[l]) == 0) {
									theRate = rateString(decryptText(ciphertext, dict[xDict]), dict[xDict]);
									if(theRate >= decryptText(ciphertext, dict[xDict]).GetLength() * 0.01) {
										
										// watch out for user cancellation
										if(abort) return -1;

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
										outputStr.Append(decryptText(ciphertext, dict[xDict]));
										outputStr += " (";
										outputStr.Append(strTheRate);
										outputStr += ")";

										output(outputStr);
										
										solvers[x][0] = dict[xDict];
										solvers[x][1] = decryptText(ciphertext, dict[xDict]);
										solvers[x][2] = strTheRate;
                    solvers[x][3] = strTheSubRate;
										x++;
										
										if(maxRating < theRate) maxRating = theRate;

										if(theRate >= 10) {
											output("-------> Key (Rate " + strTheRate + "): " + dict[xDict] + " = " + decryptText(ciphertext, dict[xDict]));
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
		CString strLength; strLength.Format("%d", ciphertext.GetLength());
		CString strCipher; strCipher = ciphertext;
		CString strRating; strRating.Format("%d", maxRating);
		for(int i=0; i<x; i++) {

			// watch out for user cancellation
			if(abort) return -1;

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
			if(solvers[i][0] == ciphertext) {
				solveKey = solvers[i][0];
			}
			if(solvers[i][1] == ciphertext) {
				solveKey = solvers[i][1];
			}
		}
    output(" ");
	}

	// TODO: see original delphi code

	return 0;
}

int VigenereAnalysisSchroedel::readDict() {

	// watch out for user cancellation
	if(abort) return -1;

	setStatus("Reading dictionary");

	CString s;

	// create a handle for the input file
	std::ifstream fileInput;
	CString pathToDictionary;
	pathToDictionary.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
	pathToDictionary = CString(Pfad) + pathToDictionary;
	fileInput.open(pathToDictionary);
	if(!fileInput) return -1;

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

	progress = 0.05;

	return 0;
}

int VigenereAnalysisSchroedel::readCiphertext() {

	// watch out for user cancellation
	if(abort) return -1;

	setStatus("Reading ciphertext");

	CString s;

	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open(ciphertextFileName);
	if(!fileInput) return -1;

	dictCount = 0;

	while(!fileInput.eof()) {
		std::string s2;
		getline(fileInput, s2);
		s = s2.c_str();
		s.Trim();
		ciphertext.Append(s);
	}

	// close input file
	fileInput.close();

	ciphertext.MakeUpper();

	output("Cipher to break: " + ciphertext);
	output(" ");

	// if necessary, indicate that the ciphertext is shorter than three characters
	if(ciphertext.GetLength() < 3) return -1;

	progress = 0.01;

	return 0;
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
				// make sure we don't run into segmentation faults when the find process was not successful
				if(klartext.Find(text[i]) != -1) {
					encryptedText.AppendChar(vigenere[o][klartext.Find(text[i])]);
				}
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
			// FLOMAR TODO CHANGE **********
			if(key[i] == vigenere[o][0]) {
				// make sure we don't run into segmentation faults when the find process was not successful
				if(vigenere[o].Find(text[i]) != -1) {
					decryptedText = decryptedText + klartext[vigenere[o].Find(text[i])];
				}
			}
		}
	}

	return decryptedText;
}

int VigenereAnalysisSchroedel::rateString(CString str, CString key) {

	CString s, tmp, start;

	int o = 0;
	int z = 0;

	int check[1000];
	CString words[1000];
	CString match[100][5];

	// check the first 100 characters only
	if(str.GetLength() > 100) {
		str = str.Left(100);
	}

	// find all words matching somehow
	for(int i=0; i<1000; i++) {
		words[i] = "";
		check[i] = 0;
	}

	for(int i=0; i<dictCount; i++) {
		s = dict[i];
		if(str.Find(s) > -1) {
			words[o++] = s;
		}
	}

	for(int i=0; i<o; i++) {
		tmp = str;
		do {
			if(tmp.Find(words[i]) > -1) {
				z = tmp.Find(words[i]);
				for(int l=0; l<words[i].GetLength(); l++) {
					// + l - 1 entfernt
					check[tmp.Find(words[i]) + l]++;
				}
				for(int l=0; l<words[i].GetLength(); l++) {
					// + l - 1 entfernt (2x)
					tmp.Delete(z + l, 1);
					tmp.Insert(z + l, '~');
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
			CString iStr; iStr.Format("%d", check[i]);
			start.Append(iStr);
		}
		else {
			start.Append(" ");
		}

		if(check[i] == 0) {
			o -= 2;
		}
		if(check[i] > 0) {
			o += 1;
		}
	
	}

	// TODO flomar: this statement seems to cause problems for the debugger (WTF?)
	if(o > maxRating) {
		solveRating = 0;
		solveText = "";
		solveKey = "";
		solveCount = 0;
	}

	// TODO flomar: this statement seems to cause problems for the debugger (WTF?)
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

void VigenereAnalysisSchroedel::writeResultFile() {

	// open result file
	std::ofstream fileResult;
	CString pathToFileResult;
	pathToFileResult = Pfad;
	pathToFileResult += "result.txt";
	fileResult.open(pathToFileResult, ios_base::trunc);
	if(!fileResult) return; // TODO error message

	fileResult.write(result.GetBuffer(), result.GetLength());
	fileResult.write("\r\n", 2);

	// close result file
	fileResult.close();

}

/****************************************
		END VIGENERE ANALYSIS SCHROEDEL
		****************************************/

// the actual analysis function (to be run in a separate thread)
UINT singleThreadVigenereAnalysisSchroedel(PVOID argument) {

	VigenereAnalysisSchroedel *theAnalysis = (VigenereAnalysisSchroedel*)(argument);

	// return if we don't have a valid analysis object
	if(!theAnalysis) {
		theApp.fs.cancel();
		AfxEndThread(0);
		return 0;
	}

	if(	theAnalysis->readCiphertext() < 0 ||					// read ciphertext
			theAnalysis->readDict() < 0 ||								// read dictionary
			theAnalysis->readTriDigrams() < 0 ||					// read digrams and trigrams file
			theAnalysis->firstChar() < 0 ||								// create pairs for first character
			theAnalysis->secondChar() < 0 ||							// create pairs for second and third character
			theAnalysis->solveTrigram() < 0)							// solve trigrams
	{
		// abort analysis and end thread properly
		theAnalysis->writeResultFile();
		theApp.fs.cancel();
		AfxEndThread(0);
		return 0;
	}
		
	// at this point the solveTrigram function was successful, so we're done
	theAnalysis->progress = 1.0;	

	// end thread properly
	theAnalysis->writeResultFile();
	theApp.fs.cancel();
	delete theAnalysis;
	AfxEndThread(0);
	return 0;
}