// DlgGenerateSavePrime.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DlgGenerateSavePrime.h"
#include "CrypToolApp.h"
#include "DialogeMessage.h"

#include <sstream>
#include <string>
#include "NTL/ZZ.h"

using namespace NTL;
// CDlgGenerateSavePrime-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgGenerateSavePrime, CDialog)

CDlgGenerateSavePrime::CDlgGenerateSavePrime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGenerateSavePrime::IDD, pParent)
	, m_Bitlength(256)
	, m_Prime(_T(""))
{

}

CDlgGenerateSavePrime::~CDlgGenerateSavePrime()
{
}

void CDlgGenerateSavePrime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ctrlTakePrime);
	DDX_Text(pDX, IDC_EDIT1, m_Bitlength);
	DDX_Text(pDX, IDC_EDIT2, m_Prime);
}


BEGIN_MESSAGE_MAP(CDlgGenerateSavePrime, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgGenerateSavePrime::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgGenerateSavePrime::OnBnClickedGeneratePrime)
END_MESSAGE_MAP()


BOOL CDlgGenerateSavePrime::OnInitDialog() 
{
	CDialog::OnInitDialog();	
 	m_ctrlTakePrime.EnableWindow(FALSE);

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CDlgGenerateSavePrime::generateGermainPrime()
{
	std::stringstream ss;
	std::string s_prime;

	SHOW_HOUR_GLASS
	ZZ zz_prime;
	GenGermainPrime(zz_prime, m_Bitlength);
	zz_prime <<= 1;
	zz_prime++;
	HIDE_HOUR_GLASS

	ss << zz_prime; ss >> s_prime;
	UpdateData(TRUE);
	m_Prime = s_prime.c_str();
	UpdateData(FALSE);
	return TRUE;
}



// CDlgGenerateSavePrime-Meldungshandler

void CDlgGenerateSavePrime::OnBnClickedOk()
{
	OnOK();
}

void CDlgGenerateSavePrime::OnBnClickedGeneratePrime()
{
	UpdateData(true);
	if ( m_Bitlength <= 1 )
	{
		Message(IDS_BL_ATLEAST2, MB_ICONINFORMATION);
		return;
	}
	if ( m_Bitlength > 16384 )
	{
		Message(IDS_BL_TOOLARGE, MB_ICONINFORMATION);
		return;
	}
	
	generateGermainPrime();
	m_ctrlTakePrime.EnableWindow();

	UpdateData(false);
}
