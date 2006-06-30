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

#include "adfgvx.h"
#include "afxwin.h"
#include <string>

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
	afx_msg void OnBnClickedResubstitute();
	afx_msg void OnBnClickedInsertKey();
	afx_msg void OnCbnEditchangePasswordBox();
	afx_msg void OnCbnSelchangePasswordBox();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
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
	CString pwdList[50];
	void CDlgAdfgvxManual::PwdEnqueue(CString pwd);
	CComboBox pwdListBox;
	CString password;
	CButton buttonResub;
	CButton buttonResetMatrix;
	CButton buttonStringBox;
	CButton buttonStdMatrix;
	CBitmapButton c_insertKey;
	bool iGotOne;
	CString subKey;
	int counter;
	CButton buttonOutput;
	afx_msg void OnBnClickedMatrixStandard();

public:
	friend static CDlgAdfgvxManual::UINT StaticThread(LPVOID param);
	BOOL CDlgAdfgvxManual::OnInitDialog();
	void CDlgAdfgvxManual::Permutate();

	afx_msg void OnBnClickedButtonStringbox();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.
