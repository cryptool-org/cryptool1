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
// Programmiert von Thomas Gauweiler 2001
//////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGPERIODEOUTPUT_H__0C041D91_4841_11D5_BC42_00500445DDBC__INCLUDED_)
#define AFX_DIALOGPERIODEOUTPUT_H__0C041D91_4841_11D5_BC42_00500445DDBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPeriodeOutput.h : Header-Datei
//

#include "RandomAnalysisTools.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPeriodicityAnalysis 

class CDlgPeriodicityAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgPeriodicityAnalysis(CWnd* pParent = NULL);  // Standardkonstruktor
	~CDlgPeriodicityAnalysis(); 
	CRandomAnalysisTools *zahlenanalyse;

	char outfile[CRYPTOOL_PATH_LENGTH];
	char *OldTitle;
		
// Dialogfelddaten
	//{{AFX_DATA(CDlgPeriodicityAnalysis)
	enum { IDD = IDD_PERIODICITY_ANALYSIS };
	CListCtrl	m_listview;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgPeriodicityAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgPeriodicityAnalysis)
	virtual BOOL OnInitDialog();
	afx_msg void OnSaveList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPERIODEOUTPUT_H__0C041D91_4841_11D5_BC42_00500445DDBC__INCLUDED_
