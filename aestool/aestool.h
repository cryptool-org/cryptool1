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
