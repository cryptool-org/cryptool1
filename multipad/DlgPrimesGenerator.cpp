// DlgPrimesGenerator.cpp: Implementierungsdatei
//


#include "stdafx.h"
#include "multipad.h"
#include <stdlib.h>

#include "DlgPrimesGenerator.h"
#include "crypt.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgPrimesGenerator 


DlgPrimesGenerator::DlgPrimesGenerator(CWnd* pParent /*=NULL*/)
	: CDialog(DlgPrimesGenerator::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgPrimesGenerator)
	m_radio1 = 0;
	m_radio4 = 0;
	m_edit1 = _T("2^7");
	m_edit2 = _T("2^8");
	m_edit3 = _T("2^7");
	m_edit4 = _T("2^8");
	m_edit5 = _T("0");
	m_edit6 = _T("0");
	//}}AFX_DATA_INIT
}


void DlgPrimesGenerator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgPrimesGenerator)
	DDX_Control(pDX, IDC_EDIT2, m_control_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_control_edit1);
	DDX_Control(pDX, IDC_BUTTON_GENERATE, m_control_button_generate);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT, m_control_button_accept);
	DDX_Control(pDX, IDC_EDIT4, m_control_edit4);
	DDX_Control(pDX, IDC_EDIT3, m_control_edit3);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Radio(pDX, IDC_RADIO4, m_radio4);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgPrimesGenerator, CDialog)
	//{{AFX_MSG_MAP(DlgPrimesGenerator)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, OnButtonAccept)
	ON_BN_CLICKED(IDC_ENDDIALOG, OnEndDialog)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgPrimesGenerator 


//=========================================================================================================
void DlgPrimesGenerator::OnRadio4() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(true);
	m_control_edit4.EnableWindow(true);
	UpdateData(false);
}

void DlgPrimesGenerator::OnRadio5() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(false);
	m_control_edit4.EnableWindow(false);
	UpdateData(false);
	OnUpdateEdit();
}

BOOL DlgPrimesGenerator::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Zusätzliche Initialisierung hier einfügen
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PRIMES,pc_str,STR_LAENGE_STRING_TABLE);
	
	m_control_edit1.SetFocus();
	CString Primes;
	if ( PasteKey( pc_str, Primes ) )
	{
		UpdateData(true);
		int d = Primes.Find(';', 0);
		m_edit5 = Primes.Mid(0, d);
		m_edit6 = Primes.Mid(d+1);
		UpdateData(false);
	}
	else
	{
		m_control_button_accept.EnableWindow(false);
	}
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void DlgPrimesGenerator::ErrorMsg(const int IDS_STRING_ID)
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	AfxMessageBox(pc_str);
}

BOOL DlgPrimesGenerator::GetRandomPrime(CString &OutStr, GeneratePrimes &P)
{
	BOOL flag = FALSE;

	for ( int i=1; i<=2000 && !flag; i++ )			 // 
	{
		P.RandP();
				
		if (0==m_radio1) flag = P.MillerRabinTest(100);
		if (1==m_radio1) flag = P.SolvayStrassenTest(100);
		if (2==m_radio1) flag = P.FermatTest(100);
	}
    if (flag)
	{
		P.GetPrime( OutStr );
	}
	else
	{
		OutStr = "0";
	}
	return flag;			// wenn keine Primzahl innerhalb der Grenzen gefunden wurde, erfolgt eine
						// entsprechende Fehlermeldung
}

//==============================================================================================================
void DlgPrimesGenerator::OnButtonGenerate() 
// erzeugt zwei Zufalls-Primzahlen innerhalb der angegebenen Grenzen
// Fehler werden mit entsprechenden Messages behandelt
{
	UpdateData(true);

	GeneratePrimes P;
	GeneratePrimes Q;

	if(0==m_radio4)
	{
		if((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty()) &&
		   (0==m_edit3.IsEmpty())&&(0==m_edit4.IsEmpty()) )
		{
			if ( P.SetLimits( m_edit1, m_edit2 ) && Q.SetLimits( m_edit3, m_edit4 ) )
			{
				theApp.DoWaitCursor(1);				// aktiviert die Sanduhr (statt des Mauszeigers)
				if ( !GetRandomPrime( m_edit5, P ) ) ErrorMsg( IDS_STRING_MSG_LEFT_PRIMES_NOT_FOUND );
				if ( !GetRandomPrime( m_edit6, Q ) ) ErrorMsg( IDS_STRING_MSG_RIGHT_PrIMES_NOT_FOUND );
				theApp.DoWaitCursor(-1);			// deaktiviert die Sanduhr
			}
			else
			{
				ErrorMsg( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND );
			}
		}
		else
		{
			ErrorMsg( IDS_STRING_ENTER_UPPER_LOWER_BOUND );
		}
	}
	else
	{
		if((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty()))
		{
			if ( P.SetLimits( m_edit1, m_edit2 ) && Q.SetLimits( m_edit1, m_edit2 ) )
			{
				theApp.DoWaitCursor(1);				// aktiviert die Sanduhr (statt des Mauszeigers)
				if ( !GetRandomPrime( m_edit5, P ) ) ErrorMsg( IDS_STRING_MSG_LEFT_PRIMES_NOT_FOUND );
				if ( !GetRandomPrime( m_edit6, Q ) ) ErrorMsg( IDS_STRING_MSG_RIGHT_PrIMES_NOT_FOUND );
				theApp.DoWaitCursor(-1);			// deaktiviert die Sanduhr
			}
			else
			{
				ErrorMsg( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND );
			}
		}
		else
		{
			ErrorMsg( IDS_STRING_ENTER_UPPER_LOWER_BOUND );
		}
	}

	if(("0"!=m_edit5)&&("0"!=m_edit6))
	{
		m_control_button_accept.EnableWindow(true);
	}

	UpdateData(false);
}

//===============================================================================================
void DlgPrimesGenerator::OnButtonAccept() 

// wenn der Button "Übernehmen" gewählt wird, kann der Dialog nur verlassen werden,
// wenn das Produkt der beiden Primzahlen kleiner als c_MaxPrime_high ist

{
	UpdateData(true);
	if ( m_edit5 != "0" && m_edit6 != "0" )
	{
		LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PRIMES,pc_str,STR_LAENGE_STRING_TABLE);
		CString Primes = m_edit5 + ";" + m_edit6;
		CopyKey ( pc_str, Primes );
		CDialog::OnOK();
	}
	UpdateData(false);
}




void DlgPrimesGenerator::OnEndDialog() 
{
	UpdateData(true);
	m_edit5=m_edit6="0";	
	CDialog::OnCancel();
	UpdateData(false);
}



void DlgPrimesGenerator::OnUpdateEdit() 
{
	if(m_radio4)
	{
		UpdateData(true);
		m_edit3 = m_edit1;
		m_edit4 = m_edit2;
		UpdateData(false);
	}	
}
