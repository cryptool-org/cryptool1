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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgMac.h"
#include "SecudeCryptography.h"
#include "CrypToolTools.h"
#include "FileTools.h"
#include ".\dlgmac.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgMac-Dialogfeld

CDlgMac::CDlgMac(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMac::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMac)
	m_alg = 0;
	m_position = 0;
	m_str_mac = _T("");
	m_key = _T("");
	m_secondkey = _T("");
	//}}AFX_DATA_INIT
}

/*CDlgMac::~CDlgMac()
{
}*/

/*Aufruf nach Konstruktion, jedoch vor Anzeige des Dialogfeldes
Anzeige der Datei im Dialog*/

BOOL CDlgMac::OnInitDialog()
{
	CDialog::OnInitDialog();	
	UpdateData(true);
	m_text.SetWindowText(strText);
	UpdateData(false);
	return TRUE;
}

void CDlgMac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMac)
	DDX_Radio(pDX, IDC_RADIO1, m_alg);
	DDX_Radio(pDX, IDC_RADIO7, m_position);
	DDX_Control(pDX, IDC_SHOW_TEXT, m_text);
	DDX_Control(pDX, IDC_SHOW_MAC, m_mac);
	DDX_Control(pDX, IDC_EDIT_KEY, m_ctrl_key);
	DDX_Text(pDX, IDC_SHOW_MAC, m_str_mac);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	DDX_Text(pDX, IDC_EDIT_KEY2, m_secondkey);
	DDX_Control(pDX, IDC_EDIT_KEY2, m_ctrl_secondkey);
	DDX_Control(pDX, IDOK, m_create_mac);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgMac, CDialog)
	//{{AFX_MSG_MAP(CDlgMac)
	ON_BN_CLICKED(IDC_RADIO11, OnBUTTONSecondKey)
	ON_EN_CHANGE(IDC_SHOW_TEXT, OnEditText)
	ON_EN_CHANGE(IDC_EDIT_KEY, OnEditKey)
	ON_BN_CLICKED(IDC_RADIO7, OnBUTTONFront)
	ON_BN_CLICKED(IDC_RADIO8, OnBUTTONBack)
	ON_BN_CLICKED(IDC_RADIO9, OnBUTTONBoth)
	ON_BN_CLICKED(IDC_RADIO10, OnBUTTONDouble)
	ON_EN_CHANGE(IDC_EDIT_KEY2, OnEditSecondKey)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_RADIO1, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO2, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO3, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO4, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO5, OnBUTTONHashFunction)
	ON_BN_CLICKED(IDC_RADIO6, OnBUTTONHashFunction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgMac::OnOK()
{
	UpdateData(true);
	CString tempRes;
	switch (m_position)
	{
	case 0: if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
			}
			strText = m_key + strText;
			break;//Schlüssel vorne
	case 1:	if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
			}
			strText += m_key;
			break;//Schlüssel hinten
	case 2:	if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
			}
			strText = m_key + strText + m_key;
			break;//Schlüssel vorne und hinten
	case 3: if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_Double, pc_str, 150);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
			}
			tempRes = m_key + strText;
			strText = m_key + CalculateMac(tempRes);
			break;//doppelte Ausführung der Hashfunktion
	case 4: if ((m_key == "") && (m_secondkey == ""))
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
			}
			else 
				if ((m_key == "") && (m_secondkey != ""))
				{
					LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_OnlyOneKey, pc_str, 150);
					AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				}
				else
					if ((m_key != "") && (m_secondkey == ""))
					{
						LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_OnlyOneKey, pc_str, 150);
						AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
					}
			strText = m_key + strText + m_secondkey;
			break;//zwei Schlüssel
	}
	SetMac(strText);
	m_text.SetWindowText(strText);
	UpdateData(false);
}

void CDlgMac::SetMac(CString input)
{
	//Umwandeln in OctetString
	OctetString os, macHash;
	os.octets = 0x00000000;
	os.noctets = 0;
	const char* None = new char[0];
	macHash.octets = 0x000000000;
	macHash.noctets = 0;
	String2Octets(&os, LPCSTR(input), input.GetLength());
	String2Octets(&macHash, None, 0);
	
	//hashen mit dem gewählten Algorithmus	
	switch (m_alg)
	{
	case 0:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.md2_aid, NULL);
			break;//MD2
	case 1:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.md4_aid, NULL);
			break;//MD4
	case 2:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.md5_aid, NULL);
			break;//MD5
	case 3:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.sha_aid, NULL);
			break;//SHA
	case 4:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.sha1_aid, NULL);
			break;//SHA1
	case 5:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.ripemd160_aid, NULL);
			break;//RIPEMD 160
	}
	m_str_mac = MacToHex(&macHash);
	m_create_mac.EnableWindow(FALSE);
	UpdateData(false);
	theApp.SecudeLib.aux_free(macHash.octets);
}

CString CDlgMac::CalculateMac(CString tmpStr)
{
	OctetString os, macHash;
	os.octets = 0x00000000;
	os.noctets = 0;
	const char* None = new char[0];
	macHash.octets = 0x000000000;
	macHash.noctets = 0;
	String2Octets(&macHash, None, 0);
	String2Octets(&os, LPCSTR(tmpStr), tmpStr.GetLength());

	//hashen mit dem gewählten Algorithmus
	macHash.noctets = 0;
	switch (m_alg)
	{
	case 0:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.md2_aid, NULL);
			break;//MD2
	case 1:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.md4_aid, NULL);
			break;//MD4
	case 2:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.md5_aid, NULL);
			break;//MD5
	case 3:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.sha_aid, NULL);
			break;//SHA
	case 4:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.sha1_aid, NULL);
			break;//SHA1
	case 5:	theApp.SecudeLib.sec_hash_all(&os, &macHash, theApp.SecudeLib.ripemd160_aid, NULL);
			break;//RIPEMD 160
	}
	CString tmpRes = MacToHex(&macHash);
	return tmpRes;
}

void CDlgMac::String2Octets(OctetString* osTarget, const char* Source, const int Length)
{
	osTarget->noctets = Length;
	char* Buffer = new char[Length];
	for(int i=0; i<Length; i++) Buffer[i] = Source[i];
	delete[] osTarget->octets;
	osTarget->octets = Buffer;
}

CString CDlgMac::MacToHex(OctetString* hash)
{
	CString hexaString;
	for (unsigned int i=0; i<hash->noctets; i++)
	{
		unsigned char x = hash->octets[i];
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
		if (i < hash->noctets+1) 
		{
			hexaString += ' ';
		}
	}
	return hexaString;
}

void CDlgMac::OnEditText()
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	m_text.GetWindowText(strText);
	UpdateData(false);
}

void CDlgMac::OnEditKey()
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgMac::OnEditSecondKey()
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgMac::OnBUTTONFront()
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgMac::OnBUTTONBack()
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgMac::OnBUTTONBoth()
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgMac::OnBUTTONDouble()
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgMac::OnBUTTONSecondKey()
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(TRUE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}
void CDlgMac::OnBUTTONHashFunction()
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}
