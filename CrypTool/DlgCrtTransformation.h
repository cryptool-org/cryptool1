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
