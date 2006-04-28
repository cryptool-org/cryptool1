// GameRules2.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "GameRules2.h"


// GameRules2-Dialogfeld

IMPLEMENT_DYNCREATE(GameRules2, CDHtmlDialog)

GameRules2::GameRules2(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(GameRules2::IDD, GameRules2::IDH, pParent)
{
}

GameRules2::~GameRules2()
{
}

void GameRules2::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL GameRules2::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

BEGIN_MESSAGE_MAP(GameRules2, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(GameRules2)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// GameRules2-Meldungshandler

HRESULT GameRules2::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

HRESULT GameRules2::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}
