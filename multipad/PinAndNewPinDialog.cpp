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
// PinAndNewPinDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "PinAndNewPinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPinAndNewPinDialog 


CPinAndNewPinDialog::CPinAndNewPinDialog(char *Text1, char *Text2, CWnd* pParent /*=NULL*/)
	: CDialog(CPinAndNewPinDialog::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CPinAndNewPinDialog)
	m_PinCode = _T("");
	m_NewPinCode = _T("");
	m_NewPinVerification = _T("");
	m_Text1 = CString(Text1);
	m_Text2 = CString(Text2);
	//}}AFX_DATA_INIT
}


void CPinAndNewPinDialog::OnFinalRelease()
{
	// Nachdem die letzte Referenz auf ein Automatisierungsobjekt freigegeben wurde,
	// wird OnFinalRelease aufgerufen. Die Basisklasse löscht das Objekt
	// automatisch. Fügen Sie zusätzlichen Bereinigungscode für Ihr Objekt
	// hinzu, bevor Sie die Basisklasse aufrufen.

	CDialog::OnFinalRelease();
}

void CPinAndNewPinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPinAndNewPinDialog)
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


BEGIN_MESSAGE_MAP(CPinAndNewPinDialog, CDialog)
	//{{AFX_MSG_MAP(CPinAndNewPinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPinAndNewPinDialog, CDialog)
	//{{AFX_DISPATCH_MAP(CPinAndNewPinDialog)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Hinweis: Wir stellen Unterstützung für IID_IPinAndNewPinDialog zur Verfügung, um typsicheres Binden
//  von VBA zu ermöglichen. Diese IID muss mit der GUID übereinstimmen, die in der
//  Disp-Schnittstelle in der .ODL-Datei angegeben ist.

// {12FFFA44-C6D3-11D5-9B5F-000629718ABC}
static const IID IID_IPinAndNewPinDialog =
{ 0x12fffa44, 0xc6d3, 0x11d5, { 0x9b, 0x5f, 0x0, 0x6, 0x29, 0x71, 0x8a, 0xbc } };

BEGIN_INTERFACE_MAP(CPinAndNewPinDialog, CDialog)
	INTERFACE_PART(CPinAndNewPinDialog, IID_IPinAndNewPinDialog, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPinAndNewPinDialog 

void CPinAndNewPinDialog::OnOK() 
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

BOOL CPinAndNewPinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_PinCodeControl.SetFocus();	

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CPinAndNewPinDialog::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();
}
