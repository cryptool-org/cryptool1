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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScintillaView

IMPLEMENT_DYNCREATE(CScintillaView, CView)

#if 0
// temporarily disabled:
	ON_COMMAND(ID_OPTIONS_VIEW_LINENUMBERS, OnOptionsViewLinenumbers)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_LINENUMBERS, OnUpdateOptionsViewLinenumbers)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine) 
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

BEGIN_MESSAGE_MAP(CScintillaView, CView)
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
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////
// @mfunc constructor
// @rvalue void | not used
//
CScintillaView::CScintillaView()
{
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
BOOL CScintillaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

/////////////////////////////////////
// @mfunc not handled
// @rvalue void | not used
//
void CScintillaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
/////////////////////////////////////
// @mfunc not handled
// @rvalue void | not used
//
void CScintillaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
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
   CDocument *pDoc = GetDocument();
   CString strTitle = pDoc->GetPathName();
	m_wndScintilla.Init();
	//m_wndScintilla.LoadFile(strTitle);

}
/////////////////////////////////////
// @mfunc menu handler - toggle display of the line number display in scintilla
// @rvalue void | not used
//
void CScintillaView::OnOptionsViewLinenumbers() 
{
	m_wndScintilla.SetDisplayLinenumbers(!m_wndScintilla.GetDisplayLinenumbers());
}
/////////////////////////////////////
// @mfunc menu check handler - check the menu item if line numbers are displayed
// @rvalue void | not used
//
void CScintillaView::OnUpdateOptionsViewLinenumbers(
                                                       CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->SetCheck(m_wndScintilla.GetDisplayLinenumbers());
}
/////////////////////////////////////
// @mfunc menu handler - copy selected text to clipboard
// @rvalue void | not used
//
void CScintillaView::OnEditCopy() 
{
	m_wndScintilla.Copy();
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
	m_wndScintilla.Cut();
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
// @mfunc update line number
// @rvalue void | not used
//
void CScintillaView::OnUpdateLine(
                                     CCmdUI* pCmdUI) //@parm handle of textpane for linenumbers - see mainfrm.cpp at top
{
   CString strLine;
   long lLine = m_wndScintilla.GetCurrentLine();
   long lColumn = m_wndScintilla.GetCurrentColumn();
   long lPos = m_wndScintilla.GetCurrentPosition();
   //TODO strLine.Format(IDS_LINE_INDICATOR, lLine, lColumn, lPos);
   //TODO pCmdUI->SetText(strLine);
   pCmdUI->SetText("FIXME CScintillaView::OnUpdateLine");
} 
/////////////////////////////////////
// @mfunc update style number
// @rvalue void | not used
//
void CScintillaView::OnUpdateStyle(
                                      CCmdUI* pCmdUI) //@parm handle of textpane for style number - see mainfrm.cpp at top
{
#if 0
   CString strLine;
   int nStyle = m_wndScintilla.GetCurrentStyle();
   strLine.Format(IDS_STYLE_INDICATOR, nStyle);
   pCmdUI->SetText(strLine);
#endif
} 
/////////////////////////////////////
// @mfunc update folding level
// @rvalue void | not used
//
void CScintillaView::OnUpdateFold(
                                      CCmdUI* pCmdUI) //@parm handle of textpane for folding level - see mainfrm.cpp at top
{
#if 0
	CString strLine;
   int nFold = m_wndScintilla.GetCurrentFoldinglevel();
   strLine.Format(IDS_FOLD_INDICATOR, nFold);
   pCmdUI->SetText(strLine);
#endif
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
// @mfunc menu handler - display a window font selection dialog and set font attributes for style at caret position
// @rvalue void | not used
//
void CScintillaView::OnOptionsSetfont() 
{
   CFontDialog dlg;
   if (dlg.DoModal() == IDOK)
   {
	   m_wndScintilla.SetFontname(m_wndScintilla.GetCurrentStyle(), dlg.GetFaceName());
	   m_wndScintilla.SetFontheight(m_wndScintilla.GetCurrentStyle(), dlg.GetSize()/10);
	   m_wndScintilla.SetBold(m_wndScintilla.GetCurrentStyle(), dlg.IsBold());
	   m_wndScintilla.SetItalic(m_wndScintilla.GetCurrentStyle(), dlg.IsItalic());
	   m_wndScintilla.SetUnderline(m_wndScintilla.GetCurrentStyle(), dlg.IsUnderline());
   }
}
/////////////////////////////////////
// @mfunc menu handler - display a color selection dialog and set foreground color attribute for style at caret position
// @rvalue void | not used
//
void CScintillaView::OnOptionsForeground() 
{
   CColorDialog dlg;
   if (dlg.DoModal() == IDOK)
   {
	   m_wndScintilla.SetForeground(m_wndScintilla.GetCurrentStyle(), dlg.GetColor());
   }
}
/////////////////////////////////////
// @mfunc menu handler - display a color selection dialog and set background color attribute for style at caret position
// @rvalue void | not used
//
void CScintillaView::OnOptionsBackground() 
{
   CColorDialog dlg;
   if (dlg.DoModal() == IDOK)
   {
	   m_wndScintilla.SetBackground(m_wndScintilla.GetCurrentStyle(), dlg.GetColor());
   }
}

/////////////////////////////////////
// @mfunc menu handler - display a wordlist dialog and set a wordlist with keywords for current lexer
// @rvalue void | not used
//
void CScintillaView::OnOptionsWordlist() 
{
#ifdef SCWORDLIST
	CWordlistDlg dlg;
   if (dlg.DoModal() == IDOK)
   {
      int nWordlist = ::atoi(dlg.m_strWordlistNumber);
      m_wndScintilla.SendMessage(SCI_SETKEYWORDS, nWordlist, (long)(LPCSTR)dlg.m_strKeywords);
      m_wndScintilla.Refresh();
   }
#endif
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
// @mfunc command handler - set control to overstrike mode - see accelarator table in ressource file
// @rvalue void | not used
//
void CScintillaView::OnToggleInsert()
{
   m_wndScintilla.SetOverstrike(!m_wndScintilla.GetOverstrike());
}
/////////////////////////////////////
// @mfunc menu handler - toggle display of folding margin
// @rvalue void | not used
//
void CScintillaView::OnOptionsFoldMargin() 
{
   m_wndScintilla.SetDisplayFolding();
}
/////////////////////////////////////
// @mfunc menu handler - toggle display of selection margin
// @rvalue void | not used
//
void CScintillaView::OnOptionsSelectionMargin() 
{
	m_wndScintilla.SetDisplaySelection(!m_wndScintilla.GetDisplaySelection());
}

/////////////////////////////////////
// @mfunc menu check handler - check menu when selection margin is displayed
// @rvalue void | not used
//
void CScintillaView::OnUpdateOptionsSelectionMargin(
                                                       CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->SetCheck(m_wndScintilla.GetDisplaySelection());
}
/////////////////////////////////////
// @mfunc menu check handler - check menu when folding margin is displayed
// @rvalue void | not used
//
void CScintillaView::OnUpdateOptionsFoldMargin(
                                                  CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->SetCheck(m_wndScintilla.GetDisplayFolding());
}

/////////////////////////////////////
// @mfunc menu handler - add a bookmark at the caret line
// @rvalue void | not used
//
void CScintillaView::OnOptionsAddmarker() 
{
   m_wndScintilla.AddBookmark(m_wndScintilla.GetCurrentLine());
}
/////////////////////////////////////
// @mfunc menu check handler - disable menu item when there is already a marker at that line
// @rvalue void | not used
//
void CScintillaView::OnUpdateOptionsAddmarker(
                                                 CCmdUI* pCmdUI) //@parm menu handle
{
   pCmdUI->Enable(!m_wndScintilla.HasBookmark(m_wndScintilla.GetCurrentLine()));
}
/////////////////////////////////////
// @mfunc menu handler - delete a bookmark at the caret line
// @rvalue void | not used
//
void CScintillaView::OnOptionsDeletemarker() 
{
   m_wndScintilla.DeleteBookmark(m_wndScintilla.GetCurrentLine());
}
/////////////////////////////////////
// @mfunc menu check handler - disable menu item when there is no marker at that line
// @rvalue void | not used
//
void CScintillaView::OnUpdateOptionsDeletemarker(
                                                    CCmdUI* pCmdUI) //@parm menu handle
{
   pCmdUI->Enable(m_wndScintilla.HasBookmark(m_wndScintilla.GetCurrentLine()));
}
/////////////////////////////////////
// @mfunc menu handler - find next bookmark from the caret line
// @rvalue void | not used
//
void CScintillaView::OnOptionsFindNextmarker() 
{
   m_wndScintilla.FindNextBookmark();
}
/////////////////////////////////////
// @mfunc menu handler - find previous bookmark from the caret line
// @rvalue void | not used
//
void CScintillaView::OnOptionsFindPrevmarker() 
{
   m_wndScintilla.FindPreviousBookmark();
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
/////////////////////////////////////
// @mfunc menu handler - save current document - let the control do the work
// @rvalue void | not used
//
BOOL CScintillaView::Save(
                             LPCSTR szPath) //@parm path of document to save to
{
   return m_wndScintilla.SaveFile(szPath);
}

/////////////////////////////////////
// @mfunc menu handler - goto to a character position in the control
// @rvalue void | not used
//
void CScintillaView::OnOptionsGotopos() 
{
#ifdef SCGOTO
	CGotoPosDlg dlg;
   dlg.m_nPos = m_wndScintilla.GetCurrentPosition();
   if (dlg.DoModal() == IDOK)
   {
      m_wndScintilla.GotoPosition(dlg.m_nPos);
      m_wndScintilla.SetFocus();
   }
#endif
}
/////////////////////////////////////
// @mfunc menu handler - goto to a character position in the control
// @rvalue void | not used
//
void CScintillaView::OnOptionsGotoline() 
{
#ifdef SCGOTO
	CGotoLineDlg dlg;
   dlg.m_nLine = m_wndScintilla.GetCurrentLine();
   if (dlg.DoModal() == IDOK)
   {
      m_wndScintilla.GotoLine(dlg.m_nLine);
      m_wndScintilla.SetFocus();
   }
#endif
}

/////////////////////////////////////
// @mfunc menu handler - 
// @rvalue void | not used
//
void CScintillaView::OnOptionsDlg() 
{
#if 0
	CScintillaDlg dlg;
   dlg.DoModal();
#endif
}
