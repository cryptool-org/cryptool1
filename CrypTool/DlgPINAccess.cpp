/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// PinCodeDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPINAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPINAccess 


CDlgPINAccess::CDlgPINAccess(int modus, CString keyinfo, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPINAccess::IDD, pParent)
{
	UserKeyId = keyinfo;
	Modus = modus;

	//{{AFX_DATA_INIT(CDlgPINAccess)
	m_PinCode = _T("");
	m_InfoBox = _T("");
	m_ModusInfoBox = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPINAccess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPINAccess)
	DDX_Control(pDX, IDC_EDIT2, m_InfoBoxCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_ModusInfoBoxCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_PinEditControl);
	DDX_Text(pDX, IDC_EDIT1, m_PinCode);
	DDX_Text(pDX, IDC_EDIT2, m_InfoBox);
	DDX_Text(pDX, IDC_EDIT3, m_ModusInfoBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPINAccess, CDialog)
	//{{AFX_MSG_MAP(CDlgPINAccess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgPINAccess 

int CDlgPINAccess::DoModal() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	
	return CDialog::DoModal();
} 

BOOL CDlgPINAccess::OnInitDialog() 
//InitInstance
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	LOGFONT LogFont;
	LONG defaultFontWeight;
	CFont *defaultFont = m_InfoBoxCtrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_ModusInfoBoxCtrl.SetFont(&m_Font);

	if (Modus == 0)
	{
		// Eintrag "UserKeyId"-Dateien löschen

		LoadString(AfxGetInstanceHandle(),IDS_STRING_REMOVE_ITEM,pc_str,STR_LAENGE_STRING_TABLE);
		m_ModusInfoBox = (CString) pc_str;

		LoadString(AfxGetInstanceHandle(),IDS_STRING_REQ_DEL_KEYDATA,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, UserKeyId);
		m_InfoBox = (CString) pc_str1;
	}
	else
	{
		// Geheime Parameter die zu Eintrag "UserKeyId" gehören einsehen

		LoadString(AfxGetInstanceHandle(),IDS_STRING_SHOW_ALL_PARAM,pc_str,STR_LAENGE_STRING_TABLE);
		m_ModusInfoBox = (CString) pc_str;

		LoadString(AfxGetInstanceHandle(),IDS_STRING_REQUEST_FOR_PIN,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, UserKeyId);
		m_InfoBox = (CString) pc_str1;
	}
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgPINAccess::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();
}

void CDlgPINAccess::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	CDialog::OnOK();
}
