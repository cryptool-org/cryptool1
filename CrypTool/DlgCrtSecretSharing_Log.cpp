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

// DlgCrtSecretSharing_Log.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "afx.h"
#include "CrypToolTools.h"
#include "FileTools.h"
#include "CrypToolApp.h"
#include "DlgCrtSecretSharing_Log.h"
#include ".\dlgcrtsecretsharing_log.h"
// #include <fstream.h>

// CDlgCrtSecretSharing_Log-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgCrtSecretSharing_Log, baseCTestDlg)
CDlgCrtSecretSharing_Log::CDlgCrtSecretSharing_Log(CWnd* pParent /*=NULL*/)
	: baseCTestDlg(CDlgCrtSecretSharing_Log::IDD, pParent)
	, m_log(_T(""))
{}


CDlgCrtSecretSharing_Log::~CDlgCrtSecretSharing_Log()
{
}

void CDlgCrtSecretSharing_Log::DoDataExchange(CDataExchange* pDX)
{
	baseCTestDlg::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRT_LOG, m_log);
}


BEGIN_MESSAGE_MAP(CDlgCrtSecretSharing_Log, baseCTestDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CRT_SecretSharing_Log_Save, OnBnClickedCrtSecretsharingLogSave)
END_MESSAGE_MAP()


// DlgCrtSecretSharing_Log-Meldungshandler

BOOL CDlgCrtSecretSharing_Log::OnInitDialog()
{	
	CString temp1, temp2;
	//Fenstertitel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARING_LOGTITLE);
	this->SetWindowText((LPCTSTR)temp1);

	this->AddResizaleCtrl(IDC_CRT_LOG, _T("C"));
	this->AddResizaleCtrlRange(IDC_CRT_SecretSharing_Log_Save,IDC_BUTTON1, _T("XY"));
	
	this->SendMessage(WM_SIZE);


	UpdateData(false);
	return TRUE;
}
void CDlgCrtSecretSharing_Log::OnBnClickedButton1()
{ 
	OnOK(); 
}

void CDlgCrtSecretSharing_Log::OnBnClickedCrtSecretsharingLogSave()
{
	
	char *filename = new char[CRYPTOOL_PATH_LENGTH];
	GetTmpName(filename, "SecretSharing-Log", ".txt");
	ofstream Outfile;
	Outfile.open(filename, ios::out | ios::trunc);
	Outfile << this->m_log;
	Outfile.close();
	CAppDocument *NewDoc = theApp.OpenDocumentFileNoMRU(filename);
	delete filename;	
	GetDlgItem(IDC_CRT_SecretSharing_Log_Save)->EnableWindow(false);
	
	CString dummy2;
	dummy2.LoadString(IDS_CRT_SECRETSHARING_LOGWRITTEN);
	AfxMessageBox(dummy2);


	OnOK();
}


