// SchluesselAusgabeLinear.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "SchluesselAusgabeLinear.h"
#include "crypt.h"

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
	DDX_Control(pDX, IDC_EDIT1, m_CtrlKey);
	DDX_Text(pDX, IDC_EDIT1, m_Key);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchluesselAusgabeLinear, CDialog)
	//{{AFX_MSG_MAP(CSchluesselAusgabeLinear)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSchluesselAusgabeLinear 


void CSchluesselAusgabeLinear::OnCopyKey() 
{
	//In der Zwischen Ablage kopieren
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CopyKey(strTitle, m_Key); 
	m_CtrlKey.SetSel(0,-1); 
	m_CtrlKey.Copy();
}

BOOL CSchluesselAusgabeLinear::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// if (s_alternativeWindowText[0])
	//	SetWindowText(s_alternativeWindowText);


	// TODO: Zusätzliche Initialisierung hier einfügen
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

int CSchluesselAusgabeLinear::DoModal() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	return CDialog::DoModal();
}


/*
void CSchluesselAusgabeLinear::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}
*/