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
	//}}AFX_DATA_INIT

	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_PLAINTEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_Header1 = pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_CODING_PLAINTEXT,pc_str,STR_LAENGE_STRING_TABLE);
	m_Header2 = pc_str;
	LoadString(AfxGetInstanceHandle(),IDS_RSA_MKPZ_ENCRYPTION,pc_str,STR_LAENGE_STRING_TABLE);
	m_Header3 = pc_str;

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
	//}}AFX_DATA_MAP
}
//******************************************************************************

BEGIN_MESSAGE_MAP(RSA_mit_kleinenPZ, CDialog)
	//{{AFX_MSG_MAP(RSA_mit_kleinenPZ)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_BN_CLICKED(IDC_BUTTON_PZ_GENERIEREN, OnButtonPzGenerieren)
	ON_EN_UPDATE(IDC_EDIT10, OnUpdateEdit10)
	ON_EN_UPDATE(IDC_EDIT11, OnUpdateEdit11)
	ON_EN_UPDATE(IDC_EDIT12, OnUpdateEdit12)
	ON_BN_CLICKED(IDC_OPTIONEN, OnOptionen)
	ON_BN_CLICKED(IDC_BUTTON2, OnParameterAktualisieren)
	ON_BN_CLICKED(IDC_BUTTON_VERSCHLUESSELN, OnButtonVerschluesseln)
	ON_BN_CLICKED(IDC_BUTTON_ENTSCHLUESSELN, OnButtonEntschluesseln)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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
			m_geheime_schluessel_d = "";
		}
	}
	UpdateData(false);		
}



void RSA_mit_kleinenPZ::Verschluesseln() 
{
	UpdateData(true);

	UpdateData(false);	
}


void RSA_mit_kleinenPZ::OnUpdateEdit1() 
{
	UpdateData(true);
	int sels,sele;
	m_control_p.GetSel(sels,sele);

	UpdateData(false);
	m_control_p.SetSel(sels,sele);
	
}

void RSA_mit_kleinenPZ::OnUpdateEdit2() 
{
	UpdateData(true);
	int sels,sele;
	m_control_q.GetSel(sels,sele);

	UpdateData(false);
	m_control_q.SetSel(sels,sele);
	
}

// Primzahlen erzeugen:



void RSA_mit_kleinenPZ::Entschluesseln() 
{
	UpdateData(true);

	UpdateData(false);	
}

void RSA_mit_kleinenPZ::OnUpdateEdit10() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit10.GetSel(sels,sele);

	UpdateData(false);
	m_control_edit10.SetSel(sels,sele);
	
}

void RSA_mit_kleinenPZ::OnUpdateEdit11() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit11.GetSel(sels,sele);

	UpdateData(false);
	m_control_edit11.SetSel(sels,sele);
	
}

void RSA_mit_kleinenPZ::OnUpdateEdit12() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit12.GetSel(sels,sele);

	UpdateData(false);
	m_control_edit12.SetSel(sels,sele);
}

void RSA_mit_kleinenPZ::OnOptionen() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	DlgOptions->DoModal();	
}

void RSA_mit_kleinenPZ::OnButtonVerschluesseln() 
{
	UpdateData(FALSE);

	EncryptASCII();

	UpdateData(FALSE);
}

void RSA_mit_kleinenPZ::OnButtonEntschluesseln() 
{
	UpdateData(FALSE);

	DecryptASCII();

	UpdateData(FALSE);
}


void RSA_mit_kleinenPZ::EncryptASCII()
{
	int baseNumbers;
	int blockSize    = RSA->GetBlockLength() / 8;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

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

	m_edit11 = ""; CString NumStr;
	for (int i = 0; i<m_edit10.GetLength(); i+=blockSize )
	{
		CharToNumStr(p_str+i, NumStr, blockSize, baseNumbers, 256);
		m_edit11 += NumStr.GetBuffer( NumStr.GetLength()+1);
		if ( i+blockSize < m_edit10.GetLength() ) m_edit11 += " # ";
	}

	RSA->Encrypt( m_edit11, m_edit12, baseNumbers );
	
}

void RSA_mit_kleinenPZ::DecryptASCII()
{
	int baseNumbers;
	int blockSize    = RSA->GetBlockLength() / 8;
	char *p_str = m_edit10.GetBuffer( m_edit10.GetLength() );

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
	m_edit11 = ""; 
	m_edit12 = "";
	
	RSA->Decrypt( m_edit10, m_edit11, baseNumbers );

	{
		int i1, i2;
		i1 = i2 = 0;
		CString tmp1, tmp2;
		while (i1 < m_edit11.GetLength() && (m_edit11[i1] == ' ' || m_edit11[i1] == '#') ) i1++;
			
		while ( i1 < m_edit11.GetLength() )
		{
			i2 = m_edit11.Find(" ", i1);
			if (i2 < 0) 
			{
				if ( i1 < m_edit11.GetLength() ) i2 = m_edit11.GetLength();
				else break;
			}
			tmp1 = m_edit11.Mid(i1, i2-i1);
			CStringToASCII( tmp1, tmp2, baseNumbers );
			m_edit12 += tmp2.GetBuffer( tmp2.GetLength()+1 );
			while ((i2 < m_edit11.GetLength()) && (m_edit11[i2] == ' ' || m_edit11[i2] == '#')) i2++;
			i1 = i2;
		}
	}

}
