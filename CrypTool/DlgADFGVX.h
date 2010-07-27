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
#include "adfgvx.h"
#include <string>
#include "AlphabetTextEdit.h"
#include "ToolTipButton.h"

// CDlgADFGVX-Dialogfeld

using namespace std;

class CDlgADFGVX : public CDialog
{
	DECLARE_DYNAMIC(CDlgADFGVX)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	DECLARE_MESSAGE_MAP()

private:
	adfgvx* cipher;
	//variables from textfields and controls of the dialog
	CString pwdString;
	CString matrix[6][6];
	CToolTipButton buttonInsertKey;
	void CDlgADFGVX::OnOK();
	void CDlgADFGVX::Decrypt();
	void CDlgADFGVX::Encrypt();
	bool restart;
	BOOL printStage1;
	BOOL newLineStage2, newLineStage1;
	int blockSizeStage2, blockSizeStage1;
	int validCiphertext;
	int validPassword;
	CString oldEntry;
	//variables used in handler methods
	char* infile;
	CString oldTitle;
	bool pwdInvalid;
	bool pwdDouble;
	
	basic_string <char>::iterator strIterTyp;


	//Dialogfelddaten
	enum { IDD = IDD_ADFGVX };
	afx_msg void OnBnClickedButtonEncrypt();
	afx_msg void OnBnClickedButtonDecrypt();
	afx_msg void OnBnClickedButtonInsertKey();
	afx_msg void OnBnClickedMatrixShuffle();
	afx_msg void OnBnClickedMatrixStandard();
	afx_msg void OnBnClickedCheckOutputStage1();
	afx_msg void OnOk();
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
	afx_msg void OnChangedTranspositionPassword();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedErasematrix();
	afx_msg void OnBnClickedCheckBlockStage2();
	afx_msg void OnBnClickedCheckBlockStage1();
	BOOL CDlgADFGVX::OnInitDialog();
	CString CDlgADFGVX::CheckInput(CString oldEntry, CString input);
	void CDlgADFGVX::CheckProgress();
	CString numberedPassword;
	BOOL boxBlockOutput2;
	BOOL boxBlockOutput1;
	BOOL boxOutput1;
	CEdit editBlockLength2;
	CEdit editBlockLength1;
	CAlphabetTextEdit editTranspositionPassword;
	BOOL boxNewLine2;
	BOOL boxNewLine1;

public:
	CDlgADFGVX(char* infile, CString oldTitle, CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgADFGVX();

	afx_msg void OnBnClickedButtonStringbox();
	afx_msg void OnBnClickedButtonTextOptions();
};
