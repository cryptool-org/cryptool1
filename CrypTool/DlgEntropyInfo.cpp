// DlgEntropyInfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgEntropyInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgEntropyInfo 


CDlgEntropyInfo::CDlgEntropyInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEntropyInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEntropyInfo)
	m_alphabet_info = _T("");
	m_entropy_info = _T("");
	//}}AFX_DATA_INIT
}


void CDlgEntropyInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEntropyInfo)
	DDX_Control(pDX, IDC_ENTROPY_INFO, m_ctrl_entropy_info);
	DDX_Control(pDX, IDC_ALPHABET_INFO, m_ctrl_alphabet_info);
	DDX_Text(pDX, IDC_ALPHABET_INFO, m_alphabet_info);
	DDX_Text(pDX, IDC_ENTROPY_INFO, m_entropy_info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEntropyInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgEntropyInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgEntropyInfo 

BOOL CDlgEntropyInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char line[1024];

	LOGFONT logFont;
	CFont   m_font;
	logFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_font.CreateFontIndirect( &logFont ); // Font initialisieren
	m_ctrl_entropy_info.SetFont(&m_font);

	UpdateData();
	if ( i_countAlphabet < 256 )
	{
		LoadString(AfxGetInstanceHandle(),IDS_ENTROPY_ALPHABET_INFO,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str, i_characters, i_countAlphabet);
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_BINARY_ENTROPY_ALPHABET_INFO,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str, i_characters);
	}
	m_alphabet_info = CString(line);

	LoadString(AfxGetInstanceHandle(),IDS_ENTROPY_INFO,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line, pc_str, d_entropy, d_maxEntropy);
	m_entropy_info = CString(line);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
