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
// HexEditCtrlView.h : interface of the CHexEditCtrlView class
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_HEXEDITCTRLVIEW_H__5DDBE23B_CA69_4C02_8643_5D03A1CB690C__INCLUDED_)
#define AFX_HEXEDITCTRLVIEW_H__5DDBE23B_CA69_4C02_8643_5D03A1CB690C__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// includes
/////////////////////////////////////////////////////////////////////////////
#include "HexEditBase.h"
#include "HexEditCtrlDoc.h"



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CHexEditCtrlView
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class CHexEditCtrlView : public CHexEditBaseView
{
public:
	CHexEditCtrlDoc* GetDocument();
	virtual BOOL OnCommand( WPARAM wParam, LPARAM lParam );

protected: 
	CHexEditCtrlView();
	virtual ~CHexEditCtrlView();	

	//{{AFX_VIRTUAL(CHexEditCtrlView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHexEditCtrlView)
	afx_msg void OnHexEditChanged();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditClear();
	afx_msg void OnEditSelectAll();
	afx_msg void OnGotoVater();
	afx_msg void OnEditFind();
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	//}}AFX_MSG

	DECLARE_DYNCREATE(CHexEditCtrlView)
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnEntropy();
	afx_msg void OnHistogram();
	afx_msg void OnTotxt();

public:
	virtual void showAsText() { OnTotxt(); }
};

#ifndef _DEBUG  // debug version in HexEditCtrlView.cpp
inline CHexEditCtrlDoc* CHexEditCtrlView::GetDocument()
   { return (CHexEditCtrlDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_HEXEDITCTRLVIEW_H__5DDBE23B_CA69_4C02_8643_5D03A1CB690C__INCLUDED_)
