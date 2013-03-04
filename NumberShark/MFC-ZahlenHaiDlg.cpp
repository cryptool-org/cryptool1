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

// MFC-ZahlenHaiDlg.cpp : Implementierungsdatei
// zahl.cpp

#include "stdafx.h"
#include "WBButton.h"
#include "MFC-ZahlenHai.h"
#include "MFC-ZahlenHaiDlg.h"
#include "math.h"
#include <time.h>
//#include "WinBase.h"

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <direct.h>
#include <stdio.h>

#include ".\mfc-zahlenhaidlg.h"

#include "DlgShowPrecalculatedScores.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CString bestWay;

using namespace std;
// CAboutDlg-Dialogfeld für Anwendungsbefehl 'Info'

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
// Dialogfelddaten
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	
// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

#define NUM_COLUMNS 6
struct listenHeader
{
	UINT columnTitle;
	int columnFormat;
	int columnWidth;
};

listenHeader columnheader[NUM_COLUMNS]={
	{IDS_ZUG,LVCFMT_LEFT,39},
	{IDS_SPIELER,LVCFMT_RIGHT,88},
	{IDS_HAI,LVCFMT_RIGHT,189},
	{IDS_SPIELER_PUNKTE,LVCFMT_RIGHT,90},
	{IDS_HAI_PUNKTE,LVCFMT_RIGHT,90},
	{IDS_REST,LVCFMT_RIGHT,55}
};

// flomar, 02/23/2010
SearchStatus searchStatus;

UINT_PTR timer=0;
int sekunden=0;
int minuten=0;
int a=1;
CString presTimer="";
CString seperator="";

CString optionenSetting="";
CString toolTipSetting="";
CString exePath = "";
int showWinner=0;
int checkList=0;
int newGameCount=0;

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CMFCZahlenHaiDlg Dialogfeld

CMFCZahlenHaiDlg::CMFCZahlenHaiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCZahlenHaiDlg::IDD, pParent)
	, pointsPlayer(0)
	, pointsComputer(0)
	, sumOfAllNumbers(0)
	, undoRedo(0)
	, shellBoxText(_T(""))
{
	numbers = 20;
}

CMFCZahlenHaiDlg::~CMFCZahlenHaiDlg(void)
{
	delete []undoRedo;
}
void CMFCZahlenHaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, numbers);
	DDX_Text(pDX, IDC_STATIC_SUM, sumText);

	DDX_Control(pDX, IDC_LIST2, ListControl);
	DDX_Control(pDX, IDC_TAB1, tabControl);

	DDX_Control(pDX, IDC_STATIC_HAI_LISTE, haiListe);

	DDX_Control(pDX, IDC_LEDTEXT, m_LedText);
	//DDX_Control(pDX, IDC_LED_WINNER, m_LedWinner);
	//	DDX_Control(pDX, ID_BUTTON_RULES,Spielregeln);
	//	DDX_Control(pDX, IDC_BUTTON_OPTION,Spieloptionen);

	DDX_Control(pDX, IDC_BUTTON01, arrayButtonControl[0]);
	DDX_Control(pDX, IDC_BUTTON02, arrayButtonControl[1]);
	DDX_Control(pDX, IDC_BUTTON03, arrayButtonControl[2]);
	DDX_Control(pDX, IDC_BUTTON04, arrayButtonControl[3]);
	DDX_Control(pDX, IDC_BUTTON05, arrayButtonControl[4]);
	DDX_Control(pDX, IDC_BUTTON06, arrayButtonControl[5]);
	DDX_Control(pDX, IDC_BUTTON07, arrayButtonControl[6]);
	DDX_Control(pDX, IDC_BUTTON08, arrayButtonControl[7]);
	DDX_Control(pDX, IDC_BUTTON09, arrayButtonControl[8]);
	DDX_Control(pDX, IDC_BUTTON10, arrayButtonControl[9]);
	DDX_Control(pDX, IDC_BUTTON11, arrayButtonControl[10]);
	DDX_Control(pDX, IDC_BUTTON12, arrayButtonControl[11]);
	DDX_Control(pDX, IDC_BUTTON13, arrayButtonControl[12]);
	DDX_Control(pDX, IDC_BUTTON14, arrayButtonControl[13]);
	DDX_Control(pDX, IDC_BUTTON15, arrayButtonControl[14]);
	DDX_Control(pDX, IDC_BUTTON16, arrayButtonControl[15]);
	DDX_Control(pDX, IDC_BUTTON17, arrayButtonControl[16]);
	DDX_Control(pDX, IDC_BUTTON18, arrayButtonControl[17]);
	DDX_Control(pDX, IDC_BUTTON19, arrayButtonControl[18]);
	DDX_Control(pDX, IDC_BUTTON20, arrayButtonControl[19]);
	DDX_Control(pDX, IDC_BUTTON21, arrayButtonControl[20]);
	DDX_Control(pDX, IDC_BUTTON22, arrayButtonControl[21]);
	DDX_Control(pDX, IDC_BUTTON23, arrayButtonControl[22]);
	DDX_Control(pDX, IDC_BUTTON24, arrayButtonControl[23]);
	DDX_Control(pDX, IDC_BUTTON25, arrayButtonControl[24]);
	DDX_Control(pDX, IDC_BUTTON26, arrayButtonControl[25]);
	DDX_Control(pDX, IDC_BUTTON27, arrayButtonControl[26]);
	DDX_Control(pDX, IDC_BUTTON28, arrayButtonControl[27]);
	DDX_Control(pDX, IDC_BUTTON29, arrayButtonControl[28]);
	DDX_Control(pDX, IDC_BUTTON30, arrayButtonControl[29]);
	DDX_Control(pDX, IDC_BUTTON_UNDO, undoButton);
	DDX_Control(pDX, IDC_BUTTON_REDO, redoButton);
	DDX_Control(pDX, ID_BUTTON_RULES, buttonRules);
	DDX_Control(pDX, IDC_STATIC_BLOCK, muschelfeld);
	DDX_Text(pDX, IDC_STATIC_BLOCK, shellBoxText);
	DDX_Control(pDX, IDC_TIMER, controlTimer);
}

BEGIN_MESSAGE_MAP(CMFCZahlenHaiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON01, IDC_BUTTON30, OnBnClickedButton)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
	
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(ID_BUTTON_END, OnBnClickedButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_STARTNEW, OnBnClickedButtonStartnew)
	ON_BN_CLICKED(ID_BUTTON_RULES, OnBnClickedButtonRules)
	ON_BN_CLICKED(IDC_BUTTON_REST, OnBnClickedButtonRest)
	ON_BN_CLICKED(IDC_BUTTON_OPTION, OnBnClickedButtonOption)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_FINISH, OnBnClickedButtonFinish)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_REDO, OnBnClickedButtonRedo)
	ON_BN_CLICKED(IDC_BUTTON_SWITCH_STYLE, OnBnClickedButtonSwitchStyle)
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnLvnColumnclickList2)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
END_MESSAGE_MAP()

// CMFCZahlenHaiDlg Meldungshandler



BOOL CMFCZahlenHaiDlg::OnInitDialog()
{		
	// read "GameData.txt"
	optionen.readGameData();
	
	// read some registry settings
	int regUpperLimit=readRegistry();

	//Beim Start des Spiels sind bereits 20 Buttons aktiv, so dass der Spieler direkt starten kann
	hai.upperLimit=regUpperLimit;
	numbers=regUpperLimit;
	hai.init(hai.getUpperLimit());

	optionen.setEvoZahlenHai(hai);

	// show the options dialog (if desired)
	if(optionen.showOption) {
		optionen.DoModal();
	}

	//TTS_BALLOON verwandelt einen normalen ToolTip in einen abgerundeten ToolTip
	toolTip.Create(this, TTS_NOPREFIX | TTS_BALLOON | TTS_ALWAYSTIP);
	toolTipNumbers.Create(this,TTS_NOPREFIX | TTS_BALLOON | TTS_ALWAYSTIP);

	//Anzeige Dauer
	toolTip.SendMessage(TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX);
	toolTipNumbers.SendMessage(TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX);

	haiBild.LoadBitmap(IDB_BITMAP2);
	haiBild2.LoadBitmap(IDB_BITMAP8);
	haiBild3.LoadBitmap(IDB_BITMAP9);
	haiBild4.LoadBitmap(IDB_BITMAP3);

	// flomar, 03/04/2010
	comicBackgroundBitmaps[0].LoadBitmap(IDB_BITMAP_NUMBERSHARK_01);
	comicBackgroundBitmaps[1].LoadBitmap(IDB_BITMAP_NUMBERSHARK_02);
	comicBackgroundBitmaps[2].LoadBitmap(IDB_BITMAP_NUMBERSHARK_03);
	comicBackgroundBitmaps[3].LoadBitmap(IDB_BITMAP_NUMBERSHARK_04);
	comicBackgroundBitmaps[4].LoadBitmap(IDB_BITMAP_NUMBERSHARK_05);
	comicBackgroundBitmaps[5].LoadBitmap(IDB_BITMAP_NUMBERSHARK_06);
	comicBackgroundBitmaps[6].LoadBitmap(IDB_BITMAP_NUMBERSHARK_07);
	comicBackgroundBitmaps[7].LoadBitmap(IDB_BITMAP_NUMBERSHARK_08);
	comicBackgroundBitmaps[8].LoadBitmap(IDB_BITMAP_NUMBERSHARK_09);

	shellBoxText.LoadString(IDS_SHELL_GROUP_BOX);
	seperator.LoadString(IDS_SEPERATOR);

	//Breite der ToolTips wird festgelegt.
	//Die Anagbe der Breite ist notwendig um mit \n im ToolTip einen
	//Zeilenumbruch zu erzwingen
	toolTip.SetMaxTipWidth(1000);
	toolTipNumbers.SetMaxTipWidth(1000);
	
	//Farbe für den Text und den Hintergrund der Tool Tipps
	toolTip.SetTipTextColor(RGB(0,0,0));
	toolTip.SetTipBkColor(RGB(213,227,241));
	toolTipNumbers.SetTipTextColor(RGB(0,0,0));
	toolTipNumbers.SetTipBkColor(RGB(213,227,241));
	CDialog::OnInitDialog();
	
	presTimer="00:00";
	controlTimer.SetWindowText(presTimer);

	exePath = GetCommandLine();
	// Hinzufügen des Menübefehls "Info..." zum Systemmenü.
	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
	    CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	// wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	createUndoRedo();

	//buttonRules.SetButtonStyle(
	//Die Schriftgröße der Zahlen auf den Muscheln wird gesetzt
	//150 = Schriftgröße (wie bei Word) mal 10 - eine größere Schrift passt nicht auf die Muscheln
	CClientDC dc(this);
	fontButton.CreatePointFont(145, "Arial", &dc);
	fontNormalButton.CreatePointFont(155, "Arial", &dc);

	//arrayButtonControl[1].SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
	//LOGFONT logFont;
	//logFont.lfUnderline = TRUE;
	//logFont.lfHeight = 13;
	//logFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	
	CString numberShark="";
	numberShark.LoadString(IDS_NUMBER_SHARK);
	CString titleVersion="";
	titleVersion.LoadString(IDS_TITLE_VERSION);
	this->SetWindowText(numberShark+titleVersion);
		
	updatePoints();
	updateButtons();

	updateTab();
	updateToolTips();
	 
	CSetList(-1);
	ListControl.ShowWindow(0);
	
	haiListe.SetBitmap(haiBild);
	haiListe.ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_STATIC_LISTE))->ShowWindow(false);
	
	//Änderung der LED-Anzeige: Hindergrundfarbe, Farbe der Zeichen
	//DigiStatic.cpp m_BackColor
	//m_LedWinner.SetBkColor(RGB(0,0,0));
	//m_LedText.SetColor(RGB(200,220,245),RGB(255,255,0));
	//m_LedWinner.SetColor(RGB(200,220,245),RGB(255,255,0));
	//controlTimer.SetColor(RGB(213,221,213),RGB(255,0,0));

	DWORD dwExStyle= tabControl.GetExtendedStyle();
	tabControl.SetExtendedStyle(dwExStyle | TCS_EX_FLATSEPARATORS);

	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(true);

	//LoadBitmap(Bitmap ID,state of the Button, size...)
	//state of the Button: 1-Normal, 2-Select, 3-Disable, 4-Focus,5-...
	undoButton.LoadBitmaps(IDB_BITMAP_UNDO,4,0,0,0,0);
	redoButton.LoadBitmaps(IDB_BITMAP_REDO,4,0,0,0,0);

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}
BOOL CMFCZahlenHaiDlg::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		//Abfangen des Drucks auf die Enter Taste
		if(pMsg->wParam == 13)
		{
			////Wenn Enter gedrückt wurde
			enterWasPressed();
			return true;
		}
		//Pfeiltasten nach Oben und Unten
		if(pMsg->wParam ==38 || pMsg->wParam==40)
		{
			arrowKeyPressed(pMsg->wParam);
			return true;
		}
	}

   if(IsWindow(toolTip.m_hWnd)) //existiert ?
   {
      toolTip.RelayEvent(pMsg);
	  toolTipNumbers.RelayEvent(pMsg);
   }
  
   return CDialog::PreTranslateMessage(pMsg);
}
void CMFCZahlenHaiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMFCZahlenHaiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}	
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CMFCZahlenHaiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Erstellung der List in welcher die Punkte von Spieler und Computer eingetragen werden
void CMFCZahlenHaiDlg::CSetList(int playerchoice)
{
	int currentRound = hai.getCurrentRound();
	int player = playerchoice;
	int rest=0;
	CString title="";
	
	///////////////////////////////////////////////////////////////////////////////////
	if(!currentRound)
	{
	
		int i;
		int bufferLength=1;
		LV_COLUMN lvc;

		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
		for(i = 0; i<6; i++)
		{
			lvc.iSubItem = i;
			title.LoadString(columnheader[i].columnTitle);
			lvc.pszText = title.GetBuffer(bufferLength);
			lvc.cx = columnheader[i].columnWidth;
			lvc.fmt = columnheader[i].columnFormat;
			ListControl.InsertColumn(i,&lvc);
			title.ReleaseBuffer();
		}
		///////////////////////SET UP THE MULTILINE HEADER CONTROL
		font.CreatePointFont(190,"MS Serif");

		CHeaderCtrl* pHeader = NULL;
		pHeader=ListControl.GetHeaderCtrl();

		if(pHeader==NULL)
			return;
	
		VERIFY(header.SubclassWindow(pHeader->m_hWnd));	

		//A BIGGER FONT MAKES THE CONTROL BIGGER
		header.SetFont(&font);
	
		HDITEM hdItem;

		hdItem.mask = HDI_FORMAT;
	
		for(i=0; i<header.GetItemCount(); i++)
		{
			header.GetItem(i,&hdItem);

			hdItem.fmt|= HDF_OWNERDRAW;
		
			header.SetItem(i,&hdItem);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
    //Der Spieler kann einzelne Zeilen in der Liste auswählen
	ListControl.SetExtendedStyle(ListControl.GetExtendedStyle()|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	char buffer[1000];
	CString stringFinalPointsComputer="";
	CString stringFinalPointsPlayer="";
	CString stringRounds="";
	CString stringNumberscomputer="";
	CString stringNumbersPlayer="";
	CString stringUsableNumbersLeft="";
	CString primeInfo="";
	CString test="";

	primeInfo.LoadString(IDS_PRIME_INFO);
	
	stringRounds = _itoa(currentRound, buffer, 10);
	stringFinalPointsPlayer = _itoa(hai.getPointsPlayer(), buffer, 10);
	stringFinalPointsComputer = _itoa(hai.getPointsComputer(), buffer, 10);
	
	if(hai.getComputerNumbers().n == 0 || rest>0)
	{
		stringNumberscomputer=_itoa(player, buffer,10);
		if(isPrime(player))
				stringNumberscomputer+=primeInfo;
		stringNumbersPlayer="0";
	}
	
	stringNumbersPlayer=_itoa(player, buffer, 10);
	if(isPrime(player))
		stringNumbersPlayer+=primeInfo;
		
	for(int i=0; i<hai.getComputerNumbers().n && rest==0; i++)
	{
		if(i == 0) 
		{
			stringNumberscomputer+=_itoa(hai.getComputerNumbers().pNumbers[i],buffer,10);
			if(isPrime(hai.getComputerNumbers().pNumbers[i]))
				stringNumberscomputer+=primeInfo;
		}
		else
		{
			stringNumberscomputer+=", ";		
			stringNumberscomputer+=_itoa(hai.getComputerNumbers().pNumbers[i],buffer,10);
			if(isPrime(hai.getComputerNumbers().pNumbers[i]))
				stringNumberscomputer+=primeInfo;
		}
	}
	
	stringUsableNumbersLeft=_itoa(hai.usableNumbersLeft(),buffer,10);
	//Die Zahlen, die jede Runde von dem Spieler und dem Computer gezogen werden, werden in die Liste eingetragen
    ListControl.InsertItem(currentRound-1, stringRounds);
	if(!hai.getComputerNumbers().n == 0 && rest==0)
	    ListControl.SetItemText(currentRound-1, 1, stringNumbersPlayer);
	else
	    ListControl.SetItemText(currentRound-1, 1,"0");
	ListControl.SetItemText(currentRound-1, 2, stringNumberscomputer);
	
	//Die Punktezahlen von Spieler und Computer werden in die Liste geschrieben
	ListControl.SetItemText(currentRound-1, 3, stringFinalPointsPlayer);
	ListControl.SetItemText(currentRound-1, 4, stringFinalPointsComputer);
	ListControl.SetItemText(currentRound-1, 5, stringUsableNumbersLeft);

	//Immer die letzte eingetragene Zeile ist sichtbar
	
	int nCount = ListControl.GetItemCount();
	if (nCount > 0)
	   ListControl.EnsureVisible(nCount-1, FALSE);
}

//Die Warnung "warning C4100: 'pNMHD R': Unreferenzierter formaler Parameter " wird für OnTcnSelchange1 ausgeschalten
#pragma warning(push)
#pragma warning( disable : 4100 )
void CMFCZahlenHaiDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Wenn ein neuer Reiter ausgewählt wird, werden auch die Buttons auf diesem Reiter aktualisiert
	updateButtons();
	//Aktualisierung(selektierbar, nicht selektierbar) der Buttons für das aktuelle Tab
	*pResult = 0;
}
#pragma warning(pop)

//Aktualisierung der Buttons für die Eingabe der gewünschten Zahlen
void CMFCZahlenHaiDlg::updateButtons()
{
	int upperLimit = hai.getUpperLimit();
	optionen.optionenUpperLimit=upperLimit;
	int *numbersTemp = hai.getNumbers();
	
	bool found;
	CString stringBeschriftung="";
	CString stringNumber="";
	
	char Buffer[100];

	int i;

	for(i=0; i<MAX_ZAHLENHAI_BUTTON; i++)
	{
		//Die Nummer des ausgewählten Reiters wird zurückgegeben
		int tab = tabControl.GetCurSel();
		int counter=0;
		if(tab < 0)
			tab=0;
		int number = tab * MAX_ZAHLENHAI_BUTTON + i + 1;
        //Alle Buttons darstellen bzw. ausblenden
		
		arrayButtonControl[i].ShowWindow(number <= upperLimit);
		
		if(number <= upperLimit)
		{
			arrayButtonControl[i].EnableWindow(numbersTemp[number] == FREE);
			if(arrayButtonControl[i].GetButtonStyle()==BS_OWNERDRAW)
			{
				//Alle Buttons sollen auswählbar sein.Alle auf PLAYER oder COMPUTER gesetzten sollen ausgegraut sein
				
				arrayButtonControl[i].LoadBitmaps(IDB_BITMAP1,5,0,0,0,0);
	//			
				arrayButtonControl[i].SetTextFont(fontButton);
				arrayButtonControl[i].SetFontColor(RGB(255,255,0));
			}
					
			stringBeschriftung=_itoa(number, Buffer, 10);
		    arrayButtonControl[i].SetWindowText(stringBeschriftung);

			//Durch diese Abfrage werden die ToolTips nur geschrieben wenn sie auch aktiviert sind
			if(optionen.showToolTips)
			{
				CString factor;
				CString isFactor;

				int j;
				//number ist eine Zahl aus den zur Verfügung stehenden Zahlen
				//In der Schleife werden alle noch vorhandenen Teiler einer Zahl herausgefunden
				for(j=1; j <= number/2+1; j++)
				{	
					//wenn die Zahle noch nicht gewählt wurde
					if(numbersTemp[j] == FREE)
					{	
						//wenn j ein Teiler von number ist
						if((!(number % j)) && (number != j))
						{
							stringNumber=_itoa(j, Buffer, 10);
							stringNumber+=", ";
							factor += stringNumber;
                    	}
					}
				}
				
				if(number<upperLimit/2+1)
				{
                    for(j=number+1;j<=upperLimit  && counter<=10; j++)
					{
						if(numbersTemp[number]==FREE && numbersTemp[j]==FREE)
						{
							if(!(j%number))
							{
								counter++;
								stringNumber=_itoa(j,Buffer,10);
								stringNumber+=", ";
								
								if(counter==10)
								{
									stringNumber.Delete(stringNumber.GetLength()-2,1);
									stringNumber+="....";
								}
								if(counter<=10)
                                    isFactor+=stringNumber;
							}
						}
					}
				}
				//Das letzte Zeichen in dem CString factor, ein Komma, wird gelöscht
				factor.Delete(factor.GetLength()-2,1);
				isFactor.Delete(isFactor.GetLength()-2,1);
				//Wenn keine Teiler in die ToolTips geschrieben werden, soll "Keine Teiler mehr vorhanden!" in dem String factor stehen
				if (factor=="")
				{
					CString toolTipNumber="";
					toolTipNumber.Format(IDS_TOOL_TIP_NUMBER,stringBeschriftung);
					CString toolTipIsFactor="";
					if(isFactor=="")
						isFactor.LoadString(IDS_ISNOT_FACTOR);
					toolTipIsFactor.Format(IDS_TOOL_TIP_ISFACTOR, isFactor);
					factor.Format(IDS_TOOL_TIP_TEXT_NO_FACTORS,toolTipNumber, toolTipIsFactor);
				}
				
				else
				{
					//wenn Teiler gefunden wurde beginnen die ToolTips mit "Übrige Teiler: "
					CString toolTipNumber="";
					toolTipNumber.Format(IDS_TOOL_TIP_NUMBER,stringBeschriftung);
					CString toolTipIsFactor="";
					if(isFactor=="")
					{
						isFactor.LoadString(IDS_ISNOT_FACTOR);
						toolTipIsFactor=isFactor;
					}
					else
                        toolTipIsFactor.Format(IDS_TOOL_TIP_ISFACTOR, isFactor);

					CString factortitle;
					factortitle.Format(IDS_TOOL_TIP_TEXT,toolTipNumber,factor,toolTipIsFactor);
					factor=factortitle;
					
				}
				//Die ToolTips werden zu jedem Button hinzugefügt
				toolTipNumbers.AddTool(&(arrayButtonControl[i]), factor);
				toolTipNumbers.Activate(true);
			}
			else
			{
				toolTipNumbers.Activate(false);
			}
		}
	}
	
	//Immer wenn eine nicht teilbare Zahl im Zahlen Block vorhanden ist erscheint der Button
	//"Zahlen ohne Teiler für den Zahlenhai"
	for(i= upperLimit; i > upperLimit/2; i--)
	{
		found=false;
		
		for(int j=1; j<=i/2 && found==false && numbersTemp[i]==FREE; j++)
		{
			if(numbersTemp[j]==FREE)
			{
                if(i%j)
					found=false;
				else
					found=true;
			}
		}

		if(found==false && numbersTemp[i]==FREE)
		{
			((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(true);
		}
	}

	//In dem ToolTip des Haifutter Buttons werden die Zahlen angezeigt welche sich der Hai nehmen würde.
	CString numbersForShark="";
	found=false;
	int counter=0;
	for(i= upperLimit; i > upperLimit/2; i--)
	{
		found=false;
		for(int j=1; j<=i/2 && found==false && numbersTemp[i]==FREE; j++)
		{
			if(numbersTemp[j]==FREE)
			{
                if(!(i%j))
					found = true;
				else
					found = false;
			}
		}
		if(numbersTemp[i]==FREE && found==false)
		{
			counter++;
			if(counter<=10)
			{
                numbersForShark+=_itoa(i,Buffer,10);
				numbersForShark+=", ";
			}
			if(counter==10)
			{
				numbersForShark.Delete(numbersForShark.GetLength()-2,1);
				numbersForShark+=".....";
			}
		}
	}
	
	numbersForShark.Delete(numbersForShark.GetLength()-2,1);
	CString tipText;
	tipText.Format(IDS_BUTTON_REST, numbersForShark);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_REST), tipText);
	
	Invalidate(false);
	//Auswertung der Spielergebnisse wenn das Spiel beendet ist
	//Der Benutzer hat die Möglichkeit die Spielzüge in eine Zusammenfassung zu schreiben
	
	if(showWinner==0)
	{
        if(winner())
		{
			writeLogFile();			
		}
		else
		{
			//Bei jeder Wahl wird der Focus auf den aktuell aktiven Reiter gesetzt
			tabControl.SetFocus();
		}
	}

	if(optionen.playername!="")
	{
		CString sharkAgainst="";
		sharkAgainst.LoadString(IDS_SHARK_AGAINST);
		CString numberShark="";
		numberShark.LoadString(IDS_NUMBER_SHARK);
		CString titleVersion="";
		titleVersion.LoadString(IDS_TITLE_VERSION);
		this->SetWindowText(numberShark+sharkAgainst+optionen.playername+titleVersion);
	}
	else
	{
		CString numberShark="";
		numberShark.LoadString(IDS_NUMBER_SHARK);
		CString titleVersion="";
		titleVersion.LoadString(IDS_TITLE_VERSION);
        this->SetWindowText(numberShark+titleVersion);
	}
}

//Anzeiger der Punktestände von Spieler und Hai werden aktualisiert
void CMFCZahlenHaiDlg::updatePoints()
{
	int upperLimit=hai.getUpperLimit();
	pointsPlayer = hai.getPointsPlayer();
	pointsComputer = hai.getPointsComputer();

	char buffer[30];
	CString strPointsPlayer="";
	strPointsPlayer=_itoa(pointsPlayer,buffer,10);
	CString strPointsComputer="";
	strPointsComputer=_itoa(pointsComputer,buffer,10);
	m_LedText.SetText(strPointsPlayer + ":" + strPointsComputer);

	CString sepValueUpperLimit=hai.setSeperator(upperLimit);
	CString sepValue=hai.setSeperator(upperLimit+((upperLimit*(upperLimit-1))/2));
	sumText.Format(IDS_SUM_TEXT, sepValueUpperLimit, sepValue);
	usablenumbersleft = hai.usableNumbersLeft();

	UpdateData(false);
}

//Aktualisierung der TabControl
void CMFCZahlenHaiDlg::updateTab()
{
	tabControl.DeleteAllItems();
	int upperLimit = hai.getUpperLimit();
	int tab = ((upperLimit + (MAX_ZAHLENHAI_BUTTON - 1))/MAX_ZAHLENHAI_BUTTON);
	char Buffer[10];
	CString stringTabCount="";

	for(int i=0; i<tab; i++)
	{
		int a = 1 + (i * MAX_ZAHLENHAI_BUTTON);
		int b = a + MAX_ZAHLENHAI_BUTTON - 1;
		if(b > upperLimit)
			b=upperLimit;
		//Beschriftung der Reiter
		stringTabCount=_itoa(a,Buffer,10);
		stringTabCount+="-";
		stringTabCount+=_itoa(b,Buffer,10);
		tabControl.InsertItem(i, stringTabCount);
	}
	
}
//ToolTips für die einzelnen Buttons.
void CMFCZahlenHaiDlg::updateToolTips()
{
	CString TipText;
	// initialize the tool tips
	TipText.LoadString(IDS_BUTTON_STARTNEW);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_STARTNEW), TipText);
	TipText.LoadString(IDS_BUTTON_END);
	toolTip.AddTool(GetDlgItem(ID_BUTTON_END), TipText);
	TipText.LoadString(IDS_BUTTON_RULES);
	toolTip.AddTool(GetDlgItem(ID_BUTTON_RULES), TipText);
	TipText.LoadString(IDS_BUTTON_OK);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_OK), TipText);
	TipText.LoadString(IDS_BUTTON_OPTION);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_OPTION), TipText);
	TipText.LoadString(IDS_BUTTON_HELP);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_HELP), TipText);
	TipText.LoadString(IDS_TOOL_TIP_UNDO);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_UNDO), TipText);
	TipText.LoadString(IDS_TOOL_TIP_REDO);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_REDO), TipText);
	TipText.LoadString(IDS_TOOLTIP_BUTTON_LOADGAME);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_LOAD), TipText);
	TipText.LoadString(IDS_TOOLTIP_BUTTON_SAVEGAME);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_SAVE), TipText);
	TipText.LoadString(IDS_TOOLTIP_BUTTON_SWITCH_STYLE);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_SWITCH_STYLE), TipText);
	// activate the tool tips
	toolTip.Activate(true);
}
//Wenn der Spieler der Knopf "Neues Spiel" drückt werden die Punkteanzeigen, sowie die
//angezeigten Buttons gelöscht
void CMFCZahlenHaiDlg::OnBnClickedButtonStartnew()
{

	// START NEW
	// Wenn der Spieler der Button "Neues Spiel" drückt werden alle Punktestände gelöscht und die Einstellungen vom vorhergehenden Spiel bleiben erhalten
	showWinner=0;
	checkList=0;
//	save="";
	hai.init(hai.getUpperLimit());
	
	updatePoints();
	updateButtons();
	
	updateToolTips();
	// Liste löschen bei Klick auf "Neues Spiel"
	ListControl.DeleteAllItems();  
	
	ListControl.ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_STATIC_LISTE))->ShowWindow(0);

	newGameCount++;
	
	switch(newGameCount)
	{
		case 1:haiListe.SetBitmap(haiBild2);break;
		case 2:haiListe.SetBitmap(haiBild3);break;
		case 3:haiListe.SetBitmap(haiBild4);break;
		case 4:haiListe.SetBitmap(comicBackgroundBitmaps[0]);break;
		case 5:haiListe.SetBitmap(comicBackgroundBitmaps[1]);break;
		case 6:haiListe.SetBitmap(comicBackgroundBitmaps[2]);break;
		case 7:haiListe.SetBitmap(comicBackgroundBitmaps[3]);break;
		case 8:haiListe.SetBitmap(comicBackgroundBitmaps[4]);break;
		case 9:haiListe.SetBitmap(comicBackgroundBitmaps[5]);break;
		case 10:haiListe.SetBitmap(comicBackgroundBitmaps[6]);break;
		case 11:haiListe.SetBitmap(comicBackgroundBitmaps[7]);break;
		case 12:haiListe.SetBitmap(comicBackgroundBitmaps[8]);break;
		case 13:haiListe.SetBitmap(haiBild);newGameCount=0;break;
    }
	
	OnStopTimer();
	sekunden=0;
	minuten=0;
	timer=0;
	presTimer="00:00";
	controlTimer.SetWindowText(presTimer);



	haiListe.ShowWindow(1);

	((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_STATIC))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_EDIT1))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_STATIC_EINSTELLUNGEN))->ShowWindow(1);

	((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(false);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();
	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);

	((CEdit*)GetDlgItem(IDC_BUTTON_UNDO))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_BUTTON_REDO))->EnableWindow(false);
	
    m_LedText.ShowWindow(0);
}

//Wenn der Spieler den Knopf "Ende" drückt beendet sich das Programm
void CMFCZahlenHaiDlg::OnBnClickedButtonEnd()
{	
	writeRegistry();
	OnStopTimer();
	OnCancel();
}

//Wenn der Spieler auf den Knopf "Regeln" drückt erscheint ein extra Fenster welches kurz die Regeln erklärt
void CMFCZahlenHaiDlg::OnBnClickedButtonRules()
{
	rules.DoModal();
}
//Wenn der OK Button gedrückt wird
void CMFCZahlenHaiDlg::OnBnClickedButtonOk()
{
	//Daten werden aktualisiert
	UpdateData(true);
	
	//Kontrolle ob die Zahl, die der Spieler eingegeben hat, nicht kleiner als 0 und nicht größer als 9999 ist.
	//Lässt sich beliebig erweitern. MAX_ZAHLENHAI_NUMBERS in der MFC-ZahlenHaiDlg.h muss nur geändert werden
	if(numbers < 1 || numbers > MAX_ZAHLENHAI_NUMBERS)
	{
		CString input;
		input.Format(IDS_INVALID_INPUT, hai.setSeperator(MAX_ZAHLENHAI_NUMBERS));
		CString headline;
		if(numbers > MAX_ZAHLENHAI_NUMBERS)
		{
			headline.LoadString(IDS_VALID_INPUT_HEADLINE);
			numbers = 9999;
		}
		if(numbers < 1)
		{
			headline.LoadString(IDS_VALID_INPUT_HEADLINE_LOW);
			numbers = 1;
		}
		MessageBox(input, headline, MB_ICONWARNING);
		UpdateData(false);
		return;
	}

	// flomar, 01/06/2012: init the NumberShark object ("hai")
	hai.init(numbers);
	optionen.setEvoZahlenHai(hai);

	// flomar, 01/06/2012: at this point we tell the user that he can start the actual game;
	// the previous "solution" was sort of ambiguous, as the "you start now" information text 
	// was already displayed before the game had even started; instead, displaying a message 
	// box as soon as the game really DOES start makes more sense to me
	CString messageBoxHeader;	messageBoxHeader.LoadString(IDS_NUMBER_SHARK);
	CString messageBoxText;		messageBoxText.LoadString(IDS_START_INFO);
	MessageBox(messageBoxText, messageBoxHeader, MB_ICONINFORMATION);
	
	//Anzeige der Buttons, sowie der Punktestände werden zurückgesetzt
	updateTab();
	updatePoints();
	updateButtons();
	updateToolTips();

    createUndoRedo();

	OnStartTimer();

    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(true);	
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->EnableWindow(false);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
//////////////////////////////////////////////////////////////////////////////////////////////////////
//TIMER
void CMFCZahlenHaiDlg::OnStartTimer() 
{
    timer = SetTimer(1, 1000, 0);
}

void CMFCZahlenHaiDlg::OnStopTimer() 
{
   KillTimer(timer);   
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





//Weiter Spieloptionen
void CMFCZahlenHaiDlg::OnBnClickedButtonOption()
{
	optionen.DoModal();

	updatePoints();
	updateButtons();
	
	updateToolTips();
	toolTip.Activate(TRUE);
	((CEdit*)GetDlgItem(IDC_BUTTON_OPTION))->SetFocus();
}

// Button "Schnelles Ende". Der Button erscheint wenn nur noch nichtteilbare Zahlen vorhanden sind, der Spieler also keine Punkte mehr 
// bekommen könnte. Wenn der Button gedrückt wird erhält der Computer die restlichen Zahlen.
// aus der Funktion hai.assignFreeNumbersToComputer() aus EvoZahlenHai muss der Wert i irgendwie mit CSetList in Verbindung gebracht werden
void CMFCZahlenHaiDlg::OnBnClickedButtonRest()
{
	bool found=false;
	int *numbersTemp = hai.getNumbers();
	int upperLimit=hai.getUpperLimit();
		
	for(int i= upperLimit; i > upperLimit/2; i--)
	{
		found=false;
		//foundTab=false;
		for(int j=1; j<=i/2 && found==false && numbersTemp[i]==FREE; j++)
		{
			if(numbersTemp[j]==FREE)
			{
                if(!(i%j))
					found = true;
				else
					found = false;
			}
		}
		if(numbersTemp[i]==FREE && found==false)
		{
			writeIntoUndo(i);
		}
	}
	
	updatePoints();
	updateButtons();
		
	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
}
//Bei jeder Wahl des Spieler beginnt eine neue Runde
//Der Wert der Buttons wird durch die Beschriftung und das aktuell aktive Tab bestimmt
void CMFCZahlenHaiDlg::OnBnClickedButton(unsigned int nID)
{
	if(!checkList)
	{
       	if(timer==0)
			OnStartTimer();
		
		ListControl.ShowWindow(1);
		checkList=1;
		haiListe.ShowWindow(0);
		((CEdit*)GetDlgItem(IDC_STATIC_LISTE))->ShowWindow(1);
		((CEdit*)GetDlgItem(IDC_BUTTON1))->EnableWindow(false);
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(false);

		((CEdit*)GetDlgItem(IDC_BUTTON_OK))->ShowWindow(false);
		((CEdit*)GetDlgItem(IDC_EDIT1))->ShowWindow(false);
		((CEdit*)GetDlgItem(IDC_STATIC))->ShowWindow(false);
		((CEdit*)GetDlgItem(IDC_STATIC_EINSTELLUNGEN))->ShowWindow(false);
	     m_LedText.ShowWindow(1);
	}
			
	int nButton = nID + 1 - IDC_BUTTON01;
	ASSERT(nButton >=1 && nButton <= MAX_ZAHLENHAI_BUTTON);
	ASSERT(IDC_BUTTON30 - IDC_BUTTON01 == 29);
    
	if(nButton!=undoRedo[hai.getCurrentRound()])
		((CEdit*)GetDlgItem(IDC_BUTTON_REDO))->EnableWindow(false);
	
	nButton = nButton + tabControl.GetCurSel() * MAX_ZAHLENHAI_BUTTON;
    ((CEdit*)GetDlgItem(IDC_BUTTON_UNDO))->EnableWindow(true);
    writeIntoUndo(nButton);


    //Ab hier ist bekannt welche Zahl gewählt wurde -> nButton
	//hai.startRound(nButton);
	//CSetList(nButton);

	updatePoints();
	updateButtons();


}

void CMFCZahlenHaiDlg::writeIntoUndo(int nButton)
{
	undoRedo[hai.getCurrentRound()]=nButton;
	undoRedo[hai.getCurrentRound()+1]=0;
	hai.startRound(nButton);
	CSetList(nButton);
}


//Die Ergebnisse, welche in der Liste im Spiel zu sehen sind werden auf Wunsch des Benutzers am Ende des Spiels auch noch in eine Zusammenfassung
//geschrieben. Die Zusammenfassung ist so breit wie nötig, orientiert sich also an der Länge der Zahlen, welche eingetragen werden.
//Am Beginn der Liste, und nach jedem 50ten Eintrag wird eine kleine Orientierung gegeben, welche Spalte welche Daten beinhaltet.
//Wenn bei einem neuen Spiel eine Zusammenfassung geschrieben wird, wird die bereits existierende überschrieben. Dies sollte nur auf Wunsch des Benutzers 
//möglich sein.
//Es soll noch die Möglichkeit geben die Zusammenfassung in einem bestimmten Ordner zu speichern.

void CMFCZahlenHaiDlg::writeLogFile()
{
	//CString logfileDate;
	//CString logfileName;
	//CString logfileNumbers;
	CString time;
	CTime t = CTime::GetCurrentTime();
	time = t.Format("%B %d, %Y, %H:%M");
	
	showWinner=1;
	char Buffer[1000];
	
	CString upperLimitNumbers = _itoa(hai.getUpperLimit(),Buffer,10);
	CString playerName = optionen.playername;
	CString SpielerPunkte;
	SpielerPunkte=_itoa(hai.getPointsPlayer(),Buffer,10);

	CStdioFile file;
	//Je nach Sprachversion heißt die Datei, in welcher das Spiel gespeichert wird anders.
	CString filename;
	filename.LoadString(IDS_FILE_NAME);
	if(playerName=="")
		playerName="name";

	CString upperLimitZeug = upperLimitNumbers;
	int openStatus;
	
	//Der Dateiname wird durch die Anzahl im Zahlenvorrat, die Punktzahl des Spielers und den Spielernamen erweitert.
	//Die ermöglicht eine Art Highscore, und das Schreiben mehrerer Dateien
	filename=upperLimitZeug+"_"+SpielerPunkte+"_"+playerName+"_"+filename;
	//Die Datei "Zusammenfassung.txt" wird zum schreiben geöffnet
	openStatus=file.Open(filename,CFile::modeCreate|CFile::modeWrite);
	CString test="Fehler";
	
    if(openStatus==0)
	{
		//Ermitteln des Verzeichnisses in dem sich die Zahlenhai.exe befindet
		CString sharkExe = GetCommandLine();
		int pos = sharkExe.ReverseFind( '\\'); // FIXME --> Thomas
		sharkExe = sharkExe.Mid(0, pos+1);

		//Erstellen der Fehlermeldung wenn keine Schreibrechte vorhanden sind
		CString message="";
		//message.LoadString(IDS_NO_SUMMARY);
		message.Format(IDS_NO_SUMMARY,filename,sharkExe);

		AfxMessageBox(message,IDOK,MB_ICONINFORMATION);
		return;
	}

	SpielerPunkte="";
	CString LogText;
	file.WriteString("\r\n"+filename);
	LogText.LoadString(IDS_LOGFILE_DATE);
	file.WriteString(LogText+time);
	LogText.LoadString(IDS_LOGFILE_NAME);
	file.WriteString(LogText+optionen.playername);
	LogText.LoadString(IDS_LOGFILE_NUMBERS);
	file.WriteString(LogText+upperLimitNumbers);

	//CStrings für die Überschriften der einzelnen Spalten
	CString Zug;
	CString Spieler;
	CString Hai;
	CString HaiPunkte;
	CString Rest;
	
	Zug.LoadString(IDS_ZUG2);
	Hai.LoadString(IDS_HAI2);
	Spieler.LoadString(IDS_SPIELER2);
	SpielerPunkte.LoadString(IDS_SPIELER_PUNKTE2);
	HaiPunkte.LoadString(IDS_HAI_PUNKTE2);
	Rest.LoadString(IDS_REST2);

	//Anzahl der Spalten wird herausgefunden
	int cols = ListControl.GetHeaderCtrl()->GetItemCount();
	int *n_max;
	n_max = new int [cols];
	//Zwei Schleifen, welche für die Breite der Spalten zuständig sind, wenn der Inhalt der Spalten kleiner ist als die Überschrift
	//bzw. die Header
	//i durchläuft die Zeilen und j die jeweiligen Spalten 
	for (int i=0; i<ListControl.GetItemCount(); i++)
	{
		for (int j=0; j<cols; j++)
		{
			//Wenn die Länge des Textes im Header kleiner ist als die der größten Zahlenreihe in der Tabelle,
			//dann wird die Überschrift links mit Leerzeichen aufgefüllt
			CString line="";
			line += ListControl.GetItemText(i,j);
			
			switch(j)
			{
				//Wenn das Wort "Zug" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingefügt, bis die Größe passt
				case 0:n_max[j] = Zug.GetLength();while(Zug.GetLength() < line.GetLength())Zug.Insert(0, " ");break;
								
				//Wenn das Wort "Spieler" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingefügt, bis die Größe passt
				case 1:n_max[j] = Spieler.GetLength();while(Spieler.GetLength() < line.GetLength())Spieler.Insert(0, " ");break;
				
				//Wenn das Wort "Hai" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingefügt, bis die Größe passt
				case 2:n_max[j] = Hai.GetLength();while(Hai.GetLength() < line.GetLength())Hai.Insert(0, " ");break;
								
				//Wenn das Wort "Spieler-Punkte" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingefügt, bis die Größe passt
				case 3:n_max[j] = SpielerPunkte.GetLength();while(SpielerPunkte.GetLength() < line.GetLength())SpielerPunkte.Insert(0, " ");break;
				
				//Wenn das Wort "Hai-Punkte" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingefügt, bis die Größe passt
				case 4:n_max[j] = HaiPunkte.GetLength();while(HaiPunkte.GetLength() < line.GetLength())HaiPunkte.Insert(0, " ");break;
				
				//Wenn das Wort "Rest" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingefügt, bis die Größe passt
				case 5:n_max[j] = Rest.GetLength();while(Rest.GetLength() < line.GetLength())Rest.Insert(0, " ");break;
			};
			
		line += ListControl.GetItemText(i,j);
		//n-max wird die größte Spaltenbreite zugewiesen
		if (n_max[j] < line.GetLength()) n_max[j] = line.GetLength();
		}
	}
	
	//Die Überschrift der einzelnen Spalten werden geschrieben
	CString logfileHeadline;
	logfileHeadline.LoadString(IDS_LOGFILE_HEADLINE);
	file.WriteString(logfileHeadline);

	//In den Überschriften der Spielverlaufstabelle wird das "-" Zeichen gesucht und die nachfolgende
	//Stelle wird gelöscht. Da diese Stelle ein Zeilenumbruch ist, ist die Darstellung in der Zusammenfassung
	//nicht richtig

	CString head = Zug + " | " + Spieler + " | " + Hai + " | " + SpielerPunkte + " | " + HaiPunkte + " | " + Rest + " |\r\n";
	file.WriteString(head);
	//Zwei Schleifen, welche für die Breite der Spalten zuständig sind, wenn der Inhalt der Spalten kleiner ist als die Überschrift
	//bzw. die Header
	//i durchläuft die Zeilen und j die jeweiligen Spalten 
	//VC7 kann den Gültigkeitsbereich von i bei mehrfachen Konstrukten for(int i ...) korrekt
	//    verarbeiten. Da VC6 dies nicht kann, wurde i hier nicht noch einmal deklariert.

	CString allNumbers="";
	//allNumbers = upperLimitNumbers + ": ";
	int i;
	for(i =0;i <ListControl.GetItemCount();i++)
	{
		CString line="\r\n";
		for(int j =0;j < ListControl.GetHeaderCtrl()->GetItemCount();j++)
		{
			//Wenn die Länge des Textes der geschrieben wird kleiner ist als die vorher ermittelte größte Länge, dann wird diese
			//mit Freizeichen links aufgefüllt
			CString tmpStr = ListControl.GetItemText(i,j);
			while (tmpStr.GetLength() < n_max[j]) tmpStr.Insert(0, " ");
			line += tmpStr + " | ";
			//Alle 50 Zeilen wird zur Orientierung eine zusätzliche Zeile eingefügt, welche die Header der Spalten wieder einfügt
			int n=i%50;

			if(j==1 && ListControl.GetItemText(i,j)!="0")
				allNumbers+=ListControl.GetItemText(i,j)+" "+seperator+" ";
			

			if(i!=0 && n==0 && j==0 && ListControl.GetItemCount() > 50)
				file.WriteString("\r\n\r\n"+head);
		}
		file.WriteString(line);
	}
	if(i>=60)
		file.WriteString("\r\n\r\n"+head);
	delete []n_max;

	CString primeInfo="";
	primeInfo.LoadString(IDS_PRIME_INFO);
	allNumbers.Delete(allNumbers.GetLength()-2,2);
	while(allNumbers.Find(primeInfo,0) >= 0)
	{
		int find = allNumbers.Find(primeInfo,0);
		allNumbers.Delete(find,primeInfo.GetLength());
	}
	
		
	CString pointsPlayer = _itoa(hai.getPointsPlayer(),Buffer,10);
	CString pointsComputer = _itoa(hai.getPointsComputer(),Buffer,10);
	CString currentRound = _itoa(hai.getCurrentRound(),Buffer,10);
	
	CString logfilePointsPlayer;
	CString logfilePointsComputer;
	CString logfileRounds;
	CString lead;
	CString behind;

	//Punkte und Rundenanzahl werden nach der Tabelle in die Zusammenfassung geschrieben		
	LogText.LoadString(IDS_LOGFILE_POINTS_PLAYER);
	file.WriteString(LogText+pointsPlayer);
	LogText.LoadString(IDS_LOGFILE_PLAYER_NUMBERS);
	file.WriteString(LogText+allNumbers);
	LogText.LoadString(IDS_LOGFILE_POINTS_COMPUTER);
	file.WriteString(LogText+pointsComputer);
	LogText.LoadString(IDS_LOGFILE_ROUNDS);
	file.WriteString(LogText+currentRound);
	if(hai.getPointsPlayer() > hai.getPointsComputer())
	{
		LogText.LoadString(IDS_LOG_LEAD);
		int lead = hai.getPointsPlayer()-hai.getPointsComputer();
		file.WriteString(LogText+(_itoa(lead,Buffer,10)));
	}
	else
	{
		if(hai.getPointsPlayer() < hai.getPointsComputer())
		{
			LogText.LoadString(IDS_LOG_BEHIND);
			int behind = hai.getPointsComputer()-hai.getPointsPlayer();
			file.WriteString(LogText+(_itoa(behind,Buffer,10)));
		}
	}
	int upperLimit=hai.getUpperLimit();
	//Wenn die maximale Punktezahl für die gewählte Zahl schonmal berechnet wurde, wird das errechnete Ergebnis
	//auch mit in der Zusammenfassung angegeben


	if(upperLimit <= optionen.getMapPrecalculatedScores().size()) {
     	CString logfileMaxPoints;
			logfileMaxPoints.LoadString(IDS_LOGFILE_MAXPOINTS);
			file.WriteString(logfileMaxPoints + optionen.getMapPrecalculatedScores()[upperLimit].score);
	}

	file.Close();

	//Andere Möglichkeit
	//file.WriteString(CMsg(IDS_LOGFILE_ROUNDS)+currentRound);
}
// Der Gewinner des Spiels wird ermittelt und das Ergebnis wird ausgegeben
int CMFCZahlenHaiDlg::winner()
{
	if(!hai.gameFinished())
		return 0;

	OnStopTimer();
	sekunden=0;
	minuten=0;

	char Buffer[1000];
	int pointsPlayer = hai.getPointsPlayer();
	int upperLimit = hai.getUpperLimit();
//	int pointsComputer = hai.getPointsComputer();

	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
	//Um den Pfad der Zusammenfassung angeben zu können wird der Pfad der Exe Datei gespeichert und um den Namen der Exe Datei 
	//gekürzt
	CString exePathSummary=exePath;
	int pos = exePathSummary.ReverseFind( '\\');
	exePathSummary = exePathSummary.Mid(1, pos-1);

	CString upperLimitSummary=_itoa(hai.getUpperLimit(),Buffer,10);
	CString SpielerPunkte=_itoa(pointsPlayer, Buffer, 10);
	CString playerName = optionen.playername;
	CString filename;
	filename.LoadString(IDS_FILE_NAME);
	if(playerName=="")
		playerName="name";

	CString summaryName=upperLimitSummary+"_"+SpielerPunkte+"_"+playerName+"_"+filename;
	CString text;
	text.Format(IDS_LOGFILE_LOCATION,summaryName,exePathSummary);
	
	((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_STATIC))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_EDIT1))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_STATIC_EINSTELLUNGEN))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_BUTTON_REDO))->EnableWindow(false);

	// flomar, 06/14/2010
	// properly initialize game summary (passing the following parameters 
	// with an empty map caused problems during game evaluation) 
	if(optionen.getMapPrecalculatedScores().size() > 0)
		summary.init(this->hai, exePathSummary, summaryName, optionen.getMapPrecalculatedScores().size(), optionen.getMapPrecalculatedScores().size(), atoi(optionen.getMapPrecalculatedScores()[upperLimit].score));
	else
		summary.init(this->hai, exePathSummary, summaryName);
	
	summary.DoModal();
	
	int writeFile=1;
	showWinner=1;

	if(summary.radio1==1)
		writeFile=1;
	if(summary.radio2==1)
        writeFile=0;

	return writeFile;
	//Bei Messageboxes mit Antwortmöglichkeiten gibt die Funktion einen int Wert der Antwort zurück
}

//Wenn sich der Fokus über einem der Zahlenbuttons befindet und der Benutzer die Enter Taste drückt, wird dieser Button ausgewählt
void CMFCZahlenHaiDlg::enterWasPressed()
{
	int buttonID = this->GetFocus()->GetDlgCtrlID();
	//Wenn auf einem der 30 Buttons mit Zahlen Enter gedrückt wird
	if(buttonID >= IDC_BUTTON01 && buttonID <= IDC_BUTTON30)
		this->OnBnClickedButton(buttonID);
	else
        //Wenn in dem Edit Feld Enter gedrückt wird, wird die Zahl gleich ausgewählt
		if(buttonID == IDC_EDIT1)
		{
			//OK-Button wurde gedrückt
			OnBnClickedButtonOk();
	
		}
		//Aktivierung der Enter Taste auf allen Buttons
		else
			if(buttonID==IDC_BUTTON_REST)
				OnBnClickedButtonRest();
			else
			    if(buttonID==IDC_BUTTON_OPTION)
					OnBnClickedButtonOption();
				else
				    if(buttonID==IDC_BUTTON_STARTNEW)
							OnBnClickedButtonStartnew();
						else
						    if(buttonID==ID_BUTTON_RULES)
								OnBnClickedButtonRules();
}

//Diese Funktion sorgt dafür, das der Benutzer mit den Pfeiltasten durch die Zahlen gehen kann 
void CMFCZahlenHaiDlg::arrowKeyPressed(WPARAM wParam)
{
	//aktuell aktiver Reiter
	int tab = tabControl.GetCurSel();
	int tabCount = tabControl.GetItemCount();
	int *numbersTemp=hai.getNumbers();

	//buttonID gibt die ID des gewählten Button an
	int buttonID = this->GetFocus()->GetDlgCtrlID();
	//maxStepsLeft und maxStepsRight, geben die Anzahl der vorhandenen Felder links und rechtes vom gewählten Button an, um damit seine
	//Position zu bestimmen
	int maxStepsRight=0;
	int maxStepsLeft=0;

	//Pfeiltaste nach Oben
	if(wParam==38)
	{
		//befindet sich der Fokus auf einem der 30 Zahlenbuttons?
		if(buttonID >= IDC_BUTTON01 && buttonID <= IDC_BUTTON30)
		{
			//nur Buttons in der mittleren und untersten Reihe
			if(buttonID>=IDC_BUTTON11 && buttonID <= IDC_BUTTON30)
			{
				//ist der Button genau oben drüber frei?
				if(numbersTemp[buttonID-IDC_BUTTON01-9+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					//wenn frei, dann erhält der Button den Fokus 
					arrayButtonControl[buttonID-IDC_BUTTON01-10].SetFocus();
					return;
				}
				else
				{
					//mittlere Reihe
					if(buttonID>=IDC_BUTTON11 && buttonID<=IDC_BUTTON20)
					{
						maxStepsRight=IDC_BUTTON20-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON11;
						nextFreeButtonAbove(buttonID, maxStepsLeft, maxStepsRight);
					}
					//untere Reihe
					else
					{
						maxStepsRight=IDC_BUTTON30-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON21;
						nextFreeButtonAbove(buttonID, maxStepsLeft, maxStepsRight);
					}
				}
			}
			else
			{
                //wenn sich der Fokus in der oberen Reihe befindet, und somit der Reiter gewechselt werden soll
				maxStepsRight=IDC_BUTTON10-buttonID;
				maxStepsLeft=buttonID-IDC_BUTTON01;

				//der aktuell ausgewählte Reiter
				tab = tabControl.GetCurSel();
				//neuer Reiter wird ermittelt und ausgewählt
				if(tab>0 && tab<=tabCount)
                    tabControl.SetCurSel(tab-1);
				//neuer ausgewählter Reiter
				tab = tabControl.GetCurSel();
				//auf dem neuen Reiter werden die Buttons aktualisiert
				updateButtons();
				
				//Nachdem der neue Reiter ausgewählt ist wird noch der Fokus auf einen Button gesetzt
				//Abfrage ob der Button direkt über dem momentan ausgewählten noch frei ist
				if(numbersTemp[buttonID-IDC_BUTTON01+20+1+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					//wenn der Button noch frei ist, erhält dieser den Fokus
					arrayButtonControl[buttonID-IDC_BUTTON01+20].SetFocus();
					//kann eigentlich auch raus
					return;
				}
				//wenn der Button über dem aktuell ausgewählten nicht mehr frei ist
				else
				{
					//alle Buttons links von dem bereits vergebenen werden durchsucht, bis ein freier gefunden wurde
					for(int i=0; i<maxStepsLeft; i++)
					{
						//-i-1, da i bei 0 anfängt zu zählen
						if(numbersTemp[buttonID-IDC_BUTTON01+20+tab*MAX_ZAHLENHAI_BUTTON - i] == FREE)
						{
							//der Index des freien Buttons wird auf maxStepsLeft gesetzt
							maxStepsLeft=i;					                            
							break;
						}
					}
					//alle Buttons rechts von dem bereits vergebenne werden durchsucht, bis ein freier gefunden wurde
					for(int i=0; i<maxStepsRight; i++)
					{
						//+i+1, da i bei 0 anfängt zu zählen
						if(numbersTemp[buttonID-IDC_BUTTON01+20+tab*MAX_ZAHLENHAI_BUTTON + i+2] == FREE)
						{
							//der Index des freien Buttons wird auf maxStepsRight gesetzt
							maxStepsRight=i;					                            
							break;
						}
					}

					if(maxStepsLeft>maxStepsRight)
					{
						//Schritt nach rechts, wenn maxStepsRight kleiner als maxStepsLeft
						arrayButtonControl[buttonID-IDC_BUTTON01+20+maxStepsRight+1].SetFocus();
					}
					else
					{
						//Schritt nach links, wenn maxStepsLeft kleiner oder gleich maxStepsRight
						arrayButtonControl[buttonID-IDC_BUTTON01+20-maxStepsLeft-1].SetFocus();
					}
				}
			}
		}
	}
	//Pfeiltaste nach Unten
	if(wParam==40)
	{
		//befindet sich der Fokus auf einem der 30 Zahlenbuttons?
		if(buttonID >= IDC_BUTTON01 && buttonID <= IDC_BUTTON30)
		{
			//nur Buttons in der mittleren und obersten Reihe
			if(buttonID>=IDC_BUTTON01 && buttonID <= IDC_BUTTON20)
			{
				//ist der Button genau drunter frei?
				if(numbersTemp[buttonID-IDC_BUTTON01+11+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					arrayButtonControl[buttonID-IDC_BUTTON01+10].SetFocus();
					return;
				}
				else
				{
					//obere Reihe
					if(buttonID>=IDC_BUTTON01 && buttonID<=IDC_BUTTON10)
					{
						maxStepsRight=IDC_BUTTON10-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON01;
						nextFreeButtonBelow(buttonID, maxStepsLeft, maxStepsRight);
					}
					//mittlere Reihe
					if(buttonID>=IDC_BUTTON11 && buttonID<=IDC_BUTTON20)
					{
						maxStepsRight=IDC_BUTTON20-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON11;
						nextFreeButtonBelow(buttonID, maxStepsLeft, maxStepsRight);
					}

				}
			}
			else
			{
                //wenn sich der Fokus in der unteren Reihe befindet, und somit dert Reiter gewechselt werden soll
				maxStepsRight=IDC_BUTTON30-buttonID;
				maxStepsLeft=buttonID-IDC_BUTTON21;
				//der aktuell ausgewählte Reiter
				tab = tabControl.GetCurSel();
				//Neuer Reiter wird ermittelt und ausgewählt
				if(tab>=0 && tab<tabCount)
                    tabControl.SetCurSel(tab+1);
				//neuer ausgewählter Reiter
				tab = tabControl.GetCurSel();
				updateButtons();
				
				//Nachdem der neue Reiter ausgewählt ist, wird noch der Fokus auf einen neuen Button gesetzt
				//Abfrage ob der Button direkt unter dem momentan ausgewählten noch frei ist
				if(numbersTemp[buttonID-IDC_BUTTON01-19+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					arrayButtonControl[buttonID-IDC_BUTTON01-20].SetFocus();
					return;
				}
				//wenn der Button unter dem aktuell ausgewählten nicht mehr frei ist
				else
				{
					//alle Buttons rechts von dem bereits vergebenen werden durchsucht, bis ein freier gefunden wurde
					int i;
					for(i=0; i<maxStepsRight;i++)
					{
						if(numbersTemp[buttonID-IDC_BUTTON01-19+tab*MAX_ZAHLENHAI_BUTTON+i+1]==FREE)
						{
							maxStepsRight=i;
							break;
						}
					}
					//alle Buttons links von dem breits vergebenen werden durchsuchr, bis ein freier gefunden wurde
					for(i=0; i<maxStepsLeft; i++)
					{
						if(numbersTemp[buttonID-IDC_BUTTON01-19+tab*MAX_ZAHLENHAI_BUTTON-i-1]==FREE)
						{
							maxStepsLeft=i;
							break;
						}
					}
					if(maxStepsRight>maxStepsLeft)
					{
						//Schritt nach links, wenn maxStepsLeft kleiner als maxStepsRight
						arrayButtonControl[buttonID-IDC_BUTTON01-20-maxStepsLeft-1].SetFocus();
					}
					else
					{
						//Schritt nach rechts, wenn maxStepsRight kleiner oder gleich maxStepsLeft
						arrayButtonControl[buttonID-IDC_BUTTON01-20+maxStepsRight+1].SetFocus();
					}
				}
			}
		}
		else
		{
			//Wenn der Benutzer die Pfeiltaste nach unten drückt und sich der Fokus auf einem Reiter befindet
			if(buttonID == IDC_TAB1)
			{
				//aktuell ausgewählter Reiter wird herausgefunden
				tab=tabControl.GetCurSel();
				//momentan dargestellter Zahlenbereich wird durchsucht
				for(int i = MAX_ZAHLENHAI_BUTTON*tab+1; i<=MAX_ZAHLENHAI_BUTTON*tab+MAX_ZAHLENHAI_BUTTON; i++)
				{
					//wenn eine freie Zahl gefunden wurde
					if(numbersTemp[i]==FREE)
					{
						//die erste freie Zahl die gefunden wurde erhält den Focus
						arrayButtonControl[i-tab*30-1].SetFocus();
						//Abbruch der for-Schleife
						i = MAX_ZAHLENHAI_BUTTON*tab+31;
					}
				}
			}
		}
	}
}

//Die Funktion findet den nächstegelegensten freien Button in der nächst höheren Zeile und legt den Focus auf diesen
void CMFCZahlenHaiDlg::nextFreeButtonAbove(int buttonID, int maxStepsLeft, int maxStepsRight)
{
	int tab = tabControl.GetCurSel();
	int *numbersTemp=hai.getNumbers();

	int i;
	for(i=0; i<maxStepsLeft; i++)
	{
		//-i-1, da i bei 0 anfängt zu zählen
		if(numbersTemp[buttonID-IDC_BUTTON01-9+tab*MAX_ZAHLENHAI_BUTTON - i-1] == FREE)
		{
			maxStepsLeft=i;					                            
			break;
		}
	}
	for(i=0; i<maxStepsRight; i++)
	{
		//+i+1, da i bei 0 anfängt zu zählen
		if(numbersTemp[buttonID-IDC_BUTTON01-9+tab*MAX_ZAHLENHAI_BUTTON + i+1] == FREE)
		{
			maxStepsRight=i;					                            
			break;
		}
	}

	//es wird verglichen in welcher Richtung eher ein feier Button zufinden ist
	if(maxStepsLeft>maxStepsRight)
	{
		//Schritt nach rechts, wenn maxStepsRight kleiner als maxStepsLeft
		arrayButtonControl[buttonID-IDC_BUTTON01-10+maxStepsRight+1].SetFocus();
	}
	else
	{
		//Schritt nach links, wenn maxStepsLeft kleiner oder gleich maxStepsRight
		arrayButtonControl[buttonID-IDC_BUTTON01-10-maxStepsLeft-1].SetFocus();
	}
}
//Die Funktion findet den nächstegelegensten freien Button in der nächst niedrigeren/unteren Zeile und legt den Focus auf diesen
void CMFCZahlenHaiDlg::nextFreeButtonBelow(int buttonID, int maxStepsLeft, int maxStepsRight)
{
	int tab=tabControl.GetCurSel();
	int *numbersTemp=hai.getNumbers();

	int i;
	for(i=0; i<maxStepsLeft; i++)
	{
		//-i-1, da i bei 0 anfängt zu zählen
		if(numbersTemp[buttonID-IDC_BUTTON01+11+tab*MAX_ZAHLENHAI_BUTTON-i-1]==FREE)
		{
			maxStepsLeft=i;
			break;
		}
	}
	for(i=0; i<maxStepsRight; i++)
	{
		//+i+1, da i bei 0 anfängt zu zählen
		if(numbersTemp[buttonID-IDC_BUTTON01+11+tab*MAX_ZAHLENHAI_BUTTON+i+1]==FREE)
		{
			maxStepsRight=i;
			break;
		}
	}

	//es wird verglichen, in welcher Richtung eher ein freier Button zu finden  ist
	if(maxStepsRight > maxStepsLeft)
	{
		//Schritt nach links, wenn maxStepsLeft kleiner ist als maxStepsRight
		arrayButtonControl[buttonID-IDC_BUTTON01+10-maxStepsLeft-1].SetFocus();
	}
	else
	{
		//Schritt nach links, wenn maxStepsRight kleiner oder gleich maxStepsLeft
		arrayButtonControl[buttonID-IDC_BUTTON01+10+maxStepsRight+1].SetFocus();
	}
}

void CMFCZahlenHaiDlg::WinHelp(DWORD dwData, UINT nCmd)
{
	execWinHelp();
}

int CMFCZahlenHaiDlg::readRegistry()
{
	//Läuft so nicht unter dem VC++ 6.0 Compiler
	optionenSetting.LoadString(IDS_REG_TRUE);
	toolTipSetting.LoadString(IDS_REG_TRUE);
	int regUpperLimit;
	
	//Die Einstellungen der Optionen werden aus der Registry geladen
	//TODO: kommentieren
	ULONG strLength = 128;
	char valueName[128], valuePlayer[128], valueOptionen[128], valueToolTips[128], valueNumber[128];

	int returnKey = regKey.Open(HKEY_CURRENT_USER,"Software\\Zahlenhai\\Settings",KEY_READ);
	if(returnKey == ERROR_SUCCESS)
	{
		regKey.Open(HKEY_CURRENT_USER, "Software\\Zahlenhai\\Settings",KEY_ALL_ACCESS);
		strcpy(valueName, "OptionenSettings");
		regKey.QueryStringValue(valueName,valueOptionen, &strLength);
        optionenSetting=valueOptionen;
		
		strLength = 128;
		strcpy(valueName,"ToolTipSettings");
		regKey.QueryStringValue(valueName,valueToolTips, &strLength);
		toolTipSetting = valueToolTips;
		
		if(toolTipSetting=="true")
			optionen.showToolTips=true;
		else
			optionen.showToolTips=false;

		strLength = 128;
		strcpy(valueName, "Spielername"); 
		regKey.QueryStringValue(valueName, valuePlayer, &strLength);
		optionen.playername=valuePlayer;

		strLength = 128;
		strcpy(valueName, "Startnummer");
		regKey.QueryStringValue(valueName, valueNumber, &strLength);
		startNumberSetting=valueNumber;
		if(startNumberSetting=="true")
		{
			optionen.showStartNumber=true;
			strLength = 128;
			strcpy(valueName, "Startzahl"); 
			regKey.QueryStringValue(valueName, valueNumber, &strLength);
			regUpperLimit=atoi(valueNumber);
			regKey.Close();
		}
		else
		{
			optionen.showStartNumber=false;
			regUpperLimit=20;
		}

		if(optionenSetting=="true")
		{
			optionen.showOption=true;
		}
		else
		{
			optionen.showOption=false;
			optionen.playername="";
		}
	}
	else
	{
		regUpperLimit=20;
	}

	optionen.optionenUpperLimit = regUpperLimit;

	return regUpperLimit;

	//Andere Variante
	//regKey.QueryStringValue(valueName, valueNumber, &strLength);
}

void CMFCZahlenHaiDlg::writeRegistry()
{
	//Läuft so nicht unter dem VC++ 6.0 Compiler

	// 1. Stelle sicher, dass ein registry key existiert
	char valueName[128];
	char charUpperLimit[128];
	int regUpperLimit = hai.getUpperLimit();
	if(regKey.Open(HKEY_CURRENT_USER,"Software\\Zahlenhai\\Settings",KEY_WRITE)== ERROR_FILE_NOT_FOUND)
	{
		HKEY hKey;
		RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Zahlenhai\\Settings", 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS | KEY_WRITE | KEY_READ, NULL, &hKey, NULL);
	}
	else
		regKey.Close();


	// 2. bereite persistente Optionen vor
	if(optionen.showOption==false)
		optionenSetting="false";
	else
		optionenSetting="true";

	if(optionen.showToolTips==false)
		toolTipSetting="false";
	else
		toolTipSetting="true";

	if(optionen.showStartNumber==false)
		startNumberSetting="false";
	else
		startNumberSetting="true";

	// 3. schreibe persistente Optionen
	
	regKey.Open(HKEY_CURRENT_USER, "Software\\Zahlenhai\\Settings", KEY_ALL_ACCESS);
	
	strcpy(valueName,"OptionenSettings");
	regKey.SetStringValue(valueName, optionenSetting);
	strcpy(valueName,"ToolTipSettings");
	regKey.SetStringValue(valueName, toolTipSetting);
	strcpy(valueName,"Spielername");
	regKey.SetStringValue(valueName, optionen.playername);
	strcpy(valueName, "Startnummer");
	regKey.SetStringValue(valueName, startNumberSetting);
	strcpy(valueName,"Startzahl");
	regKey.SetStringValue(valueName, _itoa(regUpperLimit,charUpperLimit,10));
	
	regKey.Close();

	//Andere Variante
	//regKey.SetStringValue(valueName, itoa(regUpperLimit,charUpperLimit,10),REG_SZ);
}

void CMFCZahlenHaiDlg::OnBnClickedButtonHelp()
{
	execWinHelp();
}

void CMFCZahlenHaiDlg::execWinHelp()
{
	CString exePathHelp=exePath;
	CString helpFile="";
	helpFile.LoadString(IDS_HELP_FILE);
		
	int pos = exePathHelp.ReverseFind( '\\'); // FIXME --> Thomas
	exePathHelp = exePathHelp.Mid(0, pos+1);  // FIxme ...
	int pos1 = exePathHelp.Find("\"");		// FIXME --> Thomas
	if (!pos1) exePathHelp.Delete(0);
	
	exePathHelp+=helpFile;

	//HH_DISPLAY_TOPIC durch HH_HELP_CONTEXT austauschen
	::HtmlHelp(this->m_hWnd, exePathHelp,HH_DISPLAY_TOPIC, NULL);

}
void CMFCZahlenHaiDlg::OnBnClickedButtonFinish()
{
	//Diese Funktion soll hinter der Tastenkombination Strg+Shift+F liegen.
	//Der Zahlenhai soll alle anderen Zahlen bekommen-> allerdings nur als Test
	
	updatePoints();
	updateButtons();
	
	int *numbersTemp = hai.getNumbers();
	int upperLimit=hai.getUpperLimit();
	
	for(int i=1; i<=upperLimit; i++)
	{
		if(numbersTemp[i]==FREE)
			numbersTemp[i]=COMPUTER;

		hai.startRound(i);
		CSetList(i);
	}

	updatePoints();
	updateButtons();
	
}

void CMFCZahlenHaiDlg::createUndoRedo()
{
   	delete []undoRedo;

	undoRedo = new int[hai.getUpperLimit()+1];

	ASSERT(hai.getCurrentRound()==0);

	for(int i=0; i< hai.getUpperLimit()+1; i++)
        undoRedo[i]=0;
}
void CMFCZahlenHaiDlg::OnBnClickedButtonUndo()
{
	ASSERT(hai.getCurrentRound()!=0);
	Invalidate(false);
	showWinner=0;
    ListControl.DeleteItem(hai.getCurrentRound()-1);
	int lastRound = hai.getCurrentRound()-1;

	hai.init(hai.getUpperLimit());
	int value=0;

	for(int i=0; i<lastRound; i++)
	{
       value=undoRedo[i];
	   hai.startRound(value);
	}

	if(hai.getCurrentRound()==0)
		((CEdit*)GetDlgItem(IDC_BUTTON_UNDO))->EnableWindow(false);
		
	updatePoints();
	updateButtons();

	((CEdit*)GetDlgItem(IDC_BUTTON_REDO))->EnableWindow(true);
}

void CMFCZahlenHaiDlg::OnBnClickedButtonRedo()
{
	((CEdit*)GetDlgItem(IDC_BUTTON_UNDO))->EnableWindow(true);
	
	int value;
	if(undoRedo[hai.getCurrentRound()!=0])
	{
	   value=undoRedo[hai.getCurrentRound()];
	   hai.startRound(value);
	   CSetList(value);
	}

	updatePoints();
	updateButtons();
	
	if(undoRedo[hai.getCurrentRound()]==0)
		((CEdit*)GetDlgItem(IDC_BUTTON_REDO))->EnableWindow(false);
}

void CMFCZahlenHaiDlg::OnBnClickedButtonSwitchStyle()
{
	if(arrayButtonControl[1].GetButtonStyle()!=BS_OWNERDRAW)
	{
		for(int i=0; i<MAX_ZAHLENHAI_BUTTON; i++)
        arrayButtonControl[i].SetButtonStyle(BS_OWNERDRAW);

		shellBoxText.LoadString(IDS_SHELL_GROUP_BOX);
		CString shellGroupBox="";
		shellGroupBox.LoadString(IDS_SHELL_GROUP_BOX);
		muschelfeld.SetWindowText(shellGroupBox);
	
		updateButtons();	
	}
	else
	{	
		for(int i=0; i<MAX_ZAHLENHAI_BUTTON; i++)
		{
			arrayButtonControl[i].SetButtonStyle(BS_CENTER);
			arrayButtonControl[i].SetFont(&fontNormalButton,1);
		}

		shellBoxText.LoadString(IDS_NORMAL_GROUP_BOX);
		CString shellGroupBox="";
		shellGroupBox.LoadString(IDS_NORMAL_GROUP_BOX);
		muschelfeld.SetWindowText(shellGroupBox);
	}
}
void CMFCZahlenHaiDlg::OnTimer(UINT nIDEvent)
{
   char Buffer[100];
   
   sekunden++;
   if(sekunden==60){ minuten++; sekunden=0;}
   CString sek = _itoa(sekunden,Buffer,10);
   CString min = _itoa(minuten,Buffer,10);

   if(sek.GetLength()==1)
   {
	   sek.Insert(0,"0");
   }
   if(min.GetLength()==1)
   {
	   min.Insert(0,"0");
   }

   presTimer = min + ":" + sek;
	
   controlTimer.SetWindowText(presTimer);
   CDialog::OnTimer(nIDEvent);
}

BOOL CMFCZahlenHaiDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Fügen Sie hier Ihren Meldungsbehandlungscode ein, und/oder benutzen Sie den Standard.

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CMFCZahlenHaiDlg::OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
		if(a==2)
	{
		ListControl.SetColumnWidth(0,39);
		ListControl.SetColumnWidth(1,88);
		ListControl.SetColumnWidth(2,189);
		ListControl.SetColumnWidth(3,90);
		ListControl.SetColumnWidth(4,90);
		ListControl.SetColumnWidth(5,55);
	}
	else
		a++;
	*pResult = 0;
}

void CMFCZahlenHaiDlg::writeSaveGame()
{
	char Buffer[100];
	CStdioFile saveGame;
	CString filename="";
	CString save="";
	filename.LoadString(IDS_NUMBER_SHARK);
	filename+=".save";

	save+=_itoa(hai.getUpperLimit(),Buffer,10);
	save+=seperator;

	for(int i=0; i< hai.getCurrentRound(); i++)
	{
		save+=_itoa(undoRedo[i],Buffer,10);
		save+=seperator;
	}
	
	int openstatus;
	openstatus=saveGame.Open(filename,CFile::modeCreate|CFile::modeWrite);
	if(openstatus==0)
		return;
	
	saveGame.WriteString(save);
	saveGame.Close();
}

void CMFCZahlenHaiDlg::readSaveGame()
{
	bool stopLoading = false;
	
	CString seperator="";
	seperator.LoadString(IDS_SEPERATOR);
	
	CStdioFile saveGame;
	CString filename="";
	filename.LoadString(IDS_NUMBER_SHARK);
	filename+=".save";

	
	int openstatus = saveGame.Open(filename, CFile::modeRead);
	if(openstatus == 0) {
		// display an error message to the user
		CString loadFailure;
		loadFailure.Format(IDS_LOAD_FAILED, filename);
		AfxMessageBox(loadFailure, MB_ICONWARNING);
		return;
	}
  
	CString loadsave;
	saveGame.ReadString(loadsave);
	saveGame.Close();

	CString buffer="";
	int nmb=0;
	int i=0;
	int initNumber=0;
	int *nmbArray;
	
	initNumber = atoi(loadsave.Mid(0, loadsave.Find(seperator,0)));

	nmbArray = new int [initNumber];

	loadsave.Delete(0,loadsave.Find(seperator,0)+1);

	while(loadsave.Mid(0, loadsave.Find(seperator,0))!="")
	{
		buffer=loadsave.Mid(0, loadsave.Find(seperator,0));
		
		nmb = atoi(buffer);

		if(nmb < 1 || nmb > 9999 || nmb > initNumber)
		{
			stopLoading=true;	
			delete []nmbArray;
			CString loadFailure;
			loadFailure.Format(IDS_LOAD_FAILED, filename);
			AfxMessageBox(loadFailure, MB_ICONWARNING);
			return;
		}
		if(i<initNumber)
		{
			nmbArray[i]=nmb;
		}
		else
		{
			stopLoading=true;
			delete []nmbArray;
			CString loadFailure;
			loadFailure.Format(IDS_LOAD_FAILED, filename);
			AfxMessageBox(loadFailure, MB_ICONWARNING);
			return;
		}
		
		i++;		
		loadsave.Delete(0,loadsave.Find(seperator,0)+1);
	}

	if(stopLoading==false)
	{
		OnBnClickedButtonStartnew();
		
		//ListControl.DeleteAllItems();
		
		hai.init(initNumber);
		
		for(int j=0; j<i; j++)
		{
			hai.startRound(nmbArray[j]);
			CSetList(nmbArray[j]);
			undoRedo[j]=nmbArray[j];
		}
				
		((CEdit*)GetDlgItem(IDC_STATIC_LISTE))->ShowWindow(1);
		((CEdit*)GetDlgItem(IDC_BUTTON_UNDO))->EnableWindow(true);
		((CEdit*)GetDlgItem(IDC_STATIC_EINSTELLUNGEN))->ShowWindow(0);
		
		m_LedText.ShowWindow(1);
		ListControl.ShowWindow(1);
		haiListe.ShowWindow(0);
		updatePoints();
		
		updateTab();
		updateButtons();
		Invalidate(false);
	}

	delete []nmbArray;
}

void CMFCZahlenHaiDlg::OnBnClickedButtonLoad()
{
	readSaveGame();
}

void CMFCZahlenHaiDlg::OnBnClickedButtonSave()
{
	writeSaveGame();
}

void CMFCZahlenHaiDlg::calculationResult(int maxEndPoints, int upperLimit)
{
	int tempUpperLimit = upperLimit;
	int maxPts = maxEndPoints;
	
    if(maxPts != -1)
	{	
		CString result;
  		CString headline;
		
		headline.LoadString(IDS_MAX_POINTS_HEADLINE);

		CString sepTempUpperLimit = hai.setSeperator(tempUpperLimit);
		CString sepMaxPts = hai.setSeperator(maxPts);
		if(tempUpperLimit <= MAX_POINTS_CALC)
			result.Format(IDS_MAX_POINTS_NEW_2, sepTempUpperLimit, sepMaxPts, hai.setSeperator(getTime()), hai.setSeperator(getNumberOfRounds()), hai.setSeperator(maxPrime(tempUpperLimit)), bestWay);	
		else
			result.Format(IDS_MAX_POINTS_NEW, sepTempUpperLimit, sepMaxPts, hai.setSeperator(getTime()), hai.setSeperator(getNumberOfRounds()), hai.setSeperator(maxPrime(tempUpperLimit)), bestWay);
		
		MessageBox(result,headline, MB_ICONINFORMATION);
	}
}