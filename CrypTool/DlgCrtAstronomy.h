/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/



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
