/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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
// HexEditCtrlDoc.cpp : implementation of the CHexEditCtrlDoc class
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// includes
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "HexEditCtrlDoc.h"
#include "HexEditCtrlView.h"



/////////////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DOC_EMPTY_STR	"this is an empty document... open a  file!"

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// class CHexEditCtrlDoc
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CHexEditCtrlDoc, CCryptDoc)

BEGIN_MESSAGE_MAP(CHexEditCtrlDoc, CCryptDoc)
	//{{AFX_MSG_MAP(CHexEditCtrlDoc)
	ON_COMMAND(ID_TOTXT, OnTotxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CHexEditCtrlDoc::CHexEditCtrlDoc() : m_pData(NULL), m_nSize(0)
{ 
}

CHexEditCtrlDoc::~CHexEditCtrlDoc()
{
	delete []m_pData;
}

BOOL CHexEditCtrlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	delete []m_pData;
	m_nSize = strlen(DOC_EMPTY_STR)+1;
	m_pData = new BYTE[m_nSize];
	strcpy((char*)m_pData, DOC_EMPTY_STR);
	return TRUE;
}

void CHexEditCtrlDoc::Serialize(CArchive& ar)
{
	POSITION p = GetFirstViewPosition();
	CHexEditCtrlView *view = (CHexEditCtrlView*)GetNextView(p);
	view->GetHexEditCtrl().Serialize(ar);
}

#ifdef _DEBUG
void CHexEditCtrlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHexEditCtrlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CHexEditCtrlDoc::OnTotxt() 
{
	CAppDocument *NewDoc;
 	char outfile[128];
 	BOOL Modified;
 	WINDOWPLACEMENT place;
  
 	GetTmpName(outfile,"cry",".txt");
 	
 	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->GetWindowPlacement( &place );
 	Modified = IsModified();
 	OnSaveDocument(outfile);
 
 	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,csSchluessel);
 	CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->SetWindowPlacement( &place );
 	remove(outfile);
 	NewDoc->SetTitle(GetTitle());
 	NewDoc->CWndVaterFenster = CWndVaterFenster;
 	NewDoc->hWndVaterFenster = hWndVaterFenster;
 	NewDoc->SetModifiedFlag(Modified);
 	OnCloseDocument();
}
