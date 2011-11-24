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
	void detachConsole();

	CString m_CMD_inKey;
	CString m_CMD_outName;
	CString m_CMD_inName;

	// this function returns the version string (i.e. "AES-Tool 2.6")
	static CString getAESToolVersionString() {
		static CString version;
		version.LoadString(IDS_STRING_AES_TOOL_VERSION);
		return version;
	};

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAestoolApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelpInternal( DWORD_PTR dwData, UINT nCmd = HELP_CONTEXT ); // overridden to handle F1 on menus with sub menus
#if 0 // not anymore supported
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
#endif
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CAestoolApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CAestoolApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_AESTOOL_H__A8D430F2_1896_11D5_8ACA_0010A4F6E7D5__INCLUDED_)
