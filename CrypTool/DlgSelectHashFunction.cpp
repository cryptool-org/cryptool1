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

// SelctAHashfunction.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSelectHashFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSelectHashFunction 


CDlgSelectHashFunction::CDlgSelectHashFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectHashFunction::IDD, pParent)
{
	m_deactivateMD4 = false;
	m_deactivateSHA2 = false;
	m_sHashAlg = "MD2";
	//{{AFX_DATA_INIT(CDlgSelectHashFunction)
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = -1;
	//}}AFX_DATA_INIT
}


void CDlgSelectHashFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectHashFunction)
	DDX_Control(pDX, IDC_RADIO2, m_selectedHashFunctionMD4Ctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_selectedHashFunctionMD2);
	DDX_Radio(pDX, IDC_RADIO2, m_selectedHashFunctionMD4);
	DDX_Radio(pDX, IDC_RADIO3, m_selectedHashFunctionMD5);
	DDX_Radio(pDX, IDC_RADIO4, m_selectedHashFunctionSHA);
	DDX_Radio(pDX, IDC_RADIO5, m_selectedHashFunctionSHA_1);
	DDX_Radio(pDX, IDC_RADIO7, m_selectedHashFunctionSHA_256);
	DDX_Radio(pDX, IDC_RADIO8, m_selectedHashFunctionSHA_512);
	DDX_Radio(pDX, IDC_RADIO6, m_selectedHashFunctionRIPEMD_160);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectHashFunction, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectHashFunction)
	ON_BN_CLICKED(IDC_RADIO1, OnSelectedMD2)
	ON_BN_CLICKED(IDC_RADIO2, OnSelectedMD4)
	ON_BN_CLICKED(IDC_RADIO3, OnSelectedMD5)
	ON_BN_CLICKED(IDC_RADIO4, OnSelectSHA)
	ON_BN_CLICKED(IDC_RADIO5, OnSelectedSHA_1)
	ON_BN_CLICKED(IDC_RADIO7, OnSelectedSHA_256)
	ON_BN_CLICKED(IDC_RADIO8, OnSelectedSHA_512)
	ON_BN_CLICKED(IDC_RADIO6, OnSelectedRIPEMD_160)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSelectHashFunction 

void CDlgSelectHashFunction::OnSelectedMD2() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_selectedHashFunctionMD2 = 0;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = -1;
	m_selectedHashFunction = 0;
	UpdateData(FALSE);	
}

void CDlgSelectHashFunction::OnSelectedMD4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = 0;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = -1;
	m_selectedHashFunction = 1;
	UpdateData(FALSE);		
}

void CDlgSelectHashFunction::OnSelectedMD5() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = 0;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = -1;
	UpdateData(FALSE);		
	m_selectedHashFunction = 2;
}

void CDlgSelectHashFunction::OnSelectSHA() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = 0;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = -1;
	UpdateData(FALSE);		
	m_selectedHashFunction = 3;
}

void CDlgSelectHashFunction::OnSelectedSHA_1() 
{
	// TODO: Code fü	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = 0;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = -1;
	UpdateData(FALSE);		
	m_selectedHashFunction = 4;
}

void CDlgSelectHashFunction::OnSelectedSHA_256() 
{
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = 0;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = -1;
	UpdateData(FALSE);		
	m_selectedHashFunction = 6;
}

void CDlgSelectHashFunction::OnSelectedSHA_512() 
{
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = 0;
	m_selectedHashFunctionRIPEMD_160 = -1;
	UpdateData(FALSE);		
	m_selectedHashFunction = 7;
}

void CDlgSelectHashFunction::OnSelectedRIPEMD_160() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_selectedHashFunctionMD2 = -1;
	m_selectedHashFunctionMD4 = -1;
	m_selectedHashFunctionMD5 = -1;
	m_selectedHashFunctionSHA = -1;
	m_selectedHashFunctionSHA_1 = -1;
	m_selectedHashFunctionSHA_256 = -1;
	m_selectedHashFunctionSHA_512 = -1;
	m_selectedHashFunctionRIPEMD_160 = 0;
	UpdateData(FALSE);		
	m_selectedHashFunction = 5;	
}

BOOL CDlgSelectHashFunction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	if ( m_deactivateMD4 )
	{
		m_selectedHashFunctionMD4Ctrl.EnableWindow(false);		
	}

	if ( m_deactivateSHA2 )
	{
		GetDlgItem(IDC_RADIO7)->EnableWindow(false);
		GetDlgItem(IDC_RADIO8)->EnableWindow(false);
	}

	if(m_sHashAlg=="MD2")			OnSelectedMD2();
	if(m_sHashAlg=="MD4")			OnSelectedMD4(); 
	if(m_sHashAlg=="MD5")			OnSelectedMD5(); 	
	if(m_sHashAlg=="SHA")			OnSelectSHA();
	if(m_sHashAlg=="SHA-1")			OnSelectedSHA_1();
	if(m_sHashAlg=="SHA-256")		OnSelectedSHA_256();
	if(m_sHashAlg=="SHA-512")		OnSelectedSHA_512();
	if(m_sHashAlg=="RIPEMD-160")	OnSelectedRIPEMD_160(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgSelectHashFunction::OnOK() 
{
	switch(m_selectedHashFunction)
	{
		case 0: m_sHashAlg = "MD2"; break;
		case 1: m_sHashAlg = "MD4"; break;
		case 2: m_sHashAlg = "MD5"; break;
		case 3: m_sHashAlg = "SHA"; break;
		case 4: m_sHashAlg = "SHA-1"; break;
		case 6: m_sHashAlg = "SHA-256"; break;
		case 7: m_sHashAlg = "SHA-512"; break;
		case 5: m_sHashAlg = "RIPEMD-160"; break;
		default: m_sHashAlg.Empty();
	}
	CDialog::OnOK();
}
