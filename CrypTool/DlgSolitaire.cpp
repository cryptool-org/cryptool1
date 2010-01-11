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

// DlgSolitaire.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSolitaire.h"
#include ".\dlgsolitaire.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "KeyRepository.h"
#include "DialogeMessage.h"
#include "assert.h"
#include <fstream>

using namespace std;

// CDlgSolitaire-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgSolitaire, CDialog)

CDlgSolitaire::CDlgSolitaire(char* _infile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSolitaire::IDD, pParent)
	, InitialDeck(_T(""))
	, InitialArt(_T(""))
	, m_passwort1(_T(""))
	, endDeck(_T(""))
	, key_edit(_T(""))
	, edit_zaehler_value(0)
	, edit_schl_zeichen(0)
	, infile(0)
	, in_buffer(0)
	, key_stream(0)
{
	infile = new char[strlen(_infile) +1];
	strcpy(infile, _infile);
}

CDlgSolitaire::~CDlgSolitaire()
{
	delete []infile;
	delete []in_buffer;
	delete []key_stream;
}

bool CDlgSolitaire::load_infile()
{
	ifstream i_file;
	in_buffer_size = 0;
	i_file.open( infile, ios::in || ios::binary );
	if ( i_file.is_open() )
	{	
		if ( !in_buffer  ) in_buffer  = new unsigned char[4000];
		if ( !key_stream ) key_stream = new unsigned char[4000];
		unsigned char c;
		while ( !i_file.eof() && in_buffer_size < 4000)
		{
			c = i_file.get();
			switch ( c ) {
				case '�':
				case '�':
					in_buffer[in_buffer_size++] = deck.get_char('A');
					c = 'E';
					break;
				case '�':
				case '�':
					in_buffer[in_buffer_size++] = deck.get_char('O');
					c = 'E';
					break;
				case '�':
				case '�':
					in_buffer[in_buffer_size++] = deck.get_char('O');
					c = 'E';
					break;
				case '�':
					in_buffer[in_buffer_size++] = deck.get_char('S');
					c = 'S';
					break;
				default:
					break;
			}
			if ( in_buffer_size >= 4000 )
				break;
			c = deck.get_char( c );
			if ( c ) 
				in_buffer[in_buffer_size++] = c;
		}
		key_stream_size = 0;
	
		if ( !i_file.eof() )
		{ // FIXME 
			LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_ZULANG,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str,"Solitaire Ver-/Entschl�sselung");
		}
		i_file.close();
		return true;
	}

	return false;
}


void CDlgSolitaire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, InitialDeck);
	DDX_CBString(pDX, IDC_COMBO2, InitialArt);
	DDX_Control(pDX, IDC_BUTTON9, vorgabe1);
	DDX_Control(pDX, IDC_BUTTON10, vorgabe2);
	DDX_Control(pDX, IDC_BUTTON11, vorgabe3);
	DDX_Control(pDX, IDC_BUTTON12, vorgabe4);
	DDX_Control(pDX, IDC_BUTTON13, vorgabe5);
	DDX_Control(pDX, IDC_BUTTON14, vorgabe6);
	DDX_Control(pDX, IDC_BUTTON15, vorgabe7);
	DDX_Control(pDX, IDC_BUTTON16, vorgabe8);
	DDX_Control(pDX, IDC_BUTTON17, vorgabe9);
	DDX_Control(pDX, IDC_BUTTON18, vorgabe10);
	DDX_Control(pDX, IDC_BUTTON19, vorgabe11);
	DDX_Control(pDX, IDC_BUTTON20, vorgabe12);
	DDX_Control(pDX, IDC_BUTTON21, vorgabe13);
	DDX_Control(pDX, IDC_BUTTON22, vorgabe14);
	DDX_Control(pDX, IDC_BUTTON23, vorgabe15);
	DDX_Control(pDX, IDC_BUTTON24, vorgabe16);
	DDX_Control(pDX, IDC_BUTTON25, vorgabe17);
	DDX_Control(pDX, IDC_BUTTON26, vorgabe18);
	DDX_Control(pDX, IDC_BUTTON27, vorgabe19);
	DDX_Control(pDX, IDC_BUTTON28, vorgabe20);
	DDX_Control(pDX, IDC_BUTTON29, vorgabe21);
	DDX_Control(pDX, IDC_BUTTON30, vorgabe22);
	DDX_Control(pDX, IDC_BUTTON31, vorgabe23);
	DDX_Control(pDX, IDC_BUTTON32, vorgabe24);
	DDX_Control(pDX, IDC_BUTTON33, vorgabe25);
	DDX_Control(pDX, IDC_BUTTON34, vorgabe26);
	DDX_Control(pDX, IDC_BUTTON35, vorgabe27);
	DDX_Control(pDX, IDC_BUTTON36, vorgabe28);
	DDX_Control(pDX, IDC_BUTTON37, vorgabe29);
	DDX_Control(pDX, IDC_BUTTON38, vorgabe30);
	DDX_Control(pDX, IDC_BUTTON39, vorgabe31);
	DDX_Control(pDX, IDC_BUTTON40, vorgabe32);
	DDX_Control(pDX, IDC_BUTTON41, vorgabe33);
	DDX_Control(pDX, IDC_BUTTON42, vorgabe34);
	DDX_Control(pDX, IDC_BUTTON43, vorgabe35);
	DDX_Control(pDX, IDC_BUTTON44, vorgabe36);
	DDX_Control(pDX, IDC_BUTTON45, vorgabe37);
	DDX_Control(pDX, IDC_BUTTON46, vorgabe38);
	DDX_Control(pDX, IDC_BUTTON47, vorgabe39);
	DDX_Control(pDX, IDC_BUTTON48, vorgabe40);
	DDX_Control(pDX, IDC_BUTTON49, vorgabe41);
	DDX_Control(pDX, IDC_BUTTON50, vorgabe42);
	DDX_Control(pDX, IDC_BUTTON51, vorgabe43);
	DDX_Control(pDX, IDC_BUTTON52, vorgabe44);
	DDX_Control(pDX, IDC_BUTTON53, vorgabe45);
	DDX_Control(pDX, IDC_BUTTON54, vorgabe46);
	DDX_Control(pDX, IDC_BUTTON55, vorgabe47);
	DDX_Control(pDX, IDC_BUTTON56, vorgabe48);
	DDX_Control(pDX, IDC_BUTTON57, vorgabe49);
	DDX_Control(pDX, IDC_BUTTON58, vorgabe50);
	DDX_Control(pDX, IDC_BUTTON59, vorgabe51);
	DDX_Control(pDX, IDC_BUTTON60, vorgabe52);
	DDX_Control(pDX, IDC_BUTTON61, vorgabe53);
	DDX_Control(pDX, IDC_BUTTON62, vorgabe54);
	DDX_Control(pDX, IDC_EDIT4, m_passwort);
	DDX_Text(pDX, IDC_EDIT4, m_passwort1);
	DDV_MaxChars(pDX, m_passwort1, 1024);
	DDX_Control(pDX, IDC_BUTTON1, m_passwort_button);
	DDX_Control(pDX, IDC_BUTTON63, m_reset_button);
	DDX_Control(pDX, IDC_BUTTON2, m_auto_button);
	DDX_Control(pDX, IDC_BUTTON3, m_manuell_button);
	DDX_Control(pDX, IDC_BUTTON4, m_schritt1);
	DDX_Control(pDX, IDC_BUTTON5, m_schritt2);
	DDX_Control(pDX, IDC_BUTTON6, m_schritt3);
	DDX_Control(pDX, IDC_BUTTON7, m_schritt4);
	DDX_Control(pDX, IDC_BUTTON8, m_schritt5);
	DDX_Text(pDX, IDC_EDIT2, endDeck);
	DDX_Text(pDX, IDC_EDIT3, key_edit);
	DDX_Control(pDX, IDC_BUTTON64, m_inispeichern);
	DDX_Control(pDX, IDC_BUTTON65, m_abschlussspeichern);
	DDX_Control(pDX, IDC_BUTTON66, verschl);
	DDX_Control(pDX, IDC_BUTTON68, entschl);
	DDX_Text(pDX, IDC_EDIT5, edit_zaehler_value);
	DDX_Control(pDX, IDC_BUTTON69, m_rest_generate);
	DDX_Control(pDX, IDC_EDIT5, m_edit_rest_generate);
	DDX_Control(pDX, IDC_BUTTON70, m_anderemischung);
	DDX_Text(pDX, IDC_EDIT6, edit_schl_zeichen);
	DDX_Control(pDX, IDC_EDIT6, m_edit_schl);
	DDX_Control(pDX, IDC_BUTTON72, m_keystream_save_button);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlComboSelCards);
	DDX_Control(pDX, IDC_Kartenanzahl, m_ctrlSelKartenanzahl);
}

void CDlgSolitaire::init()
{
	UpdateData(true);
	m_anderemischung.EnableWindow(false);
	m_passwort.EnableWindow(true);
	m_passwort_button.EnableWindow(true);
	m_abschlussspeichern.EnableWindow(false);
	m_inispeichern.EnableWindow(false);
	verschl.EnableWindow(false);
	entschl.EnableWindow(false);

	initdrei();

	long cards   = m_ctrlSelKartenanzahl.GetCurSel()+3;
	long variant = m_ctrlComboSelCards.GetCurSel();
	switch ( variant ) {
		case 0:
		case 1:
		case 2:
			deck.initalize(cards, variant, 0);
			enableVorgabe(false);
			if ( variant == 2 ) 
				m_anderemischung.EnableWindow(true);
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
	}
	deck.get_deck(InitialDeck);

	// FIXME 
	zaehler=0;
	m_edit_rest_generate.ShowWindow(0);
	m_edit_schl.ShowWindow(0);
	key_stream_size = 0;
	endDeck="";
	key_edit="";

	UpdateData(false);
}



BOOL CDlgSolitaire::OnInitDialog()
{
	CDialog::OnInitDialog();
	enableVorgabe(false);

	if (!load_infile())
	{
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_1,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);	
		this->EndDialog(1);
	}
	OnBnReInit();

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SOLITAIRE,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_PASTE_KEY,this));
	if ( IsKeyEmpty( Title ))
		m_Paste.EnableWindow(TRUE);
	else
		m_Paste.EnableWindow(FALSE);

	return TRUE;  // Geben Sie TRUE zur�ck, au�er ein Steuerelement soll den Fokus erhalten
}

BEGIN_MESSAGE_MAP(CDlgSolitaire, CDialog)
	ON_CBN_SELCHANGE(IDC_Kartenanzahl, OnCbnSelchangeKartenanzahl)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON61, OnBnClickedButton61)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedCryptStep1)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedCryptStep2)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedCryptStep3)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedCryptStep4)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedCryptStep5)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedDoCrypt)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedDoCryptSteps)
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
	ON_BN_CLICKED(IDC_BUTTON40, OnBnClickedButton40)
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
	ON_BN_CLICKED(IDC_BUTTON62, OnBnClickedButton62)
	ON_BN_CLICKED(IDC_BUTTON63, OnResetCardSettings)
	ON_EN_CHANGE(IDC_EDIT4, OnEnChangePassword)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedModifyDeckByPassword)
	ON_BN_CLICKED(IDC_BUTTON64, OnBnClickedSaveDeck)
	ON_BN_CLICKED(IDC_BUTTON65, OnBnClickedSaveFinalDeck)
	ON_BN_CLICKED(IDC_BUTTON67, OnBnCancel)
	ON_BN_CLICKED(IDC_BUTTON66, OnEncrypt)
	ON_BN_CLICKED(IDC_BUTTON68, OnDecrypt)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(IDC_BUTTON69, OnBnFinishCrypt)
	ON_BN_CLICKED(IDC_BUTTON71, OnBnReInit)
	ON_BN_CLICKED(IDC_BUTTON70, OnBnNewShuffle)
	ON_BN_CLICKED(IDC_BUTTON72, OnBnSaveKeyStream)
END_MESSAGE_MAP()

// BEGIN_DHTML_EVENT_MAP(CDlgSolitaire)
//	
// END_DHTML_EVENT_MAP()



void CDlgSolitaire::enableVorgabe(bool art)
{
	vorgabe1.EnableWindow(art);
	vorgabe2.EnableWindow(art);
	vorgabe3.EnableWindow(art);
	vorgabe4.EnableWindow(art);
	vorgabe5.EnableWindow(art);
	vorgabe6.EnableWindow(art);
	vorgabe7.EnableWindow(art);
	vorgabe8.EnableWindow(art);
	vorgabe9.EnableWindow(art);
	vorgabe10.EnableWindow(art);
	vorgabe11.EnableWindow(art);
	vorgabe12.EnableWindow(art);
	vorgabe13.EnableWindow(art);
	vorgabe14.EnableWindow(art);
	vorgabe15.EnableWindow(art);
	vorgabe16.EnableWindow(art);
	vorgabe17.EnableWindow(art);
	vorgabe18.EnableWindow(art);
	vorgabe19.EnableWindow(art);
	vorgabe20.EnableWindow(art);
	vorgabe21.EnableWindow(art);
	vorgabe22.EnableWindow(art);
	vorgabe23.EnableWindow(art);
	vorgabe24.EnableWindow(art);
	vorgabe25.EnableWindow(art);
	vorgabe26.EnableWindow(art);
	vorgabe27.EnableWindow(art);
	vorgabe28.EnableWindow(art);
	vorgabe29.EnableWindow(art);
	vorgabe30.EnableWindow(art);
	vorgabe31.EnableWindow(art);
	vorgabe32.EnableWindow(art);
	vorgabe33.EnableWindow(art);
	vorgabe34.EnableWindow(art);
	vorgabe35.EnableWindow(art);
	vorgabe36.EnableWindow(art);
	vorgabe37.EnableWindow(art);
	vorgabe38.EnableWindow(art);
	vorgabe39.EnableWindow(art);
	vorgabe40.EnableWindow(art);
	vorgabe41.EnableWindow(art);
	vorgabe42.EnableWindow(art);
	vorgabe43.EnableWindow(art);
	vorgabe44.EnableWindow(art);
	vorgabe45.EnableWindow(art);
	vorgabe46.EnableWindow(art);
	vorgabe47.EnableWindow(art);
	vorgabe48.EnableWindow(art);
	vorgabe49.EnableWindow(art);
	vorgabe50.EnableWindow(art);
	vorgabe51.EnableWindow(art);
	vorgabe52.EnableWindow(art);
	vorgabe53.EnableWindow(art);
	vorgabe54.EnableWindow(art);
	m_reset_button.EnableWindow(art);
	UpdateData(false);
}

void CDlgSolitaire::initdrei()
{
	m_auto_button.EnableWindow(true);
    m_manuell_button.EnableWindow(true);
	m_schritt1.EnableWindow(false);
	m_schritt2.EnableWindow(false);
	m_schritt3.EnableWindow(false);
	m_schritt4.EnableWindow(false);
	m_schritt5.EnableWindow(false);
}


void CDlgSolitaire::OnCbnSelchangeKartenanzahl()
{
	if ( 3 > m_ctrlComboSelCards.GetCurSel() )
		init();
}


void CDlgSolitaire::SetDeckSelectioMethod(CString &method)
{
	initdrei();
	endDeck="";
	key_edit="";
	verschl.EnableWindow(false);
	entschl.EnableWindow(false);
	zaehler=0;
	m_abschlussspeichern.EnableWindow(false);
	m_inispeichern.EnableWindow(false);
	
	m_passwort.EnableWindow(true);
	m_passwort_button.EnableWindow(true);

/*
	if(kartenanzahlneu<26)
	{
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);
	}

	int sel = m_ctrlComboSelCards.GetCurSel();
	switch ( sel )
	{
	case 3: // NACH VORGABE
		zaehler=0;
		vorgabe="";
		InitialDeck = "";
		enableVorgabe(true);
		m_anderemischung.EnableWindow(false);
		vorgabesetzen();
		m_manuell_button.EnableWindow(false);
		m_auto_button.EnableWindow(false);
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);
		break;
	case 4: // INITIALDECK LADEN
		myD->inideckladen();

		kartenanzahl=myD->anzahl-3;
		kartenanzahlneu=kartenanzahl+3;
		InitialDeck= myD->getDeck();
		enableVorgabe(false);
		m_anderemischung.EnableWindow(true);
		m_passwort.EnableWindow(true);
		m_passwort_button.EnableWindow(true);
		if(kartenanzahlneu<26)
		{
			m_passwort.EnableWindow(false);
			m_passwort_button.EnableWindow(false);
		}
		break;
	case 5: // ABSCHLUSSDECK LADEN
		myD->abschlussdeckladen();
		kartenanzahl=myD->anzahl-3;
		kartenanzahlneu=kartenanzahl+3;
		InitialDeck= myD->getDeck();
		enableVorgabe(false);
		m_anderemischung.EnableWindow(true);
		m_passwort.EnableWindow(true);
		m_passwort_button.EnableWindow(true);
		if(kartenanzahlneu<26)
		{
			m_passwort.EnableWindow(false);
			m_passwort_button.EnableWindow(false);
		}
		break;
	default:
		assert(false);
		break;
	}
*/
}

void CDlgSolitaire::OnCbnSelchangeCombo2()
{
	if ( 3 > m_ctrlComboSelCards.GetCurSel() )
		init();
#if 0
	UpdateData();
	SetDeckSelectioMethod(InitialArt);
	m_edit_rest_generate.ShowWindow(0);
	m_edit_schl.ShowWindow(0);
	UpdateData(FALSE);
#endif
}


/*Auswahl-Buttons 2-3*/
void CDlgSolitaire::OnBnClickedDoCrypt()
{
	m_auto_button.EnableWindow(false);
	m_manuell_button.EnableWindow(false);
	OnBnFinishCrypt();
}

void CDlgSolitaire::OnBnClickedDoCryptSteps()
{
	m_abschlussspeichern.EnableWindow(true);
	m_inispeichern.EnableWindow(true);
	m_auto_button.EnableWindow(false);
	m_passwort.EnableWindow(false);
	m_passwort_button.EnableWindow(false);
	m_edit_schl.ShowWindow(1);
	m_schritt1.EnableWindow(true);
	m_rest_generate.EnableWindow(true);
	m_edit_rest_generate.ShowWindow(1);
	edit_schl_zeichen = edit_zaehler_value = in_buffer_size;
	UpdateData(false);
}
/*Auswahl-Buttons 2-3*/



/*Schritt 1-5 Buttons*/
void CDlgSolitaire::OnBnClickedCryptStep1()
{
	deck.s1_swap_JA();
	deck.get_deck(endDeck);
	m_manuell_button.EnableWindow(false);
	m_schritt2.EnableWindow(true);
	m_schritt1.EnableWindow(false);
	m_rest_generate.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedCryptStep2()
{
	deck.s2_swap_JB();
	deck.get_deck(endDeck);
	m_manuell_button.EnableWindow(false);
	m_schritt3.EnableWindow(true);
	m_schritt2.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedCryptStep3()
{
	deck.s3_triple_cut();
	deck.get_deck(endDeck);
	m_manuell_button.EnableWindow(false);
	m_schritt4.EnableWindow(true);
	m_schritt3.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedCryptStep4()
{
	deck.s4_count_cut();
	deck.get_deck(endDeck);
	m_manuell_button.EnableWindow(false);
	m_schritt5.EnableWindow(true);
	m_schritt4.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedCryptStep5()
{
	unsigned char c = deck.s5_stream_char();
	if ( c )
	{
		if ( key_stream_size )
			key_edit += ',';
		char tmpStr[12];
		_itoa(c, tmpStr, 10);
		key_edit += CString(tmpStr);
		key_stream[key_stream_size++] = c;
		edit_zaehler_value--;
	}
	m_manuell_button.EnableWindow(false);
	m_schritt1.EnableWindow(true);
	m_schritt5.EnableWindow(false);
	m_rest_generate.EnableWindow(true);

	// FIXME: FINISHED
	if ( key_stream_size == in_buffer_size )
	{
		verschl.EnableWindow(true);
		entschl.EnableWindow(true);
		m_schritt1.EnableWindow(false);
		m_schritt2.EnableWindow(false);
		m_schritt3.EnableWindow(false);
		m_schritt4.EnableWindow(false);
		m_schritt5.EnableWindow(false);
		m_manuell_button.EnableWindow(false);
		m_rest_generate.EnableWindow(false);
		UpdateData(false);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_3,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);	
		m_keystream_save_button.EnableWindow(true);
	}
	UpdateData(false);
}
/*Schritt 1-5 Buttons*/



/*nach Vorgabe-Buttons 9-62*/
void CDlgSolitaire::DoCard( int k, CButton &button )
{
	long kartenanzahl = m_ctrlSelKartenanzahl.GetCurSel();
#if 0 // not needed ?
	if ( k > kartenanzahl )
		Message(IDS_SOLITAIRE_MESSAGE_5, MB_ICONSTOP);
	else
#endif
	{
		char tmpStr[12];
		_itoa(k, tmpStr, 10);
		vorgabe += CString(tmpStr) + ',';

		UpdateData(false);
		zaehler++;

		button.EnableWindow(false);
		if(zaehler >= kartenanzahl)
		{
			m_manuell_button.EnableWindow(true);
			m_auto_button.EnableWindow(true);
			Message(IDS_SOLITAIRE_MESSAGE_4, MB_ICONINFORMATION);
			m_anderemischung.EnableWindow(true); 
			m_reset_button.EnableWindow(false);
			if(kartenanzahl>25)
			{
				m_passwort.EnableWindow(true); 
				m_passwort_button.EnableWindow(true);
			} 
		}
		UpdateData(false);
	}
}


void CDlgSolitaire::OnBnClickedButton9()  {	DoCard(1,  vorgabe1); }
void CDlgSolitaire::OnBnClickedButton10() {	DoCard(2,  vorgabe2); }
void CDlgSolitaire::OnBnClickedButton11() { DoCard(3,  vorgabe3); }
void CDlgSolitaire::OnBnClickedButton12() {	DoCard(4,  vorgabe4); }
void CDlgSolitaire::OnBnClickedButton13() {	DoCard(5,  vorgabe5); }
void CDlgSolitaire::OnBnClickedButton14() {	DoCard(6,  vorgabe6); }
void CDlgSolitaire::OnBnClickedButton15() { DoCard(7,  vorgabe7); }
void CDlgSolitaire::OnBnClickedButton16() {	DoCard(8,  vorgabe8); }
void CDlgSolitaire::OnBnClickedButton17() { DoCard(9,  vorgabe9); }
void CDlgSolitaire::OnBnClickedButton18() { DoCard(10, vorgabe10); }
void CDlgSolitaire::OnBnClickedButton19() {	DoCard(11, vorgabe11); }
void CDlgSolitaire::OnBnClickedButton20() { DoCard(12, vorgabe12); }
void CDlgSolitaire::OnBnClickedButton21() {	DoCard(13, vorgabe13); }
void CDlgSolitaire::OnBnClickedButton22() {	DoCard(14, vorgabe14); }
void CDlgSolitaire::OnBnClickedButton23() { DoCard(15, vorgabe15); }
void CDlgSolitaire::OnBnClickedButton24() {	DoCard(16, vorgabe16); }
void CDlgSolitaire::OnBnClickedButton25() {	DoCard(17, vorgabe17); }
void CDlgSolitaire::OnBnClickedButton26() {	DoCard(18, vorgabe18); }
void CDlgSolitaire::OnBnClickedButton27() {	DoCard(19, vorgabe19); }
void CDlgSolitaire::OnBnClickedButton28() { DoCard(20, vorgabe20); }
void CDlgSolitaire::OnBnClickedButton29() {	DoCard(21, vorgabe21); }
void CDlgSolitaire::OnBnClickedButton30() {	DoCard(22, vorgabe22); }
void CDlgSolitaire::OnBnClickedButton31() {	DoCard(23, vorgabe23); }
void CDlgSolitaire::OnBnClickedButton32() {	DoCard(24, vorgabe24); }
void CDlgSolitaire::OnBnClickedButton33() {	DoCard(25, vorgabe25); }
void CDlgSolitaire::OnBnClickedButton34() {	DoCard(26, vorgabe26); }
void CDlgSolitaire::OnBnClickedButton35() {	DoCard(27, vorgabe27); }
void CDlgSolitaire::OnBnClickedButton36() {	DoCard(28, vorgabe28); }
void CDlgSolitaire::OnBnClickedButton37() {	DoCard(29, vorgabe29); }
void CDlgSolitaire::OnBnClickedButton38() {	DoCard(30, vorgabe30); }
void CDlgSolitaire::OnBnClickedButton39() { DoCard(31, vorgabe31); }
void CDlgSolitaire::OnBnClickedButton40() {	DoCard(32, vorgabe32); }
void CDlgSolitaire::OnBnClickedButton41() {	DoCard(33, vorgabe33); }
void CDlgSolitaire::OnBnClickedButton42() {	DoCard(34, vorgabe34); }
void CDlgSolitaire::OnBnClickedButton43() { DoCard(35, vorgabe35); }
void CDlgSolitaire::OnBnClickedButton44() {	DoCard(36, vorgabe36); }
void CDlgSolitaire::OnBnClickedButton45() {	DoCard(37, vorgabe37); }
void CDlgSolitaire::OnBnClickedButton46() {	DoCard(38, vorgabe38); }
void CDlgSolitaire::OnBnClickedButton47() {	DoCard(39, vorgabe39); }
void CDlgSolitaire::OnBnClickedButton48() {	DoCard(40, vorgabe40); }
void CDlgSolitaire::OnBnClickedButton49() {	DoCard(41, vorgabe41); }
void CDlgSolitaire::OnBnClickedButton50() {	DoCard(42, vorgabe42); }
void CDlgSolitaire::OnBnClickedButton51() {	DoCard(43, vorgabe43); }
void CDlgSolitaire::OnBnClickedButton52() {	DoCard(44, vorgabe44); }
void CDlgSolitaire::OnBnClickedButton53() {	DoCard(45, vorgabe45); }
void CDlgSolitaire::OnBnClickedButton54() {	DoCard(46, vorgabe46); }
void CDlgSolitaire::OnBnClickedButton55() {	DoCard(47, vorgabe47); }
void CDlgSolitaire::OnBnClickedButton56() {	DoCard(48, vorgabe48); }
void CDlgSolitaire::OnBnClickedButton57() {	DoCard(49, vorgabe49); }
void CDlgSolitaire::OnBnClickedButton58() {	DoCard(50, vorgabe50); }
void CDlgSolitaire::OnBnClickedButton59() {	DoCard(51, vorgabe51); }
void CDlgSolitaire::OnBnClickedButton60() {	DoCard(52, vorgabe52); }
void CDlgSolitaire::OnBnClickedButton61() {	DoCard(53, vorgabe53); }
void CDlgSolitaire::OnBnClickedButton62() {	DoCard(54, vorgabe54); }


/*nach Vorgabe-Buttons 9-62*/
void CDlgSolitaire::OnResetCardSettings()
{
	zaehler=0;
	InitialDeck="";
	endDeck="";
	vorgabe="";
	m_anderemischung.EnableWindow(false); 
	UpdateData(false);
	vorgabe1.EnableWindow(true);
	vorgabe2.EnableWindow(true);
	vorgabe3.EnableWindow(true);
	vorgabe4.EnableWindow(true);
	vorgabe5.EnableWindow(true);
	vorgabe6.EnableWindow(true);
	vorgabe7.EnableWindow(true);
	vorgabe8.EnableWindow(true);
	vorgabe9.EnableWindow(true);
	vorgabe10.EnableWindow(true);
	vorgabe11.EnableWindow(true);
	vorgabe12.EnableWindow(true);
	vorgabe13.EnableWindow(true);
	vorgabe14.EnableWindow(true);
	vorgabe15.EnableWindow(true);
	vorgabe16.EnableWindow(true);
	vorgabe17.EnableWindow(true);
	vorgabe18.EnableWindow(true);
	vorgabe19.EnableWindow(true);
	vorgabe20.EnableWindow(true);
	vorgabe21.EnableWindow(true);
	vorgabe22.EnableWindow(true);
	vorgabe23.EnableWindow(true);
	vorgabe24.EnableWindow(true);
	vorgabe25.EnableWindow(true);
	vorgabe26.EnableWindow(true);
	vorgabe27.EnableWindow(true);
	vorgabe28.EnableWindow(true);
	vorgabe29.EnableWindow(true);
	vorgabe30.EnableWindow(true);
	vorgabe31.EnableWindow(true);
	vorgabe32.EnableWindow(true);
	vorgabe33.EnableWindow(true);
	vorgabe34.EnableWindow(true);
	vorgabe35.EnableWindow(true);
	vorgabe36.EnableWindow(true);
	vorgabe37.EnableWindow(true);
	vorgabe38.EnableWindow(true);
	vorgabe39.EnableWindow(true);
	vorgabe40.EnableWindow(true);
	vorgabe41.EnableWindow(true);
	vorgabe42.EnableWindow(true);
	vorgabe43.EnableWindow(true);
	vorgabe44.EnableWindow(true);
	vorgabe45.EnableWindow(true);
	vorgabe46.EnableWindow(true);
	vorgabe47.EnableWindow(true);
	vorgabe48.EnableWindow(true);
	vorgabe49.EnableWindow(true);
	vorgabe50.EnableWindow(true);
	vorgabe51.EnableWindow(true);
	vorgabe52.EnableWindow(true);
	vorgabe53.EnableWindow(true);
	vorgabe54.EnableWindow(true);
	vorgabesetzen();
}

void CDlgSolitaire::vorgabesetzen()
{
	long kartenanzahl = m_ctrlSelKartenanzahl.GetCurSel();
	if (kartenanzahl<54)vorgabe54.EnableWindow(false);
	if (kartenanzahl<53)vorgabe53.EnableWindow(false);
	if (kartenanzahl<52)vorgabe52.EnableWindow(false);
	if (kartenanzahl<51)vorgabe51.EnableWindow(false);
	if (kartenanzahl<50)vorgabe50.EnableWindow(false);
	if (kartenanzahl<49)vorgabe49.EnableWindow(false);
	if (kartenanzahl<48)vorgabe48.EnableWindow(false);
	if (kartenanzahl<47)vorgabe47.EnableWindow(false);
	if (kartenanzahl<46)vorgabe46.EnableWindow(false);
	if (kartenanzahl<45)vorgabe45.EnableWindow(false);
	if (kartenanzahl<44)vorgabe44.EnableWindow(false);
	if (kartenanzahl<43)vorgabe43.EnableWindow(false);
	if (kartenanzahl<42)vorgabe42.EnableWindow(false);
	if (kartenanzahl<41)vorgabe41.EnableWindow(false);
	if (kartenanzahl<40)vorgabe40.EnableWindow(false);
	if (kartenanzahl<39)vorgabe39.EnableWindow(false);
	if (kartenanzahl<38)vorgabe38.EnableWindow(false);
	if (kartenanzahl<37)vorgabe37.EnableWindow(false);
	if (kartenanzahl<36)vorgabe36.EnableWindow(false);
	if (kartenanzahl<35)vorgabe35.EnableWindow(false);
	if (kartenanzahl<34)vorgabe34.EnableWindow(false);
	if (kartenanzahl<33)vorgabe33.EnableWindow(false);
	if (kartenanzahl<32)vorgabe32.EnableWindow(false);
	if (kartenanzahl<31)vorgabe31.EnableWindow(false);
	if (kartenanzahl<30)vorgabe30.EnableWindow(false);
	if (kartenanzahl<29)vorgabe29.EnableWindow(false);
	if (kartenanzahl<28)vorgabe28.EnableWindow(false);
	if (kartenanzahl<27)vorgabe27.EnableWindow(false);
	if (kartenanzahl<26)vorgabe26.EnableWindow(false);
	if (kartenanzahl<25)vorgabe25.EnableWindow(false);
	if (kartenanzahl<24)vorgabe24.EnableWindow(false);
	if (kartenanzahl<23)vorgabe23.EnableWindow(false);
	if (kartenanzahl<22)vorgabe22.EnableWindow(false);
	if (kartenanzahl<21)vorgabe21.EnableWindow(false);
	if (kartenanzahl<20)vorgabe20.EnableWindow(false);
	if (kartenanzahl<19)vorgabe19.EnableWindow(false);
	if (kartenanzahl<18)vorgabe18.EnableWindow(false);
	if (kartenanzahl<17)vorgabe17.EnableWindow(false);
	if (kartenanzahl<16)vorgabe16.EnableWindow(false);
	if (kartenanzahl<15)vorgabe15.EnableWindow(false);
	if (kartenanzahl<14)vorgabe14.EnableWindow(false);
	if (kartenanzahl<13)vorgabe13.EnableWindow(false);
	if (kartenanzahl<12)vorgabe12.EnableWindow(false);
	if (kartenanzahl<11)vorgabe11.EnableWindow(false);
	if (kartenanzahl<10)vorgabe10.EnableWindow(false);
	if (kartenanzahl<9)vorgabe9.EnableWindow(false);
	if (kartenanzahl<8)vorgabe8.EnableWindow(false);
	if (kartenanzahl<7)vorgabe7.EnableWindow(false);
	if (kartenanzahl<6)vorgabe6.EnableWindow(false);
	if (kartenanzahl<5)vorgabe5.EnableWindow(false);
	if (kartenanzahl<4)vorgabe4.EnableWindow(false);
}

void CDlgSolitaire::OnEnChangePassword()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie setzen den CDialog::OnInitDialog() au�er Kraft.
	// Funktion und Aufruf CRichEditCtrl().SetEventMask()
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.
	// TODO:  F�gen Sie hier Ihren Code f�r die Kontrollbenachrichtigungsbehandlung ein.

	UpdateData(true);

	int selStart;
	int selEnd;
	m_passwort.GetSel(selStart, selEnd);
	for (int i=0 ;i<m_passwort1.GetLength(); i++)
	{
		if (((m_passwort1[i]<'A')||(m_passwort1[i]>'Z')) && ((m_passwort1[i]<'a')||(m_passwort1[i]>'z')) )
		{
				//Entfernen des fehlerhaften Zeichens.
				//Der Cursor wird anschlie�end an die Stelle gesetzt, an der das
				//fehlerhafte Zeichen stand.
				m_passwort1.Delete(i);
				selStart = selEnd = i;
				i--;		
		}
	}	

	UpdateData(false);
	m_passwort.SetSel(selStart, selEnd);
}

void CDlgSolitaire::OnBnClickedModifyDeckByPassword()
{
	UpdateData(true);
	// FIXME: MODIFY DECK BY PASSWORD
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedSaveDeck()
{
	// myD->inideckspeichern();
}

void CDlgSolitaire::OnBnClickedSaveFinalDeck()
{
	// myD->abschlussdeckspeichern();
}


// CANCEL
void CDlgSolitaire::OnBnCancel()
{
	OnCancel();	
}


// ENCRYPT
void CDlgSolitaire::OnEncrypt()
{
#if 0
	char outfile[256];
	int i;
	myD->verschluesseln(myD->plaintext);
	GetTmpName(outfile,"cry",".txt");	
	myD->writeCiphertext(outfile);
	// Version Beunink + Lennarz
	OpenNewDoc(outfile,myD->getKey(),this->oldTitle,IDS_CRYPT_SOLITAIRE,false,1);

	char tmpStr[12];
	CString sKey = _T("");
	sKey +=   CString(NUMBER_OF_CARDS) + CString(_itoa(myD->anzahl, tmpStr, 10)) + CString(";")
		    + CString(SORT_METHOD)  + InitialArt + CString(";") 
			+ CString(MANUAL) + CString("X;");   // FIXME
	sKey += CString(INITIAL_DECK);
	for (i=0; i<myD->anzahl; i++)
	{
		sKey += CString(_itoa(myD->tempini[i], tmpStr, 10));
		if (i<myD->anzahl-1) sKey += CString(",");
	}
	sKey += CString(";");

	sKey += CString(MAPPED_DECK);
	for (i=0; i<myD->anzahl; i++)
	{
		sKey += CString(_itoa(myD->deck[i], tmpStr, 10));
		if (i<myD->anzahl-1) sKey += CString(",");
	}
	// Version Koy
	//OpenNewDoc(outfile,sKey,this->oldTitle,IDS_CRYPT_SOLITAIRE,false,1);
#endif

	this->EndDialog(1);	
}

// DECRYPT
void CDlgSolitaire::OnDecrypt()
{
#if 0
	char outfile[256];
	int i;

	myD->keyUmrechnen();
	myD->entschluesseln(myD->plaintext);
	GetTmpName(outfile,"cry",".txt");	
	myD->writeplaintext(outfile);	
	// OpenNewDoc(outfile,myD->getKey(),this->oldTitle,IDS_CRYPT_SOLITAIRE,true,1);
	char tmpStr[12];
	CString sKey = _T("");
	sKey +=   CString(NUMBER_OF_CARDS) + CString(_itoa(myD->anzahl, tmpStr, 10)) + CString(";")
		    + CString(SORT_METHOD)  + InitialArt + CString(";") 
			+ CString(MANUAL) + CString("X;");  // FIXME
	sKey += CString(INITIAL_DECK);
	for (i=0; i<myD->anzahl; i++)
	{
		sKey += CString(_itoa(myD->tempini[i], tmpStr, 10));
		if (i<myD->anzahl-1) sKey += CString(",");
	}
	sKey += CString(";");

	sKey += CString(MAPPED_DECK);
	for (i=0; i<myD->anzahl; i++)
	{
		sKey += CString(_itoa(myD->deck[i], tmpStr, 10));
		if (i<myD->anzahl-1) sKey += CString(",");
	}
	OpenNewDoc(outfile,sKey,this->oldTitle,IDS_CRYPT_SOLITAIRE,false,1);
#endif
	this->EndDialog(1);
}

void CDlgSolitaire::OnEnChangeEdit2()
{
	
}


void CDlgSolitaire::OnPasteKey()
{
#if 0
	CString buffer;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SOLITAIRE,pc_str,STR_LAENGE_STRING_TABLE);
	if(PasteKey(pc_str, buffer))
	{
		int ndx;
		UpdateData();
		ndx = buffer.Find(NUMBER_OF_CARDS);
		if (0 == ndx)
		{
			buffer.Delete(0, strlen(NUMBER_OF_CARDS));
			kartenanzahl = atoi(buffer);
			if (myD) delete myD; // FIXME
			myD = new Deck(kartenanzahlneu);
			myD->readPlaintext(infile); // FIXME Size of Plaintext
				// schneidet die Zeichen nach 65.535 ab.
			if(myD->plaintext.GetLength()>65535)
			{
				myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
				
			}
		}
		else
		{
			// FIXME: ERROR
		}

		ndx = buffer.Find(SORT_METHOD);
		if (0 <= ndx)
		{
			buffer.Delete(0, strlen(SORT_METHOD)+ndx);
			ndx = buffer.Find(";");
			InitialArt = buffer.Mid(0,ndx);
			SetDeckSelectioMethod(InitialArt);
		}
		else
		{
			// FIXME: ERROR
		}

		ndx = buffer.Find(MANUAL);
		if (0 <= ndx)
		{
			buffer.Delete(0, strlen(MANUAL)+ndx);
			ndx = buffer.Find(";");
			// FIXME
		}
		else
		{
			// FIXME: ERROR
		}

		ndx = buffer.Find(INITIAL_DECK);
		if (0 <= ndx)
		{
			buffer.Delete(0, strlen(INITIAL_DECK)+ndx);
			InitialDeck = _T("");
			int i;
			for (i=0; i<kartenanzahlneu; i++)
			{
				myD->tempini[i] = atoi(buffer);
				ndx = buffer.Find(",");
				if (i < kartenanzahlneu -1 && 0 < ndx) {
					InitialDeck += buffer.Mid(0, ndx+1);
					buffer.Delete(0, ndx+1);
				}
				else
				{
					ndx = buffer.Find(";");
					InitialDeck += buffer.Mid(0, ndx);
				}
			}
		}
		else
		{
			// FIXME: ERROR
		}
/*
		ndx = buffer.Find(MAPPED_DECK);
		if (0 <= ndx)
		{
			buffer.Delete(0, strlen(MAPPED_DECK)+ndx);
			endDeck = _T("");
			int i;
			for (i=0; i<kartenanzahlneu; i++)
			{
				myD->deck[i] = atoi(buffer);
				ndx = buffer.Find(",");
				if (i < kartenanzahlneu -1 && 0 < ndx) {
					endDeck += buffer.Mid(0, ndx+1);
					buffer.Delete(0, ndx+1);
				}
				else
				{
					endDeck += buffer;
				}
			}
		}
		else
		{
			// FIXME: ERROR
		}
*/
		// ????????????????
		m_abschlussspeichern.EnableWindow(true);
		m_inispeichern.EnableWindow(true);
		for(int i=0;i<myD->plaintext.GetLength();i++)
		{
			myD->schritt1();
			myD->schritt2();
			myD->schritt3();
			myD->schritt4();
			myD->key[i]=myD->schritt5ohneJokerAusgabe();
		}
		
		key_edit = myD->getKey();
		verschl.EnableWindow(true);
		entschl.EnableWindow(true);
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);


		UpdateData(FALSE);
		
	}
	else
	{
		// FIXME: ERROR
	}
#endif 
}


void CDlgSolitaire::OnBnFinishCrypt()
{
	while ( key_stream_size < in_buffer_size ) 
	{
		deck.s1_swap_JA();
		deck.s2_swap_JB();
		deck.s3_triple_cut();
		deck.s4_count_cut();
		unsigned char c = deck.s5_stream_char();
		if ( c )
		{
			if ( key_stream_size )
				key_edit += ',';
			char tmpStr[12];
			_itoa(c, tmpStr, 10);
			key_edit += CString(tmpStr);
			key_stream[key_stream_size++] = c;
		}
	}
	deck.get_deck(endDeck);
	edit_zaehler_value = 0;
	
	verschl.EnableWindow(true);
	entschl.EnableWindow(true);
	m_passwort.EnableWindow(false);
	m_passwort_button.EnableWindow(false);
	m_schritt1.EnableWindow(false);
	m_rest_generate.EnableWindow(false);
	m_keystream_save_button.EnableWindow(true);
	UpdateData(FALSE);
}

void CDlgSolitaire::OnBnReInit()
{
	m_ctrlSelKartenanzahl.SetCurSel(51);
	m_ctrlComboSelCards.SetCurSel(0);
	init();
}

void CDlgSolitaire::OnBnNewShuffle()
{
	init();
}

void CDlgSolitaire::OnBnSaveKeyStream()
{
}
