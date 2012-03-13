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

#include "adfgvx.h"
#include "afxwin.h"
#include <string>
#include <AlphabetTextEdit.h>
#include "ToolTipButton.h"

// CDlgAdfgvxManual-Dialogfeld
using namespace std;

class CDlgAdfgvxManual : public CDialog
{
	DECLARE_DYNAMIC(CDlgAdfgvxManual)

public:
	CDlgAdfgvxManual::CDlgAdfgvxManual(char* infile, CString oldTitle, CWnd* pParent);
	//CDlgAdfgvxManual(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgAdfgvxManual();

// Dialogfelddaten
	// Dialogfelddaten
	//{{AFX_DATA(CDlgAdfgvxManual)
	enum { IDD = IDD_ADFGVX_MANUAL };
	int maxLength;
	int minLength;
	// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA

	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgAdfgvxManual)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

		// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgAdfgvxManual)
	afx_msg void OnBnClickedNextPermutation(); 
	afx_msg void OnEnChangeM00();
	afx_msg void OnEnChangeM01();
	afx_msg void OnEnChangeM02();
	afx_msg void OnEnChangeM03();
	afx_msg void OnEnChangeM04();
	afx_msg void OnEnChangeM05();
	afx_msg void OnEnChangeM10();
	afx_msg void OnEnChangeM11();
	afx_msg void OnEnChangeM12();
	afx_msg void OnEnChangeM13();
	afx_msg void OnEnChangeM14();
	afx_msg void OnEnChangeM15();
	afx_msg void OnEnChangeM20();
	afx_msg void OnEnChangeM21();
	afx_msg void OnEnChangeM22();
	afx_msg void OnEnChangeM23();
	afx_msg void OnEnChangeM24();
	afx_msg void OnEnChangeM25();
	afx_msg void OnEnChangeM30();
	afx_msg void OnEnChangeM31();
	afx_msg void OnEnChangeM32();
	afx_msg void OnEnChangeM33();
	afx_msg void OnEnChangeM34();
	afx_msg void OnEnChangeM35();
	afx_msg void OnEnChangeM40();
	afx_msg void OnEnChangeM41();
	afx_msg void OnEnChangeM42();
	afx_msg void OnEnChangeM43();
	afx_msg void OnEnChangeM44();
	afx_msg void OnEnChangeM45();
	afx_msg void OnEnChangeM50();
	afx_msg void OnEnChangeM51();
	afx_msg void OnEnChangeM52();
	afx_msg void OnEnChangeM53();
	afx_msg void OnEnChangeM54();
	afx_msg void OnEnChangeM55();
	afx_msg void OnBnClickedOk();
	afx_msg void UpdateRemChars();
	afx_msg void OnCbnSelchangeMaxlength();
	afx_msg void OnCbnSelchangeMinlength();
	afx_msg void OnBnClickedButtonForce();
	afx_msg void OnBnClickedResetMatrix();
	afx_msg void OnBnClickedInsertKey();
	afx_msg void OnChangedTranspositionPassword();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
  //set the 5 most common letters from the reference text
  void SetFrequenciesFromReference();
	adfgvx* cipher;
	CString matrix[6][6];
	CString plaintext;
	double remaining;
	CString remChars;
	void Resubstitute();
	int validCipherText;
	//variables used in handler methods
	char* infile;
	CString oldTitle;
	CString oldEntry;
	basic_string <char>::iterator strIterTyp;	
	CString CDlgAdfgvxManual::CheckInput(CString oldEntry, CString input);
	CString numberedPassword;
	bool analysed;
	int validCiphertext;
	CButton buttonResetMatrix;
	CButton buttonStringBox;
	CButton buttonStdMatrix;
	CToolTipButton c_insertKey;
	bool iGotOne;
	CString subKey;
	int counter;
	CButton buttonOutput;
	afx_msg void OnBnClickedMatrixStandard();
	afx_msg void OnBnClickedButtonTextOptions();
	CAlphabetTextEdit editTranspositionPassword;

public:
	BOOL CDlgAdfgvxManual::OnInitDialog();
	void CDlgAdfgvxManual::Permutate();

	afx_msg void OnBnClickedButtonStringbox();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.
