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

// DlgCrtSecretSharing.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "stdlib.h"
#include "CrypToolApp.h"
#include "DlgCrtSecretSharing.h"
#include ".\dlgcrtsecretsharing.h"
#include "DlgCrtSecretSharingOptions.h"
#include "DlgCrtSecretSharing_Facts.h"
#include "DlgCrtSecretSharing_Log.h"
#include "DlgCrtSecretSharing_Info.h"
#include "DialogeMessage.h"
#include "big.h"
#include "crt.h"
#include "IntegerArithmetic.h"
#include "CrypToolTools.h"

// Aus DH-Visualisation eingefügt
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgCrtSecretSharing-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgCrtSecretSharing, CDialog)
CDlgCrtSecretSharing::CDlgCrtSecretSharing(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrtSecretSharing::IDD, pParent)
	, m_anzahl(5)
	, m_need(3)
	, m_x(_T("2^108"))
	, m_y(_T("2^109"))
	, m_m0(_T(""))
	, m_m1(_T(""))
	, m_m2(_T(""))
	, m_m3(_T(""))
	, m_m4(_T(""))
	, m_m5(_T(""))
	, m_m6(_T(""))
	, m_a0(_T(""))
	, m_a1(_T(""))
	, m_a2(_T(""))
	, m_a3(_T(""))
	, m_a4(_T(""))
	, m_a5(_T(""))
	, m_a6(_T(""))
	, m_reka0(_T(""))
	, m_reka1(_T(""))
	, m_reka2(_T(""))
	, m_reka3(_T(""))
	, m_reka4(_T(""))
	, m_reka5(_T(""))
	, m_reka6(_T(""))
	, m_diverse(_T(""))
	, m_maxkminus1(_T(""))
	, m_faktorA(_T(""))
	, m_s(_T(""))
	, m_w(_T(""))
	, m_s_(_T(""))
	, m_log(_T(""))
	, m_Info(FALSE)	
	, m_calcmode(0)
{

}

CDlgCrtSecretSharing::~CDlgCrtSecretSharing()
{	
}

void CDlgCrtSecretSharing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT5, m_m0);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT6, m_m1);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT7, m_m2);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT8, m_m3);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT9, m_m4);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT9b, m_m5);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT9c, m_m6);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT10, m_a0);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT11, m_a1);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT12, m_a2);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT13, m_a3);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT14, m_a4);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT15, m_a5);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT15b, m_a6);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT16, m_reka0);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT17, m_reka1);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT18, m_reka2);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT19, m_reka3);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT20, m_reka4);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT21, m_reka5);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT22, m_reka6);
	DDX_Control(pDX, IDC_CRT_Anim, m_Picture);
	DDX_Check(pDX, IDC_CRT_SHOWDIALOG, m_Info);
	DDX_Radio(pDX, IDC_CRT_Radio_AUT, m_calcmode);
}


BEGIN_MESSAGE_MAP(CDlgCrtSecretSharing, CDialog)
	ON_BN_CLICKED(IDC_SECRETSHARING_BUTTON1, OnBnClickedSecretsharingShare)
	ON_BN_CLICKED(IDC_SECRETSHARING_BUTTON2, OnBnClickedSecretsharingReset)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedSecretsharingSolve)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD1, OnBnClickedSecretsharingAdd1)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD2, OnBnClickedSecretsharingAdd2)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD3, OnBnClickedSecretsharingAdd3)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD4, OnBnClickedSecretsharingAdd4)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD5, OnBnClickedSecretsharingAdd5)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD6, OnBnClickedSecretsharingAdd6)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD7, OnBnClickedSecretsharingAdd7)
	ON_BN_CLICKED(IDC_SECRETSHARING_ALGO, OnBnClickedSecretsharingEnd)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedSecretsharingOptions)
	ON_BN_CLICKED(IDC_SECRETSHARING_FACTS, OnBnClickedSecretsharingFacts)
	ON_BN_CLICKED(IDC_SECRETSHARING_LOG, OnBnClickedSecretsharingLog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_CRT_Radio_AUT, OnBnClickedCrtRadioAut)
	ON_BN_CLICKED(IDC_CRT_RADIO_MAN, OnBnClickedCrtRadioMan)
END_MESSAGE_MAP()

// CDlgCrtAstronomy-Meldungshandler
BOOL CDlgCrtSecretSharing::OnInitDialog()
{			
	
	//Weisses GIF wird eingeblendet
	SHOW_HOUR_GLASS	// aktiviert die Sanduhr (statt des Mauszeigers)
	CDialog::OnInitDialog();

	// Animation laden und Hintergrundfarbe schwarz setzen
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF15),_T("GIF")))
	{
		m_Picture.Draw();
	}
	HIDE_HOUR_GLASS			// deaktiviert die Sanduhr


	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "CrtSecretSharing" ) == ERROR_SUCCESS )
	{
		// flomar, 07/15/2010
		// make sure we're correctly writing the user choice back to the registry
		unsigned long showIntroDialog = TRUE;
		CT_READ_REGISTRY(showIntroDialog, "ShowIntroDialog");
		if(showIntroDialog) {
			DlgCrtSecretSharing_Info dlg;
			dlg.DoModal();
			if(dlg.m_checkInfo == FALSE) {
				showIntroDialog = FALSE;
				CT_WRITE_REGISTRY(showIntroDialog, "ShowIntroDialog");
			}
		}
		CT_CLOSE_REGISTRY();

		m_Info = showIntroDialog;
		UpdateData(false);
	}
	else
	{
		// FIXME
	}


	// Temporäre Variablen
	CString temp1,temp2;

	// Fenstertitel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGTITLE);
	temp2.Format((LPCTSTR)temp1,m_need,m_anzahl);
	this->SetWindowText((LPCTSTR)temp2);
	
	// GroupBox 1 dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX1);
	temp2.Format((LPCTSTR)temp1,m_anzahl);
	GetDlgItem(IDC_CRT_FR_KO)->SetWindowText((LPCTSTR)temp2);

	// GroupBox 2 dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX2);
	temp2.Format((LPCTSTR)temp1,m_need,m_anzahl);
	GetDlgItem(IDC_CRT_FR_REKO)->SetWindowText((LPCTSTR)temp2);
	
	// GroupBox dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX3);
	temp2.Format((LPCTSTR)temp1,m_anzahl);
	GetDlgItem(IDC_REKOHELP)->SetWindowText((LPCTSTR)temp2);

return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}


// CDlgCrtSecretSharing-Meldungshandler
BOOL CDlgCrtSecretSharing::GetRandomPrime(CString &OutStr, GeneratePrimes &P)
{
	BOOL flag = FALSE;

	for ( int i=1; i<=2000 && !flag; i++ )			 // 
	{
		P.RandP();
		flag = P.MillerRabinTest(100);		
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

// erzeugt Zufalls-Primzahl innerhalb der angegebenen Grenzen
// Fehler werden mit entsprechenden Messages behandelt
void CDlgCrtSecretSharing::GeneratePrime(int anzahl, Big primes[]) 
{
	UpdateData(true);

	GeneratePrimes P;
	int PSet;
	
	if(!( (0==m_x.IsEmpty()) && 
		  (0==m_y.IsEmpty()) ) )
	{
		Message( IDS_STRING_ENTER_UPPER_LOWER_BOUND, MB_ICONINFORMATION );
		return;
	}
	
	CString UpnFormula;
	int err_ndx;
	BOOL error;
	
	error = CheckFormula(m_x,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		//m_control_x.SetSel(err_ndx-1,m_x.GetLength());
		//m_control_x.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	error = CheckFormula(m_y,10,UpnFormula,err_ndx);
	if (error == 0)
	{
		//Fehler in der Eingabe, von Parser abgefangen
		//m_control_y.SetSel(err_ndx-1,m_y.GetLength());
		//m_control_y.SetFocus();
		Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		return;
	}
	
	PSet=P.SetLimits( m_x, m_y );
	bool correct=true;
	if ( (PSet == 1) )
	{SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
		m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";m_m5="";m_m6="";
		bool solve [7];
		int k;
		for (k=0;k<7;k++) solve[k]=false;

		for (k=0;k<10;k++) {
			if (GetRandomPrime( m_m0, P )) 
			{solve[0]=true;break;}
		}
		
		if ((anzahl>1)&&(m_m0!="")) {
			for (int k=0;k<10;k++) {
				if ((GetRandomPrime( m_m1, P ))&&(m_m1!=m_m0)) 
				{solve[1]=true;break;}
			}
		}
		
		if ((anzahl>2)&&(m_m0!="")&&(m_m1!="")) {
			for (int k=0;k<10;k++) {
				if ((GetRandomPrime( m_m2, P ))&&(m_m2!=m_m0)&&(m_m2!=m_m1)) 
				{solve[2]=true;break;}
			}
		}

		if ((anzahl>3)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")) {
			for (int k=0;k<10;k++) {
				if ((GetRandomPrime( m_m3, P ))&&(m_m3!=m_m0)&&(m_m3!=m_m1)&&(m_m3!=m_m2)) 
				{solve[3]=true;break;}
			}
		}
		if ((anzahl>4)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")&&(m_m3!="")) {
			for (int k=0;k<10;k++) {
				if ((GetRandomPrime( m_m4, P ))&&(m_m4!=m_m0)&&(m_m4!=m_m1)&&(m_m4!=m_m2)&&(m_m4!=m_m3)) 
				{solve[4]=true;break;}
			}
		
		}

		if ((anzahl>5)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")&&(m_m3!="")&&(m_m4!="")) {
			for (int k=0;k<10;k++) {
				if ((GetRandomPrime( m_m5, P ))&&(m_m5!=m_m0)&&(m_m5!=m_m1)&&(m_m5!=m_m2)&&(m_m5!=m_m3)&&(m_m5!=m_m4)) 
				{solve[5]=true;break;}
			}
		
		}
		if ((anzahl>6)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")&&(m_m3!="")&&(m_m4!="")&&(m_m5!="")) {
			for (int k=0;k<10;k++) {
				if ((GetRandomPrime( m_m6, P ))&&(m_m6!=m_m0)&&(m_m6!=m_m1)&&(m_m6!=m_m2)&&(m_m6!=m_m3)&&(m_m6!=m_m4)&&(m_m6!=m_m5)) 
				{solve[6]=true;break;}
			}
		
		}

		for (int j=0;j<anzahl;j++) {
			if (solve[j]==false) correct=false;
		}

		if (!correct) {
			CString dummy;
			dummy.LoadString(IDS_CRT_SECRETSHARING_EQUALPRIMES);
			CString meldung;
			meldung.Format(dummy,anzahl);

		// Rekonstruktions-Frame: Buttons und Texfelder deaktivieren, falls 'Berechnen' erneut gedrückt worden ist

		GetDlgItem(IDC_STATIC1)->EnableWindow(false);
		GetDlgItem(IDC_STATIC2)->EnableWindow(false);
		GetDlgItem(IDC_STATIC3)->EnableWindow(false);
		GetDlgItem(IDC_STATIC4)->EnableWindow(false);
		GetDlgItem(IDC_STATIC5)->EnableWindow(false);
		GetDlgItem(IDC_STATIC6)->EnableWindow(false);
		GetDlgItem(IDC_STATIC7)->EnableWindow(false);
			
		GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(false);

		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT22)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);	
	
		GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(false);

		//Log-Datei leeren
		m_log="";
		m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";m_m5="";m_m6="";
		AfxMessageBox( meldung, MB_ICONINFORMATION );
			
		}

		HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
	}
	else if ( PSet == 3)
	{
		//m_control_x.SetFocus();
		//m_control_x.SetSel(0,-1);
		AfxMessageBox(IDS_CRT_SECRETSHARING_GENERATEPRIME, MB_ICONINFORMATION );
		correct=false;
	}
	else if ( PSet == 2)
	{
		//m_control_y.SetFocus();
		//m_control_y.SetSel(0,-1);
		AfxMessageBox(IDS_CRT_SECRETSHARING_GENERATEPRIME, MB_ICONINFORMATION );
		correct=false;
	}
		
	if (correct) {
		//** Primzahlen in Big Array abspeichern   ** //
		if (anzahl >=1) CStringToBig(m_m0,primes[0],10);
		if (anzahl >=2) CStringToBig(m_m1,primes[1],10);
		if (anzahl >=3) CStringToBig(m_m2,primes[2],10);
		if (anzahl >=4) CStringToBig(m_m3,primes[3],10);
		if (anzahl >=5) CStringToBig(m_m4,primes[4],10);
		if (anzahl >=6) CStringToBig(m_m5,primes[5],10);
		if (anzahl ==7) CStringToBig(m_m6,primes[6],10);
	
		//** Sortieren der Primzahlen  ** //
		int min;
		Big dumm;
	
		for(int i=0;i<anzahl-1;i++) {
			min=i;
			for(int j=i+1;j<=anzahl-1;j++) 
			if (primes[j]<primes[min]) min=j; 
			dumm=primes[i];primes[i]=primes[min];primes[min]=dumm;
		}

		// Primzahlen in Dialogvariablen speichern //
		if (anzahl >=1) BigToCString(primes[0],m_m0);
		if (anzahl >=2) BigToCString(primes[1],m_m1);
		if (anzahl >=3) BigToCString(primes[2],m_m2);
		if (anzahl >=4) BigToCString(primes[3],m_m3);
		if (anzahl >=5) BigToCString(primes[4],m_m4);
		if (anzahl >=6) BigToCString(primes[5],m_m5);
		if (anzahl ==7) BigToCString(primes[6],m_m6);

		
	
		if ((m_m0.GetLength()>33) || (m_m1.GetLength()>33) || (m_m2.GetLength()>33) || (m_m3.GetLength()>33) || (m_m4.GetLength()>33)|| (m_m5.GetLength()>33)|| (m_m6.GetLength()>33)) {
			m_diverse="";m_maxkminus1="";m_w="";m_s="";m_faktorA="";
			m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";m_m5="";m_m6="";m_a0="";
			m_a1="";m_a2="";m_a3="";m_a4="";m_a5="";m_a6="";m_reka0="";m_reka1="";
			m_reka2="";m_reka3="";m_reka4="";m_reka5="";m_reka6="";
	
			GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	
			GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(false);	

			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT22)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(false);

			//Log-Datei leeren
			m_log="";
			AfxMessageBox( IDS_CRT_SECRETSHARING_GENERATEPRIME, MB_ICONINFORMATION );
		}
	}
	UpdateData(false);
}

// Funktion berechnet den Wert x nach dem Chinesischen Restssatz
Big CDlgCrtSecretSharing::ChinRest (int anzahl,Big a[],Big m[]) {
	Big x;
	Crt chinese(anzahl,m);
	x=chinese.eval(a);
	return x;
}

bool CDlgCrtSecretSharing::CheckFields() 
{
	Big primes[7];
	bool fieldsOk=true;

	if (m_anzahl >=3) {
 		if (m_m1 == "") fieldsOk=false;
		if (m_m2 == "") fieldsOk=false;	
	}
	if (m_anzahl >=4) {
		if (m_m3 == "") fieldsOk=false;	
	}
	if (m_anzahl >=5) {
		if (m_m4 == "") fieldsOk=false;	
	}
	if (m_anzahl >=6) {
		if (m_m5 == "") fieldsOk=false;	
	}
	if (m_anzahl ==7) {
		if (m_m6 == "") fieldsOk=false;	
	}	
	if  (fieldsOk==false) {
		AfxMessageBox(IDS_CRT_SECRETSHARING_MAN3);	
		return fieldsOk;
	}
		
	CStringToBig(m_m0,primes[0],10);
	CStringToBig(m_m1,primes[1],10);
	if (m_anzahl >=3) CStringToBig(m_m2,primes[2],10);
	if (m_anzahl >=4) CStringToBig(m_m3,primes[3],10);
	if (m_anzahl >=5) CStringToBig(m_m4,primes[4],10);
	if (m_anzahl >=6) CStringToBig(m_m5,primes[5],10);
	if (m_anzahl ==7) CStringToBig(m_m6,primes[6],10);
	
	for (int i=0; i<m_anzahl-1; i++) {
		for (int j=i+1; j<m_anzahl;j++) {
			if (primes[i]==primes[j]) {
				fieldsOk=false; 
				CString helpme, help2, dummy;
				int help3;
				helpme.LoadString(IDS_CRT_SECRETSHARING_MAN2);
				BigToCString(primes[i],help2,10);
				help3=atoi(help2);
				dummy.Format(helpme,help3);
				AfxMessageBox(dummy);
				return fieldsOk;	
			}
		}
	}
	return fieldsOk;
}
void CDlgCrtSecretSharing::PrepareManual(Big primes[]) 
{	
	// Bereitstellung der benötigten Variablen
	int t = m_anzahl;//wie viele Parteien es geben soll (t)
	int k = m_need;//wie viele Parteien zur Lösung benötigt werden sollen (k)
	int nonprimes=0;
	bool correct=true;
	bool flag=false;
	bool fieldsOk=true;
	bool correctprimes[7];
	Big shares[7]; //Reste m_a
	Big min_k=1; //min (k) (Produkt der k kleinsten Primzahlen)
	Big max_kminus1=1; //max (k-1) (Produkt der größten k-1 Primzahlen)
	Big w; //( Quotient aus 4. und 5.; auf die ganze Zahl abgerundet)
	Big s; // s (das Geheimnis) derart: 0 <= s < w
	Big a;//Wähle ein a derart: 0 <= s + a · w < min (k) -> der Faktor a 
	Big s_;//Löse die Ungleichung auf. Man erhält s'
	GeneratePrimes P;
	CString dummy="";

	for (int i=0;i<t;i++){correctprimes[i]=true;}

	fieldsOk = CheckFields();
	if ((m_m0 != "") && (fieldsOk)) {
		// primes-Array mit gegebenen Primzahlen füllen und pruefen, ob die Zahlen prim sind
		// Erstes Element auf prim pruefen
		CStringToBig(m_m0,primes[0],10);
		P.SetP(m_m0); correctprimes[0]=(BOOL)(P.MillerRabinTest(100));
		// Zweites Element auf prim pruefen
		CStringToBig(m_m1,primes[1],10);
		P.SetP(m_m1); correctprimes[1]=(BOOL)(P.MillerRabinTest(100));
		
		if (m_anzahl >=3) {
			CStringToBig(m_m2,primes[2],10);
			P.SetP(m_m2); correctprimes[2]=(BOOL)(P.MillerRabinTest(100));
		}
		if (m_anzahl >=4) {
			CStringToBig(m_m3,primes[3],10);
			P.SetP(m_m3); correctprimes[3]=(BOOL)(P.MillerRabinTest(100));
		}
		if (m_anzahl >=5) {
			CStringToBig(m_m4,primes[4],10);
			P.SetP(m_m4); correctprimes[4]=(BOOL)(P.MillerRabinTest(100));
		}
		if (m_anzahl >=6) {
			CStringToBig(m_m5,primes[5],10);
			P.SetP(m_m5); correctprimes[5]=(BOOL)(P.MillerRabinTest(100));
		}
		if (m_anzahl ==7) {
			CStringToBig(m_m6,primes[6],10);
			P.SetP(m_m6); correctprimes[6]=(BOOL)(P.MillerRabinTest(100));
		}
		// nachhalten, ob nicht-prime zahlen eingegeben wurden
		for (int i=0;i<t;i++)
			{
				if (!correctprimes[i]) {
					nonprimes=nonprimes+1;
				// ToDo: Dialog-Box, die sgt, welche Zahl nicht prim ist
					CString helpme, help2, dummy;
					int help3;
					helpme.LoadString(IDS_CRT_SECRETSHARING_MAN1);
					BigToCString(primes[i],help2,10);
					help3=atoi(help2);
					dummy.Format(helpme,help3);
					AfxMessageBox(dummy);
				}
			}

		// An dieser Stelle muessen in Zukunft die eingegebenen Zahlen auf 'x1*x2>x3' geprüft werden

		if (nonprimes==0)// AfxMessageBox(IDS_CRT_SECRETSHARING_MAN1);
			 {
				// Prüfen, ob Reihenfolge aufsteigend
				int min;
				Big dumm;
		
				for(int i=0;i<t-1;i++) {
					min=i;
					for(int j=i+1;j<=m_anzahl-1;j++) 
					if (primes[j]<primes[min]) min=j; 
					dumm=primes[i];primes[i]=primes[min];primes[min]=dumm;
				}
		
				// getauschte Werte in Dialogfeld-Variablen schreiben
				BigToCString(primes[0],m_m0,10);
				BigToCString(primes[1],m_m1,10);
				if (m_anzahl >=3) {BigToCString(primes[2],m_m2,10);}			
				if (m_anzahl >=4) {BigToCString(primes[3],m_m3,10);}			
				if (m_anzahl >=5) {BigToCString(primes[4],m_m4,10);}			
				if (m_anzahl >=6) {BigToCString(primes[5],m_m5,10);}			
				if (m_anzahl ==7) {BigToCString(primes[6],m_m6,10);}			

				if (m_m0!="") {
					GetDlgItem(IDC_SECRETSHARING_BUTTON2)->EnableWindow(true);	
					GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(true);
					GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(true);
					GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
				}
				// Daten werden aus den Variablen in die Dialogfelder geschrieben
				UpdateData(false);
				Calculate(primes);
			}
	}
}
//In der folgenden Prozedur wird der Hinweg durhgeführt, 
//d.h. die Shares erzeugt, mit deren Hilfe das Geheimnis
//später wieder rekonstruiert werden kann.
void CDlgCrtSecretSharing::OnBnClickedSecretsharingShare()
{
	UpdateData(true);
	Big primes[7]; // Moduln m_m
	
	//Bestehende Daten aus dem Dialog in die Variablen abspeichern
	 
	// Bei einer neuen Berechnung die alten Passwörter aus dem Dialog löschen
	m_reka0="";m_reka1="";m_reka2="";m_reka3="";m_reka4="";m_reka5="";m_reka6="";
	// ...und die Dialogfelder upgedated
	UpdateData(false);

	// Wurde manuelle Berechnung gewählt
	if (m_calcmode==1) { 
		PrepareManual(primes);

	}
	//sonst Primzahlen erzeugen und Berechnungsfunktion starten
	else {
		GeneratePrime(m_anzahl, primes);
		Calculate(primes);
	}
}

void CDlgCrtSecretSharing::Calculate(Big primes[])
{	
	// Bereitstellung der benötigten Variablen
	int t = m_anzahl;//wie viele Parteien es geben soll (t)
	int k = m_need;//wie viele Parteien zur Lösung benötigt werden sollen (k)
	bool correct=true;
	
	Big shares[7]; //Reste m_a
	Big min_k=1; //min (k) (Produkt der k kleinsten Primzahlen)
	Big max_kminus1=1; //max (k-1) (Produkt der größten k-1 Primzahlen)
	Big w; //( Quotient aus 4. und 5.; auf die ganze Zahl abgerundet)
	Big s; // s (das Geheimnis) derart: 0 <= s < w
	Big a;//Wähle ein a derart: 0 <= s + a · w < min (k) -> der Faktor a 
	Big s_;//Löse die Ungleichung auf. Man erhält s'
	CString dummy="";
	
	//Log-Datei schreiben
		m_log="";
		CString helpme;
		helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE1);
		m_log=helpme;
		dummy.Format("%i",m_anzahl);
		helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE2);
		m_log=m_log+helpme+dummy+"\r\n";
		dummy.Format("%i",m_need);
		helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE3);
		m_log=m_log+helpme+dummy+"\r\n\r\n";
		helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE4);
		m_log=m_log+helpme+m_x+"\r\n";
		helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE5);
		m_log=m_log+helpme+m_y+"\r\n\r\n";


		if (m_m0 != "") {
			// LOG-Datei schreiben:
			helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE6);
			m_log=m_log+helpme+"_1: \r\n"+m_m0+"\r\n"+helpme+"_2: \r\n"+m_m1+"\r\n";
			if (m_anzahl > 2) m_log=m_log+helpme+"_3: \r\n"+m_m2+"\r\n";
			if (m_anzahl > 3) m_log=m_log+helpme+"_4: \r\n"+m_m3+"\r\n";
			if (m_anzahl > 4) m_log=m_log+helpme+"_5: \r\n"+m_m4+"\r\n";
			if (m_anzahl > 5) m_log=m_log+helpme+"_6: \r\n"+m_m5+"\r\n";
			if (m_anzahl > 6) m_log=m_log+helpme+"_7: \r\n"+m_m6+"\r\n";
 
			//** Ermitteln des Geheimnisses **//
			// -> Erzeugen von min_k
			int i;
			for (i=0;i<k;i++) min_k = min_k * primes[i];
			// -> Erzeugen von max_k-1
			for (i=t-1;i>=t-(k-1);i--) max_kminus1 = max_kminus1 * primes[i];
			// -> Erzeugen von w
			w = min_k/max_kminus1;
			if (w==0) w=1;
			//das Geheimnis = Zufallswert zwischen 0 und w
			s=rand(w+1);
			if (w==1) s=0;
			//zufallszahl zwischen 0 und (mink/w)-1	
			a=rand(((min_k)/w)); 
			// Berechnung von s', welches die Basis für die Verteilung der Shares bildet
			s_= a*w+s;
			//Ableiten der Shares 
			for (i=0;i<t;i++) shares[i]= s_ % primes[i];

		    // Hintergrunddaten in Variablen fuer den Dialog 'Rechenweg' und die Log-Datei schreiben
			BigToCString(min_k,m_diverse);
			m_log=m_log+"\r\nmin(k):\r\n"+m_diverse+"\r\n";
			BigToCString(max_kminus1,m_maxkminus1);
			m_log=m_log+"max(k-1):\r\n"+m_maxkminus1+"\r\n";
			BigToCString(w,m_w);
			helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE7);
			m_log=m_log+helpme+m_w+"\r\n";
			BigToCString(s,m_s);
			helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE8);
			m_log=m_log+helpme+m_s+"\r\n";
			BigToCString(a,m_faktorA);
			helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE9);
			m_log=m_log+helpme+m_faktorA+"\r\n";
			BigToCString(s_,m_s_);
			helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE10);
			m_log=m_log+helpme+m_s_+"\r\n";
	
			//Log-Datei weiter führen	
			BigToCString(shares[0],m_a0);
			helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE11);
			m_log=m_log+"\r\n"+helpme+"_1:\r\n"+m_a0+"\r\n";
			BigToCString(shares[1],m_a1);
			m_log=m_log+helpme+"_2:\r\n"+m_a1+"\r\n";
			if (m_anzahl >=3) {BigToCString(shares[2],m_a2); m_log=m_log+helpme+"_3:\r\n"+m_a2+"\r\n";}
			if (m_anzahl >=4) {BigToCString(shares[3],m_a3); m_log=m_log+helpme+"_4:\r\n"+m_a3+"\r\n";}
			if (m_anzahl >=5) {BigToCString(shares[4],m_a4); m_log=m_log+helpme+"_5:\r\n"+m_a4+"\r\n";}
			if (m_anzahl >=6) {BigToCString(shares[5],m_a5); m_log=m_log+helpme+"_6:\r\n"+m_a5+"\r\n";}
			if (m_anzahl ==7) {BigToCString(shares[6],m_a6); m_log=m_log+helpme+"_7:\r\n"+m_a6+"\r\n\r\n";}
		}
		//Animation beginnt: Schloß eingeblendet
		SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
		//CDialog::OnInitDialog();
		// Animation laden und Hintergrundfarbe schwarz setzen
		if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF5),_T("GIF")))	{
			m_Picture.SetBkColor(RGB(0,0,0));
			m_Picture.Draw();
		}
			HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
	
		// LOG-Datei: 'Verteilung abgeschlossen'
		helpme.LoadString(IDS_CRT_SECRETSHARING_FINISH);
		m_log+=helpme;
	 
	GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(true);

	// Zu nutzende Elemente aktivieren
	//** Alle Felder aktivieren, falls sie vorher nicht benötigt worden sind  ** //	
		
		//Obere GoupBox:
		// Moduln 
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5)->EnableWindow(true);

		// Passwoerter
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT15b)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT15)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT14)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT13)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT12)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT11)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT10)->EnableWindow(true);

		// Rekonstruktions-GroupBox
		// Labels:
		GetDlgItem(IDC_STATIC7)->EnableWindow(true);
		GetDlgItem(IDC_STATIC6)->EnableWindow(true);
		GetDlgItem(IDC_STATIC5)->EnableWindow(true);
		GetDlgItem(IDC_STATIC4)->EnableWindow(true);
		GetDlgItem(IDC_STATIC3)->EnableWindow(true);
		GetDlgItem(IDC_STATIC2)->EnableWindow(true);
		GetDlgItem(IDC_STATIC1)->EnableWindow(true);

		// Buttons:
		GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(true);
	
		// Textfelder
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT22)->EnableWindow(true);

		// Uebrige Buttons
		GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_BUTTON2)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);

		// nun Nicht benötigte Dialogfelder aus allen Gruppierungen deaktivieren

		if (t<7) {// für Paar Nummer 7
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c)->EnableWindow(false);
		    GetDlgItem(IDC_CRT_SECRETSHARINGEDIT15b)->EnableWindow(false);
		    GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(false);
		    GetDlgItem(IDC_CRT_SECRETSHARINGEDIT22)->EnableWindow(false);
			GetDlgItem(IDC_STATIC7)->EnableWindow(false);
		}
		if (t<6) {// für Paar Nummer 6
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b)->EnableWindow(false);
		    GetDlgItem(IDC_CRT_SECRETSHARINGEDIT15)->EnableWindow(false);
		    GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(false);
		    GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(false);
			GetDlgItem(IDC_STATIC6)->EnableWindow(false);
		}
		if (t<5) {// für Paar Nummer 5
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT14)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(false);
			GetDlgItem(IDC_STATIC5)->EnableWindow(false);
		}
		if (t<4) {// für Paar Nummer 4
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT13)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(false);
			GetDlgItem(IDC_STATIC4)->EnableWindow(false);
		}
		if (t<3) {// für Paar Nummer 3
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT12)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(false);
			GetDlgItem(IDC_STATIC3)->EnableWindow(false);
		}
		if (t<2) {// für Paar Nummer 2
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT11)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(false);
			GetDlgItem(IDC_STATIC2)->EnableWindow(false);
		}
		if (t<1) {// für Paar Nummer 1
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT10)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(false);
			GetDlgItem(IDC_STATIC1)->EnableWindow(false);
		}


	// Daten werden aus den Variablen in die Dialogfelder geschrieben
	UpdateData(false);
}


// Methode wird gestartet, wenn auf den Button 'Geheimnis rekonstruieren' geklickt wird
// Sie führt die angegebenen Shares zusammen und versucht, das Geheimnis zu lueften
void CDlgCrtSecretSharing::OnBnClickedSecretsharingSolve()
{	
	int i;
	UpdateData(true); //Daten aus dem Dialog in die Variablen abspeichern
	Big M=1;
	Big primes[7]; for (i=0; i<7;i++){ primes[i]=1;}// Moduln m_m
	Big shares[7]; for (i=0; i<7;i++) {shares[i]=1;} //Reste m_a
	Big min_k=1; //min (k) (Produkt der k kleinsten Primzahlen)
	Big s;//Löse die Ungleichung auf. Man erhält s'
	Big w;
	Big s_;
	int anzahl=0;
	int index=0;
	CString dummy="";
	CString dum;
	CString helper="";
	CString helpme="";
	CString helping="";
	String usedKeys[7];
		
	// array resetten
	for (i=0;i<=6;i++) usedKeys[i]="";
	
	//Log-Datei beginnen
	helpme.LoadString(IDS_CRT_SECRETSHARING_REK1);
	m_log=m_log+helpme;

	// Ab hier werden die Inhalte der Textfelder ausgelesen und in den verarbeitenden Variablen gespeichert. 
	CStringToBig(m_w,w,10);
	CStringToBig(m_s,s,10);
	
	// Sicherstellen, dass ueberhaupt Kennungen und Shares errechnet worden sind
	if (m_m0 != "")		
	{
		int i;
		//Primzahlen werden ausgelesen
		//** Primzahlen in Big Array abspeichern   ** //
		if (m_anzahl >=1) CStringToBig(m_m0,primes[0],10);
		if (m_anzahl >=2) CStringToBig(m_m1,primes[1],10);
		if (m_anzahl >=3) CStringToBig(m_m2,primes[2],10);
		if (m_anzahl >=4) CStringToBig(m_m3,primes[3],10);
		if (m_anzahl >=5) CStringToBig(m_m4,primes[4],10);
		if (m_anzahl >=6) CStringToBig(m_m5,primes[5],10);
		if (m_anzahl ==7) CStringToBig(m_m6,primes[6],10);
		
		// min_k berechnen
		for (i=0;i<m_need;i++) min_k = min_k * primes[i];
		
		// array mit shares resetten
		for (i=0;i<m_anzahl;i++) shares[i]=1;

		// Zu nutzende Schlüssel werden aus dem Frame 'Rekonstruktion' ausgelesen
		if (m_reka0 !="") {CStringToBig(m_reka0,shares[anzahl],10); primes[anzahl]=primes[0]; anzahl++; usedKeys[index]=" 1";index++;}
		if (m_reka1 !="") {CStringToBig(m_reka1,shares[anzahl],10); primes[anzahl]=primes[1]; anzahl++; usedKeys[index]=" 2";index++;}
		if (m_reka2 !="") {CStringToBig(m_reka2,shares[anzahl],10); primes[anzahl]=primes[2]; anzahl++; usedKeys[index]=" 3";index++;}
		if (m_reka3 !="") {CStringToBig(m_reka3,shares[anzahl],10); primes[anzahl]=primes[3]; anzahl++; usedKeys[index]=" 4";index++;}
		if (m_reka4 !="") {CStringToBig(m_reka4,shares[anzahl],10); primes[anzahl]=primes[4]; anzahl++; usedKeys[index]=" 5";index++;}
		if (m_reka5 !="") {CStringToBig(m_reka5,shares[anzahl],10); primes[anzahl]=primes[5]; anzahl++; usedKeys[index]=" 6";index++;}
		if (m_reka6 !="") {CStringToBig(m_reka6,shares[anzahl],10); primes[anzahl]=primes[6]; anzahl++; usedKeys[index]=" 7";}

		// Starte Schluessel-Animation entsprechend der Anzahl der eingegegbenen Schluessel
		switch (anzahl) {
			case 0: {
					CString dummy2;
					dummy2.LoadString(IDS_CRT_SECRETSHARING_REK2);
					dummy.Format(dummy2,m_need);
					AfxMessageBox(dummy, MB_ICONINFORMATION );
					CString helpme;
					helpme.LoadString(IDS_CRT_SECRETSHARING_REK3);
					m_log=m_log+helpme;
					break;
					}
			case 1: {
					//Animation mit 1 Schlüssel beginnt
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF6),_T("GIF"))) {
						m_Picture.SetBkColor(RGB(0,0,0));
						m_Picture.Draw();
					}
					
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					//Ende Animation
					break;
					}
			case 2: {
					//Animation mit 2 Schlüsseln beginnt
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF7),_T("GIF")))
						{m_Picture.SetBkColor(RGB(0,0,0));	
						m_Picture.Draw();
						}
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					//Ende Animation			
					break;
					}
			case 3: {
					//Animation mit 3 Schlüsseln beginnt
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF8),_T("GIF")))
						{m_Picture.SetBkColor(RGB(0,0,0));
						m_Picture.Draw();
						}
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					//Ende Animation
					break;
					}
			case 4: {
					//Animation mit 4 Schlüsseln beginnt
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF9),_T("GIF")))
						{m_Picture.SetBkColor(RGB(0,0,0));
						m_Picture.Draw();
					}
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					//Ende Animation
					break;
					}
			case 5: {
					//Animation mit 1 Schlüssel beginnt
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF10),_T("GIF")))
						{m_Picture.SetBkColor(RGB(0,0,0));
						m_Picture.Draw();
					}
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					//Ende Animation
					break;
					}
			case 6: {
					//Animation mit 1 Schlüssel beginnt
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF13),_T("GIF")))
						{m_Picture.SetBkColor(RGB(0,0,0));
						m_Picture.Draw();
					}
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					//Ende Animation
					break;
					}
			case 7: {
					//Animation mit 1 Schlüssel beginnt
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF14),_T("GIF")))
						{m_Picture.SetBkColor(RGB(0,0,0));
						m_Picture.Draw();
					}
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					//Ende Animation
					}
		}


		//Wenn mindestens Passwort eingegeben wurde, findet eine Berechnung statt.

		
		if (!(anzahl==0))
		{	
			// Nachricht "Schluessel werden zusammen gefuegt"
			AfxMessageBox(IDS_CRT_SECRETSHARING_REK4, MB_ICONINFORMATION);
			

			//Sucht nach einem Fenster und gibt die Fenster-ID zurück.

			HWND hWnd; //Handle für das Fenster (Ist eigentlich nur eine Fenster-ID)
			hWnd = ::FindWindow(0,"CrypTool"); //Handle beschaffen
			::PostMessage(hWnd,WM_CLOSE,0,0); //WM_CLOSE Nachricht an die MessageBox schicken
			int i;

			//Fuer Log-Datei werden die Schluesselnummern aus Array in String geschrieben
			for (i=0;i<6;i++)
			{	if (!(usedKeys[i+1]=="")) dummy = dummy + usedKeys[i]+",";
				else dummy = dummy + usedKeys[i];			
			}
			CString help;
			help.LoadString(IDS_CRT_SECRETSHARING_REK5);
			helpme.Format(help,anzahl);
			m_log=m_log+helpme+dummy+"\r\n\r\n";
			
			//Hier beginnt die Rekonstruktion des Produktes M aus genutzten Kennungen
			M=1;
			for (i=0;i<anzahl;i++) M=M * primes[i];

			// Log-Datei schreiben
			CString helpme;
			helpme.LoadString(IDS_CRT_SECRETSHARING_REK9);
			m_log=m_log+helpme+"\r\n";
			BigToCString(M,helpme,10);
			m_log=m_log+helpme+"\r\n\r\n";

			//Ist M >= min_k, wurden genügend Schlüssel angegeben
			if (M >= min_k) 
			{
				// s' kann durch crt berechnet werden
				if (anzahl>1) s_ = ChinRest (anzahl,shares,primes);
				if (anzahl==1) s_ = shares[0]%primes[0];	
				helpme.LoadString(IDS_CRT_SECRETSHARING_REK10);
				m_log=m_log+helpme+"\r\n";
				BigToCString(s_,helpme,10);
				m_log=m_log+helpme+"\r\n\r\n";
			}
			else  
			// Es wurden nicht genuegend Schluessel angegeben
			{
				//Bild mit geschlossenem Schloss wird eingeblendet
				SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)

				CDialog::OnInitDialog();
				// Animation laden und Hintergrundfarbe schwarz setzen
				if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF12),_T("GIF")))
				{
					m_Picture.SetBkColor(RGB(0,0,0));
					m_Picture.Draw();
				}
				HIDE_HOUR_GLASS		// deaktiviert die Sanduhr
				
				// flomar, 05/05/2009
				// in order to compute the remaining possibilities we multiply 
				// the n smallest primes that were not chosen by the user
				int n = m_need - anzahl;
				// we store the result in remainingPossibilites
				Big remainingPossibilities = "1";
				// the following is rather ugly and could be implemented way more elegantly, 
				// but I don't have the time to mess with the other code right now;
				// basically, we go through all primes (sorted in ascending order) and 
				// multiply "remainingPossibilities" with the current prime if the 
				// user hasn't chosen this prime for reconstruction
				for(int i=0; i<6 && n>0; i++) {
					if(i == 0 && m_reka0 == "") {
						Big prime = m_m0.GetBuffer(); remainingPossibilities *= prime; n--;
					}
					else if(i == 1 && m_reka1 == "") { 
						Big prime = m_m1.GetBuffer(); remainingPossibilities *= prime; n--;
					}
					else if(i == 2 && m_reka2 == "") { 
						Big prime = m_m2.GetBuffer(); remainingPossibilities *= prime; n--;
					}
					else if(i == 3 && m_reka3 == "") { 
						Big prime = m_m3.GetBuffer(); remainingPossibilities *= prime; n--;
					}
					else if(i == 4 && m_reka4 == "") { 
						Big prime = m_m4.GetBuffer(); remainingPossibilities *= prime; n--;
					}
					else if(i == 5 && m_reka5 == "") { 
						Big prime = m_m5.GetBuffer(); remainingPossibilities *= prime; n--;
					}
					else if(i == 6 && m_reka6 == "") { 
						Big prime = m_m6.GetBuffer(); remainingPossibilities *= prime; n--;
					}
				}
				// now display the amount of remaining possibilities for the user
				CString Ctemp3;
				BigToCString(remainingPossibilities, Ctemp3, 10);
				dum.LoadString(IDS_CRT_SECRETSHARING_REK6);
				helper.Format(dum, anzahl, m_need, Ctemp3);
				AfxMessageBox(helper, MB_ICONINFORMATION);

				// Log-Datei
				helpme.LoadString(IDS_CRT_SECRETSHARING_REK7);
				helper.Format(helpme,Ctemp3);
				m_log=m_log+helper;
			}
	
			
			// Wurden die richtigen Schlüssel angegeben?
			if ((s_%w == s) && (M >= min_k))
			{	
				helper.LoadString(IDS_CRT_SECRETSHARING_REK11);
				m_log=m_log+helper+"\r\n";

				//Bild mit geoeffnetem Schloss wird eingeblendet
				SHOW_HOUR_GLASS	// aktiviert die Sanduhr (statt des Mauszeigers)
				CDialog::OnInitDialog();
				// Animation laden und Hintergrundfarbe schwarz setzen
				if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF11),_T("GIF"))) {
					m_Picture.SetBkColor(RGB(0,0,0));
					m_Picture.Draw();
				}
				BigToCString(s,dummy,10);
				HIDE_HOUR_GLASS	// deaktiviert die Sanduhr
				helpme.LoadString(IDS_CRT_SECRETSHARING_REK8);
				helping.Format(helpme,dummy);
				AfxMessageBox(helping, MB_ICONINFORMATION );	
				helping.LoadString(IDS_CRT_SECRETSHARING_SUCCESS);
				helper.Format(helping, dummy);
				m_log=m_log+helper;
			}
		
			// genügend Schlüssel aber mind. ein falscher dabei
			else 
				if (M >= min_k) {
					helper.LoadString(IDS_CRT_SECRETSHARING_REK12);
					m_log=m_log+helper+"\r\n\r\n";

					//Bild mit geschlossenem Schloss wird eingeblendet
					SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
					CDialog::OnInitDialog();
					// Animation laden und Hintergrundfarbe schwarz setzen
					if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF12),_T("GIF"))) {
						m_Picture.SetBkColor(RGB(0,0,0));
						m_Picture.Draw();
					}
					HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
					helping.LoadString(IDS_CRT_SECRETSHARING_NOSUCCESS);
					helpme.Format(helping,anzahl);
					AfxMessageBox(helpme, MB_ICONINFORMATION );	
					helpme.LoadString(IDS_CRT_SECRETSHARING_NOSUCCESS2);	
					m_log=m_log+helpme;
				}	
			}
	//Schliessende Klammer von (m_0!="")
	}
}
void CDlgCrtSecretSharing::OnBnClickedSecretsharingReset()
{
	// Alle Dialogvariablen wieder auf Standardwerte setzen; m_anzahl=5;m_need=3;m_x="2^108";m_y="2^109";
m_diverse="";m_maxkminus1="";m_w="";m_s="";m_faktorA="";
m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";m_m5="";m_m6="";
m_a0="";m_a1="";m_a2="";m_a3="";m_a4="";m_a5="";m_a6="";
m_reka0="";m_reka1="";m_reka2="";m_reka3="";m_reka4="";m_reka5="";m_reka6="";


	// Rekonstruktions-Frame: Buttons und Texfelder deaktivieren

	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_BUTTON2)->EnableWindow(false);

	GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(false);

	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(false);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(false);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(false);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(false);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(false);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(false);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(false);

	//Log-Datei leeren
	m_log="";

//Durchsichtiges GIF wird eingeblendet
SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
CDialog::OnInitDialog();

// Animation laden und Hintergrundfarbe schwarz setzen
if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF15),_T("GIF")))
{
	m_Picture.Draw();
}
HIDE_HOUR_GLASS			// deaktiviert die Sanduhr

    //Nicht mehr zu nutzende Buttons deaktivieren
	//GetDlgItem(IDC_SECRETSHARING_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(false);
	GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(false);
UpdateData(false);
}
void CDlgCrtSecretSharing::OnBnClickedSecretsharingOptions()
{
  // flomar, 12/04/2008
  UpdateData(true);

	// neues Dialog-Objekt initialisieren
	CDlgCrtSecretSharingOptions* newdialog= new CDlgCrtSecretSharingOptions();
	//Werte aus diesem Dialog in Optionen-Dialog übernehmen
	newdialog->m_x=m_x;
	newdialog->m_y=m_y;
	newdialog->m_anzahl=m_anzahl;
	newdialog->m_need=m_need;
	newdialog->calcmode=m_calcmode;

  // flomar, 12/04/2008
  // this call is a bit weird: you loose ANY INFORMATION the user has 
  // entered in the dialog fields by calling "UpdateData(false)" here;
  // instead, we should (and will) call "UpdateData(true)" (see above)
  // UpdateData(false);

	if (IDOK == newdialog->DoModal()) {
		UpdateData(true);
		
		if ((m_x !=newdialog->m_x)||(m_y !=newdialog->m_y)||(m_anzahl !=newdialog->m_anzahl)||(m_need !=newdialog->m_need)) {

      // flomar, 12/04/2008
      // the variables for the prime numbers (m_m0...m_m6) should not be deleted unless it is 
      // necessary due to a change of options (i.e. smaller n chosen by the user) 
      m_diverse="";m_maxkminus1="";m_w="";m_s="";m_faktorA="";
      //m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";m_m5="";m_m6="";
      m_a0="";m_a1="";m_a2="";m_a3="";m_a4="";m_a5="";
      m_a6="";m_reka0="";m_reka1="";m_reka2="";m_reka3="";m_reka4="";
      m_reka5="";m_reka6="";

      // flomar, 12/04/2008
      // based on how many prime numbers we need, delete the remaining ones
      if(newdialog->m_anzahl < 1) {
        // delete all prime numbers
        m_m0 = m_m1 = m_m2 = m_m3 = m_m4 = m_m5 = m_m6 = "";
      }
      if(newdialog->m_anzahl < 2) {
        // delete all prime numbers but the first one
        m_m1 = m_m2 = m_m3 = m_m4 = m_m5 = m_m6 = "";
      }
      if(newdialog->m_anzahl < 3) {
        // delete all prime numbers but the two first ones
        m_m2 = m_m3 = m_m4 = m_m5 = m_m6 = "";
      }
      if(newdialog->m_anzahl < 4) {
        // delete all prime numbers but the three first ones
        m_m3 = m_m4 = m_m5 = m_m6 = "";
      }
      if(newdialog->m_anzahl < 5) {
        // delete all prime numbers but the four first ones
        m_m4 = m_m5 = m_m6 = "";
      }
      if(newdialog->m_anzahl < 6) {
        // delete all prime numbers but the five first ones
        m_m5 = m_m6 = "";
      }
      if(newdialog->m_anzahl < 7) {
        // delete all prime numbers but the six first ones
        m_m6 = "";
      }

			// Eingetragene Daten aus Optionen-Dialog in Variablen übernehmen
			m_x = newdialog->m_x;
			m_y = newdialog->m_y;
			m_anzahl = newdialog->m_anzahl;
			m_need = newdialog->m_need;
			UpdateData(false);

			// Rekonstruktions-Frame: Buttons und Texfelder deaktivieren
			GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(false);

			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT22)->EnableWindow(false);

			GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(false);
			//GetDlgItem(IDC_SECRETSHARING_BUTTON2)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(false);

			// Wenn 'manuell' im Hauptdialog gewaehlt ist
			if (m_calcmode==1) {
				// werden entsprechende Felder fuer die Moduln freigegeben, bzw geschuetzt
				CEdit* myE;
				GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5)->EnableWindow(true);
				myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5);
				myE->SetReadOnly(false);
				if (m_anzahl>1) {
				GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6)->EnableWindow(true);
				myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6);
				myE->SetReadOnly(false);
				} else {
					myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6);	
					myE->SetReadOnly(true);
				  }
				if (m_anzahl>2) {
				GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7)->EnableWindow(true);
				myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7);
				myE->SetReadOnly(false);
				} else {
					myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7);	
					myE->SetReadOnly(true);
				  }
				if (m_anzahl>3) {
				GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8)->EnableWindow(true);
				myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8);
				myE->SetReadOnly(false);
				} else {
					myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8);	
					myE->SetReadOnly(true);
				  }
				if (m_anzahl>4) {
				GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9)->EnableWindow(true);
				myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9);
				myE->SetReadOnly(false);
				} else {
					myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9);	
					myE->SetReadOnly(true);
				  }
				if (m_anzahl>5) {
				GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b)->EnableWindow(true);
				myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b);
				myE->SetReadOnly(false);
				} else {
					myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b);	
					myE->SetReadOnly(true);
				  }
				if (m_anzahl>6) {
				GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c)->EnableWindow(true);
				myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c);
				myE->SetReadOnly(false);
				} else {
					myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c);	
					myE->SetReadOnly(true);
				  }
			}
		} // Klammer von IF-Schleife: wenn werte verändert...

			//Log-Datei leeren
			m_log="";
			//Durchsichtiges GIF wird eingeblendet
			SHOW_HOUR_GLASS	// aktiviert die Sanduhr (statt des Mauszeigers)
			CDialog::OnInitDialog();

			// Animation laden und Hintergrundfarbe schwarz setzen
			if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF15),_T("GIF")))
			{
				m_Picture.Draw();
			}
			HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
		
		} // von: Wenn OK-geklickt wurde. Wird 'abbrechen' geklickt, gelten die aktuellen Werte

	// Speicher freigeben
	delete newdialog;
	// Temporäre Variablen
	CString temp1,temp2;

	// Fenstertitel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGTITLE);
		temp2.Format((LPCTSTR)temp1,m_need,m_anzahl);
	this->SetWindowText((LPCTSTR)temp2);
	
	// GroupBox1-Titel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX1);
	temp2.Format((LPCTSTR)temp1,m_anzahl);
	GetDlgItem(IDC_CRT_FR_KO)->SetWindowText((LPCTSTR)temp2);

	// GroupBox2-Titel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX2);
	temp2.Format((LPCTSTR)temp1,m_need);
	GetDlgItem(IDC_CRT_FR_REKO)->SetWindowText((LPCTSTR)temp2);
	
	// GroupBox3-Titel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX3);
	temp2.Format((LPCTSTR)temp1,m_anzahl);
	GetDlgItem(IDC_REKOHELP)->SetWindowText((LPCTSTR)temp2);	

	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingFacts()
{
	CDlgCrtSecretSharing_Facts* newdialog= new CDlgCrtSecretSharing_Facts();
		newdialog->m_min_k=m_diverse;
		newdialog->m_max_kminus1=m_maxkminus1;
		newdialog->m_w=m_w;
		newdialog->m_s=m_s;
		newdialog->m_a=m_faktorA;		
		newdialog->m_s_=m_s_;
		newdialog->m_anzahl=m_anzahl;
		newdialog->m_need=m_need;
		newdialog->m_log=m_log;
		// Temporäre Variablen
		CString temp1, temp2;
		Big w, s, s_, a, anzahl;
		Big shares[7], primes[7];
	
		// Punkt 1. dynamisch anzeigen
		temp1.LoadString(IDS_CRT_SECRETSHARING_FACTS1);
		temp2.Format((LPCTSTR)temp1,m_need);
		newdialog->m_CrtFacts1=temp2;

		// Punkt 2. dynamisch anzeigen
		temp1.LoadString(IDS_CRT_SECRETSHARING_FACTS2);
		temp2.Format((LPCTSTR)temp1,m_need-1);
		newdialog->m_CrtFacts2=temp2;
		UpdateData(false);

		// Nachdem OK geklickt wurde....
		if (IDOK == newdialog->DoModal())	{

		// Rekonstruktions-GroupBox aktivieren
		// Buttons:
		GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(true);
		GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(true);
	
		// Textfelder
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(true);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT22)->EnableWindow(true);

		anzahl=m_anzahl;

		// nun Nicht benötigte Dialogfelder aus allen Gruppierungen deaktivieren

		if (anzahl<7) {// für Paar Nummer 7
			GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(false);
		    GetDlgItem(IDC_CRT_SECRETSHARINGEDIT22)->EnableWindow(false);
		}
		if (anzahl<6) {// für Paar Nummer 6
		    GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(false);
		    GetDlgItem(IDC_CRT_SECRETSHARINGEDIT21)->EnableWindow(false);
		}
		if (anzahl<5) {// für Paar Nummer 5
			GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(false);
		}
		if (anzahl<4) {// für Paar Nummer 4
			GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(false);
		}
		if (anzahl<3) {// für Paar Nummer 3
			GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(false);
		}
		if (anzahl<2) {// für Paar Nummer 2
			GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(false);
		}
		if (anzahl<1) {// für Paar Nummer 1
			GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(false);
			GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(false);
		}

			// wird geprüft, ob s oder a verändert wurden...
		if ((m_s != newdialog->m_s) || (m_faktorA!= newdialog->m_a)) {
			// falls ja, werden neue Werte übernommen
			m_s=newdialog->m_s;
			m_faktorA=newdialog->m_a;
			
			// Shares neu berechnen
			// primes-Array wieder auffüllen
			if (m_anzahl >=1) CStringToBig(m_m0,primes[0],10);
			if (m_anzahl >=2) CStringToBig(m_m1,primes[1],10);
			if (m_anzahl >=3) CStringToBig(m_m2,primes[2],10);
			if (m_anzahl >=4) CStringToBig(m_m3,primes[3],10);
			if (m_anzahl >=5) CStringToBig(m_m4,primes[4],10);
			if (m_anzahl >=6) CStringToBig(m_m5,primes[5],10);
			if (m_anzahl ==7) CStringToBig(m_m6,primes[6],10);

			// w, s und a in big konvertieren
			CStringToBig(m_w,w,10);
			CStringToBig(m_s,s,10);
			CStringToBig(m_faktorA,a,10);
			// Basis für die erneute Berechnung der shares ermitteln
			s_= a*w+s;
			BigToCString(s_, m_s_);
			
			// shares berechnen
			for (int i=0;i<m_anzahl;i++) shares[i]= s_ % primes[i];
			// shares in Dialogfeld-variablen abspeichern
			if (m_anzahl >=1) BigToCString(shares[0],m_a0);
			if (m_anzahl >=2) BigToCString(shares[1],m_a1);
			if (m_anzahl >=3) BigToCString(shares[2],m_a2);
			if (m_anzahl >=4) BigToCString(shares[3],m_a3);
			if (m_anzahl >=5) BigToCString(shares[4],m_a4);
			if (m_anzahl >=6) BigToCString(shares[5],m_a5);
			if (m_anzahl ==7) BigToCString(shares[6],m_a6);
			
			UpdateData(false);
		}
	}
	delete newdialog;
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingLog()
{
	CDlgCrtSecretSharing_Log* newdialog= new CDlgCrtSecretSharing_Log();
		newdialog->m_log = m_log;
		newdialog->m_need = m_need;
		newdialog->m_anzahl = m_anzahl;
	
	if (IDOK == newdialog->DoModal())	{}
	delete newdialog;
}

void CDlgCrtSecretSharing::OnBnClickedOk()
{	
#if !defined(_MSC_VER) || _MSC_VER <= 1200		
	theApp.WinHelp( IDD_CRT_SECRETSHARING+0x20000 );
#else											
// HTML Help for VC++ .NET
    theApp.WinHelpInternal( IDD_CRT_SECRETSHARING+0x20000 );
#endif

// 	theApp.WinHelpInternal(IDD_CRT_SECRETSHARING+0x20000);  // FIXME
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd1()
{
	UpdateData();
	if (m_reka0 != "") 
		m_reka0="";
	else 
		m_reka0=m_a0;	
	UpdateData(false);
}
void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd2()
{
	UpdateData();
	if (m_reka1 != "") 
		m_reka1="";
	else 
		m_reka1=m_a1;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd3()
{
	UpdateData();
	if (m_reka2 != "") 
		m_reka2="";
	else 
		m_reka2=m_a2;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd4()
{
	UpdateData();
	if (m_reka3 != "") 
		m_reka3="";
	else 
		m_reka3=m_a3;
	UpdateData(false);
}


void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd5()
{
	UpdateData();
	if (m_reka4 != "") 
		m_reka4="";
	else 
		m_reka4=m_a4;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd6()
{
	UpdateData();
	if (m_reka5 != "") 
		m_reka5="";
	else 
		m_reka5=m_a5;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd7()
{
	UpdateData();
	if (m_reka6 != "") 
		m_reka6="";
	else 
		m_reka6=m_a6;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingEnd()
{
	UpdateData();
	UpdateData(false);

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "CrtSecretSharing" ) == ERROR_SUCCESS )
	{
		unsigned long showIntroDialog = m_Info;
		CT_WRITE_REGISTRY(showIntroDialog, "ShowIntroDialog");
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}	
	OnOK();
}
void CDlgCrtSecretSharing::OnBnClickedCrtRadioAut()
{
	m_calcmode=0;
	OnBnClickedSecretsharingReset();
	CEdit* myE;
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5);
	myE->SetReadOnly(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6);
	myE->SetReadOnly(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7);
	myE->SetReadOnly(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8);
	myE->SetReadOnly(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9);
	myE->SetReadOnly(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b);
	myE->SetReadOnly(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c);
	myE->SetReadOnly(true);
	UpdateData(false);
	}


void CDlgCrtSecretSharing::OnBnClickedCrtRadioMan()
{
	m_calcmode=1;
	OnBnClickedSecretsharingReset();
	CEdit* myE;
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5)->EnableWindow(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5);
    myE->SetReadOnly(false);
	
	if (m_anzahl>1) {
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6)->EnableWindow(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6);
	myE->SetReadOnly(false);
	}
	if (m_anzahl>2) {
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7)->EnableWindow(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7);
	myE->SetReadOnly(false);
	}
	if (m_anzahl>3) {
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8)->EnableWindow(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8);
	myE->SetReadOnly(false);
	}
	if (m_anzahl>4) {
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9)->EnableWindow(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9);
	myE->SetReadOnly(false);
	}
	if (m_anzahl>5) {
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b)->EnableWindow(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9b);
	myE->SetReadOnly(false);
	}
	if (m_anzahl>6) {
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c)->EnableWindow(true);
	myE = (CEdit*) GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9c);
	myE->SetReadOnly(false);
	}
	UpdateData(false);

}