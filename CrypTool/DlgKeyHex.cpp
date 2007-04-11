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



