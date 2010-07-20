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
#include "AlphabetTextEdit.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAlphabetTextEdit::CAlphabetTextEdit() {
	// some initializations
	stringText = "";
	selectionStart = 0;
	selectionEnd = 0;
}

CAlphabetTextEdit::~CAlphabetTextEdit() {
	
}

BEGIN_MESSAGE_MAP(CAlphabetTextEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_CUT, onEditCut)
	ON_COMMAND(ID_EDIT_COPY, onEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, onEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, onEditSelectAll)
END_MESSAGE_MAP()

void CAlphabetTextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// get the current selection
	GetSel(selectionStart, selectionEnd);

	// deletion through BACK or DELETE key
	if(nChar == VK_BACK || nChar == VK_DELETE) {
		if(selectionStart == selectionEnd) {
			stringText.Delete(selectionStart - 1, 1);
			SetWindowText(stringText);
			SetSel(selectionStart - 1, selectionStart - 1);
			return;
		}
		else {
			stringText.Delete(selectionStart, selectionEnd - selectionStart);
			SetWindowText(stringText);
			SetSel(selectionStart, selectionStart);
			return;
		}
	}

	// flomar, 07/20/2010
	// we react to a specific set of characters only: those that are part of the 
	// current alphabet, and those that would be part of the alphabet after being 
	// converted to either lower or upper case; i.e. "a" => "A" for an alphabet of 
	// [A-Z], but not for an alphabet of [A-Za-z], due to lack of distinct mapping
	const CString alphabet = theApp.TextOptions.getAlphabet();

	// these are the characters that might be implicitly converted into each other
	const CString alphabetLowercase = "abcdefghijklmnopqrstuvwxyzäöü";
	const CString alphabetUppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜ";

	// get the character that was pressed
	char character = nChar;

	// we're doing the actual conversion IF POSSIBLE; if not, the character is 
	// invalid and therefore we don't do anything but return from this function
	if(alphabet.Find(character) == -1) {
		if(alphabetLowercase.Find(character) != -1) {
			char characterUppercase = (char)(character - 32);
			if(alphabet.Find(characterUppercase) != -1) {
				character = characterUppercase;
			}
			else return;
		}
		else if(alphabetUppercase.Find(character) != -1) {
			char characterLowercase = (char)(character + 32);
			if(alphabet.Find(characterLowercase) != -1) {
				character = characterLowercase;
			}
			else return;
		}
		else return;
	}

	// add this point we have a valid character
	stringText.Delete(selectionStart, selectionEnd - selectionStart);
	stringText.Insert(selectionStart, character);
	SetWindowText(stringText);
	SetSel(selectionStart+1, selectionStart+1);
}

void CAlphabetTextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// we react to a specific set of characters only
	switch(nChar) {
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		break;
	default:
		break;
	}
	SetRedraw(TRUE);
	Invalidate(TRUE);
}

BOOL CAlphabetTextEdit::PreTranslateMessage(MSG* pMsg) 
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

void CAlphabetTextEdit::onEditCut() {
	// do the same as for onEditCopy
	onEditCopy();
	// but don't forget to erase the current selection
	stringText.Delete(selectionStart, selectionEnd - selectionStart);
	// update text
	updateText();
	// update selection
	SetSel(selectionStart, selectionStart);
}

void CAlphabetTextEdit::onEditCopy() {
	// get current selection
	GetSel(selectionStart, selectionEnd);
	// return if there is nothing selected, or if start > end (the latter should never happen)
	if(selectionStart == selectionEnd || selectionStart > selectionEnd) return;
	// create a temporary string containing the current selection
	CString selection;
	selection.Append(stringText.GetBuffer() + selectionStart, selectionEnd - selectionStart);
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

void CAlphabetTextEdit::onEditPaste() {
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

	// replace existing selection (don't replace text that was not selected)
	CString oldText;
	GetWindowText(oldText);
	
	GetSel(selectionStart, selectionEnd);

	// create new string text (with the pasted contents from the clipboard)
	CString newStringText;
	newStringText.Append(stringText.GetBuffer(), selectionStart);
	newStringText.Append(clipboardText);
	newStringText.Append(stringText.GetBuffer() + selectionEnd, stringText.GetLength() - selectionEnd);

	// set new selection
	int offset = newStringText.GetLength() - stringText.GetLength();
	selectionStart += offset;
	selectionEnd = selectionStart;
	// assign new string text
	stringText = newStringText;
	// update text
	updateText();
	// update selection
	SetSel(selectionStart, selectionEnd);
}

void CAlphabetTextEdit::onEditSelectAll() {
	// select all characters of the string text
	SetSel(0, stringText.GetLength());
}


void CAlphabetTextEdit::setText(const CString &_text) {
	// we purposely don't do any checks here: this function is provided for 
	// convenience; it can be used for displaying random text in the edit field
	stringText = _text;
	SetWindowText(stringText);
}

CString CAlphabetTextEdit::getText() {
	return stringText;
}

void CAlphabetTextEdit::updateText() {
	// get the currently configured alphabet
	const CString alphabet = theApp.TextOptions.getAlphabet();
	// remove all invalid characters from the string text
	CString newStringText;
	for(int i=0; i<stringText.GetLength(); i++) {
		if(alphabet.Find(stringText[i]) != -1) {
			newStringText.AppendChar(stringText[i]);
		}
	}
	// if the string text has changed, set selection to the end of the input
	if(newStringText != stringText) {
		stringText = newStringText;
		SetWindowText(stringText);
		SetSel(stringText.GetLength(), stringText.GetLength());
	}
	else {
		SetWindowText(stringText);
	}
}