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


// DlgSelHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSelHash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelHash 


CDlgSelHash::CDlgSelHash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelHash::IDD, pParent), m_nIDHash(0)
{
	//{{AFX_DATA_INIT(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}


void CDlgSelHash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelHash, CDialog)
	//{{AFX_MSG_MAP(CDlgSelHash)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSelHash 

BOOL CDlgSelHash::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(m_sHashAlg=="MD2")	m_nIDHash = IDC_MD2;
	else if(m_sHashAlg=="MD5") m_nIDHash = IDC_MD5;
	else if(m_sHashAlg=="SHA") m_nIDHash = IDC_SHA;
	else if(m_sHashAlg=="SHA-1") m_nIDHash = IDC_SHA_1;
	else if(m_sHashAlg=="RIPEMD-160") m_nIDHash = IDC_RIPEMD160;
	else m_nIDHash = 0;
	CheckRadioButton(IDC_MD2, IDC_RIPEMD160, m_nIDHash);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSelHash::OnOK() 
{
	m_nIDHash = GetCheckedRadioButton( IDC_MD2, IDC_RIPEMD160 );
	switch(m_nIDHash)
	{
		case IDC_MD2: m_sHashAlg = "MD2"; break;
		case IDC_MD5: m_sHashAlg = "MD5"; break;
		case IDC_SHA: m_sHashAlg = "SHA"; break;
		case IDC_SHA_1: m_sHashAlg = "SHA-1"; break;
		case IDC_RIPEMD160: m_sHashAlg = "RIPEMD-160"; break;
		default: m_sHashAlg.Empty();
	}

	CDialog::OnOK();
}
