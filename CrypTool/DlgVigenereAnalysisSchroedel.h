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
#include <map>

#if _MSC_VER > 1000
#pragma once
#endif

#define MAX_NUMBER_OF_DICT_WORDS 500000

// forward declaration
class CDlgVigenereAnalysisSchroedel;
class CDlgVigenereAnalysisSchroedelChooseKeywordLanguages;
class CDlgVigenereAnalysisSchroedelChooseCiphertextLanguage;

// this struct contains a possible result (key, cleartext, rating)
struct PossibleResult {
	CString key;
	CString cleartext;
	int rating;
};

// this struct represents a set of digrams and trigrams
struct DigramTrigramSet {
	CString digramFactorString;
	int digrams[26][26];
	int trigrams[26][26][26];
};

// 06/24/2009, flomar: Vigenere analysis class
// (originally written by Schroedel in Pascal, ported to C++ by flomar)
class VigenereAnalysisSchroedel {

public:
	// constructor
	VigenereAnalysisSchroedel(CDlgVigenereAnalysisSchroedel *_dialog, const CString _ciphertextFileName, const CString _title);
	// destructor
	~VigenereAnalysisSchroedel();

	// this function runs the analysis
	unsigned int run();

	// returns the progress of the analysis ([0.0-1.0])
	double getProgress() { return progress; };
	// returns the file name of the result file
	CString getResultFileName() const { return resultFileName; };

	// this function cancels the analysis
	void cancel() { canceled = true; };

	// is the analysis canceled?
	bool isCanceled() const { return canceled; };
	// is the analysis done?
	bool isDone() const { return done; };
	// is the analysis successful? ([a] it is done and [b] there is at least one possible result)
	bool isSuccessful() const { return done && listPossibleResults.size() > 0; };
	// is debug output tracked?
	bool isDebug() const { return debug; };

	// return the result log
	CString getResult() const { return result; };
	// return the result log (including debug information)
	CString getResultDebug() const { return resultDebug; };

	// write the result file (setting the flag overrides the class-wide debug flag)
	void writeResultFile(const bool _debug = false);

protected:
	// initialize the analysis (this should be called from within the run() function)
	void initialize();
	// read some settings from the registry
	void readSettingsFromRegistry();

	// some preparational functions
	int readCiphertext();
	int readDict();
	int readTriDigrams();
	int chooseLanguages();
	// the actual analysis functions
	int firstChar();
	int secondChar();
	int solveTrigram();

	// appends a string to the result file (setting the flag overrides the class-wide debug flag)
	void output(CString str, const bool _debug = false);

	// this treshold is used to determine if a result might be considered correct
	int analysisThreshold;

	// this is used for timing purposes
	time_t timeAnalysisStart;
	time_t timeAnalysisEnd;

	// this flag indicates if the analysis was canceled
	bool canceled;
	// this flag indicates we're in debug mode (thus, much more detailed output)
	bool debug;
	// this flag indicates if the analysis is done
	bool done;

	// this list contains all possible results
	std::list<PossibleResult> listPossibleResults;

	// this string holds the analysis results (see result file)
	CString result;
	// this string holds the analysis results INCLUDING debug output
	CString resultDebug;
	// the name of the result file
	CString resultFileName;

	// the progress of the analysis [0.0-1.0]
	double progress;

	// a map of lists of dictionary words for each language
	std::map<std::string, std::list<std::string>> mapListsDictionaryWords;
	// a map of digrams and trigrams for each language
	std::map<std::string, DigramTrigramSet> mapDigramsTrigrams;

	// the dialog object (the dialog in which the analysis is displayed)
	CDlgVigenereAnalysisSchroedel *theDialog;

	CString ciphertext;
	CString ciphertextFileName;
	CString title;

	CString pathToDictionary;
	CString pathToDigrams;
	CString pathToTrigrams;

	// internal variables
	unsigned int startzeit, endezeit;
	CString cDigramFactorString;
	int cDigram[26][26];
	int cTrigram[26][26][26];
	CString pairs[26*26*26][2];
	unsigned int score[26*26*26][2];
	CString _pairs[26*26*26][2];
	unsigned int _score[26*26*26][2];
	int remain, maxDi, maxTri, xDict, cPairs;
	unsigned int maxProzent;
	CString vigenere[30];
	CString solvers[1000][4];  
	CString dict[MAX_NUMBER_OF_DICT_WORDS];
	int solveCount, maxRating, dictCount;
	int solveRating;
	CString solveText, solveKey;
	int subRate;
	int cipherPos, aktPos, Pos2, Pos3, Remain2, Remain3;

	// some helper functions
	CString encryptText(CString text, CString key);
	CString decryptText(CString text, CString key);
	int rateString(CString str, CString key);
	CString fillLeft(CString was, int wie);
	
	// some helper variables
	CString outputString;
	CString formatString;

	// flomar, 03/03/2010
	bool isDefaultResourceLocationValid();
	void bendResourceLocationsBackToDefault();
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

// TODO
class CDlgVigenereAnalysisSchroedelChooseLanguages : public CDialog
{
	DECLARE_DYNAMIC(CDlgVigenereAnalysisSchroedelChooseLanguages)

public:
	CDlgVigenereAnalysisSchroedelChooseLanguages(std::map<std::string, std::list<std::string>> &_mapListsDictionaryWords, std::map<std::string, DigramTrigramSet> &_mapDigramsTrigrams, CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgVigenereAnalysisSchroedelChooseLanguages();

// Dialogfelddaten
	enum { IDD = IDD_VIGENERE_ANALYSIS_SCHROEDEL_CHOOSE_LANGUAGES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

	// the map of lists of all dictionary words (by language)
	std::map<std::string, std::list<std::string>> mapListsDictionaryWords;
	// the map of all digrams/trigrams (by language)
	std::map<std::string, DigramTrigramSet> mapDigramsTrigrams;

	// control for the list of keyword languages
	CCheckListBox listBoxLanguagesKeyword;
	// control for the list of ciphertext languages
	CCheckListBox listBoxLanguagesCiphertext;

public:
	// the list of selected keywords (this is compiled from ALL selected languages)
	std::list<std::string> selectedKeywordsList;
	// the digram/trigram set of the selected language
	DigramTrigramSet selectedDigramTrigramSet;
};

#endif