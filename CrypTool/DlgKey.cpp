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
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// dia1.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKey.h"
#include "Cryptography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgKey dialog

CDlgKey::CDlgKey(int maxlen, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKey::IDD, pParent)
{
	char line[80];

	len = (maxlen > 0) ? maxlen : -maxlen;
	//{{AFX_DATA_INIT(CDlgKey)
	m_text = _T("");
	m_static_text = _T("");
	//}}AFX_DATA_INIT
	if ( maxlen > 0 )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_MAX_INPUT_LENGTH_TXT,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,len);
		m_static_text = line;
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_INPUT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,len);
		m_static_text = line;
	}
	s_alternativeWindowText[0]=0;
}

int CDlgKey::Display()
{
	int res;

	res=DoModal();
	return res;
}

void CDlgKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKey)
	DDX_Control(pDX, IDOK, m_EncryptionButton);
	DDX_Control(pDX, IDC_BUTTON1, m_DecryptionButton);
	DDX_Control(pDX, IDC_BUTTON_TEXTOPTIONS, m_TextOptionsButton);
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDV_MaxChars(pDX, m_text, len);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_static_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKey, CDialog)
	//{{AFX_MSG_MAP(CDlgKey)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, OnTextOptions)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKey message handlers


char * CDlgKey::GetData( void )
{
	return m_text.GetBuffer(MAX_VIGENERE+1);
}

int CDlgKey::GetLen( void )
{
	return m_text.GetLength();
}

void CDlgKey::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */


	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.getIgnoreCase()) m_text.MakeUpper();

	for(k=i=0;i<m_text.GetLength();i++) {
		c = m_text[i];
		if(AppConv.IsInAlphabet(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		}
	}

	m_text = res;
	if ( m_text.GetLength() )
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
	m_text_ctl.SetSel(sels,sele);
} 

void CDlgKey::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Decrypt = 1;
	OnOK();
}

void CDlgKey::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Decrypt = 0;
	OnOK();
}

void CDlgKey::OnTextOptions()
{
	theApp.TextOptions.DoModal();
	// check whether key contains non-alphabet characters now
	if(!IsKeyInAlphabet(m_text, theApp.TextOptions.getAlphabet()))
	{
		// remove those characters from the key one by one
		for(int i=0; i<m_text.GetLength(); i++)
		{
			if(theApp.TextOptions.getAlphabet().Find(m_text.GetAt(i)) == -1)
				m_text.Remove(m_text.GetAt(i));
		}
	}

	// set focus to text edit for better usage
	m_text_ctl.SetFocus();

	// enable/disable encryption/decryption button if there is a/no key
	if (m_text.GetLength())
	{
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);	
	}
	else
	{
		m_EncryptionButton.EnableWindow(FALSE);
		m_DecryptionButton.EnableWindow(FALSE);	
	}

	UpdateData(false);
}

void CDlgKey::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}

BOOL CDlgKey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// TODO: Zusätzliche Initialisierung hier einfügen
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	


	if (s_alternativeWindowText[0])
		SetWindowText(s_alternativeWindowText);
	m_EncryptionButton.EnableWindow(FALSE);
	m_DecryptionButton.EnableWindow(FALSE);	

	CString Title;
	Title=s_alternativeWindowText;
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgKey::OnPasteKey() 
{
	UpdateData(TRUE);

	CString Title, alphabet = theApp.TextOptions.getAlphabet();
	Title=s_alternativeWindowText;
	ExtractStrKeyType( strTitle, Title );
	if ( PasteKey(strTitle,m_text) )
	{
		if (this->IsKeyInAlphabet(m_text, alphabet))
		{
			m_EncryptionButton.EnableWindow(TRUE);
			m_DecryptionButton.EnableWindow(TRUE);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_BAD_KEY,pc_str,255);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			m_text.Empty();
		}
	}
	UpdateData(FALSE);
}


BOOL CDlgKey::IsKeyInAlphabet(CString key, CString alphabet)
{
	for (int ii = 0; ii < key.GetLength(); ii ++)
	{
		if (alphabet.Find(key.GetAt(ii)) < 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}
