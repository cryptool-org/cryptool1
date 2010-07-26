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

//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält alle Funktionalitäten für
// das Nachbearbeitungsfenster für die automatische Analyse
// der monoalphabetischen Substitution.
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgManualSubstAnalysis.h"
#include "DialogeMessage.h"
#include "KeyRepository.h"

extern int *MaxPermu[26];
extern char *Eingabedatei;
int Eingabe[26];
int LetzteGueltig[26];

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgManualSubstAnalysis 


CDlgManualSubstAnalysis::CDlgManualSubstAnalysis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManualSubstAnalysis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgManualSubstAnalysis)
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit27 = _T("");
	m_edit4 = _T("");
	m_edit5 = _T("");
	m_edit6 = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	m_edit10 = _T("");
	m_edit11 = _T("");
	m_edit12 = _T("");
	m_edit13 = _T("");
	m_edit14 = _T("");
	m_edit15 = _T("");
	m_edit16 = _T("");
	m_edit17 = _T("");
	m_edit18 = _T("");
	m_edit19 = _T("");
	m_edit20 = _T("");
	m_edit21 = _T("");
	m_edit22 = _T("");
	m_edit23 = _T("");
	m_edit24 = _T("");
	m_edit25 = _T("");
	m_edit26 = _T("");
	m_edit1 = _T("");
	//}}AFX_DATA_INIT

	m_ptrKeyList = m_ptrKeyAct = 0;
}

CDlgManualSubstAnalysis::~CDlgManualSubstAnalysis()
{
	while ( m_ptrKeyList != 0 ) 
	{
		KeyList* toDel = m_ptrKeyList;
		m_ptrKeyList   = m_ptrKeyList->next;
		delete toDel;
	}
}



void CDlgManualSubstAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManualSubstAnalysis)
	DDX_Control(pDX, IDC_BUTTON1, m_ButtonCopyKey);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDV_MaxChars(pDX, m_edit2, 1);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDV_MaxChars(pDX, m_edit3, 1);
	DDX_Text(pDX, IDC_EDIT4, m_edit27);
	DDX_Text(pDX, IDC_EDIT5, m_edit4);
	DDV_MaxChars(pDX, m_edit4, 1);
	DDX_Text(pDX, IDC_EDIT6, m_edit5);
	DDV_MaxChars(pDX, m_edit5, 1);
	DDX_Text(pDX, IDC_EDIT7, m_edit6);
	DDV_MaxChars(pDX, m_edit6, 1);
	DDX_Text(pDX, IDC_EDIT26, m_edit7);
	DDV_MaxChars(pDX, m_edit7, 1);
	DDX_Text(pDX, IDC_EDIT8, m_edit8);
	DDV_MaxChars(pDX, m_edit8, 1);
	DDX_Text(pDX, IDC_EDIT9, m_edit9);
	DDV_MaxChars(pDX, m_edit9, 1);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	DDV_MaxChars(pDX, m_edit10, 1);
	DDX_Text(pDX, IDC_EDIT11, m_edit11);
	DDV_MaxChars(pDX, m_edit11, 1);
	DDX_Text(pDX, IDC_EDIT12, m_edit12);
	DDV_MaxChars(pDX, m_edit12, 1);
	DDX_Text(pDX, IDC_EDIT13, m_edit13);
	DDV_MaxChars(pDX, m_edit13, 1);
	DDX_Text(pDX, IDC_EDIT27, m_edit14);
	DDV_MaxChars(pDX, m_edit14, 1);
	DDX_Text(pDX, IDC_EDIT14, m_edit15);
	DDV_MaxChars(pDX, m_edit15, 1);
	DDX_Text(pDX, IDC_EDIT16, m_edit16);
	DDV_MaxChars(pDX, m_edit16, 1);
	DDX_Text(pDX, IDC_EDIT18, m_edit17);
	DDV_MaxChars(pDX, m_edit17, 1);
	DDX_Text(pDX, IDC_EDIT20, m_edit18);
	DDV_MaxChars(pDX, m_edit18, 1);
	DDX_Text(pDX, IDC_EDIT22, m_edit19);
	DDV_MaxChars(pDX, m_edit19, 1);
	DDX_Text(pDX, IDC_EDIT24, m_edit20);
	DDV_MaxChars(pDX, m_edit20, 1);
	DDX_Text(pDX, IDC_EDIT15, m_edit21);
	DDV_MaxChars(pDX, m_edit21, 1);
	DDX_Text(pDX, IDC_EDIT17, m_edit22);
	DDV_MaxChars(pDX, m_edit22, 1);
	DDX_Text(pDX, IDC_EDIT19, m_edit23);
	DDV_MaxChars(pDX, m_edit23, 1);
	DDX_Text(pDX, IDC_EDIT21, m_edit24);
	DDV_MaxChars(pDX, m_edit24, 1);
	DDX_Text(pDX, IDC_EDIT23, m_edit25);
	DDV_MaxChars(pDX, m_edit25, 1);
	DDX_Text(pDX, IDC_EDIT25, m_edit26);
	DDV_MaxChars(pDX, m_edit26, 1);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDV_MaxChars(pDX, m_edit1, 1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgManualSubstAnalysis, CDialog)
	//{{AFX_MSG_MAP(CDlgManualSubstAnalysis)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, OnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, OnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, OnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, OnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, OnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, OnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, OnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, OnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT21, OnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, OnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, OnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, OnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, OnChangeEdit25)
	ON_EN_CHANGE(IDC_EDIT26, OnChangeEdit26)
	ON_EN_CHANGE(IDC_EDIT27, OnChangeEdit27)
	ON_BN_CLICKED(IDC_UNDO_, OnUndo)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	ON_BN_CLICKED(IDC_REDO_, OnRedo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgManualSubstAnalysis 


/* Die folgende Funktion nimmt die Daten aus der Eingabemaske,
   entschlüsselt den Ciphertext mit der daraus resultierenden 
   Substitution und gibt das Ergebnis in der Textbox (im unteren
   Teil des Nachbearbeitungsfensters) aus.
   
   Diese Funktion wird immer dann aufgerufen, wenn der Benutzer
   eine Änderung an den Zuordnungen (im oberen Bereich des
   Nachbearbeitungsfensters) vorgenommen hat.			*/
void CDlgManualSubstAnalysis::OnButton1() 
{
	// Aktuelle Einstellungen aus den Feldern auslesen!!
	UpdateData(TRUE);
	FeldLeer();
	holeDaten();

	// Text entschlüsseln und anzeigen
	SymbolArray text(AlphaSpaceConv);
	text.Read(Eingabedatei);
	
	int Laenge=text.GetSize();
	
	CString Ausgabe="";
	for (int i=0 ; ((i<Laenge)&&(i<5000)); i++){
		if (text[i]!=26){
			int ord = (int)text[i];
			char chr = (char)ord;
			if (Eingabe[text[i]]!=42){
				Ausgabe+=(char)(Eingabe[text[i]]);
			}
			else {
				Ausgabe+=(char)((char)text[i]+97);
			}
		}
		else {
			Ausgabe+=" ";}
	}
	m_edit27=Ausgabe;
	UpdateData(FALSE);
}


/* Diese Funktion macht alle vom Benutzer gemachten Einstellungen
   rückgängig und schreibt die ursprünglich vom Toolkit ermittelte
   Substitution wieder in die Felder des Nachbearbeitungsfensters	*/
void CDlgManualSubstAnalysis::OnButton2() 
{
	m_ptrKeyAct = 0;

	for (int i=0; i<26; i++){
		if (*MaxPermu[i]==-1){
			*MaxPermu[i]=42;}
		Eingabe[i]=*MaxPermu[i];
		LetzteGueltig[i]=Eingabe[i];}
	schreibeDaten();
	UpdateKeyList();
	UpdateData(FALSE);
	
	// Text mit dieser Substitution entschlüsseln und anzeigen
	OnButton1();
}


/* Diese Funktion wird nur einmal zur Initialisierung der Felder des
   Nachbearbeitungsfensters ausgeführt.
   Die vom Programm ermittelte Substitution wird in die Felder des 
   Nachbearbeitungsfensters geschrieben. Anschließend wird der Ciphertext
   mit dieser Substitution entschlüsselt und dargestellt.			*/
BOOL CDlgManualSubstAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_bmpRedo.AutoLoad(IDC_REDO_, this);
	m_bmpUndo.AutoLoad(IDC_UNDO_, this);
	OnButton2();
	// Ermittelte Substitution in Eingabemaske übernehmen
	
	return TRUE;  
}


/* Diese Funktion wird nur einmal ausgeführt, wenn der Benutzer im
   Nachbearbeitungsfenster den OK-Knopf gedrückt hat.
   Die Daten aus den Feldern des Nachbearbeitungsfensters (und damit
   eventuelle Änderungen des Anwenders) werden an die Analyse Funktion 
   übergeben.										*/
void CDlgManualSubstAnalysis::OnOK() 
{
	UpdateData(TRUE);
	FeldLeer();
	holeDaten();
	for (int i=0; i<26; i++){
		*MaxPermu[i]=(char)Eingabe[i];
		if (*MaxPermu[i]==42){
			*MaxPermu[i]=-1;
		}
	}
	
	CDialog::OnOK();
}



void CDlgManualSubstAnalysis::OnChangeEdit1() 
{
	UpdateData(TRUE);
	if (m_edit1!="") OnChange (0);
}

void CDlgManualSubstAnalysis::OnChangeEdit2() 
{
	UpdateData(TRUE);
	if (m_edit2!="") OnChange (1);
}

void CDlgManualSubstAnalysis::OnChangeEdit3() 
{
	UpdateData(TRUE);
	if (m_edit3!="") OnChange (2);
}

void CDlgManualSubstAnalysis::OnChangeEdit4() 
{
	// Überprüfen, ob der eingegebene Buchstabe nicht schon wo anders existiert
	Message(IDS_STRING_ASYMKEY_MSG_DONOTCHANGE, MB_ICONINFORMATION);
	UpdateData(FALSE);
}

void CDlgManualSubstAnalysis::OnChangeEdit5() 
{
	UpdateData(TRUE);
	if (m_edit4!="") OnChange (3);
}

void CDlgManualSubstAnalysis::OnChangeEdit6() 
{
	UpdateData(TRUE);
	if (m_edit5!="") OnChange (4);
}

void CDlgManualSubstAnalysis::OnChangeEdit7() 
{
	UpdateData(TRUE);
	if (m_edit6!="") OnChange (5);
}

void CDlgManualSubstAnalysis::OnChangeEdit8() 
{
	UpdateData(TRUE);
	if (m_edit8!="") OnChange (7);
}

void CDlgManualSubstAnalysis::OnChangeEdit9() 
{
	UpdateData(TRUE);
	if (m_edit9!="") OnChange (8);
}

void CDlgManualSubstAnalysis::OnChangeEdit10() 
{
	UpdateData(TRUE);
	if (m_edit10!="") OnChange (9);
}

void CDlgManualSubstAnalysis::OnChangeEdit11() 
{
	UpdateData(TRUE);
	if (m_edit11!="") OnChange (10);
}

void CDlgManualSubstAnalysis::OnChangeEdit12() 
{
	UpdateData(TRUE);
	if (m_edit12!="") OnChange (11);
}

void CDlgManualSubstAnalysis::OnChangeEdit13() 
{
	UpdateData(TRUE);
	if (m_edit13!="") OnChange (12);
}

void CDlgManualSubstAnalysis::OnChangeEdit14() 
{
	UpdateData(TRUE);
	if (m_edit15!="") OnChange (14);
}

void CDlgManualSubstAnalysis::OnChangeEdit15() 
{
	UpdateData(TRUE);
	if (m_edit21!="") OnChange (20);
}

void CDlgManualSubstAnalysis::OnChangeEdit16() 
{
	UpdateData(TRUE);
	if (m_edit16!="") OnChange (15);
}

void CDlgManualSubstAnalysis::OnChangeEdit17() 
{
	UpdateData(TRUE);
	if (m_edit22!="") OnChange (21);
}

void CDlgManualSubstAnalysis::OnChangeEdit18() 
{
	UpdateData(TRUE);
	if (m_edit17!="") OnChange (16);
}

void CDlgManualSubstAnalysis::OnChangeEdit19() 
{
	UpdateData(TRUE);
	if (m_edit23!="") OnChange (22);
}

void CDlgManualSubstAnalysis::OnChangeEdit20() 
{
	UpdateData(TRUE);
	if (m_edit18!="") OnChange (17);
}

void CDlgManualSubstAnalysis::OnChangeEdit21() 
{
	UpdateData(TRUE);
	if (m_edit24!="") OnChange (23);
}

void CDlgManualSubstAnalysis::OnChangeEdit22() 
{
	UpdateData(TRUE);
	if (m_edit19!="") OnChange (18);
}

void CDlgManualSubstAnalysis::OnChangeEdit23() 
{
	UpdateData(TRUE);
	if (m_edit25!="") OnChange (24);
}

void CDlgManualSubstAnalysis::OnChangeEdit24() 
{
	UpdateData(TRUE);
	if (m_edit20!="") OnChange (19);
}

void CDlgManualSubstAnalysis::OnChangeEdit25() 
{
	UpdateData(TRUE);
	if (m_edit26!="") OnChange (25);
}

void CDlgManualSubstAnalysis::OnChangeEdit26() 
{
	UpdateData(TRUE);
	if (m_edit7!="") OnChange (6);
}

void CDlgManualSubstAnalysis::OnChangeEdit27() 
{
	UpdateData(TRUE);
	if (m_edit14!="") OnChange (13);
}


void CDlgManualSubstAnalysis::FeldLeer(){
	UpdateData(TRUE);
	if (m_edit1=="")	m_edit1="*";
	if (m_edit2=="")	m_edit2="*";
	if (m_edit3=="")	m_edit3="*";
	if (m_edit4=="")	m_edit4="*";
	if (m_edit5=="")	m_edit5="*";
	if (m_edit6=="")	m_edit6="*";
	if (m_edit7=="")	m_edit7="*";
	if (m_edit8=="")	m_edit8="*";
	if (m_edit9=="")	m_edit9="*";
	if (m_edit10=="")	m_edit10="*";
	if (m_edit11=="")	m_edit11="*";
	if (m_edit12=="")	m_edit12="*";
	if (m_edit13=="")	m_edit13="*";
	if (m_edit14=="")	m_edit14="*";
	if (m_edit15=="")	m_edit15="*";
	if (m_edit16=="")	m_edit16="*";
	if (m_edit17=="")	m_edit17="*";
	if (m_edit18=="")	m_edit18="*";
	if (m_edit19=="")	m_edit19="*";
	if (m_edit20=="")	m_edit20="*";
	if (m_edit21=="")	m_edit21="*";
	if (m_edit22=="")	m_edit22="*";
	if (m_edit23=="")	m_edit23="*";
	if (m_edit24=="")	m_edit24="*";
	if (m_edit25=="")	m_edit25="*";
	if (m_edit26=="")	m_edit26="*";
	UpdateData(FALSE);
	return;
}

/* Die folgende Funktion kopiert die Daten von m_edit1 bis m_edit26
   in das Feld Eingabe[0] bis Eingabe[25]								*/
void CDlgManualSubstAnalysis::holeDaten(){
	UpdateData(TRUE);
	Eingabe[0]=(char)m_edit1[0];
	Eingabe[1]=(char)m_edit2[0];
	Eingabe[2]=(char)m_edit3[0];
	Eingabe[3]=(char)m_edit4[0];
	Eingabe[4]=(char)m_edit5[0];
	Eingabe[5]=(char)m_edit6[0];
	Eingabe[6]=(char)m_edit7[0];
	Eingabe[7]=(char)m_edit8[0];
	Eingabe[8]=(char)m_edit9[0];
	Eingabe[9]=(char)m_edit10[0];
	Eingabe[10]=(char)m_edit11[0];
	Eingabe[11]=(char)m_edit12[0];
	Eingabe[12]=(char)m_edit13[0];
	Eingabe[13]=(char)m_edit14[0];
	Eingabe[14]=(char)m_edit15[0];
	Eingabe[15]=(char)m_edit16[0];
	Eingabe[16]=(char)m_edit17[0];
	Eingabe[17]=(char)m_edit18[0];
	Eingabe[18]=(char)m_edit19[0];
	Eingabe[19]=(char)m_edit20[0];
	Eingabe[20]=(char)m_edit21[0];
	Eingabe[21]=(char)m_edit22[0];
	Eingabe[22]=(char)m_edit23[0];
	Eingabe[23]=(char)m_edit24[0];
	Eingabe[24]=(char)m_edit25[0];
	Eingabe[25]=(char)m_edit26[0];
	UpdateData(FALSE);
	return;
}

/* Die folgende Funktion kopiert die Daten aus dem Feld 
   Feld Eingabe[0] bis Eingabe[25] nach m_edit1 bis m_edit26			*/
void CDlgManualSubstAnalysis::schreibeDaten(){
	UpdateData(TRUE);
	m_edit1=(char)Eingabe[0];
	m_edit2=(char)Eingabe[1];
	m_edit3=(char)Eingabe[2];
	m_edit4=(char)Eingabe[3];
	m_edit5=(char)Eingabe[4];
	m_edit6=(char)Eingabe[5];
	m_edit7=(char)Eingabe[6];
	m_edit8=(char)Eingabe[7];
	m_edit9=(char)Eingabe[8];
	m_edit10=(char)Eingabe[9];
	m_edit11=(char)Eingabe[10];
	m_edit12=(char)Eingabe[11];
	m_edit13=(char)Eingabe[12];
	m_edit14=(char)Eingabe[13];
	m_edit15=(char)Eingabe[14];
	m_edit16=(char)Eingabe[15];
	m_edit17=(char)Eingabe[16];
	m_edit18=(char)Eingabe[17];
	m_edit19=(char)Eingabe[18];
	m_edit20=(char)Eingabe[19];
	m_edit21=(char)Eingabe[20];
	m_edit22=(char)Eingabe[21];
	m_edit23=(char)Eingabe[22];
	m_edit24=(char)Eingabe[23];
	m_edit25=(char)Eingabe[24];
	m_edit26=(char)Eingabe[25];
	UpdateData(FALSE);
	return;
}

void CDlgManualSubstAnalysis::OnChange(int Feldnummer){
	holeDaten();

	// Wandle kleine in grpße Buchstaben um
	if ((Eingabe[Feldnummer]>='a')&&(Eingabe[Feldnummer]<='z')){
		Eingabe[Feldnummer]-=32;
		schreibeDaten();}

	// Eingaben außerhalb der Buchstaben und dem '*' werden nicht akzeptiert
	else {
		if ((Eingabe[Feldnummer]<'A')||(Eingabe[Feldnummer]>'Z')){
			if (Eingabe[Feldnummer]!='*'){
				Eingabe[Feldnummer]=LetzteGueltig[Feldnummer];
				schreibeDaten();
				return;
			}
		}
	}

	// Auf Kollisionen überprüfen
	bool Kollision=false;
	int kollidiert_mit=-1;

	int i;
	for (i=0; i<26; i++){
		if (i!=Feldnummer){
			if (Eingabe[i]==Eingabe[Feldnummer]){
				if (Eingabe[i]!='*'){
					LoadString (AfxGetInstanceHandle(), IDS_STRING_ASYMKEY_MSG_YOURINPUT, pc_str, STR_LAENGE_STRING_TABLE);
					CString Ausgabe=(CString)pc_str+(char)(Feldnummer+65)+(CString)" -> "+(char)(Eingabe[Feldnummer]);
					LoadString (AfxGetInstanceHandle(), IDS_STRING_ASYMKEY_ERR_COLLIDES_WITH_INPUT, pc_str, STR_LAENGE_STRING_TABLE);
					Ausgabe+=(CString)pc_str+(char)(i+65)+(CString)" -> "+(char)(Eingabe[i]);
					LoadString (AfxGetInstanceHandle(), IDS_STRING_REQ_ON_INPUT, pc_str, STR_LAENGE_STRING_TABLE);
					Ausgabe+=pc_str;
					if (AfxMessageBox (Ausgabe,MB_YESNO)==IDYES){
						Eingabe[i]='*';
						LetzteGueltig[i]='*';
						LetzteGueltig[Feldnummer]=Eingabe[Feldnummer];
						schreibeDaten();
						UpdateKeyList();
						OnButton1();
						return;
					}
					else{
						Eingabe[Feldnummer]=LetzteGueltig[Feldnummer];
						schreibeDaten();
						return;
					}
				}
			}
		}
	}
	// Zuweisung ist gültig
	LetzteGueltig[i]=Eingabe[i];
	UpdateKeyList();
	OnButton1();
}

void CDlgManualSubstAnalysis::OnCopyKey() 
{
	// get the user input (now placed in char array "Eingabe") 
	holeDaten();

	// create the key: first, we copy all valid characters from "Eingabe" into "theKey"; 
	// invalid characters are ignored and blanks are added to "theKey" instead; second, 
	// we fill "theKey" with the remaining characters in "theAlphabet" (the ones not taken)
	CString theAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	CString theKey;
	
	// step one
	for(int i=0; i<26; i++) {
		char character = Eingabe[i];
		// some initial conversion [a-z] => [A-Z]
		if(character >= 'a' && character <= 'z') {
			character -= 32;
		}
		// append character to key, and remove character from alphabet
		if(character >= 'A' && character <= 'Z') {
			theKey.AppendChar(character);
			theAlphabet.Remove(character);
		}
		// append a blank
		else {
			theKey.AppendChar(' ');
		}
	}

	// step two
	for(int i=0; i<26; i++) {
		if(theKey[i] == ' ') {
			theKey.Delete(i);
			theKey.Insert(i, theAlphabet[0]);
			theAlphabet.Remove(theAlphabet[0]);
		}
	}

	// copy substitution key to internal keystore (note: IDS_CRYPT_SUBSTITUTION)
	LoadString (AfxGetInstanceHandle(), IDS_CRYPT_SUBSTITUTION, pc_str, STR_LAENGE_STRING_TABLE);
	CopyKey(pc_str, theKey); 
}



BOOL CDlgManualSubstAnalysis::UpdateKeyList()
{
	KeyList *last;

// === Remove Forewards
	m_bmpRedo.EnableWindow(FALSE);
	if ( !m_ptrKeyAct ) 
	{
		last = m_ptrKeyList;
		m_ptrKeyList = m_ptrKeyAct = 0;
	}
	else
	{
		last = m_ptrKeyAct->next;
	}

	while ( last ) 
	{
		KeyList *toDel = last;
		last = last->next;
		delete toDel;
	}

	last = new KeyList;
	if(!last) return FALSE;
	for (int i=0; i<26; i++) last->key[i] = Eingabe[i];
	last->next = 0;
	
	if ( !m_ptrKeyAct ) 
	{
		m_ptrKeyAct = m_ptrKeyList = last;
	}
	else                
	{
		m_ptrKeyAct->next = last;
		m_ptrKeyAct       = last;
	}

	if ( m_ptrKeyAct != m_ptrKeyList )
		m_bmpUndo.EnableWindow(TRUE);
	else
		m_bmpUndo.EnableWindow(FALSE);
	m_bmpRedo.EnableWindow(FALSE);

	return TRUE;
}



BOOL CDlgManualSubstAnalysis::GetPrevKey(int* Eingabe)
{
	if (!m_ptrKeyAct) return FALSE;
	
	KeyList* last = m_ptrKeyList;
	KeyList* prev = 0;
	while(last != m_ptrKeyAct)
	{
		prev = last;
		last = last->next;
	}

	if(prev != 0)
	{
		for (int i=0; i<26; i++) 
		{
			Eingabe[i] = prev->key[i];		
		}
		m_ptrKeyAct = prev;
	}
	else
	{
		m_ptrKeyAct = m_ptrKeyList;
	}

	if (m_ptrKeyAct->next) 
		m_bmpRedo.EnableWindow(TRUE);
	if (m_ptrKeyAct == m_ptrKeyList) 
		m_bmpUndo.EnableWindow(FALSE);

	return TRUE;
}

void CDlgManualSubstAnalysis::OnUndo() 
{
	if(GetPrevKey(Eingabe)) 
	{
		schreibeDaten();
		OnButton1();
	}
}


BOOL CDlgManualSubstAnalysis::GetNextKey(int* Eingabe)
{
	if ( !m_ptrKeyAct )
	{
		return FALSE;
	}
	if ( m_ptrKeyAct->next )
	{
		m_ptrKeyAct = m_ptrKeyAct->next;
		for (int i=0; i<26; i++) 
		{
			Eingabe[i] = m_ptrKeyAct->key[i];		
		}
		if ( !m_ptrKeyAct->next )
			m_bmpRedo.EnableWindow(FALSE);
		m_bmpUndo.EnableWindow(TRUE);
		return TRUE;
	}
	else
	{
		m_bmpRedo.EnableWindow(FALSE);
		return FALSE;
	}
}


void CDlgManualSubstAnalysis::OnRedo() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
	if(GetNextKey(Eingabe)) 
	{
		schreibeDaten();
		OnButton1();
	}
}
