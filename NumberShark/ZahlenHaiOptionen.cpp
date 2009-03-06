// ZahlenHaiOptionen.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "MFC-ZahlenHai.h"
#include "MFC-ZahlenHaiDlg.h"
#include "ZahlenHaiOptionen.h"
#include ".\zahlenhaioptionen.h"

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
	DDX_Control(pDX, IDC_GAME_IDEA, richEditIdea);
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
	if(exitOptions==1)
		OnOK();
	else
		OnOK();
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
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
	
	//Formatierung des Textes im RichEdit Feld
	CHARFORMAT cf;
	cf.dwMask = CFM_STRIKEOUT|CFM_BOLD;
	cf.dwEffects = CFE_BOLD;
	CString language="";
	language.LoadString(IDS_SPRACHE);
	//CString ideaText="";
	//ideaText.LoadString(IDS_GAME_IDEA);
	//richEditIdea.SetWindowText(ideaText);
	/*if(language=="DE")
	{
        richEditIdea.SetSel(1,12);
		richEditIdea.SetWordCharFormat(cf);
		richEditIdea.SetSel(54,65);
		richEditIdea.SetWordCharFormat(cf);
	}
	else
	{
		richEditIdea.SetSel(0,18);
		richEditIdea.SetWordCharFormat(cf);
		richEditIdea.SetSel(54,65);
		richEditIdea.SetWordCharFormat(cf);
	}*/
	
	exitOptions=0;
	((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetFocus();
	if(showButton==0)
	{
		((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->EnableWindow(false);
		((CEdit*)GetDlgItem(IDC_STATIC_MAX_POINTS_TEXT))->EnableWindow(false);
		optionenUpperLimit=20;
	}
	else
	{
		if(showButton==1)
		{
			((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->EnableWindow(true);
			((CEdit*)GetDlgItem(IDC_STATIC_MAX_POINTS_TEXT))->EnableWindow(true);
		}

	}
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

	radioButton1.SetCheck(0);
	radioButton2.SetCheck(0);
	((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->EnableWindow(false);
	
	if(controlUpperLimit==0)
	{
		radioButton1.EnableWindow(1);
		radioButton2.EnableWindow(1);
		radioButton2.SetCheck(1);
		OnBnClickedRadioMax2();
		((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->EnableWindow(true);
	}
	else
	{
		if(controlUpperLimit==1)
		{
			radioButton1.EnableWindow(1);
			radioButton1.SetCheck(1);
			radioButton2.EnableWindow(0);
			calculateMaxNew=1;
			((CEdit*)GetDlgItem(IDC_BUTTON_MAX))->EnableWindow(true);
		}
		else
		{
			radioButton1.EnableWindow(0);
			radioButton2.EnableWindow(0);
		}
	}

	CString accTabText="";
	CString accTabTextBuffer="";
	
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
	exitOptions=1;
	OnOK();
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
