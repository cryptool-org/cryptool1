// DlgDiffieHellmanPublicParameters.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanPublicParameters.h"

#include "DlgPrimesGeneratorDemo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanPublicParameters 


CDlgDiffieHellmanPublicParameters::CDlgDiffieHellmanPublicParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanPublicParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanPublicParameters)
	m_Generator = _T("");
	m_Prime = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanPublicParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanPublicParameters)
	DDX_Control(pDX, IDC_PRIME, m_PrimeControl);
	DDX_Control(pDX, IDC_GENERATOR, m_GeneratorControl);
	DDX_Text(pDX, IDC_GENERATOR, m_Generator);
	DDX_Text(pDX, IDC_PRIME, m_Prime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanPublicParameters, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanPublicParameters)
	ON_BN_CLICKED(IDC_GENERATE_PRIME, OnGeneratePrime)
	ON_BN_CLICKED(IDC_GENERATE_GENERATOR, OnGenerateGenerator)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanPublicParameters 

void CDlgDiffieHellmanPublicParameters::OnOK() 
{
	UpdateData(true);
	
	Big g = (char*)(LPCTSTR)m_Generator;
	Big p = (char*)(LPCTSTR)m_Prime;

	// Überprüfungen für Primzahl (p)
	if( !IsDecimalNumber(m_Prime))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NON_DECIMAL_VALUE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_PrimeControl.SetFocus();
		return;
	}

	if( m_Prime.IsEmpty() || !prime(p) )
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_PRIME_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_PrimeControl.SetFocus();
		return;
	}

	// Überprüfung für Generator (g)
	if( !IsDecimalNumber(m_Generator))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NON_DECIMAL_VALUE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_GeneratorControl.SetFocus();
		return;
	}
	
	if( m_Generator.IsEmpty() || g <= 1 || g >= p )
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_GENERATOR_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_GeneratorControl.SetFocus();
		return;
	}

	UpdateData(false);
	
	CDialog::OnOK();
}

// Diese Funktion wird aufgerufen, wenn der User eine Primzahl erzeugen will. Dazu wird auf eine
// bereits bestehende Dialogklasse zurückgegeriffen und das Ergebnis einfach übernommen und im
// Eingabefeld für den Primzahl-Modul angezeigt.
void CDlgDiffieHellmanPublicParameters::OnGeneratePrime() 
{
	UpdateData(true);
	CDlgPrimesGeneratorDemo dlg;
	if(!(dlg.DoModal() == IDCANCEL)) m_Prime = dlg.m_edit5;
	UpdateData(false);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer den Generator nicht selbst bestimmen will,
// sondern einen gültigen Wert vom Programm erzeugen lassen will. Der entsprechende Wert wird dann
// automatisch in das Generator-Eingabefeld geschrieben.
void CDlgDiffieHellmanPublicParameters::OnGenerateGenerator() 
{
	UpdateData(true);
	Big P = (char*)(LPCTSTR)m_Prime;
	Big G = 0;
	
	if(!IsDecimalNumber(m_Prime))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NON_DECIMAL_VALUE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_PrimeControl.SetFocus();
		return;
	}

	if(m_Prime.IsEmpty() || !prime(P))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_PRIME_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_PrimeControl.SetFocus();
		return;
	}
	irand((unsigned)time(NULL));
	bigrand(P.getbig(), G.getbig());
	char *s = new char[512];
	s << G;
	this->m_Generator = s;
	delete s;
	UpdateData(false);
}
