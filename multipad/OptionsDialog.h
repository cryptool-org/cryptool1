//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_
#define AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_

// OptionsDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld OptionsDialog 

class OptionsDialog : public CDialog
{
// Konstruktion
public:
	OptionsDialog(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(OptionsDialog)
	enum { IDD = IDD_DIALOG_ANALYSE_OPT };
	BOOL	m_CKey;
	BOOL	m_CKorr;
	BOOL	m_CHist;
	BOOL	m_VKey;
	BOOL	m_VLen;
	BOOL	m_VKorr;
	BOOL	m_VBase;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(OptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(OptionsDialog)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_OPTIONSDIALOG_H__CF6277BD_7D2F_11D2_887F_00C04F795E28__INCLUDED_
