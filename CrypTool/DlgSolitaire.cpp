// DlgSolitaire.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSolitaire.h"
#include ".\dlgsolitaire.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "KeyRepository.h"


// CDlgSolitaire-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgSolitaire, CDialog)

CDlgSolitaire::CDlgSolitaire(char* infile, CString oldTitle,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSolitaire::IDD, pParent)
	, kartenanzahl(54)
	, InitialDeck(_T(""))
	, InitialArt(0)
	, m_passwort1(_T(""))
	, endDeck(_T(""))
	, key_edit(_T(""))
{
	
	myD = new Deck(kartenanzahl);

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
	DDX_CBIndex(pDX, IDC_COMBO2, InitialArt);
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
}

BOOL CDlgSolitaire::OnInitDialog()
{
	CDialog::OnInitDialog();
	enableVorgabe(false);
	myD->readPlaintext(infile);
	if ((myD->plaintext=="")||(myD->plaintext.GetLength()>15000))
	{
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_1,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);	
		this->EndDialog(1);
	}

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_SOLITAIRE,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_PASTE_KEY,this));
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	CString tmpStr;
	tmpStr.Format(IDS_TITLE_DLG_SOLITAIRE, oldTitle);
	this->SetWindowText(tmpStr);

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
	m_passwort.EnableWindow(true);
	m_passwort_button.EnableWindow(true);
	m_abschlussspeichern.EnableWindow(false);
	m_inispeichern.EnableWindow(false);
	zaehler=0;
	enableVorgabe(false);
	initdrei();
	verschl.EnableWindow(false);
	entschl.EnableWindow(false);
	endDeck="";
	key_edit="";
	if (kartenanzahl<3)
	{
		 kartenanzahl=3;
		 if (myD) delete myD; // FIXME
		 myD = new Deck(kartenanzahl);
		 InitialDeck = myD->getDeck();	
		 InitialArt = 0;
		 if(kartenanzahl<26)
	{
		m_passwort.EnableWindow(false);
		m_passwort_button.EnableWindow(false);
	}
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_2,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);	
	}
	else
	{
		if (myD) delete myD; // FIXME
		myD = new Deck(kartenanzahl);
		//hier wird der Klartext noch einmal gelesen, da ein neues Deck erstellt wurde
		myD->readPlaintext(infile);
		InitialDeck = myD->getDeck();	
		InitialArt = 0;
		if(kartenanzahl<26)
		{
			m_passwort.EnableWindow(false);
			m_passwort_button.EnableWindow(false);
		}
		UpdateData(false);
	}
	
}


void CDlgSolitaire::SetDeckSelectioMethod(int method)
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

	// aufsteigend sortiertes Deck
	if (method==0)
	{
		myD->aufsteigend();
		InitialDeck = myD->getDeck();
		enableVorgabe(false);
	}
	// absteigend sortiertes Deck
	else if (method==1)
	{
		myD->absteigend();
		InitialDeck = myD->getDeck();
		enableVorgabe(false);
	}
	//gemischtes Deck
	else if(method==2)
	{
		myD->mischen();
		InitialDeck = myD->getDeck();
		enableVorgabe(false);
	}
	// nach Vorgabe initialisiertes Deck
	else if (method==3)
	{
		zaehler=0;
		vorgabe="";
		InitialDeck = "";
		enableVorgabe(true);
		vorgabesetzen();
		m_manuell_button.EnableWindow(false);
		m_auto_button.EnableWindow(false);
	}
	// Initialdeck aus Datei lesen
	else if (method==4)
	{
		CString file = tempdir(INIDECKFILE);
		if (!myD->inideckladen(file)) {
			fehlermelden(IDS_STRING_ERROR,IDS_CT_FILE_OPEN_ERROR,file);
			return;
		}
		kartenanzahl=myD->anzahl;
		InitialDeck= myD->getDeck();
		enableVorgabe(false);
				
	}
	// Abschlussdeck aus Datei lesen
	else if (method==5)
	{
		CString file = tempdir(FINALDECKFILE);
		if (!myD->abschlussdeckladen(file)) {
			fehlermelden(IDS_STRING_ERROR,IDS_CT_FILE_OPEN_ERROR,file);
			return;
		}
		kartenanzahl=myD->anzahl;
		InitialDeck= myD->getDeck();
		enableVorgabe(false);				
	}
}

void CDlgSolitaire::OnCbnSelchangeCombo2()
{
	UpdateData();
	SetDeckSelectioMethod(InitialArt);
	UpdateData(FALSE);
}


/*Auswahl-Buttons 2-3*/
void CDlgSolitaire::OnBnClickedButton2()
{
	m_manuell_button.EnableWindow(false);
	myD->deck2tempini();
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
			 //myD->keyUmrechnen();
			 endDeck = myD->getDeck();
			 key_edit = myD->getKey();
			 verschl.EnableWindow(true);
			 entschl.EnableWindow(true);
			 m_passwort.EnableWindow(false);
			 m_passwort_button.EnableWindow(false);
			 
			
			 
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
	m_schritt1.EnableWindow(true);
	m_schritt2.EnableWindow(true);
	m_schritt3.EnableWindow(true);
	m_schritt4.EnableWindow(true);
	m_schritt5.EnableWindow(true);
	endDeck= myD->getDeck();
	UpdateData(false);

}
/*Auswahl-Buttons 2-3*/



/*Schritt 1-5 Buttons*/
void CDlgSolitaire::OnBnClickedButton4()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt1();
	endDeck = myD->getDeck();
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton5()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt2();
	endDeck = myD->getDeck();
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton6()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt3();
	endDeck = myD->getDeck();
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton7()
{
	m_manuell_button.EnableWindow(false);
	myD->schritt4();
	endDeck = myD->getDeck();
	UpdateData(false);
}

void CDlgSolitaire::OnBnClickedButton8()
{
	m_manuell_button.EnableWindow(false);
	myD->key[zaehler1-1]=myD->schritt5ohneJokerAusgabe();
	//myD->keyUmrechnen();
	key_edit = myD->getKeyChar(zaehler1);
	zaehler1++;
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
		UpdateData(false);
		LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_3,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);			
	}
	endDeck = myD->getDeck();
	UpdateData(false);
}
/*Schritt 1-5 Buttons*/



/*nach Vorgabe-Buttons 9-62*/
void CDlgSolitaire::OnBnClickedButton9()
{
			if(1>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);		
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)1;
			 vorgabe += "1,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe1.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);

				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
			 
}

void CDlgSolitaire::OnBnClickedButton10()
{
			if(2>kartenanzahl)
			 {
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);		 				 
			 }
			 else{
			 myD->deck[zaehler]=(char)2;
			 
			 vorgabe += "2,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe2.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				 m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton11()
{
	if(3>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);		
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)3;
			 
			 vorgabe += "3,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe3.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton12()
{
		if(4>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);		
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)4;
			 
			 vorgabe += "4,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe4.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton13()
{
	if(5>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);		
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)5;
			 
			 vorgabe += "5,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe5.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton14()
{
	if(6>kartenanzahl)
			 {
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)6;
			 
			 vorgabe += "6,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe6.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton15()
{
	if(7>kartenanzahl)
			 {
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)7;
			 
			 vorgabe += "7,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			
			 vorgabe7.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 } UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton16()
{
	if(8>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)8;
			 
			 vorgabe += "8,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe8.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton17()
{
	if(9>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)9;
			 
			 vorgabe += "9,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			
			 vorgabe9.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 } UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton18()
{
	if(10>kartenanzahl)
			 {
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)10;
			 
			 vorgabe += "10,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe10.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton19()
{
	if(11>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)11;
			 
			 vorgabe += "11,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe11.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton20()
{
	if(12>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)12;
			 
			 vorgabe += "12,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe12.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton21()
{
	if(13>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)13;
			 
			 vorgabe += "13,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe13.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton22()
{
	if(14>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)14;
			 
			 vorgabe += "14,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe14.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton23()
{
	if(15>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)15;
			 
			 vorgabe += "15,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			
			 vorgabe15.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 } UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton24()
{
	if(16>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)16;
			 
			 vorgabe += "16,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe16.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton25()
{
	if(17>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)17;
			 
			 vorgabe += "17,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe17.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton26()
{
	if(18>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)18;
			 
			 vorgabe += "18,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe18.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton27()
{
	if(19>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)19;
			 
			 vorgabe += "19,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe19.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton28()
{
	if(20>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)20;
			 
			 vorgabe += "20,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe20.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton29()
{
	if(21>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)21;
			 
			 vorgabe += "21,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe21.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton30()
{
	if(22>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)22;
			 
			 vorgabe += "22,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe22.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton31()
{
	if(23>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)23;
			 
			 vorgabe += "23,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe23.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton32()
{
	if(24>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)24;
			 
			 vorgabe += "24,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe24.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton33()
{
	if(25>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)25;
			 
			 vorgabe += "25,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe25.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton34()
{
	if(26>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)26;
			 
			 vorgabe += "26,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe26.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton35()
{
	if(27>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)27;
			 
			 vorgabe += "27,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe27.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton36()
{
	if(28>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)28;
			 
			 vorgabe += "28,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe28.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton37()
{
	if(29>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)29;
			 
			 vorgabe += "29,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe29.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton38()
{
	if(30>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)30;
			 
			 vorgabe += "30,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe30.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton39()
{
	if(31>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)31;
			 
			 vorgabe += "31,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe31.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton40()
{
	if(32>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)32;
			 
			 vorgabe += "32,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe32.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton41()
{
	if(33>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)33;
			 
			 vorgabe += "33,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe33.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton42()
{
	if(34>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)34;
			 
			 vorgabe += "34,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe34.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton43()
{
	if(35>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)35;
			 
			 vorgabe += "35,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe35.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton44()
{
	if(36>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)36;
			 
			 vorgabe += "36,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe36.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton45()
{
	if(37>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)37;
			 
			 vorgabe += "37,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe37.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton46()
{
	if(38>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)38;
			 
			 vorgabe += "38,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe38.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton47()
{
	if(39>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)39;
			 
			 vorgabe += "39,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe39.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton48()
{
	if(40>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)40;
			 
			 vorgabe += "40,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe40.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton49()
{
	if(41>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)41;
			 
			 vorgabe += "41,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe41.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton50()
{
	if(42>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)42;
			 
			 vorgabe += "42,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe42.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton51()
{
	if(43>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)43;
			 
			 vorgabe += "43,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe43.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton52()
{
	if(44>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)44;
			 
			 vorgabe += "44,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe44.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton53()
{
	if(45>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)45;
			 
			 vorgabe += "45,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe45.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton54()
{
	if(46>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)46;
			 
			 vorgabe += "46,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe46.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton55()
{
	if(47>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)47;
			 
			 vorgabe += "47,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe47.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton56()
{
	if(48>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)48;
			 
			 vorgabe += "48,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 UpdateData(false);
			 vorgabe48.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton57()
{
	if(49>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)49;
			 
			 vorgabe += "49,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 vorgabe49.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton58()
{
	if(50>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)50;
			 
			 vorgabe += "50,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 vorgabe50.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton59()
{
	if(51>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)51;
			 
			 vorgabe += "51,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe51.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton60()
{
	if(52>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)52;
			 
			 vorgabe += "52,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe52.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 UpdateData(false);
			 }
}


void CDlgSolitaire::OnBnClickedButton61()
{
	if(53>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
				 
			 }
			 else{
			 myD->deck[zaehler]=(char)53;
			 
			 vorgabe += "53,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe53.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 UpdateData(false);
			 }
}

void CDlgSolitaire::OnBnClickedButton62()
{
	if(54>kartenanzahl)
			 {
				 LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_5,pc_str,STR_LAENGE_STRING_TABLE);
				 MessageBox(pc_str);
			 }
			 else{
			 myD->deck[zaehler]=(char)54;
			 
			 vorgabe += "54,";
			 InitialDeck= myD->getDeckChar(zaehler+1);
			 zaehler++;
			 
			 vorgabe54.EnableWindow(false);
			 if(zaehler >= kartenanzahl)
			 {
				m_manuell_button.EnableWindow(true);
				m_auto_button.EnableWindow(true);
				LoadString(AfxGetInstanceHandle(),IDS_SOLITAIRE_MESSAGE_4,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);	
			 }
			 UpdateData(false);
			 }
}


/*nach Vorgabe-Buttons 9-62*/

void CDlgSolitaire::OnBnClickedButton63()
{
	
	zaehler=0;
	InitialDeck="";
	endDeck="";
	vorgabe="";
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

}

void CDlgSolitaire::vorgabesetzen()
{
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
	CString file = tempdir(INIDECKFILE);
	if (!myD->inideckspeichern(file))
		fehlermelden(IDS_STRING_ERROR,IDS_CT_FILE_OPEN_ERROR,file);
}

void CDlgSolitaire::OnBnClickedButton65()
{
	CString file = tempdir(FINALDECKFILE);
	if (!myD->abschlussdeckspeichern(file))
		fehlermelden(IDS_STRING_ERROR,IDS_CT_FILE_OPEN_ERROR,file);
}


// CANCEL
void CDlgSolitaire::OnBnClickedButton67()
{
	OnCancel();	
}


CString CDlgSolitaire::FormatKey()
{
	int i;
	CString sKey;
	sKey.Format(NUMBER_OF_CARDS "%d;" SORT_METHOD "%d;" MANUAL "X;",myD->anzahl,InitialArt);
#if 0
	sKey +=   CString(NUMBER_OF_CARDS) + CString(_itoa(myD->anzahl, tmpStr, 10)) + CString(";")
		    + CString(SORT_METHOD)  + InitialArt + CString(";") 
			+ CString(MANUAL) + CString("X;");   // FIXME
#endif
	char tmpStr[12];
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
	return sKey;
}
// ENCRYPT
void CDlgSolitaire::OnBnClickedButton66()
{
	char outfile[256];
	myD->verschluesseln(myD->plaintext);
	GetTmpName(outfile,"cry",".txt");	
	myD->writeCiphertext(outfile);
	// OpenNewDoc(outfile,myD->getKey(),this->oldTitle,IDS_CRYPT_SOLITAIRE,false,1);

	CString sKey = FormatKey();
	OpenNewDoc(outfile,sKey,this->oldTitle,IDS_CRYPT_SOLITAIRE,false,1);

	this->EndDialog(1);	
}

// DECRYPT
void CDlgSolitaire::OnBnClickedButton68()
{
	char outfile[256];

	myD->keyUmrechnen();
	myD->entschluesseln(myD->plaintext);
	GetTmpName(outfile,"cry",".txt");	
	myD->writeplaintext(outfile);	
	// OpenNewDoc(outfile,myD->getKey(),this->oldTitle,IDS_CRYPT_SOLITAIRE,true,1);
	CString sKey = FormatKey();
	OpenNewDoc(outfile,sKey,this->oldTitle,IDS_CRYPT_SOLITAIRE,false,1);

	this->EndDialog(1);
}

void CDlgSolitaire::OnEnChangeEdit2()
{}


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
			kartenanzahl = atoi(buffer);
			if (myD) delete myD; // FIXME
			myD = new Deck(kartenanzahl);
			myD->readPlaintext(infile); // FIXME Size of Plaintext
		}
		else
		{
			// FIXME: ERROR
		}

		ndx = buffer.Find(SORT_METHOD);
		if (0 <= ndx)
		{
			buffer.Delete(0, strlen(SORT_METHOD)+ndx);
			InitialArt = atoi(buffer);
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
			for (i=0; i<kartenanzahl; i++)
			{
				myD->tempini[i] = atoi(buffer);
				ndx = buffer.Find(",");
				if (i < kartenanzahl -1 && 0 < ndx) {
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
			for (i=0; i<kartenanzahl; i++)
			{
				myD->deck[i] = atoi(buffer);
				ndx = buffer.Find(",");
				if (i < kartenanzahl -1 && 0 < ndx) {
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

