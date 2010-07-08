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

#ifndef _NUMBEREDIT_H_
#define _NUMBEREDIT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TODO
class CNumberEdit : public CEdit
{
// Konstruktion
public:
	CNumberEdit();
	virtual ~CNumberEdit();

	// this returns the pure number as CString (without digit groupings)
	CString getNumberAsCString();

	// this sets the number (and implicitly formats it properly)
	void setNumber(const CString &_number);
	// this sets a text (without any format changes; i.e. used for displaying info messages)
	void setText(const CString &_text);

protected:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnPaste(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()

private:
	// these are initialized at construction, they should NOT be changed
	char theIntegralSeparator;
	char theFractionalSeparator;

	// this is our number as a whole (as displayed in the edit field)
	CString stringNumber;

	// this is the current selection
	int selectionStart;
	int selectionEnd;

	// some internal stuff for formatting the string number
	bool showIntegralSeparators;
	void adjustNumberFormat();
};

#endif