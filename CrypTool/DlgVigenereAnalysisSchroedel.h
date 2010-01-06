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
#include <list>

#if _MSC_VER > 1000
#pragma once
#endif

#define MAX_NUMBER_OF_DICT_WORDS 500000

// forward declaration
class CDlgVigenereAnalysisSchroedel;

// this struct contains a possible result (key, cleartext, rating)
struct PossibleResult {
	CString key;
	CString cleartext;
	int rating;
};

// 06/24/2009, flomar: Vigenere analysis class
// (originally written by Schroedel in Pascal, ported to C++ by flomar)
class VigenereAnalysisSchroedel : public CProgressModel {

public:
	// constructor
	VigenereAnalysisSchroedel(const CString _ciphertextFileName, const CString _title);
	// destructor
	~VigenereAnalysisSchroedel();

	// introduce the dialog object to the analysis
	void setDialog(CDlgVigenereAnalysisSchroedel *_theDialog);

public:
	// internal variables
	unsigned int startzeit, endezeit;
	int cDigram[26][26];
	int cTrigram[26][26][26];
	CString pairs[26*26*26][2];
	unsigned int score[26*26*26][2];
	CString _pairs[26*26*26][2];
	unsigned int _score[26*26*26][2];
	int remain, maxDi, maxTri, xDict, xlDict, cPairs;
	unsigned int maxProzent;
	CString vigenere[30];
	CString solvers[1000][4];  
	CString dict[MAX_NUMBER_OF_DICT_WORDS];
	int solveCount, maxRating, dictCount;
	int solveRating;
	CString solveText, solveKey;
	//ui, fg : Textfile;
  int subRate;
	int cipherPos, aktPos, Pos2, Pos3, Remain2, Remain3;

public:
	// various functions
	void output(CString str, const bool _debug = false);
	
	int readCiphertext();
	int readDict();
	int readTriDigrams();
	int firstChar();
	int secondChar();
	int solveTrigram();
	
	CString encryptText(CString text, CString key);
	CString decryptText(CString text, CString key);
	int rateString(CString str, CString key);
	CString fillLeft(CString was, int wie);

	// this treshold is used to determine if a result might be considered correct
	int analysisThreshold;

	// this is used for timing purposes
	time_t timeAnalysisStart;
	time_t timeAnalysisEnd;

	// this list contains all possible results
	std::list<PossibleResult> listPossibleResults;

	// this string holds the analysis results (see result file)
	CString result;
	// the name of the result file
	CString resultFileName;
	// function to write the write the result file
	void writeResultFile();

	// aux variables
	CString outputString;
	CString formatString;

public:
	CString ciphertext;
	CString ciphertextFileName;
	CString title;

	// this flag is set from the outside to abort the analysis
	bool abort;

	// this flag indicates we're in debug mode (thus, much more detailed output)
	bool debug;
	CString pathToDictionary;
	CString pathToDigrams;
	CString pathToTrigrams;

	void readSettingsFromRegistry();

	double progress;
	virtual double getProgress() { return progress; };

private:
	// the dialog object
	CDlgVigenereAnalysisSchroedel *theDialog;
};

// the actual analysis function (to be run in a separate thread)
UINT singleThreadVigenereAnalysisSchroedel(PVOID argument);

// this is our timer ID for the progress bar callback
#define VIGENERE_ANALYSIS_SCHROEDEL_TIMER_ID	9999

// TODO
class CDlgVigenereAnalysisSchroedel : public CDialog
{
	DECLARE_DYNAMIC(CDlgVigenereAnalysisSchroedel)

public:
	CDlgVigenereAnalysisSchroedel(const CString &_infileName, const CString &_infileTitle, CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgVigenereAnalysisSchroedel();

	// add a possible result (done "from the outside" by the analysis object)
	void addPossibleResult(const PossibleResult &_possibleResult);

// Dialogfelddaten
	enum { IDD = IDD_VIGENERE_ANALYSIS_SCHROEDEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	// the analysis object
	VigenereAnalysisSchroedel *theAnalysis;
	// the list box for all possible results
	CListCtrl controlListPossibleResults;
	// the start analysis button was pressed
	afx_msg void OnBnClickedStartAnalysis();
	// the cancel analysis button was pressed
	afx_msg void OnBnClickedCancelAnalysis();
	// show the analysis results
	afx_msg void OnBnClickedShowAnalysisResults();
	// the file holding the analysis results
	CString resultFileName;

	// the control variable for the progress bar
	CProgressCtrl controlProgressAnalysis;
	// the timer callback: updates the progress bar
	afx_msg void OnTimer(UINT nIDEvent);

	// parameters passed to the analysis object
	CString infileName;
	CString infileTitle;
};


#endif