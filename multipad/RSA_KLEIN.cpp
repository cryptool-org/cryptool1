// RSA_KLEIN.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "RSA_KLEIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RSA_KLEIN 


RSA_KLEIN::RSA_KLEIN(CWnd* pParent /*=NULL*/)
	: CDialog(RSA_KLEIN::IDD, pParent)
{
	//{{AFX_DATA_INIT(RSA_KLEIN)
	m_eingabe_p = _T("");
	m_eingabe_q = _T("");
	m_oeffentliche_parameter_pq = _T("");
	m_geheime_parameter = _T("");
	m_oeffentliche_schluessel_e = _T("3");
	m_oeffentliche_schluessel_d = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	//}}AFX_DATA_INIT
}


void RSA_KLEIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RSA_KLEIN)
	DDX_Text(pDX, IDC_EDIT1, m_eingabe_p);
	DDX_Text(pDX, IDC_EDIT2, m_eingabe_q);
	DDX_Text(pDX, IDC_EDIT3, m_oeffentliche_parameter_pq);
	DDX_Text(pDX, IDC_EDIT4, m_geheime_parameter);
	DDX_Text(pDX, IDC_EDIT5, m_oeffentliche_schluessel_e);
	DDX_Text(pDX, IDC_EDIT6, m_oeffentliche_schluessel_d);
	DDX_Text(pDX, IDC_EDIT7, m_edit7);
	DDX_Text(pDX, IDC_EDIT8, m_edit8);
	DDX_Text(pDX, IDC_EDIT9, m_edit9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RSA_KLEIN, CDialog)
	//{{AFX_MSG_MAP(RSA_KLEIN)
		// HINWEIS: Der Klassen-Assistent fügt hier Zuordnungsmakros für Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten RSA_KLEIN 
