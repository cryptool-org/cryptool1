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

#if !defined(AFX_DLG_PLAYFAIRKEY_H__B5942C33_4DBD_11D4_A048_002035F23D41__INCLUDED_)
#define AFX_DLG_PLAYFAIRKEY_H__B5942C33_4DBD_11D4_A048_002035F23D41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#include <PlayfairAnalysis.h>
#include "ToolTipButton.h"

// Dlg_PlayfairKey.h : Header-Datei
//

#define STR_OPT_SEPERATE_DUPLICATE_ONLY_WITHIN_PAIRS ", OPT_SEPERATE_DUPLICATE_ONLY_WITHIN_PAIRS"
#define STR_OPT_IGNORE_DUPLICATE_LETTERS_IN_KEY		 ", OPT_IGNORE_DUPLICATE_LETTERS_IN_KEY"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPlayfair 

class CDlgKeyPlayfair : public CDialog
{
	CToolTipButton m_Paste;
	// Konstruktion
protected:
	int decryption;
	CString fileNameCleartext;
	CString fileNameCiphertext;
	int separateDoubleCharacters;
	CString separator1;
	CString separator2;
	int separateDoubleCharactersOnlyWithinPairs;
	int ignoreDoubleCharactersInKey;
public:
	~CDlgKeyPlayfair();
	CDlgKeyPlayfair(const char *infile, const char *outfile, int reformat, int convert, CWnd* pParent = NULL);   // Standardkonstruktor

	char *GetData();
	int Display();

	CPlayfairAnalysis *m_Alg;

public:
// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyPlayfair)
	enum { IDD = IDD_KEY_PLAYFAIR };
	int		m_sechs;
	CString m_text;
	CEdit	m_text_ctl;
	CString m_mat[6][6];
	CButton m_matc[11];

	PlayfairOptions getPlayfairOptions();
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyPlayfair)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyPlayfair)
	afx_msg void OnSechs();
	afx_msg void OnCheck();
	afx_msg void OnChange();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnPasteKey();
	afx_msg void OnChangeSeparator();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLG_PLAYFAIRKEY_H__B5942C33_4DBD_11D4_A048_002035F23D41__INCLUDED_
