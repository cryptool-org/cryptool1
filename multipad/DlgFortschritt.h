//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_DLGFORTSCHRITT_H__386CD5D9_F7C7_11D2_888E_00C04F795E28__INCLUDED_
#define AFX_DLGFORTSCHRITT_H__386CD5D9_F7C7_11D2_888E_00C04F795E28__INCLUDED_

// DlgFortschritt.h : Header-Datei
//

#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgFortschritt 

class DlgFortschritt : public CDialog
{
// Konstruktion
public:
	void Display(const char *title);
	void cancel( void );
	int m_displayed;
	int m_canceled;
	int Set(int pos);
	int Set(int pos, CString format);
	int Set(int pos, CString caption, CString format);
	DlgFortschritt(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(DlgFortschritt)
	enum { IDD = IDD_DIALOG_FORTSCHRITT };
	CStatic	m_text_ctl;
	CProgressCtrl	m_Progress;
	CString	m_text;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(DlgFortschritt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CString Format;
	CString Title;
	int m_pos;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(DlgFortschritt)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_old_pos;
	CCriticalSection Lock;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGFORTSCHRITT_H__386CD5D9_F7C7_11D2_888E_00C04F795E28__INCLUDED_
