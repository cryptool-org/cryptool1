//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_
#define AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_

// OptionsDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsAnalysis 

class CDlgOptionsAnalysis : public CDialog
{
// Konstruktion
public:
	CDlgOptionsAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsAnalysis)
	enum { IDD = IDD_OPTIONS_ANALYSIS };
	BOOL	m_CKey;
	BOOL	m_CKorr;
	BOOL	m_CHist;
	BOOL	m_VKey;
	BOOL	m_VLen;
	BOOL	m_VKorr;
	BOOL	m_VBase;
	long	m_BFEntropyWindow;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsAnalysis)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_
