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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Plotview.cpp : implementation of the CPlotview class
//

#include "stdafx.h"
#include "CrypToolApp.h"

#include "CPlotDocument.h"
#include "PlotView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPlotview

IMPLEMENT_DYNCREATE(CPlotView, CView)

BEGIN_MESSAGE_MAP(CPlotView, CView)
	//{{AFX_MSG_MAP(CPlotView)
	ON_COMMAND(ID_GOTO_VATER, OnGotoVater)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlotView construction/destruction

CPlotView::CPlotView()
{
	// TODO: add construction code here

}

CPlotView::~CPlotView()
{
}

BOOL CPlotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPlotView drawing

void CPlotView::OnDraw(CDC* pDC)
{
	TEXTMETRIC tm;
	int y_offset;
	CRect rectClient;
	ValueType *anItem;
	int OldBkMode;
	int x, ystart, ymin, ymax, yend, xnew, ynew;
	
	CPlotDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
/*
	CPen newPen(PS_SOLID, pDoc->m_bar_width, (COLORREF) 0);
	CPen *oldPen = pDC->SelectObject(&newPen);
*/
	OldBkMode = pDC->SetBkMode(TRANSPARENT);

	// prepare units
	if(pDC->IsPrinting()) {
		pDC->SetMapMode(MM_ANISOTROPIC);
		pDC->SetWindowExt(LOG_DISPL_DIM_X, LOG_DISPL_DIM_Y);
		pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX)*6,-pDC->GetDeviceCaps(LOGPIXELSY)*4);
		pDC->SetViewportOrg(pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY)*5);
	}
	else {
		GetClientRect(rectClient);
		pDC->SetMapMode(MM_ANISOTROPIC);
		pDC->SetWindowExt(LOG_DISPL_DIM_X, LOG_DISPL_DIM_Y);
		pDC->SetViewportExt(rectClient.right, -rectClient.bottom);
		pDC->SetViewportOrg(rectClient.left, rectClient.bottom);
	}

	pDC->MoveTo(X_LEFT - PIN_LEN, Y_BOTTOM - PIN_LEN);
	pDC->LineTo(X_LEFT - PIN_LEN, LOG_DISPL_DIM_Y - Y_TOP + PIN_LEN);
	pDC->LineTo(LOG_DISPL_DIM_X - X_RIGHT + PIN_LEN, LOG_DISPL_DIM_Y - Y_TOP + PIN_LEN);
	pDC->LineTo(LOG_DISPL_DIM_X - X_RIGHT + PIN_LEN, Y_BOTTOM - PIN_LEN);
	pDC->LineTo(X_LEFT - PIN_LEN, Y_BOTTOM - PIN_LEN);

//	pDC->Rectangle(CRect(X_LEFT - PIN_LEN, Y_BOTTOM - PIN_LEN, LOG_DISPL_DIM_X - X_RIGHT + PIN_LEN, LOG_DISPL_DIM_Y - Y_TOP + PIN_LEN));

	
// draw the diagram curve
	pDoc->m_ValueList.SetFirstItem();

	// neuer Zeichnungscode
	if(pDoc->m_continuous == 1){
		CPen newPen(PS_SOLID, pDoc->m_curve_width, (COLORREF) 0);
		CPen *oldPen = pDC->SelectObject(&newPen);

		if(pDoc->m_ValueList.GetNextItem(&anItem)) {
			x = anItem->aPoint.x;
			ystart = ymin = ymax = yend = anItem->aPoint.y;

			while(pDoc->m_ValueList.GetNextItem(&anItem)) {
				xnew = anItem->aPoint.x;
				ynew = anItem->aPoint.y;
				if(xnew != x) { // Linie Zeichnen!
					if(ymin != ymax) { // senkrechte Linie zeichnen
						pDC->MoveTo(x,ymin);
						pDC->LineTo(x,ymax);
					}
					pDC->MoveTo(x,yend);
					pDC->LineTo(xnew,ynew);

					x = xnew;
					ystart = ymin = yend = ymax = ynew;
				}
				else {
					ymin = min(ymin, ynew);
					ymax = max(ymax, ynew);
					yend = ynew;
				}
			}
			// lezten Balken zeichnen
			pDC->MoveTo(x,ymin);
			pDC->LineTo(x,ymax);
		}

		pDC->SelectObject(oldPen);
	} else {
		CPen newPen(PS_SOLID, pDoc->m_bar_width, (COLORREF) 0);
		CPen *oldPen = pDC->SelectObject(&newPen);

		if(pDoc->m_ValueList.GetNextItem(&anItem)) {
			x = anItem->aPoint.x;
			ymax = anItem->aPoint.y;

			while(pDoc->m_ValueList.GetNextItem(&anItem)) {
				xnew = anItem->aPoint.x;
				ynew = anItem->aPoint.y;
				if(xnew != x) { // Balken Zeichnen!
					pDC->MoveTo(x,ymax);
					pDC->LineTo(x, Y_BOTTOM - PIN_LEN/2);

					x = xnew;
					ymax = ynew;
				}
				else {
					ymax = max(ymax, ynew);
				}
			}
			// lezten Balken zeichnen
			pDC->MoveTo(x,ymax);
			pDC->LineTo(x, Y_BOTTOM - PIN_LEN/2);
		}
		pDC->SelectObject(oldPen);
	}
// draw the axis pins	


	pDoc->m_AxisList.SetFirstItem();
	
	while(pDoc->m_AxisList.GetNextItem(&anItem)) {
		pDC->MoveTo((int)anItem->x, (int)anItem->y);
		pDC->LineTo(anItem->aPoint);
	}

// draw the axis values
	y_offset = 0;
	pDC->GetTextMetrics(&tm);
	pDoc->m_TextList.SetFirstItem();
	pDC->SetTextAlign(TA_CENTER | TA_TOP); // first draw all center aligned text

	while(pDoc->m_TextList.GetNextItem(&anItem)) {
		if(anItem->y) {pDC->SetTextAlign(TA_RIGHT), y_offset = (tm.tmHeight + tm.tmExternalLeading)/2;} // look for right aligned things
		pDC->TextOut(anItem->aPoint.x, anItem->aPoint.y + y_offset, anItem->aString, (int)anItem->x);
	}

// draw headline and labels
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);	
	pDC->TextOut(LOG_DISPL_DIM_X/2, LOG_DISPL_DIM_Y - Y_TOP/2, pDoc->m_headline, pDoc->m_headline.GetLength());
	pDC->SetTextAlign(TA_RIGHT | TA_TOP);	
	pDC->TextOut(LOG_DISPL_DIM_X - X_RIGHT, Y_BOTTOM/2, pDoc->m_xlabel, pDoc->m_xlabel.GetLength());
	pDC->SetTextAlign(TA_LEFT | TA_BASELINE);	
	pDC->TextOut(TEXT_DIST, LOG_DISPL_DIM_Y - Y_TOP + TEXT_DIST, pDoc->m_ylabel, pDoc->m_ylabel.GetLength());

	
	pDC->SetBkMode(OldBkMode);

}

/////////////////////////////////////////////////////////////////////////////
// CPlotView printing

BOOL CPlotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPlotView diagnostics

#ifdef _DEBUG
void CPlotView::AssertValid() const
{
	CView::AssertValid();
}

void CPlotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlotDocument* CPlotView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlotDocument)));
	return (CPlotDocument*)m_pDocument;
}
#endif //_DEBUG



void CPlotView::OnGotoVater() 
{
	// TODO: Code für Befehlsbehandlungsroutine hier einfügen
	
	// Sprung zum Fenster, sofern es noch geöffnet ist
	if ( IsWindow(((CAppDocument*)GetDocument())->hWndVaterFenster) )
	{
		((CMDIFrameWnd*)theApp.m_pMainWnd)->
			MDIActivate(((CAppDocument*)GetDocument())->CWndVaterFenster);
	}
}

void CPlotView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
	CMenu KontextMenu;
	KontextMenu.LoadMenu(IDR_CONTEXT_MENU_PLOT);

	if(!IsWindow(((CAppDocument*)GetDocument())->hWndVaterFenster))
	{
        KontextMenu.EnableMenuItem(ID_GOTO_VATER, MF_GRAYED);
	}

	KontextMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}
