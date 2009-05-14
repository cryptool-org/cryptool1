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

// DlgDiffieHellmanPublicParameters.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanPublicParameters.h"

#include "DlgGeneratePrime.h"
#include "IntegerArithmetic.h"
#include <math.h>


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

CDlgDiffieHellmanPublicParameters::CDlgDiffieHellmanPublicParameters(std::string p,std::string g,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanPublicParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanPublicParameters)
	m_Generator = g.c_str();
	m_Prime = p.c_str();
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
	
	// Keine "leeren" Eingabefelder zulassen
	if( this->m_Prime.IsEmpty() || this->m_Generator.IsEmpty())
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NO_USER_INPUT, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_PrimeControl.SetFocus();
		return;
	}
	
	// Überprüfungen für Primzahl (p)
	if( !IsDecimalNumber(m_Prime))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NON_DECIMAL_VALUE, pc_str, STR_LAENGE_STRING_TABLE);
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

	Big g = (char*)(LPCTSTR)m_Generator;
	Big p = (char*)(LPCTSTR)m_Prime;

	// Überprüfungen für Primzahl (p)
	if (p == Big(0)) 
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_PRIME_ZERO, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,"CrypTool",MB_ICONERROR | MB_OK);
		m_PrimeControl.SetFocus();
		return;
	}
	if( !prime(p) )
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_PRIME_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		if( MessageBox(pc_str,"CrypTool",MB_ICONINFORMATION | MB_OKCANCEL) == IDCANCEL )
		{
			m_PrimeControl.SetFocus();
			return;
		}
	}

	// FIXME
	// if ( p-1 = p_1^e_1 * ... * p_l^e_l, p_i prime ) check g^p_i != 1 for (i= 1, ..., l)
	// Überprüfung für Generator (g)
	if( g < 0 ||  (g%p)==0 || g==1 || g==(p-1))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_GENERATOR_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		if( MessageBox(pc_str,"CrypTool",MB_ICONINFORMATION | MB_OKCANCEL) == IDCANCEL )
		{
			m_GeneratorControl.SetFocus();
			return;
		}
		
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
	CDlgGeneratePrime dlg;
	dlg.m_edit1 = _T("2^255+2^254");
	dlg.m_edit2 = _T("2^256");
	if(!(dlg.DoModal() == IDCANCEL)) m_Prime = dlg.m_edit5;

	// Falls zuvor bereits ein Generator eingegeben wurde und dieser GROESSER oder gleich dem
	// gewählten Primzahlmodul ist, so wird der Generator gelöscht
	Big P = (char*)(LPCTSTR)m_Prime;
	Big G = (char*)(LPCTSTR)m_Generator;
	if(G>=P) m_Generator.Empty();
			
	UpdateData(false);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer den Generator nicht selbst bestimmen will,
// sondern einen gültigen Wert vom Programm erzeugen lassen will. Der entsprechende Wert wird dann
// automatisch in das Generator-Eingabefeld geschrieben.
void CDlgDiffieHellmanPublicParameters::OnGenerateGenerator() 
{
	UpdateData(true);

	if(!IsDecimalNumber(m_Prime))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NON_DECIMAL_VALUE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_PrimeControl.SetFocus();
		return;
	}

	if(m_Prime.IsEmpty() /*|| !prime(P)*/)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_PRIME_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_PrimeControl.SetFocus();
		return;
	}
	
	Big P = (char*)(LPCTSTR)m_Prime;
	Big G;

	irand((unsigned)time(NULL));
	bigrand(P.getbig(), G.getbig());
	char *s = new char[512];
	s << G;
	this->m_Generator = s;
	delete s;
	UpdateData(false);
}

#if 0
int DlgDiffieHellmanPublicParameters::PrimeParameterGenerationRFC2631(int bitlengthP, int bitlengthQ)
{
	int m_dash, L_dash, N_dash;
	m_dash = (int)ceil(bitlengthP/160.0);
	L_dash = (int)ceil(bitlengthQ/160.0);
	N_dash = (int)ceil(bitlengthQ/1024.0);

	


}
#endif 