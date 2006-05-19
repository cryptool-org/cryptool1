// propPage1.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "propPage1.h"
#include "ZahlenHaiOptionen.h"
#include ".\proppage1.h"


// propPage1-Dialogfeld

IMPLEMENT_DYNAMIC(propPage1, CPropertyPage)
propPage1::propPage1()
	: CPropertyPage(propPage1::IDD)
{
}

propPage1::~propPage1()
{
}

void propPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, tabctrl);
}


BEGIN_MESSAGE_MAP(propPage1, CPropertyPage)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// propPage1-Meldungshandler

void propPage1::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	*pResult = 0;
}

BOOL propPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  hier zusätzliche Initialisierung hinzufügen.
	//tabctrl.InsertItem(CDialog *dlg,"Hallo", IDD_DIALOG1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
