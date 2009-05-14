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

// für animierte GIFs
#include "PictureEx.h"

// CDlgCrtAstronomy-Dialogfeld

class CDlgCrtAstronomy : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrtAstronomy)

public:
	CDlgCrtAstronomy(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgCrtAstronomy();

// Dialogfelddaten
	enum { IDD = IDD_CRT_ASTRONOMY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	// CPictureExLoop m_Picture;
	CPictureEx m_Picture;
	CString m_a0;
	CString m_a1;
	CString m_a2;
	CString m_a3;
	CString m_a4;
	CString m_a5;
	CString m_a6;
	CString m_a7;
	CString m_a8;
	CString m_m0;
	CString m_m1;
	CString m_m2;
	CString m_m3;
	CString m_m4;
	CString m_m5;
	CString m_m6;
	CString m_m7;
	CString m_m8;
	CString m_x;
	CString m_M;
	CString m_merkurtag;
	CString m_erdetag;
	BOOL m_merkur;
	BOOL m_venus;
	BOOL m_erde;
	BOOL m_mars;
	BOOL m_jupiter;
	BOOL m_saturn;
	BOOL m_uranus;
	BOOL m_neptun;
	BOOL m_pluto;
	CEdit m_control_m0;
	CEdit m_control_m1;
	CEdit m_control_m2;
	CEdit m_control_m3;
	CEdit m_control_m4;
	CEdit m_control_m5;
	CEdit m_control_m6;
	CEdit m_control_m7;
	CEdit m_control_m8;
	afx_msg void OnEnChangeCrtAstronomyEdita0();
	afx_msg void OnEnChangeCrtAstronomyEdita1();
	afx_msg void OnEnChangeCrtAstronomyEdita2();
	afx_msg void OnEnChangeCrtAstronomyEdita3();
	afx_msg void OnEnChangeCrtAstronomyEdita4();
	afx_msg void OnEnChangeCrtAstronomyEdita5();
	afx_msg void OnEnChangeCrtAstronomyEdita6();
	afx_msg void OnEnChangeCrtAstronomyEdita7();
	afx_msg void OnEnChangeCrtAstronomyEdita8();
	afx_msg void OnEnChangeCrtAstronomyEditm0();
	afx_msg void OnEnChangeCrtAstronomyEditm1();
	afx_msg void OnEnChangeCrtAstronomyEditm2();
	afx_msg void OnEnChangeCrtAstronomyEditm3();
	afx_msg void OnEnChangeCrtAstronomyEditm4();
	afx_msg void OnEnChangeCrtAstronomyEditm5();
	afx_msg void OnEnChangeCrtAstronomyEditm6();
	afx_msg void OnEnChangeCrtAstronomyEditm7();
	afx_msg void OnEnChangeCrtAstronomyEditm8();
	afx_msg void OnBnClickedCrtAstronomyButtonsolve();
	afx_msg void OnBnClickedCrtAstronomyButtonreset();
	afx_msg void OnBnClickedCrtAstronomyButtonreset2();
	afx_msg void OnBnClickedCrtAstronomyButtonend();
	afx_msg void OnBnClickedCrtAstronomyCheckmercury();
	afx_msg void OnBnClickedCrtAstronomyCheckvenus();
	afx_msg void OnBnClickedCrtAstronomyCheckearth();
	afx_msg void OnBnClickedCrtAstronomyCheckmars();
	afx_msg void OnBnClickedCrtAstronomyCheckjupiter();
	afx_msg void OnBnClickedCrtAstronomyChecksaturn();
	afx_msg void OnBnClickedCrtAstronomyCheckuranus();
	afx_msg void OnBnClickedCrtAstronomyCheckneptun();
	afx_msg void OnBnClickedCrtAstronomyCheckpluto();
	void testdata(void);
	CString tausender (CString text);
	int werteauslesen(Big a[],Big m[]);
	bool testeteilerfremd();
	Big ChinRest (int anzahl,Big a[],Big m[]);
	Big suczessive(int anzahl,Big a[],Big m[]);
	afx_msg void OnStnClickedImage();
};
