//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias und Bartol Filipovic
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enth�lt Funktionen zur Schl�sselerzeugung
// und -verwaltung sowie zur Bereitstellung asymmetrischer
// kryptographischer Techniken wie Verschl�sselung (vorerst nur
// RSA) und digitale Signaturen.
// 
// Einige Funktionen benutzen das SECUDE-Toolkit
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DlgAsymKeyCreat.h"
#include "RsaEnc.h"
#include "RsaDec.h"
#include "secure.h"	// Header-File f�r das SECUDE-Toolkit
#include "af.h"		// Header-File f�r den SECUDE Authentication Framework
#include "fileutil.h"
#include "pkcs.h"	// SECUDE Header-File
#include "multipad.h"
#include "DlgSign.h"
#include "DlgSignVerif.h"
#include "MyDocument.h"
#include "crypt.h"

#include "DlgEcKeysCreat.h"
#include "KeyFileHandling.h"
#include "DlgAsymKeyCreat.h"
#include "DlgSignSteps.h"
#include "DlgSignVerifSteps.h"

#include "s_ecFp.h" // elliptic curve stuff
#include "s_prng.h" // big random integers
#include "arithmet.h"
#include "s_ecconv.h"
#include "ecssa.h"
#include "emsa1.h"

#include <time.h>

#include "asymmetric.h"
#include "DialogMessage.h" // ## Sp�ter Ersetzen durch Tools.h

// the extern (global) Variables are from multipad.cpp
extern char *Pfad; // Directory Path of the main programm
extern char pc_str[STR_LAENGE_STRING_TABLE]; // from multipad.cpp

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; 
// aus multipad.cpp

/* Die folgende Funktion erzeugt ein (asymmetrisches) Schl�sselpaar und legt es
PIN-gesch�tzt lokal ab.
Grunds�tzlich mu� hier zwischen Verfahren unterschieden werden, die auf dem
SECUDE-Toolkit aufbauen und Verfahren, die komplett selbst erstellt wurden.

  Verfahren, die auf SECUDE aufbauen:
  Ein Schl�sselpaar und eine PSE (Personal Secure Environment, durch PIN-Nummer
  gesch�tzter Bereich eines Benutzers) werden erzeugt. Der geheime Schl�ssel wird
  in der PSE (PIN-gesch�tzt) abgelegt. Der �ffentliche Schl�ssel wird durch eine 
  lokale CA zertifiziert und das Zertifikat in einer CA-Datenbank abgelegt.
  
	Komplett selbst erstellte Verfahren:
	Auch hier werden ein Schl�sselpaar und eine PSE erzeugt. Der geheime Schl�ssel
	wird wieder in der PSE gespeichert.
	Dieser Schl�ssel kann allerdings nicht durch die Funktionen im SECUDE-Toolkit
	zertifiziert werden, da dazu der (lokalen) CA ein selbst-signiertes (Prototyp-)
	Zertifikat vorzulegen w�re, dessen Unterschrift sie �berpr�ft und bei korrekter
	Verifikation zertifiziert.
	Da SECUDE das entsprechende Signaturverfahren jedoch nicht kennt, kann es auch die 
	Signatur nicht �berpr�fen.
	Deshalb werden die �ffentlichen Schl�ssel (lokal) in einer �ffentlichen Datei abgelegt.
	Dies betrifft vorerst nur Signatur-Verfahren, die auf Elliptischen Kurven arbeiten.
	Bei Hinzuf�gen von weiteren Verfahren, die nicht von SECUDE bereitgestellt werden, stellt
	sich jedoch dasselbe Problem.
*/
void KeyGen(){
	
	// Anzeigen der Dialogbox zur n�heren Spezifikation des zu erzeugenden
	// Schl�sselpaares (Verfahren, Schl�ssell�nge)
	CDlgAsymKeyCreat DlgKey;
	DlgKey.DoModal();
	// Schl�sselerzeugung und abspeichern der benutzten/erzeugten Daten
	// geschieht in der Klasse CDlgAsymKeyCreat
}

//////////////////////////////////////////////////////////////////////////
//
// searching for a matching within the data in->octets and the pattern
// specified by the string-table id "ID" 
//
// the function returns the values 
//     TRUE/FALSE depends on the success of pattern search
//     start: start position of the pattern within in->octets
//     end:   end position of the pattern within in->octets
//

BOOL find( OctetString *in, int ID, int &start, int &end )
{
	LoadString(AfxGetInstanceHandle(),ID,pc_str,STR_LAENGE_STRING_TABLE);
	int strLen = strlen(pc_str);
	if ( start < 0 )
		return FALSE;
	for (unsigned int k=start; k<in->noctets - strLen; k++)
	{
		if ( !strncmp(in->octets + k, pc_str, strLen) )
		{
			start = k;
			end   = k+strLen;
			return TRUE;
		}
	}
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
// extracting a substring of in->octets between the index pos
// and the index "start" computed by the function find(in, ID, start, end)
//
// the function returns the values
//     TRUE/FALSE depends on the success of find(...)
//     Result: without begining / ending whitespaces
//     pos:    end index computed by find(...)

BOOL extract( OctetString *in, CString &Result, int ID, int &pos )
{
	int start, end;
	start = pos;
	if ( find( in , ID, start, end ) )
	{
		char *tmp;
		tmp = new char[start-pos+1];
		strncpy( tmp, in->octets+pos, start-pos );
		tmp[start-pos] = '\0';
		Result = tmp;
		Result.TrimLeft();
		Result.TrimRight();
		pos = end;
		delete []tmp;
		return TRUE;
	}
	else
		return FALSE;
}


/*
Funktion zur Verschl�sselung der Daten im aktuellen Fenster mittels RSA
*/
void RsaEnc(char* infile, const char *OldTitle){
	
	char outfile[128], title[128];
    CMyDocument *NewDoc;
	
	clock_t sigStart;
	clock_t sigFinish;
	double duration;
	
	GetTmpName(outfile,"cry",".tmp");
	
	// Dialogbox zur Auswahl des zu benutzenden (�ffentlichen) Schl�ssels anzeigen
	CRsaEnc RsaDialog1;
	
	if(RsaDialog1.DoModal()==IDOK){
		// Initialisierung der Variablen
		OctetString *in;
		BitString out;
		in= theApp.SecudeLib.aux_file2OctetString(infile);
		
		int max_RSA_keysize_in_octs = ((MAX_RSA_MODULSIZE+1)+7)/8; // siehe DlgAsymKeyCreat.h for MAX_RSA_MODULSIZE
		int number_outbits_in_wc = in->noctets + in->noctets/37 + max_RSA_keysize_in_octs; // Blocksize ~ 37
		
		out.nbits=0;
		out.bits=(char*)malloc(number_outbits_in_wc);
		if (out.bits == NULL)
		{
			// Fehler. Speicher kann nicht allokiert werden
			Message(IDS_STRING_ERR_MEMORY_RSA_ENCRYPTION, MB_ICONSTOP);
			return;
		}
		
		CKeyFile KeyHandling;
		CString caDB_keyid_name = KeyHandling.CreateDistName(RsaDialog1.Name, RsaDialog1.Firstname, RsaDialog1.CreatTime);
		// caDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
		
		LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
		_tcscpy(string3, caDB_keyid_name);
		char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 
		
		// �ffnen der CA-PSE
		PSE PseHandle;
		PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		
		// Besorgen des Zertifikates der Adressaten
		SET_OF_IssuedCertificate *Liste;
		Liste=theApp.SecudeLib.af_cadb_get_user (PseHandle, string4);
		if (Liste==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,MB_ICONSTOP,theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		
		Certificate *Zert;
		OctetString *SNummer;
		SNummer=Liste->element->serial;
		Zert=theApp.SecudeLib.af_cadb_get_Certificate (PseHandle, SNummer);
		if (Zert==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,MB_ICONSTOP,theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
			theApp.SecudeLib.af_close (PseHandle);
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		
		// Besorgen des �ffentlichen Schl�ssels des Adressaten aus seinem Zertifikat
		Key Schluessel;
		Schluessel.key=Zert->tbs->subjectPK;
		Schluessel.pse_sel=NULL;
		Schluessel.alg=theApp.SecudeLib.rsa_aid;
		Schluessel.add_object=NULL;
		Schluessel.add_object_type=NULL;
		Schluessel.key_size=NULL;
		Schluessel.private_key=NULL;
		
		theApp.DoWaitCursor(1);
		sigStart = clock();
		// Verschl�sselung der Daten
		int fret = theApp.SecudeLib.af_encrypt_all(PseHandle, in, &out, &Schluessel, NULL);
		sigFinish = clock();
		duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;
		if (fret==-1)
		{  
			// Fehler bei der Entschl�sselung
			// Ausgabe einer Fehlermeldung
			Message(IDS_STRING_ENCRYPTION_ERROR,MB_ICONSTOP,theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
			theApp.SecudeLib.aux_free_Certificate (&Zert);
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			delete string3;
			return;
		}
		theApp.SecudeLib.aux_free_OctetString(&in);
		
		// Ausgabe der verschl�sselten Daten
		OctetString *outOctet;
		
		outOctet = theApp.SecudeLib.aux_BString2OString(&out);
		theApp.SecudeLib.aux_OctetString2file(outOctet,outfile,2);
		theApp.SecudeLib.aux_free_OctetString(&outOctet);
		free(out.bits);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		
		theApp.DoWaitCursor(0);
		
		if(NewDoc)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_RSA_ENCRYPTION_OF,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName(title,sizeof(title),pc_str,OldTitle);
			NewDoc->SetTitle(title);
		}
		
		// Ben�tigte Zeit zum verschl�sseln ausgeben, falls gew�nscht
		if (RsaDialog1.m_ShowDuration==TRUE)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_RSA_ENCRYPTION_TIME,pc_str1,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str, pc_str1, duration);
			AfxMessageBox (((CString)pc_str),MB_ICONINFORMATION|MB_OK);
		}
		
		theApp.SecudeLib.af_close (PseHandle);
		theApp.SecudeLib.aux_free_SET_OF_IssuedCertificate (&Liste);
		theApp.SecudeLib.aux_free_Certificate (&Zert);
		delete string3;	
	}
}

/*
Funktion zur Entschl�sselung der Daten im aktuellen Fenster mittels RSA
*/
void RsaDec(char* infile, const char *OldTitle)
{
	char outfile[128], title[128];
    CMyDocument *NewDoc;
	unsigned int i, blocklen;
	
	clock_t sigStart;
	clock_t sigFinish;
	double duration;
	
	GetTmpName(outfile,"cry",".tmp");
	
	// Anzeigen der Dialogbox zur Auswahl des zu benutzenden (geheimen) Schl�ssels
	CRsaDec RsaDialog1;
	if(RsaDialog1.DoModal()==IDOK)
	{
		// Initialisierung der Variablen
		BitString in;
		OctetString out, *help;
		help= theApp.SecudeLib.aux_file2OctetString(infile);
		in.nbits=8*(help->noctets);
		in.bits=help->octets;
		
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
				theApp.SecudeLib.aux_free_OctetString(&help);
				free(out.octets);
				delete string1;
				delete string2;
				return;
			}
			Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.aux_free_OctetString(&help);
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
		
		theApp.DoWaitCursor(1);
		sigStart = clock();
		//Entschl�sseln der Daten mittels af_decrypt_all
		int fret = theApp.SecudeLib.af_decrypt_all (PseHandle, &in, &out, &Schluessel);
		sigFinish = clock();
		duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;			
		if (fret==-1)
		{
			// Fehler bei der Entschl�sselung
			Message(IDS_STRING_ENCRYPTION_ERROR_2, MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			theApp.SecudeLib.aux_free_OctetString(&help);
			free(out.octets);
			delete string1;
			delete string2;
			return;
		}
		
		// Abschneiden abschlie�ender Nullen
		blocklen = out.noctets / (in.nbits / 8 - out.noctets);
		for(i=out.noctets-1;i>out.noctets-blocklen;i--)
			if(out.octets[i]) break;
		if(i>out.noctets-blocklen) out.noctets = i+1;
		theApp.SecudeLib.aux_free_OctetString(&help);
		
		//Ausgabe der verschluesselten Daten
		theApp.SecudeLib.aux_OctetString2file(&out, outfile, 2);
		free(out.octets);
		
		//theApp.SecudeLib.aux_free_BitString(&in);
		//free(in.bits);
		
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		
		theApp.DoWaitCursor(0);
		
		if(NewDoc) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_RSA_DECRYPTION_OF,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName(title,sizeof(title),pc_str,OldTitle);
			NewDoc->SetTitle(title);
		}
		// Ben�tigte Zeit zum entschl�sseln ausgeben, falls gew�nscht
		if (RsaDialog1.m_ShowDuration==TRUE)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_RSA_DECRYPTION_TIME,pc_str1,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str, pc_str1, duration);
			AfxMessageBox (((CString)pc_str),MB_ICONINFORMATION|MB_OK);
		}
		theApp.SecudeLib.af_close (PseHandle);
		// Freigeben von dynamisch angelegtem Speicher
		delete string1;
		delete string2;
	}
}

/*
Die folgende Funktion erstellt eine Signatur der Daten im aktuellen Fenster
*/
void Sign(char* infile, const char *OldTitle)
{
	char *hash_id;
	char *ec_sign_id;
	char *Verfahren;
	char *Verfahren2;
	bool ec_sign=false;
	L_NUMBER c[MAXLGTH];
	L_NUMBER d[MAXLGTH];
	int fret;
	clock_t sigStart;
	clock_t sigFinish;
	double duration;
	
	// Anzeigen der Dialogbox zur Auswahl des zu benutzenden Verfahrens und des
	// zu benutzenden (geheimen) Schl�ssels
	CDlgSign SigDialog;
	if (SigDialog.DoModal()==IDOK)
	{
		
		//Welches Signaturverfahren wurde gew�hlt???
		Signature Signatur;
		
		switch (SigDialog.m_SignAlg){
		case 0:	// RSA
			Verfahren = "RSA";
			ec_sign=false;
			switch (SigDialog.m_radio){
			case 0:		// MD2
				Signatur.signAI=theApp.SecudeLib.md2WithRsaEncryption_aid;
				hash_id = "MD2";
				Verfahren2="RSA (MD2)";
				break;
			case 1:		// MD5
				Signatur.signAI=theApp.SecudeLib.md5WithRsaEncryption_aid;
				hash_id = "MD5";
				Verfahren2="RSA (MD5)";
				break;
			case 2:		// RIPEMD-160
				Signatur.signAI=theApp.SecudeLib.ripemd160WithRSASignature_aid;
				hash_id = "RIPEMD-160";
				Verfahren2="RSA (RIPEMD160)";
				break;
			case 3:		// SHA
				Signatur.signAI=theApp.SecudeLib.shaWithRSASignature_aid;
				hash_id = "SHA";
				Verfahren2="RSA (SHA)";
				break;
			case 4:		// SHA-1
				Signatur.signAI=theApp.SecudeLib.sha1WithRSASignature_aid;
				hash_id = "SHA-1";
				Verfahren2="RSA (SHA1)";
				break;
			}
			break;
			case 1:		// DSA
				Verfahren = "DSA";
				ec_sign=false;
				switch (SigDialog.m_radio){
				case 3:		// SHA
					Signatur.signAI=theApp.SecudeLib.dsaWithSHA_aid;
					hash_id = "SHA";
					Verfahren2="DSA (SHA)";
					break;
				case 4:		// SHA-1
					Signatur.signAI=theApp.SecudeLib.dsaWithSHA1_aid;
					hash_id = "SHA-1";
					Verfahren2="DSA (SHA1)";
					break;
				}
				break;
				case 2:		// ECDSA
					ec_sign=true;
					ec_sign_id = "ECSP-DSA";
					Verfahren = "ECSP-DSA";
					switch (SigDialog.m_radio){
					case 2:		// RIPEMD-160
						hash_id = "RIPEMD-160";
						Verfahren2="ECSP-DSA (RIPEMD-160)";
						break;
					case 4:		// SHA-1
						hash_id = "SHA-1";
						Verfahren2 = "ECSP-DSA (SHA-1)";
						break;
					}
					break;
					case 3:		// ECNR
						ec_sign=true;
						ec_sign_id = "ECSP-NR";
						Verfahren = "ECSP-NR";
						switch (SigDialog.m_radio){
						case 2:		// RIPEMD-160
							hash_id = "RIPEMD-160";
							Verfahren2="ECSP-NR (RIPEMD-160)";
							break;
						case 4:		// SHA-1
							hash_id = "SHA-1";
							Verfahren2 = "ECSP-NR (SHA-1)";
							break;
						}
						break;
		}
		
		// Zu signierende Nachricht initialisieren
		OctetString *in=theApp.SecudeLib.aux_file2OctetString(infile);
		
		if (ec_sign == true)
		{
			// EC Signatur-Verfahren gew�hlt
			
			if (SigDialog.m_ShowSteps == TRUE)
			{
				// Zwischenschritte der Signaturerzeugung anzeigen
				
				theApp.DoWaitCursor(1);
				CDlgSignSteps dlgSignSteps(in, Verfahren, hash_id,\
					SigDialog.DomParamAc, SigDialog.DomParamPc,\
					SigDialog.UserKeyId,\
					SigDialog.Name, SigDialog.Firstname,\
					SigDialog.KeyType);
				theApp.DoWaitCursor(0);
				
				sigStart = clock();
				fret = dlgSignSteps.DoModal();
				sigFinish = clock();
				duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;
				
				if (fret==IDOK)
				{
					dlgSignSteps.GetSignature(c, d);
				}
				else
				{
					theApp.SecudeLib.aux_free_OctetString(&in);
					return;
				}
			}
			else if (SigDialog.use_affine_coord == true)
			{
				// EC-Signieren und dabei in affinen Koordinaten Rechnen
				sigStart = clock();
				fret = ecssa_sign_gen_op_ac(c, d, in, SigDialog.DomParamAc, ec_sign_id ,hash_id);
				sigFinish = clock();
				duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;
				if (fret)
				{
					// Fehler beim Signieren
					Message(IDS_STRING_ERR_EC_ON_SIGNATURE,MB_ICONSTOP);
					theApp.SecudeLib.aux_free_OctetString(&in);
					return;
				}
			}
			else //if (SigDialog.use_affine_coord == false)
			{
				// EC-Signieren und dabei in projektiven Koordinaten Rechnen
				// (sollte schneller gehen als das Rechnen in affinen Koordinaten)
				sigStart = clock();
				fret = ecssa_sign_gen_op_pc(c, d, in, SigDialog.DomParamPc, ec_sign_id ,hash_id);
				sigFinish = clock();
				duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;
				if (fret)
				{
					// Fehler beim Signieren
					Message(IDS_STRING_ERR_EC_ON_SIGNATURE,MB_ICONSTOP);
					theApp.SecudeLib.aux_free_OctetString(&in);
					return;
				}
			}			
		}
		else
		{
			// Signieren mit DSA oder RSA
			// Konvertieren der Pin-Nummer von CString nach char *
			LPTSTR string1 = new TCHAR[SigDialog.m_edit.GetLength()+1];
			_tcscpy(string1, SigDialog.m_edit);
			char *PIN=string1;
			
			// Pfad der PSE des Absenders (Signaturerstellers) in char * konvertieren
			CString help2=(CString)PseVerzeichnis+((CString)"/")+SigDialog.UserKeyId+((CString)PSE_FILE_SUFFIX);
			LPTSTR string2 = new TCHAR[help2.GetLength()+1];
			_tcscpy(string2, help2);
			char *PfadNeu=string2;
			
			// die PSE des Absenders (Siganturerstellers) �ffnen
			
			PSE PseHandle;
			PseHandle = theApp.SecudeLib.af_open(PfadNeu, NULL, PIN, NULL);
			if (PseHandle==NULL)
			{
				if (theApp.SecudeLib.LASTERROR==EPIN)
				{
					// falsche PIN-Nummer benutzt
					Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
					// Freigeben von dynamisch angelegtem Speicher
					theApp.SecudeLib.aux_free_OctetString(&in);
					delete string1;
					delete string2;
					return;
				}
				// sonstige Fehler beim �ffnen der PSE
				Message(IDS_STRING_ASYMKEY_ERR_OPEN_PSE,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
				// Freigeben von dynamisch angelegtem Speicher
				theApp.SecudeLib.aux_free_OctetString(&in);
				delete string1;
				delete string2;
				return;
			}
			
			// Eigentliche RSA bzw. DSA Signaturerstellung
			PseHandle->options.af_sign_check_Validity=FALSE;
			sigStart = clock();
			fret = theApp.SecudeLib.af_sign_all (PseHandle, in, &Signatur);//Signaturerstellung
			sigFinish = clock();
			duration = (double)(sigFinish - sigStart) / CLOCKS_PER_SEC;
			if (fret==-1)
			{
				Message(IDS_STRING_ERR_ON_SIGNING,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
				// Freigeben von dynamisch angelegtem Speicher
				theApp.SecudeLib.aux_free_OctetString(&in);
				theApp.SecudeLib.af_close(PseHandle);
				delete string1;
				delete string2;
				return;
			}
			PseHandle->options.af_sign_check_Validity=TRUE;
			theApp.SecudeLib.af_close (PseHandle);
			// Freigeben von dynamisch angelegtem Speicher
			delete string1;
			delete string2;
		}
		
		// Ausgabe von Signatur, Signaturverfahren und Nachricht in einem Fenster
		bool zugross;
		int err = PrintSignData(infile, OldTitle, in, zugross, ec_sign,\
			hash_id, Verfahren, Verfahren2, SigDialog.UserKeyId, &Signatur, c, d);
		
		if (err < 0)
		{
			// Fehler. Speicherallokation ging schief
			Message(IDS_STRING_ERR_MEMORY_SIGNATURE_GENERATION,MB_ICONSTOP);
			theApp.SecudeLib.aux_free_OctetString(&in);
			return;
		}
		
		if (zugross==true)
		{
			// die signierte Nachricht in.octets war zu gross, um mit dem Hex-Editor von CrypTool
			// angezeigt zu werden. Daher wurde Sie in eine tempor�re Datei umgeleitet
			Message(IDS_STRING_MSG_SIGNED_MESSAGE_TO_BIG,MB_ICONINFORMATION|MB_OK,infile);
		}
		
		theApp.SecudeLib.aux_free_OctetString(&in);
		// Ben�tigte Zeit um Signatur zu erstellen ausgeben, falls gew�nscht
		if (SigDialog.m_ShowDuration==TRUE)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_GENERATION_TIME,pc_str1,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str, pc_str1, duration);
			AfxMessageBox (((CString)pc_str),MB_ICONINFORMATION|MB_OK);
		}
	}
}


int PrintSignData(char *infile, const char *OldTitle, OctetString *in, bool& zugross, bool ecSign,\
				  char *hash_id, char *Verfahren, char *Verfahren2,\
				  CString UserKeyId, Signature* Signatur, L_NUMBER *c, L_NUMBER *d )
{
	char outfile[128], title[128];
    CMyDocument *NewDoc;
	
	int String_Length;
	int i;
	int signlength; // Signaturl�nge in bits
	
	GetTmpName(outfile,"cry",".hex");
	
	// Ausgabe von Signatur, Signaturverfahren und Nachricht in einem Fenster
	OctetString Text;
	char helptext[100];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,2);
	
	OctetString *SigAus;
	OctetString *SigAusEc_c;
	OctetString *SigAusEc_d;
	if (ecSign == false)
	{
		signlength = Signatur->signature.nbits; // L�nge der Signatur in bits
		
		SigAus=theApp.SecudeLib.aux_BString2OString(&Signatur->signature);
		
		// Ausgabe der RSA oder DSA Signatur
		theApp.SecudeLib.aux_OctetString2file(SigAus, outfile, 3);
		//  Leerzeichen in die Ausgabe einf�gen (damit Ausgabe sauber dargestellt wird)
		for (i=0; i<(16-((int)SigAus->noctets%16)); i++)
		{
			Text.noctets=1;
			Text.octets=" ";
			theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
		}
		theApp.SecudeLib.aux_free_OctetString(&SigAus);
	}
	else
	{
		// Ausgabe der Elliptische Kurven Signatur
		
		// wandele c und d (beides L_NUMBERs) nach Strings (char *) um
		char *strC;
		char *strD;
		
		//char *strC_oktal;
		//char *strD_oktal;
		//ln_to_string (c, &strC_oktal, 8); // Oktalsystem
		//ln_to_string (d, &strD_oktal, 8); // Oktalsystem
		//signlength = strlen(strC_oktal) + strlen(strD_oktal); // L�nge der Signatur im Oktalsystem
		
		signlength = theApp.SecudeLib.lngtouse(c)+theApp.SecudeLib.lngtouse(d)+2;// Bit-L�nge der Signatur
		
		ln_to_string (c, &strC, 10); // Dezimalsystem
		ln_to_string (d, &strD, 10); // Dezimalsystem
		// wandele strC und strD nach OctetStrings
		SigAusEc_c = (OctetString*) malloc(sizeof(OctetString));
		if (SigAusEc_c == NULL)
		{
			return -1; // Fehler bei Speicherallokation
		}
		SigAusEc_c->noctets=strlen(strC);
		SigAusEc_c->octets=strC;
		SigAusEc_d = (OctetString*) malloc(sizeof(OctetString));
		if (SigAusEc_d == NULL)
		{
			free (SigAusEc_c);
			return -2; // Fehler bei Speicherallokation
		}
		SigAusEc_d->noctets=strlen(strD);
		SigAusEc_d->octets=strD;
		
		// BEMERKUNG1[siehe auch Bem. in Verify()]:
		// Das direkte umwandeln von LN_NUMBER nach OctetString wird nicht vorgenommen,
		// da es sonst Probleme in der Funktion Verify() gibt.
		// Daher wird folgende Vorgehensweise nicht angewendet:
		// SigAusEc_c = aux_LN2OctetString(c, (lngtouse(c)+7)/8);
		// SigAusEc_d = aux_LN2OctetString(d, (lngtouse(d)+7)/8);
		
		char *c_string="[c=]";
		char *d_string="[d=]";
		
		Text.noctets=strlen(c_string);
		Text.octets=c_string;
		theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
		String_Length=16-((int)Text.noctets%16);
		for (i=0; i<String_Length; i++)
		{
			// Leerzeichen auff�llen
			Text.noctets=1;
			Text.octets=" ";
			theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
		}
		theApp.SecudeLib.aux_OctetString2file(SigAusEc_c, outfile, 3);
		String_Length=16-((int)SigAusEc_c->noctets%16);
		for (i=0; i<String_Length; i++)
		{
			// Leerzeichen auff�llen
			Text.noctets=1;
			Text.octets=" ";
			theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
		}
		
		Text.noctets=strlen(d_string);
		Text.octets=d_string;
		theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
		String_Length=16-((int)Text.noctets%16);
		for (i=0; i<String_Length; i++)
		{
			// Leerzeichen auff�llen
			Text.noctets=1;
			Text.octets=" ";
			theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
		}
		theApp.SecudeLib.aux_OctetString2file(SigAusEc_d, outfile, 3);
		String_Length=16-((int)SigAusEc_d->noctets%16);
		for (i=0; i<String_Length; i++)
		{
			// Leerzeichen auff�llen
			Text.noctets=1;
			Text.octets=" ";
			theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
		}
		
		free (SigAusEc_c->octets);
		free (SigAusEc_c);
		free (SigAusEc_d->octets);
		free (SigAusEc_d);
	}
	
	// Weitere Daten im Zusammenhang mit der Signatur ausgeben
	
	// Ausgabe: 'Signaturl�nge' in Anzahl der Octets
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HEADING_SIGNATURELENGTH,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	char signlen_in_bits_str[20];
	// schreibe die zahl signlength im Dezimalsystem nach signlen_in_bits_str
	_itoa(signlength, signlen_in_bits_str, 10);
	Text.noctets=strlen(signlen_in_bits_str);
	Text.octets=signlen_in_bits_str;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	String_Length=16-((int)Text.noctets%16);
	for (i=0; i<String_Length; i++)
	{
		// Leerzeichen auff�llen
		Text.noctets=1;
		Text.octets=" ";
		theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	}
	
	// Ausgabe: 'Verfahren'
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_METHOD,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	Text.noctets=strlen(Verfahren);
	Text.octets=Verfahren;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	String_Length=16-((int)Text.noctets%16);
	for (i=0; i<String_Length; i++)
	{
		// Leerzeichen auff�llen
		Text.noctets=1;
		Text.octets=" ";
		theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	}
	
	// Ausgabe: 'Hashfunction'
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_SELECT_HASH_METHOD,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	Text.noctets=strlen(hash_id);
	Text.octets=hash_id;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	String_Length=16-((int)Text.noctets%16);
	for (i=0; i<String_Length; i++)
	{
		// Leerzeichen auff�llen
		Text.noctets=1;
		Text.octets=" ";
		theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	}
	
	// Schl�ssel mit dem Nachricht signiert wurde ausgeben
	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	
	// Umwandeln von CString nach char*
	LPTSTR string_tmp = new TCHAR[UserKeyId.GetLength()+1];
	_tcscpy(string_tmp, UserKeyId);
	char *KeyInfo=string_tmp;
	Text.noctets=strlen(KeyInfo); // Ausgabe des benutzten Schl�ssel ID
	Text.octets=KeyInfo;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	String_Length=16-((int)Text.noctets%16);
	for (i=0; i<String_Length; i++)
	{
		// Leerzeichen einf�gen
		Text.noctets=1;
		Text.octets=" ";
		theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	}
	delete string_tmp;
	
	// signierte Nachricht ausgeben
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_MESSAGE,helptext,100);
	Text.noctets=strlen(helptext);
	Text.octets=helptext;
	theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	// Testen, ob die zu signierende Nachricht gr��er als 200k ist
	// In diesem Fall ist die HexDump-Darstellung der Signatur gr��er als 1024k und damit
	// zu gro� f�r den Editor des Toolkits
	if (in->noctets <= 204800)
	{
		zugross = false;
		theApp.SecudeLib.aux_OctetString2file(in,outfile,3);
	}
	else 
	{
		// Die signierte Nachricht ist zu gross, um in dem Editor von CrypTool
		// angezeigt zu werden, daher wird sie in eine Datei ins Temp Verzeichnis geschrieben
		// Statt der Nachricht steht im Editor von CrypTool der Pfad dieser Datei
		
		zugross = true;
		// IDS_STRING_MSG_FILENAME_SIGNED_MESSAGE: "Die signierte  Nachricht liegt in Datei:       "
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_FILENAME_SIGNED_MESSAGE,pc_str,100);
		CString help7=(CString)pc_str;
		help7+=(CString)infile;
		Text.noctets=strlen(help7);
		for (i=0; i<help7.GetLength(); i++)
		{
			Text.octets[i]=help7[i];
		}
		theApp.SecudeLib.aux_OctetString2file(&Text,outfile,3);
	}
	
	NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
	remove(outfile);
	if(NewDoc)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ASYMKEY_SIGNATURE_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(title,sizeof(title),pc_str,OldTitle,Verfahren2);
		NewDoc->SetTitle(title);
	}
	
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////


BOOL PrintSignature(OctetString&		SignText,
					const OctetString&	Signature, 
					const CString&		EncAlg, 
					const CString&		HshAlg, 
					const CString&		UserKeyId)
{
	//OctetString* osSignText = new OctetString;
	memset(&SignText, 0, sizeof(OctetString));
	CString sText;

	sText.LoadString(IDS_STRING_MSG_SIGNATURE);
	//while (sText.GetLength()<16) sText += ' ';
	Add2OString(&SignText, LPCSTR(sText), sText.GetLength());
	Add2OString(&SignText, Signature.octets, Signature.noctets);
	
	// Ausgabe: 'Signaturl�nge' in Anzahl der Octets
	char signlength[20];
	sText.LoadString(IDS_STRING_HEADING_SIGNATURELENGTH);
	_itoa(Signature.noctets*8, signlength, 10); 
	sText += signlength;
	//while (sText.GetLength()<16) sText += ' ';
	Add2OString(&SignText, LPCSTR(sText), sText.GetLength());
	
	// Ausgabe: 'Verfahren'
	sText.LoadString(IDS_STRING_ASYMKEY_METHOD);
	//while (sText.GetLength()<16) sText += ' ';
	sText += EncAlg; 
	Add2OString(&SignText, LPCSTR(sText), sText.GetLength());

	// Ausgabe: 'Hashfunction'
	sText.LoadString(IDS_STRING_ASYMKEY_SELECT_HASH_METHOD);
	sText += HshAlg;
	//while (sText.GetLength()<16) sText += ' ';
	Add2OString(&SignText, LPCSTR(sText), sText.GetLength());

	// Schl�ssel mit dem Nachricht signiert wurde ausgeben
	sText.LoadString(IDS_STRING_KEY);
	sText += UserKeyId;
	//while (sText.GetLength()<16) sText += ' ';
	Add2OString(&SignText, LPCSTR(sText), sText.GetLength());

	sText.LoadString(IDS_STRING_ASYMKEY_MESSAGE);
	//while (sText.GetLength()<16) sText += ' ';
	Add2OString(&SignText, LPCSTR(sText), sText.GetLength());

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Show Signature Data 
//

int GetSignData(char* infile, bool& zugross, CString& filename, OctetString *message, CString& SigAlg,\
				CString& HashAlg, CString& UserKeyId, int *SignLength, Signature *Signatur,\
				L_NUMBER *c, L_NUMBER *d)
{
/*
Einlesen der Daten aus dem aktuellen Fenster (aktives Dokument)
Dies Daten m�ssen folgende Struktur haben:

  Signatur:
  <Daten>
  
    Signaturl�nge:
	<Daten>
	
	  Verfahren:
	  <Daten>
	  
		Hashfunktion:
		<Daten>
		
		  Schl�ssel:
		  <Daten>
		  
			Nachricht:
			<Daten>					
	*/		
	
	int k;
	int SignType = -1;
	
	Signatur->signature.bits = NULL;
	message->octets = NULL;
	
	OctetString *help=theApp.SecudeLib.aux_file2OctetString(infile);
	if (help == NULL) return 1; // Fehlerhafte Speicherallokation
	
	int start=0, end, pos;
	CString res;

	if ( !find( help, IDS_STRING_HEADING_SIGNATURELENGTH, start, end) )
	{
		// Substring "Signaturl�nge:" konnte nicht gefunden werden 
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_OctetString(&help);
		return -1;
	}
	pos = end;
	if ( !extract( help, res, IDS_STRING_ASYMKEY_METHOD, pos ) )
	{
		// der gesuchte String wurde nicht gefunden
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_OctetString(&help);
		return -3;
	}
	// get the signature Length...
	{
		LPTSTR siglgth = new TCHAR[res.GetLength()+1];
		_tcscpy(siglgth, res);
		*SignLength = atoi(siglgth); // ascii to int Konvertierung, *SignLength ist die Bitl�nge der Sign.
		delete siglgth;
		if ( *SignLength <= 0 ) return -3;
	}
	
	if ( !extract( help, SigAlg, IDS_STRING_ASYMKEY_SELECT_HASH_METHOD, pos ) )
	{
		// der gesuchte String wurde nicht gefunden
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_OctetString(&help);
		return -4;
	}

	if ( !extract( help, HashAlg, IDS_STRING_KEY, pos ) )
	{
		// der gesuchte String wurde nicht gefunden
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_OctetString(&help);
		return -5;
	}

	if ( !extract( help, UserKeyId, IDS_STRING_ASYMKEY_MESSAGE, pos ) )
	{
		// der gesuchte String wurde nicht gefunden
		// Freigeben von dynamisch angelegtem Speicher
		theApp.SecudeLib.aux_free_OctetString(&help);
		return -6;
	}

	// extract the message
	message->noctets=(help->noctets-pos);
	message->octets= (char*) malloc ((message->noctets+1)*sizeof(char));
	if (message->octets==NULL)
	{
		theApp.SecudeLib.aux_free_OctetString(&help);
		return 2; // Fehlerhafte Speicherallokation
	}
	memcpy( message->octets, help->octets + pos, message->noctets );

	{  // 
		zugross=false;
		OctetString *fileocts;
		
		// IDS_STRING_MSG_FILENAME_SIGNED_MESSAGE : "Die signierte Nachricht liegt in Datei:"
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_FILENAME_SIGNED_MESSAGE,pc_str,100);
		size_t strl = strlen(pc_str);
		if ( message->noctets > strl ) 
		{
			CString help7(message->octets, strl);
			if (help7==(CString)pc_str)
			{
				// Die signierte Nachricht ist in eine Datei umgeleitet worden.
				
				// Daten m�ssen aus Datei eingelesen werden
				// AfxMessageBox ("Daten aus Datei einlesen");
				
				// Ermittele den Pfad und Namen der Datei
				int restmesglgth = (message->noctets-strl);
				CString filename(&message->octets[strl], restmesglgth);
				
				LPTSTR temp_ptr = new TCHAR[filename.GetLength()+1];
				_tcscpy(temp_ptr, filename);
				char *msgfile = temp_ptr; // msgfile: Dateiname der Datei die signierte Nachricht enth�lt
				
				fileocts=theApp.SecudeLib.aux_file2OctetString(msgfile);
				if (fileocts==NULL)
				{
					// Fehler bei Speicherallokation
					// Freigeben von dynamisch angelegtem Speicher
					theApp.SecudeLib.aux_free_OctetString(&help);
					delete temp_ptr;
					return 4; // Fehlerhafte Speicherallokation
				}
				filename = temp_ptr;
				delete temp_ptr;
				
				zugross=true; // zugross == true: Nachricht wurde aus Datei gelesen
				
				// message->octets mit Octets der eigentlich Signierten Nachricht belegen
				free (message->octets); // bisherigen Speicher freigeben
				message->noctets=fileocts->noctets;
				// Kopiere die eigentliche Nachricht nach message
				message->octets= (char*) malloc ((message->noctets+1)*sizeof(char));
				if (message->octets==NULL)
				{
					theApp.SecudeLib.aux_free_OctetString(&help);
					return 5; // Fehlerhafte Speicherallokation
				}
				for (k=0; k<((int)message->noctets); k++)
				{
					message->octets[k]=fileocts->octets[k];
				}
				theApp.SecudeLib.aux_free_OctetString(&fileocts);// fileocts wird nicht mehr ben�tigt
			}
		}
	}

	// extract the signature
	if ( (SigAlg == "ECSP-DSA") || (SigAlg == "ECSP-NR") )
	{
		// EC-Signatur wurde zum signieren benutzt
		SignType = EC_SIGN;
		
		Signatur->signature.bits = NULL; // Signatur->signature.bits wird nur bei DSA/RSA Sign. benutzt
		
		// Signatur besteht aus den beiden Zahlen c und d
		// Diese Zahlen werden nun aus dem Signaturausgabefenster ermittelt
		// und in den Variablen c_str und d_str abgespeichert
		
		CString sign_string(&help->octets[0], start);
		
		int cpos = sign_string.Find("[c=]");
		int dpos = sign_string.Find("[d=]");
		
		if ((cpos == -1) || (dpos == -1))
		{
			// Mind. einer der Suchstrings konnte nicht gefunden werden
			// Speicher freigeben
			theApp.SecudeLib.aux_free_OctetString(&help);
			return -7;
		}
		
		// extrahiere die beiden (Dezimal-)Zahlen c_str und d_str
		CString c_str = sign_string.Mid(cpos+4, dpos-cpos-4);
		CString d_str = sign_string.Mid(dpos+4);
		
		c_str.TrimLeft(); // linke Leerzeichen l�schen
		c_str.TrimRight(); // rechte Leerzeichen l�schen
		d_str.TrimLeft();
		d_str.TrimRight();
		
		// Umwandeln von c_str und d_str nach LN_NUMBERs c und d
		string_to_ln (c_str, c);
		string_to_ln (d_str, d);
		
	}
	else if ( (SigAlg == "DSA") || (SigAlg == "RSA") )
	{
		// RSA oder DSA Signaturverfahren zum Erzeugen der Signatur benutzt
		
		SignType = RSA_OR_DSA_SIGN;
		
		inttoln(0,c); // dummy Wert, L_NUMBER c wird nur bei EC-Verfahren benutzt
		inttoln(0,d); // dummy Wert, L_NUMBER d wird nur bei EC-Verfahren benutzt
		
		// Initialisieren von Signature Signatur
		
		OctetString help2;
		// Kopieren der Signaturdaten nach help2
		// Signaturdaten bestehen aus SignLength vielen bits
		// das entspricht (SignLength+7)/8 vielen bytes/octets
		int SigLengthInOcts = ((*SignLength)+7)/8;
		help2.octets = (char *) malloc(SigLengthInOcts);
		if (help2.octets == NULL)
		{
			// Speicher freigeben
			theApp.SecudeLib.aux_free_OctetString(&help);
			return 3;
		}
		help2.noctets = SigLengthInOcts; 
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE,pc_str,1000);
		memcpy(help2.octets, help->octets+strlen(pc_str), SigLengthInOcts); 
		
		// "Kopieren" der Signaturdaten nach Signatur
		Signatur->signature.nbits=(*SignLength);
		// oder: Signatur->signature.nbits=8*help2.noctets;
		Signatur->signature.bits=help2.octets;
	}
	else
	{
		// unbekanntes Signaturverfahren ausgelesen
		SignType = UNKNOWN_SIGN;
		theApp.SecudeLib.aux_free_OctetString(&help);
	}
	
	theApp.SecudeLib.aux_free_OctetString(&help);
	return SignType;
}



///////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/* 
Funktion zum Verifizieren von digitalen Signaturen.
Dabei wird vorausgesetzt, da� die Signatur, das verwendete Verfahren und die
signierte Nachricht so vorliegen, wie sie von der Funktion Sign() bzw. PrintSignData()
abgelegt wurden.
*/
void Verify(char* infile, const char *OldTitle)
{
	int fret;
	char temp[200];
	
	clock_t verifStart;
	clock_t verifFinish;
	double duration;
	
	bool messagefromfile=false; // zeigt an, ob die signierte Nachricht aus einer Datei
	// gelesen werden musste
	CString filename;
				
	CString SigAlg="";
	CString HashAlg="";
	CString UserKeyId="";
	int SignLength; // L�nge der Signatur in Bits
	
	OctetString message; // signed message, enth�lt sp�ter die signierte Nachricht
	Signature Signatur; // only correct initialized then verifiying RSA or DSA signatures
	
	L_NUMBER c[MAXLGTH]; // only correct initialized then verifiying EC signatures
	L_NUMBER d[MAXLGTH]; // only correct initialized then verifiying EC signatures
	
	fret = GetSignData(infile,messagefromfile, filename, &message,SigAlg,HashAlg,UserKeyId,\
		&SignLength,&Signatur,c,d);
	
	if ( (fret > 0) && (fret != EC_SIGN) && (fret != RSA_OR_DSA_SIGN) && (fret != UNKNOWN_SIGN) )
	{
		// Fehler beim auslesen der Daten (Nicht gen�gend Speicher vorhanden)
		Message(IDS_STRING_ERR_MEMORY_SIGNATURE_VERIFICATION, MB_ICONSTOP);
		if (Signatur.signature.bits) free(Signatur.signature.bits);
		if (message.octets) free(message.octets);
		return;
	}
	else if ((fret != EC_SIGN) && (fret != RSA_OR_DSA_SIGN) && (fret != UNKNOWN_SIGN))
	{
		// Fehler beim auslesen der Daten (Formatierung der Daten nicht korrekt)
		Message(IDS_STRING_ASYMKEY_ERR_ON_VERIFIKATION,MB_ICONSTOP);
		if (Signatur.signature.bits) free(Signatur.signature.bits);
		if (message.octets) free(message.octets);
		return;
	}
	
	// Folgende Speicherbereiche sind von GetSignData() alloziert worden und
	// m�ssen sp�ter wieder freigegeben werden:
	// message.octets (falls != NULL) 
	// Signatur.signature.bits (falls != NULL)
	
	LPTSTR temp_ptr = new TCHAR[SigAlg.GetLength()+1];
	_tcscpy(temp_ptr, SigAlg);
	char *sig_verfahren = temp_ptr;
	
	LPTSTR temp_ptr2 = new TCHAR[HashAlg.GetLength()+1];
	_tcscpy(temp_ptr2, HashAlg);
	char *hash_verfahren = temp_ptr2;
	
	CDlgSignVerif VerDialog(sig_verfahren, hash_verfahren, UserKeyId);
	
	if (VerDialog.DoModal()==IDOK)
	{
		if (VerDialog.UserKeyId.Find(EC_KEYFILE_IDSTRING ) > -1)
		{
			// In VerDialog wurde ein EC Schl�sselpaar Eintrag gew�hlt,
			// also Verifikation eines EC-Signaturverfahrens
			
			char *sig_verfahren;
			char *hash_verfahren;
			
			switch (VerDialog.m_SigVerfahren)
			{
				// Vom Benutzer gew�hltes Signaturverfahren ermitteln
			case 0:
				// ECSP-DSA
				sig_verfahren = "ECSP-DSA"; break;
			case 1:
				// ECSP-NR
				sig_verfahren = "ECSP-NR"; break;
			}
			switch (VerDialog.m_HashFunktion)
			{
				// Vom Benutzer gew�hlte Hashfunktion ermitteln
			case 0:
				// SHA-1
				hash_verfahren = "SHA-1";break;
			case 1:
				// RIPEMD 160
				hash_verfahren = "RIPEMD-160";break;
			}
			
			// MessageBox mit der extrahierten Signatur ausgeben
			// (dies dient nur zu Informationszwecken)
			// LoadString(AfxGetInstanceHandle(),IDS_STRING_EXTRACTED_SIGNATURE,pc_str,STR_LAENGE_STRING_TABLE);
			// CString ExtractedSig=(CString) pc_str + "\n\n" + "c = " + c_str + "\n" + "d = " + d_str;
			// LoadString(AfxGetInstanceHandle(),IDS_STRING_EXTRACTED_MESSAGE,pc_str,STR_LAENGE_STRING_TABLE);
			// CString ExtractedMesg=(CString) pc_str + "\n\n" + message_string;
			// Message(IDS_STRING_XXX, MB_ICONINFORMATION, ExtractedSig);
			
			// Verify signature and display result
			if (VerDialog.m_ShowSteps == TRUE)
			{
				// Zwischenschritte der Signaturverifikation anzeigen
				
				theApp.DoWaitCursor(1);
				CDlgSignVerifSteps verifSteps(&message, messagefromfile, filename,\
					VerDialog.DomParamAc, c, d, SignLength,\
					sig_verfahren, hash_verfahren,\
					VerDialog.UserKeyId, VerDialog.Firstname, VerDialog.Name,\
					VerDialog.KeyType, VerDialog.KeyInfo,\
					VerDialog.m_ShowDuration);
				theApp.DoWaitCursor(0);
				
				verifSteps.DoModal();
				
				delete temp_ptr;
				delete temp_ptr2;
				if (Signatur.signature.bits) free(Signatur.signature.bits);
				if (message.octets) free(message.octets);
				return;
			}
			
			theApp.DoWaitCursor(1);
			if (VerDialog.use_affine_coord == true)
			{
				// verifizieren unter Benutzung affiner Koordinaten
				verifStart = clock();
				fret = ecssa_sign_verif_op_ac( c, d, &message, VerDialog.DomParamAc, sig_verfahren, hash_verfahren);
				verifFinish = clock();
				duration = (double)(verifFinish - verifStart) / CLOCKS_PER_SEC;
				if (fret)
				{
					// signature fehlerhaft
					theApp.DoWaitCursor(-1);
					if (VerDialog.m_ShowDuration==TRUE)
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
						LoadString(AfxGetInstanceHandle(),IDS_STRING_BAD_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
						sprintf(pc_str1, pc_str, duration);
						sprintf(pc_str, temp, pc_str1);
						AfxMessageBox (pc_str, MB_ICONEXCLAMATION);
					}
					else
					{
						Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_FAIL, MB_ICONEXCLAMATION);
					}
				}
				else
				{
					// signature correct
					theApp.DoWaitCursor(-1);					
					if (VerDialog.m_ShowDuration==TRUE)
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
						LoadString(AfxGetInstanceHandle(),IDS_STRING_CORRECT_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
						sprintf(pc_str1, pc_str, duration);
						sprintf(pc_str, temp, pc_str1);
						AfxMessageBox (pc_str, MB_ICONINFORMATION);
					}
					else
					{
						Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_CORRECT, MB_ICONINFORMATION);
					}
				}
			}
			else
			{
				// verifizieren unter Benutzung projektiver Koordinaten
				verifStart = clock();
				fret = ecssa_sign_verif_op_pc( c, d, &message, VerDialog.DomParamPc, sig_verfahren, hash_verfahren);
				verifFinish = clock();
				duration = (double)(verifFinish - verifStart) / CLOCKS_PER_SEC;
				if (fret)
				{
					// signature fehlerhaft
					theApp.DoWaitCursor(-1);
					if (VerDialog.m_ShowDuration==TRUE)
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
						LoadString(AfxGetInstanceHandle(),IDS_STRING_BAD_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
						sprintf(pc_str1, pc_str, duration);
						sprintf(pc_str, temp, pc_str1);
						AfxMessageBox (pc_str, MB_ICONEXCLAMATION);
					}
					else
					{
						Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_FAIL, MB_ICONEXCLAMATION);
					}
				}
				else
				{
					// signature correct
					theApp.DoWaitCursor(-1);					
					if (VerDialog.m_ShowDuration==TRUE)
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
						LoadString(AfxGetInstanceHandle(),IDS_STRING_CORRECT_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
						sprintf(pc_str1, pc_str, duration);
						sprintf(pc_str, temp, pc_str1);
						AfxMessageBox (pc_str, MB_ICONINFORMATION);
					}
					else
					{
						Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_CORRECT, MB_ICONINFORMATION);
					}
				}
			}
			theApp.DoWaitCursor(0);
			
			delete temp_ptr;
			delete temp_ptr2;
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return;
		}
		
		// RSA oder DSA Signatur �berpr�fen
		
		//�ffnen der CA-PSE
		PSE PseHandle;
		PseHandle=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle==NULL)
		{
			if (theApp.SecudeLib.LASTERROR==EPIN)
			{
				// falsche PIN-Nummer benutzt
				Message(IDS_STRING_PRIVKEY_WRONG_PIN, MB_ICONEXCLAMATION);
				// Freigeben von dynamisch angelegtem Speicher
				delete temp_ptr;
				delete temp_ptr2;
				if (Signatur.signature.bits) free(Signatur.signature.bits);
				if (message.octets) free(message.octets);
				return;
			}
			// sonstige Fehler beim �ffenen der PSE
			Message(IDS_STRING_ASYMKEY_ERR_ON_OPEN_PSE,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			delete temp_ptr;
			delete temp_ptr2;
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return;
		}
		
		CKeyFile KeyHandling;
		CString caDB_keyid_name = KeyHandling.CreateDistName(VerDialog.Name, VerDialog.Firstname, VerDialog.CreatTime);
		// caDB_keyid_name: unter diesem Bezeichner/Namen wurde das Zertifikat in die CA-Datenbank geschrieben
		
		LPTSTR string3 = new TCHAR[caDB_keyid_name.GetLength()+1];
		_tcscpy(string3, caDB_keyid_name);
		char *string4=string3; // string4 wird benutzt, um in der CA-Datenbank die Parameter abzufragen 
		
		//Besorgen des Zertifikates der Adressaten
		SET_OF_IssuedCertificate *Liste;
		Liste=theApp.SecudeLib.af_cadb_get_user (PseHandle, string4);
		if (Liste==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,MB_ICONSTOP,theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher;
			theApp.SecudeLib.af_close(PseHandle);
			delete string3;
			delete temp_ptr;
			delete temp_ptr2;
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return;
		}
		
		Certificate *Zert;
		OctetString *SNummer;
		SNummer=Liste->element->serial;
		Zert=theApp.SecudeLib.af_cadb_get_Certificate (PseHandle, SNummer);
		if (Zert==NULL)
		{
			Message(IDS_STRING_ASYMKEY_ERR_ON_LOAD_CERTIFICATE,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close(PseHandle);
			delete string3;
			delete temp_ptr;
			delete temp_ptr2;
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return;
		}
		
		bool RsaSig=TRUE;
		
		if (!strcmp(sig_verfahren,"RSA") && !strcmp(hash_verfahren,"MD2")){
			Signatur.signAI=theApp.SecudeLib.md2WithRsaEncryption_aid;}
		else if (!strcmp(sig_verfahren,"RSA") && !strcmp(hash_verfahren,"MD5")){
			Signatur.signAI=theApp.SecudeLib.md5WithRsaEncryption_aid;}
		else if (!strcmp(sig_verfahren,"RSA") && !strcmp(hash_verfahren,"RIPEMD-160")){
			Signatur.signAI=theApp.SecudeLib.ripemd160WithRSASignature_aid;}
		else if (!strcmp(sig_verfahren,"RSA") && !strcmp(hash_verfahren,"SHA")){
			Signatur.signAI=theApp.SecudeLib.shaWithRSASignature_aid;}
		else if (!strcmp(sig_verfahren,"RSA") && !strcmp(hash_verfahren,"SHA-1")){
			Signatur.signAI=theApp.SecudeLib.sha1WithRSASignature_aid;}
		else if (!strcmp(sig_verfahren,"DSA") && !strcmp(hash_verfahren,"SHA")){
			Signatur.signAI=theApp.SecudeLib.dsaWithSHA_aid;
			RsaSig = FALSE;}
		else if (!strcmp(sig_verfahren,"DSA") && !strcmp(hash_verfahren,"SHA-1")){
			Signatur.signAI=theApp.SecudeLib.dsaWithSHA1_aid;
			RsaSig = FALSE;}
		else
		{
			// Fehler beim Auslesen des Verfahrens
			Message(IDS_STRING_ASYMKEY_ERR_ON_READING_SIGNATURE,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			delete string3;
			delete temp_ptr;
			delete temp_ptr2;
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return;
		}
		
		Key keyinfo;
		keyinfo.key=Zert->tbs->subjectPK;
		keyinfo.add_object=NULL;
		keyinfo.add_object_type=NULL;
		keyinfo.alg=NULL;
		keyinfo.key_size=NULL;
		keyinfo.pse_sel=NULL;
		keyinfo.private_key=NULL;
		
		// Pr�fung, ob der zur Signaturerstellung verwendete Algorithmus zum Schl�ssel in der
		// gew�hlten PSE pa�t.
		
		// Fall 1: RSA-Signatur, aber DSS-Schl�ssel
		if ( (keyinfo.key->subjectAI->objid->oid_nelem==6) && (RsaSig == TRUE) )
		{
			Message(IDS_STRING_ASYMKEY_ERR_WRONG_SIGNATURE_FORMAT1,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close(PseHandle);
			delete string3;
			delete temp_ptr;
			delete temp_ptr2;
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return;
		}
		
		// Fall 2: DSS-Signature, aber RSA-Schl�ssel
		if ( (keyinfo.key->subjectAI->objid->oid_nelem==5) && (RsaSig == FALSE) )
		{
			Message(IDS_STRING_ASYMKEY_ERR_WRONG_SIGNATURE_FORMAT2,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			theApp.SecudeLib.af_close (PseHandle);
			delete string3;
			delete temp_ptr;
			delete temp_ptr2;
			if (Signatur.signature.bits) free(Signatur.signature.bits);
			if (message.octets) free(message.octets);
			return;
		}
		
		// Verifikation starten
		
		verifStart = clock();
		fret = theApp.SecudeLib.sec_verify_all(&message, &Signatur, &keyinfo, NULL);
		verifFinish = clock();
		duration = (double)(verifFinish - verifStart) / CLOCKS_PER_SEC;
		if(fret==-1)
		{
			// signature fehlerhaft
			theApp.DoWaitCursor(-1);
			if (VerDialog.m_ShowDuration==TRUE)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_BAD_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1, pc_str, duration);
				sprintf(pc_str, temp, pc_str1);
				AfxMessageBox (pc_str, MB_ICONEXCLAMATION);
			}
			else
			{
				Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_FAIL, MB_ICONEXCLAMATION);
			}
		}
		else
		{
			// signature correct
			theApp.DoWaitCursor(-1);					
			if (VerDialog.m_ShowDuration==TRUE)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SIGNATURE_VERIFICATION_TIME,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_CORRECT_SIGNATURE,temp,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1, pc_str, duration);
				sprintf(pc_str, temp, pc_str1);
				AfxMessageBox (pc_str, MB_ICONINFORMATION);
			}
			else
			{
				Message(IDS_STRING_ASYMKEY_MSG_SIGNATURE_CORRECT, MB_ICONINFORMATION);
			}
		}
		
		theApp.SecudeLib.af_close (PseHandle);
		delete string3;
		delete temp_ptr;
		delete temp_ptr2;
		if (Signatur.signature.bits) free(Signatur.signature.bits);
		if (message.octets) free(message.octets);
	}
}

int GenEcKeyPair(EcDomParam_ac_ptr ecParam)
{
	int error;
	L_NUMBER null[MAXLGTH];
	inttoln(0, null);	
repeat:
	_rand_int(ecParam->privKey, ecParam->r); 
	// ecParam->privKey is a now random integer with 0 <= (ecParam->privKey) < (ecParam->r)
	if (theApp.SecudeLib.comp(ecParam->privKey, null) == 0) goto repeat;
	// ecParam->privKey is a now random integer with 0 < (ecParam->privKey) < (ecParam->r)
	error = ecFp_mult_ac (ecParam->pubKey, ecParam->E, ecParam->privKey, ecParam->G);
	if (ecParam->pubKey->infinity) goto repeat;
	return error; // if error == 0 everything worked fine
}

int EcDomParamAcToString(EcDomParamAcAsString *ecParamString, EcDomParam_ac_ptr ecParam, const int base)
{
	char *privKeyStr;
	char *rStr;
	char *kStr;
	int error = 0;
	
	ecParamString->a = (CString) ecFp_curve_getstr_a (ecParam->E, base); // no error checking!
	ecParamString->b = (CString) ecFp_curve_getstr_b (ecParam->E, base); // no error checking!
	ecParamString->p = (CString) ecFp_curve_getstr_p (ecParam->E, base); // no error checking!
	
	ecParamString->G_xcoord = (CString) ecFp_point_getstr_xcoord_ac (ecParam->G, base); // no error checking!
	ecParamString->G_ycoord = (CString) ecFp_point_getstr_ycoord_ac (ecParam->G, base); // no error checking!
	
	if (ecParam->pubKey->infinity == 0)
	{
		// pubkey ist nicht neutrales Element der ellipt. Kurve Gruppe
		ecParamString->pubKey_xcoord = (CString) ecFp_point_getstr_xcoord_ac (ecParam->pubKey, base);
		ecParamString->pubKey_ycoord = (CString) ecFp_point_getstr_ycoord_ac (ecParam->pubKey, base);
	}
	else
	{
		// pubkey ist neutrales Element O=(inf,inf) der ellipt. Kurve Gruppe
		ecParamString->pubKey_xcoord = (CString) "inf";
		ecParamString->pubKey_ycoord = (CString) "inf";
	}
	
	error += ln_to_string (ecParam->privKey, &privKeyStr, base);
	ecParamString->privKey = (CString) privKeyStr;
	free(privKeyStr);
	
	error += ln_to_string (ecParam->k, &kStr, base);
	ecParamString->k = (CString) kStr;
	free(kStr);
	
	error += ln_to_string (ecParam->r, &rStr, base);
	ecParamString->r = (CString) rStr;
	free(rStr);
	
	return error; // if error > 0 then something is wrong
}

// EOF