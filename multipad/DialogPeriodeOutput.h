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

#include "zzahlanalyse.h"


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPeriodeOutput 

class CDialogPeriodeOutput : public CDialog
{
// Konstruktion
public:
	CDialogPeriodeOutput(CWnd* pParent = NULL);   // Standardkonstruktor

	zzahlanalyse *zahlenanalyse;

		
// Dialogfelddaten
	//{{AFX_DATA(CDialogPeriodeOutput)
	enum { IDD = IDD_DIALOG_PERIOD_OUTPUT };
	CListCtrl	m_listview;
	//}}AFX_DATA

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDialogPeriodeOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogPeriodeOutput)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DIALOGPERIODEOUTPUT_H__0C041D91_4841_11D5_BC42_00500445DDBC__INCLUDED_
