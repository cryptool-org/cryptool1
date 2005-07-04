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


// DlgCrtSecretSharing_Log.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCrtSecretSharing_Log.h"
#include ".\dlgcrtsecretsharing_log.h"


// CDlgCrtSecretSharing_Log-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgCrtSecretSharing_Log, CDialog)
CDlgCrtSecretSharing_Log::CDlgCrtSecretSharing_Log(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrtSecretSharing_Log::IDD, pParent)
	, m_log(_T(""))
{

}

CDlgCrtSecretSharing_Log::~CDlgCrtSecretSharing_Log()
{
}

void CDlgCrtSecretSharing_Log::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRT_LOG, m_log);
}


BEGIN_MESSAGE_MAP(CDlgCrtSecretSharing_Log, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// DlgCrtSecretSharing_Log-Meldungshandler

BOOL CDlgCrtSecretSharing_Log::OnInitDialog()
{	
	CString temp1, temp2;
	//Fenstertitel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGTITLE);
	temp2.Format((LPCTSTR)temp1,m_need,m_anzahl);
	this->SetWindowText((LPCTSTR)temp2);
	UpdateData(false);
	return TRUE;
}

void CDlgCrtSecretSharing_Log::OnBnClickedButton1()
{ 
	OnOK(); 
}
