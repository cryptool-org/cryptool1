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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgSignVerif.cpp: Implementierungsdatei
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgVerifySignature.h"
#include "DialogeMessage.h"

//#include "secure.h"
//#include "af.h"
#include "KeyFileHandling.h"
#include "DlgKeyAsymGeneration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Globale Variablen
extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; // aus CrypTool.cpp

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgVerifySignature 


CDlgVerifySignature::CDlgVerifySignature(char* sig_id, char* hash_id, CString sig_key, CWnd* pParent /*= NULL*/)
	: CDialog(CDlgVerifySignature::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVerifySignature)
	m_SigVerfahren = -1;
	m_HashFunktion = -1;
	m_EditSigAlg = _T("");
	m_EditHashAlg = _T("");
	m_sel_coord = -1;
	m_ShowDuration = TRUE;
	m_ShowSteps = FALSE;
	//}}AFX_DATA_INIT

	signKey = sig_key; // es muss eine Datei im char *PseVerzeichnis existieren,
	                   // die den Namen signKey+PSE_FILE_SUFFIX hat - sonst ist eine Überprüfung
	                   // der Signatur nicht möglich!

	sigAlg  = sig_id; // Nur bei EC Signaturen (ECSP-DSA und ECSP-NR) relevant, da damit
	                  // die entsprechenden Radio Buttons eingestellt werden.
	                  // Dieser Parameter darf auch in CDlgVerifySignature auch "falsch" sein,
	                  // es werden dann default Einstellungen vorgenommen.
	                  // Für ECSP-DSA und ECSP-NR kann man über die Radio Buttons das
	                  // Sign/Hash-Verfahren beliebig einstellen - man erhält dann bei
	                  // der Verifikation in verify() unter Umständen eine Meldung,
	                  // dass die Signatur falsch ist.

	hashAlg = hash_id;// Nur bei EC Signaturen (ECSP-DSA und ECSP-NR) relevant, da damit
	                  // die entsprechenden Radio Buttons eingestellt werden.
	                  // Dieser Parameter darf auch in CDlgVerifySignature auch "falsch" sein,
	                  // es werden dann default Einstellungen vorgenommen.
	                  // Für ECSP-DSA und ECSP-NR kann man über die Radio Buttons das
	                  // Sign/Hash-Verfahren beliebig einstellen - man erhält dann bei
	                  // der Verifikation in verify() unter Umständen eine Meldung,
	                  // dass die Signatur falsch ist.
	UserKeyId = "";
	Name = "";
	Firstname = "";
	KeyType = "";
	KeyInfo = "";
	CreatTime = "";

	m_lastSelectedRow = -1;

	use_affine_coord = false;// TRUE:affine coordinates;FALSE:projective coordinate

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
}

CDlgVerifySignature::~CDlgVerifySignature()
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

void CDlgVerifySignature::FreeEcMemory()
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


void CDlgVerifySignature::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVerifySignature)
	DDX_Control(pDX, IDC_CHECK2, m_CheckSteps);
	DDX_Control(pDX, IDC_RADIO2, m_pcRadioButton);
	DDX_Control(pDX, IDC_RADIO1, m_acRadioButton);
	DDX_Control(pDX, IDC_EDIT2, m_CtrlSigAlg);
	DDX_Control(pDX, IDC_EDIT1, m_CtrlHashAlg);
	DDX_Control(pDX, IDC_CHECK_RSA_KEYS, m_CheckRSA);
	DDX_Control(pDX, IDC_CHECK_EC_KEYS, m_CheckEC);
	DDX_Control(pDX, IDC_CHECK_DSA_KEYS, m_CheckDSA);
	DDX_Control(pDX, IDC_LIST2, m_listview);
	DDX_Control(pDX, IDC_RADIO6, m_nrRadioButton);
	DDX_Control(pDX, IDC_RADIO5, m_ecdsaRadioButton);
	DDX_Control(pDX, IDC_RADIO7, m_sha1RadioButton);
	DDX_Control(pDX, IDC_RADIO8, m_ripemdRadioButton);
	DDX_Radio(pDX, IDC_RADIO5, m_SigVerfahren);
	DDX_Radio(pDX, IDC_RADIO7, m_HashFunktion);
	DDX_Text(pDX, IDC_EDIT2, m_EditSigAlg);
	DDX_Text(pDX, IDC_EDIT1, m_EditHashAlg);
	DDX_Radio(pDX, IDC_RADIO1, m_sel_coord);
	DDX_Check(pDX, IDC_CHECK1, m_ShowDuration);
	DDX_Check(pDX, IDC_CHECK2, m_ShowSteps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVerifySignature, CDialog)
	//{{AFX_MSG_MAP(CDlgVerifySignature)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList2)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST2, OnItemclickList2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnColumnclickList2)
	ON_BN_CLICKED(IDC_CHECK_DSA_KEYS, OnCheckDsaKey)
	ON_BN_CLICKED(IDC_CHECK_EC_KEYS, OnCheckEcKey)
	ON_BN_CLICKED(IDC_CHECK_RSA_KEYS, OnCheckRsaKey)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST2, OnKeydownList2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonSearchKey)
	ON_BN_CLICKED(IDC_RADIO5, OnRadioECDSA)
	ON_BN_CLICKED(IDC_RADIO6, OnRadioECNR)
	ON_BN_CLICKED(IDC_RADIO7, OnRadioSHA1)
	ON_BN_CLICKED(IDC_RADIO8, OnRadioRIPEMD)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioAffineCoord)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioProjectCoord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgVerifySignature 


BOOL CDlgVerifySignature::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LoadString(AfxGetInstanceHandle(),IDS_STRING_UNKNOWN,pc_str,STR_LAENGE_STRING_TABLE);
	// pc_str = "unbekannt";
	
	// Überprüfe welcher Signaturalgorithmus angeblich benutzt wurde
	if (strcmp(sigAlg, "ECSP-NR") == 0)
	{
		CheckRadioButton (IDC_RADIO5, IDC_RADIO6, IDC_RADIO6); UpdateData(TRUE);
		// CheckRadioButton (IDC_RADIO1, IDC_RADIO2, IDC_RADIO2); UpdateData(TRUE);
		m_EditSigAlg = "ECSP-NR"; UpdateData(FALSE);
	}
	else if (strcmp(sigAlg, "ECSP-DSA") == 0)
	{
		CheckRadioButton (IDC_RADIO5, IDC_RADIO6, IDC_RADIO5); UpdateData(TRUE);
		m_EditSigAlg = "ECSP-DSA"; UpdateData(FALSE);
	}
	else if (strcmp(sigAlg, "DSA") == 0)
	{
		m_EditSigAlg = "DSA"; UpdateData(FALSE);
	}
	else if (strcmp(sigAlg, "RSA") == 0)
	{
		m_EditSigAlg = "RSA"; UpdateData(FALSE);
	}
	else
	{
		// unknown signature algorithm
		m_EditSigAlg = (CString) sigAlg + ((CString)" (") + ((CString)pc_str) + ((CString)")"); UpdateData(FALSE);
		m_CtrlSigAlg.EnableWindow(FALSE);
		m_SigVerfahren = -1;
	}

	// Überprüfe welcher Hashalgorithmus angeblich benutzt wurde
	if (strcmp(hashAlg, "SHA-1") == 0)
	{
		CheckRadioButton (IDC_RADIO7, IDC_RADIO8, IDC_RADIO7); UpdateData(TRUE);
		// CheckRadioButton (IDC_RADIO1, IDC_RADIO2, IDC_RADIO2); UpdateData(TRUE);
		m_EditHashAlg = "SHA-1"; UpdateData(FALSE);
	}
	else if (strcmp(hashAlg, "RIPEMD-160") == 0)
	{
		CheckRadioButton (IDC_RADIO7, IDC_RADIO8, IDC_RADIO8); UpdateData(TRUE);
		// CheckRadioButton (IDC_RADIO1, IDC_RADIO2, IDC_RADIO2); UpdateData(TRUE);
		m_EditHashAlg = "RIPEMD-160"; UpdateData(FALSE);
	}
	else if (strcmp(hashAlg, "MD2") == 0)
	{
		m_EditHashAlg = "MD2"; UpdateData(FALSE);
	}
	else if (strcmp(hashAlg, "MD5") == 0)
	{
		m_EditHashAlg = "MD5"; UpdateData(FALSE);
	}
	else if (strcmp(hashAlg, "SHA") == 0)
	{
		m_EditHashAlg = "SHA"; UpdateData(FALSE);
	}
	else
	{
		// unknown hash-algorithm
		m_EditHashAlg = (CString) hashAlg + ((CString)" (") + ((CString)pc_str) + ((CString)")"); UpdateData(FALSE);
		m_CtrlHashAlg.EnableWindow(FALSE);
		m_HashFunktion = -1;
	}

	CheckRadioButton (IDC_RADIO1, IDC_RADIO2, IDC_RADIO2); UpdateData(TRUE); // project. Coordinates
	use_affine_coord = false;// TRUE:affine coordinates;FALSE:projective coordinate

	// m_listview initialiesieren

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

	int keyrow = FindRow(signKey);// Suche nach der Zeile mit dem Eintrag signKey

/*

Falls signKey nicht gefunden werden kann wird die AfxMessageBox() angezeigt,
bevor CDlgVerifySignature initialisiert ist - das ist etwas verwirrend. Daher
wird keine entsprechende Meldung ausgegeben - erst wenn der Benutzer den Schlüssel
durch anklicken des entsprechenden Buttons suchen lässt kommt eine Info, das es den 
gesuchten Schlüsselbezeichner nicht gibt. Siehe CDlgVerifySignature::OnButtonSearchKey()

	if (keyrow == -1)
	{
		// Info: Schlüsselbezeichner nicht in Liste vorhanden
		Message(IDS_STRING_MSG_KEY_IDENTIFIER_NOT_FOUND,MB_ICONEXCLAMATION | MB_OK, signKey);
	}

*/

	UpdateRowSel( keyrow ); // Zeile die signKey enthält unterlegen (falls vorhanden)

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

int CDlgVerifySignature::FindRow( CString pattern)
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

			return i; // signKey is in row i
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


void CDlgVerifySignature::InitAsymKeyListBox(unsigned nLocalKeylistType)
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

void CDlgVerifySignature::UpdateRowSel(int row) 
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
		// Daten aus Spalte mit Index 4 werden hier nicht gebraucht
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
		m_ripemdRadioButton.EnableWindow(TRUE);
		m_sha1RadioButton.EnableWindow(TRUE);
		m_nrRadioButton.EnableWindow(TRUE);
		m_ecdsaRadioButton.EnableWindow(TRUE);
		m_acRadioButton.EnableWindow(TRUE);
		m_pcRadioButton.EnableWindow(TRUE);
		m_CheckSteps.EnableWindow(TRUE);
	}
	else
	{
		// RSA or DSA Signature
		m_ripemdRadioButton.EnableWindow(FALSE);
		m_sha1RadioButton.EnableWindow(FALSE);
		m_nrRadioButton.EnableWindow(FALSE);
		m_ecdsaRadioButton.EnableWindow(FALSE);
		m_acRadioButton.EnableWindow(FALSE);
		m_pcRadioButton.EnableWindow(FALSE);
		if ( KeyType.Find(RSA_KEYFILE_IDSTRING ) > -1)
		{
			m_CheckSteps.EnableWindow(TRUE);
		}
		else
		{
			m_CheckSteps.EnableWindow(FALSE);
		}
	}	

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein
}


void CDlgVerifySignature::OnClickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

	int row = phdn->iItem; // gibt an in welcher Zeile von m_listview das Item angeklickt wurde

	if (row == -1)
	{
		UserKeyId = "";
		UpdateRowSel(-1); // letzte Selektion rückgängig machen
		return;
	}

	UpdateRowSel(row) ;
	
	*pResult = 0;
}

int CDlgVerifySignature::GetSpecifRow(UINT mask)
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

void CDlgVerifySignature::OnKeydownList2(NMHDR* pNMHDR, LRESULT* pResult) 
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


void CDlgVerifySignature::OnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Funktion wird benötigt, damit OnColumnclickList2() funktioniert

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	*pResult = 0;
}

void CDlgVerifySignature::OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	// Diese Funktion wird aufgerufen, falls ein Linksklick auf einen der Spaltenheader erfolgt
	// Zur Zeit ist hier nichts implementiert
	// Vielleicht kommt später eine Sortierfunktion für die Zeilen hinzu.

	if (pNMListView->iSubItem == 0) sortBy = BY_NAME;
	else if (pNMListView->iSubItem == 1) sortBy = BY_FIRSTNAME;
	else if (pNMListView->iSubItem == 2) sortBy = BY_KEYTYPE;
	else if (pNMListView->iSubItem == 3) sortBy = BY_PERS_KEYID;
	else if (pNMListView->iSubItem == 4) sortBy = BY_CREATTIME;
	else if (pNMListView->iSubItem == 5) sortBy = BY_CREATTIME;

	UserKeyId = "";
	UpdateRowSel(-1); // letzte Selektion rückgängig machen

	*pResult = 0;
}

void CDlgVerifySignature::OnCheckDsaKey() 
{
	int status = m_CheckDSA.GetCheck(); // status==1: checked ; status==0: unchecked
	if (status == 0)
	{
		nKeylistType = nKeylistType - (nKeylistType & DSA_KEY); // remove DSA keys
		if (KeyType.Find(DSA_KEYFILE_IDSTRING) > -1)
		{
			// DSA Schlüssel werden gleich aus der Liste in m_listview entfernt
			// UserKeyId enthält aber DSA Schlüssel, also setze auf leer
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

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

void CDlgVerifySignature::OnCheckEcKey() 
{
	int status = m_CheckEC.GetCheck(); // status==1: checked ; status==0: unchecked
	if (status == 0)
	{
		nKeylistType = nKeylistType - (nKeylistType & EC_KEY); // remove EC keys
		if (KeyType.Find(EC_KEYFILE_IDSTRING) > -1)
		{
			// EC Schlüssel werden gleich aus der Liste in m_listview entfernt
			// UserKeyId enthält aber EC Schlüssel, also setze auf leer
			UserKeyId = "";
		}
		// Einstellung setzen: enable all RadioButtons
		m_ripemdRadioButton.EnableWindow(FALSE);
		m_sha1RadioButton.EnableWindow(FALSE);
		m_nrRadioButton.EnableWindow(FALSE);
		m_ecdsaRadioButton.EnableWindow(FALSE);
		m_acRadioButton.EnableWindow(FALSE);
		m_pcRadioButton.EnableWindow(FALSE);
		m_CheckSteps.EnableWindow(FALSE);
	}
	if ((status == 1) && ((nKeylistType & EC_KEY) == 0))
	{
		// es sind keine EC Schlüsselbezeichner in sortedAsymKeyList vorhanden,
		// also hinzufügen
		nKeylistType = nKeylistType + EC_KEY; // add EC keys

		// Einstellung setzen: enable all RadioButtons
		m_ripemdRadioButton.EnableWindow(TRUE);
		m_sha1RadioButton.EnableWindow(TRUE);
		m_nrRadioButton.EnableWindow(TRUE);
		m_ecdsaRadioButton.EnableWindow(TRUE);
		m_acRadioButton.EnableWindow(TRUE);
		m_pcRadioButton.EnableWindow(TRUE);
		m_CheckSteps.EnableWindow(TRUE);
	}
	
	InitAsymKeyListBox(nKeylistType); // Schlüsselbezeichner-Liste neu initialisieren

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}

void CDlgVerifySignature::OnCheckRsaKey() 
{
	int status = m_CheckRSA.GetCheck(); // status==1: checked ; status==0: unchecked
	if (status == 0)
	{
		nKeylistType = nKeylistType - (nKeylistType & RSA_KEY); // remove RSA keys
		if (KeyType.Find(RSA_KEYFILE_IDSTRING) > -1)
		{
			// RSA Schlüssel werden gleich aus der Liste in m_listview entfernt
			// UserKeyId enthält aber RSA Schlüssel, also setze auf leer
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

	UpdateRowSel( FindRow(UserKeyId) ); // Zeile die UserKeyId enthält unterlegen, falls vorhanden
}


void CDlgVerifySignature::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen

	// UpdateData(TRUE);
	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYLIST_ASYM_EMPTY,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		return; // no selection
	}
	else if ( UserKeyId.GetLength() < 1 )
	{
		// Noch kein Schlüsselbezeichner gewählt, obwohl in m_listview welche zur Auswahl stehen
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_SELECT_SIGNATUREORIGINATOR,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_listview.SetFocus();
		return;
	}

	if (KeyType.Find(EC_KEYFILE_IDSTRING) > -1) 
	{
		// ellipt. Kurven Schlüsseltyp selektiert
		// Überprüfe, ob Hashverfahren und Signaturverfahren gewählt sind
		if (m_SigVerfahren == -1)
		{
			// noch kein Signaturverfahren gewählt
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_UNKNOWN_EC_SIGNATURE_ALGORITHM,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
			m_ecdsaRadioButton.SetFocus();
			return;
		}
		if (m_HashFunktion == -1)
		{
			// noch keine Hashfunktion gewählt
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_UNKNOWN_HASHFUNCTION,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
			m_sha1RadioButton.SetFocus();
			return;
		}

		// In der Listbox ist ein EC Schlüsselpaar gewählt
		CKeyFile KeyFile;
		int ret = KeyFile.GetEcPublicParam(UserKeyId, DomParamAc); // get public parameter
		if ( ret == -1 )
		{
			// error. Die Datei UserKeyId konnte nicht geöffnet werden
			CString PubDataFile = (CString) PseVerzeichnis + ((CString)"/") + UserKeyId;
			LPTSTR string3 = new TCHAR[PubDataFile.GetLength()+1];
			_tcscpy(string3, PubDataFile);		
			char *key_file = string3;

			Message(IDS_STRING_EC_ERROR_LOADING_KEYFILE, MB_ICONINFORMATION, key_file);
			// free memory
			delete string3; // string3 ist nur in diesem Block initialisiert gewesen
			return;
		}
		else if ( ret != 0)
		{
			// error. sonstige Fehler in der Methode CKeyFile::GetEcPublicParam()
			// free memory
			return;
		}
		ecFp_DomParam_ac_to_pc (DomParamPc, DomParamAc); // Domain Parameter in affine und projective Koordinaten verfügbar

		if (m_CheckSteps.GetCheck() && m_pcRadioButton.GetCheck() )
		{
			// Benutzer will Zwischenschritte in projektiven Koordinaten sehen
			// Zwischenschritte werden aber nur in affinen Koordinaten angezeigt
			Message(IDS_STRING_MSG_EC_VERIFICATION_AFFINE_PROJECTIVE_COORDINATES, MB_ICONEXCLAMATION);
		}
	}
	else FreeEcMemory(); // ellipt. Kurven werden nicht benutzt

	CDialog::OnOK();
}

void CDlgVerifySignature::OnButtonSearchKey() 
{
	if ( (strcmp(sigAlg, "ECSP-DSA") == 0) || (strcmp(sigAlg, "ECSP-NR") == 0) )
	{
		// Überprüfe ob (nKeylistType & EC_KEY) == EC_KEY,
		// falls nicht füge EC Schlüseltypen in die List sortedAsymKeyList ein
		if ((nKeylistType & EC_KEY) != EC_KEY)
		{
			m_CheckEC.SetCheck(1);
			nKeylistType = nKeylistType | EC_KEY;
		}
	}
	else if (strcmp(sigAlg, "DSA") == 0)
	{
		// Überprüfe ob (nKeylistType & DSA_KEY) == DSA_KEY,
		// falls nicht füge DSA Schlüseltypen in die List sortedAsymKeyList ein
		if ((nKeylistType & DSA_KEY) != DSA_KEY)
		{
			m_CheckDSA.SetCheck(1);
			nKeylistType = nKeylistType | DSA_KEY;
		}
	}
	else if (strcmp(sigAlg, "RSA") == 0)
	{
		// Überprüfe ob (nKeylistType & RSA_KEY) == RSA_KEY,
		// falls nicht füge RSA Schlüseltypen in die List sortedAsymKeyList ein
		if ((nKeylistType & RSA_KEY) != RSA_KEY)
		{
			m_CheckRSA.SetCheck(1);
			nKeylistType = nKeylistType | RSA_KEY;
		}
	}
	else
	{
		// unbekanntes Verfahren angegeben.
		// Suche Schlüsselbezeichner signKey in allen Schlüsseltypen 
		m_CheckRSA.SetCheck(1);
		m_CheckDSA.SetCheck(1);
		m_CheckEC.SetCheck(1);
		nKeylistType = ASYM_KEY; // alle Schlüsseltypen in List sortedAsymKeyList einfügen
	}

	// Initialisiere die Schlüsselliste mit gewünschten Schlüsseltypen
	InitAsymKeyListBox(nKeylistType);

	int keyrow = FindRow(signKey);
	if ( (keyrow == -1) && (nKeylistType == ASYM_KEY) )
	{
		// Info: Schlüsselbezeichner signKey nicht in Liste vorhanden,
		// obwohl alle Schlüsseltypen durchsucht wurden
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_IDENTIFIER_NOT_FOUND,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1, signKey);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_UNKNOWN_SIGNATURE,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		return; // no selection
	}
	else if ( (keyrow == -1) && (nKeylistType != ASYM_KEY) )
	{
		// dieser Fall kann eintreten wenn z.B.:
		// sigAlg == RSA, tatsächlicher Schlüsseltyp == DSA, alle Checkboxen unchecked

		// durchsuche alle Schlüsseltypen nach dem Schlüsselbezeichner signKey
		m_CheckRSA.SetCheck(1);
		m_CheckDSA.SetCheck(1);
		m_CheckEC.SetCheck(1);

		InitAsymKeyListBox(ASYM_KEY);

		keyrow = FindRow(signKey);
		if ( keyrow == -1 )
		{
			// Info: Schlüsselbezeichner nicht in Liste vorhanden, obwohl alle Schlüsseltypen
			// durchsucht wurden
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_KEY_IDENTIFIER_NOT_FOUND,pc_str1,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str, pc_str1, signKey);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_UNKNOWN_SIGNATURE,pc_str1,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
			return; // no selection
		}
	}

	UpdateRowSel( keyrow ); // Zeile die signKey enthält unterlegen
	
	// Default Einstellung für EC-Signatur wiederherstellen,
	// falls signKey ein EC Schlüsselbezeichner
	if (strcmp(sigAlg, "ECSP-NR") == 0){
		CheckRadioButton (IDC_RADIO5, IDC_RADIO6, IDC_RADIO6);
	}
	else if (strcmp(sigAlg, "ECSP-DSA") == 0){
		CheckRadioButton (IDC_RADIO5, IDC_RADIO6, IDC_RADIO5);
	}

	if (strcmp(hashAlg, "SHA-1") == 0){
		CheckRadioButton (IDC_RADIO7, IDC_RADIO8, IDC_RADIO7);
	}
	else if (strcmp(hashAlg, "RIPEMD-160") == 0){
		CheckRadioButton (IDC_RADIO7, IDC_RADIO8, IDC_RADIO8);
	}

	UpdateData(TRUE);
}

void CDlgVerifySignature::OnRadioECDSA() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
}

void CDlgVerifySignature::OnRadioECNR() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	
}

void CDlgVerifySignature::OnRadioSHA1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	
}

void CDlgVerifySignature::OnRadioRIPEMD() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	
}

void CDlgVerifySignature::OnRadioAffineCoord() 
{
	UpdateData(TRUE);
	use_affine_coord = true;// TRUE:affine coordinates;FALSE:projective coordinate
}

void CDlgVerifySignature::OnRadioProjectCoord() 
{
	UpdateData(TRUE);
	use_affine_coord = false;// TRUE:affine coordinates;FALSE:projective coordinate
}
