// MyEditView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "MyEditView.h"
#include "SchluesselAusgabeLinear.h"
#include "HillSchluesselAusgabe.h"
#include "HillSchluesselAusgabeGross.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEditView

IMPLEMENT_DYNCREATE(CMyEditView, CEditView)

CMyEditView::CMyEditView()
{
}

CMyEditView::~CMyEditView()
{
}


BEGIN_MESSAGE_MAP(CMyEditView, CEditView)
	//{{AFX_MSG_MAP(CMyEditView)
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_GOTO_VATER, OnGotoVater)
	ON_COMMAND(ID_SHOW_KEY, OnShowKey)
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CMyEditView 

void CMyEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einf¸gen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CMyEditView

#ifdef _DEBUG
void CMyEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f¸r Nachrichten CMyEditView 


// Zum Sprung zum Vaterfenster ist es notwendig, daﬂ wir uns die windowHandle merken.
void CMyEditView::OnKillFocus(CWnd* pNewWnd) 
{
	// Dies muss vorher gemacht werden, damit das Fenster noch den Eingabefokus hat,
	// um die Fenster Handle speichern zu koennen.
	hWndAktivesFenster = m_hWnd;

	CEditView::OnKillFocus(pNewWnd);
	
	// TODO: Code f¸r die Behandlungsroutine f¸r Nachrichten hier einf¸gen
	
}

void CMyEditView::OnGotoVater() 
{
	// TODO: Code f¸r Befehlsbehandlungsroutine hier einf¸gen

	// Sprung zum Fenster, sofern es noch geˆffnet ist
	if ( IsWindow(((CMyDocument*)GetDocument())->hWndVaterFenster) )
	{
		((CMDIFrameWnd*)theApp.m_pMainWnd)->
			MDIActivate(((CMyDocument*)GetDocument())->CWndVaterFenster);
	}
}

void CMyEditView::OnShowKey() 
{
	// TODO: Code f¸r Befehlsbehandlungsroutine hier einf¸gen

	CString Key = ((CMyDocument*)GetDocument())->csSchluessel;

	if ( Key.GetLength() > 0 )
	{
		if ( ((CMyDocument*)GetDocument())->iSchluesselTyp == SCHLUESSEL_LINEAR )
		{
			CSchluesselAusgabeLinear AusgabeFenster;
			
			AusgabeFenster.m_Key = Key;

			// Fenster anzeigen
			AusgabeFenster.DoModal();
		}
		else if ( ((CMyDocument*)GetDocument())->iSchluesselTyp == SCHLUESSEL_QUADRATISCH )
		{
			// Hill Verfahren: 
			// Format des Schluessels: Zeilenweise, durch jeweils ein Leerzeichen getrennt
			// HILL_MAX_DIM=5: 5x5 hat also 25+4=29 Zeichen
			if (Key.GetLength() <= HILL_MAX_DIM*HILL_MAX_DIM+(HILL_MAX_DIM-1))
			{
				CHillSchluesselAusgabe AusgabeFenster;

				AusgabeFenster.SchluesselAnzeigen(Key);
				
				// Es wird immer der Schluessel zum Verschluesseln angezeigt
				AusgabeFenster.m_decrypt = FALSE;
				
				// Fenster anzeigen
				AusgabeFenster.DoModal();
			}
			else
			{
				CHillSchluesselAusgabeGross AusgabeFenster;

				AusgabeFenster.SchluesselAnzeigen(Key);
				
				// Es wird immer der Schluessel zum Verschluesseln angezeigt
				AusgabeFenster.m_decrypt = FALSE;
				
				// Fenster anzeigen
				AusgabeFenster.DoModal();
			}
		}
		else
		{
			ASSERT(false);
		}
	}
}


void CMyEditView::SerializeRaw(CArchive & ar)
{
	CEditView::SerializeRaw( ar );
}

void CMyEditView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Code f¸r die Behandlungsroutine f¸r Nachrichten hier einf¸gen

	// Es ist nicht moeglich, die Zustaende des Anwendungsmenues abzulesen, und diese
	// dann als Zustaende fuer das Kontextmenue zu verwenden, da die Zustaende der 
	// Befehle des Anwendungsmenues erst nach Oeffnen des Menues aktualisiet werden. 
	// Deshalb wurde die Aktivierung/Deaktivierung von Menuepunktenn zu Fuﬂ gemacht.
	// Die folgenden Funktionen stammen aus DevStudion\Vc\mfc\src\VIEWEDIT.CPP
	// void CEditView::OnUpdateNeedSel(CCmdUI* pCmdUI)
	// void CEditView::OnUpdateNeedClip(CCmdUI* pCmdUI)
	// void CEditView::OnUpdateNeedText(CCmdUI* pCmdUI)
	// (void CEditView::OnUpdateNeedFind(CCmdUI* pCmdUI))
	// void CEditView::OnUpdateEditUndo(CCmdUI* pCmdUI)

	// Kontextmenue laden
	CMenu KontextMenu;
	KontextMenu.LoadMenu(IDR_CONTEXT_MENU);

	// Ist kein Text markiert ?
	int nStartChar, nEndChar;
	GetEditCtrl().GetSel(nStartChar, nEndChar);
	if (nStartChar == nEndChar)
	{
		// Ausschneiden, Kopieren und Loeschen deaktivieren
		KontextMenu.EnableMenuItem(ID_EDIT_CUT, MF_GRAYED);
		KontextMenu.EnableMenuItem(ID_EDIT_COPY, MF_GRAYED);
		KontextMenu.EnableMenuItem(ID_EDIT_CLEAR, MF_GRAYED);
	}

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

	// Ist Rueckgaengig machen nicht moeglich ?
	if (! GetEditCtrl().CanUndo())
	{
		KontextMenu.EnableMenuItem(ID_EDIT_UNDO, MF_GRAYED);
	}

	// Existiert das Vaterfenster nicht (mehr) ?
	if(!IsWindow(((CMyDocument*)GetDocument())->hWndVaterFenster))
	{
		// Sprung zum Vaterfenster deaktivieren
        KontextMenu.EnableMenuItem(ID_GOTO_VATER, MF_GRAYED);
	}
	
	// Gibt es keinen Schluessel ?
	if(((CMyDocument*)GetDocument())->csSchluessel.GetLength() == 0)
	{
		// Schleussel anzeigen deaktivieren
        KontextMenu.EnableMenuItem(ID_SHOW_KEY, MF_GRAYED);
	}

	// Und schliesslich das Kontextmenue anzeigen
	KontextMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}


void CMyEditView::OnSetFocus(CWnd* pOldWnd) 
{
	CEditView::OnSetFocus(pOldWnd);
	
	// Zum Sprung zum Vaterfenster ist es notwendig, daﬂ wir uns die windowHandle merken.
	// Dies muss nach OnSetFocus gemacht werden, damit das Fenster den Eingabefokus hat,
	// um die Fenster Handle speichern zu koennen.
	hWndAktivesFenster = m_hWnd;
}
