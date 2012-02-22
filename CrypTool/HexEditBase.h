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

// This file was originally written by Christian Kuendig. It was 
// obtained from www.codeguru.com in May 2005 and modified as necessary.


///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////
#ifndef __hexeditbase_h
#define __hexeditbase_h
#if _MSC_VER > 1000
#pragma once
#endif


/////////////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////////////
#define NOSECTION_VAL				0xffffffff

// notification codes
#define HEN_CHANGE					EN_CHANGE	//the same as the EDIT (CEdit)

// data length that can be handled
#define MAXHEXEDITLENGTH 0x7ffff000

// increase capacity by 1 + m_nCapacity/CAPACICTYINCDIVISOR when a character is appended/inserted
#define CAPACICTYINCDIVISOR 8

#define HE_FIND_MATCHCASE 1
#define HE_FIND_REGEXP 2
// don't skip the first char of the current select (standard behaviour to enable repeated search)
#define HE_FIND_NOSKIP 4
#define HE_FIND_BACKWARDS 8

class CHexEditAction;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CHexEditBase
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// forward declaration
class CHexEditBaseView;

class CHexEditBase : public CWnd
{
public:
	CHexEditBase();
	virtual ~CHexEditBase();
	void SetShowAddress(bool bShow, bool bUpdate = true);
	void SetShowAscii(bool bShow, bool bUpdate = true);
	void SetData(const BYTE *pData, UINT nLen, bool bUpdate = true);
	void SetDirectDataPtr(BYTE *pData, UINT nLen, bool bUpdate = true); // won't copy data and won't free memory
	void SetHighlighted(UINT nBegin, UINT nEnd, bool bMakeVisible = true, bool bUpdate = true);
	void SetSelection(UINT nBegin, UINT nEnd, bool bMakeVisible = true, bool bUpdate = true);
	void MakeVisible(UINT nBegin, UINT nEnd, bool bUpdate=true);
	UINT GetData(BYTE *pByte, UINT nLength);
	UINT GetCurrentAddress() const;
	UINT GetBytesPerRow() const;
	void SetBytesPerRow(UINT nBytesPerRow, bool bAuto = false, bool bUpdate = true);
	void SetAddressSize(BYTE nAdrSize, bool bUpdate = true);
	void SetAdrCol(COLORREF tAdrBkgCol, COLORREF tAdrTxtCol, bool bUpdate = true);
	void SetAsciiCol(COLORREF tAsciiBkgCol, COLORREF tAsciiTxtCol, bool bUpdate = true);
	void SetHighlightCol(COLORREF tHighlightFrameCol, COLORREF tHighlightBkgCol, COLORREF tHighlightTxtCol, bool bUpdate = true);
	void SetHexCol(COLORREF tHexBkgCol, COLORREF tHexTxtCol, bool bUpdate = true);
	void SetSelectedNoFocusCol(COLORREF tSelectedNoFocusBkgCol, COLORREF tSelectedNoFocusTxtCol, bool bUpdate = true);
	void SetSelectedFocusCol(COLORREF tSelectedFousTxtCol, COLORREF tSelectedFousBkgCol, bool bUpdate = true);
	void SetNotUsedCol(COLORREF tNotUsedBkCol, bool bUpdate = true);
	bool GetSelection(UINT& nBegin, UINT& nEnd) const;
	bool GetHighlighted(UINT& nBegin, UINT& nEnd) const;
	bool IsSelection() const;
	bool IsHighlighted() const;
	bool IsInsert() const;
	UINT GetDataSize() const { return m_nLength; }
	UINT GetDataSize1() const { return m_nLength + 1; } // for all caret related operations assume add one byte for appending data
	virtual void SetReadonly(bool bReadOnly, bool bUpdate = true);
	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hwndParent, HMENU nIDorHMenu, LPVOID lpParam = NULL);
	BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);	
	static void RegisterClass();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	void SetContextCopyStr(const CString& cStr) { m_cContextCopy = cStr; }
	void SetContextPasteStr(const CString& cStr) { m_cContextPaste = cStr; }
	void Serialize(CArchive& ar);
	bool Search(LPCSTR text, size_t length, UINT flags);
	bool ReplaceSelection(LPCSTR text, size_t length);
	int ReplaceAll(LPCSTR pfind, size_t findlen, LPCSTR preplace, size_t replacelen, UINT searchflags);
	void Undo();
	void Redo();
	BOOL CanUndo() { return m_undo != 0; }
	BOOL CanRedo() { return m_redo != 0; }

	// quick and dirty: to access copy/paste functions from outside
	void callOnEditCut() { OnEditCut(); }
	void callOnEditCopy() { OnEditCopy(); }
	void callOnEditPaste() { OnEditPaste(); }
	void callOnEditClear() { OnEditClear(); }
	void callOnEditSelectAll() { OnEditSelectAll(); }

protected:
	CHexEditBaseView *view;
public:
	void setView(CHexEditBaseView *_view) { view = _view; }

protected:
	bool PrepareReplace(UINT pos, UINT oldlen, UINT newlen); // Prepare replacing [pos, pos+oldlen] with new content of newlen bytes
	BOOL SaveUndoAction(UINT type, UINT position, const BYTE* replaceData, UINT replaceLen, const BYTE* insertData, UINT insertLen);

	struct PAINTINGDETAILS {
		UINT nFullVisibleLines;
		UINT nLastLineHeight;
		UINT nVisibleLines;
		UINT nLineHeight;
		UINT nCharacterWidth;
		UINT nBytesPerRow;
		UINT nHexPos;
		UINT nHexLen;
		UINT nAsciiPos;
		UINT nAsciiLen;
		UINT nAddressPos;
		UINT nAddressLen;
		CRect cPaintingRect;
	};

	bool m_bSelfCleanup;
	bool m_bDeleteData;
	PAINTINGDETAILS m_tPaintDetails;
	BYTE *m_pData;
	UINT m_nBytesPerRow;
	UINT m_nAdrSize;
	UINT m_nHighlightedEnd;
	UINT m_nHighlightedBegin;
	UINT m_nSelectionBegin;
	UINT m_nSelectionEnd;
	UINT m_nCurrentAddress;
	UINT m_nCurCaretHeight; 
	UINT m_nLength;
	UINT m_nCapacity;
	UINT m_nScrollPostionY;	
	UINT m_nScrollRangeY;
	UINT m_nScrollPostionX;	
	UINT m_nScrollRangeX;
	UINT m_nCurCaretWidth;
	UINT m_nSelectingBeg;
	UINT m_nSelectingEnd;
	UINT m_nBinDataClipboardFormat;	
	bool m_bRecalc;
	bool m_bHasCaret;
	bool m_bHighBits; // caret on high nibble
	bool m_bCaretAscii;	// true: caret in ASCII area; false: caret in hex area
	bool m_bAutoBytesPerRow;
	bool m_bShowAddress;
	bool m_bShowAscii;
	bool m_bAddressIsWide;
	bool m_bShowCategory;
	bool m_bReadOnly;
	bool m_bInsert;
	COLORREF m_tAdrBkgCol;
	COLORREF m_tAdrTxtCol;
	COLORREF m_tAsciiBkgCol;
	COLORREF m_tAsciiTxtCol;
	COLORREF m_tHighlightBkgCol;
	COLORREF m_tHighlightTxtCol;
	COLORREF m_tHighlightFrameCol;
	COLORREF m_tHexTxtCol;
	COLORREF m_tHexBkgCol;
	COLORREF m_tNotUsedBkCol;
	COLORREF m_tSelectedNoFocusTxtCol;
	COLORREF m_tSelectedNoFocusBkgCol;
	COLORREF m_tSelectedFousTxtCol;
	COLORREF m_tSelectedFousBkgCol;	
	CString m_cContextCut;
	CString m_cContextCopy;
	CString m_cContextPaste;
	CString m_cContextToTxt;
	CFont m_cFont;	
	CRect m_cDragRect;
	CPoint m_cMouseRepPoint;
	int m_iMouseRepDelta;
	WORD m_nMouseRepSpeed;
	WORD m_nMouseRepCounter;
	bool m_bIsMouseRepActive;
	CHexEditAction* m_undo;
	CHexEditAction* m_redo;

	// overrideables
	virtual void OnExtendContextMenu(CMenu&) {} // override this to add your own context-menue-items

	void NotifyParent(WORD wNBotifictionCode);
	void CalculatePaintingDetails(CDC& cDC);
	void PaintAddresses(CDC& cDC);
	void PaintHexData(CDC& cDC);
	void PaintAsciiData(CDC& cDC);	
	void CreateEditCaret(UINT nCaretHeight, UINT nCaretWidth);
	void DestoyEditCaret();
	void SetEditCaretPos(UINT nOffset, bool bHighBits);
	bool OnEditInput(WORD nInput);
	void MoveCurrentAddress(int iDeltaAdr, bool bHighBits, bool bIgnoreShift = false);
	void SetScrollPositionY(UINT nPosition, bool bUpdate=false);
	void SetScrollPositionX(UINT nPosition, bool bUpdate=false);
	void SetScrollbarRanges();
	void MoveScrollPostionY(int iDelta, bool bUpdate=false);
	void MoveScrollPostionX(int iDelta, bool bUpdate=false);
	void StartMouseRepeat(const CPoint& cPoint, int iDelta, WORD nSpeed);
	void StopMouseRepeat();
	void GetAddressFromPoint(const CPoint& cPt, UINT& nAddress, bool& bHighByte);
	UINT CreateHighlightingPolygons(const CRect& cHexRect, 
		UINT nBegin, UINT nEnd, POINT *pPoints);
	void ReInitialize();
	bool Allocate(UINT nLen);
	void OnEditCopyCutDelete(bool cutdel,bool clipboard);
	void OnDelete(WPARAM wParam);

	//{{AFX_VIRTUAL(CHexEditBase)
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHexEditBase)
	afx_msg void OnDestroy(); 
	afx_msg void OnTimer(UINT nTimerID);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint cPoint);
	afx_msg LRESULT OnWMChar(WPARAM wParam, LPARAM);
	afx_msg LRESULT OnWMSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWMGetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUmSetScrollRange(WPARAM, LPARAM);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd*);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar*);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar*);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg void OnLButtonDown(UINT, CPoint point);
	afx_msg void OnLButtonDblClk(UINT, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT, CPoint);
	afx_msg void OnKeyDown(UINT nChar, UINT, UINT);
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditClear();
	afx_msg void OnEditSelectAll();
	afx_msg void OnToTxt();
	//}}AFX_MSG
	DECLARE_DYNCREATE(CHexEditBase)
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CHexEditBaseView
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "CrypToolView.h"

class CHexEditBaseView : public CCrypToolView
{
	DECLARE_DYNCREATE(CHexEditBaseView)

public:
	enum { IDC_HEXEDITBASEVIEW_HEXCONTROL = 0x100 };

	CHexEditBaseView();
	virtual ~CHexEditBaseView();
	CHexEditBase& GetHexEditCtrl() { return m_cHexEdit; }

protected:
	CHexEditBase m_cHexEdit;

	//{{AFX_VIRTUAL(CHexEditBaseView)
	virtual void OnDraw(CDC*);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHexEditBaseView)
	afx_msg BOOL OnEraseBkgnd(CDC*);
	afx_msg int OnCreate(LPCREATESTRUCT pCreateStruc);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// this function is re-implemented in CHexEditCtrlView
	virtual void showAsText() { }
};



#endif
