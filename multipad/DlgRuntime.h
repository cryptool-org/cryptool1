#if !defined(AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRuntime.h : Header-Datei
//

#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRuntime 

class CDlgRuntime : public CDialog
{
// Konstruktion
	CCriticalSection Lock;
	long zaehler;
public:
	CString m_Caption;
	void SetCaption( const char * Caption );
	CDlgRuntime(CWnd* pParent = NULL);   // Standardkonstruktor
	int m_displayed;
    void Display(const char * title);
	void cancel();

// Dialogfelddaten
	//{{AFX_DATA(CDlgRuntime)
	enum { IDD = IDD_TEST };
	CString	m_TimeStr;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgRuntime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRuntime)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRUNTIME_H__46C9DA43_A553_11D5_BB4A_000777640932__INCLUDED_
