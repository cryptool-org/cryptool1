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

#include "PictureEx.h"	
#include "afxwin.h"
// CDlgCrtSecretSharing-Dialogfeld

class CDlgCrtSecretSharing : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrtSecretSharing)

public:
	CDlgCrtSecretSharing(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtSecretSharing();

// Dialogfelddaten
	enum { IDD = IDD_CRT_SECRETSHARING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int m_anzahl;
	int m_need;
	CString m_x;
	CString m_y;
	CString m_m0;
	CString m_m1;
	CString m_m2;
	CString m_m3;
	CString m_m4;
	CString m_m5;
	CString m_m6;
	CString m_a0;
	CString m_a1;
	CString m_a2;
	CString m_a3;
	CString m_a4;
	CString m_a5;
	CString m_a6;
	CString m_diverse;
	CString m_reka0;
	CString m_reka1;
	CString m_reka2;
	CString m_reka3;
	CString m_reka4;
	CString m_reka5;
	CString m_reka6;
	CString m_s;
	CString m_w;
	CString m_maxkminus1;
	CString m_faktorA;
	CString m_s_;
	CString m_log;
	CPictureEx m_Picture;
	afx_msg void OnBnClickedSecretsharingAdd1();
	afx_msg void OnBnClickedSecretsharingAdd2();
	afx_msg void OnBnClickedSecretsharingAdd3();
	afx_msg void OnBnClickedSecretsharingAdd4();
	afx_msg void OnBnClickedSecretsharingAdd5();
	afx_msg void OnBnClickedSecretsharingAdd6();
	afx_msg void OnBnClickedSecretsharingAdd7();
	afx_msg void OnBnClickedSecretsharingEnd();
	afx_msg void OnBnClickedSecretsharingShare();
	afx_msg void OnBnClickedSecretsharingOptions();
	afx_msg void OnBnClickedSecretsharingFacts();
	afx_msg void OnBnClickedSecretsharingLog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSecretsharingReset();
	void GeneratePrime(int anzahl, Big primes[]);
	void OnBnClickedSecretsharingSolve();
	void PrepareManual(Big primes[]);
	void Calculate(Big primes[]);
	bool CheckFields();
	Big ChinRest (int anzahl,Big a[],Big m[]);
	BOOL GetRandomPrime(CString &OutStr, GeneratePrimes &P);
	BOOL m_Info;
	int m_calcmode;
	afx_msg void OnBnClickedCrtRadioAut();
	afx_msg void OnBnClickedCrtRadioMan();
};
