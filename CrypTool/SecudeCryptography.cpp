/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/


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
#include "SecudeCryptography.h"

#include "HashingOperations.h"

inline int convert(char c)
{
	if(('0' <= c) && (c <= '9')) return c-'0';
	if(('A' <= c) && (c <= 'F')) return c+10-'A';
	if(('a' <= c) && (c <= 'f')) return c+10-'a';
	if(c==0) return 0;	// for ease of conversion
	return -1;
}

int  select_algorithm( int crypt_id, KeyInfo &key_info )
{

	switch (crypt_id) {
	case IDS_CRYPT_DES_ECB:  
		key_info.subjectAI=theApp.SecudeLib.desECB_aid; 			  
		break;
	case IDS_CRYPT_DES_CBC:  
		key_info.subjectAI=theApp.SecudeLib.desCBC_pad_aid;    
		break;
	case IDS_CRYPT_TRIPLE_DES_CBC: 
		key_info.subjectAI=theApp.SecudeLib.desCBC3_aid;  
		break;
	case IDS_CRYPT_TRIPLE_DES_ECB: 
		key_info.subjectAI=theApp.SecudeLib.desEDE_aid;   
		break;
	case IDS_CRYPT_RC2:      
		key_info.subjectAI=theApp.SecudeLib.rc2CBC_aid;      
		break;
	case IDS_CRYPT_RC4:      
		key_info.subjectAI=theApp.SecudeLib.rc4_aid;      
		break;
	case IDS_CRYPT_IDEA:     
		key_info.subjectAI=theApp.SecudeLib.idea_aid;  
		break;
	default:       
		ASSERT(0);
	}
	return 0;
}

void init_key( char *key_hex, char *key, int key_bitlength,
			 Key &key_value, KeyInfo &key_info )
{
	// convert key_hex to key
    for (int i=0; i<key_bitlength>>2; i++)
	{
		if ( !(i%2) ) key[i/2]  = convert(key_hex[i])<<4;
		else          key[i/2] += convert(key_hex[i]);
	}

	key_info.subjectkey.bits=(char *)key;  // keybuffer
	key_info.subjectkey.nbits= key_bitlength;

	key_value.key=&key_info;
	key_value.pse_sel=NULL;
	key_value.alg=NULL;
	key_value.add_object=NULL;
	key_value.add_object_type=NULL;
	key_value.key_size=NULL;
	key_value.private_key=NULL;
}

int sym_encrypt_secude(int crypt_id, 
			char *key_hex, int key_bitlength, 
			char *in,  int in_bytelength,  
			char *out, int &out_bytelength)
{
	char	key[256];
	Key		key_value;
	KeyInfo key_info;

	int error = select_algorithm( crypt_id, key_info );
	if (error < 0)
		return error;

	init_key(key_hex, key, key_bitlength, key_value, key_info);

	OctetString     input;
	BitString       output;
	input.octets  = in;
	input.noctets = in_bytelength;
	output.bits   = out;
	output.nbits  = 0;

	error = theApp.SecudeLib.sec_encrypt_all (&input, &output, &key_value);
	out_bytelength = output.nbits >> 3;
	return error;
}

int sym_decrypt_secude(int crypt_id,
			char *key_hex, int key_bitlength, 
			char *in, int in_bytelength, 
			char *out, int &out_bytelength)
{
	char	key[256];
	Key		key_value;
	KeyInfo key_info;

	int error = select_algorithm( crypt_id, key_info );
	if (error < 0)
		return error;
	init_key(key_hex, key, key_bitlength, key_value, key_info);

	BitString         input;
	OctetString       output;
	input.bits      = in;
	input.nbits     = in_bytelength << 3;
	output.octets   = out;
	output.noctets  = 0;

	error = theApp.SecudeLib.sec_decrypt_all (&input, &output, &key_value);
	out_bytelength = output.noctets;
	return error;
}

/////////////////////////////////////////////////////////////////
//

#define __KEY_NULL "0000000000000000000000000000000000000000000000000000000000000000"

sym_brute_secude::sym_brute_secude(int crypt_id, int key_bitlength, 
		char *cipher, int cipher_bytelength)
{
	int error = select_algorithm( crypt_id, key_info );
	if ( 0 > error )
	{
		// FIXME
	}
	init_key(__KEY_NULL, key, key_bitlength, key_value, key_info);
	input.bits = (char *) malloc(cipher_bytelength+16);
	memcpy(input.bits, cipher, cipher_bytelength);
	input.nbits = cipher_bytelength << 3;

	output.octets = (char *) malloc(cipher_bytelength+32);
	output.noctets = 0;
}

sym_brute_secude::~sym_brute_secude()
{
	free (output.octets);
	free (input.bits);
}

char * sym_brute_secude::decrypt(char *key_hex)
{
	output.noctets = 0;
    for (int i=0; i<(int)key_info.subjectkey.nbits<<2; i++)
	{
		if ( !(i%2) ) key[i/2]  = convert(key_hex[i])<<4;
		else          key[i/2] += convert(key_hex[i]);
	}
	int error = theApp.SecudeLib.sec_decrypt_all (&input, &output, &key_value);

	if (error == -1)
	{
		struct ErrStack *err;
		err = theApp.SecudeLib.th_remove_last_error();
		if ( err->e_number == 1792 ) error = 0;
		else                         error = err->e_number;
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
				//	theApp.SecudeLib.aux_free_AlgId((AlgId **) &(err->e_addr));
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
	decrypted_bytes = output.noctets;
	return (char*)output.octets;
}

///////////////////////////////////////////////////////////////
//

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

	Für die folgenden Hashfunktionen wird die OpenSSL-Bibliothek 
	an Stelle der Secude-Bibliothek verwendet. Welche Funktion 
	verwendet wird, hängt von den übergebenen Parametern (AlgId) ab:
	7 steht für SHA-256
	8 steht für SHA-512
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
		
		case 7: // SHA-256
			aid = 0;
			AlgTitel = "SHA-256";
			break;
		case 8: // SHA-512
			aid = 0;
			AlgTitel = "SHA-512";
			break;
	}

	LoadString(AfxGetInstanceHandle(), IDS_PROGESS_COMPUTE_DIGEST, pc_str, STR_LAENGE_STRING_TABLE);
	char progressTitel[128];
	sprintf(progressTitel, pc_str, AlgTitel);
	theApp.fs.SetWindowText(progressTitel);

	// if the AlgorithmID (aid) is zero, we use OpenSSL functions for hashing
	if(aid == 0) {

		// SHA-256
		if(CString(AlgTitel) == "SHA-256") {
			char messageDigest[32+1];
			memset(messageDigest, 0, 32+1);
			FILE *in = fopen(infile,"rb");
			ASSERT(in);
			m_pos = 0;
			fseek(in,0,SEEK_END);
			m_size = ftell(in);
			fseek(in,0,SEEK_SET);
			size_t n;

			// create hashing operations object (index 6 = SHA-256)
			HashingOperations hashingOperations(6);
			// HASH INITIALIZE
			hashingOperations.chunkHashInit();
			while (!canceled() && (n = fread(buffer,1,sizeof(buffer),in))) {
				// HASH UPDATE
				hashingOperations.chunkHashUpdate(buffer, n);
				m_pos += n;
			}
			fclose(in);
			// HASH FINALIZE
			hashingOperations.chunkHashFinal(messageDigest);
			bool canceledbyuser = canceled();
			theApp.fs.cancel();

			// assign resulting message digest
			hashostr.noctets = 32;
			hashostr.octets = messageDigest;

			while ( theApp.fs.m_displayed )	Sleep(10);  // Wait until the progress window is destroyed: FIXME !!!

			CDlgShowHash HashDlg;
			HashDlg.SetHash( hashostr, OldTitle, AlgTitel );
			if ( !canceledbyuser && IDOK == HashDlg.DoModal() )
			{
				theApp.SecudeLib.aux_OctetString2file(&hashostr,outfile,2);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
				MakeNewName2(title,sizeof(title),pc_str,OldTitle,AlgTitel);
				theApp.ThreadOpenDocumentFileNoMRU(outfile,title);
			}
			// do not let the Secude lib free the local memory, since this will cause a crash
			// theApp.SecudeLib.aux_free(hashostr.octets);
			delete this;
		}
		// SHA-512
		if(CString(AlgTitel) == "SHA-512") {
			char messageDigest[64+1];
			memset(messageDigest, 0, 64+1);
			FILE *in = fopen(infile,"rb");
			ASSERT(in);
			m_pos = 0;
			fseek(in,0,SEEK_END);
			m_size = ftell(in);
			fseek(in,0,SEEK_SET);
			size_t n;

			// create hashing operations object (index 7 = SHA-512)
			HashingOperations hashingOperations(7);
			// HASH INITIALIZE
			hashingOperations.chunkHashInit();
			while (!canceled() && (n = fread(buffer,1,sizeof(buffer),in))) {
				// HASH UPDATE
				hashingOperations.chunkHashUpdate(buffer, n);
				m_pos += n;
			}
			fclose(in);
			// HASH FINALIZE
			hashingOperations.chunkHashFinal(messageDigest);
			bool canceledbyuser = canceled();
			theApp.fs.cancel();

			// assign resulting message digest
			hashostr.noctets = 64;
			hashostr.octets = messageDigest;

			while ( theApp.fs.m_displayed )	Sleep(10);  // Wait until the progress window is destroyed: FIXME !!!

			CDlgShowHash HashDlg;
			HashDlg.SetHash( hashostr, OldTitle, AlgTitel );
			if ( !canceledbyuser && IDOK == HashDlg.DoModal() )
			{
				theApp.SecudeLib.aux_OctetString2file(&hashostr,outfile,2);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
				MakeNewName2(title,sizeof(title),pc_str,OldTitle,AlgTitel);
				theApp.ThreadOpenDocumentFileNoMRU(outfile,title);
			}
			// do not let the Secude lib free the local memory, since this will cause a crash
			// theApp.SecudeLib.aux_free(hashostr.octets);
			delete this;
		}
	}
	// if the AlgorithmID (aid) is NOT zero, we stick to Secude for hashing
	else {
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
		theApp.fs.cancel();

		while ( theApp.fs.m_displayed )	Sleep(10);  // Wait until the progress window is destroyed: FIXME !!!

		CDlgShowHash HashDlg;
		HashDlg.SetHash( hashostr, OldTitle, AlgTitel );
		if ( !canceledbyuser && IDOK == HashDlg.DoModal() )
		{
			theApp.SecudeLib.aux_OctetString2file(&hashostr,outfile,2);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_HASH_VALUE_OF,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName2(title,sizeof(title),pc_str,OldTitle,AlgTitel);
			theApp.ThreadOpenDocumentFileNoMRU(outfile,title);
		}
		theApp.SecudeLib.aux_free(hashostr.octets);
		delete this;
	}
	return 0;
}

