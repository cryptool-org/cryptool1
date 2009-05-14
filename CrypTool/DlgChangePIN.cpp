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
// Revision 1.4  2004/04/30 12:30:05  clausius
// Conflict fixed
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
// PinAndNewPinDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgChangePIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgChangePIN 


CDlgChangePIN::CDlgChangePIN(char *Text1, char *Text2, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChangePIN::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgChangePIN)
	m_PinCode = _T("");
	m_NewPinCode = _T("");
	m_NewPinVerification = _T("");
	m_Text1 = CString(Text1);
	m_Text2 = CString(Text2);
	//}}AFX_DATA_INIT
}


void CDlgChangePIN::OnFinalRelease()
{
	// Nachdem die letzte Referenz auf ein Automatisierungsobjekt freigegeben wurde,
	// wird OnFinalRelease aufgerufen. Die Basisklasse löscht das Objekt
	// automatisch. Fügen Sie zusätzlichen Bereinigungscode für Ihr Objekt
	// hinzu, bevor Sie die Basisklasse aufrufen.

	CDialog::OnFinalRelease();
}

void CDlgChangePIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChangePIN)
	DDX_Control(pDX, IDC_EDIT_PIN2, m_Text2Control);
	DDX_Control(pDX, IDC_EDIT_PIN1, m_Text1Control);
	DDX_Control(pDX, IDC_EDIT3, m_NewPinVerificationControl);
	DDX_Control(pDX, IDC_EDIT2, m_NewPinEditControl);
	DDX_Control(pDX, IDC_EDIT1, m_PinCodeControl);
	DDX_Text(pDX, IDC_EDIT1, m_PinCode);
	DDX_Text(pDX, IDC_EDIT2, m_NewPinCode);
	DDX_Text(pDX, IDC_EDIT3, m_NewPinVerification);
	DDX_Text(pDX, IDC_EDIT_PIN1, m_Text1);
	DDX_Text(pDX, IDC_EDIT_PIN2, m_Text2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChangePIN, CDialog)
	//{{AFX_MSG_MAP(CDlgChangePIN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgChangePIN, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgChangePIN)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Hinweis: Wir stellen Unterstützung für IID_IPinAndNewPinDialog zur Verfügung, um typsicheres Binden
//  von VBA zu ermöglichen. Diese IID muss mit der GUID übereinstimmen, die in der
//  Disp-Schnittstelle in der .ODL-Datei angegeben ist.

// {12FFFA44-C6D3-11D5-9B5F-000629718ABC}
static const IID IID_IPinAndNewPinDialog =
{ 0x12fffa44, 0xc6d3, 0x11d5, { 0x9b, 0x5f, 0x0, 0x6, 0x29, 0x71, 0x8a, 0xbc } };

BEGIN_INTERFACE_MAP(CDlgChangePIN, CDialog)
	INTERFACE_PART(CDlgChangePIN, IID_IPinAndNewPinDialog, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgChangePIN 

void CDlgChangePIN::OnOK() 
{
	UpdateData (TRUE);

	// TODO: Zusätzliche Prüfung hier einfügen
	if (m_NewPinCode == "")
	{
//		MessageBox("PIN must not be empty", "PIN Security", MB_ICONWARNING|MB_OK);
//		m_NewPinEditControl.SetFocus();
//		return;
	}

	if (m_NewPinCode != m_NewPinVerification) 
	{
		// PIN-Code und PIN-Code-Verifikation stimmen nicht überein
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_PIN_PINVERIFICATION_NOTMATCH,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		// Die Eingabefelder von PIN und PIN-Verifikation löschen
		m_NewPinCode = "";
		m_NewPinVerification = "";
		UpdateData(FALSE);
		m_NewPinEditControl.SetFocus();
		return;
	}

	CDialog::OnOK();
}

BOOL CDlgChangePIN::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_PinCodeControl.SetFocus();	

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgChangePIN::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();
}
