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
// HexEditCtrlView.cpp : implementation of the CHexEditCtrlView class
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CrypToolApp.h"
#include "CryptDoc.h"
#include "FileTools.h"
#include "cryptography.h"
#include "HexEditCtrlDoc.h"
#include "HexEditCtrlView.h"
#include ".\hexeditctrlview.h"


/////////////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CHexEditCtrlView
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CHexEditCtrlView, CHexEditBaseView)

BEGIN_MESSAGE_MAP(CHexEditCtrlView, CHexEditBaseView)
	//{{AFX_MSG_MAP(CHexEditCtrlView)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_GOTO_VATER, OnGotoVater)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine) 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_ENTROPY, OnEntropy)
	ON_COMMAND(ID_HISTOGRAM, OnHistogram)
	ON_COMMAND(ID_TOTXT, OnTotxt)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
END_MESSAGE_MAP()


CHexEditCtrlView::CHexEditCtrlView()
{
	GetHexEditCtrl().SetAddressSize(8, false);
	GetHexEditCtrl().SetShowAddress(true, false);
	GetHexEditCtrl().SetShowAscii(true, false);
	GetHexEditCtrl().SetBytesPerRow(16, true, true);
}

CHexEditCtrlView::~CHexEditCtrlView()
{
}

BOOL CHexEditCtrlView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CHexEditBaseView::PreCreateWindow(cs);
}


void CHexEditCtrlView::OnHexEditChanged()
{
	GetDocument()->SetModifiedFlag();
}

#ifdef _DEBUG
void CHexEditCtrlView::AssertValid() const
{
	CHexEditBaseView::AssertValid();
}

void CHexEditCtrlView::Dump(CDumpContext& dc) const
{
	CHexEditBaseView::Dump(dc);
}

CHexEditCtrlDoc* CHexEditCtrlView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHexEditCtrlDoc)));
	return (CHexEditCtrlDoc*)m_pDocument;
}
#endif //_DEBUG


void CHexEditCtrlView::OnEditCut() 
{
	GetHexEditCtrl().callOnEditCut();
}

void CHexEditCtrlView::OnEditCopy() 
{
	GetHexEditCtrl().callOnEditCopy();
}

void CHexEditCtrlView::OnEditPaste() 
{
	GetHexEditCtrl().callOnEditPaste();
}

void CHexEditCtrlView::OnEditClear() 
{
	GetHexEditCtrl().callOnEditClear();
}

void CHexEditCtrlView::OnEditSelectAll() 
{
	GetHexEditCtrl().callOnEditSelectAll();
}

void CHexEditCtrlView::OnGotoVater() 
{
	if(IsWindow(((CAppDocument*)GetDocument())->hWndVaterFenster))
	{
		((CMDIFrameWnd*)theApp.m_pMainWnd)->
			MDIActivate(((CAppDocument*)GetDocument())->CWndVaterFenster);
	}
}

void CHexEditCtrlView::OnEntropy()
{
	CCryptDoc *pDoc = GetDocument();
	pDoc->UpdateContent();
	EntropyBin(pDoc->ContentName, pDoc->GetTitle());	
}

void CHexEditCtrlView::OnHistogram()
{
	CCryptDoc *pDoc = GetDocument();
	pDoc->UpdateContent();
    HistogramBin(pDoc->ContentName, pDoc->GetTitle());	
}

void CHexEditCtrlView::OnTotxt()
{
	bHexEnabled = false;

 	CAppDocument *NewDoc;
 	char outfile[128];
 	BOOL Modified;
 	WINDOWPLACEMENT place;
	CCryptDoc *pDoc = GetDocument();
 	 
 	GetTmpName(outfile,"cry",".txt");
 	
 	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->GetWindowPlacement( &place );
	Modified = pDoc->IsModified();
	pDoc->OnSaveDocument(outfile);
 
	// we open a new document file
 	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,pDoc->csSchluessel,SCHLUESSEL_LINEAR,pDoc->fontSize,pDoc->fontFace);
 	CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->SetWindowPlacement( &place );
 	remove(outfile);
 	NewDoc->SetTitle(pDoc->GetTitle());
 	NewDoc->CWndVaterFenster = pDoc->CWndVaterFenster;
 	NewDoc->hWndVaterFenster = pDoc->hWndVaterFenster;
 	NewDoc->SetModifiedFlag(Modified);
 	pDoc->OnCloseDocument();

	// this is necessary to deal with a ScintillaView-related quirk
	NewDoc->SendInitialUpdate();
}

BOOL CHexEditCtrlView::OnCommand( WPARAM wParam, LPARAM lParam )
{
    if (HIWORD(wParam)==HEN_CHANGE)
    {
        this->GetDocument()->SetModifiedFlag();
    }
    return CWnd::OnCommand( wParam, lParam );
}

void CHexEditCtrlView::OnEditFind() 
{
	// make the find and replace dialog visible
	theApp.findAndReplaceDialog.show();
}

/////////////////////////////////////
// @mfunc menu check handler - set indicator for overstrike mode
// @rvalue void | not used
//
void CHexEditCtrlView::OnUpdateInsert(
                                       CCmdUI* pCmdUI) //@parm menu handle
{
	CString strText;
	if (!m_cHexEdit.IsInsert())
		strText.LoadString(ID_INDICATOR_OVR);
	pCmdUI->SetText(strText);
}

/////////////////////////////////////
// @mfunc menu check handler - set indicator for line number
// @rvalue void | not used
//
void CHexEditCtrlView::OnUpdateLine(
                                       CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->Enable(); 
	CString strText;
	unsigned int pos = m_cHexEdit.GetCurrentAddress();
	unsigned int bpr = m_cHexEdit.GetBytesPerRow();
	unsigned int line = pos / bpr;
	unsigned int col = pos % bpr;
	strText.Format(ID_INDICATOR_LINE, line+1, col+1, pos+1);
	pCmdUI->SetText(strText);
}

/////////////////////////////////////
// @mfunc menu handler - undo last action if possible
// @rvalue void | not used
//
void CHexEditCtrlView::OnEditUndo() 
{
	m_cHexEdit.Undo();
}
/////////////////////////////////////
// @mfunc menu check handler - check if there is an action to undo
// @rvalue void | not used
//
void CHexEditCtrlView::OnUpdateEditUndo(
                                         CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->Enable(m_cHexEdit.CanUndo());
}


/////////////////////////////////////
// @mfunc menu handler - redo last undone action
// @rvalue void | not used
//
void CHexEditCtrlView::OnEditRedo() 
{
	m_cHexEdit.Redo();
}

/////////////////////////////////////
// @mfunc menu check handler - check if there is an action to redo
// @rvalue void | not used
//
void CHexEditCtrlView::OnUpdateEditRedo(
                                         CCmdUI* pCmdUI) //@parm menu handle
{
	pCmdUI->Enable(m_cHexEdit.CanRedo());
}

