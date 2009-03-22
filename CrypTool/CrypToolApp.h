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
#include "SecudeLib.h"	// Hinzugefügt von ClassView
#include "DlgSignatureDemo.h"
#include "DlgFindAndReplace.h"
#include <atlbase.h>   // Registry

#include "HillEncryption.h"

// globale Variablen fuer Zugriff auf Stringtable
// Definiert in CrypTool.cpp
#define STR_LAENGE_STRING_TABLE 1000
extern char pc_str[STR_LAENGE_STRING_TABLE];
extern char pc_str1[STR_LAENGE_STRING_TABLE];
extern char *initializing_file;

extern int iHillSchluesselDim;
extern int iHillSchluesselFensterGroesse;
extern CString sHillGlobalKey[HILL_MAX_DIM_GROSS][HILL_MAX_DIM_GROSS];
extern int iHillMultiplicationType;  //0: (matrix)*(column vector) 1:(row vector)*(matrix)
extern bool bHexEnabled;
extern bool bGlobVerbose;

extern CString sNotInFileChars;
extern int iClearTextAlphCharCount;
extern int iClearTextNotAlphCharCount;

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
	
	BOOL m_menuItemWithSubMenuSelected; // true if a menu item with sub menu is selected
	struct menuitem {
		HMENU hmenu;
		UINT index;
	};
	deque<menuitem> m_menuItemStack; // updated by PrecessMessageFilter,
									 // used by WinHelp to create unique IDs for menu items with sub menus
	virtual void updateMenuItemStack(HMENU hmenu,INT index); // utility for updating m_menuItemStack

	// virtual void WinHelp( DWORD dwData, UINT nCmd = HELP_CONTEXT ) set public to get access from Challenge Response Demo

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
	afx_msg void OnPresentation();
	afx_msg void OnEinzelverfahrenSidechannelattackOnHybridencryption();
	afx_msg void OnPasswordQualityMeter();
	afx_msg void OnPasswordEntropy();
	afx_msg void OnChallengeResponse();
	afx_msg void OnRsaFactorhint();
	afx_msg void OnRsaStereotyped();
	afx_msg void OnRsaBloemermay();
	afx_msg void OnAnimalCaesar();
	afx_msg void OnAnimalVigenere();
	afx_msg void OnAnimalNihilist();
	afx_msg void OnAnimalDes();
	afx_msg void OnIndivCrtPlanet();
	afx_msg void OnIndivCrtDemo();
	afx_msg void OnIndivCrtSecretsharing();
	afx_msg void OnNumberShark();
	afx_msg void OnUpdateNumberShark(CCmdUI* pCmdUI);
	afx_msg void OnIndividualProceduresSecretsharing();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	char *m_Selfextract_EXE;
	char *m_NumberShark_Selfextract_EXE;
	int m_HexFormat;
	CSecudeLib SecudeLib;
	int SecudeStatus;
	HINSTANCE ScintillaLib;
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
	CDlgFindAndReplace findAndReplaceDialog;
	plot_opt_dlg PlotOptions;
	CAppDocument * OpenDocumentFileNoMRU(const char *name, CString Key = "", int KeyType = SCHLUESSEL_LINEAR, int fontSize = 10, CString fontFace = "Arial");
	BOOL MRU_Flag;
	CWnd *m_MainWnd;
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);
	
	// WinHelp set public to get access from Challenge Response Demo
	#if !defined(_MSC_VER) || _MSC_VER <= 1200  
	// HTML Help for VC++ 6.0
	virtual void CCrypToolApp::WinHelp( DWORD dwData, UINT nCmd = HELP_CONTEXT);
	#else										// HTML Help for VC++ .NET
	virtual void WinHelpInternal( DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT ); // overridden to handle F1 on menus with sub menus
	#endif

	CRegKey localRegistry;
	
private:
	void callHtmlHelp(UINT uCommand, DWORD dwData);
	virtual int ExitInstance();
	void execAnimalVisualization(int animalPathID, int animalFileID, int animalExecutableID, int animalLocaleID);
public:
	virtual BOOL OnDDECommand(LPTSTR lpszCommand);
	afx_msg void OnPrimenumberTest();
	afx_msg void OnAesSelfextract();
	afx_msg void OnIndivPointadditiononellipticcurves();
	afx_msg void OnFlashAesdemo();
	afx_msg void OnFlashRijndaelInspector();
	afx_msg void OnInteractiveNumberTheory();
	afx_msg void OnFlashEnigmademo();
	afx_msg void OnIndividualPINEncryption();
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
