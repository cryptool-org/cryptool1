// DlgDiffieHellmanCreateSharedKey.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanCreateSharedKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanCreateSharedKey 


CDlgDiffieHellmanCreateSharedKey::CDlgDiffieHellmanCreateSharedKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanCreateSharedKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanCreateSharedKey)
	m_HeadingText = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanCreateSharedKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanCreateSharedKey)
	DDX_Control(pDX, IDC_HEADING, m_HeadingControl);
	DDX_Text(pDX, IDC_HEADING, m_HeadingText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanCreateSharedKey, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanCreateSharedKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDiffieHellmanCreateSharedKey 

BOOL CDlgDiffieHellmanCreateSharedKey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadString(AfxGetInstanceHandle(), IDS_DH_STEP3, pc_str, STR_LAENGE_STRING_TABLE);
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
