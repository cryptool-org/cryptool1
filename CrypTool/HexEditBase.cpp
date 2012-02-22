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


/////////////////////////////////////////////////////////////////////////////
// includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <memory>
#include <afxole.h>
#include "HexEditBase.h"
#include "resource.h"
#include "stdafx.h"
#include "SelectCopyEncoding.h"
#include "SelectPasteDecoding.h"
#include "ChrTools.h"

class CHexEditAction {
public:
	enum ActionType { unknown, input, cut, paste } type;
protected:
	UINT  position;
	BYTE* replaceData;
	UINT  replaceLen;
	BYTE* insertData;
	UINT  insertLen;
	CHexEditAction* next;
public:
	CHexEditAction();
	~CHexEditAction();
	BOOL set(ActionType type, UINT position, const BYTE* replaceData, UINT replaceLen, const BYTE* insertData, UINT insertLen, CHexEditAction* next = 0);
	void setNext(CHexEditAction* next) { this->next = next; }
	BOOL append(const BYTE* replaceData, UINT replaceLen, const BYTE* insertData, UINT insertLen);
	ActionType getType() const { return type; }
	UINT getPosition() const { return position; }
	BYTE* getReplaceData() const { return replaceData; }
	UINT getReplaceLen() const { return replaceLen; }
	BYTE* getInsertData() const { return insertData; }
	UINT getInsertLen() const { return insertLen; }
	CHexEditAction* getNext() const { return next; }
};

CHexEditAction::CHexEditAction()
: type(unknown), position(0), replaceData(0), replaceLen(0), insertData(0), insertLen(0), next(0)
{
}

CHexEditAction::~CHexEditAction()
{
	delete next;
	delete[] replaceData;
	delete[] insertData;
}

BOOL CHexEditAction::set(ActionType type, UINT position, const BYTE* replaceData, UINT replaceLen, const BYTE* insertData, UINT insertLen, CHexEditAction* next)
{
	BYTE* rdata = replaceLen != 0 ? new BYTE[replaceLen] : 0;
	BYTE* idata = insertLen != 0  ? new BYTE[insertLen]  : 0;
	if ((replaceLen != 0 && rdata == 0) || (insertLen !=0 && idata == 0)) {
		delete[] rdata;
		delete[] idata;
		return FALSE;
	}
	if (replaceLen != 0)
		memcpy(rdata, replaceData, replaceLen);
	if (insertLen != 0)
		memcpy(idata, insertData, insertLen);
	delete[] this->replaceData;
	delete[] this->insertData;
	this->type = type;
	this->position = position;
	this->replaceData = rdata;
	this->replaceLen = replaceLen;
	this->insertData = idata;
	this->insertLen = insertLen;
	this->next = next;
	return TRUE;
}
BOOL CHexEditAction::append(const BYTE* replaceData, UINT replaceLen, const BYTE* insertData, UINT insertLen)
{
	UINT rlen = this->replaceLen + replaceLen;
	BYTE* rdata = (replaceLen > 0) ? new BYTE[rlen] : 0;
	UINT ilen = this->insertLen + insertLen;
	BYTE* idata = (insertLen > 0) ? new BYTE[ilen] : 0;
	if ((replaceLen > 0 && rdata == 0) || (insertLen > 0 && idata == 0)) {
		delete[] rdata;
		delete[] idata;
		return FALSE;
	}
	if (rdata) {
		if (this->replaceLen > 0)
			memcpy(rdata, this->replaceData, this->replaceLen);
		if (replaceLen > 0)
			memcpy(rdata + this->replaceLen, replaceData, replaceLen);
		delete[] this->replaceData;
		this->replaceData = rdata;
		this->replaceLen = rlen;
	}
	if (idata) {
		if (this->insertLen > 0)
			memcpy(idata, this->insertData, this->insertLen);
		if (insertLen > 0)
			memcpy(idata + this->insertLen, insertData, insertLen);
		delete[] this->insertData;
		this->insertData = idata;
		this->insertLen = ilen;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// control-layout customization (low-level)
#define ADR_DATA_SPACE				20
#define DATA_ASCII_SPACE			25
#define CONTROL_BORDER_SPACE		3

// boundaries and special values
#define MAX_HIGHLIGHT_POLYPOINTS	8
#define UM_SETSCROLRANGE			(WM_USER + 0x5000)
#define MOUSEREP_TIMER_TID			0x400
#define MOUSEREP_TIMER_ELAPSE		0x5

// clipboard format
#define CF_BINDATA_HEXCTRL			_T("BinaryData")

// windows-class-name
#define HEXEDITBASECTRL_CLASSNAME	_T("CHexEditBase")
#define HEXEDITBASECTRL_CLSNAME_SC	_T("CHexEditBase_SC") //self creating

// macros
#define NORMALIZE_SELECTION(beg, end) if(beg>end){UINT tmp = end; end=beg; beg=tmp; }



/////////////////////////////////////////////////////////////////////////////
// global data
/////////////////////////////////////////////////////////////////////////////
const char tabHexCharacters[16] = {
	'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' }; 




	
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// class CHexEditBase
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
	
IMPLEMENT_DYNCREATE(CHexEditBase, CWnd)

BEGIN_MESSAGE_MAP(CHexEditBase, CWnd)
	//{{AFX_MSG_MAP(CHexEditBase)
	ON_MESSAGE(UM_SETSCROLRANGE, OnUmSetScrollRange)
	ON_MESSAGE(WM_CHAR, OnWMChar)
	ON_MESSAGE(WM_SETFONT, OnWMSetFont)
	ON_MESSAGE(WM_GETFONT, OnWMGetFont)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_GETDLGCODE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_TOTXT, OnToTxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CHexEditBase::CHexEditBase() :
	m_bSelfCleanup(false),
	m_bDeleteData(true),
	m_pData(NULL), 
	m_nLength(0), 
	m_nCapacity(0), 
	m_nAdrSize(8), 
	m_nBytesPerRow(16), 
	m_nCurCaretWidth(0),
	m_nCurCaretHeight(0), 
	m_bHasCaret(false), 
	m_bHighBits(true),
	m_bCaretAscii(false),
	m_bReadOnly(false), 
	m_bInsert(false),
	m_nHighlightedBegin(NOSECTION_VAL), 
	m_nHighlightedEnd(NOSECTION_VAL),
	m_nSelectingBeg(NOSECTION_VAL),
	m_nSelectingEnd(NOSECTION_VAL),
	m_nSelectionBegin(NOSECTION_VAL),
	m_nSelectionEnd(NOSECTION_VAL), 
	m_tAdrBkgCol(RGB(255,255,255)), 
	m_tAdrTxtCol(RGB(0,0,0)), 
	m_tAsciiBkgCol(RGB(255,255,255)), 
	m_tAsciiTxtCol(RGB(0,0,0)),
	m_tHighlightBkgCol(RGB(0,90,210)), 
	m_tHighlightTxtCol(RGB(0,200,0)), 
	m_tHighlightFrameCol(RGB(0,255,255)),
	m_tHexTxtCol(RGB(0,0,0)), 
	m_tHexBkgCol(RGB(255,255,255)), 
	m_tNotUsedBkCol(RGB(255,255,255)),
	m_nCurrentAddress(0),
	m_bAutoBytesPerRow(false), 
	m_bRecalc(true),
	m_nScrollPostionX(0), 
	m_nScrollRangeX(0), 
	m_nScrollPostionY(0), 
	m_nScrollRangeY(0),
	m_bShowAscii(false), 
	m_bShowAddress(false), 
	m_bShowCategory(false),
	m_nMouseRepSpeed(0),
	m_iMouseRepDelta(0),
	m_nMouseRepCounter(0),
	m_bIsMouseRepActive(false),
	m_cDragRect(0,0,0,0),
	m_cContextCut("Cut"),
	m_cContextCopy("Copy"),
	m_cContextPaste("Paste"),
	m_cContextToTxt("ToTxt"),
	m_undo(0),
	m_redo(0)

{
	memset(&m_tPaintDetails, 0, sizeof(PAINTINGDETAILS));
#if 0 
	m_tSelectedNoFocusTxtCol = GetSysColor(COLOR_WINDOWTEXT);
	m_tSelectedNoFocusBkgCol = GetSysColor(COLOR_BTNFACE);
#else // for consistency with Scintilla
	m_tSelectedNoFocusTxtCol = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_tSelectedNoFocusBkgCol = GetSysColor(COLOR_HIGHLIGHT);
#endif
	m_tSelectedFousTxtCol = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_tSelectedFousBkgCol = GetSysColor(COLOR_HIGHLIGHT);
	if(!m_cFont.CreateStockObject(ANSI_FIXED_FONT)) {
		AfxThrowResourceException();
	}
	
	// register clipboard format
	m_nBinDataClipboardFormat = RegisterClipboardFormat(CF_BINDATA_HEXCTRL);
	ASSERT(m_nBinDataClipboardFormat != 0);

	// try to load strings from the resources
#ifdef IDS_CONTROL_CUT
	m_cContextCut.LoadString(IDS_CONTROL_CUT);
#endif
#ifdef IDS_CONTROL_COPY
	m_cContextCopy.LoadString(IDS_CONTROL_COPY);
#endif
#ifdef IDS_CONTROL_PASTE
	m_cContextPaste.LoadString(IDS_CONTROL_PASTE);
#endif
#ifdef IDS_CONTROL_TOTXT
	m_cContextToTxt.LoadString(IDS_CONTROL_TOTXT);
#endif

	// register windows-class
	RegisterClass();
}

CHexEditBase::~CHexEditBase()
{
	if(m_bDeleteData) {
		delete []m_pData;
	}
	delete m_undo;
	delete m_redo;
    if(m_cFont.m_hObject != NULL) {
		m_cFont.DeleteObject();
	}
	if(::IsWindow(m_hWnd)) {
		DestroyWindow();
	}
}

BOOL CHexEditBase::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	return CWnd::Create(HEXEDITBASECTRL_CLASSNAME, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CHexEditBase::CreateEx(DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hwndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
	return CWnd::CreateEx(dwExStyle, HEXEDITBASECTRL_CLASSNAME, lpszWindowName, dwStyle, x, y, nWidth, nHeight, hwndParent, nIDorHMenu, lpParam);
}

BOOL CHexEditBase::CreateEx(DWORD dwExStyle, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam)
{
	return CWnd::CreateEx(dwExStyle, HEXEDITBASECTRL_CLASSNAME, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
}

void CHexEditBase::RegisterClass()
{
	// register windowsclass
	WNDCLASS tWndClass;
	if(!::GetClassInfo(AfxGetInstanceHandle(), HEXEDITBASECTRL_CLASSNAME, &tWndClass))
	{
		memset(&tWndClass, 0, sizeof(WNDCLASS));
        tWndClass.style = CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
		tWndClass.lpfnWndProc = ::DefWindowProc;
		tWndClass.hInstance = AfxGetInstanceHandle();
		tWndClass.hCursor = ::LoadCursor(NULL, IDC_IBEAM);
		tWndClass.lpszClassName = HEXEDITBASECTRL_CLASSNAME;

		if(!AfxRegisterClass(&tWndClass)) {
			AfxThrowResourceException();
		}
	}
	if(!::GetClassInfo(AfxGetInstanceHandle(), HEXEDITBASECTRL_CLSNAME_SC, &tWndClass))
	{
		memset(&tWndClass, 0, sizeof(WNDCLASS));
        tWndClass.style = CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
		tWndClass.lpfnWndProc = CHexEditBase::WndProc;
		tWndClass.hInstance = AfxGetInstanceHandle();
		tWndClass.hCursor = ::LoadCursor(NULL, IDC_IBEAM);
		tWndClass.lpszClassName = HEXEDITBASECTRL_CLSNAME_SC;

		if(!AfxRegisterClass(&tWndClass)) {
			AfxThrowResourceException();
		}
	}	
}

LRESULT CALLBACK CHexEditBase::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	if(nMsg == WM_NCCREATE) {		
		ASSERT(FromHandlePermanent(hWnd) == NULL );
		CHexEditBase* pControl = NULL;
		try {
			pControl = new CHexEditBase();
			pControl->m_bSelfCleanup = true;
		} catch(...) { 
			return FALSE;
		}
		if(pControl == NULL) {
			return FALSE;
		}
		if(!pControl->SubclassWindow(hWnd)) { 
			TRACE("CHexEditBase::WndProc: ERROR: couldn't subclass window (WM_NCCREATE)\n");
			delete pControl;
			return FALSE;
		}
		return TRUE;
	}
	return ::DefWindowProc(hWnd, nMsg, wParam, lParam);
}

void CHexEditBase::NotifyParent(WORD wNBotifictionCode)
{
	CWnd *pWnd = GetParent();
	if(pWnd != NULL) {
		pWnd->SendMessage(WM_COMMAND, MAKEWPARAM((WORD)GetDlgCtrlID(), wNBotifictionCode), (LPARAM)m_hWnd);
	}
}

void CHexEditBase::PostNcDestroy() 
{
	if(m_bSelfCleanup) {
		m_bSelfCleanup = false;
		delete this;
	}
}

void CHexEditBase::OnDestroy() 
{
	CWnd::OnDestroy();
}

void CHexEditBase::CalculatePaintingDetails(CDC& cDC)
{
	ASSERT(m_nScrollPostionY >= 0);

	CFont *pOldFont;
	m_bRecalc = false;

	// Get size information
	int iWidth;
	pOldFont = cDC.SelectObject(&m_cFont);
	cDC.GetCharWidth('0', '0', &iWidth);
	ASSERT(iWidth > 0);
	m_tPaintDetails.nCharacterWidth = iWidth;
	CSize cSize = cDC.GetTextExtent("0", 1);
	ASSERT(cSize.cy > 0);
	m_tPaintDetails.nLineHeight = cSize.cy;

	// count of visible lines
	GetClientRect(m_tPaintDetails.cPaintingRect);
	if(GetStyle() & ES_MULTILINE) {
		m_tPaintDetails.cPaintingRect.InflateRect(-CONTROL_BORDER_SPACE, -CONTROL_BORDER_SPACE, 
			-CONTROL_BORDER_SPACE, -CONTROL_BORDER_SPACE);
		if(m_tPaintDetails.cPaintingRect.right < m_tPaintDetails.cPaintingRect.left) {
			m_tPaintDetails.cPaintingRect.right = m_tPaintDetails.cPaintingRect.left;
		}
		if(m_tPaintDetails.cPaintingRect.bottom < m_tPaintDetails.cPaintingRect.top) {
			m_tPaintDetails.cPaintingRect.bottom = m_tPaintDetails.cPaintingRect.top;
		}
	}
	m_tPaintDetails.nVisibleLines = m_tPaintDetails.cPaintingRect.Height() / m_tPaintDetails.nLineHeight;
	m_tPaintDetails.nLastLineHeight = m_tPaintDetails.cPaintingRect.Height() % m_tPaintDetails.nLineHeight;
	if(m_tPaintDetails.nLastLineHeight > 0) {
		m_tPaintDetails.nFullVisibleLines = m_tPaintDetails.nVisibleLines;
		m_tPaintDetails.nVisibleLines++;
	} else {
		m_tPaintDetails.nFullVisibleLines = m_tPaintDetails.nVisibleLines;
		m_tPaintDetails.nLastLineHeight = m_tPaintDetails.nLineHeight;
	}
	
	// position & size of the address
	if(m_bShowAddress) {
		m_tPaintDetails.nAddressPos = 0;
		m_tPaintDetails.nAddressLen = ADR_DATA_SPACE + m_tPaintDetails.nCharacterWidth*m_nAdrSize;
	} else {
		m_tPaintDetails.nAddressPos = 0;
		m_tPaintDetails.nAddressLen = 0;
	}

	// Calculate how many bytes per line we can display, when this is automatically calculated
	if(m_bAutoBytesPerRow && GetStyle() & ES_MULTILINE) {
		int iFreeSpace = m_tPaintDetails.cPaintingRect.Width() - m_tPaintDetails.nAddressLen;
		if(m_bShowAscii) {			
			iFreeSpace -= DATA_ASCII_SPACE;
			if(iFreeSpace < 0) {
				m_tPaintDetails.nBytesPerRow = 1;
			} else {
				m_tPaintDetails.nBytesPerRow = iFreeSpace / (4*m_tPaintDetails.nCharacterWidth) ; // 2(HEXDATA)+1(Space)+1(Ascii) = 4
				if( (iFreeSpace%(4*m_tPaintDetails.nCharacterWidth)) >= (3*m_tPaintDetails.nCharacterWidth) ) {
					m_tPaintDetails.nBytesPerRow++; // we actually only need n-1 spaces not n (n = nBytesPerRow)
				}
			}
		} else {
			if(iFreeSpace < 0) {
				m_tPaintDetails.nBytesPerRow = 1;
			} else {
				m_tPaintDetails.nBytesPerRow = iFreeSpace / (3*m_tPaintDetails.nCharacterWidth) ; // 2(HEXDATA)+1(Space) = 3
				if( (iFreeSpace%(3*m_tPaintDetails.nCharacterWidth)) >= (2*m_tPaintDetails.nCharacterWidth) ) {
					m_tPaintDetails.nBytesPerRow++; // we actually only need n-1 spaces not n (n = nBytesPerRow)
				}
			}
		}
		//remark: m_nBytesPerRow=0 is a valid thing... (not very lucky thing, but valid)
	} else {		
		m_tPaintDetails.nBytesPerRow = m_nBytesPerRow;
	}
	if(!(GetStyle() & ES_MULTILINE)) {
		m_tPaintDetails.nBytesPerRow = GetDataSize1();
	}
	if(m_tPaintDetails.nBytesPerRow == 0) {
		m_tPaintDetails.nBytesPerRow = 1;
	}

	// position & size of the hex-data
	m_tPaintDetails.nHexPos = m_tPaintDetails.nAddressPos + m_tPaintDetails.nAddressLen;
	m_tPaintDetails.nHexLen = (m_tPaintDetails.nBytesPerRow*2 + m_tPaintDetails.nBytesPerRow-1)*m_tPaintDetails.nCharacterWidth;
														//2(HEXData) + 1(Space) (only n-1 spaces needed)
	iWidth = m_tPaintDetails.nHexPos + m_tPaintDetails.nHexLen;
	m_tPaintDetails.nHexLen += DATA_ASCII_SPACE;
	
	// position & size of the ascii-data
	if(m_bShowAscii) {
		m_tPaintDetails.nAsciiPos = m_tPaintDetails.nHexPos + m_tPaintDetails.nHexLen;
		m_tPaintDetails.nAsciiLen = m_tPaintDetails.nBytesPerRow * m_tPaintDetails.nCharacterWidth;
		iWidth = m_tPaintDetails.nAsciiPos + m_tPaintDetails.nAsciiLen;
		iWidth++;
	} else {
		m_tPaintDetails.nAsciiPos = 0;
		m_tPaintDetails.nAsciiLen = 0;
	}

	if(pOldFont != NULL) {
		pOldFont = cDC.SelectObject(pOldFont);
	}

	// calculate scrollranges	
	// Y-Bar
	UINT nTotalLines;
	nTotalLines = (GetDataSize1() + m_tPaintDetails.nBytesPerRow-1)/m_tPaintDetails.nBytesPerRow;
	if(nTotalLines > m_tPaintDetails.nFullVisibleLines) {
		m_nScrollRangeY = nTotalLines - m_tPaintDetails.nFullVisibleLines;
	} else {
		m_nScrollRangeY = 0;
	}
	if(m_nScrollPostionY > m_nScrollRangeY) {
		m_nScrollPostionY = m_nScrollRangeY;
	}

	// X-Bar
	if(iWidth > m_tPaintDetails.cPaintingRect.Width()) {
		m_nScrollRangeX = iWidth - m_tPaintDetails.cPaintingRect.Width();
	} else {
		m_nScrollRangeX = 0;
	}
	if(m_nScrollPostionX > m_nScrollRangeX) {
		m_nScrollPostionX = m_nScrollRangeX;
	}
	PostMessage(UM_SETSCROLRANGE, 0 ,0);
}

void CHexEditBase::PaintAddresses(CDC& cDC)
{
	ASSERT(m_tPaintDetails.nBytesPerRow > 0);

	UINT nAdr;
	UINT nEndAdr;
	CString cAdrFormatString;
	CRect cAdrRect(m_tPaintDetails.cPaintingRect);
	_TCHAR pBuf[32];
	CBrush cBkgBrush;
	
	// create the format string
	cAdrFormatString.Format(_T("%%0%uX"), m_nAdrSize);

	// the Rect for painting & background
	cBkgBrush.CreateSolidBrush(m_tAdrBkgCol);
	cAdrRect.left += m_tPaintDetails.nAddressPos - m_nScrollPostionX;
	cAdrRect.right = cAdrRect.left + m_tPaintDetails.nAddressLen - ADR_DATA_SPACE; // without border
	cDC.FillRect(cAdrRect, &cBkgBrush);
	cAdrRect.bottom = cAdrRect.top + m_tPaintDetails.nLineHeight;

	// start & end-address
	nAdr = m_nScrollPostionY * m_tPaintDetails.nBytesPerRow;
	nEndAdr = nAdr + m_tPaintDetails.nVisibleLines*m_tPaintDetails.nBytesPerRow;
	if(nEndAdr >= GetDataSize1()) {
		nEndAdr = GetDataSize1()-1;
	}

	//  paint
	cDC.SetBkMode(OPAQUE);
	cDC.SetTextColor(m_tAdrTxtCol);
	cDC.SetBkColor(m_tAdrBkgCol);
	for(; nAdr<=nEndAdr; nAdr+=m_tPaintDetails.nBytesPerRow) {
		_sntprintf(pBuf, 32, (LPCTSTR)cAdrFormatString, nAdr); // slightly faster then CString::Format
		cDC.DrawText(pBuf, (LPRECT)cAdrRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
		cAdrRect.OffsetRect(0, m_tPaintDetails.nLineHeight);
	}
}	

UINT CHexEditBase::CreateHighlightingPolygons(const CRect& cHexRect,
										  UINT nBegin, UINT nEnd, POINT *pPoints)
{
	ASSERT(pPoints != NULL);
	ASSERT(nBegin <= nEnd);
	ASSERT(m_nLength < MAXHEXEDITLENGTH); // to make sure we don't have an overflow
	ASSERT(nBegin < m_nLength);
	ASSERT(nEnd < m_nLength);
	ASSERT(m_tPaintDetails.nBytesPerRow > 0);

	// iBegin & iEnd represents the relative Address (relativ accoring the scrollposition)
	int iBegin = nBegin - m_nScrollPostionY*m_tPaintDetails.nBytesPerRow;
	int iEnd = 1+nEnd - m_nScrollPostionY*m_tPaintDetails.nBytesPerRow;
	int iBeginRow = iBegin/(int)m_tPaintDetails.nBytesPerRow;
	int iBeginColumn = iBegin%(int)m_tPaintDetails.nBytesPerRow;
	int iEndRow = iEnd/(int)m_tPaintDetails.nBytesPerRow;
	int iEndColumn = iEnd%(int)m_tPaintDetails.nBytesPerRow;
	int iCount = 0;

	// iBegin, iEnd may be negativ
	if( (iEnd <= 0) || (iBegin >= (int)(m_tPaintDetails.nVisibleLines * m_tPaintDetails.nBytesPerRow)) ) {
		return 0; // nothing to see, polygon has 0-length
	}
	if( (iEndRow == iBeginRow+1) && (iEndColumn == 0) ) {
		iEndRow = iBeginRow;
		iEndColumn = m_tPaintDetails.nBytesPerRow;
	}

	// first two or one point(s)
	if(iBeginRow < -1) {
		// we don't see the beginning (or any parts of it)
		pPoints[iCount].x = (short)cHexRect.left-2;
		pPoints[iCount].y = (short)cHexRect.top-1;
		++iCount;
	} else  {
		if(iBeginColumn < 0 && iBeginRow == 0) {
			// must be the case where a part of the first line is not visible
			iBeginColumn += m_tPaintDetails.nBytesPerRow;
			iBeginRow = -1;
		} 
		if(iBeginColumn < 0) {
			iBeginColumn = 0;
		}
		pPoints[iCount].x = (short)cHexRect.left - 2 + iBeginColumn * 3 * m_tPaintDetails.nCharacterWidth;
		pPoints[iCount].y = (short)cHexRect.top + (1+iBeginRow) * m_tPaintDetails.nLineHeight;
		++iCount;
		pPoints[iCount].x = pPoints[iCount-1].x;
		pPoints[iCount].y = pPoints[iCount-1].y - m_tPaintDetails.nLineHeight;
		++iCount;
	}
	if( iBeginRow == iEndRow ) {
		// a simple one (two more points and we are finished
		pPoints[iCount].x = (short)cHexRect.left + 2 + (iEndColumn*3 - 1) * m_tPaintDetails.nCharacterWidth;
		pPoints[iCount].y = (short)cHexRect.top + iEndRow * m_tPaintDetails.nLineHeight;
		++iCount;
		pPoints[iCount].x = pPoints[iCount-1].x;
		pPoints[iCount].y = pPoints[iCount-1].y + m_tPaintDetails.nLineHeight;
		++iCount;
	} else { 
		// iEndRow > iBeginRow
		pPoints[iCount].x = (short)cHexRect.right + 1;
		pPoints[iCount].y = iCount > 1 ? pPoints[1].y : pPoints[0].y;
		++iCount;
		pPoints[iCount].x = (short)cHexRect.right + 1;
		pPoints[iCount].y = (short)cHexRect.top + iEndRow*m_tPaintDetails.nLineHeight;		
		++iCount;
		if(iEndColumn>0) {
			pPoints[iCount].x = (short)cHexRect.left + 2 + (iEndColumn*3 - 1) * m_tPaintDetails.nCharacterWidth;
			pPoints[iCount].y = pPoints[iCount-1].y;
			++iCount;
			pPoints[iCount].x = pPoints[iCount-1].x;
			pPoints[iCount].y = pPoints[iCount-1].y + m_tPaintDetails.nLineHeight;
			++iCount;
		}
		pPoints[iCount].x = (short)cHexRect.left - 2;
		pPoints[iCount].y = pPoints[iCount-1].y;
		++iCount;
		pPoints[iCount].x = (short)cHexRect.left - 2;
		pPoints[iCount].y = pPoints[0].y;
		++iCount;
	}
	ASSERT(iCount <= MAX_HIGHLIGHT_POLYPOINTS);
	return iCount; 
}

void CHexEditBase::PaintHexData(CDC& cDC)
{
	ASSERT(m_tPaintDetails.nBytesPerRow > 0);
	ASSERT(m_tPaintDetails.nBytesPerRow*3 < 1021);

	if((m_nLength < 1) || (m_pData == NULL)) {
		return;
	}

	UINT nAdr;
	UINT nEndAdr;
	UINT nSelectionCount=0;
	char pBuf[1024]; 
	char *pBufPtr;
	char *pSelectionBufPtrBegin;
	char *pSelectionBufPtrEnd;
	char *pHighlightedBufPtrBegin;
	char *pHighlightedBufPtrEnd;
	BYTE *pDataPtr;
	BYTE *pEndDataPtr;
	BYTE *pEndLineDataPtr;
	BYTE *pSelectionPtrBegin;
	BYTE *pSelectionPtrEnd;
	BYTE *pHighlightedPtrBegin;
	BYTE *pHighlightedPtrEnd;
	CRect cHexRect(m_tPaintDetails.cPaintingRect);
	CBrush cBkgBrush;
	CBrush *pOldBrush = NULL;
	CPen *pOldPen;
	POINT pHighlightPolygon[MAX_HIGHLIGHT_POLYPOINTS];

	// prepare the buffer for the formated hex-data
	memset(pBuf, ' ', m_tPaintDetails.nBytesPerRow*3);	// fill with spaces
	pBuf[m_tPaintDetails.nBytesPerRow*3-1] = '\0';		// zero-terminate
	
	// the Rect for painting & background
	cBkgBrush.CreateSolidBrush(m_tHexBkgCol);
	cHexRect.left += m_tPaintDetails.nHexPos - m_nScrollPostionX;
	cHexRect.right = cHexRect.left + m_tPaintDetails.nHexLen - DATA_ASCII_SPACE;
	cDC.FillRect(cHexRect, &cBkgBrush);
	cHexRect.bottom = cHexRect.top + m_tPaintDetails.nLineHeight;
	
	// highlighting section (only background and frame)
	if( (m_nHighlightedBegin != NOSECTION_VAL) && (m_nHighlightedEnd != NOSECTION_VAL) ) {
		nSelectionCount = CreateHighlightingPolygons(cHexRect, m_nHighlightedBegin, m_nHighlightedEnd, pHighlightPolygon);
		CBrush cBrush(m_tHighlightBkgCol);
		CPen cPen(PS_SOLID, 1, m_tHighlightFrameCol);
		pOldBrush = cDC.SelectObject(&cBrush);
		pOldPen = cDC.SelectObject(&cPen);
		cDC.Polygon(pHighlightPolygon, nSelectionCount);
		if(pOldBrush != NULL) {
			cDC.SelectObject(pOldBrush);
		}
		if(pOldPen != NULL) {
			cDC.SelectObject(pOldPen);
		}
		pHighlightedPtrBegin = m_pData + m_nHighlightedBegin;
		pHighlightedPtrEnd = m_pData + m_nHighlightedEnd;
	} else {
		pHighlightedPtrBegin = m_pData + m_nHighlightedBegin;
		pHighlightedPtrEnd = m_pData + m_nHighlightedEnd;
	}

	// selection (pointers)
	if( (m_nSelectionBegin != NOSECTION_VAL) && (m_nSelectionEnd != NOSECTION_VAL) ) {
		pSelectionPtrBegin = m_pData + m_nSelectionBegin;
		pSelectionPtrEnd = m_pData + m_nSelectionEnd;
	} else {
		pSelectionPtrBegin = NULL;
		pSelectionPtrEnd = NULL;
	}
	
	// start & end-address (& pointers)
	nAdr = m_nScrollPostionY * m_tPaintDetails.nBytesPerRow;
	nEndAdr = nAdr + m_tPaintDetails.nVisibleLines*m_tPaintDetails.nBytesPerRow;
	if(nEndAdr >= GetDataSize()) {
		nEndAdr = GetDataSize()-1;
	}
	pDataPtr = m_pData + nAdr;
	pEndDataPtr = m_pData + nEndAdr;
	if( (m_nHighlightedBegin != NOSECTION_VAL) && (m_nHighlightedEnd != NOSECTION_VAL) ) {
	}

	//  paint
	cDC.SetBkMode(TRANSPARENT);
	while(pDataPtr<pEndDataPtr+1) {
		pEndLineDataPtr = pDataPtr + m_tPaintDetails.nBytesPerRow;
		if(pEndLineDataPtr>pEndDataPtr) {
			pEndLineDataPtr = pEndDataPtr+1;
		}
		pSelectionBufPtrBegin = NULL;
		pSelectionBufPtrEnd = NULL;
		pHighlightedBufPtrBegin = NULL;
		pHighlightedBufPtrEnd = NULL;
		if( (pDataPtr >= pSelectionPtrBegin) && (pDataPtr <= pSelectionPtrEnd) ) {
			pSelectionBufPtrBegin = pBuf;
		}
		if( (pDataPtr >= pHighlightedPtrBegin) && (pDataPtr <= pHighlightedPtrEnd) ) {
			pHighlightedBufPtrBegin = pBuf;
		}
		for(pBufPtr=pBuf; pDataPtr<pEndLineDataPtr; ++pDataPtr) {
			if(pDataPtr == pSelectionPtrBegin) {
				pSelectionBufPtrBegin = pBufPtr;
			}
			if(pDataPtr == pSelectionPtrEnd) {
				if(pSelectionBufPtrBegin == NULL) {
					pSelectionBufPtrBegin = pBuf;
				}
				pSelectionBufPtrEnd = pBufPtr + 2;
			}
			if(pDataPtr == pHighlightedPtrBegin) {
				pHighlightedBufPtrBegin = pBufPtr;
			}
			if(pDataPtr == pHighlightedPtrEnd) {
				if(pHighlightedBufPtrBegin == NULL) {
					pHighlightedBufPtrBegin = pBuf;
				}
				pHighlightedBufPtrEnd = pBufPtr + 2;
			}
			*pBufPtr++ = tabHexCharacters[*pDataPtr>>4];
			*pBufPtr++ = tabHexCharacters[*pDataPtr&0xf];
			*pBufPtr++;
		}
		*--pBufPtr = '\0';
		// set end-pointers
		if(pHighlightedBufPtrEnd == NULL) {
			pHighlightedBufPtrEnd = pBufPtr;
		}
		if(pSelectionBufPtrEnd == NULL) {
			pSelectionBufPtrEnd = pBufPtr;
		}

		// first draw all normal
		cDC.SetTextColor(m_tHexTxtCol);
		cDC.DrawText(pBuf, (LPRECT)cHexRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
		
		// highlighted section now
		if(pHighlightedBufPtrBegin != NULL) {
			CRect cRect(cHexRect);
			cRect.left += (pHighlightedBufPtrBegin-pBuf) * m_tPaintDetails.nCharacterWidth;
			*pHighlightedBufPtrEnd = '\0'; // set "end-mark"
			cDC.SetTextColor(m_tHighlightTxtCol);
			cDC.SetBkColor(m_tHighlightBkgCol);
			cDC.DrawText(pHighlightedBufPtrBegin, (LPRECT)cRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
			*pHighlightedBufPtrEnd = ' '; // restore the buffer
		}
		
		// selection
		if(pSelectionBufPtrBegin != NULL) {
			bool bHasFocus = GetFocus() == this;
			if(bHasFocus || (GetStyle() & ES_MULTILINE)) { // todo: flag für show selection always
				CRect cRect(cHexRect);
				cRect.left += (pSelectionBufPtrBegin-pBuf) * m_tPaintDetails.nCharacterWidth;
				cRect.right -= (pBuf-1+m_tPaintDetails.nBytesPerRow*3-pSelectionBufPtrEnd) * m_tPaintDetails.nCharacterWidth;
				CRect cSelectionRect(cRect);
				cSelectionRect.InflateRect(0, -1, +1, 0);
				cDC.FillRect(cSelectionRect, &CBrush(bHasFocus ? m_tSelectedFousBkgCol : m_tSelectedNoFocusBkgCol));
				*pSelectionBufPtrEnd = '\0'; // set "end-mark"
				cDC.SetTextColor(bHasFocus ? m_tSelectedFousTxtCol : m_tSelectedNoFocusTxtCol);
				cDC.SetBkColor(m_tHighlightBkgCol);
				cDC.DrawText(pSelectionBufPtrBegin, (LPRECT)cRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
				*pSelectionBufPtrEnd = ' '; // restore the buffer
			}
		}
		cHexRect.OffsetRect(0, m_tPaintDetails.nLineHeight);
	}
	if( (m_nHighlightedBegin != NOSECTION_VAL) && (m_nHighlightedEnd != NOSECTION_VAL) ) {
		CPen cPen(PS_SOLID, 1, m_tHighlightFrameCol);
		pOldPen = cDC.SelectObject(&cPen);
		cDC.Polyline(pHighlightPolygon, nSelectionCount);
		if(pOldBrush != NULL) {
			cDC.SelectObject(pOldBrush);
		}
		if(pOldPen != NULL) {
			cDC.SelectObject(pOldPen);
		}
	}
}

void CHexEditBase::PaintAsciiData(CDC& cDC)
{
ASSERT(m_tPaintDetails.nBytesPerRow > 0);
	ASSERT(m_tPaintDetails.nBytesPerRow < 512);

	if((m_nLength < 1) || (m_pData == NULL)) {
		return;
	}

	UINT nAdr;
	UINT nEndAdr;
	CRect cAsciiRect(m_tPaintDetails.cPaintingRect);
	char pBuf[512];
	char *pBufPtr;
	CBrush cBkgBrush;
	BYTE *pDataPtr;
	BYTE *pDataPtrEnd;

	UINT nSelectionCount = 0;
	POINT pHighlightPolygon[MAX_HIGHLIGHT_POLYPOINTS];
	CBrush *pOldBrush = NULL;
	CPen *pOldPen;
	BYTE *pHighlightedPtrBegin;
	BYTE *pHighlightedPtrEnd;
	BYTE *pSelectionPtrBegin;
	BYTE *pSelectionPtrEnd;
	BYTE *pEndDataPtr;
	char *pSelectionBufPtrBegin;
	char *pSelectionBufPtrEnd;
	char *pHighlightedBufPtrBegin;
	char *pHighlightedBufPtrEnd;
	
	memset(pBuf, '\0', m_tPaintDetails.nBytesPerRow+1);

	// the Rect for painting & background
	cBkgBrush.CreateSolidBrush(m_tAsciiBkgCol);
	cAsciiRect.left += m_tPaintDetails.nAsciiPos - m_nScrollPostionX;
	cAsciiRect.right = cAsciiRect.left + m_tPaintDetails.nAsciiLen;
	cDC.FillRect(cAsciiRect, &cBkgBrush);
	cAsciiRect.bottom = cAsciiRect.top + m_tPaintDetails.nLineHeight;

	//highlighting section
	if((m_nHighlightedBegin != NOSECTION_VAL) && (m_nHighlightedEnd != NOSECTION_VAL)){
		nSelectionCount = CreateHighlightingPolygons(cAsciiRect,m_nHighlightedBegin,m_nHighlightedEnd,pHighlightPolygon);
		CBrush cBrush(m_tHighlightBkgCol);
		CPen cPen(PS_SOLID,1,m_tHighlightFrameCol);
		pOldBrush = cDC.SelectObject(&cBrush);
		pOldPen = cDC.SelectObject(&cPen);
		cDC.Polygon(pHighlightPolygon,nSelectionCount);
		if(pOldBrush != NULL){
			cDC.SelectObject(pOldBrush);
		}
		if(pOldPen != NULL){
			cDC.SelectObject(pOldPen);
		}
		pHighlightedPtrBegin = m_pData + m_nHighlightedBegin;
		pHighlightedPtrEnd = m_pData + m_nHighlightedEnd;
	}
	else{
		pHighlightedPtrBegin = m_pData + m_nHighlightedBegin;
		pHighlightedPtrEnd = m_pData + m_nHighlightedEnd;
	}
	// selection (pointers)
	if( (m_nSelectionBegin != NOSECTION_VAL) && (m_nSelectionEnd != NOSECTION_VAL) ) {
		pSelectionPtrBegin = m_pData + m_nSelectionBegin;
		pSelectionPtrEnd = m_pData + m_nSelectionEnd;
	} else {
		pSelectionPtrBegin = NULL;
		pSelectionPtrEnd = NULL;
	}
	//highlighting section




	// start & end-address
	nAdr = m_nScrollPostionY * m_tPaintDetails.nBytesPerRow;
	nEndAdr = nAdr + m_tPaintDetails.nVisibleLines*m_tPaintDetails.nBytesPerRow;
	if(nEndAdr >= m_nLength) {
		nEndAdr = m_nLength-1;
	}
	pDataPtr = m_pData + nAdr;

	pEndDataPtr = m_pData + nEndAdr;  //pEndDataPtr = m_pData + nEndAdr;
	if((m_nHighlightedBegin != NOSECTION_VAL) && (m_nHighlightedEnd != NOSECTION_VAL)){
	}


	//  paint
	cDC.SetBkMode(TRANSPARENT);
	cDC.SetTextColor(m_tAsciiTxtCol);
	cDC.SetBkColor(m_tAsciiBkgCol);
	for(; nAdr<=nEndAdr; nAdr+=m_tPaintDetails.nBytesPerRow) {
		pDataPtrEnd = pDataPtr + m_tPaintDetails.nBytesPerRow;
		if(pDataPtrEnd > m_pData + nEndAdr) {
			pDataPtrEnd = m_pData + nEndAdr+1;
		}

		pSelectionBufPtrBegin = NULL;
		pSelectionBufPtrEnd = NULL;
		pHighlightedBufPtrBegin = NULL;
		pHighlightedBufPtrEnd = NULL;
		if( (pDataPtr >= pSelectionPtrBegin) && (pDataPtr <= pSelectionPtrEnd) ) {
			pSelectionBufPtrBegin = pBuf;
		}
		if( (pDataPtr >= pHighlightedPtrBegin) && (pDataPtr <= pHighlightedPtrEnd) ) {
			pHighlightedBufPtrBegin = pBuf;
		}

		for(pBufPtr=pBuf; pDataPtr<pDataPtrEnd; ++pDataPtr, ++pBufPtr) {

			if(pDataPtr == pSelectionPtrBegin) {
				pSelectionBufPtrBegin = pBufPtr;
			}
			if(pDataPtr == pSelectionPtrEnd) {
				if(pSelectionBufPtrBegin == NULL) {
					pSelectionBufPtrBegin = pBuf;
				}
				pSelectionBufPtrEnd = pBufPtr + 1;
			}
			if(pDataPtr == pHighlightedPtrBegin) {
				pHighlightedBufPtrBegin = pBufPtr;
			}
			if(pDataPtr == pHighlightedPtrEnd) {
				if(pHighlightedBufPtrBegin == NULL) {
					pHighlightedBufPtrBegin = pBuf;
				}
				pHighlightedBufPtrEnd = pBufPtr + 1;
			}

			*pBufPtr = isprint(*pDataPtr) ? (char)*pDataPtr : '.';
		}
		*pBufPtr = '\0';

		// set end-pointers
		if(pHighlightedBufPtrEnd == NULL) {
			pHighlightedBufPtrEnd = pBufPtr;
		}
		if(pSelectionBufPtrEnd == NULL) {
			pSelectionBufPtrEnd = pBufPtr;
		}

		cDC.SetTextColor(m_tAsciiTxtCol); 
		cDC.DrawText(pBuf, (LPRECT)cAsciiRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);


		 //highlighted section now
		if(pHighlightedBufPtrBegin != NULL) {
			CRect cRect(cAsciiRect);
			cRect.left += (pHighlightedBufPtrBegin-pBuf) * m_tPaintDetails.nCharacterWidth;
			*pHighlightedBufPtrEnd = '\0'; // set "end-mark"
			cDC.SetTextColor(m_tHighlightTxtCol);
			cDC.SetBkColor(m_tHighlightBkgCol);
			cDC.DrawText(pHighlightedBufPtrBegin, (LPRECT)cRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
			*pHighlightedBufPtrEnd = ' '; // restore the buffer
		}
		
		//// selection
		if(pSelectionBufPtrBegin != NULL) {
			bool bHasFocus = GetFocus() == this;
			if(bHasFocus || (GetStyle() & ES_MULTILINE)) { // todo: flag für show selection always
				CRect cRect(cAsciiRect);
				cRect.left += (pSelectionBufPtrBegin-pBuf) * m_tPaintDetails.nCharacterWidth;
				cRect.right -= (pBuf + m_tPaintDetails.nBytesPerRow - pSelectionBufPtrEnd)*m_tPaintDetails.nCharacterWidth;
				CRect cSelectionRect(cRect);
				cSelectionRect.InflateRect(0, -1, +1, 0);
				cDC.FillRect(cSelectionRect, &CBrush(bHasFocus ? m_tSelectedFousBkgCol : m_tSelectedNoFocusBkgCol));
				*pSelectionBufPtrEnd = '\0'; // set "end-mark"
				cDC.SetTextColor(bHasFocus ? m_tSelectedFousTxtCol : m_tSelectedNoFocusTxtCol);
				cDC.SetBkColor(m_tHighlightBkgCol);
				cDC.DrawText(pSelectionBufPtrBegin, (LPRECT)cRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
				*pSelectionBufPtrEnd = ' '; // restore the buffer
			}
		}

		cAsciiRect.OffsetRect(0, m_tPaintDetails.nLineHeight);
	}

	if( (m_nHighlightedBegin != NOSECTION_VAL) && (m_nHighlightedEnd != NOSECTION_VAL) ) {
		CPen cPen(PS_SOLID, 1, m_tHighlightFrameCol);
		pOldPen = cDC.SelectObject(&cPen);
		cDC.Polyline(pHighlightPolygon, nSelectionCount);
		if(pOldBrush != NULL) {
			cDC.SelectObject(pOldBrush);
		}
		if(pOldPen != NULL) {
			cDC.SelectObject(pOldPen);
		}
	}

}

void CHexEditBase::OnPaint() 
{
	CPaintDC cPaintDC(this);
	CRect cClientRect;
	CDC	cMemDC;
	CBitmap cBmp;
	CBitmap *pOldBitmap;
	CFont *pOldFont;
	CBrush cBackBrush;

	// memorybuffered output (via a memorybitmap)
	cMemDC.CreateCompatibleDC(&cPaintDC);
	GetClientRect(cClientRect);	
	cBmp.CreateCompatibleBitmap(&cPaintDC, cClientRect.right, cClientRect.bottom);
	pOldBitmap = cMemDC.SelectObject(&cBmp);
	pOldFont = cMemDC.SelectObject(&m_cFont);
	
	if(m_bRecalc) {
		CalculatePaintingDetails(cMemDC);
	}

	cBackBrush.CreateSolidBrush(m_tNotUsedBkCol);
	cMemDC.FillRect(cClientRect, &cBackBrush);
	
	CRgn cRegn;
	CRect cRect(m_tPaintDetails.cPaintingRect);
	cRect.left-=2;
	cRect.right+=2;
	cRegn.CreateRectRgnIndirect((LPCRECT)cRect);
	cMemDC.SelectClipRgn(&cRegn);

	if(m_bShowAddress) {
		PaintAddresses(cMemDC);
	}
	PaintHexData(cMemDC);
	if(m_bShowAscii) {
		PaintAsciiData(cMemDC);
	}

	cPaintDC.BitBlt(0, 0, cClientRect.right, cClientRect.bottom, &cMemDC, 0, 0, SRCCOPY);
	if(pOldFont != NULL) {
		cMemDC.SelectObject(pOldFont);
	}
	if(pOldBitmap != NULL) {
		cMemDC.SelectObject(pOldBitmap);
	}
}

void CHexEditBase::MakeVisible(UINT nBegin, UINT nEnd, bool bUpdate)
{
	ASSERT(nBegin<=nEnd);

	UINT nAdrBeg = m_nScrollPostionY * m_tPaintDetails.nBytesPerRow;
	UINT nFullBytesPerScreen = m_tPaintDetails.nFullVisibleLines * m_tPaintDetails.nBytesPerRow;
	UINT nAdrEnd = nAdrBeg + nFullBytesPerScreen;
	UINT nLength = nEnd - nBegin;
	if( (nBegin > nAdrBeg) || (nEnd < nAdrEnd) ) {
		// don't do anything when it's simply not possible to see everything and
		// we already see one ful page.
		if(nLength > nFullBytesPerScreen) {
			if(nAdrBeg < nBegin) {
				SetScrollPositionY(nBegin/m_tPaintDetails.nBytesPerRow, false);
			} else if (nAdrEnd > nEnd) {
				SetScrollPositionY((nEnd-nFullBytesPerScreen+m_tPaintDetails.nBytesPerRow)/m_tPaintDetails.nBytesPerRow, false); 
			}
		} else {
			if(nAdrBeg > nBegin) {
				SetScrollPositionY(nBegin/m_tPaintDetails.nBytesPerRow, false);
			} else if (nAdrEnd < nEnd) {
				SetScrollPositionY((nEnd-nFullBytesPerScreen+m_tPaintDetails.nBytesPerRow)/m_tPaintDetails.nBytesPerRow, false); 
			}
		}
	}

	int iLineX = (int)((nBegin%m_tPaintDetails.nBytesPerRow)*3*m_tPaintDetails.nCharacterWidth + m_tPaintDetails.nHexPos + m_tPaintDetails.cPaintingRect.left) - (int)m_nScrollPostionX;
	int iLineX2 = (int)((2+(nEnd%m_tPaintDetails.nBytesPerRow)*3)*m_tPaintDetails.nCharacterWidth + m_tPaintDetails.nHexPos + m_tPaintDetails.cPaintingRect.left) - (int)m_nScrollPostionX;
	if(iLineX > iLineX2) {
		int iTemp = iLineX;
		iLineX = iLineX2;
		iLineX2 = iTemp;
	}
	if( (iLineX <= m_tPaintDetails.cPaintingRect.left) && (iLineX2 >= m_tPaintDetails.cPaintingRect.right) ) {
		// nothing to do here...
	} else if(iLineX < m_tPaintDetails.cPaintingRect.left) {
		SetScrollPositionX(m_nScrollPostionX + iLineX - m_tPaintDetails.cPaintingRect.left, false);
	} else if(iLineX2 >= m_tPaintDetails.cPaintingRect.right) {
		SetScrollPositionX(m_nScrollPostionX + iLineX2 - m_tPaintDetails.cPaintingRect.Width(), false);
	}

	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetScrollbarRanges()
{
	if(!(GetStyle() & ES_MULTILINE)) {
		return;
	}

	SCROLLINFO tScrollInfo;
	memset(&tScrollInfo, 0, sizeof(SCROLLINFO));
	tScrollInfo.cbSize = sizeof(SCROLLINFO);
	if(m_nScrollRangeY > 0) {
		ShowScrollBar(SB_VERT, TRUE);
		EnableScrollBar(SB_VERT);
		tScrollInfo.fMask = SIF_ALL ;
		tScrollInfo.nPage = m_tPaintDetails.nFullVisibleLines;
		tScrollInfo.nMax = m_nScrollRangeY + tScrollInfo.nPage - 1;
		if(m_nScrollPostionY > m_nScrollRangeY) {
			m_nScrollPostionY = m_nScrollRangeY;
		}
		tScrollInfo.nPos = m_nScrollPostionY;
		SetScrollInfo(SB_VERT, &tScrollInfo, TRUE);
	} else {
		ShowScrollBar(SB_VERT, FALSE);
	}
	if(m_nScrollRangeX > 0) {
		EnableScrollBar(SB_HORZ);
		ShowScrollBar(SB_HORZ, TRUE);
		tScrollInfo.fMask = SIF_ALL ;
		tScrollInfo.nPage = m_tPaintDetails.cPaintingRect.Width();
		tScrollInfo.nMax = m_nScrollRangeX + tScrollInfo.nPage - 1;
		if(m_nScrollPostionX > m_nScrollRangeX) {
			m_nScrollPostionX = m_nScrollRangeX;
		}
		tScrollInfo.nPos = m_nScrollPostionX;
		SetScrollInfo(SB_HORZ, &tScrollInfo, TRUE);
	} else {
		ShowScrollBar(SB_HORZ, FALSE);
	}
}

void CHexEditBase::OnSetFocus(CWnd*) 
{	
	SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
	Invalidate();
}

void CHexEditBase::OnKillFocus(CWnd* pNewWnd) 
{
	DestoyEditCaret();
	CWnd::OnKillFocus(pNewWnd);
	Invalidate();
}

void CHexEditBase::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	CalculatePaintingDetails(CClientDC(this));
	SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
	SetScrollbarRanges();
}

void CHexEditBase::MoveScrollPostionY(int iDelta, bool bUpdate)
{
	if(iDelta > 0) {
		SetScrollPositionY(m_nScrollPostionY+iDelta, bUpdate);
	} else {
		int iPositon = (int)m_nScrollPostionY;
		iPositon -= (-iDelta);
		if(iPositon < 0) {
			iPositon = 0;
		}
		SetScrollPositionY((UINT)iPositon, bUpdate);
	}
}

void CHexEditBase::MoveScrollPostionX(int iDelta, bool bUpdate)
{
	if(iDelta > 0) {
		SetScrollPositionX(m_nScrollPostionX+iDelta, bUpdate);
	} else {
		int iPositon = (int)m_nScrollPostionX;
		iPositon -= (-iDelta);
		if(iPositon < 0) {
			iPositon = 0;
		}
		SetScrollPositionX((UINT)iPositon, bUpdate);
	}
}

void CHexEditBase::GetAddressFromPoint(const CPoint& cPt, UINT& nAddress, bool& bHighBits)
{	
	bool bAscii = false;
	CPoint cPoint(cPt);
	cPoint.x += m_nScrollPostionX;
	cPoint.x += (m_tPaintDetails.nCharacterWidth>>1);
	cPoint.y -= m_tPaintDetails.cPaintingRect.top;
	if((GetStyle() & ES_MULTILINE)) {
		cPoint.x -= CONTROL_BORDER_SPACE + 3; // 3 determined experimentally :-(
	}
	if(cPoint.y < 0) {
		cPoint.y = 0;
	} else if(cPoint.y > (int)(m_tPaintDetails.nVisibleLines*m_tPaintDetails.nLineHeight)) {
		cPoint.y = m_tPaintDetails.nVisibleLines*m_tPaintDetails.nLineHeight;
	}

	if((int)cPoint.x < (int)m_tPaintDetails.nHexPos){
		cPoint.x = 0;
	} else if((int)cPoint.x >= (int)(m_tPaintDetails.nAsciiPos)){
		cPoint.x -= m_tPaintDetails.nAsciiPos;
		bAscii = true;
	} else {
		cPoint.x -= m_tPaintDetails.nHexPos;
		if (cPoint.x >= (LONG)m_tPaintDetails.nHexLen - DATA_ASCII_SPACE)
			cPoint.x = (LONG)m_tPaintDetails.nHexLen - DATA_ASCII_SPACE - 1;
	}

	UINT nRow = cPoint.y / m_tPaintDetails.nLineHeight;
	UINT nCharColumn  = cPoint.x / m_tPaintDetails.nCharacterWidth ;
	UINT nColumn;
	
	if(bAscii)
		nColumn = nCharColumn;
	else
		nColumn = nCharColumn / 3;

	bHighBits = nCharColumn % 3 == 0;
	nAddress = nColumn + (nRow + m_nScrollPostionY) * m_tPaintDetails.nBytesPerRow;
	if(nAddress >= GetDataSize1()) {
		nAddress = GetDataSize1() - 1;
		bHighBits = false;
	}
	m_bCaretAscii = bAscii;
}

BOOL CHexEditBase::OnMouseWheel(UINT nFlags, short zDelta, CPoint)
{
	MoveScrollPostionY(-(zDelta/WHEEL_DELTA), true);
	return TRUE;
}

void CHexEditBase::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar*) 
{
	if(m_pData == NULL) {
		return;
	}

	switch(nSBCode) {
	case SB_LINEDOWN:
		MoveScrollPostionY(1, true);
		break;
	
	case SB_LINEUP:
		MoveScrollPostionY(-1, true);
		break;
	
	case SB_PAGEDOWN:
		MoveScrollPostionY(m_tPaintDetails.nFullVisibleLines, true);
		break;

	case SB_PAGEUP:
		MoveScrollPostionY(-(int)m_tPaintDetails.nFullVisibleLines, true);
		break;

	case SB_THUMBTRACK:
		// Windows only allows 16Bit track-positions in the callback message.
		// MFC hides this by providing a 32-bit value (nobody expects to
		// be an invalid value) which is unfortunately casted from a 16Bit value.
		// -- MSDN gives a hint (in the API-documentation) about this problem
		// -- and a solution as well. We should use GetScrollInfo here to receive
		// -- the correct 32-Bit value when our scrollrange exceeds the 16bit range
		// -- to keep it simple, I decided to always do it like this
		SCROLLINFO tScrollInfo;
		memset(&tScrollInfo, 0, sizeof(SCROLLINFO));
		if(GetScrollInfo(SB_VERT, &tScrollInfo, SIF_TRACKPOS)) {
			SetScrollPositionY(tScrollInfo.nTrackPos, true);
		}
#ifdef _DEBUG
		else {
			TRACE("CHexEditBase::OnVScroll: Error receiving trackposition while thumbtracking\n");
		}
#endif
		break;
	}
}

void CHexEditBase::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar*) 
{
	if(m_pData == NULL) {
		return;
	}

	switch(nSBCode) {
	case SB_LINEDOWN:
		MoveScrollPostionX(m_tPaintDetails.nCharacterWidth, true);
		break;
	
	case SB_LINEUP:
		MoveScrollPostionX(-(int)m_tPaintDetails.nCharacterWidth, true);
		break;
	
	case SB_PAGEDOWN:
		MoveScrollPostionX(m_tPaintDetails.cPaintingRect.Width(), true);
		break;

	case SB_PAGEUP:
		MoveScrollPostionX(-(int)m_tPaintDetails.cPaintingRect.Width(), true);
		break;

	case SB_THUMBTRACK:
		SetScrollPositionX(nPos, true);
		break;
	}
}

void CHexEditBase::SetEditCaretPos(UINT nOffset, bool bHighBits)
{	
ASSERT(::IsWindow(m_hWnd));
	
	m_nCurrentAddress = nOffset;
	m_bHighBits = bHighBits;
		
	if((m_pData == NULL) || (m_nLength == NULL) ) {
		return;
	}	
	if(m_bRecalc) {
		CalculatePaintingDetails(CClientDC(this));
	}
	if(m_nCurrentAddress < m_nScrollPostionY*m_tPaintDetails.nBytesPerRow 
		|| (m_nCurrentAddress >= (m_nScrollPostionY + m_tPaintDetails.nVisibleLines)*m_tPaintDetails.nBytesPerRow) ) {
		// not in the visible range
		DestoyEditCaret();
		return;
	}
	if(GetFocus() != this) {
		// in case we missed once something...
		DestoyEditCaret();
		return;
	}
	UINT nRelAdr = m_nCurrentAddress - m_nScrollPostionY*m_tPaintDetails.nBytesPerRow;
	UINT nRow = nRelAdr / m_tPaintDetails.nBytesPerRow;
	UINT nColumn = nRelAdr % m_tPaintDetails.nBytesPerRow;
	UINT nCarretHeight;
	UINT nCarretWidth = m_tPaintDetails.nCharacterWidth;
	if(nRow == m_tPaintDetails.nVisibleLines-1) {
		// last row can be only half visible
		nCarretHeight = m_tPaintDetails.nLastLineHeight;
	} else {
		nCarretHeight = m_tPaintDetails.nLineHeight;
	}

	UINT xpos = m_tPaintDetails.cPaintingRect.left - m_nScrollPostionX;
	if (m_bCaretAscii)
		xpos += m_tPaintDetails.nAsciiPos + nColumn * m_tPaintDetails.nCharacterWidth;
	else
		xpos += m_tPaintDetails.nHexPos + (nColumn * 3 + (bHighBits ? 0 : 1)) * m_tPaintDetails.nCharacterWidth;
	UINT ypos = m_tPaintDetails.cPaintingRect.top + 1 + nRow * m_tPaintDetails.nLineHeight;
	CPoint cCarretPoint(xpos,ypos);
	
	if( (cCarretPoint.x + (short)m_tPaintDetails.nCharacterWidth <= m_tPaintDetails.cPaintingRect.left-2 ) 
		|| (cCarretPoint.x > m_tPaintDetails.cPaintingRect.right) ) {
		// we can't see it
		DestoyEditCaret();
		return;
	}
	if(cCarretPoint.x < m_tPaintDetails.cPaintingRect.left-2) {
		nCarretWidth -= m_tPaintDetails.cPaintingRect.left-2 - cCarretPoint.x;
		cCarretPoint.x = m_tPaintDetails.cPaintingRect.left-2;
	}
	if(cCarretPoint.x + (int)nCarretWidth > (int)m_tPaintDetails.cPaintingRect.right+2) {
		nCarretWidth = m_tPaintDetails.cPaintingRect.right + 2 - cCarretPoint.x;
	}

	CreateEditCaret(nCarretHeight-1, m_bInsert ? 2 : nCarretWidth); // FIXME: hardcoded insert caret width 2
	SetCaretPos(cCarretPoint);
	ShowCaret();
}

void CHexEditBase::CreateEditCaret(UINT nCaretHeight, UINT nCaretWidth)
{
	if(!m_bHasCaret || (nCaretHeight != m_nCurCaretHeight) 
		|| (nCaretWidth != m_nCurCaretWidth) ) {
		m_bHasCaret = true;
		m_nCurCaretHeight = nCaretHeight;
		m_nCurCaretWidth = nCaretWidth;
		CreateSolidCaret(m_nCurCaretWidth, m_nCurCaretHeight);
	}
}

void CHexEditBase::DestoyEditCaret() {
	m_bHasCaret = false;
	DestroyCaret();
}

UINT CHexEditBase::OnGetDlgCode() 
{
	return DLGC_WANTALLKEYS;
}

BOOL CHexEditBase::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CWnd::PreCreateWindow(cs);
}

BOOL CHexEditBase::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	if(!CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext)) {
		return FALSE;
	}
	return TRUE;
}

BOOL CHexEditBase::OnEraseBkgnd(CDC*) 
{
	return TRUE;
}

void CHexEditBase::OnLButtonDown(UINT, CPoint point) 
{
	SetFocus();
	
	GetAddressFromPoint(point, m_nCurrentAddress, m_bHighBits);
	SetEditCaretPos(m_nCurrentAddress, m_bHighBits);

		
	int iDragCX = GetSystemMetrics(SM_CXDRAG);
	int iDragCY = GetSystemMetrics(SM_CYDRAG);
	m_cDragRect = CRect(point.x - (iDragCX>>1), point.y - (iDragCY>>1),
		point.x + (iDragCX>>1) + (iDragCX&1), //(we don't want to loose a pixel, when it's so small)
		point.y + (iDragCY>>1) + (iDragCY&1));

	m_nSelectingEnd = NOSECTION_VAL;
	m_nSelectionBegin = NOSECTION_VAL;
	m_nSelectingEnd = NOSECTION_VAL;
	m_nSelectingBeg = m_nCurrentAddress;
	SetCapture();
}

void CHexEditBase::OnLButtonUp(UINT, CPoint) 
{
	if(GetCapture() == this) {
		ReleaseCapture();
	}
	StopMouseRepeat(); // in case it's started, otherwise it doesn't matter either
	Invalidate();
}

void CHexEditBase::OnLButtonDblClk(UINT, CPoint point) 
{
	SetFocus();
	if(m_pData == NULL) {
		return;
	}
	GetAddressFromPoint(point, m_nCurrentAddress, m_bHighBits);
	SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
	if( (m_nHighlightedBegin <= m_nCurrentAddress) 
		&& (m_nHighlightedEnd >= m_nCurrentAddress) ) {
		// well it's christmas and we can doubleclick the highlighted section ;)
		m_nSelectionEnd = m_nHighlightedEnd;
		m_nSelectionBegin = m_nHighlightedBegin;
	} else {
		// or just a whole byte
		m_nSelectionEnd = m_nCurrentAddress;
		m_nSelectionBegin = m_nCurrentAddress;
	}
	Invalidate();
}

void CHexEditBase::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_pData == NULL) {
		return;
	}
	if( (nFlags & MK_LBUTTON) && (m_nSelectingBeg != NOSECTION_VAL)) {
		// first make a self built drag-detect (one that doesn't block)
		if(!m_cDragRect.PtInRect(point)) {
			m_cDragRect = CRect(-1, -1, -1, -1); // when once, out, kill it...
		} else {
			return; // okay, still not draging
		}
		if( !m_tPaintDetails.cPaintingRect.PtInRect(point) && (GetStyle()&ES_MULTILINE) ) {
			int iRepSpeed = 0;
			int iDelta = 0;
			if(point.y < m_tPaintDetails.cPaintingRect.top) {
				iDelta = -1;
				iRepSpeed = (int)m_tPaintDetails.cPaintingRect.top + 1 - (int)point.y;
			} else if(point.y > m_tPaintDetails.cPaintingRect.bottom ) {
				iDelta = 1;
				iRepSpeed = (int)point.y - (int)m_tPaintDetails.cPaintingRect.bottom + 1;
			}
			if(iDelta != 0) {
				iRepSpeed /= 5;
				if(iRepSpeed > 5) {
					iRepSpeed = 6;
				}
				StartMouseRepeat(point, iDelta, (short)(7 - iRepSpeed));
			}
			m_cMouseRepPoint = point; // make sure we always have the latest point
		} else {
			StopMouseRepeat();
		}
		GetAddressFromPoint(point, m_nCurrentAddress, m_bHighBits);
		SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
		m_nSelectingEnd = m_nCurrentAddress;
		m_nSelectionBegin = m_nSelectingBeg;
		m_nSelectionEnd = m_nSelectingEnd;
		NORMALIZE_SELECTION(m_nSelectionBegin, m_nSelectionEnd);
		Invalidate();
	}
}

void CHexEditBase::OnTimer(UINT nTimerID)
{

	if(m_bIsMouseRepActive && (nTimerID == MOUSEREP_TIMER_TID) ) {
		if(m_nMouseRepCounter > 0) {
			m_nMouseRepCounter--;
		} else {
			m_nMouseRepCounter = m_nMouseRepSpeed;
			MoveScrollPostionY(m_iMouseRepDelta, false);
			GetAddressFromPoint(m_cMouseRepPoint, m_nCurrentAddress, m_bHighBits);
			SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
			m_nSelectingEnd = m_nCurrentAddress;
			m_nSelectionBegin = m_nSelectingBeg;
			m_nSelectionEnd = m_nSelectingEnd;
			NORMALIZE_SELECTION(m_nSelectionBegin, m_nSelectionEnd);
			Invalidate();
		}
	}
}

void CHexEditBase::StartMouseRepeat(const CPoint& cPoint, int iDelta, WORD nSpeed)
{
	m_cMouseRepPoint = cPoint;
	m_nMouseRepSpeed = nSpeed;
	m_iMouseRepDelta = iDelta;
	if(!m_bIsMouseRepActive && (GetStyle() & ES_MULTILINE)) {
		m_bIsMouseRepActive = true;
		m_nMouseRepCounter = nSpeed;
		SetTimer(MOUSEREP_TIMER_TID, MOUSEREP_TIMER_ELAPSE, NULL);			
	}
}

void CHexEditBase::StopMouseRepeat()
{
	if(m_bIsMouseRepActive) {
		m_bIsMouseRepActive = false;
		KillTimer(MOUSEREP_TIMER_TID);
	}
}

bool CHexEditBase::OnEditInput(WORD nInput)
{
	ASSERT(m_nCurrentAddress < GetDataSize1());

	if( (nInput > 255) || m_bReadOnly) {
		return false;
	}
	
	BYTE nValue = 255;
	char nKey = (char)MyToLower((char)nInput);	
	if (m_bCaretAscii) {
		if (nInput <= 256)
			nValue = (BYTE)nInput;
	} else if( (nKey >= 'a') && (nKey <= 'f') ) {
		nValue = nKey - (BYTE)'a' + (BYTE)0xa;
	} else if ( (nKey >= '0') && (nKey <= '9') ) {
		nValue = nKey - (BYTE)'0';
	} else
		return false;
	ASSERT(m_nCurrentAddress <= m_nLength);
	BYTE* replaceData = 0;
	UINT replaceLen = 0;
	if (m_nCurrentAddress >= m_nLength || (m_bInsert && (m_bCaretAscii || m_bHighBits))) {
		// ensure storage is available for new byte
		if (m_nLength >= m_nCapacity) { 
			// increase capacity
			UINT cap = m_nCapacity + 1 + m_nCapacity/CAPACICTYINCDIVISOR;
			if (cap > MAXHEXEDITLENGTH || cap <= m_nCapacity)
				return false;
			BYTE *data = new BYTE[cap];
			if (!data)
				return false;
			if (m_pData) {
				if (m_nCurrentAddress > 0)
					memcpy(data, m_pData, m_nCurrentAddress);
				if (m_nCurrentAddress < m_nLength)
					memcpy(data    + m_nCurrentAddress + 1, 
							m_pData + m_nCurrentAddress, 
							m_nLength - m_nCurrentAddress);
			}
			m_nCapacity = cap;
			if (m_bDeleteData) 
				delete []m_pData;
			m_pData = data;
		} else {
			// no capacity increase necessary
			if (m_nCurrentAddress < m_nLength)
				memmove(m_pData + m_nCurrentAddress + 1, 
						m_pData + m_nCurrentAddress, 
						m_nLength - m_nCurrentAddress);
		}
		m_pData[m_nCurrentAddress] = 0;
		m_nLength++;
		m_bRecalc = true;
	} else if (m_nCurrentAddress < m_nLength) { // we are overwriting 1 char
		replaceData = m_pData + m_nCurrentAddress;
		replaceLen = 1;
	}
	if (!m_bCaretAscii)
		if (m_bHighBits)
			nValue = (nValue << 4) | (m_pData[m_nCurrentAddress] & 0x0f);
		else
			nValue = (m_pData[m_nCurrentAddress] & 0xf0) | nValue;
	SaveUndoAction(CHexEditAction::input, m_nCurrentAddress, replaceData, replaceLen, &nValue, 1);
	m_pData[m_nCurrentAddress] = nValue;
	if (m_bCaretAscii)
		MoveCurrentAddress(1, true, true);
	else if(m_bHighBits)
		MoveCurrentAddress(0, false, true);
	else
		MoveCurrentAddress(1, true, true);
	Invalidate();
	NotifyParent(HEN_CHANGE);
	return true;
}

LRESULT CHexEditBase::OnUmSetScrollRange(WPARAM, LPARAM)
{
	SetScrollbarRanges();
	return 0;
}

LRESULT CHexEditBase::OnWMSetFont(WPARAM wParam, LPARAM lParam)
{
	if(wParam != NULL) {
		CFont *pFont = CFont::FromHandle((HFONT)wParam);
		if(pFont != NULL) {
			LOGFONT tLogFont;
			memset(&tLogFont, 0, sizeof(LOGFONT));
			if( pFont->GetLogFont(&tLogFont) && ((tLogFont.lfPitchAndFamily & 3) == FIXED_PITCH) ) {
				if((HFONT)m_cFont != NULL) {
					m_cFont.DeleteObject();
					ASSERT((HFONT)m_cFont == NULL);
				}	
				m_cFont.CreateFontIndirect(&tLogFont);
			}
		}
	}
	if((HFONT)m_cFont == NULL) {
		//if we failed so far, we just create a new system font 
		m_cFont.CreateStockObject(SYSTEM_FIXED_FONT);
	}
	m_bRecalc = true;
	if(lParam && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
	return 0; // no return value needed
}

LRESULT CHexEditBase::OnWMGetFont(WPARAM wParam, LPARAM lParam)
{
	wParam = 0;
	lParam = 0;
	return (LRESULT)((HFONT)m_cFont);
}
void CHexEditBase::OnDelete(WPARAM wParam)
{
	if (m_bReadOnly || m_nLength == 0)
		return;
	if (IsSelection()) {
		OnEditCopyCutDelete(true,false);
	} else {
		if (wParam == VK_BACK) {
			if (m_nCurrentAddress == 0)
				return;
			m_nCurrentAddress--;
		}
		if (m_nCurrentAddress == m_nLength)
			return;

		SaveUndoAction(CHexEditAction::cut, m_nCurrentAddress, m_pData + m_nCurrentAddress, 1, 0, 0);

		if (m_nLength - (m_nCurrentAddress + 1) > 0)
			memmove(m_pData + m_nCurrentAddress, m_pData + m_nCurrentAddress + 1, m_nLength - (m_nCurrentAddress + 1));
		m_nLength--;
		MoveCurrentAddress(0, true);
		NotifyParent(HEN_CHANGE);
		Invalidate();
	}
}

LRESULT CHexEditBase::OnWMChar(WPARAM wParam, LPARAM)
{

	if(OnEditInput((WORD)wParam))
		return 0;
	return 1;
}

BOOL CHexEditBase::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) {
		bool bIsShift = (GetKeyState(VK_SHIFT) & 0x80000000) == 0x80000000;
		bool bIsControl = (GetKeyState(VK_CONTROL) & 0x80000000) == 0x80000000;
		bool bIsAlt = (GetKeyState(VK_MENU) & 0x80000000) == 0x80000000;
		WPARAM key = pMsg->wParam;

		if(bIsControl) {
			switch(key) {			
			case 'X': // ctrl + x: cut
				OnEditCut();
				return TRUE;
			case 'C': // ctrl + c: copy
				OnEditCopy();
				return TRUE;
			case 'V': // ctrl + v: paste
				OnEditPaste();
				return TRUE;
			case 'A': // ctrl + a: select all
				OnEditSelectAll();
				return TRUE;
			case VK_HOME:
				MoveCurrentAddress(-0x8000000, true);
				return TRUE;
			case VK_END:
				MoveCurrentAddress(0x7ffffff, true);
				return TRUE;
			}
		} else { // !bIsControl
			if( bIsShift && (m_nSelectingBeg == NOSECTION_VAL) ) {
				// start with selecting
				m_nSelectingBeg = m_nCurrentAddress;
			}
			switch(key) {			
			case VK_DOWN:
				MoveCurrentAddress(m_tPaintDetails.nBytesPerRow, m_bHighBits);
				return TRUE;
			case VK_UP:
				MoveCurrentAddress(-(int)m_tPaintDetails.nBytesPerRow, m_bHighBits);
				return TRUE;
			case VK_RIGHT:
				if (IsSelection()) {
					MoveCurrentAddress(m_nSelectionEnd - m_nCurrentAddress + 1,1);
				} else if (m_bCaretAscii) {
					MoveCurrentAddress(1, true);
				} else if(m_bHighBits) {
					// offset stays the same, caret moves to low-byte
					MoveCurrentAddress(0, false);
				} else {
					MoveCurrentAddress(1, true);
				}
				return TRUE;
			case VK_LEFT:
				if (IsSelection()) {
					MoveCurrentAddress(m_nSelectionBegin - m_nCurrentAddress - 1,m_nSelectionBegin == 0);
				} else if (m_bCaretAscii) {
					MoveCurrentAddress(-1, true);
				} else if(!m_bHighBits) {
					// offset stays the same, caret moves to high-byte
					MoveCurrentAddress(0, true);
				} else {
					MoveCurrentAddress(-1, false);
				}
				return TRUE;
			case VK_PRIOR:
				MoveCurrentAddress(-(int)(m_tPaintDetails.nBytesPerRow*(m_tPaintDetails.nVisibleLines-1)), m_bHighBits);
				return TRUE;
			case VK_NEXT:
				MoveCurrentAddress(m_tPaintDetails.nBytesPerRow*(m_tPaintDetails.nVisibleLines-1), m_bHighBits);
				return TRUE;
			case VK_HOME:
				MoveCurrentAddress(-(int)(m_nCurrentAddress % m_tPaintDetails.nBytesPerRow), true);
				return TRUE;
			case VK_END:
				MoveCurrentAddress(m_tPaintDetails.nBytesPerRow  - 1 - (m_nCurrentAddress % m_tPaintDetails.nBytesPerRow), false);
				return TRUE;
			case VK_INSERT:
				m_bInsert = !m_bInsert;
				SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
				Invalidate();
				return TRUE;
			//case VK_RETURN:
				// not suported yet
				//return TRUE;
			case VK_TAB:
				if (m_bShowAscii && !m_bCaretAscii == !bIsShift) {
					m_bCaretAscii = !m_bCaretAscii;
					SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
					Invalidate();
				} else
					GetParent()->GetNextDlgTabItem(this, bIsShift)->SetFocus();
				return TRUE;
			case VK_DELETE:
			case VK_BACK:
				OnDelete(pMsg->wParam);
				return TRUE;
			}
		}
	}
	return CWnd::PreTranslateMessage(pMsg);
}

void CHexEditBase::SetScrollPositionY(UINT nPosition, bool bUpdate)
{
	if(!(GetStyle() & ES_MULTILINE)) {
		return;
	}
	if(nPosition > m_nScrollRangeY) {
		nPosition = m_nScrollRangeY;
	}
	SetScrollPos(SB_VERT, (int)nPosition, TRUE);
	if( (nPosition != m_nScrollPostionY) && bUpdate && ::IsWindow(m_hWnd) ) {
		m_nScrollPostionY = nPosition;
		Invalidate();
	}
	SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
	m_nScrollPostionY = nPosition;
}

void CHexEditBase::SetScrollPositionX(UINT nPosition, bool bUpdate)
{
	if(nPosition > m_nScrollRangeX) {
		nPosition = m_nScrollRangeX;
	}
	SetScrollPos(SB_HORZ, (int)nPosition, TRUE);
	if((nPosition != m_nScrollPostionX) && bUpdate && ::IsWindow(m_hWnd) ) {
		m_nScrollPostionX = nPosition;
		Invalidate();
		SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
	}
	m_nScrollPostionX = nPosition;
}

void CHexEditBase::MoveCurrentAddress(int iDeltaAdr, bool bHighBits, bool bIgnoreShift)
{
	bool bExtendSelection = !bIgnoreShift && (GetKeyState(VK_SHIFT) & 0x80000000) == 0x80000000;

	if(m_pData == NULL) {
		return;
	}
		
	UINT nAddress = m_nCurrentAddress;

	if(!bExtendSelection) {
		m_nSelectingBeg = NOSECTION_VAL;
		m_nSelectionBegin = NOSECTION_VAL;
		m_nSelectingEnd = NOSECTION_VAL;
		m_nSelectionEnd = NOSECTION_VAL;
	}
	if(iDeltaAdr > 0) {
		// go down
		if(nAddress + iDeltaAdr >= GetDataSize1()) {
			// we reached the end
			nAddress = GetDataSize1() - 1;
			bHighBits = false;
		} else {
			nAddress += iDeltaAdr;
		}
	} else if (iDeltaAdr < 0) {
		if((UINT)(-iDeltaAdr) <= nAddress) {
			nAddress -= (UINT)(-iDeltaAdr);
		} else {
			nAddress = 0;
			bHighBits = true;
		}
	} 
	if(bExtendSelection && (m_nSelectingBeg != NOSECTION_VAL)) {
		m_nSelectingEnd = nAddress;
		m_nSelectionBegin = m_nSelectingBeg;
		m_nSelectionEnd = m_nSelectingEnd;
		NORMALIZE_SELECTION(m_nSelectionBegin, m_nSelectionEnd);
	}
	MakeVisible(nAddress, nAddress, true);
	SetEditCaretPos(nAddress, bHighBits);
}

void CHexEditBase::OnKeyDown(UINT nChar, UINT, UINT) 
{
}

void CHexEditBase::OnContextMenu(CWnd*, CPoint cPoint)
{	
	CString cString;

	if( (cPoint.x == -1) && (cPoint.y == -1) ) {
		//keystroke invocation
		cPoint = CPoint(5, 5);
		ClientToScreen(&cPoint);
	} else {
		CPoint cRelPoint(cPoint);
		ScreenToClient(&cRelPoint);
		bool bHigh;
		UINT nAdr;
		GetAddressFromPoint(cRelPoint, nAdr, bHigh);
		if( !IsSelection() || (nAdr < m_nSelectionBegin) || (nAdr > m_nSelectionEnd) ) {
			// no selection or outside of selection
			if(IsSelection()) {
				// kill selection
				SetSelection(NOSECTION_VAL, NOSECTION_VAL, false, true);
			}
			SetEditCaretPos(nAdr, true); //always high, because of paste...
		}
	}

	CMenu cMenu;
	if(!cMenu.CreatePopupMenu()) {
		TRACE("CHexEditBase::OnContextMenu: ERROR: couldn't create PopupMenue\n");
		return;
	}

	// menue-item: cut
	cMenu.AppendMenu(IsSelection() ? MF_STRING : MF_GRAYED|MF_DISABLED|MF_STRING, ID_EDIT_CUT, (LPCSTR)m_cContextCut);
	
	// menue-item: copy
	cMenu.AppendMenu(IsSelection() ? MF_STRING : MF_GRAYED|MF_DISABLED|MF_STRING, ID_EDIT_COPY, (LPCSTR)m_cContextCopy);
	
	// menue-item: paste
	COleDataObject cSource;
	cSource.AttachClipboard();
	bool clipboardDataAvailable = 
		cSource.IsDataAvailable(CF_TEXT) ||
		cSource.IsDataAvailable(m_nBinDataClipboardFormat);
	cMenu.AppendMenu(clipboardDataAvailable && !m_bReadOnly ? MF_STRING : MF_GRAYED|MF_DISABLED|MF_STRING, 
		ID_EDIT_PASTE, (LPCSTR)m_cContextPaste);

	// menu item: show as text
	cMenu.AppendMenu(MF_STRING, ID_TOTXT, (LPCSTR)m_cContextToTxt);

	cSource.Release();
	OnExtendContextMenu(cMenu);
	cMenu.TrackPopupMenu(TPM_LEFTALIGN, cPoint.x, cPoint.y, this, CRect(0,0,100,100));
}

void CHexEditBase::OnEditCopy() 
{
	OnEditCopyCutDelete(false,true);
}

void CHexEditBase::OnEditCut() 
{
	OnEditCopyCutDelete(true,true);
}

static UINT hexEncodeLength(UINT nLength, UINT nBytesPerRow)
{
	UINT lines = (nLength + nBytesPerRow - 1) / nBytesPerRow; // rounded up
	return
		3 * nLength - 1 +	// 2 hex digits + ' ' *between* the bytes
		lines - 1 +		// *between* lines insert \r\n replacing ' '
		1;					// \0
}
static void hexEncode(BYTE *pDest, UINT nDestLength, BYTE *pData, UINT nDataLength, UINT nBytesPerRow)
{
	BYTE *pDataEnd = pData + nDataLength - 1;
	UINT ascii = 0; // index into pDest
	UINT col = 0; // current column
	while( pData <= pDataEnd ) {
		if (col >= nBytesPerRow) {
			col = 0;
			ASSERT(ascii + 2 <= nDestLength);
			pDest[ascii++] = '\r';
			pDest[ascii++] = '\n';
		} else if (ascii > 0) {
			ASSERT(ascii + 1 <= nDestLength);
			pDest[ascii++] = ' ';
		}
		ASSERT(ascii + 2 <= nDestLength);
		pDest[ascii++] = tabHexCharacters[*pData >> 4];
		pDest[ascii++] = tabHexCharacters[*pData & 0xf];
		pData++;
		col++;
	}
	ASSERT(ascii + 1 == nDestLength);
	pDest[ascii++] = '\0';
}

void CHexEditBase::OnEditCopyCutDelete(bool cutdel,bool clipboard) 
{
	if( (m_nSelectionBegin == NOSECTION_VAL) || (m_nSelectionEnd == NOSECTION_VAL) )
		return;
	if (m_nLength == 0 || m_nSelectionBegin >= m_nLength)
		return;
	if (m_bReadOnly && cutdel)
		return;
	ASSERT(m_nSelectionEnd >= m_nSelectionBegin);
	ASSERT(m_nSelectionEnd <= m_nLength);

	UINT nLength = m_nSelectionEnd - m_nSelectionBegin + 1;
	if (m_nSelectionEnd == m_nLength)
		nLength--;

	if (clipboard) {
		int encoding = CSelectCopyEncoding::selectCopyEncoding();
		if (encoding < 0)
			return;
		bool doHexEncode = (encoding == ENCODING_HEX);
		HGLOBAL hMem = NULL;
		CLIPFORMAT clipformat = 0;
		try {
			if (doHexEncode) {
				// copy ascii
				clipformat = CF_TEXT;
				UINT asciiLength = hexEncodeLength(nLength, m_tPaintDetails.nBytesPerRow);
				hMem = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, asciiLength);
				if(hMem == NULL)
					throw 0;
				BYTE *pPtr = (BYTE*)::GlobalLock(hMem);
				hexEncode(pPtr, asciiLength, m_pData + m_nSelectionBegin, nLength, m_tPaintDetails.nBytesPerRow);
				::GlobalUnlock(hMem);
			} else {
				// copy binary
				UINT cliplength;
				int contains0 = (NULL != memchr(m_pData+m_nSelectionBegin,'\0',nLength));
				if (contains0) {
					clipformat = (CLIPFORMAT)m_nBinDataClipboardFormat;
					cliplength = sizeof(UINT) + nLength;
				} else {
					clipformat = CF_TEXT;
					cliplength = nLength + 1;
				}
				hMem = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, cliplength);
				if(hMem == NULL)
					throw 1;
				BYTE *pBinData = (BYTE*)::GlobalLock(hMem);
				if (contains0) {
					*(UINT*)pBinData = nLength;
					memcpy(pBinData + sizeof(UINT), m_pData+m_nSelectionBegin, nLength);
				} else {
					memcpy(pBinData,m_pData+m_nSelectionBegin, nLength);
					pBinData[nLength] = '\0';
				}
				::GlobalUnlock(hMem);
			}

			if ( !OpenClipboard() )
				throw 2;
			// Remove the current Clipboard contents  
			if( !EmptyClipboard() )
			{
				CloseClipboard();
				throw 3;  
			}
			if (SetClipboardData(clipformat, hMem) == 0) {
				CloseClipboard();
				throw 4;
			}
			hMem = NULL;
			CloseClipboard();
		} 
		catch(...) 
		{
			if (hMem != NULL)
				GlobalFree(hMem);
			AfxMessageBox(IDS_CLIPBORD_COPY_ERROR,MB_ICONEXCLAMATION);
			return;
		}
	} // if (selection)
	if (cutdel)
		SaveUndoAction(CHexEditAction::cut, m_nSelectionBegin, m_pData + m_nSelectionBegin, nLength, 0, 0);

	if (cutdel && m_nSelectionBegin + nLength < m_nLength) {
		memmove(m_pData + m_nSelectionBegin, 
				m_pData + m_nSelectionBegin + nLength,
				m_nLength - (m_nSelectionBegin + nLength));
	}
	if (cutdel && nLength != 0) {
		m_nLength -= nLength;
		m_bRecalc = true;
		SetEditCaretPos(m_nSelectionBegin,true);
		m_nSelectingBeg = NOSECTION_VAL;
		m_nSelectionBegin = NOSECTION_VAL;
		m_nSelectingEnd = NOSECTION_VAL;
		m_nSelectionEnd = NOSECTION_VAL;
		NotifyParent(HEN_CHANGE);
		Invalidate();
	}
}

static bool isHexSeparator(BYTE b) 
{
	switch (b) {
	case '\t':
	case '\r':
	case '\n':
	case ':':
	case ' ':
		return true;
	default:
		return false;
	}
}

// returns # of hex digits, skipping white space or -1 if other chars are found
static UINT countHexDigits(const BYTE *data, UINT ndata)
{
	UINT n = 0;
	while (ndata > 0) {
		if (isxdigit(*data))
			n++;
		else if ((n & 1) == 0 && isHexSeparator(*data))
			; // skip white space etc between bytes
		else
			return -1;
		data++;
		ndata--;
	}
	return n;
}

#define hex2int(ascii) ( \
	('0' <= (ascii) && (ascii) <= '9') ? (ascii) - '0' : \
	('A' <= (ascii) && (ascii) <= 'F') ? (ascii) - 'A' + 10 : \
	('a' <= (ascii) && (ascii) <= 'f') ? (ascii) - 'a' + 10 : \
	-1 )

// decode hex digits from source to target, not writing more than ntarget bytes; 
// white space between bytes are ignored, decoding is terminated when an unexpected char is encountered
// returns number of bytes written (negative if an error has occured)
static INT hexDecode(BYTE *target, const BYTE *source, UINT ntarget)
{
	INT hexdigits = 0;
	BYTE highnibble = 0;
	while (ntarget > 0 && *source) {
		if (hexdigits & 1) { // expecting low nibble
			if (!isxdigit(*source)) 
				return -(hexdigits/2);
			BYTE lownibble = hex2int(*source);
			ASSERT(lownibble != 0xFF);
			*(target++) = (highnibble << 4) | lownibble;
			ntarget--;
			hexdigits++;
		} else { // expecting high nibble or white space etc.
			if (isxdigit(*source)) {
				highnibble = hex2int(*source);
				ASSERT(highnibble != 0xFF);
				hexdigits++;
			} else if (!isHexSeparator(*source))
				return -(hexdigits/2);
		}
		source++;
	}
	return hexdigits/2;
}

void CHexEditBase::OnEditPaste() 
{

	if(m_bReadOnly)
		return;
	
	COleDataObject cSource;
	BYTE *pSource = NULL; // don't free
	UINT nSourceByteLength = 0;

	if(!cSource.AttachClipboard()) {
		TRACE("CHexEditBase::OnEditPaste: ERROR: AttachClipboard failed\n");
		return;
	}
	UINT nPasteAdr = m_nCurrentAddress;
	UINT nReplaceLength = 0;
	if(IsSelection()) {
		nPasteAdr = m_nSelectionBegin;
		nReplaceLength = m_nSelectionEnd - m_nSelectionBegin + 1;
		if (m_nSelectionEnd >= m_nLength)
			nReplaceLength--;
	}

	CLIPFORMAT cformat = (CLIPFORMAT)m_nBinDataClipboardFormat;
	if(!cSource.IsDataAvailable(cformat))
		cformat = CF_TEXT;
	if(!cSource.IsDataAvailable(cformat))
		return;
	HGLOBAL hClipData = cSource.GetGlobalData(cformat);
	if(hClipData == NULL) {
		TRACE("CHexEditBase::OnEditPaste: ERROR: GetGlobalData failed\n");
		return;
	}
	void *pClipData = (UINT*)::GlobalLock(hClipData);
	
	if (cformat == CF_TEXT) {
		pSource = (BYTE*)pClipData;
		nSourceByteLength = strlen((char*)pSource);
	} else {
		pSource = (BYTE*)pClipData + sizeof(UINT);
		nSourceByteLength = *(UINT*)pClipData;
	}
	if (nSourceByteLength == 0) {
		::GlobalUnlock(hClipData);
		return;
	}

	bool doHexdecode = false;
	int nHexDigits = countHexDigits(pSource,nSourceByteLength); // < 0 or odd if non valid hex encoding
	if (nHexDigits > 0 && nHexDigits % 2 == 0) {
		int decoding = CSelectPasteDecoding::selectPasteDecoding();
		if (decoding < 0)
			return;
		if ( 1 == decoding )
		{
		// if (IDYES == AfxMessageBox(IDS_CLIPBOARD_HEXPASTE, MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)) {
			doHexdecode = true;
			nSourceByteLength = nHexDigits / 2;
		}
	}
	
	if (SaveUndoAction(CHexEditAction::paste, nPasteAdr, m_pData+nPasteAdr, nReplaceLength, pSource, nSourceByteLength) && 
		doHexdecode && nSourceByteLength > 0) // nSourceByteLength should be > 0, but the test cannot hurt
		hexDecode(m_undo->getInsertData(), pSource, nSourceByteLength);

	if (!PrepareReplace(nPasteAdr, nReplaceLength, nSourceByteLength)) {
		::GlobalUnlock(hClipData);
		return;
	}
	if (doHexdecode)
		hexDecode(m_pData+nPasteAdr, pSource, nSourceByteLength);
	else
		memcpy(m_pData+nPasteAdr, pSource, nSourceByteLength);
	::GlobalUnlock(hClipData);
}

// Prepare replacing [pos, pos+oldlen] with new content of newlen bytes
// Allocates new storage if required and returns false if that fails
// Does not copy the new content, only makes (ininitialized) room for it
bool CHexEditBase::PrepareReplace(UINT pos, UINT oldlen, UINT newlen) 
{
	UINT nTargetLength = m_nLength - oldlen + newlen;
	BYTE * pTarget = m_pData;
	if (nTargetLength > m_nCapacity) {
		pTarget = new BYTE[nTargetLength];
		if (!pTarget) 
			return false;
		if (pos > 0) 
			memcpy(pTarget, m_pData, pos); // data before selection
	}
	if (m_nLength - (pos + oldlen) > 0)
		memmove(pTarget  + pos + newlen, 
				m_pData  + pos + oldlen, 
				m_nLength - (pos + oldlen)); // move data behind paste area to target position
	if (pTarget != m_pData) {
		if (m_bDeleteData)
			delete []m_pData;
		m_pData = pTarget;
		m_bDeleteData = true;
		m_nCapacity = nTargetLength;
	}
	if (m_nLength != nTargetLength) {
		m_bRecalc = true;
		m_nLength = nTargetLength;
	}
	//m_bRecalc = true;
	MakeVisible(pos+newlen, pos+newlen, true);
	SetSelection(NOSECTION_VAL, NOSECTION_VAL, true, false);
	SetEditCaretPos(pos+newlen, true);
	NotifyParent(HEN_CHANGE);
	Invalidate();
	return true;
}

void CHexEditBase::OnEditClear() 
{
	OnDelete(VK_DELETE);
}
void CHexEditBase::OnEditSelectAll() 
{
	if(m_nLength > 0) {
		SetSelection(0, m_nLength-1, false, true);
	}
}

void CHexEditBase::OnToTxt()
{
	// tell the view to switch to text mode
	if(view)
		view->showAsText();
}

void CHexEditBase::ReInitialize()
{
	m_nSelectingBeg = NOSECTION_VAL;
	m_nSelectingEnd = NOSECTION_VAL;
	m_nSelectionBegin = NOSECTION_VAL;
	m_nSelectionEnd = NOSECTION_VAL;
	m_nHighlightedBegin = NOSECTION_VAL;
	m_nHighlightedEnd = NOSECTION_VAL;
	if(m_bDeleteData) {
		delete []m_pData;
	}
	m_bDeleteData = false;
	m_bRecalc = true;
	delete m_undo;
	delete m_redo;
	m_undo = 0;
	m_redo = 0;
}

bool CHexEditBase::Allocate(UINT nLen)
{
	ASSERT(nLen < MAXHEXEDITLENGTH); // about what we can manage without overflow
	ASSERT(m_pData == NULL); // call ReInitialize before Allocate
	if (nLen)
		m_pData = new BYTE[nLen];
	m_nLength = m_nCapacity = m_pData ? nLen : 0;
	m_bDeleteData = true;
	return m_pData != NULL;
}

void CHexEditBase::SetData(const BYTE *pData, UINT nLen, bool bUpdate)
{
	ASSERT(pData != NULL || nLen == 0);
	ASSERT(nLen > 0 || pData == NULL);

	ReInitialize();
	if (Allocate(nLen)) {
		if(pData != NULL)
			memcpy(m_pData, pData, nLen);
	} else { // Allocate failed
		m_nLength = 0;
		m_nCapacity = 0;
		// TODO inform user
	}
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
	SetEditCaretPos(0, true);
}

void CHexEditBase::SetDirectDataPtr(BYTE *pData, UINT nLen, bool bUpdate)
{
	ASSERT(pData != NULL || nLen == 0);
	ASSERT(nLen > 0 || pData == NULL);

	ReInitialize();
	m_nLength = nLen;
	m_pData = pData;

	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
	SetEditCaretPos(0, true);
}

UINT CHexEditBase::GetData(BYTE *pByte, UINT nLength)
{
    if(m_pData != NULL) {
		memcpy(pByte, m_pData, min(nLength, m_nLength));
		return m_nLength;
	} else {
		return 0;
	}
}
UINT CHexEditBase::GetCurrentAddress() const {
	return m_nCurrentAddress;
}
UINT CHexEditBase::GetBytesPerRow() const {
	return m_tPaintDetails.nBytesPerRow;
}

void CHexEditBase::Serialize(CArchive& ar)
{
	CFile *pFile = ar.GetFile();
	ASSERT(pFile != NULL);

	if (ar.IsStoring()) {
		pFile->Write(m_pData, m_nLength);
	} else {
		ReInitialize();
		if (Allocate((UINT)ar.GetFile()->GetLength())) {
			ASSERT(m_nLength < MAXHEXEDITLENGTH);
			pFile->Read(m_pData, m_nLength);
		} else { // Alllocate failed
			m_nLength = 0;
			// TODO inform user
		}
		if(::IsWindow(m_hWnd))
			Invalidate();
		SetEditCaretPos(0, true);
	}
}

bool CHexEditBase::IsSelection() const 
{
	return (m_nSelectionEnd != NOSECTION_VAL) && (m_nSelectionBegin != NOSECTION_VAL);
}

bool CHexEditBase::IsHighlighted() const
{
	return (m_nHighlightedEnd != NOSECTION_VAL) && (m_nHighlightedBegin != NOSECTION_VAL);
}

bool CHexEditBase::IsInsert() const
{
	return m_bInsert;
}


bool CHexEditBase::GetSelection(UINT& nBegin, UINT& nEnd) const
{
	if(IsSelection()) {
		nBegin = m_nSelectionBegin;
		nEnd = m_nSelectionEnd;
		return true;
	}
	nBegin = NOSECTION_VAL;
	nEnd = NOSECTION_VAL;
	return false;
}

bool CHexEditBase::GetHighlighted(UINT& nBegin, UINT& nEnd) const
{
	if(IsHighlighted()) {
		nBegin = m_nHighlightedBegin;
		nEnd = m_nHighlightedEnd;
		return true;
	}
	nBegin = NOSECTION_VAL;
	nEnd = NOSECTION_VAL;
	return false;
}

void CHexEditBase::SetBytesPerRow(UINT nBytesPerRow, bool bAuto, bool bUpdate)
{
	if( (m_bAutoBytesPerRow != bAuto) || (m_nBytesPerRow != nBytesPerRow) ) {
		m_bAutoBytesPerRow = bAuto;
		m_nBytesPerRow = nBytesPerRow;
		m_bRecalc = true;				
		if(::IsWindow(m_hWnd)) {
			SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
			if(bUpdate) {
				Invalidate();
			}
		}
	}
}

void CHexEditBase::SetShowAddress(bool bShow, bool bUpdate)
{
	if(m_bShowAddress != bShow) {
		m_bShowAddress = bShow;
		m_bRecalc = true;
		if(::IsWindow(m_hWnd)) {
			SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
			if(bUpdate) {
				Invalidate();
			}
		}
	}
}

void CHexEditBase::SetShowAscii(bool bShow, bool bUpdate)
{
	if(m_bShowAscii != bShow) {
		m_bShowAscii = bShow;
		m_bRecalc = true;
		if(::IsWindow(m_hWnd)) {
			SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
			if(bUpdate) {
				Invalidate();
			}
		}
	}
}

void CHexEditBase::SetSelection(UINT nBegin, UINT nEnd, bool bMakeVisible, bool bUpdate)
{
	ASSERT(m_nLength > 0);
	ASSERT( (nEnd < m_nLength) || (nEnd == NOSECTION_VAL) );
	ASSERT( (nBegin < m_nLength) || (nBegin == NOSECTION_VAL) );
	
	if( (m_nSelectionEnd != nEnd) || (m_nSelectionBegin != nBegin) ) {
		if( (nEnd >= m_nLength) && (nEnd != NOSECTION_VAL) ) {
			nEnd = m_nLength-1;
		}
		if( (nBegin >= m_nLength) && (nBegin != NOSECTION_VAL) ) {
			nBegin = m_nLength-1;
		}
		m_nSelectionEnd = nEnd;
		m_nSelectionBegin = nBegin;
		if(bMakeVisible && nEnd != NOSECTION_VAL && nBegin != NOSECTION_VAL) {
			MakeVisible(m_nSelectionBegin, m_nSelectionEnd, false);
		}
		if(bUpdate && ::IsWindow(m_hWnd)) {
			Invalidate();
		}
	}
}

void CHexEditBase::SetHighlighted(UINT nBegin, UINT nEnd, bool bMakeVisible, bool bUpdate)
{
	ASSERT(m_nLength > 0);

	if( (m_nHighlightedEnd != nEnd) || (m_nHighlightedBegin != nBegin) ) {		
		if( (nEnd >= m_nLength) && (nEnd != NOSECTION_VAL) ) {
			nEnd = m_nLength-1;
		}
		if( (nBegin >= m_nLength) && (nBegin != NOSECTION_VAL) ) {
			nBegin = m_nLength-1;
		}
		m_nHighlightedBegin = nBegin;
		m_nHighlightedEnd = nEnd;
		if(bMakeVisible) {
			MakeVisible(m_nHighlightedBegin, m_nHighlightedEnd, false);
		}
		if(bUpdate && ::IsWindow(m_hWnd)) {
			Invalidate();
		}
	}
}

void CHexEditBase::SetReadonly(bool bReadOnly, bool bUpdate)
{
	m_bReadOnly = bReadOnly;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetAddressSize(BYTE nAdrSize, bool bUpdate)
{
	m_nAdrSize = nAdrSize;
	m_bRecalc = true;
	if(::IsWindow(m_hWnd)) {
		SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
		if(bUpdate) {
			Invalidate();
		}
	}
}

void CHexEditBase::SetAdrCol(COLORREF tAdrBkgCol, COLORREF tAdrTxtCol, bool bUpdate)
{
	m_tAdrBkgCol = tAdrBkgCol;
	m_tAdrTxtCol = tAdrTxtCol;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetAsciiCol(COLORREF tAsciiBkgCol, COLORREF tAsciiTxtCol, bool bUpdate)
{
	m_tAsciiBkgCol = tAsciiBkgCol;
	m_tAsciiTxtCol = tAsciiTxtCol;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetHighlightCol(COLORREF tHighlightFrameCol, COLORREF tHighlightBkgCol, COLORREF tHighlightTxtCol, bool bUpdate)
{
	m_tHighlightFrameCol = tHighlightFrameCol;
	m_tHighlightBkgCol = tHighlightBkgCol;
	m_tHighlightTxtCol = tHighlightTxtCol;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetHexCol(COLORREF tHexBkgCol, COLORREF tHexTxtCol, bool bUpdate)
{
	m_tHexBkgCol = tHexBkgCol;
	m_tHexTxtCol = tHexTxtCol;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetSelectedNoFocusCol(COLORREF tSelectedNoFocusBkgCol, COLORREF tSelectedNoFocusTxtCol, bool bUpdate)
{
	m_tSelectedNoFocusBkgCol = tSelectedNoFocusBkgCol;
	m_tSelectedNoFocusTxtCol = tSelectedNoFocusTxtCol;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetSelectedFocusCol(COLORREF tSelectedFousTxtCol, COLORREF tSelectedFousBkgCol, bool bUpdate)
{
	m_tSelectedFousTxtCol = tSelectedFousTxtCol;
	m_tSelectedFousBkgCol = tSelectedFousBkgCol;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

void CHexEditBase::SetNotUsedCol(COLORREF tNotUsedBkCol, bool bUpdate)
{
	m_tNotUsedBkCol = tNotUsedBkCol;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
}

LPCSTR memfind(LPCSTR pattern, size_t patternlength, LPCSTR text, size_t textlength) {
	if (patternlength > textlength)
		return NULL;
	LPCSTR searchend = text + textlength - patternlength;
	while (text <= searchend) {
		if (0 == memcmp(pattern, text, patternlength))
			return text;
		text++;
	}
	return NULL;
}

LPCSTR memifind(LPCSTR pattern, size_t patternlength, LPCSTR text, size_t textlength) {
	if (patternlength > textlength)
		return NULL;
	LPCSTR searchend = text + textlength - patternlength;
	while (text <= searchend) {
		if (0 == _memicmp(pattern, text, patternlength))
			return text;
		text++;
	}
	return NULL;
}

LPCSTR memrfind(LPCSTR pattern, size_t patternlength, LPCSTR text, size_t textlength) {
	if (patternlength > textlength)
		return NULL;
	LPCSTR searchpos = text + textlength - patternlength;
	while (text <= searchpos) {
		if (0 == memcmp(pattern, searchpos, patternlength))
			return searchpos;
		searchpos--;
	}
	return NULL;
}

LPCSTR memirfind(LPCSTR pattern, size_t patternlength, LPCSTR text, size_t textlength) {
	if (patternlength > textlength)
		return NULL;
	LPCSTR searchpos = text + textlength - patternlength;
	while (text <= searchpos) {
		if (0 == _memicmp(pattern, searchpos, patternlength))
			return searchpos;
		searchpos--;
	}
	return NULL;
}


bool CHexEditBase::Search(LPCSTR pattern, size_t length, UINT flags)
{
	bool matchcase = (flags & HE_FIND_MATCHCASE) != 0;
	bool findbackwards = (flags & HE_FIND_BACKWARDS) != 0;
	UINT i;
	if (IsSelection()) {
		UINT dummy;
		GetSelection(i,dummy);
		if ((flags & HE_FIND_NOSKIP) == 0) // skip the first char of a selection (to enable repeated search) unless HE_FIND_NOSKIP
			if (findbackwards)
				i = (i == 0) ? 0 : i - 1;
			else
				i++; 
	} else
		i = m_nCurrentAddress;
	LPCSTR text = (LPCSTR)m_pData;
	LPCSTR found = NULL;
	if (i >= m_nLength)
		i = m_nLength;
	if (findbackwards)
		if (matchcase)
			found = memrfind(pattern, length, text, min(i + length, m_nLength));
		else
			found = memirfind(pattern, length, text, min(i + length, m_nLength));
	else
		if (matchcase)
			found = memfind(pattern, length, text + i, m_nLength - i);
		else
			found = memifind(pattern, length, text + i, m_nLength - i);
	if (found == NULL)
		return false;
	UINT foundAddress = found - text;
	SetSelection(foundAddress, length == 0 ? foundAddress : foundAddress + length - 1);
	return true;
}

bool CHexEditBase::ReplaceSelection(LPCSTR data, size_t length)
{
	if (!IsSelection())
		return false;
	UINT start, end;
	GetSelection(start, end);

	SaveUndoAction(CHexEditAction::paste, start, m_pData + start, end - start + 1, (const BYTE*)data, length);

	if (!PrepareReplace(start, end - start + 1, length))
		return false;
	if (length > 0)
		memcpy(m_pData + start, data, length);
	return true;
}

int CHexEditBase::ReplaceAll(LPCSTR pfind, size_t findlen, LPCSTR preplace, size_t replacelen, UINT searchflags)
{
	int count = 0;
	while (Search(pfind, findlen, searchflags)) {
		if (!ReplaceSelection(preplace, replacelen))
			break;
		count++;
	}
	return count;
}

BOOL CHexEditBase::SaveUndoAction(UINT type, UINT position, const BYTE* replaceData, UINT replaceLen, const BYTE* insertData, UINT insertLen)
{
	delete m_redo; // m_pData will change invalidating m_redo
	m_redo = 0;
	if (type == CHexEditAction::input && m_undo != 0 && m_undo->getType() == CHexEditAction::input &&
		m_undo->getPosition() + m_undo->getInsertLen() == position) {
			// merge input actions
			if (!m_undo->append(replaceData, replaceLen, insertData, insertLen)) {
				AfxMessageBox(IDS_CANT_SAVE_UNDO, MB_ICONEXCLAMATION);
				return FALSE;
			}
	} else {
		// new action can't be merged with previous
		CHexEditAction* action = new CHexEditAction();
		if (action == 0 || 
			!action->set(CHexEditAction::input, position, replaceData, replaceLen, insertData, insertLen, m_undo)) {
			delete action;
			AfxMessageBox(IDS_CANT_SAVE_UNDO, MB_ICONEXCLAMATION);
			return FALSE;
		}
		m_undo = action;
	}
	return TRUE;
}

void CHexEditBase::Undo()
{
	if (!CanUndo())
		return;

	CHexEditAction* action = m_undo;
	// ASSERT: the data inserted (if any) in the current undo action is still there
	ASSERT(action->getInsertLen() == 0 || 
		memcmp(m_pData + action->getPosition(), action->getInsertData(), action->getInsertLen()) == 0);

	// replace insertData/insertLen at position with replaceData/replaceLen
	if (!PrepareReplace(action->getPosition(), action->getInsertLen(), action->getReplaceLen())) {
		AfxMessageBox(IDS_CANT_UNDO, MB_ICONEXCLAMATION);
		return;
	}
	if (action->getReplaceLen() > 0)
		memcpy(m_pData + action->getPosition(), action->getReplaceData(), action->getReplaceLen());

	// move head of m_undo to m_redo
	m_undo = action->getNext();
	action->setNext(m_redo);
	m_redo = action;
}

void CHexEditBase::Redo()
{
	if (!CanRedo())
		return;
	
	CHexEditAction* action = m_redo;
	// ASSERT: the data to be replace(if any) in the current redo action is still there
	ASSERT(action->getReplaceLen() == 0 || 
		memcmp(m_pData + action->getPosition(), action->getReplaceData(), action->getReplaceLen()) == 0);
	
	// replace replaceData/replaceLen at position with insertData/insertLen
	if (!PrepareReplace(action->getPosition(), action->getReplaceLen(), action->getInsertLen())) {
		AfxMessageBox(IDS_CANT_REDO, MB_ICONEXCLAMATION);
		return;
	}
	if (action->getInsertLen() > 0)
		memcpy(m_pData + action->getPosition(), action->getInsertData(), action->getInsertLen());

	// move head of m_redo to m_undo
	m_redo = action->getNext();
	action->setNext(m_undo);
	m_undo = action;
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// class CHexEditBaseView
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CHexEditBaseView, CCrypToolView)

BEGIN_MESSAGE_MAP(CHexEditBaseView, CCrypToolView)
	//{{AFX_MSG_MAP(CHexEditBaseView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CHexEditBaseView::CHexEditBaseView() : CCrypToolView() 
{ 
}

CHexEditBaseView::~CHexEditBaseView()
{
}

int CHexEditBaseView::OnCreate(LPCREATESTRUCT pCreateStruc)
{
	if(CView::OnCreate(pCreateStruc) != 0) {
		return -1;
	}
	if(!m_cHexEdit.Create(NULL, WS_CHILD|WS_VISIBLE|ES_MULTILINE, CRect(0, 0, pCreateStruc->cx, pCreateStruc->cy), 
		this, IDC_HEXEDITBASEVIEW_HEXCONTROL, NULL)) {
		return -1;
	}	

	// initialize hex edit base with this view
	m_cHexEdit.setView(this);

	return 0;
}

void CHexEditBaseView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if(::IsWindow(m_hWnd)) {
		m_cHexEdit.MoveWindow(0, 0, cx, cy, TRUE);
	}
}

void CHexEditBaseView::OnDraw(CDC*)
{ // do nothing
}

BOOL CHexEditBaseView::OnEraseBkgnd(CDC*)
{ // don't erase background: avoids flickering
	return TRUE;
}

//DEL BOOL CHexEditBaseView::OnCommand( WPARAM wParam, LPARAM lParam )
//DEL {
//DEL     if (HIWORD(wParam)==HEN_CHANGE)
//DEL     {
//DEL         this->GetDocument()->SetModifiedFlag();
//DEL     }
//DEL     return CWnd::OnCommand( wParam, lParam );
//DEL }