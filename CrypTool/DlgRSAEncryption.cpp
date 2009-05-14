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
// Diese Datei enthält Routinen zum Initialisieren der
// Dialogbox zur Schlüsselauswahl für die
// RSA-Verschlüsselung
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgRSAEncryption.h"
#include "secure.h"
#include "af.h"
#include "DialogeMessage.h"

#include "KeyFileHandling.h"

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSAEncryption 


CDlgRSAEncryption::CDlgRSAEncryption(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRSAEncryption::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRSAEncryption)
	m_ShowDuration = FALSE;
	//}}AFX_DATA_INIT

	UserKeyId = "";
	Name = "";
	Firstname = "";
	KeyType = "";
	KeyInfo = "";
	CreatTime = "";
	disableButtons = false;

	m_lastSelectedRow = -1; //  Änderung in Member-Funktion CDlgRSAEncryption::OnClickList1()
}


void CDlgRSAEncryption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRSAEncryption)
	DDX_Control(pDX, IDCANCEL, m_ctrlCancel);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlTime);
	DDX_Control(pDX, IDOK, m_ctrlOK);
	DDX_Control(pDX, IDC_LIST1, m_listview);
	DDX_Check(pDX, IDC_CHECK1, m_ShowDuration);
	DDX_Control(pDX, IDC_HEADLINE_SELECT, m_ctrlHeadlineSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRSAEncryption, CDialog)
	//{{AFX_MSG_MAP(CDlgRSAEncryption)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST1, OnItemclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRSAEncryption 

BOOL CDlgRSAEncryption::OnInitDialog() 
{
	CDialog::OnInitDialog();

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

	CString tmpStr;
	tmpStr.Format(IDS_TITLE_DLG_RSAENCRYPTION, oldTitle);
	this->SetWindowText(tmpStr);


	sortBy = BY_NAME; // default Einstellung: sortiere Liste nach Namen
	// Initialisiere die Schlüsselliste mit allen verfügbaren RSA Schlüsseln
	nKeylistType = RSA_KEY;
	InitAsymKeyListBox(nKeylistType);

	{  // ACHTUNG Aktiviert wird der Button, nachdem ein Zertifikat gewählt wurde. Die Aktivierung
	   // des Encrypt-Buttons ist in der Funktion CDlgRSAEncryption::UpdateRowSel(int row) zu finden
		encryptButtonVisible = FALSE;
		m_ctrlOK.EnableWindow(FALSE);
	}  

	//disableButtons wird in CDlgHybridEncryptionDemo auf true gesetzt.
	//dieser Abschnitt modifiziert den Dialog für die Anzeige bei der
	//Hybridverschlüsselung
	if(disableButtons)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_ENC_DLG,pc_str,STR_LAENGE_STRING_TABLE);
		SetWindowText(pc_str);
		CString ok;
		ok.Format(IDS_OK);
		m_ctrlOK.SetWindowText(ok);
		m_ctrlTime.ShowWindow(false);
		disableButtons = false;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_HEADLINE_ENC_DLG,pc_str,STR_LAENGE_STRING_TABLE);
		m_ctrlHeadlineSelect.SetWindowText(pc_str);
	}

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgRSAEncryption::InitAsymKeyListBox(unsigned nLocalKeylistType)
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

	// ermittele alle vorhandenen RSA Schlüsselbezeichner die im PseVerzeichnis liegen
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

void CDlgRSAEncryption::UpdateRowSel(int row) 
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
		m_ctrlOK.EnableWindow(FALSE);
		encryptButtonVisible = FALSE;
		return;
	}

	m_lastSelectedRow = row; // m_lastSelectedRow neu setzen

	if ( encryptButtonVisible == FALSE ) 	
	{
		encryptButtonVisible = TRUE;
		m_ctrlOK.EnableWindow();		
	}


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
	
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein
}

int CDlgRSAEncryption::GetSpecifRow(UINT mask)
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

void CDlgRSAEncryption::OnOK() 
{
	// UpdateData(TRUE);

	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		Message(IDS_STRING_ASYMKEY_MSG_NO_RSA_EMPTY_KEYLIST,MB_ICONINFORMATION);
		return; // no selection
	}
	else if (UserKeyId.GetLength() < 1)
	{
		// Noch keinen Schlüsselbezeichner ausgewählt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_SELECT_RECIEVER,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_listview.SetFocus();
		return;
	}

	CDialog::OnOK();
}

void CDlgRSAEncryption::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgRSAEncryption::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	// Diese Funktion wird aufgerufen, falls ein Linksklick auf einen der Spaltenheader erfolgt
	// Zur Zeit ist hier nichts implementiert
	// Vielleicht kommt später eine Sortierfunktion für die Zeilen hinzu.

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

void CDlgRSAEncryption::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgRSAEncryption::OnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 // Funktion wird benötigt, damit OnColumnclickList3() funktioniert

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	*pResult = 0;
}



