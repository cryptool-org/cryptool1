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

#if !defined(AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRuntime.h : Header-Datei
//

#include <afxmt.h>
#include "IntegerArithmetic.h"	// Hinzugefügt von der Klassenansicht

#define THREAD_RUNNING			0x01
#define THREAD_REQUEST_ABORT	0x02
#define THREAD_FACTORIZED		0x04
#define THREAD_SUSPENDED		0x08
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgProgressFactorisation 

class CDlgProgressFactorisation : public CDialog
{
// Konstruktion
	CCriticalSection Lock;
	long zaehler;
public:
	int *m_iterVals[5];
	CButton *m_AButton[5];
	miracl *m_mip[5];
//	miracl *oldmip;
	int m_OldThread;
	int m_totalThreads;
	int m_registeredThreads;
	int ExitSchedule( int index );
	int Schedule( int index );
	int EnterSchedule( int index );
	int m_retcode;
	CTutorialFactorisation *(m_Factorisations[5]);
	int m_timeout;
	int m_numThreads;
	int m_curThread;
	CString m_Caption;
	void SetCaption( const char * Caption );
	CDlgProgressFactorisation(CWnd* pParent = NULL);   // Standardkonstruktor
	int m_displayed;
    void Display(const char * title, int totalThreads);

// Dialogfelddaten
	//{{AFX_DATA(CDlgProgressFactorisation)
	enum { IDD = IDD_PROGRESS_FACTORISATION };
	CButton	m_CQSieve;
	CButton	m_CLenstra;
	CButton	m_CWilliams;
	CButton	m_CPollard;
	CButton	m_CBrent;
	int		m_VPollard;
	int		m_VWilliams;
	int		m_VQSieve;
	int		m_VLenstra;
	int		m_VBrent;
	CString	m_zahl;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgProgressFactorisation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgProgressFactorisation)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnCancel2();
	afx_msg void OnCancel3();
	afx_msg void OnCancel4();
	afx_msg void OnCancel5();
	afx_msg void OnCancel6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int mTimerCancel;
	int mTimerSchedule;
	int mTimerDisplay;

	// flomar, October 2012: a few hackish helpers to enable the factorization demo to handle 
	// sequential factorizations (in other words: 'factorize all composite factors in one go');
	// for more details on the implementation, see function 'OnButtonVollstaendigFaktorisation'
	// in file 'DlgFactorisationDemo.cpp'
private:
	// indicates whether the factorization was aborted
	bool abortedFactorizationInOneGo;
public:
	// this must be called before starting the 'single go' factorization; as of now the 
	// only place this applies to is the function 'OnButtonVollstaendigFaktorisieren'
	void startFactorizationInOneGo() {
		abortedFactorizationInOneGo = false;
	}
	// this function is called from the outside to indicate the factorization was 
	// either aborted by the user or it was aborted due to some internal error
	void abortFactorizationInOneGo() {
		abortedFactorizationInOneGo = true;
	}
	// simple access function
	bool wasFactorizationInOneGoAborted() {
		return abortedFactorizationInOneGo;
	}
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_
