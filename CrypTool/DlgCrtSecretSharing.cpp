/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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
	, m_noInfo(FALSE)
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
	DDX_Text(pDX, IDC_EDIT1, m_m5);
	DDX_Text(pDX, IDC_EDIT132, m_m6);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT10, m_a0);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT11, m_a1);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT12, m_a2);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT13, m_a3);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT14, m_a4);
	DDX_Text(pDX, IDC_EDIT2, m_a5);
	DDX_Text(pDX, IDC_EDIT133, m_a6);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT16, m_reka0);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT17, m_reka1);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT18, m_reka2);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT19, m_reka3);
	DDX_Text(pDX, IDC_CRT_SECRETSHARINGEDIT20, m_reka4);
	DDX_Text(pDX, IDC_EDIT5, m_reka5);
	DDX_Text(pDX, IDC_EDIT4, m_reka6);
	DDX_Control(pDX, IDC_CRT_Anim, m_Picture);
	DDX_Check(pDX, IDC_CRT_SHOWDIALOG, m_noInfo);
}


BEGIN_MESSAGE_MAP(CDlgCrtSecretSharing, CDialog)
	ON_BN_CLICKED(IDC_SECRETSHARING_BUTTON1, OnBnClickedSecretsharingSolve)
	ON_BN_CLICKED(IDC_SECRETSHARING_BUTTON2, OnBnClickedSecretsharingReset)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD1, OnBnClickedSecretsharingAdd1)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD2, OnBnClickedSecretsharingAdd2)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD3, OnBnClickedSecretsharingAdd3)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD4, OnBnClickedSecretsharingAdd4)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD5, OnBnClickedSecretsharingAdd5)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD6, OnBnClickedSecretsharingAdd6)
	ON_BN_CLICKED(IDC_SECRETSHARING_ADD7, OnBnClickedSecretsharingAdd7)
	ON_BN_CLICKED(IDC_SECRETSHARING_ALGO, OnBnClickedSecretsharingAlgo)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_SECRETSHARING_FACTS, OnBnClickedSecretsharingFacts)
	ON_BN_CLICKED(IDC_SECRETSHARING_LOG, OnBnClickedSecretsharingLog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
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


			// Intro-Screen anzeigen (falls nicht in INI-Datei deaktiviert)
			if(theApp.GetProfileInt("Settings", "CRT_IntroDialogue", 1))
			{
			DlgCrtSecretSharing_Info* newdialog= new DlgCrtSecretSharing_Info();
			newdialog->DoModal();
			this->m_noInfo=newdialog->m_checkNoInfo;
			}
			UpdateData(false);

				
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
		int k;

		m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";m_m5="";m_m6="";
		bool solve [7];
		for (k=0;k<7;k++) solve[k]=false;

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

		if ((anzahl>5)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")&&(m_m3!="")&&(m_m4!="")) {
			for (k=0;k<10;k++) {
				if ((GetRandomPrime( m_m5, P ))&&(m_m5!=m_m0)&&(m_m5!=m_m1)&&(m_m5!=m_m2)&&(m_m5!=m_m3)&&(m_m5!=m_m4)) {solve[5]=true;break;}
			}
		
		}
		if ((anzahl>6)&&(m_m0!="")&&(m_m1!="")&&(m_m2!="")&&(m_m3!="")&&(m_m4!="")&&(m_m5!="")) {
			for (k=0;k<10;k++) {
				if ((GetRandomPrime( m_m6, P ))&&(m_m6!=m_m0)&&(m_m6!=m_m1)&&(m_m6!=m_m2)&&(m_m6!=m_m3)&&(m_m6!=m_m4)&&(m_m6!=m_m5)) {solve[6]=true;break;}
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

		// Rekonstruktions-Frame: Buttons und Texfelder deaktivieren
	GetDlgItem(IDC_STATIC1)->EnableWindow(false);
	GetDlgItem(IDC_STATIC2)->EnableWindow(false);
	GetDlgItem(IDC_STATIC3)->EnableWindow(false);
	GetDlgItem(IDC_STATIC4)->EnableWindow(false);
	GetDlgItem(IDC_STATIC5)->EnableWindow(false);
	GetDlgItem(IDC_STATIC6)->EnableWindow(false);
	GetDlgItem(IDC_STATIC7)->EnableWindow(false);
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
	GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	GetDlgItem(IDC_EDIT4)->EnableWindow(false);
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


		AfxMessageBox(IDS_CRT_SECRETSHARING_GENERATEPRIME, MB_ICONINFORMATION );correct=false;
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
	if (anzahl >=6) BigToCString(primes[5],m_m5);
	if (anzahl ==7) BigToCString(primes[6],m_m6);

	//** Alle Felder aktivieren, falls sie vorher nicht benötigt worden sind  ** //	
	GetDlgItem(IDC_EDIT132)->EnableWindow(true);
	GetDlgItem(IDC_EDIT1)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5)->EnableWindow(true);

	GetDlgItem(IDC_EDIT133)->EnableWindow(true);
	GetDlgItem(IDC_EDIT2)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT14)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT13)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT12)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT11)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT10)->EnableWindow(true);

	// Rekonstruktionsfelder
	GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(true);
	GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(true);
	GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(true);
	GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(true);
	GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(true);
	GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(true);
	GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(true);

	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(true);
	GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(true);
	GetDlgItem(IDC_EDIT5)->EnableWindow(true);
	GetDlgItem(IDC_EDIT4)->EnableWindow(true);

	GetDlgItem(IDC_STATIC7)->EnableWindow(true);
	GetDlgItem(IDC_STATIC6)->EnableWindow(true);
	GetDlgItem(IDC_STATIC5)->EnableWindow(true);
	GetDlgItem(IDC_STATIC4)->EnableWindow(true);
	GetDlgItem(IDC_STATIC3)->EnableWindow(true);
	GetDlgItem(IDC_STATIC2)->EnableWindow(true);
	GetDlgItem(IDC_STATIC1)->EnableWindow(true);

	// nun Nicht benötigte Dialogfelder aus allen Gruppierungen deaktivieren
	if (anzahl<7) {// für Paar Nummer 7
		GetDlgItem(IDC_EDIT132)->EnableWindow(false);
        GetDlgItem(IDC_EDIT133)->EnableWindow(false);
        GetDlgItem(IDC_SECRETSHARING_ADD7)->EnableWindow(false);
        GetDlgItem(IDC_STATIC7)->EnableWindow(false);
        GetDlgItem(IDC_EDIT4)->EnableWindow(false);
	}
	if (anzahl<6) {// für Paar Nummer 6
		GetDlgItem(IDC_EDIT1)->EnableWindow(false);
        GetDlgItem(IDC_EDIT2)->EnableWindow(false);
        GetDlgItem(IDC_SECRETSHARING_ADD6)->EnableWindow(false);
        GetDlgItem(IDC_STATIC6)->EnableWindow(false);
        GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	}
	if (anzahl<5) {// für Paar Nummer 5
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT9)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT14)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD5)->EnableWindow(false);
		GetDlgItem(IDC_STATIC5)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT20)->EnableWindow(false);
	}
	if (anzahl<4) {// für Paar Nummer 4
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT8)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT13)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD4)->EnableWindow(false);
		GetDlgItem(IDC_STATIC4)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT19)->EnableWindow(false);
	}
	if (anzahl<3) {// für Paar Nummer 3
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT7)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT12)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD3)->EnableWindow(false);
		GetDlgItem(IDC_STATIC3)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT18)->EnableWindow(false);
	}
	if (anzahl<2) {// für Paar Nummer 2
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT6)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT11)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD2)->EnableWindow(false);
		GetDlgItem(IDC_STATIC2)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT17)->EnableWindow(false);
	}
	if (anzahl<1) {// für Paar Nummer 1
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT5)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT10)->EnableWindow(false);
		GetDlgItem(IDC_SECRETSHARING_ADD1)->EnableWindow(false);
		GetDlgItem(IDC_STATIC1)->EnableWindow(false);
		GetDlgItem(IDC_CRT_SECRETSHARINGEDIT16)->EnableWindow(false);}
	
	if ((m_m0.GetLength()>33) || (m_m1.GetLength()>33) || (m_m2.GetLength()>33) || (m_m3.GetLength()>33) || (m_m4.GetLength()>33)|| (m_m5.GetLength()>33)|| (m_m6.GetLength()>33)) {
		m_diverse="";m_maxkminus1="";m_w="";m_s="";m_faktorA="";
m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";m_m5="";m_m6="";m_a0="";
m_a1="";m_a2="";m_a3="";m_a4="";m_a5="";m_a6="";m_reka0="";m_reka1="";
m_reka2="";m_reka3="";m_reka4="";m_reka5="";m_reka6="";
GetDlgItem(IDC_STATIC1)->EnableWindow(false);
	GetDlgItem(IDC_STATIC2)->EnableWindow(false);
	GetDlgItem(IDC_STATIC3)->EnableWindow(false);
	GetDlgItem(IDC_STATIC4)->EnableWindow(false);
	GetDlgItem(IDC_STATIC5)->EnableWindow(false);
	GetDlgItem(IDC_STATIC6)->EnableWindow(false);
	GetDlgItem(IDC_STATIC7)->EnableWindow(false);
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
	GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	GetDlgItem(IDC_EDIT4)->EnableWindow(false);
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

// Methode wird gestartet, wenn auf den Button 'Loesen' geklickt wird
// Sie führt die angegebenen Shares zusammen und versucht, das Geheimnis zu lueften
void CDlgCrtSecretSharing::TestSecretSharing()
{	
	UpdateData(true); //Daten aus dem Dialog in die Variablen abspeichern
	Big M=1;
	Big primes[7]; // Moduln m_m
	Big shares[7]; //Reste m_a
	Big min_k=1; //min (k) (Produkt der k kleinsten Primzahlen)
	Big s;//Löse die Ungleichung auf. Man erhält s'
	Big w;
	Big s_;
	int anzahl=0;
	int anz_shares=0;
	CString dummy="";
	CString helper="";
	// folgende Variablen werden genutzt um festzuhalten, welche Schluessel zur Rekonstruktion gebraucht werden
	int index=0;
	String usedKeys[7];
	for (int i=0;i<=6;i++) usedKeys[i]="";
	
	//Log-Datei beginnen
	CString helpme;
	helpme.LoadString(IDS_CRT_SECRETSHARING_REK1);
	m_log=m_log+helpme;

	// Ab hier werden die Inhalte der Textfelder ausgelesen und in den verarbeitenden Variablen gespeichert. 
	CStringToBig(m_w,w,10);
	CStringToBig(m_s,s,10);
	
	if (m_m0 != "")	
	{
	//Primzahlen werden ausgelesen
	//** Primzahlen in Big Array abspeichern   ** //
	if (m_anzahl >=1) CStringToBig(m_m0,primes[0],10);
	if (m_anzahl >=2) CStringToBig(m_m1,primes[1],10);
	if (m_anzahl >=3) CStringToBig(m_m2,primes[2],10);
	if (m_anzahl >=4) CStringToBig(m_m3,primes[3],10);
	if (m_anzahl >=5) CStringToBig(m_m4,primes[4],10);
	if (m_anzahl >=6) CStringToBig(m_m5,primes[5],10);
	if (m_anzahl ==7) CStringToBig(m_m6,primes[6],10);
		
		int i;
		
		for (i=0;i<m_need;i++) min_k = min_k * primes[i];
		for (i=0;i<m_anzahl;i++) shares[i]=1;

		// Benutze Schlüssel werden aus dem Frame 'Rekonstruktion' ausgelesen
		if (m_reka0 !="") {CStringToBig(m_reka0,shares[anzahl],10); primes[anzahl]=primes[0]; anzahl++; anz_shares++; usedKeys[index]=" 1";index++;}
		if (m_reka1 !="") {CStringToBig(m_reka1,shares[anzahl],10); primes[anzahl]=primes[1]; anzahl++; anz_shares++; usedKeys[index]=" 2";index++;}
		if (m_reka2 !="") {CStringToBig(m_reka2,shares[anzahl],10); primes[anzahl]=primes[2]; anzahl++; anz_shares++; usedKeys[index]=" 3";index++;}
		if (m_reka3 !="") {CStringToBig(m_reka3,shares[anzahl],10); primes[anzahl]=primes[3]; anzahl++; anz_shares++; usedKeys[index]=" 4";index++;}
		if (m_reka4 !="") {CStringToBig(m_reka4,shares[anzahl],10); primes[anzahl]=primes[4]; anzahl++; anz_shares++; usedKeys[index]=" 5";index++;}
		if (m_reka5 !="") {CStringToBig(m_reka5,shares[anzahl],10); primes[anzahl]=primes[5]; anzahl++; anz_shares++; usedKeys[index]=" 6";index++;}
		if (m_reka6 !="") {CStringToBig(m_reka6,shares[anzahl],10); primes[anzahl]=primes[6]; anzahl++; anz_shares++; usedKeys[index]=" 7";}
	
	
		//Hier wird geprüft, wieviele Shares zum Lösen eingefügt worden sind. 
		//Dementsprechend werden unterschiedliche Animationen gestartet
		if (anz_shares==0) 
			{
			CString dummy2;
			dummy2.LoadString(IDS_CRT_SECRETSHARING_REK2);
			dummy.Format(dummy2,m_need);
			AfxMessageBox( dummy, MB_ICONINFORMATION );
			CString helpme;
			helpme.LoadString(IDS_CRT_SECRETSHARING_REK3);
			m_log=m_log+helpme;
			}
			else if (anz_shares==1)
			{
				//Animation mit 1 Schlüssel beginnt
				SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
				CDialog::OnInitDialog();
				// Animation laden und Hintergrundfarbe schwarz setzen
				if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF6),_T("GIF")))
					{m_Picture.SetBkColor(RGB(0,0,0));
				m_Picture.Draw();
					}
				HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
				//Ende Animation
			}
				else if (anz_shares==2)
				{
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
				}
					else if (anz_shares==3)
					{
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
					}
					else if (anz_shares==4)
						{
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
						}
							else if (anz_shares==5)
							{
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
							}
								else if (anz_shares==6)
								{
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
								}
									
									else if (anz_shares==7)
									{
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
		
		//Wenn mindestens Passwort eingegeben wurde, findet eine Berechnung statt.
		if (!(anzahl==0))
		{	//Hier beginnt die Berechnung des Geheimnisses					
			for (i=0;i<anzahl;i++) M=M * primes[i];	
			AfxMessageBox( IDS_CRT_SECRETSHARING_REK4, MB_ICONINFORMATION );
			
			//Fuer Log-Datei werden die Schluessel aus array in string geschrieben
			dummy="";
			for (i=0;i<6;i++)
			{	if (!(usedKeys[i+1]=="")) dummy = dummy + usedKeys[i]+",";
				else dummy = dummy + usedKeys[i];			
			}
			
			//dummy.Format("%i",anzahl);
			CString helpme;
			helpme.LoadString(IDS_CRT_SECRETSHARING_REK5);
			m_log=m_log+helpme+dummy+"\r\n\r\n";
		if (M >= min_k) 
		{
			if (anzahl>1) s_ = ChinRest (anzahl,shares,primes);
			if (anzahl==1) s_ = shares[0]%primes[0];
		}
		else  
		{
			//Bild mit geschlossenem Schloss wird eingeblendet
			SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
			CDialog::OnInitDialog();
			// Animation laden und Hintergrundfarbe schwarz setzen
			if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF12),_T("GIF")))
			{m_Picture.SetBkColor(RGB(0,0,0));
			m_Picture.Draw();
			}
			HIDE_HOUR_GLASS			// deaktiviert die Sanduhr		
			CString dum;
			dum.LoadString(IDS_CRT_SECRETSHARING_REK6);
			helper.Format(dum,anzahl,m_need);
			AfxMessageBox( helper, MB_ICONINFORMATION );
			CString helpme;
			helpme.LoadString(IDS_CRT_SECRETSHARING_REK7);
			m_log=m_log+helpme;
		}
	
		if (s_%w == s)
		{
			//Bild mit geoeffnetem Schloss wird eingeblendet
			SHOW_HOUR_GLASS	// aktiviert die Sanduhr (statt des Mauszeigers)
			CDialog::OnInitDialog();
			// Animation laden und Hintergrundfarbe schwarz setzen
			if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF11),_T("GIF")))
			{m_Picture.SetBkColor(RGB(0,0,0));
			m_Picture.Draw();
			}
			HIDE_HOUR_GLASS	// deaktiviert die Sanduhr
			CString helpme;
			helpme.LoadString(IDS_CRT_SECRETSHARING_REK8);
				
			CString helping;
			helping.Format(helpme,m_s);
			AfxMessageBox(helping, MB_ICONINFORMATION );	
			helping.LoadString(IDS_CRT_SECRETSHARING_SUCCESS);
			helper.Format(helping, m_s);
			m_log=m_log+helper;
		}
		else if (M >= min_k)
		{
			//Bild mit geschlossenem Schloss wird eingeblendet
			SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
			CDialog::OnInitDialog();
			// Animation laden und Hintergrundfarbe schwarz setzen
			if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF12),_T("GIF")))
			{m_Picture.SetBkColor(RGB(0,0,0));
			m_Picture.Draw();
			}
			HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
			CString helping;CString helpme;
			helping.LoadString(IDS_CRT_SECRETSHARING_NOSUCCESS);
			helpme.Format(helping,anzahl);
			AfxMessageBox(helpme, MB_ICONINFORMATION );	
			helpme.LoadString(IDS_CRT_SECRETSHARING_NOSUCCESS2);	
			m_log=m_log+helpme;
		}
		}
}
	
}

//In der folgenden Prozedur wird der Hinweg durhgeführt, 
//d.h. die Shares erzeugt, mit deren Hilfe das Geheimnis
//später wieder rekonstruiert werden kann.
void CDlgCrtSecretSharing::OnBnClickedSecretsharingSolve()
{
	//Daten aus dem Dialog in die Variablen abspeichern
	UpdateData(true); 
	// Bei einer neuen Berechnung die alten Passwörter aus dem Dialog löschen
	m_reka0="";m_reka1="";m_reka2="";m_reka3="";m_reka4="";m_reka5="";m_reka6="";
	UpdateData(false);
	int t = m_anzahl;//wie viele Parteien es geben soll (t)
	int k = m_need;//wie viele Parteien zur Lösung benötigt werden sollen (k)
	Big primes[7]; // Moduln m_m
	Big shares[7]; //Reste m_a
	Big min_k=1; //min (k) (Produkt der k kleinsten Primzahlen)
	Big max_kminus1=1; //max (k-1) (Produkt der größten k-1 Primzahlen)
	Big w; //( Quotient aus 4. und 5.; auf die ganze Zahl abgerundet) -> wie oft geht min(k) in max(k-1)
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

	//** Primzahlen generieren **//
	GeneratePrime(m_anzahl, primes);
	helpme.LoadString(IDS_CRT_SECRETSHARING_CREATE6);
	m_log=m_log+helpme+"_1: \r\n"+m_m0+"\r\n"+helpme+"_2: \r\n"+m_m1+"\r\n";
	if (m_anzahl > 2) m_log=m_log+helpme+"_3: \r\n"+m_m2+"\r\n";
	if (m_anzahl > 3) m_log=m_log+helpme+"_4: \r\n"+m_m3+"\r\n";
	if (m_anzahl > 4) m_log=m_log+helpme+"_5: \r\n"+m_m4+"\r\n";
	if (m_anzahl > 5) m_log=m_log+helpme+"_6: \r\n"+m_m5+"\r\n";
	if (m_anzahl > 6) m_log=m_log+helpme+"_7: \r\n"+m_m6+"\r\n";


	if (m_m0 !="") {

	int i;

	t = m_anzahl;k = m_need;
	min_k=1;max_kminus1=1; 
	//** Ermitteln des Geheimnisses **//
	// -> Erzeugen von min_k
	for (i=0;i<k;i++) min_k = min_k * primes[i];
	// -> Erzeugen von max_k-1
	for (i=t-1;i>=t-(k-1);i--) max_kminus1 = max_kminus1 * primes[i];
	// -> Erzeugen von w
	w = min_k/max_kminus1;
	if (w==0) w=1;
	//das Geheimnis = Zufallswert zwischen 0 und w
	s=rand(w+1); 
	//zufallszahl zwischen 0 und (mink/w)-1	

	a=rand(((min_k)/w)); 

	s_= a*w+s;
	//**Ableiten der Shares **//
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

	//** Shares im Dialog anzeigen und Log-Datei weiter führen  ** //	
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

	//Animation beginnt Schloß eingeblendet
	SHOW_HOUR_GLASS				// aktiviert die Sanduhr (statt des Mauszeigers)
	CDialog::OnInitDialog();
	// Animation laden und Hintergrundfarbe schwarz setzen
	if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF5),_T("GIF")))
		{m_Picture.SetBkColor(RGB(0,0,0));
		m_Picture.Draw();
		}
	HIDE_HOUR_GLASS			// deaktiviert die Sanduhr
	}
	helpme.LoadString(IDS_CRT_SECRETSHARING_FINISH);
	m_log+=helpme;

	GetDlgItem(IDC_SECRETSHARING_BUTTON2)->EnableWindow(true);
	//Ab jetzt zu nutzende Buttons aktivieren
	if (m_m0!="") {
	GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(true);
	GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);

	}
	
	// Daten werden aus den Variablen in die Dialogfelder geschrieben
	UpdateData(false);	
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingReset()
{
	// Alle Dialogvariablen wieder leeren
m_anzahl=5;m_need=3;m_x="2^108";m_y="2^109";m_diverse="";m_maxkminus1="";m_w="";m_s="";m_faktorA="";
m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";
m_m5="";m_m6="";m_a0="";m_a1="";m_a2="";m_a3="";m_a4="";m_a5="";
m_a6="";m_reka0="";m_reka1="";m_reka2="";m_reka3="";m_reka4="";
m_reka5="";m_reka6="";


	// Rekonstruktions-Frame: Buttons und Texfelder deaktivieren
	GetDlgItem(IDC_STATIC1)->EnableWindow(false);
	GetDlgItem(IDC_STATIC2)->EnableWindow(false);
	GetDlgItem(IDC_STATIC3)->EnableWindow(false);
	GetDlgItem(IDC_STATIC4)->EnableWindow(false);
	GetDlgItem(IDC_STATIC5)->EnableWindow(false);
	GetDlgItem(IDC_STATIC6)->EnableWindow(false);
	GetDlgItem(IDC_STATIC7)->EnableWindow(false);
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
	GetDlgItem(IDC_EDIT5)->EnableWindow(false);
	GetDlgItem(IDC_EDIT4)->EnableWindow(false);

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


void CDlgCrtSecretSharing::OnBnClickedOk()
{	
	#if !defined(_MSC_VER) || _MSC_VER <= 1200  // HTML Help for VC++ 6.0
	theApp.WinHelp(IDD_CRT_SECRETSHARING+0x20000);
	#else
	theApp.WinHelpInternal(IDD_CRT_SECRETSHARING+0x20000);
	#endif
}

void CDlgCrtSecretSharing::OnBnClickedButton1()
{
TestSecretSharing();
}
void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd1()
{
	if (m_reka0 != "") m_reka0="";
	else m_reka0=m_a0;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd2()
{
	if (m_reka1 != "") m_reka1="";
	else m_reka1=m_a1;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd3()
{
	if (m_reka2 != "") m_reka2="";
	else m_reka2=m_a2;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd4()
{
	if (m_reka3 != "") m_reka3="";
	else m_reka3=m_a3;
	UpdateData(false);
}


void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd5()
{
	if (m_reka4 != "") m_reka4="";
	else m_reka4=m_a4;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd6()
{
	if (m_reka5 != "") m_reka5="";
	else m_reka5=m_a5;	
	UpdateData(false);
}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAdd7()
{
if (m_reka6 != "") m_reka6="";
	else m_reka6=m_a6;	
	UpdateData(false);}

void CDlgCrtSecretSharing::OnBnClickedSecretsharingAlgo()
{
	UpdateData(true);
	// In CrypTool.INI ablegen, ob der Intro-Dialogue beim nächsten Start wieder aufgerufen werden soll
	this->m_noInfo ? theApp.WriteProfileInt("Settings", "CRT_IntroDialogue", 1) : theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 0);
	
	OnOK();
}


void CDlgCrtSecretSharing::OnBnClickedButton4()
{	
	// neues Dialog-Objekt initialisieren
	CDlgCrtSecretSharingOptions* newdialog= new CDlgCrtSecretSharingOptions();
	//Werte aus diesem Dialog in Optionen-Dialog übernehmen
	newdialog->m_x=m_x;
	newdialog->m_y=m_y;
	newdialog->m_anzahl=m_anzahl;
	newdialog->m_need=m_need;
	UpdateData(false);

	if (IDOK == newdialog->DoModal()) {
		UpdateData(true);
		
		if ((m_x !=newdialog->m_x)||(m_y !=newdialog->m_y)||(m_anzahl !=newdialog->m_anzahl)||(m_need !=newdialog->m_need)) {

			m_diverse="";m_maxkminus1="";m_w="";m_s="";m_faktorA="";
			m_m0="";m_m1="";m_m2="";m_m3="";m_m4="";
			m_m5="";m_m6="";m_a0="";m_a1="";m_a2="";m_a3="";m_a4="";m_a5="";
			m_a6="";m_reka0="";m_reka1="";m_reka2="";m_reka3="";m_reka4="";
			m_reka5="";m_reka6="";
			// Rekonstruktions-Frame: Buttons und Texfelder deaktivieren
			{GetDlgItem(IDC_STATIC1)->EnableWindow(false);
			GetDlgItem(IDC_STATIC2)->EnableWindow(false);
			GetDlgItem(IDC_STATIC3)->EnableWindow(false);
			GetDlgItem(IDC_STATIC4)->EnableWindow(false);
			GetDlgItem(IDC_STATIC5)->EnableWindow(false);
			GetDlgItem(IDC_STATIC6)->EnableWindow(false);
			GetDlgItem(IDC_STATIC7)->EnableWindow(false);
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
			GetDlgItem(IDC_EDIT5)->EnableWindow(false);
			GetDlgItem(IDC_EDIT4)->EnableWindow(false);

			GetDlgItem(IDC_SECRETSHARING_FACTS)->EnableWindow(false);
			//GetDlgItem(IDC_SECRETSHARING_BUTTON2)->EnableWindow(false);
			GetDlgItem(IDC_SECRETSHARING_LOG)->EnableWindow(false);
			}

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

			m_x = newdialog->m_x;
			m_y = newdialog->m_y;
			m_anzahl = newdialog->m_anzahl;
			m_need = newdialog->m_need;
			
			UpdateData(false);
		}
	}
			
		
	// Wird 'abbrechen' geklickt, gelten die aktuellen Werte

	// Speicher freigeben
	delete newdialog;
	// Temporäre Variablen
	CString temp1,temp2;

	// Fenstertitel dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGTITLE);
		temp2.Format((LPCTSTR)temp1,m_need,m_anzahl);
	this->SetWindowText((LPCTSTR)temp2);
	
	// GroupBox dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX1);
	temp2.Format((LPCTSTR)temp1,m_anzahl);
	GetDlgItem(IDC_CRT_FR_KO)->SetWindowText((LPCTSTR)temp2);

	// GroupBox dynamisch anzeigen
	temp1.LoadString(IDS_CRT_SECRETSHARINGGROUPBOX2);
	temp2.Format((LPCTSTR)temp1,m_need);
	GetDlgItem(IDC_CRT_FR_REKO)->SetWindowText((LPCTSTR)temp2);
	
	// GroupBox dynamisch anzeigen
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
	
		// Punkt 1. dynamisch anzeigen
		temp1.LoadString(IDS_CRT_SECRETSHARING_FACTS1);
		temp2.Format((LPCTSTR)temp1,m_need);
		newdialog->m_CrtFacts1=temp2;

		// Punkt 2. dynamisch anzeigen
		temp1.LoadString(IDS_CRT_SECRETSHARING_FACTS2);
		temp2.Format((LPCTSTR)temp1,m_need-1);
		newdialog->m_CrtFacts2=temp2;
		UpdateData(false);
	if (IDOK == newdialog->DoModal())	{}
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
