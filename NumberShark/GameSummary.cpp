// GameSummary.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MFC-ZahlenHai.h"
#include "EvoZahlenHai.h"
#include "GameSummary.h"
#include ".\gamesummary.h"


// CGameSummary-Dialogfeld

IMPLEMENT_DYNAMIC(CGameSummary, CDialog)
CGameSummary::CGameSummary(CWnd* pParent /*=NULL*/)
	: CDialog(CGameSummary::IDD, pParent)
{
}

CGameSummary::~CGameSummary()
{
}

void CGameSummary::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, gameFinished);
	DDX_Control(pDX, IDC_RADIO1, radioEdit1);
	DDX_Control(pDX, IDC_RADIO2, radioEdit2);
}


BEGIN_MESSAGE_MAP(CGameSummary, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
END_MESSAGE_MAP()


// CGameSummary-Meldungshandler
EvoZahlenHai hai;

int maxPossiblePoints2[] = {0,2,3,7,9,15,17,21,30,40,44,50,52,66,81,89,93,111,113,124,144,166};
int wert=0;
int finishPointsPlayer, finishPointsComputer,finishUpperLimit;
CString radioExePath="";
CString radioSummaryName="";

void CGameSummary::uebergeben(EvoZahlenHai &hai, CString exePath, CString summaryName)
{
	finishPointsPlayer= hai.getPointsPlayer();
	finishPointsComputer=hai.getPointsComputer();
	finishUpperLimit=hai.getUpperLimit();
	radioExePath=exePath;
	radioSummaryName=summaryName;
}

void CGameSummary::OnBnClickedOk()
{
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	OnOK();
}

void CGameSummary::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	CString radioText1="";
	radioText1.Format(IDS_RADIO_EDIT1,radioSummaryName,radioExePath);
	CString radioText2="";
	radioText2.LoadString(IDS_RADIO_EDIT2);

	radioEdit1.SetWindowText(radioText1);
	radioEdit2.SetWindowText(radioText2);
	gameAnalyse();

	this->radioEdit1.SetCheck(1);
	this->radioEdit2.SetCheck(0);
}

void CGameSummary::gameAnalyse()
{
	int pointsPlayer = finishPointsPlayer;
	int pointsComputer = finishPointsComputer;
	int upperLimit = finishUpperLimit;

	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0;
	cf.crTextColor = RGB(255, 0, 0);

	CString result;

	CString sepPointsPlayer=hai.setSeperator(pointsPlayer);
	CString sepPointsComputer=hai.setSeperator(pointsComputer);
	CString sepUpperLimit=hai.setSeperator(upperLimit);

	//Spieler hat gewonnen
	if(pointsPlayer > pointsComputer)
	{
		//Wenn die maximale Punktezahl f�r die gew�hlte Zahl schon mal berechnet wurde, wird die am Ende des Spiels mit angegeben
		if(upperLimit <= sizeof(maxPossiblePoints2)/sizeof(int))
		{
			CString playerHeadline;
			//maxPossiblePoints Austauschen durch Wert aus dem 2D Array
			if(pointsPlayer==maxPossiblePoints2[upperLimit-1])
			{
				result.Format(IDS_PLAYER_WINS_OPTIMAL, sepPointsPlayer, sepUpperLimit, sepUpperLimit);
				playerHeadline.LoadString(IDS_PLAYER_WINS_HEADLINE);
				//�nderung des Dialog Titels
				this->SetWindowText(playerHeadline);
				gameFinished.SetWindowText(result);
			}
			else
			{
				result.Format(IDS_PLAYER_WINS, sepUpperLimit, sepPointsPlayer, sepUpperLimit, hai.setSeperator(maxPossiblePoints2[upperLimit-1]));
				playerHeadline.LoadString(IDS_PLAYER_WINS_HEADLINE);
				//�nderung des Dialog Titels
				this->SetWindowText(playerHeadline);
				gameFinished.SetWindowText(result);
			}
			
			wert=1;
		}
		//Einfach Ausgabe ohne die maximale Punktezahl
		else
		{
			result.Format(IDS_PLAYER_WINS_2, sepUpperLimit, sepPointsPlayer);
			CString playerHeadline;
			playerHeadline.LoadString(IDS_PLAYER_WINS_HEADLINE);
			//�nderung des Dialog Titels
			this->SetWindowText(playerHeadline);
			gameFinished.SetWindowText(result);
			wert=1;
		}
	}
	else
	{
        //Hai hat gewonnen
		if(pointsPlayer < pointsComputer)
		{
			result.Format(IDS_COMPUTER_WINS, sepPointsComputer, sepPointsPlayer);
			CString computerHeadline;
			computerHeadline.LoadString(IDS_COMPUTER_WINS_HEADLINE);
			//�nderung des Dialog Titels
			this->SetWindowText(computerHeadline);
			gameFinished.SetWindowText(result);
			wert=1;
		} else
		{
			//Unentschieden
			result.Format(IDS_DRAW, sepPointsPlayer);
			CString drawHeadline;
			drawHeadline.LoadString(IDS_DRAW_HEADLINE);
			//�nderung des Dialog Titels
			this->SetWindowText(drawHeadline);
			gameFinished.SetWindowText(result);
			wert=1;
		}
	}
}

void CGameSummary::OnBnClickedRadio1()
{
	radio2=0;
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	if(!this->radioEdit1.GetCheck())
	{
		this->radioEdit1.SetCheck(1);
		this->radioEdit2.SetCheck(0);
	}
	radio1=1;
}

void CGameSummary::OnBnClickedRadio2()
{
	
	radio1=0;
	// TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	if(!this->radioEdit2.GetCheck())
	{
		this->radioEdit1.SetCheck(0);
		this->radioEdit2.SetCheck(1);
	}
	radio2=1;
}
