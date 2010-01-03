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

// DlgHMAC.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHMAC.h"
#include "SecudeCryptography.h"
#include "CrypToolTools.h"
#include "FileTools.h"
#include "ChrTools.h"

#include "HashingOperations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHMAC 

const int hashIDmapping[8] = { 0,   1,  2,  3,  4,  6,  7,  5 };
const int hashSize[8]      = { 16, 16, 16, 20, 20, 32, 64, 20 };

CDlgHMAC::CDlgHMAC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHMAC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHMAC)
	m_alg = -1;
	m_position = -1;
	m_key = _T("");
	m_secondkey = _T("");
	m_str_outer_input = _T("");
	//}}AFX_DATA_INIT
}


void CDlgHMAC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHMAC)
	DDX_Control(pDX, IDC_EDIT_KEY2, m_ctrl_secondkey);
	DDX_Control(pDX, IDC_EDIT_KEY, m_ctrl_key);
	DDX_Control(pDX, IDC_SHOW_MAC, m_mac);
	DDX_Control(pDX, IDC_SHOW_TEXT, m_text);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	DDX_Text(pDX, IDC_EDIT_KEY2, m_secondkey);
	DDX_Text(pDX, IDC_SHOW_MAC, m_str_mac);
	DDX_Text(pDX, IDC_SHOW_TEXT, m_str_outer_input);
	DDX_Text(pDX, IDC_EDIT_ORIGINAL_MESSAGE, m_originalMessage);
	DDX_Text(pDX, IDC_SHOW_HASH, m_innerHash);
	DDX_Control(pDX, IDC_COMBO_SELECT_HASH_FUNCTION, m_comboCtrlSelectHashFunction);
	DDX_Control(pDX, IDC_COMBO_SELECT_HMAC_ALGORITHM, m_comboCtrlSelectHMACFunction);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHMAC, CDialog)
	//{{AFX_MSG_MAP(CDlgHMAC)
	ON_EN_CHANGE(IDC_SHOW_TEXT, OnEditText)
	ON_EN_CHANGE(IDC_EDIT_KEY, OnEditKey)
	ON_EN_CHANGE(IDC_EDIT_ORIGINAL_MESSAGE, OnEditOriginalMessage)
	ON_EN_CHANGE(IDC_EDIT_KEY2, OnEditSecondKey)
	//}}AFX_MSG_MAP
	ON_CBN_SELENDOK(IDC_COMBO_SELECT_HASH_FUNCTION, &CDlgHMAC::OnCbnSelendokComboSelectHashFunction)
	ON_CBN_SELENDOK(IDC_COMBO_SELECT_HMAC_ALGORITHM, &CDlgHMAC::OnCbnSelendokComboSelectHmacAlgorithm)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgHMAC 

BOOL CDlgHMAC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	LOGFONT lf={8,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Courier"};
	//Struktur lf wird deklariert und initialisiert
	m_font.CreateFontIndirect(&lf);
	CWnd* pStatic1=GetDlgItem(IDC_EDIT_KEY);
	CWnd* pStatic2=GetDlgItem(IDC_EDIT_KEY2);
	CWnd* pStatic =GetDlgItem(IDC_SHOW_TEXT);
	CWnd* pStatic3=GetDlgItem(IDC_SHOW_MAC);
	CWnd* pStatic4=GetDlgItem(IDC_SHOW_HASH);

	pStatic->SetFont(&m_font,false);
	pStatic1->SetFont(&m_font,false);
	pStatic2->SetFont(&m_font,false);
	pStatic3->SetFont(&m_font,false);
	pStatic4->SetFont(&m_font,false);

	CString str;
	str.LoadStringA(IDS_HASHDEMO_SELALGORITHM);		m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_MD2);		m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_MD4);		m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_MD5);		m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_SHA);		m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_SHA1);		m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_SHA_256);	m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_SHA_512);	m_comboCtrlSelectHashFunction.AddString(str);
	str.LoadStringA(IDS_HASHDEMO_STRING_RIPEMD160);	m_comboCtrlSelectHashFunction.AddString(str);
	m_comboCtrlSelectHashFunction.SetCurSel(0);

	str.LoadStringA(IDS_HMAC_SELALGORITHM);			m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_HKM);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_HMK);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_HKMK);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_HK1MK2);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_RFC2104);	m_comboCtrlSelectHMACFunction.AddString(str);
	m_comboCtrlSelectHMACFunction.SetCurSel(0);


	UpdateData(true);
	m_text.SetWindowText(strText);
	m_originalMessage = strText;
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgHMAC::hash(char *data, int data_len, char *digest, int &len)
{
	HashingOperations hashOp(hashIDmapping[m_alg]);
	// NOTE: make sure digest has enough memeory
	hashOp.DoHash(data, data_len, digest);
	len = hashSize[m_alg];
}

void CDlgHMAC::hash(CString &data, char *digest, int &len)
{
	hash(data.GetBuffer(), data.GetLength(), digest, len);
}


CString CDlgHMAC::CalculateMac(CString tmpStr)
{
	char digest[64];
	int  digest_length;
	hash(tmpStr, digest, digest_length);
	return hex_dump( digest, digest_length );
}

void CDlgHMAC::SetMac(CString input)
{
	char digest[64];
	int  digest_length;
	hash(input, digest, digest_length);
	m_str_mac = hex_dump( digest, digest_length );
}

CString CDlgHMAC::hex_dump( const char *data, int len )
{
	CString hexaString = _T("");
	char str[3];
	str[2] = '\0';
	for (int i=0; i<len; i++)
	{
		sprintf(str, "%02X", (unsigned char)data[i]);
		hexaString += str;
		if (i < len+1) hexaString += ' ';
	}
	return hexaString;
}


void CDlgHMAC::OnBUTTONSecondKey() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(TRUE);
	UpdateData(false);

	calculateMACAndUpdateGUI();

	// if there is no key selected, set focus to first key
	if(m_key.GetLength() == 0 && m_secondkey.GetLength() == 0)
		this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
	// if there is the first key selected, set focus to second key
	if(m_key.GetLength() > 0)
		this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
}

void CDlgHMAC::OnEditText() 
{
	UpdateData(true);
	m_text.GetWindowText(strText);
	UpdateData(false);
}

void CDlgHMAC::OnEditKey() 
{
	UpdateData(true);
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnEditOriginalMessage()
{
	UpdateData(true);
	// if there is at least one key...
	if(m_key.GetLength() > 0)
		calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnEditSecondKey() 
{
	UpdateData(true);
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::keyEmpty(int IDS)
{
	LoadString(AfxGetInstanceHandle(), IDS, pc_str, 150);
	AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
}


void CDlgHMAC::calculateMACAndUpdateGUI()
{
	UpdateData(true);

	m_str_mac = _T("");
	m_innerHash = _T("");
	m_str_outer_input = _T("");

	if ( m_alg < 0 || m_position < 0 )
	{
		UpdateData(false);
		return;
	}

	switch (m_position)
	{
		case 0: if (m_key == "") keyEmpty(IDS_STRING_MAC_NoKey);
				m_str_outer_input = m_key + m_originalMessage;
				break;//Schlüssel vorne
		case 1:	if (m_key == "") keyEmpty(IDS_STRING_MAC_NoKey);
				m_str_outer_input = m_originalMessage + m_key;
				break;//Schlüssel hinten
		case 2:	if (m_key == "") keyEmpty(IDS_STRING_MAC_NoKey);
				m_str_outer_input = m_key + m_originalMessage + m_key;
				break;//Schlüssel vorne und hinten
		case 3: if ((m_key == "") && (m_secondkey == ""))		keyEmpty(IDS_STRING_MAC_NoKey);
				else if ((m_key == "") && (m_secondkey != ""))  keyEmpty(IDS_STRING_MAC_OnlyOneKey);
				else if ((m_key != "") && (m_secondkey == ""))  keyEmpty(IDS_STRING_MAC_OnlyOneKey);
				m_str_outer_input = m_key + m_originalMessage + m_secondkey;
				break;//zwei Schlüssel
		case 4: 
				{ 
					if (m_key == "") keyEmpty(IDS_STRING_MAC_Double); 
					// acoording RFC 2104
					unsigned char k_ipad[64];
					unsigned char k_opad[64];
					unsigned char keyData[64];
					int keyLen;
					if ( m_key.GetLength() > 64 )
						hash(m_key, (char*)keyData, keyLen);
					else
					{
						keyLen = m_key.GetLength();
						memcpy(keyData, m_key.GetBuffer(), keyLen);
					}
					memset(k_ipad, '\0', 64);
					memset(k_opad, '\0', 64);
					memcpy(k_ipad, keyData, keyLen);
					memcpy(k_opad, keyData, keyLen);
					for (int i=0; i<64; i++) { 
						k_ipad[i] ^= 0x36;
						k_opad[i] ^= 0x5c;
					}

					char digest[64];
					int  digest_length;

					// inner hashing
					HashingOperations hashOp(hashIDmapping[m_alg]);
					hashOp.chunkHashInit();
					hashOp.chunkHashUpdate(k_ipad, 64);
					hashOp.chunkHashUpdate(m_originalMessage.GetBuffer(), m_originalMessage.GetLength());
					hashOp.chunkHashFinal(digest);
					digest_length = hashSize[m_alg];
					m_innerHash = hex_dump( digest, digest_length );
					m_str_outer_input = hex_dump((char*)k_opad, 64) + hex_dump( digest, digest_length );

					// outer hashing
					hashOp.chunkHashInit();
					hashOp.chunkHashUpdate(k_opad, 64);				
					hashOp.chunkHashUpdate(digest, digest_length);				
					hashOp.chunkHashFinal(digest);

					m_str_mac = hex_dump( digest, digest_length );
				}
				break;//doppelte Ausführung der Hashfunktion
	}
	if ( m_position != 4 )
	{
		SetMac(m_str_outer_input);
	}
	UpdateData(false);	
}
void CDlgHMAC::OnCbnSelendokComboSelectHashFunction()
{
	UpdateData();
	m_alg = m_comboCtrlSelectHashFunction.GetCurSel() -1;
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnCbnSelendokComboSelectHmacAlgorithm()
{
	UpdateData();
	m_position = m_comboCtrlSelectHMACFunction.GetCurSel() -1;

	switch ( m_position ) {
		case -1:
		case  0: // H(m, k)
		case  1: // H(k, m)
		case  2: // H(k,m,k)
		case  4: // H(k,H(m,k))
			m_ctrl_secondkey.EnableWindow(FALSE);
			if(m_key.GetLength() == 0)
				this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
			break;
		case 3: // H(k,m,k')
			m_ctrl_secondkey.EnableWindow(TRUE);
			if(m_key.GetLength() == 0)
				this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
			else if ( m_secondkey.GetLength() == 0)
				this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
			break;
	}			
	UpdateData(false);
	calculateMACAndUpdateGUI();
}
