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


// DlgCrtSecretSharing_Facts.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "stdlib.h"
#include "CrypToolApp.h"
#include "DlgCrtSecretSharing_Facts.h"
#include ".\dlgcrtsecretsharing_Facts.h"
#include "DlgCrtSecretSharing_Log.h"
#include "DialogeMessage.h"


// CDlgCrtSecretSharing_Facts-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgCrtSecretSharing_Facts, CDialog)
CDlgCrtSecretSharing_Facts::CDlgCrtSecretSharing_Facts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrtSecretSharing_Facts::IDD, pParent)
	, m_anzahl(2)
	, m_min_k(_T(""))
	, m_max_kminus1(_T(""))
	, m_w(_T(""))
	, m_s(_T(""))
	, m_a(_T(""))
	, m_s_(_T(""))
	
	, m_CrtFacts1(_T(""))
	, m_CrtFacts2(_T(""))
{
}

CDlgCrtSecretSharing_Facts::~CDlgCrtSecretSharing_Facts()
{
}

void CDlgCrtSecretSharing_Facts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRT_FACT1, m_min_k);
	DDX_Text(pDX, IDC_CRT_FACT2, m_max_kminus1);
	DDX_Text(pDX, IDC_CRT_FACT3, m_w);
	DDX_Text(pDX, IDC_CRT_FACT4, m_s);
	DDX_Text(pDX, IDC_CRT_FACT5, m_a);
	DDX_Text(pDX, IDC_CRT_FACT6, m_s_);
	DDX_Text(pDX, IDC_CRT_FACTS1, m_CrtFacts1);
	DDX_Text(pDX, IDC_CRT_FACTS2, m_CrtFacts2);
}


BEGIN_MESSAGE_MAP(CDlgCrtSecretSharing_Facts, CDialog)
	ON_BN_CLICKED(IDC_CRT_SHOWLOG, OnBnClickedCrtShowlog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCrtSecretSharing_Facts-Meldungshandler


void CDlgCrtSecretSharing_Facts::OnBnClickedCrtShowlog()
{
	CDlgCrtSecretSharing_Log* newdialog= new CDlgCrtSecretSharing_Log();
		newdialog->m_log = m_log;
		newdialog->m_need = m_need;
		newdialog->m_anzahl = m_anzahl;
	
	if (IDOK == newdialog->DoModal())	{}
	delete newdialog;
}


void CDlgCrtSecretSharing_Facts::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnOK();
}
