//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-200
//////////////////////////////////////////////////////////////////

// RsaDec.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgRSADecryption.h"
#include "DialogeMessage.h"
#include "KeyFileHandling.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; // aus CrypTool.cpp
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSADecryption 


CDlgRSADecryption::CDlgRSADecryption(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRSADecryption::IDD, pParent)
{
	UserKeyId = "";
	Name = "";
	Firstname = "";
	KeyType = "";
	KeyInfo = "";
	CreatTime = "";
	m_bHideDuration = FALSE;
	disableButtons = false;

	m_lastSelectedRow = -1; //  �nderung in Member-Funktion CDlgRSAEncryption::OnClickList1()

	//{{AFX_DATA_INIT(CDlgRSADecryption)
	m_PinCode = _T("");
	m_ShowDuration = FALSE;
	//}}AFX_DATA_INIT
}

void CDlgRSADecryption::DoDataExchange(CDataExchange* pDX) 
{
	//{{AFX_DATA_MAP(CDlgRSADecryption)
	DDX_Control(pDX, IDOK, m_OKCtrl);
	DDX_Control(pDX, IDCANCEL, m_CancelCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_ShowDurationCtrl);
	DDX_Control(pDX, IDC_LIST_KEYS, m_listview);
	DDX_Control(pDX, IDC_EDIT1, m_PinCodeEditctrl);
	DDX_Text(pDX, IDC_EDIT1, m_PinCode);
	DDX_Check(pDX, IDC_CHECK1, m_ShowDuration);
	//}}AFX_DATA_MAP

	// TODO: Speziellen Code hier einf�gen und/oder Basisklasse aufrufen
	
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRSADecryption, CDialog)
	//{{AFX_MSG_MAP(CDlgRSADecryption)
	ON_NOTIFY(NM_CLICK, IDC_LIST_KEYS, OnClickListKeys)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_KEYS, OnItemclickListKeys)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_KEYS, OnColumnclickListKeys)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_KEYS, OnKeydownListKeys)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgRSADecryption 

BOOL CDlgRSADecryption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zus�tzliche Initialisierung hier einf�gen

	// Modifikationen initialisieren
	if(m_bHideDuration) m_ShowDurationCtrl.ShowWindow(SW_HIDE);
	if(!m_sDialogText.IsEmpty()) SetWindowText(m_sDialogText);
	if(!m_sOKText.IsEmpty()) m_OKCtrl.SetWindowText(m_sOKText);
	if(!m_sCancelText.IsEmpty()) m_CancelCtrl.SetWindowText(m_sCancelText);

	// m_listview in Report-Mode initialisieren

	int colWidth = 100;  // Spaltenbreite in Pixel

	LoadString(AfxGetInstanceHandle(),IDS_STRING_NAME,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 0, pc_str, LVCFMT_LEFT, colWidth-15 , 0); // Name

	LoadString(AfxGetInstanceHandle(),IDS_STRING_PRENAME,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, colWidth-25 , 1); // Vorname

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYTYPE,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, colWidth-15 , 2); // Schl�sseltyp

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_IDENTIFIER,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 3, pc_str, LVCFMT_LEFT, colWidth , 3); // Schl�sselkennung
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_CREATION_DATW,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 4, pc_str, LVCFMT_LEFT, colWidth+15 , 4); // Erstellungsdatum

	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_ID,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn( 5, pc_str, LVCFMT_LEFT, colWidth-20 , 5); // Interne ID-Nr.


	sortBy = BY_NAME; // default Einstellung: sortiere Liste nach Namen
	
	// Initialisiere die Schl�sselliste mit allen verf�gbaren RSA Schl�sseln
	nKeylistType = RSA_KEY;
	InitAsymKeyListBox(nKeylistType);

	//disableButtons wird in CDlgHybridDecryptionDemo auf true gesetzt.
	//dieser Abschnitt modifiziert den Dialog f�r die Anzeige bei der
	//Hybridverschl�sselung

	if(disableButtons)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_RSA_DLG_TITLE,pc_str,STR_LAENGE_STRING_TABLE);
		SetWindowText(pc_str);
		m_OKCtrl.SetWindowText("OK");
		m_ShowDurationCtrl.ShowWindow(false);
		int keyrow = FindRow(UserKeyId);// Suche nach der Zeile mit dem Eintrag UserKeyId

		UpdateRowSel( keyrow ); // Zeile die UserKeyId enth�lt unterlegen (falls vorhanden)
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgRSADecryption::InitAsymKeyListBox(unsigned nLocalKeylistType)
{
	// ermittele die zur Verf�gung stehenden Schl�ssel(-bezeichner) aus der Liste sortedAsymKeyList
	// und f�ge Sie in m_listview ein.
	// nLocalKeyType gibt an, welche Schl�sselbezeichner angezeigt werden:
	// nLocalKeyType == ASYM_KEY : alle (EC, RSA, DSA)
	// nLocalKeyType == EC_KEY  : nur EC
	// nLocalKeyType == RSA_KEY : nur RSA
	// nLocalKeyType == DSA_KEY : nur DSA
	// nLocalKeyType == DSA_KEY | RSA_KEY : DSA und RSA 
	// usw...

	CAsymmKeyAttrib keydata;
	CAvailabAsymmKeys asymmKeys;
	int row; // Zeile

	m_listview.DeleteAllItems( ); // Alle bisherigen Eintr�ge (sofern vorhanden) l�schen

	// ermittele alle vorhandenen RSA Schl�sselbezeichner die im PseVerzeichnis liegen
	int ret = asymmKeys.GetKeyList( sortedAsymKeyList, nLocalKeylistType, sortBy);

	row = 0;
	if ( ! sortedAsymKeyList.IsEmpty() )
	{
		// es gibt mindestens ein asymmetrische Schl�sselpaar
		POSITION listptr = sortedAsymKeyList.GetHeadPosition();
		while( listptr )
		{
			// es gibt mindestens einen weiteren Eintrag in der Liste
			keydata = sortedAsymKeyList.GetNext(listptr);
			// Einf�gen in n�chste Zeile von m_listview

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

void CDlgRSADecryption::UpdateRowSel(int row) 
{
	int i;
	CString Text;

	if (m_lastSelectedRow != -1)
	{
		// Status der m_lastSelectedRow Zeile auf normal setzen (Highlighten r�ckg�ngig machen);
		for (i=0; i<6; i++) // i durchl�uft die Spalten 0,1,2,3,4 und 5 
		{
			m_listview.SetItem(m_lastSelectedRow, i, LVIF_STATE, NULL, 0, NULL, LVIS_SELECTED, m_lastSelectedRow);
		}
		UpdateWindow();
	}

	if (row == -1)
	{
		m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angew�hlte Zeile soll sichtbar sein
		return;
	}

	m_lastSelectedRow = row; // m_lastSelectedRow neu setzen

	// Farbliches hervorheben der Zeile row (highlighten) und gleichzeitig Werte auslesen
	for (i=0; i<6; i++) // i durchl�uft die Spalten 0,1,2,3,4 und 5 
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
			continue; // Falls in der aktuellen Spalte kein Text vorhanden ist, gehe zur n�chsten Spalte
		}
		m_listview.SetItem(row, i, LVIF_TEXT | LVIF_STATE, Text, 0, LVIS_SELECTED, LVIS_SELECTED, row);
		m_listview.SetItemText( row, i, Text );
	}

	UserKeyId = "";
	CKeyFile KeyHandling;
	UserKeyId = KeyHandling.CreateFilename2(Name, Firstname, KeyType, CreatTime, KeyInfo);
	
	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anw�hlte Zeile soll sichtbar sein
}

int CDlgRSADecryption::GetSpecifRow(UINT mask)
{
// liefert die erste Zeile von m_lisview in der
// das Item in der ersten Spalte den Status mask hat
	int i;
	UINT itemState;

	// �berpr�fe welches Item der Maske "mask" entspricht
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

void CDlgRSADecryption::OnOK() 
{
	UpdateData(TRUE);

	if ( sortedAsymKeyList.IsEmpty() )
	{
		// there is no string selectable
		Message(IDS_STRING_ASYMKEY_MSG_NO_RSA_EMPTY_KEYLIST,MB_ICONINFORMATION);
		return; // no selection
	}
	else if (UserKeyId.GetLength() < 1)
	{
		// noch keinen Schl�ssel ausgew�hlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_SELECT_PSE2,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_listview.SetFocus();
		return;
	}

	if (m_PinCode=="")
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MSG_ENTER_PIN,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_PinCodeEditctrl.SetFocus();
		return;
	}
	
	if (disableButtons)
	{
		// �berpr�fe, ob der PIN-Code f�r den Zugriff auf die PSE richtig ist, indem
		// die entsprechende PSE Datei ge�ffnet und wieder geschlossen wird. 

		// Konvertieren der Pin-Nummer von CString nach char *
		LPTSTR string1 = new TCHAR[m_PinCode.GetLength()+1];
		_tcscpy(string1, m_PinCode);
		char *PIN=string1;

		// Pfad der PSE des Absenders (Signaturerstellers) in char * konvertieren
		CString help2=(CString)PseVerzeichnis+((CString)"/")+UserKeyId+PSE_FILE_SUFFIX;
		LPTSTR string2 = new TCHAR[help2.GetLength()+1];
		_tcscpy(string2, help2);
		char *PfadNeu=string2;

		// �ffnen der PSE des Absenders (Siganturerstellers) - nur um G�ltigkeit der PIN zu �berpr�fen
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
			// sonstige Fehler beim �ffnen der PSE
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);

			// Freigeben von dynamisch angelegtem Speicher
			delete string1;
			delete string2;
			return;
		}
		delete string1;
		delete string2;
		theApp.SecudeLib.af_close (PseHandle);
	}
	
	
	CDialog::OnOK();
}


void CDlgRSADecryption::OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	int row = phdn->iItem; // int, gibt an in welcher Zeile in IDC_LIST3 das Item angeklickt wurde

	if (row == -1)
	{
		// Der linksklick erfolgte nicht in (g�ltigen Zeile und erste Spalte)
		/*
		m_secret_param_button.EnableWindow(TRUE); // Button einblenden
		m_pub_param_button.EnableWindow(TRUE); // Button einblenden
		m_show_cert_button.EnableWindow(TRUE); // Button einblenden
		*/
	
		UserKeyId = "";
		UpdateRowSel(-1); // letzte Selektion r�ckg�ngig machen
		return;
	}

	UpdateRowSel(row) ;

	*pResult = 0;
}

void CDlgRSADecryption::OnItemclickListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 // Funktion wird ben�tigt, damit OnColumnclickList3() funktioniert

	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	
	*pResult = 0;
}

void CDlgRSADecryption::OnColumnclickListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen

	// Diese Funktion wird aufgerufen, falls ein Linksklick auf einen der Spaltenheader erfolgt
	// Zur Zeit ist hier nichts implementiert
	// Vielleicht kommt sp�ter eine Sortierfunktion f�r die Zeilen hinzu.

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
	//m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anw�hlte Zeile soll sichtbar sein

	/* Verf�gbare Werte f�r sortBy f�r CAvailabAsymmKeys::GetKeyList()
		BY_NAME 
		BY_FIRSTNAME 
		BY_KEYTYPE 
		BY_CREATTIME 
		BY_PERS_KEYID 
	*/
	
	UserKeyId = "";
	UpdateRowSel(-1); // letzte selektion r�ckg�ngig machen

	*pResult = 0;
}

void CDlgRSADecryption::OnKeydownListKeys(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen

	// Manuelle Behandlung, falls der Benutzer in m_listview Tsten dr�ckt

	int keycode = pLVKeyDow->wVKey; // welche Taste wurde gedr�ckt?
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
		// andere Taste gedr�ckt
		UserKeyId = "";
		UpdateRowSel(-1); // letzte selektion r�ckg�ngig machen
	}

	*pResult = 0;
}
int CDlgRSADecryption::FindRow( CString pattern)
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
		// i durchl�uft die Zeilen/Rows/Items
		match = true;

		Text = m_listview.GetItemText( i, 0 ); // erste Spalte: vergleiche Namen
		if ( Text != (CString) name ) match = false;

		Text = m_listview.GetItemText( i, 1 ); // 2.te Spalte: vergleiche Vornamen
		if ( Text != (CString) firstname ) match = false;

		Text = m_listview.GetItemText( i, 2 ); // 3.te Spalte: vergleiche Schl�sseltyp
		if ( Text != (CString) keyType ) match = false;

		Text = m_listview.GetItemText( i, 3 ); // 4.te Spalte: vergleiche Schl�sselkennung
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
