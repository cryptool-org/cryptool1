// Primzahltester.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "Primzahltester.h"
#include "zzgen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld Primzahltester 


Primzahltester::Primzahltester(CWnd* pParent /*=NULL*/)
	: CDialog(Primzahltester::IDD, pParent)
{
	//{{AFX_DATA_INIT(Primzahltester)
	m_eingabe = _T("");
	//}}AFX_DATA_INIT
}


void Primzahltester::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_eingabe);
	//{{AFX_DATA_MAP(Primzahltester)
	DDX_Text(pDX, IDC_EDIT1, m_eingabe);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Primzahltester, CDialog)
	//{{AFX_MSG_MAP(Primzahltester)
	ON_BN_CLICKED(IDC_BUTTON_TESTEN, OnButtonTesten)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f¸r Nachrichten Primzahltester 

void Primzahltester::OnButtonTesten() 
{
	UpdateData(true);
	char line[256];
	if(m_eingabe.GetLength()==10&&m_eingabe>"2147483647"||m_eingabe.GetLength()>10)				
	{											
		m_eingabe="";							// wenn eingegebene Zahl zu groﬂ ist, dann	
	}											// passiert nichts
	if(m_eingabe!="")
	{
		zzgen z;
		if(z.is_prime_turbo(atoi((LPCTSTR) m_eingabe))==1)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING61437,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str,atoi((LPCTSTR)m_eingabe));
			AfxMessageBox(line);				// MessageBox, wenn i Primzahl ist
		}
		if(!z.is_prime_turbo(atoi((LPCTSTR) m_eingabe)))
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING61438,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str,atoi((LPCTSTR)m_eingabe));
			AfxMessageBox(line);				// MessageBox, wenn i keine Primzahl ist
		}
		if(z.is_prime_turbo(atoi((LPCTSTR) m_eingabe))==-1) 
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING61439,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);				// MessageBox, wenn "Primes.txt" nicht vorhanden
		}
		if(z.is_prime_turbo(atoi((LPCTSTR) m_eingabe))==-2) 
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING61440,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);				// MessageBox, wenn "Primes.txt" ver‰ndert wurde
		}
	}
	UpdateData(false);
}
}
}
