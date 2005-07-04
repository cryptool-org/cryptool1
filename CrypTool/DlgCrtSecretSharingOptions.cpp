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


// DlgCrtSecretSharingOptions.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCrtSecretSharingOptions.h"
#include ".\dlgcrtsecretsharingoptions.h"
#include "DialogeMessage.h"
#include "IntegerArithmetic.h"
#include "big.h"


// CDlgCrtSecretSharingOptions-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgCrtSecretSharingOptions, CDialog)
CDlgCrtSecretSharingOptions::CDlgCrtSecretSharingOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrtSecretSharingOptions::IDD, pParent)
	, m_anzahl(5)
	, m_need(3)
	, m_x(_T("2^108"))
	, m_y(_T("2^109"))
{
}

CDlgCrtSecretSharingOptions::~CDlgCrtSecretSharingOptions()
{
}

void CDlgCrtSecretSharingOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT1, m_anzahl);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT2, m_need);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT3, m_x);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT4, m_y);
	DDX_Control(pDX, IDC_CRT_SECRETSHARINGEDIT3, m_control_x);
	DDX_Control(pDX, IDC_CRT_SECRETSHARINGEDIT4, m_control_y);
}


BEGIN_MESSAGE_MAP(CDlgCrtSecretSharingOptions, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

// CDlgCrtSecretSharingOptions-Meldungshandler


void CDlgCrtSecretSharingOptions::OnBnClickedOk()
{
	UpdateData(true);
	GeneratePrimes P;
	int PSet;

if ( (m_anzahl >= 2) && (m_need <= m_anzahl) && (m_need>=2)&&(m_anzahl <=7)) {
	
	
	if(!( (0==m_x.IsEmpty()) && 
		  (0==m_y.IsEmpty()) ) )
	{
		Message( IDS_STRING_ENTER_UPPER_LOWER_BOUND, MB_ICONINFORMATION );
		return ;
	}
	
	CString UpnFormula;
	int err_ndx;
	BOOL error;
	
	error = CheckFormula(m_x,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_x.SetSel(err_ndx-1,m_x.GetLength());
		m_control_x.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONINFORMATION );
		return;
	}
	error = CheckFormula(m_y,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_y.SetSel(err_ndx-1,m_y.GetLength());
		m_control_y.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONINFORMATION );
		return;
	}

	Big zahl;Big zahlb;CString text="";CString textb="";
	CStringFormulaToBig(m_y,zahl);
	BigToCString(zahl,text,10);
	CStringFormulaToBig(m_x,zahlb);
	BigToCString(zahlb,textb,10);
	if ((zahl==0) || (text.GetLength()>33)) {
        AfxMessageBox(IDS_CRT_SECRETSHARING_GENERATEPRIME,MB_ICONINFORMATION );
	return;
	}
	if ((m_x!="0") &&((zahlb==0) || (textb.GetLength()>33))) {
        AfxMessageBox(IDS_CRT_SECRETSHARING_GENERATEPRIME,MB_ICONINFORMATION );
	return;
	}
	PSet=P.SetLimits( m_x, m_y );
	bool correct=true;
	if ( PSet==1)
			{
			}
			else if ( PSet == 3)
			{
			}
			else if ( PSet == 2)
			{
			}

			else if (  PSet ==1 )
			{
				m_control_x.SetFocus();
				m_control_x.SetSel(0,-1);
				Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
			return;
			}
			else 
			{
				m_control_x.SetFocus();
				m_control_x.SetSel(0,-1);
				Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
			return;
			}

	UpdateData(true);
    OnOK();
		

	}
	//Falls die Anzahl der Parteien kleiner als zwei gewählt wurde, 
	//oder die Anzahl der benötigten Parteien größer ist als die erste, gib folgendes aus:
else {
	

	CString helper1="";CString helper2="";CString helper3="";CString helper4="";	
	if (m_anzahl <2) helper1.Format(IDS_CRT_SECRETSHARINGHELP1,m_anzahl);

	if (m_anzahl >7) helper2.Format(IDS_CRT_SECRETSHARINGHELP2,m_anzahl);
	
	if (m_need > m_anzahl) helper3.Format(IDS_CRT_SECRETSHARINGHELP3,m_need);

	if ((m_need<2)&&(m_need > m_anzahl)) helper4.Format(IDS_CRT_SECRETSHARINGHELP4,m_need);
	
	if ((m_need<2)&&(m_need <=m_anzahl)) helper4.Format(IDS_CRT_SECRETSHARINGHELP5,m_need);

	AfxMessageBox(helper1+helper2+helper3+helper4, MB_ICONINFORMATION );
	
	return;
	}
	
}

void CDlgCrtSecretSharingOptions::OnBnClickedCancel()
{
	OnCancel();
}
