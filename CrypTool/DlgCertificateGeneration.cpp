// DlgCertTutorial.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCertificateGeneration.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgCertificateGeneration 


CDlgCertificateGeneration::CDlgCertificateGeneration(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCertificateGeneration::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCertificateGeneration)
	m_sDName = _T("");
	m_sFirstName = _T("");
	m_sKeyID = _T("");
	m_sName = _T("");
	m_sUserID = _T("");
	m_sBitLength = _T("");
	m_sPIN = _T("");
	m_sPINv = _T("");
	m_sKeyPublic = _T("");
	m_sModN = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCertificateGeneration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCertificateGeneration)
	DDX_Control(pDX, IDC_EDIT_CERT_NAME, m_CtrlName);
	DDX_Control(pDX, IDOK, m_CtrlOK);
	DDX_Text(pDX, IDC_EDIT_CERT_DNAME, m_sDName);
	DDX_Text(pDX, IDC_EDIT_CERT_FIRSTNAME, m_sFirstName);
	DDX_Text(pDX, IDC_EDIT_CERT_KEY_ID, m_sKeyID);
	DDX_Text(pDX, IDC_EDIT_CERT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_CERT_USER_ID, m_sUserID);
	DDX_Text(pDX, IDC_EDIT_RSA_BITLENGTH, m_sBitLength);
	DDX_Text(pDX, IDC_EDIT_CERT_PIN, m_sPIN);
	DDX_Text(pDX, IDC_EDIT_CERT_PIN_VERIFY, m_sPINv);
	DDX_Text(pDX, IDC_EDIT_RSA_KEY_PUBLIC, m_sKeyPublic);
	DDX_Text(pDX, IDC_EDIT_RSA_MODUL_N, m_sModN);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCertificateGeneration, CDialog)
	//{{AFX_MSG_MAP(CDlgCertificateGeneration)
	ON_EN_CHANGE(IDC_EDIT_CERT_NAME, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_CERT_FIRSTNAME, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_CERT_KEY_ID, OnChangeEdit)
	ON_BN_CLICKED(ID_PSE_IMPORT, OnPseImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgCertificateGeneration 


BOOL CDlgCertificateGeneration::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	ASSERT(m_Cert); // Zertifikat muß initialisiert sein -> InitRSA

	UpdateData(TRUE);
	
	m_Cert->GetName(m_sName, m_sFirstName, m_sKeyID); // Zertifikatsdaten holen
	if( !(m_sName.IsEmpty()&&m_sFirstName.IsEmpty()&&m_sKeyID.IsEmpty()) ) m_Cert->GetKeyId(m_sUserID, m_sDName);
	m_sPINv = m_sPIN = m_Cert->GetPIN();
	if(m_Cert->IsInitialized())
	{
		// Schlüsseldaten holen:
		CString sBuffer;
		m_Cert->GetParameter(m_sModN, sBuffer, m_sKeyPublic, sBuffer);
		m_sBitLength.Format(IDS_BIT, m_Cert->GetBitLength());
	}
	else m_CtrlOK.EnableWindow(FALSE);

	UpdateData(FALSE);
	
	m_CtrlName.SetFocus();
	return FALSE; // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgCertificateGeneration::InitRSA(CPSEDemo* Cert)
{
	m_Cert = Cert;
}

void CDlgCertificateGeneration::OnChangeEdit() 
{
	// TODO: Wenn dies ein RICHEDIT-Steuerelement ist, sendet das Steuerelement diese

	// Benachrichtigung nicht, bevor Sie nicht die Funktion CDialog::OnInitDialog()

	// überschreiben und CRichEditCrtl().SetEventMask() aufrufen, wobei

	// eine ODER-Operation mit dem Attribut ENM_CHANGE und der Maske erfolgt.
	UpdateData(TRUE);
	CString sName = m_sName;
	CString sFirstName = m_sFirstName;
	CString sKeyID	= m_sKeyID;	
	m_Cert->SetName(sName, sFirstName, sKeyID);
	m_Cert->SetTime();
	m_Cert->GetKeyId(m_sUserID, m_sDName); 
	UpdateData(FALSE);	
}

void CDlgCertificateGeneration::OnOK() 
{
	UpdateData(TRUE);

	if(m_sName.IsEmpty())
	{
		AfxMessageBox(IDS_NOTIFY_NAME);
		return;
	}
	if(m_sFirstName.IsEmpty())
	{
		AfxMessageBox(IDS_NOTIFY_NAME);
		return;
	}
	if(m_sPIN.IsEmpty())
	{
		AfxMessageBox(IDS_NOTIFY_PIN);
		return;
	}
	if(m_sPIN != m_sPINv)
	{
		AfxMessageBox(IDS_NOTIFY_PIN_V);
		return;
	}
	
	
	CDialog::OnOK();
}

void CDlgCertificateGeneration::OnPseImport() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Cert->AccessPSE_DLG();
}
