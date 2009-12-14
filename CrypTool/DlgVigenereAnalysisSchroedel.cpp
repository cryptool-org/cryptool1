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
#include "CrypToolTools.h"
#include "FileTools.h"

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
	debug = false;

	// create result file name
	char pathToFileResult[CRYPTOOL_PATH_LENGTH];
	GetTmpName(pathToFileResult, "cry", ".txt");
	resultFileName = pathToFileResult;

	// read analysis settings from registry
	readSettingsFromRegistry();

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

void VigenereAnalysisSchroedel::output(CString str, const bool _debug) {
	
	if(_debug || debug) result.Append(CString(str) + CString("\n"));

}

int VigenereAnalysisSchroedel::readTriDigrams() {
	
	// watch out for user cancellation
	if(abort) return -1;

	CString s;

	maxDi = 0;

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_LOADING_DIGRAMS);
	output(outputString);

	// create a handle for the input file
	std::ifstream fileInputDigrams;
	fileInputDigrams.open(pathToDigrams);
	if(!fileInputDigrams) {
		// display an info message that the file could not be opened
		CString infoMessage;
		infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
		infoMessage.Append(pathToDigrams);
		MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
		return -1;
	}

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

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_LOADING_TRIGRAMS);
	output(outputString);

	// create a handle for the input file
	std::ifstream fileInputTrigrams;
	fileInputTrigrams.open(pathToTrigrams);
	if(!fileInputTrigrams) {
		// display an info message that the file could not be opened
		CString infoMessage;
		infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
		infoMessage.Append(pathToTrigrams);
		MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
		return -1;
	}
	
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

	actChar = ciphertext[0];
	
	output("");

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_1ST_CHARACTER_OF_CIPHER);
	outputString.AppendChar(actChar);
	output(outputString);

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

	// output possible pairs
	formatString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_POSSIBLE_PAIRS);
	outputString.Format(formatString, o);
	output(outputString);
	output(s);

	remain = cPairs;

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

	// output removed duplicates
	formatString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_REMOVE_DUPLICATES);
	outputString.Format(formatString, i);
	output(outputString);
	output(s);

	// output remaining count (number of pairs that were not removed)
	formatString.Format("%d", remain);
	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_REMAINING);
	outputString.Append(formatString);
	output(outputString);

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

	for(int i=0; i<cPairs; i++) {
		pairs[i][0] = _pairs[i][0];
		pairs[i][1] = _pairs[i][1];
		score[i][0] = _score[i][0];
		score[i][1] = _score[i][1];
	}

	progress = 0.12;

	return 0;
}

int VigenereAnalysisSchroedel::secondChar() {

	// watch out for user cancellation
	if(abort) return -1;

	char actChar, lText, lKey, fText, fKey;
	int i,o,l;
	CString s, sText, sKey;
	int tDigramFactor, kDigramFactor;

	Pos2 = 0;
	Pos3 = 0;
	Remain2 = 0;
	Remain3 = 0;

	// the following string contains a few selected digrams for improving the effect of 
	// the digram factor (see below); originally, these were hard-coded for English only; 
	// we now use a language-dependent resource strings instead
	CString digramFactorString;
	digramFactorString.LoadString(IDS_STRING_VIGENERE_ANALYSIS_DIGRAM_FACTOR_STRING);

	for(int n=1; n<3; n++) {
		actChar = ciphertext[n];

		output("");

		if(n == 1) outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_2ND_CHARACTER_OF_CIPHER);
		if(n == 2) outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_3RD_CHARACTER_OF_CIPHER);
		outputString.AppendChar(actChar);
		output(outputString);

		CString temp;

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
							if(digramFactorString.Find(sText + fText) != -1) tDigramFactor = 100;
						}

						if(kDigramFactor == 0) {
							if(sKey == 'A') kDigramFactor = 20;
							if(sKey == 'I') kDigramFactor = 20;
							if(digramFactorString.Find(sKey + fKey) != -1) kDigramFactor = 100;
						}
					}

					if(n == 2) {
						tDigramFactor = cTrigram[cPosAlphabet.Find(sText[0])][cPosAlphabet.Find(sText[1])][cPosAlphabet.Find(fText)];
						kDigramFactor = cTrigram[cPosAlphabet.Find(sKey[0])][cPosAlphabet.Find(sKey[1])][cPosAlphabet.Find(fKey)];
			
						if(tDigramFactor == 0) {
							if(sText[0] == 'A') {
								if(digramFactorString.Find(sText[1] + fText) != -1) tDigramFactor = 100;
							}
							if(sText[0] == 'I') {
								if(digramFactorString.Find(sText[1] + fText) != -1) tDigramFactor = 100;
							}
							if(digramFactorString.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
						}

						if(kDigramFactor == 0) {
							if(sKey[0] == 'A') {
								if(digramFactorString.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
							}
							if(sKey[0] == 'I') {
								if(digramFactorString.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
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

			temp.Append(s);
		}

    cPairs = i;

		// output possible pairs
		formatString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_POSSIBLE_PAIRS);
		outputString.Format(formatString, i);
		output(outputString);
		output(temp);

		if(n == 1) {
			remain = cPairs;

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

			// output removed duplicates
			formatString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_REMOVE_DUPLICATES);
			outputString.Format(formatString, i);
			output(outputString);
			output(s);

			// output remaining count (number of pairs that were not removed)
			formatString.Format("%d", remain);
			outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_REMAINING);
			outputString.Append(formatString);
			output(outputString);

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

		// sorting
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

		output("");

		outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_SORTED_LIST_ALL_REMAINING);
		output(outputString);

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

		// discard underperformer
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

		// sorting
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

		output("");

		outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_SORTED_LIST_AFTER_DISCARDING);
		output(outputString);
		
		s = "";

		for(int i=0; i<cPairs; i++) {
			CString score1Str; score1Str.Format("%d", score[i][0]);
			CString score2Str; score2Str.Format("%d", score[i][1]);
			s = pairs[i][0] + "-" + pairs[i][1] + "/" + score1Str + "-" + score2Str + " ";
			output(s);
		}

		output("");
		
		outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_SORTED_LEADERS);
		output(outputString);

		s = "";
		aktPos = 0;

		for(int o=0; o<cPairs; o++) {
			if(pairs[o][0].MakeUpper() == ciphertext.Left(n+1).MakeUpper()) aktPos = o;
			CString oStr; oStr.Format("%d", o+1);
			s = s + oStr + ". " + pairs[o][0] + "-" + pairs[o][1] + " ";
		}

		if(n == 1) Pos2 = aktPos;
		if(n == 2) Pos3 = aktPos;

		output(s);

		CString cPairsStr; cPairsStr.Format("%d", cPairs);

		outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_REMAINING);
		outputString.Append(cPairsStr);
		output(outputString);

		Remain3 = cPairs;
	}

	output("");  

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

	CString decryptedText;

	for(int i=0; i<cPairs; i++, progress += loopProgress) {
		
		// watch out for user cancellation
		if(abort) return -1;
		
		key = pairs[i][0];
		text = pairs[i][1];
		cipher = ciphertext;

    // Try first key
    cKey = "";
    cText = "";

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
									decryptedText = decryptText(ciphertext, dict[xDict]);
									theRate = rateString(decryptedText, dict[xDict]);
									if(theRate >= decryptedText.GetLength() * 0.01) {
										
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

										// ATTENTION: the "analysisThreshold" variable can be configured via the 
										// CrypTool analysis options dialog. The LOWER the the threshold, the MORE 
										// possible solutions will be found (this was introduced due to problems with 
										// German texts). See Schroedel's paper for details, although a variable 
										// threshold was not part of his code.
										//
										// TODO: make sure the user cannot use unreasonable values to mess up anything
										//
										if(theRate >= analysisThreshold) {
											PossibleResult possibleResult;
											possibleResult.key = dict[xDict];
											possibleResult.cleartext = decryptText(ciphertext, dict[xDict]);
											possibleResult.rating = theRate;
											// at this point we have a possible result, store it in the list for possible results
											listPossibleResults.push_back(possibleResult);
											// suggest the possible result to the user (including the first 50 characters of 
											// the corresponing cleartext) and abort the analysis if the user decides to
											CString formatString;
											formatString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_SUGGEST_RESULT);
											CString suggestion;
											suggestion.Format(formatString, possibleResult.key, possibleResult.cleartext.Left(50));
											if(AfxMessageBox(suggestion, MB_YESNO) == IDYES) {
												found = true;
											}
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

	if(!found) {
		output("");

		outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_CHECKING_FOR_RATINGS);
		output(outputString);

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
				//output(solvers[i][3] + " " + solvers[i][0] + " / " + solvers[i][1]);
				output(solvers[i][0] + " / " + solvers[i][1]);
			}
		}

		for(int i=0; i<cPairs; i++) {
			key = pairs[i][0];
			text = pairs[i][1];
		}

		for(int i=0; i<x; i++) {
			if(solvers[i][0] == ciphertext) {
				solveKey = solvers[i][0];
			}
			if(solvers[i][1] == ciphertext) {
				solveKey = solvers[i][1];
			}
		}
    output("");
	}

	// this is the official end of the analysis
	time(&timeAnalysisEnd);

	time_t timeNeededForAnalysisInSeconds = timeAnalysisEnd - timeAnalysisStart;

	// dump a header (describing the analysis)
	CString analysisHeaderTag;
	analysisHeaderTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_HEADER_TAG);
	output(analysisHeaderTag, true);

	// dump the time needed for analysis
	CString analysisTimeNeededTag;
	analysisTimeNeededTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TIME_NEEDED_TAG);
	CString unitSeconds;
	unitSeconds.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_UNIT_SECONDS);
	CString analysisTimeNeeded;
	analysisTimeNeeded.Append(analysisTimeNeededTag);
	CString analysisTime;
	analysisTime.Format("%d", timeNeededForAnalysisInSeconds);
	analysisTimeNeeded.Append(analysisTime);
	analysisTimeNeeded.Append(unitSeconds);
	output(analysisTimeNeeded, true);

	// dump the length of the analyzed ciphertext
	CString ciphertextLengthTag;
	ciphertextLengthTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_CIPHERTEXT_LENGTH_TAG);
	CString unitCharacters;
	unitCharacters.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_UNIT_CHARACTERS);
	CString ciphertextLength;
	ciphertextLength.Format("%s %d %s", ciphertextLengthTag, ciphertext.GetLength(), unitCharacters);
	output(ciphertextLength, true);

	output("", true);

	// dump the ciphertext (only once at the beginning of the result text)
	CString ciphertextTag;
	ciphertextTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_CIPHERTEXT_TAG);
	output(ciphertextTag, true);
	output(ciphertext, true);

	output("", true);

	// TODO: sort list after scoring

	// display all possible results for the user (pairs of key and corresponding cleartext)
	if(listPossibleResults.size() == 0) {
		// display an info message if there was no possible result
		CString infoMessage;
		infoMessage.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_NO_POSSIBLE_RESULTS_FOUND);
		MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
		return -1;
	}
	else if(listPossibleResults.size() == 1) {
		// display the one possible result
		CString possibleKeyTag;
		possibleKeyTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_POSSIBLE_KEY_TAG);
		output(possibleKeyTag, true);
		output((*listPossibleResults.begin()).key, true);
		output("", true);
		CString foundCleartextTag;
		foundCleartextTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_FOUND_CLEARTEXT_TAG);
		output(foundCleartextTag, true);
		output((*listPossibleResults.begin()).cleartext, true);
		output("", true);
	}
	else {
		// display all possible results with a numbered list
		int possibleResultIndex = 1;
		for(std::list<PossibleResult>::iterator iter=listPossibleResults.begin(); iter!=listPossibleResults.end(); iter++) {
			CString stringPossibleResultIndex;
			stringPossibleResultIndex.Format("%d", possibleResultIndex++);
			CString possibleKeyTag;
			possibleKeyTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_POSSIBLE_KEY_TAG);
			output(stringPossibleResultIndex + ". " + possibleKeyTag, true);
			output((*iter).key, true);
			output("", true);
			CString foundCleartextTag;
			foundCleartextTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_FOUND_CLEARTEXT_TAG);
			output(foundCleartextTag, true);
			output((*iter).cleartext, true);
			output("", true);
		}
	}

	return 0;
}

int VigenereAnalysisSchroedel::readDict() {

	// watch out for user cancellation
	if(abort) return -1;

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_LOADING_DICTIONARY);
	output(outputString);

	CString s;

	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open(pathToDictionary);
	if(!fileInput) {
		// display an info message that the file could not be opened
		CString infoMessage;
		infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
		infoMessage.Append(pathToDictionary);
		MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
		return -1;
	}

	dictCount = 0;

	while(!fileInput.eof() && dictCount<MAX_NUMBER_OF_DICT_WORDS) {
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

	// this is the official start of the analysis
	time(&timeAnalysisStart);

	// watch out for user cancellation
	if(abort) return -1;

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_LOADING_CIPHERTEXT);
	output(outputString);

	CString s;

	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open(ciphertextFileName);
	if(!fileInput) {
		// display an info message that the file could not be opened
		CString infoMessage;
		infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
		infoMessage.Append(ciphertextFileName);
		MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
		return -1;
	}

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

	// remove all blanks prior to analysis
	ciphertext.Remove(' ');
	ciphertext.MakeUpper();

	// if necessary, indicate that the ciphertext is shorter than three characters
	if(ciphertext.GetLength() < 3) return -1;

	progress = 0.01;

	return 0;
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

	if(o > maxRating) {
		solveRating = 0;
		solveText = "";
		solveKey = "";
		solveCount = 0;
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

void VigenereAnalysisSchroedel::writeResultFile() {
	
	// open result file
	std::ofstream fileResult;
	fileResult.open(resultFileName, ios_base::trunc);
	if(!fileResult) {
		// display an info message that the file could not be opened
		CString infoMessage;
		infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
		infoMessage.Append(resultFileName);
		MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	fileResult.write(result.GetBuffer(), result.GetLength());

	// close result file
	fileResult.close();
}

void VigenereAnalysisSchroedel::readSettingsFromRegistry() {

	CString pathToDefaultDictionaryFile;
	CString pathToDefaultDigramsFile;
	CString pathToDefaultTrigramsFile;

	// we need some default values if there is no previous registry entry
	debug = false;
	pathToDefaultDictionaryFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
	pathToDefaultDictionaryFile = CString(Pfad) + pathToDefaultDictionaryFile;
	pathToDefaultDigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
	pathToDefaultDigramsFile = CString(Pfad) + pathToDefaultDigramsFile;
	pathToDefaultTrigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
	pathToDefaultTrigramsFile = CString(Pfad) + pathToDefaultTrigramsFile;

	// now try to read settings from the registry
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "VigenereAnalysisSchroedel" ) == ERROR_SUCCESS )
	{
		unsigned long u_analysisThreshold = 0;
		CT_READ_REGISTRY_DEFAULT(u_analysisThreshold, "AnalysisThreshold", 10);

		unsigned long u_extensiveLogging = 0;
		CT_READ_REGISTRY_DEFAULT(u_extensiveLogging, "ExtensiveLogging", 0);

		const unsigned long maxBufferSize = 4096;
		unsigned long bufferSize = maxBufferSize - 1;

		char c_dictionaryFile[maxBufferSize];
		pathToDefaultDictionaryFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
		pathToDefaultDictionaryFile = CString(Pfad) + pathToDefaultDictionaryFile;
		const char *c_dictionaryFileDefault = (const char*)(LPCTSTR)(pathToDefaultDictionaryFile);
		CT_READ_REGISTRY_DEFAULT(c_dictionaryFile, "DictionaryFile", c_dictionaryFileDefault, bufferSize);

		char c_digramsFile[maxBufferSize];
		pathToDefaultDigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
		pathToDefaultDigramsFile = CString(Pfad) + pathToDefaultDigramsFile;
		const char *c_digramsFileDefault = (const char*)(LPCTSTR)(pathToDefaultDigramsFile);
		CT_READ_REGISTRY_DEFAULT(c_digramsFile, "DigramsFile", c_digramsFileDefault, bufferSize);

		char c_trigramsFile[maxBufferSize];
		pathToDefaultTrigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
		pathToDefaultTrigramsFile = CString(Pfad) + pathToDefaultTrigramsFile;
		const char *c_trigramsFileDefault = (const char*)(LPCTSTR)(pathToDefaultTrigramsFile);
		CT_READ_REGISTRY_DEFAULT(c_trigramsFile, "TrigramsFile", c_trigramsFileDefault, bufferSize);

		// apply settings from registry
		analysisThreshold = u_analysisThreshold;
		debug = (BOOL)u_extensiveLogging;
		pathToDictionary = (CString)c_dictionaryFile;
		pathToDigrams = (CString)c_digramsFile;
		pathToTrigrams = (CString)c_trigramsFile;
	}
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