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


// DlgShowHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowHash.h"
#include "Cryptography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowHash 


CDlgShowHash::CDlgShowHash(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowHash::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowHash)
	m_HashStr = _T("");
	//}}AFX_DATA_INIT
}


void CDlgShowHash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowHash)
	DDX_Text(pDX, IDC_EDIT1, m_HashStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowHash, CDialog)
	//{{AFX_MSG_MAP(CDlgShowHash)
	ON_BN_CLICKED(IDOK, OnShowHashInDesktop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowHash 

void CDlgShowHash::OnShowHashInDesktop() 
{
	CDialog::OnOK();
}

BOOL CDlgShowHash::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	SetWindowText(title);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgShowHash::SetHash( OctetString &hash, const char *Title, const char * method )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName2(title, sizeof(title), pc_str, Title, method );
	m_HashStr = "";
	for (unsigned int i=0; i<hash.noctets; i++)
	{
		unsigned char x = hash.octets[i];
		char c1, c2;
		if (( x % 16 ) < 10 ) c2 = '0' + (x % 16); else c2 = 'A' + (x % 16) -10;
		x /= 16;
		if ( x < 10 ) c1 = '0' + x; else c1 = 'A' + x -10; 
		m_HashStr += c1;
		m_HashStr += c2;
		if (i < hash.noctets+1) m_HashStr += ' ';
	}
}
