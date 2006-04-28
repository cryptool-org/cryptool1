#pragma once


// GameRules2-Dialogfeld

class GameRules2 : public CDHtmlDialog
{
	DECLARE_DYNCREATE(GameRules2)

public:
	GameRules2(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~GameRules2();
// Überschreibungen
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// Dialogfelddaten
	enum { IDD = IDD_GAME_RULES, IDH = IDR_HTML_GAMERULES2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
