//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// TextEingabeHillAngriff.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "TextEingabeHillAngriff.h"
#include "hill.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CTextEingabeHillAngriff 


CTextEingabeHillAngriff::CTextEingabeHillAngriff(CWnd* pParent /*=NULL*/)
	: CDialog(CTextEingabeHillAngriff::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextEingabeHillAngriff)
	m_EingabeFeld = _T("");
	m_Klartext = 0;
	//}}AFX_DATA_INIT
}


void CTextEingabeHillAngriff::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextEingabeHillAngriff)
	DDX_Control(pDX, IDC_DIM_VON, m_DimensionVon);
	DDX_Control(pDX, IDC_DIM_BIS, m_DimensionBis);
	DDX_Text(pDX, IDC_EDIT1, m_EingabeFeld);
	DDX_Radio(pDX, IDC_RADIO1, m_Klartext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextEingabeHillAngriff, CDialog)
	//{{AFX_MSG_MAP(CTextEingabeHillAngriff)
	ON_CBN_SELCHANGE(IDC_DIM_VON, OnSelchangeDimVon)
	ON_CBN_SELCHANGE(IDC_DIM_BIS, OnSelchangeDimBis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CTextEingabeHillAngriff 

BOOL CTextEingabeHillAngriff::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen

	// Combo-Boxen fuer Bereich der Schluesselsuche initialisieren
	for (int i=1; i<=HILL_MAX_DIM_GROSS; i++)
	{
		CString cs;
		cs.Format("%d", i);
		m_DimensionVon.AddString(cs);
		m_DimensionBis.AddString(cs);
	}

	// Standartmaessig alle Dimensionen beruecksichtigen
	m_DimensionVon.SetCurSel(0);
	m_DimensionBis.SetCurSel(HILL_MAX_DIM_GROSS-1);
	von = 1;
	bis = HILL_MAX_DIM_GROSS;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CTextEingabeHillAngriff::OnSelchangeDimVon() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	von = m_DimensionVon.GetCurSel() + 1;
	if (von > bis)
	{
		bis = von;
		m_DimensionBis.SetCurSel(bis-1);
	}
}

void CTextEingabeHillAngriff::OnSelchangeDimBis() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	
	bis = m_DimensionBis.GetCurSel() + 1;
	if (bis < von)
	{
		von = bis;
		m_DimensionVon.SetCurSel(von-1);
	}
} 
