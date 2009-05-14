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
