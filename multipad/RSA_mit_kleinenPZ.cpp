// RSA_mit_kleinenPZ.cpp: Implementierungsdatei
//
#include "stdafx.h"
#include "Afx.h"
#include "multipad.h"
#include "DlgRSAwithSmallPrimesOptions.h"
#include "RSA_mit_kleinenPZ.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RSA_mit_kleinenPZ 
void RSA_mit_kleinenPZ::SetHeadLine(CString &mHeader, int IDS_STRING_ID, int base)
{
	char line[256];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	if ( base ) sprintf( line, pc_str, base );
	else		sprintf( line, pc_str );
	mHeader = line;
}

void Message( int IDS_STRING_ID, int No = 0 )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID, pc_str,STR_LAENGE_STRING_TABLE);
	if ( 0 != No )
	{
		char line[256];
		sprintf( line, pc_str, No );
		AfxMessageBox (line);
	}
	else
	{
		AfxMessageBox (pc_str);
	}
}

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
	//}}AFX_DATA_INIT

	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	m_Header2 = _T("");
	m_Header3 = _T("");

	DlgOptions   = new CDlgRSAwithSmallPrimesOptions();
	DlgRSAPrimes = new DlgPrimesGenerator();
	RSA          = new TutorialRSA;
}


void RSA_mit_kleinenPZ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RSA_mit_kleinenPZ)
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


RSA_mit_kleinenPZ::~RSA_mit_kleinenPZ()
{
	delete DlgOptions;
	delete DlgRSAPrimes;
	delete RSA;
}

int RSA_mit_kleinenPZ::GetBase()
{
	int baseNumbers = 10;

	switch ( DlgOptions->m_numberBasis ) {
	case 0: 
		baseNumbers = 10;
		break;
	case 1: 
		baseNumbers = 2;
		break;
	case 2: 
		baseNumbers = 8;
		break;
	case 3: 
		baseNumbers = 16;
		break;
	}

	return baseNumbers;
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten RSA_mit_kleinenPZ 
void RSA_mit_kleinenPZ::OnButtonPzGenerieren() 
{
	UpdateData(true);
	
	DlgRSAPrimes->DoModal();
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
		m_ButtonDecrypt.EnableWindow(true);
		m_ButtonEncrypt.EnableWindow(true);
		m_ButtonOptionen.EnableWindow(true);
		DlgOptions->ReInitBlockLength( RSA->GetBlockLength() );
	}
	else
	{
		m_ButtonDecrypt.EnableWindow(false);
		m_ButtonEncrypt.EnableWindow(false);
		m_ButtonOptionen.EnableWindow(false);
	}
	m_edit10  = "";
	m_edit11  = "";
	m_edit12  = "";
	m_edit13  = "";
	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	m_Header2 = "";
	m_Header3 = "";
	m_Header4 = "";
	UpdateData(false);
}


void RSA_mit_kleinenPZ::OnParameterAktualisieren() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(true);
	if ( RSA->InitParameter( m_eingabe_p, m_eingabe_q ) )
	{
		if (RSA->SetPublicKey( m_oeffentliche_schluessel_e ) )
		{
			RSA->SetPrivateKey();
			RSA->GetParameter( m_oeffentliche_parameter_pq, m_geheime_parameter, 
							   m_oeffentliche_schluessel_e, m_geheime_schluessel_d );
		}
		else
		{
			Message(IDS_STRING_RSATUT_WRONG_PUBLICKEY);
			m_geheime_schluessel_d = "";
		}
	}
	else
	{
		Message( IDS_STRING_RSATUT_NOPRIMES );
		m_geheime_schluessel_d = "";
	}
	if ( RSA->IsInitialized() )
	{
		m_ButtonDecrypt.EnableWindow(true);
		m_ButtonEncrypt.EnableWindow(true);
		m_ButtonOptionen.EnableWindow(true);
		DlgOptions->ReInitBlockLength( RSA->GetBlockLength() );
	}
	else
	{
		m_ButtonDecrypt.EnableWindow(false);
		m_ButtonEncrypt.EnableWindow(false);
		m_ButtonOptionen.EnableWindow(false);
	}
	m_edit10  = "";
	m_edit11  = "";
	m_edit12  = "";
	m_edit13  = "";
	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	m_Header2 = "";
	m_Header3 = "";
	m_Header4 = "";
	UpdateData(false);		
}

// Primzahlen erzeugen:
void RSA_mit_kleinenPZ::OnUpdateEdit10() 
{
	UpdateData(true);
	m_edit11 = "";
	m_edit12 = "";
	m_edit13  = "";
	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	m_Header2 = "";
	m_Header3 = "";
	m_Header4 = "";
/*
	if (DlgOptions->m_TextOptions)
	{
		for (int i=0 ;i<m_edit10.GetLength(); i++)
		{
			for (int j=0; j<DlgOptions->m_alphabet.GetLength(); j++)
			{
				if (m_edit10[i] == DlgOptions->m_alphabet[j]) break;
			}
			if (j >= DlgOptions->m_alphabet.GetLength() ) 
				m_edit10.Delete(i);
		}
	}
*/
	UpdateData(false);
}

void RSA_mit_kleinenPZ::OnOptionen() 
{
	UpdateData(TRUE);
	DlgOptions->m_Bitlength = RSA->GetBlockLength();
	DlgOptions->m_log2N = RSA->GetLog2RSAModul();
	if ( DlgOptions->m_BlockLength < 1 ) DlgOptions->m_BlockLength = 1;
	if ( IDOK == DlgOptions->DoModal() )	
	{
		m_edit10  = "";
		m_edit11  = "";
		m_edit12  = "";
		m_edit13  = "";
		SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
		m_Header2 = "";
		m_Header3 = "";
		m_Header4 = "";
	}
	SetHeadLine( m_Header1, IDS_STRING_RSA_TUTORIAL_INPUT, GetBase() );
	UpdateData(FALSE);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void RSA_mit_kleinenPZ::OnButtonVerschluesseln() 
{
	theApp.DoWaitCursor(1);
	UpdateData(FALSE);
	if ( !(RSA->CheckInput(m_edit10, GetBase())) )
	{
		if ( !DlgOptions->m_RSAVariant )
		{
			if ( !DlgOptions->m_TextOptions )
			{
				EncryptASCII();
			}
			else
			{
				for (int i=0 ;i<m_edit10.GetLength();)
				{
					for (int j=0; j<DlgOptions->m_alphabet.GetLength(); j++)
					{
						if (m_edit10[i] == DlgOptions->m_alphabet[j]) break;
					}
					if (j >= DlgOptions->m_alphabet.GetLength() ) 
						m_edit10.Delete(i);
					else
						i++;
				}
				EncryptAlphabet();
			}
			SetHeadLine( m_Header1, IDS_STRING_RSATUT_INPUTPLAINTEXT );
			SetHeadLine( m_Header4, IDS_STRING_RSA_TUT_TEXTSEGMENTATION );
			SetHeadLine( m_Header2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
			SetHeadLine( m_Header3, IDS_STRING_RSA_TUTORIAL_ENCRYPTION );
		}
		else
		{
			for (int i=0 ;i<m_edit10.GetLength();)
			{
				for (int j=0; j<DlgOptions->m_alphabet.GetLength(); j++)
				{
					if (m_edit10[i] == DlgOptions->m_alphabet[j]) break;
				}
				if (j >= DlgOptions->m_alphabet.GetLength() ) 
					m_edit10.Delete(i);
				else
					i++;
			}
			EncryptDialogueOfSisters();
			SetHeadLine( m_Header1, IDS_STRING_RSATUT_INPUTPLAINTEXT );
			SetHeadLine( m_Header4, IDS_STRING_RSA_TUT_TEXTSEGMENTATION );
			SetHeadLine( m_Header2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
			SetHeadLine( m_Header3, IDS_STRING_RSA_TUTORIAL_ENCRYPTION );
		}
	}
	else
	{
		EncryptNumbers();
		SetHeadLine( m_Header1, IDS_STRING_RSATUT_PLAINTEXTNUMBERS, GetBase() );
		SetHeadLine( m_Header4, IDS_STRING_RSA_TUTORIAL_ENCRYPTION );
		SetHeadLine( m_Header2, IDS_STRING_RSA_OUTPUT_TEXTSEGMENTATION );
		SetHeadLine( m_Header3, IDS_RSA_MKPZ_CIPHERTEXT );
	}
	UpdateData(FALSE);
	theApp.DoWaitCursor(0);
}


void RSA_mit_kleinenPZ::OnButtonEntschluesseln() 
{
	theApp.DoWaitCursor(1);
	UpdateData(FALSE);
	if ( !(RSA->CheckInput(m_edit10, GetBase())) )
	{
		if ( !DlgOptions->m_RSAVariant )
		{
			if ( !DlgOptions->m_TextOptions )
			{
				DecryptASCII();
			}
			else
			{
				for (int i=0 ;i<m_edit10.GetLength();)
				{
					for (int j=0; j<DlgOptions->m_alphabet.GetLength(); j++)
					{
						if (m_edit10[i] == DlgOptions->m_alphabet[j]) break;
					}
					if (j >= DlgOptions->m_alphabet.GetLength() ) 
						m_edit10.Delete(i);
					else
						i++;
				}
				DecryptAlphabet();
			}
			SetHeadLine( m_Header1, IDS_STRING_RSATUT_INPUTPLAINTEXT );
			SetHeadLine( m_Header4, IDS_STRING_RSA_TUT_TEXTSEGMENTATION );
			SetHeadLine( m_Header2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
			SetHeadLine( m_Header3, IDS_STRING_RSA_TUTORIAL_DECRYPTION );
		}
		else
		{
			for (int i=0 ;i<m_edit10.GetLength();)
			{
				for (int j=0; j<DlgOptions->m_alphabet.GetLength(); j++)
				{
					if (m_edit10[i] == DlgOptions->m_alphabet[j]) break;
				}
				if (j >= DlgOptions->m_alphabet.GetLength() ) 
					m_edit10.Delete(i);
				else
					i++;
			}
			DecryptDialogueOfSisters();
			SetHeadLine( m_Header1, IDS_STRING_RSATUT_INPUTPLAINTEXT );
			SetHeadLine( m_Header4, IDS_STRING_RSA_TUT_TEXTSEGMENTATION );
			SetHeadLine( m_Header2, IDS_STRING_RSA_TUTORIAL_CODING, GetBase() );
			SetHeadLine( m_Header3, IDS_STRING_RSA_TUTORIAL_DECRYPTION );
		}
	}
	else
	{
		DecryptNumbers();
		SetHeadLine( m_Header1, IDS_STRING_RSATUT_CIPHERTEXTNUMBERS, GetBase() );
		SetHeadLine( m_Header4, IDS_STRING_RSA_TUTORIAL_DECRYPTION );
		SetHeadLine( m_Header2, IDS_STRING_RSA_OUTPUT_TEXTSEGMENTATION );
		SetHeadLine( m_Header3, IDS_RSA_MKPZ_PLAINTEXT );
	}
	UpdateData(FALSE);
	theApp.DoWaitCursor(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void RSA_mit_kleinenPZ::EncryptASCII()
{
	int blockSize    = DlgOptions->m_BlockLength;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

	int baseNumbers = GetBase();
	m_edit11 = ""; CString NumStr;
	m_edit13 = ""; 
	
	for (int i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		m_edit13 += m_edit10.Mid(i, blockSize);
		CharToNumStr(p_str+i, NumStr, blockSize, baseNumbers, 256);
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) 
		{
			m_edit11 += " # ";
			m_edit13 += " # ";
		}
	}
	RSA->Encrypt( m_edit11, m_edit12, baseNumbers );
}

void RSA_mit_kleinenPZ::DecryptASCII()
{
	int blockSize    = DlgOptions->m_BlockLength;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

	int baseNumbers = GetBase();
	m_edit11 = ""; CString NumStr;
	m_edit13 = ""; 
	
	for (int i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		m_edit13 += m_edit10.Mid(i, blockSize);
		CharToNumStr(p_str+i, NumStr, blockSize, baseNumbers, 256);
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) 
		{
			m_edit13 += " # ";
			m_edit11 += " # ";
		}
	}
	RSA->Decrypt( m_edit11, m_edit12, baseNumbers );
}


void RSA_mit_kleinenPZ::EncryptAlphabet()
{
	int blockSize = DlgOptions->m_BlockLength;
	CString tmpStr;
	CString NumStr;

	int baseNumbers = GetBase();
	m_edit11 = ""; 
	m_edit13 = ""; 
	
	for (int i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		m_edit13 += m_edit10.Mid(i, blockSize);
		tmpStr    = m_edit10.Mid(i, blockSize);
		while ( tmpStr.GetLength() < blockSize ) { tmpStr += ' '; m_edit13 += ' '; }
		AlphabetToNumStr(tmpStr, NumStr, DlgOptions->m_alphabet, baseNumbers, (DlgOptions->m_codingMethod == 1) );
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) 
		{
			m_edit11 += " # ";
			m_edit13 += " # ";
		}
	}
	RSA->Encrypt( m_edit11, m_edit12, baseNumbers );
}

void RSA_mit_kleinenPZ::DecryptAlphabet()
{
	int blockSize = DlgOptions->m_BlockLength;
	CString tmpStr;
	CString NumStr;

	int baseNumbers = GetBase();
	m_edit11 = ""; 
	m_edit13 = ""; 
	
	for (int i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		tmpStr    = m_edit10.Mid(i, blockSize);
		m_edit13 += m_edit10.Mid(i, blockSize);
		while ( tmpStr.GetLength() < blockSize ) { tmpStr += ' '; m_edit13 += ' '; }
		AlphabetToNumStr(tmpStr, NumStr, DlgOptions->m_alphabet, baseNumbers, (DlgOptions->m_codingMethod == 1) );
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) 
		{
			m_edit11 += " # ";
			m_edit13 += " # ";
		}
	}
	RSA->Decrypt( m_edit11, m_edit12, baseNumbers );
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void RSA_mit_kleinenPZ::EncryptDialogueOfSisters()
{
	int blockSize    = DlgOptions->m_BlockLength;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

	int i;
	for (i=0; i<m_edit10.GetLength(); )
	{
		for (int j=0; j<DlgOptions->m_alphabet.GetLength(); j++)
			if ( m_edit10[i] == DlgOptions->m_alphabet[j] ) break;
		if ( j>=DlgOptions->m_alphabet.GetLength() ) 
		{
			m_edit10.Delete(i);
		}
		else
			i++;
	}

	int baseNumbers = GetBase();
	m_edit11 = ""; CString NumStr;
	m_edit13 = "";
	for (i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		m_edit13 += m_edit10.Mid(i, blockSize);
		AlphabetToNumStr(p_str+i, NumStr, blockSize, DlgOptions->m_alphabet, baseNumbers ); 
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) 
		{
			m_edit11 += " # ";
			m_edit13 += " # ";
		}
	}
	RSA->EncryptDialogueOfSisters( m_edit11, m_edit12, DlgOptions->m_alphabet, baseNumbers );
}

void RSA_mit_kleinenPZ::DecryptDialogueOfSisters()
{
	int blockSize    = DlgOptions->m_BlockLength;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

	int i;
	for (i=0; i<m_edit10.GetLength(); )
	{
		for (int j=0; j<DlgOptions->m_alphabet.GetLength(); j++)
			if ( m_edit10[i] == DlgOptions->m_alphabet[j] ) break;
		if ( j>=DlgOptions->m_alphabet.GetLength() ) 
		{
			m_edit10.Delete(i);
		}
		else
			i++;
	}

	int baseNumbers = GetBase();
	m_edit11 = ""; CString NumStr;
	m_edit13 = "";
	for (i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		m_edit13 += m_edit10.Mid(i, blockSize);
		AlphabetToNumStr(p_str+i, NumStr, blockSize, DlgOptions->m_alphabet, baseNumbers ); 
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) 
		{
			m_edit11 += " # ";
			m_edit13 += " # ";
		}
	}
	RSA->DecryptDialogueOfSisters( m_edit11, m_edit12, DlgOptions->m_alphabet, baseNumbers );
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void RSA_mit_kleinenPZ::EncryptNumbers()
{
	int blockSize    = DlgOptions->m_BlockLength;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

	m_edit11 = ""; 
	m_edit12 = "";
	m_edit13 = "";
	int baseNumbers = GetBase();
	
	RSA->Encrypt( m_edit10, m_edit13, baseNumbers );

	if ( !DlgOptions->m_RSAVariant )
	{
		int i1, i2;
		i1 = i2 = 0;
		CString tmp1, tmp2;
		while (i1 < m_edit13.GetLength() && (m_edit13[i1] == ' ' || m_edit13[i1] == '#') ) i1++;
				
		if ( !DlgOptions->m_TextOptions )
		{
			while ( i1 < m_edit13.GetLength() )
			{
				i2 = m_edit13.Find(" ", i1);
				if (i2 < 0) 
				{
					if ( i1 < m_edit13.GetLength() ) i2 = m_edit13.GetLength();
					else break;
				}
				tmp1 = m_edit13.Mid(i1, i2-i1);
				CStringToASCII( tmp1, tmp2, baseNumbers );
				m_edit11 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				m_edit12 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
				i1 = i2;
				if ( i1 < m_edit13.GetLength() ) m_edit11 += " # ";
			}
		}
		else
		{
			while ( i1 < m_edit13.GetLength() )
			{
				i2 = m_edit13.Find(" ", i1);
				if (i2 < 0) 
				{
					if ( i1 < m_edit13.GetLength() ) i2 = m_edit13.GetLength();
					else break;
				}
				tmp1 = m_edit13.Mid(i1, i2-i1);
				CStringToAlphabet( tmp1, tmp2, DlgOptions->m_alphabet, DlgOptions->m_BlockLength, baseNumbers, (DlgOptions->m_codingMethod == 1) );
				m_edit11 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				m_edit12 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
				i1 = i2;
				if ( i1 < m_edit13.GetLength() ) m_edit11 += " # ";
			}

		}
	}
	else
	{
		int i1, i2;
		i1 = i2 = 0;
		CString tmp1, tmp2;
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
			CStringToAlphabet( tmp1, tmp2, DlgOptions->m_alphabet, baseNumbers );
			m_edit11 += tmp2.GetBuffer( tmp2.GetLength()+1 );
			m_edit12 += tmp2.GetBuffer( tmp2.GetLength()+1 );
			while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
			i1 = i2;
			if ( i1 < m_edit13.GetLength() ) m_edit11 += " # ";
		}
	}

}

void RSA_mit_kleinenPZ::DecryptNumbers()
{
	int blockSize    = DlgOptions->m_BlockLength;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

	m_edit11 = ""; 
	m_edit12 = "";
	m_edit13 = "";
	int baseNumbers = GetBase();
	
	RSA->Decrypt( m_edit10, m_edit13, baseNumbers );

	if ( !DlgOptions->m_RSAVariant )
	{
		int i1, i2;
		i1 = i2 = 0;
		CString tmp1, tmp2;
		while (i1 < m_edit13.GetLength() && (m_edit13[i1] == ' ' || m_edit13[i1] == '#') ) i1++;

		if ( !DlgOptions->m_TextOptions )
		{				
			while ( i1 < m_edit13.GetLength() )
			{
				i2 = m_edit13.Find(" ", i1);
				if (i2 < 0) 
				{
					if ( i1 < m_edit13.GetLength() ) i2 = m_edit13.GetLength();
					else break;
				}
				tmp1 = m_edit13.Mid(i1, i2-i1);
				CStringToASCII( tmp1, tmp2, baseNumbers );
				m_edit11 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				m_edit12 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
				i1 = i2;
				if ( i1 < m_edit13.GetLength() ) m_edit11 += " # ";
			}
		}
		else
		{
			while ( i1 < m_edit13.GetLength() )
			{
				i2 = m_edit13.Find(" ", i1);
				if (i2 < 0) 
				{
					if ( i1 < m_edit13.GetLength() ) i2 = m_edit13.GetLength();
					else break;
				}
				tmp1 = m_edit13.Mid(i1, i2-i1);
				CStringToAlphabet( tmp1, tmp2, DlgOptions->m_alphabet, DlgOptions->m_BlockLength, baseNumbers, (DlgOptions->m_codingMethod == 1) );
				m_edit11 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				m_edit12 += tmp2.GetBuffer( tmp2.GetLength()+1 );
				while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
				i1 = i2;
				if ( i1 < m_edit13.GetLength() ) m_edit11 += " # ";
			}
		}
	}
	else
	{
		int i1, i2;
		i1 = i2 = 0;
		CString tmp1, tmp2;
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
			CStringToAlphabet( tmp1, tmp2, DlgOptions->m_alphabet, baseNumbers );
			m_edit11 += tmp2.GetBuffer( tmp2.GetLength()+1 );
			m_edit12 += tmp2.GetBuffer( tmp2.GetLength()+1 );
			while ((i2 < m_edit13.GetLength()) && (m_edit13[i2] == ' ' || m_edit13[i2] == '#')) i2++;
			i1 = i2;
			if ( i1 < m_edit13.GetLength() ) m_edit11 += " # ";
		}

	}

}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void RSA_mit_kleinenPZ::OnEndDialog() 
{
	CDialog::OnCancel();
}

BOOL RSA_mit_kleinenPZ::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ButtonDecrypt.EnableWindow(false);
	m_ButtonEncrypt.EnableWindow(false);
	m_ButtonOptionen.EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void RSA_mit_kleinenPZ::OnUpdatePrimeP() 
{
	UpdateData(true);
	UpdateData(false);
}

void RSA_mit_kleinenPZ::OnUpdatePrimeQ() 
{
	UpdateData(true);
	UpdateData(false);
}

void RSA_mit_kleinenPZ::OnUpdatePublicKeyE() 
{
	UpdateData(true);
	UpdateData(false);
}
