/****************************************************************
 *                                                              *
 *  This program is part of an implementation of the block      *
 *  cipher RC6(TM) that is being submitted to NIST as a         *
 *  candidate for the AES.                                      *
 *                                                              *
 *  Ronald L. Rivest and RSA Laboratories, the submitters of    *
 *  RC6, retain all rights to RC6 and to this code, except for  *
 *  those which NIST requires to be waived for submissions.     *
 *                                                              *
 *  Copyright (C) 1998 RSA Data Security, Inc.                  *
 *                                                              *
 ****************************************************************/

/* This file is the header for an optimized version of RC6 in C. */



/*  aes.h  */

/*  AES Cipher header file for ANSI C Submissions
      Lawrence E. Bassham III
      Computer Security Division
      National Institute of Standards and Technology

      April 15, 1998

    This sample is to assist implementers developing to the Cryptographic
API Profile for AES Candidate Algorithm Submissions.  Please consult this
document as a cross-reference.

    ANY CHANGES, WHERE APPROPRIATE, TO INFORMATION PROVIDED IN THIS FILE
MUST BE DOCUMENTED.  CHANGES ARE ONLY APPROPRIATE WHERE SPECIFIED WITH
THE STRING "CHANGE POSSIBLE".  FUNCTION CALLS AND THEIR PARAMETERS CANNOT
BE CHANGED.  STRUCTURES CAN BE ALTERED TO ALLOW IMPLEMENTERS TO INCLUDE
IMPLEMENTATION SPECIFIC INFORMATION.
*/

/*  Includes:
        Standard include files
*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>

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

/* This #define is specific to RC6: the number of rounds of encipherment */
#define     ROUNDS          20

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
/* This #define was added to be returned when cipherInit() is
 * provided with bad IV material.  It's not really RC6-specific. */
#define     BAD_IV_MAT         -6  /*  IV material is bad */

/*  CHANGE POSSIBLE:  inclusion of algorithm specific defines  */
/* The value of MAX_KEY_SIZE is specific to RC6 */
#undef MAX_KEY_SIZE
#define     MAX_KEY_SIZE        510  /* # of ASCII char's needed to
                                        represent a key */
#undef MAX_IV_SIZE
#define     MAX_IV_SIZE         16  /* # bytes needed to
                                        represent an IV  */

/*  Typedefs:

        Typedef'ed data storage elements.  Add any algorithm specific
parameters at the bottom of the structs as appropriate.
*/

typedef    unsigned char    BYTE;

/*  The structure for key information */
typedef struct {
      BYTE  direction;  /*  Key used for encrypting or decrypting? */
      int   keyLen;     /*  Length of the key  */
      char  keyMaterial[MAX_KEY_SIZE+1];  /*  Raw key data in ASCII,
                                    e.g., user input or KAT values */
      /*  The following parameters are algorithm dependent, replace or
                add as necessary  */
      /* Specific to RC6, we have removed the BYTE *KS and added in an
       * array of 2+2*ROUNDS+2 = 44 rounds to hold the key schedule */
      unsigned long S[2+2*ROUNDS+2];  /* Key schedule */
      } keyInstanceRC6;

/*  The structure for cipher information */
typedef struct {
      BYTE  mode;            /* MODE_ECB, MODE_CBC, or MODE_CFB1 */
      BYTE  IV[MAX_IV_SIZE]; /* A possible Initialization Vector for
                                        ciphering */
      /*  Add any algorithm specific parameters needed here  */
      /* We have removed the AES sample's blockSize field */
      } cipherInstanceRC6;


/*  Function protoypes  */
int makeKeyRC6(keyInstanceRC6 *key, BYTE direction, int keyLen,
                        char *keyMaterial);

int cipherInitRC6(cipherInstanceRC6 *cipher, BYTE mode, char *IV);

int blockEncryptRC6(cipherInstanceRC6 *cipher, keyInstanceRC6 *key, BYTE *input,
                        int inputLen, BYTE *outBuffer);

int blockDecryptRC6(cipherInstanceRC6 *cipher, keyInstanceRC6 *key, BYTE *input,
                        int inputLen, BYTE *outBuffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */
