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
// Programmierung der Dialog-Klasse zur Eingabe eines 
// hexadezimalen Schlüssels. Bei der Eingabe werden nur die 
// Zeichen a,...,f,A,...,F,0,...,9 akzeptiert; dabei werden 
// Kleinbuchstaben in Großbuchstaben umgewandelt (dies geschieht
// direkt durch das Eingabefenster, bzw. dessen Eigenschaften-Fenster). 
// Im Eingabefenster wird die hexadezimale Zahl in der üblichen 
// Schreibweise - jeweils Blöcke bestehend aus zwei Zeichen, 
// getrennt durch ein Leerzeichen - angegeben. Cut and Paste 
// über die Zwischenablage funktioniert ebenfalls. 
// Da ein Eingabefeld CEdit keine Nachricht erhält, die etwas über 
// die gedrückte Taste aussagen, ist es nicht möglich, folgende 
// Situationen zu unterscheiden:
// - Der Cursor steht links von einem Leerzeichen und der Benutzer 
//   drückt "Entfernen"
// - Der Cursor steht rechts von einem Leerzeichen und der Benutzer 
//   drückt "Backspace"
//   In diesem Fall wird so verfahren, als ob die Taste "Backspace" 
//   gedrückt worden wäre.
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// hexdialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define INIT_STRING ""


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHex 


CDlgKeyHex::CDlgKeyHex(int maxlen, CWnd* pParent /*=NULL*/)
	: CDlgKey( maxlen, pParent)
{
    i_maxlen = min(MAX_ANZ_HEX_BLOECKE,maxlen);
	len = i_maxlen*3 - 1;
	//{{AFX_DATA_INIT(CDlgKeyHex)
	m_einstr = _T(INIT_STRING);
	m_Decrypt = 0;
	//}}AFX_DATA_INIT

	char line[160];

	if ( maxlen > 0 )
	{
		LoadString(AfxGetInstanceHandle(),IDS_KEYHEX_MAX_INPUT_LENGTH_TXT, pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,i_maxlen*2, i_maxlen);
		m_static_text = line;
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_INPUT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,i_maxlen*2, i_maxlen);
		m_static_text = line;
	}
	s_alternativeWindowText[0]=0;
}

int CDlgKeyHex::Display()
{
	int res;
	res=DoModal();
	return res;
}

void CDlgKeyHex::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyHex)
	DDX_Control(pDX, IDOK, m_EncryptionButton);
	DDX_Control(pDX, IDC_BUTTON1, m_DecryptionButton);
	DDX_Control(pDX, IDC_BUTTON_TEXTOPTIONS, m_TextOptionsButton);
	DDX_Control(pDX, IDC_EDIT1, m_einfeld);
	DDX_Text(pDX, IDC_EDIT1, m_einstr);
	DDV_MaxChars(pDX, m_einstr, len);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_static_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyHex, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHex)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateKey)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteHexKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHex 

char * CDlgKeyHex::GetData( void )
{
	return m_einfeld.BinData;
}

int CDlgKeyHex::GetLen( void )
{
	return min(i_maxlen, m_einfeld.BinLen);
}

void CDlgKeyHex::OnUpdateKey() 
{
	UpdateData(TRUE);	
	if ( m_einstr.GetLength() )
	{
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);	
	}
	else
	{
		m_EncryptionButton.EnableWindow(FALSE);
		m_DecryptionButton.EnableWindow(FALSE);	
	}
	UpdateData(FALSE);
}

void CDlgKeyHex::OnPasteHexKey() 
{
	UpdateData(TRUE);
	CString Title;
	CString KeyStr;
	Title=s_alternativeWindowText;
	ExtractStrKeyType( strTitle, Title );
	if ( PasteKey(strTitle,KeyStr) )
	{
		m_einfeld.SetSel(0,-1);
		m_einfeld.ReplaceSel( KeyStr );
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);	
	}
	UpdateData(FALSE);
}

BOOL CDlgKeyHex::OnInitDialog() 
{
	CDlgKey::OnInitDialog();

	// unless explicitly wanted (e.g. in a derived dialog class), HIDE the text options button
	m_TextOptionsButton.ShowWindow(SW_HIDE);
	
	return true;
}



