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
#include "secure.h" // Include-File von SECUDE
#include "pkcs.h"   // Include-File von SECUDE
#include "MyDocument.h"
#include "DialogKeyHex.h"
#include "AESSuche.h"

#define WINSIZE	128

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
  macht das SECUDE-Toolkit.
*/
UINT Brute(PVOID p)
{
	
    char outfile[128], key[128], line[256],kfound[128];
	int i, l, lorg, r, AlgId, cntr,pos,lenght;
	int distr[256],keylen;
	double entr, emax, f;
	CryptPar *par;
	
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	r=0;
	
	FILE *fi;
	
	fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	lenght = ftell(fi);
	fclose(fi);
	if(lenght < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41544,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			theApp.DoWaitCursor(-1);
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
		LoadString(AfxGetInstanceHandle(),IDS_STRING41527,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(AlgTitel,pc_str);
		break;
	case 3://DES-CBC (Padding)
		info.subjectAI=theApp.SecudeLib.desCBC_pad_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING41528,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(AlgTitel,pc_str);
		break;
	case 4://Triple-DES (CBC mode)
		info.subjectAI=theApp.SecudeLib.desCBC3_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING41529,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(AlgTitel,pc_str);
		break;
	case 5://Triple-DES (ECB mode)
		info.subjectAI=theApp.SecudeLib.desEDE_aid;
		LoadString(AfxGetInstanceHandle(),IDS_STRING41530,pc_str,STR_LAENGE_STRING_TABLE);
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
	
	class AESSuche KeyDialog;
	
	if(KeyDialog.Display(AlgTitel,par->keylen/8)!=IDOK||KeyDialog.GetLen() ==0)
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			theApp.DoWaitCursor(-1);
		return 0;
	}
	
	if((keylen=KeyDialog.GetBinlen()) ==0) return r;
    if ((AlgId==6)||(AlgId==7))
		par->keylen=8*keylen;
	
    if(par->flags & CRYPT_DO_PROGRESS)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41571,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,AlgTitel);
		theApp.fs.Display(line);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41572,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
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
	
	info.subjectkey.nbits=par->keylen;
	info.subjectkey.bits=(char *)&key;
	keyinfo.key=&info;
	keyinfo.pse_sel=NULL;
	keyinfo.alg=NULL;
	keyinfo.add_object=NULL;
	keyinfo.add_object_type=NULL;
	keyinfo.key_size=NULL;
	keyinfo.private_key=NULL;
	
	lorg = in.nbits;
	l = min(8*WINSIZE,lorg);
	in.nbits = l;
	l = l/8;
	
	emax = 0.0;
	
	for(i=0; i<sizeof(key); i++)
	{
		key[i]=0;
		kfound[i]=0;
	}
	
	pos=0;
	while ( cntr=KeyDialog.Step())  // Nächsten Schlüssel ermitteln
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
			if(cntr>pos)           // Nur bei Forschrittsänderung
			{
				pos++;
				theApp.fs.Set(cntr);
			}
		}
		KeyDialog.GetDataInt(key); // Schlüssel besorgen
		
		out.noctets=0;
		if (theApp.SecudeLib.sec_decrypt_all (&in, &out, &keyinfo)==-1)
		{
			struct ErrStack *err;
			err = theApp.SecudeLib.th_remove_last_error();
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
		else                 // Falls kein Fehler Entropie berechenen
		{
			for(i=0;i<256;i++) distr[i]=0;
			for(i=0;i<l;i++) distr[(unsigned char) out.octets[i]]++;
			for(entr = i = 0; i<256; i++)
			{
				if(distr[i]>0)
				{
					f = distr[i];
					entr = entr + f*log(f);
				}
			}
			if(entr > emax)
			{
				emax = entr;
				memcpy(kfound,key,keylen);
			}
		}
	}
	
	if (emax == 0.0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING61427,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (pc_str);
		if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	
	CDialogKeyHex dia;
	
	if(IDCANCEL == dia.Display(kfound,keylen))
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			theApp.DoWaitCursor(-1);
		if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	
	for(i=0; i<sizeof(key); i++) key[i]=0;
	i = dia.GetLen();
	memcpy(key,dia.GetData(),i);
	if ((AlgId==6)||(AlgId==7))
		par->keylen=8*i;
	info.subjectkey.bits=(char *)key;
	info.subjectkey.nbits=par->keylen;
	
	in.nbits = lorg;
	out.noctets=0;
	if (theApp.SecudeLib.sec_decrypt_all (&in, &out, &keyinfo)==-1){
		theApp.SecudeLib.aux_free_OctetString(&help);
		free(out.octets);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41436,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
		if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	
	//Datenausgabe:
	theApp.SecudeLib.aux_OctetString2file(&out,outfile,2);
	if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING41575,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName3(line,sizeof(line),pc_str, AlgTitel, par->OldTitle, dia.m_einstr.GetBuffer(1));
    theApp.ThreadOpenDocumentFileNoMRU(outfile,line,dia.m_einstr.GetBuffer(1));
	theApp.SecudeLib.aux_free_OctetString(&help);
	free(out.octets);
	
	par->flags |= CRYPT_DONE;
	FreePar(par);
	
	return r;
}
