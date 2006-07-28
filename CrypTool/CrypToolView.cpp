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


// MyEditView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "CrypToolView.h"
#include "Cryptography.h"
#include "DlgShowKey.h"
#include "DlgShowKeyHill5x5.h"
#include "DlgShowKeyHill10x10.h"
#include "ScintillaWnd.h"
#include "ScintillaDoc.h"
#include "ScintillaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCrypToolView

IMPLEMENT_DYNCREATE(CCrypToolView, CView)

CCrypToolView::CCrypToolView()
{
}

CCrypToolView::~CCrypToolView()
{
}


BEGIN_MESSAGE_MAP(CCrypToolView, CView)
	//{{AFX_MSG_MAP(CCrypToolView)
	ON_WM_KILLFOCUS()
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
#if 0
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_VIEW_ENDOFLINE, OnViewEndOfLine)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ENDOFLINE, OnUpdateViewEndOfLine)
	ON_COMMAND(ID_VIEW_LINEWRAP, OnViewLineWrap)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LINEWRAP, OnUpdateViewLineWrap)
	ON_COMMAND(ID_VIEW_WHITESPACE, OnViewWhitespace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WHITESPACE, OnUpdateViewWhitespace)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CCrypToolView 

void CCrypToolView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einfügen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CCrypToolView

#ifdef _DEBUG
void CCrypToolView::AssertValid() const
{
	CView::AssertValid();
}

void CCrypToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CCrypToolView 


// Zum Sprung zum Vaterfenster ist es notwendig, daß wir uns die windowHandle merken.
void CCrypToolView::OnKillFocus(CWnd* pNewWnd) 
{
	// Dies muss vorher gemacht werden, damit das Fenster noch den Eingabefokus hat,
	// um die Fenster Handle speichern zu koennen.
	hWndAktivesFenster = m_hWnd;

	CView::OnKillFocus(pNewWnd);
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
}

void CCrypToolView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen

	// Es ist nicht moeglich, die Zustaende des Anwendungsmenues abzulesen, und diese
	// dann als Zustaende fuer das Kontextmenue zu verwenden, da die Zustaende der 
	// Befehle des Anwendungsmenues erst nach Oeffnen des Menues aktualisiet werden. 
	// Deshalb wurde die Aktivierung/Deaktivierung von Menuepunktenn zu Fuß gemacht.
	// Die folgenden Funktionen stammen aus DevStudion\Vc\mfc\src\VIEWEDIT.CPP
	// void CRichEditView::OnUpdateNeedSel(CCmdUI* pCmdUI)
	// void CRichEditView::OnUpdateNeedClip(CCmdUI* pCmdUI)
	// void CRichEditView::OnUpdateNeedText(CCmdUI* pCmdUI)
	// (void CRichEditView::OnUpdateNeedFind(CCmdUI* pCmdUI))
	// void CRichEditView::OnUpdateEditUndo(CCmdUI* pCmdUI)

	// Kontextmenue laden
	CMenu KontextMenu;
	KontextMenu.LoadMenu(IDR_CONTEXT_MENU);

	// Befindet sich kein Text in der Zwischenablage ?
	if (! ::IsClipboardFormatAvailable(CF_TEXT))
	{
		// Einfuegen deaktivieren
		KontextMenu.EnableMenuItem(ID_EDIT_PASTE, MF_GRAYED);
	}

	// Befindet sich kein Text im Fenster ?
	if (GetWindowTextLength() == 0)
	{
		// Alles markieren deaktivieren
		KontextMenu.EnableMenuItem(ID_EDIT_SELECT_ALL, MF_GRAYED);
	}

	// Existiert das Vaterfenster nicht (mehr) ?
	if(!IsWindow(((CAppDocument*)GetDocument())->hWndVaterFenster))
	{
		// Sprung zum Vaterfenster deaktivieren
        KontextMenu.EnableMenuItem(ID_GOTO_VATER, MF_GRAYED);
	}
	
	// Gibt es keinen Schluessel ?
	if(((CAppDocument*)GetDocument())->csSchluessel.GetLength() == 0)
	{
		// Schleussel anzeigen deaktivieren
        KontextMenu.EnableMenuItem(ID_SHOW_KEY, MF_GRAYED);
	}

	// Und schliesslich das Kontextmenue anzeigen
	KontextMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}


void CCrypToolView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// Zum Sprung zum Vaterfenster ist es notwendig, daß wir uns die windowHandle merken.
	// Dies muss nach OnSetFocus gemacht werden, damit das Fenster den Eingabefokus hat,
	// um die Fenster Handle speichern zu koennen.
	hWndAktivesFenster = m_hWnd;

	// Fokus für neue Scintilla-Komponente explizit setzen
	GetTopWindow()->SetFocus();
}

/*
void CCrypToolView::OnViewEndOfLine()
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

void CCrypToolView::OnUpdateViewEndOfLine(CCmdUI* pCmdUI)
{
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
		pCmdUI->SetCheck(pActiveWindow->SendMessage(SCI_GETVIEWEOL));
}

void CCrypToolView::OnViewLineWrap()
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

void CCrypToolView::OnUpdateViewLineWrap(CCmdUI* pCmdUI)
{
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
		pCmdUI->SetCheck(pActiveWindow->SendMessage(SCI_GETWRAPMODE));
}

void CCrypToolView::OnViewWhitespace()
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

void CCrypToolView::OnUpdateViewWhitespace(CCmdUI* pCmdUI)
{
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
		pCmdUI->SetCheck(pActiveWindow->SendMessage(SCI_GETVIEWWS));
}
*/

BOOL CCrypToolView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CCrypToolView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CView::OnPrint(pDC, pInfo);
}

void CCrypToolView::OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
	CSize size;
	pDC->SetWindowOrg(-200,-200);
	size = pDC->GetWindowExt();
	size.cx -= 200;
	size.cy -= 200;
	pDC->SetWindowExt(size);
	CView::OnBeginPrinting( pDC, pInfo);
}

void CCrypToolView::find()
{
	// do nothing here...
}

void CCrypToolView::findAndReplace()
{
	// do nothing here...
}

void CCrypToolView::findAndReplaceAll()
{
	// do nothing here...
}
