/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


// DlgHybridDecryptionDemo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include <fstream>
#include "FileTools.h"
#include <sys\stat.h>
#include "Cryptography.h"
#include "CryptDoc.h"
#include "AppDocument.h"
#include "s_ecconv.h"
#include "IntegerArithmetic.h"
#include <mbstring.h>
#include "DlgKeyHex.h"	// Dialog-Box f�r die Schl�sseleingabe
#include "DlgKeyHexAnalysis.h"
#include "DlgKeyAsymGeneration.h"
#include "DlgShowKeyParameter.h"
#include "DialogeMessage.h"
#include "DlgHybridDecryptionDemo.h"
#include "DlgKeyAsymGeneration.h"
#include "SecudeTools.h"
#include "DlgShowCertificate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char* CaPseDatei;
extern char* CaPseVerzeichnis, *PseVerzeichnis;
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgHybridDecryptionDemo 


CDlgHybridDecryptionDemo::CDlgHybridDecryptionDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHybridDecryptionDemo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHybridDecryptionDemo)
	m_TextSignSteps = _T("");
	m_Step = _T("");
	m_DisplayData = _T("");
	//}}AFX_DATA_INIT
	step = 0;
	DecSessionKey="";
	m_iIsGenAsymKey = false;
	m_Cert = new CPSEDemo;

}


void CDlgHybridDecryptionDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHybridDecryptionDemo)
	DDX_Control(pDX, IDC_EDIT_SHOW_STEPS, m_DisplayDataCtrl);
	DDX_Control(pDX, IDC_EDIT4, m_StepCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_TextSignStepsCtrl);
	DDX_Control(pDX, IDOK, m_FlushDecDataCtrl);
	DDX_Control(pDX, IDC_BUTTON_CONTINUE, m_ContinueButtonCtrl);
	DDX_Control(pDX, IDC_SHOW_CERTIFICATE, m_ShowCertificate);
	DDX_Text(pDX, IDC_EDIT3, m_TextSignSteps);
	DDX_Text(pDX, IDC_EDIT4, m_Step);
	DDX_Text(pDX, IDC_EDIT_SHOW_STEPS, m_DisplayData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHybridDecryptionDemo, CDialog)
	//{{AFX_MSG_MAP(CDlgHybridDecryptionDemo)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, OnButtonContinue)
	ON_BN_CLICKED(IDC_SHOW_CERTIFICATE, OnButtonShowCertificate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgHybridDecryptionDemo 

BOOL CDlgHybridDecryptionDemo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_FlushDecDataCtrl.EnableWindow(FALSE);
	m_ShowCertificate.EnableWindow(FALSE);

	LOGFONT LogFont;
	char DefaultFontName[32];
	LONG defaultFontWeight;
	CFont *defaultFont = m_ContinueButtonCtrl.GetFont();
	defaultFont->GetLogFont( &LogFont ); // Default Systemschrift ermitteln
	strncpy(DefaultFontName, LogFont.lfFaceName, 32); // Default Wert sichern
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_Font.CreateFontIndirect( &LogFont ); // Font initialisieren
	m_TextSignStepsCtrl.SetFont(&m_Font);
	m_StepCtrl.SetFont(&m_Font);
	LogFont.lfWeight = defaultFontWeight; // Auf default Wert zur�ckstellen
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen	
	m_Font2.CreateFontIndirect( &LogFont ); // Font2 initialisieren

	m_DisplayDataCtrl.SetFont(&m_Font2);

	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_STEP,pc_str,STR_LAENGE_STRING_TABLE);
	m_TextSignSteps = (CString) pc_str; // Schrittweise Hybrid-Entschl�sselung:
	UpdateData(FALSE);

	UpdateDataDisplay();
	
	HIDE_HOUR_GLASS
	
	UpdateData();	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgHybridDecryptionDemo::OnButtonContinue() 
{
	
	nFirstVisibleLine = m_DisplayDataCtrl.GetFirstVisibleLine();
	UpdateDataDisplay();
}


CDlgHybridDecryptionDemo::~CDlgHybridDecryptionDemo()
{

}

int CDlgHybridDecryptionDemo::UpdateDataDisplay()
{
	
	CString sp1 = (CString)" ";
	CString sp2 = (CString)"  ";
	CString nl = (CString)"\r\n";

	bool err;
	CString cont1,cont2,cont3;
	int maxsteps = 3;
	
	if (step == 0)

	{
		// Hier wird man angefordert die Taste <Weiter> zu dr�cken
		if (m_DisplayData="")
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG2,pc_str,STR_LAENGE_STRING_TABLE);
			cont1 = (CString) pc_str; 
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG12,pc_str,STR_LAENGE_STRING_TABLE);
			cont2 = (CString) pc_str; 
			m_DisplayData += ( cont1 + nl + cont2 + nl +nl);
		//	LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_STEP_BY_STEP,pc_str,STR_LAENGE_STRING_TABLE);
		//	sprintf(pc_str1, pc_str, step, maxsteps);
		//	m_Step = (CString) pc_str1;
		}
		
		nFirstVisibleLine = 0;
		//LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_STEP_BY_STEP,pc_str,STR_LAENGE_STRING_TABLE);
		//sprintf(pc_str1, pc_str, step, maxsteps);
		//m_Step = (CString) pc_str1;
		step++;
		UpdateData(false);
		m_DisplayDataCtrl.LineScroll( step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
		UpdateData(true);
		return 0;
	}
	RsaDialog1.disableButtons = true;
	if (step == 1)
	{
		//Falls man in Schritt 0 auf weiter gedr�ckt hat so �ffnet sich der Dialog RSADialog1
		//Beachte: In RsaDialog1 die �berpr�fung ob Pin Korrekt eingegeben wird durchgef�hrt!!!
		err=false;
		RsaDialog1.UserKeyId=UserKeyId_Datei;
		if ( IDOK == RsaDialog1.DoModal() ) 
		{
			err=true;
			m_iIsGenAsymKey = true;
		}
		UserKeyId=RsaDialog1.UserKeyId;
		if (err)
		{
			CKeyFile KeyHandling;
			CString caDB_entry_name = KeyHandling.CreateDistName(RsaDialog1.Name, RsaDialog1.Firstname, RsaDialog1.CreatTime);
			// caDB_entry_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
			LPTSTR string1 = new TCHAR[caDB_entry_name.GetLength()+1];
			_tcscpy(string1, caDB_entry_name);
			char *Auswahl=string1; // Auswahl entspricht caDB_entry_name
			PSE PseHandle;
			PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
			if (PseHandle==NULL)
			{
				// Fehler beim �ffnen der CA-Datenbank
				RsaDialog1.m_PinCode=_T("");
				Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
				delete string1;
				return 0;
			}
		
			//Routine f�r das Holen von Zertifikaten aus der CA-Datenbank
			SET_OF_IssuedCertificate *Zert;
			Zert=theApp.SecudeLib.af_cadb_get_user(PseHandle, Auswahl);
			if (Zert==NULL)
			{
				// Fehler beim lesen des Zertifikats
				char *Fehler=theApp.SecudeLib.LASTTEXT;
				CString Fehler2=Fehler;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_ERR_GET_PSE,pc_str,STR_LAENGE_STRING_TABLE);
				CString Fehler3=(CString)pc_str+(CString)Fehler2;
				AfxMessageBox (Fehler3,MB_ICONSTOP);
				RsaDialog1.m_PinCode=_T("");
				// Freigeben von dynamisch angelegtem Speicher
				delete string1;
				theApp.SecudeLib.af_close(PseHandle);
				return 0;
			}
			if (UserKeyId!=UserKeyId_Datei)
			{
				RsaDialog1.m_PinCode=_T("");
				Message(IDS_STRING_HYBRID_DEC_MSG10, MB_ICONEXCLAMATION);
				return 0;
			}

				
			Certificate *Zert2;
			OctetString *SNummer;
			SNummer=Zert->element->serial;
			Zert2=theApp.SecudeLib.af_cadb_get_Certificate(PseHandle, SNummer);
			m_CertificateData = CString(sprint_Certificate_with_key(PseHandle,NULL,Zert2));
			m_ShowCertificate.EnableWindow(TRUE);

 			
			theApp.SecudeLib.af_close(PseHandle);

			// Freigeben von dynamisch angelegtem Speicher
			delete string1;
			m_Cert->SetName(RsaDialog1.Name, RsaDialog1.Firstname, RsaDialog1.KeyInfo);
			m_Cert->SetTime(RsaDialog1.CreatTime);
			m_Cert->SetPIN(RsaDialog1.m_PinCode);
			CString help3=(CString)PseVerzeichnis+((CString)"/")+RsaDialog1.UserKeyId+PSE_FILE_SUFFIX;
			
			m_Cert->AccessPSE(RsaDialog1.m_PinCode, help3);
			m_Cert->GetParameter(sModN, sPhiN,sKeyPublic,sKeyPrivate);

			// Hier werden die Certifikate-Daten ausgegeben
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG12,pc_str,STR_LAENGE_STRING_TABLE);
			cont1 = (CString) pc_str; 
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG13,pc_str,STR_LAENGE_STRING_TABLE);
			cont2 = (CString) pc_str; 
			m_DisplayData += ( cont2 +nl + cont1 + nl);	
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_STEP_BY_STEP,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str1, pc_str, step, maxsteps);
			m_Step = (CString) pc_str1;
			step++;
			
			UpdateData(false);
			m_DisplayDataCtrl.LineScroll( step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
			UpdateData(true);
			return 0;
		}
		else
		{
			RsaDialog1.m_PinCode=_T("");
			return 0;
		}
	}
	if (step == 2)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG4,pc_str,STR_LAENGE_STRING_TABLE);
		cont1 = (CString) pc_str; 
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG5,pc_str,STR_LAENGE_STRING_TABLE);
		cont2 = (CString) pc_str; 
		m_DisplayData += ( cont1 + sKeyPrivate  + nl + nl +nl + cont2 + nl );
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG12,pc_str,STR_LAENGE_STRING_TABLE);
		cont1 = (CString) pc_str; 
		m_DisplayData += cont1;

		// Fussnote: "Schritt 2 von 3"
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_STEP_BY_STEP,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, step, maxsteps);
		m_Step = (CString) pc_str1;
		step++;
		UpdateData(false);
		m_DisplayDataCtrl.LineScroll( step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
		UpdateData(true);
		return 0;
	}
	if (step == 3)
	{
		HIDE_HOUR_GLASS
		RsaDec();
		CString DecSessionKey_tmp="";
		for (int k=0;k<DecSessionKey.GetLength();k++)
		{	
			DecSessionKey_tmp += DecSessionKey[k];
			if(k%2==1)
			{
				DecSessionKey_tmp += ' ';
			}
		}
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG6,pc_str,STR_LAENGE_STRING_TABLE);
		cont1 = (CString) pc_str; 
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_MSG7,pc_str,STR_LAENGE_STRING_TABLE);
		cont2 = (CString) pc_str; 
		m_DisplayData += ( cont1 + DecSessionKey_tmp + nl +nl + cont2 + nl +nl);	
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_STEP_BY_STEP,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str1, pc_str, step, maxsteps);
		m_Step = (CString) pc_str1;
		m_ContinueButtonCtrl.EnableWindow(FALSE);
		m_FlushDecDataCtrl.EnableWindow(TRUE);
		m_FlushDecDataCtrl.SetFocus();		
		step++;
		UpdateData(false);
		m_DisplayDataCtrl.LineScroll( step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
		UpdateData(true);
		return 0;
	}
	return 0;
}

void CDlgHybridDecryptionDemo::RsaDec()
{
	char outfile[128];
	
	// Anzeigen der Dialogbox zur Auswahl des zu benutzenden (geheimen) Schl�ssels
	
	// Initialisierung der Variablen
	BitString in;
	OctetString out;
	in.nbits=8*(OctetEncSessionKey.noctets);
	in.bits=OctetEncSessionKey.octets;

	//out initialisieren:
	out.noctets=0;
	out.octets=(char*)malloc(in.nbits/8+256);
	if (out.octets == NULL)
	{
		// Fehler. Speicher kann nicht allokiert werden
		Message(IDS_STRING_ERR_MEMORY_RSA_DECRYPTION,MB_ICONSTOP);
		return;
	}
		
	//Konvertieren der Pin-Nummer von CString nach char *
	LPTSTR string1 = new TCHAR[RsaDialog1.m_PinCode.GetLength()+1];
	_tcscpy(string1, RsaDialog1.m_PinCode);
	char *PIN=string1;
		
	//Pfad mit Dateinamen der PSE des Entschl�sselers in char * konvertieren
	CString help2=(CString)PseVerzeichnis+((CString)"/")+RsaDialog1.UserKeyId+((CString)PSE_FILE_SUFFIX);
	LPTSTR string2 = new TCHAR[help2.GetLength()+1];
	_tcscpy(string2, help2);
	char *PfadNeu=string2;
	
	//�ffnen der PSE des Entschl�sselers
	PSE PseHandle;
	PseHandle = theApp.SecudeLib.af_open(PfadNeu, NULL, PIN, NULL);
	if (PseHandle==NULL)
	{
		if (theApp.SecudeLib.LASTERROR==EPIN)
		{
			// falsche PIN-Nummer benutzt
			Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
			// Freigeben von dynamisch angelegtem Speicher
			free(out.octets);
			delete string1;
			delete string2;
			return;
		}
		Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
		// Freigeben von dynamisch angelegtem Speicher
		free(out.octets);
		delete string1;
		delete string2;
		return;
	}
		
	//Besorgen des privaten Schl�ssels
	Key Schluessel;
	Schluessel.key=NULL;
	Schluessel.pse_sel=NULL;
	Schluessel.alg=theApp.SecudeLib.rsa_aid;
	Schluessel.add_object=NULL;
	Schluessel.add_object_type=NULL;
	Schluessel.key_size=NULL;
	Schluessel.private_key=NULL;
	
	SHOW_HOUR_GLASS
	//Entschl�sseln der Daten mittels af_decrypt_all
	int fret = theApp.SecudeLib.af_decrypt_all (PseHandle, &in, &out, &Schluessel);
	if (fret==-1)
	{
		// Fehler bei der Entschl�sselung
		Message(IDS_STRING_ENCRYPTION_ERROR_2, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.af_close (PseHandle);
		free(out.octets);
		delete string1;
		delete string2;
		return;
	}
		
	//Ausgabe der verschluesselten Daten

	for (unsigned int j=0;j<out.noctets;j++)
	{
			char array[3];
			_snprintf(array,3,"%02.2X",(unsigned char) out.octets[j]);
			DecSessionKey+=array;					
	}

	free(out.octets);
	
	remove(outfile);
	
	HIDE_HOUR_GLASS
	
	theApp.SecudeLib.af_close (PseHandle);
	// Freigeben von dynamisch angelegtem Speicher
	delete string1;
	delete string2;
}

void CDlgHybridDecryptionDemo::OnOK() 
{
	// Hybrid-Entschl�sselung + Ausgabe der Entschl�sselung 
	char outfile[200];
	char key[200];
	strcpy(key,DecSessionKey.GetBuffer(0));

	int AlgId=3;

	GetTmpName(outfile,"cry",".hex");

	theApp.SecudeLib.aux_OctetString2file(&message,outfile,2);
		
	SHOW_HOUR_GLASS
	
	AESCrypt(outfile, m_strTitle1, AlgId, false, outfile,key); // "true" steht f�r eine Verschl�sselung

	remove(outfile);
	
	HIDE_HOUR_GLASS	

	CDialog::OnOK();
}

void CDlgHybridDecryptionDemo::OnCancel() 
{
	// TODO: Zus�tzlichen Bereinigungscode hier einf�gen
	CDialog::OnCancel();
}
void CDlgHybridDecryptionDemo::SetHeadLine(CString &mHeader, int IDS_STRING_ID, int base)
{
	char line[IDS_STRINGLENGTH];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	if ( base ) sprintf( line, pc_str, base );
	else	    sprintf( line, pc_str );
	mHeader = line;
}

void CDlgHybridDecryptionDemo::OnButtonShowCertificate()
{
	CDlgShowCertificate DCert(m_CertificateData, NULL);
	DCert.DoModal();
}


