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
// Programmiert von Bartol Filipovic 1999-2000
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält alle Funktionalitäten für
// die Dialogbox zum Signieren von Dateien.
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "secure.h"
#include "af.h"
#include "KeyFileHandling.h"
#include "DlgKeyAsymGeneration.h"
#include "DlgSignature.h"
#include "DialogeMessage.h"

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; // aus CrypTool.cpp

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignature 


CDlgSignature::CDlgSignature(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSignature::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSignature)
	m_edit = _T("");
	m_radio = -1;
	m_SignAlg = -1;
	m_EcPointRepresModus = -1;
	m_ShowDuration = FALSE;
	m_ShowSteps = FALSE;
	//}}AFX_DATA_INIT

	DomParamAc = (EcDomParam_ac_ptr) malloc(sizeof(__DomParamAc_struct)); // Allocate memory. !! DELETE with destruktor!!
	if (DomParamAc == NULL) return; // error. keine Speicherallokation
	DomParamAc->E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
	if (DomParamAc->E == NULL)
	{
		free(DomParamAc);
		return; // error. keine Speicherallokation
	}
	DomParamAc->G = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (DomParamAc->G == NULL)
	{
		free(DomParamAc->E);
		free(DomParamAc);
		return; // error. keine Speicherallokation
	}
	DomParamAc->pubKey = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (DomParamAc->pubKey == NULL)
	{
		free(DomParamAc->G);
		free(DomParamAc->E);
		free(DomParamAc);
		return; // error. keine Speicherallokation
	}
	DomParamAc->pubKey->infinity=1; // pubKey is not defined yet
	inttoln(0, DomParamAc->privKey); // initialize privKey = 0 (not defined yet)

	DomParamPc = (EcDomParam_pc_ptr) malloc(sizeof(__DomParamPc_struct));
	if (DomParamPc == NULL)
	{
		free(DomParamAc->pubKey);
		free(DomParamAc->G);
		free(DomParamAc->E);
		free(DomParamAc);
		return; // error. keine Speicherallokation
	}
	DomParamPc->E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
	if (DomParamPc->E == NULL)
	{
		free(DomParamPc);
		free(DomParamAc->pubKey);
		free(DomParamAc->G);
		free(DomParamAc->E);
		free(DomParamAc);
		return; // error. keine Speicherallokation
	}
	DomParamPc->G = (ecFp_point_pc_t) malloc(sizeof(__PointPc_struct));
	if (DomParamPc->G == NULL)
	{
		free(DomParamPc->E);
		free(DomParamPc);
		free(DomParamAc->pubKey);
		free(DomParamAc->G);
		free(DomParamAc->E);
		free(DomParamAc);
		return; // error. keine Speicherallokation
	}
	DomParamPc->pubKey = (ecFp_point_pc_t) malloc(sizeof(__PointPc_struct));
	if (DomParamPc->pubKey == NULL)
	{
		free(DomParamPc->G);
		free(DomParamPc->E);
		free(DomParamPc);
		free(DomParamAc->pubKey);
		free(DomParamAc->G);
		free(DomParamAc->E);
		free(DomParamAc);
		return; // error. keine Speicherallokation
	}


	use_affine_coord = false;// TRUE:affine coordinates;FALSE:projective coordinate

	UserKeyId = "";
	Name = "";
	Firstname = "";
	KeyType = "";
	KeyInfo = "";
	CreatTime = "";

	m_lastSelectedRow = -1;
}

CDlgSignature::~CDlgSignature()
{
	// Speicher freigeben (falls nicht bereits mit FreeEcMemory() getan)

	if (DomParamAc)
	{
		if (DomParamAc->pubKey) free (DomParamAc->pubKey);
		if (DomParamAc->G) free (DomParamAc->G);
		if (DomParamAc->E) free (DomParamAc->E);
		free (DomParamAc);
	}

	if (DomParamPc)
	{
		if (DomParamPc->pubKey) free(DomParamPc->pubKey);
		if (DomParamPc->G) free(DomParamPc->G);
		if (DomParamPc->E) free(DomParamPc->E);
		free(DomParamPc);
	}
}

void CDlgSignature::FreeEcMemory()
{
	// Speicher freigeben

	free (DomParamAc->pubKey); DomParamAc->pubKey = NULL;
	free (DomParamAc->G); DomParamAc->G = NULL;
	free (DomParamAc->E); DomParamAc->E = NULL;
	free (DomParamAc); DomParamAc = NULL;

	free(DomParamPc->pubKey); DomParamPc->pubKey = NULL;
	free(DomParamPc->G); DomParamPc->G = NULL;
	free(DomParamPc->E); DomParamPc->E = NULL;
	free(DomParamPc); DomParamPc = NULL;
}

void CDlgSignature::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSignature)
	DDX_Control(pDX, IDC_CHECK2, m_CheckSteps);
	DDX_Control(pDX, IDC_RADIO11, m_pcRadio);
	DDX_Control(pDX, IDC_RADIO10, m_acRadio);
	DDX_Control(pDX, IDC_RADIO9, m_RadioECNR);
	DDX_Control(pDX, IDC_RADIO8, m_RadioECDSA);
	DDX_Control(pDX, IDC_RADIO7, m_RadioDSA);
	DDX_Control(pDX, IDC_RADIO6, m_RadioRSA);
	DDX_Control(pDX, IDC_CHECK_RSA_KEYS, m_CheckRSA);
	DDX_Control(pDX, IDC_CHECK_DSA_KEYS, m_CheckDSA);
	DDX_Control(pDX, IDC_CHECK_EC_KEYS, m_CheckEC);
	DDX_Control(pDX, IDC_LIST2, m_listview);
	DDX_Control(pDX, IDC_RADIO1, m_ctrl11);
	DDX_Control(pDX, IDC_RADIO5, m_ctrl15);
	DDX_Control(pDX, IDC_RADIO4, m_ctrl14);
	DDX_Control(pDX, IDC_RADIO3, m_ctrl13);
	DDX_Control(pDX, IDC_RADIO2, m_ctrl12);
	DDX_Control(pDX, IDC_EDIT1, m_ctrl1);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Radio(pDX, IDC_RADIO6, m_SignAlg);
	DDX_Radio(pDX, IDC_RADIO10, m_EcPointRepresModus);
	DDX_Check(pDX, IDC_CHECK1, m_ShowDuration);
	DDX_Check(pDX, IDC_CHECK2, m_ShowSteps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSignature, CDialog)
	//{{AFX_MSG_MAP(CDlgSignature)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList2)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST2, OnItemclickList2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnColumnclickList2)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST2, OnKeydownList2)
	ON_BN_CLICKED(IDC_CHECK_DSA_KEYS, OnCheckDsaKeys)
	ON_BN_CLICKED(IDC_CHECK_EC_KEYS, OnCheckEcKeys)
	ON_BN_CLICKED(IDC_CHECK_RSA_KEYS, OnCheckRsaKeys)
	ON_BN_CLICKED(IDC_RADIO6, OnRadioRSA)
	ON_BN_CLICKED(IDC_RADIO7, OnRadioDSA)
	ON_BN_CLICKED(IDC_RADIO8, OnRadioECDSA)
	ON_BN_CLICKED(IDC_RADIO9, OnRadioECNR)
	ON_BN_CLICKED(IDC_RADIO10, OnRadioAffinCoord)
	ON_BN_CLICKED(IDC_RADIO11, OnRadioProjectCoord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSignature 

BOOL CDlgSignature::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Default RSA mit MD5
	CheckRadioButton (IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
	CheckRadioButton (IDC_RADIO6, IDC_RADIO9, IDC_RADIO6);

	CheckRadioButton (IDC_RADIO10, IDC_RADIO11, IDC_RADIO11); // Projective Coordinates for EC-Points
	use_affine_coord = false;// TRUE:affine coordinates;FALSE:projective coordinate
	
	m_acRadio.EnableWindow(FALSE);
	m_pcRadio.EnableWindow(FALSE);
	m_CheckSteps.EnableWindow(FALSE);

	// m_listview in Report-Mode initialisieren

	int colWidth = 100;  // Spaltenbreite in Pixel

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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSignature::InitAsymKeyListBox(unsigned nLocalKeylistType)
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

int CDlgSignature::FindRow( CString pattern)
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

void CDlgSignature::OnOK() 
{
	UpdateData (TRUE);
	int ret;

	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		Message(IDS_STRING_KEYLIST_ASYM_EMPTY, MB_ICONINFORMATION);
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// Noch kein Schlüsselbezeichner gewählt, obwohl in m_listview welche zur Auswahl stehen
		Message(IDS_STRING_ASYMKEY_MSG_SELECT_PSE,MB_ICONWARNING|MB_OK);
		m_listview.SetFocus();
		return;
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein

	if (m_edit=="")
	{
		// Pin-Code noch nicht eingegeben
		Message(IDS_STRING_ASYMKEY_MSG_ENTER_PIN,MB_ICONWARNING|MB_OK);
		m_ctrl1.SetFocus();
		return;
	}
		
	if ( m_RadioECDSA.GetCheck() || m_RadioECNR.GetCheck() )
	{
		// EC Signaturverfahren gewählt
		if ( KeyType.Find(EC_KEYFILE_IDSTRING ) > -1 )
		{
			// In der Listbox ist ein EC Schlüsselpaar gewählt
			CKeyFile KeyFileHandling;
			ret = KeyFileHandling.GetEcAllParam(UserKeyId, m_edit, DomParamAc);
			if ( ret == -1)
			{
				// falsche PIN-Nummer zum öffnen der PSE benutzt
				Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
				return;
			}
			else if ( ret == -2)
			{
				// sonstiger Fehler beim öffnen der PSE
				Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
				return;
			}
			else if (ret != 0)
			{
				// sonstiger Fehler in CKeyFile::GetEcAllParam()
				return;
			}
			ecFp_DomParam_ac_to_pc (DomParamPc, DomParamAc);
			// Domain Parameter in affine und projective Koordinaten verfügbar
		}
		if ( m_CheckSteps.GetCheck() && m_pcRadio.GetCheck() )
		{
			// Benutzer will Zwischenschritte in projektiven Koordinaten sehen
			// Zwischenschritte werden aber nur in affinen Koordinaten angezeigt
			Message(IDS_STRING_MSG_EC_AFFINE_PROJECTIVE_COORDINATES, MB_ICONEXCLAMATION);
		}
	}
	else
	{
		// RSA oder DSA Signaturverfahren gewählt
		// Überprüfe, ob der PIN-Code für den Zugriff auf die PSE richtig ist, indem
		// die entsprechende PSE Datei geöffnet und wieder geschlossen wird. 

		// Konvertieren der Pin-Nummer von CString nach char *
		LPTSTR string1 = new TCHAR[m_edit.GetLength()+1];
		_tcscpy(string1, m_edit);
		char *PIN=string1;

		// Pfad der PSE des Absenders (Signaturerstellers) in char * konvertieren
		CString help2=(CString)PseVerzeichnis+((CString)"/")+UserKeyId+PSE_FILE_SUFFIX;
		LPTSTR string2 = new TCHAR[help2.GetLength()+1];
		_tcscpy(string2, help2);
		char *PfadNeu=string2;

		// Öffnen der PSE des Absenders (Siganturerstellers) - nur um Gültigkeit der PIN zu überprüfen
		PSE PseHandle;
		PseHandle = theApp.SecudeLib.af_open(PfadNeu, NULL, PIN, NULL);
		if (PseHandle==NULL)
		{
			if (theApp.SecudeLib.LASTERROR==EPIN)
			{
				// falsche PIN-Nummer benutzt
				Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);

				// Freigeben von dynamisch angelegtem Speicher
				delete string1;
				delete string2;
				return;
			}
			// sonstige Fehler beim öffnen der PSE
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);

			// Freigeben von dynamisch angelegtem Speicher
			delete string1;
			delete string2;
			return;
		}
		delete string1;
		delete string2;
		theApp.SecudeLib.af_close (PseHandle);

		FreeEcMemory(); // ellipt. Kurven werden nicht benutzt
	}
	CDialog::OnOK();
}


void CDlgSignature::EnableAllRadioButtons()
{
	// alle Hashfunktionen einblenden
	m_ctrl11.EnableWindow(TRUE); // MD2
	m_ctrl12.EnableWindow(TRUE); // MD5
	m_ctrl13.EnableWindow(TRUE); // RIPEMD-160
	m_ctrl14.EnableWindow(TRUE); // SHA
	m_ctrl15.EnableWindow(TRUE); // SHA-1

	// alle Signaturverfahren einblenden
	m_RadioRSA.EnableWindow(TRUE); // RSA
	m_RadioDSA.EnableWindow(TRUE); // DSA
	m_RadioECDSA.EnableWindow(TRUE); // ECSP-DSA
	m_RadioECNR.EnableWindow(TRUE); //ECSP-NR

	if ( (m_RadioECDSA.GetCheck() == 0) && (m_RadioECNR.GetCheck() == 0) )
	{
		// Kein EC-Verfahren gewählt
		m_acRadio.EnableWindow(FALSE);
		m_pcRadio.EnableWindow(FALSE);
		m_CheckSteps.EnableWindow(FALSE);
	}
	else
	{
		m_acRadio.EnableWindow(TRUE);
		m_pcRadio.EnableWindow(TRUE);
		m_CheckSteps.EnableWindow(TRUE);
	}
}


void CDlgSignature::UpdateRowSel(int row) 
{
	int i;
	CString Text;

	UpdateData(TRUE);

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
		// UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
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
		// Spalte mit Index 4 wird nicht genutzt
		else if (i==5) CreatTime = Text; // CreatTime: Time in seconds since UTC 1/1/70

		if (Text.GetLength() == 0)
		{
			continue; // Falls in der aktuellen Spalte kein Text vorhanden ist, gehe zur nächsten Spalte
		}
		m_listview.SetItem(row, i, LVIF_TEXT | LVIF_STATE, Text, 0, LVIS_SELECTED, LVIS_SELECTED, row);
		m_listview.SetItemText( row, i, Text );
	}

	UserKeyId = "";
	CKeyFile KeyHandling;
	UserKeyId = KeyHandling.CreateFilename2(Name, Firstname, KeyType, CreatTime, KeyInfo);

	if (KeyType.Find(EC_KEYFILE_IDSTRING ) > -1)
	{
		// der gewählte Schlüsselbezeichner gehört zu einem Elliptische Kurven Schlüsselpaar
		
		if ( (!m_RadioECDSA.GetCheck()) && (!m_RadioECNR.GetCheck()) )
		{
			// kein ECDSA-RadioButton oder ECNR-RadioButton gecheckt
			// Auswahl auf ECDSA setzen (ECDSA ist default Einstellung für EC Schlüssel) 
			CheckRadioButton (IDC_RADIO6, IDC_RADIO9, IDC_RADIO8);
		}
		if ((m_radio!=2) && (m_radio!=4))
		{
			CheckRadioButton (IDC_RADIO1, IDC_RADIO5, IDC_RADIO5); // Hashfunktion auf SHA_1 (Standard) setzen
		}
		// alle Hashfunktionen ausser RIPEMD-160 und SHA-1 ausblenden
		m_ctrl11.EnableWindow(FALSE); // MD2
		m_ctrl12.EnableWindow(FALSE); // MD5
		m_ctrl13.EnableWindow(TRUE); // RIPEMD-160
		m_ctrl14.EnableWindow(FALSE); // SHA
		m_ctrl15.EnableWindow(TRUE); // SHA-1
		
		m_RadioRSA.EnableWindow(FALSE); // RSA ausblenden
		m_RadioDSA.EnableWindow(FALSE); // DSA ausblenden
		m_RadioECDSA.EnableWindow(TRUE); // Signatur nach ECDSA Auswahl ermöglichen
		m_RadioECNR.EnableWindow(TRUE); // Signatur nach Nyberg-Rueppel Auswahl ermöglichen

		m_acRadio.EnableWindow(TRUE);
		m_pcRadio.EnableWindow(TRUE);
		m_CheckSteps.EnableWindow(TRUE);
	}
	else
	{
		// RSA oder DSA Schlüsselpaar gewählt

		CKeyFile KeyHandling;
		CString caDB_keyid_name = KeyHandling.CreateDistName(Name, Firstname, CreatTime);
		// caDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben

		LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
		_tcscpy(string3, caDB_keyid_name);
		char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 

		//Öffnen der CA-PSE
		PSE PseHandle;
		PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			return;
		}
		
		//Besorgen des Zertifikates der Adressaten
		SET_OF_IssuedCertificate *Liste;
		Liste=theApp.SecudeLib.af_cadb_get_user (PseHandle, string4);
		if (Liste==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,MB_ICONSTOP,theApp.SecudeLib.LASTTEXT);
			theApp.SecudeLib.af_close (PseHandle);
			return;
		}

		Certificate *Zert;
		OctetString *SNummer;
		SNummer=Liste->element->serial;
		Zert=theApp.SecudeLib.af_cadb_get_Certificate (PseHandle, SNummer);
		if (Zert==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			theApp.SecudeLib.af_close (PseHandle);
			return;
		}

		// Fall, daß in der gewählten PSE ein DSA-Schlüssel liegt
		// Der Algorithm Identifier von dsa-aid hat 6 Komponenten

		if ((Zert->tbs->subjectPK->subjectAI->objid->oid_nelem)==6)
		{
			if ( !m_RadioDSA.GetCheck() )
			{
				// kein DSA-RadioButton gewählt, also jetzt anwählen	
				CheckRadioButton (IDC_RADIO6, IDC_RADIO9, IDC_RADIO7); // Auswahl auf DSA setzen
			}
			if ((m_radio!=3) && (m_radio!=4))
			{
				// kein SHA oder SHA-1 Button gewähhlt
				CheckRadioButton (IDC_RADIO1, IDC_RADIO5, IDC_RADIO5); // Hashfunktion auf SHA-1 (Standard) setzen
			}
			// Buttons ein- und ausblenden
			m_ctrl11.EnableWindow(FALSE); // MD2 Button ausblenden
			m_ctrl12.EnableWindow(FALSE); // MD5 Button ausblenden
			m_ctrl13.EnableWindow(FALSE); // RIPEMD-160 Button ausblenden
			m_ctrl14.EnableWindow(TRUE); // SHA Button einblenden
			m_ctrl15.EnableWindow(TRUE); // SHA-1 Button einblenden

			m_RadioDSA.EnableWindow(TRUE); // DSA Button einblenden
			m_RadioRSA.EnableWindow(FALSE); // RSA Button ausblenden
			m_RadioECDSA.EnableWindow(FALSE); // ECSP-DSA Button ausblenden
			m_RadioECNR.EnableWindow(FALSE); // ECSP-NR Button ausblenden
			
			m_acRadio.EnableWindow(FALSE);
			m_pcRadio.EnableWindow(FALSE);
			m_CheckSteps.EnableWindow(FALSE);
		}
		
		// Fall, daß in der gewählten PSE ein RSA-Schlüssel liegt
		// Der Algorithm Identifier von rsa-aid hat 5 Komponenten

		else if ((Zert->tbs->subjectPK->subjectAI->objid->oid_nelem)==5)
		{
			if ( !m_RadioRSA.GetCheck() )
			{
				// bisher nicht RSA Radio gewählt, also
				// Auswahl auf RSA Radio setzen
				CheckRadioButton (IDC_RADIO6, IDC_RADIO9, IDC_RADIO6);
			}
			// Buttons ein- und ausblenden
			m_ctrl11.EnableWindow(TRUE); // MD2 Button 
			m_ctrl12.EnableWindow(TRUE); // MD5 Button 
			m_ctrl13.EnableWindow(TRUE); // RIPEMD-160 Button 
			m_ctrl14.EnableWindow(TRUE); // SHA Button 
			m_ctrl15.EnableWindow(TRUE); // SHA-1 Button

			m_RadioRSA.EnableWindow(TRUE); // RSA Button 
			m_RadioDSA.EnableWindow(FALSE); // DSA Button
			m_RadioECDSA.EnableWindow(FALSE); // ECSP-DSA Button 
			m_RadioECNR.EnableWindow(FALSE); // ECSP-NR Button 
			
			m_acRadio.EnableWindow(FALSE);
			m_pcRadio.EnableWindow(FALSE);
			m_CheckSteps.EnableWindow(FALSE);
		}
		theApp.SecudeLib.af_close (PseHandle);
		delete string3; // Freigeben des allokierten Speichers 
	}
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein
}

void CDlgSignature::OnClickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	int row = phdn->iItem; // row gibt an in welcher Zeile in m_listview das Item angeklickt wurde

	if (row == -1)
	{
		// Der linksklick erfolgte nicht in (gültige Zeile und erste Spalte)

		UserKeyId = "";
		UpdateRowSel(-1); // letzte Selektion rückgängig machen
		EnableAllRadioButtons();
		return;
	}

	UpdateRowSel(row) ;

	*pResult = 0;
}

void CDlgSignature::OnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 // Funktion wird benötigt, damit OnColumnclickList2() funktioniert

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	//phdn->iItem; // int, Specifies the index of item associated with notification.
	//phdn->pitem; // Pointer to an HD_ITEM structure that contains information about the header item associated with the notification message.
	
	*pResult = 0;
}

void CDlgSignature::OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	// Diese Funktion wird aufgerufen, falls ein Linksklick auf einen der Spaltenheader erfolgt
	// Zur Zeit ist hier nichts implementiert
	// Vielleicht kommt später eine Sortierfunktion für die Zeilen hinzu.

	// EnableAllRadioButtons();

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

	//UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
	//m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein

	/* Verfügbare Flags für CAvailabAsymmKeys::GetKeyList()
		BY_NAME 
		BY_FIRSTNAME 
		BY_KEYTYPE 
		BY_CREATTIME 
		BY_PERS_KEYID 
	*/

	UserKeyId = "";
	UpdateRowSel(-1); // letzte Selektion rückgängig machen
	EnableAllRadioButtons();

	*pResult = 0;
}

int CDlgSignature::GetSpecifRow(UINT mask)
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

void CDlgSignature::OnKeydownList2(NMHDR* pNMHDR, LRESULT* pResult) 
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
		EnableAllRadioButtons();
	}

	*pResult = 0;
}


void CDlgSignature::OnCheckDsaKeys() 
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

	//EnableAllRadioButtons(); // alle Radio Buttons "freischalten"

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

void CDlgSignature::OnCheckEcKeys() 
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

	//EnableAllRadioButtons(); // alle Radio Buttons "freischalten"

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

void CDlgSignature::OnCheckRsaKeys() 
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

	//EnableAllRadioButtons(); // alle Radio Buttons "freischalten"

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

void CDlgSignature::OnRadioRSA() 
{
	// RSA gewählt
	UpdateData(TRUE);
	
	// alle Hashfunktionen einblenden
	m_ctrl11.EnableWindow(TRUE);
	m_ctrl12.EnableWindow(TRUE);
	m_ctrl13.EnableWindow(TRUE);
	m_ctrl14.EnableWindow(TRUE);
	m_ctrl15.EnableWindow(TRUE);

	m_acRadio.EnableWindow(FALSE);
	m_pcRadio.EnableWindow(FALSE);
	m_CheckSteps.EnableWindow(FALSE);

	if ( nKeylistType != RSA_KEY )
	{
		// Es werden nicht nur RSA Schlüssel angezeigt, dies wird geändert:

		// Nur RSA Schlüsseltypen anzeigen
		m_CheckRSA.SetCheck(1); // Button checked
		m_CheckDSA.SetCheck(0); // Button unchecked
		m_CheckEC.SetCheck(0); // Button unchecked

		nKeylistType = RSA_KEY; // add RSA keys only
		
		InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

		UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
	}
}

void CDlgSignature::OnRadioDSA() 
{
	// DSA gewählt
	UpdateData(TRUE);

	// alle Hashfunktionen einblenden
	m_ctrl11.EnableWindow(TRUE);
	m_ctrl12.EnableWindow(TRUE);
	m_ctrl13.EnableWindow(TRUE);
	m_ctrl14.EnableWindow(TRUE);
	m_ctrl15.EnableWindow(TRUE);

	if ((m_radio!=3) && (m_radio!=4)){// Falls weder SHA noch SHA-1 gewählt
		CheckRadioButton (IDC_RADIO1, IDC_RADIO5, IDC_RADIO5); // SHA-1 wählen
	}

	// Nur SHA und SHA-1 einblenden
	m_ctrl11.EnableWindow(FALSE);
	m_ctrl12.EnableWindow(FALSE);
	m_ctrl13.EnableWindow(FALSE);
	m_ctrl14.EnableWindow(TRUE);
	m_ctrl15.EnableWindow(TRUE);

	m_acRadio.EnableWindow(FALSE);
	m_pcRadio.EnableWindow(FALSE);
	m_CheckSteps.EnableWindow(FALSE);

	if ( nKeylistType != DSA_KEY )
	{
		// Es werden nicht nur DSA Schlüssel angezeigt, dies wird geändert:

		// nur DSA Schlüsseltypen anzeigen
		m_CheckRSA.SetCheck(0); // Button unchecked
		m_CheckDSA.SetCheck(1); // Button checked
		m_CheckEC.SetCheck(0); // Button unchecked

		nKeylistType = DSA_KEY; // add DSA keys only
		
		InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

		UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
	}
}

void CDlgSignature::OnRadioECDSA() 
{
	// ECDSA gewählt
	UpdateData(TRUE);
	
	// alle Hashfunktionen einblenden
	m_ctrl11.EnableWindow(TRUE);
	m_ctrl12.EnableWindow(TRUE);
	m_ctrl13.EnableWindow(TRUE);
	m_ctrl14.EnableWindow(TRUE);
	m_ctrl15.EnableWindow(TRUE);

	if ((m_radio!=2) && (m_radio!=4)){// Falls weder RIPEMD-160 noch SHA-1 gewählt
		CheckRadioButton (IDC_RADIO1, IDC_RADIO5, IDC_RADIO5); // SHA-1 wählen
	}
	// Nur RIPEMD-160 und SHA-1 einblenden
	m_ctrl11.EnableWindow(FALSE);
	m_ctrl12.EnableWindow(FALSE);
	m_ctrl13.EnableWindow(TRUE);
	m_ctrl14.EnableWindow(FALSE);
	m_ctrl15.EnableWindow(TRUE);
			
	m_acRadio.EnableWindow(TRUE);
	m_pcRadio.EnableWindow(TRUE);
	m_CheckSteps.EnableWindow(TRUE);
	
	if ( nKeylistType != EC_KEY )
	{
		// Es werden nicht nur EC Schlüssel angezeigt, dies wird geändert:

		// Nur EC Schlüsseltypen anzeigen
		m_CheckRSA.SetCheck(0); // Button unchecked
		m_CheckDSA.SetCheck(0); // Button unchecked
		m_CheckEC.SetCheck(1); // Button checked

		nKeylistType = EC_KEY; // add EC keys only
		
		InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

		UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
	}
}

void CDlgSignature::OnRadioECNR() 
{
	// Nyberg-Rueppel gewählt
	UpdateData(TRUE);

	// alle Hashfunktionen einblenden
	m_ctrl11.EnableWindow(TRUE);
	m_ctrl12.EnableWindow(TRUE);
	m_ctrl13.EnableWindow(TRUE);
	m_ctrl14.EnableWindow(TRUE);
	m_ctrl15.EnableWindow(TRUE);

	if ((m_radio!=2) && (m_radio!=4)){// Falls weder RIPEMD-160 noch SHA-1 gewählt
		CheckRadioButton (IDC_RADIO1, IDC_RADIO5, IDC_RADIO5); // SHA-1 wählen
	}
	// Nur RIPEMD-160 und SHA-1 einblenden
	m_ctrl11.EnableWindow(FALSE);
	m_ctrl12.EnableWindow(FALSE);
	m_ctrl13.EnableWindow(TRUE);
	m_ctrl14.EnableWindow(FALSE);
	m_ctrl15.EnableWindow(TRUE);

	m_acRadio.EnableWindow(TRUE);
	m_pcRadio.EnableWindow(TRUE);
	m_CheckSteps.EnableWindow(TRUE);

	if ( nKeylistType != EC_KEY )
	{
		// Es werden nicht nur EC Schlüssel angezeigt, dies wird geändert:

		// Nur EC Schlüsseltypen anzeigen
		m_CheckRSA.SetCheck(0); // Button unchecked
		m_CheckDSA.SetCheck(0); // Button unchecked
		m_CheckEC.SetCheck(1); // Button checked

		nKeylistType = EC_KEY; // add EC keys only
		
		InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

		UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
	}
}


void CDlgSignature::OnRadioAffinCoord() 
{
	UpdateData(TRUE);
	use_affine_coord = true;// TRUE:affine coordinates;FALSE:projective coordinate
}

void CDlgSignature::OnRadioProjectCoord() 
{
	UpdateData(TRUE);
	use_affine_coord = false;// TRUE:affine coordinates;FALSE:projective coordinate	
}
