// MFC-ZahlenHaiDlg.h : Headerdatei
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
//#include "htmlhelp.h"

#include <stdio.h>
#include <atlbase.h>
#include <stdlib.h>

#include "EvoZahlenHai.h"
#include "ZahlenHaiOptionen.h"
#include "GameRules.h"
#include "GameSummary.h"
#include "zahl.h"

#include "WBButton.h"
#include "HeaderCtrlExt.h"

//Change row color -> m_colRow1 and m_colRow2 in the CColoredListCtrl constructor
#include "ColoredListCtrl.h"
#include "digistatic.h"


#define MAX_ZAHLENHAI_BUTTON 30
#define MIN_ZAHLENHAI_BUTTON 1
#define MAX_ZAHLENHAI_NUMBERS 9999
#define MAX_POINTS_CALC 22

// CMFCZahlenHaiDlg Dialogfeld
class CMFCZahlenHaiDlg : public CDialog
{
  
  ZahlenHaiOptionen optionen;
  GameRules rules;
  CGameSummary summary;
  // Konstruktion
public:
	CMFCZahlenHaiDlg(CWnd* pParent = NULL);	// Standardkonstruktor
    EvoZahlenHai hai;
	~CMFCZahlenHaiDlg(void);
// Dialogfelddaten
	enum { IDD = IDD_MFCZAHLENHAI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
protected:
	virtual BOOL OnInitDialog();
	afx_msg virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton( unsigned int nID );
	
	afx_msg HCURSOR OnQueryDragIcon();	
	DECLARE_MESSAGE_MAP()

	void enterWasPressed();
	void arrowKeyPressed(WPARAM wParam);
	void nextFreeButtonAbove(int buttonID, int maxStepsLeft, int maxStepsRight);
	void nextFreeButtonBelow(int buttonID, int maxStepsLeft, int maxStepsRight);
	
public:
	CColoredListCtrl ListControl;
	CTabCtrl tabControl;
	CToolTipCtrl toolTip;
	CToolTipCtrl toolTipNumbers;
	CRegKey regKey;
	CFont font;
	CFont fontButton; // TODO 
	CHeaderCtrlEx header;
	CStatic haiListe;
	CDigiStatic m_LedText;
	CDigiStatic m_LedWinner;
	CBitmap haiBild;
	CPropertySheet propSheet;
	CPropertyPage propPage;

    //BUTTON 
	CWBButton arrayButtonControl[MAX_ZAHLENHAI_BUTTON];
	CWBButton undoButton;
	CWBButton redoButton;

	int numbers;
	int pointsPlayer;
	int pointsComputer;
	int activeTab;
	int sumOfAllNumbers;
	int usablenumbersleft;
	int winner();
	int readRegistry();

	int *undoRedo;
		
	void CSetList(int playerchoice);
	void updateButtons();
	void updatePoints();
	void updateTab();
	void updateToolTips();
	void writeLogFile();
	void addOnInformation();
	void addOn();
	void readGameData();
	void writeRegistry();
	void execWinHelp();
	void createUndoRedo();
	void writeIntoUndo(int nButton);
	//CString setSeperator(__int64 value);
		
	CString sumText;
	CString startInfo;
	CString gameIdea;
	//CString disclaimerText;
	//CString infoText;
	CString startNumberSetting;
		
	afx_msg void OnBnClickedButtonStartnew();
	afx_msg void OnBnClickedButtonEnd();
	afx_msg void OnBnClickedButtonRules();	
	afx_msg void OnBnClickedButtonOk();	
	afx_msg void OnBnClickedButtonOption();
	afx_msg void OnBnClickedButtonRest();
   	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonFinish();
	afx_msg void OnBnClickedButtonUndo();
	
	afx_msg void OnBnClickedButtonRedo();
	
	CButton buttonRules;
};
