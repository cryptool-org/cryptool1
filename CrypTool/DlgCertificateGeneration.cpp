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
	DDX_Control(pDX, IDC_EDIT_CERT_NAME, m_CtrlName);
	DDX_Control(pDX, IDOK, m_CtrlOK);
	DDX_Text(pDX, IDC_EDIT_CERT_DNAME, m_sDName);
	DDX_Text(pDX, IDC_EDIT_CERT_FIRSTNAME, m_sFirstName);
	DDX_Text(pDX, IDC_EDIT_CERT_KEY_ID, m_sKeyID);
	DDX_Text(pDX, IDC_EDIT_CERT_NAME, m_sName);
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
	ON_EN_CHANGE(IDC_EDIT_CERT_NAME, OnChangeEdit)
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
	m_lTime = m_Cert->GetTime();
	
	//if( !(m_sName.IsEmpty()&&m_sFirstName.IsEmpty()&&m_sKeyID.IsEmpty()) ) 
	if( m_Cert->PSEIsInitialized() )
	{
		m_sUserID = m_Cert->CreateUserKeyID(m_sName, m_sFirstName, m_sKeyID, m_lTime);
		m_sDName = m_Cert->CreateDisName(m_sName, m_sFirstName, m_lTime);
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
	m_CtrlOK.EnableWindow(FALSE);

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
	// TODO: Wenn dies ein RICHEDIT-Steuerelement ist, sendet das Steuerelement diese

	// Benachrichtigung nicht, bevor Sie nicht die Funktion CDialog::OnInitDialog()

	// überschreiben und CRichEditCrtl().SetEventMask() aufrufen, wobei

	// eine ODER-Operation mit dem Attribut ENM_CHANGE und der Maske erfolgt.
	UpdateData(TRUE);
	time((time_t*)&m_lTime);

	
	m_sUserID = m_Cert->CreateUserKeyID(m_sName, m_sFirstName, m_sKeyID, m_lTime);
	m_sDName = m_Cert->CreateDisName(m_sName, m_sFirstName, m_lTime);
	UpdateData(FALSE);
	if(m_Cert->IsInitialized()) m_CtrlOK.EnableWindow(TRUE);
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
	m_Cert->SetTime(m_lTime);
	
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

