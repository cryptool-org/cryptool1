// DlgDiffieHellmanSecretInput.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanSecretInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSecretInput 


CDlgDiffieHellmanSecretInput::CDlgDiffieHellmanSecretInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSecretInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanSecretInput)
	m_Secret = _T("");
	m_PartyHeader = _T("");
	//}}AFX_DATA_INIT
}

CDlgDiffieHellmanSecretInput::CDlgDiffieHellmanSecretInput( std::string party, Big& prime, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSecretInput::IDD, pParent)
{
	m_Party = party;
	m_Prime = prime;
	m_Secret = _T("");
}

void CDlgDiffieHellmanSecretInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanSecretInput)
	DDX_Control(pDX, IDC_SECRET, m_SecretControl);
	DDX_Text(pDX, IDC_SECRET, m_Secret);
	DDX_Text(pDX, IDC_PARTY, m_PartyHeader);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanSecretInput, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanSecretInput)
	ON_BN_CLICKED(IDC_GENERATE_SECRET, OnGenerateSecret)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgDiffieHellmanSecretInput 

void CDlgDiffieHellmanSecretInput::OnOK() 
{
	UpdateData(true);

	// Fehlermeldung ausgeben, wenn Geheimnis keine Dezimalzahl ist
	if(!IsDecimalNumber(m_Secret))
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_NON_DECIMAL_VALUE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_SecretControl.SetFocus();
		return;
	}

	Big S = (char*)(LPCTSTR)this->m_Secret;
	
	// Fehlermeldung ausgeben, wenn das Geheimnis gleich oder gr��er dem Primzahlmodul ist
	// oder wenn das Geheimnis kleiner oder gleich Eins ist.
	if(S >= this->m_Prime || S <= 1)
	{
		LoadString(AfxGetInstanceHandle(), IDS_DH_PP_SECRET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONSTOP);
		m_SecretControl.SetFocus();
		return;
	}

	CDialog::OnOK();
}

void CDlgDiffieHellmanSecretInput::OnGenerateSecret() 
{
	// "Das Geheimnis" (Big-Format)
	Big S;
	irand((unsigned)time(NULL));
	bigrand(this->m_Prime.getbig(), S.getbig());
	char *s = new char[512];
	s << S;
	this->m_Secret = s;
	delete s;
	UpdateData(false);
}

BOOL CDlgDiffieHellmanSecretInput::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Tempor�re Variablen
	CString temp1,temp2;

	// Name der DH-Partei dynamisch im Fenstertitel anzeigen
	temp1.LoadString(IDS_DH_SECRET_DIALOGUEHEADER);
	temp2.Format((LPCTSTR)temp1, (LPCTSTR)this->m_Party.c_str());
	this->SetWindowText((LPCTSTR)temp2);
	
	// Name der DH-Partei dynamisch im Dialog anzeigen
	temp1.LoadString(IDS_DH_SECRET_PARTYNAME);
	temp2.Format((LPCTSTR)temp1, (LPCTSTR)this->m_Party.c_str());
	this->m_PartyHeader = (LPCTSTR)temp2;

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}
