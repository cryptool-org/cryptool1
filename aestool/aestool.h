// aestool.h : Haupt-Header-Datei für die Anwendung AESTOOL
//

#if !defined(AFX_AESTOOL_H__A8D430F2_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_)
#define AFX_AESTOOL_H__A8D430F2_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CAestoolApp:
// Siehe aestool.cpp für die Implementierung dieser Klasse
//

class CAestoolApp : public CWinApp
{
public:
	CAestoolApp();
	int findStr(CString *l); // used in ScanCMDLine
	void ScanCMDLine( char * cmd );

	CString m_CMD_inKey;
	CString m_CMD_outName;
	CString m_CMD_inName;

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAestoolApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CAestoolApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CAestoolApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_AESTOOL_H__A8D430F2_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_)
