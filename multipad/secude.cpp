//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält die Funktionen zur symmetrischen
// Ver- und Entschlüsselung sowie zur Berechnung von Hashwerten.
// 
// In beiden Fällen wird dabei auf das SECUDE-Toolkit aufgesetzt.
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "multipad.h"
#include "crypt.h"
#include "fileutil.h"
#include "CryptDoc.h"
#include "hexdialog.h"	// Dialog-Box für die Schlüsseleingabe
#include "secure.h" // Include-File von SECUDE
#include "pkcs.h"   // Include-File von SECUDE
#include "MyDocument.h"
#include "DlgShowHash.h"

void MakeNewName2(char *dest, int len, const char *format, const char *old, const char *alg);


/*  Die Funktion Crypt führt die eigentliche 
	(symmetrische) Verschlüsselung aus. 
	Über die Parameter, die Crypt von der 
	aufrufenden Funktion bekommt wird so die 
	Funktion sec_encrypt_all bzw. sec_decrypt_all
	angesteuert.
	Der Parameter AlgId gibt an, mit welchem Algorithmus
	die Daten ver-/entschlüsselt werden sollen:
	1 steht für IDEA
	2 steht für DES im ECB mode
	3 steht für DES im CBC mode
	4 steht für Triple-DES im CBC mode
	5 steht für Triple-DES im ECB mode
	6 steht für RC4
	7 steht für rc2

    Sollen später weitere Algorithmen integriert werden, so muß diese Funktion
    aber unter Umständen angepaßt werden:
	Die Funktion baut, in ihrer jetzigen Form, einzig und allein auf der SECUDE-
	Bibliothek auf. Zur Ver- und Entschlüsselung müssen nur der Plain- bzw.
	Ciphertext zusammen mit dem eingegebenen Schlüssel und dem Algorithmen-
	Identifier des zu benutzenden Verfahrens übergeben werden. Alles weitere
	macht das SECUDE-Toolkit.
*/
void Crypt (char* infile, const char *OldTitle, int KeyLength, int AlgId)
{
	
    char outfile[128], title[128], *key, line[256];
    CMyDocument *NewDoc;

	FILE *fi;
	int lenght;

	fi = fopen(infile,"rb");
	fseek(fi,0,SEEK_END);
	lenght = ftell(fi);
	fclose(fi);
	if(lenght < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

// == Definition der Parameter
	Key keyinfo;
	KeyInfo info;
	char AlgTitel[64];
	switch (AlgId){
	case 1://IDEA
		info.subjectAI=theApp.SecudeLib.idea_aid;
		sprintf(AlgTitel, "IDEA");
		break;
	case 2://DES-ECB
		info.subjectAI=theApp.SecudeLib.desECB_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DES_ECB,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(AlgTitel, pc_str);
		break;
	case 3://DES-CBC (Padding)
		info.subjectAI=theApp.SecudeLib.desCBC_pad_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DES_CBC,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(AlgTitel, pc_str);
		break;
	case 4://Triple-DES (CBC mode)
		info.subjectAI=theApp.SecudeLib.desCBC3_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_TRIPLE_DES_CBC,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(AlgTitel, pc_str);
		break;
	case 5://Triple-DES (ECB mode)
		info.subjectAI=theApp.SecudeLib.desEDE_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_TRIPLE_DES_ECB,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(AlgTitel, pc_str);
		break;
	case 6://RC4
		info.subjectAI=theApp.SecudeLib.rc4_aid;
		sprintf(AlgTitel, "RC4");
		break;
	case 7://RC2
		info.subjectAI=theApp.SecudeLib.rc2CBC_aid;
		sprintf(AlgTitel, "RC2");
		break;
	}


    hexdialog KeyDialog(KeyLength/8);
	// ## NEW-CODE (Mai 01)
	// key-input dialog gets now the approppriate title
	LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYINPUT_SYMMETRIC,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str,AlgTitel);
	KeyDialog.SetAlternativeWindowText(line);
	// ## END NEW-CODE
	// Aenderung Jens Liebehenschel, 18.02.00
	// Bei Drücken von Escape oder Klicken auf Abbruch wird das Fenster 
	// geschlossen, aber die Ver-/Entschluesselung wird trotzdem durchgefuehrt.
	// Es muss der Returnwert von DoModal in der Funktion Display überprüft werden.
//	KeyDialog.Display();
	if (KeyDialog.Display() != IDOK) 
	{
		return;
	}
	// Ende der Aenderung
	if(KeyDialog.GetLen() ==0) return;
    if ((AlgId==6)||(AlgId==7)){
		KeyLength=8*(KeyDialog.GetLen());
	}
	key = KeyDialog.GetData();

    GetTmpName(outfile,"cry",".tmp");


	info.subjectkey.nbits=KeyLength;
	info.subjectkey.bits=key;
	keyinfo.key=&info;
	keyinfo.pse_sel=NULL;
	keyinfo.alg=NULL;
	keyinfo.add_object=NULL;
	keyinfo.add_object_type=NULL;
	keyinfo.key_size=NULL;
	keyinfo.private_key=NULL;


    if(KeyDialog.m_Decrypt){		// Entschlüsselung ausgewählt
		  
		// Initialisierung der Variablen
		// in enthält den Ciphertext, out den ermittelten Plaintext
		BitString in;
		OctetString out,*help;
		
		//Konversion File->BitString (über den Umweg OctetString)
		help = theApp.SecudeLib.aux_file2OctetString(infile);
		in.nbits=8*(help->noctets);
		in.bits=help->octets;
				
		//out initialisieren:
		out.noctets=0;
		out.octets=(char*)malloc(in.nbits/8+16); // mindestens bis zur nächsten 
                                                         // Blockgrenze Speicher 

		// Entschlüsselung des Ciphertextes mit dem vom Benutzer eingegebenen Schlüssel.
		if(theApp.SecudeLib.sec_decrypt_all (&in, &out, &keyinfo)==-1){
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_ERROR_2,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			theApp.SecudeLib.aux_free_OctetString(&help);
			free(out.octets);
			return;}
		theApp.SecudeLib.aux_free_OctetString(&help);
		
		//Datenausgabe:
		theApp.SecudeLib.aux_OctetString2file(&out, outfile, 2);
		free(out.octets);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.m_einstr);
		remove(outfile);
		if(NewDoc) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,AlgTitel,OldTitle,KeyDialog.m_einstr);
			NewDoc->SetTitle(title);
		}
	}
    
	else {			// Verschlüsseln ausgewählt
		
		// Einlesen des zu verschlüsselnden Textes aus infile
		// Der Plaintext wird in der Variablen "in", der resultierende Ciphertext
		// in der Variablen "out" gespeichert.
		OctetString *in;
		BitString out;
		in = theApp.SecudeLib.aux_file2OctetString(infile);
		out.nbits=0;
		out.bits=(char*)malloc(in->noctets+16);  // Speicher bis zur
                                                         // Blockgrenze
		
		// Verschlüsselung des Plaintextes mit dem vom Benutzer eingegebenen Schlüssel.
		if (theApp.SecudeLib.sec_encrypt_all (in, &out, &keyinfo)==-1){
			theApp.SecudeLib.aux_free_OctetString(&in);
			free(out.bits);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			return;}
		theApp.SecudeLib.aux_free_OctetString(&in);
		
		//Datenausgabe:
		OctetString *outOctet;
		outOctet = theApp.SecudeLib.aux_BString2OString(&out);
		free(out.bits);
		theApp.SecudeLib.aux_OctetString2file(outOctet,outfile,2);
		theApp.SecudeLib.aux_free_OctetString(&outOctet);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.m_einstr);
		remove(outfile);
		if(NewDoc) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,AlgTitel,OldTitle,KeyDialog.m_einstr);
			NewDoc->SetTitle(title);
		}
    }
}


/*  Die Funktion hash dient zum hashen der Daten.
	Sie benutzt die Funktion sec_hash_all().
	Welche Hashfunktion benutzt wird, hängt von den
	übergebenen Parametern (AlgId) ab:
	1 steht für MD2
	2 steht für MD4
	3 steht für MD5
	4 steht für SHA
	5 steht für SHA-1
	6 steht für RIPEMD160
*/

void hash (char* infile, const char *OldTitle, int AlgId)
{
	char outfile[128], title[128];
    CMyDocument *NewDoc;
	GetTmpName(outfile,"cry",".hex");
	
	OctetString *message, hash;
	message = theApp.SecudeLib.aux_file2OctetString(infile);
	hash.noctets=0;
    
	char *AlgTitel;
	switch (AlgId){
		case 1://MD2
			theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.md2_aid,NULL);
			AlgTitel="MD2";
			break;
		case 2://MD4
			theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.md4_aid,NULL);
			AlgTitel="MD4";
			break;
		case 3://MD5
			theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.md5_aid,NULL);
			AlgTitel="MD5";
			break;
		case 4://SHA
			theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.sha_aid,NULL);
			AlgTitel="SHA";
			break;
		case 5://SHA_1
			theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.sha1_aid,NULL);
			AlgTitel="SHA-1";
			break;
		case 6://RIPEMD160
			theApp.SecudeLib.sec_hash_all(message,&hash,theApp.SecudeLib.ripemd160_aid,NULL);
			AlgTitel="RIPEMD160";
			break;
	}
	CDlgShowHash HashDlg;
	HashDlg.SetHash( hash, AlgTitel );
	if ( IDOK == HashDlg.DoModal() )
	{
		theApp.SecudeLib.aux_free_OctetString(&message);
		//Datenausgabe:
		theApp.SecudeLib.aux_OctetString2file(&hash,outfile,2);
		theApp.SecudeLib.aux_free(hash.octets);

		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		if(NewDoc) {
				LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
				MakeNewName2(title,sizeof(title),pc_str,OldTitle,AlgTitel);
				NewDoc->SetTitle(title);
			}

	}
}


/* Die folgende Funktion generiert aus dem Namen des Fensters mit den zu bearbeitenden
   Daten einen Namen für das Fenster, in dem die Ausgabe dargestellt wird		*/
void MakeNewName2(char *dest, int len, const char *format, const char *old, const char *alg)
{
	///////////////////////////////////////////////////////////////////////
	// Aenderung Jens Liebehenschel, 30.12.1998
	///////////////////////////////////////////////////////////////////////
	// Um die Warnung C4018 
	// "Konflikt zwischen signed und unsigned"
	// wegzubekommen, wird der Type-Cast nach 
	// size_t (= unsigned int) durchgefuehrt.
	///////////////////////////////////////////////////////////////////////
    if(strlen(format)+strlen(old)+strlen(alg)<(size_t)len)
        sprintf(dest,format,alg,old);
    else
        sprintf(dest,format,alg,"...");
	///////////////////////////////////////////////////////////////////////
	// Ende Aenderung Jens Liebehenschel, 30.12.1998
	///////////////////////////////////////////////////////////////////////
}