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


// CDlgCrtTransformation-Dialogfeld

class CDlgCrtTransformation : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrtTransformation)

public:
	CDlgCrtTransformation(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtTransformation();

// Dialogfelddaten
	enum { IDD = IDD_CRT_TRANSFORMATION };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString m_a;
	CString m_b;
	CString m_m0;
	CString m_m1;
	CString m_m2;
	CString m_m3;
	CString m_m4;
	CString m_bereich;
	CString m_ma;
	CString m_mb;
	CString m_mab;
	CString m_basis;
	CString m_x;
	CString m_rueck;
	CString m_primex;
	CString m_primey;
	CEdit m_control_m0;
	CEdit m_control_m1;
	CEdit m_control_m2;
	CEdit m_control_m3;
	CEdit m_control_m4;
	CEdit m_control_anzahl;
	int m_anzahl;
	int m_radio;
	CEdit	m_control_primex;
	CEdit	m_control_primey;
	afx_msg void OnBnClickedGenerate1();
	afx_msg void OnBnClickedCrtTransformationRadio1();
	afx_msg void OnBnClickedCrtTransformationRadio2();
	afx_msg void OnBnClickedCrtTransformationRadio3();
	afx_msg void OnBnClickedCrtTransformationButtonsolve();
	afx_msg void OnBnClickedCrtTransformationButtonreset();
	afx_msg void OnBnClickedCrtTransformationButtonend();
	afx_msg void OnEnChangeCrtTransformationEdita0();
	afx_msg void OnEnChangeCrtTransformationEdita1();
	afx_msg void OnEnChangeCrtTransformationEditm0();
	afx_msg void OnEnChangeCrtTransformationEditm1();
	afx_msg void OnEnChangeCrtTransformationEditm2();
	afx_msg void OnEnChangeCrtTransformationEditm3();
	afx_msg void OnEnChangeCrtTransformationEditm4();
	afx_msg void OnEnChangeCrtTransformationEditanzahl();
	afx_msg void OnEnChangeCrtTransformationEditx();
	afx_msg void OnEnChangeCrtTransformationEdity();
	void GeneratePrime(int anzahl);
	BOOL GetRandomPrime(CString &OutStr, GeneratePrimes &P);
	void testdata(void);
    CString BigVektorToCString(Big myarray[],int anzahl);
	int werteauslesen(Big m[]);
	bool testeteilerfremd();
	CString tausender (CString text);
	int m_radiogenerate;
	afx_msg void OnBnClickedGenerateradio1();
	afx_msg void OnBnClickedGenerateradio2();
};
