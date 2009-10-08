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
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedContributors();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// Funktion zur Ermittlung der verschiedenen Bibliotheksversionen
	void determineLibraryVersions();

	// used for dialog header
	CString stringCrypToolVersion;
	CFont font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_ABOUT_H__831C14C2_3834_11D3_8A66_0020351F15C0__INCLUDED_
