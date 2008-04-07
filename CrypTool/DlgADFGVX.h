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
#include "adfgvx.h"
#include <string>

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
	CString password;
	CString pwdString;
	CString matrix[6][6];
	CBitmapButton buttonInsertKey;
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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedErasematrix();
	afx_msg void OnEnChangeTextfieldPassword();
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
	BOOL boxNewLine2;
	BOOL boxNewLine1;

public:
	CDlgADFGVX(char* infile, CString oldTitle, CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgADFGVX();

	afx_msg void OnBnClickedButtonStringbox();
	afx_msg void OnBnClickedButtonTextOptions();
};
