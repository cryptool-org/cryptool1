/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_
