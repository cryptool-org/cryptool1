// ScintillaDoc.cpp : Implementierung der Klasse CScintillaDoc
//

#include "stdafx.h"
//#include "Scintillamfc.h"
#include "ScintillaDoc.h"
#include "ScintillaView.h"
#include "ScintillaWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScintillaDoc

#if 0
IMPLEMENT_DYNCREATE(CScintillaDoc, CDocument)

BEGIN_MESSAGE_MAP(CScintillaDoc, CDocument)
	//{{AFX_MSG_MAP(CScintillaDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#else
IMPLEMENT_DYNCREATE(CScintillaDoc, CCryptDoc)

BEGIN_MESSAGE_MAP(CScintillaDoc, CCryptDoc)
	//{{AFX_MSG_MAP(CScintillaDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#endif
/////////////////////////////////////////////////////////////////////////////
// CScintillaDoc Konstruktion/Destruktion

CScintillaDoc::CScintillaDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CScintillaDoc::~CScintillaDoc()
{
}

BOOL CScintillaDoc::OnNewDocument()
{
	// call base class method (see CCryptDoc implementation for details)
	if(!CCryptDoc::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CScintillaDoc Serialisierung

void CScintillaDoc::Serialize(CArchive& ar)
{
	POSITION p = GetFirstViewPosition();
	CScintillaView *view = (CScintillaView*)GetNextView(p);
	view->GetEditControl()->Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CScintillaDoc Diagnose

#ifdef _DEBUG
void CScintillaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScintillaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScintillaDoc Befehle
#if 0
BOOL CScintillaDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// call base class method (see CCryptDoc implementation for details)
	if(!CCryptDoc::OnOpenDocument(lpszPathName))
		return FALSE;	
	
	return TRUE;
}

BOOL CScintillaDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{  
   POSITION pos = GetFirstViewPosition();
   CScintillaView *pFirstView = (CScintillaView*)GetNextView( pos ); // assume only one view
   if (pFirstView != NULL)
      return pFirstView->Save(lpszPathName);
	return CDocument::OnSaveDocument(lpszPathName);
}
#endif