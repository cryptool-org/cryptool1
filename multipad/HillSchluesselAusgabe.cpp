//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// HillSchluesselAusgabe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "HillSchluesselAusgabe.h"
#include "sq_mat.h"
#include "KeyRepository.h"
#include "hill.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CHillSchluesselAusgabe 


CHillSchluesselAusgabe::CHillSchluesselAusgabe(CWnd* pParent /*=NULL*/)
	: CDialog(CHillSchluesselAusgabe::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHillSchluesselAusgabe)
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
}


void CHillSchluesselAusgabe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHillSchluesselAusgabe)
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
	DDX_Radio(pDX, IDC_RADIO1, m_decrypt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHillSchluesselAusgabe, CDialog)
	//{{AFX_MSG_MAP(CHillSchluesselAusgabe)
	ON_BN_CLICKED(IDC_DECRYPT, OnDecrypt)
	ON_BN_CLICKED(IDC_RADIO1, OnVerschluesseln)
	ON_BN_CLICKED(IDC_RADIO2, OnEntschluesseln)
	ON_BN_CLICKED(IDC_BUTTON1, OnKopieren)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CHillSchluesselAusgabe 

void CHillSchluesselAusgabe::OnDecrypt() 
{
	UpdateData(TRUE);

	if (m_decrypt != decrypt_vorher)
	{
		theApp.DoWaitCursor(1);

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
		// Nun sind die Werte in eine square_matrix einzulesen

		// nur fuer Funktion my_char_to_int
		hill hillklasse(theApp.TextOptions.m_alphabet.GetBuffer(0));
		
		square_matrix mat(dim,hillklasse.get_modul());

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
		square_matrix inv_mat(dim,hillklasse.get_modul());
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

		theApp.DoWaitCursor(0);
	}
}

BOOL CHillSchluesselAusgabe::OnInitDialog() 
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

	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			m_pControlFelder[i][j]->SetFont(&cf);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CHillSchluesselAusgabe::MatrixAnzeigen(square_matrix& mat, int dim, hill& hillklasse)
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
}


void CHillSchluesselAusgabe::OnVerschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();	
}

void CHillSchluesselAusgabe::OnEntschluesseln() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	OnDecrypt();
}

void CHillSchluesselAusgabe::OnKopieren() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	// Zuerst in cs die Matrix der Schlüssel aufbauen,
	// danach in das unsichtbare Feld schreiben und
	// schliesslich in diesem Feld alles markieren und in die Zwischenablage speichern

	UpdateData(TRUE);
	m_decrypt = 0;
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
		cs += '\n';
	}
    LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	CopyKey(pc_str, cs); 
	m_FeldUnsichtbar.SetWindowText(cs);
	m_FeldUnsichtbar.SetSel(0,-1);  // Alles markieren
 	m_FeldUnsichtbar.Copy();

	CDialog::OnOK();
}

void CHillSchluesselAusgabe::SchluesselAnzeigen(CString Key)
{
	int iLaenge = Key.GetLength(),
		iDimension = 1;

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
