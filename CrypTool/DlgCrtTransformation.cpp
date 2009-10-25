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

// DlgCrtTransformation.cpp : Implementierungsdatei

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCrtTransformation.h"
#include ".\dlgcrttransformation.h"
#include "big.h"
#include "crt.h"
#include "IntegerArithmetic.h"
#include "DialogeMessage.h"

// CDlgCrtTransformation-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgCrtTransformation, CDialog)
CDlgCrtTransformation::CDlgCrtTransformation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrtTransformation::IDD, pParent)
	, m_a(_T(""))
	, m_b(_T(""))
	, m_m0(_T(""))
	, m_m1(_T(""))
	, m_m2(_T(""))
	, m_m3(_T(""))
	, m_m4(_T(""))
	, m_bereich(_T(""))
	, m_ma(_T(""))
	, m_mb(_T(""))
	, m_mab(_T(""))
	, m_basis(_T(""))
	, m_rueck(_T(""))
	, m_x(_T(""))
	, m_radio(0)
	, m_primex(_T("2^185"))
	, m_primey(_T("2^186"))
	, m_anzahl(5)
	, m_radiogenerate(1)
{
}

CDlgCrtTransformation::~CDlgCrtTransformation()
{
}

void CDlgCrtTransformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITA0, m_a);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITA1, m_b);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITM0, m_m0);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITM1, m_m1);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITM2, m_m2);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITM3, m_m3);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITM4, m_m4);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITSOLVE6, m_bereich);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITSOLVE1, m_ma);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITSOLVE2, m_mb);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITSOLVE3, m_mab);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITSOLVE4, m_basis);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITSOLVE5, m_x);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITBACK, m_rueck);
	DDX_Radio(pDX, IDC_CRT_TRANSFORMATION_RADIO1, m_radio);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITX, m_primex);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITY, m_primey);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITX, m_control_primex);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITY, m_control_primey);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITM0, m_control_m0);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITM1, m_control_m1);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITM2, m_control_m2);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITM3, m_control_m3);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITM4, m_control_m4);
	DDX_Control(pDX, IDC_CRT_TRANSFORMATION_EDITANZAHL, m_control_anzahl);
	DDX_Text(pDX, IDC_CRT_TRANSFORMATION_EDITANZAHL, m_anzahl);
	DDX_Radio(pDX, IDC_GENERATERADIO1, m_radiogenerate);
}


BEGIN_MESSAGE_MAP(CDlgCrtTransformation, CDialog)
	ON_BN_CLICKED(IDC_CRT_TRANSFORMATION_BUTTONSOLVE, OnBnClickedCrtTransformationButtonsolve)
	ON_BN_CLICKED(IDC_CRT_TRANSFORMATION_BUTTONRESET2, OnBnClickedCrtTransformationButtonreset)
	ON_BN_CLICKED(IDC_CRT_TRANSFORMATION_BUTTONEND2, OnBnClickedCrtTransformationButtonend)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITA0, OnEnChangeCrtTransformationEdita0)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITA1, OnEnChangeCrtTransformationEdita1)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITM0, OnEnChangeCrtTransformationEditm0)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITM1, OnEnChangeCrtTransformationEditm1)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITM2, OnEnChangeCrtTransformationEditm2)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITM3, OnEnChangeCrtTransformationEditm3)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITM4, OnEnChangeCrtTransformationEditm4)
	ON_BN_CLICKED(IDC_Generate1, OnBnClickedGenerate1)
	ON_BN_CLICKED(IDC_CRT_TRANSFORMATION_RADIO1, OnBnClickedCrtTransformationRadio1)
	ON_BN_CLICKED(IDC_CRT_TRANSFORMATION_RADIO2, OnBnClickedCrtTransformationRadio2)
	ON_BN_CLICKED(IDC_CRT_TRANSFORMATION_RADIO3, OnBnClickedCrtTransformationRadio3)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITANZAHL, OnEnChangeCrtTransformationEditanzahl)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITX, OnEnChangeCrtTransformationEditx)
	ON_EN_CHANGE(IDC_CRT_TRANSFORMATION_EDITY, OnEnChangeCrtTransformationEdity)
	ON_BN_CLICKED(IDC_GENERATERADIO1, OnBnClickedGenerateradio1)
	ON_BN_CLICKED(IDC_GENERATERADIO2, OnBnClickedGenerateradio2)
END_MESSAGE_MAP()


// CDlgCrtTransformation-Meldungshandler

//** Funktion erzeugt eine Primzahl **/
BOOL CDlgCrtTransformation::GetRandomPrime(CString &OutStr, GeneratePrimes &P)
{
	BOOL flag = FALSE;

	for ( int i=1; i<=2000 && !flag; i++ )			 // 
	{
		P.RandP();
		flag = P.MillerRabinTest(100);		
		//if (0==m_radio1) flag = P.MillerRabinTest(100);
		//if (1==m_radio1) flag = P.SolvayStrassenTest(100);
		//if (2==m_radio1) flag = P.FermatTest(100);
	}
    if (flag)
	{
		P.GetPrime( OutStr );
	}
	else
	{
		OutStr = "0";
	}
	return flag;// wenn keine Primzahl innerhalb der Grenzen gefunden wurde, erfolgt eine entsprechende Fehlermeldung
}

//** Funktion erzeugt Zufalls-Primzahl innerhalb der angegebenen Grenzen **/
void CDlgCrtTransformation::GeneratePrime(int anzahl) 
{
	UpdateData(true);
	
	GeneratePrimes P;
	int PSet;
	
	if(!( (0==m_primex.IsEmpty()) && 
		  (0==m_primey.IsEmpty()) ) )
	{
		Message( IDS_STRING_ENTER_UPPER_LOWER_BOUND, MB_ICONINFORMATION );
		return;
	}
	
	CString UpnFormula;
	int err_ndx, k;
	BOOL error;
	
	error = CheckFormula(m_primex,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_primex.SetSel(err_ndx-1,m_primex.GetLength());
		m_control_primex.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	error = CheckFormula(m_primey,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		m_control_primey.SetSel(err_ndx-1,m_primey.GetLength());
		m_control_primey.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	
	Big zahl;CString text="";
	CStringFormulaToBig(m_primey,zahl);
	BigToCString(zahl,text,10);

	if ((zahl==0) || (text.GetLength()>56)) {
	m_m0=m_m1=m_m2=m_m3=m_m4="";
	m_control_primey.SetFocus();
	m_control_primey.SetSel(0,-1);
	Message( IDS_CRT_TRANSFORMATION_GENERATEPRIME, MB_ICONINFORMATION);
	return;
	}

	
	PSet=P.SetLimits( m_primex, m_primey );
	bool correct=true;
	if ( (PSet == 1) )
	{	
    
		SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
		m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";
		bool solve [5];
		for (k=0;k<5;k++) solve[k]=false;

		for (k=0;k<10;k++) {
			if (GetRandomPrime( m_m0, P )) {solve[0]=true;break;}
		}
		
		if ((anzahl>1)&&(m_m0!="")) {
			for (k=0;k<10;k++) {
			if ((GetRandomPrime( m_m1, P ))&&(m_m1!=m_m0)) {solve[1]=true;break;}
			}
		}
		
		if ((anzahl>2)&&(m_m0!="")&&(m_m1!="")) {
			for (k=0;k<10;k++) {
			if ((GetRandomPrime( m_m2, P ))&&(m_m2!=m_m0)&&(m_m2!=m_m1)) 
			{solve[2]=true;break;}
			}
		}

		if ((anzahl>3)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")) {
			for (k=0;k<10;k++) {
				if ((GetRandomPrime( m_m3, P ))&&(m_m3!=m_m0)&&(m_m3!=m_m1)&&(m_m3!=m_m2)) {solve[3]=true;break;}
			}
		}
		if ((anzahl>4)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")&&(m_m3!="")) {
			for (k=0;k<10;k++) {
				if ((GetRandomPrime( m_m4, P ))&&(m_m4!=m_m0)&&(m_m4!=m_m1)&&(m_m4!=m_m2)&&(m_m4!=m_m3)) {solve[4]=true;break;}
			}
		
		}
		
		for (int j=0;j<anzahl;j++) {
			if (solve[j]==false) correct=false;
		}

		if (!correct) {
		CString dummy;
		dummy.LoadString(IDS_CRT_TRANSFORMATION_EQUALPRIMES);
		CString meldung;
		meldung.Format(dummy,anzahl);
		AfxMessageBox(meldung, MB_ICONINFORMATION );
		m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";
		}

		HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
	}
	else if ( PSet == 3)
	{
		m_control_primex.SetFocus();
		m_control_primex.SetSel(0,-1);
		Message( IDS_CRT_TRANSFORMATION_GENERATEPRIME, MB_ICONINFORMATION );
	}
	else if ( PSet == 2)
	{
		m_control_primey.SetFocus();
		m_control_primey.SetSel(0,-1);
		Message( IDS_CRT_TRANSFORMATION_GENERATEPRIME, MB_ICONINFORMATION );
	}
	else if (  PSet ==1 )
	{
	m_control_primex.SetFocus();
	m_control_primex.SetSel(0,-1);
	Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
	m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";
	correct=false;
	}
	else 
	{
	m_control_primex.SetFocus();
	m_control_primex.SetSel(0,-1);
	Message( IDS_STRING_MSG_LOWERBOUND_UPPERBOUND, MB_ICONSTOP );
	m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";
	correct=false;
	}

	if (correct) {
	
	Big primes[5];
	
	//** Primzahlen in Big Array abspeichern   ** //
	if (anzahl >=1) CStringToBig(m_m0,primes[0],10);
	if (anzahl >=2) CStringToBig(m_m1,primes[1],10);
	if (anzahl >=3) CStringToBig(m_m2,primes[2],10);
	if (anzahl >=4) CStringToBig(m_m3,primes[3],10);
	if (anzahl >=5) CStringToBig(m_m4,primes[4],10);


	//** Sortieren der Primzahlen  ** //
	int min;Big dumm;
	for(int i=0;i<anzahl-1;i++) {
		min=i;
		for(int j=i+1;j<=anzahl-1;j++) 
		if (primes[j]<primes[min]) min=j; 
		dumm=primes[i];primes[i]=primes[min];primes[min]=dumm;
	}
	//** Primzahlen im Dialog anzeigen  ** //	
	if (anzahl >=1) BigToCString(primes[0],m_m0);
	if (anzahl >=2) BigToCString(primes[1],m_m1);
	if (anzahl >=3) BigToCString(primes[2],m_m2);
	if (anzahl >=4) BigToCString(primes[3],m_m3);
	if (anzahl >=5) BigToCString(primes[4],m_m4);

	}

	UpdateData(false);
}

//** Funktion testet, ob alle Moduln paarweise teilerfremd sind **/
bool CDlgCrtTransformation::testeteilerfremd()
{	bool prim=true; bool one=false; 
	CString ausgabe="";CString modul1="";CString modul2="";
	CString planet1="";CString planet2="";
	CString notprime="";CString text="";
	Big dummya=0;Big dummyb=0;
	CString str_m [5]; 
	str_m[0]=m_m0;str_m[1]=m_m1;str_m[2]=m_m2;
	str_m[3]=m_m3;str_m[4]=m_m4;

	for (int i=0;i<5;i++){
		for(int j=i+1;j<5;j++) {
			if ((str_m[i]!="") && (str_m[j]!="")) {
				CStringToBig(str_m[i],dummya,10);
				CStringToBig(str_m[j],dummyb,10);
				if (gcd(dummya,dummyb) !=1) {
				modul1=str_m[i];
				modul2=str_m[j];
				if (i==0) planet1=" 1";
				if (i==1)planet1=" 2";
				if (i==2) planet1=" 3";
				if (i==3) planet1=" 4";
				if (i==4) planet1=" 5";
				if (j==0) planet2=" 1";
				if (j==1) planet2=" 2";
				if (j==2) planet2=" 3";
				if (j==3) planet2=" 4";
				if (j==4) planet2=" 5";
				
				CString planetall;
				planetall.LoadString(IDS_CRT_TRANSFORMATION_PLANETALL);
				ausgabe.Format(planetall,planet1,modul1,planet2,modul2);
				text=text+ausgabe;
				prim=false;
				}
			}
		}
	if ((str_m[i]=="1") || (str_m[i]=="0")) {prim=false;one=true;}
	}

	if (one) {		
		if ((m_m0=="1") || (m_m0=="0")){m_control_m0.SetFocus();m_control_m0.SetSel(0,m_m0.GetLength());}
		if ((m_m1=="1") || (m_m1=="0")){m_control_m1.SetFocus();m_control_m1.SetSel(0,m_m1.GetLength());}
		if ((m_m2=="1") || (m_m2=="0")){m_control_m2.SetFocus();m_control_m2.SetSel(0,m_m2.GetLength());}
		if ((m_m3=="1") || (m_m3=="0")){m_control_m3.SetFocus();m_control_m3.SetSel(0,m_m3.GetLength());}
		if ((m_m4=="1") || (m_m4=="0")){m_control_m4.SetFocus();m_control_m4.SetSel(0,m_m4.GetLength());}
		Message( IDS_CRT_ASTRONOMY_NULLORONE, MB_ICONINFORMATION);
	}

	if (ausgabe!="") {// Moduln sind nicht teilerfremd!
	CString planetall2;
	planetall2.LoadString(IDS_CRT_TRANSFORMATION_PLANETALL2);
	ausgabe.Format(text+planetall2);
	AfxMessageBox(ausgabe, MB_ICONINFORMATION | MB_OK);}

return prim;
}

//** Funktion konvertiert ein Array vom Typ Big in einen Vektor vom Typ CString **/
CString CDlgCrtTransformation::BigVektorToCString(Big myarray[],int anzahl)
{ 		
			CString ausgabe="(";
			CString text="";
			int i;
			for (i=0;i<anzahl-1;i++) {
				BigToCString(myarray[i],text);
				ausgabe=ausgabe+text+", ";
				}
			BigToCString(myarray[i],text);ausgabe=ausgabe+text+")";

			return ausgabe;
}

//** Funktion liest die Werte im Dialog aus und speichert diese in Hilfsarrays ab **/
int CDlgCrtTransformation::werteauslesen(Big m[])
{
	CString str_m[5];
	str_m[0]=m_m0;str_m[1]=m_m1;str_m[2]=m_m2;
	str_m[3]=m_m3;str_m[4]=m_m4;
	int anzahl=0;
	for (int i=0;i<5;i++) {
		if (str_m[i]!=""){
			CStringToBig(str_m[i],m[anzahl],10);
			anzahl ++;}
	}
	return anzahl;
}

//** Tausender Markierung "." einfügen **/
CString CDlgCrtTransformation::tausender (CString text)
  {
    for (int i = text.GetLength()-3; i > 0; i -= 3)
    {
    text.Insert(i, ".");
    }
    return text;
  }

//** Hauptfunktion: Hin-und Rücktransformation Button Lösen gedrückt! **/
void CDlgCrtTransformation::OnBnClickedCrtTransformationButtonsolve()

{
	SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
	UpdateData(true);
	Big a; // Zahl a
	Big b; // Zahl b
	Big m[5];  // Teilermoduln
	Big va[5]; // Vektordarstellung Zahl a
	Big vb[5]; // Vektordarstellung Zahl b
	Big vo[5]; // Vektordarstellung Operation a * b
	Big e[5]; // Basisdarstellung
	Big x=0; // Lösung der Operation a * b
	Big M=1; // M=m1*..*mr
	Big Mi;	   // Mi = M/m[i]
	int anzahl=0, i; // Anzahl der tatsächlichen Teiler

	// Gleichungen aus dem Dialog auslesen und abspeichern
	CStringToBig(m_a,a,10);
	CStringToBig(m_b,b,10);

	anzahl=werteauslesen(m);

	// M bestimmen
	for (i=0; i<anzahl;i++) M=M*m[i];

	// testen, ob die Moduln paarweise teilerfremd sind
	bool prim=testeteilerfremd();

	if (prim) {// TRUE: Moduln paarweise teilerfremd
		if (((a*b)>M && m_radio==0)|| ((a+b)>M && m_radio==1)||((a-b)>M && m_radio==2)||((a-b)<0 && m_radio==2)) {// jedoch wurde der Zahlenbereich über-/unterschritten!
				// Zahlenbereich in CString konvertieren
			
			CString text="";
			CString ausgabe;
			ausgabe.LoadString(IDS_CRT_TRANSFORMATION_TIL);
			BigToCString(M-1,text);
			ausgabe=ausgabe+text;
			m_bereich=ausgabe;
			UpdateData(false);Big erg;CString ergtext="";
			if (m_radio==0) erg=a*b;
			if (m_radio==1) erg=a+b;
			if (m_radio==2) erg=a-b;
			BigToCString(erg,ergtext);
			CString anzeige;
			if (((a-b)<0)&&(m_radio==2)) {
				text.LoadString(IDS_CRT_TRANSFORMATION_NOTINRANGE2);
				anzeige.Format(text,ergtext);
			}
			else {text.LoadString(IDS_CRT_TRANSFORMATION_NOTINRANGE);
				  anzeige.Format(text,m_bereich,ergtext);
			}
		AfxMessageBox(anzeige, MB_ICONINFORMATION | MB_OK);
		}
		else{// Zahlenbereich wurde eingehalten!

			// Modulare Darstellung von a und b bestimmen
			for (i = 0; i < anzahl; i++) {
			va[i]=a%m[i];
			vb[i]=b%m[i];
			}
            // Ergebnis in der modularen Darstellung bestimmen
			switch (m_radio) {
			case 0: for (i = 0; i < anzahl; i++) vo[i]=(va[i]*vb[i])%m[i];break;
			case 1: for (i = 0; i < anzahl; i++) vo[i]=(va[i]+vb[i])%m[i];break;
			case 2: for (i = 0; i < anzahl; i++) vo[i]=(va[i]-vb[i])%m[i];break;
			}
			// Basis bestimmen
			for (i=0; i<anzahl;i++){
			Mi=M/m[i];
			e[i]=inverse(Mi,m[i])*Mi;
			}
			// Lösung x berechnen
			for (i = 0; i < anzahl; i++) x=x+e[i]*vo[i];
			x=x%M;
			while (x<0) x=x+M; // X <0 ?in postive Zahl umwandeln

			// Big in Vektor CString konvertieren			
			m_ma    = BigVektorToCString(va,anzahl);
			m_mb    = BigVektorToCString(vb,anzahl);
			m_mab   = BigVektorToCString(vo,anzahl);
			m_basis = BigVektorToCString(e,anzahl);
			// Berechnung der Rücktransformation in CString konvertieren
			CString ausgabe="";CString text="";
			for (i=0;i<anzahl-1;i++) {
				BigToCString(vo[i],text);ausgabe=ausgabe+"("+text+"*";
				BigToCString(e[i],text);ausgabe=ausgabe+text+")\r\n+";
				}
			BigToCString(vo[i],text);ausgabe=ausgabe+"("+text+"*";
			BigToCString(e[i],text);ausgabe=ausgabe+text+")\r\n"+" mod ";
			BigToCString(M,text);
            ausgabe=ausgabe+text;
			m_rueck=ausgabe;
			// Lösung x in CString konvertieren
			BigToCString(x,m_x);m_x=tausender(m_x);
			// Zahlenbereich in CString konvertieren
			text="";
			ausgabe.LoadString(IDS_CRT_TRANSFORMATION_TIL);
			BigToCString(M-1,text);
			ausgabe=ausgabe+text;
			m_bereich=ausgabe;
			UpdateData(false);
			}
		}
HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
}

//** Funktion überprüft, ob der Button Loesen aktiviert werden kann **/
void CDlgCrtTransformation::testdata(void)
{	CString str_m [5];
	UpdateData(true);
	// Werte auslesen
	str_m[0]=m_m0;str_m[1]=m_m1;str_m[2]=m_m2;
	str_m[3]=m_m3;str_m[4]=m_m4;
	bool korrekt=false;
	
	for (int i=0;i<5;i++) {
		if (str_m[i]!=""){korrekt=true;break;}
	}
	
    if ((m_a=="")||(m_b==""))korrekt=false;

	if (korrekt){m_x="";m_ma="";m_mb="";m_mab="";m_basis="";m_bereich="";m_rueck="";GetDlgItem(IDC_CRT_TRANSFORMATION_BUTTONSOLVE)->EnableWindow(true);
	}
	else {m_x="";m_ma="";m_mb="";m_mab="";m_basis="";m_bereich="";m_rueck="";GetDlgItem(IDC_CRT_TRANSFORMATION_BUTTONSOLVE)->EnableWindow(false);}

	UpdateData(false);
}

//** Alle Dialogwerte werden gelöscht **/
void CDlgCrtTransformation::OnBnClickedCrtTransformationButtonreset()
{	m_m0=m_m1=m_m2=m_m3=m_m4=m_a=m_b=m_ma=m_mb=m_mab=m_basis=m_x="";
	m_rueck="";m_bereich="";m_radio=0;m_radiogenerate=1;
	m_primex="2^185";m_primey="2^186";m_anzahl=5;
	GetDlgItem(IDC_CRT_TRANSFORMATION_BUTTONSOLVE)->EnableWindow(false); //Loesen-Button wird deaktiviert
GetDlgItem(IDC_GENERATEAUTOM1)->ShowWindow(true);
GetDlgItem(IDC_GENERATEAUTOM2)->ShowWindow(true);
GetDlgItem(IDC_GENERATEAUTOM3)->ShowWindow(true);
GetDlgItem(IDC_GENERATEAUTOM4)->ShowWindow(true);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITANZAHL)->ShowWindow(true);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITX)->ShowWindow(true);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITY)->ShowWindow(true);
GetDlgItem(IDC_Generate1)->ShowWindow(true);

	UpdateData(false);
}

//** Programm beenden **/
void CDlgCrtTransformation::OnBnClickedCrtTransformationButtonend()
{
OnOK();
}

//** Primzahl generieren Button wurde gedrückt! **/
void CDlgCrtTransformation::OnBnClickedGenerate1()
{	UpdateData(true);
	m_m0=m_m1=m_m2=m_m3=m_m4="";
	UpdateData(false);
	if 	((m_anzahl>5)|| (m_anzahl==0)) {
	Message(IDS_CRT_TRANSFORMATION_MAXFIVE, MB_ICONINFORMATION);
	m_control_anzahl.SetFocus();m_control_anzahl.SetSel(0,m_anzahl);}
	else {
	GeneratePrime(m_anzahl);
	UpdateData(false);
	testdata();
	}
}
//** the following functions call testdata() to check all edit-control fields **/
//** and check-control buttons **/
void CDlgCrtTransformation::OnEnChangeCrtTransformationEdita0()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEdita1()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEditm0()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEditm1()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEditm2()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEditm3()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEditm4()
{testdata();}
void CDlgCrtTransformation::OnBnClickedCrtTransformationRadio1()
{testdata();}
void CDlgCrtTransformation::OnBnClickedCrtTransformationRadio2()
{testdata();}
void CDlgCrtTransformation::OnBnClickedCrtTransformationRadio3()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEditanzahl()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEditx()
{testdata();}
void CDlgCrtTransformation::OnEnChangeCrtTransformationEdity()
{testdata();}
void CDlgCrtTransformation::OnBnClickedGenerateradio1()
{UpdateData(true);
m_m0=m_m1=m_m2=m_m3=m_m4="";
GetDlgItem(IDC_GENERATEAUTOM1)->ShowWindow(false);
GetDlgItem(IDC_GENERATEAUTOM2)->ShowWindow(false);
GetDlgItem(IDC_GENERATEAUTOM3)->ShowWindow(false);
GetDlgItem(IDC_GENERATEAUTOM4)->ShowWindow(false);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITANZAHL)->ShowWindow(false);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITX)->ShowWindow(false);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITY)->ShowWindow(false);
GetDlgItem(IDC_Generate1)->ShowWindow(false);
UpdateData(false);
}

void CDlgCrtTransformation::OnBnClickedGenerateradio2()
{UpdateData(true);
m_m0=m_m1=m_m2=m_m3=m_m4="";
GetDlgItem(IDC_GENERATEAUTOM1)->ShowWindow(true);
GetDlgItem(IDC_GENERATEAUTOM2)->ShowWindow(true);
GetDlgItem(IDC_GENERATEAUTOM3)->ShowWindow(true);
GetDlgItem(IDC_GENERATEAUTOM4)->ShowWindow(true);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITANZAHL)->ShowWindow(true);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITX)->ShowWindow(true);
GetDlgItem(IDC_CRT_TRANSFORMATION_EDITY)->ShowWindow(true);
GetDlgItem(IDC_Generate1)->ShowWindow(true);
UpdateData(false);

}
