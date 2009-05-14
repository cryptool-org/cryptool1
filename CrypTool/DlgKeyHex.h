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
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
#ifndef HEXDIALOG_H
#define HEXDIALOG_H

#include "DlgKey.h"
#include "HexEdit.h"

#define MAX_ANZ_HEX_BLOECKE MAX_VIGENERE

// hexdialog.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHex 

class CDlgKeyHex : public CDlgKey
{
    int i_maxlen;
// Konstruktion
public:
	CDlgKeyHex(int maxlen, CWnd* pParent = NULL);   // Standardkonstruktor
	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int Display();

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHex)
	enum { IDD = IDD_KEY };
	CHexEdit	m_einfeld;
	CString		m_einstr;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHex)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHex)
	afx_msg void OnUpdateKey();
	afx_msg void OnPasteHexKey();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // HEXDIALOG_H
