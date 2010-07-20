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

#ifndef _ALPHABETTEXTEDIT_H_
#define _ALPHABETTEXTEDIT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TODO
class CAlphabetTextEdit : public CEdit
{
// Konstruktion
public:
	CAlphabetTextEdit();
	virtual ~CAlphabetTextEdit();

	void setText(const CString &_text);
	CString getText();

	// call this function to update the string text, i.e. to remove invalid characters
	void updateText();

protected:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);

	// functions for copy/paste and other stuff
	void onEditCut();
	void onEditCopy();
	void onEditPaste();
	void onEditSelectAll();

	DECLARE_MESSAGE_MAP()

private:
	// this the text within our edit field
	CString stringText;

	// this is the current selection
	int selectionStart;
	int selectionEnd;
};

#endif