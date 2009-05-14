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

#if !defined(AFX_DLGFINDTEXT_H__94A7CB7E_6FAC_4CA5_B549_AFACBF9F2AC8__INCLUDED_)
#define AFX_DLGFINDTEXT_H__94A7CB7E_6FAC_4CA5_B549_AFACBF9F2AC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFindText.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFindText 

class CDlgFindText : public CDialog
{
// Konstruktion
public:
	CDlgFindText(CWnd* pParent = NULL);   // Standardkonstruktor
	char *str_ttf;

// Dialogfelddaten
	//{{AFX_DATA(CDlgFindText)
	enum { IDD = IDD_FIND_TEXT };
	CEdit	m_CtrlSearchText;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFindText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFindText)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGFINDTEXT_H__94A7CB7E_6FAC_4CA5_B549_AFACBF9F2AC8__INCLUDED_
