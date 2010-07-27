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

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	m_paste_key.SetToolTipText(&buttonPasteText);

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
