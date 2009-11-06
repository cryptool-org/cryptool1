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
// DlgAsymKeyCreat.cpp: Implementierungsdatei
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include <io.h>
#include "CrypToolApp.h"
#include "CrypToolTools.h"
#include "DlgKeyAsymGeneration.h"

#include "secure.h"	// Header-File für das SECUDE-Toolkit
#include "af.h"		// Header-File für den SECUDE Authentication Framework
#include "pkcs.h"	// SECUDE Header-File

#include "s_ecFp.h"
#include "s_ecconv.h"
#include "arithmet.h"

#include "ParseIniFile.h"
#include "KeyFileHandling.h"
#include "DlgShowParameterKeyEC.h"
#include "DlgShowKeyParameter.h"
#include "DlgChangePIN.h"
#include "SecudeTools.h"

#include "DialogeMessage.h"
#include <time.h>


// the extern (global) Variables are from CrypTool.cpp
extern char *Pfad; // Directory Path of the main programm
extern char pc_str[STR_LAENGE_STRING_TABLE]; // from CrypTool.cpp
extern char pc_str1[STR_LAENGE_STRING_TABLE]; // from CrypTool.cpp

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; // aus CrypTool.cpp


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyAsymGeneration 


CDlgKeyAsymGeneration::CDlgKeyAsymGeneration(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyAsymGeneration::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyAsymGeneration)
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_rsa_modul_str = _T("");
	m_dsa_prime_str = _T("");
	m_ec_dom_par_str = _T("");
	m_verfahren = -1;
	m_zahlensystem = -1;
	m_ShowKeypair = FALSE;
	m_user_keyinfo = _T("");
	m_ec_dom_par_description = _T("");
	//}}AFX_DATA_INIT

	curveParameter = (EcDomParam_ac_ptr) malloc(sizeof(__DomParamAc_struct)); // Allocate memory. !! DELETE with destruktor!!
	if (curveParameter == NULL) return; // error. keine Speicherallokation
	curveParameter->E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
	if (curveParameter->E == NULL) return; // error. keine Speicherallokation
	curveParameter->G = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (curveParameter->G == NULL) return; // error. keine Speicherallokation
	curveParameter->pubKey = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (curveParameter->pubKey == NULL) return; // error. keine Speicherallokation
	curveParameter->pubKey->infinity=1; // pubKey is not defined yet
	inttoln(0, curveParameter->privKey); // initialize privKey = 0 (not defined yet)

	m_showRSAKeysOnly = false;
}

CDlgKeyAsymGeneration::~CDlgKeyAsymGeneration()
{
	free (curveParameter->pubKey);
	free (curveParameter->G);
	free (curveParameter->E);
	free (curveParameter);
}


void CDlgKeyAsymGeneration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyAsymGeneration)
	DDX_Control(pDX, IDC_KEYASYM_TEXTEC, m_ECTextInfo);
	DDX_Control(pDX, IDC_KEYASYM_TEXTDSA, m_DSATextInfo);
	DDX_Control(pDX, IDC_KEYASYM_TEXTRSA, m_RSATextInfo);
	DDX_Control(pDX, IDC_LIST1, m_dom_param_listview);
	DDX_Control(pDX, IDC_EDIT5, m_ctrl5);
	DDX_Control(pDX, IDC_CHECK1, m_ShowKeypairButton);
	DDX_Control(pDX, IDC_RADIO6, m_hexadecimal_radio);
	DDX_Control(pDX, IDC_RADIO5, m_decimal_radio);
	DDX_Control(pDX, IDC_RADIO4, m_octal_radio);
	DDX_Control(pDX, IDC_RADIO1, m_RSARadio);
	DDX_Control(pDX, IDC_RADIO3, m_ECRadio);
	DDX_Control(pDX, IDC_RADIO2, m_DSARadio);
	DDX_Control(pDX, IDC_COMBO3, m_ec_combo);
	DDX_Control(pDX, IDC_COMBO2, m_dsa_combo);
	DDX_Control(pDX, IDC_COMBO1, m_rsa_combo);
	DDX_Control(pDX, IDC_EDIT4, m_ctrl4);
	DDX_Control(pDX, IDC_EDIT3, m_ctrl3);
	DDX_Control(pDX, IDC_EDIT2, m_ctrl2);
	DDX_Control(pDX, IDC_EDIT1, m_ctrl1);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_CBString(pDX, IDC_COMBO1, m_rsa_modul_str);
	DDX_CBString(pDX, IDC_COMBO2, m_dsa_prime_str);
	DDX_CBString(pDX, IDC_COMBO3, m_ec_dom_par_str);
	DDX_Radio(pDX, IDC_RADIO1, m_verfahren);
	DDX_Radio(pDX, IDC_RADIO4, m_zahlensystem);
	DDX_Check(pDX, IDC_CHECK1, m_ShowKeypair);
	DDX_Text(pDX, IDC_EDIT5, m_user_keyinfo);
	DDX_Text(pDX, IDC_STATIC_PARAM_DESCRIPTION, m_ec_dom_par_description);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlShowKeyPair);
}

//	DDX_Control(pDX, IDC_RADIO3, m_ec_radio);

BEGIN_MESSAGE_MAP(CDlgKeyAsymGeneration, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyAsymGeneration)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeEcCombo)
	ON_BN_CLICKED(IDC_RADIO1, OnRSARadio)
	ON_BN_CLICKED(IDC_RADIO2, OnDSARadio)
	ON_BN_CLICKED(IDC_RADIO3, OnECRadio)
	ON_BN_CLICKED(IDC_RADIO5, OnDecimalRadio)
	ON_BN_CLICKED(IDC_RADIO4, OnOctalRadio)
	ON_BN_CLICKED(IDC_RADIO6, OnHexRadio)
	ON_BN_CLICKED(IDC_BUTTON_P12IMPORT, OnButtonP12import)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList)
	ON_EN_KILLFOCUS(IDC_EDIT_LV, OnKillfocusEditLv)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgKeyAsymGeneration::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyAsymGeneration 

void CDlgKeyAsymGeneration::OnOK() 
{
	UpdateData (TRUE);
	m_edit1.TrimLeft();
	m_edit1.TrimRight();
	m_edit2.TrimLeft();
	m_edit2.TrimRight();
	m_user_keyinfo.TrimLeft();
	m_user_keyinfo.TrimRight();
	UpdateData (FALSE);

	UpdateData (TRUE);

	// Check if Name, Last Name, PIN-Code, and PIN-Verification were entered
	if (m_edit1==""){
		// Name fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_ENTER_SURNAME,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl1.SetFocus();
		return;
	}

	if (m_edit2==""){
		// Vorname fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_ENTER_PRENAME,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl2.SetFocus();
		return;
	}

	if (m_edit3==""){
		// PIN-Code fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_ENTER_PIN2,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl3.SetFocus();
		return;
	}

	if (m_edit4==""){
		// PIN-Code-Verifikation fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_ENTER_PINVERIFICATION,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl4.SetFocus();
		return;
	}

	if (m_edit3!=m_edit4){
		// PIN-Code und PIN-Code-Verifikation stimmen nicht überein
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_PIN_PINVERIFICATION_NOTMATCH,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		// Die Eingabefelder von PIN und PIN-Verifikation löschen
		m_edit3="";
		m_edit4="";
		UpdateData(FALSE);
		m_ctrl3.SetFocus();
		return;
	}

	if ( /*(m_edit1.Find(EC_KEYFILE_IDSTRING ) > (-1)) ||*/ (m_edit1.Find(PSE_FILE_SUFFIX) > (-1)) ||
		 /*(m_edit2.Find(EC_KEYFILE_IDSTRING ) > (-1)) ||*/ (m_edit2.Find(PSE_FILE_SUFFIX) > (-1)) ||
		 /*(m_user_keyinfo.Find(EC_KEYFILE_IDSTRING ) > (-1)) ||*/ (m_user_keyinfo.Find(PSE_FILE_SUFFIX) > (-1)) )
	{		
		// Name oder Vorname oder Schlüsselkennung enthält unzulässige Zeichenfolge.
		// EC_KEYFILE_IDSTRING, "RSA" und "DSA" werden intern zum identifizieren Schlüsselbezeichnern
		// benutzt - diese Teilstrings dürfen aber dennoch vom Benutzer eingegeben werden, da es 
		// in der Funktion CKeyFile::ExtractData() zu keinen Problemen kommt.
		// PSE_FILE_SUFFIX dient als Dateiendung für die Datei in der geheimer Schlüssel
		// gespeichert wird (PSE) und sollte/darf nicht in den Benutzereingaben auftauchen.
		char tmp_str[200];
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_FORMAT_SUBSTR,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(tmp_str, pc_str, PSE_FILE_SUFFIX);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ILLEGAL_INPUT,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(tmp_str,pc_str1,MB_ICONWARNING|MB_OK);

		/* Eingaben nicht löschen, damit Benutzer noch sieht was er eingegeben hatte.
		if ( m_user_keyinfo.Find(EC_KEYFILE_IDSTRING ) > (-1) ){
			m_ctrl5.SetFocus();
			m_user_keyinfo = ""; // Eingabe löschen
		}
		else if ( m_edit1.Find(EC_KEYFILE_IDSTRING ) > (-1) ){
			m_ctrl1.SetFocus();
			m_edit1 = ""; // Eingabe löschen
		}
		else if ( m_edit2.Find(EC_KEYFILE_IDSTRING ) > (-1) ){
			m_ctrl2.SetFocus();
			m_edit2 = ""; // Eingabe löschen
		}
		*/
		return;
	}

	// Der Name und Vorname, sowie die optionale Schlüsselkennung werden als Dateinamen
	// benutzt. Daher sind einige (BETRIEBSYSTEMABHÄNGIGE) Sonderzeichen (Win NT: \/:*?"<>| )
	// nicht erlaubt. Eine diesbezügliche Überprüfung findet nun statt.
	// Weiterhin werden einige Zeichen ausgeschlossen die intern von CrypTool zum Parsen von Dateinamen
	// benutzt werden, z.B. [ und ]
	if ((m_edit1.FindOneOf("\\/:*?\"<>|~$%&,;[]") > (-1)) ||
		(m_edit2.FindOneOf("\\/:*?\"<>|~$%&,;[]") > (-1)) ||
		(m_user_keyinfo.FindOneOf("\\/:*?\"<>|~$%&,;[]") > (-1)) ){
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_ON_INPUT_FORMAT,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ILLEGAL_INPUT,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
		return;
	}
	
	// convert the String m_rsa_modul_str (from rsa-combobox) to an int, and store it in rsa_modul
	LPTSTR modul_char = new TCHAR[m_rsa_modul_str.GetLength()+1];
	_tcscpy(modul_char, m_rsa_modul_str);
	rsa_modul = atoi(modul_char);
	delete(modul_char);

	// convert the String m_dsa_prime_str (from dsa-combobox) to an int, and store it in dsa_modul
	LPTSTR prime_char = new TCHAR[m_dsa_prime_str.GetLength()+1];
	_tcscpy(prime_char, m_dsa_prime_str);
	dsa_prime = atoi(prime_char);
	delete(prime_char);

	// Check if the value in rsa-combobox is valid for rsa_keysize
	if ((m_rsa_combo.IsWindowEnabled()) && 
		((rsa_modul<MIN_RSA_MODULSIZE) || (rsa_modul>MAX_RSA_MODULSIZE)))
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_WRONG_RSAMODUL_BITLENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1, MIN_RSA_MODULSIZE-1, MAX_RSA_MODULSIZE+1);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_NONVALID_INPUT,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_rsa_combo.SetFocus();
		return;
	}

	if (m_dsa_combo.IsWindowEnabled() && 
		((dsa_prime<MIN_RSA_MODULSIZE) || (dsa_prime>MAX_RSA_MODULSIZE) || (dsa_prime % 64 != 0)))
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_RANGE_DSA_BITLENGTH,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1, MIN_RSA_MODULSIZE-1,MAX_RSA_MODULSIZE+1);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_NONVALID_INPUT,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_dsa_combo.SetFocus();
		return;
	}

	CreateAsymKeys(); // Create Keys with memberfunction CreateAsymKeys()

	// Die Eingabefelder von PIN und PIN-Verifikation löschen
	m_edit3="";
	m_edit4="";
	UpdateData(FALSE);
	m_ctrl3.SetFocus();

	return; // Dialogbox geöffnet lassen, um dem Benutzer die Möglichkeit zu geben mehrere
	// Schlüssel unter seinem Namen direkt hintereinander anzulegen

	// CDialog::OnOK();
}

BOOL CDlgKeyAsymGeneration::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// m_dom_param_listview aufbauen

	m_dom_param_listview.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 65 , 0); // Parameter

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PARAMETER_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 455 , 1); // Wert des Parameters

	LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_PARAM_BITLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, 50 , 2); // Bitlänge

	// Daten Initialisieren

	CParseIniFile iniFile;

	CParseIniFile::CStringList ecIDlist;

	CString default_rsa_modulsize = "1024"; // Default: RSA with 1024 Bits
	CString default_dsa_primesize = "1024"; // Default: DSA with 1024 Bits

	int combolist_stringindex;

	m_rsa_combo.LimitText(5); // User can insert at most 5 characters
	m_dsa_combo.LimitText(5); // User can insert at most 5 characters

	// SELECT default key size from the (preinitialized) combolist entries
	m_rsa_combo.SelectString(-1, default_rsa_modulsize);
	m_dsa_combo.SelectString(-1, default_dsa_primesize);

	base = 10; // display numbers in listbox (elliptic curve parameters) in base 'base'

	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO1); // RSA key generation is default setup

	CheckRadioButton (IDC_RADIO4, IDC_RADIO6, IDC_RADIO5); // select the radio button which represents base

	m_dsa_combo.EnableWindow(FALSE); // Set dsa-combobox inactiv
	m_ec_combo.EnableWindow(FALSE); // Set ec-combobox inactiv
	m_dom_param_listview.EnableWindow(FALSE); // Set "elliptic curve parameter info box" inactiv
	m_octal_radio.EnableWindow(FALSE); // and so on ...
	m_decimal_radio.EnableWindow(FALSE);
	m_hexadecimal_radio.EnableWindow(FALSE);
	m_ShowKeypairButton.EnableWindow(TRUE);

	m_ShowKeypairButton.SetCheck(1); // Check the button

	UpdateData(TRUE);

	if (iniFile.GetEcIDList(ecIDlist) == -1)
	{
		m_ECRadio.EnableWindow(FALSE); // Enable ec_radio_button (not able to read iniFile)
	}
	else
	{
		// no problems due opening IniFile 
		while ( !ecIDlist.IsEmpty()){
			m_ec_combo.AddString(ecIDlist.RemoveHead()); // Add curve ID to combobox-list
		}	

		if (!iniFile.GetPreSelEcID(curveID))
		{
			// A curve ID is in the iniFile specified as default curve ID 
			combolist_stringindex = m_ec_combo.SelectString( -1, curveID);
		}

		iniFile.GetEcDomParam(curveID, curveParameter); // get curve parameter of the curve with name 'curveID'

		// Convert curve parameter to numberstrings in default_base
		int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
		if (error)
		{
			// error while converting curveParameter to Strings
			Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
			return TRUE;
		}

		UpdateEcListBox(curveParameter, &ecParamString, curveID, FALSE);
	}

	// disable non-RSA components if necessary
	if(this->m_showRSAKeysOnly)
	{
		m_RSARadio.SetCheck(1);
		m_DSARadio.SetCheck(0);
		m_ECRadio.SetCheck(0);
		m_RSARadio.EnableWindow(TRUE);
		m_DSARadio.EnableWindow(FALSE);
		m_ECRadio.EnableWindow(FALSE);
		m_rsa_combo.EnableWindow(TRUE);
		m_dsa_combo.EnableWindow(FALSE);
		m_ec_combo.EnableWindow(FALSE);
		m_RSATextInfo.EnableWindow(TRUE);
		m_DSATextInfo.EnableWindow(FALSE);
		m_ECTextInfo.EnableWindow(FALSE);
	}

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgKeyAsymGeneration::UpdateEcListBox(EcDomParam_ac_ptr curveParameter, EcDomParamAcAsString *ecParamString, 
											CString curveID, BOOL WindowActive)
{	
	unsigned int bitlength;

	m_dom_param_listview.DeleteAllItems(); // Delete all data in the listview
	// m_dom_param_listview.InsertItem( 0, " " );

	if ( WindowActive )
	{
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DOMAIN_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, curveID);
		m_ec_dom_par_description = (CString) pc_str1;
		UpdateData(FALSE);
		
	// == EC curve parameter a, b, p
		LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_SEPERATOR,pc_str,STR_LAENGE_STRING_TABLE);
		m_dom_param_listview.InsertItem( 0, pc_str );
		LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
		m_dom_param_listview.SetItemText( 0, 1, pc_str );

		m_dom_param_listview.InsertItem( 1, "a" );
		m_dom_param_listview.SetItemText( 1, 1, ecParamString->a );
		// l = lngtouse(L_NUMBER r); /* l+1 == (length of r in bits) */
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
	}
	else
	{
		UpdateData(TRUE);
		LoadString(AfxGetInstanceHandle(),IDS_HEADING_EMPTY_ECDOMAINPARAMETER,
			       pc_str,STR_LAENGE_STRING_TABLE);
		m_ec_dom_par_description = (CString) pc_str;
		UpdateData(FALSE);
	}
}


void CDlgKeyAsymGeneration::OnSelchangeEcCombo() 
{
	// Show parameters of the selected curve ID
	// The parameters are loaded from the file 'initializing_file'

	CParseIniFile iniFile;

	m_ec_combo.GetLBText(m_ec_combo.GetCurSel(), curveID);

	iniFile.GetEcDomParam(curveID, curveParameter); // get curve parameter of the curve with name 'curveID'

	// Convert curve parameter to numberstrings in default base
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}

	UpdateEcListBox(curveParameter, &ecParamString, curveID);

}

void CDlgKeyAsymGeneration::OnRSARadio() 
{
	m_rsa_combo.EnableWindow(TRUE); // Set rsa-combobox activ
	m_dsa_combo.EnableWindow(FALSE); // Set dsa-combobox inactiv
	m_ec_combo.EnableWindow(FALSE); // Set ec-combobox inactiv
	m_dom_param_listview.EnableWindow(FALSE); // Set "elliptic curve parameter info box" inactiv
	m_octal_radio.EnableWindow(FALSE);
	m_decimal_radio.EnableWindow(FALSE);
	m_hexadecimal_radio.EnableWindow(FALSE);
	m_ShowKeypairButton.EnableWindow(TRUE);
	UpdateEcListBox(curveParameter, &ecParamString, curveID, FALSE);
}

void CDlgKeyAsymGeneration::OnDSARadio() 
{
	if(this->m_showRSAKeysOnly)
	{
		// creating a DSA key is not allowed at this point
		Message(IDS_STRING_ASYMKEYGEN_RSAONLY, MB_ICONINFORMATION);
		m_RSARadio.SetCheck(1);
		m_DSARadio.SetCheck(0);
		m_ECRadio.SetCheck(0);
		m_RSARadio.EnableWindow(TRUE);
		m_DSARadio.EnableWindow(FALSE);
		m_ECRadio.EnableWindow(FALSE);
		m_rsa_combo.EnableWindow(TRUE);
		m_dsa_combo.EnableWindow(FALSE);
		m_ec_combo.EnableWindow(FALSE);
		return;
	}

	m_rsa_combo.EnableWindow(FALSE); // Set rsa-combobox inactiv
	m_dsa_combo.EnableWindow(TRUE); // Set dsa-combobox activ
	m_ec_combo.EnableWindow(FALSE); // Set ec-combobox inactiv
	m_dom_param_listview.EnableWindow(FALSE); // Set "elliptic curve parameter info box" inactiv
	m_octal_radio.EnableWindow(FALSE);
	m_decimal_radio.EnableWindow(FALSE);
	m_hexadecimal_radio.EnableWindow(FALSE);
	m_ShowKeypairButton.EnableWindow(FALSE);
	UpdateEcListBox(curveParameter, &ecParamString, curveID, FALSE);
}

void CDlgKeyAsymGeneration::OnECRadio() 
{
	if(this->m_showRSAKeysOnly)
	{
		// creating a DSA key is not allowed at this point
		Message(IDS_STRING_ASYMKEYGEN_RSAONLY, MB_ICONINFORMATION);
		m_RSARadio.SetCheck(1);
		m_DSARadio.SetCheck(0);
		m_ECRadio.SetCheck(0);
		m_RSARadio.EnableWindow(TRUE);
		m_DSARadio.EnableWindow(FALSE);
		m_ECRadio.EnableWindow(FALSE);
		m_rsa_combo.EnableWindow(TRUE);
		m_dsa_combo.EnableWindow(FALSE);
		m_ec_combo.EnableWindow(FALSE);
		return;
	}

	m_rsa_combo.EnableWindow(FALSE); // Set rsa combobox inactiv
	m_dsa_combo.EnableWindow(FALSE); // Set dsa combobox inactiv
	m_ec_combo.EnableWindow(TRUE); // Set ec combobox activ
	m_dom_param_listview.EnableWindow(TRUE); // Set "elliptic curve parameter info box" activ
	m_octal_radio.EnableWindow(TRUE);
	m_decimal_radio.EnableWindow(TRUE);
	m_hexadecimal_radio.EnableWindow(TRUE);
	m_ShowKeypairButton.EnableWindow(TRUE);
	UpdateEcListBox(curveParameter, &ecParamString, curveID);
}

void CDlgKeyAsymGeneration::OnDecimalRadio() 
{
	base = 10;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, &ecParamString, curveID);
}

void CDlgKeyAsymGeneration::OnOctalRadio() 
{
	base = 8;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		Message( IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, &ecParamString, curveID);
}

void CDlgKeyAsymGeneration::OnHexRadio() 
{
	base = 16;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, &ecParamString, curveID);
}


/* Die folgende Funktion erzeugt ein (asymmetrisches) Schlüsselpaar und legt es
   PIN-geschützt lokal ab.
   Grundsätzlich muß hier zwischen Verfahren unterschieden werden, die auf dem
   SECUDE-Toolkit aufbauen und Verfahren, die komplett selbst erstellt wurden.

   Verfahren, die auf SECUDE aufbauen:
   Ein Schlüsselpaar und eine PSE (Personal Secure Environment, durch PIN-Nummer
   geschützter Bereich eines Benutzers) werden erzeugt. Der geheime Schlüssel wird
   in der PSE (PIN-geschützt) abgelegt. Der öffentliche Schlüssel wird durch eine 
   lokale CA zertifiziert und das Zertifikat in einer CA-Datenbank abgelegt.

   Komplett selbst erstellte Verfahren:
   Auch hier werden ein Schlüsselpaar und eine PSE erzeugt. Der geheime Schlüssel
   wird wieder in der PSE gespeichert.
   Dieser Schlüssel kann allerdings nicht durch die Funktionen im SECUDE-Toolkit
   zertifiziert werden, da dazu der (lokalen) CA ein selbst-signiertes (Prototyp-)
   Zertifikat vorzulegen wäre, dessen Unterschrift sie überprüft und bei korrekter
   Verifikation zertifiziert.
   Da SECUDE das entsprechende Signaturverfahren jedoch nicht kennt, kann es auch die 
   Signatur nicht überprüfen.
   Deshalb werden die öffentlichen Schlüssel (lokal) in einer öffentlichen Datei abgelegt.
   Dies betrifft vorerst nur Signatur-Verfahren, die auf Elliptischen Kurven arbeiten.
   Bei Hinzufügen von weiteren Verfahren, die nicht von SECUDE bereitgestellt werden, stellt
   sich jedoch dasselbe Problem.
*/
void CDlgKeyAsymGeneration::CreateAsymKeys()
{
	AlgId *Algorithmus;
	Key keyinfo;

	CKeyFile KeyHandling; // In der Datei CKeyFile::KeyHandling werden die Schlüsselbezeichner
	                      // abgespeichert

	bool use_secude_api;
	CString verfahren;
	CString keyBits;
	CString UserKeyId;
	CString time_of_creat;
	int error;

	CString UserName = m_edit1;
	CString UserFirstName = m_edit2;
	CString UserPinCode = m_edit3;

	clock_t start;
	clock_t finish;
	double duration;

	// Ermittlung des vom Benutzer im Dialogfeld gewählten Verfahrens:
			
	if (m_verfahren == 0)
	{
		// Generate RSA key pair
		use_secude_api = TRUE;
		/* Algorithmus = theApp.SecudeLib.md5WithRsaEncryption_aid; */
		Algorithmus = theApp.SecudeLib.sha1WithRSASignature_aid;
		keyinfo.alg = theApp.SecudeLib.rsa_aid;
		keyinfo.key_size = rsa_modul; // used keysize as int
		verfahren = RSA_KEYFILE_IDSTRING;
		keyBits = m_rsa_modul_str; // used keysize as string
	}
	if (m_verfahren == 1)
	{
		// Generate DSA key pair
		use_secude_api = TRUE;
		Algorithmus = theApp.SecudeLib.dsaWithSHA1_aid;
		keyinfo.alg = theApp.SecudeLib.dsa_aid;
		keyinfo.key_size = dsa_prime; // used keysize as int
		verfahren = DSA_KEYFILE_IDSTRING;
		keyBits = m_dsa_prime_str; // used keysize as string
	}
	if (m_verfahren == 2)
	{
		// Generate Elliptic Curve key pair
		
		use_secude_api = FALSE;

		// generate keys
		if (m_ShowKeypair == TRUE)
		{
			// User wants to see the generated keypair
			start = clock();
			CDlgShowParameterKeyEC ShowEcKeys(curveParameter, &ecParamString, curveID);
			if(ShowEcKeys.DoModal()==IDCANCEL) return; // Cancel Button pushed
			else
			{
				// key pair was generated in ShowEcKeys()
				// ecParamString und curveParameter sind entsprechend initialisiert
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC; // Dauer der Schlüssel Erzeugung
			}
		}
		else
		{
			// User didn't want to see the generated keypair; there is no keypair generated yet
			SHOW_HOUR_GLASS
			start = clock();
			error = GenEcKeyPair(curveParameter); // create key pairs
			finish = clock();
			duration = (double)(finish - start) / CLOCKS_PER_SEC; // Dauer der Schlüssel Erzeugung
			if (error)
			{
				// error while creating key pair
				Message(IDS_STRING_ERR_EC_GEN_EC_KEY_PAIR, MB_ICONSTOP);
				return;
			}
			error = EcDomParamAcToString(&ecParamString, curveParameter, 16);
			if (error)
			{
				// error while converting curveParameter to Strings
				Message(IDS_STRING_ERR_EC_ON_CONVERT_PARAM, MB_ICONSTOP);
				return;
			}
			HIDE_HOUR_GLASS
		}
		
		SHOW_HOUR_GLASS
		// Datum und Zeitpunkt der Schlüsselerzeugung
		char buffer[20];
		time_t aclock;
		time( &aclock ); // Get time in seconds
		_itoa((int)aclock, buffer, 10);
		time_of_creat = (CString) buffer; // time_of_creat: Time in seconds since UTC 1/1/70

		UserKeyId = KeyHandling.CreateFilename(UserName, UserFirstName, EC_KEYFILE_IDSTRING, m_ec_dom_par_str, time_of_creat, m_user_keyinfo);
		// UserKeyId ist der Dateiname ohne Suffix PSE_FILE_SUFFIX
		// UserKeyId ist aufgrund von time_of_creat EINDEUTIG

		// create public and private keyfiles 
		error = KeyHandling.CreateEcKeyFiles(UserKeyId, UserPinCode, curveParameter, &ecParamString);
		if (error == -1)
		{
			// irgendein Fehler beim erzeugen der PSE ist aufgetreten
			theApp.SecudeLib.ErrorMessage(IDS_STRING_ASYMKEY_ERR_CREATE_PSE, NULL);
			return;
		}
		else if (error == -2)
		{
			// irgendein Fehler beim öffnen der PSE ist aufgetreten
			theApp.SecudeLib.ErrorMessage(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, NULL);
			return;
		}
		else if (error == -9)
		{
			// Fehler: die Dateien für die öffentlichen bzw. geheimen Parameter konnten nicht
			// im Verzeichnis "Pfad" (siehe CrypTool.cpp) erzeugt werden
			theApp.SecudeLib.ErrorMessage(IDS_STRING_KEYLIST_ASYM_ERROR_ONSAVE, NULL);
			return;
		}
		else if (error != 0)
		{
			return; // sonstige Fehler
		}

		HIDE_HOUR_GLASS
	}

	if (use_secude_api)
	{
		// RSA or DSA key generation with secude API's

		// Datum und Zeitpunkt der Schlüsselerzeugung
		char buffer[20];
		time_t aclock;
		time( &aclock ); // Get time in seconds
		_itoa((int)aclock, buffer, 10);
		time_of_creat = (CString) buffer; // time_of_creat: Time in seconds since UTC 1/1/70

		// Anlegen der PSE mit den Daten aus den Eingabefeldern der Dialogbox, dabei werden zusätzliche
		// Erkennungsmerkmale verwendet:

		UserKeyId = KeyHandling.CreateFilename(UserName, UserFirstName, verfahren, keyBits, time_of_creat, m_user_keyinfo);
		// UserKeyId ist aufgrund von time_of_creat EINDEUTIG

		CString secret_key_file = (CString) PseVerzeichnis + ((CString)"/") + UserKeyId + ((CString)PSE_FILE_SUFFIX);
		LPTSTR string2 = new TCHAR[secret_key_file.GetLength()+1];
		_tcscpy(string2, secret_key_file);		
		char *string3=string2;

		// Kopieren von CString m_edit3 nach char *string5, PIN-Nummer
		LPTSTR string4 = new TCHAR[m_edit3.GetLength()+1];
		_tcscpy(string4, m_edit3);
		char *string5=string4;
		
		// Anlegen einer PSE für den neuen Benutzer 
		// Erklärung der Parameter
		// string 3: Name der PSE samt absoluter Pfad
		// NULL	   : PSE für Benutzer anlegen
		// string 5: PIN-Nummer
		// NULL    : Software-PSE anlegen
		// TRUE    : Schlüsselpaar in PSE kann für Verschl. und Sign. verwendet werden
		PSE PseHandle;
		
		PseHandle=theApp.SecudeLib.af_create (string3  , NULL, string5, NULL, TRUE);
		if (PseHandle==NULL)
		{	// Fehler bei der PSE-Erzeugung
			theApp.SecudeLib.ErrorMessage(IDS_STRING_ASYMKEY_ERR_CREATE_PSE, PseHandle);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			return;
		}

		// Initialisierung der Struktur, in die der neu erzeugte Schlüssel abgelegt wird
		keyinfo.key=NULL;
		keyinfo.pse_sel=NULL;
		keyinfo.add_object=NULL;
		keyinfo.add_object_type=NULL;
		keyinfo.private_key=NULL;

		SHOW_HOUR_GLASS
		start = clock();
		error = theApp.SecudeLib.af_gen_key (PseHandle, &keyinfo, SIGNATURE, 1); // create key pairs
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC; // Dauer der Schlüssel Erzeugung
		if (error == -1)
		{
			// Fehler bei der Schlüsselerzeugung
			Message(IDS_STRING_ERR_ON_KEY_GENERATION, MB_ICONSTOP);
			// Lösche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			HIDE_HOUR_GLASS
			return;
		}
		else                         // Secude Api ???
		{
			int mlen,elen,i;
			unsigned char *buf;
			KeyBits *ki;
			L_NUMBER temp[MAXLGTH];

			ki=theApp.SecudeLib.d_KeyBits(&(keyinfo.key->subjectkey));
			if (ki&&m_ShowKeypair == TRUE)
			{
				class CDlgShowKeyParameter showparam;
				int maxoctets = ki->part1.noctets > ki->part2.noctets ? ki->part1.noctets : ki->part2.noctets;
				int hexreplen = sizeof("0x") + maxoctets * 2;
				char *hexrep = new char[hexreplen];
				if (hexrep == 0) {
					remove(string3);
					delete string2;
					delete string4;
					HIDE_HOUR_GLASS
					return;
				}
				mlen=ki->part1.noctets;
				buf=(unsigned char *)ki->part1.octets;
				sprintf(hexrep,"0x");
				for (i=0;i<mlen;i++)
					sprintf(hexrep+2+(2*i),"%02X",buf[i]);
				string_to_ln(hexrep,temp);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MODUL,pc_str,STR_LAENGE_STRING_TABLE);
				showparam.addentry(pc_str,temp);
				elen=ki->part2.noctets;
				buf=(unsigned char *)ki->part2.octets;
				sprintf(hexrep,"0x");
				for (i=0;i<elen;i++)
					sprintf(hexrep+2+(2*i),"%02X",buf[i]);
				string_to_ln(hexrep,temp);
				delete[] hexrep;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_EXPONENT,pc_str,STR_LAENGE_STRING_TABLE);
				showparam.addentry(pc_str,temp);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_DSA_SHOW_PUBLIC_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,UserKeyId);
				showparam.settitel(pc_str1);
				if (showparam.DoModal()!=IDOK)
				{
					remove(string3);
					// Freigeben von dynamisch angelegtem Speicher
					delete string2;
					delete string4;
					HIDE_HOUR_GLASS
					return;
				}

			}
		}
		HIDE_HOUR_GLASS

		// Initialisierung der Variablen, die zur Zertifizierung notwendig sind
		OctetString SNummer;
		char *string="000001";
		SNummer.noctets=strlen(string);
		SNummer.octets=string;

		DName *DisName; // Distinguishing Name: unter diesem Bezeichner/Namen wird das Zertifikat in die
		                // CA-Datenbank geschrieben
		CString string6 = KeyHandling.CreateDistName(UserName, UserFirstName, time_of_creat);
		LPTSTR string7 = new TCHAR[string6.GetLength()+1];
		_tcscpy(string7, string6);
		char *string8=string7;

		DisName=theApp.SecudeLib.aux_Name2DName(string8);

		// Erzeugung des self-signed Prototyp-Zertifikates
		// Erklärung der Parameter:
		// PseHandle    : 
		// keyinfo.key  : zu zertifizierender öff. Schl.
		// Algorithmus  : Algorithmus-Identifier
		// SKnew        : 
		// DisName
		// SNummer
		// NULL
		// NULL
		// TRUE
		// NULL

		Certificate *Zert;
		Zert=theApp.SecudeLib.af_create_Certificate (PseHandle, keyinfo.key, Algorithmus,"SKnew",
			DisName, &SNummer, NULL, NULL, TRUE, NULL); // Fails in Secude 7.4.60C and older if keylength >8200bit
		if (Zert==NULL)
		{
			// Fehler bei der Zertifikatserzeugung
			Message(IDS_STRING_ASYMKEY_ERR_CREATE_CERT_1, MB_ICONSTOP);
			// Lösche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}


		// Make it a X509.v3 certificate
		// Add extensions, in particular store the PSE name in a private extension.
		// This is required if the certificate is exported via PKCS#12 and later
		// imported by another CrypTool

		// get PSE name
		LPTSTR UserKeyId_str= new TCHAR[UserKeyId.GetLength()+1];
		_tcscpy(UserKeyId_str, UserKeyId);

		SEQUENCE_OF_Extension extensions;
		extensions.element = (v3Extension *) theApp.SecudeLib.aux_malloc(sizeof(v3Extension));
		extensions.element->extnId = CrypToolPSEName_OID();
		extensions.element->critical = false;
		extensions.element->extnDERcode = theApp.SecudeLib.e_PrintableString((char *) UserKeyId_str);
		extensions.next = NULL;
		delete [] UserKeyId_str;

		CertExtensions cert_ext;
		memset (&cert_ext, 0, sizeof(CertExtensions));
		cert_ext.nonSupported = &extensions;

		Zert->tbs->extensions = &cert_ext;


		PSE PseHandle2;
		
		// Öffnen der CA-PSE
		PseHandle2=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle2==NULL)
		{
			// Fehler beim Öffnen der CA-PSE
			Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Lösche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}
		unsigned long random_serial_number_bytes = 8;
		if ( ERROR_SUCCESS == CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "UserKeyStore") )
		{
			CT_READ_REGISTRY_DEFAULT(random_serial_number_bytes, "RandomSerialNumberBytes", random_serial_number_bytes);
			CT_CLOSE_REGISTRY();
		}
		if (random_serial_number_bytes >= 2) {
			SerialNumber *serial = theApp.SecudeLib.sec_random_ostr(random_serial_number_bytes, 1);
			if (serial == NULL) {
				// Fehler beim zufaelligen Waehlen der Seriennummer
				Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT); 
				// Lösche die neu angelegte PSE
				remove(string3);
				// Freigeben von dynamisch angelegtem Speicher
				delete string2;
				delete string4;
				delete string7;
				return;
			}
			Certificate *excert = theApp.SecudeLib.af_cadb_get_Certificate(PseHandle2, serial);
			if (excert) {
				Message(IDS_STRING_ASYMKEY_ERR_CERT_SERIAL_EXISTS, MB_ICONSTOP);
				theApp.SecudeLib.aux_free_OctetString(&serial);
				remove(string3);
				// Freigeben von dynamisch angelegtem Speicher
				delete string2;
				delete string4;
				delete string7;
				return;
			}
			theApp.SecudeLib.af_pse_update_SerialNumber(PseHandle2, serial);
			theApp.SecudeLib.aux_free_OctetString(&serial);
		}
		// Übergabe des Prototyp-Zertifikates an die CA, die den enthaltenen Schlüssel
		// zertifiziert
		Certificate *Zert2;
		Zert2=theApp.SecudeLib.af_certify(PseHandle2, Zert, NULL, theApp.SecudeLib.sha1WithRSASignature_aid /* theApp.SecudeLib.md5WithRsaEncryption_aid*/, NULL);
		if (Zert2==NULL)
		{
			// Fehler bei der Zertifizierung
			Message(IDS_STRING_ASYMKEY_ERR_CREATE_CERT_2, MB_ICONSTOP);
			// Lösche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}
		
		//Zertifikat in die CA-Datenbank einfügen!!!
		int fehler=theApp.SecudeLib.af_cadb_add_Certificate (PseHandle2, SIGNATURE, Zert2);
		if (fehler==-1)
		{
			// Fehler beim Einfügen des Zertifikats in die CA-Datenbank
			Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP);
			// Lösche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}

		// 2001-10-26 Martin Bartosch: added
		// get PKRoot object from CA PSE and copy it to the new PSE
		PKRoot * pkroot;
		pkroot = theApp.SecudeLib.af_pse_get_PKRoot(PseHandle2);
		if (pkroot)
		{
			fehler = theApp.SecudeLib.af_pse_update_PKRoot(PseHandle, pkroot);
			if (fehler==-1)
			{
				// Error writing certificate to the user PSE
				Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP);
				// Lösche die neu angelegte PSE
				remove(string3);
				// Freigeben von dynamisch angelegtem Speicher
				delete string2;
				delete string4;
				delete string7;
				theApp.SecudeLib.af_close(PseHandle2);
				theApp.SecudeLib.aux_free_DName (&DisName);
				theApp.SecudeLib.aux_free_PKRoot(&pkroot);
				theApp.SecudeLib.af_close(PseHandle);
				return;
			}
		}

		theApp.SecudeLib.aux_free_PKRoot(&pkroot);
		

		// 2001-10-22 Martin Bartosch: added
		// write certificate to PSE object
		fehler=theApp.SecudeLib.af_pse_update(PseHandle, "Cert", Zert2, *theApp.SecudeLib.Cert_OID);
		if (fehler==-1)
		{
			// Error writing certificate to the user PSE
			Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP);
			// Lösche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			theApp.SecudeLib.af_close(PseHandle2);
			theApp.SecudeLib.aux_free_DName (&DisName);
			theApp.SecudeLib.af_close(PseHandle);
			return;
		}

			
		theApp.SecudeLib.af_close(PseHandle2);
		theApp.SecudeLib.aux_free_DName (&DisName);
		theApp.SecudeLib.af_close(PseHandle);
		// Freigeben von dynamisch angelegtem Speicher

		delete string2;
		delete string4;
		delete string7;
	}

	// Eine Sekunde Verzögerung eingebaut, damit time_of_creat: Time in seconds since UTC 1/1/70
	// für verschiedene Schlüssel immer verschieden ist (Wahrung der EINDEUTIGKEIT von UserKeyId)
	Sleep(1000); // wait a second

	// user-information: key pair succesfully created.
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_STORE_KEYPAIR,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, UserKeyId);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_GENERATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
	char temp[256];
	char strDuration[20];
	double_fmt( duration, strDuration, 3 );
	sprintf(temp, pc_str, strDuration);
	AfxMessageBox (((CString)pc_str1)+((CString)"\n\n")+temp,MB_ICONINFORMATION);
}


// import PKCS#12 files; store private key and certificate in new PSE
// and in CA database
// 2001-11 Martin Bartosch; Cynops GmbH

void CDlgKeyAsymGeneration::OnButtonP12import() 
{
	CString p12_passwd;
	CString pse_passwd;
	SEQUENCE_OF_Extension *thisextension = NULL;
	char *PSEName_from_ext = NULL;
	char *PSEName = NULL;

	// pop up file selector box
	CFileDialog Dlg(TRUE, P12_FILE_SUFFIX, NULL, OFN_HIDEREADONLY,
	"PKCS #12 Files (*.p12)|*.p12|All Files (*.*)|*.*||", this);
	if(IDCANCEL == Dlg.DoModal()) return;

	CString p12_file = Dlg.GetPathName();

	// make temporary PSE file (will be removed or renamed later)
	PSEName = _tempnam(PseVerzeichnis, "pse");

	// check if PSE already exists
	if (_access(PSEName, 0) != -1)
	{
		Message(IDS_STRING_FILEEXISTS, MB_ICONEXCLAMATION);
		free(PSEName);
		return;
	}

	// read input file
	OctetString * input = theApp.SecudeLib.aux_file2OctetString(p12_file);

	if (!input) 
	{
		Message(IDS_STRING_FILEOPENERROR, MB_ICONEXCLAMATION);
		free(PSEName);
		return; // no selection
	}

	// get PIN for PKCS#12 file and PIN for new PSE
	LoadString(AfxGetInstanceHandle(),IDS_STRING_INPUT_P12PIN,pc_str,STR_LAENGE_STRING_TABLE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_INPUT_PSEPIN,pc_str1,STR_LAENGE_STRING_TABLE);

	CDlgChangePIN PinRequest(pc_str, pc_str1);
	if (PinRequest.DoModal() == IDOK)
	{
		p12_passwd = PinRequest.m_PinCode;
		pse_passwd = PinRequest.m_NewPinCode;
	}
	else 
	{
		theApp.SecudeLib.aux_free_OctetString(&input);
		free(PSEName);
		return;
	}



	LPTSTR pse_passwd_str = new TCHAR[pse_passwd.GetLength()+1];
	_tcscpy(pse_passwd_str, pse_passwd);
	char *pse_passwd_strptr = pse_passwd_str;

	// create new PSE
	PSE	pse = theApp.SecudeLib.af_create(PSEName, NULL, pse_passwd_strptr, NULL, TRUE);
	delete [] pse_passwd_str;

	if (!pse) 
	{
		theApp.SecudeLib.aux_free_OctetString(&input);
		Message(IDS_STRING_PSECREATIONERROR, MB_ICONINFORMATION);
	    // aux_print_error(NULL, verbose);
		free(PSEName);
		theApp.SecudeLib.af_close(pse);
		theApp.SecudeLib.aux_free_OctetString(&input);
	    return;
	}


	LPTSTR p12_passwd_str = new TCHAR[p12_passwd.GetLength()+1];
	_tcscpy(p12_passwd_str, p12_passwd);
	char *p12_passwd_strptr = p12_passwd_str;

	OctetString * p12_passwd_ostr = theApp.SecudeLib.aux_latin1_to_unicode(p12_passwd_strptr, TRUE);
	delete [] p12_passwd_str;

	int rc = PKCS12_import(pse, input, p12_passwd_ostr, 1);
	if (rc) 
	{
	 	AfxMessageBox("Could not decode PKCS#12 file", MB_ICONINFORMATION, 0);
	    // aux_print_error(NULL, verbose);
		remove(PSEName);
		free(PSEName);
		theApp.SecudeLib.aux_free_OctetString(&p12_passwd_ostr);
		theApp.SecudeLib.af_close(pse);
		theApp.SecudeLib.aux_free_OctetString(&input);
		return;
	}
	theApp.SecudeLib.aux_free_OctetString(&p12_passwd_ostr);


	// The certificate is now stored in the PSE
	// get it and register it in the CA database
	// NOTE: this is a hack that is necessary because of the 
	// way CrypTool handles its certificates.
	// As a side effect, it is probably not possible to import
	// certificates not issued by CrypTool.
	
	Certificate * cert = theApp.SecudeLib.af_pse_get_Certificate(pse, SIGNATURE, NULL, NULL);
 	if (!cert)
	{
		Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT );
		// remove newly created PSE
		remove(PSEName);
		free(PSEName);
		theApp.SecudeLib.af_close(pse);
		theApp.SecudeLib.aux_free_OctetString(&input);
		return;
	}

	theApp.SecudeLib.af_close(pse);


	// get certificate extensions
	PSEName_from_ext = NULL;
	if (cert->tbs->extensions)
		for (thisextension = cert->tbs->extensions->nonSupported; thisextension; thisextension = thisextension->next)
			if (theApp.SecudeLib.aux_cmp_ObjId(thisextension->element->extnId, CrypToolPSEName_OID()) == 0)
				// found private PSE name extension
				PSEName_from_ext = theApp.SecudeLib.d_PrintableString(thisextension->element->extnDERcode);


	// get proper name for the PSE
	if (PSEName_from_ext)
	{
		// if our private extension is present, use the PSE name contained in the extension
		// and rename the temporary PSE to this name

		CString tmp = (CString) PseVerzeichnis + ((CString)"/") + (CString) PSEName_from_ext + (CString)PSE_FILE_SUFFIX;
		theApp.SecudeLib.aux_free(PSEName_from_ext);

		LPTSTR tmp_str = (LPTSTR) calloc(tmp.GetLength() + 1, sizeof(TCHAR));
		_tcscpy(tmp_str, tmp);

		rename(PSEName, (char *) tmp_str);
		free(PSEName);
		PSEName = (char *) tmp_str;
	}
	else
	{
		// this seems to be an old certificate (issued by an older version of CrypTool) or
		// a certficate that has not been issued by cryptool at all.

		// determine if this is a CrypTool cert
		char *issuer_name = theApp.SecudeLib.aux_DName2Name(cert->tbs->issuer);
		if (issuer_name)
		{
			if (strstr(issuer_name, DN_SUFFIX))
			{
				// this is a CrypTool certificate, try to extract the relevant data

				// compose PSE name from certificate data
				char * subject_name = theApp.SecudeLib.aux_DName2Name(cert->tbs->subject);
	
				CString FirstName, LastName, CreationTime, Algorithm, KeySize;
				LastName = subject_name;
				LastName.Delete(0, LastName.Find("CN=") + 3);

				FirstName = LastName.Left(LastName.Find(" "));
				LastName.Delete(0, FirstName.GetLength() + 1);
				LastName = LastName.Left(LastName.Find(" "));

				CreationTime = subject_name;
				CreationTime.Delete(0, CreationTime.Find("[") + 1);
				CreationTime = CreationTime.Left(CreationTime.Find("]"));

				theApp.SecudeLib.aux_free(&subject_name);

				// get algorithm ID
				char * alg_name = theApp.SecudeLib.aux_sprint_AlgId(NULL, cert->tbs->subjectPK->subjectAI);

				KeySize = alg_name;
				KeySize.Delete(0, KeySize.Find("Keysize =") + 9);
				KeySize.TrimLeft(" ");
				KeySize = KeySize.SpanIncluding("0123456789");

				Algorithm = alg_name;
				Algorithm.Delete(0, Algorithm.Find("Algorithm") + 9);
				Algorithm.TrimLeft(" ");
				Algorithm = Algorithm.Left(Algorithm.Find("(OID"));
				Algorithm.TrimRight(" ");
				
				theApp.SecudeLib.aux_free(&alg_name);

				// construct PSE name
				CString tmp = (CString) PseVerzeichnis + 
					(CString)"/[" + LastName + (CString) "][" + 
					FirstName + (CString) "][" + 
					Algorithm + (CString) "-" + KeySize + (CString) "][" +
					CreationTime + (CString) "]" + 
					(CString) PSE_FILE_SUFFIX;

				LPTSTR tmp_str = (LPTSTR) calloc(tmp.GetLength() + 1, sizeof(TCHAR));
				_tcscpy(tmp_str, tmp);

				rename(PSEName, (char *) tmp_str);
				free(PSEName);
				PSEName = (char *) tmp_str;
			}
			else
			{
				// this is not a CrypTool certificate - for now we cannot process these
				// certificates because of the internal PSE handling.
				// FIXME: find out what we can do about it.
				Message(IDS_STRING_INCOMPATIBLE_CERT, MB_ICONSTOP);

				remove(PSEName);
				free(PSEName);
				theApp.SecudeLib.aux_free(&issuer_name);
				theApp.SecudeLib.aux_free_Certificate(&cert);
				theApp.SecudeLib.aux_free_OctetString(&input);
				return;
			}

			theApp.SecudeLib.aux_free(&issuer_name);
		}
		else
		{
			// FIXME: error handling
			Message(IDS_STRING_CERT_DECODING_ERROR, MB_ICONSTOP);
			remove(PSEName);
			free(PSEName);
			theApp.SecudeLib.aux_free(&issuer_name);
			theApp.SecudeLib.aux_free_Certificate(&cert);
			theApp.SecudeLib.aux_free_OctetString(&input);
			return;
		}
	}


	// Open CA PSE
	PSE capse = theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
	if (!capse)
	{
		Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
	
		remove(PSEName);
		free(PSEName);
		theApp.SecudeLib.aux_free_Certificate(&cert);
		theApp.SecudeLib.aux_free_OctetString(&input);
		return;
	}

	Certificate *excert = theApp.SecudeLib.af_cadb_get_Certificate(capse, cert->tbs->serialnumber);
	if (excert) {
		Message(IDS_STRING_ASYMKEY_ERR_CERT_SERIAL_EXISTS, MB_ICONSTOP);
		// remove newly created PSE
		remove(PSEName);
		free(PSEName);
		theApp.SecudeLib.aux_free_Certificate(&excert);
		theApp.SecudeLib.aux_free_Certificate(&cert);
		theApp.SecudeLib.af_close(capse);
		theApp.SecudeLib.aux_free_OctetString(&input);
		return;
	}
	rc = theApp.SecudeLib.af_cadb_add_Certificate (capse, SIGNATURE, cert);
	if (rc)
	{
		// Fehler beim Einfügen des Zertifikats in die CA-Datenbank
		Message(IDS_STRING_ASYMKEY_ERR_ADD_CERT, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
		// remove newly created PSE
		remove(PSEName);
		free(PSEName);
		theApp.SecudeLib.aux_free_Certificate(&cert);
		theApp.SecudeLib.af_close(capse);
		theApp.SecudeLib.aux_free_OctetString(&input);
		return;
	}

	free(PSEName);
	theApp.SecudeLib.aux_free_Certificate(&cert);
	theApp.SecudeLib.aux_free_OctetString(&input);
	theApp.SecudeLib.af_close(capse);
}


void CDlgKeyAsymGeneration::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//Invalidate();
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	//get the row number
	int nItem = temp->iItem;
	//get the column number
	int nSubItem = temp->iSubItem;
	if(nSubItem == 0 || nSubItem == -1 || nItem == -1)
		return ;
	//Retrieve the text of the selected subItem from the list
	CString str = GetItemText(hWnd1,nItem ,nSubItem);
	//WndProc: hwnd=0x3E0A98, msg = WM_NOTIFY (0x0418, 0x0012E240)
	RECT rect;  // subitem
	RECT rect0; // item 0
	RECT rect1; // list
	RECT rect2; // dialog
	// this macro is used to retrieve the Rectanle of the selected SubItem
	ListView_GetSubItemRect(hWnd1,temp->iItem,temp->iSubItem,LVIR_BOUNDS,&rect);
	ListView_GetSubItemRect(hWnd1,ListView_GetTopIndex(hWnd1),0,LVIR_BOUNDS,&rect0);
	rect.left -= rect0.left;
	rect.top  -= rect0.top;
	//Get the Rectange of the listControl
	::GetWindowRect(temp->hdr.hwndFrom,&rect1);
	//::GetWindowRect(hWnd1,&rect1);
	//Get the Rectange of the Dialog
	::GetWindowRect(m_hWnd,&rect2);

	int x=rect1.left-rect2.left; // list x relative to dialog
	int y=rect1.top-rect2.top;   // list y relative to dialog
	
	HWND edit = ::GetDlgItem(m_hWnd,IDC_EDIT_LV);
	//if(nItem != -1)	
	//::SetWindowPos(edit,HWND_TOP,rect.left+x,rect.top+y+4,rect.right-rect.left - 3,rect.bottom-rect.top -1,NULL);
	::SetWindowPos(edit,HWND_TOP,x+rect.left + 5, y+rect.top -1, rect.right-rect.left, rect0.bottom-rect0.top,NULL);
	::ShowWindow(edit,SW_SHOW);
	::SetFocus(edit);
	//Draw a Rectangle around the SubItem
	//::Rectangle(::GetDC(temp->hdr.hwndFrom),rect.left,rect.top-1,rect.right,rect.bottom);
	//Set the listItem text in the EditBox
	::SetWindowText(edit,str);
	*pResult = 0;
}

//this function will returns the item text depending on the item and SubItem Index
CString CDlgKeyAsymGeneration::GetItemText(HWND hWnd, int nItem, int nSubItem) const
{
	LVITEM lvi;
	memset(&lvi, 0, sizeof(LVITEM));
	lvi.iSubItem = nSubItem;
	CString str;
	int nLen = 128;
	int nRes;
	do
	{
		nLen *= 2;
		lvi.cchTextMax = nLen;
		lvi.pszText = str.GetBufferSetLength(nLen);
		nRes  = (int)::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)nItem,
			(LPARAM)&lvi);
	} while (nRes == nLen-1);
	str.ReleaseBuffer();
	return str;
}

void CDlgKeyAsymGeneration::OnKillfocusEditLv() 
{
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT_LV),SW_HIDE);
}


void CDlgKeyAsymGeneration::showRSAKeysOnly()
{
	this->m_showRSAKeysOnly = true;
}

void CDlgKeyAsymGeneration::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
