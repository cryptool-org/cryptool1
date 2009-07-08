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

#if _MSC_VER > 1000
#pragma once
#endif

// forward declaration
class CDlgVigenereAnalysisSchroedel;

// 06/24/2009, flomar: Vigenere analysis class
// (originally written by Schroedel in Pascal, ported to C++ by flomar)
class VigenereAnalysisSchroedel {

private:
	// this is ugly, but it's the simplest way to connect GUI and model (sort of)
	CDlgVigenereAnalysisSchroedel *theDialog;

public:
	// constructor initializing the dialog object
	VigenereAnalysisSchroedel(CDlgVigenereAnalysisSchroedel *dlg);
	// destructor
	~VigenereAnalysisSchroedel();

private:
	// internal variables
	unsigned int startzeit, endezeit;
	int cDigram[26][26];
	int cTrigram[26][26][26];
	CString pairs[26*26*26][2];
	unsigned int score[26*26*26][2];
	CString _pairs[26*26*26][2];
	unsigned int _score[26*26*26][2];
	int remain, maxDi, maxTri, maxProzent, xDict, xlDict, cPairs;
	CString vigenere;
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
	void readTriDigrams();
	void firstChar();
	void secondChar();
	void solveTrigram();
	void readDict();
	void outputSave(CString a1, CString a2, CString a3, CString a4, CString a5, CString a6, CString a7);
	CString encryptText(CString text, CString key);
	CString decryptText(CString text, CString key);
	int rateString(CString str, CString key);
	CString fillLeft(CString was, int wie);

};

// CDlgVigenereAnalysisSchroedel dialog

class CDlgVigenereAnalysisSchroedel : public CDialog
{
	DECLARE_DYNAMIC(CDlgVigenereAnalysisSchroedel)

public:
	CDlgVigenereAnalysisSchroedel(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgVigenereAnalysisSchroedel();

// Dialog Data
	enum { IDD = IDD_VIGENERE_ANALYSIS_SCHROEDEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CString ciphertext;
	CString plaintext;
	CString key;
	CString edit1;

	VigenereAnalysisSchroedel *theAnalysis;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

#endif