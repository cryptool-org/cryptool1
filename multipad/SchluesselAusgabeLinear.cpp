// SchluesselAusgabeLinear.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "SchluesselAusgabeLinear.h"
#include "crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSchluesselAusgabeLinear 


CSchluesselAusgabeLinear::CSchluesselAusgabeLinear(CWnd* pParent /*=NULL*/)
	: CDialog(CSchluesselAusgabeLinear::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSchluesselAusgabeLinear)
	m_Key = _T("");
	//}}AFX_DATA_INIT
}


void CSchluesselAusgabeLinear::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchluesselAusgabeLinear)
	DDX_Control(pDX, IDC_EDIT1, m_CtrlKey);
	DDX_Text(pDX, IDC_EDIT1, m_Key);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchluesselAusgabeLinear, CDialog)
	//{{AFX_MSG_MAP(CSchluesselAusgabeLinear)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CSchluesselAusgabeLinear 


void CSchluesselAusgabeLinear::OnCopyKey() 
{
	//In der Zwischen Ablage kopieren
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	CopyKey(strTitle, m_Key); 
	m_CtrlKey.SetSel(0,-1); 
	m_CtrlKey.Copy();
	CDialog::OnOK();
}

BOOL CSchluesselAusgabeLinear::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (strTitle[0])
	{
		LoadString(AfxGetInstanceHandle(),IDS_METHOD_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		char keyMethodStr[128];
		sprintf( keyMethodStr, pc_str, strTitle );
		SetWindowText(keyMethodStr);
	}

	// TODO: Zus�tzliche Initialisierung hier einf�gen
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

int CSchluesselAusgabeLinear::DoModal() 
{
	// TODO: Speziellen Code hier einf�gen und/oder Basisklasse aufrufen
	return CDialog::DoModal();
}

