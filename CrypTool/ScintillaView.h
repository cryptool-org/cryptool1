/* @doc
 * @module ScintillaView.h | Definition of a Scintilla syntax coloring edit view for MFC
 * See www.scintilla.org for details
 * Author: Horst Brückner, hb@ec-logic.com
 * Environment: VisualC++ Version 6, static Build of Scintilla, SciLexer.dll as Lexer
 */
#if !defined(AFX_ScintillaView_H__8370B793_3C97_4B71_BE55_1520C8497972__INCLUDED_)
#define AFX_ScintillaView_H__8370B793_3C97_4B71_BE55_1520C8497972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "scintillawnd.h"
#include "CrypToolView.h"
#ifdef SCFIND
#include "FindDlg.h"
#include "ReplaceDlg.h"
#endif
////////////////////////////////////
// @class CScintillaWnd | Class of a GCL Scintilla syntax coloring edit view for MFC
// @base public | CView
//
class CScintillaView : public CCrypToolView
{
	int fontSize;
	char fontFace[128];
protected: // Nur aus Serialisierung erzeugen
// @access protected constructor - destructor
// @cmember empty Constructor
	CScintillaView();
	DECLARE_DYNCREATE(CScintillaView)

public:
// @access public function member
// @cmember get document
	CScintillaDoc* GetDocument();
	void RefreshAlphabet(); // refresh alphabet from text options

// @cmember process notification from scintilla control
   virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
   virtual BOOL OnCommand( WPARAM wParam, LPARAM lParam );
// @cmember save document
   virtual BOOL Save(LPCSTR szPath);
// @cmember get the edit control pointer
   virtual CScintillaWnd *GetEditControl(){return &m_wndScintilla;};

protected:
// @access protected data members
// @cmember the scintilla window/view
	CScintillaWnd     m_wndScintilla;
	CArray<int, int> m_aPageStart;
	CRect            m_rMargin;
	BOOL             m_bUsingMetric;
	BOOL             m_bPersistMarginSettings;           //Should we persist the margin settings for the Page Setup dialog
	BOOL             m_bPrintHeader;                     //Should Headers be printed?
	BOOL             m_bPrintFooter;                     //Should Footers be printed?	



#ifdef SCFIND
// @cmember a nonmodal dialog handle for finding text
   CFindDlg          m_dlgFind;
// @cmember a nonmodal dialog handle for replacing text
   CReplaceDlg       m_dlgReplace;
#endif

public:
// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CScintillaView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnViewFontArial08();
	virtual void OnViewFontArial10();
	virtual void OnViewFontArial12();
	virtual void OnViewFontCourier08();
	virtual void OnViewFontCourier10();
	virtual void OnViewFontCourier12();

	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual BOOL PaginateTo(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	virtual void PrintHeader(CDC* pDC, CPrintInfo* pInfo, RangeToFormat& frPrint);
	virtual void PrintFooter(CDC* pDC, CPrintInfo* pInfo, RangeToFormat& frPrint);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual long PrintPage(CDC* pDC, CPrintInfo* pInfo, long nIndexStart, long nIndexStop);
	virtual void OnViewEndOfLine();
	virtual void OnUpdateViewEndOfLine(CCmdUI* pCmdUI);
	virtual void OnViewLineWrap();
	virtual void OnUpdateViewLineWrap(CCmdUI* pCmdUI);
	virtual void OnViewWhitespace();
	virtual void OnUpdateViewWhitespace(CCmdUI* pCmdUI);
	//}}AFX_VIRTUAL
	static BOOL UserWantsMetric();
	virtual void LoadMarginSettings(const CString& sSection = _T("PageSetup"));
	virtual void SaveMarginSettings(const CString& sSection = _T("PageSetup"));


// Implementierung
public:
	virtual ~CScintillaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void setTextFont(int size, const char* fontClass);
	BOOL checkFontStyle(int size, const char* FaceName);

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CScintillaView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditClear();
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnEditFind();
	afx_msg void OnFilePageSetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTohex();
	afx_msg void OnUpdateZeichenformatArial08(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZeichenformatArial10(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZeichenformatArial12(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZeichenformatCourier08(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZeichenformatCourier10(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZeichenformatCourier12(CCmdUI *pCmdUI);
	afx_msg void OnViewAlphabet();
	afx_msg void OnUpdateViewAlphabet(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // Testversion in ScintillaView.cpp
inline CScintillaDoc* CScintillaView::GetDocument()
   { return (CScintillaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ScintillaView_H__8370B793_3C97_4B71_BE55_1520C8497972__INCLUDED_)
