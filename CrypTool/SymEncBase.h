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