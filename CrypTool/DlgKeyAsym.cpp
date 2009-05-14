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
// DlgAsymKeys.cpp: Implementierungsdatei
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyAsym.h"
#include "KeyFileHandling.h"
#include "DlgKeyAsymGeneration.h"
#include "DlgPINAccess.h"
#include "DlgChangePIN.h"
#include "DlgShowPublicKeyEC.h"
#include "DlgShowPrivateKeyEC.h"
#include "DlgShowCertificate.h"
#include "DlgShowKeyParameter.h"
#include "s_ecconv.h"
#include "s_ecFp.h" // elliptic curve stuff
#include "s_prng.h" // big random integers

#include "SecudeTools.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globale Variablen
extern char *PseVerzeichnis, *CaPseDatei, *CaPseVerzeichnis; // siehe multipda.cpp

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyAsym 


CDlgKeyAsym::CDlgKeyAsym(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyAsym::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyAsym)
	//}}AFX_DATA_INIT

	UserKeyId = "";
	Name = "";
	Firstname = "";
	KeyType = "";
	KeyInfo = "";
	CreatTimeUTC = "";
	CreatTime = "";

	m_lastSelectedRow = -1; //  Änderung in Member-Funktion CDlgKeyAsym::OnClickList3()
}

/*
CDlgKeyAsym::~CDlgKeyAsym()
{
}
*/

void CDlgKeyAsym::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyAsym)
	DDX_Control(pDX, IDC_BUTTON3, m_RemoveItem);
	DDX_Control(pDX, IDC_CHECK3, m_CheckEC);
	DDX_Control(pDX, IDC_CHECK2, m_CheckDSA);
	DDX_Control(pDX, IDC_CHECK1, m_CheckRSA);
	DDX_Control(pDX, IDC_BUTTON4, m_show_cert_button);
	DDX_Control(pDX, IDC_BUTTON5, m_export_cert_button);
	DDX_Control(pDX, IDC_LIST3, m_listview);
	DDX_Control(pDX, IDC_BUTTON2, m_secret_param_button);
	DDX_Control(pDX, IDC_BUTTON1, m_pub_param_button);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyAsym, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyAsym)
	ON_BN_CLICKED(IDC_BUTTON1, OnShowPubParamButton)
	ON_BN_CLICKED(IDC_BUTTON2, OnShowAllParamButton)
	ON_BN_CLICKED(IDC_BUTTON3, OnDeleteEntryButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonShowCert)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonExportCert)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST3, OnColumnclickList3)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST3, OnItemclickList3)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST3, OnKeydownList3)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckRsaKey)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckDsaKey)
	ON_BN_CLICKED(IDC_CHECK3, OnCheckEcKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyAsym 


BOOL CDlgKeyAsym::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// m_listview in Report-Mode initialisieren

	int colWidth = 100;  // Spaltenbreite in Pixel

	// Other Functions are now obsolete (see marker XXXX OBSOLETE XXXX)
	m_listview.SetExtendedStyle( LVS_EX_FULLROWSELECT );

	LoadString(AfxGetInstanceHandle(),IDS_STRING_NAME,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 0, pc_str, LVCFMT_LEFT, colWidth-15 , 0); // Name

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PRENAME,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, colWidth-25 , 1); // Vorname

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYTYPE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, colWidth-15 , 2); // Schlüsseltyp

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_IDENTIFIER,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 3, pc_str, LVCFMT_LEFT, colWidth , 3); // Schlüsselkennung
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_CREATION_DATW,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 4, pc_str, LVCFMT_LEFT, colWidth+15 , 4); // Erstellungsdatum

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_ID,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 5, pc_str, LVCFMT_LEFT, colWidth-20 , 5); // Interne ID-Nr.


	sortBy = BY_NAME; // default Einstellung: sortiere Liste nach Namen
	
	// Initialisiere die Schlüsselliste mit allen verfügbaren asymmetrischen Schlüsseln
	m_CheckRSA.SetCheck(1);
	m_CheckDSA.SetCheck(1);
	m_CheckEC.SetCheck(1);
	nKeylistType = ASYM_KEY;
	InitAsymKeyListBox(nKeylistType);
	
	m_RemoveItem.EnableWindow(FALSE);
	m_secret_param_button.EnableWindow(FALSE); // Button einblenden
	m_pub_param_button.EnableWindow(FALSE); // Button einblenden
	m_show_cert_button.EnableWindow(FALSE); // Button ausblenden
	m_export_cert_button.EnableWindow(FALSE); // Button ausblenden

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


//////////////////////////////////////////////////////////////////////////////////////
// Öffentliche Schlüsselparameter anzeigen für
// - EC-Schlüssel
// - RSA-Schlüssel

void CDlgKeyAsym::OnShowPubParamButton() 
{
	if ( KeyType.Find(EC_KEYFILE_IDSTRING) > -1 ) 
	{
		if ( sortedAsymKeyList.IsEmpty() )
		{
			// there is no string selectable
			Message(IDS_STRING_KEYLIST_ASYM_EMPTY, MB_ICONINFORMATION);
			return; // no selection
		}
		else if (UserKeyId.GetLength() < 1)
		{
			// there is no selected string
			Message(IDS_STRING_KEYLIST_ASYM_SELECT, MB_ICONINFORMATION);
			return; // no selection
		}

		m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

		EcDomParam_ac_ptr curveParameter;
		
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

		CKeyFile KeyFileHandling;
		int ret;
		ret = KeyFileHandling.GetEcPublicParam(UserKeyId, curveParameter);
		if ( ret == -1 )
		{
			// error. Die Datei "UserKeyId" konnte nicht geöffnet werden
			CString PubDataFile = (CString) PseVerzeichnis + ((CString)"/") + (CString) UserKeyId;
			{
				LPTSTR string3 = new TCHAR[PubDataFile.GetLength()+1];
				_tcscpy(string3, PubDataFile);		
				char *toc_file = string3;

				Message(IDS_STRING_EC_ERROR_LOADING_KEYFILE, MB_ICONINFORMATION, toc_file);
				delete string3;
			}
			free (curveParameter->pubKey);
			free (curveParameter->G);
			free (curveParameter->E);
			free (curveParameter);		
			return;
		}
		else if ( ret != 0)
		{
			// error. sonstige Fehler in der Methode CKeyFile::GetEcPublicParam()
			free (curveParameter->pubKey);
			free (curveParameter->G);
			free (curveParameter->E);
			free (curveParameter);		
			return;
		}

		CDlgShowPublicKeyEC PubParamDlg(UserKeyId, Name, Firstname, CreatTime, KeyType, curveParameter);
		if (PubParamDlg.DoModal()==IDCANCEL) CDialog::OnCancel();

		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
	}
	else if ( KeyType.Find(RSA_KEYFILE_IDSTRING) > -1 )
	{

		if ( sortedAsymKeyList.IsEmpty() )
		{
			// there is no string selectable
			Message(IDS_STRING_KEYLIST_ASYM_EMPTY, MB_ICONINFORMATION );
			return; // no selection
		}
		else if ( UserKeyId.GetLength() < 1 )
		{
			// there is no selected string
			Message(IDS_STRING_KEYLIST_ASYM_SELECT, MB_ICONINFORMATION);
			return; // no selection
		}

		m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

		CKeyFile KeyHandling;
		CString caDB_keyid_name = KeyHandling.CreateDistName(Name, Firstname, CreatTimeUTC);
		// cDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben

		// Öffnen der CA-PSE
		PSE PseHandle;
		PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle==NULL)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			return;
		}
		
		// Besorgen des Zertifikates der Adressaten
		SET_OF_IssuedCertificate *Liste;
		{
			LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
			_tcscpy(string3, caDB_keyid_name);
			char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 
			Liste=theApp.SecudeLib.af_cadb_get_user (PseHandle, string4);
			delete [] string3;
		}

		if (Liste==NULL)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			return;
		}
		
		Certificate *Zert;
		OctetString *SNummer;
		SNummer=Liste->element->serial;
		Zert=theApp.SecudeLib.af_cadb_get_Certificate (PseHandle, SNummer);
		if (Zert==NULL)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
			theApp.SecudeLib.af_close (PseHandle);
			return;
		}
		
		// Besorgen des öffentlichen Schlüssels des Adressaten aus seinem Zertifikat
		Key Schluessel;
		Schluessel.key=Zert->tbs->subjectPK;
		Schluessel.pse_sel=NULL;
		Schluessel.alg=theApp.SecudeLib.rsa_aid;
		Schluessel.add_object=NULL;
		Schluessel.add_object_type=NULL;
		Schluessel.key_size=NULL;
		Schluessel.private_key=NULL;

		CDlgShowKeyParameter dlg;

		LoadString(AfxGetInstanceHandle(), IDS_DLG_KEY_ASYM_TITLE, pc_str, STR_LAENGE_STRING_TABLE);
		dlg.m_Title = pc_str;
		dlg.m_Title+= Firstname;
		dlg.m_Title+= " ";
		dlg.m_Title+= Name;
		dlg.disableOkButton = true;
		KeyBits *ki;
		ki=theApp.SecudeLib.d_KeyBits(&(Schluessel.key->subjectkey));
		int mlen = ki->part1.noctets;
		unsigned char* buf = (unsigned char*) ki->part1.octets;
		L_NUMBER temp[MAXLGTH];
		char temphex[sizeof("0x") + (MAXKEYLENGTH+3)/4];
		sprintf(temphex,"0x");

		int i;
		for (i=0;i<mlen;i++)
		{
			sprintf(temphex+2+(2*i),"%02X",buf[i]);	
		}
		string_to_ln(temphex,temp);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MODUL,pc_str,STR_LAENGE_STRING_TABLE);
		dlg.addentry(pc_str,temp);

		int mlen2 = ki->part2.noctets;
		unsigned char* buf2 = (unsigned char*) ki->part2.octets;
		sprintf(temphex,"0x");
		for (i=0;i<mlen2;i++)
		{
			sprintf(temphex+2+(2*i),"%02X",buf2[i]);
		}
		string_to_ln(temphex,temp);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_EXPONENT,pc_str,STR_LAENGE_STRING_TABLE);
		dlg.addentry(pc_str,temp);
		
		dlg.DoModal();
		UpdateData(false);	
	}
}

void CDlgKeyAsym::OnShowAllParamButton() 
{
	CString passwd;

	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		Message(IDS_STRING_KEYLIST_ASYM_EMPTY, MB_ICONINFORMATION);
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// there is no selected string
		Message(IDS_STRING_KEYLIST_ASYM_SELECT, MB_ICONINFORMATION);
		return; // no selection
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

	// passwd erfragen
	CDlgPINAccess PinCodeDialog(1, UserKeyId);
	if (PinCodeDialog.DoModal() == IDOK)
	{
		passwd = PinCodeDialog.m_PinCode;
	}
	else return;

	EcDomParam_ac_ptr curveParameter;
	
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

	CKeyFile KeyFileHandling;
	int ret;
	ret = KeyFileHandling.GetEcAllParam(UserKeyId, passwd, curveParameter);
	if ( ret == -1)
	{
		// falsche PIN-Nummer zum öffnen der PSE benutzt
		Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
		// Speicher freigeben
		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
		return;
	}
	else if ( ret == -2)
	{
		// sonstiger Fehler beim öffnen der PSE
		Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP);
		// Speicher freigeben
		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
		return;
	}
	else if (ret != 0)
	{
		// sonstiger Fehler in CKeyFile::GetEcAllParam()
		// Speicher freigeben
		free (curveParameter->pubKey);
		free (curveParameter->G);
		free (curveParameter->E);
		free (curveParameter);
		return;
	}

	CDlgShowPrivateKeyEC PrivParamDlg(UserKeyId, Name, Firstname, CreatTime, KeyType, curveParameter);
	if (PrivParamDlg.DoModal()==IDCANCEL) CDialog::OnCancel();

	free (curveParameter->pubKey);
	free (curveParameter->G);
	free (curveParameter->E);
	free (curveParameter);
}

void CDlgKeyAsym::OnDeleteEntryButton() 
{
	CKeyFile DataFile;
	int ret;
	CString passwd;
	
	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		Message(IDS_STRING_KEYLIST_ASYM_EMPTY, MB_ICONINFORMATION);
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// there is no selected string
		Message(IDS_STRING_KEYLIST_ASYM_SELECT, MB_ICONINFORMATION);
		return; // no selection
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

	// Nachfragen, ob das Schlüsselpaar wirklich gelöscht werden soll
	CString InfoString;
	AfxFormatString1( InfoString, IDS_STRING_ASSURE_DEL_ASYM_KEY, UserKeyId ); 
	if (AfxMessageBox(InfoString,MB_ICONQUESTION | MB_OKCANCEL, 0 ) == IDCANCEL)
	{
		return; // es wird nichts gelöscht
	}

	// die Schlüsseldateien sollen gelöscht werden.
	// passwd erfragen
	CDlgPINAccess PinCodeDialog(0, UserKeyId);
	if (PinCodeDialog.DoModal() == IDOK)
	{
		passwd = PinCodeDialog.m_PinCode;
	}
	else return;


	if (UserKeyId.Find(EC_KEYFILE_IDSTRING ) == -1 )
	{
		// DSA oder RSA Schlüsselbezeichner gewählt
		// lösche die Datei mit dem geheimen Schlüssel
		ret=DataFile.DeleteUserKeyFiles(UserKeyId, passwd, 1);
		if ( ret == -1 )
		{
			// falsche PIN-Nummer benutzt
			Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
			return;
		}
		else if ( ret != 0)
		{
			// sonstiger Fehler beim öffnen der PSE
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP);
			return;
		}

	}
	else
	{
		// ellipt. Kurven Schlüsselbezeichner
		// lösche die Dateie mit dem geheimen Schlüssel und die Datei mit den öffentlichen Parametern
		ret = DataFile.DeleteUserKeyFiles(UserKeyId, passwd, 0);
		if ( ret == -1 )
		{
			// falsche PIN-Nummer benutzt
			Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
			return;

		}
		else if ( ret != 0)
		{
			// sonstiger Fehler beim öffnen der PSE
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE,MB_ICONSTOP);
			return;
		}
	}

	InitAsymKeyListBox(nKeylistType); // m_listview neu mit Werten initialisieren
	UserKeyId = ""; // gelöscht!
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein
}


void CDlgKeyAsym::OnButtonShowCert() 
{
	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		Message(IDS_STRING_KEYLIST_ASYM_EMPTY,MB_ICONINFORMATION);
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// there is no selected string
		Message(IDS_STRING_KEYLIST_ASYM_SELECT, MB_ICONINFORMATION);
		return; // no selection
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

	CKeyFile KeyHandling;
	CString caDB_entry_name = KeyHandling.CreateDistName(Name, Firstname, CreatTimeUTC);
	// caDB_entry_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
	LPTSTR string1 = new TCHAR[caDB_entry_name.GetLength()+1];
	_tcscpy(string1, caDB_entry_name);
	char *Auswahl=string1; // Auswahl entspricht caDB_entry_name

	PSE PseHandle;
	PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
	if (PseHandle==NULL)
	{
		// Fehler beim öffnen der CA-Datenbank
		Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
		// Freigeben von dynamisch angelegtem Speicher
		delete string1;
		return;
	}

	//Routine für das Holen von Zertifikaten aus der CA-Datenbank
	SET_OF_IssuedCertificate *Zert;
	Zert=theApp.SecudeLib.af_cadb_get_user(PseHandle, Auswahl);
	if (Zert==NULL)
	{
		// Fehler beim lesen des Zertifikats
		char *Fehler=theApp.SecudeLib.LASTTEXT;
		CString Fehler2=Fehler;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_GET_PSE,pc_str,STR_LAENGE_STRING_TABLE);
		CString Fehler3=(CString)pc_str+(CString)Fehler2;
		AfxMessageBox (Fehler3,MB_ICONSTOP);
		// Freigeben von dynamisch angelegtem Speicher
		delete string1;
		theApp.SecudeLib.af_close(PseHandle);
		return;
	}
		
	Certificate *Zert2;
	OctetString *SNummer;
	SNummer=Zert->element->serial;
	Zert2=theApp.SecudeLib.af_cadb_get_Certificate(PseHandle, SNummer);
    //*theApp.SecudeLib.print_cert_flag = DER | TBS | KEYINFO | VAL | ISSUER |ALG |SIGNAT | HSH | VER | SUBJECT | EXTENSIONS | NOASN1;
    *theApp.SecudeLib.print_cert_flag = TBS | KEYINFO | VAL | ISSUER |ALG |SIGNAT | HSH | VER | SUBJECT | EXTENSIONS;
    //*theApp.SecudeLib.print_keyinfo_flag = ALGID | BITSTRING | KEYBITS | PK | SK | ALGINFO;
	*theApp.SecudeLib.print_keyinfo_flag = ALGID | KEYBITS | PK;
	CString Zertifikat=sprint_Certificate_with_key(PseHandle,NULL,Zert2);
	{	CDlgShowCertificate DCert(Zertifikat, NULL);
		if (DCert.DoModal()==IDCANCEL) CDialog::OnCancel();
	}
	
	theApp.SecudeLib.af_close(PseHandle);

	// Freigeben von dynamisch angelegtem Speicher
	delete string1;
	
	return;
}

// 2001-10 Martin Bartosch; Cynops GmbH
// added PKCS#12 export
void CDlgKeyAsym::OnButtonExportCert() 
{
	CKeyFile DataFile;
	CString passwd;
	CString export_passwd;
	
	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		Message(IDS_STRING_KEYLIST_ASYM_EMPTY, MB_ICONINFORMATION );
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// there is no selected string
		Message(IDS_STRING_KEYLIST_ASYM_SELECT, MB_ICONINFORMATION);
		return; // no selection
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

	// Query PINs for PSE and PKCS#12 file
	LoadString(AfxGetInstanceHandle(),IDS_STRING_INPUT_PSEPIN,pc_str,STR_LAENGE_STRING_TABLE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_INPUT_P12PIN,pc_str1,STR_LAENGE_STRING_TABLE);

	CDlgChangePIN PinRequest(pc_str, pc_str1);
	if (PinRequest.DoModal() == IDOK)
	{
		passwd = PinRequest.m_PinCode;
		export_passwd = PinRequest.m_NewPinCode;
	}
	else return;

	// get absolute PSE file name
	CString PSE_file = (CString) PseVerzeichnis + ((CString)"/") + UserKeyId + ((CString)PSE_FILE_SUFFIX);

	// copy PSE file name
	LPTSTR PSE_file_str = new TCHAR[PSE_file.GetLength()+1];
	_tcscpy(PSE_file_str, PSE_file);		
	char *PSE_file_strptr = PSE_file_str;

	// copy PIN
	LPTSTR passwd_str= new TCHAR[passwd.GetLength()+1];
	_tcscpy(passwd_str, passwd);
	char *passwd_strptr = passwd_str;

	// Open PSE and export certificate as PKCS #12 structure
	PSE PseHandle;
	PseHandle = theApp.SecudeLib.af_open(PSE_file_strptr, NULL, passwd_strptr, NULL);

	if (!PseHandle)
	{	// report PSE open error 

		Message(IDS_STRING_PSEOPENERROR, MB_ICONSTOP, PSE_file_strptr, theApp.SecudeLib.LASTTEXT);

		delete [] passwd_str;
		delete [] PSE_file_str;
		return;
	}
	delete [] passwd_str;
	delete [] PSE_file_str;

	// pop up "save as" file selector box
	CFileDialog Dlg(FALSE, P12_FILE_SUFFIX, UserKeyId, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
	"PKCS #12 Files (*.p12)|*.p12||", this);
	if(IDCANCEL == Dlg.DoModal()) return;

	CString p12_file = Dlg.GetPathName();

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein


	// FIXME: get password from GUI
	LPTSTR export_passwd_str = new TCHAR[export_passwd.GetLength()+1];
	_tcscpy(export_passwd_str, export_passwd);		
	char *export_passwd_strptr = export_passwd_str;

	OctetString * export_passwd_ostr;
	export_passwd_ostr = theApp.SecudeLib.aux_latin1_to_unicode(export_passwd_strptr, TRUE);
	delete [] export_passwd_str;

	// PSE is now open; get Cert and SKNew objects and stuff them into a 
	// PKCS#12 structure
	OctetString *P12_Obj = PKCS12_encode(PseHandle, export_passwd_ostr, 1, 1);
	if (!P12_Obj)
	{
		Message(IDS_STRING_P12_CREAT_FAILED, MB_ICONSTOP, PSE_file_strptr, theApp.SecudeLib.LASTTEXT);
		return;
	}

	// copy p12 file name
	LPTSTR p12_file_str = new TCHAR[p12_file.GetLength()+1];
	_tcscpy(p12_file_str, p12_file);		
	char *p12_file_strptr = p12_file_str;

	RC rc = theApp.SecudeLib.aux_OctetString2file(P12_Obj, p12_file_strptr, 2); // 2: 'create or overwrite'

	delete [] p12_file_str;
	
	theApp.SecudeLib.aux_free_OctetString(&P12_Obj);
	theApp.SecudeLib.af_close(PseHandle);

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein
}

void CDlgKeyAsym::InitAsymKeyListBox(unsigned nLocalKeylistType)
{
	// ermittele die zur Verfügung stehenden Schlüssel(-bezeichner) aus der Liste sortedAsymKeyList
	// und füge Sie in m_listview ein.
	// nLocalKeyType gibt an, welche Schlüsselbezeichner angezeigt werden:
	// nLocalKeyType == ASYM_KEY : alle (EC, RSA, DSA)
	// nLocalKeyType == EC_KEY  : nur EC
	// nLocalKeyType == RSA_KEY : nur RSA
	// nLocalKeyType == DSA_KEY : nur DSA
	// nLocalKeyType == DSA_KEY | RSA_KEY : DSA und RSA 
	// usw...

	CAsymmKeyAttrib keydata;
	CAvailabAsymmKeys asymmKeys;
	int row; // Zeile

	m_listview.DeleteAllItems( ); // Alle bisherigen Einträge (sofern vorhanden) löschen

	// ermittele alle vorhandenen Schlüsselbezeichner vom Typ nLocalKeylistType die im PseVerzeichnis liegen
	int ret = asymmKeys.GetKeyList( sortedAsymKeyList, nLocalKeylistType, sortBy);

	row = 0;
	if ( ! sortedAsymKeyList.IsEmpty() )
	{
		// es gibt mindestens ein asymmetrische Schlüsselpaar
		POSITION listptr = sortedAsymKeyList.GetHeadPosition();
		while( listptr )
		{
			// es gibt mindestens einen weiteren Eintrag in der Liste
			keydata = sortedAsymKeyList.GetNext(listptr);
			// Einfügen in nächste Zeile von m_listview

			m_listview.InsertItem( row, keydata.Name );

			m_listview.SetItemText( row, 1, keydata.Firstname );
			m_listview.SetItemText( row, 2, keydata.KeyType );
			if (keydata.PersKeyInfo.GetLength()>0) m_listview.SetItemText( row, 3, keydata.PersKeyInfo );
			m_listview.SetItemText( row, 4, (CString) keydata.CreatTime );
			m_listview.SetItemText( row, 5, (CString) keydata.UTCstring ); // Time in seconds since UTC 1/1/70

			row++;
		}
	}
} 


// XXXX OBSOLETE XXXX
void CDlgKeyAsym::UpdateRowSel(int row) 
{
	int i;
	CString Text;

	if (m_lastSelectedRow != -1)
	{
		// Status der m_lastSelectedRow Zeile auf normal setzen (Highlighten rückgängig machen);
		for (i=0; i<6; i++) // i durchläuft die Spalten 0,1,2,3,4 und 5 
		{
			m_listview.SetItem(m_lastSelectedRow, i, LVIF_STATE, NULL, 0, NULL, LVIS_SELECTED, m_lastSelectedRow);
		}
		UpdateWindow();
	}

	if (row == -1)
	{
		m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein
		m_RemoveItem.EnableWindow(FALSE);
		m_secret_param_button.EnableWindow(FALSE); // Button einblenden
		m_pub_param_button.EnableWindow(FALSE); // Button einblenden
		m_show_cert_button.EnableWindow(FALSE); // Button ausblenden
		m_export_cert_button.EnableWindow(FALSE); // Button ausblenden
		return;
	}
	m_RemoveItem.EnableWindow();

	m_lastSelectedRow = row; // m_lastSelectedRow neu setzen

	// Farbliches hervorheben der Zeile row (highlighten) und gleichzeitig Werte auslesen
	for (i=0; i<6; i++) // i durchläuft die Spalten 0,1,2,3,4 und 5 
	{
		Text = m_listview.GetItemText( row, i );

		if (i==0) Name = Text;
		else if (i==1) Firstname = Text;
		else if (i==2) KeyType = Text;
		else if (i==3) KeyInfo = Text;
		else if (i==4) CreatTime = Text;
		else if (i==5) CreatTimeUTC = Text; // CreatTimeUTC: Time in seconds since UTC 1/1/70

		if (Text.GetLength() == 0)
		{
			continue; // Falls in der aktuellen Spalte kein Text vorhanden ist, gehe zur nächsten Spalte
		}
		m_listview.SetItem(row, i, LVIF_TEXT | LVIF_STATE, Text, 0, LVIS_SELECTED, LVIS_SELECTED, row);
		m_listview.SetItemText( row, i, Text );
	}

	UserKeyId = "";
	CKeyFile KeyHandling;
	UserKeyId = KeyHandling.CreateFilename2(Name, Firstname, KeyType, CreatTimeUTC, KeyInfo);

	if (KeyType.Find(EC_KEYFILE_IDSTRING ) > -1 )
	{
		// ellipt. Kurven Schlüsselbezeichner
		m_secret_param_button.EnableWindow(TRUE); // Button einblenden
		m_pub_param_button.EnableWindow(TRUE); // Button einblenden
		m_show_cert_button.EnableWindow(FALSE); // Button ausblenden
		m_export_cert_button.EnableWindow(FALSE); // Button ausblenden
	}
	else 
	{
		// DSA oder RSA Schlüsselbezeichner
		m_secret_param_button.EnableWindow(FALSE); // Button ausblenden
		if ( KeyType.Find(RSA_KEYFILE_IDSTRING ) > -1 )
		{
			m_pub_param_button.EnableWindow(TRUE); //  RSA Button einblenden
		}
		else
		{
			m_pub_param_button.EnableWindow(FALSE); // DSA Button einblenden
		}
		m_show_cert_button.EnableWindow(TRUE); // Button einblenden
		m_export_cert_button.EnableWindow(TRUE); // Button einblenden
	}
	
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein
}

void CDlgKeyAsym::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	int row = phdn->iItem; // int, gibt an in welcher Zeile in IDC_LIST3 das Item angeklickt wurde

	if (row == -1)
	{
		// Der linksklick erfolgte nicht in (gültigen Zeile und erste Spalte)
		/*
		m_secret_param_button.EnableWindow(TRUE); // Button einblenden
		m_pub_param_button.EnableWindow(TRUE); // Button einblenden
		m_show_cert_button.EnableWindow(TRUE); // Button einblenden
		*/
	
		UserKeyId = "";
		UpdateRowSel(-1); // letzte Selektion rückgängig machen
		return;
	}

	UpdateRowSel(row) ;

	*pResult = 0;
}

void CDlgKeyAsym::OnItemclickList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	 // Funktion wird benötigt, damit OnColumnclickList3() funktioniert

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	//phdn->iItem; // int, Specifies the index of item associated with notification.
	//phdn->pitem; // Pointer to an HD_ITEM structure that contains information about the header item associated with the notification message.

	*pResult = 0;
}

void CDlgKeyAsym::OnColumnclickList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	// Diese Funktion wird aufgerufen, falls ein Linksklick auf einen der Spaltenheader erfolgt
	// Zur Zeit ist hier nichts implementiert
	// Vielleicht kommt später eine Sortierfunktion für die Zeilen hinzu.

	/*
	m_secret_param_button.EnableWindow(TRUE); // Button einblenden
	m_pub_param_button.EnableWindow(TRUE); // Button einblenden
	m_show_cert_button.EnableWindow(TRUE); // Button einblenden
	*/

	// pNMListView->iSubItem; // zeigt an welche Spalte angeclickt wurde

	if (pNMListView->iSubItem == 0) sortBy = BY_NAME;
	else if (pNMListView->iSubItem == 1) sortBy = BY_FIRSTNAME;
	else if (pNMListView->iSubItem == 2) sortBy = BY_KEYTYPE;
	else if (pNMListView->iSubItem == 3) sortBy = BY_PERS_KEYID;
	else if (pNMListView->iSubItem == 4) sortBy = BY_CREATTIME;
	else if (pNMListView->iSubItem == 5) sortBy = BY_CREATTIME;

	//CAvailabAsymmKeys asymmKeys;
	//int ret = asymmKeys.GetKeyList( sortedAsymKeyList, sortBy);
	//InitAsymKeyListBox(nKeylistType); // m_listview mit neu sortierten Werten initialisieren
	//m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein

	/* Verfügbare Werte für sortBy für CAvailabAsymmKeys::GetKeyList()
		BY_NAME 
		BY_FIRSTNAME 
		BY_KEYTYPE 
		BY_CREATTIME 
		BY_PERS_KEYID 
	*/
	
	UserKeyId = "";
	UpdateRowSel(-1); // letzte selektion rückgängig machen

	*pResult = 0;
}

void CDlgKeyAsym::OnKeydownList3(NMHDR* pNMHDR, LRESULT* pResult) // In m_listview Taste gedrückt
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	// Manuelle Behandlung, falls der Benutzer in m_listview Tsten drückt

	int keycode = pLVKeyDow->wVKey; // welche Taste wurde gedrückt?
	int selRow;

	if ( (keycode == VK_UP) && (m_lastSelectedRow > 0) )
	{
		// UP-Arrow key pressed
		selRow = GetSpecifRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
		UpdateRowSel(selRow-1);
	}
	else if ( (keycode == VK_DOWN) && (m_lastSelectedRow < m_listview.GetItemCount()-1) )
	{
		// DOWN-Arrow key pressed
		selRow = GetSpecifRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
		UpdateRowSel(selRow+1);
	}
	else if ( (keycode == VK_RIGHT) || (keycode == VK_LEFT) || (keycode == VK_SPACE) )
	{
		// RIGHT- OR LEFT-Arrow or SPACEBAR pressed
		selRow = GetSpecifRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
		UpdateRowSel(selRow); // Select row
	}
	else
	{
		// andere Taste gedrückt
		UserKeyId = "";
		UpdateRowSel(-1); // letzte selektion rückgängig machen
	}
	
	*pResult = 0;
}

int CDlgKeyAsym::GetSpecifRow(UINT mask)
{
// liefert die erste Zeile von m_lisview in der
// das Item in der ersten Spalte den Status mask hat
	int i;
	UINT itemState;

	// Überprüfe welches Item der Maske "mask" entspricht
	for (i=0; i < m_listview.GetItemCount(); i++)
	{
		itemState = m_listview.GetItemState( i, mask);
		if ( (itemState & mask) == mask )
		{
			// das i-te item entspricht mask
			return i; // gefunden
		}
	}

	return -1;
}

int CDlgKeyAsym::FindRow( CString pattern)
{
	int i;
	bool match;

	char *utcStr = NULL;
	char *creatime = NULL;
	char *name = NULL;
	char *firstname = NULL;
	char *keyType = NULL;
	char *keyInfo = NULL;

	CString Text;

	// Zerlege CString pattern in seine Komponenten
	CKeyFile KeyfileName;
	int ret = KeyfileName.ExtractData(pattern, &utcStr, &creatime, &name, &firstname, &keyType, &keyInfo);
	if (ret != 0) return -1;

	for (i=0; i <= m_listview.GetItemCount(); i++)
	{
		// i durchläuft die Zeilen/Rows/Items
		match = true;

		Text = m_listview.GetItemText( i, 0 ); // erste Spalte: vergleiche Namen
		if ( Text != (CString) name ) match = false;

		Text = m_listview.GetItemText( i, 1 ); // 2.te Spalte: vergleiche Vornamen
		if ( Text != (CString) firstname ) match = false;

		Text = m_listview.GetItemText( i, 2 ); // 3.te Spalte: vergleiche Schlüsseltyp
		if ( Text != (CString) keyType ) match = false;

		Text = m_listview.GetItemText( i, 3 ); // 4.te Spalte: vergleiche Schlüsselkennung
		if ( Text != (CString) keyInfo ) match = false;

		Text = m_listview.GetItemText( i, 4 ); // 5.te Spalte: vergleiche Erstellungsdatum
		if ( Text != (CString) creatime ) match = false;

		Text = m_listview.GetItemText( i, 5 ); // 6.te Spalte: vergleiche "UTC-Zeit String"
		if ( Text != (CString) utcStr ) match = false;

		if (match)
		{
			if (utcStr != NULL){ delete utcStr; utcStr = NULL; }
			if (creatime != NULL){ delete creatime;creatime = NULL; }
			if (name != NULL){ delete name;name = NULL; }
			if (firstname != NULL){ delete firstname;firstname = NULL; }
			if (keyType != NULL){ delete keyType;keyType = NULL; }
			if (keyInfo != NULL){ delete keyInfo;keyInfo = NULL; }

			return i; // keyId is in row i
		}
	}
	if (utcStr != NULL){ delete utcStr; utcStr = NULL; }
	if (creatime != NULL){ delete creatime;creatime = NULL; }
	if (name != NULL){ delete name;name = NULL; }
	if (firstname != NULL){ delete firstname;firstname = NULL; }
	if (keyType != NULL){ delete keyType;keyType = NULL; }
	if (keyInfo != NULL){ delete keyInfo;keyInfo = NULL; }

	return -1; // No match found
}

void CDlgKeyAsym::OnCheckDsaKey() 
{
	int status = m_CheckDSA.GetCheck(); // status==1: checked ; status==0: unchecked
	if (status == 0)
	{
		nKeylistType = nKeylistType - (nKeylistType & DSA_KEY); // remove DSA keys
		if (KeyType.Find(DSA_KEYFILE_IDSTRING) > -1)
		{
			// DSA Schlüssel werden gleich aus der Liste in m_listview entfernt
			UserKeyId = "";
		}
	}
	if ((status == 1) && ((nKeylistType & DSA_KEY) == 0))
	{
		// es sind keine DSA Schlüsselbezeichner in sortedAsymKeyList vorhanden,
		// also hinzufügen
		nKeylistType = nKeylistType + DSA_KEY; // add DSA keys
	}
	
	InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

	m_secret_param_button.EnableWindow(TRUE); // Button einblenden
	m_pub_param_button.EnableWindow(TRUE); // Button einblenden
	m_show_cert_button.EnableWindow(TRUE); // Button einblenden

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

void CDlgKeyAsym::OnCheckEcKey() 
{
	int status = m_CheckEC.GetCheck(); // status==1: checked ; status==0: unchecked
	if (status == 0)
	{
		nKeylistType = nKeylistType - (nKeylistType & EC_KEY); // remove EC keys
		if (KeyType.Find(EC_KEYFILE_IDSTRING) > -1)
		{
			// EC Schlüssel werden gleich aus der Liste in m_listview entfernt
			UserKeyId = "";
		}
	}
	if ((status == 1) && ((nKeylistType & EC_KEY) == 0))
	{
		// es sind keine EC Schlüsselbezeichner in sortedAsymKeyList vorhanden,
		// also hinzufügen
		nKeylistType = nKeylistType + EC_KEY; // add EC keys
	}
	
	InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

	m_secret_param_button.EnableWindow(TRUE); // Button einblenden
	m_pub_param_button.EnableWindow(TRUE); // Button einblenden
	m_show_cert_button.EnableWindow(TRUE); // Button einblenden

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

void CDlgKeyAsym::OnCheckRsaKey() 
{
	int status = m_CheckRSA.GetCheck(); // status==1: checked ; status==0: unchecked
	if (status == 0)
	{
		nKeylistType = nKeylistType - (nKeylistType & RSA_KEY); // remove RSA keys
		if (KeyType.Find(RSA_KEYFILE_IDSTRING) > -1)
		{
			// RSA Schlüssel werden gleich aus der Liste in m_listview entfernt
			UserKeyId = "";
		}
	}
	if ((status == 1) && ((nKeylistType & RSA_KEY) == 0))
	{
		// es sind keine RSA Schlüsselbezeichner in sortedAsymKeyList vorhanden,
		// also hinzufügen
		nKeylistType = nKeylistType + RSA_KEY; // add RSA keys
	}
	
	InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

	m_secret_param_button.EnableWindow(TRUE); // Button einblenden
	m_pub_param_button.EnableWindow(TRUE); // Button einblenden
	m_show_cert_button.EnableWindow(TRUE); // Button einblenden

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

bool CDlgKeyAsym::AreThereRSAKeys()
{
    return (KeyType.Find(RSA_KEYFILE_IDSTRING) > -1);
}
