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

/*
 * base64.h
 *
 * Header for base64 encoding and decoding algorithm. 
 *
 * Copyright (c) 2001--2002 by Wolfgang Wieser (wwieser@gmx.de)
 *
 * This file may be distributed and/or modified under the terms of the 
 * GNU General Public License version 2 as published by the Free Software 
 * Foundation. (See COPYING.GPL for details.)
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */


#ifndef _HLIB_Base64EncDec_H_
#define _HLIB_Base64EncDec_H_ 1
#define __attribute__(x)
// ERROR CODES
#define B64_CODE_NOERROR 0
#define B64_DECODE_PREMATURE_END -1
#define B64_DECODE_ILLEGAL_CHARACTER -2
#define B64_DECODE_MISSING_CHAR -3
#define B64_FILE_OPEN_ERROR -4
#define B64_FILE_WRITE_ERROR -5

// #include <hlib/prototypes.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int u_int32_t __attribute__((__mode__(__SI__)));
typedef signed int ssize_t;


/* ---ENCODE---
 * Reads in binary (8 bit) input data in _in of size inlen and encodes 
 * it as base64 storing the result in _out of size outlen. 
 * You may set lwidth to something non-zero to make Base64Encode() 
 * insert newlines every lwidth*4 chars. (lwidth=1 -> every 4 chars; 
 * lwidth=0 -> disable this feature)
 * If state is non-NULL state info is updated. 
 * State info (carry) is needed only if you have a large amount of 
 * 8bit data which cannot be encoded in one single call. 
 * To do this, set up the u_int32_t state value to zero and pass a 
 * pointer to it whenever calling Base64Encode(). The function will 
 * store non-encoded bytes (max. 2 bytes + 2 bit counter) in state 
 * to be able to process them the next time unless you call 
 * Base64Encode() with inlen=0 to tell it that this is the end of the 
 * input data. (state will be 0 after that but better relay on the 
 * return values for error diagnosis.) 
 * When reaching input data end (either state!=NULL and inlen=0 or 
 * state=NULL), the base64 termination char `=' is appended to the 
 * output. 
 * Note: the current byte quartett count is also stored in state as 
 *   14 bit value so that the base64 text stays formatted even if you 
 *   have to call Base64Encode() repeatedly. So, you don't try to 
 *   set lwidth to values >2^14 (that is 2^14*4=65536 chars per line). 
 * 
 * Return value: 
 *    0 -> correct encoding
 */
extern __w64 int Base64Encode(
	const char *_in,size_t inlen,
	char *_out,size_t outlen,int lwidth/*=0*/,ssize_t *outfill);

/* ---DECODE---
 * Reads in the base64 encoded string passed in _in of size inlen and 
 * stores the decoded result in buffer _out of size outlen. 
 * If state is non-NULL state info is updated. 
 * State info (carry) is needed only if you have a large amount of 
 * base64 data which cannot be decoded in one single call. 
 * To do this, set up the u_int32_t state value to zero and pass a 
 * pointer to it whenever calling Base64Decode(). The function will 
 * store non-decoded chars (max. 18 bits + 2 bit counter) in state 
 * to be able to process them the next time unless 
 *  - the base64 termination char (`=') is encountered or
 *  - you call Base64Decode() with inlen=0 which does just the same 
 *    as if you merely pass "=" as input. 
 * (state will be 0 after reading `=' / when passig inlen=0 but 
 *  better relay on the return values for error diagnosis.)
 * Return value: 
 *	  0 -> correct decoding
 *   -1 -> premature end (only if state is NULL or base64 termination 
 *         char `=' is encountered too early)
 *   -2 -> illegal char in input
 *   -3 -> Bad base64 block.
 *   -4 -> Error while opening file 
 *   -5 -> Error while writing to file
 */
extern ssize_t Base64Decode(
	const char *_in,size_t inlen,
	char *_out,size_t outlen,
	u_int32_t *state /*=NULL*/,ssize_t *outfill,ssize_t *indec, BOOL lastBlock,int *ai);

#ifdef __cplusplus
}
#endif

//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
void dobase64enc(const char *infile, const char *OldTitle);
void dobase64dec(const char *infile, const char *OldTitle);
void base64error(std::string text,char errchar,ssize_t errcode, ssize_t position, int chlb);


#endif   /* _HLIB_Base64EncDec_H_ */

