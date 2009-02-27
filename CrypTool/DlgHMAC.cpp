/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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
	m_alg = 0;
	m_position = 0;
	m_key = _T("");
	m_secondkey = _T("");
	m_str_mac = _T("");
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
	DDX_Radio(pDX, IDC_RADIO1, m_alg);
	DDX_Radio(pDX, IDC_RADIO7, m_position);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	DDX_Text(pDX, IDC_EDIT_KEY2, m_secondkey);
	DDX_Text(pDX, IDC_SHOW_MAC, m_str_mac);
	DDX_Text(pDX, IDC_EDIT_ORIGINAL_MESSAGE, m_originalMessage);
	DDX_Text(pDX, IDC_SHOW_HASH, m_outerHash);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHMAC, CDialog)
	//{{AFX_MSG_MAP(CDlgHMAC)
	ON_BN_CLICKED(IDC_RADIO11, OnBUTTONSecondKey)
	ON_EN_CHANGE(IDC_SHOW_TEXT, OnEditText)
	ON_EN_CHANGE(IDC_EDIT_KEY, OnEditKey)
	ON_EN_CHANGE(IDC_EDIT_ORIGINAL_MESSAGE, OnEditOriginalMessage)
	ON_BN_CLICKED(IDC_RADIO7, OnBUTTONFront)
	ON_BN_CLICKED(IDC_RADIO8, OnBUTTONBack)
	ON_BN_CLICKED(IDC_RADIO9, OnBUTTONBoth)
	ON_BN_CLICKED(IDC_RADIO10, OnBUTTONDouble)
	ON_EN_CHANGE(IDC_EDIT_KEY2, OnEditSecondKey)
	ON_BN_CLICKED(IDC_RADIO1, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO2, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO3, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO4, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO5, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO12, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO13, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO6, OnBUTTONHashFunction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgHMAC 

BOOL CDlgHMAC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(true);
	m_text.SetWindowText(strText);

	m_originalMessage = strText;

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgHMAC::hash(OctetString *data, char *digest, int &len)
{
	HashingOperations hashOp(hashIDmapping[m_alg]);
	// NOTE: make sure digest has enough memeory
	hashOp.DoHash(data->octets, data->noctets, digest);
	len = hashSize[m_alg];
}

void CDlgHMAC::hash(CString &data, char *digest, int &len)
{
	OctetString os;
	os.octets  = 0;
	os.noctets = 0;
	String2Octets(&os, LPCSTR(data), data.GetLength());
	hash(&os, digest, len);
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
	SetOuterHash();
}

void CDlgHMAC::SetOuterHash()
{
	char digest[64];
	int  digest_length;
	hash(m_originalMessage, digest, digest_length);
	m_outerHash = hex_dump( digest, digest_length );
}

void CDlgHMAC::String2Octets(OctetString *osTarget, const char *Source, const int Length)
{
	osTarget->noctets = Length;
	char* Buffer = new char[Length];
	for(int i=0; i<Length; i++) Buffer[i] = Source[i];
	delete[] osTarget->octets;
	osTarget->octets = Buffer;
}

CString CDlgHMAC::hex_dump( const char *data, int len )
{
	CString hexaString;
	for (unsigned int i=0; i<len; i++)
	{
		unsigned char x = data[i];
		char c1, c2;
		if (( x % 16 ) < 10 ) 
		{
			c2 = '0' + (x % 16);
		}
		else 
		{
			c2 = 'A' + (x % 16) -10;
		}
		x /= 16;
		if ( x < 10 ) 
		{
			c1 = '0' + x; 
		}
		else 
		{
			c1 = 'A' + x -10;
		}
		hexaString += c1;
		hexaString += c2;
		if (i < len+1) 
		{
			hexaString += ' ';
		}
	}
	return hexaString;
}


CString CDlgHMAC::MacToHex(OctetString *hash)
{
	return hex_dump( (char*)hash->octets, hash->noctets );
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

void CDlgHMAC::OnBUTTONFront() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	UpdateData(false);

	calculateMACAndUpdateGUI();

	// if there is no key selected, set focus to first key
	if(m_key.GetLength() == 0 && m_secondkey.GetLength() == 0)
		this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
	// if there is the first key selected, set focus to second key
	if(m_key.GetLength() > 0)
		this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
}

void CDlgHMAC::OnBUTTONBack() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	UpdateData(false);

	calculateMACAndUpdateGUI();

	// if there is no key selected, set focus to first key
	if(m_key.GetLength() == 0 && m_secondkey.GetLength() == 0)
		this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
	// if there is the first key selected, set focus to second key
	if(m_key.GetLength() > 0)
		this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
}

void CDlgHMAC::OnBUTTONBoth() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	UpdateData(false);

	calculateMACAndUpdateGUI();

	// if there is no key selected, set focus to first key
	if(m_key.GetLength() == 0 && m_secondkey.GetLength() == 0)
		this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
	// if there is the first key selected, set focus to second key
	if(m_key.GetLength() > 0)
		this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
}

void CDlgHMAC::OnBUTTONDouble() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	UpdateData(false);

	calculateMACAndUpdateGUI();

	// if there is no key selected, set focus to first key
	if(m_key.GetLength() == 0 && m_secondkey.GetLength() == 0)
		this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
	// if there is the first key selected, set focus to second key
	if(m_key.GetLength() > 0)
		this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
}

void CDlgHMAC::OnEditSecondKey() 
{
	UpdateData(true);

	calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnBUTTONHashFunction() 
{
	UpdateData(true);

	calculateMACAndUpdateGUI();
}

void CDlgHMAC::calculateMACAndUpdateGUI()
{
	UpdateData(true);
	CString tempRes;
	switch (m_position)
	{
	case 0: if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				// no return because of auto-update implementation
				//return;
			}
			strText = m_key + m_originalMessage;
			break;//Schl�ssel vorne
	case 1:	if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				// no return because of auto-update implementation
				//return;
			}
			strText = m_originalMessage + m_key;
			break;//Schl�ssel hinten
	case 2:	if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				// no return because of auto-update implementation
				//return;
			}
			strText = m_key + m_originalMessage + m_key;
			break;//Schl�ssel vorne und hinten
	case 3: 
			{ 
				if (m_key == "")
				{
					LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_Double, pc_str, 150);
					AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
					// no return because of auto-update implementation
					//return;
				}
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
				tempRes = hex_dump((char*)k_opad, 64) + hex_dump( digest, digest_length );
				m_text.SetWindowText(tempRes);

				// outer hashing
				hashOp.chunkHashInit();
				hashOp.chunkHashUpdate(k_opad, 64);				
				hashOp.chunkHashUpdate(digest, digest_length);				
				hashOp.chunkHashFinal(digest);

				m_str_mac = hex_dump( digest, digest_length );
			}
			break;//doppelte Ausf�hrung der Hashfunktion
	case 4: if ((m_key == "") && (m_secondkey == ""))
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				// no return because of auto-update implementation
				//return;
			}
			else if ((m_key == "") && (m_secondkey != ""))
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_OnlyOneKey, pc_str, 150);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				// no return because of auto-update implementation
				//return;
			}
			else if ((m_key != "") && (m_secondkey == ""))
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_OnlyOneKey, pc_str, 150);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				// no return because of auto-update implementation
				//return;
			}
			strText = m_key + m_originalMessage + m_secondkey;
			break;//zwei Schl�ssel
	}
	if ( m_position != 3 )
	{
		SetMac(strText);
		m_text.SetWindowText(strText);
	}
	UpdateData(false);	
}