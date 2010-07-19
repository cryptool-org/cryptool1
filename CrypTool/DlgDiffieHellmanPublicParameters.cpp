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

#include "ZZ_helpers.h"
#include "NTL/ZZ.h"

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanPublicParameters.h"
#include "DlgGenerateSavePrime.h"
#include <math.h>




using namespace NTL;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanPublicParameters 


CDlgDiffieHellmanPublicParameters::CDlgDiffieHellmanPublicParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanPublicParameters::IDD, pParent),
	b_isSavePrime(FALSE),
	b_errType(0)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanPublicParameters)
	m_Generator = _T("");
	m_Prime = _T("");
	//}}AFX_DATA_INIT
}

CDlgDiffieHellmanPublicParameters::CDlgDiffieHellmanPublicParameters(std::string p,std::string g,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanPublicParameters::IDD, pParent),
	b_isSavePrime(FALSE),
	b_errType(0)
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
	ON_EN_CHANGE(IDC_PRIME, &CDlgDiffieHellmanPublicParameters::OnEnChangePrime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanPublicParameters 

void CDlgDiffieHellmanPublicParameters::OnOK() 
{
	UpdateData(true);
	
	// Keine "leeren" Eingabefelder zulassen

	if ( !b_isSavePrime )
	{ 
		ZZ Q, P; 
		conv(P, (char*)(LPCTSTR)m_Prime);
		Q = P/2;
		b_isSavePrime = ProbPrime(Q);
	}

	int res;
	if ( res = checkGenerator() )
	{
		LoadString(AfxGetInstanceHandle(), res, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,"CrypTool",MB_ICONERROR | MB_OK);
		if ( res == IDS_DH_PP_GENERATOR_INVALID ) 
			m_GeneratorControl.SetFocus();
		else
			m_PrimeControl.SetFocus();
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
	CDlgGenerateSavePrime dlg;
	if ( !(dlg.DoModal() == IDCANCEL) )
	{
		UpdateData(true);
		m_Prime = dlg.m_Prime;
		if ( m_Prime.GetLength() ) 
		{
			b_isSavePrime = TRUE;
			ZZ P, G;

			conv( P, (char*)(LPCTSTR)m_Prime);
			if ( m_Generator.GetLength() )
			{
				conv(G, (char*)(LPCTSTR)m_Generator);
				if ( G>=P ) 
					m_Generator.Empty();
			}
		}
		else
		{
			m_Prime = _T("");
			m_Generator = _T("");
		}
		UpdateData(false);
	}
	// Falls zuvor bereits ein Generator eingegeben wurde und dieser GROESSER oder gleich dem
	// gewählten Primzahlmodul ist, so wird der Generator gelöscht		
}


int CDlgDiffieHellmanPublicParameters::checkGenerator()
{
	b_errType = 0;
	if( m_Prime.IsEmpty() || m_Generator.IsEmpty())
	{
		b_errType = 1;
		return IDS_DH_PP_NO_USER_INPUT;
	}
	if ( !IsDecimalNumber(m_Prime) )
	{
		b_errType = 1;
		return IDS_DH_PP_NON_DECIMAL_VALUE;
	}
	if ( !IsDecimalNumber(m_Generator) || m_Generator.IsEmpty() )
	{
		b_errType = 2;
		return IDS_DH_PP_NON_DECIMAL_VALUE; 
	}

	ZZ G, P, Q, r;
	conv(P, (char*)(LPCTSTR)m_Prime);
	conv(G, (char*)(LPCTSTR)m_Generator);

	if ( ProbPrime(P, 40) )
	{
		Q = P >> 1;
		unsigned long f = 0;

		if ( ProbPrime(Q, 40) )
		{
			// if P is a save prime we just have to check G^2 != 1 mod P and G^Q != 1 mop P
			SqrMod(r, G, P);
			f |= ( r == 1 );

         if ( G >= P || G <= 1 || P <= 1 )
				return IDS_DH_PP_GENERATOR_INVALID; // FIXME: more explicit error message

			PowerMod(r, G, Q, P);
			f |= ( r == 1 );
			if ( f )
			{
				b_errType = 2;
				return IDS_DH_PP_GENERATOR_INVALID;
			}
			else
				return 0;
		}
		else
		{
			r = P; r--;
			if ( G == r ) return IDS_DH_PP_GENERATOR_INVALID;
			r = G % P;
			if( (G < 0) || (r == 0) || (G==1) )
			{
				b_errType = 2;
				return IDS_DH_PP_GENERATOR_INVALID;
			}
			else
				return 0;
		}
	}
	return IDS_DH_PP_PRIME_INVALID;
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
	
	ZZ P, G, S; 
	conv(P, (char*)(LPCTSTR)m_Prime);

    S =  (unsigned long)time(NULL); // FIXME weak seed
	SetSeed(S);

	if ( !b_isSavePrime )
	{ 
		ZZ Q;
		Q = P/2;
		b_isSavePrime = ProbPrime(Q);
	}

	if ( b_isSavePrime )
	{
		SHOW_HOUR_GLASS
		int counter = 0;
		do {
			RandomBnd(G, P);
			m_Generator = toString(G, 10, 0);
		} while ( counter++ < 4096 && checkGenerator() );
		HIDE_HOUR_GLASS
		if ( counter >= 4096 )
		{
			// FIXME 
		}
	}
	else
	{
		RandomBnd(G, P);
		m_Generator = toString(G, 10, 0);
	}
	UpdateData(false);
}


void CDlgDiffieHellmanPublicParameters::OnEnChangePrime()
{
	b_isSavePrime = FALSE;
}
