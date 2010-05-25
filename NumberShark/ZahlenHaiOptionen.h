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

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <map>

#include "EvoZahlenHai.h"
#include "DlgSearchProgress.h"

// flomar, 05/05/2010
// this is used for a much clearer code
struct GameDataBlock {
	CString limit;
	CString score;
	CString sequence;
	CString sequenceLength;
	CString leadingPrime;
	bool proved;

	// default construction
	GameDataBlock() {
		proved = false;
	};

	// construction
	GameDataBlock(const CString &_limit, const CString &_score, const CString &_sequence, const CString &_sequenceLength, const CString &_leadingPrime, const bool &_proved) {
		limit = _limit;
		score = _score;
		sequence = _sequence;
		sequenceLength = _sequenceLength;
		leadingPrime = _leadingPrime;
		proved = _proved;
	};
};

enum SearchStatus {
	RUNNING,
	ABORTED,
	DONE
};

// ZahlenHaiOptionen-Dialogfeld

class ZahlenHaiOptionen : public CDialog
{

	DECLARE_DYNAMIC(ZahlenHaiOptionen)
	
	

public:
	ZahlenHaiOptionen(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~ZahlenHaiOptionen();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:

	CTabCtrl dialogOptionsTab;
	
	CStatic optionenButtonMax;
	CButton checkButton;
	CButton checkButtonOption;
	CButton checkStartNumber;
	CButton radioButton1;
	CButton radioButton2;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButtonMax();
	afx_msg void OnBnClickedRadioMax1();
	afx_msg void OnBnClickedRadioMax2();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL showToolTips;
	BOOL showOption;
    BOOL showStartNumber;
	
	int calcUpperLimit;
	int calculateMaxNew;
	int showMax;
	int optionenUpperLimit;

	CString playername;
	CString optionStart;
	CString optionToolTip;
	CString optionGameStart;
	CString optionRemember;
	CString optionenMaxP;
	
	void drawStartTab();
	void drawOptionsTab();
	CString gameIdea;
	CString disclaimerText;
	CString infoText;
	CStatic accControl;

protected:
	// flomar, 05/05/2010
	// the following variables and functions are part of a major bug fix; due to 
	// time constraints I decided to *NOT* completely re-write the relevant parts

	std::map<int, GameDataBlock> mapPrecalculatedScores;

	void calculateMaximumScore();

	EvoZahlenHai hai;

public:
	void readGameData();
	CString readGameDataBlock(CString &data);

	CDlgSearchProgress dialogSearchProgress;

	// access method, see above
	void setEvoZahlenHai(EvoZahlenHai &_hai) { hai = _hai; };

	// access methods only, see above
	std::map<int, GameDataBlock> getMapPrecalculatedScores() { return mapPrecalculatedScores; };
};