// ==========================================================================
// Dlg_homophone.cpp: Implementation of homophone encrytion
//

#include "stdafx.h"
#include "multipad.h"
#include "Dlg_homophone.h"
#include "assert.h"
#include "crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Dlg_homophone 
Dlg_homophone::Dlg_homophone(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_homophone::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_homophone)
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

void Dlg_homophone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_homophone)
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

BEGIN_MESSAGE_MAP(Dlg_homophone, CDialog)
	//{{AFX_MSG_MAP(Dlg_homophone)
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
// Behandlungsroutinen für Nachrichten Dlg_homophone 

void Dlg_homophone::OnErzeugen() 
{
	UpdateData(true);
	theApp.DoWaitCursor(0);
	HB.Init_Data();
	Init_ListBox();
	theApp.DoWaitCursor(-1);
	UpdateData(false);
}

int Dlg_homophone::Display()
{
	return(DoModal());
}

bool Dlg_homophone::Get_crypt()
// liefert true zurück, wenn Verschlüsseln und false, wenn Entschlüsseln eingestellt ist
{
	if(0==m_crypt)
	{
		return(true);
	}
	return(false);
}

void Dlg_homophone::OnDecrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_crypt = 1;
	OnOK();
}

void Dlg_homophone::OnEncrypt() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_crypt = 0;
	OnOK();
}

BOOL Dlg_homophone::OnInitDialog() 
{
	int colWidth = 100;										// Spaltenbreite in Pixel

	CDialog::OnInitDialog();

	m_listview.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_COLUMN_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-24,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING_QUANTITY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth-8,3);							// Verschlüsselung
	LoadString(AfxGetInstanceHandle(),IDS_STRING_LIST_OF_HOMOPHONES,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(4,pc_str,LVCFMT_LEFT,colWidth+2000,4);							// Verschlüsselung
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
	m_AlphabetBackup = theApp.TextOptions.m_alphabet;
	return(TRUE);
}

void Dlg_homophone::Init_ListBox()
// füllt die Liste auf mit
//	1.	den im Alphabet (Textoptionen) eingestellten Zeichen
//	2.	der Anzahl der ciphers, mit denen jedes Zeichen verschlüsselt werden kann
//	3.	den ciphers selbst
{
	theApp.DoWaitCursor(0);
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
	theApp.DoWaitCursor(-1);
}

void Dlg_homophone::OnLoadKey() 
{
	theApp.DoWaitCursor(0);

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
	UpdateData(FALSE);

	theApp.DoWaitCursor(-1);
}

void Dlg_homophone::LoadListBox()
{
	int		i,j,k,m,number;
	char	string[16000];

	for(i=m=0;i<range;i++)
	{
		if(HB.GetEncryptionData1(i)>0)
		{
	// Insert letter
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

void Dlg_homophone::OnHex() 
{
	UpdateData(TRUE);
	m_listview.DeleteAllItems(); 
	LoadListBox();	
	UpdateData(FALSE);
}

void Dlg_homophone::OnDecimal() 
{
	UpdateData(TRUE);
	m_listview.DeleteAllItems(); 
	LoadListBox();
	UpdateData(FALSE);
}

void Dlg_homophone::OnActualizeNoOfHomophones() 
{
	UpdateData(TRUE);
	if ( m_NoOfHomophones < range )
	{
		char Note[128];
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_HOMOPHONE_LOWERBND,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(Note, pc_str, range);
		AfxMessageBox( Note );
		m_NoOfHomophones = range;
	}

	if ( m_NoOfHomophones > upper_range )
	{
		char Note[128];
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_HOMOPHONE_UPPERBND,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(Note, pc_str, upper_range);
		AfxMessageBox( Note );
		m_NoOfHomophones = upper_range;
	}

	if ( m_NoOfHomophones != HB.GetKeySize() )
	{
		theApp.DoWaitCursor(0);
		HB.Resize( m_NoOfHomophones );
		m_Bitlength = HB.LogKeySize( 2 );
		HB.Init_Data();
		Init_ListBox();
		theApp.DoWaitCursor(-1);
	}
	UpdateData(FALSE);
}

void Dlg_homophone::OnSelectList(NMHDR* pNMHDR, LRESULT* pResult) 
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

void Dlg_homophone::UpdateSelectedRow(int newRow)
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

int Dlg_homophone::GetSpecificRow(UINT mask)
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

void Dlg_homophone::OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int selRow = GetSpecificRow( LVIS_FOCUSED ); // Welche Zeile hat Focus
	UpdateSelectedRow(selRow); // letzte selektion rückgängig machen

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

void Dlg_homophone::OnReturnSelect(NMHDR* pNMHDR, LRESULT* pResult) 
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

void Dlg_homophone::OnSelectEncryptFormatCharacters() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if ( !m_EncryptFormatCharacters )
	{	
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
