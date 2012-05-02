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

// ZahlenHaiOptionen.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "MFC-ZahlenHai.h"
#include "MFC-ZahlenHaiDlg.h"
#include "ZahlenHaiOptionen.h"
#include "DlgShowPrecalculatedScores.h"
#include "zhl.h"

CMFCZahlenHaiDlg sharkMaxPoints;
// ZahlenHaiOptionen-Dialogfeld

IMPLEMENT_DYNAMIC(ZahlenHaiOptionen, CDialog)
ZahlenHaiOptionen::ZahlenHaiOptionen(CWnd* pParent /*=NULL*/)
	: CDialog(ZahlenHaiOptionen::IDD, pParent)
	, playername(_T(""))
	, showToolTips(FALSE)
	, showOption(TRUE)
	, showStartNumber(TRUE)
	, optionStart(_T(""))
	, optionToolTip(_T(""))
	, optionGameStart(_T(""))
	, optionRemember(_T(""))
	, optionenMaxP(_T(""))
	, gameIdea(_T(""))
	, disclaimerText(_T(""))
	, infoText(_T(""))
{
}

ZahlenHaiOptionen::~ZahlenHaiOptionen()
{
}

void ZahlenHaiOptionen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, playername);
	DDX_Check(pDX, IDC_CHECK1, showToolTips);
	DDX_Check(pDX, IDC_CHECK2, showOption);
	DDX_Check(pDX, IDC_CHECK3, showStartNumber);

	DDX_Control(pDX, IDC_CHECK1, checkButton);
	DDX_Control(pDX, IDC_CHECK2, checkButtonOption);
	DDX_Control(pDX, IDC_CHECK3, checkStartNumber);

	DDX_Control(pDX, IDC_RADIO_MAX1, radioButton1);
	DDX_Control(pDX, IDC_RADIO_MAX2, radioButton2);

	DDX_Text(pDX, IDC_OPTION_START, optionStart);
	DDX_Text(pDX, IDC_OPTION_TOOLTIP, optionToolTip);
	DDX_Text(pDX, IDC_OPTION_GAME_START, optionGameStart);
	DDX_Text(pDX, IDC_OPTION_REMEMBER, optionRemember);
	DDX_Text(pDX, IDC_STATIC_MAX_POINTS_TEXT, optionenMaxP);

	DDX_Control(pDX, IDC_TAB1, dialogOptionsTab);
	DDX_Control(pDX, IDC_STATIC_MAX_POINTS_TEXT, optionenButtonMax);
	DDX_Text(pDX, IDC_GAME_IDEA, gameIdea);
	DDX_Text(pDX, IDC_DISCLAIMER_TEXT, disclaimerText);
	DDX_Text(pDX, IDC_INFO_TEXT, infoText);
	DDX_Control(pDX, IDC_ACCELERATORS, accControl);
}


BEGIN_MESSAGE_MAP(ZahlenHaiOptionen, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
	
	ON_BN_CLICKED(IDC_BUTTON_MAX, OnBnClickedButtonMax)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_RADIO_MAX1, OnBnClickedRadioMax1)
	ON_BN_CLICKED(IDC_RADIO_MAX2, OnBnClickedRadioMax2)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
END_MESSAGE_MAP()



// ZahlenHaiOptionen-Meldungshandler

void ZahlenHaiOptionen::OnBnClickedOk()
{	
	OnOK();
}

void ZahlenHaiOptionen::OnBnClickedCheck1()
{
	if(this->showToolTips)
		showToolTips = false;
	else
		showToolTips = true;

	UpdateData(true);
}

BOOL ZahlenHaiOptionen::OnInitDialog()
{
	optionStart.Format(IDS_OPTIONS_HEAD_TEXT);
	optionToolTip.Format(IDS_OPTIONS_TOOLTIPS);
	optionGameStart.Format(IDS_OPTIONS_SHOW_DIALOG);
	optionRemember.Format(IDS_OPTIONS_SHOW_NUMBERS);
	
	gameIdea.Format(IDS_GAME_IDEA);
	disclaimerText.Format(IDS_DISCLAIMER_TEXT);
	infoText.Format(IDS_INFO_TEXT);
	
	((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetFocus();
	
	CString sepUpperLimit=sharkMaxPoints.hai.setSeperator(optionenUpperLimit);
	optionenMaxP.Format(IDS_OPTIONS_MAX_POINTS,sepUpperLimit);
	CDialog::OnInitDialog();
	
	if(showToolTips)
		checkButton.SetCheck(1);
	else
		checkButton.SetCheck(0);
	
	if(showOption)
		checkButtonOption.SetCheck(1);
	else
		checkButtonOption.SetCheck(0);

	if(showStartNumber)
		checkStartNumber.SetCheck(1);
	else
		checkStartNumber.SetCheck(0);

	
	CString radioButtonText="";
	radioButtonText.LoadString(IDS_TAB_RADIO1);
	radioButton1.SetWindowText(radioButtonText);
	radioButtonText="";
	radioButtonText.LoadString(IDS_TAB_RADIO2);
	radioButton2.SetWindowText(radioButtonText);

	optionenButtonMax.EnableWindow(true);
	radioButton1.EnableWindow(true);
	radioButton2.EnableWindow(true);

	radioButton1.SetCheck(1);
	radioButton2.SetCheck(0);

	CString accTabText="";
	CString accTabTextBuffer="";

	accTabTextBuffer.LoadString(IDS_ACC_TAB);
	accTabText+=accTabTextBuffer;

	accTabTextBuffer.LoadString(IDS_ACC_ENTER_OR_SPACE);
	accTabText+=accTabTextBuffer;
	
	accTabTextBuffer.LoadString(IDS_ACC_CHANGE);
	accTabText+=accTabTextBuffer;

	accTabTextBuffer.LoadString(IDS_ACC_LOAD);
	accTabText+=accTabTextBuffer;

	accTabTextBuffer.LoadString(IDS_ACC_SAVE);
	accTabText+=accTabTextBuffer;

	accControl.SetWindowText(accTabText);
		
	drawStartTab();

	UpdateData(true);
	
	return true;
}

void ZahlenHaiOptionen::OnBnClickedCheck2()
{
	if(this->showOption)
		showOption = false;
	else
		showOption = true;

	UpdateData(true);
}

void ZahlenHaiOptionen::OnBnClickedCheck3()
{
	if(this->showStartNumber)
		showStartNumber = false;
	else
		showStartNumber = true;
	
	UpdateData(true);
}
void ZahlenHaiOptionen::OnBnClickedButtonMax()
{
	// flomar, 05/05/2010
	if(radioButton1.GetCheck()) {
		// at this point we want to recalculate the maximum score
		calculateMaximumScore();
		return;
	}
	else {
		// at this point we want to show the precalculated scores;
		// however, if our map is empty (meaning: no scores were found 
		// in "GameData.txt"), we want to tell the user about it
		if(mapPrecalculatedScores.empty()) {
			CString missingFileName; missingFileName.Format(IDS_GAME_DATA);
			CString message; message.Format(IDS_GAME_DATA_FILE_MISSING, missingFileName);
			CString title; title.Format(IDS_NUMBER_SHARK);
			MessageBox(message, title, MB_ICONWARNING);
			return;
		}
		else {
			CDlgShowPrecalculatedScores dlg(mapPrecalculatedScores);
			dlg.DoModal();
			return;
		}
	}
}

void ZahlenHaiOptionen::readGameData()
{
	// flomar, 02/22/2010
	// complete re-write of this function along with a new file format for the game data file

	// file handle
  CStdioFile gameDataFile;
	// file name
	CString gameDataFileName;
	gameDataFileName.LoadString(IDS_GAME_DATA);

	// make sure we start with an empty map
	mapPrecalculatedScores.clear();

	// try to open the game data file
	if(gameDataFile.Open(gameDataFileName, CFile::modeRead)) {
		// we have two differenct sections ("proved" and "best known")
		CString section;
		// we read one line at a time
		CString line;
		// we go through all lines in the game data file
		while(gameDataFile.ReadString(line)) {
			// remove leading/trailing whitespaces
			line.Trim();
			// ignore empty lines and those starting with # (for comments)
			if(line.Find("#") == 0 || line.GetLength() == 0) continue;
			
			// check if we need to change the section
			if(line.Find("proved") == 0) {
				section = "proved";
				continue;
			}
			if(line.Find("best known") == 0) {
				section = "best known";
				continue;
			}

			// create a game data block
			GameDataBlock gameDataBlock;
			// extract the necessary information
			gameDataBlock.limit = readGameDataBlock(line);
			gameDataBlock.score = readGameDataBlock(line);
			gameDataBlock.sequence = readGameDataBlock(line);
			gameDataBlock.sequenceLength = readGameDataBlock(line);
			gameDataBlock.leadingPrime = readGameDataBlock(line);
			gameDataBlock.proved = (section == "proved");

			mapPrecalculatedScores[atoi(gameDataBlock.limit.GetBuffer())] = gameDataBlock;
		}

		// close file handle
		gameDataFile.Close();
	}
	// dump a warning message
	else {
		CString missingFileName; missingFileName.Format(IDS_GAME_DATA);
		CString message; message.Format(IDS_GAME_DATA_FILE_MISSING, missingFileName);
		CString title; title.Format(IDS_NUMBER_SHARK);
		MessageBox(message, title, MB_ICONWARNING);
	}
}

CString ZahlenHaiOptionen::readGameDataBlock(CString &data)
{
	// flomar, 02/22/2010
	// this function takes the first block of data from the variable passed in, 
	// cuts it off (note: variable is a reference!) and returns it; the data 
	// parameter passed in is supposed to consist of "blocks of data" separated 
	// by colons (see "GameData.txt for details)

	// we will store the data block in this variable
	CString dataBlock;

	// find the first colon
	int index = data.Find(":");

	// ignore everything past this first colon (including the colon itself)
	if(index != -1) {
		// extract data block
		dataBlock = data.Left(index);
		// cut off data block from reference variable
		data.Delete(0, index + 1);
	}
	// if there is no colon, we might be at the end of the data block
	else {
		// extract data block
		dataBlock = data;
		// delete reference variable
		data.Empty();
	}

	// return the extracted data block
	return dataBlock;
}

void ZahlenHaiOptionen::calculateMaximumScore()
{
	int upperLimit = hai.getUpperLimit();
	CString sepUpperLimit = hai.setSeperator(upperLimit);

	CString question;
	question.LoadString(IDS_QUESTION);
	CString headline;
	headline.LoadString(IDS_MAX_POINTS_HEADLINE);

	// store the desired upper limit
	int tempUpperLimit = hai.getUpperLimit();

	// flomar, 02/16/2010
	// we have two options here to calculate the maximum number of possible points: 
	// (a) the "old" brute-force algorithm or (b) the "new" back-tracking algorithm
	CString selectSearchAlgorithm; selectSearchAlgorithm.Format(IDS_SELECT_SEARCH_ALGORITHM);

	int selection = AfxMessageBox(selectSearchAlgorithm, MB_YESNOCANCEL|MB_ICONQUESTION);

	// we go with the new back-tracking algorithm if the user pressed "YES"
	if(selection == IDYES) {
		// we're using a new approach that speeds up the search (see zhl.{cpp|h} for details) 
		AfxBeginThread(zhl::maxPointsSearch, (LPVOID)((int)(tempUpperLimit)), THREAD_PRIORITY_BELOW_NORMAL);
		// show the search progress dialog
		CString algorithm; algorithm.Format(IDS_ALGORITHM_BACK_TRACKING);
		dialogSearchProgress.show(clock(), algorithm, tempUpperLimit);
	}
	// we go with the old brute-force algorithm if the user pressed "NO"
	else if(selection == IDNO) {
		AfxBeginThread(maxPointsStatic, (LPVOID)((int)(tempUpperLimit)),THREAD_PRIORITY_BELOW_NORMAL);
		// show the search progress dialog
		CString algorithm; algorithm.Format(IDS_ALGORITHM_BRUTE_FORCE);
		dialogSearchProgress.show(clock(), algorithm, tempUpperLimit);
	}
	else {
		// simply return in case the user pushed the cancel button
		return;
	}
}

void ZahlenHaiOptionen::OnBnClickedRadioMax1()
{
	showMax=0;
	((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->EnableWindow(true);
	if(!this->radioButton1.GetCheck())
	{
		radioButton1.SetCheck(1);
		radioButton2.SetCheck(0);
	}
	calculateMaxNew=1;
}

void ZahlenHaiOptionen::OnBnClickedRadioMax2()
{
	calculateMaxNew=0;
	((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->EnableWindow(true);
	if(!this->radioButton2.GetCheck())
	{
		radioButton1.SetCheck(0);
		radioButton2.SetCheck(1);
	}
	showMax=1;
}

void ZahlenHaiOptionen::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	*pResult = 0;
	drawOptionsTab();
}

void ZahlenHaiOptionen::drawStartTab()
{
	DWORD dwExStyle= dialogOptionsTab.GetExtendedStyle();
	dialogOptionsTab.SetExtendedStyle(dwExStyle | TCS_EX_FLATSEPARATORS);

	
	CString tabHeader="";
	tabHeader.LoadString(IDS_TAB_HEADER1);
	dialogOptionsTab.InsertItem(0,tabHeader);
	

	tabHeader="";
	tabHeader.LoadString(IDS_TAB_HEADER2);
	dialogOptionsTab.InsertItem(1,tabHeader);

	tabHeader="";
	tabHeader.LoadString(IDS_TAB_HEADER3);
	dialogOptionsTab.InsertItem(2,tabHeader);

	tabHeader="";
	tabHeader.LoadString(IDS_TAB_HEADER4);
	dialogOptionsTab.InsertItem(3,tabHeader);

	drawOptionsTab();
}

void ZahlenHaiOptionen::drawOptionsTab()
{
	int tab = dialogOptionsTab.GetCurSel();
	int seeOptionsStandard = 1;
	int seeOptionsMaximum  = 0;
	int seeOptionsWelcome  = 0;
	int seeAccelerators    = 0;

	if(tab==0)
	{
		seeOptionsWelcome=1;
		seeOptionsStandard=0;
		seeOptionsMaximum=0;
		seeAccelerators=0;
	}
	else
	{
		if(tab==1)
		{
			seeOptionsWelcome=0;
			seeOptionsStandard=1;
			seeOptionsMaximum=0;
			seeAccelerators=0;
		}
		if(tab==2)
		{
			seeOptionsWelcome=0;
			seeOptionsStandard=0;
			seeOptionsMaximum=1;
			seeAccelerators=0;
		}
		if(tab==3)
		{
			seeOptionsWelcome=0;
			seeOptionsStandard=0;
			seeOptionsMaximum=0;
			seeAccelerators=1;
		}
	}

   	((CEdit*)GetDlgItem(IDC_CHECK1))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_CHECK2))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_CHECK3))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_STATIC1))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_STATIC2))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_STATIC3))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_STATIC4))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_STATIC5))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_EDIT_NAME))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_OPTION_TOOLTIP))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_OPTION_GAME_START))->ShowWindow(seeOptionsStandard);
	((CEdit*)GetDlgItem(IDC_OPTION_REMEMBER))->ShowWindow(seeOptionsStandard);
	
	((CEdit*)GetDlgItem(IDC_STATIC_MAX_POINTS_TEXT))->ShowWindow(seeOptionsMaximum);
	((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->ShowWindow(seeOptionsMaximum);
	((CEdit*)GetDlgItem(IDC_RADIO_MAX1))->ShowWindow(seeOptionsMaximum);
	((CEdit*)GetDlgItem(IDC_RADIO_MAX2))->ShowWindow(seeOptionsMaximum);
	((CEdit*)GetDlgItem(IDC_STATIC_MAXVALUE))->ShowWindow(seeOptionsMaximum);

	((CEdit*)GetDlgItem(IDC_GAME_IDEA))->ShowWindow(seeOptionsWelcome);
	((CEdit*)GetDlgItem(IDC_DISCLAIMER_TEXT))->ShowWindow(seeOptionsWelcome);
	((CEdit*)GetDlgItem(IDC_INFO_TEXT))->ShowWindow(seeOptionsWelcome);
	((CEdit*)GetDlgItem(IDC_ACCELERATORS))->ShowWindow(seeAccelerators);

}
