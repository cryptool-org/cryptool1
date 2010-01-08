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


// CDlgSolitaire-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgSolitaire, CDialog)

CDlgSolitaire::CDlgSolitaire(char* infile, CString oldTitle,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSolitaire::IDD, pParent)
	, kartenanzahl(51)
	, InitialDeck(_T(""))
	, InitialArt(_T("Aufsteigend"))
	, m_passwort1(_T(""))
	, endDeck(_T(""))
	, key_edit(_T(""))
	, edit_zaehler_value(0)
	, edit_schl_zeichen(0)
{
	kartenanzahlneu=kartenanzahl+3;
	myD = new Deck(kartenanzahlneu);

	InitialDeck = myD->getDeck(); 
	this->infile = infile;
	this->oldTitle = oldTitle;
}

CDlgSolitaire::~CDlgSolitaire()
{
}

void CDlgSolitaire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_Kartenanzahl, kartenanzahl);

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
}

BOOL CDlgSolitaire::OnInitDialog()
{
	CDialog::OnInitDialog();
	enableVorgabe(false);
	myD->readPlaintext(infile);
	
	// Leere Nachricht ist nicht erlaubt
	if (myD->plaintext=="")
	{
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_1,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);	
		this->EndDialog(1);
	}
	
	// schneidet die Zeichen nach 65.535 ab.
	if(myD->plaintext.GetLength()>65535)
	{
		myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_ZULANG,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,"Solitaire Ver-/Entschlüsselung");
	}
	
	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SOLITAIRE,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_PASTE_KEY,this));
	if ( IsKeyEmpty( Title ))
		m_Paste.EnableWindow(TRUE);
	else
		m_Paste.EnableWindow(FALSE);

	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

BEGIN_MESSAGE_MAP(CDlgSolitaire, CDialog)
	ON_CBN_SELCHANGE(IDC_Kartenanzahl, OnCbnSelchangeKartenanzahl)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON61, OnBnClickedButton61)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
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
	ON_BN_CLICKED(IDC_BUTTON63, OnBnClickedButton63)
	ON_EN_CHANGE(IDC_EDIT4, OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON64, OnBnClickedButton64)
	ON_BN_CLICKED(IDC_BUTTON65, OnBnClickedButton65)
	ON_BN_CLICKED(IDC_BUTTON67, OnBnClickedButton67)
	ON_BN_CLICKED(IDC_BUTTON66, OnBnClickedButton66)
	ON_BN_CLICKED(IDC_BUTTON68, OnBnClickedButton68)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(IDC_BUTTON69, OnBnClickedButton69)
	ON_BN_CLICKED(IDC_BUTTON71, OnBnClickedButton71)
	ON_BN_CLICKED(IDC_BUTTON70, OnBnClickedButton70)
	ON_BN_CLICKED(IDC_BUTTON72, OnBnClickedButton72)
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
	UpdateData(true);
	kartenanzahlneu= kartenanzahl+3;
	m_passwort.EnableWindow(true);
	m_passwort_button.EnableWindow(true);
	m_abschlussspeichern.EnableWindow(false);
	m_inispeichern.EnableWindow(false);
	zaehler=0;
	enableVorgabe(false);
	m_anderemischung.EnableWindow(true);
	initdrei();
	verschl.EnableWindow(false);
	entschl.EnableWindow(false);
	m_edit_rest_generate.ShowWindow(0);
	m_edit_schl.ShowWindow(0);
	endDeck="";
	key_edit="";
	/*
	if (kartenanzahl<3)
	{
		 kartenanzahl=3;
		 if (myD) delete myD; // FIXME
		 myD = new Deck(kartenanzahl);
		 InitialDeck = myD->getDeck();	
		 InitialArt = "aufsteigend";
		 if(kartenanzahl<26)
	{
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);
	}
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_2,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);	
	}
	*/
	//else
	//{
		if (myD) delete myD; // FIXME
		myD = new Deck(kartenanzahlneu);
		//hier wird der Klartext noch einmal gelesen, da ein neues Deck erstellt wurde
		myD->readPlaintext(infile);
		
			// schneidet die Zeichen nach 65.535 ab.
		if(myD->plaintext.GetLength()>65535)
		{
		myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
		}

		InitialDeck = myD->getDeck();	
		InitialArt = "aufsteigend";
		if(kartenanzahlneu<26)
		{
			m_passwort.EnableWindow(false);
			m_passwort_button.EnableWindow(false);
		}
		UpdateData(false);
	//}
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
	if(kartenanzahlneu<26)
	{
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);
	}

	int sel = m_ctrlComboSelCards.GetCurSel();
	switch ( sel )
	{
	case 0: // AUFSTEIGEND
		myD->aufsteigend();
		InitialDeck = myD->getDeck();
		enableVorgabe(false);
		m_anderemischung.EnableWindow(true);
		break;
	case 1: // ABSTEIGEND
		myD->absteigend();
		InitialDeck = myD->getDeck();
		enableVorgabe(false);
		m_anderemischung.EnableWindow(true);
		break;
	case 2: // GEMISCHT
		myD->mischen();
		InitialDeck = myD->getDeck();
		enableVorgabe(false);
		m_anderemischung.EnableWindow(true);
		break;
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
}

void CDlgSolitaire::OnCbnSelchangeCombo2()
{
	UpdateData();
	SetDeckSelectioMethod(InitialArt);
	m_edit_rest_generate.ShowWindow(0);
	m_edit_schl.ShowWindow(0);
	UpdateData(FALSE);
}


/*Auswahl-Buttons 2-3*/
void CDlgSolitaire::OnBnClickedButton2()
{
	m_auto_button.EnableWindow(false);
	m_manuell_button.EnableWindow(false);
	myD->deck2tempini();
	
	for(int i=0;i<myD->plaintext.GetLength();i++)
	 {
		 myD->schritt1();
		 myD->schritt2();
		 myD->schritt3();
		 myD->schritt4();
		 myD->key[i] = myD->schritt5ohneJokerAusgabe();
	 }
	//myD->keyUmrechnen();
	endDeck = myD->getDeck();
	key_edit = myD->getKey();
	m_abschlussspeichern.EnableWindow(true);
	m_inispeichern.EnableWindow(true);
	verschl.EnableWindow(true);
	entschl.EnableWindow(true);
	m_passwort.EnableWindow(false);
	m_passwort_button.EnableWindow(false);
	m_edit_rest_generate.ShowWindow(0);
	m_edit_schl.ShowWindow(0);
	m_keystream_save_button.EnableWindow(true);	
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton3()
{
	myD->deck2tempini();
	m_abschlussspeichern.EnableWindow(true);
	m_inispeichern.EnableWindow(true);
	zaehler1=1;
	m_auto_button.EnableWindow(false);
	m_passwort.EnableWindow(false);
	m_passwort_button.EnableWindow(false);
	/*
	m_schritt1.EnableWindow(true);
	m_schritt2.EnableWindow(true);
	m_schritt3.EnableWindow(true);
	m_schritt4.EnableWindow(true);
	m_schritt5.EnableWindow(true);
	*/
	endDeck= myD->getDeck();
	edit_zaehler_value = myD->plaintext.GetLength();
	edit_schl_zeichen = myD->plaintext.GetLength();
	m_edit_schl.ShowWindow(1);
	m_schritt1.EnableWindow(true);
	m_rest_generate.EnableWindow(true);
	m_edit_rest_generate.ShowWindow(1);
	UpdateData(false);

}
/*Auswahl-Buttons 2-3*/



/*Schritt 1-5 Buttons*/
void CDlgSolitaire::OnBnClickedButton4()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt1();
	endDeck = myD->getDeck();
	m_schritt2.EnableWindow(true);
	m_schritt1.EnableWindow(false);
	m_rest_generate.EnableWindow(false);
	
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton5()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt2();
	endDeck = myD->getDeck();
	m_schritt3.EnableWindow(true);
	m_schritt2.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton6()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt3();
	endDeck = myD->getDeck();
	m_schritt4.EnableWindow(true);
	m_schritt3.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton7()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt4();
	endDeck = myD->getDeck();
	m_schritt5.EnableWindow(true);
	m_schritt4.EnableWindow(false);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton8()
{
	m_manuell_button.EnableWindow(false);
	myD->key[zaehler1-1]=myD->schritt5ohneJokerAusgabe();
	//myD->keyUmrechnen();
	key_edit = myD->getKeyChar(zaehler1);
	zaehler1++;
	m_schritt1.EnableWindow(true);
	m_schritt5.EnableWindow(false);
	m_rest_generate.EnableWindow(true);
	endDeck = myD->getDeck();
	edit_zaehler_value--;
	if (zaehler1==myD->plaintext.GetLength()+1)
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
	if ( k > kartenanzahlneu )
		Message(IDS_SOLITAIRE_MESSAGE_5, MB_ICONSTOP);
	else
	{
		char tmpStr[12];
		_itoa(k, tmpStr, 10);
		vorgabe += CString(tmpStr) + ',';
		myD->deck[zaehler]=(char)k;
		InitialDeck= myD->getDeckChar(zaehler+1); 
		UpdateData(false);
		zaehler++;

		button.EnableWindow(false);
		if(zaehler >= kartenanzahlneu)
		{
			m_manuell_button.EnableWindow(true);
			m_auto_button.EnableWindow(true);
			Message(IDS_SOLITAIRE_MESSAGE_4, MB_ICONINFORMATION);
			m_anderemischung.EnableWindow(true); 
			m_reset_button.EnableWindow(false);
			if(kartenanzahlneu>25)
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
void CDlgSolitaire::OnBnClickedButton63()
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
	if (kartenanzahlneu<54)vorgabe54.EnableWindow(false);
	if (kartenanzahlneu<53)vorgabe53.EnableWindow(false);
	if (kartenanzahlneu<52)vorgabe52.EnableWindow(false);
	if (kartenanzahlneu<51)vorgabe51.EnableWindow(false);
	if (kartenanzahlneu<50)vorgabe50.EnableWindow(false);
	if (kartenanzahlneu<49)vorgabe49.EnableWindow(false);
	if (kartenanzahlneu<48)vorgabe48.EnableWindow(false);
	if (kartenanzahlneu<47)vorgabe47.EnableWindow(false);
	if (kartenanzahlneu<46)vorgabe46.EnableWindow(false);
	if (kartenanzahlneu<45)vorgabe45.EnableWindow(false);
	if (kartenanzahlneu<44)vorgabe44.EnableWindow(false);
	if (kartenanzahlneu<43)vorgabe43.EnableWindow(false);
	if (kartenanzahlneu<42)vorgabe42.EnableWindow(false);
	if (kartenanzahlneu<41)vorgabe41.EnableWindow(false);
	if (kartenanzahlneu<40)vorgabe40.EnableWindow(false);
	if (kartenanzahlneu<39)vorgabe39.EnableWindow(false);
	if (kartenanzahlneu<38)vorgabe38.EnableWindow(false);
	if (kartenanzahlneu<37)vorgabe37.EnableWindow(false);
	if (kartenanzahlneu<36)vorgabe36.EnableWindow(false);
	if (kartenanzahlneu<35)vorgabe35.EnableWindow(false);
	if (kartenanzahlneu<34)vorgabe34.EnableWindow(false);
	if (kartenanzahlneu<33)vorgabe33.EnableWindow(false);
	if (kartenanzahlneu<32)vorgabe32.EnableWindow(false);
	if (kartenanzahlneu<31)vorgabe31.EnableWindow(false);
	if (kartenanzahlneu<30)vorgabe30.EnableWindow(false);
	if (kartenanzahlneu<29)vorgabe29.EnableWindow(false);
	if (kartenanzahlneu<28)vorgabe28.EnableWindow(false);
	if (kartenanzahlneu<27)vorgabe27.EnableWindow(false);
	if (kartenanzahlneu<26)vorgabe26.EnableWindow(false);
	if (kartenanzahlneu<25)vorgabe25.EnableWindow(false);
	if (kartenanzahlneu<24)vorgabe24.EnableWindow(false);
	if (kartenanzahlneu<23)vorgabe23.EnableWindow(false);
	if (kartenanzahlneu<22)vorgabe22.EnableWindow(false);
	if (kartenanzahlneu<21)vorgabe21.EnableWindow(false);
	if (kartenanzahlneu<20)vorgabe20.EnableWindow(false);
	if (kartenanzahlneu<19)vorgabe19.EnableWindow(false);
	if (kartenanzahlneu<18)vorgabe18.EnableWindow(false);
	if (kartenanzahlneu<17)vorgabe17.EnableWindow(false);
	if (kartenanzahlneu<16)vorgabe16.EnableWindow(false);
	if (kartenanzahlneu<15)vorgabe15.EnableWindow(false);
	if (kartenanzahlneu<14)vorgabe14.EnableWindow(false);
	if (kartenanzahlneu<13)vorgabe13.EnableWindow(false);
	if (kartenanzahlneu<12)vorgabe12.EnableWindow(false);
	if (kartenanzahlneu<11)vorgabe11.EnableWindow(false);
	if (kartenanzahlneu<10)vorgabe10.EnableWindow(false);
	if (kartenanzahlneu<9)vorgabe9.EnableWindow(false);
	if (kartenanzahlneu<8)vorgabe8.EnableWindow(false);
	if (kartenanzahlneu<7)vorgabe7.EnableWindow(false);
	if (kartenanzahlneu<6)vorgabe6.EnableWindow(false);
	if (kartenanzahlneu<5)vorgabe5.EnableWindow(false);
	if (kartenanzahlneu<4)vorgabe4.EnableWindow(false);
}

void CDlgSolitaire::OnEnChangeEdit4()
{
	// TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
	// diese Benachrichtigung nicht senden, es sei denn, Sie setzen den CDialog::OnInitDialog() außer Kraft.
	// Funktion und Aufruf CRichEditCtrl().SetEventMask()
	// mit dem ENM_CHANGE-Flag ORed in der Eingabe.

	// TODO:  Fügen Sie hier Ihren Code für die Kontrollbenachrichtigungsbehandlung ein.
UpdateData(true);

	int selStart;
	int selEnd;
	m_passwort.GetSel(selStart, selEnd);
	for (int i=0 ;i<m_passwort1.GetLength(); i++)
	{
		if (((m_passwort1[i]<'A')||(m_passwort1[i]>'Z')) && ((m_passwort1[i]<'a')||(m_passwort1[i]>'z')) )
		{
				//Entfernen des fehlerhaften Zeichens.
				//Der Cursor wird anschließend an die Stelle gesetzt, an der das
				//fehlerhafte Zeichen stand.
				m_passwort1.Delete(i);
				selStart = selEnd = i;
				i--;		
		}
	}	

	UpdateData(false);
	m_passwort.SetSel(selStart, selEnd);
}

void CDlgSolitaire::OnBnClickedButton1()
{
	UpdateData(true);
	myD->passwortinzahlen(m_passwort1);
	myD->pass2deck(m_passwort1.GetLength());
	InitialDeck = myD->getDeck();
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton64()
{
	myD->inideckspeichern();
}

void CDlgSolitaire::OnBnClickedButton65()
{
	myD->abschlussdeckspeichern();
}


// CANCEL
void CDlgSolitaire::OnBnClickedButton67()
{
	OnCancel();	
}


// ENCRYPT
void CDlgSolitaire::OnBnClickedButton66()
{
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

	this->EndDialog(1);	
}

// DECRYPT
void CDlgSolitaire::OnBnClickedButton68()
{
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

	this->EndDialog(1);
}

void CDlgSolitaire::OnEnChangeEdit2()
{
	
}


void CDlgSolitaire::OnPasteKey()
{
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
			kartenanzahlneu = atoi(buffer);
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
}


void CDlgSolitaire::OnBnClickedButton69()
{
	int temp = myD->plaintext.GetLength()-edit_zaehler_value;
	for(int i=0;i<edit_zaehler_value;i++)
		{
			myD->schritt1();
			myD->schritt2();
			myD->schritt3();
			myD->schritt4();
			myD->key[temp]=myD->schritt5ohneJokerAusgabe();
			temp++;
		}
		key_edit = myD->getKey();
		verschl.EnableWindow(true);
		entschl.EnableWindow(true);
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);
		m_schritt1.EnableWindow(false);
		m_rest_generate.EnableWindow(false);
		edit_zaehler_value=0;
		m_keystream_save_button.EnableWindow(true);
		UpdateData(FALSE);
}

void CDlgSolitaire::OnBnClickedButton71()
{
	UpdateData(true);
	m_passwort.EnableWindow(true);
	m_passwort_button.EnableWindow(true);
	m_abschlussspeichern.EnableWindow(false);
	m_inispeichern.EnableWindow(false);
	zaehler=0;
	enableVorgabe(false);
	initdrei();
	verschl.EnableWindow(false);
	entschl.EnableWindow(false);
	m_edit_rest_generate.ShowWindow(0);
	m_edit_schl.ShowWindow(0);
	endDeck="";
	key_edit="";
	
	
	
		//gefuddelt
		kartenanzahl=51;
		kartenanzahlneu=54;
		myD = new Deck(kartenanzahlneu);
		//hier wird der Klartext noch einmal gelesen, da ein neues Deck erstellt wurde
		myD->readPlaintext(infile);
			// schneidet die Zeichen nach 65.535 ab.
		if(myD->plaintext.GetLength()>65535)
		{
			myD->plaintext.Delete(65535,myD->plaintext.GetLength()-65535);
		}
		InitialDeck = myD->getDeck();	
		InitialArt = "aufsteigend";


	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton70()
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
	if(kartenanzahlneu<26)
	{
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);
	}
	myD->mischen();
	InitialDeck = myD->getDeck();
	enableVorgabe(false);
	m_edit_rest_generate.ShowWindow(0);
	m_edit_schl.ShowWindow(0);
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton72()
{
	myD->keyspeichern();
	
}
