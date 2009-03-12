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
// DialoKeyCaesar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCaesarAnalysis.h"
// #include "DlgPrimesGeneratorDemo.h" // ## Weg 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCaesarAnalysis 


CDlgCaesarAnalysis::CDlgCaesarAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCaesarAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCaesarAnalysis)
	m_string = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCaesarAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCaesarAnalysis)
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_string);
	DDV_MaxChars(pDX, m_string, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCaesarAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgCaesarAnalysis)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCaesarAnalysis 

void CDlgCaesarAnalysis::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */
	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.getIgnoreCase())
	{
		m_string.MakeUpper();
	}

	for(k=i=0;i<m_string.GetLength();i++) {
		c = m_string[i];
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

	m_string = res;
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
}

BOOL CDlgCaesarAnalysis::OnInitDialog()
{
	CDialog::OnInitDialog();

	// display the remark regarding the key offset
	GetDlgItem(IDC_EDIT_KEY_OFFSET_REMARK)->SetWindowText(createKeyOffsetRemark());

	return FALSE;
}

CString CDlgCaesarAnalysis::createKeyOffsetRemark()
{
	// memory allocation
	char result[STR_LAENGE_STRING_TABLE+1];
	memset(result, 0, STR_LAENGE_STRING_TABLE+1);
	char derivedKey[2];
	memset(derivedKey, 0, 2);
	char alternativeKey[2];
	memset(alternativeKey, 0, 2);
	// build the remark string based on the resource string, the derived key and the alternative key
	LoadString(AfxGetInstanceHandle(), IDS_CAESAR_ANALYSIS_REMARK, pc_str, STR_LAENGE_STRING_TABLE);
	memcpy(derivedKey, m_string.GetBuffer(), 1);

	// get the alternative key
	int pos = theApp.TextOptions.getAlphabet().Find(derivedKey);
	// take the "next" character in the alphabet after the derived key
	int newPos = (pos + 1) % theApp.TextOptions.getAlphabet().GetLength();
	memcpy(alternativeKey, (const char*)theApp.TextOptions.getAlphabet() + newPos, 1);

	// mix it all together
	sprintf(result, pc_str, derivedKey, alternativeKey);
	// return the resulting string
	CString theResult = result;
	return theResult;
}