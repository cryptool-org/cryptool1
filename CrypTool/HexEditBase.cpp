/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/

// This file was originally written by Christian Kuendig. It was 
// obtained from www.codeguru.com in May 2005 and modified as necessary.


/////////////////////////////////////////////////////////////////////////////
// includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <memory>
#include <afxole.h>
#include "HexEditBase.h"
//#include "resource.h"
#include "stdafx.h"


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
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CHexEditBase::CHexEditBase() :
	m_bSelfCleanup(false),
	m_bDeleteData(true),
	m_pData(NULL), 
	m_nLength(0), 
	m_nAdrSize(8), 
	m_nBytesPerRow(16), 
	m_nCurCaretWidth(0),
	m_nCurCaretHeight(0), 
	m_bHasCaret(false), 
	m_bHighBits(true),
	m_bReadOnly(false), 
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
	m_cContextCopy("Copy"),
	m_cContextPaste("Paste")

{
	memset(&m_tPaintDetails, 0, sizeof(PAINTINGDETAILS));
	m_tSelectedNoFocusTxtCol = GetSysColor(COLOR_WINDOWTEXT);
	m_tSelectedNoFocusBkgCol = GetSysColor(COLOR_BTNFACE);
	m_tSelectedFousTxtCol = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_tSelectedFousBkgCol = GetSysColor(COLOR_HIGHLIGHT);
	if(!m_cFont.CreateStockObject(ANSI_FIXED_FONT)) {
		AfxThrowResourceException();
	}
	
	// register clipboard format
	m_nBinDataClipboardFormat = RegisterClipboardFormat(CF_BINDATA_HEXCTRL);
	ASSERT(m_nBinDataClipboardFormat != 0);

	// try to load strings from the resources
#ifdef IDS_CONTROL_COPY
	if(!m_cContextCopy.LoadString(IDS_CONTROL_COPY)) {
		cString = _T("Copy");
	}
#endif
#ifdef IDS_CONTROL_PASTE
	if(!m_cContextPaste.LoadString(IDS_CONTROL_PASTE)) {
		cString = _T("Paste");
	}
#endif

	// register windows-class
	RegisterClass();
}

CHexEditBase::~CHexEditBase()
{
	if(m_bDeleteData) {
		delete []m_pData;
	}
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
		m_tPaintDetails.nBytesPerRow = m_nLength;
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
	nTotalLines = (m_nLength + m_tPaintDetails.nBytesPerRow-1)/m_tPaintDetails.nBytesPerRow;
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

	if((m_nLength < 1) || (m_pData == NULL)) {
		return;
	}

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
	if(nEndAdr >= m_nLength) {
		nEndAdr = m_nLength-1;
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
	ASSERT(m_nLength < 0x7ffff000); // to make sure we don't have an overflow
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
	if(nEndAdr >= m_nLength) {
		nEndAdr = m_nLength-1;
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
	
	memset(pBuf, '\0', m_tPaintDetails.nBytesPerRow+1);

	// the Rect for painting & background
	cBkgBrush.CreateSolidBrush(m_tAsciiBkgCol);
	cAsciiRect.left += m_tPaintDetails.nAsciiPos - m_nScrollPostionX;
	cAsciiRect.right = cAsciiRect.left + m_tPaintDetails.nAsciiLen;
	cDC.FillRect(cAsciiRect, &cBkgBrush);
	cAsciiRect.bottom = cAsciiRect.top + m_tPaintDetails.nLineHeight;

	// start & end-address
	nAdr = m_nScrollPostionY * m_tPaintDetails.nBytesPerRow;
	nEndAdr = nAdr + m_tPaintDetails.nVisibleLines*m_tPaintDetails.nBytesPerRow;
	if(nEndAdr >= m_nLength) {
		nEndAdr = m_nLength-1;
	}
	pDataPtr = m_pData + nAdr;

	//  paint
	cDC.SetBkMode(OPAQUE);
	cDC.SetTextColor(m_tAsciiTxtCol);
	cDC.SetBkColor(m_tAsciiBkgCol);
	for(; nAdr<=nEndAdr; nAdr+=m_tPaintDetails.nBytesPerRow) {
		pDataPtrEnd = pDataPtr + m_tPaintDetails.nBytesPerRow;
		if(pDataPtrEnd > m_pData + nEndAdr) {
			pDataPtrEnd = m_pData + nEndAdr+1;
		}
		for(pBufPtr=pBuf; pDataPtr<pDataPtrEnd; ++pDataPtr, ++pBufPtr) {
			*pBufPtr = isprint(*pDataPtr) ? (char)*pDataPtr : '.';
		}
		*pBufPtr = '\0';
		cDC.DrawText(pBuf, (LPRECT)cAsciiRect, DT_LEFT|DT_TOP|DT_SINGLELINE|DT_NOPREFIX);
		cAsciiRect.OffsetRect(0, m_tPaintDetails.nLineHeight);
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
	if(m_pData != NULL) {
		SetEditCaretPos(m_nCurrentAddress, m_bHighBits);
		Invalidate();
	}
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
	CPoint cPoint(cPt);
	cPoint.x += m_nScrollPostionX;
	cPoint.y -= m_tPaintDetails.cPaintingRect.top;
	if((GetStyle() & ES_MULTILINE)) {
		cPoint.x += (m_tPaintDetails.nCharacterWidth>>1) - CONTROL_BORDER_SPACE ;
	} else {
		cPoint.x += (m_tPaintDetails.nCharacterWidth>>1);
	}
	if(cPoint.y < 0) {
		cPoint.y = 0;
	} else if(cPoint.y > (int)(m_tPaintDetails.nVisibleLines*m_tPaintDetails.nLineHeight)) {
		cPoint.y = m_tPaintDetails.nVisibleLines*m_tPaintDetails.nLineHeight;
	}
	if((int)cPoint.x < (int)m_tPaintDetails.nHexPos) {
		cPoint.x = m_tPaintDetails.nHexPos;
	} else if(cPoint.x > (int)(m_tPaintDetails.nHexPos + m_tPaintDetails.nHexLen - DATA_ASCII_SPACE)) {
		cPoint.x = m_tPaintDetails.nHexPos + m_tPaintDetails.nHexLen - DATA_ASCII_SPACE;
	}
	cPoint.x -= m_tPaintDetails.nHexPos;
	UINT nRow = cPoint.y / m_tPaintDetails.nLineHeight;
	UINT nCharColumn  = cPoint.x / m_tPaintDetails.nCharacterWidth;
	UINT nColumn = nCharColumn / 3;
	bHighBits = nCharColumn % 3 == 0;
	nAddress = nColumn + (nRow + m_nScrollPostionY) * m_tPaintDetails.nBytesPerRow;
	if(nAddress >= m_nLength) {
		nAddress = m_nLength - 1;
		bHighBits = false;
	}
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
	CPoint cCarretPoint(m_tPaintDetails.cPaintingRect.left 
		- m_nScrollPostionX + m_tPaintDetails.nHexPos 
		+ (nColumn * 3 + (bHighBits ? 0 : 1)) * m_tPaintDetails.nCharacterWidth,
		m_tPaintDetails.cPaintingRect.top + 1 + nRow * m_tPaintDetails.nLineHeight);
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

	CreateEditCaret(nCarretHeight-1, nCarretWidth);
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
	if(m_pData == NULL) {
		return;
	}
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
	if( (m_pData == NULL) || (m_nLength < 1) ) {
		return;
	}

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
	if( (m_pData == NULL) || (m_nLength < 1) ) {
		return;
	}

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
	ASSERT(m_nCurrentAddress < m_nLength);

	if( (nInput > 255) || (m_pData == NULL) || m_bReadOnly) {
		return false;
	}
	
	BYTE nValue = 255;
	char nKey = (char)tolower(nInput);	
	if( (nKey >= 'a') && (nKey <= 'f') ) {
		nValue = nKey - (BYTE)'a' + (BYTE)0xa;
	} else if ( (nKey >= '0') && (nKey <= '9') ) {
		nValue = nKey - (BYTE)'0';
	}
	if(nValue != 255) {
		if(m_bHighBits) {
			nValue <<= 4;
			m_pData[m_nCurrentAddress] &= 0x0f;
			m_pData[m_nCurrentAddress] |= nValue;
			MoveCurrentAddress(0, false);
		} else {
			m_pData[m_nCurrentAddress] &= 0xf0;
			m_pData[m_nCurrentAddress] |= nValue;
			MoveCurrentAddress(1, true);
		}
		Invalidate();
		NotifyParent(HEN_CHANGE);
	} else {
		return false;
	}
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

LRESULT CHexEditBase::OnWMChar(WPARAM wParam, LPARAM)
{

	if(wParam == 0x08) {			
		//example: backspace-processing, (if once needed)
		//OnEditBackspace(); 
		//return 0;
	} /* other special processing here (insert: "else if() {}" ) */ else {
		if(OnEditInput((WORD)wParam)) {
			return 0;
		}
	}
	return 1;
}

BOOL CHexEditBase::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) {
		if(GetKeyState(VK_CONTROL) & 0x80000000) {
			switch(pMsg->wParam) {			
			case 'C': // ctrl + c: copy
				OnEditCopy();
				return TRUE;
			case 'V': // ctrl + v: paste
				OnEditPaste();
				return TRUE;
			case 'A': // ctrl + a: select all
				OnEditSelectAll();
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

void CHexEditBase::MoveCurrentAddress(int iDeltaAdr, bool bHighBits)
{
	bool bIsShift = (GetKeyState(VK_SHIFT) & 0x80000000) == 0x80000000;

	if(m_pData == NULL) {
		return;
	}
		
	UINT nAddress = m_nCurrentAddress;

	if(!bIsShift) {
		m_nSelectingBeg = NOSECTION_VAL;
		m_nSelectionBegin = NOSECTION_VAL;
		m_nSelectingEnd = NOSECTION_VAL;
		m_nSelectionEnd = NOSECTION_VAL;
	}
	if(iDeltaAdr > 0) {
		// go down
		if(nAddress + iDeltaAdr >= m_nLength) {
			// we reached the end
			nAddress = m_nLength - 1;
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
	if(bIsShift && (m_nSelectingBeg != NOSECTION_VAL)) {
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
	bool bIsShift = (GetKeyState(VK_SHIFT) & 0x80000000) == 0x80000000;

	
	if( bIsShift && (m_nSelectingBeg == NOSECTION_VAL) ) {
		// start with selecting
		m_nSelectingBeg = m_nCurrentAddress;
	}

	switch(nChar) {
	case VK_DOWN:
		MoveCurrentAddress(m_tPaintDetails.nBytesPerRow, m_bHighBits);
		break;
	case VK_UP:
		MoveCurrentAddress(-(int)m_tPaintDetails.nBytesPerRow, m_bHighBits);
		break;
	case VK_RIGHT:
		if(m_bHighBits) {
			// offset stays the same, caret moves to low-byte
			MoveCurrentAddress(0, false);
		} else {
			MoveCurrentAddress(1, true);
		}
		break;
	case VK_LEFT:
		if(!m_bHighBits) {
			// offset stays the same, caret moves to high-byte
			MoveCurrentAddress(0, true);
		} else {
			MoveCurrentAddress(-1, false);
		}
		break;
	case VK_PRIOR:
		MoveCurrentAddress(-(int)(m_tPaintDetails.nBytesPerRow*(m_tPaintDetails.nVisibleLines-1)), m_bHighBits);
		break;
	case VK_NEXT:
		MoveCurrentAddress(m_tPaintDetails.nBytesPerRow*(m_tPaintDetails.nVisibleLines-1), m_bHighBits);
		break;
	case VK_HOME:
		MoveCurrentAddress(-0x8000000, true);
		break;
	case VK_END:
		MoveCurrentAddress(0x7ffffff, false);
		break;
	case VK_INSERT:
		// not suported yet
		break;
	case VK_DELETE:
		// not suported yet
		break;
	case VK_RETURN:
		// not suported yet
		break;
	case VK_TAB:
		GetParent()->GetNextDlgTabItem(this, bIsShift)->SetFocus();
		break;
	}
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

	// menue-item: copy
	cMenu.AppendMenu(IsSelection() ? MF_STRING : MF_GRAYED|MF_DISABLED|MF_STRING, ID_EDIT_COPY, (LPCSTR)m_cContextCopy);
	
	// menue-item: paste
	COleDataObject cSource;
	cSource.AttachClipboard();
	cMenu.AppendMenu(cSource.IsDataAvailable(m_nBinDataClipboardFormat) && !m_bReadOnly ? MF_STRING : MF_GRAYED|MF_DISABLED|MF_STRING, 
		ID_EDIT_PASTE, (LPCSTR)m_cContextPaste);
	cSource.Release();
	OnExtendContextMenu(cMenu);
	cMenu.TrackPopupMenu(TPM_LEFTALIGN, cPoint.x, cPoint.y, this, CRect(0,0,100,100));
}

void CHexEditBase::OnEditCopy() 
{
	if( (m_nSelectionBegin != NOSECTION_VAL) && (m_nSelectionEnd != NOSECTION_VAL) ) {
		ASSERT(m_nSelectionEnd >= m_nSelectionBegin);

		BYTE *pData = m_pData + m_nSelectionBegin;
		BYTE *pDataEnd = m_pData + m_nSelectionEnd;
		CString cStr;

		COleDataSource *pSource = new COleDataSource;
		char* pBuf = new char[m_tPaintDetails.nBytesPerRow*3+2];
		try {
			memset(pBuf, ' ', m_tPaintDetails.nBytesPerRow*3);
			UINT nColumn = m_nSelectionBegin%m_tPaintDetails.nBytesPerRow;
			if(pDataEnd - pData <= m_tPaintDetails.nBytesPerRow) {
				nColumn = 0;
			}
			UINT nAdr = m_nSelectionBegin;
			while(pData <= pDataEnd ) {			
				CString cStr2;
				//cStr2.Format(_T("%0*X: "), (int)m_nAdrSize,  nAdr);
				for(; nColumn<m_tPaintDetails.nBytesPerRow && pData <= pDataEnd; ++nColumn, ++pData, ++nAdr) {
					pBuf[nColumn*3] = tabHexCharacters[*pData>>4];
					pBuf[nColumn*3+1] = tabHexCharacters[*pData&0xf];
				}
				pBuf[(nColumn-1)*3+2] = '\0';
				cStr += cStr2;
				cStr += pBuf;
				cStr += _T("\n");
				nColumn = 0;
			}

			EmptyClipboard();
			UINT nLength = m_nSelectionEnd - m_nSelectionBegin + 1;
			HGLOBAL	hMemb = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, nLength+sizeof(UINT));
			HGLOBAL	hMema = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT, cStr.GetLength() + 1);

			if( (hMema == NULL) || (hMemb == NULL)) {
				return;
			}

			// copy binary
			UINT *pData = (UINT*)::GlobalLock(hMemb);
			*pData = nLength;
			memcpy(&pData[1], m_pData+m_nSelectionBegin, nLength);
			::GlobalUnlock(hMemb);

			// copy ascii
			char *pPtr = (char*)::GlobalLock(hMema);
			memcpy(pPtr, (LPCSTR)cStr, cStr.GetLength());
			::GlobalUnlock(hMema);

			OpenClipboard();
			SetClipboardData((CLIPFORMAT)m_nBinDataClipboardFormat, hMemb);
			SetClipboardData((CF_TEXT), hMema);
			CloseClipboard();
		} 
		catch(...) 
		{
			delete pSource;
			delete []pBuf;
			throw;
		}
		delete []pBuf;
	}
}

void CHexEditBase::OnEditPaste() 
{
	ASSERT(m_nCurrentAddress < m_nLength);

	if(m_bReadOnly || (m_pData == NULL)) {
		return;
	}
	
	COleDataObject cSource;
	if(!cSource.AttachClipboard()) {
		TRACE("CHexEditBase::OnEditPaste: ERROR: AttachClipboard failed\n");
		return;
	}
	if(cSource.IsDataAvailable((CLIPFORMAT)m_nBinDataClipboardFormat)) {
		// okay, data available
		HGLOBAL hData = cSource.GetGlobalData((CLIPFORMAT)m_nBinDataClipboardFormat);
		if(hData == NULL) {
			TRACE("CHexEditBase::OnEditPaste: ERROR: GetGlobalData failed\n");
			return;
		}		
		UINT nPasteAdr = m_nCurrentAddress;
		if(IsSelection()) {
			nPasteAdr = m_nSelectionBegin;
		}
		UINT *pData = (UINT*)::GlobalLock(hData);
		UINT nLength = *pData;
		if( (nPasteAdr + nLength >= m_nLength) || (nLength >= m_nLength) ) {
			nLength = m_nLength - nPasteAdr;
		}
		memcpy(m_pData+nPasteAdr, &pData[1], nLength);
		::GlobalUnlock(hData);
		SetSelection(nPasteAdr, nPasteAdr+nLength-1, true, false);
		SetEditCaretPos(nPasteAdr+nLength-1, false);
		Invalidate();
		if(nLength>0) {
			NotifyParent(HEN_CHANGE);
		}
	}
}

void CHexEditBase::OnEditSelectAll() 
{
	if(m_nLength > 0) {
		SetSelection(0, m_nLength-1, false, true);
	}
}

void CHexEditBase::SetData(const BYTE *pData, UINT nLen, bool bUpdate)
{
	ASSERT(pData != NULL || nLen == 0);
	ASSERT(nLen > 0 || pData == NULL);
	ASSERT(nLen < 0x7ffff000); // about what we can manage without overflow

	m_nSelectingBeg = NOSECTION_VAL;
	m_nSelectingEnd = NOSECTION_VAL;
	m_nSelectionBegin = NOSECTION_VAL;
	m_nSelectionEnd = NOSECTION_VAL;
	m_nHighlightedBegin = NOSECTION_VAL;
	m_nHighlightedEnd = NOSECTION_VAL;
	if(m_bDeleteData) {
		delete []m_pData;
	}
	if(pData != NULL) {
		m_bDeleteData = true;
		m_nLength = nLen;
		m_pData = new BYTE[nLen];
		memcpy(m_pData, pData, nLen);
	} else {
		m_bDeleteData = false;
		m_nLength = 0;
		m_pData = NULL;
	}
	m_bRecalc = true;
	if(bUpdate && ::IsWindow(m_hWnd)) {
		Invalidate();
	}
	SetEditCaretPos(0, true);
}

void CHexEditBase::SetDirectDataPtr(BYTE *pData, UINT nLen, bool bUpdate)
{
	ASSERT(pData != NULL || nLen == 0);
	ASSERT(nLen > 0 || pData == NULL);
	ASSERT(nLen < 0x7ffff000); // about what we can manage without overflow

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
	m_nLength = nLen;
	m_pData = pData;
	m_bRecalc = true;
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

bool CHexEditBase::IsSelection() const 
{
	return (m_nSelectionEnd != NOSECTION_VAL) && (m_nSelectionBegin != NOSECTION_VAL);
}

bool CHexEditBase::IsHighlighted() const
{
	return (m_nHighlightedEnd != NOSECTION_VAL) && (m_nHighlightedBegin != NOSECTION_VAL);
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



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// class CHexEditBaseView
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CHexEditBaseView, CView)

BEGIN_MESSAGE_MAP(CHexEditBaseView, CView)
	//{{AFX_MSG_MAP(CHexEditBaseView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CHexEditBaseView::CHexEditBaseView() : CView() 
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
