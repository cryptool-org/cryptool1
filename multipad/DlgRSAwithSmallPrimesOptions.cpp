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
	m_alphabet = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_numberBasis = 0;
	m_TextOptions = 0;
	m_BlockLength = 1;
	m_MaxBlockLength = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRSAwithSmallPrimesOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRSAwithSmallPrimesOptions)
	DDX_Control(pDX, IDC_EDIT2, m_BlockLengthCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_alphabetControl);
	DDX_Text(pDX, IDC_EDIT1, m_alphabet);
	DDX_Radio(pDX, IDC_RADIO3, m_numberBasis);
	DDX_Radio(pDX, IDC_RADIO7, m_TextOptions);
	DDX_Text(pDX, IDC_EDIT2, m_BlockLength);
	DDV_MinMaxUInt(pDX, m_BlockLength, 0, 1024);
	DDX_Text(pDX, IDC_EDIT3, m_MaxBlockLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRSAwithSmallPrimesOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgRSAwithSmallPrimesOptions)
	ON_BN_CLICKED(IDC_RADIO7, OnTextOptionsASCII)
	ON_BN_CLICKED(IDC_RADIO8, OnTextOptionsAlphabet)
	ON_EN_UPDATE(IDC_EDIT1, OnChangeAlphabet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgRSAwithSmallPrimesOptions 



void CDlgRSAwithSmallPrimesOptions::OnTextOptionsASCII() 
{
	UpdateData(true);
	m_alphabetControl.EnableWindow( FALSE );	
	m_BlockLengthCtrl.EnableWindow( TRUE );
	MsgBlockLength();
	UpdateData(false);
}

void CDlgRSAwithSmallPrimesOptions::OnTextOptionsAlphabet() 
{
	UpdateData(true);
	m_alphabetControl.EnableWindow( TRUE );
	m_BlockLengthCtrl.EnableWindow( FALSE );
	MsgBlockLength();
	UpdateData(false);
}

BOOL CDlgRSAwithSmallPrimesOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	UpdateData(true);
	if ( m_BlockLength < 1 )
	{
		m_BlockLength = 1;
	}
	if ( !m_TextOptions ) 
	{
		m_alphabetControl.EnableWindow( FALSE );
		m_BlockLength = m_Bitlength / 8;
	}
	else
	{
		m_alphabetControl.EnableWindow( TRUE );
		m_BlockLength = (int)floor(m_BlockLength/(log(m_alphabet.GetLength()+1)/log(2)) );
	}
	MsgBlockLength();
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgRSAwithSmallPrimesOptions::MsgBlockLength()
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_RSATUT_MAXBLOCKLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
	char line[256];
	int  bl;
	if ( !m_TextOptions )
	{
		bl = m_Bitlength / 8;
	}
	else
	{
		m_BlockLength = 1;
		bl = 1;
/*
		if ( m_alphabet.GetLength() > 1 )
			bl = m_Bitlength / (int)ceil(log(m_alphabet.GetLength()+1)/log(2));
		else
			bl = m_Bitlength;
*/
	}
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
	UpdateData(false);
	m_alphabetControl.SetSel(sels, sele);

}

void CDlgRSAwithSmallPrimesOptions::ReInitBlockLength(int Bitlength)
{
	if ( !m_TextOptions )
	{
		m_BlockLength = Bitlength / 8;
	}
	else
	{
		m_BlockLength = 1;
	}
}
