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


// DlgHMAC.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHMAC.h"
#include "SecudeCryptography.h"
#include "CrypToolTools.h"
#include "FileTools.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHMAC 


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
	DDX_Control(pDX, IDOK, m_create_mac);
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
	ON_BN_CLICKED(IDC_RADIO6, OnBUTTONHashFunction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgHMAC 

void CDlgHMAC::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	// CDialog::OnOK();

	UpdateData(true);
	CString tempRes;
	switch (m_position)
	{
	case 0: if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				return;
			}
			strText = m_key + m_originalMessage;
			break;//Schlüssel vorne
	case 1:	if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				return;
			}
			strText = m_originalMessage + m_key;
			break;//Schlüssel hinten
	case 2:	if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				return;
			}
			strText = m_key + m_originalMessage + m_key;
			break;//Schlüssel vorne und hinten
	case 3: if (m_key == "")
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_Double, pc_str, 150);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				return;
			}
			tempRes = m_key + m_originalMessage;
			strText = m_key + CalculateMac(tempRes);
			break;//doppelte Ausführung der Hashfunktion
	case 4: if ((m_key == "") && (m_secondkey == ""))
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_NoKey, pc_str, 100);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				return;
			}
			else if ((m_key == "") && (m_secondkey != ""))
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_OnlyOneKey, pc_str, 150);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				return;
			}
			else if ((m_key != "") && (m_secondkey == ""))
			{
				LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_OnlyOneKey, pc_str, 150);
				AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
				return;
			}
			strText = m_key + m_originalMessage + m_secondkey;
			break;//zwei Schlüssel
	}
	SetMac(strText);
	m_text.SetWindowText(strText);
	UpdateData(false);
}

BOOL CDlgHMAC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UpdateData(true);
	m_text.SetWindowText(strText);

	m_originalMessage = strText;

	// make "Calculate MAC" button invisble; maybe remove this button completely...
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}



CString CDlgHMAC::CalculateMac(CString tmpStr)
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

void CDlgHMAC::SetMac(CString input)
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

void CDlgHMAC::String2Octets(OctetString *osTarget, const char *Source, const int Length)
{
	osTarget->noctets = Length;
	char* Buffer = new char[Length];
	for(int i=0; i<Length; i++) Buffer[i] = Source[i];
	delete[] osTarget->octets;
	osTarget->octets = Buffer;
}

CString CDlgHMAC::MacToHex(OctetString *hash)
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

void CDlgHMAC::OnBUTTONSecondKey() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(TRUE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);	
}

void CDlgHMAC::OnEditText() 
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	m_text.GetWindowText(strText);
	UpdateData(false);
}

void CDlgHMAC::OnEditKey() 
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);

	// calculate MAC implicitly after the key is altered
	OnOK();
}

void CDlgHMAC::OnEditOriginalMessage()
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);

	// if there is at least one key, calculate MAC implicitly after text is altered
	if(m_key.GetLength() > 0)
		OnOK();
}

void CDlgHMAC::OnBUTTONFront() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgHMAC::OnBUTTONBack() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgHMAC::OnBUTTONBoth() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgHMAC::OnBUTTONDouble() 
{
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(FALSE);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}

void CDlgHMAC::OnEditSecondKey() 
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);

	// calculate MAC implicitly after the second key is altered
	OnOK();
}

void CDlgHMAC::OnBUTTONHashFunction() 
{
	UpdateData(true);
	m_create_mac.EnableWindow(TRUE);
	UpdateData(false);
}
