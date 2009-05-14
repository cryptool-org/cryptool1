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
// Behandlungsroutinen f�r Nachrichten CDlgPINAccess 

int CDlgPINAccess::DoModal() 
{
	// TODO: Speziellen Code hier einf�gen und/oder Basisklasse aufrufen
	
	return CDialog::DoModal();
} 

BOOL CDlgPINAccess::OnInitDialog() 
//InitInstance
{
	CDialog::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen

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
		// Eintrag "UserKeyId"-Dateien l�schen

		LoadString(AfxGetInstanceHandle(),IDS_STRING_REMOVE_ITEM,pc_str,STR_LAENGE_STRING_TABLE);
		m_ModusInfoBox = (CString) pc_str;

		LoadString(AfxGetInstanceHandle(),IDS_STRING_REQ_DEL_KEYDATA,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, UserKeyId);
		m_InfoBox = (CString) pc_str1;
	}
	else
	{
		// Geheime Parameter die zu Eintrag "UserKeyId" geh�ren einsehen

		LoadString(AfxGetInstanceHandle(),IDS_STRING_SHOW_ALL_PARAM,pc_str,STR_LAENGE_STRING_TABLE);
		m_ModusInfoBox = (CString) pc_str;

		LoadString(AfxGetInstanceHandle(),IDS_STRING_REQUEST_FOR_PIN,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, UserKeyId);
		m_InfoBox = (CString) pc_str1;
	}
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgPINAccess::OnCancel() 
{
	// TODO: Zus�tzlichen Bereinigungscode hier einf�gen
	
	CDialog::OnCancel();
}

void CDlgPINAccess::OnOK() 
{
	// TODO: Zus�tzliche Pr�fung hier einf�gen
	
	CDialog::OnOK();
}
