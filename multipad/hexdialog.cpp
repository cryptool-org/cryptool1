//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmierung der Dialog-Klasse zur Eingabe eines 
// hexadezimalen Schlüssels. Bei der Eingabe werden nur die 
// Zeichen a,...,f,A,...,F,0,...,9 akzeptiert; dabei werden 
// Kleinbuchstaben in Großbuchstaben umgewandelt (dies geschieht
// direkt durch das Eingabefenster, bzw. dessen Eigenschaften-Fenster). 
// Im Eingabefenster wird die hexadezimale Zahl in der üblichen 
// Schreibweise - jeweils Blöcke bestehend aus zwei Zeichen, 
// getrennt durch ein Leerzeichen - angegeben. Cut and Paste 
// über die Zwischenablage funktioniert ebenfalls. 
// Da ein Eingabefeld CEdit keine Nachricht erhält, die etwas über 
// die gedrückte Taste aussagen, ist es nicht möglich, folgende 
// Situationen zu unterscheiden:
// - Der Cursor steht links von einem Leerzeichen und der Benutzer 
//   drückt "Entfernen"
// - Der Cursor steht rechts von einem Leerzeichen und der Benutzer 
//   drückt "Backspace"
//   In diesem Fall wird so verfahren, als ob die Taste "Backspace" 
//   gedrückt worden wäre.
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// hexdialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "hexdialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define INIT_STRING ""


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld hexdialog 


hexdialog::hexdialog(int maxlen, CWnd* pParent /*=NULL*/)
	: dia1( maxlen, pParent)
{
    i_maxlen = min(MAX_ANZ_HEX_BLOECKE,maxlen);
	len = i_maxlen*3;
	//{{AFX_DATA_INIT(hexdialog)
	m_einstr = _T(INIT_STRING);
	m_Decrypt = 0;
	//}}AFX_DATA_INIT
}

int hexdialog::Display()
{
	int res;
	res=DoModal();
	return res;
}

void hexdialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(hexdialog)
	DDX_Control(pDX, IDOK, m_EncryptionButton);
	DDX_Control(pDX, IDC_BUTTON1, m_DecryptionButton);
	DDX_Control(pDX, IDC_EDIT1, m_einfeld);
	DDX_Text(pDX, IDC_EDIT1, m_einstr);
	DDV_MaxChars(pDX, m_einstr, len);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_static_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(hexdialog, CDialog)
	//{{AFX_MSG_MAP(hexdialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateKey)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteHexKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten hexdialog 

char * hexdialog::GetData( void )
{
	return m_einfeld.BinData;
}

int hexdialog::GetLen( void )
{
	return min(i_maxlen, m_einfeld.BinLen);
}

void hexdialog::OnUpdateKey() 
{
	UpdateData(TRUE);	
	if ( m_einstr.GetLength() )
	{
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);	
	}
	else
	{
		m_EncryptionButton.EnableWindow(FALSE);
		m_DecryptionButton.EnableWindow(FALSE);	
	}
	UpdateData(FALSE);
}

void hexdialog::OnPasteHexKey() 
{
	UpdateData(TRUE);
	CString Title;
	CString KeyStr;
	Title=s_alternativeWindowText;
	ExtractStrKeyType( strTitle, Title );
	if ( PasteKey(strTitle,KeyStr) )
	{
		m_einfeld.SetSel(0,-1);
		m_einfeld.ReplaceSel( KeyStr );
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);	
	}
	UpdateData(FALSE);
}


