// MyDocument.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "AppDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppDocument

IMPLEMENT_DYNCREATE(CAppDocument, CDocument)

CAppDocument::CAppDocument()
{
	hWndVaterFenster = NULL;
	CWndVaterFenster = NULL;
}

BOOL CAppDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CAppDocument::~CAppDocument()
{
}


BEGIN_MESSAGE_MAP(CAppDocument, CDocument)
	//{{AFX_MSG_MAP(CAppDocument)
	ON_UPDATE_COMMAND_UI(ID_GOTO_VATER, OnUpdateGotoVater)
	ON_UPDATE_COMMAND_UI(ID_SHOW_KEY, OnUpdateShowKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CAppDocument

#ifdef _DEBUG
void CAppDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CAppDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialisierung CAppDocument 

void CAppDocument::Serialize(CArchive& ar)
{
	CObject::Serialize( ar );
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Code zum Speichern hier einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Code zum Laden hier einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// Befehle CAppDocument 

void CAppDocument::OnUpdateGotoVater(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
	if(IsWindow(hWndVaterFenster))
	{
        pCmdUI->Enable(TRUE);
	}
	else
	{
        pCmdUI->Enable(FALSE);
	}
}

void CAppDocument::OnUpdateShowKey(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
	if(csSchluessel.GetLength() > 0)
	{
        pCmdUI->Enable(TRUE);
	}
	else
	{
        pCmdUI->Enable(FALSE);
	}
}

void CAppDocument::SetData(int i)
{
}





