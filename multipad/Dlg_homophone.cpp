// Dlg_homophone.cpp: Implementierungsdatei
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

bool Dlg_homophone::Is_key()
{
	//return(!(m_key.IsEmpty()));
	return(true);
}

int Dlg_homophone::Display()
{
	return(DoModal());
}

bool Dlg_homophone::Get_crypt()
{
	if(0==m_crypt)
	{
		return(true);
	}
	return(false);
}

CString Dlg_homophone::Get_key()
{
	CString key,help;
	int value;
	key.Empty();
	for(int i=0;i<=255;i++)
	{
		value=HB.Get_key(i);
		if(value<10)
		{
			key+="00";
		}
		else if(value<100)
		{
			key+="0";
		}
		itoa(value,help.GetBuffer(10),10);
		key.Insert(key.GetLength(),help);
		key.Insert(key.GetLength()," ");
		help.Empty();
	}
	return(key);
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
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING37001,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING37002,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-40,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING37006,pc_str,STR_LAENGE_STRING_TABLE);
	m_listview.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth+2000,3);							// Verschlüsselung
	Init_ListBox();

	return(TRUE);
}

void Dlg_homophone::Init_ListBox()
{
	theApp.DoWaitCursor(0);
	char string[1300];
	int i,j,k,m,chars,number;
	NGram R(reference);
	
	m_listview.DeleteAllItems(); 
	chars=R.GetSize();
	for(i=0;i<chars;i++)
	{
		HB.Set_freq(i,R.GetFrequency(i));
	}
	HB.Calculate_ciphers(chars);
	HB.Generate_key();
	for(i=m=0;i<chars;i++)
	{
		string[0]=alphabet[i];
		string[1]=0;
		j=m_listview.InsertItem(i,string);
		number=HB.Get_cipher(i);
		assert(number>0);
		sprintf(string,"%2i",number);
		m_listview.SetItemText(j,1,string);
		for(k=0;k<HB.Get_cipher(i);k++)
		{
			sprintf(string+k*5,"%3i",HB.Get_key(m));
			if(k<HB.Get_cipher(i)-1)
			{
				sprintf(string+k*5+3,", ",HB.Get_key(m));
			}
			m++;
		}
		m_listview.SetItemText(j,2,string);
	}
	theApp.DoWaitCursor(-1);
}

void Dlg_homophone::Set_texts(SymbolArray t,SymbolArray r)
{
	alphabet=theApp.TextOptions.m_alphabet;
	text=t;	
	reference=r;
}

int Dlg_homophone::Crypt(int index,bool encrypt)
{
	if(true==encrypt)
	{
		return(HB.Get_random_number(index));		
	}
	else
	{

	}
	return(-1);
}

SymbolArray Dlg_homophone::Get_text()
{
	return(text);
}

int Dlg_homophone::Is_in_alpha(char c)
{
	int i;

	for(i=0;i<alphabet.GetLength();i++)
	{
		if(c==alphabet[i])
		{
			return(i);
		}
	}

	return(-1);
}
