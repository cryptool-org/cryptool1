// DlgRandomParameterLCG.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgLCGRandomParameter.h"
#include "IntegerArithmetic.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgLCGRandomParameter 


CDlgLCGRandomParameter::CDlgLCGRandomParameter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLCGRandomParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLCGRandomParameter)
	m_LinParam_a = _T("23");
	m_LinParam_b = _T("0");
	m_LinParam_N = _T("100000001");
	//}}AFX_DATA_INIT
}


void CDlgLCGRandomParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLCGRandomParameter)
	DDX_Control(pDX, IDC_EDIT3, m_control_LinParam_N);
	DDX_Control(pDX, IDC_EDIT2, m_control_LinParam_b);
	DDX_Control(pDX, IDC_EDIT1, m_control_LinParam_a);
	DDX_Text(pDX, IDC_EDIT1, m_LinParam_a);
	DDX_Text(pDX, IDC_EDIT2, m_LinParam_b);
	DDX_Text(pDX, IDC_EDIT3, m_LinParam_N);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLCGRandomParameter, CDialog)
	//{{AFX_MSG_MAP(CDlgLCGRandomParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgLCGRandomParameter 

void CDlgLCGRandomParameter::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	BOOL Modul_N_IsOK;
	BOOL Multiplikator_a_IsOK;
	BOOL Inkrement_b_IsOK;
	int     ndx_a;
	int     ndx_b;
	int     ndx_N;
	UpdateData(TRUE);
	{ 
		CString upnStr;
		Modul_N_IsOK = EvalFormula(m_LinParam_N, ndx_N);
		Multiplikator_a_IsOK = EvalFormula(m_LinParam_a, ndx_a);
		Inkrement_b_IsOK = EvalFormula(m_LinParam_b, ndx_b);
	}
	UpdateData(FALSE);
	if ( Modul_N_IsOK  && Multiplikator_a_IsOK && Inkrement_b_IsOK)
	{
		CDialog::OnOK();
	}
	else
	{
		// ********* Fehlermeldung
		if ( !Modul_N_IsOK )
		{
			if (ndx_N == -1)
			{
				Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
				m_control_LinParam_N.SetSel(0,-1);
				m_control_LinParam_N.SetFocus();
			}
			else
			{
				Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
				m_control_LinParam_N.SetSel(ndx_N-1,-1);
				m_control_LinParam_N.SetFocus();
			}
		}
		else if ( !Multiplikator_a_IsOK )
		{
			if (ndx_a == -1)
			{
				Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
				m_control_LinParam_a.SetSel(0,-1);
				m_control_LinParam_a.SetFocus();
			}
			else
			{
				Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
				m_control_LinParam_a.SetSel(ndx_a-1,-1);
				m_control_LinParam_a.SetFocus();
			}
		}
		else
		{
			if (ndx_b == -1)
			{
				Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
				m_control_LinParam_b.SetSel(0,-1);
				m_control_LinParam_b.SetFocus();
			}
			else
			{
				Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
				m_control_LinParam_b.SetSel(ndx_b-1,-1);
				m_control_LinParam_b.SetFocus();
			}
		}
	}
	
}
