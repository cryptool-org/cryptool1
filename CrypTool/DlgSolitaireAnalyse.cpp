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

// DlgSolitaireAnalyse.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSolitaireAnalyse.h"
#include ".\dlgsolitaireanalyse.h"
#include "FileTools.h"
#include "DialogeMessage.h"
#include "CrypToolTools.h"


// CDlgSolitaireAnalyse-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgSolitaireAnalyse, CDialog)
CDlgSolitaireAnalyse::CDlgSolitaireAnalyse(char* infile, CString oldTitle,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSolitaireAnalyse::IDD, pParent)
	, kartenanzahl(51)
	, gefundenesDeck(_T(""))
	, vorgaben(0)
	, zwischendeck(_T(""))
	, Initialdeck(_T(""))
	, schluesselstrom(_T(""))
{
	kartenanzahlneu=kartenanzahl+3;
	myD = new Deck(kartenanzahlneu);
	zaehler=0;
	this->infile = infile;
	this->oldTitle = oldTitle;
	
	myD->readPlaintext(infile);
	myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
}

CDlgSolitaireAnalyse::~CDlgSolitaireAnalyse()
{
   delete myD;
}

void CDlgSolitaireAnalyse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_Kartenanzahl, kartenanzahl);
	DDX_Text(pDX, IDC_EDIT1, gefundenesDeck);
	DDX_Control(pDX, IDC_BUTTON9, but1);
	DDX_Control(pDX, IDC_BUTTON10, but2);
	DDX_Control(pDX, IDC_BUTTON11, but3);
	DDX_Control(pDX, IDC_BUTTON12, but4);
	DDX_Control(pDX, IDC_BUTTON13, but5);
	DDX_Control(pDX, IDC_BUTTON14, but6);
	DDX_Control(pDX, IDC_BUTTON15, but7);
	DDX_Control(pDX, IDC_BUTTON16, but8);
	DDX_Control(pDX, IDC_BUTTON17, but9);
	DDX_Control(pDX, IDC_BUTTON18, but10);
	DDX_Control(pDX, IDC_BUTTON19, but11);
	DDX_Control(pDX, IDC_BUTTON20, but12);
	DDX_Control(pDX, IDC_BUTTON21, but13);
	DDX_Control(pDX, IDC_BUTTON22, but14);
	DDX_Control(pDX, IDC_BUTTON23, but15);
	DDX_Control(pDX, IDC_BUTTON24, but16);
	DDX_Control(pDX, IDC_BUTTON25, but17);
	DDX_Control(pDX, IDC_BUTTON26, but18);
	DDX_Control(pDX, IDC_BUTTON27, but19);
	DDX_Control(pDX, IDC_BUTTON28, but20);
	DDX_Control(pDX, IDC_BUTTON29, but21);
	DDX_Control(pDX, IDC_BUTTON30, but22);
	DDX_Control(pDX, IDC_BUTTON31, but23);
	DDX_Control(pDX, IDC_BUTTON32, but24);
	DDX_Control(pDX, IDC_BUTTON33, but25);
	DDX_Control(pDX, IDC_BUTTON34, but26);
	DDX_Control(pDX, IDC_BUTTON35, but27);
	DDX_Control(pDX, IDC_BUTTON36, but28);
	DDX_Control(pDX, IDC_BUTTON37, but29);
	DDX_Control(pDX, IDC_BUTTON38, but30);
	DDX_Control(pDX, IDC_BUTTON39, but31);
	DDX_Control(pDX, IDC_BUTTON40, but32);
	DDX_Control(pDX, IDC_BUTTON41, but33);
	DDX_Control(pDX, IDC_BUTTON42, but34);
	DDX_Control(pDX, IDC_BUTTON43, but35);
	DDX_Control(pDX, IDC_BUTTON44, but36);
	DDX_Control(pDX, IDC_BUTTON45, but37);
	DDX_Control(pDX, IDC_BUTTON46, but38);
	DDX_Control(pDX, IDC_BUTTON47, but39);
	DDX_Control(pDX, IDC_BUTTON48, but40);
	DDX_Control(pDX, IDC_BUTTON49, but41);
	DDX_Control(pDX, IDC_BUTTON50, but42);
	DDX_Control(pDX, IDC_BUTTON51, but43);
	DDX_Control(pDX, IDC_BUTTON52, but44);
	DDX_Control(pDX, IDC_BUTTON53, but45);
	DDX_Control(pDX, IDC_BUTTON54, but46);
	DDX_Control(pDX, IDC_BUTTON55, but47);
	DDX_Control(pDX, IDC_BUTTON56, but48);
	DDX_Control(pDX, IDC_BUTTON57, but49);
	DDX_Control(pDX, IDC_BUTTON58, but50);
	DDX_Control(pDX, IDC_BUTTON59, but51);
	DDX_Control(pDX, IDC_BUTTON60, but52);
	DDX_Control(pDX, IDC_BUTTON61, but53);
	DDX_Control(pDX, IDC_BUTTON62, but4054);
	DDX_Control(pDX, IDC_BUTTON63, m_Reset);
	DDX_Control(pDX, IDC_BUTTON1, vorne);
	DDX_Control(pDX, IDC_BUTTON2, hinten);
	DDX_Control(pDX, IDC_BUTTON3, waehlen);
	DDX_Text(pDX, IDC_EDIT132, zwischendeck);
	DDX_Text(pDX, IDC_EDIT2, Initialdeck);
	//DDX_Control(pDX, IDC_BUTTON4, starten);
	//DDX_Control(pDX, IDC_BUTTON5, man_hinten);
	DDX_Control(pDX, IDC_BUTTON4, schluesselerzeugen);
	DDX_Control(pDX, IDC_EDIT3, schluessel);
	DDX_Text(pDX, IDC_EDIT3, schluesselstrom);
	DDX_Control(pDX, IDOK, entschluesseln);
	DDX_Control(pDX, IDC_Kartenanzahl, m_kartenanzahl);
}
BOOL CDlgSolitaireAnalyse::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Leere Nachricht ist nicht erlaubt
	myD->readPlaintext(infile);
	if (myD->plaintext=="")
	{
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_1,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);	
		this->EndDialog(1);
	}
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

BEGIN_MESSAGE_MAP(CDlgSolitaireAnalyse, CDialog)
	ON_CBN_SELCHANGE(IDC_Kartenanzahl, OnCbnSelchangeKartenanzahl)
	ON_BN_CLICKED(IDC_BUTTON40, OnBnClickedButton40)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON29, OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON30, OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON31, OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON32, OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON33, OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON34, OnBnClickedButton34)
	ON_BN_CLICKED(IDC_BUTTON35, OnBnClickedButton35)
	ON_BN_CLICKED(IDC_BUTTON36, OnBnClickedButton36)
	ON_BN_CLICKED(IDC_BUTTON37, OnBnClickedButton37)
	ON_BN_CLICKED(IDC_BUTTON38, OnBnClickedButton38)
	ON_BN_CLICKED(IDC_BUTTON39, OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON41, OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON42, OnBnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON43, OnBnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON44, OnBnClickedButton44)
	ON_BN_CLICKED(IDC_BUTTON45, OnBnClickedButton45)
	ON_BN_CLICKED(IDC_BUTTON46, OnBnClickedButton46)
	ON_BN_CLICKED(IDC_BUTTON47, OnBnClickedButton47)
	ON_BN_CLICKED(IDC_BUTTON48, OnBnClickedButton48)
	ON_BN_CLICKED(IDC_BUTTON49, OnBnClickedButton49)
	ON_BN_CLICKED(IDC_BUTTON50, OnBnClickedButton50)
	ON_BN_CLICKED(IDC_BUTTON51, OnBnClickedButton51)
	ON_BN_CLICKED(IDC_BUTTON52, OnBnClickedButton52)
	ON_BN_CLICKED(IDC_BUTTON53, OnBnClickedButton53)
	ON_BN_CLICKED(IDC_BUTTON54, OnBnClickedButton54)
	ON_BN_CLICKED(IDC_BUTTON55, OnBnClickedButton55)
	ON_BN_CLICKED(IDC_BUTTON56, OnBnClickedButton56)
	ON_BN_CLICKED(IDC_BUTTON57, OnBnClickedButton57)
	ON_BN_CLICKED(IDC_BUTTON58, OnBnClickedButton58)
	ON_BN_CLICKED(IDC_BUTTON59, OnBnClickedButton59)
	ON_BN_CLICKED(IDC_BUTTON60, OnBnClickedButton60)
	ON_BN_CLICKED(IDC_BUTTON61, OnBnClickedButton61)
	ON_BN_CLICKED(IDC_BUTTON62, OnBnClickedButton62)
	ON_BN_CLICKED(IDC_BUTTON63, OnBnClickedButton63)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
   ON_EN_CHANGE(IDC_EDIT132, OnEnChangeEdit132)
   ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
   ON_BN_CLICKED(IDOK, OnBnClickedOk)
   ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
   ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
END_MESSAGE_MAP()


// CDlgSolitaireAnalyse-Meldungshandler
//Buttons zur Deckvorbelegung
void CDlgSolitaireAnalyse::OnCbnSelchangeKartenanzahl()
{
	UpdateData(true);
	kartenanzahlneu=kartenanzahl+3;

	enablebut(true);
	vorgabesetzen();
	//deckart="nach Vorgabe";
	gefundenesDeck="";
	Initialdeck="";
	zwischendeck="";
	schluesselstrom="";
	hinten.EnableWindow(false);
	vorne.EnableWindow(false);
	waehlen.EnableWindow(false);
	entschluesseln.EnableWindow(false);
	schluesselerzeugen.EnableWindow(false);
	
	zaehler=0;
	
	
	myD = new Deck(kartenanzahlneu);
	
	UpdateData(false);
}

void CDlgSolitaireAnalyse::DoCard( int k, CButton &button )
{
	if ( k > kartenanzahlneu )
		Message(IDS_SOLITAIRE_MESSAGE_5, MB_ICONSTOP);
	else
	{
		myD->deck[zaehler]=(char)k;
		gefundenesDeck= myD->getDeckChar(zaehler+1);
		zaehler++;
		button.EnableWindow(false);
		UpdateData(false);

		if(zaehler >= kartenanzahlneu)
		{
			hinten.EnableWindow(true);
			vorne.EnableWindow(true);
			waehlen.EnableWindow(true);
			Message(IDS_SOLITAIRE_MESSAGE_6, MB_ICONINFORMATION);
		}
	}
}

void CDlgSolitaireAnalyse::OnBnClickedButton9()  {	DoCard(1,  but1); }
void CDlgSolitaireAnalyse::OnBnClickedButton10() {	DoCard(2,  but2); }
void CDlgSolitaireAnalyse::OnBnClickedButton11() {	DoCard(3,  but3); }
void CDlgSolitaireAnalyse::OnBnClickedButton12() {	DoCard(4,  but4); }
void CDlgSolitaireAnalyse::OnBnClickedButton13() {	DoCard(5,  but5); }
void CDlgSolitaireAnalyse::OnBnClickedButton14() {	DoCard(6,  but6); }
void CDlgSolitaireAnalyse::OnBnClickedButton15() {	DoCard(7,  but7); }
void CDlgSolitaireAnalyse::OnBnClickedButton16() {	DoCard(8,  but8); }
void CDlgSolitaireAnalyse::OnBnClickedButton17() {	DoCard(9,  but9); }
void CDlgSolitaireAnalyse::OnBnClickedButton18() {	DoCard(10, but10); }
void CDlgSolitaireAnalyse::OnBnClickedButton19() {	DoCard(11, but11); }
void CDlgSolitaireAnalyse::OnBnClickedButton20() {	DoCard(12, but12); }
void CDlgSolitaireAnalyse::OnBnClickedButton21() {	DoCard(13, but13); }
void CDlgSolitaireAnalyse::OnBnClickedButton22() {	DoCard(14, but14); }
void CDlgSolitaireAnalyse::OnBnClickedButton23() {	DoCard(15, but15); }
void CDlgSolitaireAnalyse::OnBnClickedButton24() {	DoCard(16, but16); }
void CDlgSolitaireAnalyse::OnBnClickedButton25() {	DoCard(17, but17); }
void CDlgSolitaireAnalyse::OnBnClickedButton26() {	DoCard(18, but18); }
void CDlgSolitaireAnalyse::OnBnClickedButton27() {	DoCard(19, but19); }
void CDlgSolitaireAnalyse::OnBnClickedButton28() {	DoCard(20, but20); }
void CDlgSolitaireAnalyse::OnBnClickedButton29() {	DoCard(21, but21); }
void CDlgSolitaireAnalyse::OnBnClickedButton30() {	DoCard(22, but22); }
void CDlgSolitaireAnalyse::OnBnClickedButton31() {	DoCard(23, but23); }
void CDlgSolitaireAnalyse::OnBnClickedButton32() {	DoCard(24, but24); }
void CDlgSolitaireAnalyse::OnBnClickedButton33() {	DoCard(25, but25); }
void CDlgSolitaireAnalyse::OnBnClickedButton34() {	DoCard(26, but26); }
void CDlgSolitaireAnalyse::OnBnClickedButton35() {	DoCard(27, but27); }
void CDlgSolitaireAnalyse::OnBnClickedButton36() {	DoCard(28, but28); }
void CDlgSolitaireAnalyse::OnBnClickedButton37() {	DoCard(29, but29); }
void CDlgSolitaireAnalyse::OnBnClickedButton38() {	DoCard(30, but30); }
void CDlgSolitaireAnalyse::OnBnClickedButton39() {	DoCard(31, but31); }
void CDlgSolitaireAnalyse::OnBnClickedButton40() {	DoCard(32, but32); }
void CDlgSolitaireAnalyse::OnBnClickedButton41() {	DoCard(33, but33); }
void CDlgSolitaireAnalyse::OnBnClickedButton42() {	DoCard(34, but34); }
void CDlgSolitaireAnalyse::OnBnClickedButton43() {	DoCard(35, but35); }
void CDlgSolitaireAnalyse::OnBnClickedButton44() {	DoCard(36, but36); }
void CDlgSolitaireAnalyse::OnBnClickedButton45() {	DoCard(37, but37); }
void CDlgSolitaireAnalyse::OnBnClickedButton46() {	DoCard(38, but38); }
void CDlgSolitaireAnalyse::OnBnClickedButton47() {	DoCard(39, but39); }
void CDlgSolitaireAnalyse::OnBnClickedButton48() {	DoCard(40, but40); }
void CDlgSolitaireAnalyse::OnBnClickedButton49() {	DoCard(41, but41); }
void CDlgSolitaireAnalyse::OnBnClickedButton50() {	DoCard(42, but42); }
void CDlgSolitaireAnalyse::OnBnClickedButton51() {	DoCard(43, but43); }
void CDlgSolitaireAnalyse::OnBnClickedButton52() {	DoCard(44, but44); }
void CDlgSolitaireAnalyse::OnBnClickedButton53() {	DoCard(45, but45); }
void CDlgSolitaireAnalyse::OnBnClickedButton54() {	DoCard(46, but46); }
void CDlgSolitaireAnalyse::OnBnClickedButton55() {	DoCard(47, but47); }
void CDlgSolitaireAnalyse::OnBnClickedButton56() {	DoCard(48, but48); }
void CDlgSolitaireAnalyse::OnBnClickedButton57() {	DoCard(49, but49); }
void CDlgSolitaireAnalyse::OnBnClickedButton58() {	DoCard(50, but50); }
void CDlgSolitaireAnalyse::OnBnClickedButton59() {	DoCard(51, but51); }
void CDlgSolitaireAnalyse::OnBnClickedButton60() {	DoCard(52, but52); }
void CDlgSolitaireAnalyse::OnBnClickedButton61() {	DoCard(53, but53); }
void CDlgSolitaireAnalyse::OnBnClickedButton62() {	DoCard(54, but4054); }


//Ende --> Buttons zur Deckvorbelegung

void CDlgSolitaireAnalyse::enablebut(bool art)
{
	but1.EnableWindow(art);
	but2.EnableWindow(art);
	but3.EnableWindow(art);
	but4.EnableWindow(art);
	but5.EnableWindow(art);
	but6.EnableWindow(art);
	but7.EnableWindow(art);
	but8.EnableWindow(art);
	but9.EnableWindow(art);
	but10.EnableWindow(art);
	but11.EnableWindow(art);
	but12.EnableWindow(art);
	but13.EnableWindow(art);
	but14.EnableWindow(art);
	but15.EnableWindow(art);
	but16.EnableWindow(art);
	but17.EnableWindow(art);
	but18.EnableWindow(art);
	but19.EnableWindow(art);
	but20.EnableWindow(art);
	but21.EnableWindow(art);
	but22.EnableWindow(art);
	but23.EnableWindow(art);
	but24.EnableWindow(art);
	but25.EnableWindow(art);
	but26.EnableWindow(art);
	but27.EnableWindow(art);
	but28.EnableWindow(art);
	but29.EnableWindow(art);
	but30.EnableWindow(art);
	but31.EnableWindow(art);
	but32.EnableWindow(art);
	but33.EnableWindow(art);
	but34.EnableWindow(art);
	but35.EnableWindow(art);
	but36.EnableWindow(art);
	but37.EnableWindow(art);
	but38.EnableWindow(art);
	but39.EnableWindow(art);
	but40.EnableWindow(art);
	but41.EnableWindow(art);
	but42.EnableWindow(art);
	but43.EnableWindow(art);
	but44.EnableWindow(art);
	but45.EnableWindow(art);
	but46.EnableWindow(art);
	but47.EnableWindow(art);
	but48.EnableWindow(art);
	but49.EnableWindow(art);
	but50.EnableWindow(art);
	but51.EnableWindow(art);
	but52.EnableWindow(art);
	but53.EnableWindow(art);
	but4054.EnableWindow(art);
	m_Reset.EnableWindow(art);
	vorgabesetzen();
	UpdateData(false);
}

void CDlgSolitaireAnalyse::vorgabesetzen()
{
	if (kartenanzahlneu<54)but4054.EnableWindow(false);
	if (kartenanzahlneu<53)but53.EnableWindow(false);
	if (kartenanzahlneu<52)but52.EnableWindow(false);
	if (kartenanzahlneu<51)but51.EnableWindow(false);
	if (kartenanzahlneu<50)but50.EnableWindow(false);
	if (kartenanzahlneu<49)but49.EnableWindow(false);
	if (kartenanzahlneu<48)but48.EnableWindow(false);
	if (kartenanzahlneu<47)but47.EnableWindow(false);
	if (kartenanzahlneu<46)but46.EnableWindow(false);
	if (kartenanzahlneu<45)but45.EnableWindow(false);
	if (kartenanzahlneu<44)but44.EnableWindow(false);
	if (kartenanzahlneu<43)but43.EnableWindow(false);
	if (kartenanzahlneu<42)but42.EnableWindow(false);
	if (kartenanzahlneu<41)but41.EnableWindow(false);
	if (kartenanzahlneu<40)but40.EnableWindow(false);
	if (kartenanzahlneu<39)but39.EnableWindow(false);
	if (kartenanzahlneu<38)but38.EnableWindow(false);
	if (kartenanzahlneu<37)but37.EnableWindow(false);
	if (kartenanzahlneu<36)but36.EnableWindow(false);
	if (kartenanzahlneu<35)but35.EnableWindow(false);
	if (kartenanzahlneu<34)but34.EnableWindow(false);
	if (kartenanzahlneu<33)but33.EnableWindow(false);
	if (kartenanzahlneu<32)but32.EnableWindow(false);
	if (kartenanzahlneu<31)but31.EnableWindow(false);
	if (kartenanzahlneu<30)but30.EnableWindow(false);
	if (kartenanzahlneu<29)but29.EnableWindow(false);
	if (kartenanzahlneu<28)but28.EnableWindow(false);
	if (kartenanzahlneu<27)but27.EnableWindow(false);
	if (kartenanzahlneu<26)but26.EnableWindow(false);
	if (kartenanzahlneu<25)but25.EnableWindow(false);
	if (kartenanzahlneu<24)but24.EnableWindow(false);
	if (kartenanzahlneu<23)but23.EnableWindow(false);
	if (kartenanzahlneu<22)but22.EnableWindow(false);
	if (kartenanzahlneu<21)but21.EnableWindow(false);
	if (kartenanzahlneu<20)but20.EnableWindow(false);
	if (kartenanzahlneu<19)but19.EnableWindow(false);
	if (kartenanzahlneu<18)but18.EnableWindow(false);
	if (kartenanzahlneu<17)but17.EnableWindow(false);
	if (kartenanzahlneu<16)but16.EnableWindow(false);
	if (kartenanzahlneu<15)but15.EnableWindow(false);
	if (kartenanzahlneu<14)but14.EnableWindow(false);
	if (kartenanzahlneu<13)but13.EnableWindow(false);
	if (kartenanzahlneu<12)but12.EnableWindow(false);
	if (kartenanzahlneu<11)but11.EnableWindow(false);
	if (kartenanzahlneu<10)but10.EnableWindow(false);
	if (kartenanzahlneu<9)but9.EnableWindow(false);
	if (kartenanzahlneu<8)but8.EnableWindow(false);
	if (kartenanzahlneu<7)but7.EnableWindow(false);
	if (kartenanzahlneu<6)but6.EnableWindow(false);
	if (kartenanzahlneu<5)but5.EnableWindow(false);
	if (kartenanzahlneu<4)but4.EnableWindow(false);
}

void CDlgSolitaireAnalyse::OnBnClickedButton63()
{
	enablebut(true);
	vorgabesetzen();
	hinten.EnableWindow(false);
	vorne.EnableWindow(false);
	waehlen.EnableWindow(false);
	gefundenesDeck="";
	zwischendeck="";
	Initialdeck="";
	zaehler=0;
	UpdateData(false);
}

void CDlgSolitaireAnalyse::OnBnClickedButton1()
{
	myD->readPlaintext(infile);
	if(myD->plaintext.GetLength()>65535)
	{
		myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
	}

	int i =myD->plaintext.GetLength();
	for (i; i>0;i--)
	{
		myD->analysevorne();
		if(myD->pruefenullrunde()==true && i>1){i++;};	
	}

	hinten.EnableWindow(false);
	vorne.EnableWindow(false);
	waehlen.EnableWindow(false);
	zwischendeck=myD->getDeck();
	Initialdeck=myD->getDeck();
	schluesselerzeugen.EnableWindow(true);
	UpdateData(false);
	
}

void CDlgSolitaireAnalyse::OnBnClickedButton2()
{
	myD->readPlaintext(infile);
	if(myD->plaintext.GetLength()>65535)
	{
		myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
	}
	
	int i=myD->plaintext.GetLength();
	for (i; i>0;i--)
	{
		myD->analysehinten();
		if(myD->pruefenullrunde()==true && i>1){i++;};
	}

	hinten.EnableWindow(false);
	vorne.EnableWindow(false);
	waehlen.EnableWindow(false);
	zwischendeck=myD->getDeck();
	Initialdeck=myD->getDeck();
	schluesselerzeugen.EnableWindow(true);
	UpdateData(false);
}

void CDlgSolitaireAnalyse::OnBnClickedButton3()
{
	hinten.EnableWindow(false);
	vorne.EnableWindow(false);
	waehlen.EnableWindow(false);
	myD->readPlaintext(infile);
	if(myD->plaintext.GetLength()>65535)
	{
		myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
	}
	int i=myD->plaintext.GetLength(); 
	int tempa=6;
	for(i; i>0;i--)
	{
	myD->schritt4revers();
	myD->schritt3revers();

	if (myD->schritt2reversabfrage()==true)
	{
		zwischendeck=myD->getDeck();
		UpdateData(false);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_9,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_10,pc_str1,STR_LAENGE_STRING_TABLE);	
		tempa = MessageBox(pc_str, pc_str1, MB_ICONQUESTION | MB_YESNOCANCEL);
		if(tempa==6)
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->vorneeinordnenb();
			zwischendeck=myD->getDeck();
			UpdateData(false);
		}
		else {if(tempa==7)
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->hinteneinordnenb();
			zwischendeck=myD->getDeck();
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_7,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);	
		}
		else
		{
		UpdateData(true);
		m_kartenanzahl.EnableWindow(true);		
		gefundenesDeck="";
		zwischendeck="";
		Initialdeck="";
		schluesselstrom="";
		zaehler=0;
		enablebut(1);
		vorgabesetzen();
		hinten.EnableWindow(false);
		vorne.EnableWindow(false);
		waehlen.EnableWindow(false);
		entschluesseln.EnableWindow(false);
		schluesselerzeugen.EnableWindow(false);
		UpdateData(false);
		break;
		}}
		if(tempa==6 || tempa==7){
		zwischendeck=myD->getDeck();
		UpdateData(false);
		}
	};

	if (myD->schritt1reversabfrage()==true && tempa!=3)
	{
		zwischendeck=myD->getDeck();
		UpdateData(false);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_11,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_10,pc_str1,STR_LAENGE_STRING_TABLE);
		tempa=MessageBox(pc_str, pc_str1, MB_ICONQUESTION | MB_YESNOCANCEL);

		if(tempa==6)
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->vorneeinordnena();
			zwischendeck=myD->getDeck();
			UpdateData(false);
		}
		else if(tempa==7)
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->hinteneinordnena();
			zwischendeck=myD->getDeck();
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_8,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);	
		}
		else
		{
			UpdateData(true);
			m_kartenanzahl.EnableWindow(true);		
			gefundenesDeck="";
			zwischendeck="";
			Initialdeck="";
			schluesselstrom="";
			zaehler=0;
			enablebut(1);
			vorgabesetzen();
			hinten.EnableWindow(false);
			vorne.EnableWindow(false);
			waehlen.EnableWindow(false);
			entschluesseln.EnableWindow(false);
			schluesselerzeugen.EnableWindow(false);
			UpdateData(false);
			break;
		}

		if(tempa==6 || tempa==7){
		zwischendeck=myD->getDeck();
		UpdateData(false);
		}
		
	};
	if(tempa ==6 || tempa ==7){
	if(myD->pruefenullrunde()==true && i>1){i++;};
	zwischendeck=myD->getDeck();
	UpdateData(false);}
	
	
	}
	if(tempa ==6 || tempa ==7){
	Initialdeck=myD->getDeck();
	schluesselerzeugen.EnableWindow(true);
	UpdateData(false);
	}
}


void CDlgSolitaireAnalyse::OnEnChangeEdit132()
{
}

void CDlgSolitaireAnalyse::OnBnClickedButton4()
{
	myD->readPlaintext(infile);

	if(myD->plaintext.GetLength()>65535)
	{
		myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
	}

	for(int i=0;i<myD->plaintext.GetLength();i++)
	 {
		 myD->schritt1();
		 myD->schritt2();
		 myD->schritt3();
		 myD->schritt4();
		 myD->key[i]=myD->schritt5ohneJokerAusgabe();
	 }
	 schluesselerzeugen.EnableWindow(false);
	 schluesselstrom = myD->getKey();
	 entschluesseln.EnableWindow(true);
	 
	 UpdateData(false);
}

void CDlgSolitaireAnalyse::OnBnClickedOk()
{
	char outfile[256];
	myD->keyUmrechnen();
	myD->entschluesseln(myD->plaintext);
	GetTmpName(outfile,"cry",".txt");	
	myD->writeplaintext(outfile);
	OpenNewDoc(outfile,myD->getKey(),this->oldTitle,IDS_SOLITAIRE,true,1);
	this->EndDialog(1);
}

void CDlgSolitaireAnalyse::OnBnClickedButton5()
{
	UpdateData(true);
   CString csErr;
   int res = myD->loaddeck( "*.txt" );

   switch ( res ) {
      case 0:
         return;
      case 1:
         break;
      case -1:
         csErr.LoadStringA(IDS_SOLITAIRE_COULD_NOT_LOAD_DECK);
         MessageBox( csErr );
         return;
      case -2:
         csErr.LoadStringA(IDS_SOLITAIRE_COULD_NOT_LOAD_DECK);
         MessageBox( csErr );
         return;
   };
//   myD->readdeck( "LastFinaldeck" );
	kartenanzahl=myD->anzahl-3;
	kartenanzahlneu=kartenanzahl+3;
	gefundenesDeck=myD->getDeck();
	zwischendeck=gefundenesDeck;
	schluesselstrom="";
	Initialdeck="";
	enablebut(false);
	hinten.EnableWindow(true);
	vorne.EnableWindow(true);
	waehlen.EnableWindow(true);
	entschluesseln.EnableWindow(false);
	schluesselerzeugen.EnableWindow(false);
	m_kartenanzahl.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaireAnalyse::OnBnClickedButton6()
{
	UpdateData(true);
	m_kartenanzahl.EnableWindow(true);		
	gefundenesDeck="";
	zwischendeck="";
	Initialdeck="";
	schluesselstrom="";
	zaehler=0;
	enablebut(1);
	vorgabesetzen();
	hinten.EnableWindow(false);
	vorne.EnableWindow(false);
	waehlen.EnableWindow(false);
	entschluesseln.EnableWindow(false);
	schluesselerzeugen.EnableWindow(false);
	UpdateData(false);
}
