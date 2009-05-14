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
#include "PrimeTestAKS.h"
#include "DlgShowProgress.h"

//#define PRIMETEST_TIME_MEASUREMENT

// CDlgPrimeTest-Dialogfeld

class CDlgPrimeTest : public CDialog, public CProgressModel
{
	DECLARE_DYNAMIC(CDlgPrimeTest)

public:

  CDlgPrimeTest(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgPrimeTest();

// Dialogfelddaten
	enum { IDD = IDD_PRIME_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
  
	DECLARE_MESSAGE_MAP()

  CString inputNumber;          // holds checked and converted input number 
  PrimeTestAKS *pAKS;	// pointer to AKS object during thread execution
  void UpdateResultField(int result, CString text);
public:
  afx_msg void OnBnClickedPrimetestButtonTest();
  afx_msg void OnBnClickedPrimetestButtonCancel();
  afx_msg void OnBnClickedPrimetestButtonLoadnumber();
  afx_msg void OnBnClickedPrimetestRadio();
  afx_msg void OnEnChangePrimetestEditNumber();
  afx_msg void OnBnClickedButtonJumpToFactorization();

  virtual BOOL OnInitDialog();

  virtual double getProgress();
  void runAKS();

  CEdit m_Result;               // member field for CEditResult
  CEdit m_control_editName;     
  CString m_editNumber;         // member field for CEditNumber
  CButton m_control_buttonJumpToFactorization;
  int m_radio;                  // member field for CRadio
  int m_algo;                   // holds chosen algorithm (set by radio buttons)
  
  CStatic m_picPrime;
  CStatic m_picNotPrime;

#ifdef PRIMETEST_TIME_MEASUREMENT
  // Time required by the prime test algo
  double algoTime;
#endif
};
