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
#include "CrypToolApp.h"
#include "Cryptography.h"
#include "FileTools.h"
#include "CryptDoc.h"
#include "DlgKeyHexFixedLen.h"
#include "secure.h" // Include-File von SECUDE
#include "pkcs.h"   // Include-File von SECUDE
#include "AppDocument.h"
#include "DlgShowHash.h"
#include "DialogeMessage.h"

/*  Die Funktion Crypt führt die eigentliche 
	(symmetrische) Verschlüsselung aus. 
	Über die Parameter, die Crypt von der 
	aufrufenden Funktion bekommt wird so die 
	Funktion sec_encrypt_all bzw. sec_decrypt_all
	angesteuert.
	Der Parameter alg gibt an, mit welchem Algorithmus
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
void Crypt (char* infile, const char *OldTitle, int keylenmin, int keylenmax, int keylenstep, int AlgId)
{
	
    char outfile[CRYPTOOL_PATH_LENGTH], title[128];
    CAppDocument *NewDoc;

	FILE *fi;
	int lenght;

	fi = fopen(infile,"rb");
	fseek(fi,0,SEEK_END);
	lenght = ftell(fi);
	fclose(fi);
	if(lenght < 1) {
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
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


	CString Title;
	Title.Format(IDS_STRING_KEYINPUT_SYMMETRIC,AlgTitel);
    CDlgKeyHexFixedLen KeyDialog;
	KeyDialog.Init(Title,keylenmin,keylenmax,keylenstep);
	if (KeyDialog.DoModal() != IDOK) 
		return;
	int keybytelen = KeyDialog.GetKeyByteLength();
	char *key = KeyDialog.GetKeyBytes();

    GetTmpName(outfile,"cry",".tmp");


	info.subjectkey.nbits = keybytelen * 8;
	info.subjectkey.bits = key;
	keyinfo.key=&info;
	keyinfo.pse_sel=NULL;
	keyinfo.alg=NULL;
	keyinfo.add_object=NULL;
	keyinfo.add_object_type=NULL;
	keyinfo.key_size=NULL;
	keyinfo.private_key=NULL;


    if(KeyDialog.ModeIsDecrypt()){		// Entschlüsselung ausgewählt
		  
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
			Message(IDS_STRING_DECRYPTION_ERROR,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			theApp.SecudeLib.aux_free_OctetString(&help);
			free(out.octets);
			return;}
		theApp.SecudeLib.aux_free_OctetString(&help);
		
		//Datenausgabe:
		theApp.SecudeLib.aux_OctetString2file(&out, outfile, 2);
		free(out.octets);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetKeyFormatted());
		remove(outfile);
		if(NewDoc) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,AlgTitel,OldTitle,KeyDialog.GetKeyFormatted());
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
			Message(IDS_STRING_ENCRYPTION_ERROR,MB_ICONSTOP, theApp.SecudeLib.LASTTEXT);
			return;}
		theApp.SecudeLib.aux_free_OctetString(&in);
		
		//Datenausgabe:
		OctetString *outOctet;
		outOctet = theApp.SecudeLib.aux_BString2OString(&out);
		free(out.bits);
		theApp.SecudeLib.aux_OctetString2file(outOctet,outfile,2);
		theApp.SecudeLib.aux_free_OctetString(&outOctet);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetKeyFormatted());
		remove(outfile);
		if(NewDoc) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
			MakeNewName3(title,sizeof(title),pc_str1,AlgTitel,OldTitle,KeyDialog.GetKeyFormatted());
			NewDoc->SetTitle(title);
		}
    }
}


class CHashRunnable : public CProgressRunnable 
{
public:
	CHashRunnable(char* infile, const char *OldTitle, int alg) {
		this->infile = infile;
		this->OldTitle = OldTitle;
		this->alg = alg;
		m_pos = 0;
		m_size = 0;
	}
	UINT run();
	double getProgress();
protected:
	CString infile;
	CString OldTitle;
	int alg;
	long m_pos;
	long m_size;
};

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

void hash (char* infile, const char *OldTitle, int alg)
{
	CHashRunnable *runnable = new CHashRunnable(infile,OldTitle,alg);
	runnable->startthread();
}

double CHashRunnable::getProgress()
{
	if (m_pos == 0 || m_size == 0)
		return 0.0;
	return double(m_pos)/double(m_size);
}
UINT CHashRunnable::run()
{
	char outfile[128], title[128];
	GetTmpName(outfile,"cry",".hex");
	
	char buffer[4096];
	OctetString bufferostr = { sizeof buffer, buffer };
	OctetString hashostr = { 0, 0 };
    
	char *AlgTitel;
	AlgId *aid;
	switch (alg){
		case 1://MD2
			aid = theApp.SecudeLib.md2_aid;
			AlgTitel="MD2";
			break;
		case 2://MD4
			aid = theApp.SecudeLib.md4_aid;
			AlgTitel="MD4";
			break;
		case 3://MD5
			aid = theApp.SecudeLib.md5_aid;
			AlgTitel="MD5";
			break;
		case 4://SHA
			aid = theApp.SecudeLib.sha_aid;
			AlgTitel="SHA";
			break;
		case 5://SHA_1
			aid = theApp.SecudeLib.sha1_aid;
			AlgTitel="SHA-1";
			break;
		case 6://RIPEMD160
			aid = theApp.SecudeLib.ripemd160_aid;
			AlgTitel="RIPEMD-160";
			break;
	}
	FILE *in = fopen(infile,"rb");
	ASSERT(in);
	m_pos = 0;
	fseek(in,0,SEEK_END);
	m_size = ftell(in);
	fseek(in,0,SEEK_SET);
	RC rc;
	void *context = NULL;
	rc = theApp.SecudeLib.sec_hash_init(&context,aid,NULL);
	ASSERT(rc == 0);
	size_t n;
	while (!canceled() && (n = fread(buffer,1,sizeof(buffer),in))) {
		bufferostr.noctets = n;
		rc = theApp.SecudeLib.sec_hash_more(&context,&bufferostr);
		ASSERT(rc == 0);
		m_pos += n;
	}
	fclose(in);
	rc = theApp.SecudeLib.sec_hash_end(&context,&hashostr);
	ASSERT(rc == 0);
	bool canceledbyuser = canceled();
	//theApp.fs.cancel();
	CDlgShowHash HashDlg;
	HashDlg.SetHash( hashostr, OldTitle, AlgTitel );
	if ( !canceledbyuser && IDOK == HashDlg.DoModal() )
	{
		theApp.SecudeLib.aux_OctetString2file(&hashostr,outfile,2);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(title,sizeof(title),pc_str,OldTitle,AlgTitel);
		theApp.ThreadOpenDocumentFileNoMRU(outfile,title);
#if 0
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		if(NewDoc) {
				LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
				MakeNewName2(title,sizeof(title),pc_str,OldTitle,AlgTitel);
				NewDoc->SetTitle(title);
			}
#endif
	}
	theApp.SecudeLib.aux_free(hashostr.octets);
	delete this;
	return 0;
}

