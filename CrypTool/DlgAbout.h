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
#ifndef AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
#define AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
#include "afxwin.h"

// About.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAbout 

class CDlgAbout : public CDialog
{
	// Konstruktion
public:
	CDlgAbout(CWnd* pParent = NULL);   // Standardkonstruktor
	
	// Dialogfelddaten
	//{{AFX_DATA(CDlgAbout)
	enum { IDD = IDD_ABOUT };

	// Versionsstring der Secude Bibliothek
	CString strVersionSecude1;
	CString strVersionSecude2;
	// Versionsstring der Miracl Bibliothek
	CString strVersionMiracl;
	// Versionsstring der OpenSSL Bibliothek
	CString strVersionOpenSSL;
	// Versionsstring der NTL Bibliothek
	CString strVersionNTL;
	// Versionsstring der Scintilla Bibliothek
	CString strVersionScintilla;
	// Versionsstring der cryptovision Bibliothek
	CString strVersionCryptovision;
	// Versionsstring der GMP Bibliothek
	CString strVersionGMP;
	//}}AFX_DATA
	
	
	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgAbout)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL
	
	// Implementierung
protected:
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgAbout)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// Funktion zur Ermittlung der verschiedenen Bibliotheksversionen
	void determineLibraryVersions();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
