//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgFortschritt.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowProgress 


CDlgShowProgress::CDlgShowProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowProgress::IDD, pParent)
{
	m_canceled=0;
	m_displayed=0;
	m_pos=-1;
	//{{AFX_DATA_INIT(CDlgShowProgress)
	m_text = _T("");
	//}}AFX_DATA_INIT
}


void CDlgShowProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowProgress)
	DDX_Control(pDX, IDC_TEXT, m_text_ctl);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Text(pDX, IDC_TEXT, m_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowProgress, CDialog)
	//{{AFX_MSG_MAP(CDlgShowProgress)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowProgress 

int CDlgShowProgress::Set(int pos)
{
	int t;

/*	if(m_pos==-1) {
		return -1;
	}*/
	t = m_pos;
	m_pos = pos;
	return t;
}

int CDlgShowProgress::Set(int pos, CString format)
{
	Format = format;
	return Set(pos);
}

BOOL CDlgShowProgress::OnInitDialog() 
{
	char line[256];

	Lock.Lock();
	CDialog::OnInitDialog();

	m_Progress.SetRange(0,100);
	SetWindowText(Title);
	sprintf(line, Format, m_pos);
	m_text = line;
	m_pos = 0;
	m_old_pos=-1;
	m_displayed=1;
	m_canceled = 0;
	SetTimer(43,200,NULL);
	Lock.Unlock();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgShowProgress::OnCancel() 
{
	Lock.Lock();
	KillTimer(43);
	m_pos=-1;	
	m_canceled=1;
	CDialog::OnCancel();
	DestroyWindow();
	m_displayed=0;
	Lock.Unlock();
}


int CDlgShowProgress::Set(int pos, CString caption, CString format)
{
	Title=caption;
	m_canceled = 0;
	return Set(pos, format);
}

void CDlgShowProgress::OnTimer(UINT nIDEvent) 
{
	char line[256];

	if(nIDEvent ==43) {
		if(m_displayed==0) return;
		Lock.Lock();
		if((m_pos==-1) || (m_old_pos == m_pos)) {
			Lock.Unlock();
			return;
		}
		m_old_pos = m_pos;
		m_Progress.SetPos(m_pos);
		theApp.DoWaitCursor(0);
		sprintf(line, Format, m_pos);
		m_text_ctl.SetWindowText(line);
		theApp.DoWaitCursor(0);
		Lock.Unlock();
		return;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgShowProgress::cancel()
{
	if(m_displayed)
		PostMessage(WM_COMMAND,IDCANCEL,NULL);
}

void CDlgShowProgress::Display(const char * title)
{
	while(m_displayed) Sleep(100);
	Set(0,title,"");
	theApp.m_MainWnd->PostMessage(WM_TIMER,44,NULL); /* oeffnet das Fenster modal im Hauptthread */
	while(!m_displayed) Sleep(100); /* wartet bis das Fenster existiert */
} 