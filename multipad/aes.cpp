//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält die Funktionen zur symmetrischen
// Ver- und Entschlüsselung.
// 
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "multipad.h"
#include "crypt.h"
#include "fileutil.h"
#include "CryptDoc.h"
#include "hexdialog.h"	// Dialog-Box für die Schlüsseleingabe
#include "..\AES\mars\mars.h"
#include "..\AES\RC6\RC6.h"
#include "..\AES\Rijndael\Rijndael-api-fst.h"
#include "..\AES\Serpent\Serpent.h"
#include "..\AES\Twofish\Twofish.h"
#include "MyDocument.h"
#include "DialogKeyHex.h"
#include "AESSuche.h"   // Dialogbox für die Schlüsselsuche

void MakeNewName2(char *dest, int len, const char *format, const char *old, const char *alg);
void FreePar(CryptPar *par);
void doaescrypt(int AlgId,char mode,int keylen,char *keybuffhex,unsigned char *borg,int datalen,
				unsigned char *bcip);


/*  Die Funktion doaescrypt führt die eigentliche 
(symmetrische) Verschlüsselung aus. 
Über die Parameter, die doaescrypt von der 
aufrufenden Funktion bekommt wird so die 
Funktion sec_encrypt_all bzw. sec_decrypt_all
angesteuert. (je nach mode)
keybufhex enthält den Schlüssel, Länge keylen,
borg den Orginaltext, Länge datalen, und in bcip
wird der ciphertext gespeichert. 
Der Parameter AlgId gibt an, mit welchem Algorithmus
die Daten ver-/entschlüsselt werden sollen:
*/
void doaescrypt(int AlgId,char mode,int keylen,char *keybuffhex,unsigned char *borg,int datalen,
				unsigned char *bcip)
{
	switch (AlgId){
	case 1://Mars
		{
			keyInstanceMars keyin;
			cipherInstanceMars cipher;
			makeKeyMars(&keyin,mode,keylen*8,keybuffhex);
			cipherInitMars(&cipher,MODE_CBC,"00000000000000000000000000000000");
			if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
				blockDecryptMars(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			else
				blockEncryptMars(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			break;
		}
	case 2://RC6
		{
			keyInstanceRC6 keyin;
			cipherInstanceRC6 cipher;
			makeKeyRC6(&keyin,mode,keylen*8,keybuffhex);
			cipherInitRC6(&cipher,MODE_CBC,"00000000000000000000000000000000");
			if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
				blockDecryptRC6(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			else
				blockEncryptRC6(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			break;
		}
	case 3://Rijndael
		{
			keyInstanceRijndael keyin;
			cipherInstanceRijndael cipher;
			makeKeyRijndael(&keyin,mode,keylen*8,keybuffhex);
			cipherInitRijndael(&cipher,MODE_CBC,"00000000000000000000000000000000");
			if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
				blockDecryptRijndael(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			else
				blockEncryptRijndael(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			break;
		}
	case 4://Serpent
		{
			keyInstanceSerpent keyin;
			cipherInstanceSerpent cipher;
			makeKeySerpent(&keyin,mode,keylen*8,keybuffhex);
			cipherInitSerpent(&cipher,MODE_CBC,"00000000000000000000000000000000");
			if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
				blockDecryptSerpent(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			else
				blockEncryptSerpent(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			break;
		}
	case 5://Twofish
		{
			keyInstanceTwofish keyin;
			cipherInstanceTwofish cipher;
			makeKeyTwofish(&keyin,mode,keylen*8,keybuffhex);
			cipherInitTwofish(&cipher,MODE_CBC,"00000000000000000000000000000000");
			if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
				blockDecryptTwofish(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			else
				blockEncryptTwofish(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			break;
		}
	}
}


/*  Die Funktion AESCrypt führt die eigentliche 
(symmetrische) Verschlüsselung aus. 
Der Parameter AlgId gibt an, mit welchem Algorithmus
die Daten ver-/entschlüsselt werden sollen:
1 steht für Mars
2 steht für RC6
3 steht für Rijndael
4 steht für Serpent
5 steht für Twofish
*/
void AESCrypt (char* infile, const char *OldTitle, int AlgId)
{
	
    char outfile[128], line[256], keybuffhex[65],AlgTitel[128];
	unsigned char keybuffbin[33];
	unsigned char *borg, *bcip, *key;
	char mode;
	int keylen;
	int titleID;

	FILE *fi;
	int i, datalen;
	
	fi = fopen(infile,"rb");
	fseek(fi,0,SEEK_END);
	datalen = ftell(fi);
	fclose(fi);
	if(datalen < 1) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		return;
	}

	strcpy(AlgTitel,"");           // Name setzen
	switch (AlgId)
	{
	case 1:                        // Mars
		titleID = IDS_CRYPT_MARS;
		break;
	case 2:                        // RC6
		titleID = IDS_CRYPT_RC6;
		break;
	case 3:                        // Rijndael
		titleID = IDS_CRYPT_RIJNDAEL;
		break;
	case 4:                        // Serpent
		titleID = IDS_CRYPT_SERPENT;
		break;
	case 5:                        // Twofish
		titleID = IDS_CRYPT_TWOFISH;
		break;
	}
	LoadString(AfxGetInstanceHandle(),titleID,pc_str,STR_LAENGE_STRING_TABLE);
	strcpy( AlgTitel, pc_str );
	if ( 3 == AlgId )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYINPUT_AES_RIJNDAEL,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line, pc_str);
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEYINPUT_AES_CANDIDATE,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,AlgTitel);
	}
	
    hexdialog KeyDialog(32);
	KeyDialog.SetAlternativeWindowText(line);
	if (KeyDialog.Display() != IDOK) 
	{
		return;
	}
	key = (unsigned char *) KeyDialog.GetData();
	if ( 0 == (keylen = KeyDialog.GetLen()) ) return;

	for(i=0;i<32;i++) keybuffbin[i]=0;
	for(i=0;i<keylen; i++) keybuffbin[i] = key[i];
	
	if(keylen <= 16) keylen = 16;
	else if(keylen <= 24) keylen = 24;
	else keylen = 32;
	
	for(i=0; i<keylen; i++) {
		sprintf(keybuffhex+2*i,"%02.2X",keybuffbin[i]);
	}
	
	borg = (unsigned char *) malloc(datalen+32);
	bcip = (unsigned char *) malloc(datalen+64);
	
	fi = fopen(infile,"rb");
	fread(borg,1,datalen,fi);
	fclose(fi);
	
    if(KeyDialog.m_Decrypt)	{	   // Entschlüsselung ausgewählt
		mode = DIR_DECRYPT;        // padden der Eingabe
		for(; datalen %16; datalen++) borg[datalen]=0;
	}
	else {
		mode = DIR_ENCRYPT;        // padden der Eingabe
		borg[datalen++]=1;
		for(; datalen %16; datalen++) borg[datalen]=0;
	}
	datalen <<= 3;                 // Länge in Bits
	
	GetTmpName(outfile,"cry",".tmp");
	
	doaescrypt(AlgId,mode,keylen,keybuffhex,borg,datalen,bcip);
	
	free(borg);
	datalen >>= 3;                 // Länge wieder in Byte
	
    if(KeyDialog.m_Decrypt)
	{	                           // Entschlüsselung ausgewählt
		// Padding entfernen
		for(datalen--; 0 == bcip[datalen]; datalen--);
	}
	
	fi = fopen(outfile,"wb");
	fwrite(bcip, 1, datalen, fi);
	fclose(fi);

	OpenNewDoc( outfile, KeyDialog.m_einstr, OldTitle, titleID, KeyDialog.m_Decrypt );
}


/////////////////////////////////////////////////////////////////////////////////////////
// AESBrute() führt eine Schlüsselraumsuche für die AES Verfahren aus.
// in (CryptPar *)p sind alle nötigen Daten (AlgId siehe AESCrypt())
// enthalten.
UINT AESBrute(PVOID p)
{
    char outfile[128], line[256], AlgTitel[128];
    char mode, *keyhex, kfound[65];
	unsigned char key[128], *borg, *bcip;
	int i,pos, AlgId, cntr, keylen, datalen;
	int distr[256];
	double entr, emax, f;
	FILE *fi;
	CryptPar *par;
	Key keyinfo;
	KeyInfo info;
	int titleID;
	
	mode = DIR_DECRYPT;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		theApp.DoWaitCursor(1);
	
	fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	datalen = ftell(fi);
	fclose(fi);
	
	if(datalen < 1) 
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_INPUT_TEXT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,1);
		AfxMessageBox (line);
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			theApp.DoWaitCursor(-1);
		return 0;
	}
	borg = (unsigned char *) malloc(datalen+32);
	bcip = (unsigned char *) malloc(datalen+64);
	
	if(datalen > 1000)     // nur die ersten 1000 Zeichen anschauen
		datalen=1000;
	
	AlgId = *((int *) par->key);  // Namen setzen

	strcpy(AlgTitel,"");           // Name setzen
	switch (AlgId)
	{
	case 1:                        // Mars
		titleID = IDS_CRYPT_MARS;
		break;
	case 2:                        // RC6
		titleID = IDS_CRYPT_RC6;
		break;
	case 3:                        // Rijndael
		titleID = IDS_CRYPT_RIJNDAEL;
		break;
	case 4:                        // Serpent
		titleID = IDS_CRYPT_SERPENT;
		break;
	case 5:                        // Twofish
		titleID = IDS_CRYPT_TWOFISH;
		break;
	}
	LoadString(AfxGetInstanceHandle(),titleID,pc_str,STR_LAENGE_STRING_TABLE);
	strcpy( AlgTitel, pc_str );
	
	fi = fopen(par->infile,"rb");
	fread(borg,1,datalen,fi);
	fclose(fi);
	
	for(; datalen %16; datalen++)
		borg[datalen]=0;          // padden
	datalen <<= 3;
	
	class AESSuche KeyDialog;
	
	if(KeyDialog.Display(AlgTitel)!=IDOK||KeyDialog.GetLen() ==0)
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			theApp.DoWaitCursor(-1);
		return 0;
	}
	
	if(par->flags & CRYPT_DO_PROGRESS)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYSE_ON,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,AlgTitel);
		theApp.fs.Display(line);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_SEARCHING_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	
	info.subjectkey.bits=(char *)key;
	keyinfo.key=&info;
	keyinfo.pse_sel=NULL;
	keyinfo.alg=NULL;
	keyinfo.add_object=NULL;
	keyinfo.add_object_type=NULL;
	keyinfo.key_size=NULL;
	keyinfo.private_key=NULL;
	
	emax = 0.0;                      // max Entropie 
	
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	keylen = KeyDialog.GetLen();
//	if(keylen <= 16) keylen = 16;
//	else if(keylen <= 24) keylen = 24;
//	else keylen = 32;
//	par->keylen = keylen;
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	par->keylen = KeyDialog.GetLen();
	keylen = par->keylen;

		
	info.subjectkey.nbits=par->keylen;

	keyhex=KeyDialog.GetData();
	memcpy(kfound,keyhex,65);
	
    GetTmpName(outfile,"cry",".tmp");

	pos=0;
	while (cntr=KeyDialog.Step())    // nächsten Schlüssel setzen
	{                                // und Fortschritt erhalten
		keyhex=KeyDialog.GetData();  // Schlüssel holen
		
		if(par->flags & CRYPT_DO_PROGRESS)
		{
			if(theApp.fs.m_canceled)
			{
				theApp.fs.cancel();
				par->flags |= CRYPT_DONE;
				FreePar(par);
				free(borg);
				return 2;
			}
			if(cntr>pos)            // nur einmal für jedes Prozent
			{
				theApp.fs.Set(cntr);
				pos++;
			}
		}
		
		doaescrypt(AlgId,mode,keylen,keyhex,borg,datalen,bcip);
		
		for(i=0;i<256;i++)           // Entropie berechnen
			distr[i]=0;
		for(i=0;i<1000;i++)
			distr[(unsigned int) bcip[i]]++;
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
			memcpy(kfound,keyhex,65);
		}
	}
	
	CDialogKeyHex dia;
	
	if(IDCANCEL == dia.Display(kfound))
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			theApp.DoWaitCursor(-1);
		if(par->flags & CRYPT_DO_PROGRESS)
			theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return 0;
	}

/*
	for (i=0;i<64;i++)
		kfound[i]='0';
	keyhex=dia.GetData();
	for (i=0;i<dia.GetLen();i++)
	{                        // gefundenen Schlüssel in String 
		pos=keyhex[i];       // umwandeln
		kfound[i*2]=((pos/16)>9)?(pos/16)-10+'A':(pos/16)+'0';
		kfound[(i*2)+1]=((pos%16)>9)?(pos%16)-10+'A':(pos%16)+'0';
	}
*/

	if(par->flags & CRYPT_DO_PROGRESS)
		theApp.fs.cancel();

	fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	datalen = ftell(fi);
	fseek(fi,0,SEEK_SET);
	fread(borg,1,datalen,fi);
	fclose(fi);
	
	for(; datalen %16; datalen++)    // padden
		borg[datalen]=0;            
	datalen <<= 3;
	
	doaescrypt(AlgId,mode,keylen,kfound,borg,datalen,bcip);
	free(borg);
	
	datalen >>= 3;
	
	for(datalen--; 0 == bcip[datalen]; datalen--);
	
	fi = fopen(outfile,"wb");        // Ergebnis ausgeben
	fwrite(bcip, 1, datalen, fi);
	fclose(fi);
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName3(line,sizeof(line),pc_str, AlgTitel, par->OldTitle, dia.m_einstr.GetBuffer(1));
    theApp.ThreadOpenDocumentFileNoMRU(outfile,line,dia.m_einstr.GetBuffer(1));
	
	par->flags |= CRYPT_DONE;
	FreePar(par);
	
	return 0;
}
