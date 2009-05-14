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

// RSA_mit_kleinenPZ.cpp: Implementierungsdatei
//
#include "stdafx.h"
#include "Afx.h"
#include "CrypToolApp.h"
#include "DlgOptionsRSADemo.h"
#include "DlgRSADemo.h"
#include "DialogeMessage.h"
#include "KeyRepository.h"
#include "ChrTools.h"
#include "FileTools.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ENCRYPT_TEXT     TRUE
#define ENCRYPT_NUMBERS  FALSE
#define DECRYPT_TEXT     TRUE
#define DECRYPT_NUMBERS  FALSE
#define MODE_ASCII          0
#define MODE_ALPHABET       1
#define MODE_DLG_OF_SISTERS 2
#define MODE_HEX_DUMP       3
#define RSA_DEMO_DECRYPT    64
#define RSA_DEMO_ENCRYPT    128

int load(CString &Src, const char *pattern, CString *Dest);


BOOL g_pre_dialogue = TRUE;

///////////////////////////////////////////////////////////////////////////////
//
// Konstruktor / Destructor
// 

CDlgRSADemo::CDlgRSADemo(CWnd* pParent /*=NULL*/)
: CDialog(CDlgRSADemo::IDD, pParent) 
{

	//{{AFX_DATA_INIT(CDlgRSADemo)
	m_edit_p = _T("");
	m_edit_q = _T("");
	m_edit_N = _T("");
	m_edit_phi_of_N = _T("");
	m_edit_e = _T("2^16+1");  // in der Praxis immer relativ Prim zu "phi(N)"
	m_edit_d = _T("");
	m_edit_RSA_input = _T("");
	m_edit_RSA_step_1 = _T("");
	m_edit_RSA_step_2 = _T("");
	m_edit_RSA_step_3 = _T("");
	m_Header_RSA_input = _T("");
	m_Header_RSA_step_2 = _T("");
	m_Header_RSA_step_3 = _T("");
	m_Header_RSA_step_1 = _T("");
	m_EncryptTextOrNumbers = m_control_RSA_input.EncryptTextOrNumbers = 0;
	m_RSAPublicKeyOnly = 0;
    //}}AFX_DATA_INIT


	// Sub-Dialoge werden zu Beginn dynamisch erzeugt ...
	DlgOptions			= new CDlgOptionsRSADemo();
	DlgRSAPrimes		= new CDlgPrimesGeneratorDemo();
	RSA					= new CRSADemo;
	DlgFactorisation	= new CDlgFactorisationDemo;
	DlgFactorisation->m_inputReadOnly = TRUE; // Don't edit the input for factorisation
//	m_RSAKeyStatus = 0;

// == RSA-Signatur, Schritt Für Schritt verifizieren
    CheckRSASignature = false;
	message = NULL;
}

CDlgRSADemo::~CDlgRSADemo()
{
	// Dynamisch allokierte Sub-Dialoge freigeben.
	delete DlgOptions;
	delete DlgRSAPrimes;
	delete DlgFactorisation;
	delete RSA;
}

///////////////////////////////////////////////////////////////////
//
// Ressourcen in das Programm einbinden
//

void CDlgRSADemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRSADemo)
	DDX_Control(pDX, IDC_HEADER3, m_control_Header_RSA_step_3);
	DDX_Control(pDX, IDC_RADIO3, m_control_RSA_with_own_parameter);
	DDX_Control(pDX, IDC_RSA_MODE_FACTORISATION, m_RSA_mode_factorisation);
	DDX_Control(pDX, IDC_RSA_CAPTION_PRIME_Q, m_RSA_caption_prime_q);
	DDX_Control(pDX, IDC_RSA_CAPTION_PRIME_P, m_RSA_caption_prime_p);
	DDX_Control(pDX, IDC_FRAME_RSA_MODE, m_frame_rsa_mode);
	DDX_Control(pDX, IDC_BUTTON_PZ_GENERIEREN, m_GeneratePrimes);
	DDX_Control(pDX, IDC_OPTIONEN, m_ButtonOptionen);
	DDX_Control(pDX, IDC_BUTTON_VERSCHLUESSELN, m_ButtonEncrypt);
	DDX_Control(pDX, IDC_BUTTON_ENTSCHLUESSELN, m_ButtonDecrypt);
	DDX_Control(pDX, IDC_EDIT1, m_control_edit_p);
	DDX_Text(pDX, IDC_EDIT1, m_edit_p);
	DDX_Control(pDX, IDC_EDIT2, m_control_edit_q);
	DDX_Text(pDX, IDC_EDIT2, m_edit_q);
	DDX_Control(pDX, IDC_EDIT3, m_control_edit_N);
	DDX_Text(pDX, IDC_EDIT3, m_edit_N);
	DDX_Text(pDX, IDC_EDIT4, m_edit_phi_of_N);
	DDX_Control(pDX, IDC_EDIT5, m_control_edit_e);
	DDX_Text(pDX, IDC_EDIT5, m_edit_e);
	DDX_Text(pDX, IDC_EDIT6, m_edit_d);
	DDX_Control(pDX, IDC_EDIT10, m_control_RSA_input);
	DDX_Control(pDX, IDC_EDIT13, m_control_edit_RSA_step_1);
	DDX_Control(pDX, IDC_EDIT11, m_control_edit_RSA_step_2);
	DDX_Control(pDX, IDC_EDIT12, m_control_edit_RSA_step_3);
	DDX_Text(pDX, IDC_EDIT10, m_edit_RSA_input);
	DDX_Text(pDX, IDC_EDIT13, m_edit_RSA_step_1);
	DDX_Text(pDX, IDC_EDIT11, m_edit_RSA_step_2);
	DDX_Text(pDX, IDC_EDIT12, m_edit_RSA_step_3);
	DDX_Text(pDX, IDC_HEADER1, m_Header_RSA_input);
	DDX_Text(pDX, IDC_HEADER4, m_Header_RSA_step_1);
	DDX_Text(pDX, IDC_HEADER2, m_Header_RSA_step_2);
	DDX_Text(pDX, IDC_HEADER3, m_Header_RSA_step_3);
	DDX_Radio(pDX, IDC_RADIO1, m_EncryptTextOrNumbers);
	DDX_Radio(pDX, IDC_RADIO3, m_RSAPublicKeyOnly);
	//}}AFX_DATA_MAP
}


//******************************************************************************
BEGIN_MESSAGE_MAP(CDlgRSADemo, CDialog)
	//{{AFX_MSG_MAP(CDlgRSADemo)
	ON_BN_CLICKED(IDC_BUTTON_PZ_GENERIEREN, OnButtonGeneratePrimes)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonUpdateRSAParameter)
	ON_BN_CLICKED(IDC_OPTIONEN, OnButtonOptions)
	ON_BN_CLICKED(IDC_BUTTON_VERSCHLUESSELN, OnButtonEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_ENTSCHLUESSELN, OnButtonDecrypt)
	ON_BN_CLICKED(IDC_ENDDIALOG, OnEndDialog)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdatePrimeP)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdatePrimeQ)
	ON_EN_UPDATE(IDC_EDIT3, OnUpdateModulN)
	ON_EN_UPDATE(IDC_EDIT5, OnUpdatePublicKeyE)
	ON_EN_UPDATE(IDC_EDIT10, OnUpdateRSAInput)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioRSAText)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioRSANumbers)
	ON_BN_CLICKED(IDC_RADIO3, OnRadioRSAComplete)
	ON_BN_CLICKED(IDC_RADIO4, OnRadioRSAPublicKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
//                      I M P L E M E N T I E R U N G 
///////////////////////////////////////////////////////////////////////////////
//  
// AUSWAHL: 
// ~~~~~~~~
// - RSA mit eigenen Parametern oder 
// - RSA mit veröffentlichten RSA-Parametern N und e
// 

///////////////////////////////////////////////////////////////////////////////
//
// RSA mit eigenen Parametern:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Wähle zwei Primzahlen p und q sowie den öffentlichen Schlüssel e:
// Nur diese Edit-Felder werden dementsprechend editierbar gemacht.
// Danach wird der Focus entsprechend gesetzt

void CDlgRSADemo::OnRadioRSAComplete() 
{

	UpdateData();
	m_edit_N = _T("");
	UpdateData(FALSE);

	m_control_edit_p.EnableWindow();
	m_control_edit_q.EnableWindow();
	m_control_edit_N.SetReadOnly(TRUE);
	m_GeneratePrimes.EnableWindow();
	
	SetStatusPrivateKey(TRUE);

	// RESSOURCEN
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_HEADER_ENTERPRIME,pc_str,STR_LAENGE_STRING_TABLE);
	m_frame_rsa_mode.SetWindowText(pc_str);
	m_RSA_caption_prime_p.ShowWindow(TRUE);
	m_RSA_caption_prime_q.ShowWindow(TRUE);
	m_control_edit_p.ShowWindow(TRUE);
	m_control_edit_q.ShowWindow(TRUE);
	m_RSA_mode_factorisation.ShowWindow(FALSE);
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_HEADER_GENERATEPRIMES,pc_str,STR_LAENGE_STRING_TABLE);
	m_GeneratePrimes.SetWindowText(pc_str);

	CheckRSAParameter();

	if ( !KeyStatusPrimePValid() ) 
	{
		m_control_edit_p.SetSel(0,-1);
		m_control_edit_p.SetFocus();	
	}
	else if ( !KeyStatusPrimeQValid() )
	{
		m_control_edit_q.SetSel(0,-1);
		m_control_edit_q.SetFocus();
	}
	else if ( !KeyStatusKeyEValid() )
	{
		m_control_edit_e.SetSel(0,-1);
		m_control_edit_e.SetFocus();
	}
	else 
	{
		m_control_RSA_input.SetSel(0,-1);
		m_control_RSA_input.SetFocus();
	}	
	
	ButtonManagement();
}

////////////////////////////////////////////////////////////////////////////
// 
// RSA mit veröffentlichten Parametern N und e:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Hier ist es möglich veröffentlichte RSA-Parameter in die Editierbaren 
// Felder "Modul-N" und "öffentlicher Schlüssel e" einzutragen.
// Zusätzlich wird das Feld für die Primzahleingabe durch die Funktionalität
// Faktorisieren ersetzt, um die Bedienung des Angriffs auf RSA möglichst 
// einfach zu gestalten

void CDlgRSADemo::OnRadioRSAPublicKey() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData();
	m_edit_p = m_edit_q = m_edit_phi_of_N = m_edit_d = "";
	UpdateData(FALSE);
	
	SetStatusPublicKeyOnly(TRUE);
	// unbekannte Felder deaktivieren
	m_GeneratePrimes.EnableWindow(FALSE);
	m_control_edit_p.EnableWindow(FALSE);
	m_control_edit_q.EnableWindow(FALSE);
	// Öffentlicher RSA-Modul N editierbar
	m_control_edit_N.SetReadOnly(FALSE);
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_HEADER_FACTORISEATTACK,pc_str,STR_LAENGE_STRING_TABLE);
	m_GeneratePrimes.SetWindowText(pc_str);

	// RESSOURCEN
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_HEADER_FACTORISERSAMODUL,pc_str,STR_LAENGE_STRING_TABLE);
	m_frame_rsa_mode.SetWindowText(pc_str);
	m_RSA_caption_prime_p.ShowWindow(FALSE);
	m_RSA_caption_prime_q.ShowWindow(FALSE);
	m_control_edit_p.ShowWindow(FALSE);
	m_control_edit_q.ShowWindow(FALSE);
	m_RSA_mode_factorisation.ShowWindow(TRUE);
	
	CheckRSAParameter();	
	// fokus setzen
	if ( !KeyStatusModulNValid() )
	{
		m_control_edit_N.SetSel(0, -1);
		m_control_edit_N.SetFocus();
	}
	else if ( !KeyStatusKeyEValid() )
	{
		m_control_edit_e.SetSel(0, -1);
		m_control_edit_e.SetFocus();
	}
	else
	{
		m_control_RSA_input.SetFocus();
	}
	ButtonManagement();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Primzahlen für den RSA-Modul genereieren (RSA mit eigenen Parametern):
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Bei der Erzeugung von Primzahlen kann man selbst gewählte Primzahlen eingeben, oder
// wie im folgenden implementiert: Zufällige Primzahlen über den gleichen Dialog wie unter
// Menü -> Einzelverfahren -> RSA-Demo

void CDlgRSADemo::OnButtonGeneratePrimes() 
{
	if ( KeyStatusPrivateKey() )
	{
		if ( IDOK == DlgRSAPrimes->DoModal() )
		{
			UpdateData();
			m_edit_p = DlgRSAPrimes->m_edit5;
			m_edit_q = DlgRSAPrimes->m_edit6;
			UpdateData(FALSE);
			int Parameter_N_zu_gross;
			Parameter_N_zu_gross = RSA->InitParameter( m_edit_p, m_edit_q );
			if (Parameter_N_zu_gross==0)
			{
				CheckRSAParameter() ;
			}
			else
			{
				UpdateData();
				Message(IDS_STRING_BIG_RSA_MODUL, MB_ICONSTOP);
				m_ButtonOptionen.EnableWindow(false);
				m_edit_p = _T("");
				m_edit_q = _T("");
				m_edit_phi_of_N = _T("");
				m_edit_N = _T("");
				m_edit_d = _T("");
				m_control_edit_p.SetFocus();
				UpdateData(FALSE);
			}
		}
	}
	else
	{
		if ( m_edit_N.GetLength() )
		{
			if ( DlgFactorisation->m_CompositeNoStr != m_edit_N )
			{
				DlgFactorisation->InitialiseFactorList();
				DlgFactorisation->m_CompositeNoStr = m_edit_N;
			}
			AfxInitRichEdit();
			DlgFactorisation->DoModal();
			CString tmp_p, tmp_q;
			int l_result = DlgFactorisation->GetRSAFactorisation( tmp_p, tmp_q );
			if ( l_result == NUMBER_RSA_MODUL )
			{
				Message( IDS_NUMBER_RSA_MODUL, MB_ICONINFORMATION);
				UpdateData();
				m_RSAPublicKeyOnly = 0;
				m_edit_p = tmp_p;
				m_edit_q = tmp_q;
				UpdateData(FALSE);
				OnRadioRSAComplete();			
			}
			else if ( l_result == NUMBER_NOT_FACTORISED )
			{
				Message( IDS_NUMBER_NOT_FACTORIZED, MB_ICONINFORMATION);
			}
			else if ( l_result == NUMBER_NOT_RSA_MODUL )
			{
				Message( IDS_NUMBER_NOT_RSA_MODUL, MB_ICONINFORMATION);
				UpdateData();
				m_control_edit_N.SetSel(0,-1);
				m_control_edit_N.SetFocus();
			}

		}
	}
	ButtonManagement();
}

//////////////////////////////////////////////////////////////////////////////
// Inhalt aus dem Zwischenspeicher laden:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

int load(CString &Src, const char *pattern, CString *Dest)
{
	int p1, p2;
	if ( 0 > ( p1 = Src.Find(pattern)) ) return -1;
	p1 += strlen(pattern);
	p2 = Src.Find(';', p1);
	if ( Dest ) 
	{
		*Dest = Src.Mid(p1,p2-p1);
		return 0;
	}
	else if ( p2-p1 < 5 )
	{
		return atoi(Src.Mid(p1, p2-p1).GetBuffer(0));
	}
	return -1;
}


//////////////////////////////////////////////////////////////////////////////
// Check RSA-Parameter:
// ~~~~~~~~~~~~~~~~~~~~
// 
// Überprüft die aktuelle Eingabe, ob diese einen gültigen "RSA-Schlüssel" beschreibt: 
// Dabei unterscheiden wir zwischen RSA mit eigenen Parametern und öffentliche 
// RSA-Parameter:
// 
// 1. Öffentliche RSA-Parameter:
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Die Funktion RSA->SetPublicParameter überprüft, ob die Zahleneingabe für 
//    N ganze Zahlen grösser als 2 sind.
//
// 2. RSA mit eigenen Parametern:
//    ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    Hier überprüft die Funktion RSA->InitParameter( m_edit_p, m_edit_q ); zum
//    einen, ob p und q Primzahlen sind und bei Erfolg wird zum anderen mit der
//    Funktion RSA->SetPublicKey( m_edit_e ) zunächst überprüft, ob e teiler-
//    fremd zu Phi(N) ist. 
//
//    Wenn e Phi(N) nicht teilt, wird der Private Schlüssel d berechnet, und 
//    alle Parameter werden mit der Funktion RSA->GetParameter(..) in den 
//    Dialog übertragen.

int CDlgRSADemo::CheckRSAParameter()
{	UpdateData();	
	int ret;
	if ( KeyStatusPublicKeyOnly() )
	{ // Öffentliche RSA-Parameter ...
		SetStatusKeyEValid(FALSE);
		SetStatusModulNValid(FALSE);
		SetStatusOptionsValid(FALSE);
		ret = RSA->SetPublicParameter(m_edit_N, m_edit_e);
		if ( ret == 0 )
		{
			SetStatusKeyEValid(TRUE);
			SetStatusModulNValid(TRUE);
			SetStatusOptionsValid(DlgOptions->CompareModulAlphabetSize(m_edit_N));
		}
	}
	else
	{
		SetStatusModulNValid(FALSE);			
		SetStatusKeyEValid(FALSE);
		SetStatusPrimePValid(FALSE);
		SetStatusPrimeQValid(FALSE);
		SetStatusOptionsValid(FALSE);

	

		ret = RSA->InitParameter( m_edit_p, m_edit_q );
		if ( ret == 0 )
		{	
			SetStatusPrimePValid(TRUE);
			SetStatusPrimeQValid(TRUE);
			SetStatusModulNValid(TRUE);			
			if ( 1 == RSA->SetPublicKey( m_edit_e ) )
			{
				RSA->SetPrivateKey();
				CString l_e_str;
				RSA->GetParameter( m_edit_N, m_edit_phi_of_N, 
						   l_e_str, m_edit_d );
				SetStatusKeyEValid(TRUE);
				SetStatusOptionsValid( DlgOptions->CompareModulAlphabetSize(m_edit_N) );
			}
			else
			{
				ret = ERR_ON_INITIALIZE_E;
			}
		}
		else
		{
			m_edit_d = "";
		}
	}
	
	SetDlgOptions(TRUE);
	UpdateData(FALSE);
	return ret;
}



///////////////////////////////////////////////////////////////////////////////
// InitPrivateRSAParameter:
// ~~~~~~~~~~~~~~~~~~~~~~~~
// Bevor die Funktion CheckRSAParameter() (siehe oben) aufgerufen wird, überprüft
// die Funktion zunächst, ob die eingegebenen Zahlen (oder deren Formeldarstellung
// wie "2^16+1" korrekt sind -- andernfalls wird eine Fehlermeldung ausgegeben, und  
// Der Fokus geht zur Fehlerhaften Eingabe über.
//
// Danach erfolgt ggf. eine Fehlerbehandlung von CheckRSAParameter(). 

///////////////////////////////////////////////////////////////////////////////
// Fehlerbehandlung für falsche - oder zu grosse Zahlen:  
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
BOOL CDlgRSADemo::CheckIntegerInput( CString &NumStr, CEdit &EditCtrl )
{	
	CString UpnFormula;
	int error, err_ndx;
	error = CheckFormula(NumStr, 10, UpnFormula, err_ndx);
	if (error==0 && !g_pre_dialogue)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		EditCtrl.SetSel(err_ndx-1,m_edit_p.GetLength());
		EditCtrl.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// Fehlerausgabe für falsche - oder zu grosse Zahlen:  
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

void CDlgRSADemo::MessageIntegerRSAError( CEdit &EditCtrl, int id_IDS, BOOL select )
{
	Message(id_IDS, MB_ICONINFORMATION);
	EditCtrl.SetFocus();
	if ( select )
	{
		EditCtrl.SetSel(0,-1);
	}
}


void CDlgRSADemo::InitPrivateRSAParameter()
{
	int RSAInitError;

	
	if ( !CheckIntegerInput(m_edit_p, m_control_edit_p) ) 
	{
		SetStatusPrimePValid(FALSE);
		return;
	}
	if ( !CheckIntegerInput(m_edit_q, m_control_edit_q) ) 
	{
		SetStatusPrimeQValid(FALSE);
		return;
	}
	if ( !CheckIntegerInput(m_edit_e, m_control_edit_e) ) 
	{
		SetStatusKeyEValid(FALSE);
		return;
	}

	// Check & ggf. Initialisierung der eignen RSA-Parameter
	RSAInitError = CheckRSAParameter();
	
	if ( 0 != RSAInitError && !g_pre_dialogue ) 
	{
		// In diesem Fall ist mindestens eine der Zahlen p oder q keine Primzahl.
		if ( ERR_P_TO_BIG & RSAInitError )
		{
			MessageIntegerRSAError( m_control_edit_p, IDS_STRING_BIG_NUMBER, TRUE );
		}
		else if ( ERR_Q_TO_BIG & RSAInitError )
		{
			MessageIntegerRSAError( m_control_edit_q, IDS_STRING_BIG_NUMBER, TRUE );
		}
		else if ( RSAInitError & ERR_P_NOT_PRIME && RSAInitError & ERR_Q_NOT_PRIME )
		{
			MessageIntegerRSAError( m_control_edit_p, IDS_PRIME_NO_CHECK_PQ, TRUE );
		}
		else if ( ERR_P_NOT_PRIME & RSAInitError )
		{
			MessageIntegerRSAError( m_control_edit_p, IDS_STRING_RSADEMO_P_NOT_PRIME, FALSE );
		}
		else if ( ERR_Q_NOT_PRIME & RSAInitError )
		{
			MessageIntegerRSAError( m_control_edit_q, IDS_STRING_RSADEMO_Q_NOT_PRIME, FALSE );
		}
		else if ( ERR_P_EQUALS_Q & RSAInitError )
		{
			MessageIntegerRSAError( m_control_edit_p, IDS_STRING_ERR_PRIME_ARE_EQUAL, FALSE );
		}
		else if ( ERR_ON_INITIALIZE_E )
		{
			MessageIntegerRSAError( m_control_edit_e,IDS_STRING_RSATUT_WRONG_PUBLICKEY, FALSE );
		}
		return;
	}
}


///////////////////////////////////////////////////////////////////////////////
// InitPublicRSAParameter:
// ~~~~~~~~~~~~~~~~~~~~~~~~
// Bevor die Funktion CheckRSAParameter() (siehe oben) aufgerufen wird, überprüft
// die Funktion zunächst, ob die eingegebenen Zahlen (oder deren Formeldarstellung
// wie "2^16+1" korrekt sind -- andernfalls wird eine Fehlermeldung ausgegeben, und  
// Der Fokus geht zur Fehlerhaften Eingabe über.
//
// Danach erfolgt ggf. eine Fehlerbehandlung von CheckRSAParameter(). 

void CDlgRSADemo::InitPublicRSAParameter()
{
	int RSAInitError;

	if ( !CheckIntegerInput(m_edit_N, m_control_edit_N) ) 
	{
		SetStatusModulNValid(FALSE);			
		return;
	}
	
	if ( !CheckIntegerInput(m_edit_e,  m_control_edit_e) ) 
	{
		SetStatusKeyEValid(FALSE);
		return;
	}
	
	// Check & ggf. Initialisierung der Public RSA-Parameter
	RSAInitError = CheckRSAParameter();

	
	if ( 0 != RSAInitError && !g_pre_dialogue ) 
	{
		if ( ERR_ON_MODUL_N == RSAInitError )
		{
			SetStatusModulNValid(FALSE);
		}
		if ( ERR_ON_PUBLIC_KEY == RSAInitError )
		{
			SetStatusKeyEValid(FALSE);
		}
	}
	else
	{
		SetStatusKeyEValid(TRUE);
		SetStatusModulNValid(TRUE);
	}
}

///////////////////////////////////////////////////////////////////////////////////
//
// Knopf: "Parameter aktualisieren:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Dieser Knopf wird demnächst ersetzt ...
// 

void CDlgRSADemo::OnButtonUpdateRSAParameter() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if ( !m_RSAPublicKeyOnly )
	{
		InitPrivateRSAParameter();
	}
	else
	{
		InitPublicRSAParameter();
	}
		
	if ( KeyStatusModulNValid() ) 
	{
		if ( DlgOptions->m_BlockLength!=0 && !( m_edit_N.GetLength() <= 3 && 
					                DlgOptions->Anzahl_Zeichen>atoi(m_edit_N.GetBuffer(0))) )
		{ // Save Actual Primes
			LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
			CString Primes = m_edit_p + ";" + m_edit_q + ";"+m_edit_e;
			CopyKey ( pc_str, Primes );
			if ( m_edit_RSA_input.GetLength() > 0 )
			{
				SetStatusInputValid(TRUE);
			}
		}
		else 
		{
			SetStatusInputValid(FALSE);
			if ( !g_pre_dialogue )
				Message(!m_EncryptTextOrNumbers? IDS_STRING_RSADEMO_MODUL_KLEIN: IDS_STRING_RSADEMO_MODUL_KLEIN_NUM, MB_ICONEXCLAMATION, 
					DlgOptions->Anzahl_Zeichen, m_edit_N );
		}	
		m_control_RSA_input.SetFocus();
		m_control_RSA_input.SetSel(100000, 100000);
	}
	RequestForInput(FALSE);
	ButtonManagement();
}





/////////////////////////////////////////////////////////////////////////////
// 
// RSA-Demo: Dialog Initialisieren:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Wenn mit diesem Dialog bereits zuvor gearbeitet wurde, werden die bisherigen
// Dialogdaten aus dem Zwischenspeicher in den Dialog geladen
//
// Möglichkeiten:
// ~~~~~~~~~~~~~~
//
// 1. Nur zwei Primzahlen wurden gewählt
// 2.a) RSA mit eigenen Parametern
// 2.b) RSA nur mit Öffentlichen Schlüssel

BOOL CDlgRSADemo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	g_pre_dialogue = TRUE;

	m_control_edit_p.SetFocus();

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_RSA_DEMO,pc_str,STR_LAENGE_STRING_TABLE);
	CString RSAParam;
	
	// Paste into the dialouge the old RSA status
	if ( CheckRSASignature ) 
	{ // Wenn vorher Signaturdaten überliefert wurden ....
		UpdateData();
		m_EncryptTextOrNumbers = 1;
		m_RSAPublicKeyOnly = 1;
		DlgOptions->m_numberBasis = 3;
		UpdateData(FALSE);
		OnRadioRSAPublicKey();
		OnButtonUpdateRSAParameter();
		LoadString(AfxGetInstanceHandle(),IDS_RSADEMO_VERIFY,pc_str,STR_LAENGE_STRING_TABLE);
		m_control_RSA_with_own_parameter.EnableWindow(FALSE);
		m_ButtonEncrypt.SetWindowText(pc_str);
	}
	else if ( PasteKey( pc_str, RSAParam ) )
	{
		UpdateData(); 
		m_RSAPublicKeyOnly = load(RSAParam,"PUBLIC_KEY_ONLY:", NULL);
		load(RSAParam,"PUBLIC_KEY:",&m_edit_e);
		load(RSAParam,"PRIME_P:",&m_edit_p); 
		load(RSAParam,"PRIME_Q:",&m_edit_q); 
		load(RSAParam,"MODUL_N:",&m_edit_N);
		m_EncryptTextOrNumbers    = load(RSAParam,"CRYPT_TEXT_OR_NUMBERS:", NULL);
		DlgOptions->m_TextOptions = load(RSAParam,"TEXT_OPTIONS", NULL);
		if ( DlgOptions->m_TextOptions )
			load(RSAParam,"ALPHABET:",&DlgOptions->m_alphabet);
		DlgOptions->m_RSAVariant = load(RSAParam,"RSA_VARIANT:", NULL);
		DlgOptions->m_numberBasis = load(RSAParam,"BASEOFNUMBERS:", NULL);
		DlgOptions->m_codingMethod = load(RSAParam,"CODING_METHOD:", NULL);
		DlgOptions->m_BlockLength = load(RSAParam, "BLOCK_LENGTH:", NULL);
		UpdateData(FALSE);
		if ( !m_RSAPublicKeyOnly )
		{
			OnButtonUpdateRSAParameter();
			OnRadioRSAComplete();	
		}
		else
		{
			OnButtonUpdateRSAParameter();
			OnRadioRSAPublicKey();				
		}
	}
	else 
	{	
		LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
		CString Primes;
		if ( PasteKey( pc_str, Primes ) )
		{
			UpdateData(true);
			int d1 = Primes.Find(';', 0);
			int d2 = Primes.Find(';', d1+1);
			m_edit_p = Primes.Mid(0, d1);
			m_edit_q = Primes.Mid(d1+1, ((d2-d1)-1));
			m_edit_e = Primes.Mid(d2+1);
			UpdateData(false);
			OnButtonUpdateRSAParameter();
			OnRadioRSAComplete();	
		}
		else
		{
			OnRadioRSAComplete();	
		}
	}
	// End of paste ...

	ButtonManagement();	
	m_control_RSA_input.mode = DlgOptions->m_TextOptions;
	if ( CheckRSASignature ) 
	{ // Wenn vorher Signaturdaten überliefert wurden ....
		RequestForInput(FALSE);
	}
	else
	{
		RequestForInput(TRUE);
	}

	g_pre_dialogue = FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Schliessen des RSA-Dialoges:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Ggf. wird der letzte Stand des RSA-Kryptosystems in den Speicher gesichtert.
// 
 
void CDlgRSADemo::OnEndDialog() 
{
	if ( (!m_RSAPublicKeyOnly && RSA->IsInitialized()) ||
		 (m_RSAPublicKeyOnly && RSA->IsInitializedPublicParameter()) )
	{ // Copy RSA Demo Parameter
		CString Store_N = _T("");
		if ( m_RSAPublicKeyOnly ) Store_N = m_edit_N;
		char tmp[20];
		sprintf(tmp, "%i", DlgOptions->m_BlockLength);
		LoadString(AfxGetInstanceHandle(),IDS_PARAM_RSA_DEMO,pc_str,STR_LAENGE_STRING_TABLE);
		CString RSAOptions = "";
		RSAOptions = CString("PUBLIC_KEY_ONLY:") + char(m_RSAPublicKeyOnly+'0')
		            +CString(";PUBLIC_KEY:") + m_edit_e 
					+CString(";PRIME_P:") + m_edit_p 
					+CString(";PRIME_Q:") + m_edit_q 
					+CString(";MODUL_N:") + Store_N
					+CString(";CRYPT_TEXT_OR_NUMBERS:") + char(m_EncryptTextOrNumbers+'0')
					+CString(";TEXT_OPTIONS") + char(DlgOptions->m_TextOptions      +'0');
		if ( DlgOptions->m_TextOptions == 1 ) 
			 RSAOptions += CString(";ALPHABET:")+DlgOptions->m_alphabet;
		RSAOptions += CString(";RSA_VARIANT:")   + char(DlgOptions->m_RSAVariant   + '0')
					+CString(";BASEOFNUMBERS:")  + char(DlgOptions->m_numberBasis  + '0')
					+CString(";CODING_METHOD:")  + char(DlgOptions->m_codingMethod + '0')  
					+CString(";BLOCK_LENGTH:")   + CString(tmp) + ';';
		CopyKey ( pc_str, RSAOptions );
	}
	
	CDialog::OnCancel();
}


////////////////////////////////////////////////////////////////////////////////////////////////
//
// Die nächste Funktion unterdrückt bei der Eingabe alle Zeichen ausser die in "expr"
// (Beispiel expr = "0, 1, .., 9, +-*^")
// 

BOOL CDlgRSADemo::PreCheckNumExpression( CEdit &editCtrl, CString &editStr, const char *expr )
{
	CString res = editStr;
	UpdateData();
	int sele, sels;

	editCtrl.GetSel(sels, sele);	
	for (int i=0; i<editStr.GetLength(); )
	{
		if ( !isCharOf(editStr[i], expr ) )
		{
			if (i < sels) sels--;
			if (i < sele) sele--;
			editStr.Delete(i); 
		}
		else			
		{
			i++;
		}
	}
	UpdateData(FALSE);
	editCtrl.SetSel(sels, sele);
	return ( res == editStr );
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Eingabe-Check für die Primzahl P
//

void CDlgRSADemo::OnUpdatePrimeP() 
{
	if ( !PreCheckNumExpression( m_control_edit_p, m_edit_p, "0..9+-*^()") )
	{
		UpdateData();
		m_edit_phi_of_N = _T("");
		m_edit_N = _T("");
		m_edit_d = _T("");
		UpdateData(FALSE);
		RequestForInput(FALSE);
		SetStatusPrimePValid(false);
		SetStatusKeyDValid(false);
	}
	ButtonManagement();
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Eingabe-Check für die Primzahl Q
//

void CDlgRSADemo::OnUpdatePrimeQ() 
{
	if ( !PreCheckNumExpression( m_control_edit_q, m_edit_q, "0..9+-*^()") )
	{
		UpdateData();
		m_edit_phi_of_N = _T("");
		m_edit_N = _T("");
		m_edit_d = _T("");
		UpdateData(FALSE);
		RequestForInput(FALSE);
		SetStatusPrimeQValid(false);
		SetStatusKeyDValid(false);
	}
	ButtonManagement();
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Eingabe-Check für den öffentlichen Schlüssel e
//

void CDlgRSADemo::OnUpdatePublicKeyE() 
{
	if ( !PreCheckNumExpression( m_control_edit_e, m_edit_e, "0..9+-*^()") )
	{
		UpdateData();
		m_edit_d = _T("");
		UpdateData(FALSE);
		RequestForInput(FALSE);
		SetStatusKeyEValid(FALSE);
	}
	CheckRSAParameter();
	ButtonManagement();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// Eingabe-Check für den öffentlichen Modul N
// 

void CDlgRSADemo::OnUpdateModulN() 
{
	if ( !PreCheckNumExpression( m_control_edit_N, m_edit_N, "0..9+-*^()") )
	{
		RequestForInput(FALSE);
		SetStatusModulNValid(FALSE);
	}
	CheckRSAParameter();
	ButtonManagement();
}

/////////////////////////////////////////////////////////////////////////////////////////////
// RSA-Alphabet- und Zahlenoptionen:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// In diesem Dialog (Siehe Datei DlgRSADemoOptions.{h|cpp} wird 
// - das Alphabet für das RSA-Kryptosystem eingestellt
// - als Option das Kryptosystem "Dialog der Schwestern" von Dr. C. Elsner eingestellt
// - die Zahlenbasis für das Rechnen mit dem RSA-Kryptosystem eingestellt.

///////////////////////////////////////////////////////////////////////////////////////////
// Übertragung von Parametern an den Optionen-Dialog:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
void CDlgRSADemo::SetDlgOptions(BOOL reinitBlockLength)
{
	if (DlgOptions->m_TextOptions==0)
	{	
		DlgOptions->Anzahl_Zeichen=256;
	}
	else
	{
		DlgOptions->Anzahl_Zeichen=DlgOptions->m_alphabet.GetLength();
	}
    if ( KeyStatusModulNValid() )
	{
		DlgOptions->m_Bitlength = RSA->GetBlockLength();
		DlgOptions->m_log2N     = RSA->GetLog2RSAModul();
		DlgOptions->RSA_Modul   = m_edit_N;
		DlgOptions->ReInitBlockLength(reinitBlockLength);
	}
}

void CDlgRSADemo::OnButtonOptions() 
{
	SetDlgOptions();	
	if ( IDOK == DlgOptions->DoModal() ) 
	{
		RequestForInput();
		UpdateData(TRUE);
		m_control_RSA_input.mode = DlgOptions->m_TextOptions;
		UpdateData(FALSE);

		SetStatusOptionsValid(DlgOptions->CompareModulAlphabetSize(m_edit_N));

		if ( KeyStatusModulNValid() ) 
		{
			if ( KeyStatusOptionsValid() )
			{ 
				if ( m_edit_RSA_input.GetLength() > 0 )
					SetStatusInputValid(TRUE);
				m_control_RSA_input.SetFocus();
				m_control_RSA_input.SetSel(100000, 100000);
			}
			else 
			{
				if ( !g_pre_dialogue )
					Message(!m_EncryptTextOrNumbers? IDS_STRING_RSADEMO_MODUL_KLEIN: IDS_STRING_RSADEMO_MODUL_KLEIN_NUM, MB_ICONEXCLAMATION, 
						DlgOptions->Anzahl_Zeichen, m_edit_N );
			}	
		}
		RequestForInput(FALSE);
	}	
	else 
	{
		if ( m_edit_N.GetLength() <= 3 &&
			 DlgOptions->Anzahl_Zeichen > atoi(m_edit_N))
		{
			Message(!m_EncryptTextOrNumbers? IDS_STRING_RSADEMO_MODUL_KLEIN: IDS_STRING_RSADEMO_MODUL_KLEIN_NUM, MB_ICONEXCLAMATION, 
				DlgOptions->Anzahl_Zeichen, m_edit_N );
			
		}
	}

	ButtonManagement();

}


//////////////////////////////////////////////////////////////////////////////////////////
// Button - Management:
// ~~~~~~~~~~~~~~~~~~~~  
// Je nachdem, in welchen Zustand sich der RSA-Demo-Dialog befindet, werden
// die Buttons aktiviert oder deaktiviert. 

void CDlgRSADemo::ButtonManagement()
{
	if ( KeyStatusPrivateKey() )
	{
		if ( KeyStatusPrimePValid() && KeyStatusPrimeQValid() )
		{	
			m_ButtonOptionen.EnableWindow(TRUE);
			if ( KeyStatusKeyEValid() )
			{
				if ( KeyStatusInputValid() && KeyStatusOptionsValid() 
					                       && m_edit_RSA_input.GetLength() )
				{
					m_ButtonDecrypt.EnableWindow(TRUE);		
					m_ButtonEncrypt.EnableWindow(TRUE);
				}
				else
				{
					m_ButtonDecrypt.EnableWindow(FALSE);		
					m_ButtonEncrypt.EnableWindow(FALSE);
				}
			}
		}
		else
		{
			m_ButtonOptionen.EnableWindow(FALSE);
			m_ButtonDecrypt.EnableWindow(FALSE);		
			m_ButtonEncrypt.EnableWindow(FALSE);
		}
	}
	else
	{
		m_ButtonDecrypt.EnableWindow(FALSE);		
		m_GeneratePrimes.EnableWindow(FALSE);
		if ( KeyStatusModulNValid() )
		{
			m_GeneratePrimes.EnableWindow(TRUE);
			m_ButtonOptionen.EnableWindow(TRUE);
			if ( KeyStatusKeyEValid() )
			{
				if ( KeyStatusInputValid() && KeyStatusOptionsValid() 
					                       && m_edit_RSA_input.GetLength() )
				{
					m_ButtonEncrypt.EnableWindow(TRUE);
				}
				else
				{
					m_ButtonEncrypt.EnableWindow(FALSE);
				}
			}			
		}
		else
		{	
			m_ButtonOptionen.EnableWindow(FALSE);
			m_ButtonEncrypt.EnableWindow(FALSE);		
		}
	}
}




///////////////////////////////////////////////////////////
//                                                       // 
//   R S A  V E R - / E N T S C H L U E S S E L U N G    //
//                                                       //
///////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
// Ändern der RSA-Eingabe:
// ~~~~~~~~~~~~~~~~~~~~~~~
// Bei jeder Änderun im EingabeText, wird die "Ausgabe der RSA Ver-/Entschlüsselung gelöscht
//

void CDlgRSADemo::OnUpdateRSAInput() 
{
	SetStatusOptionsValid(DlgOptions->CompareModulAlphabetSize(m_edit_N));
	RequestForInput(FALSE);
	if ( m_edit_RSA_input.GetLength() == 0 )
		SetStatusInputValid(FALSE);
	else
		SetStatusInputValid(TRUE);
	ButtonManagement();
}

///////////////////////////////////////////////////////////////////////////////////////////
// Überschriften für die RSA-Ver-/Entschlüsselung setzen:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
// 

void CDlgRSADemo::SetHeadLine(CString &mHeader, int IDS_STRING_ID, int base, int BlockLength )
{
	char line[IDS_STRINGLENGTH];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	if ( BlockLength ) sprintf( line, pc_str, base, BlockLength );       
	else if ( base )   sprintf( line, pc_str, base );
	     else	       sprintf( line, pc_str );
	mHeader = line;
}

void CDlgRSADemo::SetHeadLine(CString &mHeader, int IDS_STRING_ID, CString &Str, const char *str2)
{
	char line[IDS_STRINGLENGTH];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	if ( !str2 )
		sprintf( line, pc_str, Str );
	else
		sprintf( line, pc_str, Str, str2 );
	mHeader = line;
}


///////////////////////////////////////////////////////////////////////////////////////////
// Alte Ausgaben und Überschriften der RSA-Ver-/Entschlüsselung löschen:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

void CDlgRSADemo::RequestForInput( BOOL clearInput )
{

	UpdateData();
	if ( clearInput ) m_edit_RSA_input.Empty();
	m_edit_RSA_step_2.Empty();
	m_edit_RSA_step_3.Empty();
	m_edit_RSA_step_1.Empty();
	if ( !m_EncryptTextOrNumbers) SetHeadLine( m_Header_RSA_input, IDS_STRING_RSA_TUTORIAL_INPUT );
	else						  SetHeadLine( m_Header_RSA_input, IDS_STRING_RSA_TUTORIAL_INPUT_NUMBERS, GetBase() );
	m_Header_RSA_step_2.Empty();
	m_Header_RSA_step_3.Empty();
	m_Header_RSA_step_1.Empty();
	UpdateData(FALSE);
}


///////////////////////////////////////////////////////////////////////////////////////////
// Überschriften RSA-Verschlüsselung:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ... für die Eingabe von Text oder von Zahlen.

void CDlgRSADemo::HeadingEncryption( BOOL encryptText )
{
	if ( encryptText ) 
	{
		SetHeadLine( m_Header_RSA_input, IDS_STRING_RSATUT_INPUTPLAINTEXT );
		SetHeadLine( m_Header_RSA_step_1, IDS_STRING_RSA_TUT_TEXTSEGMENTATION, DlgOptions->m_BlockLength );
		SetHeadLine( m_Header_RSA_step_2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
		SetHeadLine( m_Header_RSA_step_3, IDS_STRING_RSA_TUTORIAL_ENCRYPTION );
	}
	else
	{
		SetHeadLine( m_Header_RSA_input, IDS_STRING_RSATUT_PLAINTEXTNUMBERS, GetBase());
		SetHeadLine( m_Header_RSA_step_1, IDS_STRING_RSA_TUTORIAL_ENCRYPTION );
		SetHeadLine( m_Header_RSA_step_2, IDS_STRING_RSA_OUTPUT_TEXTSEGMENTATION, DlgOptions->m_BlockLength );
		SetHeadLine( m_Header_RSA_step_3, IDS_RSA_MKPZ_CIPHERTEXT );
	}
}


////////////////////////////////////////////////////////////////////////////////////////////
//Überschriften RSA-Entschlüsselung:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ... für die Eingabe von Text oder von Zahlen.

void CDlgRSADemo::HeadingDecryption( BOOL decryptText )
{
	if ( decryptText ) 
	{
		SetHeadLine( m_Header_RSA_input, IDS_STRING_RSATUT_INPUTPLAINTEXT );
		SetHeadLine( m_Header_RSA_step_1, IDS_STRING_RSA_TUT_TEXTSEGMENTATION, DlgOptions->m_BlockLength );
		SetHeadLine( m_Header_RSA_step_2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
		SetHeadLine( m_Header_RSA_step_3, IDS_STRING_RSA_TUTORIAL_DECRYPTION );
	}
	else
	{
		SetHeadLine( m_Header_RSA_input, IDS_STRING_RSATUT_CIPHERTEXTNUMBERS, GetBase());
		SetHeadLine( m_Header_RSA_step_1, IDS_STRING_RSA_TUTORIAL_DECRYPTION );
		SetHeadLine( m_Header_RSA_step_2, IDS_STRING_RSA_OUTPUT_DECRYPTION_TEXTSEGMENTATION, DlgOptions->m_BlockLength );
		SetHeadLine( m_Header_RSA_step_3, IDS_RSA_MKPZ_PLAINTEXT );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Die im Optionendialog festgelegte Zahlenbasis bestimmen:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 

int CDlgRSADemo::GetBase()
{
	int baseNumbers = BASE_DEC;

	switch ( DlgOptions->m_numberBasis ) {
	case 0: 
		baseNumbers = BASE_DEC;
		break;
	case 1: 
		baseNumbers = BASE_BIN;
		break;
	case 2: 
		baseNumbers = BASE_OCT;
		break;
	case 3: 
		baseNumbers = BASE_HEX;
		break;
	}

	return baseNumbers;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// OnRadioRSA{Text|Numbers}: 
// ~~~~~~~~~~~~~~~~~~~~~~~~~
// Manuelle auswahl, ob "Text" oder Gleich Zahlen in die RSA-Berechnung eingehen
// 

void CDlgRSADemo::OnRadioRSANumbers() 
{
	RequestForInput(FALSE);
}

void CDlgRSADemo::OnRadioRSAText() 
{
	RequestForInput(FALSE);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Dienst für OnButton{Encrypt|Decrypt} (siehe unten):
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

BOOL CDlgRSADemo::SkipWS()
{
	CString cleanStr = m_edit_RSA_input;
	for (int i=0 ;i<cleanStr.GetLength();)
	{
		if ( !isCharOf(cleanStr[i], DlgOptions->m_alphabet.GetBuffer(0)) )
			cleanStr.Delete(i);
		else
			i++;
	}
	// FLORIAN
	// Fügt man den folgenden if-Block NICHT ein, so besteht die Gefahr,
	// dass man den gesamten Klartext löscht und somit "nichts" verschlüsselt;
	// der User wird also auf seine fehlerhafte Eingabe hingewiesen, der
	// FALSE-Rückgabewert wiederum bewirkt, dass keine Verschlüsselung stattfindet.
	if ( cleanStr.GetLength() == 0 )
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_RSADEMO_ERR_NO_VALID_CHARS, pc_str, STR_LAENGE_STRING_TABLE);
		
		MessageBox(pc_str, "RSA-Demo", MB_OK | MB_ICONINFORMATION);

		return FALSE;
	}
	if ( m_edit_RSA_input.GetLength() != cleanStr.GetLength() )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_WARN_BEFOR_SKIPWS, pc_str,STR_LAENGE_STRING_TABLE);
		int RetValue;
		if ( 1 != (RetValue = MessageBox(pc_str, "RSA-Demo", MB_OKCANCEL | MB_ICONINFORMATION )) )
		{
			return FALSE;
		}
	}
	m_edit_RSA_input = cleanStr;
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////
//
// Wenn ein HEX-String eingefügt wurde, dann besteht die Möglichkeit, dass es such um einen 
// bereits RSA-Verschlüsselten Text Handelt....

int CDlgRSADemo::CheckInversion()
{
	if (!DlgOptions->m_RSAVariant && !DlgOptions->m_TextOptions && IsHexDump( m_edit_RSA_input ) )
	{
		int i=0;
		int l_byteLength = RSA->GetBlockLength()/8+1;
		CString plain  = m_edit_RSA_input;
		CString plain2 = "";
		CString number = "";

// Segmentierung der HEX-Eingabe
		while ( 1 )
		{					
			if (  i < plain.GetLength() && ' ' == plain[i] ) 
			{
				plain.Delete(i);
			}
			else 
			{
				if ( (i > 0 && 0 == (i % (2*l_byteLength))) || i == plain.GetLength() )
				{
					number = plain.Mid(0, i);
					BaseRepr(number, 16, GetBase());
					if ( i < plain.GetLength() ) 
						plain2 = plain2 + number + CString(" # ");
					else
					{
						plain2 = plain2 + number;
						break;
					}
					plain.Delete(0, i);
					i = 0;
				}
				if ( i < plain.GetLength() ) i++;
			}
		}

		if ( !RSA->PreCheckInput( plain2, GetBase(), DlgOptions->m_RSAVariant ) )
		{
			UpdateData();
			m_edit_RSA_input = plain2;
			UpdateData(FALSE);
			return 1;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// Test, ob bei der Eingabe es sich um Zahlen handelt:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Wenn Ja: Rückfrage, ob die RSA-Invertierungsoperation durchgeführt werden
// Soll
BOOL CDlgRSADemo::CheckIfNumberStream()
{
	if ( 0 == m_EncryptTextOrNumbers )
	{
		int NumberStreamFlag;
		if ( !DlgOptions->m_RSAVariant )
			NumberStreamFlag = IsNumberStream( m_edit_RSA_input, GetBase(), m_edit_N, SPLIT_NUMBERS_VSMODUL );
		else
			NumberStreamFlag = IsNumberStream( m_edit_RSA_input, GetBase(), m_edit_N );
		if ( NumberStreamFlag )
		{
			if ( IDYES == Message( IDS_RSADEMO_REQUEST_FORNUMMBERS, MB_ICONEXCLAMATION | MB_YESNO ) )
			{
				UpdateData();
				m_EncryptTextOrNumbers = 1;
				UpdateData(FALSE);
			}
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//
//

bool CDlgRSADemo::CheckIfSignature()
{
	char buffer[MAX_BIT_LENGTH+1];
	int size = decode(m_edit_RSA_step_1, buffer, sizeof(buffer), 0, GetBase(), 0, NULL);
	int i, flag = 0;

	OctetString hash;
	hash.noctets=0;

	if ( 0 > m_edit_RSA_step_1.Find('#') && size > 30 ) 
	{
        for ( i=0; i<=size - 20; i++ ) 
		{
		   if      ( !memcmp(buffer+i, DER_MD2, DER_MD2_SIZE) )
		   {
			   SetHeadLine( m_Header_RSA_step_2, 
				            IDS_RSADEMO_OBTAINED_SIGNATURE, CString("MD2"));
			   i += (DER_MD2_SIZE);
			   flag = 1;
			   if ( message ) 
			   {
				   theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.md2_aid,NULL);
			   }	
			   break;
		   }
		   else if ( !memcmp(buffer+i, DER_MD5, DER_MD5_SIZE) )
		   {

			   SetHeadLine( m_Header_RSA_step_2, 
				            IDS_RSADEMO_OBTAINED_SIGNATURE, CString("MD5"));
			   i += (DER_MD5_SIZE);
			   flag = 1;
			   if ( message )
			   {			   
				   theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.md5_aid,NULL);
			   }
			   break;
		   }
		   else if ( !memcmp(buffer+i, DER_SHA, DER_SHA_SIZE) )
		   {

			   SetHeadLine( m_Header_RSA_step_2, 
				            IDS_RSADEMO_OBTAINED_SIGNATURE, CString("SHA"));
			   i += (DER_SHA_SIZE);
			   flag = 1;
			   if ( message )
			   {			   
				   theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.sha_aid,NULL);
			   }
			   break;
		   }
		   else if ( !memcmp(buffer+i, DER_SHA1, DER_SHA1_SIZE) )
		   {

			   SetHeadLine( m_Header_RSA_step_2, 
				            IDS_RSADEMO_OBTAINED_SIGNATURE, CString("SHA-1"));
			   i += (DER_SHA1_SIZE);
			   flag = 1;
			   if ( message )
			   {			   
				   theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.sha1_aid,NULL);
			   }
			   break;
		   }
		   else if ( !memcmp(buffer+i, DER_RIPEMD160, DER_RIPEMD160_SIZE) )
		   {

			   SetHeadLine( m_Header_RSA_step_2, 
				            IDS_RSADEMO_OBTAINED_SIGNATURE, CString("RIPEMD160"));
			   i += (DER_RIPEMD160_SIZE);
			   flag = 1;
			   if ( message )
			   {			   
				   theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.ripemd160_aid,NULL);
			   }
			   break;
		   }
		}
	}
	if ( flag ) 
	{
		dataToHexDump( buffer+i, size-i, m_edit_RSA_step_2); 
		if ( message && message->noctets )
		{		   			
			dataToHexDump( hash.octets, hash.noctets, m_edit_RSA_step_3);
			if ( memcmp(hash.octets, buffer+i, hash.noctets) )
			{
				LoadString(AfxGetInstanceHandle(),IDS_RSADEMO_NOT, pc_str,STR_LAENGE_STRING_TABLE);
				SetHeadLine( m_Header_RSA_step_3, IDS_RSADEMO_COMPARE_HASHVALUES, CString(pc_str), ":-(");
			}
			else
			{
				SetHeadLine( m_Header_RSA_step_3, IDS_RSADEMO_COMPARE_HASHVALUES, CString(""), ":-)");
			}
			theApp.SecudeLib.aux_free(hash.octets);
		}
		m_ButtonEncrypt.EnableWindow(FALSE);
		return true;
	}
	else        
	{
		return false;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Das RSA-Verschlüsseln von Zahlen:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 

void CDlgRSADemo::EncryptNumbers()
{

	CString tmpStr = m_edit_RSA_input;
	if (DlgOptions->m_RSAVariant)
	{
		IsNumberStream( tmpStr, GetBase(), m_edit_N, FORMAT_MODULO );
	}

	errorRSA = RSA->Encrypt( tmpStr, m_edit_RSA_step_1, GetBase() );
	if ( errorRSA == 2 )
	{
		Message( IDS_RSADEMO_NUMBERS_BIGGER_THAN_N, MB_ICONEXCLAMATION );
		return;
	}

	if ( !CheckIfSignature() )
	{
		if ( !DlgOptions->m_RSAVariant )
		{
					
			if ( !DlgOptions->m_TextOptions )
			{
				ReSegmentation( MODE_ASCII | RSA_DEMO_ENCRYPT );
			}
			else
			{
				ReSegmentation( MODE_ALPHABET | RSA_DEMO_ENCRYPT );
			}
		}
		else
		{  
			ReSegmentation( MODE_DLG_OF_SISTERS | RSA_DEMO_ENCRYPT );
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
// Button RSA-Verschlüsselung:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//

void CDlgRSADemo::OnButtonEncrypt() 
{
	CheckIfNumberStream();

	SHOW_HOUR_GLASS
	UpdateData(TRUE);
	if ( 0 == m_EncryptTextOrNumbers && !DlgOptions->m_RSAVariant && !DlgOptions->m_TextOptions && IsHexDump( m_edit_RSA_input ) )
	{
		HeadingEncryption( ENCRYPT_TEXT );
		Segmentation( MODE_HEX_DUMP );
		RSA->Encrypt( m_edit_RSA_step_2, m_edit_RSA_step_3, GetBase() );
	}
	else 	
	{
		if ( 0 == m_EncryptTextOrNumbers )
		{

			if ( !DlgOptions->m_RSAVariant )
			{
				HeadingEncryption( ENCRYPT_TEXT );
				if ( !DlgOptions->m_TextOptions )
				{
					Segmentation( MODE_ASCII );
				}
				else
				{
					if ( FALSE == SkipWS() ) return;
					Segmentation( MODE_ALPHABET );
				}
				RSA->Encrypt( m_edit_RSA_step_2, m_edit_RSA_step_3, GetBase() );
			}
			else
			{
				if ( FALSE == SkipWS() ) return;
				HeadingEncryption( ENCRYPT_TEXT );		
				Segmentation( MODE_DLG_OF_SISTERS );
				RSA->Encrypt( m_edit_RSA_step_2, m_edit_RSA_step_3, GetBase(), TRUE );
			}
		}
		else
		{	
			if ( 1 == CheckInversion() )
			{
				HeadingEncryption( ENCRYPT_NUMBERS );
				EncryptNumbers();
			}
			else if ( -1 == CheckInversion() )
			{
				Message(IDS_RSA_HEXNOTINVERTIBLE, MB_ICONEXCLAMATION);
			}
			else
			{
				int NumberStreamFlag;
				if ( !DlgOptions->m_RSAVariant )
					NumberStreamFlag = IsNumberStream( m_edit_RSA_input, GetBase(), m_edit_N /*, SPLIT_NUMBERS_VSMODUL */ );
				else
					NumberStreamFlag = IsNumberStream( m_edit_RSA_input, GetBase(), m_edit_N );
				if ( NumberStreamFlag )
				{
					EncryptNumbers();
					if ( !errorRSA ) HeadingEncryption( ENCRYPT_NUMBERS );
				}
				else
					Message( IDS_STRING_ERROR_NO_NUMBER_STREAM, MB_ICONEXCLAMATION, GetBase() );
				}
		}
	}
	UpdateData(FALSE);
	HIDE_HOUR_GLASS
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Das RSA-Entschlüsseln von Zahlen:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 

void CDlgRSADemo::DecryptNumbers()
{
	int ret = CheckInversion();

	if ( ret == -1 )
	{
		Message(IDS_RSA_HEXNOTINVERTIBLE, MB_ICONEXCLAMATION);
		return;
	}
	
	CString tmpStr = m_edit_RSA_input;
	if (DlgOptions->m_RSAVariant)
	{
		IsNumberStream( tmpStr, GetBase(), m_edit_N, FORMAT_MODULO );
	}

	errorRSA = RSA->Decrypt( tmpStr, m_edit_RSA_step_1, GetBase());
	if ( errorRSA == 2 )
	{
		Message( IDS_RSADEMO_NUMBERS_BIGGER_THAN_N, MB_ICONEXCLAMATION );
		return;
	}

	if ( !DlgOptions->m_RSAVariant )
	{

		if ( !DlgOptions->m_TextOptions )
		{				
			ReSegmentation( MODE_ASCII | RSA_DEMO_DECRYPT );
		}
		else
		{
			ReSegmentation( MODE_ALPHABET | RSA_DEMO_DECRYPT );
		}
	}
	else
	{
		ReSegmentation( MODE_DLG_OF_SISTERS | RSA_DEMO_DECRYPT );
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Button RSA-Entschlüsselung:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//

void CDlgRSADemo::OnButtonDecrypt() 
{
	CheckIfNumberStream();

	SHOW_HOUR_GLASS
	UpdateData(TRUE);
	if ( 0 == m_EncryptTextOrNumbers && !DlgOptions->m_RSAVariant && !DlgOptions->m_TextOptions && IsHexDump( m_edit_RSA_input ) )
	{
		Segmentation( MODE_HEX_DUMP );
		RSA->Decrypt( m_edit_RSA_step_2, m_edit_RSA_step_3, GetBase() );
	}
	else 
	{
		if ( 0 == m_EncryptTextOrNumbers )
		{
			if ( !DlgOptions->m_RSAVariant )
			{
				HeadingDecryption( DECRYPT_TEXT );
				if ( !DlgOptions->m_TextOptions )
				{
					Segmentation( MODE_ASCII );
				}
				else
				{
					if ( FALSE == SkipWS() ) return;
					Segmentation( MODE_ALPHABET );
				}
				RSA->Decrypt( m_edit_RSA_step_2, m_edit_RSA_step_3, GetBase() );
			}
			else
			{
				HeadingDecryption( DECRYPT_TEXT );		
				if ( FALSE == SkipWS() ) return;
				Segmentation( MODE_DLG_OF_SISTERS );
				RSA->Decrypt( m_edit_RSA_step_2, m_edit_RSA_step_3, GetBase(), TRUE );
			}
		}
		else
		{
			if ( 1 == CheckInversion() )
			{
				HeadingEncryption( ENCRYPT_NUMBERS );
				EncryptNumbers();
			}
			else if ( -1 == CheckInversion() )
			{
				Message(IDS_RSA_HEXNOTINVERTIBLE, MB_ICONEXCLAMATION);
			}
			else
			{
				int NumberStreamFlag;
				if ( !DlgOptions->m_RSAVariant )
					NumberStreamFlag = IsNumberStream( m_edit_RSA_input, GetBase(), m_edit_N /*, SPLIT_NUMBERS_VSMODUL */ );
				else
					NumberStreamFlag = IsNumberStream( m_edit_RSA_input, GetBase(), m_edit_N );

				if ( NumberStreamFlag )
				{
					DecryptNumbers();
					if ( !errorRSA ) HeadingDecryption( DECRYPT_NUMBERS );
				}
				else
					Message( IDS_STRING_ERROR_NO_NUMBER_STREAM, MB_ICONEXCLAMATION, GetBase() );
			}
		}
	}
	UpdateData(FALSE);
	HIDE_HOUR_GLASS
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// RSA - Kodierung von Text & RSA-Operation:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1. Aufteilung des Textes In Blöken
// 2. Kodieren dieser Text-Blöcke in Zahlen < N
// 3. RSA-Verschlüsseln dieser Zahlen

void CDlgRSADemo::Segmentation( int mode )
{
	int blockSize    = DlgOptions->m_BlockLength;
	CString tmpStr;
	CString NumStr;

	int baseNumbers = GetBase();
	m_edit_RSA_step_2 = ""; 
	m_edit_RSA_step_1 = ""; 

	for (int i = 0; i<m_edit_RSA_input.GetLength(); )
	{
		if ( mode == MODE_HEX_DUMP ) {
			int j=i;
			int cnt=0;
			while (j < m_edit_RSA_input.GetLength() && cnt < 2*blockSize )
				if ( IsNumber( m_edit_RSA_input[j++], BASE_HEX ) ) cnt++;
			tmpStr    = m_edit_RSA_input.Mid(i, j-i);
			while ( cnt < 2*blockSize )
			{
				if ( cnt < 2*blockSize-1 && 0 == cnt % 2 ) tmpStr += ' ';
				tmpStr += '0';				
				cnt++;
			}
			m_edit_RSA_step_1 += tmpStr;			
			i = j;
		}
		else
		{
			m_edit_RSA_step_1 += m_edit_RSA_input.Mid(i, blockSize);
			tmpStr    = m_edit_RSA_input.Mid(i, blockSize);
			while ( tmpStr.GetLength() < blockSize ) { 
				tmpStr += ' '; m_edit_RSA_step_1 += ' '; 
			}
			i += blockSize;
		}
		switch ( mode ) {
			case MODE_HEX_DUMP:
				{
					char *data;
					data = new char[blockSize];
					if ( blockSize == HexDumpToData( tmpStr, data ) )
					{
						encode( data, NumStr, blockSize, baseNumbers, (DlgOptions->m_codingMethod == 1), NULL );
					}
					delete []data;
				}
				break;
			case MODE_ASCII: 
				encode( tmpStr.GetBuffer(0), NumStr, blockSize, baseNumbers, (DlgOptions->m_codingMethod == 1), NULL );
				break;
			case MODE_ALPHABET:
				encode( tmpStr.GetBuffer(0), NumStr, blockSize, baseNumbers, (DlgOptions->m_codingMethod == 1), DlgOptions->m_alphabet );
				break;
			case MODE_DLG_OF_SISTERS:
				encode( tmpStr.GetBuffer(0), NumStr, blockSize, baseNumbers, (DlgOptions->m_codingMethod == 1), DlgOptions->m_alphabet );
				RandRepr( NumStr, DlgOptions->m_alphabet.GetLength(), baseNumbers, 1, 1 );				
				break;
		}
		m_edit_RSA_step_2 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i < m_edit_RSA_input.GetLength() ) 
		{
			m_edit_RSA_step_2 += " # ";
			m_edit_RSA_step_1 += " # ";
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
// RSA-Operation & folgende Dekodierung der Zahlen in Text (wenn möglich): 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1. RSA-Entschlüsselung der Zahlenblöcke
// 2. Dekodieren der ZahlenBlöcke in Text (Wenn möglich)
// 3. Entfernen der Segmentierung

BOOL CDlgRSADemo::ReSegmentation( int mode )
{
	int blockSize   = DlgOptions->m_BlockLength;
	int baseNumbers = GetBase();

	m_edit_RSA_step_2 = "";
	m_edit_RSA_step_3 = "";
	BOOL flag = TRUE, hexDumpFlag = FALSE;
	int i1, i2;
	i1 = i2 = 0;
	CString tmp1;
	CString hexDump1 = "";
 	CString hexDump2 = "";
	// *************  Hier noch richtige groesse finden ....
	char _tmp2[MAX_BIT_LENGTH+1]; // FIXME

	while (i1 < m_edit_RSA_step_1.GetLength() && (m_edit_RSA_step_1[i1] == ' ' || m_edit_RSA_step_1[i1] == '#') ) i1++;
	while ( i1 < m_edit_RSA_step_1.GetLength() )
	{
		i2 = m_edit_RSA_step_1.Find(" ", i1);
		if (i2 < 0) 
		{
			if ( i1 < m_edit_RSA_step_1.GetLength() ) i2 = m_edit_RSA_step_1.GetLength();
			else break;
		}
		tmp1 = m_edit_RSA_step_1.Mid(i1, i2-i1);
		switch ( mode & 15 ) {
			case MODE_ASCII: 
				if ( !(blockSize ==  decode( tmp1, _tmp2, sizeof(_tmp2), blockSize, baseNumbers, (DlgOptions->m_codingMethod == 1), NULL )) )
					flag = FALSE;
				break;
			case MODE_ALPHABET:
				if ( !(blockSize ==  decode( tmp1, _tmp2, sizeof(_tmp2), blockSize, baseNumbers, 
					                         (DlgOptions->m_codingMethod == 1), DlgOptions->m_alphabet )) )
					flag = FALSE;
				break;
			case MODE_DLG_OF_SISTERS:
				ModRepr ( tmp1, DlgOptions->m_alphabet.GetLength()+1, baseNumbers, -1 ); 
				if ( !(blockSize ==  decode( tmp1, _tmp2, sizeof(_tmp2), blockSize, baseNumbers, FALSE, DlgOptions->m_alphabet )) )
					flag = FALSE;
				break;
		}
		if ( flag )
		{
			if ( (mode & 15)== MODE_ASCII )
			{
				for ( int i=0; i<blockSize; i++ ) if ( !IsPrint(_tmp2[i]) )
					hexDumpFlag = TRUE;
				dataToHexDump( _tmp2, blockSize, tmp1 );
				hexDump1 += tmp1; 
				hexDump2 += tmp1;
			}
			m_edit_RSA_step_2 += _tmp2;
			m_edit_RSA_step_3 += _tmp2;
		}
		else
		{
			if ( RSA_DEMO_DECRYPT == (mode & RSA_DEMO_DECRYPT) )
				LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_MSG_DECRYPTION_NOTEXT,pc_str,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_MSG_ENCRYPTION_NOTEXT,pc_str,STR_LAENGE_STRING_TABLE);
			m_edit_RSA_step_2  = pc_str; 
			m_edit_RSA_step_3  = "";
			m_Header_RSA_step_2 = "";
			m_Header_RSA_step_3 = "";
			break;
		}
		
		while ((i2 < m_edit_RSA_step_1.GetLength()) && (m_edit_RSA_step_1[i2] == ' ' || m_edit_RSA_step_1[i2] == '#')) i2++;
		i1 = i2;
		if ( i1 < m_edit_RSA_step_1.GetLength() ) {
			if ( mode == MODE_ASCII ) hexDump1 += " # ";
			m_edit_RSA_step_2 += " # ";
		}
	}
	if ( mode == MODE_ASCII && hexDumpFlag )
	{
		m_edit_RSA_step_2 = hexDump1;
		m_edit_RSA_step_3 = hexDump2;
	}
	return flag;
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  P A S T E  -  F I L T E R    F Ü R   D I E   R S A  -  E I N G A B E   //
//                                                                         // 
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CMyRSADemoEdit

CMyRSADemoEdit::CMyRSADemoEdit()
{
}

CMyRSADemoEdit::~CMyRSADemoEdit()
{
}


BEGIN_MESSAGE_MAP(CMyRSADemoEdit, CEdit)
	//{{AFX_MSG_MAP(CMyRSADemoEdit)
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_PASTE, OnMyPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//
// Behandlungsroutinen für Nachrichten CMyRSADemoEdit 
//

void CMyRSADemoEdit::OnMyPaste() 
{
	OpenClipboard();
	HANDLE hndl;
	char *globBuff, *dataBuff;
	long  dataLen;

	EncryptTextOrNumbers = 0;
	if ( mode == MODE_ASCII )
	{
		if( hndl = ::GetClipboardData(theApp.m_HexFormat)) 
		{
			globBuff = (char *) GlobalLock(hndl);
			dataLen = ((long *) globBuff)[0];
			dataBuff = globBuff+sizeof(long);
			char *tmpIn  = new char[dataLen+1];
			memcpy( tmpIn, dataBuff, dataLen);
			int OutLength = 0;
			CString P;
			dataToHexDump( tmpIn, dataLen, P);
			delete []tmpIn;

			int startc, endc;
			GetSel(startc, endc );
			ReplaceSel( P );
			startc += P.GetLength();
			SetSel( startc, startc );
			GlobalUnlock(hndl);
			CloseClipboard();
		}
		else if ( hndl = ::GetClipboardData(CF_TEXT) )
		{
			globBuff = (char *) GlobalLock(hndl);
			dataLen = strlen(globBuff);
			dataBuff = globBuff;
			char *tmpIn  = new char[dataLen+1];
			CString P = _T("");
			unsigned char *p = (unsigned char*)dataBuff;
			for ( int i=0; i<dataLen; i++ )
			{
				if ( p[i] >= 32 && IsPrint( (unsigned char)p[i] ) )
				{
					P += p[i];
				}
				else if ( p[i] == '\r' ) // Kodieren eines <CR> als <SPACE>
				{
					P += ' ';
				}
			}
			
			
			
			{  // *** Check the Pasted String if it is a stream of numbers
				CString CheckStr = P;
				if ( IsHexDump(CheckStr) )
				{
					P = CheckStr;
					EncryptTextOrNumbers = 1;
				}
				else if ( IsNumberStream(CheckStr, 16, "0") )
				{
					P = CheckStr;
					EncryptTextOrNumbers = 1;
				}
			}
			int startc, endc;
			GetSel(startc, endc );
			ReplaceSel( P );
			startc += P.GetLength();
			SetSel( startc, startc );
			GlobalUnlock(hndl);
			CloseClipboard();
		}
	}
	else
	{
		if ( hndl = ::GetClipboardData(CF_TEXT) )
		{
			globBuff = (char *) GlobalLock(hndl);
			dataLen = strlen(globBuff);
			dataBuff = globBuff;
			char *tmpIn  = new char[dataLen+1];
			char *tmpOut = new char[4*dataLen+1];
			memcpy( tmpIn, dataBuff, dataLen);
			tmpIn[dataLen] = '\0';
			unsigned char *p = (unsigned char*)dataBuff;
			CString P = _T("");
			for ( int i=0; i<dataLen; i++ )
			{
				if ( p[i] >= 32 && IsPrint( (unsigned char)p[i] ) )
				{
					P += p[i];
				}
				else if ( p[i] == '\r' ) // Kodieren eines <CR> als <SPACE>
				{
					P += ' ';
				}
			}
			// *** Check the Pasted String if it is a stream of numbers
			{
				CString CheckStr = P;
				if ( IsHexDump(CheckStr) )
				{
					P = CheckStr;
					EncryptTextOrNumbers = 1;
				}
				else if ( IsNumberStream(CheckStr, 16, "0") )
				{
					P = CheckStr;
					EncryptTextOrNumbers = 1;
				}
			}
			int startc, endc;
			GetSel(startc, endc );
			ReplaceSel( P );
			startc += P.GetLength();
			SetSel( startc, startc );
			GlobalUnlock(hndl);
			CloseClipboard();
		}
	}

}


/////////////////////////////////////////////////////////////////////////
//
// 
//

void CMyRSADemoEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen


	long curp = GetSel();
	if ( nChar == 22 && ((nFlags & 47) == 47) )
	{
		OnMyPaste();
	}
	else
	{
		CEdit::OnChar(nChar,nRepCnt,nFlags);
	}
}




void CDlgRSADemo::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	int i = 0;
  	i = i*2;
	// CDialog::OnOK();
}


