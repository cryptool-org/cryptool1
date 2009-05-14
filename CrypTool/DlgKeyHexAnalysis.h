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
#ifndef DIALOGKEYHEX_H
#define DIALOGKEYHEX_H

#include "DlgKeyVigenere.h"
#include "HexEdit.h"

#define MAX_ANZ_HEX_BLOECKE MAX_VIGENERE
// DialogKeyHex.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHex 

class CDlgKeyHexAnalysis : public CDlgKeyVigenereAnalyisis
{
// Konstruktion
public:
	CDlgKeyHexAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int GetHexData(LPTSTR v, int len); // copy m_einstr, removing non-hex chars
	virtual int Display(LPCTSTR title, char *, int, bool fixed=true);
	virtual int Display(LPCTSTR title, CString, bool fixed=true);
	int len;

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHexAnalysis)
	enum { IDD = IDD_KEY_ANALYSIS };
	CHexEdit	m_einfeld;
	CString	m_einstr;
	CString	m_static_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHexAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont m_font; // font for key display
	bool m_fixed; // fixed key length
	CString m_title; // dialog title
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHexAnalysis)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // DIALOGKEYHEX_H
