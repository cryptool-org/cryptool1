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

#include "CoreCryptography.h"
#include "..\AES\mars\mars.h"
#include "..\AES\RC6\RC6.h"
#include "..\AES\Rijndael\Rijndael-api-fst.h"
#include "..\AES\Serpent\Serpent.h"
#include "..\AES\Twofish\Twofish.h"
#include "DESXL.h"
#include "resource.h"



void MARS(char mode, int key_bits, char *keybuffhex, 
		  unsigned char *borg, int datalen, unsigned char *bcip, char *IV);
void RC6 (char mode, int key_bits, char *keybuffhex, 
		  unsigned char *borg, int datalen, unsigned char *bcip, char *IV);
void RIJNDAEL(char mode, int key_bits, char *keybuffhex, 
			  unsigned char *borg, int datalen, unsigned char *bcip, char *IV);
void SERPENT(char mode, int key_bits, char *keybuffhex, 
			 unsigned char *borg, int datalen, unsigned char *bcip, char *IV);
void TWOFISH(char mode, int key_bits, char *keybuffhex, 
			 unsigned char *borg, int datalen, unsigned char *bcip, char *IV);
void DES_XL(int ID, char mode, int key_bits, char *keybuffhex, 
			unsigned char *borg, int datalen, unsigned char *bcip);


int sym_encrypt_core(int crypt_id, 
			char *key_hex, int key_bitlength, 
			char *in,  int in_bytelength,  
			char *out, int &out_bytelength)
{
	in[in_bytelength++] = 1;
	for (; in_bytelength % 16; in_bytelength++)
		in[in_bytelength] = 0;

	int bitlength = in_bytelength <<= 3;

	switch (crypt_id) {
	case IDS_CRYPT_MARS:     
		MARS(DIR_ENCRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_RC6:      
		RC6(DIR_ENCRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_RIJNDAEL: 
		RIJNDAEL(DIR_ENCRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_SERPENT:  
		SERPENT(DIR_ENCRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_TWOFISH:  
		TWOFISH(DIR_ENCRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);    
		break;
	case IDS_CRYPT_DESL:
	case IDS_CRYPT_DESX:
	case IDS_CRYPT_DESXL:     
		DES_XL(crypt_id, DIR_ENCRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out);
		break;
	default:       
		ASSERT(0);
	}

	out_bytelength = bitlength >> 3;

	return out_bytelength;
}


int sym_decrypt_core(int crypt_id,
			char *key_hex, int key_bitlength, 
			char *in, int in_bytelength, 
			char *out, int &out_bytelength)
{
	int error = 0;

	for (; in_bytelength % 16; in_bytelength++)
		in[in_bytelength] = 0;

	int bitlength = in_bytelength << 3;

	switch (crypt_id) {
	case IDS_CRYPT_MARS:     
		MARS(DIR_DECRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_RC6:      
		RC6(DIR_DECRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_RIJNDAEL: 
		RIJNDAEL(DIR_DECRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_SERPENT:  
		SERPENT(DIR_DECRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_TWOFISH:  
		TWOFISH(DIR_DECRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out, IV_NULL);    
		break;
	case IDS_CRYPT_DESL:
	case IDS_CRYPT_DESX:
	case IDS_CRYPT_DESXL:     
		DES_XL(crypt_id, DIR_DECRYPT, key_bitlength, key_hex, 
			(unsigned char *)in, bitlength, (unsigned char *)out);
		break;
	default:       
		ASSERT(0);
	}

	out_bytelength = bitlength >> 3;
	for ( out_bytelength--; 0 == out[out_bytelength]; out_bytelength-- ); // remove padding

	return out_bytelength;
}

/////////////////////////////////////////////////////////////////////
//
sym_brute_core::sym_brute_core(int crypt_id, int key_bitlength, 
					char *cipher, int cipher_bytelength)
{
	in_size = cipher_bytelength;
	id = crypt_id;
	key_bits = key_bitlength;
	in  = (char *) malloc(in_size+16);
	out = (char *) malloc(in_size+32);
	
	memcpy(in, cipher, in_size);
	for ( ; in_size%16; in_size++) // 0 padding
		in[in_size] = 0;
	in_size <<= 3;
}

sym_brute_core::~sym_brute_core()
{
	free (in);
	free (out);
}

char * sym_brute_core::decrypt(char *key_hex)
{
	decrypted_bytes = in_size;
	switch (id) {
	case IDS_CRYPT_MARS:     
		MARS(DIR_DECRYPT, key_bits, key_hex, 
			(unsigned char *)in, decrypted_bytes, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_RC6:      
		RC6(DIR_DECRYPT, key_bits, key_hex, 
			(unsigned char *)in, decrypted_bytes, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_RIJNDAEL: 
		RIJNDAEL(DIR_DECRYPT, key_bits, key_hex, 
			(unsigned char *)in, decrypted_bytes, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_SERPENT:  
		SERPENT(DIR_DECRYPT, key_bits, key_hex, 
			(unsigned char *)in, decrypted_bytes, (unsigned char *)out, IV_NULL);
		break;
	case IDS_CRYPT_TWOFISH:  
		TWOFISH(DIR_DECRYPT, key_bits, key_hex, 
			(unsigned char *)in, decrypted_bytes, (unsigned char *)out, IV_NULL);    
		break;
	case IDS_CRYPT_DESL:
	case IDS_CRYPT_DESX:
	case IDS_CRYPT_DESXL:     
		DES_XL(id, DIR_DECRYPT, key_bits, key_hex, 
			(unsigned char *)in, decrypted_bytes, (unsigned char *)out);
		break;
	default:       
		ASSERT(0);
	}

	decrypted_bytes >>= 3;
	return out;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////
//

void MARS(char mode, int key_bits, char *keybuffhex, unsigned char *borg, int datalen, unsigned char *bcip, char *IV)
{
	keyInstanceMars keyin;
	cipherInstanceMars cipher;
	makeKeyMars(&keyin,mode,key_bits,keybuffhex);
	cipherInitMars(&cipher,MODE_CBC,IV);
	if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
		blockDecryptMars(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
	else
		blockEncryptMars(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
}

void RC6 (char mode, int key_bits, char *keybuffhex, unsigned char *borg, int datalen, unsigned char *bcip, char *IV)
{
	keyInstanceRC6 keyin;
	cipherInstanceRC6 cipher;
	makeKeyRC6(&keyin,mode,key_bits,keybuffhex);
	cipherInitRC6(&cipher,MODE_CBC,IV);
	if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
		blockDecryptRC6(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
	else
		blockEncryptRC6(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
}

void RIJNDAEL(char mode, int key_bits, char *keybuffhex, unsigned char *borg, int datalen, unsigned char *bcip, char *IV)
{
	keyInstanceRijndael keyin;
	cipherInstanceRijndael cipher;
	makeKeyRijndael(&keyin,mode,key_bits,keybuffhex);
	cipherInitRijndael(&cipher,MODE_CBC,IV);
	if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
		blockDecryptRijndael(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
	else
		blockEncryptRijndael(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
}

void SERPENT(char mode, int key_bits, char *keybuffhex, unsigned char *borg, int datalen, unsigned char *bcip, char *IV)
{
	keyInstanceSerpent keyin;
	cipherInstanceSerpent cipher;
	makeKeySerpent(&keyin,mode,key_bits,keybuffhex);
	cipherInitSerpent(&cipher,MODE_CBC,IV);
	if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
		blockDecryptSerpent(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
	else
		blockEncryptSerpent(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
}

void TWOFISH(char mode, int key_bits, char *keybuffhex, unsigned char *borg, int datalen, unsigned char *bcip, char *IV)
{
	keyInstanceTwofish keyin;
	cipherInstanceTwofish cipher;
	makeKeyTwofish(&keyin,mode,key_bits,keybuffhex);
	cipherInitTwofish(&cipher,MODE_CBC,IV);
	if(mode==DIR_DECRYPT)		// Entschlüsselung ausgewählt
		blockDecryptTwofish(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
	else
		blockEncryptTwofish(&cipher, &keyin, (BYTE *)borg,datalen, bcip);
}

void DES_XL(int ID, char mode, int key_bits, char *keybuffhex, unsigned char *borg, 
			int datalen, unsigned char *bcip)
{
	char desxl_variant;
	DESXL desxlInstance;

	switch (ID){
	case IDS_CRYPT_DESL: desxl_variant = VAR_DESL;
		break;
	case IDS_CRYPT_DESX: desxl_variant = VAR_DESX;
		break;
	case IDS_CRYPT_DESXL: desxl_variant = VAR_DESXL;
		break;
	default:
		ASSERT(0);
	};


	desxlInstance.createKey(keybuffhex,key_bits,desxl_variant);
	if(mode==DIR_DECRYPT)
		desxlInstance.decrypt((BYTE *)borg,datalen,bcip,desxl_variant);
	else
		desxlInstance.encrypt((BYTE *)borg,datalen,bcip,desxl_variant);
}


