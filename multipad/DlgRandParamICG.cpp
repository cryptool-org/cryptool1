// DlgRandParamICG.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRandParamICG.h"
#include "CryptologyUsingMiracl.h"
#include "DlgPrimesGenerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandParamICG 


DlgRandParamICG::DlgRandParamICG(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRandParamICG::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRandParamICG)
	m_Param_a = _T("22211");
	m_Param_b = _T("11926380");
	m_Param_N = _T("2147483053");
	m_PrimLang = 128;
	//}}AFX_DATA_INIT
}


void DlgRandParamICG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRandParamICG)
	DDX_Control(pDX, IDC_STATIC_GPA, m_StaticGPA);
	DDX_Control(pDX, IDC_EDIT4, m_PrimLang_Ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_Param_NCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_Param_bCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_Param_aCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_Param_a);
	DDX_Text(pDX, IDC_EDIT2, m_Param_b);
	DDX_Text(pDX, IDC_EDIT3, m_Param_N);
	DDX_Text(pDX, IDC_EDIT4, m_PrimLang);
	DDV_MinMaxUInt(pDX, m_PrimLang, 0, 256);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRandParamICG, CDialog)
	//{{AFX_MSG_MAP(DlgRandParamICG)
	ON_BN_CLICKED(IDC_STATIC_GPA, OnStaticGp_a)
	ON_BN_CLICKED(IDC_PRIMBUTTON, OnPrimbutton)
	ON_BN_CLICKED(IDC_STATIC_GPC, OnStaticGpc)
	ON_BN_CLICKED(IDC_STATIC_GPP, OnStaticGpp)
	ON_BN_CLICKED(IDC_STATIC_GPL, OnStaticGpl)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgRandParamICG 


void DlgRandParamICG::OnStaticGp_a() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Param_aCtrl.SetFocus();
}

void DlgRandParamICG::OnStaticGpc() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	m_Param_bCtrl.SetFocus();
	UpdateData(FALSE);
}

void DlgRandParamICG::OnStaticGpp() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_Param_NCtrl.SetFocus();
}

void DlgRandParamICG::OnStaticGpl() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	m_PrimLang_Ctrl.SetFocus();
}

void DlgRandParamICG::OnPrimbutton() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData(TRUE);
	// m_Param_N = CString("0");
	GeneratePrimes P;
	DlgPrimesGenerator Gen;
	if(8 >= m_PrimLang) m_PrimLang = 128;
	char tmpStr[12];
	sprintf(tmpStr, "%i", m_PrimLang-1);
	CString lowerBound = CString("2^") + CString(tmpStr);
	sprintf(tmpStr, "%i", m_PrimLang);
	CString upperBound = CString("2^") + CString(tmpStr);
	P.SetLimits( lowerBound, upperBound );
	theApp.DoWaitCursor(0);				// aktiviert die Sanduhr (statt des Mauszeigers)
		Gen.GetRandomPrime( m_Param_N, P );
	theApp.DoWaitCursor(-1);			// deaktiviert die Sanduhr
	UpdateData(FALSE);
}


void DlgRandParamICG::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nFlags & (1<<13)) {
		switch(nChar) {
		case('p'):
		case('P'): m_Param_NCtrl.SetFocus();
			return;
		case('a'):
		case('A'): m_Param_bCtrl.SetFocus();
			return;
		}
	}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void DlgRandParamICG::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	BOOL Modul_N_IsOK;
	BOOL Multiplikator_a_IsOK;
	BOOL Inkrement_b_IsOK;
	char line[256];
	int     ndx_a;
	int     ndx_b;
	int     ndx_N;
	UpdateData(TRUE);
	{ 
		CString upnStr;
		Modul_N_IsOK = EvalFormula(m_Param_N, ndx_N);
		Multiplikator_a_IsOK = EvalFormula(m_Param_a, ndx_a);
		Inkrement_b_IsOK = EvalFormula(m_Param_b, ndx_b);
	}
	UpdateData(FALSE);
	if ( Modul_N_IsOK  && Multiplikator_a_IsOK && Inkrement_b_IsOK)
	{
		GeneratePrimes P;
		P.SetP(Get_N());
		BOOL test=FALSE;
		test = P.MillerRabinTest(100);
		test = P.SolvayStrassenTest(100);
		test = P.FermatTest(100);

		if ( !test ) 
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MODUL_NOT_PRIME,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);
			m_Param_NCtrl.SetSel(0,-1);
			m_Param_NCtrl.SetFocus();
		}
		else
		{
			CDialog::OnOK();
		}
	}
	else
	{
		// ********* Fehlermeldung
		if ( !Modul_N_IsOK )
		{
			if (ndx_N == -1)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_BIG_NUMBER,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				m_Param_NCtrl.SetSel(0,-1);
				m_Param_NCtrl.SetFocus();
			}
			else
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_INPUT_FALSE,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				m_Param_NCtrl.SetSel(ndx_N-1,-1);
				m_Param_NCtrl.SetFocus();
			}
		}
		else if ( !Multiplikator_a_IsOK )
		{
			if (ndx_a == -1)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_BIG_NUMBER,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				m_Param_aCtrl.SetSel(0,-1);
				m_Param_aCtrl.SetFocus();
			}
			else
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_INPUT_FALSE,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				m_Param_aCtrl.SetSel(ndx_a-1,-1);
				m_Param_aCtrl.SetFocus();
			}
		}
		else
		{
			if (ndx_b == -1)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_BIG_NUMBER,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				m_Param_bCtrl.SetSel(0,-1);
				m_Param_bCtrl.SetFocus();
			}
			else
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_INPUT_FALSE,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
				m_Param_bCtrl.SetSel(ndx_b-1,-1);
				m_Param_bCtrl.SetFocus();
			}
		}
	}
}
