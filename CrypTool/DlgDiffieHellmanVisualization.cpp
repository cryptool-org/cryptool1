// DlgDiffieHellmanVisualization.cpp

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanVisualization.h"

#include "DlgDiffieHellmanPublicParameters.h"
#include "DlgDiffieHellmanSetSecrets.h"
#include "DlgDiffieHellmanCreateSharedKey.h"
#include "DlgDiffieHellmanExchangeSharedKeys.h"
#include "DlgDiffieHellmanGenerateFinalKey.h"

#include "DlgDiffieHellmanSecretInput.h"

#include "DlgDiffieHellmanIntro.h"

#include "DlgDiffieHellmanSetPublicParameters.h"

#include "DlgDiffieHellmanKeyInformation.h"

#include "DiffieHellmanButtonControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanVisualization 


CDlgDiffieHellmanVisualization::CDlgDiffieHellmanVisualization(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanVisualization::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanVisualization)
	m_Generator = _T("");
	m_Prime = _T("");
	m_SecretAlice = _T("");
	m_SecretBob = _T("");
	m_SharedKeyAlice = _T("");
	m_SharedKeyBob = _T("");
	m_SessionKeyAlice = _T("");
	m_SessionKeyBob = _T("");
	m_bShowInfoDialogues = FALSE;
	//}}AFX_DATA_INIT

	// Initialisierungen
	this->Alice = NULL;
	this->Bob = NULL;
	this->pDiffieHellmanLogFile = NULL;
}

CDlgDiffieHellmanVisualization::~CDlgDiffieHellmanVisualization()
{
	// Freigabe von dynamisch allokiertem Speicher
	delete this->Alice;
	delete this->Bob;
	delete this->pButtonControl;
	delete this->pDiffieHellmanLogFile;
}

void CDlgDiffieHellmanVisualization::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanVisualization)
	DDX_Text(pDX, IDC_GENERATOR, m_Generator);
	DDX_Text(pDX, IDC_PRIME, m_Prime);
	DDX_Text(pDX, IDC_SECRETALICE, m_SecretAlice);
	DDX_Text(pDX, IDC_SECRETBOB, m_SecretBob);
	DDX_Text(pDX, IDC_SHAREDALICE, m_SharedKeyAlice);
	DDX_Text(pDX, IDC_SHAREDBOB, m_SharedKeyBob);
	DDX_Text(pDX, IDC_FINALALICE, m_SessionKeyAlice);
	DDX_Text(pDX, IDC_FINALBOB, m_SessionKeyBob);
	DDX_Check(pDX, IDC_CHECK_DISABLEHELP, m_bShowInfoDialogues);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanVisualization, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanVisualization)
	ON_BN_CLICKED(IDC_SETPUBLICPARAMETERS, OnSetPublicParameters)
	ON_BN_CLICKED(IDC_SETSECRETS, OnSetsecrets)
	ON_BN_CLICKED(IDC_CREATESHAREDKEY, OnCreatesharedkey)
	ON_BN_CLICKED(IDC_EXCHANGESHAREDKEYS, OnExchangesharedkeys)
	ON_BN_CLICKED(IDC_GENERATEFINALKEY, OnGeneratefinalkey)
	ON_BN_CLICKED(IDC_BUTTONALICE1, OnButtonalice1)
	ON_BN_CLICKED(IDC_BUTTONBOB1, OnButtonbob1)
	ON_BN_CLICKED(IDC_BUTTONALICE2, OnButtonalice2)
	ON_BN_CLICKED(IDC_BUTTONBOB2, OnButtonbob2)
	ON_BN_CLICKED(IDC_BUTTONALICE3, OnButtonalice3)
	ON_BN_CLICKED(IDC_BUTTONBOB3, OnButtonbob3)
	ON_BN_CLICKED(IDC_CHECK_DISABLEHELP, OnCheckDisablehelp)
	ON_BN_CLICKED(IDC_KEY, OnKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Diese Funktion wird aufgerufen, sobald der Benutzer die �ffentlichen Parameter f�r das Diffie-
// Hellman-Schl�sselaustausch-Verfahren setzen will
void CDlgDiffieHellmanVisualization::OnSetPublicParameters() 
{
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanSetPublicParameters dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}
		
	// Eingabe-Dialog f�r die �ffentlichen Parameter anzeigen
	CDlgDiffieHellmanPublicParameters dlg2;
	if(dlg2.DoModal() == IDCANCEL) return;

	// Benutzerangaben f�r g und p aus Eingabe-Dialog �bernehmen
	std::string g = (char*)(LPCTSTR)dlg2.m_Generator;
	std::string p = (char*)(LPCTSTR)dlg2.m_Prime;

	try
	{
		// Speicher freigeben, falls schon vorher Alice/Bob erzeugt wurden!
		if( Alice != NULL) delete Alice;
		if( Bob != NULL) delete Bob;
		
		// Den beiden Parteien die �ffentlichen Parameter zuweisen
		Alice = new DiffieHellmanParty(g,p);
		Bob = new DiffieHellmanParty(g,p);
		
		// Parameter f�r Benutzer sichtbar machen
		this->m_Generator = g.c_str();
		this->m_Prime = p.c_str();
		UpdateData(false);
				
	}
	// Exceptions auffangen und entsprechende Fehlermeldungen erzeugen
	catch(DHError& e) { CreateErrorMessage(e); return; }

	// Button mit Index 0 gedr�ckt
	this->UpdateGUI(0);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer die Geheimnisse f�r Alice und Bob festlegen will.
void CDlgDiffieHellmanVisualization::OnSetsecrets() 
{
	if(!this->CheckInternalStatus()) return;
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanSetSecrets dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// Button mit Index 1 gedr�ckt
	this->UpdateGUI(1);
}

// Diese Funktion wird augerufen, wenn der Benutzer die �ffentlichen Teilschl�ssel - sowohl von
// Alice als auch von Bob - festlegen m�chte.
void CDlgDiffieHellmanVisualization::OnCreatesharedkey() 
{
	if(!this->CheckInternalStatus()) return;
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanCreateSharedKey dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// Button mit Index 2 gedr�ckt
	this->UpdateGUI(2);
}

// Diese Funktion wird aufgerufen, falls der Benutzer die �ffentlichen Teilschl�ssel, die er zuvor festgelegt
// hat, zwischen Alice und Bob austauschen will. (Anmerkung: Alice UND Bob ben�tigen den �ffentlichen Teilschl�ssel
// des Gegen�bers f�r die Berechnung des Session Key. Der Austausch ist daher unabdingbar!)
void CDlgDiffieHellmanVisualization::OnExchangesharedkeys() 
{
	if(!this->CheckInternalStatus()) return;	
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanExchangeSharedKeys dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// Button mit Index 3 gedr�ckt
	this->UpdateGUI(3);
}

// Diese Funktion soll aufgerufen werden, sobald der Benutzer alle n�tigen Schritte durchgef�hrt hat und nun
// den Session Key f�r Alice und Bob berechnen will.
void CDlgDiffieHellmanVisualization::OnGeneratefinalkey() 
{
	if(!this->CheckInternalStatus()) return;	
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanGenerateFinalKey dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// Button mit Index 4 gedr�ckt
	this->UpdateGUI(4);
}

// Diese Funktion wird aufgerufen, wenn der Benutzer das Geheimnis f�r Alice w�hlen m�chte.
void CDlgDiffieHellmanVisualization::OnButtonalice1() 
{
	if(!this->CheckInternalStatus()) return;
	
	// Da die Verifikation des Geheimnisses vom zuvor gew�hlten Primzahlmodul p
	// abh�ngt, muss dem Konstruktor an dieser Stelle der Primzahlmodul per 
	// Parameter �bergeben werden. Anhand des ersten Parameters wird der Titel
	// des erscheinenden Dialogs generiert.
	CDlgDiffieHellmanSecretInput dlg("Alice",this->Alice->GetPrime());
	if(dlg.DoModal() == IDCANCEL) return;

	// Zugriff auf DH-Partei, ggf. Ausnahmebehandlung
	try{ this->Alice->SetSecret((char*)(LPCTSTR)dlg.m_Secret); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_SECRET_SUCCESSFULLY_SET_ALICE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}
	
	this->m_SecretAlice = dlg.m_Secret;
	UpdateData(false);

	// Button mit Index 5 gedr�ckt
	this->UpdateGUI(5);
}

// Diese Funktion wird aufgerufen, wenn der Benutzer das Geheimnis f�r Bob w�hlen m�chte.
void CDlgDiffieHellmanVisualization::OnButtonbob1() 
{
	if(!this->CheckInternalStatus()) return;
	
	// Da die Verifikation des Geheimnisses vom zuvor gew�hlten Primzahlmodul p
	// abh�ngt, muss dem Konstruktor an dieser Stelle der Primzahlmodul per 
	// Parameter �bergeben werden. Anhand des ersten Parameters wird der Titel
	// des erscheinenden Dialogs generiert.
	CDlgDiffieHellmanSecretInput dlg("Bob", this->Bob->GetPrime());
	if(dlg.DoModal() == IDCANCEL) return;

	try{ this->Bob->SetSecret((char*)(LPCTSTR)dlg.m_Secret); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(),IDS_DH_SECRET_SUCCESSFULLY_SET_BOB, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}
	
	this->m_SecretBob = dlg.m_Secret;
	UpdateData(false);

	// Button mit Index 6 gedr�ckt
	this->UpdateGUI(6);
}

// Diese Funktion wird augerufen, wenn der Benutzer den �ffentlichen Schl�ssel f�r Alice erzeugen will.
void CDlgDiffieHellmanVisualization::OnButtonalice2() 
{
	if(!this->CheckInternalStatus()) return;	

	try{ this->m_SharedKeyAlice = (char*)this->Alice->GetPublicKey().c_str(); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_CALCULATE_PUBLIC_KEY_ALICE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}
		
	UpdateData(false);

	// Button mit Index 7 gedr�ckt
	this->UpdateGUI(7);
}

// Diese Funktion wird augerufen, wenn der Benutzer den �ffentlichen Schl�ssel f�r Bob erzeugen will.
void CDlgDiffieHellmanVisualization::OnButtonbob2() 
{
	if(!this->CheckInternalStatus()) return;	

	try{ this->m_SharedKeyBob = (char*)this->Bob->GetPublicKey().c_str(); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_CALCULATE_PUBLIC_KEY_BOB, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}
	
	UpdateData(false);

	// Button mit Index 8 gedr�ckt
	this->UpdateGUI(8);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer den gemeinsamen und geheimen Schl�ssel von Alice und Bob
// F�R ALICE berechnen will (die Berechnungen f�r Alice und Bob laufen getrennt ab).
void CDlgDiffieHellmanVisualization::OnButtonalice3() 
{
	if(!this->CheckInternalStatus()) return;	

	try{ this->m_SessionKeyAlice = (char*)this->Alice->GetSessionKey(this->Bob->GetPublicKey()).c_str(); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_SESSION_KEY_CALCULATED_BY_ALICE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}

	UpdateData(false);

	// Button mit Index 9 gedr�ckt
	this->UpdateGUI(9);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer den gemeinsamen und geheimen Schl�ssel von Alice und Bob
// F�R ALICE berechnen will (die Berechnungen f�r Alice und Bob laufen getrennt ab).
void CDlgDiffieHellmanVisualization::OnButtonbob3() 
{
	if(!this->CheckInternalStatus()) return;	

	try{ this->m_SessionKeyBob = (char*)this->Bob->GetSessionKey(this->Alice->GetPublicKey()).c_str(); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_SESSION_KEY_CALCULATED_BY_BOB, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}
	
	UpdateData(false);

	// Button mit Index 10 gedr�ckt
	this->UpdateGUI(10);
}

BOOL CDlgDiffieHellmanVisualization::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Intro-Screen anzeigen (falls nicht in INI-Datei deaktiviert)
	if(theApp.GetProfileInt("Settings", "DH_IntroDialogue", 1))
	{
		CDlgDiffieHellmanIntro dlg;
		dlg.DoModal();
	}

	// Sollen die Hilfe-Dialoge angezeigt werden? (Abspeicherung ebenfalls in ini)
	if(theApp.GetProfileInt("Settings", "DH_InfoDialogues", 1))
	{
		this->m_bShowInfoDialogues = true;
	}

	this->pButtonControl = new DiffieHellmanBitmapButtonControl(this);

	UpdateData(false);
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}


// Diese Funktion erm�glicht die einfache und schnelle Anzeige verschiedener Fehlermeldungen.
// Der Funktion muss ausschlie�lich die Fehlermeldung, die angezeigt werden soll, als Parameter �bergeben werden.
void CDlgDiffieHellmanVisualization::CreateErrorMessage(DHError& e)
{
	// GENERATOR UNG�LTIG
	if(e.GetErrorCode() & E_GENERATOR_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_GENERATOR_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// PRIMZAHL UNG�LTIG
	if(e.GetErrorCode() & E_PRIME_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PRIME_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// GEHEIMNIS UNG�LTIG
	if(e.GetErrorCode() & E_SECRET_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_SECRET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// �FFENTL. SCHL�SSEL UNG�LTIG
	if(e.GetErrorCode() & E_PUBLIC_KEY_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PK_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// AND. �FFENTLICH. SCHL�SSEL UNG�LTIG
	if(e.GetErrorCode() & E_OTHERS_PUBLIC_KEY_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_OPK_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// SESSION KEY UNG�LTIG
	if(e.GetErrorCode() & E_SESSION_KEY_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_SESSION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
}

// Diese Funktion stellt sicher, dass die beiden Zeiger auf Alice und Bob NICHT NULL sind, damit keine
// Zugriffsverletzungen auftreten. Diese Funktion sollte deshalb BEIM DRUCK AUF JEDEN BUTTON
// aufgerufen werden, bevor mit den Zeigern auf Alice oder Bob gearbeitet wird.
bool CDlgDiffieHellmanVisualization::CheckInternalStatus()
{
	if(this->Alice != NULL && this->Bob != NULL) return true;

	LoadString(AfxGetInstanceHandle(), IDS_DH_DATA_INCONSISTENCY, pc_str, STR_LAENGE_STRING_TABLE);
	MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	
	return false;
}

// Diese Funktion informiert die Button-Kontrollstruktur dar�ber, welcher Button gedr�ckt wurde
// und l�scht entsprechende Textfelder, die nicht angezeigt werden d�rfen.
void CDlgDiffieHellmanVisualization::UpdateGUI(int b)
{
	// Zun�chst muss die Buttonstruktur aktualisiert werden
	this->pButtonControl->PerformAction(b);

	// Nun werden alle Textfelder, deren Inhalt nicht mehr sichtbar sein darf, gel�scht.
	if(b==0)
	{
		// es m�ssen ALLE Eingabefelder bis auf die �ffentlichen Parameter (Generator, Prime) gel�scht werden
		this->m_SecretAlice = "";
		this->m_SecretBob = "";
		this->m_SharedKeyAlice = "";
		this->m_SharedKeyBob = "";
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==1)
	{
		this->m_SecretAlice = "";
		this->m_SecretBob = "";
		this->m_SharedKeyAlice = "";
		this->m_SharedKeyBob = "";
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==2)
	{
		this->m_SharedKeyAlice = "";
		this->m_SharedKeyBob = "";
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==3)
	{
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==4)
	{
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==5)
	{
		this->m_SharedKeyAlice = "";
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==6)
	{
		this->m_SharedKeyBob = "";
		this->m_SessionKeyBob = "";
		this->m_SessionKeyAlice = "";
	}
	if(b==7)
	{
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==8)
	{
		this->m_SessionKeyAlice = "";
		this->m_SessionKeyBob = "";
	}
	if(b==9)
	{
		
	}
	if(b==10)
	{
		
	}

	// Falls Bob UND Alice f�r sich den Session Key bereits errechnet haben, wird das gemeinsame Ergebnis
	// im untersten Textfeld des Dialogs ausgegeben.
	if(this->pButtonControl->AllButtons[9].IsActionPerformed() && this->pButtonControl->AllButtons[10].IsActionPerformed())
	{
		if(this->m_bShowInfoDialogues)
		{
			LoadString(AfxGetInstanceHandle(), IDS_DH_RESULT_MESSAGE, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		}

		// Log-Datei erzeugen
		this->pDiffieHellmanLogFile = new DiffieHellmanLogFile(
			this->Alice->GetStrPrime(),
			this->Bob->GetStrGenerator(),
			this->Alice->GetStrSecret(),
			this->Bob->GetStrSecret(),
			this->Alice->GetPublicKey(),
			this->Bob->GetPublicKey(),
			this->Alice->GetSessionKey(this->Bob->GetPublicKey()),
			this->Bob->GetSessionKey(this->Alice->GetPublicKey()));
		
	}

	UpdateData(false);
}



// Der User hat die Check-Box "Informationsidaloge anzeigen" geklickt. Je nach aktuellem Zustand
// wird die Anzeige dieser Dialoge nun aktiviert oder deaktiviert.
void CDlgDiffieHellmanVisualization::OnCheckDisablehelp() 
{
	UpdateData(true);

	this->m_bShowInfoDialogues ? theApp.WriteProfileInt("Settings", "DH_InfoDialogues", 1) : theApp.WriteProfileInt("Settings", "DH_InfoDialogues", 0);
}

// Der User verlangt nach weiteren Informationen zum Session Key. Also wird der entsprechende
// Dialog aufgerufen. Als Parameter �bergibt man dem Dialog die errechneten Session Keys von 
// Alice und Bob sowie einen Zeiger auf die in der Dialogklasse CDlgDiffieHellmanVisualization 
// bereits erzeugte Diffie-Hellman-Log-Datei.
void CDlgDiffieHellmanVisualization::OnKey() 
{
	CDlgDiffieHellmanKeyInformation dlg((char*)(LPCTSTR)this->m_SessionKeyAlice, (char*)(LPCTSTR)this->m_SessionKeyBob, this->pDiffieHellmanLogFile);
	dlg.DoModal();
}
