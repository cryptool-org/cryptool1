// DlgRandParameter_x2_mod_N.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRandParameter_x2_mod_N.h"
#include "CryptologyUsingMiracl.h"
#include "crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandParameter_x2_mod_N 


DlgRandParameter_x2_mod_N::DlgRandParameter_x2_mod_N(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRandParameter_x2_mod_N::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRandParameter_x2_mod_N)
	m_EditModul_N = _T("");
	//}}AFX_DATA_INIT
}


void DlgRandParameter_x2_mod_N::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRandParameter_x2_mod_N)
	DDX_Control(pDX, IDC_EDIT1, m_Control_Edit_Modul_N);
	DDX_Text(pDX, IDC_EDIT1, m_EditModul_N);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRandParameter_x2_mod_N, CDialog)
	//{{AFX_MSG_MAP(DlgRandParameter_x2_mod_N)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgRandParameter_x2_mod_N 

void DlgRandParameter_x2_mod_N::SetModul(CString &NStr)
{
	m_EditModul_N = NStr;
}

CString DlgRandParameter_x2_mod_N::GetModul()
{
	return m_EditModul_N;
}

void DlgRandParameter_x2_mod_N::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	BOOL NumberIsOK;
	int     ndx;
	UpdateData(TRUE);
	{ 
		CString upnStr;
		NumberIsOK = EvalFormula(m_EditModul_N, ndx);
	}
	UpdateData(FALSE);
	if ( NumberIsOK )
	{
		CDialog::OnOK();
	}
	else
	{
		// ********* Fehlermeldung
		if (ndx == -1)
		{
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			m_Control_Edit_Modul_N.SetSel(0,-1);
			m_Control_Edit_Modul_N.SetFocus();
		}
		else
		{
			Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
			m_Control_Edit_Modul_N.SetSel(ndx-1,-1);
			m_Control_Edit_Modul_N.SetFocus();
		}
	}
}
