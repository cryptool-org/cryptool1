// MyDocument.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "MyDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDocument

IMPLEMENT_DYNCREATE(CMyDocument, CDocument)

CMyDocument::CMyDocument()
{
	hWndVaterFenster = NULL;
	CWndVaterFenster = NULL;
}

BOOL CMyDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMyDocument::~CMyDocument()
{
}


BEGIN_MESSAGE_MAP(CMyDocument, CDocument)
	//{{AFX_MSG_MAP(CMyDocument)
	ON_UPDATE_COMMAND_UI(ID_GOTO_VATER, OnUpdateGotoVater)
	ON_UPDATE_COMMAND_UI(ID_SHOW_KEY, OnUpdateShowKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CMyDocument

#ifdef _DEBUG
void CMyDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialisierung CMyDocument 

void CMyDocument::Serialize(CArchive& ar)
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
// Befehle CMyDocument 

void CMyDocument::OnUpdateGotoVater(CCmdUI* pCmdUI) 
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

void CMyDocument::OnUpdateShowKey(CCmdUI* pCmdUI) 
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

void CMyDocument::SetData(int i)
{
}



