//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-200
//////////////////////////////////////////////////////////////////

// RsaDec.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "RsaDec.h"

#include "KeyFileHandling.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRsaDec 


CRsaDec::CRsaDec(CWnd* pParent /*=NULL*/)
	: CDialog(CRsaDec::IDD, pParent)
{
	UserKeyId = "";
	Name = "";
	Firstname = "";
	KeyType = "";
	KeyInfo = "";
	CreatTime = "";

	m_lastSelectedRow = -1; //  Änderung in Member-Funktion CRsaEnc::OnClickList1()

	//{{AFX_DATA_INIT(CRsaDec)
	m_PinCode = _T("");
	m_ShowDuration = FALSE;
	//}}AFX_DATA_INIT
}

void CRsaDec::DoDataExchange(CDataExchange* pDX) 
{
	//{{AFX_DATA_MAP(CRsaDec)
	DDX_Control(pDX, IDC_LIST_KEYS, m_listview);
	DDX_Control(pDX, IDC_EDIT1, m_PinCodeEditctrl);
	DDX_Text(pDX, IDC_EDIT1, m_PinCode);
	DDX_Check(pDX, IDC_CHECK1, m_ShowDuration);
	//}}AFX_DATA_MAP

	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRsaDec, CDialog)
	//{{AFX_MSG_MAP(CRsaDec)
	ON_NOTIFY(NM_CLICK, IDC_LIST_KEYS, OnClickListKeys)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_KEYS, OnItemclickListKeys)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_KEYS, OnColumnclickListKeys)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_KEYS, OnKeydownListKeys)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CRsaDec 

BOOL CRsaDec::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	// m_listview in Report-Mode initialisieren

	int colWidth = 100;  // Spaltenbreite in Pixel

	LoadString(AfxGetInstanceHandle(),IDS_STRING32879,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 0, pc_str, LVCFMT_LEFT, colWidth-15 , 0); // Name

	LoadString(AfxGetInstanceHandle(),IDS_STRING32880,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, colWidth-25 , 1); // Vorname

	LoadString(AfxGetInstanceHandle(),IDS_STRING32881,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, colWidth-15 , 2); // Schlüsseltyp

	LoadString(AfxGetInstanceHandle(),IDS_STRING32882,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 3, pc_str, LVCFMT_LEFT, colWidth , 3); // Schlüsselkennung
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING32883,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 4, pc_str, LVCFMT_LEFT, colWidth+15 , 4); // Erstellungsdatum

	LoadString(AfxGetInstanceHandle(),IDS_STRING32884,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 5, pc_str, LVCFMT_LEFT, colWidth-20 , 5); // Interne ID-Nr.


	sortBy = BY_NAME; // default Einstellung: sortiere Liste nach Namen
	
	// Initialisiere die Schlüsselliste mit allen verfügbaren RSA Schlüsseln
	nKeylistType = RSA_KEY;
	InitAsymKeyListBox(nKeylistType);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CRsaDec::InitAsymKeyListBox(unsigned nLocalKeylistType)
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

void CRsaDec::UpdateRowSel(int row) 
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
	
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein
}

int CRsaDec::GetSpecifRow(UINT mask)
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

void CRsaDec::OnOK() 
{
	UpdateData(TRUE);

	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		LoadString(AfxGetInstanceHandle(),IDS_STRING41550,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str,MB_ICONINFORMATION, 0 );
		return; // no selection
	}
	else if (UserKeyId.GetLength() < 1)
	{
		// noch keinen Schlüssel ausgewählt
		LoadString(AfxGetInstanceHandle(),IDS_STRING41427,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41408,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_listview.SetFocus();
		return;
	}

	if (m_PinCode=="")
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41410,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41408,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_PinCodeEditctrl.SetFocus();
		return;
	}
	
	CDialog::OnOK();
}


void CRsaDec::OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CRsaDec::OnItemclickListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 // Funktion wird benötigt, damit OnColumnclickList3() funktioniert

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	*pResult = 0;
}

void CRsaDec::OnColumnclickListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CRsaDec::OnKeydownListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
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
