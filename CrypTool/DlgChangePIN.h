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
// Revision 1.3  2004/04/30 12:09:35  clausius
// Compiles with VS.NET C++
//
// Revision 1.2  2003/12/17 17:49:14  clausius
// GPL Header hinzugefuegt
//
// Revision 1.1  2002/02/27 12:48:24  idj100
// CrypTool develop 1.3.01
//
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
// Dialogfeld CDlgChangePIN 

class CDlgChangePIN : public CDialog
{
// Konstruktion
public:
	CDlgChangePIN(char *Text1, char *Text2, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgChangePIN)
	enum { IDD = IDD_CHANGE_PIN };
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
	//{{AFX_VIRTUAL(CDlgChangePIN)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgChangePIN)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generierte OLE-Dispatch-Zuordnungsfunktionen
	//{{AFX_DISPATCH(CDlgChangePIN)
		// HINWEIS - Der Klassen-Assistent fügt hier Member-Funktionen ein und entfernt diese.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PINANDNEWPINDIALOG_H__12FFFA45_C6D3_11D5_9B5F_000629718ABC__INCLUDED_
