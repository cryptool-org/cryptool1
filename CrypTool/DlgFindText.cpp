// DlgFindText.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgFindText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFindText 


CDlgFindText::CDlgFindText(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFindText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFindText)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgFindText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFindText)
	DDX_Control(pDX, IDC_EDIT1, m_CtrlSearchText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFindText, CDialog)
	//{{AFX_MSG_MAP(CDlgFindText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgFindText 

void CDlgFindText::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	long ttf_length = m_CtrlSearchText.GetWindowTextLength()+1;
	str_ttf = new char[ttf_length];
	m_CtrlSearchText.GetWindowText(str_ttf, ttf_length);
	CDialog::OnOK();
}
