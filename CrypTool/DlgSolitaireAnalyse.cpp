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
#include "FileTools.h"
#include "CrypToolTools.h"


// CDlgSolitaireAnalyse-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgSolitaireAnalyse, CDialog)
CDlgSolitaireAnalyse::CDlgSolitaireAnalyse(char* infile, CString oldTitle,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSolitaireAnalyse::IDD, pParent)
	, kartenanzahl(54)
	, deckart(0)
	, gefundenesDeck(_T(""))
	, vorgaben(0)
	, zwischendeck(_T(""))
	, Initialdeck(_T(""))
	, schluesselstrom(_T(""))
{
	myD = new Deck(kartenanzahl);
	zaehler=0;
	this->infile = infile;
	this->oldTitle = oldTitle;

	
	myD->readPlaintext(infile);
	
	
	
}

CDlgSolitaireAnalyse::~CDlgSolitaireAnalyse()
{
}

void CDlgSolitaireAnalyse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_Kartenanzahl, kartenanzahl);
	DDX_CBIndex(pDX, IDC_COMBO2, deckart);
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
}
BOOL CDlgSolitaireAnalyse::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	myD->readPlaintext(infile);
	if ((myD->plaintext=="")||(myD->plaintext.GetLength()>15000))
	{
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_1,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		this->EndDialog(1);
		
	}
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

BEGIN_MESSAGE_MAP(CDlgSolitaireAnalyse, CDialog)
	ON_CBN_SELCHANGE(IDC_Kartenanzahl, OnCbnSelchangeKartenanzahl)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
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
//	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
//	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
ON_EN_CHANGE(IDC_EDIT132, OnEnChangeEdit132)
ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSolitaireAnalyse-Meldungshandler
//Buttons zur Deckvorbelegung
void CDlgSolitaireAnalyse::OnCbnSelchangeKartenanzahl()
{
	UpdateData(true);
	enablebut(true);
	vorgabesetzen();
	deckart=0;
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
	
	if (kartenanzahl<3)
	{
		 kartenanzahl=3;
		 myD = new Deck(kartenanzahl);
		 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_2,pc_str,STR_LAENGE_STRING_TABLE);
		 MessageBox(pc_str);	
	}
	else
	{
		 myD = new Deck(kartenanzahl);
	}
	UpdateData(false);
}

void CDlgSolitaireAnalyse::OnCbnSelchangeCombo2()
{
	UpdateData(true);
	zaehler=0;

	// Vorgabe
	if (deckart==0)
	{
		zaehler=0;
		//vorgabe="";
		enablebut(true);
		vorgabesetzen();
		gefundenesDeck="";
		zwischendeck="";
		Initialdeck="";
		schluesselstrom="";
		hinten.EnableWindow(false);
		vorne.EnableWindow(false);
		waehlen.EnableWindow(false);
		entschluesseln.EnableWindow(false);
		schluesselerzeugen.EnableWindow(false);
		zwischendeck="";
			
	}
	// Finales Deck Laden
	else if(deckart==1)
	{
		CString file = tempdir(FINALDECKFILE);
		if (!myD->abschlussdeckladen(file)) {
			fehlermelden(IDS_STRING_ERROR,IDS_CT_FILE_OPEN_ERROR,file);
			return;
		}
		kartenanzahl=myD->anzahl;
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
		
	}

	UpdateData(false);
}


void CDlgSolitaireAnalyse::OnBnClickedButton9()
{
	if(1>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);	
			 }
			 else{
			 myD->deck[zaehler]=(char)1;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but1.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton10()
{
	if(2>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)2;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but2.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton11()
{
	if(3>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)3;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but3.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton12()
{
	if(4>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)4;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but4.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton13()
{
	if(5>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)5;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but5.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton14()
{
	if(6>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)6;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but6.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton15()
{
	if(7>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)7;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but7.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton16()
{
	if(8>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)8;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but8.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton17()
{
	if(9>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)9;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but9.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton18()
{
	if(10>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)10;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but10.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton19()
{
	if(11>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)11;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but11.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton20()
{
	if(12>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)12;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but12.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton21()
{
	if(13>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)13;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but13.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton22()
{
	if(14>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)14;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but14.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton23()
{
	if(15>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)15;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but15.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton24()
{
	if(16>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)16;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but16.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton25()
{
	if(17>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)17;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but17.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton26()
{
	if(18>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)18;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but18.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton27()
{
	if(19>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)19;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but19.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton28()
{
	if(20>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)20;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but20.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton29()
{
	if(21>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)21;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but21.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton30()
{
	if(22>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)22;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but22.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton31()
{
	if(23>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)23;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but23.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton32()
{
	if(24>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)24;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but24.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton33()
{
	if(25>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)25;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but25.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton34()
{
	if(26>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)26;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but26.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton35()
{
	if(27>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)27;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but27.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton36()
{
	if(28>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)28;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but28.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton37()
{
	if(29>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)29;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but29.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton38()
{
	if(30>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)30;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but30.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton39()
{
	if(31>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)31;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but31.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton40()
{
	if(32>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)32;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but32.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton41()
{
	if(33>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)33;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but33.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton42()
{
	if(34>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)34;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but34.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton43()
{
	if(35>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)35;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but35.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton44()
{
	if(36>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)36;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but36.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton45()
{
	if(37>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)37;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but37.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton46()
{
	if(38>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)38;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but38.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton47()
{
	if(39>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)39;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but39.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton48()
{
	if(40>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)40;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but40.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton49()
{
	if(41>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)41;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but41.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton50()
{
	if(42>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)42;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but42.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton51()
{
	if(43>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)43;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but43.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton52()
{
	if(44>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)44;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but44.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton53()
{
	if(45>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)45;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but45.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton54()
{
	if(46>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)46;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but46.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton55()
{
	if(47>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)47;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but47.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton56()
{
	if(48>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)48;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but48.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton57()
{
	if(49>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)49;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but49.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton58()
{
	if(50>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)50;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but50.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton59()
{
	if(51>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)51;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but51.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton60()
{
	if(52>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)52;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but52.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton61()
{
	if(53>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)53;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but53.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}

void CDlgSolitaireAnalyse::OnBnClickedButton62()
{
	if(54>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)54;
			 gefundenesDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 but4054.EnableWindow(false);
			 UpdateData(false);
			 
			 if(zaehler >= kartenanzahl)
			 {
				hinten.EnableWindow(true);
				vorne.EnableWindow(true);
				waehlen.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_6,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 }
}
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
	UpdateData(false);
}

void CDlgSolitaireAnalyse::vorgabesetzen()
{
	if (kartenanzahl<54)but4054.EnableWindow(false);
	if (kartenanzahl<53)but53.EnableWindow(false);
	if (kartenanzahl<52)but52.EnableWindow(false);
	if (kartenanzahl<51)but51.EnableWindow(false);
	if (kartenanzahl<50)but50.EnableWindow(false);
	if (kartenanzahl<49)but49.EnableWindow(false);
	if (kartenanzahl<48)but48.EnableWindow(false);
	if (kartenanzahl<47)but47.EnableWindow(false);
	if (kartenanzahl<46)but46.EnableWindow(false);
	if (kartenanzahl<45)but45.EnableWindow(false);
	if (kartenanzahl<44)but44.EnableWindow(false);
	if (kartenanzahl<43)but43.EnableWindow(false);
	if (kartenanzahl<42)but42.EnableWindow(false);
	if (kartenanzahl<41)but41.EnableWindow(false);
	if (kartenanzahl<40)but40.EnableWindow(false);
	if (kartenanzahl<39)but39.EnableWindow(false);
	if (kartenanzahl<38)but38.EnableWindow(false);
	if (kartenanzahl<37)but37.EnableWindow(false);
	if (kartenanzahl<36)but36.EnableWindow(false);
	if (kartenanzahl<35)but35.EnableWindow(false);
	if (kartenanzahl<34)but34.EnableWindow(false);
	if (kartenanzahl<33)but33.EnableWindow(false);
	if (kartenanzahl<32)but32.EnableWindow(false);
	if (kartenanzahl<31)but31.EnableWindow(false);
	if (kartenanzahl<30)but30.EnableWindow(false);
	if (kartenanzahl<29)but29.EnableWindow(false);
	if (kartenanzahl<28)but28.EnableWindow(false);
	if (kartenanzahl<27)but27.EnableWindow(false);
	if (kartenanzahl<26)but26.EnableWindow(false);
	if (kartenanzahl<25)but25.EnableWindow(false);
	if (kartenanzahl<24)but24.EnableWindow(false);
	if (kartenanzahl<23)but23.EnableWindow(false);
	if (kartenanzahl<22)but22.EnableWindow(false);
	if (kartenanzahl<21)but21.EnableWindow(false);
	if (kartenanzahl<20)but20.EnableWindow(false);
	if (kartenanzahl<19)but19.EnableWindow(false);
	if (kartenanzahl<18)but18.EnableWindow(false);
	if (kartenanzahl<17)but17.EnableWindow(false);
	if (kartenanzahl<16)but16.EnableWindow(false);
	if (kartenanzahl<15)but15.EnableWindow(false);
	if (kartenanzahl<14)but14.EnableWindow(false);
	if (kartenanzahl<13)but13.EnableWindow(false);
	if (kartenanzahl<12)but12.EnableWindow(false);
	if (kartenanzahl<11)but11.EnableWindow(false);
	if (kartenanzahl<10)but10.EnableWindow(false);
	if (kartenanzahl<9)but9.EnableWindow(false);
	if (kartenanzahl<8)but8.EnableWindow(false);
	if (kartenanzahl<7)but7.EnableWindow(false);
	if (kartenanzahl<6)but6.EnableWindow(false);
	if (kartenanzahl<5)but5.EnableWindow(false);
	if (kartenanzahl<4)but4.EnableWindow(false);
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
	int i=myD->plaintext.GetLength(); 
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
		
		if(MessageBox(pc_str, pc_str1, MB_ICONQUESTION | MB_YESNO)==6)
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->vorneeinordnenb();
			zwischendeck=myD->getDeck();
			UpdateData(false);
		}
		else
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->hinteneinordnenb();
			zwischendeck=myD->getDeck();
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_7,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);	
		}
		
	
		
		UpdateData(false);
	};

	if (myD->schritt1reversabfrage()==true)
	{
		zwischendeck=myD->getDeck();
		UpdateData(false);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_11,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_10,pc_str1,STR_LAENGE_STRING_TABLE);


		if(MessageBox(pc_str, pc_str1, MB_ICONQUESTION | MB_YESNO)==6)
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->vorneeinordnena();
			zwischendeck=myD->getDeck();
			UpdateData(false);
		}
		else
		{
			zwischendeck=myD->getDeck();
			UpdateData(false);
			myD->hinteneinordnena();
			zwischendeck=myD->getDeck();
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_8,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);	
		}
		zwischendeck=myD->getDeck();
		UpdateData(false);
		
	};
	if(myD->pruefenullrunde()==true && i>1){i++;};
	zwischendeck=myD->getDeck();
	UpdateData(false);
	
	
	}
	Initialdeck=myD->getDeck();
	schluesselerzeugen.EnableWindow(true);
	UpdateData(false);
}





void CDlgSolitaireAnalyse::OnEnChangeEdit132()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie setzen den CDialog::OnInitDialog() außer Kraft.
	// Funktion und Aufruf CRichEditCtrl().SetEventMask()
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
}

void CDlgSolitaireAnalyse::OnBnClickedButton4()
{
	myD->readPlaintext(infile);
	for(int i=0;i<myD->plaintext.GetLength();i++)
			 {
			 myD->schritt1();
			 myD->schritt2();
			 myD->schritt3();
			 myD->schritt4();
			 myD->key[i]=myD->schritt5ohneJokerAusgabe();
			 }
			
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
