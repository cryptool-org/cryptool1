// ==========================================================================
// Dlg_homophone.cpp: Implementation of homophone encrytion
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHomophone.h"
#include "assert.h"
#include "DialogeMessage.h"
#include "KeyRepository.h"

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
	m_Bitlength = 8;
	m_NoOfHomophones = range;
	m_EditNoOfHomophones = 0;
	m_RowHomophonesList = _T("");
	m_HomophonesList = _T("");
	m_EncryptFormatCharacters = FALSE;
	m_KodiereUmlaute = FALSE;
	//}}AFX_DATA_INIT
	m_crypt = 0;
	m_lastSelectedRow = -1;
	DeactivateDecryptionButton = FALSE;
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
	DDX_Text(pDX, IDC_EDIT5, m_Bitlength);
	DDX_Text(pDX, IDC_EDIT1, m_NoOfHomophones);
	DDX_Text(pDX, IDC_EDIT3, m_EditNoOfHomophones);
	DDV_MinMaxInt(pDX, m_EditNoOfHomophones, 0, 4096);
	DDX_Text(pDX, IDC_EDIT2, m_RowHomophonesList);
	DDX_Text(pDX, IDC_ROW, m_HomophonesList);
	DDX_Check(pDX, IDC_CHECK1, m_EncryptFormatCharacters);
	DDX_Check(pDX, IDC_CHECK2, m_KodiereUmlaute);
	//}}AFX_DATA_MAP
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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgKeyHomophone 

void CDlgKeyHomophone::OnErzeugen() 
{
	UpdateData(true);
	SHOW_HOUR_GLASS
	HB.Init_Data();
	Init_ListBox();
	HIDE_HOUR_GLASS
	UpdateData(false);
}

int CDlgKeyHomophone::Display()
{
	return(DoModal());
}

bool CDlgKeyHomophone::Get_crypt()
// liefert true zur�ck, wenn Verschl�sseln und false, wenn Entschl�sseln eingestellt ist
{
	if(0==m_crypt)
	{
		return(true);
	}
	return(false);
}

void CDlgKeyHomophone::OnDecrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	OnActualizeNoOfHomophones(); 
	m_crypt = 1;

	{ // Copy Homophone Parameter
		LoadString(AfxGetInstanceHandle(),IDS_PARAM_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
		char tmpStr[6];
		sprintf(tmpStr, "%i", m_NoOfHomophones );
		CString Primes = CString("PARAMETER: ") + char(m_BaseHomophones + '0') + ' ' + char(m_EncryptFormatCharacters + '0') +
											' ' + char(m_KodiereUmlaute + '0') + ' ' + CString( tmpStr );
		CopyKey ( pc_str, Primes );
	}
	OnOK();
}

void CDlgKeyHomophone::OnEncrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	OnActualizeNoOfHomophones();
	m_crypt = 0;

	{ // Copy Homophone Parameter
		LoadString(AfxGetInstanceHandle(),IDS_PARAM_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
		char tmpStr[6];
		sprintf(tmpStr, "%i", m_NoOfHomophones );
		CString Primes = CString("PARAMETER: ") + char(m_BaseHomophones + '0') + ' ' + char(m_EncryptFormatCharacters + '0') +
											' ' + char(m_KodiereUmlaute + '0') + ' ' + CString( tmpStr );
		CopyKey ( pc_str, Primes );
	}
	OnOK();
}

BOOL CDlgKeyHomophone::OnInitDialog() 
{
	int colWidth = 100;										// Spaltenbreite in Pixel

	CDialog::OnInitDialog();

	m_AlphabetBackup = theApp.TextOptions.m_alphabet;

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
	CString HParam;
	if ( PasteKey( pc_str, HParam ) )
	{
		UpdateData(true);
		int d = strlen("PARAMETER: ");
		m_BaseHomophones          = (int)(HParam[d] - '0');
		m_EncryptFormatCharacters = (int)(HParam[d+2] - '0');
		m_KodiereUmlaute          = (int)(HParam[d+4] - '0');
		m_NoOfHomophones          = (int)atoi( HParam.GetBuffer(0) +(d+6) );
		UpdateData(false);

		{ // Error-Precheck
			int l_alphabetLength = theApp.TextOptions.m_alphabet.GetLength();
			if (m_NoOfHomophones < l_alphabetLength) {
				UpdateData();
				m_NoOfHomophones = l_alphabetLength;
				UpdateData(FALSE);
			}
		}

		int ReInitFlag = 0;
		if ( m_EncryptFormatCharacters )
		{	
			if ( 0 > theApp.TextOptions.m_alphabet.Find("\n", 0) ) 
				theApp.TextOptions.m_alphabet.Insert(0, "\n"); 
			if ( 0 > theApp.TextOptions.m_alphabet.Find("\t", 0) ) 
				theApp.TextOptions.m_alphabet.Insert(0, "\t");
			if ( 0 > theApp.TextOptions.m_alphabet.Find("\r", 0) ) 
				theApp.TextOptions.m_alphabet.Insert(0, "\r");			
			ReInitFlag = 1;
		}	
		else
		{
			int ndx;
			if ( 0 <= (ndx = theApp.TextOptions.m_alphabet.Find("\n", 0)) ) 
				theApp.TextOptions.m_alphabet.Delete(ndx);
			if ( 0 <= (ndx = theApp.TextOptions.m_alphabet.Find("\t", 0)) ) 
				theApp.TextOptions.m_alphabet.Delete(ndx);
			if ( 0 <= (ndx = theApp.TextOptions.m_alphabet.Find("\r", 0)) ) 
				theApp.TextOptions.m_alphabet.Delete(ndx);
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
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_COLUMN_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-24,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING_QUANTITY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth-8,3);							// Verschl�sselung
	LoadString(AfxGetInstanceHandle(),IDS_STRING_LIST_OF_HOMOPHONES,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(4,pc_str,LVCFMT_LEFT,colWidth+2000,4);							// Verschl�sselung
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

	if ( IsKeyEmpty( "Homophone" ))
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
// f�llt die Liste auf mit
//	1.	den im Alphabet (Textoptionen) eingestellten Zeichen
//	2.	der Anzahl der ciphers, mit denen jedes Zeichen verschl�sselt werden kann
//	3.	den ciphers selbst
{
	SHOW_HOUR_GLASS
	int i;
	
	m_listview.DeleteAllItems(); 
	TA.Analyse( );
	for(i=0;i<range;i++)
	{
		HB.SetFrequency(i, TA.freq[i]);
	}
	HB.Make_enc_table();
	HB.Generate_key();
	LoadListBox();
	HIDE_HOUR_GLASS
}

void CDlgKeyHomophone::OnLoadKey() 
{
	SHOW_HOUR_GLASS

	UpdateData(TRUE);
	
	if ( FALSE == PasteKey("Homophone", m_KeyCStr ) )
	{
		m_KeyCtrl.SetSel(0,-1);
		m_KeyCtrl.Paste();
		m_KeyCtrl.GetWindowText(m_KeyCStr);
	}

	HB.load_enc_table(m_KeyCStr.GetBuffer(16000));	
	m_NoOfHomophones = HB.GetKeySize();
	m_Bitlength = HB.LogKeySize( 2 );
	m_listview.DeleteAllItems(); 
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
			if ( 0 > theApp.TextOptions.m_alphabet.Find(char(i)) ) 
			{
				Flag |= 2;
			}
		}
	}
	if ( Flag & 1 ) m_EncryptFormatCharacters = 1;
	if ( Flag & 2 || newAlphabet.GetLength() != theApp.TextOptions.m_alphabet.GetLength() ) {
		Message( IDS_MSG_HOMOPHONE_CHANGE_OF_ALPHABET, MB_ICONINFORMATION,
			 theApp.TextOptions.m_alphabet, newAlphabet );
		theApp.TextOptions.m_alphabet = newAlphabet;
	}

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
			for (k=0; k<=6; k++) string[k] =' '; 
			string[k] = 0;
			if ( char(i) == '\n' )      strncpy(string, "<LF>", 4); 
			else if ( char(i) == '\t' ) strncpy(string, "<TAB>", 5);
			else if ( char(i) == '\r' ) strncpy(string, "<CR>", 4); 
			else string[0]=i;

			j=m_listview.InsertItem(i,string);
	// Insert frequency
			number=HB.GetEncryptionData1(i);
			assert(number>0);
			sprintf(string,"%2i.%1i", (int)floor(HB.GetFrequency(i)*100.0),
				   (int)floor( (HB.GetFrequency(i)*100.0-floor(HB.GetFrequency(i)*100.0))*10.0+0.5) );
			string[4] = 0;
			m_listview.SetItemText(j,1,string);
	// Insert Count of Homophones
			sprintf(string,"%4i  ",number);
			m_listview.SetItemText(j,2,string);
			
	// Insert list of Homophones
			int		l = ( !m_BaseHomophones ) ? HB.LogKeySize( 16 ) : HB.LogKeySize( 10 );
			char	num[64];

			for(k=0;k<HB.GetEncryptionData1(i);k++)
			{
				number = HB.GetKey( m );
				num[l] = 0;
				if ( !m_BaseHomophones ) 
				{
					for ( int g = l-1; g >= 0; g-- )
					{
						char h = number % 16;
						number /= 16;
						if ( h < 10 ) num[g] = '0'+ h;
						else          num[g] = 'A'+(h-10);
					}
				}
				else
				{
					for ( int g = l-1; g >= 0; g-- )
					{
						char h = number % 10;
						number /= 10;
						num[g] = '0'+ h;
					}
				}
				sprintf( string+k*(l+2), "%s", num );
				if(k<HB.GetEncryptionData1(i)-1) 
					sprintf(string+k*(l+2)+l,", ");
				m++;
			}

			m_listview.SetItemText(j,3,string);
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
	int lng = theApp.TextOptions.m_alphabet.GetLength();
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

	if ( m_NoOfHomophones != HB.GetKeySize() )
	{
		SHOW_HOUR_GLASS
		HB.Resize( m_NoOfHomophones );
		m_Bitlength = HB.LogKeySize( 2 );
		HB.Init_Data();
		Init_ListBox();
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
		UpdateSelectedRow(-1); // letzte Selektion r�ckg�ngig machen
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
		// Status der m_lastSelectedRow Zeile auf normal setzen (Highlighten r�ckg�ngig machen);
		for (i=0; i<3; i++) // i durchl�uft die Spalten 0,1,2,3,4 und 5 
		{
			m_listview.SetItem(m_lastSelectedRow, i, LVIF_STATE, NULL, 0, NULL, LVIS_SELECTED, m_lastSelectedRow);
		}
		UpdateWindow();
	}

	if (newRow == -1)
	{
		m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt angew�hlte Zeile soll sichtbar sein
		return;
	}

	m_lastSelectedRow = newRow; // m_lastSelectedRow neu setzen

	// Farbliches hervorheben der Zeile row (highlighten) und gleichzeitig Werte auslesen
	for (i=0; i<3; i++) // i durchl�uft die Spalten 0,1,2,3,4 und 5 
	{
		Text = m_listview.GetItemText( newRow, i );

		if (Text.GetLength() == 0)
		{
			continue; // Falls in der aktuellen Spalte kein Text vorhanden ist, gehe zur n�chsten Spalte
		}
		m_listview.SetItem( newRow, i, LVIF_TEXT | LVIF_STATE, Text, 0, LVIS_SELECTED, LVIS_SELECTED, newRow);
		m_listview.SetItemText( newRow, i, Text );
	}

	m_listview.EnsureVisible( m_lastSelectedRow, FALSE ); // Die zuletzt anw�hlte Zeile soll sichtbar sein
}

int CDlgKeyHomophone::GetSpecificRow(UINT mask)
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

void CDlgKeyHomophone::OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int selRow = GetSpecificRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
	UpdateSelectedRow(selRow); // letzte selektion r�ckg�ngig machen

	CString Text;
	UpdateData(TRUE);
	Text = m_listview.GetItemText( selRow, 0 );
	m_RowHomophonesList = Text;

	Text = m_listview.GetItemText( selRow, 2 );
	m_EditNoOfHomophones = atoi(Text);

	int		l = ( !m_BaseHomophones ) ? HB.LogKeySize( 16 ) : HB.LogKeySize( 10 );
	char	num[64];
	
	int   m;
	{
		char  ch_tmp;
		if (      0 == m_RowHomophonesList.Find("<TAB>")) ch_tmp = '\t';
		else if ( 0 == m_RowHomophonesList.Find("<LF>"))  ch_tmp = '\n';
		else if ( 0 == m_RowHomophonesList.Find("<CR>"))  ch_tmp = '\r';
		else ch_tmp = m_RowHomophonesList[0];
		m = HB.GetEncryptionData0( (unsigned int)ch_tmp );
	}

	{
		char string[16000];

		for(int k=0;k<m_EditNoOfHomophones;k++)
		{
			int number = HB.GetKey( m );
			num[l] = 0;
			if ( !m_BaseHomophones ) 
			{
				for ( int g = l-1; g >= 0; g-- )
				{
					char h = number % 16;
					number /= 16;
					if ( h < 10 ) num[g] = '0'+ h;
					else          num[g] = 'A'+(h-10);
				}
			}
			else
			{
				for ( int g = l-1; g >= 0; g-- )
				{
					char h = number % 10;
					number /= 10;
					num[g] = '0'+ h;
				}
			}
			sprintf( string+k*(l+2), "%s", num );
			if(k<m_EditNoOfHomophones-1) 
				sprintf( string+k*(l+2)+l,", ");
			m++;
		}
		m_HomophonesList = string;

	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgKeyHomophone::OnReturnSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	int selRow = GetSpecificRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
	UpdateSelectedRow(selRow); // letzte selektion r�ckg�ngig machen

	CString Text;
	UpdateData(TRUE);
	for (int i=0; i<2; i++) // i durchl�uft die Spalten 0,1,2,3,4 und 5 
	{
		Text = m_listview.GetItemText( selRow, i );

		if (Text.GetLength() == 0)
		{
			continue; // Falls in der aktuellen Spalte kein Text vorhanden ist, gehe zur n�chsten Spalte
		}
	}
	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgKeyHomophone::OnSelectEncryptFormatCharacters() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	if ( !m_EncryptFormatCharacters )
	{	
		if (theApp.TextOptions.m_alphabet.GetLength()+3 > m_NoOfHomophones)
		{
			Message(IDS_MSG_HOMOPHONE_ALPHABET_SIZE_ERROR, MB_ICONEXCLAMATION, 
				    theApp.TextOptions.m_alphabet.GetLength()+3);
			UpdateData();
		    m_EncryptFormatCharacters = FALSE;
			UpdateData(FALSE);
			return;
		}

		m_EncryptFormatCharacters = TRUE;
		if ( 0 > theApp.TextOptions.m_alphabet.Find("\n", 0) ) 
			theApp.TextOptions.m_alphabet.Insert(0, "\n"); 
		if ( 0 > theApp.TextOptions.m_alphabet.Find("\t", 0) ) 
			theApp.TextOptions.m_alphabet.Insert(0, "\t");
		if ( 0 > theApp.TextOptions.m_alphabet.Find("\r", 0) ) 
			theApp.TextOptions.m_alphabet.Insert(0, "\r");
		m_listview.DeleteAllItems(); 
		LoadListBox();	
		OnErzeugen();
	}
	else
	{
		m_EncryptFormatCharacters = FALSE;
		int ndx;
		if ( 0 <= (ndx = theApp.TextOptions.m_alphabet.Find("\n", 0)) ) 
			theApp.TextOptions.m_alphabet.Delete(ndx);
		if ( 0 <= (ndx = theApp.TextOptions.m_alphabet.Find("\t", 0)) ) 
			theApp.TextOptions.m_alphabet.Delete(ndx);
		if ( 0 <= (ndx = theApp.TextOptions.m_alphabet.Find("\r", 0)) ) 
			theApp.TextOptions.m_alphabet.Delete(ndx);
		m_listview.DeleteAllItems(); 
		LoadListBox();
		OnErzeugen();
	}
	
}
