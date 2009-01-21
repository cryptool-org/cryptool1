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


// DlgKeyHexFixedLen.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "Cryptography.h"
#include "HexEdit.h"
#include "KeyRepository.h"
#include "DlgKeyHexFixedLen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHexFixedLen 


CDlgKeyHexFixedLen::CDlgKeyHexFixedLen(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHexFixedLen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyHexFixedLen)
	m_key_len_index = -1;
	//}}AFX_DATA_INIT
}


void CDlgKeyHexFixedLen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyHexFixedLen)
	DDX_Control(pDX, IDC_KEY, m_key_ctl);
	DDX_Control(pDX, IDC_KEY_LEN, m_key_len_ctl);
	DDX_CBIndex(pDX, IDC_KEY_LEN, m_key_len_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyHexFixedLen, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHexFixedLen)
	ON_CBN_SELCHANGE(IDC_KEY_LEN, OnChangeKeyLen)
	ON_BN_CLICKED(IDC_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(IDC_DECRYPT, OnDecrypt)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHexFixedLen 

void CDlgKeyHexFixedLen::OnChangeKeyLen() 
{
	UpdateData(TRUE); 
	int targetbits = m_keylenmin + m_key_len_index * m_keylenstep;
	ASSERT(targetbits % 8 == 0);
	m_key_ctl.SetFixedByteLength(targetbits / 8);
}

void CDlgKeyHexFixedLen::Init(CString title, int keylenmin, int keylenmax, int keylenstep, int parity_check)
{
	m_title = title;
	m_keylenmin = keylenmin;
	m_keylenmax = keylenmax;
	m_keylenstep = keylenstep;
	m_parity_check = parity_check;
}

char * CDlgKeyHexFixedLen::GetKeyBytes()
{
	return m_key_ctl.BinData;
}

int CDlgKeyHexFixedLen::GetKeyByteLength()
{
	return m_key_ctl.BinLen;
}

BOOL CDlgKeyHexFixedLen::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText(m_title);

	m_font.CreatePointFont(100,"Courier New");
	m_key_ctl.SetFont(&m_font);
	m_key_len_ctl.ResetContent();
	for (int b = m_keylenmin; b <= m_keylenmax; b += m_keylenstep) {
		CString s;
		CString eff;
		int beff = m_parity_check == CRYPT_PARITY_DES ? 7*b/8 : m_parity_check == CRYPT_PARITY_DESX ? 184 : b;
		if (m_parity_check) 
			eff.Format(IDS_BIT_EFFECTIVE_FMT, beff);
		s.Format(IDS_BIT_FMT, b, (const char*)eff);
		m_key_len_ctl.AddString(s);
	}
	m_key_len_ctl.SetCurSel(0);
	OnChangeKeyLen();

	VERIFY(m_paste_key.AutoLoad(IDC_PASTE_KEY,this));
	m_paste_key.EnableWindow(IsKeyEmpty(m_title));

	return TRUE;  // return TRUE unless you set the focus to a control
}

bool CDlgKeyHexFixedLen::ModeIsDecrypt()
{
	return m_modeisdecrypt;
}

void CDlgKeyHexFixedLen::OnEncrypt() 
{
	m_modeisdecrypt = false;
	m_key_ctl.GetWindowText(m_key_formatted);
	OnOK();
}

void CDlgKeyHexFixedLen::OnDecrypt() 
{
	m_modeisdecrypt = true;
	m_key_ctl.GetWindowText(m_key_formatted);
	OnOK();	
}

CString CDlgKeyHexFixedLen::GetKeyFormatted()
{
	return m_key_formatted;

}

void CDlgKeyHexFixedLen::OnPasteKey() 
{
	char strTitle[KEYDATA_HASHSTRING_LENGTH];

	ExtractStrKeyType( strTitle, m_title );
	CString key;
	PasteKey(strTitle,key);
	int keybytelen = (key.GetLength() + 1) / 3;
	ASSERT(key.GetLength() == keybytelen * 3 - 1 && 
		keybytelen * 8 >= m_keylenmin && keybytelen * 8 <= m_keylenmax);
	int index = (keybytelen * 8 - m_keylenmin) / m_keylenstep;
	ASSERT(keybytelen * 8 == m_keylenmin + index * m_keylenstep);
	if (index != m_key_len_ctl.GetCurSel()) {
		m_key_len_ctl.SetCurSel(index);
		OnChangeKeyLen();
	}
	m_key_ctl.SetSel(0,m_key_ctl.GetWindowTextLength());
	m_key_ctl.ReplaceSel(key); // don't use SetWindowText, CHexEdit wouldn't notice the update
}
