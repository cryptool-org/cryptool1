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
#pragma once

#include "stdafx.h"
#include "SymEncBase.h"

int sym_encrypt_secude(int crypt_id, 
			char *key_hex, int key_bitlength, 
			char *in,  int in_bytelength,  
			char *out, int &out_bytelength);
int sym_decrypt_secude(int crypt_id,
			char *key_hex, int key_bitlength, 
			char *in, int in_bytelength, 
			char *out, int &out_bytelength);

class sym_brute_secude : public sym_brute {
	char			key[256];
	Key				key_value;
	KeyInfo			key_info;
	BitString         input;
	OctetString       output;

public:
	sym_brute_secude(int crypt_id, int key_bitlength, 
		char *cipher, int cipher_bytelength);
	~sym_brute_secude();
	char *decrypt(char *key_hex);
};

void hash (char* infile, const char *OldTitle, int AlgId);



