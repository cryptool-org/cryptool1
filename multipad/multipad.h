//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// multipad.h : main header file for the Multipad application
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"
#include "PlotDoc.h"
#include "DlgFortschritt.h"
#include "OptionsDialog.h"	// Hinzugefügt von ClassView
#include "TextOptions.h"
#include "MyDocument.h"
#include "MyEditView.h"
#include "SecudeLib.h"	// Hinzugefügt von ClassView


// globale Variablen fuer Zugriff auf Stringtable
// Definiert in multipad.cpp
#define STR_LAENGE_STRING_TABLE 1000
extern char pc_str[STR_LAENGE_STRING_TABLE];
extern char pc_str1[STR_LAENGE_STRING_TABLE];
extern char *initializing_file;

extern int iHillSchluesselDim;
extern int iHillSchluesselFensterGroesse;
#define HILL_SCHLUESSEL_KLEIN	1
#define HILL_SCHLUESSEL_GROSS	2

extern HWND hWndAktivesFenster;

#define SCHLUESSEL_INIT			0
#define SCHLUESSEL_LINEAR		1
#define SCHLUESSEL_QUADRATISCH	2


class CMultiPadApp : public CWinApp
{
	BOOL InitInstance();
	//{{AFX_MSG(CMultiPadApp)
	afx_msg void OnAppAbout();
	afx_msg void OnOptionsAnalysis();
	afx_msg void OnWindowCloseAll();
	afx_msg void OnOpttext();
	afx_msg void OnUpdateNeedSecudeTicket(CCmdUI* pCmdUI);
	afx_msg void OnShowKeys();
	afx_msg void OnKeyGen();

	afx_msg void OnEinzelverfahrenTutorialPrimzahlengenerieren();
	afx_msg void OnEinzelverfahrenTutorialRsaalgorithmus();
	afx_msg void OnEinzelverfahrenTutorialfrkleinezahlenFaktorisieren();
	afx_msg void OnEinzelverfahrenSchluesselgenerieren();
	afx_msg void OnGenRandomData();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_HexFormat;
	CSecudeLib SecudeLib;
	int SecudeStatus;
	CTextOptions TextOptions;
	void ThreadOpenDocumentFileNoMRU( const char *name, const char *title, char *Key=NULL, int KeyType = SCHLUESSEL_LINEAR);
	char OpenTitle[128];
	int OpenBGFlag;
	char OpenPath[128];
	// Zwei globale Variablen, die fuer das Durchreichen des Schluessels von der Funktion 
	// ThreadOpenDocumentFileNoMRU zur Funktion OpenDocumentFileNoMRU benoetigt werden.
	// Der Pfad der Datei (Openpath)
	CString KeyOpenDocumentFile;
	int KeyTypeOpenDocumentFile;
//	CCritSec OpenLock;
	DlgFortschritt fs;
	OptionsDialog Options;
	plot_opt_dlg PlotOptions;
	CMyDocument * OpenDocumentFileNoMRU(const char *name, CString Key = "", int KeyType = SCHLUESSEL_LINEAR);
	BOOL WriteProfileDouble( LPCTSTR lpszSection, LPCTSTR lpszEntry, double Value );
	BOOL MRU_Flag;
	CWnd *m_MainWnd;
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);
private:
	virtual int ExitInstance();
};

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)
	CStatusBar  m_StatusBar;
	CToolBar    m_ToolBar;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOptionsPlot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPadDoc : public CMyDocument
{
	DECLARE_DYNCREATE(CPadDoc)
	void Serialize(CArchive& ar);
	//{{AFX_MSG(CPadDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
extern CMultiPadApp NEAR theApp;
