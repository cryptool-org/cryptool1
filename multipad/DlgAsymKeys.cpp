//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgAsymKeys.cpp: Implementierungsdatei
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security

#include "stdafx.h"
#include "multipad.h"
#include "DlgAsymKeys.h"
#include "KeyFileHandling.h"
#include "DlgAsymKeyCreat.h"
#include "PinCodeDialog.h"
#include "DlgShowPubEcKeys.h"
#include "DlgShowPrivEcKeys.h"
#include "DialogCert.h"

#include "s_ecFp.h" // elliptic curve stuff
#include "s_prng.h" // big random integers


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globale Variablen
extern char *PseVerzeichnis, *CaPseDatei, *CaPseVerzeichnis; // siehe multipda.cpp

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAsymKeys 


CDlgAsymKeys::CDlgAsymKeys(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAsymKeys::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAsymKeys)
	//}}AFX_DATA_INIT

	UserKeyId = "";
	Name = "";
	Firstname = "";
	KeyType = "";
	KeyInfo = "";
	CreatTimeUTC = "";
	CreatTime = "";

	m_lastSelectedRow = -1; //  Änderung in Member-Funktion CDlgAsymKeys::OnClickList3()
}

/*
CDlgAsymKeys::~CDlgAsymKeys()
{
}
*/

void CDlgAsymKeys::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAsymKeys)
	DDX_Control(pDX, IDC_CHECK3, m_CheckEC);
	DDX_Control(pDX, IDC_CHECK2, m_CheckDSA);
	DDX_Control(pDX, IDC_CHECK1, m_CheckRSA);
	DDX_Control(pDX, IDC_BUTTON4, m_show_cert_button);
	DDX_Control(pDX, IDC_LIST3, m_listview);
	DDX_Control(pDX, IDC_BUTTON2, m_secret_param_button);
	DDX_Control(pDX, IDC_BUTTON1, m_pub_param_button);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAsymKeys, CDialog)
	//{{AFX_MSG_MAP(CDlgAsymKeys)
	ON_BN_CLICKED(IDC_BUTTON1, OnShowPubParamButton)
	ON_BN_CLICKED(IDC_BUTTON2, OnShowAllParamButton)
	ON_BN_CLICKED(IDC_BUTTON3, OnDeleteEntryButton)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonShowCert)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST3, OnColumnclickList3)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST3, OnItemclickList3)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST3, OnKeydownList3)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckRsaKey)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckDsaKey)
	ON_BN_CLICKED(IDC_CHECK3, OnCheckEcKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgAsymKeys 


BOOL CDlgAsymKeys::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// m_listview in Report-Mode initialisieren

	int colWidth = 100;  // Spaltenbreite in Pixel

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
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgAsymKeys::OnShowPubParamButton() 
{
	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_EMPTY,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
		return; // no selection
	}
	else if (UserKeyId.GetLength() < 1)
	{
		// there is no selected string
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_SELECT,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
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
		LPTSTR string3 = new TCHAR[PubDataFile.GetLength()+1];
		_tcscpy(string3, PubDataFile);		
		char *toc_file = string3;

		LoadString(AfxGetInstanceHandle(),IDS_STRING_EC_ERROR_LOADING_KEYFILE,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, toc_file);
		AfxMessageBox(pc_str1,MB_ICONINFORMATION, 0 );
		delete string3;
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

	CDlgShowPubEcKeys PubParamDlg(UserKeyId, Name, Firstname, CreatTime, KeyType, curveParameter);
	if (PubParamDlg.DoModal()==IDCANCEL) CDialog::OnCancel();

	free (curveParameter->pubKey);
	free (curveParameter->G);
	free (curveParameter->E);
	free (curveParameter);
}

void CDlgAsymKeys::OnShowAllParamButton() 
{
	CString passwd;

	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_EMPTY,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// there is no selected string
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_SELECT,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
		return; // no selection
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

	// passwd erfragen
	CPinCodeDialog PinCodeDialog(1, UserKeyId);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIVKEY_WRONG_PIN,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str, MB_ICONEXCLAMATION, 0);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_OPEN_PSE,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
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

	CDlgShowPrivEcKeys PrivParamDlg(UserKeyId, Name, Firstname, CreatTime, KeyType, curveParameter);
	if (PrivParamDlg.DoModal()==IDCANCEL) CDialog::OnCancel();

	free (curveParameter->pubKey);
	free (curveParameter->G);
	free (curveParameter->E);
	free (curveParameter);
}

void CDlgAsymKeys::OnDeleteEntryButton() 
{
	CKeyFile DataFile;
	int ret;
	CString passwd;
	
	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_EMPTY,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// there is no selected string
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_SELECT,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
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
	CPinCodeDialog PinCodeDialog(0, UserKeyId);
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
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIVKEY_WRONG_PIN,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str, MB_ICONEXCLAMATION, 0);
			return;
			//
			//LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_DATA_NOT_CHANGED,pc_str,STR_LAENGE_STRING_TABLE);
			//AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
			//return; // error: couldn't open inputfile
			//

		}
		else if ( ret != 0)
		{
			// sonstiger Fehler beim öffnen der PSE
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_OPEN_PSE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
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
			LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIVKEY_WRONG_PIN,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str, MB_ICONEXCLAMATION, 0);
			return;

		}
		else if ( ret != 0)
		{
			// sonstiger Fehler beim öffnen der PSE
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_OPEN_PSE,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			return;
		}
	}

	InitAsymKeyListBox(nKeylistType); // m_listview neu mit Werten initialisieren
	UserKeyId = ""; // gelöscht!
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein
}


void CDlgAsymKeys::OnButtonShowCert() 
{
	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_EMPTY,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// there is no selected string
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_SELECT,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
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
		char *Fehler=theApp.SecudeLib.LASTTEXT;
		CString Fehler2=Fehler;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE,pc_str,STR_LAENGE_STRING_TABLE);
		CString Fehler3=(CString)pc_str+(CString)Fehler2;
		AfxMessageBox (Fehler3,MB_ICONSTOP);
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
	CString Zertifikat=theApp.SecudeLib.aux_sprint_Certificate(PseHandle,NULL,Zert2);
	{	CDialogCert DCert(Zertifikat, NULL);
		if (DCert.DoModal()==IDCANCEL) CDialog::OnCancel();
	}
	
	theApp.SecudeLib.af_close(PseHandle);

	// Freigeben von dynamisch angelegtem Speicher
	delete string1;
	
	return;
}


void CDlgAsymKeys::InitAsymKeyListBox(unsigned nLocalKeylistType)
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


void CDlgAsymKeys::UpdateRowSel(int row) 
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
		return;
	}

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
	}
	else
	{
		// DSA oder RSA Schlüsselbezeichner
		m_secret_param_button.EnableWindow(FALSE); // Button ausblenden
		m_pub_param_button.EnableWindow(FALSE); // Button ausblenden
		m_show_cert_button.EnableWindow(TRUE); // Button einblenden
	}
	
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein
}

void CDlgAsymKeys::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgAsymKeys::OnItemclickList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	 // Funktion wird benötigt, damit OnColumnclickList3() funktioniert

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	//phdn->iItem; // int, Specifies the index of item associated with notification.
	//phdn->pitem; // Pointer to an HD_ITEM structure that contains information about the header item associated with the notification message.

	*pResult = 0;
}

void CDlgAsymKeys::OnColumnclickList3(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgAsymKeys::OnKeydownList3(NMHDR* pNMHDR, LRESULT* pResult) // In m_listview Taste gedrückt
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

int CDlgAsymKeys::GetSpecifRow(UINT mask)
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

int CDlgAsymKeys::FindRow( CString pattern)
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

void CDlgAsymKeys::OnCheckDsaKey() 
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

void CDlgAsymKeys::OnCheckEcKey() 
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

void CDlgAsymKeys::OnCheckRsaKey() 
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
