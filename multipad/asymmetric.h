//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
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

int PrintSignData(char *infile, const char *OldTitle, OctetString *in, bool& zugross, bool ecSign,\
				  char *hash_id, char *Verfahren, char *Verfahren2,\
				  CString UserKeyId, Signature* Signatur, L_NUMBER *c, L_NUMBER *d );

OctetString* PrintSignature(OctetString&	Signature, 
							const CString&	EncAlg, 
							const CString&	HshAlg, 
							const CString&	UserKeyId);

int GetSignData(char* infile, bool& zugross, CString& filename, OctetString *message, CString& SigAlg,\
				CString& HashAlg, CString& UserKeyId, int *SignLength, Signature *Signatur,\
				L_NUMBER *c, L_NUMBER *d);

int GenEcKeyPair(EcDomParam_ac_ptr ecParam);
int EcDomParamAcToString(EcDomParamAcAsString *ecParamString, EcDomParam_ac_ptr ecParam, const int base);

#endif // #ifndef _asymmetric_