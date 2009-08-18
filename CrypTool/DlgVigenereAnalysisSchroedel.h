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

#ifndef _DLGVIGENEREANALYSISSCHROEDEL_
#define _DLGVIGENEREANALYSISSCHROEDEL_

#include "afxwin.h"

#if _MSC_VER > 1000
#pragma once
#endif

// 06/24/2009, flomar: Vigenere analysis class
// (originally written by Schroedel in Pascal, ported to C++ by flomar)
class VigenereAnalysisSchroedel : public CProgressModel {

public:
	// constructor
	VigenereAnalysisSchroedel(const CString _ciphertextFileName, const CString _title);
	// destructor
	~VigenereAnalysisSchroedel();

public:
	// internal variables
	unsigned int startzeit, endezeit;
	int cDigram[26][26];
	int cTrigram[26][26][26];
	CString pairs[26*26*26][2];
	unsigned int score[26*26*26][2];
	CString _pairs[26*26*26][2];
	unsigned int _score[26*26*26][2];
	int remain, maxDi, maxTri, maxProzent, xDict, xlDict, cPairs;
	CString vigenere[30];
	CString solvers[1000][4];  
	CString dict[100000];
	int solveCount, maxRating, dictCount;
	int solveRating;
	CString solveText, solveKey;
	//ui, fg : Textfile;
  int subRate;
	int cipherPos, aktPos, Pos2, Pos3, Remain2, Remain3;

public:
	// various functions
	void setStatus(CString str);
	void output(CString str);
	
	int readCiphertext();
	int readDict();
	int readTriDigrams();
	int firstChar();
	int secondChar();
	int solveTrigram();
	
	void outputSave(CString a1, CString a2, CString a3, CString a4, CString a5, CString a6, CString a7);
	CString encryptText(CString text, CString key);
	CString decryptText(CString text, CString key);
	int rateString(CString str, CString key);
	CString fillLeft(CString was, int wie);

	// this string holds the analysis results (see result file)
	CString result;
	// function to write the write the result file
	void writeResultFile();

public:
	CString ciphertext;
	CString ciphertextFileName;
	CString title;

	// this flag is set from the outside to abort the analysis
	bool abort;

	double progress;
	virtual double getProgress() { return progress; };

};

// the actual analysis function (to be run in a separate thread)
UINT singleThreadVigenereAnalysisSchroedel(PVOID argument);

#endif