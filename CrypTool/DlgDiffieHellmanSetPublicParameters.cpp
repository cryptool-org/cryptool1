// DlgDiffieHellmanSetPublicParameters.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanSetPublicParameters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanSetPublicParameters 


CDlgDiffieHellmanSetPublicParameters::CDlgDiffieHellmanSetPublicParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanSetPublicParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanSetPublicParameters)
	m_HeadingText = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanSetPublicParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanSetPublicParameters)
	DDX_Control(pDX, IDC_HEADING, m_HeadingControl);
	DDX_Text(pDX, IDC_HEADING, m_HeadingText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanSetPublicParameters, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanSetPublicParameters)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanSetPublicParameters 

BOOL CDlgDiffieHellmanSetPublicParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadString(AfxGetInstanceHandle(), IDS_DH_STEP1, pc_str, STR_LAENGE_STRING_TABLE);
	this->m_HeadingText = pc_str;

	LOGFONT logFont;
	CFont   m_font;
	
	logFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_font.CreateFontIndirect( &logFont ); // Font initialisieren
	
	m_HeadingControl.SetFont(&m_font);

	UpdateData(false);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
