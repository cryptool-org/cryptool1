#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// GameRules-Dialogfeld

class GameRules : public CDialog
{
	DECLARE_DYNAMIC(GameRules)

public:
	GameRules(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~GameRules();

// Dialogfelddaten
	enum { IDD = IDD_GAME_RULES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedOk();
	CRichEditCtrl richEdit;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
