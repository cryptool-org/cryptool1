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


// MyEditView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "CrypToolView.h"
#include "Cryptography.h"
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
	// flomar, 02/22/2012: the old implementation ("GetWindowTextLength") would always 
	// return zero for Scintilla documents; we use the Scintilla messaging API now to 
	// determine if a document is really empty or not
	CWnd *pActiveWindow = this->GetTopWindow();
	if(pActiveWindow)
	{
		if(pActiveWindow->SendMessage(SCI_GETLENGTH) == 0) {
			KontextMenu.EnableMenuItem(ID_EDIT_SELECT_ALL, MF_GRAYED);
		}
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
	CCryptDoc *pDoc = (CCryptDoc*)GetDocument();
	
	bool found = false;
	deque<void*>::iterator it = theApp.m_fileList.begin();
	while ( it != theApp.m_fileList.end() )
	{
		if ( pDoc == (CCryptDoc*)*it )
		{
			theApp.active = it;
			found = true;
			break;
		}
		it++;
	}
	if ( !found )
		theApp.m_fileList.push_back((void*)pDoc);
	
	int i = 0;
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
