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
// Behandlungsroutinen f�r Nachrichten CDlgOptionsSignatureAttack 

BOOL CDlgOptionsSignatureAttack::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS ) == ERROR_SUCCESS )
	{
		unsigned long u_hashalgorithm_ID = 0;
		CT_READ_REGISTRY_DEFAULT(u_hashalgorithm_ID, "SignatureAttackHashAlgorithmID", u_hashalgorithm_ID);
		if (u_hashalgorithm_ID < 0 || u_hashalgorithm_ID > 5) 
		{
			u_hashalgorithm_ID = 0;
			CT_WRITE_REGISTRY(u_hashalgorithm_ID, "SignatureAttackHashAlgorithmID");
		}
		m_hashalgorithm = u_hashalgorithm_ID;

		unsigned long u_bitLength = _OPT_SIG_ATT_STANDARD_BITLENGTH;
		CT_READ_REGISTRY_DEFAULT(u_bitLength, "SignatureAttackSignificantBitLength", u_bitLength);
		m_bitlength = CString(_itoa(u_bitLength, NULL, 10));

		unsigned long u_mod_method = 0;
		CT_READ_REGISTRY_DEFAULT(u_mod_method, "SignatureAttackModificationMethod", u_mod_method);
		if (u_mod_method < 0 || u_mod_method > 1) 
		{
			u_mod_method = 0;
			CT_WRITE_REGISTRY(u_mod_method, "SignatureAttackModificationMethod");
		}
		m_mod_method = u_mod_method;

		unsigned long u_check1 = 1;
		CT_READ_REGISTRY_DEFAULT(u_check1, "SignatureAttackCheck1", u_check1);
		m_control_check1.SetCheck((int)u_check1);

		unsigned long u_check3 = 1;
		CT_READ_REGISTRY_DEFAULT(u_check3, "SignatureAttackCheck3", u_check3);
		m_control_check3.SetCheck((int)u_check3);

		unsigned long u_att_method = 0;
		CT_READ_REGISTRY_DEFAULT(u_att_method, "SignatureAttackAttMethod", u_att_method);
		if (u_att_method < 0 || u_att_method > 1) 
		{
			u_att_method = 0;
			CT_WRITE_REGISTRY(u_att_method, "SignatureAttackAttMethod");
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
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
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

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY((unsigned long)m_hashalgorithm, "SignatureAttackHashAlgorithmID");
		unsigned long u_bitlength = (unsigned long)atoi(m_bitlength);
		CT_WRITE_REGISTRY(u_bitlength, "SignatureAttackSignificantBitLength");
		CT_WRITE_REGISTRY((unsigned long)m_mod_method, "SignatureAttackModificationMethod");
		CT_WRITE_REGISTRY((unsigned long)m_control_check1.GetCheck(), "SignatureAttackCheck1");
		CT_WRITE_REGISTRY((unsigned long)m_control_check3.GetCheck(), "SignatureAttackCheck3");
		CT_WRITE_REGISTRY((unsigned long)m_att_method, "SignatureAttackAttMethod");
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

	m_hashalgorithm = 0;
	m_bitlength = itoa(_OPT_SIG_ATT_STANDARD_BITLENGTH, NULL, 10);
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
