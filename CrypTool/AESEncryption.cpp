//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enthält die Funktionen zur symmetrischen
// Ver- und Entschlüsselung.
// 
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "DlgKeyHexFixedLen.h"
#include "..\AES\mars\mars.h"
#include "..\AES\RC6\RC6.h"
#include "..\AES\Rijndael\Rijndael-api-fst.h"
#include "..\AES\Serpent\Serpent.h"
#include "..\AES\Twofish\Twofish.h"
#include "AppDocument.h"
#include "DlgKeyHexAnalysis.h"
#include "DlgBruteForceAES.h"   // Dialogbox für die Schlüsselsuche

#include "DialogeMessage.h"
#include "CrypToolTools.h"
#include "Cryptography.h"
#include "MakeNewName.h"


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
	die Daten ver-/entschlüsselt werden sollen: */
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
	5 steht für Twofish */
void AESCrypt (char* infile, const char *OldTitle, int AlgId, bool Enc_Or_Dec, char * NewFileName, char* NewFileKey)
{
	
    char outfile[CRYPTOOL_PATH_LENGTH], keybuffhex[65],title[128];
	CString AlgTitle,Title;
	unsigned char keybuffbin[33];
	unsigned char *borg, *bcip, *key;
	char mode;
	int keylen;

	FILE *fi;
	int i, datalen;
	
	fi = fopen(infile,"rb");
	fseek(fi,0,SEEK_END);
	datalen = ftell(fi);
	fclose(fi);
	if(datalen < 1) {
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		return;
	}

	UINT AlgResIds[] = {
		0, // dummy
		IDS_CRYPT_MARS,
		IDS_CRYPT_RC6,
		IDS_CRYPT_RIJNDAEL,
		IDS_CRYPT_SERPENT,
		IDS_CRYPT_TWOFISH
	};
	ASSERT(AlgId < sizeof(AlgResIds)/sizeof(UINT));
	AlgTitle.LoadString(AlgResIds[AlgId]);
	if ( 3 == AlgId )
		Title.LoadString(IDS_STRING_KEYINPUT_AES_RIJNDAEL);
	else
		Title.Format(IDS_STRING_KEYINPUT_AES_CANDIDATE,AlgTitle);
	int tag=0;
    CDlgKeyHexFixedLen KeyDialog;
	KeyDialog.Init(Title,128,256,64);
	if( NewFileName == NULL )
	{
		int res;
		res = KeyDialog.DoModal();
		if (res == IDCANCEL)
			return;
		mode = (KeyDialog.ModeIsDecrypt()) ? DIR_DECRYPT : DIR_ENCRYPT;
			
		key = (unsigned char *) KeyDialog.GetKeyBytes();
		keylen = KeyDialog.GetKeyByteLength();

		for(i=0;i<keylen; i++) keybuffbin[i] = key[i];
				
		for(i=0; i<keylen; i++) 
			sprintf(keybuffhex+2*i,"%02.2X",keybuffbin[i]);
	}
	else
	{
		tag=1;
		keylen=16;
		strcpy(keybuffhex,NewFileKey);

	}
	borg = (unsigned char *) malloc(datalen+32);
	bcip = (unsigned char *) malloc(datalen+64);
	
	fi = fopen(infile,"rb");
	fread(borg,1,datalen,fi);
	fclose(fi);
	
	if (tag==0)
	{
		if(mode == DIR_DECRYPT)	{	   // Entschlüsselung ausgewählt
				        // padden der Eingabe
			for(; datalen %16; datalen++) borg[datalen]=0;
		}
		else {
			borg[datalen++]=1;
			for(; datalen %16; datalen++) borg[datalen]=0;
		}
	}
	else
	{
		if (Enc_Or_Dec)
		{
			// Verschlüsselung ausgewählt
			mode = DIR_ENCRYPT;        // padden der Eingabe
			borg[datalen++]=1;
			for(; datalen %16; datalen++) borg[datalen]=0;
			
		}
		else
		{
			// Entschlüsselung ausgewählt
			mode = DIR_DECRYPT;        // padden der Eingabe
			for(; datalen %16; datalen++) borg[datalen]=0;

		}
	}
	datalen <<= 3;                 // Länge in Bits

	if ( NewFileName == NULL )
	{
		GetTmpName(outfile,"cry",".tmp");
	}
	else
	{
		strcpy( outfile, NewFileName );
	}
	
	doaescrypt(AlgId,mode,keylen,keybuffhex,borg,datalen,bcip);
	
	free(borg);
	datalen >>= 3;                 // Länge wieder in Byte
	
    if( tag==0 && mode == DIR_DECRYPT)
	{	                           // Entschlüsselung ausgewählt
		// Padding entfernen
		for(datalen--; 0 == bcip[datalen]; datalen--);
	}
	if( tag==1 && !Enc_Or_Dec)
	{	                           // Entschlüsselung ausgewählt
		// Padding entfernen
		for(datalen--; 0 == bcip[datalen]; datalen--);
	}
	fi = fopen(outfile,"wb");
	fwrite(bcip, 1, datalen, fi);
        free (bcip);
	fclose(fi);

	if ( NewFileName == NULL )
	{	
		OpenNewDoc( outfile, KeyDialog.GetKeyFormatted(), OldTitle, AlgResIds[AlgId], mode == DIR_DECRYPT );
	}
	else if (tag==1 && !Enc_Or_Dec)//Entschlüsselung + Hybrid
	{
		//titleID = IDS_STRING_HYBRID_TITLE;
		//OpenNewDoc( outfile, (CString) keybuffhex, OldTitle, titleID, 1 );
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		
		
		if(NewDoc)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HYBRID_DEC_TITLE,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName(title,sizeof(title),pc_str,OldTitle);
			NewDoc->SetTitle(title);
		}
		HIDE_HOUR_GLASS		
	}
}


/* AESBrute() führt eine Schlüsselraumsuche für die AES Verfahren aus.
	in (CryptPar *)p sind alle nötigen Daten (AlgId siehe AESCrypt())
	enthalten. */
UINT AESBrute(PVOID p)
{
	int windowlen = theApp.Options.m_BFEntropyWindow;
    char outfile[CRYPTOOL_PATH_LENGTH], line[256], AlgTitel[128];
    char mode, *keyhex, kfound[65];
	unsigned char *borg, *bcip;
	int i,pos, AlgId, cntr, keylen, datalen;
	int distr[256];
	double entr, emax, f;
	FILE *fi;
	CryptPar *par = (CryptPar *) p;
	int titleID;
	double *xlogx = new double[windowlen + 1];
	if (!xlogx) return 0;
	xlogx[0] = 0.0;
	for (i = 1; i <= windowlen; i++) 
		xlogx[i] = (f = i) * log(f);
	mode = DIR_DECRYPT;

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS
	
	fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	datalen = ftell(fi);
	fclose(fi);
	
	if(datalen < 1) 
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		return 0;
	}
	borg = (unsigned char *) malloc(datalen+32);
	bcip = (unsigned char *) malloc(datalen+64);
	
	if(datalen > windowlen)     // nur die ersten windowlen Zeichen anschauen
		datalen=windowlen;
	
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
	
	CDlgBruteForceAES KeyDialog;

	if(KeyDialog.Display(AlgTitel,par->keylenmin,par->keylenmax,par->keylenstep)!=IDOK)
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		return 0;
	}
	
	if(par->flags & CRYPT_DO_PROGRESS)
	{
		CString title;
		title.Format(IDS_STRING_ANALYSE_ON,AlgTitel);
		CString message;
		message.Format(IDS_STRING_MSG_SEARCHING_COMPLETE,KeyDialog.GetSearchBitLen());
		theApp.fs.setModelTitleFormat(&KeyDialog,title,message);
		theApp.fs.Display();
	}
		
	emax = 0.0;                      // max Entropie 
	
	keylen = KeyDialog.GetBinlen();
	keyhex=KeyDialog.GetData();
	strcpy(kfound,keyhex);
	
    GetTmpName(outfile,"cry",".tmp");

	pos=0;
	theApp.fs.startClock();
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
		}
		
		doaescrypt(AlgId,mode,keylen/8,keyhex,borg,datalen,bcip);
		
		// Entropie berechnen
		memset(distr,0,sizeof(distr));
		for(i=0;i<windowlen;i++)
			distr[(unsigned int) bcip[i]]++;
		entr = 0.0;
		for(i = 0; i<256; i++)
			entr += xlogx[distr[i]];
		if(entr > emax)
		{
			emax = entr;
			strcpy(kfound,keyhex);
		}
	}
	
	CDlgKeyHexAnalysis dia;
	
	if(IDCANCEL == dia.Display(kfound))
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		if(par->flags & CRYPT_DO_PROGRESS)
			theApp.fs.cancel();
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return 0;
	}
	
	if(par->flags & CRYPT_DO_PROGRESS)
		theApp.fs.cancel();

	dia.GetHexData(kfound,sizeof(kfound));

	fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	datalen = ftell(fi);
	fseek(fi,0,SEEK_SET);
	fread(borg,1,datalen,fi);
	fclose(fi);
	
	for(; datalen %16; datalen++)    // padden
		borg[datalen]=0;            
	datalen <<= 3;
	
	doaescrypt(AlgId,mode,keylen/8,kfound,borg,datalen,bcip);
	free(borg);
	
	datalen >>= 3;
	
	for(datalen--; 0 == bcip[datalen]; datalen--);
	
	fi = fopen(outfile,"wb");        // Ergebnis ausgeben
	fwrite(bcip, 1, datalen, fi);
	free(bcip);
	fclose(fi);
	
	LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName3(line,sizeof(line),pc_str, AlgTitel, par->OldTitle, dia.m_einstr.GetBuffer(1));
    theApp.ThreadOpenDocumentFileNoMRU(outfile,line,dia.m_einstr.GetBuffer(1));
	
	par->flags |= CRYPT_DONE;
	FreePar(par);
	
	return 0;
}
