// Hashdemo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHashDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHashDemo 


CDlgHashDemo::CDlgHashDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHashDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHashDemo)
	m_rb_DarstHW = 1;
	m_Auswahl_HW = 0;
	m_strOrigHash = _T("");
	m_strNewHash = _T("");
	m_strTitel = _T("");
	m_strTitel2 = _T("");
	m_strHashDiffRE = _T("");
	//}}AFX_DATA_INIT
}


void CDlgHashDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHashDemo)
	DDX_Control(pDX, IDC_EDIT_TEXT, m_ctrlText);
	DDX_Control(pDX, IDC_RICHEDIT_HASHDIFF, m_ctrlHashDiff);
	DDX_Control(pDX, IDC_EDIT_ORIGHASH, m_ctrlOrigHash);
	DDX_Control(pDX, IDC_EDIT_AKTHASH, m_ctrlNewHash);
	DDX_Radio(pDX, IDC_RADIO_DEC, m_rb_DarstHW);
	DDX_Radio(pDX, IDC_RADIO_MD2, m_Auswahl_HW);
	DDX_Text(pDX, IDC_EDIT_ORIGHASH, m_strOrigHash);
	DDX_Text(pDX, IDC_EDIT_AKTHASH, m_strNewHash);
	DDX_Text(pDX, IDC_STATIC_TITEL, m_strTitel);
	DDX_Text(pDX, IDC_STATIC_TITEL2, m_strTitel2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHashDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgHashDemo)
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
// Behandlungsroutinen für Nachrichten CDlgHashDemo 

BOOL CDlgHashDemo::OnInitDialog() 
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
		
	m_ctrlText.SetWindowText(m_strText);
	OnChangeEditText();
	// SetRed();
	//farbige Darstellung der Differenz 


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgHashDemo::SetHash(OctetString &hashMD2,OctetString &hashMD5,OctetString &hashSHA)
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

void CDlgHashDemo::SetNewHash(OctetString &hashMD2,OctetString &hashMD5,OctetString &hashSHA)
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
}


void CDlgHashDemo::OnRadioMd2() 
{
	hashTextWithMd2();
}

void CDlgHashDemo::hashTextWithMd2()
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


void CDlgHashDemo::OnRadioMd5() 
{
	hashTextWithMd5();
}

void CDlgHashDemo::hashTextWithMd5()
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


void CDlgHashDemo::OnRadioSha() 
{
	UpdateData(true);
	hashTextWithSha();
	UpdateData(false);
}

void CDlgHashDemo::hashTextWithSha()
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

void CDlgHashDemo::OnRadioHex() 
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



void CDlgHashDemo::showHashHex(OctetString &hash)
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


void CDlgHashDemo::OnRadioDec() 
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


void CDlgHashDemo::showHashDec(OctetString &hash)
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


void CDlgHashDemo::OnRadioBin() 
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

void CDlgHashDemo::showHashBin(OctetString &hash)
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




void CDlgHashDemo::OnChangeEditText() 
{
	UpdateData(true);
	m_strTitel2=" ";
	/***************************************************
	MAX_LAENGE als extern deklarieren!!!!
	***************************************************/
	long MAX_LAENGE_STRTEXT=16000;
    //m_strNewHash
	CString text;
	m_ctrlText.GetWindowText(text);
	m_Messg=new OctetString;

	m_Messg->octets = (LPTSTR)(LPCTSTR)text;
	int strlaenge = text.GetLength();
	m_Messg->noctets = strlaenge;

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
	UpdateData(false);	
	SetRed();

}


/*************************************************************************************************************/

void CDlgHashDemo::showNewHashHex(OctetString &hash)
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

void CDlgHashDemo::showNewHashDec(OctetString &hash)
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
void CDlgHashDemo::showNewHashBin(OctetString &hash)
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



void CDlgHashDemo::SetTitle(char *titel)
{

}


void CDlgHashDemo::OnPaint() 
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


void CDlgHashDemo::showDiffOrigHashBin(OctetString &hash)
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

void CDlgHashDemo::showDiffNewHashBin(OctetString &hash)
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

void CDlgHashDemo::SetHashDiff(OctetString &hash1, OctetString &hash2)
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


static DWORD CALLBACK EditStreamCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, 
                                                              LONG *pcb)
{
      CString *pstr = (CString *)dwCookie;

      if( pstr->GetLength() < cb )
      {
              *pcb = pstr->GetLength();
              memcpy(pbBuff, (LPCSTR)*pstr, *pcb );
              pstr->Empty();
      }
      else
      {
              *pcb = cb;
              memcpy(pbBuff, (LPCSTR)*pstr, *pcb );
              *pstr = pstr->Right( pstr->GetLength() - cb );
      }
      return 0;
}

void CDlgHashDemo::SetRed()
{

	CString rtfPrefix, rtfPostfix;
	rtfPrefix = "{\\rtf1\\ansi\\deff0\\deftab720{\\fonttbl{\\f0\\froman "
		      "Courier New;}}\n{\\colortbl;\\red0\\green0\\blue0;\\red255\\green0\\blue0;}\n"
			  "\\deflang1033\\pard\\tx360\\tx720\\tx1080\\tx1440\\tx1800"
			  "\\tx2160\\tx2520\\tx2880\\tx3240\\tx3600\\tx3960\\tx4320"
			  "\\tx4680\\tx5040\\tx5400\\tx5760\\tx6120"
			  "\\tx6480\\plain\\f3\\fs20 ";
    rtfPostfix = "\n\\par }";


	m_ctrlHashDiff.ShowWindow(SW_HIDE);
	m_ctrlHashDiff.SetSel(0,-1);
	m_ctrlHashDiff.ReplaceSel("");

	static int c=0;

	int laenge=144; 
	m_strHashDiffRE.GetLength();

	int x=0;

	CString b = "";
	if(m_ctrlHashDiff.m_hWnd!=0)
	{	
		for( x=0;x<laenge;x++)
		{
			if(m_strHashDiffRE[x]=='1')
			{	
				b += "{\\cf2 1}";
			}
			else
			{
				b += m_strHashDiffRE[x];
			}
		
		}
	}

	m_ctrlHashDiff.ShowWindow(SW_SHOW);


    // The rtfString contains the word Bold in bold font.
    CString rtfString = rtfPrefix + b + rtfPostfix;
    EDITSTREAM es = {(DWORD)&rtfString, 0, EditStreamCallBack};

	// richEd is the rich edit control
	m_ctrlHashDiff.StreamIn(SF_RTF | SFF_SELECTION, es);
}
