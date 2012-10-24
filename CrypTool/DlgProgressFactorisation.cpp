/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

// DlgRuntime.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgProgressFactorisation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_IDNOSUCCESS 4
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgProgressFactorisation 


CDlgProgressFactorisation::CDlgProgressFactorisation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProgressFactorisation::IDD, pParent)
{
	int i;

	for(i=0;i<5;i++) m_mip[i] = NULL;
	m_displayed = 0;
	m_registeredThreads = 0;
	m_OldThread = -1;
	m_Caption = _T("");
	m_retcode = IDCANCEL;
	m_AButton[0] = &m_CBrent;
	m_AButton[1] = &m_CPollard;
	m_AButton[2] = &m_CWilliams;
	m_AButton[3] = &m_CLenstra;
	m_AButton[4] = &m_CQSieve;
	m_iterVals[0] = &m_VBrent;
	m_iterVals[1] = &m_VPollard;
	m_iterVals[2] = &m_VWilliams;
	m_iterVals[3] = &m_VLenstra;
	m_iterVals[4] = &m_VQSieve;
	//{{AFX_DATA_INIT(CDlgProgressFactorisation)
	m_VPollard = 0;
	m_VWilliams = 0;
	m_VQSieve = 0;
	m_VLenstra = 0;
	m_VBrent = 0;
	m_zahl = _T("");
	//}}AFX_DATA_INIT
}


void CDlgProgressFactorisation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProgressFactorisation)
	DDX_Control(pDX, IDCANCEL6, m_CQSieve);
	DDX_Control(pDX, IDCANCEL5, m_CLenstra);
	DDX_Control(pDX, IDCANCEL4, m_CWilliams);
	DDX_Control(pDX, IDCANCEL3, m_CPollard);
	DDX_Control(pDX, IDCANCEL2, m_CBrent);
	DDX_Text(pDX, IDC_EDIT2, m_VPollard);
	DDX_Text(pDX, IDC_EDIT3, m_VWilliams);
	DDX_Text(pDX, IDC_EDIT5, m_VQSieve);
	DDX_Text(pDX, IDC_EDIT4, m_VLenstra);
	DDX_Text(pDX, IDC_EDIT1, m_VBrent);
	DDX_Text(pDX, IDC_EDIT6, m_zahl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProgressFactorisation, CDialog)
	//{{AFX_MSG_MAP(CDlgProgressFactorisation)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL2, OnCancel2)
	ON_BN_CLICKED(IDCANCEL3, OnCancel3)
	ON_BN_CLICKED(IDCANCEL4, OnCancel4)
	ON_BN_CLICKED(IDCANCEL5, OnCancel5)
	ON_BN_CLICKED(IDCANCEL6, OnCancel6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgProgressFactorisation 

#if 0
void CDlgProgressFactorisation::Display(const char * title, int totalThreads)
{
	m_totalThreads = totalThreads;
	while(m_displayed) Sleep(100);
	// theApp.m_MainWnd->PostMessage(WM_TIMER,46,NULL); // oeffnet das Fenster modal im Hauptthread 
	DoModal();
	while(!m_displayed) Sleep(100); // wartet bis das Fenster existiert 
} 
#endif

BOOL CDlgProgressFactorisation::OnInitDialog() 
{
	int i;

	Lock.Lock();
	CDialog::OnInitDialog();
	for(i=0;i<5;i++)  {
		m_AButton[i]->EnableWindow(FALSE);
		*m_iterVals[i] = 0;
	}
	UpdateData(FALSE);
	zaehler = 0;
	m_displayed=1;
	if ( m_Caption != _T("") )
		SetWindowText( m_Caption );
	Lock.Unlock();
	while(m_totalThreads > m_registeredThreads) Sleep(2); 
	mTimerDisplay =  SetTimer(45,1000,NULL);
	if(m_totalThreads == 0) {
		EndDialog(m_retcode);
		return TRUE;
	}
	m_retcode = MY_IDNOSUCCESS;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgProgressFactorisation::OnCancel() 
{
	int i;

	Lock.Lock();
	for(i=0;i<5;i++)
		if(m_Factorisations[i]->status & THREAD_RUNNING)
			m_Factorisations[i]->status |= THREAD_REQUEST_ABORT;
	Lock.Unlock();
	m_retcode = IDCANCEL;
	// flomar, October 2012: please see comments in header file for details
	abortedFactorizationInOneGo = true;
}


void CDlgProgressFactorisation::OnTimer(UINT nIDEvent) 
{
	int i;

	if(nIDEvent == 45) { // display timer
		if(m_displayed==0) return;
		{
			Lock.Lock();
			UpdateData(TRUE);
			for(i=0;i<5;i++) {
				if((m_Factorisations[i]->status & (THREAD_RUNNING | THREAD_REQUEST_ABORT)) == THREAD_RUNNING) {
					m_AButton[i]->EnableWindow(TRUE);
					*m_iterVals[i] = m_Factorisations[i]->m_iterations;
				}
				else {
					*m_iterVals[i] = m_Factorisations[i]->m_iterations;
					m_AButton[i]->EnableWindow(FALSE);
				}
			}
			UpdateData(FALSE);
			Lock.Unlock();
		}
		return;
	}
	if(nIDEvent == 47) { // m_numThreads == 0
		if(m_displayed==0) return;
		{
			int t = m_retcode;
			KillTimer(mTimerCancel);
			m_curThread = 0; // FIXME Lock?
			m_numThreads = 0; 
			m_displayed = 0;
			m_OldThread = -1;
			m_registeredThreads = 0;
			// m_retcode = IDCANCEL;
			m_displayed = 0;
			EndDialog(t);
		}
		return;
	}
	if(nIDEvent == 49) { // Die Zeitscheibe des aktuellenThreads ist abgelaufen --> flag setzen
		m_timeout++;
	}
	CDialog::OnTimer(nIDEvent);
}


void CDlgProgressFactorisation::SetCaption( const char * Caption)
{
	m_Caption = Caption;
}


int CDlgProgressFactorisation::EnterSchedule(int index)
{
	m_Factorisations[index]->m_iterations = 0;
	m_Factorisations[index]->status = THREAD_RUNNING; // FIXME Lock required
	while(!m_displayed) Sleep(2);
	Lock.Lock();

	m_registeredThreads++;
	m_numThreads++;
	if(m_numThreads > 1){
		m_Factorisations[index]->status |= THREAD_SUSPENDED;
	}
	else { // first thread
//		oldmip = get_mip();
		m_curThread = index;
		mTimerSchedule = SetTimer(49, 10, NULL); // next schedule
		ASSERT(mTimerSchedule!=0);
	}
	Lock.Unlock();
	while(m_Factorisations[index]->status & THREAD_SUSPENDED) Sleep(1);
	if(m_OldThread != -1) { // FIXME Lock required?
		m_Factorisations[m_OldThread]->m_Thread->SuspendThread();
		m_OldThread = -1;
	}
//	mirsys(50,0);
//	m_Factorisations[index]->mip = m_mip[index] = get_mip();
	m_mip[index] = m_Factorisations[index]->mip;
	set_mip(m_mip[index]);
	if(m_Factorisations[index]->status & THREAD_REQUEST_ABORT) return 1;
	return 0;
}

int CDlgProgressFactorisation::Schedule(int index)
{
	ASSERT(index == m_curThread);
	if (m_Factorisations[index]->status & THREAD_REQUEST_ABORT) return 1;
	if(m_timeout < 10) return 0;
	m_timeout = 0;
	while(m_totalThreads > m_registeredThreads) Sleep(2); 
	Lock.Lock();
	if(m_numThreads > 1) {
		m_Factorisations[index]->status |= THREAD_SUSPENDED;
		m_OldThread = index;
		m_mip[index] = get_mip();
		do {
			m_curThread = (m_curThread+1) % 5;
			if(m_Factorisations[m_curThread]->status & THREAD_RUNNING) break;
		} while(1);
		Lock.Unlock();
		m_Factorisations[m_curThread]->status &= ~THREAD_SUSPENDED;
		m_Factorisations[m_curThread]->m_Thread->ResumeThread();
	}
	else {
		Lock.Unlock();
	}
	while(m_Factorisations[index]->status & THREAD_SUSPENDED) Sleep(1);
	if(m_OldThread != -1) { // FIXME Lock required?
		m_Factorisations[m_OldThread]->m_Thread->SuspendThread();
		m_OldThread = -1;
	}
	set_mip(m_mip[index]);
	if(m_Factorisations[index]->status & THREAD_REQUEST_ABORT) return 1;
	return 0;
}

int CDlgProgressFactorisation::ExitSchedule(int index)
{
	int i;

	ASSERT(index == m_curThread);
	m_Factorisations[index]->status &= ~THREAD_RUNNING;
	if(m_Factorisations[index]->status & THREAD_FACTORIZED) { // faktorisierung erfolgreich, alle anderen Threads abbrechen...
		m_retcode = IDOK;
		for(i=0;i<5;i++) {
			if(m_Factorisations[i]->status & THREAD_RUNNING) {
				m_Factorisations[i]->status |= THREAD_REQUEST_ABORT;
			}
		}
	}
	while(m_totalThreads > m_registeredThreads) Sleep(2); 
	ASSERT(m_registeredThreads == m_totalThreads);
	Lock.Lock();
	m_numThreads--;
	if((m_numThreads == 0) && (m_registeredThreads == m_totalThreads)) { // all threads exited, shutdown window
		KillTimer(mTimerSchedule);
		KillTimer(mTimerDisplay);
		mTimerCancel = SetTimer(47, 1, NULL); // terminate
		ASSERT(mTimerCancel!=0);
	}
	if(m_numThreads > 0) { // select new thread
		do {
			m_curThread = (m_curThread+1) % 5;
			if(m_Factorisations[m_curThread]->status & THREAD_RUNNING) break;
		} while(1);
		m_Factorisations[m_curThread]->status &= ~THREAD_SUSPENDED;
		m_Factorisations[m_curThread]->m_Thread->ResumeThread();
	}
	Lock.Unlock();
	return 0;
}

void CDlgProgressFactorisation::OnCancel2() //Brent
{
	m_Factorisations[0]->status |= THREAD_REQUEST_ABORT;
	if ( m_numThreads <= 1 ) m_retcode = IDCANCEL;
}

void CDlgProgressFactorisation::OnCancel3() // Pollard
{
	m_Factorisations[1]->status |= THREAD_REQUEST_ABORT;
	if ( m_numThreads <= 1 ) m_retcode = IDCANCEL;
}

void CDlgProgressFactorisation::OnCancel4() // Williams
{
	m_Factorisations[2]->status |= THREAD_REQUEST_ABORT;
	if ( m_numThreads <= 1 ) m_retcode = IDCANCEL;
}

void CDlgProgressFactorisation::OnCancel5() // Lensta
{
	m_Factorisations[3]->status |= THREAD_REQUEST_ABORT;
	if ( m_numThreads <= 1 ) m_retcode = IDCANCEL;
}

void CDlgProgressFactorisation::OnCancel6() // QSieve
{
	m_Factorisations[4]->status |= THREAD_REQUEST_ABORT;
	if ( m_numThreads <= 1 ) m_retcode = IDCANCEL;
}
