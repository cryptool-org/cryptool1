// DlgCertTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgCertTutorial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCertTutorial 


CDlgCertTutorial::CDlgCertTutorial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCertTutorial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCertTutorial)
	m_sFirstName = _T("");
	m_sHash = _T("");
	m_sHashEnc = _T("");
	m_sName = _T("");
	m_sModN = _T("");
	m_sKeyPublic = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCertTutorial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCertTutorial)
	DDX_Text(pDX, IDC_EDIT_CERT_FIRSTNAME, m_sFirstName);
	DDX_Text(pDX, IDC_EDIT_CERT_HASH, m_sHash);
	DDX_Text(pDX, IDC_EDIT_CERT_HASH_ENC, m_sHashEnc);
	DDX_Text(pDX, IDC_EDIT_CERT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_RSA_MODUL_N, m_sModN);
	DDX_Text(pDX, IDC_EDIT_RSA_KEY_PUBLIC, m_sKeyPublic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCertTutorial, CDialog)
	//{{AFX_MSG_MAP(CDlgCertTutorial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCertTutorial 

BOOL CDlgCertTutorial::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	ASSERT(m_Cert); // Zertifikat muß initialisiert sein -> InitRSA

	UpdateData(TRUE);

	CString sBuffer;
	m_Cert->GetName(m_sName, m_sFirstName); // Zertifikatsdaten holen
	if(m_Cert->IsInitialized())
	{
		// Schlüsseldaten holen:
		m_Cert->GetParameter(m_sModN, sBuffer, m_sKeyPublic, sBuffer); 
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgCertTutorial::InitRSA(CTutorialCert* Cert)
{
	m_Cert = Cert;
}
