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

#if !defined(AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_)
#define AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPermutation.h : Header-Datei
//
#include "AscEdit.h"
#include "Cryptography.h"
#include "DlgKeyPermutationInfo.h"
#include "afxwin.h"
#include "ToolTipButton.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutation 

// #define MAX_PERM_LENGTH <Innerhalb der Datei AscEdit.h defniert>

#define INV_TOKEN		"INV, "
#define PARAM_TOKEN		"PARAMETER: "
#define TEXT_TOKEN		"TEXT, "
#define BINARY_TOKEN	"BINARY, "

class CDlgKeyPermutation : public CDialog
{
	CToolTipButton m_Paste;
	// Konstruktion
public:
	int MakePermInt(CString *Pin, int p[], int pinv[]);
	CString makeASCII( CString &line);
	int PrintPerm(char *dest, int *perm, int len);
	int m_Dec;
	int MakePerm(CString *Pin, int p[MAX_PERM_LENGTH], int pinv[MAX_PERM_LENGTH]);
	int m_P1[MAX_PERM_LENGTH];
	int m_P1inv[MAX_PERM_LENGTH];
	int m_P1len;
	int m_P2[MAX_PERM_LENGTH];
	int m_P2inv[MAX_PERM_LENGTH];
	int m_P2len;
	CDlgKeyPermutation(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyPermutation)
	enum { IDD = IDD_KEY_PERMUTATION };
	CButton	 m_Decrypt;
	CButton	 m_Encrypt;
	CButton  chk_showPermutations;
	CAscEdit m_CPerm2;
	CAscEdit m_CPerm1;
	CString  m_Perm1;
	CString	 m_Perm2;
	CString	 m_P1out;
	CString	 m_P2out;
	int		 m_P1InSeq;
	int		 m_P1OutSeq;
	int		 m_P2InSeq;
	int		 m_P2OutSeq;
	int		 m_P1Perm;
	int		 m_P2Perm;
	int		 m_DataType;
	BOOL	 m_Invert;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyPermutation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyPermutation)
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnPasteKey();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnRadioButtonBinaryData();
	afx_msg void OnRadioButtonText();
	afx_msg void OnTextOptions();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void setInputFilename(CString _inputFilename);
private:
	bool doesInputComplyWithAlphabet();
	CString inputFilename;

	// Required because of BACK-Button from CDlgKeyPermutationInfo !!!
	int  readKeyParam(CString &buffer); // TRUE, if Parameters were found
	void strKeyParam();
	void writeRegistry();
	int  chekPermInput(CString &m_Perm, CAscEdit &cInput, int MSG_ID );
public:
	int ShowPermutations();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_
