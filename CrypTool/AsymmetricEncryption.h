/**************************************************************************

  Copyright [2009] [Christian Tobias, Bartol Filipovic] [CrypTool Team]

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
