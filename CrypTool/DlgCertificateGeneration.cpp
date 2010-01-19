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

// DlgCertTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCertificateGeneration.h"
#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCertificateGeneration 


CDlgCertificateGeneration::CDlgCertificateGeneration(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCertificateGeneration::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCertificateGeneration)
	m_sDName = _T("");
	m_sFirstName = _T("");
	m_sKeyID = _T("");
	m_sName = _T("");
	m_sUserID = _T("");
	m_sBitLength = _T("");
	m_sPIN = _T("");
	m_sPINv = _T("");
	m_sKeyPublic = _T("");
	m_sModN = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCertificateGeneration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCertificateGeneration)
	DDX_Control(pDX, IDC_EDIT_CERT_PIN_VERIFY, m_CtrlPINv);
	DDX_Control(pDX, IDC_EDIT_CERT_PIN, m_CtrlPIN);
	DDX_Control(pDX, IDC_EDIT_CERT_KEY_ID, m_CtrlKeyID);
	DDX_Control(pDX, IDC_EDIT_CERT_FIRSTNAME, m_CtrlFirstName);
	DDX_Control(pDX, IDC_EDIT_CERTNAME, m_CtrlName);
	DDX_Control(pDX, IDOK, m_CtrlOK);
	DDX_Text(pDX, IDC_EDIT_CERT_DNAME, m_sDName);
	DDX_Text(pDX, IDC_EDIT_CERT_FIRSTNAME, m_sFirstName);
	DDX_Text(pDX, IDC_EDIT_CERT_KEY_ID, m_sKeyID);
	DDX_Text(pDX, IDC_EDIT_CERTNAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_CERT_USER_ID, m_sUserID);
	DDX_Text(pDX, IDC_EDIT_RSA_BITLENGTH, m_sBitLength);
	DDX_Text(pDX, IDC_EDIT_CERT_PIN, m_sPIN);
	DDX_Text(pDX, IDC_EDIT_CERT_PIN_VERIFY, m_sPINv);
	DDX_Text(pDX, IDC_EDIT_RSA_KEY_PUBLIC, m_sKeyPublic);
	DDX_Text(pDX, IDC_EDIT_RSA_MODUL_N, m_sModN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCertificateGeneration, CDialog)
	//{{AFX_MSG_MAP(CDlgCertificateGeneration)
	ON_EN_CHANGE(IDC_EDIT_CERTNAME, OnChangeEdit)
	ON_BN_CLICKED(IDC_PSE_IMPORT, OnPseImport)
	ON_EN_CHANGE(IDC_EDIT_CERT_FIRSTNAME, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_CERT_KEY_ID, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCertificateGeneration 


BOOL CDlgCertificateGeneration::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	ASSERT(m_Cert); // Zertifikat muß initialisiert sein -> InitRSA

	UpdateData(TRUE);
	
	m_Cert->GetName(m_sName, m_sFirstName, m_sKeyID); // Zertifikatsdaten holen
	m_sPINv = m_sPIN = m_Cert->GetPIN();
	m_lTime = (time_t)m_Cert->GetTime();
	
	//if( !(m_sName.IsEmpty()&&m_sFirstName.IsEmpty()&&m_sKeyID.IsEmpty()) ) 
	if( m_Cert->PSEIsInitialized() )
	{
		m_sUserID = m_Cert->CreateUserKeyID(m_sName, m_sFirstName, m_sKeyID, (long)m_lTime);
		m_sDName = m_Cert->CreateDisName(m_sName, m_sFirstName, (long)m_lTime);
	}
	
	if(m_Cert->IsInitialized())
	{
		// Schlüssel vorhanden:
		CString sBuffer;
		m_Cert->GetParameter(m_sModN, sBuffer, m_sKeyPublic, sBuffer);
		m_sBitLength.Format(IDS_BIT, m_Cert->GetBitLength());

	}
	m_CtrlFirstName.EnableWindow(m_Cert->IsInitialized());
	m_CtrlName.EnableWindow(m_Cert->IsInitialized());
	m_CtrlPIN.EnableWindow(m_Cert->IsInitialized());
	m_CtrlPINv.EnableWindow(m_Cert->IsInitialized());
	m_CtrlKeyID.EnableWindow(m_Cert->IsInitialized());
	m_CtrlOK.EnableWindow(TRUE);

	UpdateData(FALSE);
	
	m_CtrlName.SetFocus();
	return FALSE; // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgCertificateGeneration::InitRSA(CPSEDemo* Cert)
{
	m_Cert = Cert;
}

void CDlgCertificateGeneration::OnChangeEdit() 
{
	UpdateData(TRUE);

	time(&m_lTime);

	m_sUserID = m_Cert->CreateUserKeyID(m_sName, m_sFirstName, m_sKeyID, (long)m_lTime);
	m_sDName = m_Cert->CreateDisName(m_sName, m_sFirstName, (long)m_lTime);

	if(m_Cert->IsInitialized()) m_CtrlOK.EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CDlgCertificateGeneration::OnOK() 
{
	UpdateData(TRUE);

	if(m_sName.IsEmpty())
	{
		AfxMessageBox(IDS_NOTIFY_NAME);
		m_CtrlName.SetFocus();
		return;
	}
	if(m_sFirstName.IsEmpty())
	{
		AfxMessageBox(IDS_NOTIFY_FIRST_NAME);
		m_CtrlFirstName.SetFocus();
		return;
	}
	if(m_sPIN.IsEmpty())
	{
		AfxMessageBox(IDS_NOTIFY_PIN);
		m_CtrlPIN.SetFocus();
		return;
	}
	if(m_sPIN != m_sPINv)
	{
		AfxMessageBox(IDS_NOTIFY_PIN_V);
		m_CtrlPINv.SetFocus();
		return;
	}
	m_Cert->SetPIN(m_sPIN);
	m_Cert->SetName(m_sName, m_sFirstName, m_sKeyID);
	m_Cert->SetTime((long)m_lTime);
	
	m_PSEIsExtern = FALSE;
	CDialog::OnOK();
}

void CDlgCertificateGeneration::OnPseImport() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if(m_Cert->AccessPSE_DLG())	
	{
		m_PSEIsExtern = TRUE;
		CDialog::OnOK();
	}
}

