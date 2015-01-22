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

// Hashdemo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgHashDemo.h"
#include "HashingOperations.h"
#include "CrypToolTools.h"

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
	m_strOrigHash = _T("");
	m_strNewHash = _T("");
	//}}AFX_DATA_INIT

	m_dataOrig.octets = 0;
	m_strHashDiffRE = _T("");
	m_strTitle = _T("");
}

CDlgHashDemo::~CDlgHashDemo()
{
	if (m_dataOrig.octets)
		delete []m_dataOrig.octets;
}

void CDlgHashDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHashDemo)
	DDX_Control(pDX, IDC_COMBO_SELECT_HASH_FUNCTION, m_comboCtrlSelectHashFunction);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_ctrlText);
	DDX_Control(pDX, IDC_RICHEDIT_HASHDIFF, m_ctrlHashDiff);
	DDX_Radio(pDX, IDC_RADIO_DEC, m_rb_DarstHW);
	DDX_Text(pDX, IDC_EDIT_ORIGHASH, m_strOrigHash);
	DDX_Text(pDX, IDC_EDIT_AKTHASH, m_strNewHash);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHashDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgHashDemo)
	ON_BN_CLICKED(IDC_RADIO_BIN, OnRadioBin)
	ON_BN_CLICKED(IDC_RADIO_DEC, OnRadioDec)
	ON_BN_CLICKED(IDC_RADIO_HEX, OnRadioHex)
	ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
	ON_CBN_SELENDOK(IDC_COMBO_SELECT_HASH_FUNCTION, OnSelendokComboSelectHashFunction)
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

	CString title;
	title.LoadString(IDS_HASH_DEMO_TITLE_MD2);
	SetWindowText((LPCTSTR)title);
	// Der Text in der Titelleiste von Hashdemo wird gesetzt

	// Texte für Auswahl der Hashfunktion werden aus Ressourcen geholt
	m_strHashFunctionMD2.LoadString(IDS_HASHDEMO_STRING_MD2);
	m_strHashFunctionMD4.LoadString(IDS_HASHDEMO_STRING_MD4);
	m_strHashFunctionMD5.LoadString(IDS_HASHDEMO_STRING_MD5);
	m_strHashFunctionSHA.LoadString(IDS_HASHDEMO_STRING_SHA);
	m_strHashFunctionSHA1.LoadString(IDS_HASHDEMO_STRING_SHA1);
	m_strHashFunctionSHA256.LoadString(IDS_HASHDEMO_STRING_SHA256);
	m_strHashFunctionSHA512.LoadString(IDS_HASHDEMO_STRING_SHA512);
	m_strHashFunctionRIPEMD160.LoadString(IDS_HASHDEMO_STRING_RIPEMD160);
	// Die Combobox für die Auswahl der Hashfunktion wird gesetzt
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionMD2);
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionMD4);
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionMD5);
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionSHA);
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionSHA1);
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionSHA256);
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionSHA512);
	m_comboCtrlSelectHashFunction.AddString(m_strHashFunctionRIPEMD160);

	m_comboCtrlSelectHashFunction.SelectString(-1, m_strHashFunctionMD2);

	m_ctrlText.SetWindowText(m_strText);
	OnSelendokComboSelectHashFunction();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CDlgHashDemo::OnRadioHex() 
{
	UpdateData(true);
	showHashHex(m_hash);
	showNewHashHex(m_newHash);
 	UpdateData(false);
}

void CDlgHashDemo::OnRadioDec() 
{
	UpdateData(true);
	showHashDec(m_hash);
	showNewHashDec(m_newHash);
 	UpdateData(false);
}

void CDlgHashDemo::OnRadioBin() 
{
	UpdateData(true);
	showHashBin(m_hash);
	showNewHashBin(m_newHash);
	UpdateData(false);
}


void CDlgHashDemo::OnChangeEditText() 
{
	UpdateData(true);
	/***************************************************
	MAX_LAENGE als extern deklarieren!!!!
	***************************************************/
    //m_strNewHash

	CString text;
	m_ctrlText.GetWindowText(text);

	OctetString *m_Messg;
	m_Messg=new OctetString;
	m_Messg->octets = (LPTSTR)(LPCTSTR)text;
	int strlaenge = text.GetLength();
	m_Messg->noctets = strlaenge;


	ComputeHash(m_Messg, &m_newHash);

	switch (m_rb_DarstHW) {
		case 1: showNewHashHex(m_newHash); break;
		case 0: showNewHashDec(m_newHash); break;
		case 2: showNewHashBin(m_newHash); break;
	}

	SetHashDiff( m_hash, m_newHash );

	delete m_Messg;
	UpdateData(false);	
	SetRed();

}


/*************************************************************************************************************/

void CDlgHashDemo::showHashHex(OctetString &hash)
{
	m_strOrigHash ="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strOrigHash, hash.octets[i], 16, (i < hash.noctets+1) ? ' ' : '\0');
}


void CDlgHashDemo::showHashDec(OctetString &hash)
{
	m_strOrigHash ="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strOrigHash, hash.octets[i], 10, (i < hash.noctets+1) ? ' ' : '\0');
}

void CDlgHashDemo::showHashBin(OctetString &hash)
{
	m_strOrigHash ="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strOrigHash, hash.octets[i], 2, (i < hash.noctets+1) ? '#' : '\0');
}

void CDlgHashDemo::showNewHashHex(OctetString &hash)
{
	m_strNewHash ="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strNewHash, hash.octets[i], 16, (i < hash.noctets+1) ? ' ' : '\0');
}

void CDlgHashDemo::showNewHashDec(OctetString &hash)
{
	m_strNewHash ="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strNewHash, hash.octets[i], 10, (i < hash.noctets+1) ? ' ' : '\0');
}

void CDlgHashDemo::showNewHashBin(OctetString &hash)
{
	
	m_strNewHash="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strNewHash, hash.octets[i], 2, '#');	
}

void CDlgHashDemo::showDiffOrigHashBin(OctetString &hash)
{
	m_strOrigHashBin="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strOrigHashBin, hash.octets[i], 2, '#');
}

void CDlgHashDemo::showDiffNewHashBin(OctetString &hash)
{
	m_strNewHashBin="";
	for (unsigned int i=0; i<hash.noctets; i++)
		getNextBlock(m_strNewHashBin, hash.octets[i], 2, '#');
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

	int laenge = m_strHashDiffRE.GetLength();

	int x=0;

	// offset:	Speichert das Offset der längsten unveränderten Bitfolge
	// length:	Speichert die Länge der längsten unveränderten Bitfolge
	int offset=0;
	int length=0;
	// o:		Speichert das Offset der aktuellen Bitfolge
	// l:		Speichert die Länge der aktuellen Bitfolge
	int o=0;
	int l=0;
	// y:		Gibt die Anzahl der gezählten Bits wieder, d.h. lässt die automatisch
	//			eingefügten Trennzeichen (#) zwischen den 8er-Bitblöcken aus
	int y=0;

	CString b = "";
	int zero = 0, one = 0;
	if(m_ctrlHashDiff.m_hWnd!=0)
	{	
		for( x=0;x<laenge;x++)
		{
			// ...hier unterscheidet sich ein Bit.
			if(m_strHashDiffRE[x]=='1')
			{	
				one++;
				b += "{\\cf2 1}";

				// Variablen sollen ausschliesslich dann neu gesetzt werden, wenn
				// es sich NICHT um ein Trennzeichen (#) handelt.
				if( (x+1)%9 != 0)
				{
					l = 0;
					y++;
				}
			}
			// ...hier ist das entsprechende Bit gleich.
			else
			{
				if(m_strHashDiffRE[x]=='0')
					zero++;
				b += m_strHashDiffRE[x];

				// Variablen sollen ausschliesslich dann neu gesetzt werden, wenn
				// es sich NICHT um ein Trennzeichen (#) handelt.
				if( (x+1)%9 != 0)
				{

					if(l==0) o = y;
					l++;
					if(l>length)
					{
						length = l;
						offset = o;
					}
					y++;
				}
			}
		}

		b += "\n\\par ";
		CString ratio;
		CString percentage = createStringNumberWithDigitGrouping((100.0*one)/(one+zero));
		ratio.Format(IDS_HASH_DEMO_PERCENT, percentage, one, (one+zero));
		b += ratio;
				
		CString sequence;
		sequence.Format(IDS_HASH_DEMO_SEQUENCE, offset, length);

		// Neue Zeile beginnen und Angaben über Offset/Länge ausgeben
		b += "\n\\par ";
		b += sequence;
	}

	m_ctrlHashDiff.ShowWindow(SW_SHOW);


    // The rtfString contains the word Bold in bold font.
    CString rtfString = rtfPrefix + b + rtfPostfix;
    EDITSTREAM es = {(DWORD)&rtfString, 0, EditStreamCallBack};

	// richEd is the rich edit control
	m_ctrlHashDiff.StreamIn(SF_RTF | SFF_SELECTION, es);
}


void CDlgHashDemo::getNextBlock(CString &dispByte, unsigned char inByte, unsigned short numberBase, char seperator)
{
	char digit[8];
	unsigned short n = 255, modulo;
	int i;
	for (i=0; n>0; i++)
	{
		n/=numberBase;
		modulo = inByte % numberBase;
		inByte /= numberBase;
		digit[i] = (modulo >= 10) ? modulo-10 + 'A' : modulo + '0';
	}
	while (i>0)	dispByte += digit[--i];
	if (seperator) dispByte += seperator;
}


unsigned long CDlgHashDemo::loadData( const char *infile, const char *title, unsigned long filesize, unsigned long max_filesize )
{

	m_strTitle = title;

	m_dataOrig.noctets = filesize;
	m_dataOrig.octets = new char [filesize+1];

	CFile f( infile, CFile::modeRead );
	f.Read( (void *)m_dataOrig.octets, filesize );
	f.Close();
	m_dataOrig.octets[filesize] = '\0';

	// flomar, March 2013: in case the inserted data contains null bytes, the user may be 
	// confused because everything after the first null byte is implicitly removed as we're 
	// internally working with CStrings (see below)-- integrating a control which is able 
	// to display null bytes (i.e. Scintilla) into the dialog is not an easy task, thus we 
	// go with a warning message here to at least make sure the user knows why the hash 
	// values for original and current document differ right from the get go
	for(int i=0; i<filesize; i++) {
		const char currentByte = m_dataOrig.octets[i];
		if(currentByte == 0) {
			LoadString(AfxGetInstanceHandle(), IDS_STRING_HASH_DEMO_SOURCE_DOCUMENT_CONTAINS_NULL_BYTE, pc_str, STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str, MB_ICONEXCLAMATION);
		}
	}

	m_strText = CString((char*)m_dataOrig.octets);

	return (unsigned long)m_strText.GetLength();
}

void CDlgHashDemo::OnSelendokComboSelectHashFunction() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	ComputeHash(&m_dataOrig, &m_hash);
	UpdateData(true);
	switch (m_rb_DarstHW) {
		case 1: showHashHex(m_hash); break;
		case 0: showHashDec(m_hash); break;
		case 2: showHashBin(m_hash); break;
	}
	UpdateData(false);
	OnChangeEditText();
	
	char strSelectedHash[21];
	m_comboCtrlSelectHashFunction.GetWindowText(strSelectedHash, 20);
	CString title;
	title.Format(IDS_STRING_Hashdemo_orighash,strSelectedHash);
	title += m_strTitle;
	this->SetWindowText(title);
}

void CDlgHashDemo::ComputeHash(OctetString *data, OctetString *hashValue)
{
	char strSelectedHash[256+1];
	m_comboCtrlSelectHashFunction.GetWindowText(strSelectedHash, 256);
	hashValue->noctets = 0;

	if (!strcmp(strSelectedHash, m_strHashFunctionMD2) )
	{
		theApp.SecudeLib.sec_hash_all(data,hashValue,theApp.SecudeLib.md2_aid,NULL);
	}
	if (!strcmp(strSelectedHash, m_strHashFunctionMD4) )
	{
		theApp.SecudeLib.sec_hash_all(data,hashValue,theApp.SecudeLib.md4_aid,NULL);
	}
	if (!strcmp(strSelectedHash, m_strHashFunctionMD5) )
	{
		theApp.SecudeLib.sec_hash_all(data,hashValue,theApp.SecudeLib.md5_aid,NULL);
	}
	if (!strcmp(strSelectedHash, m_strHashFunctionSHA) )
	{
		theApp.SecudeLib.sec_hash_all(data,hashValue,theApp.SecudeLib.sha_aid,NULL);
	}
	if (!strcmp(strSelectedHash, m_strHashFunctionSHA1) )
	{
		theApp.SecudeLib.sec_hash_all(data,hashValue,theApp.SecudeLib.sha1_aid,NULL);
	}
	if (!strcmp(strSelectedHash, m_strHashFunctionSHA256) )
	{
		// flomar, 04/14/2010
		// contrary to the approach above, we use OpenSSL (see HashingOperations) for SHA-256
		HashingOperations hashingOperations(6);
		hashingOperations.DoHash(data->octets, data->noctets, hashValue->octets);
		hashValue->noctets = 32;
	}
	if (!strcmp(strSelectedHash, m_strHashFunctionSHA512) )
	{
		// flomar, 04/14/2010
		// contrary to the approach above, we use OpenSSL (see HashingOperations) for SHA-512
		HashingOperations hashingOperations(7);
		hashingOperations.DoHash(data->octets, data->noctets, hashValue->octets);
		hashValue->noctets = 64;
	}
	if (!strcmp(strSelectedHash, m_strHashFunctionRIPEMD160) )
	{
		theApp.SecudeLib.sec_hash_all(data,hashValue,theApp.SecudeLib.ripemd160_aid,NULL);
	}
}