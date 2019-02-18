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

// SchluesselAusgabeLinear.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowKey.h"
#include "KeyRepository.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKey 


CDlgShowKey::CDlgShowKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowKey)
	m_Key = _T("");
	//}}AFX_DATA_INIT
}


void CDlgShowKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowKey)
	DDX_Control(pDX, IDC_EDIT1, m_CtrlKey);
	DDX_Text(pDX, IDC_EDIT1, m_Key);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowKey, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowKey 


void CDlgShowKey::OnCopyKey() 
{
	//In der Zwischen Ablage kopieren
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	CopyKey(strTitle, m_Key); 
///////////////////////////////////////////////
//	HENRIK KOY 06-08-2002
//  Das Einfügen des Schlüsselstrings in die Windows-Zwischenablage bewirkt, dass der vom User eventuell
//  dorthinein gespeicherte Inhalt überschrieben wird (verwirrt den User). -- deshalb auskommentiert
//	m_CtrlKey.SetSel(0,-1); 
//	m_CtrlKey.Copy();
	CDialog::OnOK();
}

BOOL CDlgShowKey::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_font.CreatePointFont(100,"Courier New");
	m_CtrlKey.SetFont(&m_font);
	if (strTitle[0])
	{
		LoadString(AfxGetInstanceHandle(),IDS_METHOD_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		char keyMethodStr[128];
		sprintf( keyMethodStr, pc_str, strTitle );
		SetWindowText(keyMethodStr);
	}

	// TODO: Zusätzliche Initialisierung hier einfügen
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CDlgShowKey::PreTranslateMessage(MSG *msg) {
	// flomar, 2019/02/18: This custom message handler functionality was necessary 
	// to allow users to press Ctrl+A to select all text in the log window. For some 
	// mysterious reason MFC would not allow it out-of-the-box.
	if(msg->message == WM_KEYDOWN && msg->wParam == 'A' && GetKeyState(VK_CONTROL) < 0) {
		CEdit *edit = (CEdit*)(GetDlgItem(IDC_EDIT1));
		if(edit) {
			edit->SetSel(0, -1);
			return true;
		}
	}
	return CDialog::PreTranslateMessage(msg);
}

int CDlgShowKey::DoModal() 
{
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	return CDialog::DoModal();
}

