//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DialogCert.cpp: Implementierungsdatei
//
// Programmiert von Bartol Filipovic, 2000

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowCertificate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowCertificate 


CDlgShowCertificate::CDlgShowCertificate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowCertificate::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowCertificate)
	m_CertEdit = _T("");
	m_dummy = _T("");
	//}}AFX_DATA_INIT
	Cert = _T("");
}


CDlgShowCertificate::CDlgShowCertificate(CString CertIn, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowCertificate::IDD, pParent)
{
	Cert = CertIn;
}


void CDlgShowCertificate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowCertificate)
	DDX_Control(pDX, IDC_EDIT2, m_dummyCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_CertEditCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_CertEdit);
	DDX_Text(pDX, IDC_EDIT2, m_dummy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowCertificate, CDialog)
	//{{AFX_MSG_MAP(CDlgShowCertificate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgShowCertificate 

BOOL CDlgShowCertificate::OnInitDialog() 
{
	int i;
	CString tmp,tmp2;
	
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	tmp = Cert;

	LOGFONT LogFont;
	CFont *defaultFont = m_dummyCtrl.GetFont(); // this->GetFont() sollte auch funktionieren
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_CertEditCtrl.SetFont(&m_Font);

	while(!tmp.IsEmpty()) {
		i = tmp.Find('\r');
		if(i==-1) {
			m_CertEdit += (tmp+((CString)"\r\n"));
			break;
		}
		else {
			tmp2 = tmp.Mid(0,i);
			m_CertEdit += (tmp2+((CString)"\r\n"));
			tmp = tmp.Mid(i+2);
		}
	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
 

void CDlgShowCertificate::OnCancel() 
{
	// TODO: Zusätzlichen Bereinigungscode hier einfügen
	
	CDialog::OnCancel();
}

void CDlgShowCertificate::OnOK() 
{
	// TODO: Zusätzliche Prüfung hier einfügen
	
	CDialog::OnOK();
}
