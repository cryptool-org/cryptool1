//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// HillEingabe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHill5x5.h"
#include "HillEncryption.h"
#include "ChrTools.h"
#include "KeyRepository.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill5x5 


CDlgKeyHill5x5::CDlgKeyHill5x5(CHillEncryption *hillkl, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHill5x5::IDD, pParent)
{
	hillklasse = hillkl;
	m_decrypt = 0;
	//{{AFX_DATA_INIT(CDlgKeyHill5x5)
	m_Verbose = FALSE;
	//}}AFX_DATA_INIT
}

CDlgKeyHill5x5::~CDlgKeyHill5x5()
{
	if (mat)
	{
		delete mat;
	}
}

void CDlgKeyHill5x5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyHill5x5)
	DDX_Check(pDX, IDC_CHECK1, m_Verbose);
	DDX_Control(pDX, IDC_EDIT1, m_FeldUnsichtbar);
	DDX_Control(pDX, IDC_EDIT11, m_Feld11);
	DDX_Control(pDX, IDC_EDIT12, m_Feld12);
	DDX_Control(pDX, IDC_EDIT13, m_Feld13);
	DDX_Control(pDX, IDC_EDIT14, m_Feld14);
	DDX_Control(pDX, IDC_EDIT15, m_Feld15);
	DDX_Control(pDX, IDC_EDIT21, m_Feld21);
	DDX_Control(pDX, IDC_EDIT22, m_Feld22);
	DDX_Control(pDX, IDC_EDIT23, m_Feld23);
	DDX_Control(pDX, IDC_EDIT24, m_Feld24);
	DDX_Control(pDX, IDC_EDIT25, m_Feld25);
	DDX_Control(pDX, IDC_EDIT31, m_Feld31);
	DDX_Control(pDX, IDC_EDIT32, m_Feld32);
	DDX_Control(pDX, IDC_EDIT33, m_Feld33);
	DDX_Control(pDX, IDC_EDIT34, m_Feld34);
	DDX_Control(pDX, IDC_EDIT35, m_Feld35);
	DDX_Control(pDX, IDC_EDIT41, m_Feld41);
	DDX_Control(pDX, IDC_EDIT42, m_Feld42);
	DDX_Control(pDX, IDC_EDIT43, m_Feld43);
	DDX_Control(pDX, IDC_EDIT44, m_Feld44);
	DDX_Control(pDX, IDC_EDIT45, m_Feld45);
	DDX_Control(pDX, IDC_EDIT51, m_Feld51);
	DDX_Control(pDX, IDC_EDIT52, m_Feld52);
	DDX_Control(pDX, IDC_EDIT53, m_Feld53);
	DDX_Control(pDX, IDC_EDIT54, m_Feld54);
	DDX_Control(pDX, IDC_EDIT55, m_Feld55);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyHill5x5, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHill5x5)
	ON_BN_CLICKED(IDC_RADIO1, OnDimension1)
	ON_BN_CLICKED(IDC_RADIO2, OnDimension2)
	ON_BN_CLICKED(IDC_RADIO3, OnDimension3)
	ON_BN_CLICKED(IDC_RADIO4, OnDimension4)
	ON_BN_CLICKED(IDC_RADIO5, OnDimension5)
	ON_EN_UPDATE(IDC_EDIT11, OnUpdateMat11)
	ON_EN_UPDATE(IDC_EDIT12, OnUpdateMat12)
	ON_EN_UPDATE(IDC_EDIT13, OnUpdateMat13)
	ON_EN_UPDATE(IDC_EDIT14, OnUpdateMat14)
	ON_EN_UPDATE(IDC_EDIT15, OnUpdateMat15)
	ON_EN_UPDATE(IDC_EDIT21, OnUpdateMat21)
	ON_EN_UPDATE(IDC_EDIT22, OnUpdateMat22)
	ON_EN_UPDATE(IDC_EDIT23, OnUpdateMat23)
	ON_EN_UPDATE(IDC_EDIT24, OnUpdateMat24)
	ON_EN_UPDATE(IDC_EDIT25, OnUpdateMat25)
	ON_EN_UPDATE(IDC_EDIT31, OnUpdateMat31)
	ON_EN_UPDATE(IDC_EDIT32, OnUpdateMat32)
	ON_EN_UPDATE(IDC_EDIT33, OnUpdateMat33)
	ON_EN_UPDATE(IDC_EDIT34, OnUpdateMat34)
	ON_EN_UPDATE(IDC_EDIT35, OnUpdateMat35)
	ON_EN_UPDATE(IDC_EDIT41, OnUpdateMat41)
	ON_EN_UPDATE(IDC_EDIT42, OnUpdateMat42)
	ON_EN_UPDATE(IDC_EDIT43, OnUpdateMat43)
	ON_EN_UPDATE(IDC_EDIT44, OnUpdateMat44)
	ON_EN_UPDATE(IDC_EDIT45, OnUpdateMat45)
	ON_EN_UPDATE(IDC_EDIT51, OnUpdateMat51)
	ON_EN_UPDATE(IDC_EDIT52, OnUpdateMat52)
	ON_EN_UPDATE(IDC_EDIT53, OnUpdateMat53)
	ON_EN_UPDATE(IDC_EDIT54, OnUpdateMat54)
	ON_EN_UPDATE(IDC_EDIT55, OnUpdateMat55)
	ON_BN_CLICKED(IDC_BUTTON3, OnZufaelligerSchluessel)
	ON_BN_CLICKED(IDC_BUTTON4, OnGroessereSchluessel)
	ON_BN_CLICKED(IDC_BUTTON5, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHill5x5 


void CDlgKeyHill5x5::OnUpdateMat11() 
{
	// TODO: Wenn es sich hierbei um ein RICHEDIT-Steuerelement handelt, sendet es
	// sendet diese Benachrichtigung nur, wenn die Funktion CDialog::OnInitDialog()
	// überschrieben wird, um die EM_SETEVENTMASK-Nachricht an das Steuerelement
	// mit dem ENM_UPDATE-Attribut Ored in die Maske lParam zu senden.
	
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	UpdateFeld(m_pFelder[0][0]);
}

void CDlgKeyHill5x5::OnUpdateMat12() 
{
	UpdateFeld(m_pFelder[0][1]);
}

void CDlgKeyHill5x5::OnUpdateMat13() 
{
	UpdateFeld(m_pFelder[0][2]);
}

void CDlgKeyHill5x5::OnUpdateMat14() 
{
	UpdateFeld(m_pFelder[0][3]);
}

void CDlgKeyHill5x5::OnUpdateMat15() 
{
	UpdateFeld(m_pFelder[0][4]);
}

void CDlgKeyHill5x5::OnUpdateMat21() 
{
	UpdateFeld(m_pFelder[1][0]);
}

void CDlgKeyHill5x5::OnUpdateMat22() 
{
	UpdateFeld(m_pFelder[1][1]);
}

void CDlgKeyHill5x5::OnUpdateMat23() 
{
	UpdateFeld(m_pFelder[1][2]);
}

void CDlgKeyHill5x5::OnUpdateMat24() 
{
	UpdateFeld(m_pFelder[1][3]);
}

void CDlgKeyHill5x5::OnUpdateMat25() 
{
	UpdateFeld(m_pFelder[1][4]);
}

void CDlgKeyHill5x5::OnUpdateMat31() 
{
	UpdateFeld(m_pFelder[2][0]);
}

void CDlgKeyHill5x5::OnUpdateMat32() 
{
	UpdateFeld(m_pFelder[2][1]);
}

void CDlgKeyHill5x5::OnUpdateMat33() 
{
	UpdateFeld(m_pFelder[2][2]);
}

void CDlgKeyHill5x5::OnUpdateMat34() 
{
	UpdateFeld(m_pFelder[2][3]);
}

void CDlgKeyHill5x5::OnUpdateMat35() 
{
	UpdateFeld(m_pFelder[2][4]);
}

void CDlgKeyHill5x5::OnUpdateMat41() 
{
	UpdateFeld(m_pFelder[3][0]);
}

void CDlgKeyHill5x5::OnUpdateMat42() 
{
	UpdateFeld(m_pFelder[3][1]);
}

void CDlgKeyHill5x5::OnUpdateMat43() 
{
	UpdateFeld(m_pFelder[3][2]);
}

void CDlgKeyHill5x5::OnUpdateMat44() 
{
	UpdateFeld(m_pFelder[3][3]);
}

void CDlgKeyHill5x5::OnUpdateMat45() 
{
	UpdateFeld(m_pFelder[3][4]);
}

void CDlgKeyHill5x5::OnUpdateMat51() 
{
	UpdateFeld(m_pFelder[4][0]);
}

void CDlgKeyHill5x5::OnUpdateMat52() 
{
	UpdateFeld(m_pFelder[4][1]);
}

void CDlgKeyHill5x5::OnUpdateMat53() 
{
	UpdateFeld(m_pFelder[4][2]);
}

void CDlgKeyHill5x5::OnUpdateMat54() 
{
	UpdateFeld(m_pFelder[4][3]);
}

void CDlgKeyHill5x5::OnUpdateMat55() 
{
	UpdateFeld(m_pFelder[4][4]);
}


void CDlgKeyHill5x5::UpdateFeld(CEdit *feld)
{
	CString cs;
	feld->GetWindowText(cs);

	if (cs.GetLength() == 1)
	{
		if ( hillklasse->ist_erlaubtes_zeichen(cs[0]) )
		{
			// zum naechsten Feld springen
			NextDlgCtrl();
		}
		else if ( (theApp.TextOptions.m_IgnoreCase) && (MyIsLower(cs[0])) && 
			     (hillklasse->ist_erlaubtes_zeichen(MyToUpper(cs[0]))) )
		{
			// Zeichen in Grossbuchstaben umwandeln und anzeigen
			char c;
			c = MyToUpper(cs[0]);
			cs.SetAt(0,c);
			feld->SetWindowText(cs);
			// Jetzt wird die Funktion UpdateFeld erneut aufgerufen, daher darf
			// kein Sprung ins naechste Feld gemacht werden,
			// da das Programm wieder in diese funktion, dieses Mal in den
			// ersten Fall kommt. 
			// // zum naechsten Feld springen
			// NextDlgCtrl();
		}
		else
		{
			// Zeichen loeschen und Cursor wieder auf Anfang positionieren.
			// (Cursorpositionierung vor erstes moegliches Eingabezeichen
			// erfolgt mit leerem String automatisch.)
			cs.Empty();
			feld->SetWindowText(cs);
		}
	}
}


int CDlgKeyHill5x5::Display(CHillEncryption *hillklasse)
{
	int res;

	res=DoModal();

	//	MakeBin(m_einstr, buffer);
	
	return res;
}

void CDlgKeyHill5x5::OnOK() 
{

	// Matrizen anlegen und Daten aus Eingabefenster auslesen
	CSquareMatrixModN mat1(dim,hillklasse->get_modul());

	// mat muss wieder freigegeben werden, wenn nicht mehr benoetigt !
	// Dies geschieht im Destruktor
	mat = new CSquareMatrixModN(dim,hillklasse->get_modul());

	// Ueberpruefen, ob alle Felder der Matrix gefuellt sind
	// Falls ein Fehler ausgetreten ist (mindestens eine Eingabe fehlt),
	// zu der ersten fehlenden Eingabe springen (und Funktion verlasssen).
	if (! AlleFelderKorrekt(dim))
	{
		return;
	}

	// Matrix mit den Werten aus der Eingabemaske fuellen
	MatrixEinlesen(*mat, dim);
	
	// Falls die Matrix nicht invertierbar ist, wieder ins Fenster zurueckspringen
	if ( ! mat->invert(&mat1))
	{
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_INV,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
		return;
	}
	else
	{
		m_decrypt = 0;
		CDialog::OnOK();
	}
}

void CDlgKeyHill5x5::OnDecrypt()
{

	// Matrizen anlegen und Daten aus Eingabefenster auslesen
	CSquareMatrixModN mat1(dim,hillklasse->get_modul());

	// mat muss wieder freigegeben werden, wenn nicht mehr benoetigt !
	// Dies geschieht im Destruktor
	mat = new CSquareMatrixModN(dim,hillklasse->get_modul());

	// Ueberpruefen, ob alle Felder der Matrix gefuellt sind
	// Falls ein Fehler ausgetreten ist (mindestens eine Eingabe fehlt),
	// zu der ersten fehlenden Eingabe springen (und Funktion verlasssen).
	if (! AlleFelderKorrekt(dim))
	{
		return;
	}

	// Matrix mit den Werten aus der Eingabemaske fuellen
	MatrixEinlesen(*mat, dim);
	
	// Falls die Matrix nicht invertierbar ist, wieder ins Fenster zurueckspringen
	if ( ! mat->invert(&mat1))
	{
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_INV,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
		m_pFelder[0][0]->SetFocus();
		m_pFelder[0][0]->SetSel(0,-1);
		return;
	}
	else
	{
		m_decrypt = 1;
		CDialog::OnOK();
	}
}

BOOL CDlgKeyHill5x5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

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

	
	// Font mit fester Breite erstellen und fuer alle Schluesselfelder setzen
	cf.CreatePointFont(80,"Courier");
	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			m_pFelder[i][j]->SetFont(&cf);
		}
	}

	if (iHillSchluesselDim > HILL_MAX_DIM)
	{
		iHillSchluesselDim = HILL_MAX_DIM;
	}

	ASSERT ((0 <= iHillSchluesselDim) && (iHillSchluesselDim <= HILL_MAX_DIM));
	dim = iHillSchluesselDim;

	switch (iHillSchluesselDim)
	{
	case 1:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO1);
		break;
	case 2:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
		break;
	case 3:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO3);
		break;
	case 4:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO4);
		break;
	case 5:	
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO5);
		break;
	default:
		// Default Dimension = 2
		dim = 2;
		iHillSchluesselDim = dim;
		CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
		break;
	}

	// Default: Verschlüsseln
	CheckRadioButton(IDC_RADIO15, IDC_RADIO16, IDC_RADIO15);

	AnzeigeDimensionSetzen(dim);

	// Die Matrix enthaelt am Ende die Daten der Eingabemaske
	// Sie wird in der Nachrichtenbehandlungsfunktion "OnOK" angelegt und 
	// im Destruktor wieder freigegeben.
	mat = 0;

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgKeyHill5x5::OnDimension1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 1;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CDlgKeyHill5x5::OnDimension2() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 2;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CDlgKeyHill5x5::OnDimension3() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 3;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CDlgKeyHill5x5::OnDimension4() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	dim = 4;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CDlgKeyHill5x5::OnDimension5() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	dim = 5;
	iHillSchluesselDim = dim;
	AnzeigeDimensionSetzen(dim);

	m_pFelder[0][0]->SetFocus();
	m_pFelder[0][0]->SetSel(0,-1);
}

void CDlgKeyHill5x5::AnzeigeDimensionSetzen(int dim)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	BOOL mybool;

	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			if (i<dim && j<dim)
			{
				// Eine Eingabe in die Felder muss moeglich sein
				mybool = TRUE;
			}
			else
			{
				// Eine Eingabe in die Felder darf nicht moeglich sein
				mybool = FALSE;
			}
			m_pFelder[i][j]->EnableWindow(mybool);
		}
	}
}

int CDlgKeyHill5x5::AlleFelderKorrekt(int dim)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	CString cs;

	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			m_pFelder[i][j]->GetWindowText(cs);

			// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
			// deshalb muss dies hier nicht mehr abgefragt werden.
			if ( (cs.GetLength() == 0) || (! hillklasse->ist_erlaubtes_zeichen(cs[0])) )
			{
				LoadString(AfxGetInstanceHandle(),IDS_HILL_BAD_KEY_NONVALID_CHAR,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED,pc_str1,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
				m_pFelder[i][j]->SetFocus();
				m_pFelder[i][j]->SetSel(0,-1);
				return FALSE;
			}
		}
	}

	return TRUE;
}

void CDlgKeyHill5x5::MatrixEinlesen(CSquareMatrixModN& mat, int dim)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	CString cs;

	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			m_pFelder[i][j]->GetWindowText(cs);

			// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
			// deshalb muss dies hier nicht mehr beruecksichtigt werden.
			ASSERT(hillklasse->ist_erlaubtes_zeichen(cs[0]));
			mat(i,j) = hillklasse->my_char_to_int(cs[0]);
		}
	}
}

void CDlgKeyHill5x5::MatrixAnzeigen(CSquareMatrixModN& mat)
{
	int dimension = mat.get_dim();

	ASSERT ((1 <= dimension) && (dimension <= HILL_MAX_DIM));

	CString cs;

	for (int i=0; i<dimension; i++)
	{
		for (int j=0; j<dimension; j++)
		{
			cs = hillklasse->my_int_to_char(mat(i,j));
			m_pFelder[i][j]->SetWindowText(cs);
		}
	}
}


// Die Position fuer den naechsten Eintrag in der Schluesselmatrix wird berechnet.
// Falls kein weiterer Eintrag mehr zur Verfuegung steht, wird FALSE zurueckgegeben,
// im anderen Fall TRUE.
bool CDlgKeyHill5x5::NaechsterEintrag(int &i, int &j) 
{
	bool rc = true;

	j++;
	if (j == HILL_MAX_DIM)
	{
		// Wir starten in der naechsten Zeile wieder vorne, ...
		i++;
		j = 0;
		// ... sofern es noch eine weitere gibt.
		if (i == HILL_MAX_DIM)
		{
			// Es gibt keine weitere Zeile
			rc = false;
		}
	}

	return rc;
}


void CDlgKeyHill5x5::OnPasteKey() 
{
	CString cs, hilf;

	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	if ( PasteKey(pc_str,cs) )
	{

 		int i=0,          // Zeile des naechsten Eintrages in die Schluesselmatrix
 			j=-1,         // Spalte des naechsten Eintrages in die Schluesselmatrix 
 			l=0,          // Laufvariable fuer den Text aus der Zwischenablage
 			laenge = cs.GetLength(); // Laenge des Textes der Zwischenablage
		int keyDim = 0;
		while (l<laenge) {
			hilf = cs[l++];
			if (hillklasse->ist_erlaubtes_zeichen(hilf[0])) i++;
		}
		
		if ( i <= HILL_MAX_DIM*HILL_MAX_DIM )
		{	
			i = l = 0;
 			while (l < laenge)
 			{
 				hilf = cs[l];
 
				// Kleinbuchstaben wurden schon zu Grossbuchstaben konvertiert, sofern erforderlich;
				// deshalb muss dies hier nicht mehr abgefragt werden.
				if (hillklasse->ist_erlaubtes_zeichen(hilf[0]))
				{
 					// Naechsten Eintrag berechnen
 					if (NaechsterEintrag(i,j))
 					{
 						// Wert einfach uebernehmen
						m_pFelder[i][j]->SetWindowText(hilf);
 					}
 					else
 					{
 						// Es gibt keine weitere Zeile
 						l = laenge;
 					}
 				}
 				else if (hilf[0] == '\n')
 				{
 					// Wir starten in der naechsten Zeile wieder vorne,
 					// sofern wir nicht schon am Anfang einer Zeile stehen...
					if (keyDim == 0) keyDim = j+1;
					else if ( j >= 0 && j+1 != keyDim ) {
						/* ToDo: Fehler Meldung */
						return; 
					}
 					i++;
 					j = -1;
 					// ... sofern es noch eine weitere gibt.
 					if (i == HILL_MAX_DIM)
 					{
 						// Es gibt keine weitere Zeile
 						l = laenge;
 					}
 				}
 
 				l++;
 			}

			// if ( j < 0 ) i--;
			ASSERT ((0 <= keyDim) && (keyDim <= HILL_MAX_DIM));
			dim = keyDim;
			iHillSchluesselDim = dim;

			switch (iHillSchluesselDim)
			{
			case 1:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO1);
				OnDimension1();
				break;
			case 2:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
				OnDimension2();
				break;
			case 3:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO3);
				OnDimension3();
				break;
			case 4:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO4);
				OnDimension4();
				break;
			case 5:	
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO5);
				OnDimension5();
				break;
			default:
				// Default Dimension = 2
				dim = 2;
				iHillSchluesselDim = dim;
				CheckRadioButton(IDC_RADIO1, IDC_RADIO5, IDC_RADIO2);
				OnDimension2();
				break;
			}
			AnzeigeDimensionSetzen(dim);
			// Cursor in Feld links oben setzen
 			m_pFelder[0][0]->SetFocus();
 			m_pFelder[0][0]->SetSel(0,-1);
		}
 		else
		{  
			// Message ... the stored Hill Key ...
		}
	}
}


void CDlgKeyHill5x5::OnCopyKey()
{
	CString cs, hilf;

	for (int i=0; i<HILL_MAX_DIM; i++)
	{
		for (int j=0; j<HILL_MAX_DIM; j++)
		{
			m_pFelder[i][j]->GetWindowText(hilf);			
			if (i < dim && j < dim)
			{
				cs += hilf;
			}
			else
			{
				cs += ' ';
			}
		}
		if ( i+1 < HILL_MAX_DIM )
		{
			cs += '\n';
		}
	}
    LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);
	CopyKey(pc_str, cs); 
	m_Paste.EnableWindow(TRUE);
}



void CDlgKeyHill5x5::OnZufaelligerSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	// Zuerst eine zufaellige Matrix erzeugen und im Anschluss
	// in die Maske schreiben
	CSquareMatrixModN mat1(dim, hillklasse->get_modul());
	if (mat1.zufaellige_invertierbare_matrix())
	{
		MatrixAnzeigen(mat1);
		m_pFelder[0][0]->SetFocus();
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ON_WRONG_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, NULL, MB_ICONERROR|MB_OK);

	}
}


void CDlgKeyHill5x5::OnGroessereSchluessel() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen

	iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_GROSS;

	CDialog::OnOK();	
}

BEGIN_MESSAGE_MAP(CHiEdit, CEdit)
	//{{AFX_MSG_MAP(CHiEdit)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHiEdit::OnLButtonUp(UINT nFlags, CPoint point )
{
	CEdit::OnLButtonUp(nFlags,point);
	SetSel(0, -1);
} 
