// DlgRuntime.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRuntime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRuntime 


CDlgRuntime::CDlgRuntime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRuntime::IDD, pParent)
{
	m_displayed = 0;
	m_Caption = _T("");
	//{{AFX_DATA_INIT(CDlgRuntime)
	m_TimeStr = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRuntime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRuntime)
	DDX_Text(pDX, IDC_EDIT1, m_TimeStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRuntime, CDialog)
	//{{AFX_MSG_MAP(CDlgRuntime)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRuntime 

void CDlgRuntime::Display(const char * title)
{
	while(m_displayed) Sleep(100);
	// theApp.m_MainWnd->PostMessage(WM_TIMER,46,NULL); // oeffnet das Fenster modal im Hauptthread 
	DoModal();
	while(!m_displayed) Sleep(100); // wartet bis das Fenster existiert 
} 


BOOL CDlgRuntime::OnInitDialog() 
{
	Lock.Lock();
	CDialog::OnInitDialog();
	zaehler = 0;
	SetTimer(45,200,NULL);
	m_displayed=1;
	if ( m_Caption != _T("") )
		SetWindowText( m_Caption );
	Lock.Unlock();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgRuntime::OnCancel() 
{
	Lock.Lock();
	KillTimer(45);
	CDialog::OnCancel();
	DestroyWindow();
	m_displayed=0;
	Lock.Unlock();
}


void CDlgRuntime::OnTimer(UINT nIDEvent) 
{
	char line[256];

	if(nIDEvent ==45) {
		if(m_displayed==0) return;
		{
			Lock.Lock();
			UpdateData(TRUE);
			char tmpStr[64];
			sprintf(tmpStr, "Zähler: %i", zaehler++);
			m_TimeStr = tmpStr;
			SetTimer(45,200,NULL);
			UpdateData(FALSE);
			Lock.Unlock();
		}
		return;
	}
	if(nIDEvent ==47) {
		if(m_displayed==0) return;
		{
			OnCancel();
		}
		return;
	}

	CDialog::OnTimer(nIDEvent);
}



void CDlgRuntime::cancel()
{
	if(m_displayed)
		PostMessage(WM_COMMAND,IDCANCEL,NULL);
}

void CDlgRuntime::SetCaption( const char * Caption)
{
	m_Caption = Caption;
}
