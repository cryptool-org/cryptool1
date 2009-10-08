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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_AUTOREN_H__831C14C1_3834_11D3_8A66_0020351F15C0__INCLUDED_
#define AFX_AUTOREN_H__831C14C1_3834_11D3_8A66_0020351F15C0__INCLUDED_

// Autoren.h : Header-Datei
//

#include "TextScroller.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAuthors 

class CDlgAuthors : public CDialog
{
	// Konstruktion
public:
	CDlgAuthors(CWnd* pParent = NULL);   // Standardkonstruktor
	
	// Dialogfelddaten
	//{{AFX_DATA(CDlgAuthors)
	enum { IDD = IDD_AUTHORS };
	// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA
	
	
	// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgAuthors)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementierung
protected:
	
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgAuthors)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	// this function reads all authors from "authors.txt"
	void readAuthors();

	// this text scroller holds all authors for implementation, documentation and translation
	CTextScroller textScrollerImplementationDocumentationTranslation;
	// this text scroller holds all authors for review and feedback
	CTextScroller textScrollerReviewFeedback;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_AUTOREN_H__831C14C1_3834_11D3_8A66_0020351F15C0__INCLUDED_
