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
