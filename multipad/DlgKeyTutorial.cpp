// DlgKeyTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgKeyTutorial.h"
#include "DlgPrimesGenerator.h"
#include "KeyRepository.h"
#include "CryptologyUsingMiracl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyTutorial 


CDlgKeyTutorial::CDlgKeyTutorial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyTutorial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgKeyTutorial)
	m_sPrime_p = _T("");
	m_sPrime_q = _T("");
	m_sKeyPublic = _T("2^16+1");
	m_sKeyPrivate = _T("");
	m_sModN = _T("");
	m_sPhiN = _T("");
	m_sCheckPrime = _T("");
	m_sCheckPublic = _T("");
	m_sBitLength = _T("");
	//}}AFX_DATA_INIT
}


void CDlgKeyTutorial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKeyTutorial)
	DDX_Control(pDX, IDC_EDIT_RSA_BITLENGTH, m_BitLengthCtrl);
	DDX_Control(pDX, IDC_CHECK_PRIME, m_CheckPrimeCtrl);
	DDX_Control(pDX, IDC_CHECK_PUBLIC, m_CheckPublicCtrl);
	DDX_Control(pDX, IDC_EDIT_RSA_KEY_PUBLIC, m_KeyPublicCtrl);
	DDX_Control(pDX, IDOK, m_ButtonOKCtrl);
	DDX_Text(pDX, IDC_EDIT_PRIME_P, m_sPrime_p);
	DDX_Text(pDX, IDC_EDIT_PRIME_Q, m_sPrime_q);
	DDX_Text(pDX, IDC_EDIT_RSA_KEY_PUBLIC, m_sKeyPublic);
	DDX_Text(pDX, IDC_EDIT_RSA_KEY_PRIVATE, m_sKeyPrivate);
	DDX_Text(pDX, IDC_EDIT_RSA_MODUL_N, m_sModN);
	DDX_Text(pDX, IDC_EDIT_RSA_PHI_N, m_sPhiN);
	DDX_Text(pDX, IDC_CHECK_PRIME, m_sCheckPrime);
	DDX_Text(pDX, IDC_CHECK_PUBLIC, m_sCheckPublic);
	DDX_Text(pDX, IDC_EDIT_RSA_BITLENGTH, m_sBitLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKeyTutorial, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyTutorial)
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDC_GENERATE_PRIME, OnGeneratePrime)
	ON_EN_UPDATE(IDC_EDIT_RSA_KEY_PUBLIC, OnUpdateParameter)
	ON_EN_UPDATE(IDC_EDIT_PRIME_P, OnUpdateParameter)
	ON_EN_UPDATE(IDC_EDIT_PRIME_Q, OnUpdateParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgKeyTutorial 

BOOL CDlgKeyTutorial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ASSERT(m_Cert); // Zertifikat mu� initialisiert sein -> InitRSA

	UpdateData(TRUE);	
	
	if(m_Cert->IsInitialized())
	{
		// Schl�sseldaten holen:
		m_Cert->GetParameter(m_sModN, m_sPhiN, m_sKeyPublic, m_sKeyPrivate); 
		m_Cert->GetPublicString( m_sKeyPublic );
		m_Cert->GetPrimes(m_sPrime_p, m_sPrime_q); // Primzahlen holen
		//m_Cert->GetName(m_sName, m_sFirstName); // Zertifikatsdaten holen
	}

	UpdateData(FALSE);

	// Bitmaps laden:
	VERIFY(m_bmpCheck.LoadBitmap(IDB_BITMAP3));
	VERIFY(m_bmpNoCheck.LoadBitmap(IDB_BITMAP4));

	OnUpdateParameter(); // Schl�ssel und Anzeige initialisieren
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgKeyTutorial::OnGeneratePrime() 
{
	DlgPrimesGenerator* PrimeDialog;
	PrimeDialog = new DlgPrimesGenerator(this);

	PrimeDialog->m_edit1 = "2^150";
	//PrimeDialog->m_edit3 = "2^150";
	PrimeDialog->m_edit2 = "2^151";
	//PrimeDialog->m_edit4 = "2^151";
	PrimeDialog->m_radio4 = 1;

	if(PrimeDialog->DoModal()==IDOK) // Primzahl Generierung
	{
		UpdateData(TRUE);
		m_sPrime_p = PrimeDialog->m_edit5;
		m_sPrime_q = PrimeDialog->m_edit6;
		UpdateData(FALSE);
	}

	delete PrimeDialog;

    OnUpdateParameter();	
}

void CDlgKeyTutorial::InitRSA(CTutorialCert* Cert)
{
	m_Cert = Cert;
}

/*****************************************************************************/
/*	�bernimmt die automatische Aktualisierung der Anzeigen des Dialogs/*
/*****************************************************************************/
void CDlgKeyTutorial::OnUpdateParameter() 
{
	UpdateData(TRUE);

	CString sKeyPublic = m_sKeyPublic; // Eingegebene Formel (z.B. 2^16+1) sichern.
	int		ePrime = m_Cert->InitParameter( m_sPrime_p, m_sPrime_q );
	BOOL	bIsEmpty = m_sPrime_p.IsEmpty() || m_sPrime_q.IsEmpty();
	int		iBitLength = m_Cert->GetBitLength();
	if(iBitLength) m_sBitLength.Format(IDS_BIT, iBitLength);
		else m_sBitLength.Empty();
	
	if( bIsEmpty )
	{
		m_CheckPrimeCtrl.ShowWindow( SW_HIDE );
		m_CheckPublicCtrl.ShowWindow( SW_HIDE );
		m_KeyPublicCtrl.EnableWindow(FALSE); // Eingabe f�r Public Key verhindern...
		m_sKeyPrivate.Empty();	// Private Key = ""
		m_sPhiN.Empty();		// Phi (N) = ""
		m_sModN.Empty();		// RSA-Modul N = ""
	}
	else
	{
		m_CheckPrimeCtrl.ShowWindow( SW_SHOW );
		if( ePrime )
		{
			m_CheckPublicCtrl.ShowWindow( SW_HIDE );
			m_KeyPublicCtrl.EnableWindow( FALSE ); // Eingabe f�r Public Key verhindern...
			m_sKeyPrivate.Empty();	// Private Key = ""
			m_sPhiN.Empty();		// Phi (N) = ""
			m_sModN.Empty();		// RSA-Modul N = ""
			if ( ePrime & ERR_P_LESS_THAN_TWO ) m_sCheckPrime.LoadString( IDS_PRIME_LESS_THAN_TWO_P );
			else if ( ePrime & ERR_Q_LESS_THAN_TWO ) m_sCheckPrime.LoadString( IDS_PRIME_LESS_THAN_TWO_Q );
			else if ( (ePrime & ERR_PQ_NOT_PRIME) == ERR_PQ_NOT_PRIME ) m_sCheckPrime.LoadString( IDS_PRIME_NO_CHECK_PQ );
			else if ( ePrime & ERR_P_NOT_PRIME ) m_sCheckPrime.LoadString( IDS_PRIME_NO_CHECK_P );
			else if ( ePrime & ERR_Q_NOT_PRIME ) m_sCheckPrime.LoadString( IDS_PRIME_NO_CHECK_Q );
			else if ( ePrime & ERR_P_EQUALS_Q ) m_sCheckPrime.LoadString( IDS_PRIME_P_EQUALS_Q );
			else if ( ePrime & ERR_MAX_BIT_LENGTH ) m_sCheckPrime.LoadString( IDS_PRIME_BIT_LENGTH );
			else ASSERT( FALSE );
		}
		else
		{
			m_sCheckPrime.LoadString( IDS_PRIME_CHECK ); // "p und q sind Primzahlen."		
			m_CheckPublicCtrl.ShowWindow( SW_SHOW ); // CheckPublic anzeigen.
			m_KeyPublicCtrl.EnableWindow( TRUE );	// Eingabe f�r Public Key erm�glichen...
			if ( m_Cert->SetPublicKey( m_sKeyPublic ) ) // Ist e teilerfremd zu phi (N)?
			{
				m_sCheckPublic.LoadString( IDS_PUBLIC_CHECK ); // "e ist teilerfremd zu phi (N) ."
				m_Cert->SetPrivateKey(); // Private Key ermitteln..
				m_Cert->GetParameter( m_sModN, m_sPhiN, sKeyPublic, m_sKeyPrivate ); // Parameter abfragen...
				// Schl�ssel kopieren:
				LoadString( AfxGetInstanceHandle(),IDS_CRYPT_RSADEMO_PARAMETER,pc_str,STR_LAENGE_STRING_TABLE );
				CopyKey ( pc_str, m_sPrime_p + ";" + m_sPrime_q + ";" + sKeyPublic );
			}
			else // Ist e teilerfremd zu phi (N)?
			{
				m_sCheckPublic.LoadString( IDS_PUBLIC_NO_CHECK ); // "e ist NICHT teilerfremd zu phi (N) !"
				m_Cert->GetParameter( m_sModN, m_sPhiN, sKeyPublic, m_sKeyPrivate ); // Parameter abfragen...
				m_sKeyPrivate.Empty(); // Private Key = ""
			}
		}
	}
	if ( m_Cert->IsInitialized() ) // Zertifikat initialisiert?
	{
		// Zertifikat INITIALISIERT!
		m_ButtonOKCtrl.EnableWindow(TRUE); // OK - Button einblenden
	}
	else
	{
		// Zertifikat NICHT INITIALISIERT!
		m_ButtonOKCtrl.EnableWindow(FALSE);	// OK - Button ausblenden
	}
	UpdateData(FALSE);
}

void CDlgKeyTutorial::OnOK() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);

	CDialog::OnOK();
}

