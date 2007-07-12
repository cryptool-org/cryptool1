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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Diese Quellcode-Datei enth�lt die Funktionen zur symmetrischen
// Ver- und Entschl�sselung.
// 
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "DlgKeyHexFixedLen.h"
// #include "..\AES\mars\mars.h"
// #include "..\AES\RC6\RC6.h"
// #include "..\AES\Rijndael\Rijndael-api-fst.h"
// #include "..\AES\Serpent\Serpent.h"
// #include "..\AES\Twofish\Twofish.h"
#include "AppDocument.h"
#include "DlgKeyHexAnalysis.h"
#include "DlgBruteForceAES.h"   // Dialogbox f�r die Schl�sselsuche

#include "DialogeMessage.h"
#include "CrypToolTools.h"
#include "Cryptography.h"
#include "MakeNewName.h"

// #include "DESXL.h"
#include "bruteforceheap.h"

void FreePar(CryptPar *par);

#if 0
void doaescrypt(int AlgId,char mode,int keylen,char *keybuffhex,unsigned char *borg,int datalen,
				unsigned char *bcip);


/*  Die Funktion doaescrypt f�hrt die eigentliche 
	(symmetrische) Verschl�sselung aus. 
	�ber die Parameter, die doaescrypt von der 
	aufrufenden Funktion bekommt wird so die 
	Funktion sec_encrypt_all bzw. sec_decrypt_all
	angesteuert. (je nach mode)
	keybufhex enth�lt den Schl�ssel, L�nge keylen,
	borg den Orginaltext, L�nge datalen, und in bcip
	wird der ciphertext gespeichert. 
	Der Parameter AlgId gibt an, mit welchem Algorithmus
	die Daten ver-/entschl�sselt werden sollen: */
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
			if(mode==DIR_DECRYPT)		// Entschl�sselung ausgew�hlt
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
			if(mode==DIR_DECRYPT)		// Entschl�sselung ausgew�hlt
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
			if(mode==DIR_DECRYPT)		// Entschl�sselung ausgew�hlt
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
			if(mode==DIR_DECRYPT)		// Entschl�sselung ausgew�hlt
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
			if(mode==DIR_DECRYPT)		// Entschl�sselung ausgew�hlt
				blockDecryptTwofish(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			else
				blockEncryptTwofish(&cipher, &keyin, 
				(BYTE *)borg,datalen, bcip);
			break;
		}
	case 6://DESL
		{
			DESXL desxlInstance;
			desxlInstance.createKey(keybuffhex,keylen*8,VAR_DESL);
			if(mode==DIR_DECRYPT)
				desxlInstance.decrypt((BYTE *)borg,datalen,bcip,VAR_DESL);
			else
				desxlInstance.encrypt((BYTE *)borg,datalen,bcip,VAR_DESL);
			break;
		}
	case 7://DESX
		{
			DESXL desxlInstance;
			desxlInstance.createKey(keybuffhex,keylen*8,VAR_DESX);
			if(mode==DIR_DECRYPT)
				desxlInstance.decrypt((BYTE *)borg,datalen,bcip,VAR_DESX);
			else
				desxlInstance.encrypt((BYTE *)borg,datalen,bcip,VAR_DESX);
			break;
		}
	case 8://DESXL
		{
			DESXL desxlInstance;
			desxlInstance.createKey(keybuffhex,keylen*8,VAR_DESXL);
			if(mode==DIR_DECRYPT)
				desxlInstance.decrypt((BYTE *)borg,datalen,bcip,VAR_DESXL);
			else
				desxlInstance.encrypt((BYTE *)borg,datalen,bcip,VAR_DESXL);
			break;
		}
	}
}
#endif

/*  Die Funktion AESCrypt f�hrt die eigentliche 
	(symmetrische) Verschl�sselung aus. 
	Der Parameter AlgId gibt an, mit welchem Algorithmus
	die Daten ver-/entschl�sselt werden sollen:
	1 steht f�r Mars
	2 steht f�r RC6
	3 steht f�r Rijndael
	4 steht f�r Serpent
	5 steht f�r Twofish 
	6 steht f�r DESL
	7 steht f�r DESX
	8 steht f�r DESXL*/
void AESCrypt (const char* infile, const char *OldTitle, int AlgId, bool Enc_Or_Dec, const char * NewFileName, const char* NewFileKey)
{
	
#if 0
	char outfile[CRYPTOOL_PATH_LENGTH], keybuffhex[256/4+1],title[200];
	CString AlgTitle,Title;
	unsigned char keybuffbin[256/8];
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
		IDS_CRYPT_TWOFISH,
		IDS_CRYPT_DESL,
		IDS_CRYPT_DESX,
		IDS_CRYPT_DESXL
	};
	ASSERT(AlgId < sizeof(AlgResIds)/sizeof(UINT));
	AlgTitle.LoadString(AlgResIds[AlgId]);
	if ( 3 == AlgId )
		Title.LoadString(IDS_STRING_KEYINPUT_AES_RIJNDAEL);
	else if ((6 == AlgId)||(7 == AlgId)||(8 == AlgId))
        Title.Format(IDS_STRING_KEYINPUT_SYMMETRIC,AlgTitle);
	else
		Title.Format(IDS_STRING_KEYINPUT_AES_CANDIDATE,AlgTitle);
	int tag=0;
    CDlgKeyHexFixedLen KeyDialog;
	if ((7 == AlgId)||(8 == AlgId))
		KeyDialog.Init(Title,192,192,192);
	else if ((6 == AlgId))
		KeyDialog.Init(Title,64,64,64);
	else
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

		ASSERT(keylen <= sizeof keybuffbin);
		for(i=0;i<keylen; i++) keybuffbin[i] = key[i];
		
		ASSERT(2*keylen + 1 <= sizeof keybuffhex);
		for(i=0; i<keylen; i++) 
			sprintf(keybuffhex+2*i,"%02.2X",keybuffbin[i]);
	}
	else
	{
		tag=1;
		keylen=16;
	// nur niederwertigsten 128 Bit (16 Byte = 32 Hex-Halb-Bytes) betrachten
		int len = strlen(NewFileKey);
		ASSERT(len >= keylen*2);
		ASSERT(2*keylen + 1 <= sizeof keybuffhex);
		strcpy(keybuffhex,NewFileKey + len - keylen*2);
	}

	borg = (unsigned char *) malloc(datalen+32);
	bcip = (unsigned char *) malloc(datalen+64);
	
	fi = fopen(infile,"rb");
	fread(borg,1,datalen,fi);
	fclose(fi);
	
	if (tag==0)
	{
		if(mode == DIR_DECRYPT)	{	   // Entschl�sselung ausgew�hlt
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
			// Verschl�sselung ausgew�hlt
			mode = DIR_ENCRYPT;        // padden der Eingabe
			borg[datalen++]=1;
			for(; datalen %16; datalen++) borg[datalen]=0;
			
		}
		else
		{
			// Entschl�sselung ausgew�hlt
			mode = DIR_DECRYPT;        // padden der Eingabe
			for(; datalen %16; datalen++) borg[datalen]=0;

		}
	}
	datalen <<= 3;                 // L�nge in Bits

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
	datalen >>= 3;                 // L�nge wieder in Byte
	
    if( tag==0 && mode == DIR_DECRYPT)
	{	                           // Entschl�sselung ausgew�hlt
		// Padding entfernen
		for(datalen--; 0 == bcip[datalen]; datalen--); // FIXME: ensure datalen >= 0
	}
	if( tag==1 && !Enc_Or_Dec)
	{	                           // Entschl�sselung ausgew�hlt
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
	else if (tag==1 && !Enc_Or_Dec)//Entschl�sselung + Hybrid
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

#endif
}


/* AESBrute() f�hrt eine Schl�sselraumsuche f�r die AES Verfahren aus.
	in (CryptPar *)p sind alle n�tigen Daten (AlgId siehe AESCrypt())
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
	// mode = DIR_DECRYPT;

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
	case 6:                        // DESL
		titleID = IDS_CRYPT_DESL;
		break;
	case 7:                        // DESX
		titleID = IDS_CRYPT_DESX;
		break;
	case 8:                        // DESXL
		titleID = IDS_CRYPT_DESXL;
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
	
	CString title;
	title.Format(IDS_STRING_ANALYSE_ON,AlgTitel);
	if(par->flags & CRYPT_DO_PROGRESS)
	{
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
	while (cntr=KeyDialog.Step())    // n�chsten Schl�ssel setzen
	{                                // und Fortschritt erhalten
		keyhex=KeyDialog.GetData();  // Schl�ssel holen
		
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
		
//		doaescrypt(AlgId,mode,keylen/8,keyhex,borg,datalen,bcip);
		
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
	
	if(IDCANCEL == dia.Display((LPCTSTR)title,kfound))
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
	
//	doaescrypt(AlgId,mode,keylen/8,kfound,borg,datalen,bcip);
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

#if 0

/*  SymEncBrute() f�hrt eine Schl�sselraumsuche f�r die AES Verfahren aus.
	in (CryptPar *)p sind alle n�tigen Daten (AlgId siehe AESCrypt())
	enthalten. */
UINT BruteSymmetricEncryption(PVOID p)
{
	int windowlen = theApp.Options.m_BFEntropyWindow;
    char outfile[CRYPTOOL_PATH_LENGTH], line[256];
	CString AlgTitel;
    char mode, *keyhex, kfound[65];
	unsigned char *borg, *bcip;
	int i,pos, cntr, keylen, datalen;
	cryptProviderID providerID;
	symmetricEncAlg AlgID;
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
	
	AlgId = (symmetricEncAlg)(*((int *) par->key));  // Namen setzen

// Set name, select decryption provider
	strcpy(AlgTitel,"");           // Name setzen
	switch (AlgId)
	{
	case DES_ECB:                       
		titleID = IDS_CRYPT_DES_ECB;
		parity_check = 1;
		providerID = SECUDE;
		break;
	case DES_CBC:                       
		titleID = IDS_CRYPT_DES_CBC;
		parity_check = 1;
		providerID = SECUDE;
		break;
	case TDES_CBC:                       
		titleID = IDS_CRYPT_TRIPLE_DES_CBC;
		parity_check = 1;
		providerID = SECUDE;
		break;
	case TDES_ECB:                       
		titleID = IDS_CRYPT_TRIPLE_DES_ECB;
		parity_check = 1;
		providerID = SECUDE;
		break;
	case RC2:                        
		titleID = IDS_CRYPT_RC2;
		providerID = SECUDE;
		break;
	case RC4:                       
		titleID = IDS_CRYPT_RC4;
		providerID = SECUDE;
		break;
	case IDEA:                       
		titleID = IDS_CRYPT_IDEA;
		providerID = SECUDE;
		break;
	case MARS:                        
		titleID = IDS_CRYPT_MARS;
		providerID = CRYPTOOL;
		break;
	case RC6:                       
		titleID = IDS_CRYPT_RC6;
		providerID = CRYPTOOL;
		break;
	case RIJNDAEL:                       
		titleID = IDS_CRYPT_RIJNDAEL;
		providerID = CRYPTOOL;
		break;
	case SERPENT:                        
		titleID = IDS_CRYPT_SERPENT;
		providerID = CRYPTOOL;
		break;
	case TWOFISH:                       
		titleID = IDS_CRYPT_TWOFISH;
		providerID = CRYPTOOL;
		break;
	case DESL:                       
		titleID = IDS_CRYPT_DESL;
		providerID = CRYPTOOL;
		parity_check = 1;
		break;
	case DESX:                      
		titleID = IDS_CRYPT_DESX;
		providerID = CRYPTOOL;
		parity_check = 1;
		break;
	case DESXL:                       
		titleID = IDS_CRYPT_DESXL;
		providerID = CRYPTOOL;
		parity_check = 1;
		break;
	}
	LoadString(AfxGetInstanceHandle(),titleID,pc_str,STR_LAENGE_STRING_TABLE);
	strcpy( AlgTitel, pc_str );

	// load ciphertext 
	fi = fopen(par->infile,"rb");
	int inputSize = fread(borg,1,datalen,fi);
	fclose(fi);

	// Get KeyPattern
	CDlgBruteForceAES KeyDialog;
	if(KeyDialog.Display(AlgTitel,par->keylenmin,par->keylenmax,par->keylenstep)!=IDOK)
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		return 0;
	}

	keylen = KeyDialog.GetBinlen();
	keyhex = KeyDialog.GetData();
	strcpy(kfound,keyhex);

	class symEncProviderBase *provider;
	// initiate encryption provider
	switch (providerID) {
		case SECUDE:
			{
				symEncProviderSecude *SecudeProvider;
				SecudeProvider = new symEncProviderSecude();
				provider = SecudeProvider;
				break;
			}
		case CRYPTOOL: 
			{
				for(; inputSize %16; inputSize++)
					borg[inputSize]=0;          // padden
				datalen <<= 3;
				symEncProviderCrypTool *CrypToolProvider;
				CrypToolProvider = new symEncProviderCrypTool();
				provider = CrypToolProvider;
				break;
			}
	}

	provider->setAlgorithmID(AlgID);
	provider->initBufferEncryption(borg, min(8*inputSize, 8*windowlen));
	
	CString title;
	title.Format(IDS_STRING_ANALYSE_ON,AlgTitel);
	if(par->flags & CRYPT_DO_PROGRESS)
	{
		CString message;
		message.Format(IDS_STRING_MSG_SEARCHING_COMPLETE,KeyDialog.GetSearchBitLen());
		theApp.fs.setModelTitleFormat(&KeyDialog,title,message);
		theApp.fs.Display();
	}
		

	CBruteForceHeap candidates;
	candidates.init( keybits/8, in.nbits/8+16, 5);

	emax = 0.0;                      // max Entropie 
	pos=0;
	char *outbuffer;
	int   outlength;
	theApp.fs.startClock();
	while (cntr=KeyDialog.Step(parity_check))    // n�chsten Schl�ssel setzen
	{                                // und Fortschritt erhalten
		
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
	
		KeyDialog.GetDataInt(keyval);
		keyhex=KeyDialog.GetData();

		switch (providerID) {
			case SECUDE:
				{
					provider->set_key(keyval, keylen/8);
					break;
				}
			case CRYPTOOL:
				{
					
					provider->set_key(keyhex, keylen/8);
					break;
				}
		}

		
		provider->decrypt();
		outbuffer = provider->getOutput(outlength);

		BOOL decryptionResult_invalid = FALSE;
		if ( theApp.Options.i_alphabetOptions )
		{
			for (int i=0; i<outlength; i++)
				if (!alphaSet[(int)outbuffer[i]])
				{
					decryptionResult_invalid = TRUE;
					break;
				}
		}

		if ( !decryptionError && !decryptionResult_invalid ) 
		{
			// Entropie berechnen
			memset(distr,0,sizeof(distr));
			for(i=0;i<windowlen;i++)
				distr[(unsigned int) outbuffer[i]]++;
			entr = 0.0;
			for(i = 0; i<256; i++)
				entr += xlogx[distr[i]];

			if ( candidates.check_add( entr ) )
				candidates.add_candidate( entr, key, out.octets);

			if(entr > emax)
			{
				emax = entr;
				strcpy(kfound,keyhex);
			}
		}
	}
	
	candidates.sort();



	CDlgKeyHexAnalysis dia;
	
	if(IDCANCEL == dia.Display((LPCTSTR)title,kfound))
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

	GetTmpName(outfile,"cry",".tmp");
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

#endif