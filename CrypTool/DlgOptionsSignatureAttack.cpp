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

// DlgOptionsSignatureAttack.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsSignatureAttack.h"
#include "HashingOperations.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSignatureAttack 


CDlgOptionsSignatureAttack::CDlgOptionsSignatureAttack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsSignatureAttack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsSignatureAttack)
	m_hashalgorithm = 0;
	m_bitlength = _T("");
	m_mod_method = -1;
	m_att_method = -1;
	//}}AFX_DATA_INIT
}


void CDlgOptionsSignatureAttack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsSignatureAttack)
	DDX_Control(pDX, IDC_RADIO9, m_control_att_print);
	DDX_Control(pDX, IDC_RADIO10, m_control_att_unprint);
	DDX_Control(pDX, IDC_RADIO7, m_control_mod_method);
	DDX_Control(pDX, IDC_EDIT1, m_control_bitlength);
	DDX_Control(pDX, IDC_STATIC_SIG_ATT_BITLENGTH_RANGE, m_control_bitlength_range);
	DDX_Control(pDX, IDC_CHECK1, m_control_check1);
	DDX_Control(pDX, IDC_CHECK3, m_control_check3);
	DDX_Control(pDX, IDC_RADIO1, m_control_md2);
	DDX_Radio(pDX, IDC_RADIO1, m_hashalgorithm);
	DDX_Text(pDX, IDC_EDIT1, m_bitlength);
	DDV_MaxChars(pDX, m_bitlength, 4);
	DDX_Radio(pDX, IDC_RADIO7, m_mod_method);
	DDX_Radio(pDX, IDC_RADIO9, m_att_method);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsSignatureAttack, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsSignatureAttack)
	ON_BN_CLICKED(IDC_RADIO1, OnMD2)
	ON_BN_CLICKED(IDC_RADIO2, OnMD4)
	ON_BN_CLICKED(IDC_RADIO3, OnMD5)
	ON_BN_CLICKED(IDC_RADIO4, OnSHA)
	ON_BN_CLICKED(IDC_RADIO5, OnSHA_1)
	ON_BN_CLICKED(IDC_RADIO6, OnRIPEMD_160)
	ON_BN_CLICKED(IDC_BUTTON1, OnResetToDefault)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsSignatureAttack 

BOOL CDlgOptionsSignatureAttack::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SignatureAttack" ) == ERROR_SUCCESS )
	{
		char strBuffer[20];
		unsigned long u_hashalgorithm_ID = 0;
		CT_READ_REGISTRY_DEFAULT(u_hashalgorithm_ID, "HashAlgorithmID", u_hashalgorithm_ID);
		if (u_hashalgorithm_ID < 0 || u_hashalgorithm_ID > 5) 
		{
			u_hashalgorithm_ID = 0;
			CT_WRITE_REGISTRY(u_hashalgorithm_ID, "HashAlgorithmID");
		}
		m_hashalgorithm = u_hashalgorithm_ID;

		unsigned long u_bitLength = _OPT_SIG_ATT_STANDARD_BITLENGTH;
		CT_READ_REGISTRY_DEFAULT(u_bitLength, "SignificantBitLength", u_bitLength);
		_itoa(u_bitLength, strBuffer, 10);
		m_bitlength = strBuffer;

		unsigned long u_mod_method = 0;
		CT_READ_REGISTRY_DEFAULT(u_mod_method, "ModificationMethod", u_mod_method);
		if (u_mod_method < 0 || u_mod_method > 1) 
		{
			u_mod_method = 0;
			CT_WRITE_REGISTRY(u_mod_method, "ModificationMethod");
		}
		m_mod_method = u_mod_method;

		unsigned long u_check1 = 1;
		CT_READ_REGISTRY_DEFAULT(u_check1, "ModfiyBlankEOL", u_check1);
		m_control_check1.SetCheck((int)u_check1);

		unsigned long u_check3 = 1;
		CT_READ_REGISTRY_DEFAULT(u_check3, "ModifyDoubleBlank", u_check3);
		m_control_check3.SetCheck((int)u_check3);

		unsigned long u_att_method = 0;
		CT_READ_REGISTRY_DEFAULT(u_att_method, "ModifyCharSet", u_att_method);
		if (u_att_method < 0 || u_att_method > 1) 
		{
			u_att_method = 0;
			CT_WRITE_REGISTRY(u_att_method, "ModifyCharSet");
		}
		m_att_method = u_att_method;

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}


	SetTextBitlengthRange();

	if (0 == m_mod_method)
	{
		m_control_check1.EnableWindow(TRUE);
		m_control_check3.EnableWindow(TRUE);
		m_control_att_print.EnableWindow(FALSE);
		m_control_att_unprint.EnableWindow(FALSE);
	}
	else if (1 == m_mod_method)
	{
		m_control_check1.EnableWindow(FALSE);
		m_control_check3.EnableWindow(FALSE);
		m_control_att_print.EnableWindow(TRUE);
		m_control_att_unprint.EnableWindow(TRUE);
	}
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgOptionsSignatureAttack::OnMD2() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 0;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnMD4() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 1;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnMD5() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 2;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnSHA() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 3;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnSHA_1() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 4;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnRIPEMD_160() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 5;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnOK() 
{
	UpdateData(TRUE);

	CString msg;
	int maxbit;
	HashingOperations HO(m_hashalgorithm);
	
	maxbit = HO.GetHashAlgorithmBitLength();

	if (atoi(m_bitlength) > maxbit || atoi(m_bitlength) < 1)
	{
		msg.Format(IDS_STRING_SIG_ATT_BAD_BITLENGTH, maxbit);
		MessageBox(msg, "CrypTool", MB_ICONEXCLAMATION | MB_APPLMODAL);
		m_control_bitlength.SetSel(0, -1);
		m_control_bitlength.SetFocus();
				
		return;
	}

	if (0 == m_mod_method && 1 != m_control_check1.GetCheck() && 1 != m_control_check3.GetCheck())
	{
		msg.Format(IDS_STRING_SIG_ATT_NO_CHECK);
		MessageBox(msg, "CrypTool", MB_ICONEXCLAMATION | MB_APPLMODAL);
		m_control_check1.SetCheck(1);

		return;
	}

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "SignatureAttack" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY((unsigned long)m_hashalgorithm, "HashAlgorithmID");
		unsigned long u_bitlength = (unsigned long)atoi(m_bitlength);
		CT_WRITE_REGISTRY(u_bitlength, "SignificantBitLength");
		CT_WRITE_REGISTRY((unsigned long)m_mod_method, "ModificationMethod");
		CT_WRITE_REGISTRY((unsigned long)m_control_check1.GetCheck(), "ModfiyBlankEOL");
		CT_WRITE_REGISTRY((unsigned long)m_control_check3.GetCheck(), "ModifyDoubleBlank");
		CT_WRITE_REGISTRY((unsigned long)m_att_method, "ModifyCharSet");
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}	

	CDialog::OnOK();
}

void CDlgOptionsSignatureAttack::OnResetToDefault() 
{
	UpdateData(TRUE);

	char strBuffer[20];
	m_hashalgorithm = 0; 
	_itoa(_OPT_SIG_ATT_STANDARD_BITLENGTH, strBuffer, 10);
	m_bitlength = strBuffer;
	m_mod_method = 0;
	m_control_check1.SetCheck(1);
	m_control_check1.EnableWindow(TRUE);
	m_control_check3.SetCheck(1);
	m_control_check3.EnableWindow(TRUE);
	m_control_att_print.EnableWindow(FALSE);
	m_control_att_unprint.EnableWindow(FALSE);

	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnUpdateEdit1() 
{
	UpdateData(TRUE);

	int ii;

	if (TRUE == m_bitlength.IsEmpty())
	{
		return;
	}

	for (ii = 0; ii < m_bitlength.GetLength(); ii ++)
	{
		if (m_bitlength.GetAt(ii) < '0' || m_bitlength.GetAt(ii) > '9')
		{
			m_bitlength.Delete(ii, 1);
		}
	}	

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::SetTextBitlengthRange()
{
	CString msg;
	HashingOperations HO(m_hashalgorithm);
	if (0 != HO.GetErrorcode())
	{
		return;
	}

	msg.Format(IDS_STRING_SIG_ATT_BITLENGTH_RANGE, HO.GetHashAlgorithmBitLength());
	m_control_bitlength_range.SetWindowText(msg);
}

void CDlgOptionsSignatureAttack::OnRadio7() 
{
	m_mod_method = 0;
	
	m_control_check1.EnableWindow(TRUE);
	m_control_check3.EnableWindow(TRUE);
	m_control_att_print.EnableWindow(FALSE);
	m_control_att_unprint.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnRadio8() 
{
	m_mod_method = 1;

	m_control_check1.EnableWindow(FALSE);
	m_control_check3.EnableWindow(FALSE);
	m_control_att_print.EnableWindow(TRUE);
	m_control_att_unprint.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnRadio9() 
{
	m_att_method = 0;
}

void CDlgOptionsSignatureAttack::OnRadio10() 
{
	m_att_method = 1;
}
