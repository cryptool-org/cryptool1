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
	char line[80];
    i_maxlen = min(MAX_ANZ_HEX_BLOECKE,maxlen);
	len = i_maxlen*3;
	//{{AFX_DATA_INIT(hexdialog)
	m_einstr = _T(INIT_STRING);
	m_static_text = _T("");
	m_Decrypt = 0;
	//}}AFX_DATA_INIT
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_MAX_INPUT_LENGTH_BYTE,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str,len/3);
	m_static_text = line;
	s_alternativeWindowText[0] = 0;
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
	DDX_Control(pDX, IDC_EDIT1, m_einfeld);
	DDX_Text(pDX, IDC_EDIT1, m_einstr);
	DDV_MaxChars(pDX, m_einstr, len);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_static_text);
	DDX_Radio(pDX, IDC_RADIO1, m_Decrypt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(hexdialog, CDialog)
	//{{AFX_MSG_MAP(hexdialog)
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

BOOL hexdialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Zusätzliche Initialisierung hier einfügen	
	if (s_alternativeWindowText[0])
		SetWindowText(s_alternativeWindowText);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void hexdialog::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}
