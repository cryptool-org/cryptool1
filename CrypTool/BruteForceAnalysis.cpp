//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Christian Tobias
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält die Funktionen zur symmetrischen
// Ver- und Entschlüsselung sowie zur Berechnung von Hashwerten.
// 
// In beiden Fällen wird dabei auf das SECUDE-Toolkit aufgesetzt.
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "Cryptography.h"
#include "FileTools.h"
#include "CryptDoc.h"
#include "secure.h" // Include-File von SECUDE
#include "pkcs.h"   // Include-File von SECUDE
#include "AppDocument.h"
#include "DlgKeyHexAnalysis.h"
#include "DlgBruteForceAES.h"
#include "DialogeMessage.h"

void FreePar(CryptPar *par);

int KLen(unsigned __int64 *k)
{
	char *c;
	int i;
	
	c = (char *) k;
	for(i=7; i>0; i--)
		if(c[i] != 0) break;
		return (i+1);
}

/*  Die Funktion Brute führt die eigentliche Analyse der
	symmetrischen Verschlüsselung über Brute force aus. 
	Über die Parameter, die Crypt von der 
	aufrufenden Funktion bekommt wird so die 
	Funktion sec_encrypt_all bzw. angesteuert.
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
	macht das SECUDE-Toolkit. */
UINT Brute(PVOID p)
{
	int windowlen = theApp.Options.m_BFEntropyWindow;
    char outfile[CRYPTOOL_PATH_LENGTH], key[128], line[256],kfound[128];
	int i, l, lorg, r, AlgId, pos,lenght;
	int distr[256],keybits;
	double entr, emax, f;
	double *xlogx = new double[windowlen + 1];
	if (!xlogx) return 0;
	xlogx[0] = 0.0;
	for (i = 1; i <= windowlen; i++) 
		xlogx[i] = (f = i) * log(f);
	
	CryptPar *par;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	r=0;
	
	FILE *fi;
	
	fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	lenght = ftell(fi);
	fclose(fi);
	if(lenght < 1) {
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		return r;
	}
	
	for(i=0; i<sizeof(key); i++) key[i]=0;
	
	//Definition der Parameter
	Key keyinfo;
	KeyInfo info;
	char AlgTitel[128];
	AlgId = *((int *) par->key);
	switch (AlgId){
	case 1://IDEA
		info.subjectAI=theApp.SecudeLib.idea_aid;
		strcpy(AlgTitel,"IDEA");
		break;
	case 2://DES-ECB
		info.subjectAI=theApp.SecudeLib.desECB_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DES_ECB,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(AlgTitel,pc_str);
		break;
	case 3://DES-CBC (Padding)
		info.subjectAI=theApp.SecudeLib.desCBC_pad_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DES_CBC,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(AlgTitel,pc_str);
		break;
	case 4://Triple-DES (CBC mode)
		info.subjectAI=theApp.SecudeLib.desCBC3_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_TRIPLE_DES_CBC,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(AlgTitel,pc_str);
		break;
	case 5://Triple-DES (ECB mode)
		info.subjectAI=theApp.SecudeLib.desEDE_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_TRIPLE_DES_ECB,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(AlgTitel,pc_str);
		break;
	case 6://RC4
		info.subjectAI=theApp.SecudeLib.rc4_aid;
		strcpy(AlgTitel,"RC4");
		break;
	case 7://RC2
		info.subjectAI=theApp.SecudeLib.rc2CBC_aid;
		strcpy(AlgTitel,"RC2");
		break;
	}
	
	class CDlgBruteForceAES KeyDialog;
	
	if(KeyDialog.Display(AlgTitel,par->keylenmin,par->keylenmax,par->keylenstep)!=IDOK)
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		return 0;
	}
	
	if((keybits=KeyDialog.GetBinlen()) ==0) return r;
    //if ((AlgId==6)||(AlgId==7))
	//	par->keylen=8*keylen;
	
    if(par->flags & CRYPT_DO_PROGRESS)
	{
		CString title;
		title.Format(IDS_STRING_ANALYSE_ON,AlgTitel);
		CString message;
		message.Format(IDS_STRING_MSG_SEARCHING_COMPLETE,KeyDialog.GetSearchBitLen());
		theApp.fs.setModelTitleFormat(&KeyDialog,title,message);
		theApp.fs.Display();
	}
	
    GetTmpName(outfile,"cry",".tmp");
	
	// Einlesen des zu verschlüsselnden Textes aus infile
	// Der Plaintext wird in der Variablen "in", der resultierende Ciphertext
	// in der Variablen "out" gespeichert.
	
	BitString in;
	OctetString out,*help;
	
	//Konversion File->BitString (über den Umweg OctetString)
	help = theApp.SecudeLib.aux_file2OctetString(par->infile);
	in.nbits=8*(help->noctets);
	in.bits=help->octets;
	
	out.noctets=0;
	out.octets=(char*)malloc(in.nbits/8+16);   // genug Speicher !!
	
	info.subjectkey.nbits= keybits;
	info.subjectkey.bits=(char *)&key;
	keyinfo.key=&info;
	keyinfo.pse_sel=NULL;
	keyinfo.alg=NULL;
	keyinfo.add_object=NULL;
	keyinfo.add_object_type=NULL;
	keyinfo.key_size=NULL;
	keyinfo.private_key=NULL;
	
	lorg = in.nbits;
	l = min(8*windowlen,lorg);
	in.nbits = l;
	l = l/8;
	
	emax = 0.0;
	
	for(i=0; i<sizeof(key); i++)
	{
		key[i]=0;
		kfound[i]=0;
	}
	
	pos=0;
	while ( KeyDialog.Step())  // Nächsten Schlüssel ermitteln
	{                               // und Fortschritt
		// Entschlüsselung des Plaintextes mit dem vom Benutzer eingegebenen Schlüssel.
		if(par->flags & CRYPT_DO_PROGRESS)
		{
			if(theApp.fs.m_canceled)
			{
				theApp.SecudeLib.aux_free_OctetString(&help);
				free(out.octets);
				theApp.fs.cancel();
				par->flags |= CRYPT_DONE;
				FreePar(par);
				return 2;
			}
		}
		KeyDialog.GetDataInt(key); // Schlüssel besorgen
		
		out.noctets=0;
		int decryptionError = 0;
		if (theApp.SecudeLib.sec_decrypt_all (&in, &out, &keyinfo)==-1)
		{
			struct ErrStack *err;
			err = theApp.SecudeLib.th_remove_last_error();
			if ( err->e_number == 1792 ) decryptionError = 0;
			else                         decryptionError = err->e_number;
			if(err->e_text) theApp.SecudeLib.aux_free(err->e_text);
			if(err->e_proc) theApp.SecudeLib.aux_free(err->e_proc);
			if(err->e_addr)
			{
				switch (err->e_addrtype)
				{
				case int_n:
					break;
				case OctetString_n:
					theApp.SecudeLib.aux_free_OctetString((OctetString **) &(err->e_addr));
					break;
				case BitString_n:
					theApp.SecudeLib.aux_free_BitString((BitString **) &(err->e_addr));
					break;
				case AlgId_n:
					//					theApp.SecudeLib.aux_free_AlgId((AlgId **) &(err->e_addr));
					break;
				case KeyInfo_n:
					theApp.SecudeLib.aux_free_KeyInfo((KeyInfo **) &(err->e_addr));
					break;
				case ObjId_n:
					theApp.SecudeLib.aux_free_ObjId((ObjId **) &(err->e_addr));
					break;
				case KeyBits_n:
					theApp.SecudeLib.aux_free_KeyBits((KeyBits **) &(err->e_addr));
					break;
				case PSEToc_n:
					theApp.SecudeLib.aux_free_PSEToc((PSEToc **) &(err->e_addr));
					break;
				}
			}
			theApp.SecudeLib.aux_free(err);
		}

		// else                 // Falls kein Fehler Entropie berechenen
		if ( !decryptionError ) {
			memset(distr,0,sizeof(distr));
			for(i=0;i<l;i++) distr[(unsigned char) out.octets[i]]++;
			for(entr = i = 0; i<256; i++)
				entr += xlogx[distr[i]];
			if(entr > emax)
			{
				emax = entr;
				memcpy(kfound,key,keybits / 8);
			}
		}
	}
	
	if (emax == 0.0)
	{
		Message(IDS_STRING_NO_VALID_KEYS_FOUND, MB_ICONINFORMATION);
		if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	
	CDlgKeyHexAnalysis dia;
	
	if(IDCANCEL == dia.Display(kfound,keybits / 8))
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	
	for(i=0; i<sizeof(key); i++) key[i]=0;
	memcpy(key,dia.GetData(),keybits / 8);
	info.subjectkey.bits = (char *)key;
	info.subjectkey.nbits = keybits;
	
	in.nbits = lorg;
	out.noctets=0;
	if (theApp.SecudeLib.sec_decrypt_all (&in, &out, &keyinfo)==-1){
		theApp.SecudeLib.aux_free_OctetString(&help);
		free(out.octets);
		Message(IDS_STRING_DECRYPTION_ERROR,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
		if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	
	//Datenausgabe:
	theApp.SecudeLib.aux_OctetString2file(&out,outfile,2);
	if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName3(line,sizeof(line),pc_str, AlgTitel, par->OldTitle, dia.m_einstr.GetBuffer(1));
    theApp.ThreadOpenDocumentFileNoMRU(outfile,line,dia.m_einstr.GetBuffer(1));
	theApp.SecudeLib.aux_free_OctetString(&help);
	free(out.octets);
	
	par->flags |= CRYPT_DONE;
	FreePar(par);
	
	return r;
}
