// DlgOptionsSignatureAttack.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgOptionsSignatureAttack.h"
#include "HashingOperations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsSignatureAttack 


CDlgOptionsSignatureAttack::CDlgOptionsSignatureAttack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsSignatureAttack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsSignatureAttack)
	m_hashalgorithm = 0;
	m_bitlength = _T("");
	m_mod_method = -1;
	m_att_method = -1;
	//}}AFX_DATA_INIT
}


void CDlgOptionsSignatureAttack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsSignatureAttack)
	DDX_Control(pDX, IDC_RADIO9, m_control_att_print);
	DDX_Control(pDX, IDC_RADIO10, m_control_att_unprint);
	DDX_Control(pDX, IDC_RADIO7, m_control_mod_method);
	DDX_Control(pDX, IDC_EDIT1, m_control_bitlength);
	DDX_Control(pDX, IDC_STATIC_SIG_ATT_BITLENGTH_RANGE, m_control_bitlength_range);
	DDX_Control(pDX, IDC_CHECK1, m_control_check1);
	DDX_Control(pDX, IDC_CHECK3, m_control_check3);
	DDX_Control(pDX, IDC_RADIO1, m_control_md2);
	DDX_Radio(pDX, IDC_RADIO1, m_hashalgorithm);
	DDX_Text(pDX, IDC_EDIT1, m_bitlength);
	DDV_MaxChars(pDX, m_bitlength, 4);
	DDX_Radio(pDX, IDC_RADIO7, m_mod_method);
	DDX_Radio(pDX, IDC_RADIO9, m_att_method);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsSignatureAttack, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsSignatureAttack)
	ON_BN_CLICKED(IDC_RADIO1, OnMD2)
	ON_BN_CLICKED(IDC_RADIO2, OnMD4)
	ON_BN_CLICKED(IDC_RADIO3, OnMD5)
	ON_BN_CLICKED(IDC_RADIO4, OnSHA)
	ON_BN_CLICKED(IDC_RADIO5, OnSHA_1)
	ON_BN_CLICKED(IDC_RADIO6, OnRIPEMD_160)
	ON_BN_CLICKED(IDC_BUTTON1, OnResetToDefault)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgOptionsSignatureAttack 

BOOL CDlgOptionsSignatureAttack::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_hashalgorithm = theApp.GetProfileInt("Settings", "SignatureAttackHashAlgorithmID", 0);
	if (m_hashalgorithm < 0 || m_hashalgorithm > 5)
	{
		m_hashalgorithm = 0;
	}
	SetTextBitlengthRange();

	m_bitlength = theApp.GetProfileString("Settings", "SignatureAttackSignificantBitLength", _OPT_SIG_ATT_STANDARD_BITLENGTH);
	
	m_mod_method = theApp.GetProfileInt("Settings", "SignatureAttackModificationMethod", 0);
	if (m_mod_method < 0 || m_mod_method > 1)
	{
		m_mod_method = 0;
	}

	m_control_check1.SetCheck(theApp.GetProfileInt("Settings", "SignatureAttackCheck1", 1));
	m_control_check3.SetCheck(theApp.GetProfileInt("Settings", "SignatureAttackCheck3", 1));

	m_att_method = theApp.GetProfileInt("Settings", "SignatureAttackAttMethod", 0);
	if (m_att_method < 0 || m_att_method > 1)
	{
		m_att_method = 0;
	}

	if (0 == m_mod_method)
	{
		m_control_check1.EnableWindow(TRUE);
		m_control_check3.EnableWindow(TRUE);
		m_control_att_print.EnableWindow(FALSE);
		m_control_att_unprint.EnableWindow(FALSE);
	}
	else if (1 == m_mod_method)
	{
		m_control_check1.EnableWindow(FALSE);
		m_control_check3.EnableWindow(FALSE);
		m_control_att_print.EnableWindow(TRUE);
		m_control_att_unprint.EnableWindow(TRUE);
	}
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgOptionsSignatureAttack::OnMD2() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 0;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnMD4() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 1;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnMD5() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 2;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnSHA() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 3;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnSHA_1() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 4;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnRIPEMD_160() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 5;
	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnOK() 
{
	UpdateData(TRUE);

	CString msg;
	int maxbit;
	HashingOperations HO(m_hashalgorithm);
	
	maxbit = HO.GetHashAlgorithmBitLength();

	if (atoi(m_bitlength) > maxbit || atoi(m_bitlength) < 1)
	{
		msg.Format(IDS_STRING_SIG_ATT_BAD_BITLENGTH, maxbit);
		MessageBox(msg, "CrypTool", MB_ICONEXCLAMATION | MB_APPLMODAL);
		m_control_bitlength.SetSel(0, -1);
		m_control_bitlength.SetFocus();
				
		return;
	}

	if (0 == m_mod_method && 1 != m_control_check1.GetCheck() && 1 != m_control_check3.GetCheck())
	{
		msg.Format(IDS_STRING_SIG_ATT_NO_CHECK);
		MessageBox(msg, "CrypTool", MB_ICONEXCLAMATION | MB_APPLMODAL);
		m_control_check1.SetCheck(1);

		return;
	}

	theApp.WriteProfileInt("Settings", "SignatureAttackHashAlgorithmID", m_hashalgorithm);	
	theApp.WriteProfileString("Settings", "SignatureAttackSignificantBitLength", m_bitlength);
	theApp.WriteProfileInt("Settings", "SignatureAttackModificationMethod", m_mod_method);
	theApp.WriteProfileInt("Settings", "SignatureAttackCheck1", m_control_check1.GetCheck());
	theApp.WriteProfileInt("Settings", "SignatureAttackCheck3", m_control_check3.GetCheck());
	theApp.WriteProfileInt("Settings", "SignatureAttackAttMethod", m_att_method);

	CDialog::OnOK();
}

void CDlgOptionsSignatureAttack::OnResetToDefault() 
{
	UpdateData(TRUE);

	m_hashalgorithm = 0;
	m_bitlength = _OPT_SIG_ATT_STANDARD_BITLENGTH;
	m_mod_method = 0;
	m_control_check1.SetCheck(1);
	m_control_check1.EnableWindow(TRUE);
	m_control_check3.SetCheck(0);
	m_control_check3.EnableWindow(TRUE);
	m_control_att_print.EnableWindow(FALSE);
	m_control_att_unprint.EnableWindow(FALSE);

	SetTextBitlengthRange();

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnUpdateEdit1() 
{
	UpdateData(TRUE);

	int ii;

	if (TRUE == m_bitlength.IsEmpty())
	{
		return;
	}

	for (ii = 0; ii < m_bitlength.GetLength(); ii ++)
	{
		if (m_bitlength.GetAt(ii) < '0' || m_bitlength.GetAt(ii) > '9')
		{
			m_bitlength.Delete(ii, 1);
		}
	}	

	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::SetTextBitlengthRange()
{
	CString msg;
	HashingOperations HO(m_hashalgorithm);
	if (0 != HO.GetErrorcode())
	{
		return;
	}

	msg.Format(IDS_STRING_SIG_ATT_BITLENGTH_RANGE, HO.GetHashAlgorithmBitLength());
	m_control_bitlength_range.SetWindowText(msg);
}

void CDlgOptionsSignatureAttack::OnRadio7() 
{
	m_mod_method = 0;
	
	m_control_check1.EnableWindow(TRUE);
	m_control_check3.EnableWindow(TRUE);
	m_control_att_print.EnableWindow(FALSE);
	m_control_att_unprint.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnRadio8() 
{
	m_mod_method = 1;

	m_control_check1.EnableWindow(FALSE);
	m_control_check3.EnableWindow(FALSE);
	m_control_att_print.EnableWindow(TRUE);
	m_control_att_unprint.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CDlgOptionsSignatureAttack::OnRadio9() 
{
	m_att_method = 0;
}

void CDlgOptionsSignatureAttack::OnRadio10() 
{
	m_att_method = 1;
}
