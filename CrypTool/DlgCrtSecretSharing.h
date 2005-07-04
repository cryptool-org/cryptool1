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
	afx_msg void OnBnClickedSecretsharingAlgo();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSecretsharingSolve();
	BOOL GetRandomPrime(CString &OutStr, GeneratePrimes &P);
	void GeneratePrime(int anzahl, Big primes[]);
	afx_msg void OnBnClickedSecretsharingReset();
	void TestSecretSharing();
	Big ChinRest (int anzahl,Big a[],Big m[]);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedSecretsharingFacts();
	afx_msg void OnBnClickedSecretsharingLog();
	afx_msg void OnBnClickedOk();
	BOOL m_noInfo;
};
