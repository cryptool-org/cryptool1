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

// DlgCrtAstronomy.cpp : Implementierungsdatei

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgCrtAstronomy.h"
#include ".\dlgcrtastronomy.h"
#include "big.h"
#include "crt.h"
#include "IntegerArithmetic.h"
#include "DialogeMessage.h"

// CDlgCrtAstronomy-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgCrtAstronomy, CDialog)
CDlgCrtAstronomy::CDlgCrtAstronomy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrtAstronomy::IDD, pParent)
	, m_a0(_T("15"))
	, m_a1(_T(""))
	, m_a2(_T("100"))
	, m_a3(_T(""))
	, m_a4(_T(""))
	, m_a5(_T(""))
	, m_a6(_T(""))
	, m_a7(_T(""))
	, m_a8(_T(""))
	, m_m0(_T("88"))
	, m_m1(_T(""))
	, m_m2(_T("365"))
	, m_m3(_T(""))
	, m_m4(_T(""))
	, m_m5(_T(""))
	, m_m6(_T(""))
	, m_m7(_T(""))
	, m_m8(_T(""))
	, m_x(_T(""))
	, m_M(_T(""))
	, m_merkur(true)
	, m_venus(FALSE)
	, m_erde(true)
	, m_mars(FALSE)
	, m_jupiter(FALSE)
	, m_saturn(FALSE)
	, m_uranus(FALSE)
	, m_neptun(FALSE)
	, m_pluto(FALSE)
	, m_merkurtag(_T("15"))
	, m_erdetag(_T("100"))
{
}

CDlgCrtAstronomy::~CDlgCrtAstronomy()
{
}

void CDlgCrtAstronomy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA0, m_a0);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA1, m_a1);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA2, m_a2);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA3, m_a3);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA4, m_a4);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA5, m_a5);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA6, m_a6);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA7, m_a7);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITA8, m_a8);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM0, m_m0);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM1, m_m1);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM2, m_m2);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM3, m_m3);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM4, m_m4);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM5, m_m5);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM6, m_m6);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM7, m_m7);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITM8, m_m8);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITSOLVE, m_x);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKMERCURY, m_merkur);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKVENUS, m_venus);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKEARTH, m_erde);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKMARS, m_mars);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKJUPITER, m_jupiter);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKSATURN, m_saturn);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKURANUS, m_uranus);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKNEPTUN, m_neptun);
	DDX_Check(pDX, IDC_CRT_ASTRONOMY_CHECKPLUTO, m_pluto);
	DDX_Control(pDX, IDC_GIF_CRT_ASTRONOMY, m_Picture);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITREPEAT, m_M);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITAMERCURY, m_merkurtag);
	DDX_Text(pDX, IDC_CRT_ASTRONOMY_EDITAEARTH, m_erdetag);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM0, m_control_m0);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM1, m_control_m1);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM2, m_control_m2);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM3, m_control_m3);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM4, m_control_m4);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM5, m_control_m5);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM6, m_control_m6);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM7, m_control_m7);
	DDX_Control(pDX, IDC_CRT_ASTRONOMY_EDITM8, m_control_m8);

}

BEGIN_MESSAGE_MAP(CDlgCrtAstronomy, CDialog)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_BUTTONSOLVE, OnBnClickedCrtAstronomyButtonsolve)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_BUTTONRESET, OnBnClickedCrtAstronomyButtonreset)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_BUTTONEND, OnBnClickedCrtAstronomyButtonend)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA0, OnEnChangeCrtAstronomyEdita0)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA1, OnEnChangeCrtAstronomyEdita1)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA2, OnEnChangeCrtAstronomyEdita2)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA3, OnEnChangeCrtAstronomyEdita3)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA4, OnEnChangeCrtAstronomyEdita4)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA5, OnEnChangeCrtAstronomyEdita5)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA6, OnEnChangeCrtAstronomyEdita6)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA7, OnEnChangeCrtAstronomyEdita7)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITA8, OnEnChangeCrtAstronomyEdita8)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM0, OnEnChangeCrtAstronomyEditm0)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM1, OnEnChangeCrtAstronomyEditm1)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM2, OnEnChangeCrtAstronomyEditm2)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM3, OnEnChangeCrtAstronomyEditm3)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM4, OnEnChangeCrtAstronomyEditm4)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM5, OnEnChangeCrtAstronomyEditm5)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM6, OnEnChangeCrtAstronomyEditm6)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM7, OnEnChangeCrtAstronomyEditm7)
	ON_EN_CHANGE(IDC_CRT_ASTRONOMY_EDITM8, OnEnChangeCrtAstronomyEditm8)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKMERCURY, OnBnClickedCrtAstronomyCheckmercury)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKVENUS, OnBnClickedCrtAstronomyCheckvenus)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKEARTH, OnBnClickedCrtAstronomyCheckearth)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKMARS, OnBnClickedCrtAstronomyCheckmars)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKJUPITER, OnBnClickedCrtAstronomyCheckjupiter)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKSATURN, OnBnClickedCrtAstronomyChecksaturn)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKURANUS, OnBnClickedCrtAstronomyCheckuranus)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKNEPTUN, OnBnClickedCrtAstronomyCheckneptun)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_CHECKPLUTO, OnBnClickedCrtAstronomyCheckpluto)
	ON_BN_CLICKED(IDC_CRT_ASTRONOMY_BUTTONRESET2, OnBnClickedCrtAstronomyButtonreset2)
	ON_STN_CLICKED(IDC_Image, OnStnClickedImage)
END_MESSAGE_MAP()


// CDlgCrtAstronomy-Meldungshandler
BOOL CDlgCrtAstronomy::OnInitDialog()
{
	SHOW_HOUR_GLASS
	CDialog::OnInitDialog();

	this->m_Picture.UnLoad();
	this->m_Picture.Load(MAKEINTRESOURCE(IDR_CRT_ASTRONOMY), _T("GIF"));
	this->m_Picture.Stop();
	this->m_Picture.Draw();

	// Animation laden und Hintergrundfarbe schwarz setzen
	// if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF4),_T("GIF")))
	// {m_Picture.SetBkColor(RGB(0,0,0));
    // m_Picture.Draw();
	// }
	HIDE_HOUR_GLASS // deaktiviert die Sanduhr
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

//** Funktion testet, ob alle Moduln paarweise teilerfremd sind **/
bool CDlgCrtAstronomy::testeteilerfremd()
{	bool prim=true; 
	CString ausgabe="";CString modul1="";CString modul2="";
	CString planet1="";CString planet2="";
	CString notprime="";CString text="";
	Big dummya=0;Big dummyb=0;
	CString str_m [9]; 
	CString str_a [9]; 
	str_m[0]=m_m0;str_m[1]=m_m1;str_m[2]=m_m2;
	str_m[3]=m_m3;str_m[4]=m_m4;
	str_m[5]=m_m5;str_m[6]=m_m6;str_m[7]=m_m7;
	str_m[8]=m_m8;
	for (int i=0;i<9;i++){
		for(int j=i+1;j<9;j++) {
			if ((str_m[i]!="") && (str_m[j]!="")) {
				CStringToBig(str_m[i],dummya,10);
				CStringToBig(str_m[j],dummyb,10);
				if (gcd(dummya,dummyb) !=1) {
				modul1=str_m[i];
				modul2=str_m[j];
				if (i==0) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET1);
				if (i==1) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET2);
				if (i==2) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET3);
				if (i==3) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET4);
				if (i==4) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET5);
				if (i==5) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET6);
				if (i==6) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET7);
				if (i==7) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET8);
				if (i==8) planet1.LoadString(IDS_CRT_ASTRONOMY_PLANET9);
				if (j==0) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET1);
				if (j==1) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET2);
				if (j==2) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET3);
				if (j==3) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET4);
				if (j==4) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET5);
				if (j==5) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET6);
				if (j==6) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET7);
				if (j==7) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET8);
				if (j==8) planet2.LoadString(IDS_CRT_ASTRONOMY_PLANET9);
				
				CString planetall;
				planetall.LoadString(IDS_CRT_ASTRONOMY_PLANETALL);
				ausgabe.Format(planetall,planet1,modul1,planet2,modul2);
				text=text+ausgabe;
				prim=false;
				}
			}
		}
	}

if (ausgabe!="") {// Moduln sind nicht teilerfremd!
	CString planetall2;
	planetall2.LoadString(IDS_CRT_ASTRONOMY_PLANETALL2);
	ausgabe.Format(text+planetall2);
AfxMessageBox(ausgabe, MB_ICONINFORMATION | MB_OK);}

return prim;
}

#if 0
//** Funktion berechnet den Wert x nach der sukzessiven Methode **/
Big CDlgCrtAstronomy::suczessive(int anzahl,Big a[],Big m[]){
	Big neua[9];
	Big neum[9];
	for (int i=0;i<anzahl-1;i++) {
		Big ggt=gcd(m[i],m[i+1]);
		if (ggt!=1) {
			if (((a[i]-a[i+1]) % ggt) ==0) {
			neua[i]=a[i]+m[i]*(((a[i+1]-a[i])/ggt)*inverse(m[i]/ggt,m[i+1]/ggt)%(m[i+1]/ggt));
			neum[i]=m[i]*(m[i+1]/ggt);
			}
			else return -1; // Es existiert keine Lösung
			}
 		else {neua[i]=a[i]+m[i]*( (a[i+1]-a[i])*inverse(m[i],m[i+1])%m[i+1] );
			  neum[i]=m[i]*m[i+1];}
		//Zusammenfassen der Gleichungen
		while (neua[i]<0) neua[i]=neua[i]+neum[i];
		a[i+1]=neua[i];
		m[i+1]=neum[i];
		}
	return a[anzahl-1]; // Rückgabe der Lösung x
}
#endif

#if 1
//** Funktion berechnet den Wert x nach der sukzessiven Methode **/
Big CDlgCrtAstronomy::suczessive(int anzahl,Big a[],Big m[])
{
	for (int i=1;i<anzahl;i++) 
	{
		Big ggt=gcd(m[i-1],m[i]);
		Big kgv=abs(m[i-1]*m[i])/ggt;
		if ( 0 == ( (a[i]-a[i-1]) % ggt ) )
		{
			a[i] = a[i-1]+m[i-1]*(((a[i]-a[i-1])/ggt)*inverse(m[i-1]/ggt,m[i]/ggt)%(m[i]/ggt));
			m[i] = kgv;
		}
		else
			return -1;
	}
	return a[anzahl-1]; // Rückgabe der Lösung x
}
#endif


//** Funktion berechnet den Wert x nach dem Chinesischen Restssatz **/
Big CDlgCrtAstronomy::ChinRest (int anzahl,Big a[],Big m[]) {
	Big x;
	Crt chinese(anzahl,m);
	x=chinese.eval(a);
	return x;
}

//** Werte im Dialog auslesen und in die Hilfsarrays abspeichern **/
int CDlgCrtAstronomy::werteauslesen(Big a[],Big m[]) {
 
	CString str_m [9]; // Hilfsarray m
	CString str_a [9]; // Hilfarray a
	str_m[0]=m_m0;str_m[1]=m_m1;str_m[2]=m_m2;
	str_m[3]=m_m3;str_m[4]=m_m4;
	str_m[5]=m_m5;str_m[6]=m_m6;str_m[7]=m_m7;
	str_m[8]=m_m8;
	str_a[0]=m_a0;str_a[1]=m_a1;str_a[2]=m_a2;
	str_a[3]=m_a3;str_a[4]=m_a4;
	str_a[5]=m_a5;str_a[6]=m_a6;str_a[7]=m_a7;
	str_a[8]=m_a8;

	int i;

	// überprüfen ob die Moduln grösser als 1 sind	
	for (i=0;i<9;i++) {
		if (str_m[i]=="0" || str_m[i]=="1") {
		//Das Modul muss grösser als 1 sein !
		Message( IDS_CRT_ASTRONOMY_NULLORONE, MB_ICONINFORMATION);
		if (i==0){m_control_m0.SetFocus();m_control_m0.SetSel(0,m_m0.GetLength());}
		if (i==1){m_control_m1.SetFocus();m_control_m1.SetSel(0,m_m1.GetLength());}	
        if (i==2){m_control_m2.SetFocus();m_control_m2.SetSel(0,m_m2.GetLength());}
		if (i==3){m_control_m3.SetFocus();m_control_m3.SetSel(0,m_m3.GetLength());}
        if (i==4){m_control_m4.SetFocus();m_control_m4.SetSel(0,m_m4.GetLength());}
		if (i==5){m_control_m5.SetFocus();m_control_m5.SetSel(0,m_m5.GetLength());}
		if (i==6){m_control_m6.SetFocus();m_control_m6.SetSel(0,m_m6.GetLength());}
		if (i==7){m_control_m7.SetFocus();m_control_m7.SetSel(0,m_m7.GetLength());}
		if (i==8){m_control_m8.SetFocus();m_control_m8.SetSel(0,m_m8.GetLength());}
		return -1;
		}
	}
	int anzahl=0;//Anzahl der Gleichungen ist 0
	for (i=0;i<9;i++) {
		if ((str_m[i]!="")&&(str_a[i]!=""))
		{
			CStringToBig(str_m[i],m[anzahl],10);
			CStringToBig(str_a[i],a[anzahl],10);
			anzahl ++;
		}
	}
	return anzahl;
}

//** Funktion überprüft, ob der Button Loesen aktiviert werden kann **/
void CDlgCrtAstronomy::testdata(void)
{	CString str_m [9];
	CString str_a [9];
	UpdateData(true);
	// Werte auslesen
	str_m[0]=m_m0;str_m[1]=m_m1;str_m[2]=m_m2;
	str_m[3]=m_m3;str_m[4]=m_m4;
	str_m[5]=m_m5;str_m[6]=m_m6;str_m[7]=m_m7;
	str_m[8]=m_m8;
	str_a[0]=m_a0;str_a[1]=m_a1;str_a[2]=m_a2;
	str_a[3]=m_a3;str_a[4]=m_a4;
	str_a[5]=m_a5;str_a[6]=m_a6;str_a[7]=m_a7;
	str_a[8]=m_a8;
	
	bool korrekt=true;	

// überprüfen, ob die Werte m und a gleichzeitig ausgefüllt sind 
	int countempty=0;
	for (int i=0;i<9;i++) {
		if ((str_m[i]!="")&&(str_a[i]=="")){
			korrekt=false;m_x="";m_M="";break;}
		
		if ((str_m[i]=="")&&(str_a[i]!="")){
			korrekt=false;m_x="";m_M="";break;}
        
		if ((str_m[i]=="")&&(str_a[i]=="")) countempty++;
	}
	if (countempty==9){korrekt=false;m_x="";m_M="";}

	if (korrekt){
		m_x="";m_M="";
		GetDlgItem(IDC_CRT_ASTRONOMY_BUTTONSOLVE)->EnableWindow(true);}
    else {
		m_x="";m_M="";
		GetDlgItem(IDC_CRT_ASTRONOMY_BUTTONSOLVE)->EnableWindow(false);}
	
	UpdateData(false);
}

//** Tausender Markierung "." einfügen ! **/
CString CDlgCrtAstronomy::tausender (CString text)
{
	char strPT[128];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PT,strPT,128);
	for (int i = text.GetLength()-3; i > 0; i -= 3)
		text.Insert(i, strPT);
	return text;
}

  //** Hauptfunktion: Button Solve wurde gedrückt! **/
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyButtonsolve()
{
	SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
	UpdateData(true); //Daten aus dem Dialog in die Variablen abspeichern
    Big a [9]; // Rest ai für i=0..9
	Big m [9]; // Modul mi für i=0..9
	Big x = 0; // Lösung x
	Big M = 1; // M=m1*...*mr 
	int anzahl=0; // Anzahl der Gleichungen
	
	// Gleichungen aus dem Dialog auslesen und abspeichern
	anzahl=werteauslesen(a,m);
	
	if (anzahl!=-1) 
	{
		// testen, ob die Moduln paarweise teilerfremd sind
		bool prim=testeteilerfremd();

		if (prim) 
		{// TRUE: Moduln sind paarweise teilerfremd 
			//->Loesung nach dem Chinesischen Restsatz möglich
			// X und M bestimmen
			if (anzahl >1) 
				x = ChinRest (anzahl,a,m);
			if (anzahl ==1) 
				x=a[0]%m[0];
			BigToCString(x,m_x); m_x=tausender(m_x);	
			for (int i=0; i<anzahl;i++) 
				M=M*m[i];
			BigToCString(M,m_M); m_M=tausender(m_M);
		}
		else 
		{	
			x=suczessive(anzahl,a,m);
			if (x!=-1) // Loesung nach der sukzessiven Methode möglich
			{
				BigToCString(x,m_x); m_x=tausender(m_x);	
				M = m[anzahl-1];
				BigToCString(M,m_M); m_M=tausender(m_M);
			}
			else // Es gibt keine Lösung
			{
				CString ausgabe="";
				ausgabe.LoadString(IDS_CRT_ASTRONOMY_BRUTEFORCE);
				AfxMessageBox(ausgabe, MB_ICONINFORMATION | MB_OK);
				m_x.LoadString(IDS_CRT_ASTRONOMY_NOSOLUTION);
			}
		}
	}
	
	UpdateData(false);
	HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
}

//** alle Werte löschen **/
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyButtonreset()
{
	GetDlgItem(IDC_CRT_ASTRONOMY_BUTTONSOLVE)->EnableWindow(false); 
	m_m0=m_m1=m_m2=m_m3=m_m4="";m_m5=m_m6=m_m7=m_m8="";
	m_a0=m_a1=m_a2=m_a3=m_a4="";m_a5=m_a6=m_a7=m_a8="";
	m_x="";m_M="";m_erdetag="";m_merkurtag="";
	m_merkur=m_venus=m_erde=m_mars=m_jupiter=m_saturn=m_uranus=m_neptun=m_pluto=false;
    UpdateData(false);
}

//** alle Werte auf Initialzustand zurücksetzen **/
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyButtonreset2()
{	GetDlgItem(IDC_CRT_ASTRONOMY_BUTTONSOLVE)->EnableWindow(true); 
	m_m0="88";m_m1="";m_m2="365";m_m3=m_m4="";m_m5=m_m6=m_m7=m_m8="";
	m_a0="15";m_a1="";m_a2="100";m_a3=m_a4="";m_a5=m_a6=m_a7=m_a8="";
	m_x="";m_M="";m_erdetag="100";m_merkurtag="15";
	m_venus=m_mars=m_jupiter=m_saturn=m_uranus=m_neptun=m_pluto=false;
	m_merkur=m_erde=true;
    UpdateData(false);
}

//** Programm beenden **/
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyButtonend()
{
	OnOK();
}

//** the following functions call testdata() to check all edit-control fields **/
//** and check-control buttons **/
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita0()
{
	UpdateData(true);
	if (m_merkur) m_merkurtag=m_a0;
	else m_merkurtag="";
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita1()
{testdata();}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita2()
{	UpdateData(true);
	if (m_erde) m_erdetag=m_a2;
	else m_erdetag="";
	UpdateData(false);	
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita3()
{testdata();}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita4()
{testdata();}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita5()
{testdata();}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita6()
{testdata();}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita7()
{testdata();}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEdita8()
{testdata();}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm0()
{	UpdateData(true);
	if (m_merkur) m_merkur=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm1()
{	UpdateData(true);
	if (m_venus) m_venus=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm2()
{	UpdateData(true);
	if (m_erde) m_erde=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm3()
{	UpdateData(true);
	if (m_mars) m_mars=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm4()
{	UpdateData(true);
	if (m_jupiter) m_jupiter=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm5()
{	UpdateData(true);
	if (m_saturn) m_saturn=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm6()
{	UpdateData(true);
	if (m_uranus) m_uranus=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm7()
{	UpdateData(true);
	if (m_neptun) m_neptun=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnEnChangeCrtAstronomyEditm8()
{	UpdateData(true);
	if (m_pluto) m_pluto=false;
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckmercury()
{	UpdateData(true);
	if (m_merkur) {m_m0="88";m_a0="0";} else {m_m0="";m_a0="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckvenus()
{	UpdateData(true);
	if (m_venus) {m_m1="225";m_a1="0";} else {m_m1="";m_a1="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckearth()
{	UpdateData(true);
	if (m_erde) {m_m2="365";m_a2="0";} else {m_m2="";m_a2="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckmars()
{	UpdateData(true);
	if (m_mars) {m_m3="687";m_a3="0";} else {m_m3="";m_a3="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckjupiter()
{	UpdateData(true);
	if (m_jupiter) {m_m4="4327";m_a4="0";} else {m_m4="";m_a4="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyChecksaturn()
{	UpdateData(true);
	if (m_saturn) {m_m5="10751";m_a5="0";} else {m_m5="";m_a5="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckuranus()
{	UpdateData(true);
	if (m_uranus) {m_m6="30661";m_a6="0";} else {m_m6="";m_a6="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckneptun()
{	UpdateData(true);
	if (m_neptun) {m_m7="60149";m_a7="0";} else {m_m7="";m_a7="";}
	UpdateData(false);
	testdata();
}
void CDlgCrtAstronomy::OnBnClickedCrtAstronomyCheckpluto()
{	UpdateData(true);
	if (m_pluto) {m_m8="90491";m_a8="0";} else {m_m8="";m_a8="";}
	UpdateData(false);
	testdata();
}

void CDlgCrtAstronomy::OnStnClickedImage()
{
	// TODO: Add your control notification handler code here
}
