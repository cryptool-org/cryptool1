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
// Programmiert von Christian Tobias und Bartol Filipovic
//////////////////////////////////////////////////////////////////


#ifndef _asymmetric_
#define _asymmetric_

#include "s_ecFp.h" // elliptic curve stuff
#include "s_prng.h" // big random integers

#define UNKNOWN_SIGN 16
#define EC_SIGN 32
#define RSA_OR_DSA_SIGN 64

typedef struct
{
	CString a;
	CString b;
	CString p;
	CString G_xcoord;
	CString G_ycoord;
	CString pubKey_xcoord;
	CString pubKey_ycoord;
	CString privKey;
	CString k;
	CString r;
} EcDomParamAcAsString;

void KeyGen();
void DelPse();
void RsaEnc(char* infile, const char *OldTitle);
void RsaDec(char* infile, const char *OldTitle);
void Sign(char* infile, const char *OldTitle);
void Verify(char* infile, const char *OldTitle);
void DecHyb(char* infile, const char *OldTitle);
int GetEncHybridData(char* infile,CString& UserKeyId, CString& EncSessionKey, CString& SymAlg,\
				CString& AsymAlg, OctetString *message);

int PrintSignData(char *infile, const char *OldTitle, OctetString *in, bool& zugross, bool ecSign,\
				  char *hash_id, char *Verfahren, char *Verfahren2,\
				  CString UserKeyId, Signature* Signatur, L_NUMBER *c, L_NUMBER *d );

BOOL PrintSignature(OctetString&		SignText,
					const OctetString&	Signature, 
					const CString&		EncAlg, 
					const CString&		HshAlg, 
					const CString&		UserKeyId);

int GetSignData(char* infile, bool& zugross, CString& filename, OctetString *message, CString& SigAlg,\
				CString& HashAlg, CString& UserKeyId, int *SignLength, Signature *Signatur,\
				L_NUMBER *c, L_NUMBER *d);

int GenEcKeyPair(EcDomParam_ac_ptr ecParam);
int EcDomParamAcToString(EcDomParamAcAsString *ecParamString, EcDomParam_ac_ptr ecParam, const int base);

BOOL find(OctetString*, int, int&, int&);

#endif // #ifndef _asymmetric_
