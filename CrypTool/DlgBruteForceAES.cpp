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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// AESSuche.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "Cryptography.h"
#include "HexEdit.h"
#include "DlgBruteForceAES.h"
#include ".\dlgbruteforceaes.h"

// nibble i contains a parity bit if m_parity == CRYPT_PARITY_DES*: in low nibble (i & 1) and for DESX* in the first 64 bit only
#define parity_in_nibble(i) (m_parity_check && (i & 1) && (m_parity_check != CRYPT_PARITY_DESX || i < 64/4))


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBruteForceAES 

CDlgBruteForceAES::CDlgBruteForceAES(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBruteForceAES::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBruteForceAES)
	m_len=0;
	m_keylenindex = -1;
	//}}AFX_DATA_INIT
	for (int i = 0; i < sizeof m_hexinc; i++) 
		m_hexinc[i] = i + 1;
	m_hexinc['9'] = 'A';
	m_hexinc['F'] = '0';
	m_text_ctl.SetValidChars("*0123456789ABCDEF");
	m_text_ctl.SetFillChar('*');

}

void CDlgBruteForceAES::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBruteForceAES)
	DDX_Control(pDX, IDC_KEY_LEN, m_keylen_ctl);
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_CBIndex(pDX, IDC_KEY_LEN, m_keylenindex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBruteForceAES, CDialog)
	//{{AFX_MSG_MAP(CDlgBruteForceAES)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdate)
	ON_CBN_SELCHANGE(IDC_KEY_LEN, OnSelchangeKeyLen)
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusHexEdit)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK2, OnBnClickedOk2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgBruteForceAES 

void CDlgBruteForceAES::OnUpdate() 
{
	//m_text_ctl.GetWindowText(m_text); // done in OnSelchangeKeyLen()
}

void CDlgBruteForceAES::OnSelchangeKeyLen() 
{
	UpdateData(TRUE); // fetch m_keylenindex for GetBinlen()
	int targetbits = GetBinlen();
	ASSERT(targetbits % 8 == 0);
	m_text_ctl.SetFixedByteLength(targetbits / 8);
	//m_text_ctl.SetFocus();
}

char *CDlgBruteForceAES::GetData()
{
	return m_data;
}

void CDlgBruteForceAES::GetDataInt(char *p)
{
	int i;
	for (i=0;i<m_len*2;i++)
	{
		if (i%2)
			p[i/2]+=m_text_ctl.HexVal(m_data[i]);
		else
			p[i/2]=m_text_ctl.HexVal(m_data[i])<<4;
	}
}

int CDlgBruteForceAES::GetLen()
{
	return m_len;
}

int CDlgBruteForceAES::GetBinlen()
{
	return m_keylenmin + m_keylenindex * m_keylenstep;
}

int CDlgBruteForceAES::GetSearchBitLen()
{
	int n;
	int bits = 0;
	for (n = 0; m_mask[n] >= 0; n++)
		bits += parity_in_nibble(m_mask[n]) ? 3 : 4;
	return bits;
}

int CDlgBruteForceAES::Display(char *titel,int keylenmin,int keylenmax, int keylenstep, int parity_check)
{
	int res;
	m_alg = titel;
	m_keylenmin = keylenmin;
	m_keylenmax = keylenmax;
	m_keylenstep = keylenstep;
	m_parity_check = parity_check;
	res=DoModal();
	return res;
}

double CDlgBruteForceAES::getProgress()
{
	// interpret *m_mask[0],*m_mask[1],*m_mask[2],... as a base 16 fractional number 
	// with least significant digit *m_mask[0] 
	if (m_state == 0)
		return 1.0;
	double p = 0.0;
	int i = 0;
	while (m_mask[i] >= 0) {
		//char c = *(m_mask[i++]);
		char c = m_data[m_mask[i]];
		//  p += c >= 'A' ? c - 'A' + 10 : c - '0';
		if ( parity_in_nibble(m_mask[i]) )
		{
			p += (c >= 'A' ? c - 'A' + 10 : c - '0')/2;
			p /= 8.0;
		}
		else
		{
			p += c >= 'A' ? c - 'A' + 10 : c - '0';
			p /= 16.0;
		}
		i++;
	}
	return p;
}


#define incWithCarry(p) (((p) = m_hexinc[(p)]) == '0')
int CDlgBruteForceAES::Step()
{
	if (m_state < 0) {
		m_state = 1;
		return true;
	}
	int i = 0;
	int j;
	if (m_parity_check) // For DES variants
	{  // note: 1. lower half byte ((m_mask[i] %2) == TRUE) contains the parity bit (least significant bit)
	   //       2. Step() ignores parity checks as the des implementations ignores them too
		while ( (j = m_mask[i]) >= 0
			&&  parity_in_nibble(j) 
				? (incWithCarry(m_data[j]), incWithCarry(m_data[j]))
				: incWithCarry(m_data[j]) )
		{
			ASSERT( j < sizeof(m_data));
			i++;
		}
	}
	else
	{
		while ((j = m_mask[i]) >= 0 && incWithCarry(m_data[j]))
			i++;
	}
	return m_state = (j >= 0);
}

#if 0
alte implementierung
int CDlgBruteForceAES::Step()
{
	int i,n,m;
	if (m_co<=m_max)
	{
		i=0;
		while((n=m_mask[i])!=100)
		{
			m=(m_co>>(i*4))%16;
			m_data[n]=m>9?m-10+'A':m+'0';
			i++;
		}
		m_co++;
		return 1+(m_co*99/(m_max+1));
	}
	return 0;
}
#endif 


BOOL CDlgBruteForceAES::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString titel;
	titel.Format(IDS_STRING_ANALYSE_ON,m_alg);
	SetWindowText(titel);
	m_font.CreatePointFont(100,"Courier New");
	m_text_ctl.SetFont(&m_font);
	m_keylen_ctl.ResetContent();
	for (int b = m_keylenmin; b <= m_keylenmax; b += m_keylenstep) {
		CString s;
		CString eff;
		int beff =m_parity_check == CRYPT_PARITY_DES ? 7*b/8 : m_parity_check == CRYPT_PARITY_DESX ? 184 : b;
		if (m_parity_check) 
			eff.Format(IDS_BIT_EFFECTIVE_FMT, beff);
		s.Format(IDS_BIT_FMT, b, (const char*)eff);
		m_keylen_ctl.AddString(s);
	}
	m_keylen_ctl.SetCurSel(0);
	m_data[0] = 0;
	OnSelchangeKeyLen();
	m_text_ctl.SetFocus();
	return 0; // don't let MFC mess with the focus
}

void CDlgBruteForceAES::UpdateDataMask()
{
	int l, i,j, k,num;
	char c;
	CString res;

#if 0
	for (i=0;i<64;i++)
		m_data[i]='0';
#endif
	for(k=i=num=l=j=0;i<m_text.GetLength();i++)
	{
		c = m_text[i];
		if((c >= 'A' && c <= 'F')||(c >= '0'&& c <= '9')||(c=='*'))
		{
			if (c== '*') {
				ASSERT(l < sizeof(m_mask)/sizeof(int));
				m_mask[l++] = j;
				c = '0';
			}
			ASSERT(j < sizeof(m_data));
			m_data[j++] = c;
		}
	}
	ASSERT(l < sizeof(m_mask)/sizeof(int));
	m_mask[l] = -1;
	m_state = -1;
#if 0
	if(j == 0) m_len=0;
	else if(j <= 16) m_len = 8;
	else if(j <= 32) m_len = 16;
	else if(j <= 48) m_len = 24;
	else m_len = 32;
	m_data[m_len<<1]=0;
#else
	ASSERT(j < sizeof(m_data));
	m_data[j] = 0;
	ASSERT(j % 2 == 0);
	m_len = j/2;
#endif
}

void CDlgBruteForceAES::OnOK() 
{
	m_text_ctl.GetWindowText(m_text);
	UpdateDataMask();
	CDialog::OnOK();
}

void CDlgBruteForceAES::OnSetfocusHexEdit() 
{
	m_text_ctl.SetSel(0,0);	
}

void CDlgBruteForceAES::OnBnClickedOk2()
{
	theApp.Options.DoModal();
}
