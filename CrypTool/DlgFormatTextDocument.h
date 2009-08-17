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

#ifndef _DLGFORMATTEXTDOCUMENT_
#define _DLGFORMATTEXTDOCUMENT_

class CDlgFormatTextDocument : public CDialog
{
	DECLARE_DYNAMIC(CDlgFormatTextDocument)

public:
	CDlgFormatTextDocument(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CDlgFormatTextDocument();

	// this function formats a text (specified with a file name) using the parameters in the dialog
	CString format(CString fileName);

// Dialogfelddaten
	enum { IDD = IDD_FORMAT_TEXT_DOCUMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	int removeNonAlphabetCharacters;
	int convertToUppercase;
	int convertToLowercase;
	int divideInBlocks;
	CString blockSize;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckRemoveNonAlphabetCharacters();
	afx_msg void OnBnClickedCheckConvertToUppercase();
	afx_msg void OnBnClickedCheckConvertToLowercase();
	afx_msg void OnBnClickedCheckDivideInBlocks();
	afx_msg void OnBnClickedTextoptions();
};

#endif