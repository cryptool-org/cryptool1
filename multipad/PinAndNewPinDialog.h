//////////////////////////////////////////////////////////////////
//
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//
// $Id$
//
// PIN/PIN verification dialog
//
// 2001 Martin Bartosch <m.bartosch@cynops.de>; Cynops GmbH
//
// $Log$
// Revision 1.1  2001/11/09 15:37:35  idj100
// Sourcen von Martin Bartosch mit Eingebunden
// RSA-Demo überarbeitet
//
//


#if !defined(AFX_PINANDNEWPINDIALOG_H__12FFFA45_C6D3_11D5_9B5F_000629718ABC__INCLUDED_)
#define AFX_PINANDNEWPINDIALOG_H__12FFFA45_C6D3_11D5_9B5F_000629718ABC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PinAndNewPinDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPinAndNewPinDialog 

class CPinAndNewPinDialog : public CDialog
{
// Konstruktion
public:
	CPinAndNewPinDialog(char *Text1, char *Text2, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CPinAndNewPinDialog)
	enum { IDD = IDD_DIALOG_PIN_VERIFICATION };
	CEdit	m_Text2Control;
	CEdit	m_Text1Control;
	CEdit	m_NewPinVerificationControl;
	CEdit	m_NewPinEditControl;
	CEdit	m_PinCodeControl;
	CString	m_PinCode;
	CString	m_NewPinCode;
	CString	m_NewPinVerification;
	CString	m_Text1;
	CString	m_Text2;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CPinAndNewPinDialog)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPinAndNewPinDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generierte OLE-Dispatch-Zuordnungsfunktionen
	//{{AFX_DISPATCH(CPinAndNewPinDialog)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PINANDNEWPINDIALOG_H__12FFFA45_C6D3_11D5_9B5F_000629718ABC__INCLUDED_
