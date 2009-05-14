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


BOOL CDlgCrtSecretSharingOptions::OnInitDialog()
{
	UpdateData(false);
	// Pruefen ob automatische oder manuelle Ermittlung der Primzahlen 
	if (calcmode==1) {
		//manuelle Berechnung: blende Felder für Wertebereich aus
		m_x="";
		m_y="";
		UpdateData(false);
		GetDlgItem(IDC_CRT_SECRETSHARING_OPT_T2)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT3)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT4)->EnableWindow(false);
	}
	else {
		//automatische Berechnung
		GetDlgItem(IDC_CRT_SECRETSHARING_OPT_T2)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT3)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT4)->EnableWindow(true);
	}
	return true;
}

void CDlgCrtSecretSharingOptions::OnBnClickedOk()
{
	UpdateData(true);
	GeneratePrimes P;
	int PSet;

  // flomar, 12/04/2008
  // here we catch the special case k=n
  if(m_anzahl == m_need) {
    char temp[STR_LAENGE_STRING_TABLE];
    LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRET_SHARING_K_EQUALS_N, pc_str, STR_LAENGE_STRING_TABLE);
    sprintf(temp, pc_str, m_anzahl);
    MessageBox(temp, "CrypTool", MB_ICONINFORMATION);
    return;
  }	

if ( (m_anzahl >= 2) && (m_need <= m_anzahl) && (m_need>=2)&&(m_anzahl <=7)) {
	
	if (calcmode==1) {
		m_x="2^108";
		m_y="2^109";
	}

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
