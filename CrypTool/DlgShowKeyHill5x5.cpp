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

//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// HillSchluesselAusgabe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "SquareMatrixModN.h"
#include "CrypToolApp.h"
#include "DlgShowKeyHill5x5.h"
#include "KeyRepository.h"
#include "HillEncryption.h"
#include "Cryptography.h"
#include "assert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKeyHill5x5 


CDlgShowKeyHill5x5::CDlgShowKeyHill5x5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKeyHill5x5::IDD, pParent)
	, i_multDirection(0)
	, m_alphabetOffset(0)
{
	//{{AFX_DATA_INIT(CDlgShowKeyHill5x5)
	m_Feld11 = _T("");
	m_Feld12 = _T("");
	m_Feld13 = _T("");
	m_Feld14 = _T("");
	m_Feld15 = _T("");
	m_Feld21 = _T("");
	m_Feld22 = _T("");
	m_Feld23 = _T("");
	m_Feld24 = _T("");
	m_Feld25 = _T("");
	m_Feld31 = _T("");
	m_Feld32 = _T("");
	m_Feld33 = _T("");
	m_Feld34 = _T("");
	m_Feld35 = _T("");
	m_Feld41 = _T("");
	m_Feld42 = _T("");
	m_Feld43 = _T("");
	m_Feld44 = _T("");
	m_Feld45 = _T("");
	m_Feld51 = _T("");
	m_Feld52 = _T("");
	m_Feld53 = _T("");
	m_Feld54 = _T("");
	m_Feld55 = _T("");

	m_AlphFeld36 = _T("");
	m_AlphFeld37 = _T("");
	m_AlphFeld38 = _T("");
	m_AlphFeld40 = _T("");
	m_AlphFeld46 = _T("");
	m_AlphFeld47 = _T("");
	m_AlphFeld48 = _T("");
	m_AlphFeld49 = _T("");
	m_AlphFeld50 = _T("");
	m_AlphFeld111 = _T("");
	m_AlphFeld57 = _T("");
	m_AlphFeld58 = _T("");
	m_AlphFeld59 = _T("");
	m_AlphFeld56 = _T("");
	m_AlphFeld115 = _T("");
	m_AlphFeld60 = _T("");
	m_AlphFeld61 = _T("");
	m_AlphFeld62 = _T("");
	m_AlphFeld116 = _T("");
	m_AlphFeld117 = _T("");
	m_AlphFeld63 = _T("");
	m_AlphFeld64 = _T("");
	m_AlphFeld69 = _T("");
	m_AlphFeld65 = _T("");
	m_AlphFeld66 = _T("");

	m_decrypt = 0;
	//}}AFX_DATA_INIT

	decrypt_vorher = m_decrypt;

	m_pFelder[0][0] = &m_Feld11;
	m_pFelder[0][1] = &m_Feld12;
	m_pFelder[0][2] = &m_Feld13;
	m_pFelder[0][3] = &m_Feld14;
	m_pFelder[0][4] = &m_Feld15;
	m_pFelder[1][0] = &m_Feld21;
	m_pFelder[1][1] = &m_Feld22;
	m_pFelder[1][2] = &m_Feld23;
	m_pFelder[1][3] = &m_Feld24;
	m_pFelder[1][4] = &m_Feld25;
	m_pFelder[2][0] = &m_Feld31;
	m_pFelder[2][1] = &m_Feld32;
	m_pFelder[2][2] = &m_Feld33;
	m_pFelder[2][3] = &m_Feld34;
	m_pFelder[2][4] = &m_Feld35;
	m_pFelder[3][0] = &m_Feld41;
	m_pFelder[3][1] = &m_Feld42;
	m_pFelder[3][2] = &m_Feld43;
	m_pFelder[3][3] = &m_Feld44;
	m_pFelder[3][4] = &m_Feld45;
	m_pFelder[4][0] = &m_Feld51;
	m_pFelder[4][1] = &m_Feld52;
	m_pFelder[4][2] = &m_Feld53;
	m_pFelder[4][3] = &m_Feld54;
	m_pFelder[4][4] = &m_Feld55;

	m_pAlphFelder[0][0] = &m_AlphFeld36;
	m_pAlphFelder[0][1] = &m_AlphFeld37;
	m_pAlphFelder[0][2] = &m_AlphFeld38;
	m_pAlphFelder[0][3] = &m_AlphFeld40;
	m_pAlphFelder[0][4] = &m_AlphFeld46;
	m_pAlphFelder[1][0] = &m_AlphFeld47;
	m_pAlphFelder[1][1] = &m_AlphFeld48;
	m_pAlphFelder[1][2] = &m_AlphFeld49;
	m_pAlphFelder[1][3] = &m_AlphFeld50;
	m_pAlphFelder[1][4] = &m_AlphFeld111;
	m_pAlphFelder[2][0] = &m_AlphFeld57;
	m_pAlphFelder[2][1] = &m_AlphFeld58;
	m_pAlphFelder[2][2] = &m_AlphFeld59;
	m_pAlphFelder[2][3] = &m_AlphFeld56;
	m_pAlphFelder[2][4] = &m_AlphFeld115;
	m_pAlphFelder[3][0] = &m_AlphFeld60;
	m_pAlphFelder[3][1] = &m_AlphFeld61;
	m_pAlphFelder[3][2] = &m_AlphFeld62;
	m_pAlphFelder[3][3] = &m_AlphFeld116;
	m_pAlphFelder[3][4] = &m_AlphFeld117;
	m_pAlphFelder[4][0] = &m_AlphFeld63;
	m_pAlphFelder[4][1] = &m_AlphFeld64;
	m_pAlphFelder[4][2] = &m_AlphFeld69;
	m_pAlphFelder[4][3] = &m_AlphFeld65;
	m_pAlphFelder[4][4] = &m_AlphFeld66;
}


void CDlgShowKeyHill5x5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowKeyHill5x5)
	DDX_Control(pDX, IDC_EDIT1, m_FeldUnsichtbar);
	DDX_Text(pDX, IDC_EDIT11, m_Feld11);
	DDX_Text(pDX, IDC_EDIT12, m_Feld12);
	DDX_Text(pDX, IDC_EDIT13, m_Feld13);
	DDX_Text(pDX, IDC_EDIT14, m_Feld14);
	DDX_Text(pDX, IDC_EDIT15, m_Feld15);
	DDX_Text(pDX, IDC_EDIT21, m_Feld21);
	DDX_Text(pDX, IDC_EDIT22, m_Feld22);
	DDX_Text(pDX, IDC_EDIT23, m_Feld23);
	DDX_Text(pDX, IDC_EDIT24, m_Feld24);
	DDX_Text(pDX, IDC_EDIT25, m_Feld25);
	DDX_Text(pDX, IDC_EDIT31, m_Feld31);
	DDX_Text(pDX, IDC_EDIT32, m_Feld32);
	DDX_Text(pDX, IDC_EDIT33, m_Feld33);
	DDX_Text(pDX, IDC_EDIT34, m_Feld34);
	DDX_Text(pDX, IDC_EDIT35, m_Feld35);
	DDX_Text(pDX, IDC_EDIT41, m_Feld41);
	DDX_Text(pDX, IDC_EDIT42, m_Feld42);
	DDX_Text(pDX, IDC_EDIT43, m_Feld43);
	DDX_Text(pDX, IDC_EDIT44, m_Feld44);
	DDX_Text(pDX, IDC_EDIT45, m_Feld45);
	DDX_Text(pDX, IDC_EDIT51, m_Feld51);
	DDX_Text(pDX, IDC_EDIT52, m_Feld52);
	DDX_Text(pDX, IDC_EDIT53, m_Feld53);
	DDX_Text(pDX, IDC_EDIT54, m_Feld54);
	DDX_Text(pDX, IDC_EDIT55, m_Feld55);

	DDX_Text(pDX, IDC_EDIT36, m_AlphFeld36);
	DDX_Text(pDX, IDC_EDIT37, m_AlphFeld37);
	DDX_Text(pDX, IDC_EDIT38, m_AlphFeld38);
	DDX_Text(pDX, IDC_EDIT40, m_AlphFeld40);
	DDX_Text(pDX, IDC_EDIT46, m_AlphFeld46);
	DDX_Text(pDX, IDC_EDIT47, m_AlphFeld47);
	DDX_Text(pDX, IDC_EDIT48, m_AlphFeld48);
	DDX_Text(pDX, IDC_EDIT49, m_AlphFeld49);
	DDX_Text(pDX, IDC_EDIT50, m_AlphFeld50);
	DDX_Text(pDX, IDC_EDIT111, m_AlphFeld111);
	DDX_Text(pDX, IDC_EDIT57, m_AlphFeld57);
	DDX_Text(pDX, IDC_EDIT58, m_AlphFeld58);
	DDX_Text(pDX, IDC_EDIT59, m_AlphFeld59);
	DDX_Text(pDX, IDC_EDIT56, m_AlphFeld56);
	DDX_Text(pDX, IDC_EDIT115, m_AlphFeld115);
	DDX_Text(pDX, IDC_EDIT60, m_AlphFeld60);
	DDX_Text(pDX, IDC_EDIT61, m_AlphFeld61);
	DDX_Text(pDX, IDC_EDIT62, m_AlphFeld62);
	DDX_Text(pDX, IDC_EDIT116, m_AlphFeld116);
	DDX_Text(pDX, IDC_EDIT117, m_AlphFeld117);
	DDX_Text(pDX, IDC_EDIT63, m_AlphFeld63);
	DDX_Text(pDX, IDC_EDIT64, m_AlphFeld64);
	DDX_Text(pDX, IDC_EDIT69, m_AlphFeld69);
	DDX_Text(pDX, IDC_EDIT65, m_AlphFeld65);
	DDX_Text(pDX, IDC_EDIT66, m_AlphFeld66);

	DDX_Control(pDX, IDC_EDIT11, m_ControlFeld11);
	DDX_Control(pDX, IDC_EDIT12, m_ControlFeld12);
	DDX_Control(pDX, IDC_EDIT13, m_ControlFeld13);
	DDX_Control(pDX, IDC_EDIT14, m_ControlFeld14);
	DDX_Control(pDX, IDC_EDIT15, m_ControlFeld15);
	DDX_Control(pDX, IDC_EDIT21, m_ControlFeld21);
	DDX_Control(pDX, IDC_EDIT22, m_ControlFeld22);
	DDX_Control(pDX, IDC_EDIT23, m_ControlFeld23);
	DDX_Control(pDX, IDC_EDIT24, m_ControlFeld24);
	DDX_Control(pDX, IDC_EDIT25, m_ControlFeld25);
	DDX_Control(pDX, IDC_EDIT31, m_ControlFeld31);
	DDX_Control(pDX, IDC_EDIT32, m_ControlFeld32);
	DDX_Control(pDX, IDC_EDIT33, m_ControlFeld33);
	DDX_Control(pDX, IDC_EDIT34, m_ControlFeld34);
	DDX_Control(pDX, IDC_EDIT35, m_ControlFeld35);
	DDX_Control(pDX, IDC_EDIT41, m_ControlFeld41);
	DDX_Control(pDX, IDC_EDIT42, m_ControlFeld42);
	DDX_Control(pDX, IDC_EDIT43, m_ControlFeld43);
	DDX_Control(pDX, IDC_EDIT44, m_ControlFeld44);
	DDX_Control(pDX, IDC_EDIT45, m_ControlFeld45);
	DDX_Control(pDX, IDC_EDIT51, m_ControlFeld51);
	DDX_Control(pDX, IDC_EDIT52, m_ControlFeld52);
	DDX_Control(pDX, IDC_EDIT53, m_ControlFeld53);
	DDX_Control(pDX, IDC_EDIT54, m_ControlFeld54);
	DDX_Control(pDX, IDC_EDIT55, m_ControlFeld55);

	DDX_Control(pDX, IDC_EDIT36, m_ControlAlphFeld36);
	DDX_Control(pDX, IDC_EDIT37, m_ControlAlphFeld37);
	DDX_Control(pDX, IDC_EDIT38, m_ControlAlphFeld38);
	DDX_Control(pDX, IDC_EDIT40, m_ControlAlphFeld40);
	DDX_Control(pDX, IDC_EDIT46, m_ControlAlphFeld46);
	DDX_Control(pDX, IDC_EDIT47, m_ControlAlphFeld47);
	DDX_Control(pDX, IDC_EDIT48, m_ControlAlphFeld48);
	DDX_Control(pDX, IDC_EDIT49, m_ControlAlphFeld49);
	DDX_Control(pDX, IDC_EDIT50, m_ControlAlphFeld50);
	DDX_Control(pDX, IDC_EDIT111, m_ControlAlphFeld111);
	DDX_Control(pDX, IDC_EDIT57, m_ControlAlphFeld57);
	DDX_Control(pDX, IDC_EDIT58, m_ControlAlphFeld58);
	DDX_Control(pDX, IDC_EDIT59, m_ControlAlphFeld59);
	DDX_Control(pDX, IDC_EDIT56, m_ControlAlphFeld56);
	DDX_Control(pDX, IDC_EDIT115, m_ControlAlphFeld115);
	DDX_Control(pDX, IDC_EDIT60, m_ControlAlphFeld60);
	DDX_Control(pDX, IDC_EDIT61, m_ControlAlphFeld61);
	DDX_Control(pDX, IDC_EDIT62, m_ControlAlphFeld62);
	DDX_Control(pDX, IDC_EDIT116, m_ControlAlphFeld116);
	DDX_Control(pDX, IDC_EDIT117, m_ControlAlphFeld117);
	DDX_Control(pDX, IDC_EDIT63, m_ControlAlphFeld63);
	DDX_Control(pDX, IDC_EDIT64, m_ControlAlphFeld64);
	DDX_Control(pDX, IDC_EDIT69, m_ControlAlphFeld69);
	DDX_Control(pDX, IDC_EDIT65, m_ControlAlphFeld65);
	DDX_Control(pDX, IDC_EDIT66, m_ControlAlphFeld66);
	DDX_Radio  (pDX, IDC_RADIO1, m_decrypt);
	DDX_Text   (pDX, IDC_EDIT2,  m_alphabetOffset);
	DDX_Radio(pDX, IDC_RADIO8,   i_multDirection);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowKeyHill5x5, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKeyHill5x5)
	ON_BN_CLICKED(IDC_DECRYPT, OnDecrypt)
	ON_BN_CLICKED(IDC_RADIO1, OnVerschluesseln)
	ON_BN_CLICKED(IDC_RADIO2, OnEntschluesseln)
	ON_BN_CLICKED(IDC_BUTTON1, OnKopieren)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowKeyHill5x5 

void CDlgShowKeyHill5x5::OnDecrypt() 
{
	UpdateData(TRUE);

	if (m_decrypt != decrypt_vorher)
	{
		SHOW_HOUR_GLASS

		decrypt_vorher = m_decrypt;

		// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
		int i,
			j;
		
		// Alle Eintraege aus dem Fenster auslesen
		char Zeichen[HILL_MAX_DIM][HILL_MAX_DIM];
		
		int dim = 1;
		
		for (i=0; i<HILL_MAX_DIM; i++)
		{
			for (j=0; j<HILL_MAX_DIM; j++)
			{
				CString cs;
				m_pControlFelder[i][j]->GetWindowText(cs);
				
				if (cs.GetLength() == 1)
				{
					Zeichen[i][j] = cs[0];
					
					// Die Variable dim erhaelt am Ende der Schleife die Dimension der angezeigten Matrix,
					// da die letzte Zuweisung passiert, wenn das letzte Ausgabefeld (rechts unten) 
					// angesprochen wird. Dieses befindet sich in der letzten Zeile der Matrix. 
					dim = j+1;
				}
			}
		}
		
		// Anhand der Eintraege wurde die Groesse der Matrix bestimmt (dim)
		// Nun sind die Werte in eine CSquareMatrixModN einzulesen

		// nur fuer Funktion my_char_to_int
		CHillEncryption hillklasse(theApp.TextOptions.refAlphabet());
		
		CSquareMatrixModN mat(dim,hillklasse.get_modul());

		for (i=0; i<dim; i++)
		{
			for (j=0; j<dim; j++)
			{
				CString cs;
				m_pControlFelder[i][j]->GetWindowText(cs);
				
				mat(i,j) = hillklasse.my_char_to_int(cs[0]);
			}
		}
		
		// Matrix invertieren
		CSquareMatrixModN inv_mat(dim,hillklasse.get_modul());
		BOOL b = mat.invert(&inv_mat);
		ASSERT(b);
		
		
		// Werte anzeigen
		for (i=0; i<dim; i++)
		{
			for (j=0; j<dim; j++)
			{
				CString cs;
				cs = hillklasse.my_int_to_char(inv_mat(i,j));
				
				ASSERT( (cs.GetLength() == 1) && (hillklasse.ist_erlaubtes_zeichen(cs[0])));
				m_pControlFelder[i][j]->SetWindowText(cs);
			}
		}

		HIDE_HOUR_GLASS
	}
}

BOOL CDlgShowKeyHill5x5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	m_pControlFelder[0][0] = &m_ControlFeld11;
	m_pControlFelder[0][1] = &m_ControlFeld12;
	m_pControlFelder[0][2] = &m_ControlFeld13;
	m_pControlFelder[0][3] = &m_ControlFeld14;
	m_pControlFelder[0][4] = &m_ControlFeld15;
	m_pControlFelder[1][0] = &m_ControlFeld21;
	m_pControlFelder[1][1] = &m_ControlFeld22;
	m_pControlFelder[1][2] = &m_ControlFeld23;
	m_pControlFelder[1][3] = &m_ControlFeld24;
	m_pControlFelder[1][4] = &m_ControlFeld25;
	m_pControlFelder[2][0] = &m_ControlFeld31;
	m_pControlFelder[2][1] = &m_ControlFeld32;
	m_pControlFelder[2][2] = &m_ControlFeld33;
	m_pControlFelder[2][3] = &m_ControlFeld34;
	m_pControlFelder[2][4] = &m_ControlFeld35;
	m_pControlFelder[3][0] = &m_ControlFeld41;
	m_pControlFelder[3][1] = &m_ControlFeld42;
	m_pControlFelder[3][2] = &m_ControlFeld43;
	m_pControlFelder[3][3] = &m_ControlFeld44;
	m_pControlFelder[3][4] = &m_ControlFeld45;
	m_pControlFelder[4][0] = &m_ControlFeld51;
	m_pControlFelder[4][1] = &m_ControlFeld52;
	m_pControlFelder[4][2] = &m_ControlFeld53;
	m_pControlFelder[4][3] = &m_ControlFeld54;
	m_pControlFelder[4][4] = &m_ControlFeld55;

	m_pControlAlphFelder[0][0] = &m_ControlAlphFeld36;
	m_pControlAlphFelder[0][1] = &m_ControlAlphFeld37;
	m_pControlAlphFelder[0][2] = &m_ControlAlphFeld38;
	m_pControlAlphFelder[0][3] = &m_ControlAlphFeld40;
	m_pControlAlphFelder[0][4] = &m_ControlAlphFeld46;
	m_pControlAlphFelder[1][0] = &m_ControlAlphFeld47;
	m_pControlAlphFelder[1][1] = &m_ControlAlphFeld48;
	m_pControlAlphFelder[1][2] = &m_ControlAlphFeld49;
	m_pControlAlphFelder[1][3] = &m_ControlAlphFeld50;
	m_pControlAlphFelder[1][4] = &m_ControlAlphFeld111;
	m_pControlAlphFelder[2][0] = &m_ControlAlphFeld57;
	m_pControlAlphFelder[2][1] = &m_ControlAlphFeld58;
	m_pControlAlphFelder[2][2] = &m_ControlAlphFeld59;
	m_pControlAlphFelder[2][3] = &m_ControlAlphFeld56;
	m_pControlAlphFelder[2][4] = &m_ControlAlphFeld115;
	m_pControlAlphFelder[3][0] = &m_ControlAlphFeld60;
	m_pControlAlphFelder[3][1] = &m_ControlAlphFeld61;
	m_pControlAlphFelder[3][2] = &m_ControlAlphFeld62;
	m_pControlAlphFelder[3][3] = &m_ControlAlphFeld116;
	m_pControlAlphFelder[3][4] = &m_ControlAlphFeld117;
	m_pControlAlphFelder[4][0] = &m_ControlAlphFeld63;
	m_pControlAlphFelder[4][1] = &m_ControlAlphFeld64;
	m_pControlAlphFelder[4][2] = &m_ControlAlphFeld69;
	m_pControlAlphFelder[4][3] = &m_ControlAlphFeld65;
	m_pControlAlphFelder[4][4] = &m_ControlAlphFeld66;
	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			m_pControlFelder[i][j]->SetFont(&cf);
			m_pControlAlphFelder[i][j]->SetFont(&cf);
		}
	}

	CString str;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			m_pControlFelder[i][j]->GetWindowText(str);
			m_pControlAlphFelder[i][j]->SetWindowText(getAlphCode(str));
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgShowKeyHill5x5::MatrixAnzeigen(CSquareMatrixModN& mat, int dim, CHillEncryption& hillklasse)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	CString cs;

	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			if (i<dim && j<dim)
			{
				// Wert anzeigen
				cs = hillklasse.my_int_to_char(mat(i,j));
			}
			else
			{
				// Feld leeren
				cs.Empty();
			}
			(*m_pFelder[i][j]) = cs;
		}
	}
	i_multDirection  = (iHillMultiplicationType) ? 0 : 1;
	m_alphabetOffset = (hillklasse.firstPosNull) ? 0 : 1;
}


void CDlgShowKeyHill5x5::OnVerschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();
	
	CString str;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			m_pControlFelder[i][j]->GetWindowText(str);
			m_pControlAlphFelder[i][j]->SetWindowText(getAlphCode(str));
		}
	}
}

void CDlgShowKeyHill5x5::OnEntschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();
	
	CString str;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			m_pControlFelder[i][j]->GetWindowText(str);
			m_pControlAlphFelder[i][j]->SetWindowText(getAlphCode(str));
		}
	}
}

void CDlgShowKeyHill5x5::OnKopieren() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	// Zuerst in cs die Matrix der Schlüssel aufbauen,
	// danach in das unsichtbare Feld schreiben und
	// schliesslich in diesem Feld alles markieren und in die Zwischenablage speichern

	UpdateData(TRUE);
//	m_decrypt = 0;  to copy also the inverse matrix
	UpdateData(FALSE);
	OnDecrypt();
	CString cs, hilf;

	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			m_pControlFelder[i][j]->GetWindowText(hilf);
			if (hilf.GetLength() == 1)
			{
				cs += hilf;
			}
			else
			{
				cs += ' ';
			}
		}
		if (i+1 < HILL_MAX_DIM) cs += '\n';
	}
	cs += HILLSTR_ALPHABETOFFSET;
	cs += ' ';
	cs += char('0' + m_alphabetOffset);
	cs += ' ';
	cs += HILLSTR_MULTVARIANT;
	cs += ' ';
	cs += char('0' + i_multDirection);
	cs += " \0";

    LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	CopyKey(pc_str, cs); 
	m_FeldUnsichtbar.SetWindowText(cs);
	m_FeldUnsichtbar.SetSel(0,-1);  // Alles markieren
 	m_FeldUnsichtbar.Copy();

	CDialog::OnOK();
}

void CDlgShowKeyHill5x5::SchluesselAnzeigen(CString Key)
{
	int pos = Key.Find(HILLSTR_ALPHABETOFFSET);
	int iLaenge = pos, iDimension = 1;
	pos += strlen(HILLSTR_ALPHABETOFFSET) +1;
	assert(pos > 0);
	m_alphabetOffset = (Key.GetAt(pos) == '0') ? 0 : 1;
	pos = Key.Find(HILLSTR_MULTVARIANT);
	assert(pos > 0);
	pos += strlen(HILLSTR_MULTVARIANT) +1;
	i_multDirection = (Key.GetAt(pos) == '0') ? 0 : 1;


	// Format: Zeilenweise Apspeicherung des Schluessel, jeweils durch ein Leerzeichen getrennt
	// iLaenge muss gleich i^2+(i-1) sein, 1 <= i <= HILL_MAX_DIM
	while ( ((iDimension*iDimension+(iDimension-1)) < iLaenge) && (iDimension <= HILL_MAX_DIM))
	{
		iDimension++;
	}

	ASSERT( (1 <= iDimension) && (iDimension <= HILL_MAX_DIM) );
	ASSERT( (iDimension*iDimension+(iDimension-1)) == iLaenge);

	CString hilf;
	for (int i=0; i<iDimension; i++)
	{
		for (int j=0; j<iDimension; j++)
		{
			hilf = Key[i*(iDimension+1)+j];
			(*m_pFelder[i][j]) = hilf;
		}
	}
}
CString CDlgShowKeyHill5x5::getAlphCode(CString alphChar)
{
	CString str;
	for(int i=0;i<theApp.TextOptions.getAlphabet().GetLength();i++)
	{
		if(theApp.TextOptions.getAlphabet()[i] == alphChar)
		{
			str.Format("%d",i+1);
			
			if(str.GetLength() == 1)
				str.Insert(0,"0");
			return str;
		}
	}
	return "";
}
