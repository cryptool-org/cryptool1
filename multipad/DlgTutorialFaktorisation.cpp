// DlgTutorialFaktorisation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgTutorialFaktorisation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgTutorialFaktorisation 


DlgTutorialFaktorisation::DlgTutorialFaktorisation(CWnd* pParent /*=NULL*/)
	: CDialog(DlgTutorialFaktorisation::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgTutorialFaktorisation)
		// HINWEIS: Der Klassen-Assistent f�gt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void DlgTutorialFaktorisation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgTutorialFaktorisation)
		// HINWEIS: Der Klassen-Assistent f�gt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgTutorialFaktorisation, CDialog)
	//{{AFX_MSG_MAP(DlgTutorialFaktorisation)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten DlgTutorialFaktorisation 
