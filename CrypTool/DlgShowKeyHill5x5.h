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
#ifndef AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_
#define AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_

#include "afxwin.h"
#include "KeyHillBase.h"

// HillSchluesselAusgabe.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyHill5x5 

class CDlgShowKeyHill5x5 : public CDialog
{
	CKeyHillBase  *m_HillBase;
   BOOL           m_ShowInvKey;
	CString        m_pHillAlphInfo;

// Konstruktion
public:
	CDlgShowKeyHill5x5(CWnd* pParent = NULL);   // Standardkonstruktor
	~CDlgShowKeyHill5x5();
   void init( CKeyHillBase *Hillbase );

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowKeyHill5x5)
	enum { IDD = IDD_SHOW_KEY_HILL5x5 };
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgShowKeyHill5x5)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
	void displayAlphabet();
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowKeyHill5x5)
	virtual BOOL OnInitDialog();
   afx_msg void OnCopyKey();
   afx_msg void OnKey();
   afx_msg void OnInvKey();
   afx_msg void OnOfs0();
   afx_msg void OnOfs1();
	//}}AFX_MSG

   DECLARE_MESSAGE_MAP()
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HILLSCHLUESSELAUSGABE_H__2270633D_8B55_11D2_8D35_00C04F795E36__INCLUDED_
