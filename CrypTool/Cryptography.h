//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#ifndef __CRYPT_H
#define __CRYPT_H

#include "DlgShowProgress.h"
#include "MakeNewName.h"

/////////////////////////////////////////////////////////////////
//
//
//

typedef struct {
	const char	*infile;
	const char	*OldTitle;
	int			keylen;
	char		*key;
	int			flags;
	void		*result;
} CryptPar;

// ================================================================
#define CRYPT_DISPLAY_BG		0x001
#define CRYPT_FREE_MEM			0x002
#define CRYPT_DO_WAIT_CURSOR	0x004
#define CRYPT_DISPLAY_IMMEDIATE	0x008
#define CRYPT_DO_PROGRESS		0x010
#define CRYPT_ASCII				0x020
#define CRYPT_DONE				0x080000000


void CaesarAsc(const char *infile, const char *OldTitle);	
void VigenereAsc(const char *infile, const char *OldTitle);	
void XorBin(const char *infile, const char *OldTitle);	
void AddBin(const char *infile, const char *OldTitle);	
void PlayfairBin(const char *infile, const char *OldTitle);	
void homophoncrypt(const char *infile, const char *OldTitle);	
void PlayfairAnalyse(const char *infile, const char *OldTitle);	
void VernamBin(const char *infile, const char *OldTitle);	
void EntropyASCII(const char *infile, const char *OldTitle);	
void EntropyBin(const char *infile, const char *OldTitle);	
UINT  Autocorr(PVOID p);	
UINT  Vitanycorr(PVOID p);	
UINT  Periode(PVOID p);	
UINT  zzgenit(PVOID p);	
UINT  FloatingEntropy(PVOID p);	
void HistogramASCII(const char *infile, const char *OldTitle);	
void HistogramBin(const char *infile, const char *OldTitle);	
void Hill(const char *infile, const char *OldTitle);
void Mono(const char *infile, const char *OldTitle);
UINT  AnaSubst(PVOID p);	
void AESCrypt (char* infile, const char *OldTitle, int AlgId, char * NewFileName = NULL, char* NewFileKey = NULL );
void HomophoneAsc(const char *infile, const char *OldTitle);
void HomophoneHex(const char *infile, const char *OldTitle);	
void NGramAsc(const char *infile, const char *OldTitle);
void NGramBin(const char *infile, const char *OldTitle);
void PermutationAsc(const char *infile, const char *OldTitle);
void Hashdemo(const char *infile,const char *OldTitle);
void HashOfAFile();
void SignatureTutorial(const char *infile, const char* OldTitle);

#endif // __CRYPT_H