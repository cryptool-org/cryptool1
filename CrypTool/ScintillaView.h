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
protected: // Nur aus Serialisierung erzeugen
// @access protected constructor - destructor
// @cmember empty Constructor
	CScintillaView();
	DECLARE_DYNCREATE(CScintillaView)

public:
// @access public function member
// @cmember get document
	CScintillaDoc* GetDocument();
// @cmember process notification from scintilla control
   virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
// @cmember save document
   virtual BOOL Save(LPCSTR szPath);
// @cmember get the edit control pointer
   virtual CScintillaWnd *GetEditControl(){return &m_wndScintilla;};

protected:
// @access protected data members
// @cmember the scintilla window/view
	CScintillaWnd     m_wndScintilla;
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
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void OnViewEndOfLine();
	afx_msg void OnUpdateViewEndOfLine(CCmdUI* pCmdUI);
	afx_msg void OnViewLineWrap();
	afx_msg void OnUpdateViewLineWrap(CCmdUI* pCmdUI);
	afx_msg void OnViewWhitespace();
	afx_msg void OnUpdateViewWhitespace(CCmdUI* pCmdUI);
	afx_msg void OnViewFontArial08();
	afx_msg void OnViewFontArial10();
	afx_msg void OnViewFontArial12();
	afx_msg void OnViewFontCourier08();
	afx_msg void OnViewFontCourier10();
	afx_msg void OnViewFontCourier12();
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CScintillaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void setFixedFont(int size, const char* fontClass);

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTohex();
};

#ifndef _DEBUG  // Testversion in ScintillaView.cpp
inline CScintillaDoc* CScintillaView::GetDocument()
   { return (CScintillaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ScintillaView_H__8370B793_3C97_4B71_BE55_1520C8497972__INCLUDED_)
