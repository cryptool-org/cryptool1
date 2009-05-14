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

//////////////////////////////////////////////////////////////////
// DlgEcKeysCreat.cpp: Implementierungsdatei
//
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowParameterKeyEC.h"
#include "DlgKeyAsymGeneration.h"

#include "s_ecFp.h" // elliptic curve stuff
#include "s_prng.h" // big random integers
#include "arithmet.h"
#include "s_ecconv.h"
#include "AsymmetricEncryption.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowParameterKeyEC 


CDlgShowParameterKeyEC::CDlgShowParameterKeyEC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowParameterKeyEC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowParameterKeyEC)
	m_ec_dom_par_editbox = _T("");
	//}}AFX_DATA_INIT
}


CDlgShowParameterKeyEC::CDlgShowParameterKeyEC(EcDomParam_ac_ptr ecParam, EcDomParamAcAsString* EcParamStringPtr, CString cID, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowParameterKeyEC::IDD, pParent)
{
	curveParameter = ecParam;
	ecParamString = EcParamStringPtr;
	curveID = cID;
}

void CDlgShowParameterKeyEC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowParameterKeyEC)
	DDX_Control(pDX, IDC_LIST3, m_privKey_listview);
	DDX_Control(pDX, IDC_LIST2, m_pubKey_listview);
	DDX_Control(pDX, IDC_LIST1, m_dom_param_listview);
	DDX_Control(pDX, IDC_BUTTON1, m_GenNewKeyPair);
	DDX_Text(pDX, IDC_EDIT1, m_ec_dom_par_editbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowParameterKeyEC, CDialog)
	//{{AFX_MSG_MAP(CDlgShowParameterKeyEC)
	ON_BN_CLICKED(IDC_RADIO1, OnOctalRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnDecimalRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnHexRadio)
	ON_BN_CLICKED(IDC_BUTTON1, OnNewKeyPair)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowParameterKeyEC 


BOOL CDlgShowParameterKeyEC::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// m_dom_param_listview aufbauen
	UpdateData(TRUE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DOMAIN_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_ec_dom_par_editbox = (CString) pc_str1;
	UpdateData(FALSE);

	// m_dom_param_listview aufbauen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 65 , 0); // Parameter

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 455 , 1); // Wert des Parameters

	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, 50 , 2); // Bitlänge

	// m_pubKey_listview aufbauen
	m_pubKey_listview.DeleteAllItems(); // Delete all data in the listview
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_PUBLIC_KEY,pc_str,STR_LAENGE_STRING_TABLE);
	m_pubKey_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 520 , 0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_pubKey_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 50 , 1); // Bitlänge


	// m_privKey_listview aufbauen
	m_privKey_listview.DeleteAllItems(); // Delete all data in the listview
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_PRIVATE_KEY,pc_str,STR_LAENGE_STRING_TABLE);
	m_privKey_listview.InsertColumn( 0, pc_str, LVCFMT_LEFT, 520 , 0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_privKey_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 50 , 1); // Bitlänge


	SHOW_HOUR_GLASS
	int error = GenEcKeyPair(curveParameter);
	HIDE_HOUR_GLASS
	if (error)
	{
		Message(IDS_STRING_ERR_EC_GEN_EC_KEY_PAIR, MB_ICONSTOP);
		EndDialog(IDCANCEL);
		return FALSE;
	}

	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO2); // base 10 is default

	base = 10; // base ist in der ganzen Klasse sichtbar
	error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		EndDialog(IDCANCEL);
		return FALSE;
	}

	UpdateEcListBox(curveParameter, ecParamString);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgShowParameterKeyEC::UpdateEcListBox(EcDomParam_ac_ptr curveParameter, EcDomParamAcAsString *ecParamString)
{
	unsigned int bitlength;

	m_dom_param_listview.DeleteAllItems(); // Delete all data in the listview
	// m_dom_param_listview.InsertItem( 0, " " );

// == EC curve parameter a, b, p
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SEPERATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertItem( 0, pc_str );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.SetItemText( 0, 1, pc_str );
	m_dom_param_listview.InsertItem( 1, "a" );
	m_dom_param_listview.SetItemText( 1, 1, ecParamString->a );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->a);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 2, 2, pc_str ); // Bitlänge von a
	m_dom_param_listview.InsertItem( 2, "b" );
	m_dom_param_listview.SetItemText( 2, 1, ecParamString->b );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->b);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 2, 2, pc_str ); // Bitlänge von b
	m_dom_param_listview.InsertItem( 3, "p" );
	m_dom_param_listview.SetItemText( 3, 1, ecParamString->p );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->p);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 3, 2, pc_str ); // Bitlänge von p
// == EC curve point G = (x,y)
	m_dom_param_listview.InsertItem( 4, " " );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SEPERATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertItem( 5, pc_str );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_POINT_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.SetItemText( 5, 1, pc_str );
	m_dom_param_listview.InsertItem( 6, "x" );
	m_dom_param_listview.SetItemText( 6, 1, ecParamString->G_xcoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->x);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 6, 2, pc_str ); // Bitlänge von x coord of G
	m_dom_param_listview.InsertItem( 7, "y" );
	m_dom_param_listview.SetItemText( 7, 1, ecParamString->G_ycoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->y);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 7, 2, pc_str ); // Bitlänge von y coord of G
// == EC kofactor k, the prime number r is the order of G
	m_dom_param_listview.InsertItem( 8, " " );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SEPERATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertItem( 9, pc_str );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_KF_ORD_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.SetItemText( 9, 1, pc_str );
	m_dom_param_listview.InsertItem( 10, "k" );
	m_dom_param_listview.SetItemText( 10, 1, ecParamString->k );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->k);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 10, 2, pc_str ); // Bitlänge von k
	m_dom_param_listview.InsertItem( 11, "r" );
	m_dom_param_listview.SetItemText( 11, 1, ecParamString->r );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->r);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 11, 2, pc_str ); // Bitlänge von r
	m_dom_param_listview.InsertItem( 12, " " );

// Public EC key
	m_pubKey_listview.DeleteAllItems(); // Delete all data in the listview
	m_pubKey_listview.InsertItem( 0, " ");
	m_pubKey_listview.InsertItem( 1, ((CString) "x = ") + ecParamString->pubKey_xcoord);
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->pubKey->x);
	_itoa(bitlength+1, pc_str, 10);
	m_pubKey_listview.SetItemText( 1, 1, pc_str ); // Bitlänge von x
	m_pubKey_listview.InsertItem( 2, ((CString) "y = ") + ecParamString->pubKey_ycoord);
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->pubKey->y);
	_itoa(bitlength+1, pc_str, 10);
	m_pubKey_listview.SetItemText( 2, 1, pc_str ); // Bitlänge von y
	m_pubKey_listview.InsertItem( 3, " ");

// Private EC key
	m_privKey_listview.DeleteAllItems(); // Delete all data in the listview
	m_privKey_listview.InsertItem( 0, " ");
	m_privKey_listview.InsertItem( 1, ((CString) "s = ") + ecParamString->privKey);
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->privKey);
	_itoa(bitlength+1, pc_str, 10);
	m_privKey_listview.SetItemText( 1, 1, pc_str ); // Bitlänge von s
	m_privKey_listview.InsertItem( 2, " ");
}


void CDlgShowParameterKeyEC::OnNewKeyPair() 
{
	SHOW_HOUR_GLASS
	int error = GenEcKeyPair(curveParameter);
	SHOW_HOUR_GLASS
	if (error)
	{
		Message(IDS_STRING_ERR_EC_GEN_EC_KEY_PAIR, MB_ICONSTOP);
		return;
	}

	error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}

	UpdateEcListBox(curveParameter, ecParamString);
}

void CDlgShowParameterKeyEC::OnOctalRadio() 
{
	base = 8;
	int error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, ecParamString);
}

void CDlgShowParameterKeyEC::OnDecimalRadio() 
{
	base = 10;
	int error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, ecParamString);
}

void CDlgShowParameterKeyEC::OnHexRadio() 
{
	base = 16;
	int error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, ecParamString);	
}

void CDlgShowParameterKeyEC::OnOK() 
{
	CDialog::OnOK();
	int error = EcDomParamAcToString(ecParamString, curveParameter, 16);// strore domain parameter in hexadecimal representation
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		EndDialog(IDCANCEL);
		return;
	}
}

void CDlgShowParameterKeyEC::OnCancel() 
{
	
	CDialog::OnCancel();
} 
