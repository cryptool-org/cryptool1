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
	Big a,s,w,min_k;
	UpdateData(true);
	CStringToBig(m_a,a,10);
	CStringToBig(m_s,s,10);
	CStringToBig(m_w,w,10);	
	CStringToBig(m_min_k,min_k,10);

	// pruefen, ob s und a den NB entsprechen
	if ((m_s!="") && (m_a!="") && (s>=0) && (s<=w) && (a>=0) && (a<=(min_k/w))) {
		OnOK();
	}
	else {
		AfxMessageBox(IDS_CRT_SECRETSHARING_FACTS3);
	}
}
