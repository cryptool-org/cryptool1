#pragma once
#include "afxcmn.h"
#include "EvoZahlenHai.h"
#include "afxwin.h"


// CGameSummary-Dialogfeld

class CGameSummary : public CDialog
{
	DECLARE_DYNAMIC(CGameSummary)

public:
	CGameSummary(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~CGameSummary();

// Dialogfelddaten
	enum { IDD = IDD_GAME_SUMMARY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl gameFinished;
	afx_msg void OnBnClickedOk();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	void gameAnalyse();
	void uebergeben(EvoZahlenHai &hai, CString exePath, CString summaryName,int proofed2, int bestKnown2, int bestValue);
	CButton radioEdit1;
	CButton radioEdit2;
	int radio1;
	int radio2;


	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
