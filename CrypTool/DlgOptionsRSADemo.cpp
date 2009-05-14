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

// DlgRSAwithSmallPrimesOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsRSADemo.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsRSADemo 



CDlgOptionsRSADemo::CDlgOptionsRSADemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsRSADemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsRSADemo)
	m_alphabet = _T(" ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_numberBasis = 0;
	m_TextOptions = 0;
	m_RSAVariant  = 0;
	m_BlockLength = -1;
	m_MaxBlockLength = _T("");
	m_codingMethod = 0;
	m_AnzahlZeichen = _T("");
	//}}AFX_DATA_INIT
}


void CDlgOptionsRSADemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsRSADemo)
	DDX_Control(pDX, IDC_RADIO1, m_RSAVariantCtrl);
	DDX_Control(pDX, IDC_RADIO10, m_CodingControl);
	DDX_Control(pDX, IDC_EDIT2, m_BlockLengthCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_alphabetControl);
	DDX_Text(pDX, IDC_EDIT1, m_alphabet);
	DDX_Radio(pDX, IDC_RADIO3, m_numberBasis);
	DDX_Radio(pDX, IDC_RADIO1, m_TextOptions);
	DDX_Radio(pDX, IDC_RADIO7, m_RSAVariant);
	DDX_Text(pDX, IDC_EDIT2, m_BlockLength);
	DDX_Text(pDX, IDC_EDIT3, m_MaxBlockLength);
	DDX_Radio(pDX, IDC_RADIO9, m_codingMethod);
	DDX_Text(pDX, IDC_EDIT_ANZAHL_ZEICHEN, m_AnzahlZeichen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsRSADemo, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsRSADemo)
	ON_BN_CLICKED(IDC_RADIO7, OnSelectRSA)
	ON_BN_CLICKED(IDC_RADIO8, OnSelectDialougeOfSisters)
	ON_EN_UPDATE(IDC_EDIT1, OnChangeAlphabet)
	ON_BN_CLICKED(IDC_RADIO1, OnSelectASCII)
	ON_BN_CLICKED(IDC_RADIO2, OnSelectAlphabet)
	ON_BN_CLICKED(IDC_RADIO10, OnCodingNumberSystem)
	ON_BN_CLICKED(IDC_RADIO9, OnCodingBAdic)
	ON_BN_CLICKED(IDC_RADIO3, OnBase10)
	ON_BN_CLICKED(IDC_RADIO4, OnBase2)
	ON_BN_CLICKED(IDC_RADIO5, OnBase8)
	ON_BN_CLICKED(IDC_RADIO6, OnBase16)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsRSADemo 

BOOL CDlgOptionsRSADemo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	{ // Für Cancel Button alte Werte retten
		s_alphabet        = m_alphabet;
		s_numberBasis     = m_numberBasis;
		s_TextOptions     = m_TextOptions;
		s_RSAVariant      = m_RSAVariant;
		s_BlockLength     = m_BlockLength;
		s_MaxBlockLength  = m_MaxBlockLength;
		s_codingMethod    = m_codingMethod;
		s_AnzahlZeichen   = m_AnzahlZeichen;
	}

	// TODO: Zusätzliche Initialisierung hier einfügen
	unsigned long blockLength = GetBlockLength();
	UpdateData(true);
	if ( m_BlockLength <= 0 || m_BlockLength > blockLength )
		m_BlockLength = blockLength;
	if ( !m_RSAVariant ) 
	{
		if ( !m_TextOptions )
		{
			m_alphabetControl.EnableWindow( FALSE );
			m_CodingControl.EnableWindow( TRUE );
		}
		else
		{
			m_alphabetControl.EnableWindow( TRUE );
			m_CodingControl.EnableWindow( TRUE );
		}		
	}
	else
	{
		m_RSAVariantCtrl.EnableWindow( FALSE );	
		m_alphabetControl.EnableWindow( TRUE );
		m_CodingControl.EnableWindow( FALSE );
	}
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgOptionsRSADemo::MsgBlockLength()
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_RSATUT_MAXBLOCKLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	char line[256];
	unsigned int  bl = GetBlockLength();
	sprintf( line, pc_str, bl );
	m_MaxBlockLength = line;
	if ( !m_BlockLength ) m_BlockLength = 1;
	if ( bl < m_BlockLength ) m_BlockLength = bl;
}



void CDlgOptionsRSADemo::OnChangeAlphabet() 
{
	UpdateData(true);
	int i,j,len =m_alphabet.GetLength();
	int sels, sele;
	m_alphabetControl.GetSel(sels, sele);

	for ( i = 1; i<len; i++ )
	{
		for ( j=0; j<i; j++ )
		{
			if ( m_alphabet[j] == m_alphabet[i] )
			{
				if (i<sels) sels--;
				if (i<sele) sele--;
				m_alphabet.Delete(i);
				len--; i--; break;
			}
		}
	}
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
	m_alphabetControl.SetSel(sels, sele);

}

void CDlgOptionsRSADemo::ReInitBlockLength(BOOL setMaxBlockLength)
{
	unsigned long blockLength = GetBlockLength();
	if (setMaxBlockLength || m_BlockLength <= 0 || m_BlockLength > blockLength )
		m_BlockLength = blockLength;
}

void CDlgOptionsRSADemo::OnSelectRSA() 
{
	UpdateData(true);	
	m_BlockLengthCtrl.EnableWindow( TRUE );
	m_RSAVariantCtrl.EnableWindow( TRUE );
	m_CodingControl.EnableWindow( TRUE );
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
}

void CDlgOptionsRSADemo::OnSelectDialougeOfSisters() 
{
	UpdateData(true);
	m_alphabetControl.EnableWindow( TRUE );
	m_BlockLengthCtrl.EnableWindow( FALSE );
	m_TextOptions = 1;
	m_codingMethod = 0;
	UpdateData(false);
	MsgBlockLength();
	MsgAnzahlZeichen();
	OnSelectAlphabet();
	m_RSAVariantCtrl.EnableWindow( FALSE );	
	m_CodingControl.EnableWindow( FALSE );
}

void CDlgOptionsRSADemo::OnSelectASCII() 
{
	UpdateData(true);
	m_codingMethod = 0;
	m_alphabetControl.EnableWindow( FALSE );
	m_CodingControl.EnableWindow(TRUE);
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
}

void CDlgOptionsRSADemo::OnSelectAlphabet() 
{
	UpdateData(true);
	m_alphabetControl.EnableWindow( TRUE );
	m_CodingControl.EnableWindow( TRUE );
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
}

void CDlgOptionsRSADemo::OnOK() 
{
	UpdateData();
	unsigned int blockLength = GetBlockLength();
	if (m_TextOptions == 0)
	{
		Anzahl_Zeichen=256;	
	}
	else
	{
		Anzahl_Zeichen=m_alphabet.GetLength();
	}

	if ( m_RSAVariant == 1  )
	{
		int int_RSA_Modul;
		if ( RSA_Modul.GetLength() > 3 ) int_RSA_Modul = 1000;
		else                             int_RSA_Modul = atoi(RSA_Modul);
		if ( Anzahl_Zeichen > int_RSA_Modul)
		{
			Message(IDS_STRING_ERR_ONBLOCKLENGTH_NULL, MB_ICONSTOP, Anzahl_Zeichen, RSA_Modul);
			return;
		}
		
	}
	// FALL 1:
	// Falls GetBlockLength() null zurückgibt, eine Fehlermeldung erzeugen
	else if ( blockLength==0 ) 
	{
		Message(IDS_STRING_ERR_ONBLOCKLENGTH_NULL, MB_ICONSTOP, Anzahl_Zeichen, RSA_Modul);
		return;
	}
	// FALL 2:
	// Falls die mögliche Blocklänge eins, der Anwender aber einen anderen Wert eingibt, ebenfalls Fehlermeldung erzeugen
	else if ( blockLength == 1  &&  m_BlockLength != 1 ) 
	{
		Message(IDS_STRING_ERR_ONBLOCKLENGTH_1, MB_ICONSTOP);
		return;
	}
	// FALL 3:
	// Falls Eingabe des Anwenders <1 bzw. seine Angabe generell ungültig (z.B. >blocklength)
	else if ( m_BlockLength < 1 || m_BlockLength > blockLength ) 
	{
		Message(IDS_STRING_ERR_ONBLOCKLENGTH, MB_ICONSTOP, blockLength);
		return;
	}
		
	// Ggf. Änderungen für Anwender sichtbar machen
	UpdateData(FALSE);
	
	CDialog::OnOK();
		
	
	/*
	else if ( blockLength==0 ) 
	{
		Message(IDS_STRING_ERR_ONBLOCKLENGTH_NULL, MB_ICONSTOP, Anzahl_Zeichen, RSA_Modul);
		return;
	}
	else if ( blockLength==1 && (m_BlockLength ==0 || m_BlockLength > 1) ) 
	{
		Message(IDS_STRING_ERR_ONBLOCKLENGTH_1, MB_ICONSTOP);
		return;
	}
	// FLORIAN
	// Letzte Bedingung m_BlockLength>blockLength nötig, da sonst "falsche" Eingaben
	// für die Blocklänge möglich sind (z.B. 4 anstatt 2 Byte usw.)
	else if ( blockLength >2  && (m_BlockLength < 1 || m_BlockLength > blockLength ) || m_BlockLength > blockLength ) 
	{
		Message(IDS_STRING_ERR_ONBLOCKLENGTH, MB_ICONSTOP, blockLength);
		return;
	}
	
	UpdateData(FALSE);
	CDialog::OnOK();
	*/
}


bool CDlgOptionsRSADemo::CompareModulAlphabetSize(CString N_str) // FIXME in case of greater alphabet size or changed number base
{
	int int_RSA_Modul;
	if    ( N_str.GetLength() > 3 ) int_RSA_Modul = 1000;
	else   int_RSA_Modul = atoi(RSA_Modul);
	return ( Anzahl_Zeichen < int_RSA_Modul );
}

void CDlgOptionsRSADemo::OnCodingNumberSystem() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgOptionsRSADemo::OnCodingBAdic() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgOptionsRSADemo::OnBase10() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgOptionsRSADemo::OnBase2() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgOptionsRSADemo::OnBase8() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgOptionsRSADemo::OnBase16() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

int CDlgOptionsRSADemo::GetBlockLength()
{
	int blockLength = 0;
	if ( !m_RSAVariant )
	{
		int AlphabetSize = ( !m_TextOptions ) ? 256 : m_alphabet.GetLength();
		if ( !m_codingMethod )
			blockLength = (int)floor(m_log2N / (log((double) AlphabetSize)/ log((double) 2)));
		else
		{
			double bl1 =  log((double)AlphabetSize)/ log((double)2);
			int b1, b2;
			double b3;
			switch ( m_numberBasis ) {
				case 0: b1=10;
					break;
				case 1: b1=2;
					break;
				case 2: b1=8;
					break;
				case 3: b1=16;
			}
			b2 = (int)ceil(log((double)AlphabetSize)/log((double)b1));
			b3 = double(b2)*log((double)b1)/log((double)2);
			blockLength = (int)(floor)(m_Bitlength / b3);
			if ( blockLength*b3 + bl1 <= m_log2N ) blockLength++;
		}
	}
	else
	{
		blockLength = 1;
	}
	return blockLength;
}

void CDlgOptionsRSADemo::OnCancel() 
{
	UpdateData();
	{ // Alte Werte zurückholen
		m_alphabet        = s_alphabet;
		m_numberBasis     = s_numberBasis;
		m_TextOptions     = s_TextOptions;
		m_RSAVariant      = s_RSAVariant;
		m_BlockLength     = s_BlockLength;
		m_MaxBlockLength  = s_MaxBlockLength;
		m_codingMethod    = s_codingMethod;
		m_AnzahlZeichen   = s_AnzahlZeichen;
	}
	UpdateData(false);


	CDialog::OnCancel();
}

void CDlgOptionsRSADemo::MsgAnzahlZeichen()
{
	if (m_TextOptions==0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANZAHL_ZEICHEN,pc_str,STR_LAENGE_STRING_TABLE);
		char line[256];
		sprintf( line, pc_str, 256 );
		m_AnzahlZeichen = line;	
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANZAHL_ZEICHEN,pc_str,STR_LAENGE_STRING_TABLE);
		char line[256];
		sprintf( line, pc_str, m_alphabet.GetLength() );
		m_AnzahlZeichen = line;
	}
}
