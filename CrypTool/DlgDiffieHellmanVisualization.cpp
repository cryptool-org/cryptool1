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
#include "DlgDiffieHellmanFinalInfo.h"
#include "CrypToolTools.h"

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
	m_bShowIntroDialog = FALSE;
	//}}AFX_DATA_INIT

	// Initialisierungen
	this->Alice = NULL;
	this->Bob = NULL;
	this->pDiffieHellmanLogFile = NULL;

	// Zu Beginn keine GIFs geladen
	this->m_bAnimatedGIFLoaded = false;
	this->m_bStaticGIFLoaded = false;
}

CDlgDiffieHellmanVisualization::~CDlgDiffieHellmanVisualization()
{
	// Freigabe von dynamisch allokiertem Speicher
	delete this->Alice;
	delete this->Bob;
	delete this->pButtonControl;
	delete this->pDiffieHellmanLogFile;
	
	if( this->m_bAnimatedGIFLoaded || this->m_bStaticGIFLoaded )
	{
		m_AnimGif.UnLoad();
		this->m_bAnimatedGIFLoaded = false;
		this->m_bStaticGIFLoaded = false;
	}
}

void CDlgDiffieHellmanVisualization::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanVisualization)
	DDX_Control(pDX, IDC_ANIMGIF, m_AnimGif);
	DDX_Text(pDX, IDC_GENERATOR, m_Generator);
	DDX_Text(pDX, IDC_PRIME, m_Prime);
	DDX_Text(pDX, IDC_SECRETALICE, m_SecretAlice);
	DDX_Text(pDX, IDC_SECRETBOB, m_SecretBob);
	DDX_Text(pDX, IDC_SHAREDALICE, m_SharedKeyAlice);
	DDX_Text(pDX, IDC_SHAREDBOB, m_SharedKeyBob);
	DDX_Text(pDX, IDC_FINALALICE, m_SessionKeyAlice);
	DDX_Text(pDX, IDC_FINALBOB, m_SessionKeyBob);
	DDX_Check(pDX, IDC_CHECK_DISABLEHELP, m_bShowInfoDialogues);
	DDX_Check(pDX, IDC_CHECK_DISABLEINTRODUCTION, m_bShowIntroDialog);
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
	ON_BN_CLICKED(IDC_CHECK_DISABLEINTRODUCTION, OnCheckDisableIntroDialog)
	ON_BN_CLICKED(IDC_KEY, OnKey)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// Diese Funktion wird aufgerufen, sobald der Benutzer die öffentlichen Parameter für das Diffie-
// Hellman-Schlüsselaustausch-Verfahren setzen will
void CDlgDiffieHellmanVisualization::OnSetPublicParameters() 
{
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanSetPublicParameters dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}
		
	// Eingabe-Dialog für die öffentlichen Parameter anzeigen
	CDlgDiffieHellmanPublicParameters *dlg2;
	// Falls zuvor bereits Werte für g und p gesetzt wurden, wird der Dialog damit initialisiert
	if(Alice != NULL && Bob != NULL) 
		dlg2 = new CDlgDiffieHellmanPublicParameters(Alice->GetStrPrime(), Alice->GetStrGenerator());
	else
		dlg2 = new CDlgDiffieHellmanPublicParameters();

	if(dlg2->DoModal() == IDCANCEL)
	{
		// Speicher freigeben
		delete dlg2;
		return;
	}

	// Benutzerangaben für g und p aus Eingabe-Dialog übernehmen
	std::string g = (char*)(LPCTSTR)dlg2->m_Generator;
	std::string p = (char*)(LPCTSTR)dlg2->m_Prime;

	if (!dlg2->b_isSavePrime)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_NO_SAVE_PRIME, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);		
	}

	// Speicher freigeben
	delete dlg2;

	try
	{
		// Speicher freigeben, falls schon vorher Alice/Bob erzeugt wurden!
		if( Alice != NULL) delete Alice;
		if( Bob != NULL) delete Bob;
		
		// Den beiden Parteien die öffentlichen Parameter zuweisen
		Alice = new DiffieHellmanParty(g,p);
		Bob = new DiffieHellmanParty(g,p);
		
		// Parameter für Benutzer sichtbar machen
		this->m_Generator = g.c_str();
		this->m_Prime = p.c_str();
		UpdateData(false);
				
	}
	// Exceptions auffangen und entsprechende Fehlermeldungen erzeugen
	catch(DHError& e) { CreateErrorMessage(e); return; }

	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);

	// Button mit Index 0 gedrückt
	this->UpdateGUI(0);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer die Geheimnisse für Alice und Bob festlegen will.
void CDlgDiffieHellmanVisualization::OnSetsecrets() 
{
	if(!this->CheckInternalStatus()) return;
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanSetSecrets dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);

	// Button mit Index 1 gedrückt
	this->UpdateGUI(1);
}

// Diese Funktion wird augerufen, wenn der Benutzer die öffentlichen Teilschlüssel - sowohl von
// Alice als auch von Bob - festlegen möchte.
void CDlgDiffieHellmanVisualization::OnCreatesharedkey() 
{
	if(!this->CheckInternalStatus()) return;
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanCreateSharedKey dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);

	// Button mit Index 2 gedrückt
	this->UpdateGUI(2);
}

// Diese Funktion wird aufgerufen, falls der Benutzer die öffentlichen Teilschlüssel, die er zuvor festgelegt
// hat, zwischen Alice und Bob austauschen will. (Anmerkung: Alice UND Bob benötigen den öffentlichen Teilschlüssel
// des Gegenübers für die Berechnung des Session Key. Der Austausch ist daher unabdingbar!)
void CDlgDiffieHellmanVisualization::OnExchangesharedkeys() 
{
	if(!this->CheckInternalStatus()) return;	
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanExchangeSharedKeys dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// GIF Animation starten
	this->ShowAnimatedGIF();

	// Button mit Index 3 gedrückt
	this->UpdateGUI(3);
}

// Diese Funktion soll aufgerufen werden, sobald der Benutzer alle nötigen Schritte durchgeführt hat und nun
// den Session Key für Alice und Bob berechnen will.
void CDlgDiffieHellmanVisualization::OnGeneratefinalkey() 
{
	if(!this->CheckInternalStatus()) return;	
	
	if(this->m_bShowInfoDialogues)
	{
		CDlgDiffieHellmanGenerateFinalKey dlg;
		if(dlg.DoModal() == IDCANCEL) return;
	}

	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF2);

	// Button mit Index 4 gedrückt
	this->UpdateGUI(4);
}

// Diese Funktion wird aufgerufen, wenn der Benutzer das Geheimnis für Alice wählen möchte.
void CDlgDiffieHellmanVisualization::OnButtonalice1() 
{
	if(!this->CheckInternalStatus()) return;
	
	// Da die Verifikation des Geheimnisses vom zuvor gewählten Primzahlmodul p
	// abhängt, muss dem Konstruktor an dieser Stelle der Primzahlmodul per 
	// Parameter übergeben werden. Anhand des ersten Parameters wird der Titel
	// des erscheinenden Dialogs generiert.

	// Weiterhin wird ggf. das zuvor eingegebene Geheimnis "voreingestellt", sofern
	// der Benutzer ein Geheimnis zum zweiten Mal festlegen will (bzw. widerrufen will)

	CDlgDiffieHellmanSecretInput *dlg;

	if(Alice->HasSecret()) dlg = new CDlgDiffieHellmanSecretInput("Alice", Alice->GetStrSecret(), Alice->GetPrime());
	else dlg = new CDlgDiffieHellmanSecretInput("Alice", this->Alice->GetPrime());
	
	if(dlg->DoModal() == IDCANCEL) return;

	// Zugriff auf DH-Partei, ggf. Ausnahmebehandlung
	try{ this->Alice->SetSecret((char*)(LPCTSTR)dlg->m_Secret); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_SECRET_SUCCESSFULLY_SET_ALICE, pc_str, STR_LAENGE_STRING_TABLE);
		if ( dlg->SecretExceedsPrime() )
		{
			char tmp[1024];
			LoadString(AfxGetInstanceHandle(),IDS_DH_SECRET_EXCEEDS_PRIME, tmp, STR_LAENGE_STRING_TABLE);
			strcat(pc_str, "\n\n");
			strcat(pc_str, tmp);
		}
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}
	
	this->m_SecretAlice = dlg->m_Secret;
	
	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);
	
	UpdateData(false);

	// Speicher freigeben
	delete dlg;

	// Button mit Index 5 gedrückt
	this->UpdateGUI(5);
}

// Diese Funktion wird aufgerufen, wenn der Benutzer das Geheimnis für Bob wählen möchte.
void CDlgDiffieHellmanVisualization::OnButtonbob1() 
{
	if(!this->CheckInternalStatus()) return;
	
	// Da die Verifikation des Geheimnisses vom zuvor gewählten Primzahlmodul p
	// abhängt, muss dem Konstruktor an dieser Stelle der Primzahlmodul per 
	// Parameter übergeben werden. Anhand des ersten Parameters wird der Titel
	// des erscheinenden Dialogs generiert.
	CDlgDiffieHellmanSecretInput *dlg;
	
	if(Bob->HasSecret()) dlg = new CDlgDiffieHellmanSecretInput("Bob", Bob->GetStrSecret(), this->Bob->GetPrime());
	else dlg = new CDlgDiffieHellmanSecretInput("Bob", Bob->GetPrime());

	if(dlg->DoModal() == IDCANCEL) return;

	try{ this->Bob->SetSecret((char*)(LPCTSTR)dlg->m_Secret); }
	catch(DHError& e){ CreateErrorMessage(e); return; }

	if(this->m_bShowInfoDialogues)
	{
		LoadString(AfxGetInstanceHandle(),IDS_DH_SECRET_SUCCESSFULLY_SET_BOB, pc_str, STR_LAENGE_STRING_TABLE);
		if ( dlg->SecretExceedsPrime() )
		{
			char tmp[1024];
			LoadString(AfxGetInstanceHandle(),IDS_DH_SECRET_EXCEEDS_PRIME, tmp, STR_LAENGE_STRING_TABLE);
			strcat(pc_str, "\n\n");
			strcat(pc_str, tmp);
		}
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}
	
	this->m_SecretBob = dlg->m_Secret;
	
	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);
	
	UpdateData(false);

	// Speicher freigeben
	delete dlg;

	// Button mit Index 6 gedrückt
	this->UpdateGUI(6);
}

// Diese Funktion wird augerufen, wenn der Benutzer den öffentlichen Schlüssel für Alice erzeugen will.
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
		
	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);

	UpdateData(false);

	// Button mit Index 7 gedrückt
	this->UpdateGUI(7);
}

// Diese Funktion wird augerufen, wenn der Benutzer den öffentlichen Schlüssel für Bob erzeugen will.
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
	
	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);

	UpdateData(false);

	// Button mit Index 8 gedrückt
	this->UpdateGUI(8);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer den gemeinsamen und geheimen Schlüssel von Alice und Bob
// FÜR ALICE berechnen will (die Berechnungen für Alice und Bob laufen getrennt ab).
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

	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF2);

	UpdateData(false);

	// Button mit Index 9 gedrückt
	this->UpdateGUI(9);
}

// Diese Funktion wird aufgerufen, sobald der Benutzer den gemeinsamen und geheimen Schlüssel von Alice und Bob
// FÜR ALICE berechnen will (die Berechnungen für Alice und Bob laufen getrennt ab).
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

	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF2);
	
	UpdateData(false);

	// Button mit Index 10 gedrückt
	this->UpdateGUI(10);
}

BOOL CDlgDiffieHellmanVisualization::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "DiffieHellman" ) == ERROR_SUCCESS ) {
		// flomar, 07/15/2010
		// make sure we're correctly writing the user choice back to the registry
		unsigned long showIntroDialog = TRUE;
		CT_READ_REGISTRY(showIntroDialog, "ShowIntroDialog");
		if(showIntroDialog) {
			CDlgDiffieHellmanIntro dlg;
			dlg.DoModal();
			if(dlg.m_Check_NoShow == TRUE) {
				showIntroDialog = FALSE;
				CT_WRITE_REGISTRY(showIntroDialog, "ShowIntroDialog");
			}
		}

		unsigned long u_showInfoDialogues = TRUE;
		CT_READ_REGISTRY_DEFAULT(u_showInfoDialogues, "ShowInfo", u_showInfoDialogues);
		m_bShowInfoDialogues = u_showInfoDialogues;		

		CT_CLOSE_REGISTRY();

		UpdateData(false);
	}
	else
	{
		// FIXME
	}


	this->pButtonControl = new DiffieHellmanBitmapButtonControl(this);

	// Farben für Textfelder etc. festlegen
	this->m_greycolor=0x00C0C0C0; // RGB(0x00C0C0C0/*198,195,198*/);	// Standard-Grau
	this->m_greybrush.CreateSolidBrush(m_greycolor);
	this->m_blackcolor=RGB(0,0,0); // Schwarz
	this->m_blackbrush.CreateSolidBrush(m_blackcolor);
	
	// Statische GIF-Anim einblenden
	this->ShowStaticGIF(IDR_GIF3);

	// ToolTip kreieren und aktivieren (vgl. auch PreTranslateMessage)
	pToolTipKey = new CToolTipCtrl;
	pToolTipKey->Create(this);
	pToolTipKey->AddTool(GetDlgItem(IDC_KEY), IDS_DH_VISUALIZATION_TOOLTIPKEY);
	pToolTipKey->Activate(TRUE);
	
	UpdateData(false);

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CDlgDiffieHellmanVisualization::PreTranslateMessage(MSG* pMsg)
{
	// diese Zeile ist notwendig, damit die Tooltips funktionieren (warum auch immer)
	if(pToolTipKey) pToolTipKey->RelayEvent(pMsg);

    return CDialog::PreTranslateMessage(pMsg);
}


// Diese Funktion ermöglicht die einfache und schnelle Anzeige verschiedener Fehlermeldungen.
// Der Funktion muss ausschließlich die Fehlermeldung, die angezeigt werden soll, als Parameter übergeben werden.
void CDlgDiffieHellmanVisualization::CreateErrorMessage(DHError& e)
{
	// GENERATOR UNGÜLTIG
	if(e.GetErrorCode() & E_GENERATOR_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_GENERATOR_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// PRIMZAHL UNGÜLTIG
	if(e.GetErrorCode() & E_PRIME_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PRIME_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// GEHEIMNIS UNGÜLTIG
	if(e.GetErrorCode() & E_SECRET_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_SECRET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// ÖFFENTL. SCHLÜSSEL UNGÜLTIG
	if(e.GetErrorCode() & E_PUBLIC_KEY_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PK_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// AND. ÖFFENTLICH. SCHLÜSSEL UNGÜLTIG
	if(e.GetErrorCode() & E_OTHERS_PUBLIC_KEY_INVALID)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_OPK_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	}
	// SESSION KEY UNGÜLTIG
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

// Diese Funktion informiert die Button-Kontrollstruktur darüber, welcher Button gedrückt wurde
// und löscht entsprechende Textfelder, die nicht angezeigt werden dürfen.
void CDlgDiffieHellmanVisualization::UpdateGUI(int b)
{
	// Zunächst muss die Buttonstruktur aktualisiert werden
	this->pButtonControl->PerformAction(b);

	// Nun werden alle Textfelder, deren Inhalt nicht mehr sichtbar sein darf, gelöscht.
	if(b==0)
	{
		// es müssen ALLE Eingabefelder bis auf die öffentlichen Parameter (Generator, Prime) gelöscht werden
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

	// Falls Bob UND Alice für sich den Session Key bereits errechnet haben, wird das gemeinsame Ergebnis
	// im untersten Textfeld des Dialogs ausgegeben.
	if(this->pButtonControl->AllButtons[9].IsActionPerformed() && this->pButtonControl->AllButtons[10].IsActionPerformed())
	{
		// Dialog über erfolgreichen Abschluss des Verfahrens anzeigen
		CDlgDiffieHellmanFinalInfo dlg;
		dlg.DoModal();

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

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "DiffieHellman" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY((unsigned long)m_bShowInfoDialogues, "ShowInfo" );
		CT_CLOSE_REGISTRY();
	}
}

void CDlgDiffieHellmanVisualization::OnCheckDisableIntroDialog() 
{
	UpdateData(true);

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "DiffieHellman" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY((unsigned long)m_bShowIntroDialog, "ShowIntroDialog" );
		CT_CLOSE_REGISTRY();
	}
}

// Der User verlangt nach weiteren Informationen zum Session Key. Also wird der entsprechende
// Dialog aufgerufen. Als Parameter übergibt man dem Dialog die errechneten Session Keys von 
// Alice und Bob sowie einen Zeiger auf die in der Dialogklasse CDlgDiffieHellmanVisualization 
// bereits erzeugte Diffie-Hellman-Log-Datei.
void CDlgDiffieHellmanVisualization::OnKey() 
{
	CDlgDiffieHellmanKeyInformation dlg((char*)(LPCTSTR)this->m_SessionKeyAlice, (char*)(LPCTSTR)this->m_SessionKeyBob, this->pDiffieHellmanLogFile);
	dlg.DoModal();
}


// Diese Funktion soll verhindern, dass der Hauptdialog unter verschiedenen
// Betriebssystemen/Versionen möglichst ähnlich aussieht. Die Funktion hinterlegt
// ein flächendeckendes, großes Bitmap, dass für eine einheiliche Hintergrundfarbe
// sorgt.
void CDlgDiffieHellmanVisualization::OnPaint() 
{

	CPaintDC dc(this); // device context for painting
	 CBitmap bmp, *poldbmp;
     CDC memdc;
     // Load the bitmap resource
     bmp.LoadBitmap( IDB_DH_MAINBACKGROUND );
     // Create a compatible memory DC
     memdc.CreateCompatibleDC( &dc );
     // Select the bitmap into the DC
     poldbmp = memdc.SelectObject( &bmp );
     // Copy (BitBlt) bitmap from memory DC to screen DC
     dc.BitBlt( 0, 0, 795, 575, &memdc, 0, 0, SRCCOPY );
     memdc.SelectObject( poldbmp );
         // Do not call CDialog::OnPaint() for painting messages
}


// Diese Funktion sorgt für korrekte Hintergrundfarben in den Textfeldern (vgl. OnPaint)
HBRUSH CDlgDiffieHellmanVisualization::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr;

	// ***********
	switch (nCtlColor) 
	{ 
		
		case CTLCOLOR_MSGBOX: 
		case CTLCOLOR_EDIT: 
		case CTLCOLOR_BTN:
		case CTLCOLOR_STATIC:
		switch (pWnd->GetDlgCtrlID())  
		{     
			case IDC_PRIME:
			case IDC_GENERATOR: 
			case IDC_SECRETALICE: 
			case IDC_SECRETBOB:
			case IDC_SHAREDALICE:
			case IDC_SHAREDBOB:
			case IDC_FINALALICE:
			case IDC_FINALBOB:
			case IDC_PUBLICFRAME:		// Rahmen um die beiden Textfelder für g und p
			case IDC_PRIMELABEL:		// Primzahlbeschriftung
			case IDC_GENERATORLABEL:	// Generatorbeschriftung
			case IDC_ALICEFRAMELABEL:
			case IDC_BOBFRAMELABEL:
			case IDC_ALICESECRETLABEL:
			case IDC_BOBSECRETLABEL:
			case IDC_ALICESHAREDLABEL:
			case IDC_BOBSHAREDLABEL:
			case IDC_ALICEFINALLABEL:
			case IDC_BOBFINALLABEL:
			case IDC_CHECK_DISABLEHELP:
			case IDC_CHECK_DISABLEINTRODUCTION:
			case IDOK:
			// put your own CONTROL ID here    
			pDC->SetBkColor(m_greycolor); // change the background color
			pDC->SetTextColor(m_blackcolor); // change the text color			
			hbr = (HBRUSH) m_greybrush; //  apply the brush
			break; 
        
			// otherwise do default handling of OnCtlColor
			default:    
			hbr= CDialog::OnCtlColor(pDC,pWnd,nCtlColor); 
			break;  
		}  
		
		break; 
   
		// otherwise do default handling of OnCtlColor
		default:  
		hbr=CDialog::OnCtlColor(pDC,pWnd,nCtlColor); 
	}
	// ***********
	
	// TODO: Anderen Pinsel zurückgeben, falls Standard nicht verwendet werden soll
	return hbr;
}



// Die beiden folgenden Funktionen laden das animierte bzw. statische
// GIF, welches den Schlüsselaustausch zwischen Alice und Bob darstellen
// soll. Die entsprechenden Ressourcen werden dabei geladen und wieder entladen--
// es genügt zum Anzeigen des jeweiligen GIFs der simple Aufruf einer der Funktionen.
void CDlgDiffieHellmanVisualization::ShowAnimatedGIF()
{
	if(!this->m_bAnimatedGIFLoaded)
	{
		if(this->m_bStaticGIFLoaded) m_AnimGif.UnLoad();
		m_AnimGif.Load(MAKEINTRESOURCE(IDR_GIF1), _T("GIF"));
		this->m_bAnimatedGIFLoaded = true;
		this->m_bStaticGIFLoaded = false;
	}

	m_AnimGif.Stop();
	m_AnimGif.Draw();
}

// siehe oben (letzter Kommentar)
void CDlgDiffieHellmanVisualization::ShowStaticGIF(unsigned long gifIDR)
{
	if(!this->m_bStaticGIFLoaded)
	{
		if(this->m_bAnimatedGIFLoaded) m_AnimGif.UnLoad();
		m_AnimGif.Load(MAKEINTRESOURCE(gifIDR), _T("GIF"));
		this->m_bAnimatedGIFLoaded = false;
		this->m_bStaticGIFLoaded = true;
	}
	else
	{
		m_AnimGif.UnLoad();
		m_AnimGif.Load(MAKEINTRESOURCE(gifIDR), _T("GIF"));
		this->m_bAnimatedGIFLoaded = false;
		this->m_bStaticGIFLoaded = true;
	}

	
	m_AnimGif.Stop();
	m_AnimGif.Draw();
}