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


/* rijndael-api-fst.h   v2.0   August '99
 * Optimised ANSI C code
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include "rijndael-alg-fst.h"

/*  Defines:
	Add any additional defines you need
*/

#define     DIR_ENCRYPT     0    /*  Are we encrpyting?  */
#define     DIR_DECRYPT     1    /*  Are we decrpyting?  */
#define     MODE_ECB        1    /*  Are we ciphering in ECB mode?   */
#define     MODE_CBC        2    /*  Are we ciphering in CBC mode?   */
#define     MODE_CFB1       3    /*  Are we ciphering in 1-bit CFB mode? */
#define     TRUE            1
#define     FALSE           0
#define	BITSPERBLOCK		128		/* Default number of bits in a cipher block */

/*  Error Codes - CHANGE POSSIBLE: inclusion of additional error codes  */
#define     BAD_KEY_DIR        -1  /*  Key direction is invalid, e.g.,
					unknown value */
#define     BAD_KEY_MAT        -2  /*  Key material not of correct 
					length */
#define     BAD_KEY_INSTANCE   -3  /*  Key passed is not valid  */
#define     BAD_CIPHER_MODE    -4  /*  Params struct passed to 
					cipherInit invalid */
#define     BAD_CIPHER_STATE   -5  /*  Cipher in wrong state (e.g., not 
					initialized) */
#define     BAD_BLOCK_LENGTH   -6 
#define     BAD_CIPHER_INSTANCE   -7 


/*  CHANGE POSSIBLE:  inclusion of algorithm specific defines  */
#undef MAX_KEY_SIZE
#undef MAX_IV_SIZE
#define     MAX_KEY_SIZE	64  /* # of ASCII char's needed to
					represent a key */
#define     MAX_IV_SIZE		32  /* # bytes needed to
					represent an IV  */

/*  Typedefs:

	Typedef'ed data storage elements.  Add any algorithm specific 
parameters at the bottom of the structs as appropriate.
*/

typedef    unsigned char    BYTE;

/*  The structure for key information */
typedef struct {
      BYTE  direction;	/*  Key used for encrypting or decrypting? */
      int   keyLen;	/*  Length of the key  */
      char  keyMaterial[MAX_KEY_SIZE+1];  /*  Raw key data in ASCII,
                                    e.g., user input or KAT values */
      /*  The following parameters are algorithm dependent, replace or
      		add as necessary  */
      int   blockLen;   /* block length */
      word8 keySched[MAXROUNDS+1][4][4];	/* key schedule		*/
      } keyInstanceRijndael;

/*  The structure for cipher information */
typedef struct {  /* changed order of the components */
      BYTE  IV[MAX_IV_SIZE]; /* A possible Initialization Vector for 
      					ciphering */
      /*  Add any algorithm specific parameters needed here  */
      int   blockLen;    	/* Sample: Handles non-128 bit block sizes
      					(if available) */
      } cipherInstanceRijndael;


/*  Function protoypes  */
/*  CHANGED: makeKey(): parameter blockLen added
                        this parameter is absolutely necessary if you want to
			setup the round keys in a variable block length setting 
	     cipherInit(): parameter blockLen added (for obvious reasons)		
 */
int makeKeyRijndael(keyInstanceRijndael *key, BYTE direction, int keyLen, char *keyMaterial);

int cipherInitRijndael(cipherInstanceRijndael *cipher, char *IV);

int blockEncryptRijndael(cipherInstanceRijndael *cipher, keyInstanceRijndael *key, BYTE *input, 
			unsigned int inputLen, BYTE *outBuffer);

int blockDecryptRijndael(cipherInstanceRijndael *cipher, keyInstanceRijndael *key, BYTE *input,
			unsigned int inputLen, BYTE *outBuffer);
int cipherUpdateRounds(cipherInstanceRijndael *cipher, keyInstanceRijndael *key, BYTE *input, 
                        int inputLen, BYTE *outBuffer, int Rounds);

#ifdef __cplusplus
}
#endif /* __cplusplus */
