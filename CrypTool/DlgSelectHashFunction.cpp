// SelctAHashfunction.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSelectHashFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHashFunction 


CDlgSelectHashFunction::CDlgSelectHashFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectHashFunction::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectHashFunction)
	m_selectedHashFunction = 0;
	//}}AFX_DATA_INIT
}


void CDlgSelectHashFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectHashFunction)
	DDX_Radio(pDX, IDC_RADIO1, m_selectedHashFunction);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectHashFunction, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectHashFunction)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSelectHashFunction 
