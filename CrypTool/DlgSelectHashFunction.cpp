/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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
// Behandlungsroutinen f�r Nachrichten CDlgSelectHashFunction 

void CDlgSelectHashFunction::OnSelectedMD2() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
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
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
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
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
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
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
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
	// TODO: Code f�	m_selectedHashFunctionMD2 = -1;
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
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
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
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen
	if ( m_deactivateMD4 )
	{
		m_selectedHashFunctionMD4Ctrl.EnableWindow(false);		
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
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
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
