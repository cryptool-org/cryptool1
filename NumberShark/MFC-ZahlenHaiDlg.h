/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

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
	CFont fontNormalButton;
	CHeaderCtrlEx header;
	CStatic haiListe;
	CDigiStatic m_LedText;
	CDigiStatic m_LedWinner;

	CBitmap haiBild;
	CBitmap haiBild2;
	CBitmap haiBild3;
	CBitmap haiBild4;

	// flomar, 03/04/2010
	CBitmap comicBackgroundBitmaps[9];

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
	void writeRegistry();
	void execWinHelp();
	void createUndoRedo();
	void writeIntoUndo(int nButton);
	void writeSaveGame();
	void readSaveGame();
	void calculationResult(int maxEndPoints, int upperLimit);

	CString sumText;
	CString startInfo;
	CString gameIdea;
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
	CStatic muschelfeld;
	CString shellBoxText;

	
	afx_msg void OnStartTimer();
	afx_msg void OnStopTimer();

	afx_msg void OnBnClickedButtonSwitchStyle();
	afx_msg void OnTimer(UINT nIDEvent);
	CStatic controlTimer;
	//CDigiStatic controlTimer;
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
};
