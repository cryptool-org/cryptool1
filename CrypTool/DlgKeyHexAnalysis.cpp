//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
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
// hexdialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHexAnalysis.h"


#define INIT_STRING ""


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHex 


CDlgKeyHexAnalysis::CDlgKeyHexAnalysis(CWnd* pParent /*=NULL*/)
	: CDlgKeyVigenereAnalyisis(pParent)
{
	char line[80];

	len = 600;
	//{{AFX_DATA_INIT(CDlgKeyHexAnalysis)
	m_einstr = _T(INIT_STRING);
	m_static_text = _T("");
	//}}AFX_DATA_INIT
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_MAX_INPUT_LENGTH_BYTE,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str,len/3);
	m_static_text = line;
}

int CDlgKeyHexAnalysis::Display(char *data, int len)
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

int CDlgKeyHexAnalysis::Display(CString c)
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

void CDlgKeyHexAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyHexAnalysis)
	DDX_Control(pDX, IDC_EDIT1, m_einfeld);
	DDX_Text(pDX, IDC_EDIT1, m_einstr);
	DDV_MaxChars(pDX, m_einstr, len);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyHexAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHexAnalysis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHex 


char * CDlgKeyHexAnalysis::GetData( void )
{
	return m_einfeld.BinData;
}


int CDlgKeyHexAnalysis::GetLen( void )
{
	return m_einfeld.BinLen;
} 

int CDlgKeyHexAnalysis::GetHexData(LPTSTR v, int len) {
	// copy m_einstr, removing non-hex chars
	int i,j;
	for (i = j = 0; i < m_einstr.GetLength() && j < len - 1; i++)
		if (isxdigit(m_einstr[i]))
			v[j++] = m_einstr[i];
	v[j] = '\0';
	return j; 
}

BOOL CDlgKeyHexAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_font.CreatePointFont(100,"Courier New");
	m_einfeld.SetFont(&m_font);
	m_einfeld.SetFixedByteLength((m_einfeld.GetWindowTextLength()+1)/3);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
