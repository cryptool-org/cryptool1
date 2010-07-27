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

#include "stdafx.h"
#include "NumberEdit.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNumberEdit::CNumberEdit() {
	// some initializations
	stringNumber = "";
	selectionStart = 0;
	selectionEnd = 0;
	// get separators from resource file (we need them later on)
	theIntegralSeparator = getIntegralNumberSeparator();
	theFractionalSeparator = getFractionalNumberSeparator();
	// do we want to show integral separators?
	showIntegralSeparators = false;
	// do we want to show fractional separators?
	showFractionalSeparators = false;
	// do we want to show a sign?
	showSign = false;
	// do we have a decimal? (this overrides "showFractionalSeparators" menu option)
	decimal = false;
	// do we want to allow modification of the number?
	readOnly = false;
}

CNumberEdit::~CNumberEdit() {
	
}

BEGIN_MESSAGE_MAP(CNumberEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_CUT, onEditCut)
	ON_COMMAND(ID_EDIT_COPY, onEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, onEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, onEditSelectAll)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// we don't want the user to alter disabled edit fields
	if(readOnly) {
		return;
	}
	// get the current selection
	GetSel(selectionStart, selectionEnd);
	// prepare insertion through update function
	CString text; text.AppendChar(nChar);
	// update number
	updateNumber(selectionStart, selectionEnd, text);
}

void CNumberEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// we react to a specific set of characters only
	switch(nChar) {
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
	case VK_PRIOR:
	case VK_NEXT:
	case VK_HOME:
	case VK_END:
	case VK_TAB:
		// cursor movement within edit field
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		break;
	case VK_BACK:
	case VK_DELETE:
		if(readOnly) {
			break;
		}
		// deletion through BACK or DELETE key
		GetSel(selectionStart, selectionEnd);
		if(selectionStart == selectionEnd) {
			stringNumber.Delete(selectionStart - 1, 1);
			SetWindowText(stringNumber);
			updateNumber(selectionStart - 1, selectionStart - 1); 
		}
		else {
			stringNumber.Delete(selectionStart, selectionEnd - selectionStart);
			SetWindowText(stringNumber);
			updateNumber(selectionStart, selectionStart);
		}
		break;
	default:
		break;
	}
	SetRedraw(TRUE);
	Invalidate(TRUE);
}

BOOL CNumberEdit::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) {
		bool bIsShift = (GetKeyState(VK_SHIFT) & 0x80000000) == 0x80000000;
		bool bIsControl = (GetKeyState(VK_CONTROL) & 0x80000000) == 0x80000000;
		bool bIsAlt = (GetKeyState(VK_MENU) & 0x80000000) == 0x80000000;
		
		WPARAM key = pMsg->wParam;

		if(bIsControl) {
			switch(key) {			
			case 'X': // ctrl + x: cut
				onEditCut();
				return TRUE;
			case 'C': // ctrl + c: copy
				onEditCopy();
				return TRUE;
			case 'V': // ctrl + v: paste
				onEditPaste();
				return TRUE;
			case 'A': // ctrl + a: select all
				onEditSelectAll();
				return TRUE;
			}
		} 
	}
	return CWnd::PreTranslateMessage(pMsg);
}

BOOL CNumberEdit::OnCommand(WPARAM wParam, LPARAM lParam)
{
    switch (LOWORD(wParam))
    {
    case WM_CUT:
			onEditCut();
			return TRUE;
    case WM_COPY:
			onEditCopy();
			return TRUE;
    case WM_PASTE:
			onEditPaste();
			return TRUE;
		case CM_SELECT_ALL:
			onEditSelectAll();
			return TRUE;
		case CM_TOGGLE_INTEGRAL_SEPARATORS:
			showIntegralSeparators = !showIntegralSeparators;
			updateNumber();
			return TRUE;
		case CM_TOGGLE_FRACTIONAL_SEPARATORS:
			showFractionalSeparators = !showFractionalSeparators;
			updateNumber();
			return TRUE;
    default:
        return CEdit::OnCommand(wParam, lParam);
    }
}


void CNumberEdit::OnContextMenu(CWnd *pWnd, CPoint pos) {
	SetFocus();
	CMenu menu;
	menu.CreatePopupMenu();
  BOOL bReadOnly = GetStyle() & ES_READONLY;
  
	CString menuText;

	menuText.LoadString(IDS_CONTROL_CUT);
	menu.InsertMenu(0, MF_BYPOSITION, WM_CUT, menuText);

	menuText.LoadString(IDS_CONTROL_COPY);
	menu.InsertMenu(1, MF_BYPOSITION, WM_COPY, menuText);

	menuText.LoadString(IDS_CONTROL_PASTE);
	menu.InsertMenu(2, MF_BYPOSITION, WM_PASTE, menuText);

	menuText.LoadString(IDS_CONTROL_SELECT_ALL);
	menu.InsertMenu(3, MF_BYPOSITION, CM_SELECT_ALL, menuText);

	menu.InsertMenu(4, MF_BYPOSITION | MF_SEPARATOR);

	// we have two different menu entries, one for each state: on/off
	if(showIntegralSeparators) {
		menuText.LoadString(IDS_CONTROL_TOGGLE_INTEGRAL_SEPARATORS_OFF);
		menu.InsertMenu(5, MF_BYPOSITION, CM_TOGGLE_INTEGRAL_SEPARATORS, menuText);
	}
	else {
		menuText.LoadString(IDS_CONTROL_TOGGLE_INTEGRAL_SEPARATORS_ON);
		menu.InsertMenu(5, MF_BYPOSITION, CM_TOGGLE_INTEGRAL_SEPARATORS, menuText);
	}

	// we have two different menu entries, one for each state: on/off
	if(showFractionalSeparators) {
		menuText.LoadString(IDS_CONTROL_TOGGLE_FRACTIONAL_SEPARATORS_OFF);
		// we gray out the fractional separator option for non decimals (integers)
		if(decimal) {
			menu.InsertMenu(6, MF_BYPOSITION, CM_TOGGLE_FRACTIONAL_SEPARATORS, menuText);
		}
		else {
			menu.InsertMenu(6, MF_BYPOSITION|MF_GRAYED, CM_TOGGLE_FRACTIONAL_SEPARATORS, menuText);
		}
	}
	else {
		menuText.LoadString(IDS_CONTROL_TOGGLE_FRACTIONAL_SEPARATORS_ON);
		// we gray out the fractional separator option for non decimals (integers)
		if(decimal) {
			menu.InsertMenu(6, MF_BYPOSITION, CM_TOGGLE_FRACTIONAL_SEPARATORS, menuText);
		}
		else {
			menu.InsertMenu(6, MF_BYPOSITION|MF_GRAYED, CM_TOGGLE_FRACTIONAL_SEPARATORS, menuText);
		}
	}

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pos.x, pos.y, this);
}

void CNumberEdit::onEditCut() {
	// do the same as for onEditCopy
	onEditCopy();
	// but don't do anything else if we're in read only mode
	if(readOnly) {
		return;
	}
	// but don't forget to erase the current selection
	stringNumber.Delete(selectionStart, selectionEnd - selectionStart);
	// update the string number
	updateNumber(selectionStart, selectionStart);
}

void CNumberEdit::onEditCopy() {
	// get current selection
	GetSel(selectionStart, selectionEnd);
	// return if there is nothing selected, or if start > end (the latter should never happen)
	if(selectionStart == selectionEnd || selectionStart > selectionEnd) return;
	// create a temporary string containing the current selection
	CString selection;
	selection.Append(stringNumber.GetBuffer() + selectionStart, selectionEnd - selectionStart);
	// do the copy-paste-stuff (compare CHexEditBase for details, I'm too lazy ATM)
	HGLOBAL hMem = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, selection.GetLength() + 1);
	if(!hMem) return;
	BYTE *pPtr = (BYTE*)::GlobalLock(hMem);
	memcpy(pPtr, selection.GetBuffer(), selection.GetLength());
	::GlobalUnlock(hMem);
	if(!OpenClipboard()) return;
	if(!EmptyClipboard()) return;
	if(!SetClipboardData(CF_TEXT, hMem)) {
		CloseClipboard();
		return;
	}
	CloseClipboard();
}

void CNumberEdit::onEditPaste() {
	// don't do anything if we're in read only mode
	if(readOnly) {
		return;
	}
	CString clipboardText;
	// at first we try to get the contents of the clipboard
  if(::IsClipboardFormatAvailable(CF_TEXT)) {
    // open the clipboard to get clipboard text
    if(::OpenClipboard(m_hWnd)) {
      HANDLE  hClipBrdData = NULL;
      if((hClipBrdData = ::GetClipboardData(CF_TEXT)) != NULL) {
        LPTSTR  lpClipBrdText = (LPTSTR)::GlobalLock(hClipBrdData);
        if(lpClipBrdText) {
          clipboardText = lpClipBrdText;
          ::GlobalUnlock(hClipBrdData);
        }
      }
			VERIFY(::CloseClipboard());
		}
	
		// now we should have the contents of the clipboard;
		// however, we need to replace the line breaks with spaces 
		// to prevent the input field from getting messed up
		int lineBreakIndex = 0;
		while((lineBreakIndex = clipboardText.Find("\r\n")) != -1) {
			clipboardText.Delete(lineBreakIndex, 2);
			clipboardText.Insert(lineBreakIndex, " ");
		}
	}

	// get current selection
	GetSel(selectionStart, selectionEnd);
	// update the number (in particular, insert integral separators)
	updateNumber(selectionStart, selectionEnd, clipboardText);
}

void CNumberEdit::onEditSelectAll() {
	// select all characters of the string number
	SetSel(0, stringNumber.GetLength());
}

CString CNumberEdit::getNumberAsCString() {
	CString result;
	CString validCharacters = "+-0123456789";
	validCharacters.AppendChar(theFractionalSeparator);
	for(int i=0; i<stringNumber.GetLength(); i++) {
		char character = stringNumber[i];
		if(validCharacters.Find(character) == -1) {
			continue;
		}
		// special treatment for the fractional separator: if "showFractionalSeparators" 
		// is not set, we bail out and return the integral part of the number only; if the 
		// option is set, we make sure to use a colon (".") instead of the language-dependent
		// separator configured in the resource file
		if(character == theFractionalSeparator) {
			if(showFractionalSeparators) {
				result.AppendChar('.');
			}
			else {
				// we bail out
				return result;
			}
		}
		else {
			result.AppendChar(character);
		}
	}
	return result;
}

CString CNumberEdit::getNumberAsCStringLanguageDependent() {
	CString result;
	CString validCharacters = "+-0123456789";
	validCharacters.AppendChar(theIntegralSeparator);
	validCharacters.AppendChar(theFractionalSeparator);
	for(int i=0; i<stringNumber.GetLength(); i++) {
		char character = stringNumber[i];
		if(validCharacters.Find(character) == -1) {
			continue;
		}
		// special treatment for the fractional separator: if "showFractionalSeparators" 
		// is not set, we bail out and return the integral part of the number only; if the 
		// option is set, we make sure to use the language-dependent separator configured 
		// in the resource file
		if(character == theFractionalSeparator) {
			if(showFractionalSeparators) {
				result.AppendChar(theFractionalSeparator);
			}
			else {
				// we bail out
				return result;
			}
		}
		else {
			result.AppendChar(character);
		}
	}
	return result;
}

void CNumberEdit::setNumber(const CString &_number) {
	CString result;
	// we go through our string number and remove everything but valid characters, 
	// which are signs [+-], the ten digits [0-9], and the fractional separator
	CString validCharacters = "+-0123456789";
	validCharacters.AppendChar(theFractionalSeparator);
	for(int i=0; i<_number.GetLength(); i++) {
		char character = _number[i];
		if(validCharacters.Find(character) == -1) {
			continue;
		}
		result.AppendChar(character);
	}
	stringNumber = result;
	SetWindowText(stringNumber);
	SetSel(stringNumber.GetLength(), stringNumber.GetLength());
}

void CNumberEdit::setText(const CString &_text) {
	// we purposely don't do any checks here: this function is provided for 
	// convenience; it can be used for displaying random text in the edit field
	stringNumber = _text;
	SetWindowText(stringNumber);
}

void CNumberEdit::updateNumber(const int &_selectionStart, const int &_selectionEnd, const CString &_text) {

	// first, we make a copy of the existing string number
	CString oldStringNumber = stringNumber;

	// then we store the last selection
	int selectionStart = _selectionStart;
	int selectionEnd = _selectionEnd;

	// we also store the amount of integral separators IN FRONT OF the current selection;
	// this will come handy later on when we try to determine the correct cursor position
	int amountOfIntegralSeparatorsInFrontOfCurrentSelection = 0;
	for(int i=0; i<stringNumber.GetLength() && i<selectionStart; i++) {
		if(stringNumber[i] == theIntegralSeparator) {
			amountOfIntegralSeparatorsInFrontOfCurrentSelection++;
		}
	}

	// delete the current selection
	stringNumber.Delete(selectionStart, selectionEnd - selectionStart);

	// then we clear the text to be inserted (if there is any) of all invalid characters
	if(_text.GetLength()) {
		CString text = _text;
		CString validText;
		for(int i=0; i<text.GetLength(); i++) {
			char character = text[i];

			if(character >= '0' && character <= '9') {
				validText.AppendChar(character);
			}
			if((character == '+' || character == '-') && selectionStart == 0 && i == 0 && showSign) {
				validText.AppendChar(character);
			}
			if(character == theFractionalSeparator && validText.Find(theFractionalSeparator) == -1 && showFractionalSeparators) {
				validText.AppendChar(character);
			}
		}

		// now we insert the valid text into the existing string number; however, there's 
		// some special case we need to handle: if "validText" contains fractional separators, 
		// first we remove all frational separators from "stringNumber"; for each removal, 
		// "selectionStart" and "selectionEnd" are adjusted accordingly
		if(showFractionalSeparators) {
			if(validText.Find(theFractionalSeparator) != -1) {
				int amountOfSeparatorsRemoved = stringNumber.Remove(theFractionalSeparator);
				selectionStart -= amountOfSeparatorsRemoved;
				selectionEnd = selectionStart;
			}
		}

		// enter the valid text
		stringNumber.Insert(selectionStart, validText);	

		// update the selection (place it right behind what we just inserted)
		selectionStart += validText.GetLength();
		selectionEnd = selectionStart;
	}

	// at this point we probably have a not properly formatted string number; so we 
	// try to transform it into something that's valid in our context: we allow an 
	// optional leading sign [+-], an integral part [0-9], an optional fractional 
	// separator [depends on resource file], and an optional fractional part [0-9]
	CString stringNumberSign;
	CString stringNumberIntegralPart;
	CString stringNumberFractionalSeparator;
	CString stringNumberFractionalPart;

	for(int i=0; i<stringNumber.GetLength(); i++) {
		// get the current character
		char character = stringNumber[i];
		// SIGN
		if(i == 0 && (character == '+' || character == '-') && stringNumberSign.GetLength() == 0 && showSign) {
			stringNumberSign.AppendChar(character);
		}
		// INTEGRAL PART
		if(character >= '0' && character <= '9' && stringNumberFractionalSeparator.GetLength() == 0) {
			stringNumberIntegralPart.AppendChar(character);
		}
		// FRACTIONAL SEPARATOR
		if(character == theFractionalSeparator && stringNumberFractionalSeparator.GetLength() == 0) {
			stringNumberFractionalSeparator.AppendChar(character);
		}
		// FRACTIONAL PART
		if(character >= '0' && character <= '9' && stringNumberFractionalSeparator.GetLength() == 1) {
			stringNumberFractionalPart.AppendChar(character);
		}
	}

	// at this point we should have a properly formatted string number;
	// but the integral separators are still missing (if we want to display them)
	if(showIntegralSeparators) {
		// determine the amount of integral separators we need
		int amountOfIntegralSeparators = (stringNumberIntegralPart.GetLength() - 1) / 3;
		// insert integral separators
		for(int i=0; i<amountOfIntegralSeparators; i++) {
			stringNumberIntegralPart.Insert(stringNumberIntegralPart.GetLength() - 3*(i+1) - i, theIntegralSeparator);
		}
		// correct the selection (see above at beginning of function)
		int amountOfIntegralSeparatorsInsertedInFrontOfCurrentSelection = 0;
		for(int i=0; i<stringNumberIntegralPart.GetLength(); i++) {
			if(stringNumberIntegralPart[i] == theIntegralSeparator && i < selectionStart) {
				amountOfIntegralSeparatorsInsertedInFrontOfCurrentSelection++;
			}
		}
		int offset = amountOfIntegralSeparatorsInsertedInFrontOfCurrentSelection - amountOfIntegralSeparatorsInFrontOfCurrentSelection;
		selectionStart += offset;
		selectionEnd = selectionStart;
	}

	// build the new string number out of its parts
	stringNumber = "";
	stringNumber.Append(stringNumberSign);
	stringNumber.Append(stringNumberIntegralPart);
	if(showFractionalSeparators) {
		stringNumber.Append(stringNumberFractionalSeparator);
		stringNumber.Append(stringNumberFractionalPart);
	}

	SetWindowText(stringNumber);

	SetSel(selectionStart, selectionEnd);
}