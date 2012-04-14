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

VigenereAnalysisSchroedel::VigenereAnalysisSchroedel(CDlgVigenereAnalysisSchroedel *_dialog, const CString _ciphertextFileName, const CString _title) :
	ciphertextFileName(_ciphertextFileName),
	title(_title),
	theDialog(_dialog),
	canceled(false),
	done(false),
	debug(false) {

	// create result file name
	char pathToFileResult[CRYPTOOL_PATH_LENGTH];
	GetTmpName(pathToFileResult, "cry", ".txt");
	resultFileName = pathToFileResult;
}

VigenereAnalysisSchroedel::~VigenereAnalysisSchroedel() {

}

unsigned int VigenereAnalysisSchroedel::run() {
	// initialize the analysis
	initialize();

	if(	readCiphertext() < 0 ||					// read ciphertext
			readDict() < 0 ||								// read dictionary
			readTriDigrams() < 0 ||					// read digrams and trigrams file
			chooseLanguages() < 0 ||				// let the user choose the languages
			firstChar() < 0 ||							// create pairs for first character
			secondChar() < 0 ||							// create pairs for second and third character
			solveTrigram() < 0)							// solve trigrams
	{
		return 1;
	}

	return 0;
}

void VigenereAnalysisSchroedel::initialize() {
	// initialize internal variables
	canceled = false;
	debug = false;
	done = false;
	startzeit = 0;
	endezeit = 0;
	memset(cDigram, 0, sizeof(cDigram));
	memset(cTrigram, 0, sizeof(cTrigram));
	memset(score, 0, sizeof(score));
	memset(_score, 0, sizeof(_score));
	remain = maxDi = maxTri = xDict = dictCount = cPairs = 0;
	solveCount = solveRating = maxRating = subRate = maxProzent = 0;
	cipherPos = aktPos = Pos2 = Pos3 = Remain2 = Remain3 = 0;

	// read analysis settings from registry
	readSettingsFromRegistry();

	// initialize Vigenere array
	CString s;
	CString t;
	s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  s = s + s;
	for(int i=0; i<26; i++) {
		t = s;
		t.Delete(0, i+1);
		vigenere[i] = t.Left(26);
	}

	// initialize strings
	for(int i=0;i<26*26*26; i++) {
		pairs[i][0] = "";
		pairs[i][1] = "";
		_pairs[i][0] = "";
		_pairs[i][1] = "";
	}
	for(int i=0; i<1000; i++) {
		solvers[i][0] = "";
		solvers[i][1] = "";
		solvers[i][2] = "";
		solvers[i][3] = "";
	}
	result = "";
	resultDebug = "";

	// flomar, 05/19/2010
	// this fix drastically reduces memory usage on subsequent analysis runs
	mapDigramsTrigrams.clear();
	mapListsDictionaryWords.clear();
}

void VigenereAnalysisSchroedel::output(CString str, const bool _debug) {
	
	// if at least on flag is set, we append the output to the result log
	if(_debug || debug) {
		result.Append(CString(str) + CString("\n"));
	}

	// either way we append the output to the debug log
	resultDebug.Append(CString(str) + CString("\n"));
}

int VigenereAnalysisSchroedel::readTriDigrams() {
	
	// flomar, 02/02/2010
	// we expect the digram/trigram files to be formatted in different LANGUAGE sections; a language 
	// within the digram/trigram file is declared with "[LANGUAGE X]", where "X" is the current 
	// language; each line following this declaration is interpreted as digram/trigram and 
	// appended to the list "listDigrams[X]"/"listTrigrams[X]"

	// watch out for user cancellation
	if(canceled) return -1;

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_LOADING_DIGRAMS);
	output(outputString);

	// create a handle for the input file
	std::ifstream fileInputDigrams;
	fileInputDigrams.open(pathToDigrams);
	if(!fileInputDigrams) {
		// flomar, 03/03/2010
		// there are two possible reasons why the desired file (the digrams file) 
		// cannot be opened: (a) the default location is invalid (i.e. the file 
		// was manually deleted), or (b) the location is invalid but the 
		// default location (where the file SHOULD be) is valid-- as for case (b),
		// we should point out to the user that he might have a problem with old 
		// registry entries and offer to bend all the resource paths (digrams, 
		// trigrams and dictionary) back to its proper default location for the 
		// current installation of CrypTool

		// CASE (a): location is invalid and default location is invalid
		if(!isDefaultResourceLocationValid()) {
			CString infoMessage;
			infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
			infoMessage.Append(pathToDigrams);
			MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
			return -1;
		}
		// CASE (b): location is invalid, but default location is valid
		else {
			// the user probably has a problem with old registry entries; ask 
			// him if we should bend all resource paths (dict, digrams, trigrams) 
			// back to the default location; if the answer is yes, re-init the 
			// resource paths and re-read the settings from the registry, then 
			// proceed as usual; otherwise, return -1
			CString infoMessage;
			infoMessage.LoadStringA(IDS_STRING_FILE_NOT_FOUND_BUT_ASK_FOR_MIGRATION_TO_DEFAULT_RESOURCES);
			if(MessageBox(NULL, infoMessage, "CrypTool", MB_ICONQUESTION|MB_YESNO) == IDYES) {
				bendResourceLocationsBackToDefault();
				readSettingsFromRegistry();
				// the clear call is necessary, otherwise the stream is corrupted
				fileInputDigrams.clear();
				fileInputDigrams.open(pathToDigrams);
			}
			else {
				return -1;
			}
		}
	}

	// the currently selected language
	std::string currentLanguage;

	CString s;
	std::string s2;

	while(!fileInputDigrams.eof()) {
		// watch out for user cancellation
		if(canceled) return -1;
		// get the next word
		getline(fileInputDigrams, s2);
		// check if we need to change the current language
		if(s2.find("[LANGUAGE ") != - 1) {
			int beg = 10;
			int end = s2.find("]");
			// isolate the name of the language
			std::string language = s2.substr(beg, end - beg);
			// apply the new language
			currentLanguage = language;

			// read digram factor string for the current language
			getline(fileInputDigrams, s2);
			// TODO
			mapDigramsTrigrams[language].digramFactorString = s2.c_str();
				
			// read digrams for the current language
			maxDi = 0;
			for(int i=0; i<26; i++) {
				for(int o=0; o<26; o++) {
					getline(fileInputDigrams, s2);
					s = s2.c_str();
					s.Delete(0, s.Find(';') + 1);
					
					// TODO
					mapDigramsTrigrams[currentLanguage].digrams[i][o] = atoi(s.GetBuffer());
					//cDigram[i][o] = atoi(s.GetBuffer());
					maxDi = maxDi + atoi(s.GetBuffer());
				}
			}
		}
	}

	// close input file
	fileInputDigrams.close();

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_LOADING_TRIGRAMS);
	output(outputString);

	// create a handle for the input file
	std::ifstream fileInputTrigrams;
	fileInputTrigrams.open(pathToTrigrams);
	if(!fileInputTrigrams) {
		// flomar, 03/03/2010
		// there are two possible reasons why the desired file (the trigrams file) 
		// cannot be opened: (a) the default location is invalid (i.e. the file 
		// was manually deleted), or (b) the location is invalid but the 
		// default location (where the file SHOULD be) is valid-- as for case (b),
		// we should point out to the user that he might have a problem with old 
		// registry entries and offer to bend all the resource paths (digrams, 
		// trigrams and dictionary) back to its proper default location for the 
		// current installation of CrypTool

		// CASE (a): location is invalid and default location is invalid
		if(!isDefaultResourceLocationValid()) {
			CString infoMessage;
			infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
			infoMessage.Append(pathToTrigrams);
			MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
			return -1;
		}
		// CASE (b): location is invalid, but default location is valid
		else {
			// the user probably has a problem with old registry entries; ask 
			// him if we should bend all resource paths (dict, digrams, trigrams) 
			// back to the default location; if the answer is yes, re-init the 
			// resource paths and re-read the settings from the registry, then 
			// proceed as usual; otherwise, return -1
			CString infoMessage;
			infoMessage.LoadStringA(IDS_STRING_FILE_NOT_FOUND_BUT_ASK_FOR_MIGRATION_TO_DEFAULT_RESOURCES);
			if(MessageBox(NULL, infoMessage, "CrypTool", MB_ICONQUESTION|MB_YESNO) == IDYES) {
				bendResourceLocationsBackToDefault();
				readSettingsFromRegistry();
				// the clear call is necessary, otherwise the stream is corrupted
				fileInputTrigrams.clear();
				fileInputTrigrams.open(pathToTrigrams);
			}
			else {
				return -1;
			}
		}
	}

	while(!fileInputTrigrams.eof()) {
		// watch out for user cancellation
		if(canceled) return -1;
		// get the next word
		getline(fileInputTrigrams, s2);
		// check if we need to change the current language
		if(s2.find("[LANGUAGE ") != - 1) {
			int beg = 10;
			int end = s2.find("]");
			// isolate the name of the language
			std::string language = s2.substr(beg, end - beg);
			// apply the new language
			currentLanguage = language;
			
			// read trigrams for the current language
			maxTri = 0;
			for(int i=0; i<26; i++) {
				for(int o=0; o<26; o++) {
					for(int l=0; l<26; l++) {
						getline(fileInputTrigrams, s2);
						s = s2.c_str();
						s.Delete(0, s.Find(';') + 1);

						// TODO
						mapDigramsTrigrams[currentLanguage].trigrams[i][o][l] = atoi(s.GetBuffer());
						//cTrigram[i][o][l] = atoi(s.GetBuffer());
						maxTri = maxTri + atoi(s.GetBuffer());
					}
				}
			}
		}
	}

	// close input file
	fileInputTrigrams.close();

	progress = 0.10;

	return 0;
}

int VigenereAnalysisSchroedel::firstChar() {
	
	// this is the official start of the analysis; originally, we had this line in 
	// "readCiphertext"; but since we're having user interaction AFTER that, we're 
	// putting the official start in this function here to not fudge the time needed 
	time(&timeAnalysisStart);

	// watch out for user cancellation
	if(canceled) return -1;

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
	if(canceled) return -1;

	char actChar, lText, lKey, fText, fKey;
	int i,o,l;
	CString s, sText, sKey;
	int tDigramFactor, kDigramFactor;

	Pos2 = 0;
	Pos3 = 0;
	Remain2 = 0;
	Remain3 = 0;

	// flomar, 07/23/2010
	// some areas should be passed in English only, otherwise we get weird results 
	// in German for example; note that we're looking for the code "1031"-- which 
	// is the language code in the English part of our resource file
	bool englishGB = ((int)(GetThreadLocale())) == 1031;

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
							// flomar, 07/23/2010: see above
							if(englishGB) {
								if(sText == 'A') tDigramFactor = 20;
								if(sText == 'I') tDigramFactor = 20;
							}
							if(cDigramFactorString.Find(sText + fText) != -1) tDigramFactor = 100;
						}

						if(kDigramFactor == 0) {
							// flomar, 07/23/2010: see above
							if(englishGB) {
								if(sKey == 'A') kDigramFactor = 20;
								if(sKey == 'I') kDigramFactor = 20;
							}
							if(cDigramFactorString.Find(sKey + fKey) != -1) kDigramFactor = 100;
						}
					}

					if(n == 2) {
						tDigramFactor = cTrigram[cPosAlphabet.Find(sText[0])][cPosAlphabet.Find(sText[1])][cPosAlphabet.Find(fText)];
						kDigramFactor = cTrigram[cPosAlphabet.Find(sKey[0])][cPosAlphabet.Find(sKey[1])][cPosAlphabet.Find(fKey)];
			
						if(tDigramFactor == 0) {
							// flomar, 07/23/2010: see above
							if(englishGB) {
								if(sText[0] == 'A') {
									if(cDigramFactorString.Find(sText[1] + fText) != -1) tDigramFactor = 100;
								}
								if(sText[0] == 'I') {
									if(cDigramFactorString.Find(sText[1] + fText) != -1) tDigramFactor = 100;
								}
							}
							if(cDigramFactorString.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
						}

						if(kDigramFactor == 0) {
							// flomar, 07/23/2010: see above
							if(englishGB) {
								if(sKey[0] == 'A') {
									if(cDigramFactorString.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
								}
								if(sKey[0] == 'I') {
									if(cDigramFactorString.Find(sKey[1] + fKey) != -1) kDigramFactor = 100;
								}
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
	if(canceled) return -1;

	CString key, text, cipher;
	CString cKey, cText;
	CString rKey, rText;

	int x = 0;

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
	const double loopProgress = (double)(0.75) / (double)(cPairs) / (double)(dictCount);

	CString decryptedText;

	for(int i=0; i<cPairs; i++) {
		
		// watch out for user cancellation
		if(canceled) return -1;
		
		key = pairs[i][0];
		text = pairs[i][1];
		cipher = ciphertext;

    // Try first key
    cKey = "";
    cText = "";

		for(xDict=0; xDict<dictCount; xDict++, progress += loopProgress) {

			// watch out for user cancellation
			if(canceled) return -1;
			
			if(dict[xDict].Find(key) == 0) {
				if(dict[xDict].GetLength() > key.GetLength()) {
					if(cKey.Find(dict[xDict][3]) == -1) {
						cKey = cKey + dict[xDict][3];
					}
				}
			}
			if(dict[xDict].Find(text) == 0) {
				if(dict[xDict].GetLength() > text.GetLength()) {
					if(cText.Find(dict[xDict][3]) == -1) {
						cText = cText + dict[xDict][3];
					}
				}
			}
		}

		if(cKey.GetLength() > 0 && cText.GetLength() > 0) {
			for(int o=0; o<cKey.GetLength(); o++) {
				for(int l=0; l<cText.GetLength(); l++) {
					
					// watch out for user cancellation
					if(canceled) return -1;

					if(encryptChar(cText[l], cKey[o]) == cipher[3]) {
						rKey = "";
						rText = "";
						for(xDict=0; xDict<dictCount; xDict++) {

							// watch out for user cancellation
							if(canceled) return -1;

							if(dict[xDict].GetLength() <= ciphertext.GetLength()) {
								if(dict[xDict].Find(key + cKey[o]) == 0 || dict[xDict].Find(text + cText[l]) == 0) {
									decryptedText = decryptText(ciphertext, dict[xDict]);

									// watch out for user cancellation
									if(canceled) return -1;

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

									PossibleResult possibleResult;
									possibleResult.key = dict[xDict];
									possibleResult.cleartext = decryptedText;

									CString foo;
									CString bar;
									CString longestDictionaryMatch;
									for(int indexDict=0; indexDict<dictCount; indexDict++) {
										foo = dict[indexDict];
										bar = decryptedText;
										// to lowercase
										foo.MakeLower();
										bar.MakeLower();
										// try to find dictionary word
										if(foo.Find(bar) == 0) {
											if(dict[indexDict].GetLength() > longestDictionaryMatch) {
												longestDictionaryMatch = dict[indexDict];
											}
										}
									}
									possibleResult.longestDictionaryMatch = longestDictionaryMatch.MakeLower();

									// add possible result to our results map (and avoid duplicates)
									if(mapPossibleResults.find(possibleResult.key) == mapPossibleResults.end()) {
										mapPossibleResults[possibleResult.key] = possibleResult;
										// also, pass it through to the analysis dialog (if the dialog 
										// exists, and if there was a dictionary match) 
										if(theDialog) {
											if(possibleResult.longestDictionaryMatch.GetLength() > 0) {
												theDialog->addPossibleResult(possibleResult);
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

		// list ALL possible results (not just one)
		for(std::map<CString, PossibleResult>::iterator it=mapPossibleResults.begin(); it!=mapPossibleResults.end(); it++) {
			if((*it).second.longestDictionaryMatch.GetLength() > 0) 
				output((*it).second.key + "/" + (*it).second.cleartext + " [" + (*it).second.longestDictionaryMatch + "]");
			else
				output((*it).second.key + "/" + (*it).second.cleartext);
		}
		
		for(int i=0; i<cPairs; i++) {
			key = pairs[i][0];
			text = pairs[i][1];
		}
    output("");
	}

	// this is the official end of the analysis
	time(&timeAnalysisEnd);
	progress = 1.0;
	done = true;

	// compute the time needed for the analysis
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

	// dump the selected keyword language(s)
	CString selectedKeywordLanguagesTag;
	selectedKeywordLanguagesTag.Format(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_SELECTED_KEYWORD_LANGUAGES, theDialog->getSelectedCiphertextLanguageAsString());
	output(selectedKeywordLanguagesTag, true);

	// dump the selected ciphertext language
	CString selectedCiphertextLanguageTag;
	selectedCiphertextLanguageTag.Format(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_SELECTED_CIPHERTEXT_LANGUAGE, theDialog->getSelectedCiphertextLanguageAsString());
	output(selectedCiphertextLanguageTag, true);

	output("", true);

	// dump the ciphertext (only once at the beginning of the result text)
	CString ciphertextTag;
	ciphertextTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_CIPHERTEXT_TAG);
	output(ciphertextTag, true);
	output(ciphertext, true);

	output("", true);

	// fill results list
	for(std::map<CString, PossibleResult>::iterator it=mapPossibleResults.begin(); it!=mapPossibleResults.end(); it++) {
		listPossibleResults.push_back((*it).second);
	}
	// sort list with possible results (see header file for details of PossibleResult::sort)
	listPossibleResults.sort();

	if(listPossibleResults.size() == 0) {
		CString message;
		message.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_NO_POSSIBLE_RESULTS_FOUND);
		output(message, true);
	}
	// display all possible results for the user (pairs of key and corresponding cleartext)
	if(listPossibleResults.size() == 1) {
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
	if(listPossibleResults.size() > 1) {
		// display all possible results with a numbered list
		int possibleResultIndex = 1;
		for(std::list<PossibleResult>::iterator iter=listPossibleResults.begin(); iter!=listPossibleResults.end(); iter++) {
			CString stringPossibleResultIndex;
			stringPossibleResultIndex.Format("%d", possibleResultIndex++);
			CString possibleKeyTag;
			possibleKeyTag.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_POSSIBLE_KEY_TAG);
			output(stringPossibleResultIndex + ". " + possibleKeyTag, true);
			output((*iter).key, true);
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

	// flomar, 01/19/2010
	// we expect the dictionary to be formatted in different LANGUAGE sections; a language 
	// within the dictionary is declared with "[LANGUAGE X]", where "X" is the current 
	// language; each line following this declaration is interpreted as dictionary word and 
	// appended to the list "listDictionaryWords[X]"; with this technique the user can limit 
	// the size of the dictionary and thus speed up the analysis

	// watch out for user cancellation
	if(canceled) return -1;

	outputString.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_TAG_LOADING_DICTIONARY);
	output(outputString);

	// create a handle for the input file
	std::ifstream fileInputDictionary;
	fileInputDictionary.open(pathToDictionary);
	if(!fileInputDictionary) {
		// flomar, 03/03/2010
		// there are two possible reasons why the desired file (the dictionary) 
		// cannot be opened: (a) the default location is invalid (i.e. the file 
		// was manually deleted), or (b) the location is invalid but the 
		// default location (where the file SHOULD be) is valid-- as for case (b),
		// we should point out to the user that he might have a problem with old 
		// registry entries and offer to bend all the resource paths (digrams, 
		// trigrams and dictionary) back to its proper default location for the 
		// current installation of CrypTool

		// CASE (a): location is invalid and default location is invalid
		if(!isDefaultResourceLocationValid()) {
			CString infoMessage;
			infoMessage.LoadStringA(IDS_STRING_FILE_COULD_NOT_BE_OPENED);
			infoMessage.Append(pathToDictionary);
			MessageBox(NULL, infoMessage, "CrypTool", MB_ICONINFORMATION);
			return -1;
		}
		// CASE (b): location is invalid, but default location is valid
		else {
			// the user probably has a problem with old registry entries; ask 
			// him if we should bend all resource paths (dict, digrams, trigrams) 
			// back to the default location; if the answer is yes, re-init the 
			// resource paths and re-read the settings from the registry, then 
			// proceed as usual; otherwise, return -1
			CString infoMessage;
			infoMessage.LoadStringA(IDS_STRING_FILE_NOT_FOUND_BUT_ASK_FOR_MIGRATION_TO_DEFAULT_RESOURCES);
			if(MessageBox(NULL, infoMessage, "CrypTool", MB_ICONQUESTION|MB_YESNO) == IDYES) {
				bendResourceLocationsBackToDefault();
				readSettingsFromRegistry();
				// the clear call is necessary, otherwise the stream is corrupted
				fileInputDictionary.clear();
				fileInputDictionary.open(pathToDictionary);
			}
			else {
				return -1;
			}
		}
	}

	// the currently selected language
	std::string currentLanguage;

	CString s;
	std::string s2;
	dictCount = 0;

	while(!fileInputDictionary.eof() && dictCount<MAX_NUMBER_OF_DICT_WORDS) {
		// watch out for user cancellation
		if(canceled) return -1;
		// get the next word
		getline(fileInputDictionary, s2);
		// check if we need to change the current language
		if(s2.find("[LANGUAGE ") != - 1) {
			int beg = 10;
			int end = s2.find("]");
			// isolate the name of the language
			std::string language = s2.substr(beg, end - beg);
			// apply the new language
			currentLanguage = language;
		}
		// process the next word
		else {
			s = s2.c_str();
			s.Trim();
			s.MakeUpper();
			// ignore those words that don't match the standard alphabet
			for(int i=0; i<s.GetLength(); i++) {
				if(cPosAlphabet.Find(s[i]) == -1)
					continue;
			}
			// add this word to the analysis dictionary
			if(!currentLanguage.empty() && s.GetLength() > 0) {
				mapListsDictionaryWords[currentLanguage].push_back(s.GetBuffer());
			}
		}
	}

	// close input file
	fileInputDictionary.close();

	progress = 0.05;

	return 0;
}

int VigenereAnalysisSchroedel::chooseLanguages() {

	// flomar, 03/08/2010
	// let the user decide which language(s) to use
	CDlgVigenereAnalysisSchroedelChooseLanguages dlg(mapListsDictionaryWords, mapDigramsTrigrams);
	if(dlg.DoModal() == IDOK) {

		// create the dictionary for our analysis
		std::list<std::string>::iterator iter;
		for(iter=dlg.selectedKeywordsList.begin(); iter!=dlg.selectedKeywordsList.end(); iter++) {
			dict[dictCount++] = (*iter).c_str();
		}

		// create digrams/trigrams for our analysis
		cDigramFactorString = dlg.selectedDigramTrigramSet.digramFactorString;
		memset(cDigram, 0, sizeof(cDigram));
		memset(cTrigram, 0, sizeof(cTrigram));
		memcpy(cDigram, dlg.selectedDigramTrigramSet.digrams, sizeof(cDigram));
		memcpy(cTrigram, dlg.selectedDigramTrigramSet.trigrams, sizeof(cTrigram));

		// flomar, 05/15/2010
		// update the selected languages
		theDialog->updateSelectedLanguages(dlg.selectedKeywordLanguagesAsString, dlg.selectedCiphertextLanguageAsString);
		
		// indicate we're done without any errors
		return 0;
	}

	return -1;
}

int VigenereAnalysisSchroedel::readCiphertext() {

	// watch out for user cancellation
	if(canceled) return -1;

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
	// convert ciphertext to upper case
	ciphertext.MakeUpper();
	// remove all non-alphabet characters (since our analysis works on [A-Z] only anyway)
	CString cleanedCiphertext;
	for(int i=0; i<ciphertext.GetLength(); i++) {
		if(ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {	
			cleanedCiphertext.AppendChar(ciphertext[i]);
		}
	}
	ciphertext = cleanedCiphertext;

	// if necessary, indicate that the ciphertext is shorter than three characters
	if(ciphertext.GetLength() < 3) return -1;

	progress = 0.01;

	return 0;
}

char VigenereAnalysisSchroedel::encryptChar(const char &_char, const char &_key) {
	char result = '\0';
	int index;
	for(int i=0; i<26; i++) {
		if(_key == vigenere[i][0]) {
			if((index = klartext.Find(_char)) > -1) {
				return vigenere[i][index];
			}
		}
	}
	return result;
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

void VigenereAnalysisSchroedel::writeResultFile(const bool _debug) {
	
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

	// write the debug output if desired
	if(_debug) fileResult.write(resultDebug.GetBuffer(), resultDebug.GetLength());
	// otherwise, stick to the regular output
	else fileResult.write(result.GetBuffer(), result.GetLength());

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
		unsigned long u_extensiveLogging = 0;
		CT_READ_REGISTRY_DEFAULT(u_extensiveLogging, "ExtensiveLogging", 0);

		const unsigned long maxBufferSize = 4096;
		unsigned long bufferSize;

		char c_dictionaryFile[maxBufferSize];
		pathToDefaultDictionaryFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
		pathToDefaultDictionaryFile = CString(Pfad) + pathToDefaultDictionaryFile;
		const char *c_dictionaryFileDefault = (const char*)(LPCTSTR)(pathToDefaultDictionaryFile);
		bufferSize = maxBufferSize - 1;
		CT_READ_REGISTRY_DEFAULT(c_dictionaryFile, "DictionaryFile", c_dictionaryFileDefault, bufferSize);

		char c_digramsFile[maxBufferSize];
		pathToDefaultDigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
		pathToDefaultDigramsFile = CString(Pfad) + pathToDefaultDigramsFile;
		const char *c_digramsFileDefault = (const char*)(LPCTSTR)(pathToDefaultDigramsFile);
		bufferSize = maxBufferSize - 1;
		CT_READ_REGISTRY_DEFAULT(c_digramsFile, "DigramsFile", c_digramsFileDefault, bufferSize);

		char c_trigramsFile[maxBufferSize];
		pathToDefaultTrigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
		pathToDefaultTrigramsFile = CString(Pfad) + pathToDefaultTrigramsFile;
		const char *c_trigramsFileDefault = (const char*)(LPCTSTR)(pathToDefaultTrigramsFile);
		bufferSize = maxBufferSize - 1;
		CT_READ_REGISTRY_DEFAULT(c_trigramsFile, "TrigramsFile", c_trigramsFileDefault, bufferSize);

		// apply settings from registry
		debug = (bool)(u_extensiveLogging != 0);
		pathToDictionary = (CString)c_dictionaryFile;
		pathToDigrams = (CString)c_digramsFile;
		pathToTrigrams = (CString)c_trigramsFile;
	}
}

bool VigenereAnalysisSchroedel::isDefaultResourceLocationValid() {
	// flomar, 03/03/2010
	// this function returns true only if all three files are 
	// available in their default locations: the dictionary, the 
	// digrams file and the trigrams file

	// get default paths for our resources
	CString pathToDefaultDictionaryFile;
	pathToDefaultDictionaryFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
	pathToDefaultDictionaryFile.Insert(0, Pfad);
	CString pathToDefaultDigramsFile;
	pathToDefaultDigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
	pathToDefaultDigramsFile.Insert(0, Pfad);
	CString pathToDefaultTrigramsFile;
	pathToDefaultTrigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
	pathToDefaultTrigramsFile.Insert(0, Pfad);

	bool allResourcesAvailable = true;

	// retrieve the file stati (sp?) for our resources
	CFileStatus dictionaryFileStatus;
	if(!CFile::GetStatus(pathToDefaultDictionaryFile, dictionaryFileStatus))
		return false;
	CFileStatus digramsFileStatus;
	if(!CFile::GetStatus(pathToDefaultDigramsFile, digramsFileStatus)) 
		return false;
	CFileStatus trigramsFileStatus;
	if(!CFile::GetStatus(pathToDefaultTrigramsFile, trigramsFileStatus))
		return false;

	// if we get to this point, all our resource files are there
	return true;
}

void VigenereAnalysisSchroedel::bendResourceLocationsBackToDefault() {
	// flomar, 03/03/2010
	// this function bends all resource locations (dictionary, digrams, trigrams) 
	// back to their default values (i.e. to the installation directory); needless 
	// to say, you shouldn't use this function unless you verified the default 
	// resource locations are valid

	CString pathToDefaultDictionaryFile;
	pathToDefaultDictionaryFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DICTIONARY_FILENAME);
	pathToDefaultDictionaryFile.Insert(0, Pfad);
	CString pathToDefaultDigramsFile;
	pathToDefaultDigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_DIGRAMS_FILENAME);
	pathToDefaultDigramsFile.Insert(0, Pfad);
	CString pathToDefaultTrigramsFile;
	pathToDefaultTrigramsFile.LoadStringA(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_TRIGRAMS_FILENAME);
	pathToDefaultTrigramsFile.Insert(0, Pfad);

	// essentially, we're writing the application defaults back to the registry
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "VigenereAnalysisSchroedel" ) == ERROR_SUCCESS )
	{	
		CT_WRITE_REGISTRY(pathToDefaultDictionaryFile, "DictionaryFile");
		CT_WRITE_REGISTRY(pathToDefaultDigramsFile, "DigramsFile");
		CT_WRITE_REGISTRY(pathToDefaultTrigramsFile, "TrigramsFile");
	}
	else {
		// flomar, 03/03/2010
		// TODO/FIXME: that's a problem almost everywhere in registry-related code
	}
}

/****************************************
		END VIGENERE ANALYSIS SCHROEDEL
 ****************************************/

// the actual analysis function (to be run in a separate thread)
UINT singleThreadVigenereAnalysisSchroedel(PVOID argument) {

	// get a pointer to the analysis object
	VigenereAnalysisSchroedel *theAnalysis = (VigenereAnalysisSchroedel*)(argument);

	// return if we don't have a valid analysis object
	if(!theAnalysis) {
		return 1;
	}

	// run the analysis
	return theAnalysis->run();
}



IMPLEMENT_DYNAMIC(CDlgVigenereAnalysisSchroedel, CDialog)

CDlgVigenereAnalysisSchroedel::CDlgVigenereAnalysisSchroedel(const CString &_infileName, const CString &_infileTitle, CWnd* pParent) : 
	CDialog(CDlgVigenereAnalysisSchroedel::IDD, pParent),
	theAnalysis(0),
	infileName(_infileName),
	infileTitle(_infileTitle) {

}

CDlgVigenereAnalysisSchroedel::~CDlgVigenereAnalysisSchroedel()
{
	if(theAnalysis) delete theAnalysis;
}

void CDlgVigenereAnalysisSchroedel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POSSIBLE_RESULTS, controlListPossibleResults);
	DDX_Control(pDX, IDC_PROGRESS_ANALYSIS, controlProgressAnalysis);
}

BEGIN_MESSAGE_MAP(CDlgVigenereAnalysisSchroedel, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_START_ANALYSIS, OnBnClickedStartAnalysis)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_ANALYSIS, OnBnClickedCancelAnalysis)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ANALYSIS_RESULTS, OnBnClickedShowAnalysisResults)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CDlgVigenereAnalysisSchroedel::OnInitDialog()
{
	CDialog::OnInitDialog();

	// clear the list
	controlListPossibleResults.DeleteAllItems();
	// make sure we select the full row (key AND cleartext), not just a single items 
	controlListPossibleResults.SetExtendedStyle(controlListPossibleResults.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	// add column headers
	CString columnHeaderKey; columnHeaderKey.LoadString(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_COLUMNHEADERKEY);
	CString columnHeaderCleartext; columnHeaderCleartext.LoadString(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_COLUMNHEADERCLEARTEXT);
	controlListPossibleResults.InsertColumn( 0, columnHeaderKey, LVCFMT_LEFT, 200);
	controlListPossibleResults.InsertColumn( 1, columnHeaderCleartext, LVCFMT_LEFT, 270);

	// enable the "start analysis" button
	GetDlgItem(IDC_BUTTON_START_ANALYSIS)->EnableWindow(true);
	// disable the "cancel analysis" button
	GetDlgItem(IDC_BUTTON_CANCEL_ANALYSIS)->EnableWindow(false);
	// disable the "show results" button
	GetDlgItem(IDC_BUTTON_SHOW_ANALYSIS_RESULTS)->EnableWindow(false);
	// enable the "close" button
	GetDlgItem(IDCANCEL)->EnableWindow(true);

	// set the range for the progress bar
	controlProgressAnalysis.SetRange(0, 100);

	return FALSE;
}

void CDlgVigenereAnalysisSchroedel::addPossibleResult(const PossibleResult &_possibleResult)
{
	controlListPossibleResults.InsertItem(0, "ITEM");
	controlListPossibleResults.SetItemText(0, 0, _possibleResult.key);
	controlListPossibleResults.SetItemText(0, 1, _possibleResult.cleartext);
}

void CDlgVigenereAnalysisSchroedel::updateSelectedLanguages(const CString &_selectedKeywordLanguages, const CString &_selectedCiphertextLanguage)
{
	selectedKeywordLanguagesAsString = _selectedKeywordLanguages;
	selectedCiphertextLanguageAsString = _selectedCiphertextLanguage;

	CString columnHeaderCleartext;
	// if our language is empty, we go with the default column header (language assumption not displayed)
	if(selectedCiphertextLanguageAsString.IsEmpty()) columnHeaderCleartext.Format(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_COLUMNHEADERCLEARTEXT);
	// if our language is set, we add the language assumption
	else columnHeaderCleartext.Format(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_COLUMNHEADERCLEARTEXT_WITHLANGUAGE, selectedCiphertextLanguageAsString);
	// delete old column
	controlListPossibleResults.DeleteColumn(1);
	// add new column
	controlListPossibleResults.InsertColumn(1, columnHeaderCleartext, LVCFMT_LEFT, 270);
}

void CDlgVigenereAnalysisSchroedel::OnBnClickedStartAnalysis()
{
	// create the analysis object (initializing the dialog as well as name and title of the infile)
	if(!theAnalysis) theAnalysis = new VigenereAnalysisSchroedel(this, infileName, infileTitle);

	// clear the list of possible results
	controlListPossibleResults.DeleteAllItems();

	// flomar, 05/15/2010
	// go back to default headers (maybe the language changed during multiple analysis runs)
	controlListPossibleResults.DeleteColumn(1);
	CString columnHeaderCleartext; columnHeaderCleartext.LoadString(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_COLUMNHEADERCLEARTEXT);
	controlListPossibleResults.InsertColumn( 1, columnHeaderCleartext, LVCFMT_LEFT, 270);

	// disable the "start analysis" button
	GetDlgItem(IDC_BUTTON_START_ANALYSIS)->EnableWindow(false);
	// enable the "cancel analysis" button
	GetDlgItem(IDC_BUTTON_CANCEL_ANALYSIS)->EnableWindow(true);
	// disable the "show results" button
	GetDlgItem(IDC_BUTTON_SHOW_ANALYSIS_RESULTS)->EnableWindow(false);
	// disable the "close" button (stop the analysis first to close the dialog)
	GetDlgItem(IDCANCEL)->EnableWindow(false);

	// start the actual analysis
	AfxBeginThread(singleThreadVigenereAnalysisSchroedel, (PVOID)(theAnalysis));

	// call our callback function every 250 ms
	SetTimer(VIGENERE_ANALYSIS_SCHROEDEL_TIMER_ID, 250, NULL);
}

void CDlgVigenereAnalysisSchroedel::OnBnClickedCancelAnalysis()
{
	// don't do anything if the analysis object is invalid
	if(!theAnalysis) return;
	// cancel the analysis
	theAnalysis->cancel();
}

void CDlgVigenereAnalysisSchroedel::OnBnClickedShowAnalysisResults()
{
	// return if the analysis object is invalid
	if(!theAnalysis) return;
	
	// decide which log to write: the standard log (result) or the debug log (resultDebug)
	if(theAnalysis->getResult().IsEmpty()) {
		// write the debug log if the standard log is empty regardless of any other settings
		theAnalysis->writeResultFile(true);
	}
	else {
		// write the standard log
		theAnalysis->writeResultFile(false);
	}
		
	// open the new result file
	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(theAnalysis->getResultFileName());
	// close the dialog
	OnCancel();
}

void CDlgVigenereAnalysisSchroedel::OnTimer(UINT nIDEvent) 
{
	// only process timer events that match our ID
	if (nIDEvent != VIGENERE_ANALYSIS_SCHROEDEL_TIMER_ID) {
		CDialog::OnTimer(nIDEvent);
		return;
	}

	// update the progress bar
	controlProgressAnalysis.SetPos((int)(theAnalysis->getProgress() * 100));

	// at this point the analysis is either canceled or done
	if(theAnalysis->isCanceled() || theAnalysis->isDone()) {
		// kill the timer that was set upon analysis start
		KillTimer(VIGENERE_ANALYSIS_SCHROEDEL_TIMER_ID);

		// enable the "start analysis" button
		GetDlgItem(IDC_BUTTON_START_ANALYSIS)->EnableWindow(true);
		// disable the "cancel analysis" button
		GetDlgItem(IDC_BUTTON_CANCEL_ANALYSIS)->EnableWindow(false);
		// disable the "show results" button
		GetDlgItem(IDC_BUTTON_SHOW_ANALYSIS_RESULTS)->EnableWindow(true);
		// enable the "close" button
		GetDlgItem(IDCANCEL)->EnableWindow(true);

		// display analysis result to the user (completed: yes/no, if completed: successful or not)
		CString message;
		CString temp;
		// add information about completion status
		if(theAnalysis->isCanceled()) {
			// the analysis was not completed
			temp.LoadString(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_ANALYSIS_INCOMPLETE);
			message.Append(temp);
		}
		else {
			if(theAnalysis->isDone()) {
				// the analysis was completed
				temp.LoadString(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_ANALYSIS_COMPLETE);
				message.Append(temp);
				// add information in case of completion without any results (which means: no success);
				// this is provided for user convenience: since the analysis can fail in quite a few 
				// different scenarios, we want to let the user know what the problem might be
				if(!theAnalysis->isSuccessful()) {
					temp.LoadString(IDS_STRING_VIGENERE_ANALYSIS_SCHROEDEL_ANALYSIS_NOT_SUCCESSFUL);
					message.Append(temp);
				}
			}
		}
		// display message box
		AfxMessageBox(message, MB_ICONINFORMATION);
	}
}



IMPLEMENT_DYNAMIC(CDlgVigenereAnalysisSchroedelChooseLanguages, CDialog)

CDlgVigenereAnalysisSchroedelChooseLanguages::CDlgVigenereAnalysisSchroedelChooseLanguages(std::map<std::string, std::list<std::string>> &_mapListsDictionaryWords, std::map<std::string, DigramTrigramSet> &_mapDigramsTrigrams, CWnd* pParent) : 
	CDialog(CDlgVigenereAnalysisSchroedelChooseLanguages::IDD, pParent),
	mapListsDictionaryWords(_mapListsDictionaryWords),
	mapDigramsTrigrams(_mapDigramsTrigrams) {

}

CDlgVigenereAnalysisSchroedelChooseLanguages::~CDlgVigenereAnalysisSchroedelChooseLanguages()
{
	
}

void CDlgVigenereAnalysisSchroedelChooseLanguages::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LANGUAGES_KEYWORD, listBoxLanguagesKeyword);
	DDX_Control(pDX, IDC_LIST_LANGUAGES_CIPHERTEXT, listBoxLanguagesCiphertext);
}

BEGIN_MESSAGE_MAP(CDlgVigenereAnalysisSchroedelChooseLanguages, CDialog)
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()

BOOL CDlgVigenereAnalysisSchroedelChooseLanguages::OnInitDialog()
{
	CDialog::OnInitDialog();

	// clear the lists
	listBoxLanguagesKeyword.ResetContent();
	listBoxLanguagesCiphertext.ResetContent();

	// make sure we're using the correct checkbox style
	listBoxLanguagesKeyword.SetCheckStyle(BS_AUTOCHECKBOX);
	listBoxLanguagesCiphertext.SetCheckStyle(BS_AUTOCHECKBOX);

	// add all available languages (keyword)
	std::map<std::string, std::list<std::string>>::iterator mapIteratorKeyword;
	for(mapIteratorKeyword=mapListsDictionaryWords.begin(); mapIteratorKeyword!=mapListsDictionaryWords.end(); mapIteratorKeyword++) {
		listBoxLanguagesKeyword.AddString((*mapIteratorKeyword).first.c_str());
	}

	// all all available languages (ciphertext)
	std::map<std::string, DigramTrigramSet>::iterator mapIteratorCiphertext;
	for(mapIteratorCiphertext=mapDigramsTrigrams.begin(); mapIteratorCiphertext!=mapDigramsTrigrams.end(); mapIteratorCiphertext++) {
		listBoxLanguagesCiphertext.AddString((*mapIteratorCiphertext).first.c_str());
	}

	// select ALL LANGUAGES (keyword) by default
	for(int i=0; i<listBoxLanguagesKeyword.GetCount(); i++) {
		listBoxLanguagesKeyword.SetCheck(i, 1);
	}

	// select THE FIRST LANGUAGE (ciphertext) by default
	if(listBoxLanguagesCiphertext.GetCount() > 0) {
		listBoxLanguagesCiphertext.SetCheck(0, 1);
	}

	UpdateData(false);

	return FALSE;
}

void CDlgVigenereAnalysisSchroedelChooseLanguages::OnOK()
{
	// flomar, 03/15/2010
	// since we're using custom items with checkboxes, we need to manually 
	// extract how many items are actually selected
	int numberOfKeywordLanguagesSelected = 0;
	int numberOfCiphertextLanguagesSelected = 0;
	for(int i=0; i<listBoxLanguagesKeyword.GetCount(); i++) {
		if(listBoxLanguagesKeyword.GetCheck(i)) {
			// we have a keyword language here
			numberOfKeywordLanguagesSelected++;
			// add the language to the result structure
			CString selectedLanguage;
			listBoxLanguagesKeyword.GetText(i, selectedLanguage);
			std::list<std::string> listKeywords = mapListsDictionaryWords[(LPCTSTR)selectedLanguage];
			for(std::list<std::string>::iterator iter=listKeywords.begin(); iter!=listKeywords.end(); iter++)
         selectedKeywordsList.push_back(*iter);
		}
	}
	for(int i=0; i<listBoxLanguagesCiphertext.GetCount(); i++) {
		if(listBoxLanguagesCiphertext.GetCheck(i)) {
			// we have a ciphertext language here
			numberOfCiphertextLanguagesSelected++;
			// add the language to the result structure
			CString selectedLanguage;
			listBoxLanguagesCiphertext.GetText(i, selectedLanguage);
			selectedDigramTrigramSet = mapDigramsTrigrams[(LPCTSTR)selectedLanguage]; 
		}
	}

	// don't do anything if less than one keyword language is selected or if not exactly 
	// one ciphertext language is selected; in this case, revert all changes, display 
	// a notification message to the user and return 
	if(numberOfKeywordLanguagesSelected < 1 || numberOfCiphertextLanguagesSelected != 1) {
		// clean up our result structures
		selectedKeywordsList.clear();
		selectedDigramTrigramSet.digramFactorString = "";
		memset(selectedDigramTrigramSet.digrams, sizeof(selectedDigramTrigramSet.digrams), 0);
		memset(selectedDigramTrigramSet.trigrams, sizeof(selectedDigramTrigramSet.trigrams), 0);
		// display notification message
		CString message; message.Format(IDS_STRING_LANGUAGE_CHOICE_REQUIREMENTS);
		AfxMessageBox(message, MB_ICONINFORMATION);
		return;
	}

	// flomar, 05/15/2010
	CString selectedKeywordLanguages;
	for(int i=0; i<listBoxLanguagesKeyword.GetCount(); i++) {
		if(listBoxLanguagesKeyword.GetCheck(i)) {
			// we have a keyword language here
			CString selectedKeywordLanguage;
			listBoxLanguagesKeyword.GetText(i, selectedKeywordLanguage);
			// append the language to the string of existing languages
			if(selectedKeywordLanguages.IsEmpty()) {
				selectedKeywordLanguages.Append(selectedKeywordLanguage);
			}
			else {
				selectedKeywordLanguages.Append(", ");
				selectedKeywordLanguages.Append(selectedKeywordLanguage);
			}
		}
	}

	// flomar, 05/15/2010
	CString selectedCiphertextLanguage;
	for(int i=0; i<listBoxLanguagesCiphertext.GetCount(); i++) {
		if(listBoxLanguagesCiphertext.GetCheck(i)) {
			// we have a ciphertext language here
			listBoxLanguagesCiphertext.GetText(i, selectedCiphertextLanguage); 
		}
	}

	selectedKeywordLanguagesAsString = selectedKeywordLanguages;
	selectedCiphertextLanguageAsString = selectedCiphertextLanguage;

	// close the dialog
	CDialog::OnOK();
}