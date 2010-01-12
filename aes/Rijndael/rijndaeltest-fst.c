/* rijndaeltest-fst.c   v2.0   August '99
 * Optimised ANSI C code
 * authors: v1.0: Paulo Barreto
 *                Antoon Bosselaers
 *          v2.0: Vincent Rijmen
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rijndael-api-fst.h"

#define SUBMITTER "Joan Daemen"

static void blockPrint (FILE *fp, const BYTE *block, const char *tag)
{
	int i;
	fprintf (fp, "%s=", tag);
	for (i = 0; i < 16; i++) {
		fprintf (fp, "%02X", block[i]);
	}
	fprintf (fp, "\n");
	fflush (fp);
} /* blockPrint */

static void rijndaelVKKAT (FILE *fp, int keyLength)
{
	int i, j, r;
	BYTE block[4*4];
	BYTE keyMaterial[320];
	BYTE byteVal = (BYTE)'8';
	keyInstance keyInst;
	cipherInstance cipherInst;

#ifdef TRACE_KAT_MCT
	printf ("Executing Variable-Key KAT (key %d): ", keyLength);
	fflush (stdout);
#endif /* ?TRACE_KAT_MCT */
	fprintf (fp,
		"\n"
		"==========\n"
		"\n"
		"KEYSIZE=%d\n"
		"\n", keyLength);
	fflush (fp);
	memset (block, 0, 16);
	blockPrint (fp, block, "PT");
	memset (keyMaterial, 0, sizeof (keyMaterial));
	memset (keyMaterial, '0', keyLength/4);
	for (i = 0; i < keyLength; i++) {
		keyMaterial[i/4] = byteVal; /* set only the i-th bit of the i-th test key */
		r = makeKey(&keyInst, DIR_ENCRYPT, keyLength, keyMaterial);
		if (TRUE != r) {
			fprintf(stderr,"makeKey error %d\n",r);
			exit(-1);
		}
		fprintf (fp, "\nI=%d\n", i+1);
		fprintf (fp, "KEY=%s\n", keyMaterial);
		memset (block, 0, 16);
		r = cipherInit (&cipherInst, MODE_ECB, NULL);
		if (TRUE != r) {
			fprintf(stderr,"cipherInit error %d\n",r);
			exit(-1);
		}
		r = blockEncrypt(&cipherInst, &keyInst, block, 128, block);
		if (128 != r) {
			fprintf(stderr,"blockEncrypt error %d\n",r);
			exit(-1);
		}
		blockPrint (fp, block, "CT");
		/* now check decryption: */
		makeKey(&keyInst, DIR_DECRYPT, keyLength, keyMaterial);
		blockDecrypt(&cipherInst, &keyInst, block, 128, block);
		for (j = 0; j < 16; j++) {
			assert (block[j] == 0);
		}
		/* undo changes for the next iteration: */
		keyMaterial[i/4] = (BYTE)'0';
		byteVal =
			(byteVal == '8') ?	'4' :
			(byteVal == '4') ?	'2' :
			(byteVal == '2') ?	'1' :
		/*	(byteVal == '1') */	'8';
	}
	assert (byteVal == (BYTE)'8');
	
#ifdef TRACE_KAT_MCT
	printf (" done.\n");
#endif /* ?TRACE_KAT_MCT */
} /* rijndaelVKKAT */


static void rijndaelVTKAT (FILE *fp, int keyLength)
{
	int i;
	BYTE block[4*4];
	BYTE keyMaterial[320];
	keyInstance keyInst;
	cipherInstance cipherInst;

#ifdef TRACE_KAT_MCT
	printf ("Executing Variable-Text KAT (key %d): ", keyLength);
	fflush (stdout);
#endif /* ?TRACE_KAT_MCT */
	fprintf (fp,
		"\n"
		"==========\n"
		"\n"
		"KEYSIZE=%d\n"
		"\n", keyLength);
	fflush (fp);
	memset (keyMaterial, 0, sizeof (keyMaterial));
	memset (keyMaterial, '0', keyLength/4);
	makeKey(&keyInst, DIR_ENCRYPT, keyLength, keyMaterial);
	fprintf (fp, "KEY=%s\n", keyMaterial);
	for (i = 0; i < 128; i++) {
		memset (block, 0, 16);
		block[i/8] |= 1 << (7 - i%8); /* set only the i-th bit of the i-th test block */
		fprintf (fp, "\nI=%d\n", i+1);
		blockPrint (fp, block, "PT");
		cipherInit (&cipherInst, MODE_ECB, NULL);
		blockEncrypt(&cipherInst, &keyInst, block, 128, block);
		blockPrint (fp, block, "CT");
	}
#ifdef TRACE_KAT_MCT
	printf (" done.\n");
#endif /* ?TRACE_KAT_MCT */
}


static void rijndaelTKAT (FILE *fp,  int keyLength, FILE *in)
{
	int i, j;
	unsigned int s;
	BYTE block[4*4], block2[4*4];
	BYTE keyMaterial[320];
	keyInstance keyInst;
	cipherInstance cipherInst;

#ifdef TRACE_KAT_MCT
	printf ("Executing Tables KAT (key %d): ", keyLength);
	fflush (stdout);
#endif /* ?TRACE_KAT_MCT */
	fprintf (fp,
		"\n"
		"==========\n"
		"\n"
		"KEYSIZE=%d\n"
		"\n", keyLength);
	fflush (fp);

	memset (keyMaterial, 0, sizeof (keyMaterial));
	
	for(i = 0; i < 64; i++) {
		fprintf (fp, "\nI=%d\n", i+1);
		for(j = 0; j < keyLength/4; j++) {
			fscanf(in,"%c",&keyMaterial[j]);
		}
		makeKey(&keyInst, DIR_ENCRYPT, keyLength, keyMaterial);
		
		fprintf (fp, "KEY=%s\n", keyMaterial);
		
		for(j = 0; j < 16; j++) {
			fscanf(in,"%02x",&s);
			block[j] = s;
		}
		fscanf(in,"%c",&s);
		fscanf(in,"%c",&s);
		blockPrint (fp, block, "PT");
		cipherInit (&cipherInst, MODE_ECB, NULL);
		blockEncrypt(&cipherInst, &keyInst, block, 128, block2);
		blockPrint (fp, block2, "CT");
	}
	for(i = 64; i < 128; i++) {
		fprintf (fp, "\nI=%d\n", i+1);
		for(j = 0; j < keyLength/4; j++) {
			fscanf(in,"%c",&keyMaterial[j]);
		}
		makeKey(&keyInst, DIR_DECRYPT, keyLength, keyMaterial);
		
		fprintf (fp, "KEY=%s\n", keyMaterial);
		
		for(j = 0; j < 16; j++) {
			fscanf(in,"%02x",&s);
			block[j] = s;
		}
		fscanf(in,"%c",&s);
		fscanf(in,"%c",&s);
		cipherInit (&cipherInst, MODE_ECB, NULL);
		blockDecrypt(&cipherInst, &keyInst, block, 128, block2);
		blockPrint (fp, block2, "PT");
		blockPrint (fp, block, "CT");
	}

#ifdef TRACE_KAT_MCT
	printf (" done.\n");
#endif /* ?TRACE_KAT_MCT */
}

static void rijndaelIVKAT (FILE *fp, int keyLength)
{
	int i;
	BYTE block[4*4], block2[4*4];
	BYTE keyMaterial[320];
	keyInstance keyInst;
	cipherInstance cipherInst;
	char format[10];
#ifdef TRACE_KAT_MCT
	printf ("Executing Intermediate value KAT (key %d): ", keyLength);
	fflush (stdout);
#endif /* ?TRACE_KAT_MCT */

	
	fprintf (fp,
		"\n"
		"==========\n"
		"\n"
		"KEYSIZE=%d\n",
		keyLength);
	fflush (fp);
	memset (keyMaterial, 0, sizeof (keyMaterial));
	for (i = 0; i < keyLength/8; i++) {
		sprintf (&keyMaterial[2*i], "%02X", i);
	}
	makeKey(&keyInst, DIR_ENCRYPT, keyLength, keyMaterial);
	fprintf (fp, "KEY=%s\n", keyMaterial);
	fprintf (fp, "\nIntermediate Ciphertext Values (Encryption)\n\n");
	for (i = 0; i < 16; i++) {
		block[i] = i;
	}
	blockPrint (fp, block, "PT");
	cipherInit (&cipherInst, MODE_ECB, NULL);
	for(i = 1; i < ROUNDS; i++) {
		cipherUpdateRounds (&cipherInst, &keyInst, block, 16, block2, i);
		sprintf(format,"CT%d",i);
		blockPrint (fp, block2, format);
	}
	cipherUpdateRounds (&cipherInst, &keyInst, block, 128, block2, ROUNDS);
	blockPrint (fp, block2, "CT");
	
	/* hack ! */
	/* in order to get the same intermediate values in decryption
	   as in decryption, we need to use the encryption roundkeys,
	   but the key direction has to be DIR_DECRYPT
	   
	   consider it as a dirty trick 
	 */
	makeKey(&keyInst, DIR_ENCRYPT, keyLength, keyMaterial);
	keyInst.direction = DIR_DECRYPT;
	/* end hack */
	fprintf (fp, "\nIntermediate Ciphertext Values (Decryption)\n\n");
	blockPrint (fp, block2, "CT");
	cipherInit (&cipherInst, MODE_ECB, NULL);
	for(i = 1; i < ROUNDS; i++) {
		cipherUpdateRounds (&cipherInst, &keyInst, block2, 128,block, ROUNDS-i);
		sprintf(format,"PT%d",i);
		blockPrint (fp, block, format);
	}
	cipherUpdateRounds (&cipherInst, &keyInst, block2, 128, block, 0);
	blockPrint (fp, block, "PT");
	
#ifdef TRACE_KAT_MCT
	printf (" done.\n");
#endif 
}

static void makeKATs (const char *vkFile, const char *vtFile, const char *tblFile,
                      const char *ivFile)
{
	FILE *fp, *fp2;

	/* prepare Variable Key Known Answer Tests: */
	fp = fopen (vkFile, "w");
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Electronic Codebook (ECB) Mode\n"
		"Variable Key Known Answer Tests\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		vkFile,SUBMITTER);
	fflush (fp);

	rijndaelVKKAT (fp, 128); /* test for 128-bit key */
	rijndaelVKKAT (fp, 192); /* test for 192-bit key */
	rijndaelVKKAT (fp, 256); /* test for 256-bit key */

	fprintf (fp,
		"\n"
		"==========");
	fclose (fp);

	/* prepare Variable Text Known Answer Tests: */
	fp = fopen (vtFile, "w");
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Electronic Codebook (ECB) Mode\n"
		"Variable Text Known Answer Tests\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		vtFile,SUBMITTER);
	fflush (fp);

	rijndaelVTKAT (fp, 128);
	rijndaelVTKAT (fp, 192);
	rijndaelVTKAT (fp, 256);

	fprintf (fp,
		"\n"
		"==========");
	fclose (fp);

	/* prepare Tables Known Answer Tests: */
	fp = fopen (tblFile, "w");
	fprintf (fp,
	        "/* Description of what tables are tested:\n"
		"   The provided implementations each use a different set of tables\n"
		"    - Java implementation: uses no tables\n"
		"    - reference C implementation: uses Logtable, Alogtable, S, Si, rcon\n"
		"    - fast C implementation: uses Logtable, Alogtable,  rcon\n"
		"        and additionally, T1, T2, T3, T4, T5, T6, T7, T8\n"
		"   All these tables are tested.\n" 
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Electronic Codebook (ECB) Mode\n"
		"Tables Known Answer Tests\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		tblFile,SUBMITTER);
	fflush (fp);


	if (NULL != (fp2 = fopen("table.128","r"))) {
		rijndaelTKAT (fp, 128,fp2);
		fclose(fp2);
	} else {
		printf("Table Known Answer test expects file table.128\n");
		fclose(fp);
		exit (EXIT_FAILURE);		
	}
	if (NULL != (fp2 = fopen("table.192","r"))) {
		rijndaelTKAT (fp, 192,fp2);
		fclose(fp2);
	} else {
		printf("Table Known Answer test expects file table.192\n");
		fclose(fp);
		exit (EXIT_FAILURE);		
	}
	if (NULL != (fp2 = fopen("table.256","r"))) {
		rijndaelTKAT (fp, 256,fp2);
		fclose(fp2);
	} else {
		printf("Table Known Answer test expects file table.192\n");
		fclose(fp);
		exit (EXIT_FAILURE);		
	}
	
	fprintf (fp,
		"\n"
		"==========");
	fclose (fp);

	/* prepare Intermediate Values Known Answer Tests: */
	fp = fopen (ivFile, "w");
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Electronic Codebook (ECB) Mode\n"
		"Intermediate Value Known Answer Tests\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		ivFile,SUBMITTER);
	fflush (fp);

	rijndaelIVKAT (fp, 128);
	rijndaelIVKAT (fp, 192);
	rijndaelIVKAT (fp, 256);

	fprintf (fp,
		"\n"
		"==========");
	fclose (fp);

}

static void rijndaelECB_MCT (FILE *fp, int keyLength, BYTE direction)
{
	int i, j;
	BYTE inBlock[4*4], outBlock[4*4], binKey[4*MAXKC];
	BYTE keyMaterial[320];
	keyInstance keyInst;
	cipherInstance cipherInst;

#ifdef TRACE_KAT_MCT
	int width = 0;
	clock_t elapsed = -clock();
	printf ("Executing ECB MCT (%s, key %d): ",
		direction == DIR_ENCRYPT ? "ENCRYPT" : "DECRYPT", keyLength);
	fflush (stdout);
#endif /* ?TRACE_KAT_MCT */
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"KEYSIZE=%d\n", keyLength);
	fflush (fp);
	memset (outBlock, 0, 16);
	memset (binKey, 0, keyLength/8);
	for (i = 0; i < 400; i++) {
#ifdef TRACE_KAT_MCT                 
        while (width-- > 0) putchar ('\b'); width = printf ("%d", i); fflush (stdout);    
#endif /* ?TRACE_KAT_MCT */
		fprintf (fp, "\nI=%d\n", i);
		/* prepare key: */
		for (j = 0; j < keyLength/8; j++) {
			sprintf (&keyMaterial[2*j], "%02X", binKey[j]);
		}
		keyMaterial[keyLength/4] = 0;
		fprintf (fp, "KEY=%s\n", keyMaterial);
		makeKey(&keyInst, direction, keyLength, keyMaterial);
		/* do encryption/decryption: */
		blockPrint (fp, outBlock, direction == DIR_ENCRYPT ? "PT" : "CT");
		cipherInit (&cipherInst, MODE_ECB, NULL);
		if (direction == DIR_ENCRYPT) {
			for (j = 0; j < 10000; j++) {
				memcpy (inBlock, outBlock, 16);
				blockEncrypt(&cipherInst, &keyInst, inBlock, 128, outBlock);
			}
		} else {
			for (j = 0; j < 10000; j++) {
				memcpy (inBlock, outBlock, 16);
				blockDecrypt(&cipherInst, &keyInst, inBlock, 128, outBlock);
			}
		}
		blockPrint (fp, outBlock, direction == DIR_ENCRYPT ? "CT" : "PT");
		/* prepare new key: */
		switch (keyLength) {
		case 128:
			for (j = 0; j < 128/8; j++) {
				binKey[j] ^= outBlock[j];
			}
			break;
		case 192:
			for (j = 0; j < 64/8; j++) {
				binKey[j] ^= inBlock[j + 64/8];
			}
			for (j = 0; j < 128/8; j++) {
				binKey[j + 64/8] ^= outBlock[j];
			}
			break;
		case 256:
			for (j = 0; j < 128/8; j++) {
				binKey[j] ^= inBlock[j];
			}
			for (j = 0; j < 128/8; j++) {
				binKey[j + 128/8] ^= outBlock[j];
			}
			break;
		}
	}
#ifdef TRACE_KAT_MCT
	elapsed += clock();
	printf (" done (%.1f s).\n", (float)elapsed/CLOCKS_PER_SEC);
#endif /* ?TRACE_KAT_MCT */
} /* rijndaelECB_MCT */


static void rijndaelCBC_MCT (FILE *fp, int keyLength, BYTE direction)
{
	int i, j, r, t;
	BYTE inBlock[256/8], outBlock[256/8], binKey[256/8], cv[256/8];
	BYTE keyMaterial[320];
	keyInstance keyInst;
	cipherInstance cipherInst;

#ifdef TRACE_KAT_MCT
	int width = 0;
	clock_t elapsed = -clock();
	printf ("Executing CBC MCT (%s, key %d): ",
		direction == DIR_ENCRYPT ? "ENCRYPT" : "DECRYPT", keyLength);
	fflush (stdout);
#endif /* ?TRACE_KAT_MCT */
	fprintf (fp,
		"\n"
		"==========\n"
		"\n"
		"KEYSIZE=%d\n", keyLength);
	fflush (fp);
	memset(cv,0,16);
	memset(inBlock,0,16);
	memset(binKey,0,keyLength/8);
	for (i = 0; i < 400; i++) {
#ifdef TRACE_KAT_MCT                 
        while (width-- > 0) putchar ('\b'); width = printf ("%d", i); fflush (stdout);    
#endif /* ?TRACE_KAT_MCT */
		fprintf (fp, "\nI=%d\n", i);
		/* prepare key: */
		for (j = 0; j < keyLength/8; j++) {
			sprintf (&keyMaterial[2*j], "%02X", binKey[j]);
		}
		keyMaterial[keyLength/4] = 0;
		fprintf (fp, "KEY=%s\n", keyMaterial);
		r = makeKey(&keyInst, direction, keyLength, keyMaterial);
		if (TRUE != r) {
			fprintf(stderr,"makeKey error %d\n",r);
			exit(-1);
		}
		r = cipherInit (&cipherInst, MODE_ECB, NULL);
		if (TRUE != r) {
			fprintf(stderr,"cipherInit error %d\n",r);
			exit(-1);
		}
		/* do encryption/decryption: */
		blockPrint (fp, cv, "IV");
		blockPrint (fp, inBlock, direction == DIR_ENCRYPT ? "PT" : "CT");
		if (direction == DIR_ENCRYPT) {
			for (j = 0; j < 10000; j++) {
				for(t = 0; t < 16; t++) inBlock[t] ^= cv[t];
				r = blockEncrypt(&cipherInst, &keyInst, inBlock, 128, outBlock);
				if (128 != r) {
					fprintf(stderr,"blockEncrypt error %d\n",r);
					exit(-1);
				}
				memcpy (inBlock, cv, 16);
				memcpy (cv, outBlock, 16);
			}
		} else {
			for (j = 0; j < 10000; j++) {
				blockDecrypt(&cipherInst, &keyInst, inBlock, 128, outBlock);
				for(t = 0; t < 16; t++) outBlock[t] ^= cv[t];
				memcpy (cv, inBlock, 16);
				memcpy (inBlock, outBlock, 16);
			}
		}
		blockPrint (fp, outBlock, direction == DIR_ENCRYPT ? "CT" : "PT");
		/* prepare new key: */
		switch (keyLength) {
		case 128:
			for (j = 0; j < 128/8; j++) {
				binKey[j] ^= outBlock[j];
			}
			break;
		case 192:
			for (j = 0; j < 64/8; j++) {
				if (direction == DIR_ENCRYPT)
					binKey[j] ^= inBlock[j + 64/8];
				else
					binKey[j] ^= cv[j + 64/8];
			}
			for (j = 0; j < 128/8; j++) {
				binKey[j + 64/8] ^= outBlock[j];
			}
			break;
		case 256:
			for (j = 0; j < 128/8; j++) {
				if (direction == DIR_ENCRYPT)
					binKey[j] ^= inBlock[j];
				else
					binKey[j] ^= cv[j];
			}
			for (j = 0; j < 128/8; j++) {
				binKey[j + 128/8] ^= outBlock[j];
			}
			break;
		}
	}
#ifdef TRACE_KAT_MCT
	elapsed += clock();
	printf (" done (%.1f s).\n", (float)elapsed/CLOCKS_PER_SEC);
#endif /* ?TRACE_KAT_MCT */
} /* rijndaelCBC_MCT */


static void makeMCTs (const char *ecbEncryptionFile, const char *ecbDecryptionFile,
	const char *cbcEncryptionFile, const char *cbcDecryptionFile)
{
	FILE *fp;

	/* prepare ECB Encryption Monte Carlo Tests: */
	fp = fopen (ecbEncryptionFile, "w");
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Electronic Codebook (ECB) Mode - ENCRYPTION\n"
		"Monte Carlo Test\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		ecbEncryptionFile,SUBMITTER);
	fflush (fp);

	rijndaelECB_MCT (fp, 128, DIR_ENCRYPT);
	rijndaelECB_MCT (fp, 192, DIR_ENCRYPT);
	rijndaelECB_MCT (fp, 256, DIR_ENCRYPT);

	fprintf (fp,
		"\n"
		"===========");
	fclose (fp);

	/* prepare ECB Decryption Monte Carlo Tests: */
	fp = fopen (ecbDecryptionFile, "w");
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Electronic Codebook (ECB) Mode - DECRYPTION\n"
		"Monte Carlo Test\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		ecbDecryptionFile,SUBMITTER);
	fflush (fp);

	rijndaelECB_MCT (fp, 128, DIR_DECRYPT);
	rijndaelECB_MCT (fp, 192, DIR_DECRYPT);
	rijndaelECB_MCT (fp, 256, DIR_DECRYPT);

	fprintf (fp,
		"\n"
		"===========");
	fclose (fp);

	/* prepare CBC Encryption Monte Carlo Tests: */
	fp = fopen (cbcEncryptionFile, "w");
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Cipher Block Chaining (CBC) Mode - ENCRYPTION\n"
		"Monte Carlo Test\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		cbcEncryptionFile,SUBMITTER);
	fflush (fp);

	rijndaelCBC_MCT (fp, 128, DIR_ENCRYPT);
	rijndaelCBC_MCT (fp, 192, DIR_ENCRYPT);
	rijndaelCBC_MCT (fp, 256, DIR_ENCRYPT);


	fprintf (fp,
		"\n"
		"===========");
	fclose (fp);

	/* prepare CBC Decryption Monte Carlo Tests: */
	fp = fopen (cbcDecryptionFile, "w");
	fprintf (fp,
		"\n"
		"=========================\n"
		"\n"
		"FILENAME:  \"%s\"\n"
		"\n"
		"Cipher Block Chaining (CBC) Mode - DECRYPTION\n"
		"Monte Carlo Test\n"
		"\n"
		"Algorithm Name: Rijndael\n"
		"Principal Submitter: %s\n",
		cbcDecryptionFile,SUBMITTER);
	fflush (fp);

	rijndaelCBC_MCT (fp, 128, DIR_DECRYPT);
	rijndaelCBC_MCT (fp, 192, DIR_DECRYPT);
	rijndaelCBC_MCT (fp, 256, DIR_DECRYPT);

	fprintf (fp,
		"\n"
		"===========");
	fclose (fp);
} /* makeMCTs */


void rand_init(void)
{
	srand(time(NULL));
}

word32 rand_word32(void)
{
	return
	((word32)(rand() >> 7) << 24) | 
	((word32)(rand() >> 7) << 16) | 
	((word32)(rand() >> 7) << 8) | 
	(word32)(rand() >> 7);
}


static void rijndaelSpeed (FILE *fp, int keyLength, BYTE mode, int iterations)
{
	int i, rounds;
	BYTE block[4*4];
	BYTE keyMaterial[320];
	char IV[2*4*4+1] = "A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5A5";
	keyInstance keyInst;
	cipherInstance cipherInst;
	clock_t elapsed;
	double sec;

	printf ("Measuring speed (key %d): \n", keyLength);
	fflush (stdout);

	rounds = iterations;
	rand_init();
	for (i=3; i>=0; i--)
		((word32*)block)[i] = rand_word32();
   	blockPrint (fp, block, "plaintext");

	memset (keyMaterial, 0, sizeof (keyMaterial));
	memset (keyMaterial, '0', keyLength/4);
	for (i = 0; i < keyLength/4; i++)
		keyMaterial[i] = '0'+ i;

	printf ("Measuring key scheduling speed...");
	elapsed = -clock ();
	for (i = rounds; i > 0; i--) {
		makeKey(&keyInst, DIR_ENCRYPT, keyLength, keyMaterial);
	}
	elapsed += clock ();
	sec = elapsed ? (double) elapsed / CLOCKS_PER_SEC : 1.0;
	printf (" %.2f sec, %.1f Mbit/sec.\n",
		sec, (double)keyLength*iterations/1E6/sec);

	if (mode == MODE_ECB) {
		cipherInit (&cipherInst, mode, NULL);
		}
	else {
		cipherInit (&cipherInst, mode, IV);
		}

	printf ("Measuring encryption speed...");
	elapsed = -clock ();
	for (i = rounds; i > 0; i--) {
		blockEncrypt(&cipherInst, &keyInst, block, 128, block);
	}
	elapsed += clock ();

	sec = elapsed ? (double) elapsed / CLOCKS_PER_SEC : 1.0;
	printf (" %.2f sec, %.1f Mbit/sec.\n",
		sec, (double)128*iterations/1E6/sec);
   	blockPrint (fp, block, "encrypted text");


	if (mode == MODE_ECB) {
		cipherInit (&cipherInst, mode, NULL);
		}
	else {
		cipherInit (&cipherInst, mode, IV);
		}

	if (mode != MODE_CFB1) {
		printf ("Measuring key scheduling speed...");
		elapsed = -clock ();
		for (i = rounds; i > 0; i--) {
			makeKey(&keyInst, DIR_DECRYPT, keyLength, keyMaterial);
		}
		elapsed += clock ();
		sec = elapsed ? (double) elapsed / CLOCKS_PER_SEC : 1.0;
		printf (" %.2f sec, %.1f Mbit/sec.\n",
			sec, (double)keyLength*iterations/1E6/sec);
	}
	printf ("Measuring decryption speed...");
	elapsed = -clock ();
	for (i = rounds; i > 0; i--) {
		blockDecrypt(&cipherInst, &keyInst, block, 128, block);
	}
	elapsed += clock ();
	sec = elapsed ? (double) elapsed / CLOCKS_PER_SEC : 1.0;
	printf (" %.2f sec, %.1f Mbit/sec.\n",
		sec, (double)128*iterations/1E6/sec);
   	blockPrint (fp, block, "decrypted text");
	
	printf ("done.\n");
} /* rijndaelSpeed */


int main (void)
{
	makeKATs ("ecb_vk.txt", "ecb_vt.txt", "ecb_tbl.txt", "ecb_iv.txt");
	makeMCTs ("ecb_e_m.txt", "ecb_d_m.txt", "cbc_e_m.txt", "cbc_d_m.txt");

	printf("ECB:\n");
	rijndaelSpeed (stdout, 128, MODE_ECB, 1000000);
	rijndaelSpeed (stdout, 192, MODE_ECB, 1000000);
	rijndaelSpeed (stdout, 256, MODE_ECB, 1000000);
	printf("CFB1:\n");
	rijndaelSpeed (stdout, 128, MODE_CFB1, 10000);

	return 0;
}

