/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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