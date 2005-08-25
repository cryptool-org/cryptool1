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


// DlgKeyPermutationInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyPermutationInfo.h"
#include ".\dlgkeypermutationinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyPermutationInfo 


CDlgKeyPermutationInfo::CDlgKeyPermutationInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyPermutationInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyPermutationInfo)
	m_Inverse1 = _T("");
	m_Permutation1 = _T("");
	m_Permutation2 = _T("");
	m_Inverse2 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgKeyPermutationInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyPermutationInfo)
	DDX_Control(pDX, IDOK, m_button_control);
	DDX_Text(pDX, IDC_EDIT2, m_Inverse1);
	DDX_Text(pDX, IDC_EDIT1, m_Permutation1);
	DDX_Text(pDX, IDC_EDIT3, m_Permutation2);
	DDX_Text(pDX, IDC_EDIT4, m_Inverse2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyPermutationInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyPermutationInfo)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDBACK, OnBnClickedBack)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyPermutationInfo 

BOOL CDlgKeyPermutationInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// TODO: Zusätzliche Initialisierung hier einfügen

	SetWindowText(LPCTSTR(m_dialogue_title));
	m_button_control.SetWindowText(LPCTSTR(m_button_title));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgKeyPermutationInfo::OnBnClickedBack()
{
	EndDialog(IDBACK);
}
