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
};

#ifndef _DEBUG  // debug version in HexEditCtrlView.cpp
inline CHexEditCtrlDoc* CHexEditCtrlView::GetDocument()
   { return (CHexEditCtrlDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_HEXEDITCTRLVIEW_H__5DDBE23B_CA69_4C02_8643_5D03A1CB690C__INCLUDED_)
