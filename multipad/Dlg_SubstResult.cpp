//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält alle Funktionalitäten für
// das Nachbearbeitungsfenster für die automatische Analyse
// der monoalphabetischen Substitution.
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "multipad.h"
#include "Dlg_SubstResult.h"

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
// Dialogfeld CDlg_SubstResult 


CDlg_SubstResult::CDlg_SubstResult(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_SubstResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_SubstResult)
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
}


void CDlg_SubstResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_SubstResult)
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


BEGIN_MESSAGE_MAP(CDlg_SubstResult, CDialog)
	//{{AFX_MSG_MAP(CDlg_SubstResult)
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlg_SubstResult 


/* Die folgende Funktion nimmt die Daten aus der Eingabemaske,
   entschlüsselt den Ciphertext mit der daraus resultierenden 
   Substitution und gibt das Ergebnis in der Textbox (im unteren
   Teil des Nachbearbeitungsfensters) aus.
   
   Diese Funktion wird immer dann aufgerufen, wenn der Benutzer
   eine Änderung an den Zuordnungen (im oberen Bereich des
   Nachbearbeitungsfensters) vorgenommen hat.			*/
void CDlg_SubstResult::OnButton1() 
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
			if (Eingabe[text[i]]!=42){
				Ausgabe+=(char)(Eingabe[text[i]]);
			}
			else {
				Ausgabe+=(char)text[i]+97;
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
void CDlg_SubstResult::OnButton2() 
{
	OnInitDialog();
}


/* Diese Funktion wird nur einmal zur Initialisierung der Felder des
   Nachbearbeitungsfensters ausgeführt.
   Die vom Programm ermittelte Substitution wird in die Felder des 
   Nachbearbeitungsfensters geschrieben. Anschließend wird der Ciphertext
   mit dieser Substitution entschlüsselt und dargestellt.			*/
BOOL CDlg_SubstResult::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Ermittelte Substitution in Eingabemaske übernehmen
	for (int i=0; i<26; i++){
		if (*MaxPermu[i]==-1){
			*MaxPermu[i]=42;}
		Eingabe[i]=*MaxPermu[i];
		LetzteGueltig[i]=Eingabe[i];}
	schreibeDaten();
	UpdateData(FALSE);
	
	// Text mit dieser Substitution entschlüsseln und anzeigen
	OnButton1();
	
	return TRUE;  
}


/* Diese Funktion wird nur einmal ausgeführt, wenn der Benutzer im
   Nachbearbeitungsfenster den OK-Knopf gedrückt hat.
   Die Daten aus den Feldern des Nachbearbeitungsfensters (und damit
   eventuelle Änderungen des Anwenders) werden an die Analyse Funktion 
   übergeben.										*/
void CDlg_SubstResult::OnOK() 
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



void CDlg_SubstResult::OnChangeEdit1() 
{
	UpdateData(TRUE);
	if (m_edit1!="") OnChange (0);
}

void CDlg_SubstResult::OnChangeEdit2() 
{
	UpdateData(TRUE);
	if (m_edit2!="") OnChange (1);
}

void CDlg_SubstResult::OnChangeEdit3() 
{
	UpdateData(TRUE);
	if (m_edit3!="") OnChange (2);
}

void CDlg_SubstResult::OnChangeEdit4() 
{
	// Überprüfen, ob der eingegebene Buchstabe nicht schon wo anders existiert
	LoadString(AfxGetInstanceHandle(),IDS_STRING41414,pc_str,STR_LAENGE_STRING_TABLE);
	AfxMessageBox (pc_str);
	UpdateData(FALSE);
}

void CDlg_SubstResult::OnChangeEdit5() 
{
	UpdateData(TRUE);
	if (m_edit4!="") OnChange (3);
}

void CDlg_SubstResult::OnChangeEdit6() 
{
	UpdateData(TRUE);
	if (m_edit5!="") OnChange (4);
}

void CDlg_SubstResult::OnChangeEdit7() 
{
	UpdateData(TRUE);
	if (m_edit6!="") OnChange (5);
}

void CDlg_SubstResult::OnChangeEdit8() 
{
	UpdateData(TRUE);
	if (m_edit8!="") OnChange (7);
}

void CDlg_SubstResult::OnChangeEdit9() 
{
	UpdateData(TRUE);
	if (m_edit9!="") OnChange (8);
}

void CDlg_SubstResult::OnChangeEdit10() 
{
	UpdateData(TRUE);
	if (m_edit10!="") OnChange (9);
}

void CDlg_SubstResult::OnChangeEdit11() 
{
	UpdateData(TRUE);
	if (m_edit11!="") OnChange (10);
}

void CDlg_SubstResult::OnChangeEdit12() 
{
	UpdateData(TRUE);
	if (m_edit12!="") OnChange (11);
}

void CDlg_SubstResult::OnChangeEdit13() 
{
	UpdateData(TRUE);
	if (m_edit13!="") OnChange (12);
}

void CDlg_SubstResult::OnChangeEdit14() 
{
	UpdateData(TRUE);
	if (m_edit15!="") OnChange (14);
}

void CDlg_SubstResult::OnChangeEdit15() 
{
	UpdateData(TRUE);
	if (m_edit21!="") OnChange (20);
}

void CDlg_SubstResult::OnChangeEdit16() 
{
	UpdateData(TRUE);
	if (m_edit16!="") OnChange (15);
}

void CDlg_SubstResult::OnChangeEdit17() 
{
	UpdateData(TRUE);
	if (m_edit22!="") OnChange (21);
}

void CDlg_SubstResult::OnChangeEdit18() 
{
	UpdateData(TRUE);
	if (m_edit17!="") OnChange (16);
}

void CDlg_SubstResult::OnChangeEdit19() 
{
	UpdateData(TRUE);
	if (m_edit23!="") OnChange (22);
}

void CDlg_SubstResult::OnChangeEdit20() 
{
	UpdateData(TRUE);
	if (m_edit18!="") OnChange (17);
}

void CDlg_SubstResult::OnChangeEdit21() 
{
	UpdateData(TRUE);
	if (m_edit24!="") OnChange (23);
}

void CDlg_SubstResult::OnChangeEdit22() 
{
	UpdateData(TRUE);
	if (m_edit19!="") OnChange (18);
}

void CDlg_SubstResult::OnChangeEdit23() 
{
	UpdateData(TRUE);
	if (m_edit25!="") OnChange (24);
}

void CDlg_SubstResult::OnChangeEdit24() 
{
	UpdateData(TRUE);
	if (m_edit20!="") OnChange (19);
}

void CDlg_SubstResult::OnChangeEdit25() 
{
	UpdateData(TRUE);
	if (m_edit26!="") OnChange (25);
}

void CDlg_SubstResult::OnChangeEdit26() 
{
	UpdateData(TRUE);
	if (m_edit7!="") OnChange (6);
}

void CDlg_SubstResult::OnChangeEdit27() 
{
	UpdateData(TRUE);
	if (m_edit14!="") OnChange (13);
}


void CDlg_SubstResult::FeldLeer(){
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
void CDlg_SubstResult::holeDaten(){
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
void CDlg_SubstResult::schreibeDaten(){
	UpdateData(TRUE);
	m_edit1=Eingabe[0];
	m_edit2=Eingabe[1];
	m_edit3=Eingabe[2];
	m_edit4=Eingabe[3];
	m_edit5=Eingabe[4];
	m_edit6=Eingabe[5];
	m_edit7=Eingabe[6];
	m_edit8=Eingabe[7];
	m_edit9=Eingabe[8];
	m_edit10=Eingabe[9];
	m_edit11=Eingabe[10];
	m_edit12=Eingabe[11];
	m_edit13=Eingabe[12];
	m_edit14=Eingabe[13];
	m_edit15=Eingabe[14];
	m_edit16=Eingabe[15];
	m_edit17=Eingabe[16];
	m_edit18=Eingabe[17];
	m_edit19=Eingabe[18];
	m_edit20=Eingabe[19];
	m_edit21=Eingabe[20];
	m_edit22=Eingabe[21];
	m_edit23=Eingabe[22];
	m_edit24=Eingabe[23];
	m_edit25=Eingabe[24];
	m_edit26=Eingabe[25];
	UpdateData(FALSE);
	return;
}

void CDlg_SubstResult::OnChange(int Feldnummer){
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
	for (int i=0; i<26; i++){
		if (i!=Feldnummer){
			if (Eingabe[i]==Eingabe[Feldnummer]){
				if (Eingabe[i]!='*'){
					LoadString (AfxGetInstanceHandle(), IDS_STRING41415, pc_str, STR_LAENGE_STRING_TABLE);
					CString Ausgabe=(CString)pc_str+(CString)(Feldnummer+65)+(CString)" -> "+(CString)(Eingabe[Feldnummer]);
					LoadString (AfxGetInstanceHandle(), IDS_STRING41423, pc_str, STR_LAENGE_STRING_TABLE);
					Ausgabe+=(CString)pc_str+(CString)(i+65)+(CString)" -> "+(CString)(Eingabe[i]);
					LoadString (AfxGetInstanceHandle(), IDS_STRING41485, pc_str, STR_LAENGE_STRING_TABLE);
					Ausgabe+=pc_str;
					if (AfxMessageBox (Ausgabe,MB_YESNO)==IDYES){
						Eingabe[i]='*';
						LetzteGueltig[i]='*';
						LetzteGueltig[Feldnummer]=Eingabe[Feldnummer];
						schreibeDaten();
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
	OnButton1();
}
