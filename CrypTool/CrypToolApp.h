//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// crypTool.h : main header file for the Multipad application
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

#ifndef __CRYPTOOL_H
#define __CRYPTOOL_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <deque>
#define deque std::deque
#include "resource.h"
#include "CPlotDocument.h"
#include "DlgShowProgress.h"
#include "DlgOptionsAnalysis.h"	// Hinzugefügt von ClassView
#include "DlgTextOptions.h"
#include "AppDocument.h"
#include "AppEditView.h"
#include "SecudeLib.h"	// Hinzugefügt von ClassView
#include "DlgSignatureDemo.h"

// globale Variablen fuer Zugriff auf Stringtable
// Definiert in CrypTool.cpp
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

#define CRYPTOOL_PATH_LENGTH				1024

class CCrypToolApp : public CWinApp
{
	BOOL InitInstance();
	
	BOOL m_menuItemWithSubMenuSelected; // true iff a menu item with sub menu is selected
	struct menuitem {
		HMENU hmenu;
		UINT index;
	};
	deque<menuitem> m_menuItemStack; // updated by PrecessMessageFilter,
									 // used by WinHelp to create unique IDs for menu items with sub menus
	virtual void updateMenuItemStack(HMENU hmenu,INT index); // utility for updating m_menuItemStack
	virtual void WinHelp( DWORD dwData, UINT nCmd = HELP_CONTEXT ); // overridden to handle F1 on menus with sub menus
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg); // overridden for tracking menu selection and updating m_menuItemStack
	
	//{{AFX_MSG(CCrypToolApp)
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
	afx_msg void OnHashOfAFile();
	afx_msg void OnEinzelverfahrenTutorialSignaturerzeugung();
	afx_msg void OnVerentschlsselnHybridverfahrenHybridverschlsselung();
	afx_msg void OnOptionsStartoptions();
	afx_msg void OnHilfeIndex();
	afx_msg void OnHilfeStartseite();
	afx_msg void OnHilfeSzenarien();
	afx_msg void OnSignaturAttack();
	afx_msg void OnOptionsFurtheroptions();
	afx_msg void OnEinzelverfahrenDiffiehellmandemo();
	afx_msg void OnSigattmodificdemo();
	afx_msg void OnLoadReadme();
	afx_msg void OnScript();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	char *m_Selfextract_EXE;
	int m_HexFormat;
	CSecudeLib SecudeLib;
	int SecudeStatus;
	CDlgTextOptions TextOptions;
	void ThreadOpenDocumentFileNoMRU( const char *name, const char *title, char *Key=NULL, int KeyType = SCHLUESSEL_LINEAR);
	char OpenTitle [CRYPTOOL_PATH_LENGTH];
	int OpenBGFlag;
	char OpenPath [CRYPTOOL_PATH_LENGTH];
	// Zwei globale Variablen, die fuer das Durchreichen des Schluessels von der Funktion 
	// ThreadOpenDocumentFileNoMRU zur Funktion OpenDocumentFileNoMRU benoetigt werden.
	// Der Pfad der Datei (Openpath)
	CString KeyOpenDocumentFile;
	int KeyTypeOpenDocumentFile;
//	CCritSec OpenLock;
	CDlgShowProgress fs;
	CDlgOptionsAnalysis Options;
	plot_opt_dlg PlotOptions;
	CAppDocument * OpenDocumentFileNoMRU(const char *name, CString Key = "", int KeyType = SCHLUESSEL_LINEAR);
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

class CPadDoc : public CAppDocument
{
	DECLARE_DYNCREATE(CPadDoc)
	void Serialize(CArchive& ar);
	//{{AFX_MSG(CPadDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
extern CCrypToolApp NEAR theApp;

/* *************************************************** 
   Die folgende Klasse wird im Quellcode bisher nicht verwendet,
   soll aber eine Alternative Für die Implementierung der Anzeige 
   der Sanduhr, während rechenaufwendiger Operationen in CrypTool
   aufzeigen:

   {  // in diesem Frame wird die Sanduhr angezeigt
      CHourGlass hourglass;

      // hier den Quellcode, während dessen die Sanduhr angezeigt wird.
   }

   *************************************************** */
class CHourGlass {
	 CHourGlass() { theApp.DoWaitCursor( 1); }
	~CHourGlass() { theApp.DoWaitCursor(-1); }
};

#define SHOW_HOUR_GLASS theApp.DoWaitCursor( 1);
#define HIDE_HOUR_GLASS theApp.DoWaitCursor(-1);

#endif
