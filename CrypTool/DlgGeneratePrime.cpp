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

// DlgGeneratePrime.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include <stdlib.h>

#include "DlgGeneratePrime.h"
#include "Keyrepository.h"
#include "DialogeMessage.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgGeneratePrime 


CDlgGeneratePrime::CDlgGeneratePrime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGeneratePrime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGeneratePrime)
	m_radio1 = 0;
	m_edit1 = _T("2^7");
	m_edit2 = _T("2^8");
	m_edit5 = _T("0");
	//}}AFX_DATA_INIT
}


void CDlgGeneratePrime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGeneratePrime)
	DDX_Control(pDX, IDC_EDIT2, m_control_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_control_edit1);
	DDX_Control(pDX, IDC_BUTTON_GENERATE, m_control_button_generate);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT, m_control_button_accept);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGeneratePrime, CDialog)
	//{{AFX_MSG_MAP(CDlgGeneratePrime)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, OnButtonAccept)
	ON_BN_CLICKED(IDC_ENDDIALOG, OnEndDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgGeneratePrime 

BOOL CDlgGeneratePrime::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Zusätzliche Initialisierung hier einfügen
	m_control_button_accept.EnableWindow(false);

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


BOOL CDlgGeneratePrime::GetRandomPrime(CString &OutStr, GeneratePrimes &P)
{
	BOOL flag = FALSE;

	for ( int i=1; i<=2000 && !flag; i++ )			 // 
	{
		P.RandP();
				
		if (0==m_radio1) flag = P.MillerRabinTest(100);
		if (1==m_radio1) flag = P.SolvayStrassenTest(100);
		if (2==m_radio1) flag = P.FermatTest(100);
	}
    if (flag)
	{
		P.GetPrime( OutStr );
	}
	else
	{
		OutStr = "0";
	}
	return flag;			// wenn keine Primzahl innerhalb der Grenzen gefunden wurde, erfolgt eine
						// entsprechende Fehlermeldung
}

//==============================================================================================================
void CDlgGeneratePrime::OnButtonGenerate() 
// erzeugt zwei Zufalls-Primzahlen innerhalb der angegebenen Grenzen
// Fehler werden mit entsprechenden Messages behandelt
{
	UpdateData(true);

	GeneratePrimes P;
	int PSet;
	
	if(!( (0==m_edit1.IsEmpty()) && 
		  (0==m_edit2.IsEmpty()) ) )
	{
		Message( IDS_STRING_ENTER_UPPER_LOWER_BOUND, MB_ICONINFORMATION );
		return;
	}
	
	CString UpnFormula;
	int err_ndx;
	BOOL error;
	
	error = CheckFormula(m_edit1,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit1.SetSel(err_ndx-1,m_edit1.GetLength());
		m_control_edit1.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	error = CheckFormula(m_edit2,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit2.SetSel(err_ndx-1,m_edit2.GetLength());
		m_control_edit2.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	
	PSet=P.SetLimits( m_edit1, m_edit2 );
	if ( (PSet == 1) )
	{
		SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
		if ( !GetRandomPrime( m_edit5, P ) ) Message( IDS_STRING_MSG_LEFT_PRIMES_NOT_FOUND, MB_ICONSTOP );
		HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
	}
	else if ( PSet == 3)
	{
		m_control_edit1.SetFocus();
		m_control_edit1.SetSel(0,-1);
		Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
	}
	else if ( PSet == 2)
	{
		m_control_edit2.SetFocus();
		m_control_edit2.SetSel(0,-1);
		Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
	}

	if("0"!=m_edit5)
	{
		m_control_button_accept.EnableWindow(true);
	}

	UpdateData(false);
}

//===============================================================================================
void CDlgGeneratePrime::OnButtonAccept() 

// wenn der Button "Übernehmen" gewählt wird, kann der Dialog nur verlassen werden,
// wenn das Produkt der beiden Primzahlen kleiner als c_MaxPrime_high ist

{
	UpdateData(true);
	if ( m_edit5 != "0" )
	{
		CDialog::OnOK();
	}
	UpdateData(false);
}

void CDlgGeneratePrime::OnEndDialog() 
{
	UpdateData(true);
	m_edit5="0";	
	CDialog::OnCancel();
	UpdateData(false);
}



