//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmierung der Dialog-Klasse zur Eingabe eines 
// hexadezimalen Schl�ssels. Bei der Eingabe werden nur die 
// Zeichen a,...,f,A,...,F,0,...,9 akzeptiert; dabei werden 
// Kleinbuchstaben in Gro�buchstaben umgewandelt (dies geschieht
// direkt durch das Eingabefenster, bzw. dessen Eigenschaften-Fenster). 
// Im Eingabefenster wird die hexadezimale Zahl in der �blichen 
// Schreibweise - jeweils Bl�cke bestehend aus zwei Zeichen, 
// getrennt durch ein Leerzeichen - angegeben. Cut and Paste 
// �ber die Zwischenablage funktioniert ebenfalls. 
// Da ein Eingabefeld CEdit keine Nachricht erh�lt, die etwas �ber 
// die gedr�ckte Taste aussagen, ist es nicht m�glich, folgende 
// Situationen zu unterscheiden:
// - Der Cursor steht links von einem Leerzeichen und der Benutzer 
//   dr�ckt "Entfernen"
// - Der Cursor steht rechts von einem Leerzeichen und der Benutzer 
//   dr�ckt "Backspace"
//   In diesem Fall wird so verfahren, als ob die Taste "Backspace" 
//   gedr�ckt worden w�re.
//////////////////////////////////////////////////////////////////
// hexdialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DialogKeyHex.h"


#define INIT_STRING ""


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld hexdialog 


CDialogKeyHex::CDialogKeyHex(CWnd* pParent /*=NULL*/)
	: CDialogVienereKey(pParent)
{
	char line[80];

	len = 600;
	//{{AFX_DATA_INIT(CDialogKeyHex)
	m_einstr = _T(INIT_STRING);
	m_static_text = _T("");
	//}}AFX_DATA_INIT
	LoadString(AfxGetInstanceHandle(),IDS_STRING41526,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str,len/3);
	m_static_text = line;
}

int CDialogKeyHex::Display(char *data, int len)
{
	int res, i;
	char buff[601];

	for(i=0;i<len;i++)
		sprintf(buff+i*3,"%02.2X ",(unsigned char)data[i]);

	buff[len*3-1]=0;
	m_einstr = buff;
	m_einfeld.SetHex( data, len );

	res=DoModal();

	return res;
}

int CDialogKeyHex::Display(CString c)
{
	int res, i,j;
	char buff[600];

	for(i=j=0;i<c.GetLength();i++)
	{
		sprintf(buff+j,"%c",c[i]);
		j++;
		if ((i%2)&&i!=0)
			buff[j++]=' ';
	}

	buff[j]=0;
	m_einstr = buff;
	m_einfeld.SetAscii(c);

	res=DoModal();

	return res;
}

void CDialogKeyHex::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogKeyHex)
	DDX_Control(pDX, IDC_EDIT1, m_einfeld);
	DDX_Text(pDX, IDC_EDIT1, m_einstr);
	DDV_MaxChars(pDX, m_einstr, len);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogKeyHex, CDialog)
	//{{AFX_MSG_MAP(CDialogKeyHex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten hexdialog 


char * CDialogKeyHex::GetData( void )
{
	return m_einfeld.BinData;
}

int CDialogKeyHex::GetLen( void )
{
	return m_einfeld.BinLen;
} 