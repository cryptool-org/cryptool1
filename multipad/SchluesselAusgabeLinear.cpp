// SchluesselAusgabeLinear.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "SchluesselAusgabeLinear.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSchluesselAusgabeLinear 


CSchluesselAusgabeLinear::CSchluesselAusgabeLinear(CWnd* pParent /*=NULL*/)
	: CDialog(CSchluesselAusgabeLinear::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSchluesselAusgabeLinear)
	m_Key = _T("");
	//}}AFX_DATA_INIT
}


void CSchluesselAusgabeLinear::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchluesselAusgabeLinear)
	DDX_Text(pDX, IDC_EDIT1, m_Key);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchluesselAusgabeLinear, CDialog)
	//{{AFX_MSG_MAP(CSchluesselAusgabeLinear)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSchluesselAusgabeLinear 
// Behandlungsroutinen für Nachrichten CSchluesselAusgabeLinear 
// Behandlungsroutinen für Nachrichten CSchluesselAusgabeLinear 
