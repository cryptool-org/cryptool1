// DlgRSAwithSmallPrimesOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRSAwithSmallPrimesOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRSAwithSmallPrimesOptions 



CDlgRSAwithSmallPrimesOptions::CDlgRSAwithSmallPrimesOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRSAwithSmallPrimesOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRSAwithSmallPrimesOptions)
	m_alphabet = _T(" ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_numberBasis = 0;
	m_TextOptions = 0;
	m_RSAVariant  = 0;
	m_BlockLength = 1;
	m_MaxBlockLength = _T("");
	m_codingMethod = 0;
	m_AnzahlZeichen = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRSAwithSmallPrimesOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRSAwithSmallPrimesOptions)
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


BEGIN_MESSAGE_MAP(CDlgRSAwithSmallPrimesOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgRSAwithSmallPrimesOptions)
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
// Behandlungsroutinen für Nachrichten CDlgRSAwithSmallPrimesOptions 

BOOL CDlgRSAwithSmallPrimesOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	UpdateData(true);
	m_BlockLength = GetBlockLength();
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

void CDlgRSAwithSmallPrimesOptions::MsgBlockLength()
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_RSATUT_MAXBLOCKLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	char line[256];
	int  bl = GetBlockLength();
	sprintf( line, pc_str, bl );
	m_MaxBlockLength = line;
	if ( !m_BlockLength ) m_BlockLength = 1;
	if ( bl < m_BlockLength ) m_BlockLength = bl;
}



void CDlgRSAwithSmallPrimesOptions::OnChangeAlphabet() 
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

void CDlgRSAwithSmallPrimesOptions::ReInitBlockLength()
{
	m_BlockLength = GetBlockLength();
}

void CDlgRSAwithSmallPrimesOptions::OnSelectRSA() 
{
	UpdateData(true);	
	m_BlockLengthCtrl.EnableWindow( TRUE );
	m_RSAVariantCtrl.EnableWindow( TRUE );
	m_CodingControl.EnableWindow( TRUE );
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
}

void CDlgRSAwithSmallPrimesOptions::OnSelectDialougeOfSisters() 
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

void CDlgRSAwithSmallPrimesOptions::OnSelectASCII() 
{
	UpdateData(true);
	m_codingMethod = 0;
	m_alphabetControl.EnableWindow( FALSE );
	m_CodingControl.EnableWindow(TRUE);
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
}

void CDlgRSAwithSmallPrimesOptions::OnSelectAlphabet() 
{
	UpdateData(true);
	m_alphabetControl.EnableWindow( TRUE );
	m_CodingControl.EnableWindow( TRUE );
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(false);
}

void CDlgRSAwithSmallPrimesOptions::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	UpdateData();
	int blockLength = GetBlockLength();
	if (m_TextOptions==0)
	{
		Anzahl_Zeichen=256;	
	}
	else
	{
		Anzahl_Zeichen=m_alphabet.GetLength();
	}
//	if ( m_BlockLength < 1 || m_BlockLength > blockLength ) 

	if ( m_RSAVariant == 1  )
	{
		int int_RSA_Modul;
		int_RSA_Modul=atoi(RSA_Modul);
		if ( Anzahl_Zeichen > int_RSA_Modul)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ONBLOCKLENGTH_NULL, pc_str,STR_LAENGE_STRING_TABLE);
			char line[128];
			sprintf(line, pc_str, Anzahl_Zeichen, RSA_Modul);
//			sprintf(line, pc_str, theApp.TextOptions.m_alphabet);
			AfxMessageBox(line);
			//m_BlockLength = 1;
			return;
		}
		
	}
	else if ( blockLength==0 ) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ONBLOCKLENGTH_NULL, pc_str,STR_LAENGE_STRING_TABLE);
		char line[128];
		sprintf(line, pc_str, Anzahl_Zeichen, RSA_Modul);
//		sprintf(line, pc_str, theApp.TextOptions.m_alphabet);
		AfxMessageBox(line);
		//m_BlockLength = 1;
		return;
	}
	else if ( blockLength==1 && (m_BlockLength ==0 || m_BlockLength > 1) ) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ONBLOCKLENGTH_1, pc_str,STR_LAENGE_STRING_TABLE);
		char line[128];
		sprintf(line, pc_str);
		AfxMessageBox(line);
		//m_BlockLength = 1;
		return;
	}
	else if ( blockLength >2  && (m_BlockLength < 1 || m_BlockLength > blockLength )) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ONBLOCKLENGTH, pc_str,STR_LAENGE_STRING_TABLE);
		char line[128];
		sprintf(line, pc_str, blockLength);
		AfxMessageBox(line);
		//m_BlockLength = 1;
		return;
	}
	UpdateData(false);
	CDialog::OnOK();
}

void CDlgRSAwithSmallPrimesOptions::OnCodingNumberSystem() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgRSAwithSmallPrimesOptions::OnCodingBAdic() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgRSAwithSmallPrimesOptions::OnBase10() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgRSAwithSmallPrimesOptions::OnBase2() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgRSAwithSmallPrimesOptions::OnBase8() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

void CDlgRSAwithSmallPrimesOptions::OnBase16() 
{
	UpdateData();
	MsgBlockLength();
	MsgAnzahlZeichen();
	UpdateData(FALSE);
}

int CDlgRSAwithSmallPrimesOptions::GetBlockLength()
{
	int blockLength = 0;
	if ( !m_RSAVariant )
	{
		int AlphabetSize = ( !m_TextOptions ) ? 256 : m_alphabet.GetLength();
		if ( !m_codingMethod )
			blockLength = (int)floor(m_log2N / (log(AlphabetSize)/log(2)));
		else
		{
			double bl1 = log(AlphabetSize)/log(2);
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
			b2 = (int)ceil(log(AlphabetSize)/log(b1));
			b3 = double(b2)*log(b1)/log(2);
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

void CDlgRSAwithSmallPrimesOptions::OnCancel() 
{
		// TODO: Zusätzliche Prüfung hier einfügen
	UpdateData();
	int blockLength = GetBlockLength();

	if ( m_BlockLength > blockLength ) 
	{
		m_BlockLength=blockLength;
	}
	/*
	if (m_BlockLength < 1)
	{
		
	}
	*/
	UpdateData(false);
	CDialog::OnCancel();
}

void CDlgRSAwithSmallPrimesOptions::MsgAnzahlZeichen()
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
