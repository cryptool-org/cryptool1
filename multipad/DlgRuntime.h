#if !defined(AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRuntime.h : Header-Datei
//

#include <afxmt.h>
#include "CryptologyUsingMiracl.h"	// Hinzugef�gt von der Klassenansicht

#define THREAD_RUNNING			0x01
#define THREAD_REQUEST_ABORT	0x02
#define THREAD_FACTORIZED		0x04
#define THREAD_SUSPENDED		0x08
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRuntime 

class CDlgRuntime : public CDialog
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
	TutorialFactorisation *(m_Factorisations[5]);
	int m_timeout;
	int m_numThreads;
	int m_curThread;
	CString m_Caption;
	void SetCaption( const char * Caption );
	CDlgRuntime(CWnd* pParent = NULL);   // Standardkonstruktor
	int m_displayed;
    void Display(const char * title, int totalThreads);

// Dialogfelddaten
	//{{AFX_DATA(CDlgRuntime)
	enum { IDD = IDD_TEST };
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


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgRuntime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRuntime)
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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_
