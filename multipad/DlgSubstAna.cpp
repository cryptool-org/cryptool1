//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgSubstAna.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgSubstAna.h"
#include "fileutil.h"
#include "crypt.h"

extern char *Eingabedatei;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSubstAna 


CDlgSubstAna::CDlgSubstAna(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSubstAna::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSubstAna)
	m_radio1 = 0;
	m_check1 = FALSE;
	m_check2 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSubstAna::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSubstAna)
	DDX_Control(pDX, IDC_CHECK2, m_control2);
	DDX_Control(pDX, IDC_CHECK1, m_control1);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSubstAna, CDialog)
	//{{AFX_MSG_MAP(CDlgSubstAna)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSubstAna 


BOOL CDlgSubstAna::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Default-Einstellung ist englischer Klartext mit reiner Pattern Suche
	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO2);
	m_control2.EnableWindow(FALSE);	
	return TRUE;  
}

void CDlgSubstAna::OnCheck2() 
{
	// Wenn der Knopf "erweiterte Analyse" gewählt wird:
	// Diese Option schließt die Option "'e' als häufigstes Zeichen logisch ein, so daß 
	// diese Option automatsich auch angewählt wird.
	// Ferner muß ausgeschlossen werden, daß der Benutzer eine erweiterte Analyse für
	// englischen Klartext gewählt hat, da das derzeit vom Programm noch nicht unterstützt
	// wird.
	UpdateData(TRUE);
	m_check1=true;
	UpdateData(FALSE);	
}

void CDlgSubstAna::OnCheck1() 
{
	// Wenn die Option "'e' als häufigstes Zeichen" geändert wird, muß die Option
	// "erweiterte Analyse" automatisch abgeschaltet werden, damit es nicht vorkommt,
	// daß die zweite ohne die erste Option ausgewählt wurde
	UpdateData(TRUE);
	if ( false == m_check1 )
		m_check2=false;
	UpdateData(FALSE);
}

void CDlgSubstAna::OnRadio1() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	UpdateData();
	m_control1.EnableWindow();
	m_control2.EnableWindow();
	UpdateData(FALSE);
}

void CDlgSubstAna::OnRadio2() 
{
	// Wird englischer Klartext gewählt, so muß die Option "erweiterte Analyse" abgeschaltet werden
	UpdateData();
	m_control1.EnableWindow();
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgSubstAna::OnRadio3() 
{
	UpdateData();
	m_check1 = false;
	m_control1.EnableWindow(FALSE);
	m_check2 = false;
	m_control2.EnableWindow(FALSE);
	UpdateData(FALSE);
}
