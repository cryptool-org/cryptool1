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

void Message( int IDS_STRING_ID, int No = 0 )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	if ( 0 != No )
	{
		char line[IDS_STRINGLENGTH];
		sprintf( line, pc_str, No );
		AfxMessageBox (line);
	}
	else
	{
		AfxMessageBox (pc_str);
	}
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
	m_oeffentliche_schluessel_e = _T("3");
	m_geheime_schluessel_d = _T("");
	m_edit10 = _T("");
	m_edit11 = _T("");
	m_edit12 = _T("");
	m_Header1 = _T("");
	m_Header2 = _T("");
	m_Header3 = _T("");
	m_Header4 = _T("");
	m_edit13 = _T("");
	//m_control_p.SetFocus();
	//}}AFX_DATA_INIT

	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	m_Header2 = _T("");
	m_Header3 = _T("");

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
		m_eingabe_p = DlgRSAPrimes->m_edit5;
		m_eingabe_q = DlgRSAPrimes->m_edit6;
		RSA->InitParameter( m_eingabe_p, m_eingabe_q );
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
			RequestForInput();
		}
		else
		{
			EnableEncryption(false);
			m_ButtonOptionen.EnableWindow(false);
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
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	UpdateData(true);
	char line [IDS_STRINGLENGTH];
	int RSAInitError;
	if ( 0 == (RSAInitError = RSA->InitParameter( m_eingabe_p, m_eingabe_q )) )
	{
		if (RSA->SetPublicKey( m_oeffentliche_schluessel_e ) )
		{
			RSA->SetPrivateKey();
			RSA->GetParameter( m_oeffentliche_parameter_pq, m_geheime_parameter, 
					   m_oeffentliche_schluessel_e, m_geheime_schluessel_d );
		}
		else
		{
			// Falls e nicht coprime zu phi(N) ist, wird man aufgefordert eine andere Zahl f�r e zu w�hlen
			Message(IDS_STRING_RSATUT_WRONG_PUBLICKEY);
			m_geheime_schluessel_d = "";
			m_control_edit5.SetFocus();
			return;
		}
	}
	else 
	{
		// In diesem Fall ist mindestens eine der Zahlen p oder q keine Primzahl.
		if ( ERR_P_NOT_PRIME == RSAInitError )
		{
			Message(IDS_STRING_RSADEMO_P_NOT_PRIME);
			m_control_p.SetFocus();
			return;
		}
		if ( ERR_Q_NOT_PRIME == RSAInitError )
		{
			Message(IDS_STRING_RSADEMO_Q_NOT_PRIME);
			m_control_q.SetFocus();
			m_geheime_schluessel_d = "";
			return;
		}
		if ( ERR_P_EQUALS_Q == RSAInitError )
		{
			Message(IDS_STRING_ERR_PRIME_ARE_EQUAL);
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
				LoadString(AfxGetInstanceHandle(),IDS_STRING_RSADEMO_MODUL_KLEIN, pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line, pc_str, DlgOptions->Anzahl_Zeichen, m_oeffentliche_parameter_pq );
				AfxMessageBox(line);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING_RSADEMO_MODUL_KLEIN, pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line, pc_str, DlgOptions->Anzahl_Zeichen, m_oeffentliche_parameter_pq );
		AfxMessageBox(line);
		EnableEncryption(false);
		m_ButtonOptionen.EnableWindow(true);		
	}	
	RequestForInput();
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
			char line[256];
			LoadString(AfxGetInstanceHandle(),IDS_STRING_RSADEMO_MODUL_KLEIN, pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line, pc_str, DlgOptions->Anzahl_Zeichen, m_oeffentliche_parameter_pq );
			AfxMessageBox(line);
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
	UpdateData(FALSE);
	if ( !DlgOptions->m_RSAVariant && !DlgOptions->m_TextOptions && IsHexDump( m_edit10 ) )
	{
		Segmentation( MODE_HEX_DUMP );
		RSA->Encrypt( m_edit11, m_edit12, GetBase() );
	}
	else if ( !IsNumberStream( m_edit10, GetBase(), m_oeffentliche_parameter_pq, SPLIT_NUMBERS_VSFLOOR ) )
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
				SkipWS();
				Segmentation( MODE_ALPHABET );
			}
			RSA->Encrypt( m_edit11, m_edit12, GetBase() );
		}
		else
		{
			SkipWS();
			HeadingEncryption( ENCRYPT_TEXT );		
			Segmentation( MODE_DLG_OF_SISTERS );
			RSA->EncryptDialogueOfSisters( m_edit11, m_edit12, DlgOptions->m_alphabet, GetBase() );
		}
	}
	else
	{
		HeadingEncryption( ENCRYPT_NUMBERS );
		EncryptNumbers();
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
	UpdateData(FALSE);
	if ( !DlgOptions->m_RSAVariant && !DlgOptions->m_TextOptions && IsHexDump( m_edit10 ) )
	{
		Segmentation( MODE_HEX_DUMP );
		RSA->Decrypt( m_edit11, m_edit12, GetBase() );
	}
	else if ( !IsNumberStream( m_edit10, GetBase(), m_oeffentliche_parameter_pq, SPLIT_NUMBERS_VSFLOOR ) )
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
				SkipWS();
				Segmentation( MODE_ALPHABET );
			}
			RSA->Decrypt( m_edit11, m_edit12, GetBase() );
		}
		else
		{
			HeadingDecryption( DECRYPT_TEXT );		
			SkipWS();
			Segmentation( MODE_DLG_OF_SISTERS );
			RSA->DecryptDialogueOfSisters( m_edit11, m_edit12, DlgOptions->m_alphabet, GetBase() );
		}
	}
	else
	{
		HeadingDecryption( DECRYPT_NUMBERS );
		DecryptNumbers();
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
	return FALSE;  // return TRUE unless you set the focus to a control
 	               // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
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
		m_edit10 = _T("");
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
		m_edit10 = _T("");
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
	if ( clearInput ) 
		m_edit10  = "";
	m_edit11  = "";
	m_edit12  = "";
	m_edit13  = "";
	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	m_Header2 = "";
	m_Header3 = "";
	m_Header4 = "";
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


void RSA_mit_kleinenPZ::SkipWS()
{
	for (int i=0 ;i<m_edit10.GetLength();)
	{
		if ( !isCharOf(m_edit10[i], DlgOptions->m_alphabet.GetBuffer(0)) )
			m_edit10.Delete(i);
		else
			i++;
	}
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

	for (int i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		m_edit13 += m_edit10.Mid(i, blockSize);
		tmpStr    = m_edit10.Mid(i, blockSize);
		while ( tmpStr.GetLength() < blockSize ) { 
			tmpStr += ' '; m_edit13 += ' '; 
		}
		switch ( mode ) {
			case MODE_HEX_DUMP:
				break;
			case MODE_ASCII: 
				break;
			case MODE_ALPHABET:
				break;
			case MODE_DLG_OF_SISTERS:
				break;
		}
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) 
		{
			m_edit11 += " # ";
			m_edit13 += " # ";
		}
	}
}


BOOL RSA_mit_kleinenPZ::ReSegmentation( int mode )
{
	int blockSize   = DlgOptions->m_BlockLength;
	int baseNumbers = GetBase();

	m_edit11 = "";
	m_edit12 = "";
	BOOL flag = TRUE;
	int i1, i2;
	i1 = i2 = 0;
	CString tmp1, tmp2;
	char _tmp2[512];
	char _tmp3[512];
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
				break;
			case MODE_ALPHABET:
				break;
			case MODE_DLG_OF_SISTERS:
				break;
		}
		if ( !flag )
		{
			LoadString(AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_MSG_ENCRYPTION_NOTEXT,pc_str,STR_LAENGE_STRING_TABLE);
			m_edit11  = pc_str; 
			m_edit12  = "";
			m_Header2 = "";
			m_Header3 = "";
			break;
		}
		int outStrLength = 0;
		m_edit11 += _tmp2;
		m_edit12 += _tmp2;
		while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
		i1 = i2;
		if ( i1 < m_edit13.GetLength() ) m_edit11 += " # ";
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
// Behandlungsroutinen f�r Nachrichten CMyRSADemoEdit 

void CMyRSADemoEdit::OnMyPaste() 
{
	OpenClipboard();
	HANDLE hndl;
	char *globBuff, *dataBuff;
	long  dataLen;

	if ( mode == MODE_ASCII )
	{
		if( hndl = ::GetClipboardData(theApp.m_HexFormat)) 
		{
			globBuff = (char *) GlobalLock(hndl);
			dataLen = ((long *) globBuff)[0];
			dataBuff = globBuff+sizeof(long);
			char *tmpIn  = new char[dataLen+1];
			char *tmpOut = new char[4*dataLen+1];
			memcpy( tmpIn, dataBuff, dataLen);
			int OutLength = 0;
			// encodeASCII( tmpOut, OutLength, 4*dataLen, tmpIn,  0, dataLen, NULL );
			tmpOut[OutLength] = '\0';
			CString P = tmpOut;
			delete []tmpIn;
			delete []tmpOut;

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
			char *tmpOut = new char[4*dataLen+1];
			memcpy( tmpIn, dataBuff, dataLen);
			tmpIn[dataLen] = '\0';
			int OutLength = 0;
			// encodeASCII( tmpOut, OutLength, 4*dataLen, tmpIn,  0, dataLen, NULL );
			tmpOut[OutLength] = '\0';
			CString P = tmpOut;
			delete []tmpIn;
			delete []tmpOut;

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
	// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen und/oder Standard aufrufen

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
