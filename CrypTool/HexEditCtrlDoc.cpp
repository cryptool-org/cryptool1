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


void CHexEditCtrlDoc::Serialize(CArchive& ar)
{
	POSITION p = GetFirstViewPosition();
	CHexEditCtrlView *view = (CHexEditCtrlView*)GetNextView(p);
	view->GetHexEditCtrl().Serialize(ar);
}

void CHexEditCtrlDoc::OnTotxt() 
{
	bHexEnabled = false;

	CAppDocument *NewDoc;
 	char outfile[128];
 	BOOL Modified;
 	WINDOWPLACEMENT place;
  
 	GetTmpName(outfile,"cry",".txt");
 	
 	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->GetWindowPlacement( &place );
 	Modified = IsModified();
 	OnSaveDocument(outfile);
 
 	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,csSchluessel,SCHLUESSEL_LINEAR,fontSize,fontFace);
 	CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();
 	CWnd_hilf->SetWindowPlacement( &place );
 	remove(outfile);
 	NewDoc->SetTitle(GetTitle());
 	NewDoc->CWndVaterFenster = CWndVaterFenster;
 	NewDoc->hWndVaterFenster = hWndVaterFenster;
 	NewDoc->SetModifiedFlag(Modified);
 	OnCloseDocument();
}
