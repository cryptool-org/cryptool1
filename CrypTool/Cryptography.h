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
	char		*key;
	int			flags;
	void		*result;
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
void PermutationAsc(const char *infile, const char *OldTitle);
void Hashdemo(const char *infile,const char *OldTitle);
void HashOfAFile();
void SignatureTutorial(const char *infile, const char* OldTitle);
void CreateMac(const char *infile, const char *OldTitle);
void SymmetricEncryption(int AlgId, cryptProvider provider, 
						 const char* infile, const char *OldTitle, 
						 int fixed_keylength = 0);
UINT SymmetricBruteForce(PVOID p);

BOOL Rot13CaesarAsc(SymbolArray & text, const char *infile);
void Rot13CaesarAscFinish(SymbolArray & text, const char * infile, char * sKey, BOOL bDecrypt, const char *OldTitle, UINT type, bool keyOffsetZero);

// Rail Fence encryption (part of the simple transpositions dialog)
int RailFenceEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt = true);
// Scytale encryption (part of the simple transpositions dialog)
int ScytaleEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt = true);

#endif // __CRYPT_H