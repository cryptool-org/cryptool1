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


// DlgPrimesGenerator.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "CrypToolApp.h"
#include <stdlib.h>

#include "DlgPrimesGeneratorDemo.h"
#include "Keyrepository.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgPrimesGeneratorDemo 


CDlgPrimesGeneratorDemo::CDlgPrimesGeneratorDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrimesGeneratorDemo::IDD, pParent)
{
	m_hide_button_accept = false;
	//{{AFX_DATA_INIT(CDlgPrimesGeneratorDemo)
	m_radio1 = 0;
	m_radio4 = 0;
	m_edit1 = _T("2^7");
	m_edit2 = _T("2^8");
	m_edit3 = _T("2^7");
	m_edit4 = _T("2^8");
	m_edit5 = _T("0");
	m_edit6 = _T("0");
	//}}AFX_DATA_INIT
}

CDlgPrimesGeneratorDemo::CDlgPrimesGeneratorDemo(CString lower, CString upper, CWnd *pParent)
	: CDialog(CDlgPrimesGeneratorDemo::IDD, pParent)
{
	m_hide_button_accept = false;
	//{{AFX_DATA_INIT(CDlgPrimesGeneratorDemo)
	m_radio1 = 0;
	m_radio4 = 0;
	m_edit1 = lower;
	m_edit2 = upper;
	m_edit3 = _T("2^7");
	m_edit4 = _T("2^8");
	m_edit5 = _T("0");
	m_edit6 = _T("0");
	//}}AFX_DATA_INIT
}

void CDlgPrimesGeneratorDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrimesGeneratorDemo)
	DDX_Control(pDX, IDC_EDIT2, m_control_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_control_edit1);
	DDX_Control(pDX, IDC_BUTTON_GENERATE, m_control_button_generate);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT, m_control_button_accept);
	DDX_Control(pDX, IDC_EDIT4, m_control_edit4);
	DDX_Control(pDX, IDC_EDIT3, m_control_edit3);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Radio(pDX, IDC_RADIO4, m_radio4);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrimesGeneratorDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgPrimesGeneratorDemo)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, OnButtonAccept)
	ON_BN_CLICKED(IDC_ENDDIALOG, OnEndDialog)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgPrimesGeneratorDemo 


//=========================================================================================================
void CDlgPrimesGeneratorDemo::OnRadio4() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(true);
	m_control_edit4.EnableWindow(true);
	UpdateData(false);
}

void CDlgPrimesGeneratorDemo::OnRadio5() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(false);
	m_control_edit4.EnableWindow(false);
	UpdateData(false);
	OnUpdateEdit();
}

BOOL CDlgPrimesGeneratorDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Zusätzliche Initialisierung hier einfügen
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PRIMES,pc_str,STR_LAENGE_STRING_TABLE);
	
	m_control_edit1.SetFocus();
	CString Primes;
//	if ( PasteKey( pc_str, Primes ) )
	if (false)
	{
		UpdateData(true);
		int d = Primes.Find(';', 0);
		m_edit5 = Primes.Mid(0, d);
		m_edit6 = Primes.Mid(d+1);
		UpdateData(false);
	}
	else
	{
		m_control_button_accept.EnableWindow(false);
	}
	
	if(m_radio4) OnRadio5();

	if (m_hide_button_accept)
		m_control_button_accept.ShowWindow(SW_HIDE);

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CDlgPrimesGeneratorDemo::GetRandomPrime(CString &OutStr, GeneratePrimes &P)
{
	BOOL flag = FALSE;

	for ( int i=1; i<=20000 && !flag; i++ )			 // 
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
void CDlgPrimesGeneratorDemo::OnButtonGenerate() 
// erzeugt zwei Zufalls-Primzahlen innerhalb der angegebenen Grenzen
// Fehler werden mit entsprechenden Messages behandelt
{
	UpdateData(true);

	GeneratePrimes P;
	GeneratePrimes Q;
	int PSet,QSet;
	
	if(!((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty()) &&
		   (0==m_edit3.IsEmpty())&&(0==m_edit4.IsEmpty())) )
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
	error = CheckFormula(m_edit3,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit3.SetSel(err_ndx-1,m_edit3.GetLength());
		m_control_edit3.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	error = CheckFormula(m_edit4,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit4.SetSel(err_ndx-1,m_edit4.GetLength());
		m_control_edit4.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	
	if(0==m_radio4)
	{
		//if((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty()) &&
		//	(0==m_edit3.IsEmpty())&&(0==m_edit4.IsEmpty()) )
		//	{
			PSet=P.SetLimits( m_edit1, m_edit2 );
			QSet=Q.SetLimits( m_edit3, m_edit4 );
			if ( (PSet == 1) && (QSet ==1))
			{
				SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
				if ( !GetRandomPrime( m_edit5, P ) ) Message( IDS_STRING_MSG_LEFT_PRIMES_NOT_FOUND, MB_ICONSTOP );
				if ( !GetRandomPrime( m_edit6, Q ) ) Message( IDS_STRING_MSG_RIGHT_PrIMES_NOT_FOUND, MB_ICONSTOP );
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
			else if (  QSet ==3)
			{
				m_control_edit3.SetFocus();
				m_control_edit3.SetSel(0,-1);
				Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
			}
			else if (  QSet ==2)
			{
				m_control_edit4.SetFocus();
				m_control_edit4.SetSel(0,-1);
				Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
			}
			else if (  PSet ==1 )
			{
				m_control_edit3.SetFocus();
				m_control_edit3.SetSel(0,-1);
				Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
			}
			else 
			{
				m_control_edit1.SetFocus();
				m_control_edit1.SetSel(0,-1);
				Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
			}
	}
	else
	{
		//if((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty()))
		//{
			PSet=P.SetLimits( m_edit1, m_edit2 );
			QSet=Q.SetLimits( m_edit1, m_edit2 );

			if ( PSet==1 && QSet==1 )
			{
				SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
				if ( !GetRandomPrime( m_edit5, P ) ) Message( IDS_STRING_MSG_LEFT_PRIMES_NOT_FOUND, MB_ICONSTOP );
				if ( !GetRandomPrime( m_edit6, Q ) ) Message( IDS_STRING_MSG_RIGHT_PrIMES_NOT_FOUND, MB_ICONSTOP );
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
			else if (  QSet ==3)
			{
				m_control_edit3.SetFocus();
				m_control_edit3.SetSel(0,-1);
				Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
			}
			else if (  QSet ==2)
			{
				m_control_edit4.SetFocus();
				m_control_edit4.SetSel(0,-1);
				Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
			}
			else if (  PSet ==1 )
			{
				m_control_edit3.SetFocus();
				m_control_edit3.SetSel(0,-1);
				Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
			}
			else 
			{
				m_control_edit1.SetFocus();
				m_control_edit1.SetSel(0,-1);
				Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
			}
	}

	if(("0"!=m_edit5)&&("0"!=m_edit6))
	{
		m_control_button_accept.EnableWindow(true);
	}

	UpdateData(false);
}

//===============================================================================================
void CDlgPrimesGeneratorDemo::OnButtonAccept() 

// wenn der Button "Übernehmen" gewählt wird, kann der Dialog nur verlassen werden,
// wenn das Produkt der beiden Primzahlen kleiner als c_MaxPrime_high ist

{
	UpdateData(true);
	if ( m_edit5 != "0" && m_edit6 != "0" )
	{
		LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PRIMES,pc_str,STR_LAENGE_STRING_TABLE);
		CString Primes = m_edit5 + CString( ";" ) + m_edit6;
		CopyKey ( pc_str, Primes );
		CDialog::OnOK();
	}
	UpdateData(false);
}




void CDlgPrimesGeneratorDemo::OnEndDialog() 
{
	UpdateData(true);
	m_edit5=m_edit6="0";	
	CDialog::OnCancel();
	UpdateData(false);
}



void CDlgPrimesGeneratorDemo::OnUpdateEdit() 
{
	if(m_radio4)
	{
		UpdateData(true);
		m_edit3 = m_edit1;
		m_edit4 = m_edit2;
		UpdateData(false);
	}	
}
