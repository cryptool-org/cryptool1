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

#ifndef _DLGFINDANDREPLACE_H_
#define _DLGFINDANDREPLACE_H_

// DlgFindAndReplace.h

#include "HexEdit.h"

#include <vector>

// global vector for previously used FIND terms
extern std::vector<CString> termsFind;
// global vector for previously used REPLACE terms
extern std::vector<CString> termsReplace;

class CDlgFindAndReplace : public CDialog
{
	DECLARE_DYNAMIC(CDlgFindAndReplace)

public:
	CDlgFindAndReplace(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFindAndReplace();

	// bring dialog window to foreground (make it visible)
	void show();

	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonReplace();
	afx_msg void OnBnClickedButtonReplaceAll();
	afx_msg void OnBnClickedRadioTextMode();
	afx_msg void OnBnClickedRadioHexMode();

	CString textFind;
	CString textReplace;
	CString textFindHex;
	CString textReplaceHex;

// Dialog Data
	enum { IDD = IDD_FIND_AND_REPLACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

private:
	// handles to our Scintilla windows
	HWND handleScintillaWindowFind;
	HWND handleScintillaWindowReplace;

	// hex edit fields for hex mode
	CHexEdit hexEditControlFind;
	CHexEdit hexEditControlReplace;

	// radio button for text mode
	CButton radioButtonControlText;
	// radio button for hex mode
	CButton radioButtonControlHex;

	void updateMode();

	BOOL checkCaseSensitive;
	BOOL checkFindBackwards;
	BOOL checkRegularExpressions;

	// has dialog window already been created? (MODELESS dialog!)
	bool created;
	// overridden OnCancel (MODELESS dialog!)
	virtual void OnCancel();

	void OnBnClickedButtonFind(bool replace, bool all);
	void DoFindReplace(bool replace, bool all);
	void DoFindReplaceScintilla(CWnd *pWindow, bool replace, bool all);
	void DoFindReplaceHexEdit(CWnd *pWindow, bool replace, bool all);
};

#endif
