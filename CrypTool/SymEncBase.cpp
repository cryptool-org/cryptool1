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
#include "stdafx.h"
#include "CrypToolApp.h"
#include ".\symencbase.h"
#include "SecudeCryptography.h"
#include "CoreCryptography.h"
#include "secure.h" // Include-File von SECUDE


inline
int sym_encrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			char *in,  int in_bytelength,  
			char *out, int &out_bytelength)
{
	switch (provider) {
		case CORE_PROVIDER:
			return sym_encrypt_core( crypt_id, key_hex, key_bitlength, in, in_bytelength, out, out_bytelength);
			break;
		case SECUDE_PROVIDER:
			return sym_encrypt_secude( crypt_id, key_hex, key_bitlength, in, in_bytelength, out, out_bytelength);
			break;
	}
	CString errStr = _T("Internal error: function sym_encrypt, unknown cryptProvider");
	throw errStr; 
	return -1;
}

inline
int sym_decrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			char *in, int in_bytelength, 
			char *out, int &out_bytelength)
{
	switch (provider) {
		case CORE_PROVIDER:
			return sym_decrypt_core( crypt_id, key_hex, key_bitlength, in, in_bytelength, out, out_bytelength);
			break;
		case SECUDE_PROVIDER:
			return sym_decrypt_secude( crypt_id, key_hex, key_bitlength, in, in_bytelength, out, out_bytelength);
			break;
	}
	CString errStr = _T("Internal error: function sym_encrypt, unknown cryptProvider");
	throw errStr; 
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////
// File Encryption

int sym_encrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			const char *in_filename, char *out_filename)
{
	FILE *fi;
	int in_size, out_size;
	char *in, *out;
	int error = 0;
	CString internalErrorStr;


	// Get Filesize

	fi = fopen(in_filename,"rb");
	if ( fi != NULL )
	{
		fseek(fi,0,SEEK_END);
		in_size = ftell(fi);
		fclose(fi);
	}
	else
	{
		error = IDS_ERR_ON_OPEN_INFILE;
		internalErrorStr.FormatMessage(_T("Internal error: Function = sym_encrypt, section = Get Filesize, Filename = %1"), 
			in_filename);
	}

	if ( !error )
		if ( NULL == (in = (char*) malloc(in_size+32)) )
		{
			internalErrorStr = _T("Internal error: Function = sym_encrypt, section = allocate memory for in");
			error = IDS_ERR_ON_ALLOC_MEMORY;
		}
	if ( !error )
		if ( NULL == (out = (char*) malloc(in_size+64)) )
		{
			free (in);
			internalErrorStr = _T("Internal error: Function = sym_encrypt, section = allocate memory for out");
			error = IDS_ERR_ON_ALLOC_MEMORY;
		}

	if ( !error )
	{
		fi = fopen(in_filename,"rb");
		fread(in,1,in_size,fi);
		fclose(fi);


		int retVal = sym_encrypt(crypt_id, provider, key_hex, key_bitlength, in, in_size, out, out_size);
		if ( 0 > retVal )
		{
			error = IDS_ERR_ON_SYMCRYPT;
			internalErrorStr.FormatMessage(_T("Internal error: Function = sym_encrypt, section call sym_encrypt, provider %1!d!, %2!d!"), 
				(int)provider, crypt_id);
			free(in); free(out);
		}
		else
		{
			if ( NULL == (fi = fopen(out_filename, "wb")) )
			{
				error = IDS_ERR_ON_OPEN_OUTFILE;
				internalErrorStr.FormatMessage(_T("Internal error: Function = sym_encrypt, section = write output, Filename = %1"), 
					out_filename);
				free(in); free(out);
			}
			fwrite(out, 1, out_size, fi);
			fclose(fi);
		}
	}

	if ( error )
	{
		CString errStr;
		errStr.FormatMessage(error, (LPCSTR)internalErrorStr);
		throw errStr;
	}
	else
	{
		free(in);
		free(out);
	}
	return error;
}




int sym_decrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			const char *in_filename, char *out_filename)
{
	FILE *fi;
	int in_size, out_size;
	char *in, *out;

	int error = 0;
	CString internalErrorStr;

	// Get Filesize

	fi = fopen(in_filename,"rb");
	if ( fi != NULL )
	{
		fseek(fi,0,SEEK_END);
		in_size = ftell(fi);
		fclose(fi);
	}
	else
	{
		error = IDS_ERR_ON_OPEN_INFILE;
		internalErrorStr.FormatMessage(_T("Internal error: Function = sym_decrypt, section = Get Filesize, Filename = %1"), 
			in_filename);
	}

	if ( !error )
		if ( NULL == (in = (char*) malloc(in_size+32)) )
		{
			internalErrorStr = _T("Internal error: Function = sym_decrypt, section = allocate memory for in");
			error = IDS_ERR_ON_ALLOC_MEMORY;
		}
	if ( !error )
		if ( NULL == (out = (char*) malloc(in_size+64)) )
		{
			free (in);
			internalErrorStr = _T("Internal error: Function = sym_decrypt, section = allocate memory for out");
			error = IDS_ERR_ON_ALLOC_MEMORY;
		}

	if ( !error )
	{
		fi = fopen(in_filename,"rb");
		fread(in,1,in_size,fi);
		fclose(fi);


		int retVal = sym_decrypt(crypt_id, provider, key_hex, key_bitlength, in, in_size, out, out_size);
		if ( 0 > retVal )
		{
			error = IDS_ERR_ON_SYMCRYPT;
			internalErrorStr.FormatMessage(_T("Internal error: Function = sym_decrypt, section call sym_encrypt, provider = %1!d!, algID = %2!d!"), 
				(int)provider, crypt_id);
			free(in); free(out);
		}
		else
		{
			if ( NULL == (fi = fopen(out_filename, "wb")) )
			{
				error = IDS_ERR_ON_OPEN_OUTFILE;
				internalErrorStr.FormatMessage(_T("Internal error: Function = sym_decrypt, section = write output, Filename = %1"), 
					out_filename);
				free(in); free(out);
			}
			fwrite(out, 1, out_size, fi);
			fclose(fi);
		}
	}

	if ( error )
	{
		CString errStr;
		errStr.FormatMessage(error, (LPCSTR)internalErrorStr);
		throw errStr;
	}
	else
	{
		free(in);
		free(out);
	}
	return error;
}

/////////////////////////////////////////////////////////////////
//


		
class 
sym_brute *init_sym_brute(int crypt_id, cryptProvider provider, 
										int key_bitlength, char *cipher, int cipher_bytelength)
{
	switch (provider) {
		case CORE_PROVIDER:
		{
			sym_brute_core *obj_sym_brute;
			obj_sym_brute = new sym_brute_core(crypt_id, key_bitlength, 
									cipher, cipher_bytelength);
			return (sym_brute*)obj_sym_brute;
		}
			break;
		case SECUDE_PROVIDER:
		{
			sym_brute_secude *obj_sym_brute;
			obj_sym_brute = new sym_brute_secude(crypt_id, key_bitlength, 
									cipher, cipher_bytelength);
			return (sym_brute*)obj_sym_brute;
		}
			break;
	}
	return NULL;
}