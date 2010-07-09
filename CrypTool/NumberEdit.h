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

	// this returns the pure number as CString (without digit groupings); it may contain 
	// a sign, an integral part, a fractional separator, and the fractional part; however, 
	// this function does not return a string that is compliant to the current language-- 
	// the fractional separator is ALWAYS a colon (".") due to the C++ language constraints
	CString getNumberAsCString();

	// see function above; in contrast, this function always uses the language-dependent 
	// fractional separator; so keep this in mind: using this function for computing rather 
	// than mere displaying may yield unexpected (WRONG!) results-- you have been warned; 
	// the parameter "withDigitGroupings" indicates if there should be integral separators
	CString getNumberAsCStringLanguageDependent(const bool &_withDigitGroupings = false);

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