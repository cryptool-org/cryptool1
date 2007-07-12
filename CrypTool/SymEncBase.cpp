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
	throw ""; // FIXME
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
	throw ""; // FIXME
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

	// Get Filesize

	fi = fopen(in_filename,"rb");
	fseek(fi,0,SEEK_END);
	in_size = ftell(fi);
	fclose(fi);

 // additional space for padding
	out = (char*) malloc(in_size+64);
	in  = (char*) malloc(in_size+32);

	fi = fopen(in_filename,"rb");
	fread(in,1,in_size,fi);
	fclose(fi);


	int error = sym_encrypt(crypt_id, provider, key_hex, key_bitlength, in, in_size, out, out_size);
	if ( 0 > error )
	{
		// FIXME throw ...
	}
	else
	{
		fi = fopen(out_filename, "wb");
		fwrite(out, 1, out_size, fi);
		fclose(fi);
	}

	free(in);
	free(out);

	return error;
}

int sym_decrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			const char *in_filename, char *out_filename)
{
	FILE *fi;
	int in_size, out_size;
	char *in, *out;

	fi = fopen(in_filename,"rb");
	fseek(fi,0,SEEK_END);
	in_size = ftell(fi);
	fclose(fi);

	in  = (char*) malloc(in_size+32); // additional space for padding
	out = (char*) malloc(in_size+64);

	fi = fopen(in_filename,"rb");
	fread(in,1,in_size,fi);
	fclose(fi);

	int error = sym_decrypt(crypt_id, provider, key_hex, key_bitlength, in, in_size, out, out_size);
	if ( 0 > error )
	{
		// FIXME throw ...
	}
	else
	{
		fi = fopen(out_filename, "wb");
		fwrite(out, 1, out_size, fi);
		fclose(fi);
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