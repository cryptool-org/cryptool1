//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgShowPrivEcKeys.cpp: Implementierungsdatei
//
//////////////////////////////////////////////////////////////////
//
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security


#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowPrivateKeyEC.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowPrivateKeyEC 


CDlgShowPrivateKeyEC::CDlgShowPrivateKeyEC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowPrivateKeyEC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowPrivateKeyEC)
	m_ec_dom_par_editbox = _T("");
	m_InfoKeyCreatedBy = _T("");
	m_InfoKeyType = _T("");
	m_InfoCreatTime = _T("");
	m_TextKeyOwner = _T("");
	m_TextKeyType = _T("");
	m_TextKeyCreatDate = _T("");
	//}}AFX_DATA_INIT
}

CDlgShowPrivateKeyEC::CDlgShowPrivateKeyEC(CString User, CString name, CString firstname, CString creattime, CString cID, EcDomParam_ac_ptr ecParam, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowPrivateKeyEC::IDD, pParent)
{
	curveParameter = ecParam;
	UserId = User;
	curveID = cID;
	Name = name;
	Firstname = firstname;
	CreatTime = creattime;
}


void CDlgShowPrivateKeyEC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowPrivateKeyEC)
	DDX_Control(pDX, IDC_EDIT2, m_InfoKeyCreatedByCtrl);
	DDX_Control(pDX, IDC_EDIT5, m_TextKeyCreatDateCtrl);
	DDX_Control(pDX, IDC_EDIT4, m_TextKeyTypeCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_TextKeyOwnerCtrl);
	DDX_Control(pDX, IDC_LIST3, m_privKey_listview);
	DDX_Control(pDX, IDC_LIST2, m_pubKey_listview);
	DDX_Control(pDX, IDC_LIST1, m_dom_param_listview);
	DDX_Text(pDX, IDC_EDIT1, m_ec_dom_par_editbox);
	DDX_Text(pDX, IDC_EDIT2, m_InfoKeyCreatedBy);
	DDX_Text(pDX, IDC_EDIT_KEYTYPE, m_InfoKeyType);
	DDX_Text(pDX, IDC_EDIT_CREATTIME, m_InfoCreatTime);
	DDX_Text(pDX, IDC_EDIT3, m_TextKeyOwner);
	DDX_Text(pDX, IDC_EDIT4, m_TextKeyType);
	DDX_Text(pDX, IDC_EDIT5, m_TextKeyCreatDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowPrivateKeyEC, CDialog)
	//{{AFX_MSG_MAP(CDlgShowPrivateKeyEC)
	ON_BN_CLICKED(IDC_RADIO1, OnOctalRadio)
	ON_BN_CLICKED(IDC_RADIO2, OnDecimalRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnHexRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgShowPrivateKeyEC 

void CDlgShowPrivateKeyEC::OnOctalRadio() 
{
	base = 8;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error > 0)
	{
		// Fehler. Umwandlung der Domain Parameter in String nicht m�glich.
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}
	UpdateEcListBox();	
}

void CDlgShowPrivateKeyEC::OnDecimalRadio() 
{
	base = 10;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error > 0)
	{
		// Fehler. Umwandlung der Domain Parameter in String nicht m�glich.
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM,MB_ICONSTOP);
		return;
	}
	UpdateEcListBox();
}

void CDlgShowPrivateKeyEC::OnHexRadio() 
{
	base = 16;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error > 0)
	{
		// Fehler. Umwandlung der Domain Parameter in String nicht m�glich.
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM,MB_ICONSTOP);
		return;
	}
	UpdateEcListBox();	
}

void CDlgShowPrivateKeyEC::UpdateEcListBox()
{
	unsigned int bitlength;

	m_dom_param_listview.DeleteAllItems(); // Delete all data in the listview
// == EC curve parameter a, b, p
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SEPERATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertItem( 0, pc_str );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.SetItemText( 0, 1, pc_str );
	m_dom_param_listview.InsertItem( 1, "a" );
	m_dom_param_listview.SetItemText( 1, 1, ecParamString.a );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->a);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 2, 2, pc_str ); // Bitl�nge von a
	m_dom_param_listview.InsertItem( 2, "b" );
	m_dom_param_listview.SetItemText( 2, 1, ecParamString.b );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->b);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 2, 2, pc_str ); // Bitl�nge von b
	m_dom_param_listview.InsertItem( 3, "p" );
	m_dom_param_listview.SetItemText( 3, 1, ecParamString.p );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->p);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 3, 2, pc_str ); // Bitl�nge von p
// == EC curve point G = (x,y)
	m_dom_param_listview.InsertItem( 4, " " );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SEPERATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertItem( 5, pc_str );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_POINT_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.SetItemText( 5, 1, pc_str );
	m_dom_param_listview.InsertItem( 6, "x" );
	m_dom_param_listview.SetItemText( 6, 1, ecParamString.G_xcoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->x);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 6, 2, pc_str ); // Bitl�nge von x coord of G
	m_dom_param_listview.InsertItem( 7, "y" );
	m_dom_param_listview.SetItemText( 7, 1, ecParamString.G_ycoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->y);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 7, 2, pc_str ); // Bitl�nge von y coord of G
// == EC kofactor k, the prime number r is the order of G
	m_dom_param_listview.InsertItem( 8, " " );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SEPERATOR,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertItem( 9, pc_str );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_KF_ORD_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.SetItemText( 9, 1, pc_str );
	m_dom_param_listview.InsertItem( 10, "k" );
	m_dom_param_listview.SetItemText( 10, 1, ecParamString.k );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->k);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 10, 2, pc_str ); // Bitl�nge von k
	m_dom_param_listview.InsertItem( 11, "r" );
	m_dom_param_listview.SetItemText( 11, 1, ecParamString.r );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->r);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 11, 2, pc_str ); // Bitl�nge von r
	m_dom_param_listview.InsertItem( 12, " " );

	m_pubKey_listview.DeleteAllItems(); // Delete all data in the listview
	m_pubKey_listview.InsertItem( 0, " ");
	m_pubKey_listview.InsertItem( 1, ((CString)"x = ") + ecParamString.pubKey_xcoord);
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->pubKey->x);
	_itoa(bitlength+1, pc_str, 10);
	m_pubKey_listview.SetItemText( 1, 1, pc_str ); // Bitl�nge von x
	m_pubKey_listview.InsertItem( 2, ((CString)"y = ") + ecParamString.pubKey_ycoord);
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->pubKey->y);
	_itoa(bitlength+1, pc_str, 10);
	m_pubKey_listview.SetItemText( 2, 1, pc_str ); // Bitl�nge von y
	m_pubKey_listview.InsertItem( 3, " ");

	m_privKey_listview.DeleteAllItems(); // Delete all data in the listview
	m_privKey_listview.InsertItem( 0, " ");
	m_privKey_listview.InsertItem( 1, ((CString)"s = ") + ecParamString.privKey);
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->privKey);
	_itoa(bitlength+1, pc_str, 10);
	m_privKey_listview.SetItemText( 1, 1, pc_str ); // Bitl�nge von s
	m_privKey_listview.InsertItem( 2, " ");
}

BOOL CDlgShowPrivateKeyEC::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LOGFONT LogFont;
	LONG defaultFontWeight;
	CFont *defaultFont = m_InfoKeyCreatedByCtrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_TextKeyCreatDateCtrl.SetFont(&m_Font);
	m_TextKeyTypeCtrl.SetFont(&m_Font);
	m_TextKeyOwnerCtrl.SetFont(&m_Font);


	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO2); // base 10 is default
	base = 10;

	// Info about Key Owner
	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_OWNER,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextKeyOwner = (CString) pc_str;
	m_InfoKeyCreatedBy = Firstname+((CString)" ")+Name; // Created by

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_TYPE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextKeyType = (CString) pc_str;
	m_InfoKeyType = curveID; // Key Type

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_GENERATION_DATE,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextKeyCreatDate = (CString) pc_str;
	m_InfoCreatTime = CreatTime; // Time of key creation

	UpdateData(FALSE);

	// m_dom_param_listview aufbauen
	UpdateData(TRUE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DOMAIN_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_ec_dom_par_editbox = (CString) pc_str1;
	UpdateData(FALSE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 65 , 0); // Parameter

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 455 , 1); // Wert des Parameters

	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, 50 , 2); // Bitl�nge

	// m_pubKey_listview aufbauen
	m_pubKey_listview.DeleteAllItems(); // Delete all data in the listview
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_PUBLIC_KEY,pc_str,STR_LAENGE_STRING_TABLE);
	m_pubKey_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 520 , 0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_pubKey_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 50 , 1); // Bitl�nge

	// m_privKey_listview aufbauen
	m_privKey_listview.DeleteAllItems(); // Delete all data in the listview
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_PRIVATE_KEY,pc_str,STR_LAENGE_STRING_TABLE);
	m_privKey_listview.InsertColumn( 0, pc_str, LVCFMT_LEFT, 520 , 0);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_privKey_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 50 , 1); // Bitl�nge

	// Daten ausgeben
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error > 0)
	{
		// Fehler. Umwandlung der Domain Parameter in String nicht m�glich.
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM,MB_ICONSTOP);
		return TRUE;
	}

	UpdateEcListBox();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
} 
void CDlgShowPrivateKeyEC::OnCancel() 
{
	// TODO: Zus�tzlichen Bereinigungscode hier einf�gen
	
	CDialog::OnCancel();
}

void CDlgShowPrivateKeyEC::OnOK() 
{
	// TODO: Zus�tzliche Pr�fung hier einf�gen
	
	CDialog::OnOK();
}
