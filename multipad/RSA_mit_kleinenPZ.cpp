// RSA_mit_kleinenPZ.cpp: Implementierungsdatei
//
#include "stdafx.h"
#include "Afx.h"
#include "multipad.h"
#include "DlgRSAwithSmallPrimesOptions.h"
#include "RSA_mit_kleinenPZ.h"
#include "crypt.h"
#include "ChrTools.h"
#include "fileutil.h"
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


/////////////////////////////////////////////////////////////////////////////
//
// Dialogfeld RSA_mit_kleinenPZ 
//

void RSA_mit_kleinenPZ::SetHeadLine(CString &mHeader, int IDS_STRING_ID, int base)
{
	char line[IDS_STRINGLENGTH];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	if ( base ) sprintf( line, pc_str, base );
	else	    sprintf( line, pc_str );
	mHeader = line;
}

///////////////////////////////////////////////////////////////////////////////
//
// Constructor/Destructor + MFC Source
// 

RSA_mit_kleinenPZ::RSA_mit_kleinenPZ(CWnd* pParent /*=NULL*/)
: CDialog(RSA_mit_kleinenPZ::IDD, pParent) 
{
	//{{AFX_DATA_INIT(RSA_mit_kleinenPZ)
	m_eingabe_p = _T("");
	m_eingabe_q = _T("");
	m_geheime_parameter = _T("");
	m_oeffentliche_parameter_pq = _T("");
	m_oeffentliche_schluessel_e = _T("2^16+1");
	m_geheime_schluessel_d = _T("");
	m_edit10 = _T("");
	m_edit11 = _T("");
	m_edit12 = _T("");
	m_Header1 = _T("");
	m_Header2 = _T("");
	m_Header3 = _T("");
	m_Header4 = _T("");
	m_edit13 = _T("");
	m_EncryptTextOrNumbers = m_control_edit10.EncryptTextOrNumbers = 0;
	//}}AFX_DATA_INIT

	DlgOptions   = new CDlgRSAwithSmallPrimesOptions();
	DlgRSAPrimes = new DlgPrimesGenerator();
	RSA          = new TutorialRSA;
}

RSA_mit_kleinenPZ::~RSA_mit_kleinenPZ()
{
	delete DlgOptions;
	delete DlgRSAPrimes;
	delete RSA;
}




void RSA_mit_kleinenPZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RSA_mit_kleinenPZ)
	DDX_Control(pDX, IDC_EDIT5, m_control_edit5);
	DDX_Control(pDX, IDC_EDIT13, m_control_edit13);
	DDX_Control(pDX, IDC_OPTIONEN, m_ButtonOptionen);
	DDX_Control(pDX, IDC_BUTTON_VERSCHLUESSELN, m_ButtonEncrypt);
	DDX_Control(pDX, IDC_BUTTON_ENTSCHLUESSELN, m_ButtonDecrypt);
	DDX_Control(pDX, IDC_EDIT11, m_control_edit11);
	DDX_Control(pDX, IDC_EDIT12, m_control_edit12);
	DDX_Control(pDX, IDC_EDIT10, m_control_edit10);
	DDX_Control(pDX, IDC_EDIT2, m_control_q);
	DDX_Control(pDX, IDC_EDIT1, m_control_p);
	DDX_Text(pDX, IDC_EDIT1, m_eingabe_p);
	DDX_Text(pDX, IDC_EDIT2, m_eingabe_q);
	DDX_Text(pDX, IDC_EDIT4, m_geheime_parameter);
	DDX_Text(pDX, IDC_EDIT3, m_oeffentliche_parameter_pq);
	DDX_Text(pDX, IDC_EDIT5, m_oeffentliche_schluessel_e);
	DDX_Text(pDX, IDC_EDIT6, m_geheime_schluessel_d);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	DDX_Text(pDX, IDC_EDIT11, m_edit11);
	DDX_Text(pDX, IDC_EDIT12, m_edit12);
	DDX_Text(pDX, IDC_HEADER1, m_Header1);
	DDX_Text(pDX, IDC_HEADER2, m_Header2);
	DDX_Text(pDX, IDC_HEADER3, m_Header3);
	DDX_Text(pDX, IDC_HEADER4, m_Header4);
	DDX_Text(pDX, IDC_EDIT13, m_edit13);
	DDX_Radio(pDX, IDC_RADIO1, m_EncryptTextOrNumbers);
	//}}AFX_DATA_MAP
}


//******************************************************************************
BEGIN_MESSAGE_MAP(RSA_mit_kleinenPZ, CDialog)
	//{{AFX_MSG_MAP(RSA_mit_kleinenPZ)
	ON_BN_CLICKED(IDC_BUTTON_PZ_GENERIEREN, OnButtonPzGenerieren)
	ON_EN_UPDATE(IDC_EDIT10, OnUpdateEdit10)
	ON_BN_CLICKED(IDC_OPTIONEN, OnOptionen)
	ON_BN_CLICKED(IDC_BUTTON2, OnParameterAktualisieren)
	ON_BN_CLICKED(IDC_BUTTON_VERSCHLUESSELN, OnButtonVerschluesseln)
	ON_BN_CLICKED(IDC_BUTTON_ENTSCHLUESSELN, OnButtonEntschluesseln)
	ON_BN_CLICKED(IDC_ENDDIALOG, OnEndDialog)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdatePrimeP)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdatePrimeQ)
	ON_EN_UPDATE(IDC_EDIT5, OnUpdatePublicKeyE)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// 
// The Primes P & Q may generated external
// 

void RSA_mit_kleinenPZ::OnButtonPzGenerieren() 
{
	UpdateData(true);
	
	if ( IDOK == DlgRSAPrimes->DoModal() )
	{
		int Parameter_N_zu_gross;
		m_eingabe_p = DlgRSAPrimes->m_edit5;
		m_eingabe_q = DlgRSAPrimes->m_edit6;
		Parameter_N_zu_gross = RSA->InitParameter( m_eingabe_p, m_eingabe_q );
		if (Parameter_N_zu_gross==0)
		{
			if (RSA->SetPublicKey( m_oeffentliche_schluessel_e ) )
			{
				RSA->SetPrivateKey();
				RSA->GetParameter( m_oeffentliche_parameter_pq, m_geheime_parameter, 
								   m_oeffentliche_schluessel_e, m_geheime_schluessel_d );
			}
			else
			{
				CString t1, t2;
				RSA->GetParameter( m_oeffentliche_parameter_pq, m_geheime_parameter, t1, t2 );
				m_geheime_schluessel_d = "";
			}
			if ( RSA->IsInitialized() )
			{
				EnableEncryption();
				m_ButtonOptionen.EnableWindow(true);
				SetDlgOptions();
				RequestForInput(FALSE);
			}
			else
			{
				EnableEncryption(false);
				m_ButtonOptionen.EnableWindow(false);
			}
		}
		else
		{
			Message(IDS_STRING_BIG_RSA_MODUL, MB_ICONSTOP);
			EnableEncryption(false);
			m_ButtonOptionen.EnableWindow(false);
			m_eingabe_p = _T("");
			m_eingabe_q = _T("");
			m_geheime_parameter = _T("");
			m_oeffentliche_parameter_pq = _T("");
			m_geheime_schluessel_d = _T("");
			m_control_p.SetFocus();
		}
	}
	UpdateData(false);
}

///////////////////////////////////////////////////////////////////////////
//
// This Button will be later obsolete
//

void RSA_mit_kleinenPZ::OnParameterAktualisieren() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(true);
	int RSAInitError;
	int RSASetPublicKeyError;

	CString UpnFormula;
	int err_ndx;
	BOOL error;
	
	error = CheckFormula(m_eingabe_p,10,UpnFormula,err_ndx);
	if (error==0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_p.SetSel(err_ndx-1,m_eingabe_p.GetLength());
		m_control_p.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
		return;
	}

	error = CheckFormula(m_eingabe_q,10,UpnFormula,err_ndx);
	if (error==0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_q.SetSel(err_ndx-1,m_eingabe_q.GetLength());
		m_control_q.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
		return;
	}
	error = CheckFormula(m_oeffentliche_schluessel_e,10,UpnFormula,err_ndx);
	if (error==0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_edit5.SetSel(err_ndx-1,m_oeffentliche_schluessel_e.GetLength());
		m_control_edit5.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
		return;
	}


	if ( 0 == (RSAInitError = RSA->InitParameter( m_eingabe_p, m_eingabe_q )) )
	{
		RSASetPublicKeyError = RSA->SetPublicKey( m_oeffentliche_schluessel_e );
		if (1 == RSASetPublicKeyError )
		{
			RSA->SetPrivateKey();
			RSA->GetParameter( m_oeffentliche_parameter_pq, m_geheime_parameter, 
					   m_oeffentliche_schluessel_e, m_geheime_schluessel_d );
		}
		else if (0 == RSASetPublicKeyError)
		{
			// Falls e nicht coprime zu phi(N) ist, wird man aufgefordert eine andere Zahl für e zu wählen
			Message(IDS_STRING_RSATUT_WRONG_PUBLICKEY, MB_ICONINFORMATION);
			m_geheime_schluessel_d = "";
			m_control_edit5.SetFocus();
			return;
		}
		else
		{
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			m_control_edit5.SetFocus();
			m_control_edit5.SetSel(0,-1);
			return;
		}
	}
	else 
	{
		// In diesem Fall ist mindestens eine der Zahlen p oder q keine Primzahl.

		if ( ERR_P_TO_BIG == RSAInitError )
		{
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			m_control_p.SetFocus();
			m_control_p.SetSel(0,-1);
			return;
		}
		if ( ERR_Q_TO_BIG == RSAInitError )
		{
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			m_control_q.SetFocus();
			m_control_q.SetSel(0,-1);
			return;
		}
		if ( ERR_P_NOT_PRIME == RSAInitError )
		{
			Message(IDS_STRING_RSADEMO_P_NOT_PRIME, MB_ICONINFORMATION);
			m_control_p.SetFocus();
			return;
		}
		if ( ERR_Q_NOT_PRIME == RSAInitError )
		{
			Message(IDS_STRING_RSADEMO_Q_NOT_PRIME, MB_ICONINFORMATION);
			m_control_q.SetFocus();
			m_geheime_schluessel_d = "";
			return;
		}
		if ( ERR_P_EQUALS_Q == RSAInitError )
		{
			Message(IDS_STRING_ERR_PRIME_ARE_EQUAL, MB_ICONINFORMATION);
			m_control_p.SetFocus();
			m_geheime_schluessel_d = "";
			return;
		}
	}

	SetDlgOptions();
	
	if ( RSA->IsInitialized() && DlgOptions->m_BlockLength!=0 && DlgOptions->m_alphabet.GetLength()<m_oeffentliche_schluessel_e)
	{
		if (DlgOptions->m_RSAVariant==0)
		{
			LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
			CString Primes = m_eingabe_p + ";" + m_eingabe_q + ";"+m_oeffentliche_schluessel_e;
			CopyKey ( pc_str, Primes );
			EnableEncryption(true);
			m_ButtonOptionen.EnableWindow(true);
		}
		else
		{
			if (DlgOptions->m_TextOptions==0)
			{
				DlgOptions->Anzahl_Zeichen=256;	
			}
			else
			{
				DlgOptions->Anzahl_Zeichen=DlgOptions->m_alphabet.GetLength();
			}
			if ( DlgOptions->Anzahl_Zeichen <= atoi(m_oeffentliche_parameter_pq))
			{
				LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
				CString Primes = m_eingabe_p + ";" + m_eingabe_q + ";"+m_oeffentliche_schluessel_e;
				CopyKey ( pc_str, Primes );
				EnableEncryption(true);
				m_ButtonOptionen.EnableWindow(true);	
			}
			else
			{
				Message(!m_EncryptTextOrNumbers? IDS_STRING_RSADEMO_MODUL_KLEIN: IDS_STRING_RSADEMO_MODUL_KLEIN_NUM, MB_ICONEXCLAMATION, 
					    DlgOptions->Anzahl_Zeichen, m_oeffentliche_parameter_pq );
				EnableEncryption(false);
				m_ButtonOptionen.EnableWindow(true);
			}
		}
	}
	else 
	{
		if (DlgOptions->m_TextOptions==0)
		{
			DlgOptions->Anzahl_Zeichen=256;	
		}
		else
		{
			DlgOptions->Anzahl_Zeichen=DlgOptions->m_alphabet.GetLength();
		}
		Message(!m_EncryptTextOrNumbers? IDS_STRING_RSADEMO_MODUL_KLEIN: IDS_STRING_RSADEMO_MODUL_KLEIN_NUM, MB_ICONEXCLAMATION, DlgOptions->Anzahl_Zeichen, m_oeffentliche_parameter_pq );
		EnableEncryption(false);
		m_ButtonOptionen.EnableWindow(true);		
	}	
	RequestForInput(FALSE);
	UpdateData(false);		
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// Delete the En/Decryption output if the input is changed
//

void RSA_mit_kleinenPZ::OnUpdateEdit10() 
{
	UpdateData(true);
	RequestForInput( FALSE );
	UpdateData(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Set the RSA Encryption/Decryption Options via external Dialouge
//

void RSA_mit_kleinenPZ::OnOptionen() 
{
	UpdateData(TRUE);
	SetDlgOptions();	
	if ( IDOK == DlgOptions->DoModal()) 
	{
		RequestForInput();
		EnableEncryption();
		m_control_edit10.mode = DlgOptions->m_TextOptions;
	}	
	else 
	{
		if ( DlgOptions->Anzahl_Zeichen > atoi(m_oeffentliche_parameter_pq))
		{
			Message(!m_EncryptTextOrNumbers? IDS_STRING_RSADEMO_MODUL_KLEIN: IDS_STRING_RSADEMO_MODUL_KLEIN_NUM, MB_ICONEXCLAMATION, 
				DlgOptions->Anzahl_Zeichen, m_oeffentliche_parameter_pq );
			EnableEncryption(false);
		}
	}

	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	UpdateData(FALSE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// the RSA Encryption/Decryption depends on the type of INPUT 
//

void RSA_mit_kleinenPZ::OnButtonVerschluesseln() 
{
	theApp.DoWaitCursor(1);
	UpdateData(TRUE);
	if ( 0 == m_EncryptTextOrNumbers && !DlgOptions->m_RSAVariant && !DlgOptions->m_TextOptions && IsHexDump( m_edit10 ) )
	{
		Segmentation( MODE_HEX_DUMP );
		RSA->Encrypt( m_edit11, m_edit12, GetBase() );
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
				RSA->Encrypt( m_edit11, m_edit12, GetBase() );
			}
			else
			{
				if ( FALSE == SkipWS() ) return;
				HeadingEncryption( ENCRYPT_TEXT );		
				Segmentation( MODE_DLG_OF_SISTERS );
				RSA->Encrypt( m_edit11, m_edit12, GetBase(), TRUE );
			}
		}
		else
		{
			int NumberStreamFlag;
			if ( !DlgOptions->m_RSAVariant )
				NumberStreamFlag = IsNumberStream( m_edit10, GetBase(), m_oeffentliche_parameter_pq, SPLIT_NUMBERS_VSMODUL );
			else
				NumberStreamFlag = IsNumberStream( m_edit10, GetBase(), m_oeffentliche_parameter_pq );
			if ( NumberStreamFlag )
			{
				HeadingEncryption( ENCRYPT_NUMBERS );
				EncryptNumbers();
			}
			else
				Message( IDS_STRING_ERROR_NO_NUMBER_STREAM, MB_ICONEXCLAMATION, GetBase() );
		}
	}
	UpdateData(FALSE);
	theApp.DoWaitCursor(-1);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Decryption Button Clicked ...
//

void RSA_mit_kleinenPZ::OnButtonEntschluesseln() 
{
	theApp.DoWaitCursor(1);
	UpdateData(TRUE);
	if ( 0 == m_EncryptTextOrNumbers && !DlgOptions->m_RSAVariant && !DlgOptions->m_TextOptions && IsHexDump( m_edit10 ) )
	{
		Segmentation( MODE_HEX_DUMP );
		RSA->Decrypt( m_edit11, m_edit12, GetBase() );
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
				RSA->Decrypt( m_edit11, m_edit12, GetBase() );
			}
			else
			{
				HeadingDecryption( DECRYPT_TEXT );		
				if ( FALSE == SkipWS() ) return;
				Segmentation( MODE_DLG_OF_SISTERS );
				RSA->Decrypt( m_edit11, m_edit12, GetBase(), TRUE );
			}
		}
		else
		{
			int NumberStreamFlag;
			if ( !DlgOptions->m_RSAVariant )
				NumberStreamFlag = IsNumberStream( m_edit10, GetBase(), m_oeffentliche_parameter_pq, SPLIT_NUMBERS_VSMODUL );
			else
				NumberStreamFlag = IsNumberStream( m_edit10, GetBase(), m_oeffentliche_parameter_pq );

			if ( NumberStreamFlag )
			{
				HeadingDecryption( DECRYPT_NUMBERS );
				DecryptNumbers();
			}
			else
				Message( IDS_STRING_ERROR_NO_NUMBER_STREAM, MB_ICONEXCLAMATION, GetBase() );
		}
	}
	UpdateData(FALSE);
	theApp.DoWaitCursor(-1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// The RSA Encryption/Decryption of numbers results in a Message or into a stream of numbers
// 

void RSA_mit_kleinenPZ::EncryptNumbers()
{
	
	RSA->Encrypt( m_edit10, m_edit13, GetBase() );

	if ( !DlgOptions->m_RSAVariant )
	{
				
		if ( !DlgOptions->m_TextOptions )
		{
			ReSegmentation( MODE_ASCII );
		}
		else
		{
			ReSegmentation( MODE_ALPHABET );
		}
	}
	else
	{  
		ReSegmentation( MODE_DLG_OF_SISTERS );
	}

}

void RSA_mit_kleinenPZ::DecryptNumbers()
{
	
	RSA->Decrypt( m_edit10, m_edit13, GetBase() );

	if ( !DlgOptions->m_RSAVariant )
	{

		if ( !DlgOptions->m_TextOptions )
		{				
			ReSegmentation( MODE_ASCII );
		}
		else
		{
			ReSegmentation( MODE_ALPHABET );
		}
	}
	else
	{
		ReSegmentation( MODE_DLG_OF_SISTERS );
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// O.K. kill the RSA - Demo
//
 
void RSA_mit_kleinenPZ::OnEndDialog() 
{
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// O.K. start the RSA Demo
//

BOOL RSA_mit_kleinenPZ::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_control_p.SetFocus();
	EnableEncryption(false);
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE);
	CString Primes;
	if ( PasteKey( pc_str, Primes ) )
	{
		UpdateData(true);
		int d1 = Primes.Find(';', 0);
		int d2 = Primes.Find(';', d1+1);
		m_eingabe_p = Primes.Mid(0, d1);
		m_eingabe_q = Primes.Mid(d1+1, ((d2-d1)-1));
		m_oeffentliche_schluessel_e = Primes.Mid(d2+1);
		UpdateData(false);
		OnParameterAktualisieren();
	}
	else
	{
		m_ButtonOptionen.EnableWindow(false);
	}
	m_control_edit10.mode = DlgOptions->m_TextOptions;

	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	return FALSE;  // return TRUE unless you set the focus to a control
 	               // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
// You may enter the Primes ... e.g. P = 2^4+1, Q = 2^3-1
//

void RSA_mit_kleinenPZ::OnUpdatePrimeP() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	RequestForInput(FALSE);

	UpdateData(TRUE); // get the displayed value in m_text 
	m_control_p.GetSel(sels, sele);

	res.Empty();
	
	for(k=i=0;i<m_eingabe_p.GetLength();i++) {
		c = m_eingabe_p[i];
		res += c;
		k++;
	}

	m_eingabe_p = res;
	if ( m_eingabe_p.GetLength() )
	{
		m_geheime_parameter = _T("");
		m_oeffentliche_parameter_pq = _T("");
		m_geheime_schluessel_d = _T("");
		RequestForInput(FALSE);
		EnableEncryption(false);
	}
	
	UpdateData(FALSE);
	m_control_p.SetSel(sels,sele);

}

void RSA_mit_kleinenPZ::OnUpdatePrimeQ() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	RequestForInput(FALSE);

	UpdateData(TRUE); // get the displayed value in m_text 
	m_control_q.GetSel(sels, sele);
	
	res.Empty();

	for(k=i=0;i<m_eingabe_q.GetLength();i++) {
		c = m_eingabe_q[i];
		res += c;
		k++;
	}
	m_eingabe_q = res;
	if ( m_eingabe_q.GetLength() )
	{
		m_geheime_parameter = _T("");
		m_oeffentliche_parameter_pq = _T("");
		m_geheime_schluessel_d = _T("");
		RequestForInput(FALSE);
		EnableEncryption(false);
	}
	
	UpdateData(FALSE);
	m_control_q.SetSel(sels,sele);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//
//

void RSA_mit_kleinenPZ::OnUpdatePublicKeyE() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	RequestForInput(FALSE);

	UpdateData(TRUE); // get the displayed value in m_text 
	m_control_edit5.GetSel(sels, sele);
	
	res.Empty();

	for(k=i=0;i<m_oeffentliche_schluessel_e.GetLength();i++) {
		c = m_oeffentliche_schluessel_e[i];
		res += c;
		k++;
	}

	m_oeffentliche_schluessel_e = res;
	if ( m_oeffentliche_schluessel_e.GetLength() )
	{
		m_geheime_parameter = _T("");
		m_oeffentliche_parameter_pq = _T("");
		m_geheime_schluessel_d = _T("");
		m_edit10 = _T("");
		EnableEncryption(false);
	}
	
	UpdateData(FALSE);
	m_control_edit5.SetSel(sels,sele);
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Small Tools
//

int RSA_mit_kleinenPZ::GetBase()
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

void RSA_mit_kleinenPZ::RequestForInput( BOOL clearInput )
{

	if ( clearInput ) m_edit10.Empty();
	m_edit11.Empty();
	m_edit12.Empty();
	m_edit13.Empty();
	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	m_Header2.Empty();
	m_Header3.Empty();
	m_Header4.Empty();

}


void RSA_mit_kleinenPZ::EnableEncryption(BOOL mode)
{
	m_ButtonDecrypt.EnableWindow(mode);		
	m_ButtonEncrypt.EnableWindow(mode);	

	
}


void RSA_mit_kleinenPZ::HeadingEncryption( BOOL encryptText )
{
	if ( encryptText ) 
	{
		SetHeadLine( m_Header1, IDS_STRING_RSATUT_INPUTPLAINTEXT );
		SetHeadLine( m_Header4, IDS_STRING_RSA_TUT_TEXTSEGMENTATION );
		SetHeadLine( m_Header2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
		SetHeadLine( m_Header3, IDS_STRING_RSA_TUTORIAL_ENCRYPTION );
	}
	else
	{
		SetHeadLine( m_Header1, IDS_STRING_RSATUT_PLAINTEXTNUMBERS, GetBase() );
		SetHeadLine( m_Header4, IDS_STRING_RSA_TUTORIAL_ENCRYPTION );
		SetHeadLine( m_Header2, IDS_STRING_RSA_OUTPUT_TEXTSEGMENTATION );
		SetHeadLine( m_Header3, IDS_RSA_MKPZ_CIPHERTEXT );
	}
}

void RSA_mit_kleinenPZ::HeadingDecryption( BOOL decryptText )
{
	if ( decryptText ) 
	{
		SetHeadLine( m_Header1, IDS_STRING_RSATUT_INPUTPLAINTEXT );
		SetHeadLine( m_Header4, IDS_STRING_RSA_TUT_TEXTSEGMENTATION );
		SetHeadLine( m_Header2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
		SetHeadLine( m_Header3, IDS_STRING_RSA_TUTORIAL_DECRYPTION );
	}
	else
	{
		SetHeadLine( m_Header1, IDS_STRING_RSATUT_CIPHERTEXTNUMBERS, GetBase() );
		SetHeadLine( m_Header4, IDS_STRING_RSA_TUTORIAL_DECRYPTION );
		SetHeadLine( m_Header2, IDS_STRING_RSA_OUTPUT_TEXTSEGMENTATION );
		SetHeadLine( m_Header3, IDS_RSA_MKPZ_PLAINTEXT );
	}
}


BOOL RSA_mit_kleinenPZ::SkipWS()
{
	CString cleanStr = m_edit10;
	for (int i=0 ;i<cleanStr.GetLength();)
	{
		if ( !isCharOf(cleanStr[i], DlgOptions->m_alphabet.GetBuffer(0)) )
			cleanStr.Delete(i);
		else
			i++;
	}
	if ( m_edit10.GetLength() != cleanStr.GetLength() )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_WARN_BEFOR_SKIPWS, pc_str,STR_LAENGE_STRING_TABLE);
		int RetValue;
		if ( 1 != (RetValue = MessageBox(pc_str, "RSA Demo", MB_OKCANCEL | MB_ICONINFORMATION )) )
		{
			return FALSE;
		}
	}
	m_edit10 = cleanStr;
	return TRUE;
}


void RSA_mit_kleinenPZ::SetDlgOptions()
{
	DlgOptions->m_Bitlength = RSA->GetBlockLength();
	DlgOptions->m_log2N     = RSA->GetLog2RSAModul();
	DlgOptions->RSA_Modul   = m_oeffentliche_parameter_pq;
	DlgOptions->ReInitBlockLength();
}


void RSA_mit_kleinenPZ::Segmentation( int mode )
{
	int blockSize    = DlgOptions->m_BlockLength;
	CString tmpStr;
	CString NumStr;

	int baseNumbers = GetBase();
	m_edit11 = ""; 
	m_edit13 = ""; 

	for (int i = 0; i<m_edit10.GetLength(); )
	{
		if ( mode == MODE_HEX_DUMP ) {
			int j=i;
			int cnt=0;
			while (j < m_edit10.GetLength() && cnt < 2*blockSize )
				if ( IsNumber( m_edit10[j++], BASE_HEX ) ) cnt++;
			tmpStr    = m_edit10.Mid(i, j-i);
			while ( cnt < 2*blockSize )
			{
				if ( cnt < 2*blockSize-1 && 0 == cnt % 2 ) tmpStr += ' ';
				tmpStr += '0';				
				cnt++;
			}
			m_edit13 += tmpStr;			
			i = j;
		}
		else
		{
			m_edit13 += m_edit10.Mid(i, blockSize);
			tmpStr    = m_edit10.Mid(i, blockSize);
			while ( tmpStr.GetLength() < blockSize ) { 
				tmpStr += ' '; m_edit13 += ' '; 
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
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i < m_edit10.GetLength() ) 
		{
			m_edit11 += " # ";
			m_edit13 += " # ";
		}
	}
}

void RSA_mit_kleinenPZ::OnRadio2() 
{
	UpdateData(TRUE);
	RequestForInput(TRUE);
	UpdateData(FALSE);
}

void RSA_mit_kleinenPZ::OnRadio1() 
{
	UpdateData(TRUE);
	RequestForInput(TRUE);
	UpdateData(FALSE);
}



BOOL RSA_mit_kleinenPZ::ReSegmentation( int mode )
{
	int blockSize   = DlgOptions->m_BlockLength;
	int baseNumbers = GetBase();

	m_edit11 = "";
	m_edit12 = "";
	BOOL flag = TRUE, hexDumpFlag = FALSE;
	int i1, i2;
	i1 = i2 = 0;
	CString tmp1;
	CString hexDump1 = "";
    CString hexDump2 = "";
	// *************  Hier noch richtige groesse finden ....
	char _tmp2[512]; 

	while (i1 < m_edit13.GetLength() && (m_edit13[i1] == ' ' || m_edit13[i1] == '#') ) i1++;
	while ( i1 < m_edit13.GetLength() )
	{
		i2 = m_edit13.Find(" ", i1);
		if (i2 < 0) 
		{
			if ( i1 < m_edit13.GetLength() ) i2 = m_edit13.GetLength();
			else break;
		}
		tmp1 = m_edit13.Mid(i1, i2-i1);
		switch ( mode ) {
			case MODE_ASCII: 
				if ( !(blockSize ==  decode( tmp1, _tmp2, blockSize, baseNumbers, (DlgOptions->m_codingMethod == 1), NULL )) )
					flag = FALSE;
				break;
			case MODE_ALPHABET:
				if ( !(blockSize ==  decode( tmp1, _tmp2, blockSize, baseNumbers, 
					                         (DlgOptions->m_codingMethod == 1), DlgOptions->m_alphabet )) )
					flag = FALSE;
				break;
			case MODE_DLG_OF_SISTERS:
				ModRepr ( tmp1, DlgOptions->m_alphabet.GetLength(), baseNumbers, -1 ); 
				if ( !(blockSize ==  decode( tmp1, _tmp2, blockSize, baseNumbers, FALSE, DlgOptions->m_alphabet )) )
					flag = FALSE;
				break;
		}
		if ( flag )
		{
			if ( mode == MODE_ASCII )
			{
				for ( int i=0; i<blockSize; i++ ) if ( !IsPrint(_tmp2[i]) )
					hexDumpFlag = TRUE;
				dataToHexDump( _tmp2, blockSize, tmp1 );
				hexDump1 += tmp1; 
				hexDump2 += tmp1;
			}
			m_edit11 += _tmp2;
			m_edit12 += _tmp2;
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_MSG_ENCRYPTION_NOTEXT,pc_str,STR_LAENGE_STRING_TABLE);
			m_edit11  = pc_str; 
			m_edit12  = "";
			m_Header2 = "";
			m_Header3 = "";
			break;
		}
		
		while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
		i1 = i2;
		if ( i1 < m_edit13.GetLength() ) {
			if ( mode == MODE_ASCII ) hexDump1 += " # ";
			m_edit11 += " # ";
		}
	}
	if ( mode == MODE_ASCII && hexDumpFlag )
	{
		m_edit11 = hexDump1;
		m_edit12 = hexDump2;
	}
	return flag;
}


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
// Behandlungsroutinen für Nachrichten CMyRSADemoEdit 

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
			// *** Check the Pasted String if it is a stream of numbers
			{
				CString CheckNumber = P;
				if ( IsNumberStream(CheckNumber, 16, "0") )
				{
					P = CheckNumber;
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
				CString CheckNumber = P;
				if ( IsNumberStream(CheckNumber, 16, "0" ) )
				{
					P = CheckNumber;
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

void CMyRSADemoEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen


	long curp = GetSel();
	if ( nChar == 22 && nFlags == 47 )
	{
		OnMyPaste();
	}
	else

	{
		CEdit::OnChar(nChar,nRepCnt,nFlags);
	}
}




