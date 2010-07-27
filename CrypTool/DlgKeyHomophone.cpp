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

// ==========================================================================
// Dlg_homophone.cpp: Implementation of homophone encrytion
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHomophone.h"
#include "assert.h"
#include "DialogeMessage.h"
#include "KeyRepository.h"
#include ".\dlgkeyhomophone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHomophone 
CDlgKeyHomophone::CDlgKeyHomophone(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHomophone::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyHomophone)
	m_KeyCStr = _T("");
	m_BaseHomophones = 0;
	m_InputType = 0;
	m_Bitlength = 8;
	m_NoOfHomophones = range;
	m_EditNoOfHomophones = 0;
	m_RowHomophonesList = _T("");
	m_HomophonesList = _T("");
	//}}AFX_DATA_INIT
	m_crypt = 0;
	m_lastSelectedRow = -1;
	DeactivateDecryptionButton = FALSE;
	c_SourceFile[0] = '\0';
	InputTypeIsChanged = FALSE;
}

void CDlgKeyHomophone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyHomophone)
	DDX_Control(pDX, IDC_EDIT3, m_EditNoOfHomophonesCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_NoOfHomophonesCtrl);
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonDecryption);
	DDX_Control(pDX, IDC_EDIT5, m_BitlengthCtrl);
	DDX_Control(pDX, IDC_EDIT6, m_KeyCtrl);
	DDX_Control(pDX, IDC_LIST1, m_listview);
	DDX_Text(pDX, IDC_EDIT6, m_KeyCStr);
	DDX_Radio(pDX, IDC_RADIO4, m_BaseHomophones);
	DDX_Radio(pDX, IDC_RADIO_TEXT_INPUT, m_InputType);
	DDX_Text(pDX, IDC_EDIT5, m_Bitlength);
	DDX_Text(pDX, IDC_EDIT1, m_NoOfHomophones);
	DDX_Text(pDX, IDC_EDIT3, m_EditNoOfHomophones);
	DDV_MinMaxInt(pDX, m_EditNoOfHomophones, 0, 4096);
	DDX_Text(pDX, IDC_EDIT2, m_RowHomophonesList);
	DDX_Text(pDX, IDC_ROW, m_HomophonesList);
	DDX_Control(pDX, IDC_CHECK2, m_ctrlEncodeUmlauts);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlEncryptFormatCharacters);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON_TEXTOPTIONS, m_ctrlTextOptions);
}

BEGIN_MESSAGE_MAP(CDlgKeyHomophone, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHomophone)
	ON_BN_CLICKED(IDC_ERZEUGEN, OnErzeugen)
	ON_BN_CLICKED(IDC_BUTTON2, OnLoadKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_RADIO4, OnHex)
	ON_BN_CLICKED(IDC_RADIO5, OnDecimal)
	ON_BN_CLICKED(IDC_BUTTON3, OnActualizeNoOfHomophones)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnSelectList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkSelect)
	ON_NOTIFY(NM_RETURN, IDC_LIST1, OnReturnSelect)
	ON_BN_CLICKED(IDC_CHECK1, OnSelectEncryptFormatCharacters)
  //}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_RADIO_TEXT_INPUT, OnBnClickedRadioTextInput)
  ON_BN_CLICKED(IDC_RADIO_BINARY_INPUT, OnBnClickedRadioBinaryInput)
  ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, &CDlgKeyHomophone::OnBnClickedButtonTextoptions)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHomophone 

void CDlgKeyHomophone::OnErzeugen() 
{
	UpdateData(true);
	SHOW_HOUR_GLASS
	HB.Init_Data();
	Init_ListBox();

// === Reset selected homophonic list
	m_EditNoOfHomophones = 0;
	m_RowHomophonesList = _T("");
	m_HomophonesList = _T("");

	HIDE_HOUR_GLASS
	UpdateData(false);
}

int CDlgKeyHomophone::Display()
{
	return(DoModal());
}

bool CDlgKeyHomophone::Get_crypt()
// liefert true zurück, wenn Verschlüsseln und false, wenn Entschlüsseln eingestellt ist
{
	if(0==m_crypt)
	{
		return(true);
	}
	return(false);
}

void CDlgKeyHomophone::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnActualizeNoOfHomophones(); 
	m_crypt = 1;

	{ // Copy Homophone Parameter
		LoadString(AfxGetInstanceHandle(),IDS_PARAM_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
		char tmpStr[6];
		sprintf(tmpStr, "%i", m_NoOfHomophones );
		CString Primes = CString("PARAMETER: ") + char(m_BaseHomophones + '0') + ' ' + char(m_ctrlEncryptFormatCharacters.GetCheck() + '0') +
			' ' + char(m_ctrlEncodeUmlauts.GetCheck() + '0') + 
			' ' + char(m_InputType + '0') + ' ' + CString( tmpStr );
		CopyKey ( pc_str, Primes );
	}
	OnOK();
}

void CDlgKeyHomophone::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnActualizeNoOfHomophones();
	m_crypt = 0;

	{ // Copy Homophone Parameter
		LoadString(AfxGetInstanceHandle(),IDS_PARAM_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
		char tmpStr[6];
		sprintf(tmpStr, "%i", m_NoOfHomophones );
		CString Primes = CString("PARAMETER: ") + char(m_BaseHomophones + '0') + ' ' + char(m_ctrlEncryptFormatCharacters.GetCheck() + '0') +
			' ' + char(m_ctrlEncodeUmlauts.GetCheck() + '0') + 
			' ' + char(m_InputType + '0') + ' ' + CString( tmpStr );
		CopyKey ( pc_str, Primes );
		m_encodeUmlauts = m_ctrlEncodeUmlauts.GetCheck();
	}
	OnOK();
}

BOOL CDlgKeyHomophone::OnInitDialog() 
{
	int colWidth = 100;										// Spaltenbreite in Pixel

	CDialog::OnInitDialog();

	m_ctrlEncodeUmlauts.SetCheck(FALSE);
	m_AlphabetBackup = theApp.TextOptions.getAlphabet();

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
	CString HParam;
	if ( PasteKey( pc_str, HParam ) )
	{
		UpdateData(true);
		int d = strlen("PARAMETER: ");
		m_BaseHomophones          = (int)(HParam[d] - '0');
		m_ctrlEncryptFormatCharacters.SetCheck((int)(HParam[d+2] - '0'));
		m_ctrlEncodeUmlauts.SetCheck((int)(HParam[d+4] - '0'));
		m_InputType				  = (int)(HParam[d+6] - '0');
		m_NoOfHomophones          = (int)atoi( HParam.GetBuffer(0) +(d+8) );
		UpdateData(false);



		// TEXT 
		int ReInitFlag = 0;
		if ( !m_InputType )
		{
			int l_alphabetLength = theApp.TextOptions.getAlphabet().GetLength();
			if (m_NoOfHomophones < l_alphabetLength) {
				UpdateData();
				m_NoOfHomophones = l_alphabetLength;
				UpdateData(FALSE);
			}


			if ( m_ctrlEncryptFormatCharacters.GetCheck() )
			{	
				if ( 0 > theApp.TextOptions.getAlphabet().Find("\n", 0) ) 
					theApp.TextOptions.refAlphabet().Insert(0, "\n"); 
				if ( 0 > theApp.TextOptions.getAlphabet().Find("\t", 0) ) 
					theApp.TextOptions.refAlphabet().Insert(0, "\t");
				if ( 0 > theApp.TextOptions.getAlphabet().Find("\r", 0) ) 
					theApp.TextOptions.refAlphabet().Insert(0, "\r");			
				ReInitFlag = 1;
			}	
			else
			{
				int ndx;
				if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\n", 0)) ) 
					theApp.TextOptions.refAlphabet().Delete(ndx);
				if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\t", 0)) ) 
					theApp.TextOptions.refAlphabet().Delete(ndx);
				if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\r", 0)) ) 
					theApp.TextOptions.refAlphabet().Delete(ndx);
			}
		}

		if ( m_NoOfHomophones != HB.GetKeySize() )
		{
			HB.Resize( m_NoOfHomophones );
			UpdateData();
			m_Bitlength = HB.LogKeySize( 2 );
			UpdateData(FALSE);
			ReInitFlag = 1;
		}
		if ( ReInitFlag )
			HB.Init_Data();
	}

	m_listview.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	// LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(1,"Ord",LVCFMT_LEFT,colWidth-48,1);							// Ordnung Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_COLUMN_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth-24,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING_QUANTITY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(4,pc_str,LVCFMT_LEFT,colWidth-8,3);							// Verschlüsselung
	LoadString(AfxGetInstanceHandle(),IDS_STRING_LIST_OF_HOMOPHONES,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(5,pc_str,LVCFMT_LEFT,colWidth+2000,4);							// Verschlüsselung
	Init_ListBox();

	LOGFONT LogFont;
	CFont *defaultFont=m_listview.GetFont();				// this->GetFont() sollte auch funktionieren
	defaultFont->GetLogFont(&LogFont);						// Default Systemschrift ermitteln
	strncpy(LogFont.lfFaceName,"Courier",32);				// Auf Courier umstellen
	m_Font.CreateFontIndirect(&LogFont);					// Font initialisieren
	m_listview.SetFont(&m_Font);

	if ( DeactivateDecryptionButton )
		m_ButtonDecryption.EnableWindow(FALSE);

	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	m_Paste.SetToolTipText(&buttonPasteText);

	if ( m_InputType == HOM_ENC_TXT )
	{
		m_ctrlEncodeUmlauts.EnableWindow();
		m_ctrlEncryptFormatCharacters.EnableWindow();
		m_ctrlTextOptions.EnableWindow();
	}
	else
	{
		m_ctrlTextOptions.EnableWindow(FALSE);
		m_ctrlEncodeUmlauts.EnableWindow(FALSE);
		m_ctrlEncryptFormatCharacters.EnableWindow(FALSE);
	}

	CString SKeyID;
	SKeyID.LoadStringA(IDS_CRYPT_HOMOPHONE);
	if ( IsKeyEmpty( SKeyID ) )
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}
	return(TRUE);
}

void CDlgKeyHomophone::Init_ListBox()
// füllt die Liste auf mit
//	1.	den im Alphabet (Textoptionen) eingestellten Zeichen
//	2.	der Anzahl der ciphers, mit denen jedes Zeichen verschlüsselt werden kann
//	3.	den ciphers selbst
{
	SHOW_HOUR_GLASS
	int i;
	if (!m_InputType)
	{
		m_listview.DeleteAllItems(); 
		if ( !TA.Analyse() )
		{
			// Message( IDS_STATISTICAL_REFERENCE_FILE_MISSING, MB_ICONINFORMATION );
			TA.Analyse(c_SourceFile);
		}
	}
	else
	{
		m_listview.DeleteAllItems(); 
		TA.Analyse(c_SourceFile, HOM_ENC_BIN);
	}

	for(i=0;i<range;i++)
	{
		HB.SetFrequency(i, TA.freq[i]);
	}
	HB.Make_enc_table(m_InputType);
	HB.Generate_key();
	LoadListBox();

	HIDE_HOUR_GLASS
}

void CDlgKeyHomophone::OnLoadKey() 
{
	SHOW_HOUR_GLASS

	UpdateData(TRUE);

	CString SKeyID;
	SKeyID.LoadStringA(IDS_CRYPT_HOMOPHONE);
	if ( FALSE == PasteKey(SKeyID, m_KeyCStr ) )
	{
		m_KeyCtrl.SetSel(0,-1);
		m_KeyCtrl.Paste();
		m_KeyCtrl.GetWindowText(m_KeyCStr);
	}

	HB.load_enc_table(m_KeyCStr.GetBuffer(16000));	
	m_NoOfHomophones = HB.GetKeySize();
	m_Bitlength = HB.LogKeySize( 2 );
	m_listview.DeleteAllItems(); 
	m_InputType = HB.GetKeyType();

	LoadListBox();	
	int Flag = 0;

	CString newAlphabet = _T("");
	for(int i=0;i<range;i++)
	{
		if(HB.GetEncryptionData1(i)>0) 			
		{
			if ( char(i) == '\n' || char(i) == '\t' || char(i) == '\r' )  
			{
				Flag |= 1;
			}
			newAlphabet += char(i);
			if ( 0 > theApp.TextOptions.getAlphabet().Find(char(i)) ) 
			{
				Flag |= 2;
			}
		}
	}
	if ( (HOM_ENC_TXT == m_InputType) && (Flag & 1) ) m_ctrlEncryptFormatCharacters.SetCheck(1);
	if ( (HOM_ENC_TXT == m_InputType) && (Flag & 2 || newAlphabet.GetLength() != theApp.TextOptions.getAlphabet().GetLength()) ) {
		Message( IDS_MSG_HOMOPHONE_CHANGE_OF_ALPHABET, MB_ICONINFORMATION,
			 theApp.TextOptions.getAlphabet(), newAlphabet );
		theApp.TextOptions.refAlphabet() = newAlphabet;
	}

	if ( m_InputType == HOM_ENC_TXT )
	{
		m_ctrlEncodeUmlauts.EnableWindow();
		m_ctrlEncryptFormatCharacters.EnableWindow();
	}
	else
	{
		m_ctrlEncodeUmlauts.EnableWindow(FALSE);
		m_ctrlEncryptFormatCharacters.EnableWindow(FALSE);
	}


// === Reset selected homophonic list
	m_EditNoOfHomophones = 0;
	m_RowHomophonesList = _T("");
	m_HomophonesList = _T("");

	UpdateData(FALSE);

	HIDE_HOUR_GLASS
}

void CDlgKeyHomophone::LoadListBox()
{
	int		i,j,k,m,number;
	char	string[16000];

	for(i=m=0;i<range;i++)
	{
		if(HB.GetEncryptionData1(i)>0)
		{
	// Insert CPlayfairLetter
			if ( !m_BaseHomophones )
				sprintf(string, "%X", (unsigned short)i);
			else
				sprintf(string, "%d", (unsigned short)i);

			j=m_listview.InsertItem(i,string);

			for (k=0; k<=6; k++) string[k] =' '; 
			string[k] = 0;
			if ( char(i) == '\n' )      strncpy(string, "<LF>", 4); 
			else if ( char(i) == '\t' ) strncpy(string, "<TAB>", 5);
			else if ( char(i) == '\r' ) strncpy(string, "<CR>", 4); 
			else {
				string[0] = ((32 < i) && (i < 256)) ? char(i) : ' ';
				string[1] = '\0';
			}

			m_listview.SetItemText(j,1, string);
	// Insert frequency
			number=HB.GetEncryptionData1(i);
			assert(number>0);
			sprintf(string,"%2i.%1i", (int)floor(HB.GetFrequency(i)*100.0),
				   (int)floor( (HB.GetFrequency(i)*100.0-floor(HB.GetFrequency(i)*100.0))*10.0+0.5) );
			string[4] = 0;
			m_listview.SetItemText(j,2,string);
	// Insert Count of Homophones
			sprintf(string,"%4i  ",number);
			m_listview.SetItemText(j,3,string);
			
	// Insert list of Homophones
			char	num[64];
			string[0] = '\0';

			for(k=0;k<HB.GetEncryptionData1(i);k++)
			{
				number = HB.GetKey( m );
				num[0] = '\0';
				if ( !m_BaseHomophones )
					sprintf(num,"%X", number);
				else
					sprintf(num,"%d", number);
				strcat(string, num);
				if(k<HB.GetEncryptionData1(i)-1) 
					strcat(string, ", ");				
				m++;
			}

			m_listview.SetItemText(j,4,string);
		}
	}
}

void CDlgKeyHomophone::OnHex() 
{
	UpdateData(TRUE);
	m_listview.DeleteAllItems(); 
	LoadListBox();	
	UpdateData(FALSE);
}

void CDlgKeyHomophone::OnDecimal() 
{
	UpdateData(TRUE);
	m_listview.DeleteAllItems(); 
	LoadListBox();
	UpdateData(FALSE);
}

void CDlgKeyHomophone::OnActualizeNoOfHomophones() 
{
	UpdateData(TRUE);
	int lng = 256;
	if ( !m_InputType )
	{
		lng = theApp.TextOptions.getAlphabet().GetLength();
		if ( m_ctrlEncryptFormatCharacters.GetCheck() ) 
			lng +=3;
	}
	if ( m_NoOfHomophones <  lng /* range */ )
	{
		Message(IDS_STRING_MSG_HOMOPHONE_LOWERBND, MB_ICONEXCLAMATION, lng /*range*/);
		m_NoOfHomophones = lng /*range */;
	}

	if ( m_NoOfHomophones > upper_range )
	{
		Message(IDS_STRING_MSG_HOMOPHONE_UPPERBND, MB_ICONEXCLAMATION, upper_range);
		m_NoOfHomophones = upper_range;
	}

	if ( m_NoOfHomophones != HB.GetKeySize() || InputTypeIsChanged )
	{
		SHOW_HOUR_GLASS
		HB.Resize( m_NoOfHomophones );
		m_Bitlength = HB.LogKeySize( 2 );
		HB.Init_Data();
		Init_ListBox();

	// === Reset selected homophonic list
		m_EditNoOfHomophones = 0;
		m_RowHomophonesList = _T("");
		m_HomophonesList = _T("");
		InputTypeIsChanged = FALSE;

		HIDE_HOUR_GLASS
	}
	UpdateData(FALSE);
}

void CDlgKeyHomophone::OnSelectList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	int row = phdn->iItem; // int, gibt an in welcher Zeile in IDC_LIST3 das Item angeklickt wurde

	if (row == -1)
	{
		UpdateSelectedRow(-1); // letzte Selektion rückgängig machen
		return;
	}

	UpdateSelectedRow(row) ;
	
	*pResult = 0;
}

void CDlgKeyHomophone::UpdateSelectedRow(int newRow)
{
	int i;
	CString Text;

	if (m_lastSelectedRow != -1)
	{
		// Status der m_lastSelectedRow Zeile auf normal setzen (Highlighten rückgängig machen);
		for (i=0; i<3; i++) // i durchläuft die Spalten 0,1,2,3,4 und 5 
		{
			m_listview.SetItem(m_lastSelectedRow, i, LVIF_STATE, NULL, 0, NULL, LVIS_SELECTED, m_lastSelectedRow);
		}
		UpdateWindow();
	}

	if (newRow == -1)
	{
		m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angewählte Zeile soll sichtbar sein
		return;
	}

	m_lastSelectedRow = newRow; // m_lastSelectedRow neu setzen

	// Farbliches hervorheben der Zeile row (highlighten) und gleichzeitig Werte auslesen
	for (i=0; i<3; i++) // i durchläuft die Spalten 0,1,2,3,4 und 5 
	{
		Text = m_listview.GetItemText( newRow, i );

		if (Text.GetLength() == 0)
		{
			continue; // Falls in der aktuellen Spalte kein Text vorhanden ist, gehe zur nächsten Spalte
		}
		m_listview.SetItem( newRow, i, LVIF_TEXT | LVIF_STATE, Text, 0, LVIS_SELECTED, LVIS_SELECTED, newRow);
		m_listview.SetItemText( newRow, i, Text );
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anwählte Zeile soll sichtbar sein
}

int CDlgKeyHomophone::GetSpecificRow(UINT mask)
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

void CDlgKeyHomophone::OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int selRow = GetSpecificRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
	UpdateSelectedRow(selRow); // letzte selektion rückgängig machen

	CString Text;
	UpdateData(TRUE);
	Text = m_listview.GetItemText( selRow, 1 );
	m_RowHomophonesList = Text;

	Text = m_listview.GetItemText( selRow, 3 );
	m_EditNoOfHomophones = atoi(Text);

	int   m;
	char  ch_tmp;
	if (      0 == m_RowHomophonesList.Find("<TAB>")) ch_tmp = '\t';
	else if ( 0 == m_RowHomophonesList.Find("<LF>"))  ch_tmp = '\n';
	else if ( 0 == m_RowHomophonesList.Find("<CR>"))  ch_tmp = '\r';
	else ch_tmp = m_RowHomophonesList[0];
	m = HB.GetEncryptionData0( (unsigned char)ch_tmp );

	char string[16000];
	string[0] = '\0';
	char	num[64];
	for(int k=0;k<m_EditNoOfHomophones;k++)
	{
		int number = HB.GetKey( m );
		num[0] = '\0';
		if ( !m_BaseHomophones )
			sprintf(num,"%X", number);
		else
			sprintf(num,"%d", number);
		strcat(string, num);
		if(k<m_EditNoOfHomophones-1) 
			strcat(string, ", ");				
		m++;
	}
	m_HomophonesList = string;

	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgKeyHomophone::OnReturnSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	int selRow = GetSpecificRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
	UpdateSelectedRow(selRow); // letzte selektion rückgängig machen

	CString Text;
	UpdateData(TRUE);
	for (int i=0; i<2; i++) // i durchläuft die Spalten 0,1,2,3,4 und 5 
	{
		Text = m_listview.GetItemText( selRow, i );

		if (Text.GetLength() == 0)
		{
			continue; // Falls in der aktuellen Spalte kein Text vorhanden ist, gehe zur nächsten Spalte
		}
	}
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgKeyHomophone::OnSelectEncryptFormatCharacters() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if ( m_ctrlEncryptFormatCharacters.GetCheck() )
	{	
		if (theApp.TextOptions.getAlphabet().GetLength()+3 > m_NoOfHomophones)
		{
			Message(IDS_MSG_HOMOPHONE_ALPHABET_SIZE_ERROR, MB_ICONEXCLAMATION, 
				    theApp.TextOptions.getAlphabet().GetLength()+3);
			UpdateData();
		    m_ctrlEncryptFormatCharacters.SetCheck(0);;
			UpdateData(FALSE);
			return;
		}

		m_ctrlEncryptFormatCharacters.SetCheck(1);
		if ( 0 > theApp.TextOptions.getAlphabet().Find("\n", 0) ) 
			theApp.TextOptions.refAlphabet().Insert(0, "\n"); 
		if ( 0 > theApp.TextOptions.getAlphabet().Find("\t", 0) ) 
			theApp.TextOptions.refAlphabet().Insert(0, "\t");
		if ( 0 > theApp.TextOptions.getAlphabet().Find("\r", 0) ) 
			theApp.TextOptions.refAlphabet().Insert(0, "\r");
		m_listview.DeleteAllItems(); 
		LoadListBox();	
		OnErzeugen();
	}
	else
	{
		int ndx;
		if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\n", 0)) ) 
			theApp.TextOptions.refAlphabet().Delete(ndx);
		if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\t", 0)) ) 
			theApp.TextOptions.refAlphabet().Delete(ndx);
		if ( 0 <= (ndx = theApp.TextOptions.getAlphabet().Find("\r", 0)) ) 
			theApp.TextOptions.refAlphabet().Delete(ndx);
		m_listview.DeleteAllItems(); 
		LoadListBox();
		OnErzeugen();
	}
	
}

void CDlgKeyHomophone::OnBnClickedRadioTextInput()
{
	if (m_InputType) 
		InputTypeIsChanged = TRUE;
	OnActualizeNoOfHomophones();
	m_ctrlEncodeUmlauts.EnableWindow();
	m_ctrlEncryptFormatCharacters.EnableWindow();
	m_ctrlTextOptions.EnableWindow();
}

void CDlgKeyHomophone::OnBnClickedRadioBinaryInput()
{
	if (!m_InputType) 
		InputTypeIsChanged = TRUE;
	OnActualizeNoOfHomophones();
	m_ctrlEncodeUmlauts.EnableWindow(FALSE);
	m_ctrlEncryptFormatCharacters.EnableWindow(FALSE);
	m_ctrlTextOptions.EnableWindow(FALSE); 
}

void CDlgKeyHomophone::OnBnClickedButtonTextoptions()
{
	theApp.TextOptions.DoModal();
	InputTypeIsChanged = TRUE;
	OnActualizeNoOfHomophones();
}
