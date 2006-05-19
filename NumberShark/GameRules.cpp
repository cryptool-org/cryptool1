// GameRules.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "GameRules.h"
#include ".\gamerules.h"
#include <richedit.h>

// GameRules-Dialogfeld

IMPLEMENT_DYNAMIC(GameRules, CDialog)
GameRules::GameRules(CWnd* pParent /*=NULL*/)
	: CDialog(GameRules::IDD, pParent)
{
}

GameRules::~GameRules()
{
}

void GameRules::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, richEdit);
}

BEGIN_MESSAGE_MAP(GameRules, CDialog)
	
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


void GameRules::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnOK();
}

void GameRules::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	//Die Spielbeschreibung/Regeln werden in ein RichEdit Feld geschrieben.
	//Text kann jetzt herauskopiert werden
	CString rules;
	rules.LoadString(IDS_RULES);
	CString rules2;
	rules2.LoadString(IDS_RULES_2);
	richEdit.SetWindowText(rules + rules2);
	
	
	// TODO: Fügen Sie hier Ihren Meldungsbehandlungscode ein.
}
