// Hashdemo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "Hashdemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHashdemo 


CHashdemo::CHashdemo(CWnd* pParent /*=NULL*/)
	: CDialog(CHashdemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHashdemo)
	m_strText = _T("");
	m_rb_DarstHW = 1;
	m_Auswahl_HW = 0;
	m_strOrigHash = _T("");
	m_strNewHash = _T("");
	m_strTitel = _T("");
	m_strTitel2 = _T("");
	m_strHashDiffRE = _T("");
	//}}AFX_DATA_INIT
}


void CHashdemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHashdemo)
	DDX_Control(pDX, IDC_RICHEDIT_HASHDIFF, m_ctrlHashDiff);
	DDX_Control(pDX, IDC_EDIT_ORIGHASH, m_ctrlOrigHash);
	DDX_Control(pDX, IDC_EDIT_AKTHASH, m_ctrlNewHash);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDX_Radio(pDX, IDC_RADIO_DEC, m_rb_DarstHW);
	DDX_Radio(pDX, IDC_RADIO_MD2, m_Auswahl_HW);
	DDX_Text(pDX, IDC_EDIT_ORIGHASH, m_strOrigHash);
	DDX_Text(pDX, IDC_EDIT_AKTHASH, m_strNewHash);
	DDX_Text(pDX, IDC_STATIC_TITEL, m_strTitel);
	DDX_Text(pDX, IDC_STATIC_TITEL2, m_strTitel2);
	DDX_Text(pDX, IDC_RICHEDIT_HASHDIFF, m_strHashDiffRE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHashdemo, CDialog)
	//{{AFX_MSG_MAP(CHashdemo)
	ON_BN_CLICKED(IDC_RADIO_MD2, OnRadioMd2)
	ON_BN_CLICKED(IDC_RADIO_MD5, OnRadioMd5)
	ON_BN_CLICKED(IDC_RADIO_SHA, OnRadioSha)
	ON_BN_CLICKED(IDC_RADIO_BIN, OnRadioBin)
	ON_BN_CLICKED(IDC_RADIO_DEC, OnRadioDec)
	ON_BN_CLICKED(IDC_RADIO_HEX, OnRadioHex)
	ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHashdemo 

BOOL CHashdemo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	LOGFONT lf={14,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,"Courier"};
	//Struktur lf wird deklariert und initialisiert

	m_font.CreateFontIndirect(&lf);
	//Objekt der Klasse CFont (m_font) wird gesetzt initialisiert

	CWnd* pStatic=GetDlgItem(IDC_EDIT_TEXT);
	CWnd* pStatic1=GetDlgItem(IDC_EDIT_ORIGHASH);
	CWnd* pStatic2=GetDlgItem(IDC_EDIT_AKTHASH);
	CWnd* pStatic3=GetDlgItem(IDC_RICHEDIT_HASHDIFF);

	pStatic->SetFont(&m_font,false);
	pStatic1->SetFont(&m_font,false);
	pStatic2->SetFont(&m_font,false);
	pStatic3->SetFont(&m_font,false);
	// Schriftart im Textfeld "aktuelle Datei", Felder in denen die Hashwerte und die Differenz angezeigt 
	// werden, "Courier" definieren

	sprintf(title, "Hash Demo   MD2-Hash");
	SetWindowText(title);
	// Der Text in der Titelleiste von Hashdemo wird gesetzt

	//CString leisteText;
	//GetWindowText(leisteText);
	//gibt den Titel des Editfenstern zurück, leiste Text würd per Referenzübergabe übergeben
		
	SetRed();
	//farbige Darstellung der Differenz 


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CHashdemo::SetHash(OctetString &hashMD2,OctetString &hashMD5,OctetString &hashSHA)
{
	m_hashMD2=hashMD2;
	m_hashMD5=hashMD5;
	m_hashSHA=hashSHA;
	//die Hashwerte der Originaldatei werden in m_hashxxx (in der Klasse Hash Demo) gespeichert

	showHashHex( m_hashMD2 );
	//Beim Aufruf des Dialogs soll der Hashwert MD2 hexadezimal angezeigt werden

	SetNewHash(hashMD2,hashMD5,hashSHA);
	//der aktuellen Hashwerte sind beim Aufruf gleich denen der Originaldatei 
	//und im Speicher gehalten,so daß bei der Betätigung der Radiobuttons nicht der 
	//Hashwert jedes Mal neu berechnet werden muß
	showNewHashHex(m_newHashMD2);
	//der aktuelle Hashwert der Funktion MD2 wird gesetzt

	SetHashDiff(m_hashMD2,m_newHashMD2);
	//die Differenz der beiden Hashwerte wird gesetzt

	
	

}

void CHashdemo::SetNewHash(OctetString &hashMD2,OctetString &hashMD5,OctetString &hashSHA)
{
	m_newHashMD2=hashMD2;
	m_newHashMD5=hashMD5;
	m_newHashSHA=hashSHA;
	//Initialisieren der Membervariablen der aktuellen Hashwerte 

	switch(m_Auswahl_HW)
	{
	case 2:
			switch(m_rb_DarstHW)
		   {
			case 1:showNewHashHex(m_newHashSHA);
				   showDiffNewHashBin(m_newHashSHA);break;
			case 0:showNewHashDec(m_newHashSHA);
				   showDiffNewHashBin(m_newHashSHA);break;
			case 2:showNewHashBin(m_newHashSHA);
				   showDiffNewHashBin(m_newHashSHA);break;
		   }
	case 1:
			switch(m_rb_DarstHW)
		   {
			case 1:showNewHashHex(m_newHashMD5);
				showDiffNewHashBin(m_newHashMD5);break;
			case 0:showNewHashDec(m_newHashMD5);
				showDiffNewHashBin(m_newHashMD5);break;
			case 2:showNewHashBin(m_newHashMD5);break;
		   }
	case 0:
			switch(m_rb_DarstHW)
		   {
			case 1:showNewHashHex(m_newHashMD2);
				showDiffNewHashBin(m_newHashMD2);break;
			case 0:showNewHashDec(m_newHashMD2);
				showDiffNewHashBin(m_newHashMD2);break;
			case 2:showNewHashBin(m_newHashMD2);
				showDiffNewHashBin(m_newHashMD2);break;
		   }
			
	}

	//Abfrage, welche Radiobuttons sind gesetzt
}


void CHashdemo::OnRadioMd2() 
{
	hashTextWithMd2();
}

void CHashdemo::hashTextWithMd2()
{
	UpdateData(true);
	
	sprintf(title, "Hash Demo   MD2-Hash");

	m_strOrigHash = "";

	if(m_rb_DarstHW==0)
	{
		OnRadioDec();
	}
	else if (m_rb_DarstHW==1)
	{
		OnRadioHex();
	}
	else
	{
		OnRadioBin();
	}

	showDiffOrigHashBin(m_hashMD2);
	SetHashDiff(m_hashMD2,m_newHashMD2);
	SetWindowText(title);
	//Titel des Dialogs wird gesetzt

	UpdateData(false);
	
}


void CHashdemo::OnRadioMd5() 
{
	hashTextWithMd5();
}

void CHashdemo::hashTextWithMd5()
{
	UpdateData(true);

	sprintf(title, "Hash Demo   MD5-Hash");

	if(m_rb_DarstHW==0)
	{
		OnRadioDec();
	}
	else if (m_rb_DarstHW==1)
	{
		OnRadioHex();
	}
	else
	{
		OnRadioBin();
	}

	showDiffOrigHashBin(m_hashMD5);
	SetHashDiff(m_hashMD5,m_newHashMD5);

	SetWindowText(title);
	UpdateData(false);
}


void CHashdemo::OnRadioSha() 
{
	UpdateData(true);
	hashTextWithSha();
	UpdateData(false);
}

void CHashdemo::hashTextWithSha()
{	
	sprintf(title, "Hash Demo   SHA-Hash");

	if(m_rb_DarstHW==0)
	{
		OnRadioDec();
	}
	else if (m_rb_DarstHW==1)
	{
		OnRadioHex();
	}
	else
	{
		OnRadioBin();
	}


	showDiffOrigHashBin(m_hashSHA);
	showDiffNewHashBin(m_hashSHA);

	SetHashDiff(m_hashSHA,m_newHashSHA);

	SetWindowText(title);

}

void CHashdemo::OnRadioHex() 
{
	UpdateData(true);
    switch (m_Auswahl_HW) 
	{	
		case 0: showHashHex(m_hashMD2);
				showNewHashHex(m_newHashMD2);
			break;
		case 1: showHashHex(m_hashMD5);
				showNewHashHex(m_newHashMD5);
			break;
		case 2: showHashHex(m_hashSHA);
				showNewHashHex(m_newHashSHA);
			break;
	}
	UpdateData(false);
}



void CHashdemo::showHashHex(OctetString &hash)
{
	m_strOrigHash="";

	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2;
			if (( x % 16 ) < 10 ) c2 = '0' + (x % 16); else c2 = 'A' + (x % 16) -10;
			x /= 16;
			if ( x < 10 ) c1 = '0' + x; else c1 = 'A' + x -10; 
			m_strOrigHash += c1;
			m_strOrigHash += c2;
			if (i < hash.noctets+1) m_strOrigHash += ' ';
		}

}


void CHashdemo::OnRadioDec() 
{
	UpdateData(true);
	switch (m_Auswahl_HW) 
	{	
		case 0: showHashDec(m_hashMD2);
				showNewHashDec(m_newHashMD2);
			break;
		case 1: showHashDec(m_hashMD5);
				showNewHashDec(m_newHashMD5);
			break;
		case 2: showHashDec(m_hashSHA);
				showNewHashDec(m_newHashSHA);
			break;
	}
	UpdateData(false);
}


void CHashdemo::showHashDec(OctetString &hash)
{

	m_strOrigHash="";
	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2,c3;
			c3 = '0' + (x % 10);
			x /= 10;
			c2 = '0' + (x % 10);
			x /= 10;
			c1 = '0' + x;
			m_strOrigHash += c1;
			m_strOrigHash += c2;
			m_strOrigHash += c3;
			if (i < hash.noctets+1) m_strOrigHash += ' ';
		}

}


void CHashdemo::OnRadioBin() 
{
	UpdateData(true);
	switch (m_Auswahl_HW) 
	{	
		case 0: showHashBin(m_hashMD2);
				showNewHashBin(m_newHashMD2);

			break;
		case 1: showHashBin(m_hashMD5);
				showNewHashBin(m_newHashMD5);

			break;
		case 2: showHashBin(m_hashSHA);
				showNewHashBin(m_newHashSHA);

			break;
	}
	UpdateData(false);
	
}

void CHashdemo::showHashBin(OctetString &hash)
{
	CString txt1="#";
	m_strOrigHash="";
	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2,c3,c4,c5,c6,c7,c8;
			c8 = '0' + (x % 2);
			x /= 2;
			c7 = '0' + (x % 2);
			x /= 2;
			c6 = '0' + (x % 2);
			x /= 2;
			c5 = '0' + (x % 2);
			x /= 2;
			c4 = '0' + (x % 2);
			x /= 2;
			c3 = '0' + (x % 2);
			x /= 2;
			c2 = '0' + (x % 2);
			x /= 2;
			c1 = '0' + x;
			m_strOrigHash += c1;
			m_strOrigHash += c2;
			m_strOrigHash += c3;
			m_strOrigHash += c4;
			m_strOrigHash += c5;
			m_strOrigHash += c6;
			m_strOrigHash += c7;
			m_strOrigHash += c8;
			m_strOrigHash += txt1;
			//if (i < hash.noctets+1) m_strOrigHash += ' ';
		}

}




void CHashdemo::OnChangeEditText() 
{
	UpdateData(true);
	m_strTitel2=" ";
	/***************************************************
	MAX_LAENGE als extern deklarieren!!!!
	***************************************************/
	long MAX_LAENGE_STRTEXT=16000;
    //m_strNewHash
	m_Messg=new OctetString;

	LPTSTR m_LPTText = new TCHAR[m_strText.GetLength()+1];
	_tcscpy(m_LPTText, m_strText);
	//Umkonvertieren des Inhalts vom CString m_strText in ein LPTSTR (m_LPTText)

	m_Messg->octets=m_LPTText;
	int strlaenge=m_strText.GetLength ();
	m_Messg->noctets=strlaenge;

	/*************************************
	bearbeiten
	*************************************/
	if(strlaenge>MAX_LAENGE_STRTEXT)
	{
		MessageBox("Textlänge zu groß!");
	}


	m_sndHashMD2.noctets=0;
	m_sndHashMD5.noctets=0;
	m_sndHashSHA.noctets=0;
	
	theApp.SecudeLib.sec_hash_all(m_Messg,&m_sndHashMD2,theApp.SecudeLib.md2_aid,NULL);
	theApp.SecudeLib.sec_hash_all(m_Messg,&m_sndHashMD5,theApp.SecudeLib.md5_aid,NULL);
	theApp.SecudeLib.sec_hash_all(m_Messg,&m_sndHashSHA,theApp.SecudeLib.sha_aid,NULL);

	SetNewHash(m_sndHashMD2,m_sndHashMD5,m_sndHashSHA);
	
	
	if(m_Auswahl_HW==0)
	{
		SetHashDiff(m_hashMD2,m_newHashMD2);
	}
	else if(m_Auswahl_HW==1)
	{
		SetHashDiff(m_hashMD5,m_newHashMD5);
	}
	else
	{
		SetHashDiff(m_hashSHA,m_newHashSHA);
	}


	delete m_Messg;
	delete m_LPTText;
	UpdateData(false);	
		SetRed();

}


/*************************************************************************************************************/

void CHashdemo::showNewHashHex(OctetString &hash)
{
		m_strNewHash="";

	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2;
			if (( x % 16 ) < 10 ) c2 = '0' + (x % 16); else c2 = 'A' + (x % 16) -10;
			x /= 16;
			if ( x < 10 ) c1 = '0' + x; else c1 = 'A' + x -10; 
			m_strNewHash += c1;
			m_strNewHash += c2;
			if (i < hash.noctets+1) m_strNewHash += ' ';
		}
}

void CHashdemo::showNewHashDec(OctetString &hash)
{

	m_strNewHash="";
	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2,c3;
			c3 = '0' + (x % 10);
			x /= 10;
			c2 = '0' + (x % 10);
			x /= 10;
			c1 = '0' + x;
			m_strNewHash += c1;
			m_strNewHash += c2;
			m_strNewHash += c3;
			if (i < hash.noctets+1) m_strNewHash += ' ';
		}

}
void CHashdemo::showNewHashBin(OctetString &hash)
{	CString txt="#";
	m_strNewHash="";
	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2,c3,c4,c5,c6,c7,c8;
			c8 = '0' + (x % 2);
			x /= 2;
			c7 = '0' + (x % 2);
			x /= 2;
			c6 = '0' + (x % 2);
			x /= 2;
			c5 = '0' + (x % 2);
			x /= 2;
			c4 = '0' + (x % 2);
			x /= 2;
			c3 = '0' + (x % 2);
			x /= 2;
			c2 = '0' + (x % 2);
			x /= 2;
			c1 = '0' + x;
			m_strNewHash += c1;
			m_strNewHash += c2;
			m_strNewHash += c3;
			m_strNewHash += c4;
			m_strNewHash += c5;
			m_strNewHash += c6;
			m_strNewHash += c7;
			m_strNewHash += c8;
			m_strNewHash += txt;
			//if (i < hash.noctets+1) m_strNewHash += ' ';
		}
		

}



void CHashdemo::SetTitle(char *titel)
{

}


void CHashdemo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	/*////////////////////////////////////////////////7
	CClientDC dc(this);
	BITMAP bm;
	m_bmp1.GetObject(sizeof(bm),&bm);
	CDC SpeicherDC;
	SpeicherDC.CreateCompatibleDC(&dc);
	SpeicherDC.SelectObject(&m_bmp1);
	CRect rect;
	GetClientRect(&rect);
	dc.SetStretchBltMode(HALFTONE);
	dc.StretchBlt(0,0,rect.right,rect.bottom,&SpeicherDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	/////////////////////////////////////////////////////
	CDialog::OnPaint();	
	// Kein Aufruf von CDialog::OnPaint() für Zeichnungsnachrichten*/
	
}


void CHashdemo::showDiffOrigHashBin(OctetString &hash)
{
	
	m_strOrigHashBin="";
	CString txt2="#";
	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2,c3,c4,c5,c6,c7,c8;
			c8 = '0' + (x % 2);
			x /= 2;
			c7 = '0' + (x % 2);
			x /= 2;
			c6 = '0' + (x % 2);
			x /= 2;
			c5 = '0' + (x % 2);
			x /= 2;
			c4 = '0' + (x % 2);
			x /= 2;
			c3 = '0' + (x % 2);
			x /= 2;
			c2 = '0' + (x % 2);
			x /= 2;
			c1 = '0' + x;
			m_strOrigHashBin += c1;
			m_strOrigHashBin += c2;
			m_strOrigHashBin += c3;
			m_strOrigHashBin += c4;
			m_strOrigHashBin += c5;
			m_strOrigHashBin += c6;
			m_strOrigHashBin += c7;
			m_strOrigHashBin += c8;
			m_strOrigHashBin += txt2;
			//if (i < hash.noctets+1) m_strOrigHash += ' ';
		}
		

}

void CHashdemo::showDiffNewHashBin(OctetString &hash)
{
		m_strNewHashBin="";
		CString txt3="#";
	for (unsigned int i=0; i<hash.noctets; i++)
		{
			unsigned char x = hash.octets[i];
			char c1, c2,c3,c4,c5,c6,c7,c8;
			c8 = '0' + (x % 2);
			x /= 2;
			c7 = '0' + (x % 2);
			x /= 2;
			c6 = '0' + (x % 2);
			x /= 2;
			c5 = '0' + (x % 2);
			x /= 2;
			c4 = '0' + (x % 2);
			x /= 2;
			c3 = '0' + (x % 2);
			x /= 2;
			c2 = '0' + (x % 2);
			x /= 2;
			c1 = '0' + x;
			m_strNewHashBin += c1;
			m_strNewHashBin += c2;
			m_strNewHashBin += c3;
			m_strNewHashBin += c4;
			m_strNewHashBin += c5;
			m_strNewHashBin += c6;
			m_strNewHashBin += c7;
			m_strNewHashBin += c8;
			m_strNewHashBin += txt3;
			//if (i < hash.noctets+1) m_strOrigHash += ' ';
		}
}

void CHashdemo::SetHashDiff(OctetString &hash1, OctetString &hash2)
{
	

	showDiffNewHashBin(hash2);
	showDiffOrigHashBin(hash1);
	m_strHashDiffRE="";
	int iLaengeDerHW;
	iLaengeDerHW=m_strNewHashBin.GetLength();
	
	for (int i=0;i<iLaengeDerHW;i++)
	{
		if (m_strNewHashBin[i]==m_strOrigHashBin[i]&&m_strNewHashBin[i]!='#')
		{
			m_strHashDiffRE+="0";
		}
		else if(m_strNewHashBin[i]=='#')
		{
			m_strHashDiffRE+="#";
		}
		else
		{
			m_strHashDiffRE+="1";
		}
	}
	

	
}

void CHashdemo::SetRed()
{
	m_ctrlHashDiff.HideSelection( true, true );
	CHARFORMAT farbeZahl;
	farbeZahl.cbSize=sizeof (CHARFORMAT);
	farbeZahl.dwMask=CFM_COLOR;
	farbeZahl.dwEffects = 0;
	
	static int c=0;

	int laenge=144; 
	m_strHashDiffRE.GetLength();

	int x=0;

	CString b;
	if(m_ctrlHashDiff.m_hWnd!=0)
	{	
		for( x=0;x<laenge;x++)
		{
			if(m_strHashDiffRE[x]=='1')
			{	
				farbeZahl.crTextColor=RGB(255,0,0);
				m_ctrlHashDiff.SetSel(x,x+1);
				m_ctrlHashDiff.SetSelectionCharFormat(farbeZahl);	
						
			}
			
			else
			{
				farbeZahl.crTextColor=RGB(0,0,0);
				m_ctrlHashDiff.SetSel(x,x+1);
				m_ctrlHashDiff.SetSelectionCharFormat(farbeZahl);	
		
			}
		
		}
		
		

	}

}
