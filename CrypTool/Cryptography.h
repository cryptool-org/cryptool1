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

#ifndef __CRYPT_H
#define __CRYPT_H

#include "DlgShowProgress.h"
#include "MakeNewName.h"
#include "symEncBase.h"

#define _CRT_SECURE_NO_WARNINGS

/////////////////////////////////////////////////////////////////
//
//
//

typedef struct {
	const char	*infile;
	const char	*OldTitle;
	int			keylenmin;  // valid key lengths [bit]:
	int			keylenmax;  // { x | x = keylenmin + n*keylenstep, n >= 0, x <= keylenmax }
	int			keylenstep; 
	char		  *key;
	int			flags;
	void		  *result;
} CryptPar;

typedef struct  {
	int AlgId;
	cryptProvider provider;
} algorithm_info;

// ================================================================
#define CRYPT_DISPLAY_BG		0x001
#define CRYPT_FREE_MEM			0x002
#define CRYPT_DO_WAIT_CURSOR	0x004
#define CRYPT_DISPLAY_IMMEDIATE	0x008
#define CRYPT_DO_PROGRESS		0x010
#define CRYPT_ASCII				0x020
#define CRYPT_DONE				0x080000000

#define CRYPT_PARITY_NONE				0
#define CRYPT_PARITY_DES				1
#define CRYPT_PARITY_DESX				2

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
int AnalyseMonoManual(const char *infile, const char *OldTitle);
void Mono(const char *infile, const char *OldTitle);
UINT  AnaSubst(PVOID p);	
void AESCrypt (const char* infile, const char *OldTitle, int AlgId, bool Enc_Or_Dec = NULL, const char * NewFileName = NULL, const char* NewFileKey = NULL);
void HomophoneAsc(const char *infile, const char *OldTitle);
void NGramAsc(const char *infile, const char *OldTitle);
void NGramBin(const char *infile, const char *OldTitle);
// void PermutationAsc(const char *infile, const char *OldTitle);
void Permutation(const char *infile, const char *OldTitle, BOOL TEXTMODE);
void Hashdemo(const char *infile,const char *OldTitle);
void HashOfAFile();
void SignatureTutorial(const char *infile, const char* OldTitle);
void CreateMac(const char *infile, const char *OldTitle);
void SymmetricEncryption(int AlgId, cryptProvider provider, 
						 const char* infile, const char *OldTitle, 
						 int fixed_keylength = 0);
UINT SymmetricBruteForce(PVOID p);

long Rot13CaesarAscStart(SymbolArray & text, const char *infile);
void Rot13CaesarAscFinish(SymbolArray & text, const char * infile, char * sKey, BOOL bDecrypt, const char *OldTitle, UINT type, bool keyOffsetZero);

// Rail Fence encryption (part of the simple transpositions dialog)
int RailFenceEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt = true);
// Scytale encryption (part of the simple transpositions dialog)
int ScytaleEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt = true);
void Solitaire(const char *infile, const char *OldTitle);


#endif // __CRYPT_H