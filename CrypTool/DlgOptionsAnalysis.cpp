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
// OptionsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsAnalysis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsAnalysis 


CDlgOptionsAnalysis::CDlgOptionsAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsAnalysis::IDD, pParent)
	, i_alphabetOptions(0)
{
	//{{AFX_DATA_INIT(CDlgOptionsAnalysis)
	m_CKey = TRUE;
	m_CKorr = TRUE;
	m_CHist = TRUE;
	m_VKey = TRUE;
	m_VLen = TRUE;
	m_VKorr = TRUE;
	m_VBase = FALSE;
	m_BFEntropyWindow = 128;
	//}}AFX_DATA_INIT
	i_alphabetOptions = 0;
}

static long GetWindowTextAsLong(CWnd *wnd)
{
	CString text;
	wnd->GetWindowText(text);
	return atol(text);
}

void CDlgOptionsAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	pDX->PrepareCtrl(IDC_EDIT_ENTROPY_WINDOW); // this is needed to set the focus to IDC_EDIT_ENTROPY_WINDOW if the following check fails
	// we do DDV_MinMaxLong before DDX_Text to prevent MFC from change the value of m_BFEntropyWindow to something
	// outside the valid range. This value would be kept even on pressing Cancel
	DDV_MinMaxLong(pDX, GetWindowTextAsLong(GetDlgItem(IDC_EDIT_ENTROPY_WINDOW)), 32, 4096); 
	//{{AFX_DATA_MAP(CDlgOptionsAnalysis)
	DDX_Check(pDX, IDC_CHECK1, m_CKey);
	DDX_Check(pDX, IDC_CHECK2, m_CKorr);
	DDX_Check(pDX, IDC_CHECK3, m_CHist);
	DDX_Check(pDX, IDC_CHECK6, m_VKey);
	DDX_Check(pDX, IDC_CHECK7, m_VLen);
	DDX_Check(pDX, IDC_CHECK8, m_VKorr);
	DDX_Check(pDX, IDC_CHECK4, m_VBase);
	DDX_Text(pDX, IDC_EDIT_ENTROPY_WINDOW, m_BFEntropyWindow);
	//}}AFX_DATA_MAP
	//DDV_MinMaxLong(pDX, m_BFEntropyWindow, 32, 4096); // see remark above
	DDX_Radio(pDX, IDC_RADIO1, i_alphabetOptions);
}


BEGIN_MESSAGE_MAP(CDlgOptionsAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsAnalysis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

