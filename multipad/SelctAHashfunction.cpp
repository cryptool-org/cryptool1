// SelctAHashfunction.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "SelctAHashfunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld SelctAHashfunction 


SelctAHashfunction::SelctAHashfunction(CWnd* pParent /*=NULL*/)
	: CDialog(SelctAHashfunction::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelctAHashfunction)
	m_selectedHashFunction = 0;
	//}}AFX_DATA_INIT
}


void SelctAHashfunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelctAHashfunction)
	DDX_Radio(pDX, IDC_RADIO1, m_selectedHashFunction);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelctAHashfunction, CDialog)
	//{{AFX_MSG_MAP(SelctAHashfunction)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten SelctAHashfunction 
