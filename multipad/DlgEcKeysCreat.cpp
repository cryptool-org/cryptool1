//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgEcKeysCreat.cpp: Implementierungsdatei
//
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#include "stdafx.h"
#include "multipad.h"
#include "DlgEcKeysCreat.h"
#include "DlgAsymKeyCreat.h"

#include "s_ecFp.h" // elliptic curve stuff
#include "s_prng.h" // big random integers
#include "arithmet.h"
#include "s_ecconv.h"
#include "asymmetric.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEcKeysCreat 


CDlgEcKeysCreat::CDlgEcKeysCreat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEcKeysCreat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEcKeysCreat)
	m_ec_dom_par_editbox = _T("");
	//}}AFX_DATA_INIT
}


CDlgEcKeysCreat::CDlgEcKeysCreat(EcDomParam_ac_ptr ecParam, EcDomParamAcAsString* EcParamStringPtr, CString cID, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEcKeysCreat::IDD, pParent)
{
	curveParameter = ecParam;
	ecParamString = EcParamStringPtr;
	curveID = cID;
}

void CDlgEcKeysCreat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEcKeysCreat)
	DDX_Control(pDX, IDC_LIST3, m_privKey_listview);
	DDX_Control(pDX, IDC_LIST2, m_pubKey_listview);
	DDX_Control(pDX, IDC_LIST1, m_dom_param_listview);
	DDX_Control(pDX, IDC_BUTTON1, m_GenNewKeyPair);
	DDX_Text(pDX, IDC_EDIT1, m_ec_dom_par_editbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEcKeysCreat, CDialog)
	//{{AFX_MSG_MAP(CDlgEcKeysCreat)
	ON_BN_CLICKED(IDC_RADIO1, OnOctalRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnDecimalRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnHexRadio)
	ON_BN_CLICKED(IDC_BUTTON1, OnNewKeyPair)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgEcKeysCreat 


BOOL CDlgEcKeysCreat::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// m_dom_param_listview aufbauen
	UpdateData(TRUE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING32889,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_ec_dom_par_editbox = (CString) pc_str1;
	UpdateData(FALSE);

	// m_dom_param_listview aufbauen
	LoadString(AfxGetInstanceHandle(),IDS_STRING32887,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 65 , 0); // Parameter

	LoadString(AfxGetInstanceHandle(),IDS_STRING32888,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 455 , 1); // Wert des Parameters

	LoadString(AfxGetInstanceHandle(),IDS_STRING32894,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, 50 , 2); // Bitlänge

	// m_pubKey_listview aufbauen
	m_pubKey_listview.DeleteAllItems(); // Delete all data in the listview
	LoadString(AfxGetInstanceHandle(),IDS_STRING32892,pc_str,STR_LAENGE_STRING_TABLE);
	m_pubKey_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 520 , 0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING32894,pc_str,STR_LAENGE_STRING_TABLE);
	m_pubKey_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 50 , 1); // Bitlänge


	// m_privKey_listview aufbauen
	m_privKey_listview.DeleteAllItems(); // Delete all data in the listview
	LoadString(AfxGetInstanceHandle(),IDS_STRING32893,pc_str,STR_LAENGE_STRING_TABLE);
	m_privKey_listview.InsertColumn( 0, pc_str, LVCFMT_LEFT, 520 , 0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING32894,pc_str,STR_LAENGE_STRING_TABLE);
	m_privKey_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 50 , 1); // Bitlänge


	theApp.DoWaitCursor(1);
	int error = GenEcKeyPair(curveParameter);
	theApp.DoWaitCursor(0);
	if (error)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41541,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		EndDialog(IDCANCEL);
		return FALSE;
	}

	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO2); // base 10 is default

	base = 10; // base ist in der ganzen Klasse sichtbar
	error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		EndDialog(IDCANCEL);
		return FALSE;
	}

	UpdateEcListBox(curveParameter, ecParamString);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgEcKeysCreat::UpdateEcListBox(EcDomParam_ac_ptr curveParameter, EcDomParamAcAsString *ecParamString)
{
	unsigned int bitlength;

	m_dom_param_listview.DeleteAllItems(); // Delete all data in the listview
	m_dom_param_listview.InsertItem( 0, " " );
	m_dom_param_listview.InsertItem( 1, "a" );
	m_dom_param_listview.SetItemText( 1, 1, ecParamString->a );
	// l = lngtouse(L_NUMBER r); /* l+1 == (length of r in bits) */
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->a);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 1, 2, pc_str ); // Bitlänge von a
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
	LoadString(AfxGetInstanceHandle(),IDS_STRING32890,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_dom_param_listview.InsertItem( 4, (CString) pc_str1 ); // "x coord of G"
	m_dom_param_listview.SetItemText( 4, 1, ecParamString->G_xcoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->x);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 4, 2, pc_str ); // Bitlänge von x coord of G
	LoadString(AfxGetInstanceHandle(),IDS_STRING32891,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_dom_param_listview.InsertItem( 5, (CString) pc_str1 ); // "y coord of G"
	m_dom_param_listview.SetItemText( 5, 1, ecParamString->G_ycoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->y);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 5, 2, pc_str ); // Bitlänge von y coord of G
	m_dom_param_listview.InsertItem( 6, "k" );
	m_dom_param_listview.SetItemText( 6, 1, ecParamString->k );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->k);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 6, 2, pc_str ); // Bitlänge von k
	m_dom_param_listview.InsertItem( 7, "r" );
	m_dom_param_listview.SetItemText( 7, 1, ecParamString->r );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->r);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 7, 2, pc_str ); // Bitlänge von r
	m_dom_param_listview.InsertItem( 8, " " );

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

	m_privKey_listview.DeleteAllItems(); // Delete all data in the listview
	m_privKey_listview.InsertItem( 0, " ");
	m_privKey_listview.InsertItem( 1, ((CString) "s = ") + ecParamString->privKey);
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->privKey);
	_itoa(bitlength+1, pc_str, 10);
	m_privKey_listview.SetItemText( 1, 1, pc_str ); // Bitlänge von s
	m_privKey_listview.InsertItem( 2, " ");
}


void CDlgEcKeysCreat::OnNewKeyPair() 
{
	theApp.DoWaitCursor(1);
	int error = GenEcKeyPair(curveParameter);
	theApp.DoWaitCursor(0);
	if (error)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41541,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		return;
	}

	error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		//EndDialog(IDCANCEL);
		//return FALSE;
		return;
	}

	UpdateEcListBox(curveParameter, ecParamString);
}

void CDlgEcKeysCreat::OnOctalRadio() 
{
	base = 8;
	int error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		//EndDialog(IDCANCEL);
		//return FALSE;
		return;
	}
	UpdateEcListBox(curveParameter, ecParamString);
}

void CDlgEcKeysCreat::OnDecimalRadio() 
{
	base = 10;
	int error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		//EndDialog(IDCANCEL);
		//return FALSE;
		return;
	}
	UpdateEcListBox(curveParameter, ecParamString);
}

void CDlgEcKeysCreat::OnHexRadio() 
{
	base = 16;
	int error = EcDomParamAcToString(ecParamString, curveParameter, base);
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		//EndDialog(IDCANCEL);
		//return FALSE;
		return;
	}
	UpdateEcListBox(curveParameter, ecParamString);	
}

void CDlgEcKeysCreat::OnOK() 
{
	CDialog::OnOK();
	int error = EcDomParamAcToString(ecParamString, curveParameter, 16);// strore domain parameter in hexadecimal representation
	if (error)
	{
		// Fehler. Umwandlung in Strings nicht möglich
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		EndDialog(IDCANCEL);
		//return FALSE;
		return;
	}
}

void CDlgEcKeysCreat::OnCancel() 
{
	
	CDialog::OnCancel();
} 
