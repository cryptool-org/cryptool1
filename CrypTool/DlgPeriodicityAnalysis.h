//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
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
	CDlgPeriodicityAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

	CRandomAnalysisTools *zahlenanalyse;

		
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DIALOGPERIODEOUTPUT_H__0C041D91_4841_11D5_BC42_00500445DDBC__INCLUDED_
