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

/******************************************************************************************************/
/*            GenEcKurve.cpp: Implementierungsdatei der Klasse GenEcKurve.                            */
/*                     Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main                        */
/*                     Programmiert von Roger Oyono März 2001                                         */
/*                     Deutsche Bank AG Frankfurt - IT Security                                       */
/******************************************************************************************************/


#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgECGeneration.h"
// #include "Ber_Ell_Kurve.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgECGeneration 


CDlgECGeneration::CDlgECGeneration(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgECGeneration::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgECGeneration)
/*
	m_edit1 = _T("2^{200-8}-2^{8^2}-7");
	m_radio1 = 0;
	m_radio3 = 0;
	m_edit_random_seed = 2147483647;
*/
	//}}AFX_DATA_INIT
}

/*
void CDlgECGeneration::DoDataExchange(CDataExchange* pDX)
{
//	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgECGeneration)
	DDX_Control(pDX, IDC_EDIT2, m_control_edit2);
	DDX_Control(pDX, IDC_LIST1, m_listview);
	DDX_Control(pDX, IDC_EDIT1, m_control_edit1);
	DDX_Control(pDX, IDC_BUTTON_GEN, m_control_button_gen);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT, m_control_button_accept);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Radio(pDX, IDC_RADIO3, m_radio3);
	DDX_Text(pDX, IDC_EDIT2, m_edit_random_seed);
	//}}AFX_DATA_MAP
}
*/


BEGIN_MESSAGE_MAP(CDlgECGeneration, CDialog)
	//{{AFX_MSG_MAP(CDlgECGeneration)
/*
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON_GEN, OnButtonGen)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
*/
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgECGeneration 



/*
void CDlgECGeneration::OnCheck1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
}

void CDlgECGeneration::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	CDialog::OnOK();
}

void CDlgECGeneration::OnCancel() 
{
	UpdateData(true);
	CDialog::OnCancel();
	UpdateData(false);
}

BOOL CDlgECGeneration::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_control_button_accept.EnableWindow(false);

	int colWidth = 100;  // Spaltenbreite in Pixel
	// m_listview aufbauen

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 65 , 0); // Parameter

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 455 , 1); // Wert des Parameters

	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, 50 , 2); // Bitlänge

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgECGeneration::OnButtonGen() 
{
	UpdateData(true);
	SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
	if(-1==BEK.GetInitPrime(m_edit1,m_edit_random_seed))
	{
		Liste_leeren();
		m_control_button_accept.EnableWindow(false);
	}
	else
	{
		char string[100];

		m_listview.DeleteAllItems();
		m_listview.InsertItem(0,"");
		m_listview.InsertItem(1,"a");
		m_listview.InsertItem(2,"b");
		m_listview.InsertItem(3,"p");
		m_listview.InsertItem(4,"x-Koord.");
		m_listview.InsertItem(5,"y-Koord.");
		m_listview.InsertItem(6,"k");
		m_listview.InsertItem(7,"r");
		m_listview.InsertItem(8,"D");


//		BEK.mip->IOBASE=10;
		string << BEK.a_par;
		m_listview.SetItemText(1,1,string);

//		BEK.mip->IOBASE=10;
		string << BEK.b_par;
		m_listview.SetItemText(2,1,string);

//		BEK.mip->IOBASE=10;
		string << BEK.p_par;
		m_listview.SetItemText(3,1,string);

//		BEK.mip->IOBASE=10;
		string << BEK.x_par;
		m_listview.SetItemText(4,1,string);

//		BEK.mip->IOBASE=10;
		string << BEK.y_par;
		m_listview.SetItemText(5,1,string);
		
//		BEK.mip->IOBASE=10;
		string << BEK.k_par;
		m_listview.SetItemText(6,1,string);

//		BEK.mip->IOBASE=10;
		string << BEK.r_par;
		m_listview.SetItemText(7,1,string);

		_itoa(BEK.Disc, string, 10);
		m_listview.SetItemText(8,1,string);


		_itoa(bits(BEK.a_par), string, 10);
		m_listview.SetItemText(1,2,string);

		_itoa(bits(BEK.b_par), string, 10);
		m_listview.SetItemText(2,2,string);

		_itoa(bits(BEK.p_par), string, 10);
		m_listview.SetItemText(3,2,string);

		_itoa(bits(BEK.x_par), string, 10);
		m_listview.SetItemText(4,2,string);

		_itoa(bits(BEK.y_par), string, 10);
		m_listview.SetItemText(5,2,string);

		_itoa(bits(BEK.k_par), string, 10);
		m_listview.SetItemText(6,2,string);

		_itoa(bits(BEK.r_par), string, 10);
		m_listview.SetItemText(7,2,string);

		_itoa(bits(BEK.Disc), string, 10);
		m_listview.SetItemText(8,2,string);

		m_control_button_accept.EnableWindow(true);
	}
	HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
	UpdateData(false);
}

void CDlgECGeneration::Liste_leeren()
{
	UpdateData(true);
	m_listview.DeleteAllItems();
	UpdateData(false);
}

void CDlgECGeneration::OnUpdateEdit1() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit1.GetSel(sels,sele);
	UpdateData(false);
	m_control_edit1.SetSel(sels,sele);
}

void CDlgECGeneration::OnUpdateEdit2() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit2.GetSel(sels,sele);
	UpdateData(false);
	m_control_edit2.SetSel(sels,sele);
}
*/