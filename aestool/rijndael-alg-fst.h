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


/* rijndael-alg-fst.h   v2.0   August '99
 * Optimised ANSI C code
 */
#ifndef __RIJNDAEL_ALG_H
#define __RIJNDAEL_ALG_H

#define MAXKC				(256/32)
#define MAXROUNDS			14

typedef unsigned char		word8;	
typedef unsigned short		word16;	
typedef unsigned int		word32;

#undef ROUNDS
#undef W

int ROUNDS;

int rijndaelKeySched (word8 k[MAXKC][4], int keyBits,  
		word8 rk[MAXROUNDS+1][4][4]);
int rijndaelKeyEnctoDec (int keyBits, word8 W[MAXROUNDS+1][4][4]);
int rijndaelEncrypt (word8 a[16], word8 b[16], 
		word8 rk[MAXROUNDS+1][4][4]);
int rijndaelEncryptRound (word8 a[4][4],  
		word8 rk[MAXROUNDS+1][4][4], int rounds);
int rijndaelDecrypt (word8 a[16], word8 b[16],
		word8 rk[MAXROUNDS+1][4][4]);
int rijndaelDecryptRound (word8 a[4][4],  
		word8 rk[MAXROUNDS+1][4][4], int rounds);

#endif /* __RIJNDAEL_ALG_H */
