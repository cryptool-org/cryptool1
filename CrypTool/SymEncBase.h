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

#pragma once

#include "stdafx.h"

#define SYMENC_MAXKEYBYTELENGTH 256


enum cryptProvider {
	CORE_PROVIDER, SECUDE_PROVIDER
};

// Prototypes -- no stream
int sym_encrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			char *in,  int in_bytelength,  
			char *out, int &out_bytelength);
int sym_decrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			char *in, int in_bytelength, 
			char *out, int &out_bytelength);


int sym_encrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			const char *in_filename, char *out_filename);
int sym_decrypt(int crypt_id, cryptProvider provider,
			char *key_hex, int key_bitlength, 
			const char *in_filename, char *out_filename);

class sym_brute {
public:
	int decrypted_bytes;
	sym_brute() {}
	virtual ~sym_brute() {}
	virtual char *decrypt(char *key_hex) = 0;
};

class 
sym_brute *init_sym_brute(int crypt_id, cryptProvider provider,
						  int key_bitlength, char *cipher, int cipher_bytelength);