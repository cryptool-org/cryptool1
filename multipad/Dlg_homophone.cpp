// ==========================================================================
// Dlg_homophone.cpp: Implementation of homophone encrytion
//

#include "stdafx.h"
#include "multipad.h"
#include "Dlg_homophone.h"
#include "assert.h"

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
	m_crypt = 0;
	//}}AFX_DATA_INIT
}


void Dlg_homophone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_homophone)
	DDX_Control(pDX, IDC_LIST1, m_listview);
	DDX_Radio(pDX, IDC_RADIO1, m_crypt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_homophone, CDialog)
	//{{AFX_MSG_MAP(Dlg_homophone)
	ON_BN_CLICKED(IDC_ERZEUGEN, OnErzeugen)
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

BOOL Dlg_homophone::OnInitDialog() 
{
	int colWidth = 100;										// Spaltenbreite in Pixel

	CDialog::OnInitDialog();

	LOGFONT LogFont;
	CFont *defaultFont=m_listview.GetFont();				// this->GetFont() sollte auch funktionieren
	defaultFont->GetLogFont(&LogFont);						// Default Systemschrift ermitteln
	strncpy(LogFont.lfFaceName,"Courier",32);				// Auf Courier umstellen
	m_Font.CreateFontIndirect(&LogFont);					// Font initialisieren
	m_listview.SetFont(&m_Font);
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_SIGN,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_QUANTITY,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-40,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING_LIST_OF_HOMOPHONES,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth+2000,3);							// Verschlüsselung
	Init_ListBox();

	return(TRUE);
}

void Dlg_homophone::Init_ListBox()
// füllt die Liste auf mit

//	1.	den im Alphabet (Textoptionen) eingestellten Zeichen
//	2.	der Anzahl der ciphers, mit denen jedes Zeichen verschlüsselt werden kann
//	3.	den ciphers selbst

{
	theApp.DoWaitCursor(0);
	char string[1300];
	int i,j,k,m,number;
	
	m_listview.DeleteAllItems(); 
	TA.Analyse();
	for(i=0;i<range;i++)
	{
		HB.freq[i]=TA.freq[i];
	}
	HB.Make_enc_table();
	HB.Generate_key();
	for(i=m=0;i<range;i++)
	{
		if(HB.enc_data[i][1]>0)
		{
			string[0]=i;
			string[1]=0;
			j=m_listview.InsertItem(i,string);
			number=HB.enc_data[i][1];
			assert(number>0);
			sprintf(string,"%2i",number);
			m_listview.SetItemText(j,1,string);
			for(k=0;k<HB.enc_data[i][1];k++)
			{
				sprintf(string+k*5,"%3i",HB.key[m]);
				if(k<HB.enc_data[i][1]-1)
				{
					sprintf(string+k*5+3,", ",HB.key[m]);
				}
				m++;
			}
			m_listview.SetItemText(j,2,string);
		}
	}
	theApp.DoWaitCursor(-1);
}
