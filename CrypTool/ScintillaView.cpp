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

/* @doc
 * @module ScintillaView.cpp | Implementation of a Scintilla syntax coloring view for MFC
 */
//Debug		..\LibAnalyse\Debug\LibAnalyse.lib ..\Libec\Lib\EcBibV2D.lib ..\libmiracl\Debug\LibMiracl.lib ..\OpenSSL\libeay32.lib htmlhelp.lib ..\libNtl\Debug\LibNTL.lib
//Releasede	..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib ..\OpenSSL\libeay32.lib ..\libNTL\Release\libNTL.lib "C:\program files\HTML Help Workshop\lib\htmlhelp.lib"
//Releaseen	..\LibAnalyse\Release\LibAnalyse.lib ..\Libec\Lib\EcBibV2.lib ..\libmiracl\Release\LibMiracl.lib ..\OpenSSL\libeay32.lib ..\libNTL\Release\libNTL.lib "C:\program files\HTML Help Workshop\lib\htmlhelp.lib"

#include "stdafx.h"
//#include "scintillamfc.h"

#include "ScintillaDoc.h"
#include "ScintillaView.h"
#ifdef SCWORDLIST
#include "wordlistdlg.h"
#endif
#ifdef SCGOTO
#include "GotoLineDlg.h"
#include "GotoPosDlg.h"
#endif
//#include "ScintillaDlg.h"
#include "scintilla.h"
#include ".\scintillaview.h"
#include "FileTools.h"
// Suchen und ersetzen
#include "DlgFindAndReplace.h"

#include "cryptoolapp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScintillaView

IMPLEMENT_DYNCREATE(CScintillaView, CCrypToolView)

#if 0
// temporarily disabled:
	ON_COMMAND(ID_OPTIONS_VIEW_LINENUMBERS, OnOptionsViewLinenumbers)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_LINENUMBERS, OnUpdateOptionsViewLinenumbers)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_STYLE, OnUpdateStyle) 
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_FOLD, OnUpdateFold) 
	ON_COMMAND(ID_OPTIONS_SETFONT, OnOptionsSetfont)
	ON_COMMAND(ID_OPTIONS_FOREGROUND, OnOptionsForeground)
	ON_COMMAND(ID_OPTIONS_BACKGROUND, OnOptionsBackground)
	ON_COMMAND(ID_OPTIONS_WORDLIST, OnOptionsWordlist)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SELECTION_MARGIN, OnUpdateOptionsSelectionMargin)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FOLD_MARGIN, OnUpdateOptionsFoldMargin)
	ON_COMMAND(ID_OPTIONS_ADDMARKER, OnOptionsAddmarker)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ADDMARKER, OnUpdateOptionsAddmarker)
	ON_COMMAND(ID_OPTIONS_DELETEMARKER, OnOptionsDeletemarker)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DELETEMARKER, OnUpdateOptionsDeletemarker)
	ON_COMMAND(ID_OPTIONS_FIND_NEXTMARKER, OnOptionsFindNextmarker)
	ON_COMMAND(ID_OPTIONS_FIND_PREVMARKER, OnOptionsFindPrevmarker)
	ON_COMMAND(ID_OPTIONS_GOTOPOS, OnOptionsGotopos)
	ON_COMMAND(ID_OPTIONS_GOTOLINE, OnOptionsGotoline)
	ON_COMMAND(ID_OPTIONS_DLG, OnOptionsDlg)
	ON_COMMAND(ID_OPTIONS_FOLD_MARGIN, OnOptionsFoldMargin)
	ON_COMMAND(ID_OPTIONS_SELECTION_MARGIN, OnOptionsSelectionMargin)
	ON_COMMAND(ID_TOGGLE_INSERT, OnToggleInsert)
#endif

BEGIN_MESSAGE_MAP(CScintillaView, CCrypToolView)
	//{{AFX_MSG_MAP(CScintillaView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine) 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
	ON_COMMAND(ID_VIEW_ENDOFLINE, OnViewEndOfLine)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ENDOFLINE, OnUpdateViewEndOfLine)
	ON_COMMAND(ID_VIEW_LINEWRAP, OnViewLineWrap)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LINEWRAP, OnUpdateViewLineWrap)
	ON_COMMAND(ID_VIEW_WHITESPACE, OnViewWhitespace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WHITESPACE, OnUpdateViewWhitespace)
	ON_COMMAND(ID_ZEICHENFORMAT_ARIAL08, OnViewFontArial08)
	ON_COMMAND(ID_ZEICHENFORMAT_ARIAL10, OnViewFontArial10)
	ON_COMMAND(ID_ZEICHENFORMAT_ARIAL12, OnViewFontArial12)
	ON_COMMAND(ID_ZEICHENFORMAT_ARIAL14, OnViewFontArial14)
	ON_COMMAND(ID_ZEICHENFORMAT_ARIAL16, OnViewFontArial16)
	ON_COMMAND(ID_ZEICHENFORMAT_ARIAL18, OnViewFontArial18)
	ON_COMMAND(ID_ZEICHENFORMAT_ARIAL20, OnViewFontArial20)
	ON_COMMAND(ID_ZEICHENFORMAT_COURIER08, OnViewFontCourier08)
	ON_COMMAND(ID_ZEICHENFORMAT_COURIER10, OnViewFontCourier10)
	ON_COMMAND(ID_ZEICHENFORMAT_COURIER12, OnViewFontCourier12)
	ON_COMMAND(ID_ZEICHENFORMAT_COURIER14, OnViewFontCourier14)
	ON_COMMAND(ID_ZEICHENFORMAT_COURIER16, OnViewFontCourier16)
	ON_COMMAND(ID_ZEICHENFORMAT_COURIER18, OnViewFontCourier18)
	ON_COMMAND(ID_ZEICHENFORMAT_COURIER20, OnViewFontCourier20)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PAGE_SETUP, OnFilePageSetup)
	ON_COMMAND(ID_TOHEX, OnTohex)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_ARIAL08, OnUpdateZeichenformatArial08)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_ARIAL10, OnUpdateZeichenformatArial10)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_ARIAL12, OnUpdateZeichenformatArial12)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_ARIAL14, OnUpdateZeichenformatArial14)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_ARIAL16, OnUpdateZeichenformatArial16)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_ARIAL18, OnUpdateZeichenformatArial18)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_ARIAL20, OnUpdateZeichenformatArial20)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_COURIER08, OnUpdateZeichenformatCourier08)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_COURIER10, OnUpdateZeichenformatCourier10)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_COURIER12, OnUpdateZeichenformatCourier12)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_COURIER14, OnUpdateZeichenformatCourier14)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_COURIER16, OnUpdateZeichenformatCourier16)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_COURIER18, OnUpdateZeichenformatCourier18)
	ON_UPDATE_COMMAND_UI(ID_ZEICHENFORMAT_COURIER20, OnUpdateZeichenformatCourier20)
	ON_COMMAND(ID_VIEW_ALPHABET, OnViewAlphabet)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALPHABET, OnUpdateViewAlphabet)
END_MESSAGE_MAP()

/////////////////////////////////////
// @mfunc constructor
// @rvalue void | not used
//
CScintillaView::CScintillaView() : m_rMargin(0, 0, 0, 0),
                                   m_bPrintHeader(FALSE), 
                                   m_bPrintFooter(TRUE),
								   m_bPersistMarginSettings(FALSE)

{
	m_bUsingMetric = UserWantsMetric();
}

BOOL CScintillaView::UserWantsMetric()
{
  TCHAR localeInfo[3];
  GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IMEASURE, localeInfo, 3);
  return (localeInfo[0] == _T('0')) ;
}

/////////////////////////////////////
// @mfunc destructor
// @rvalue void | not used
//
CScintillaView::~CScintillaView()
{
}
/////////////////////////////////////
// @mfunc called before window is created
// @rvalue void | not used
//
BOOL CScintillaView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
/////////////////////////////////////
// @mfunc Called when view should be redrawn - not used - handled by scintilla window
// @rvalue void | not used
//
void CScintillaView::OnDraw(CDC* pDC)
{
	CScintillaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}
/////////////////////////////////////
// @mfunc not handled
// @rvalue void | not used
//

void CScintillaView::OnFilePageSetup() 
{
  //Display a standard page setup dialog
	CPageSetupDialog dlg;

  //Allow the margin settings to be tweaked
  dlg.m_psd.Flags |= PSD_MARGINS;

  //Are we using the metric or imperial system	
  if (m_bUsingMetric)
    dlg.m_psd.Flags |= PSD_INHUNDREDTHSOFMILLIMETERS;
  else
    dlg.m_psd.Flags |= PSD_INTHOUSANDTHSOFINCHES;

  if (m_bPersistMarginSettings)
    LoadMarginSettings();

  //Set the current margin settings to the current value from m_rectMargin 
  dlg.m_psd.rtMargin = m_rMargin;

	//get the current device from the app
	PRINTDLG pd;
	pd.hDevNames = NULL;
	pd.hDevMode = NULL;
  CWinApp* pApp = AfxGetApp();
	pApp->GetPrinterDeviceDefaults(&pd);
	dlg.m_psd.hDevNames = pd.hDevNames;
	dlg.m_psd.hDevMode = pd.hDevMode;

	if (dlg.DoModal() == IDOK)
	{
    //Save the new margin value in to the member variable
    m_rMargin = dlg.m_psd.rtMargin;

    if (m_bPersistMarginSettings)
      SaveMarginSettings();

    //Update the printer settings
		pApp->SelectPrinter(dlg.m_psd.hDevNames, dlg.m_psd.hDevMode);
	}
}

BOOL CScintillaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	  //Determine if we should allow selection printing
	CScintillaWnd* rCtrl = GetEditControl();


	long nStartChar = rCtrl->GetSelectionStart();
  long nEndChar = rCtrl->GetSelectionEnd();
  if (nStartChar != nEndChar)
  {
    // Enable the Selection button
    pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;

    // Check the Selection button
    pInfo->m_pPD->m_pd.Flags |= PD_SELECTION;
  }

  //Let the base class do its thing
  return DoPreparePrinting(pInfo);
}

/////////////////////////////////////
// @mfunc not handled
// @rvalue void | not used
//
void CScintillaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* pInfo)
{
		ASSERT_VALID(this);

  CScintillaWnd* rCtrl = GetEditControl();

	//initialize page start vector
	ASSERT(m_aPageStart.GetSize() == 0);
	if (pInfo->m_pPD->PrintSelection())
		m_aPageStart.Add(rCtrl->GetSelectionStart());
	else {
		m_aPageStart.Add(0);
		UINT page = pInfo->GetFromPage();
		if (pInfo->GetToPage() > page) 
			page = pInfo->GetToPage();
		pInfo->SetMaxPage(page);
	}
	ASSERT(m_aPageStart.GetSize() > 0);

	ASSERT_VALID(this);
}

BOOL CScintillaView::PaginateTo(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

  CRect rectSave = pInfo->m_rectDraw;
	UINT nPageSave = pInfo->m_nCurPage;
	ASSERT(nPageSave > 1);
	ASSERT(nPageSave >= static_cast<UINT>(m_aPageStart.GetSize()));
	VERIFY(pDC->SaveDC() != 0);
	pDC->IntersectClipRect(0, 0, 0, 0);
	pInfo->m_nCurPage = m_aPageStart.GetSize();
	while (pInfo->m_nCurPage < nPageSave)
	{
		ASSERT(pInfo->m_nCurPage == static_cast<UINT>(m_aPageStart.GetSize()));
		OnPrepareDC(pDC, pInfo);
		ASSERT(pInfo->m_bContinuePrinting);
		pInfo->m_rectDraw.SetRect(0, 0,	pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));
		OnPrint(pDC, pInfo);
		if (pInfo->m_nCurPage == static_cast<UINT>(m_aPageStart.GetSize()))
			break;
		++pInfo->m_nCurPage;
	}
	BOOL bResult = pInfo->m_nCurPage == nPageSave;
	pDC->RestoreDC(-1);
	pInfo->m_nCurPage = nPageSave;
  pInfo->m_rectDraw = rectSave;
	ASSERT_VALID(this);
	return bResult;
}

void CScintillaView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	//Validate our parameters
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	UNUSED(pDC); // unused in release builds
	if (pInfo == NULL)
		return;
	if (pInfo->m_nCurPage <= pInfo->GetMaxPage())
	{
		if ((pInfo->m_nCurPage > static_cast<UINT>(m_aPageStart.GetSize())) &&	!PaginateTo(pDC, pInfo))
		{
			//can't paginate to that page, thus cannot print it.
			pInfo->m_bContinuePrinting = FALSE;
		}
		ASSERT_VALID(this);
	}
	else
	{
			//Reached the max page to print
			pInfo->m_bContinuePrinting = FALSE;
	}
}

void CScintillaView::PrintHeader(CDC* pDC, CPrintInfo* /*pInfo*/, RangeToFormat& frPrint)
{
  //By Default we print "Document Name - Printed on Date" as well as a line separator below the text
  //Derived classes are of course free to implement their own version of PrintHeader
  CString sHeader;
  AfxFormatString2(sHeader, IDS_SCINTILLA_DEFAULT_PRINT_HEADER, GetDocument()->GetTitle(), COleDateTime::GetCurrentTime().Format());

  //Setup the DC
  pDC->SetTextColor(RGB(0, 0, 0));
  UINT nAlign = pDC->SetTextAlign(TA_LEFT | TA_TOP);

  //Draw the header
  CSize sizeText = pDC->GetTextExtent(sHeader);
  int nHeaderDepth = 2*sizeText.cy;
	CRect rLine(frPrint.rcPage.left, frPrint.rcPage.top, frPrint.rcPage.right, frPrint.rcPage.top + nHeaderDepth);
  pDC->ExtTextOut(frPrint.rcPage.left, frPrint.rcPage.top + nHeaderDepth/3, 0, &rLine, sHeader, NULL);

  //Draw a line underneath the text
  pDC->MoveTo(frPrint.rcPage.left, frPrint.rcPage.top + nHeaderDepth - 5);
  pDC->LineTo(frPrint.rcPage.right, frPrint.rcPage.top + nHeaderDepth - 5);

  //Restore the DC
  pDC->SetTextAlign(nAlign);

  //Adjust the place where scintilla will draw the text
  if (frPrint.rc.top < (frPrint.rcPage.top + nHeaderDepth))
    frPrint.rc.top = frPrint.rcPage.top + nHeaderDepth;
}

void CScintillaView::PrintFooter(CDC* pDC, CPrintInfo* pInfo, RangeToFormat& frPrint)
{
  //By Default we print "Page X" as well as a line separator above the text
  //Derived classes are of course free to implement their own version of PrintFooter
  CString sPage;
  sPage.Format(_T("%d"), pInfo->m_nCurPage);
  CString sFooter;
  AfxFormatString1(sFooter, IDS_SCINTILLA_DEFAULT_PRINT_FOOTER, sPage);

  //Setup the DC
  pDC->SetTextColor(RGB(0, 0, 0));
  UINT nAlign = pDC->SetTextAlign(TA_LEFT | TA_TOP);
  
  //Draw the header
  CSize sizeText = pDC->GetTextExtent(sFooter);
  int nFooterDepth = 2*sizeText.cy;
  CRect rLine(frPrint.rcPage.left, frPrint.rcPage.bottom - nFooterDepth, frPrint.rcPage.right, frPrint.rcPage.bottom);
  pDC->ExtTextOut(frPrint.rcPage.left, frPrint.rcPage.bottom - nFooterDepth*2/3, 0, &rLine, sFooter, NULL);

  //Draw a line above the text
  pDC->MoveTo(frPrint.rcPage.left, frPrint.rcPage.bottom - nFooterDepth + 5);
  pDC->LineTo(frPrint.rcPage.right, frPrint.rcPage.bottom - nFooterDepth + 5);

  //Restore the DC
  pDC->SetTextAlign(nAlign);

  //Adjust the place where scintilla will draw the text
  if (frPrint.rc.bottom > (frPrint.rcPage.bottom - nFooterDepth))
    frPrint.rc.bottom = frPrint.rcPage.bottom - nFooterDepth;
}

long CScintillaView::PrintPage(CDC* pDC, CPrintInfo* pInfo, long nIndexStart, long nIndexStop)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	RangeToFormat rfPrint;
	rfPrint.hdc = pDC->m_hDC;
	rfPrint.hdcTarget = pDC->m_hAttribDC;

	//Take into account the specified margins
  CRect rMargins;
	if ((m_rMargin.left) != 0 || (m_rMargin.right) != 0 || (m_rMargin.top) != 0 || (m_rMargin.bottom != 0)) 
  {
    //Get printer resolution
    CPoint pDpi;
    pDpi.x = pDC->GetDeviceCaps(LOGPIXELSX);  //Dpi in X direction
    pDpi.y = pDC->GetDeviceCaps(LOGPIXELSY);  //Dpi in Y direction

		//Convert the hundredths of millimeters or thousandths of inches margin values
		//from the Page Setup dialog to device units.
		int iScale = m_bUsingMetric ? 2540 : 1000;    //scale factor for margin scaling;
		rMargins.left   = MulDiv(m_rMargin.left, pDpi.x, iScale);
		rMargins.top    = MulDiv(m_rMargin.top, pDpi.y, iScale);
		rMargins.right	= MulDiv(m_rMargin.right, pDpi.x, iScale);
		rMargins.bottom	= MulDiv(m_rMargin.bottom, pDpi.y, iScale);
	} 
  else 
		rMargins = m_rMargin;

  //We take the page size from the pInfo member variable (decrement the right and
  //bottom values by 1 to suit Scintilla)
	rfPrint.rcPage.left = pInfo->m_rectDraw.left;
	rfPrint.rcPage.top = pInfo->m_rectDraw.top;
	rfPrint.rcPage.right = pInfo->m_rectDraw.right - 1;
	rfPrint.rcPage.bottom = pInfo->m_rectDraw.bottom - 1;

  //Fill in the area to print
  rfPrint.rc.left = rfPrint.rcPage.left + rMargins.right;
  rfPrint.rc.top = rfPrint.rcPage.top + rMargins.top;
  rfPrint.rc.right = rfPrint.rcPage.right - rMargins.right;
  rfPrint.rc.bottom = rfPrint.rcPage.bottom - rMargins.bottom;

  //Fill in the text to print
	rfPrint.chrg.cpMin = nIndexStart;
	rfPrint.chrg.cpMax = nIndexStop;

  //print the header (if requested to)
  if (m_bPrintHeader)
    PrintHeader(pDC, pInfo, rfPrint);

  //print the footer (if requested to)
  if (m_bPrintFooter)
    PrintFooter(pDC, pInfo, rfPrint);

  //Finally ask the control to print the text
	return GetEditControl()->FormatRange(TRUE,&rfPrint);
}
void CScintillaView::OnPrint(CDC *pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
	ASSERT(pInfo != NULL);
	ASSERT(pInfo->m_bContinuePrinting);

	UINT nPage = pInfo->m_nCurPage;
	ASSERT(nPage <= (UINT) m_aPageStart.GetSize());
	int nIndex = m_aPageStart[nPage-1];

  //Determine where we should end the printing
  int nEndPrint = 0;
  if (pInfo->m_pPD->PrintSelection())
	  nEndPrint = GetEditControl()->GetSelectionEnd();
  else
	  nEndPrint = GetEditControl()->GetTextLength();

	//print as much as possible in the current page.
	nIndex = PrintPage(pDC, pInfo, nIndex, nEndPrint);
	if (nIndex >= nEndPrint)
	{
		TRACE0("End of Document\n");
		pInfo->SetMaxPage(nPage);
		//pInfo->SetMaxPage(0xffff);
	} 

	//update pagination information for page just printed
	if (nPage == (UINT) m_aPageStart.GetSize())
	{
		if (nIndex < nEndPrint)
			m_aPageStart.Add(nIndex);
	}
	else
	{
		ASSERT(nPage+1 <= static_cast<UINT>(m_aPageStart.GetSize()));
		ASSERT(nIndex == m_aPageStart[nPage+1-1]);
	}

}
/////////////////////////////////////
// @mfunc not handled
// @rvalue void | not used
//
void CScintillaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
		ASSERT_VALID(this);
	m_aPageStart.RemoveAll();
}
#ifdef _DEBUG
void CScintillaView::AssertValid() const
{
	CView::AssertValid();
}

void CScintillaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

/////////////////////////////////////
// @mfunc return document handle
// @rvalue void | not used
//
CScintillaDoc* CScintillaView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScintillaDoc)));
	return (CScintillaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////
// @mfunc Called when window is created - we create our scintilla window here
// @rvalue int | 0 on succescc else -1
//
int CScintillaView::OnCreate(
                                LPCREATESTRUCT lpCreateStruct) //@parm pointer to propsed create structure - may be modified
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
   if (!m_wndScintilla.Create(_T("Title"), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 10000)) // hb - todo autogenerate id
   {   
      LPVOID lpMsgBuf;
      ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
               NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL);
      // Write to stderr
      TRACE (_T("%s\n"), (LPCTSTR)lpMsgBuf);
      // Free the buffer.
      LocalFree( lpMsgBuf );
      return -1;
   }

	 // flomar, 02/22/2012: disable the built-in Scintilla popup menu,
	 // and use an i18n-ed custom context menu in CCrypToolView instead
	 m_wndScintilla.SendMessage(SCI_USEPOPUP, 0, 0);

	return 0;
}

/////////////////////////////////////
// @mfunc Called when view is resized - we adjust the size of the scintilla window to fit client size
// @rvalue void | not used
//
void CScintillaView::OnSize(
                               UINT nType, //@parm indicator
                               int cx,     //@parm new width in pixel
                               int cy)     //@parm new height in pixel
{
	CView::OnSize(nType, cx, cy);
	if (m_wndScintilla.GetSafeHwnd())
   {
      m_wndScintilla.MoveWindow(0, 0, cx, cy);
   }
}

/////////////////////////////////////
// @mfunc Called when view was created - we try to let scintilla load a file if there is one
// @rvalue void | not used
//
void CScintillaView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
    CCryptDoc *pDoc = (CCryptDoc*)GetDocument();
    CString strTitle = pDoc->GetPathName();

	m_wndScintilla.Init();

	// set the Scintilla window's font according to what's stored in the document
	setTextFont(pDoc->fontSize, pDoc->fontFace);

	this->SetFocus();

	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
	{
		pActiveWindow->SendMessage(SCI_EMPTYUNDOBUFFER);  // FIXME -- right place to do this ?

		// FIXME: this is also done in CScintillaWnd::Init - why?
		pActiveWindow->SendMessage(SCI_SETEOLMODE, 0);
		pActiveWindow->SendMessage(SCI_SETVIEWEOL, 0);
	}
}


/////////////////////////////////////
// @mfunc menu handler - copy selected text to clipboard
// @rvalue void | not used
//
void CScintillaView::OnEditCopy() 
{
	m_wndScintilla.CopyCut(SCI_COPY);
}
/////////////////////////////////////
// @mfunc menu check handler - do nothing
// @rvalue void | not used
//
void CScintillaView::OnUpdateEditCopy(
                                         CCmdUI* pCmdUI) //@parm menu handle
{
}
/////////////////////////////////////
// @mfunc menu handler - cut selected text to clipboard
// @rvalue void | not used
//
void CScintillaView::OnEditCut() 
{
	m_wndScintilla.CopyCut(SCI_CUT);
}
/////////////////////////////////////
// @mfunc menu check handler - do nothing
// @rvalue void | not used
//
void CScintillaView::OnUpdateEditCut(
                                        CCmdUI* pCmdUI) //@parm menu handle
{
}
/////////////////////////////////////
// @mfunc menu handler - paste text from clipboard
// @rvalue void | not used
//
void CScintillaView::OnEditPaste() 
{
	m_wndScintilla.Paste();
}
/////////////////////////////////////
// @mfunc menu check handler - check if there is somethiong to paste
// @rvalue void | not used
//
void CScintillaView::OnUpdateEditPaste(
                                          CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->Enable(m_wndScintilla.CanPaste());
}
/////////////////////////////////////
// @mfunc menu handler - undo last action if possible
// @rvalue void | not used
//
void CScintillaView::OnEditUndo() 
{
   if (m_wndScintilla.CanUndo())
		m_wndScintilla.Undo();
}
/////////////////////////////////////
// @mfunc menu check handler - check if there is an action to undo
// @rvalue void | not used
//
void CScintillaView::OnUpdateEditUndo(
                                         CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->Enable(m_wndScintilla.CanUndo());
}




/////////////////////////////////////
// @mfunc menu handler - delete selection
// @rvalue void | not used
//
void CScintillaView::OnEditClear() 
{
	m_wndScintilla.Clear();
}

/////////////////////////////////////
// @mfunc menu handler - redo last undone action
// @rvalue void | not used
//
void CScintillaView::OnEditRedo() 
{
   if (m_wndScintilla.CanRedo())
		m_wndScintilla.Redo();
}

/////////////////////////////////////
// @mfunc menu check handler - check if there is an action to redo
// @rvalue void | not used
//
void CScintillaView::OnUpdateEditRedo(
                                         CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->Enable(m_wndScintilla.CanRedo());
}

/////////////////////////////////////
// @mfunc menu handler - select complete text
// @rvalue void | not used
//
void CScintillaView::OnEditSelectAll() 
{
	m_wndScintilla.SelectAll();
}




/////////////////////////////////////
// @mfunc menu check handler - set indicator for overstrike mode
// @rvalue void | not used
//
void CScintillaView::OnUpdateInsert(
                                       CCmdUI* pCmdUI) //@parm menu handle
{
	CString strText;
	if (m_wndScintilla.GetOverstrike())
		strText.LoadString(ID_INDICATOR_OVR);
	pCmdUI->SetText(strText);
}

/////////////////////////////////////
// @mfunc menu check handler - set indicator for line number
// @rvalue void | not used
//
void CScintillaView::OnUpdateLine(
                                       CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->Enable(); 
	CString strText;
	unsigned int pos = m_wndScintilla.SendMessage(SCI_GETCURRENTPOS);
	unsigned int line = m_wndScintilla.SendMessage(SCI_LINEFROMPOSITION, pos);
	unsigned int col = m_wndScintilla.SendMessage(SCI_GETCOLUMN, pos);
	strText.Format(ID_INDICATOR_LINE, line+1, col+1, pos+1);
	pCmdUI->SetText(strText);
}



/////////////////////////////////////
// @mfunc menu handler - find previous bookmark from the caret line
// @rvalue BOOL | TRUE if we handled the message - FALSE if message should be processed further
//
BOOL CScintillaView::OnNotify( 
                                 WPARAM wParam,       //@parm not used
                                 LPARAM lParam,       //@parm pointer to notification structure
                                 LRESULT* pResult )   //@parm result
{
   NMHDR *phDR;
   phDR = (NMHDR*)lParam;
// does notification come from my scintilla window?
   if (phDR != NULL && phDR->hwndFrom == m_wndScintilla.m_hWnd)
   {
      SCNotification *pMsg = (SCNotification*)lParam;
      switch (phDR->code)
      {
	     case SCN_STYLENEEDED: 
#if CONTAINER_LEXER_CURRENTLY_NOT_USED
	     {
			unsigned int startPos = SendMessage(SCI_GETENDSTYLED);
			//do we need to find start of line?
			unsigned int lineNumber = SendMessage(SCI_LINEFROMPOSITION,startPos);
			startPos = SendMessage(SCI_POSITIONFROMLINE,lineNumber);
			unsigned int endPos = pMsg->position;
			m_wndScintilla.StyleNeeded(startPos, endPos,theApp.TextOptions.getAlphabet(),theApp.TextOptions.getAlphabet().GetLength());
	        break;
		 }
#endif
	     break;
         case SCN_CHARADDED:
         break;
         case SCN_SAVEPOINTREACHED:
         break;
//       called when the document is changed - mark document modified
         case SCN_SAVEPOINTLEFT:
         {
            CDocument *pDoc = GetDocument();
            pDoc->SetModifiedFlag(TRUE);
         }
         break;
         case SCN_MODIFYATTEMPTRO:
         break;
         case SCN_KEY:
         break;
         case SCN_DOUBLECLICK:
         break;
//       called when something changes and we want to show new indicator state or brace matching
         case SCN_UPDATEUI:
         {
            m_wndScintilla.UpdateUI();
         }
         break;
         case SCN_MODIFIED:
//			 {
//				this->GetDocument()->SetModifiedFlag();
//				/* FIXME 
//
//				*/
//			 }
         break;
         case SCN_MACRORECORD:
         break;
//       user clicked margin - try folding action
         case SCN_MARGINCLICK:
         {
            m_wndScintilla.DoDefaultFolding(pMsg->margin, pMsg->position);
         }
         break;
         case SCN_NEEDSHOWN:
         break;
         case SCN_PAINTED:
         break;
         case SCN_USERLISTSELECTION:
         break;
         case SCN_URIDROPPED:
         break;
         case SCN_DWELLSTART:
         break;
         case SCN_DWELLEND:
         break;

      }
      return TRUE; // we processed the message
   }
   return CWnd::OnNotify(wParam, lParam, pResult);
}

BOOL CScintillaView::OnCommand( WPARAM wParam, LPARAM lParam )
{
    if (HIWORD(wParam)==SCEN_CHANGE)
    {
        this->GetDocument()->SetModifiedFlag();
    }
    return CWnd::OnCommand( wParam, lParam );
}

/////////////////////////////////////
// @mfunc menu handler - save current document - let the control do the work
// @rvalue void | not used
//
BOOL CScintillaView::Save(
                             LPCSTR szPath) //@parm path of document to save to
{
   return m_wndScintilla.SaveFile(szPath);
}

void CScintillaView::OnViewEndOfLine()
{
	// Anzeigen von Zeilenenden für Scintilla-Fenster ein-/ausschalten
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
	{
		int endofline = pActiveWindow->SendMessage(SCI_GETVIEWEOL);
		if(endofline) pActiveWindow->SendMessage(SCI_SETVIEWEOL, 0);
		else pActiveWindow->SendMessage(SCI_SETVIEWEOL, 1);
	}
}

void CScintillaView::OnUpdateViewEndOfLine(CCmdUI* pCmdUI)
{
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
		pCmdUI->SetCheck(pActiveWindow->SendMessage(SCI_GETVIEWEOL));
}

void CScintillaView::OnViewLineWrap()
{
	// Anzeigen von Zeilenumbrüchen für Scintilla-Fenster ein-/ausschalten
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
	{
		int linewrap = pActiveWindow->SendMessage(SCI_GETWRAPMODE);
		if(linewrap) pActiveWindow->SendMessage(SCI_SETWRAPMODE, 0);
		else pActiveWindow->SendMessage(SCI_SETWRAPMODE, 1);
	}
}

void CScintillaView::OnUpdateViewLineWrap(CCmdUI* pCmdUI)
{
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
		pCmdUI->SetCheck(pActiveWindow->SendMessage(SCI_GETWRAPMODE));
}

void CScintillaView::OnViewWhitespace()
{
	// Anzeigen von Leerzeichen für Scintilla-Fenster ein-/ausschalten
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
	{
		int whitespace = pActiveWindow->SendMessage(SCI_GETVIEWWS);
		if(whitespace) pActiveWindow->SendMessage(SCI_SETVIEWWS, 0);
		else pActiveWindow->SendMessage(SCI_SETVIEWWS, 1);
	}
}

void CScintillaView::OnUpdateViewWhitespace(CCmdUI* pCmdUI)
{
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
		pCmdUI->SetCheck(pActiveWindow->SendMessage(SCI_GETVIEWWS));
}

void CScintillaView::setTextFont(int size, const char* fontClass)
{
	fontSize = size;
	strcpy(fontFace, fontClass);

	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
	{
		int style = STYLE_DEFAULT; // set the font for all styles without their own font settings
		pActiveWindow->SendMessage(SCI_STYLESETSIZE, style, size);
		pActiveWindow->SendMessage(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(fontClass));
	}

	// we need to store font size and font face if it is changed
	this->GetDocument()->fontSize = size;
	this->GetDocument()->fontFace = fontClass;
}

void CScintillaView::OnViewFontArial08()
{
	setTextFont(8, "Arial");
}

void CScintillaView::OnViewFontArial10()
{
	setTextFont(10, "Arial");
}

void CScintillaView::OnViewFontArial12()
{
	setTextFont(12, "Arial");
}

void CScintillaView::OnViewFontArial14()
{
	setTextFont(14, "Arial");
}

void CScintillaView::OnViewFontArial16()
{
	setTextFont(16, "Arial");
}

void CScintillaView::OnViewFontArial18()
{
	setTextFont(18, "Arial");
}

void CScintillaView::OnViewFontArial20()
{
	setTextFont(20, "Arial");
}

void CScintillaView::OnViewFontCourier08()
{
	setTextFont(8, "Courier");
}

void CScintillaView::OnViewFontCourier10()
{
	setTextFont(10, "Courier");
}

void CScintillaView::OnViewFontCourier12()
{
	setTextFont(12, "Courier");
}

void CScintillaView::OnViewFontCourier14()
{
	setTextFont(14, "Courier");
}

void CScintillaView::OnViewFontCourier16()
{
	setTextFont(16, "Courier");
}

void CScintillaView::OnViewFontCourier18()
{
	setTextFont(18, "Courier");
}

void CScintillaView::OnViewFontCourier20()
{
	setTextFont(20, "Courier");
}

void CScintillaView::OnTohex()
{
	bHexEnabled = true;

	CAppDocument *NewDoc;
	char outfile[128];
	BOOL Modified;
	WINDOWPLACEMENT place;

	CCryptDoc *pDoc = GetDocument();

	GetTmpName(outfile,"cry",".hex");
	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
	CWnd_hilf->GetWindowPlacement( &place );

	Modified = pDoc->IsModified();
	pDoc->OnSaveDocument(outfile);
	CString key = pDoc->csSchluessel;

	// we open a new document file
	NewDoc = theApp.OpenDocumentFileNoMRU(outfile, pDoc->csSchluessel, SCHLUESSEL_LINEAR, pDoc->fontSize, pDoc->fontFace);
	NewDoc->SetModifiedFlag(Modified);
	NewDoc->SetTitle(pDoc->GetTitle());
	NewDoc->CWndVaterFenster = pDoc->CWndVaterFenster;
	NewDoc->hWndVaterFenster = pDoc->hWndVaterFenster;

	CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
	pDoc->OnCloseDocument();
	CWnd_hilf->SetWindowPlacement( &place );
	remove(outfile);

	CWnd_hilf->SetFocus();
}

BOOL CScintillaView::checkFontStyle(int size, const char* FaceName)
{
	return (size == fontSize && !strcmp(fontFace, FaceName));
}

void CScintillaView::OnUpdateZeichenformatArial08(CCmdUI *pCmdUI)
{
	if (checkFontStyle(8, "Arial"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatArial10(CCmdUI *pCmdUI)
{
	if (checkFontStyle(10, "Arial"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatArial12(CCmdUI *pCmdUI)
{
	if (checkFontStyle(12, "Arial"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatArial14(CCmdUI *pCmdUI)
{
	if (checkFontStyle(14, "Arial"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatArial16(CCmdUI *pCmdUI)
{
	if (checkFontStyle(16, "Arial"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatArial18(CCmdUI *pCmdUI)
{
	if (checkFontStyle(18, "Arial"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatArial20(CCmdUI *pCmdUI)
{
	if (checkFontStyle(20, "Arial"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatCourier08(CCmdUI *pCmdUI)
{
	if (checkFontStyle(8, "Courier"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatCourier10(CCmdUI *pCmdUI)
{
	if (checkFontStyle(10, "Courier"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}


void CScintillaView::OnUpdateZeichenformatCourier12(CCmdUI *pCmdUI)
{
	if (checkFontStyle(12, "Courier"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatCourier14(CCmdUI *pCmdUI)
{
	if (checkFontStyle(14, "Courier"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatCourier16(CCmdUI *pCmdUI)
{
	if (checkFontStyle(16, "Courier"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatCourier18(CCmdUI *pCmdUI)
{
	if (checkFontStyle(18, "Courier"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnUpdateZeichenformatCourier20(CCmdUI *pCmdUI)
{
	if (checkFontStyle(20, "Courier"))
		pCmdUI->SetCheck(1);
	else 
		pCmdUI->SetCheck(0);
}

void CScintillaView::OnEditFind() 
{
	// make the find and replace dialog visible
	theApp.findAndReplaceDialog.show();
}

void CScintillaView::LoadMarginSettings(const CString& sSection)
{
  //Get the margin values 
  CWinApp* pApp = AfxGetApp();
  ASSERT(pApp);
	m_rMargin.left = pApp->GetProfileInt(sSection, _T("LeftMargin"), m_rMargin.left);
	m_rMargin.right = pApp->GetProfileInt(sSection, _T("RightMargin"), m_rMargin.right);
	m_rMargin.top = pApp->GetProfileInt(sSection, _T("TopMargin"), m_rMargin.top);
	m_rMargin.bottom = pApp->GetProfileInt(sSection, _T("BottomMargin"), m_rMargin.bottom);
}

void CScintillaView::SaveMarginSettings(const CString& sSection)
{
  //Write out the margin values 
  CWinApp* pApp = AfxGetApp();
  ASSERT(pApp);
	pApp->WriteProfileInt(sSection, _T("LeftMargin"), m_rMargin.left);
	pApp->WriteProfileInt(sSection, _T("RightMargin"), m_rMargin.right);
	pApp->WriteProfileInt(sSection, _T("TopMargin"), m_rMargin.top);
	pApp->WriteProfileInt(sSection, _T("BottomMargin"), m_rMargin.bottom);
}

void CScintillaView::OnViewAlphabet()
{
	CScintillaWnd *pActiveWindow = (CScintillaWnd*)GetTopWindow();
	if (!pActiveWindow)
		return;
	int show = pActiveWindow->GetShowAlphabet();
	pActiveWindow->SetShowAlphabet(!show);
}

void CScintillaView::OnUpdateViewAlphabet(CCmdUI *pCmdUI)
{
	CScintillaWnd *pActiveWindow = (CScintillaWnd*)GetTopWindow();
	if(pActiveWindow)
		pCmdUI->SetCheck(pActiveWindow->GetShowAlphabet());
}

void CScintillaView::RefreshAlphabet()
{
	CScintillaWnd *pActiveWindow = (CScintillaWnd*)GetTopWindow();
	if (!pActiveWindow)
		return;
	if (pActiveWindow->GetShowAlphabet())
		pActiveWindow->SetShowAlphabet(true);
}

void CScintillaView::activatePlayfairView()
{
	// the old data (without separating blanks)
	const unsigned long lengthOldData = m_wndScintilla.SendMessage(SCI_GETLENGTH);
	char *oldData = new char[lengthOldData + 1];
	memset(oldData, 0, lengthOldData + 1);
	// the new data (including separating blanks)
	CString newData;
	// some tracking variables
	unsigned long numberOfCharactersProcessed = 0;
	unsigned long numberOfBlanksProcessed = 0;

	// get old text from Scintilla window
	m_wndScintilla.SendMessage(SCI_GETTEXT, (WPARAM)(lengthOldData + 1), (LPARAM)(oldData));

	// insert a blank after every two characters
	for(unsigned long i=0; i<lengthOldData; i++) {
		newData.AppendChar(*(oldData + numberOfCharactersProcessed));
		numberOfCharactersProcessed++;
		if(numberOfCharactersProcessed != 0 && !(numberOfCharactersProcessed%2)) {
			newData.AppendChar(' ');
			numberOfBlanksProcessed++;
		}
	}

	// remove trailing blanks
	newData.TrimRight();

	// set new text in Scintilla window
	m_wndScintilla.SendMessage(SCI_SETTEXT, (WPARAM)(newData.GetLength()), (LPARAM)(newData.GetBuffer()));

	// set font to Courier (size 10), so that pairs are smoothly aligned
	setTextFont(10, "Courier");
}