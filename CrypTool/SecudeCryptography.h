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



