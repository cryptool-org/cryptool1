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
// DialogLaengeBin.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DialogLaengeBin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgBinKeyLength 


CDlgBinKeyLength::CDlgBinKeyLength(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinKeyLength::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinKeyLength)
	m_Char = _T("00");
	m_laenge = 0;
	//}}AFX_DATA_INIT
}


void CDlgBinKeyLength::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinKeyLength)
	DDX_Control(pDX, IDC_EDIT2, m_Ctl);
	DDX_Text(pDX, IDC_EDIT2, m_Char);
	DDV_MaxChars(pDX, m_Char, 2);
	DDX_Text(pDX, IDC_EDIT1, m_laenge);
	DDV_MinMaxUInt(pDX, m_laenge, 1, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBinKeyLength, CDialog)
	//{{AFX_MSG_MAP(CDlgBinKeyLength)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgBinKeyLength 

void CDlgBinKeyLength::OnChangeEdit2() 
{
	int i;
	char c;

	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	for(i=0;i<m_Char.GetLength();i++) {
		c=m_Char[i];
		if(!((('0'<=c) && (c <='9'))||(('A'<=c)&&(c<='F')))) m_Ctl.Undo();
	}
}

void CDlgBinKeyLength::OnOK() 
{
	int i;
	char c;

	m_c = 0;

	UpdateData(TRUE);  // Werte aus Eingabemaske lesen

	for(i=0;i<m_Char.GetLength();i++) {
		c = m_Char[i];
		if(('0'<=c) && (c<='9')) m_c = m_c*16 + (c-'0');
		if(('A'<=c) && (c<='F')) m_c = m_c*16 + (c-'A') + 10;
	}
	
	CDialog::OnOK();
}

BOOL CDlgBinKeyLength::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_title.GetLength())
		SetWindowText(m_title);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
