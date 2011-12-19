/* rijndael-api-fst.c   v2.0   August '99
 * Optimised ANSI C code
 * authors: v1.0: Antoon Bosselaers
 *          v2.0: Vincent Rijmen
 */

#include <stdlib.h>
#include <string.h>

#include "rijndael-alg-fst.h"
#include "rijndael-api-fst.h"

int makeKeyRijndael(keyInstanceRijndael *key, BYTE direction, int keyLen, char *keyMaterial)
{
	word8 k[MAXKC][4];
	int i, j, t;
	
	key->direction = direction;

	if ((keyLen == 128) || (keyLen == 192) || (keyLen == 256)) { 
		key->keyLen = keyLen;
	} else {
		return BAD_KEY_MAT;
	}

	if ( keyMaterial ) {
		strncpy_s(key->keyMaterial, MAX_KEY_SIZE+1, keyMaterial, keyLen/4);
	}

	ROUNDS = keyLen/32 + 6;

	/* initialize key schedule: */
 	for(i = 0; i < key->keyLen/8; i++) {
		t = key->keyMaterial[2*i];
		if ((t >= '0') && (t <= '9')) j = (t - '0') << 4;
		else if ((t >= 'a') && (t <= 'f')) j = (t - 'a' + 10) << 4; 
		else if ((t >= 'A') && (t <= 'F')) j = (t - 'A' + 10) << 4; 
		else return BAD_KEY_MAT;
		
		t = key->keyMaterial[2*i+1];
		if ((t >= '0') && (t <= '9')) j ^= (t - '0');
		else if ((t >= 'a') && (t <= 'f')) j ^= (t - 'a' + 10); 
		else if ((t >= 'A') && (t <= 'F')) j ^= (t - 'A' + 10); 
		else return BAD_KEY_MAT;
		
		k[i / 4][i % 4] = (word8) j; 
	}
	rijndaelKeySched (k, key->keyLen, key->keySched);
	if (direction == DIR_DECRYPT)
		rijndaelKeyEnctoDec (key->keyLen, key->keySched);

	return TRUE;
}

int cipherInitRijndael(cipherInstanceRijndael *cipher, char *IV)
{
	int i, j, t;
	

	if (IV != NULL) {
 		for(i = 0; i < 16; i++) {
			t = IV[2*i];
			if ((t >= '0') && (t <= '9')) j = (t - '0') << 4;
			else if ((t >= 'a') && (t <= 'f')) j = (t - 'a' + 10) << 4; 
			else if ((t >= 'A') && (t <= 'F')) j = (t - 'A' + 10) << 4; 
			else return BAD_CIPHER_INSTANCE;
		
			t = IV[2*i+1];
			if ((t >= '0') && (t <= '9')) j ^= (t - '0');
			else if ((t >= 'a') && (t <= 'f')) j ^= (t - 'a' + 10); 
			else if ((t >= 'A') && (t <= 'F')) j ^= (t - 'A' + 10); 
			else return BAD_CIPHER_INSTANCE;
			
			cipher->IV[i] = (word8) j;
		} 
	}

	return TRUE;
}


int blockEncryptRijndael(cipherInstanceRijndael *cipher,
	keyInstanceRijndael *key, BYTE *input, unsigned int inputLen, BYTE *outBuffer)
{
	int i, numBlocks;
	word8 block[16];

	if (cipher == NULL ||
		key == NULL ||
		key->direction == DIR_DECRYPT) {
		return BAD_CIPHER_STATE;
	}
	

	numBlocks = inputLen/16;
	
#if STRICT_ALIGN 
		memcpy(block,cipher->IV,16); 
#else
		*((word32*)block) =  *((word32*)(cipher->IV));
		*((word32*)(block+4)) =  *((word32*)(cipher->IV+4));
		*((word32*)(block+8)) =  *((word32*)(cipher->IV+8));
		*((word32*)(block+12)) =  *((word32*)(cipher->IV+12));
#endif
		
		for (i = numBlocks; i > 0; i--) {
			*((word32*)block) ^= *((word32*)(input));
			*((word32*)(block+4)) ^= *((word32*)(input+4));
			*((word32*)(block+8)) ^= *((word32*)(input+8));
			*((word32*)(block+12)) ^= *((word32*)(input+12));

			rijndaelEncrypt (block, outBuffer, key->keySched);
			
			*((word32*)block) =  *((word32*)(outBuffer));
			*((word32*)(block+4)) =  *((word32*)(outBuffer+4));
			*((word32*)(block+8)) =  *((word32*)(outBuffer+8));
			*((word32*)(block+12)) =  *((word32*)(outBuffer+12));

			input += 16;
			outBuffer += 16;
		}
#if STRICT_ALIGN 
		memcpy(cipher->IV,block,16); 
#else
		*((word32*)(cipher->IV)) = *((word32*)block);
		*((word32*)(cipher->IV+4)) = *((word32*)(block+4));
		*((word32*)(cipher->IV+8)) = *((word32*)(block+8));
		*((word32*)(cipher->IV+12)) = *((word32*)(block+12));
#endif
	
	
	return numBlocks*16;
}

int blockDecryptRijndael(cipherInstanceRijndael *cipher,
	keyInstanceRijndael *key, BYTE *input, unsigned int inputLen, BYTE *outBuffer)
{
	int i, numBlocks;
	word8 block[16];


	numBlocks = inputLen/16;
	
		/* first block */ 

		rijndaelDecrypt (input, block, key->keySched);
#if STRICT_ALIGN
		memcpy(outBuffer,cipher->IV,16); 
  		*((word32*)(outBuffer)) ^= *((word32*)block);
  		*((word32*)(outBuffer+4)) ^= *((word32*)(block+4));
  		*((word32*)(outBuffer+8)) ^= *((word32*)(block+8));
  		*((word32*)(outBuffer+12)) ^= *((word32*)(block+12));
#else
  		*((word32*)(outBuffer)) = *((word32*)block) ^ *((word32*)(cipher->IV));
  		*((word32*)(outBuffer+4)) = *((word32*)(block+4)) ^ *((word32*)(cipher->IV+4));
  		*((word32*)(outBuffer+8)) = *((word32*)(block+8)) ^ *((word32*)(cipher->IV+8));
  		*((word32*)(outBuffer+12)) = *((word32*)(block+12)) ^ *((word32*)(cipher->IV+12));
#endif
		
		/* next blocks */
		for (i = numBlocks-1; i > 0; i--) { 

			input += 16;

			rijndaelDecrypt (input, block, key->keySched);

			*((word32*)(outBuffer+16)) = *((word32*)block) ^
					*((word32*)(input-16));
			*((word32*)(outBuffer+20)) = *((word32*)(block+4)) ^
					*((word32*)(input-12));
			*((word32*)(outBuffer+24)) = *((word32*)(block+8)) ^
					*((word32*)(input-8));
			*((word32*)(outBuffer+28)) = *((word32*)(block+12)) ^
					*((word32*)(input-4));

			outBuffer += 16;

		}
	
#if STRICT_ALIGN
		memcpy(cipher->IV,input,16); 
#else
		*((word32*)(cipher->IV)) = *((word32*)input);
		*((word32*)(cipher->IV+4)) = *((word32*)(input+4));
		*((word32*)(cipher->IV+8)) = *((word32*)(input+8));
		*((word32*)(cipher->IV+12)) = *((word32*)(input+12));
#endif

		return numBlocks*16;
}


/**
 *	cipherUpdateRounds:
 *
 *	Encrypts/Decrypts exactly one full block a specified number of rounds.
 *	Only used in the Intermediate Value Known Answer Test.	
 *
 *	Returns:
 *		TRUE - on success
 *		BAD_CIPHER_STATE - cipher in bad state (e.g., not initialized)
 */
int cipherUpdateRounds(cipherInstanceRijndael *cipher,
	keyInstanceRijndael *key, BYTE *input, int inputLen, BYTE *outBuffer, int rounds)
{
	int j;
	word8 block[4][4];

	for (j = 3; j >= 0; j--) {
		/* parse input stream into rectangular array */
  		*((word32*)block[j]) = *((word32*)(input+4*j));
	}

	switch (key->direction) {
	case DIR_ENCRYPT:
		rijndaelEncryptRound (block, key->keySched, rounds);
	break;
		
	case DIR_DECRYPT:
		rijndaelDecryptRound (block, key->keySched, rounds);
	break;
		
	default: return BAD_KEY_DIR;
	} 

	for (j = 3; j >= 0; j--) {
		/* parse rectangular array into output ciphertext bytes */
		*((word32*)(outBuffer+4*j)) = *((word32*)block[j]);
	}
	
	return TRUE;
}
