

/* AES known answer tests and Monte Carlo tests.
   This code assumes little endian (Intel)

   The results are output to the following files:

    cbc_d_m.txt - Monte Carlo cipher block chaining decryption
    cbc_e_m.txt - Monte Carlo cipher block chaining encryption
    ecb_d_m.txt - Monte Carlo electronic codebook mode decryption
    ecb_e_m.txt - Monte Carlo electronic codebook mode encryption
    ecb_vk.txt - variable key known answer test electrnoic codebook mode
    ecb_vt.txt - variable text known answer test electrnoic codebook mode

 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "aes.h"


#define BLOCKSIZE   128
#define ALG_NAME    "RC6 (TM)"
#define SUBMITTER   "RSA Laboratories"



/* These macros always have hexadecimal letters in lower case */
#define HEX(x) (char) ( ((x) < 10) ? (x)+'0' : (x)+'a'-10 )
#define HEX_TO_DIGIT(x) (BYTE) ( ((x) >= '0' && (x) <= '9') ?  (x)-'0' : (x)-'a'+10 )

void KAT1();
void KAT2();
void outputHeaderKAT1();
void outputHeaderKAT2();

void MCT1();
void MCT2();
void MCT3();
void MCT4();
void outputHeaderMCT1();
void outputHeaderMCT2();
void outputHeaderMCT3();
void outputHeaderMCT4();

int
main () {
  FILE *fp;
  char filename[100], fullname[100];


  sprintf (filename, "ecb_vk.txt");
  sprintf (fullname, "%s",filename);
  fp = fopen (fullname,"w");
  if (fp == NULL) {
    printf ("error opening file %s\n", filename);
    exit(1);
  }
  outputHeaderKAT1 (fp, filename);
  printf ("KAT1\n"); fflush(stdout);
  KAT1(fp, 16);
  KAT1(fp, 24);
  KAT1(fp, 32);
  fprintf (fp, "==========\n");
  fclose(fp);

  sprintf (filename, "ecb_vt.txt");
  sprintf (fullname, "%s",filename);
  fp = fopen (fullname,"w");
  if (fp == NULL) {
    printf ("error opening file %s\n", filename);
    exit(1);
  }
  outputHeaderKAT2 (fp, filename);
  printf ("KAT2\n"); fflush(stdout);
  KAT2(fp, 16);
  KAT2(fp, 24);
  KAT2(fp, 32);
  fprintf (fp, "==========\n");
  fclose(fp);

  sprintf (filename, "ecb_e_m.txt");
  sprintf (fullname, "%s",filename);
  fp = fopen (fullname,"w");
  if (fp == NULL) {
    printf ("error opening file %s\n", filename);
    exit(1);
  }
  outputHeaderMCT1 (fp, filename);
  printf ("MCT1\n"); fflush(stdout);
  MCT1(fp, 16);
  MCT1(fp, 24);
  MCT1(fp, 32);
  fprintf (fp, "==========\n");
  fclose(fp);

  sprintf (filename, "ecb_d_m.txt");
  sprintf (fullname, "%s",filename);
  fp = fopen (fullname,"w");
  if (fp == NULL) {
    printf ("error opening file %s\n", filename);
    exit(1);
  }
  outputHeaderMCT2 (fp, filename);
  printf ("MCT2\n"); fflush(stdout);
  MCT2(fp, 16);
  MCT2(fp, 24);
  MCT2(fp, 32);
  fprintf (fp, "==========\n");
  fclose(fp);

  sprintf (filename, "cbc_e_m.txt");
  sprintf (fullname, "%s",filename);
  fp = fopen (fullname,"w");
  if (fp == NULL) {
    printf ("error opening file %s\n", filename);
    exit(1);
  }
  outputHeaderMCT3 (fp, filename);
  printf ("MCT3\n"); fflush(stdout);
  MCT3(fp, 16);
  MCT3(fp, 24);
  MCT3(fp, 32);
  fprintf (fp, "==========\n");
  fclose(fp);

  sprintf (filename, "cbc_d_m.txt");
  sprintf (fullname, "%s",filename);
  fp = fopen (fullname,"w");
  if (fp == NULL) {
    printf ("error opening file %s\n", filename);
    exit(1);
  }
  outputHeaderMCT4 (fp, filename);
  printf ("MCT4\n"); fflush(stdout);
  MCT4(fp, 16);
  MCT4(fp, 24);
  MCT4(fp, 32);
  fprintf (fp, "==========\n");
  fclose(fp);

  return 0;
}



void
outputBlock (FILE *fp, BYTE *block)
{
  int k;

  for (k=0; k < BLOCKSIZE/8; ++k)
    fprintf (fp,"%.2x", block[k]);
}



void
outputKey (FILE *fp, char *K, int len)
{
  register int i;

  for (i=0; i < len; ++i)
    fprintf (fp, "%c",K[i]);
}


void
outputHeaderKAT1 (FILE *fp, char *filename)
{
  fprintf (fp,"=========================\n\n");
  fprintf (fp,"FILENAME:  \"%s\"\n\n", filename);
  fprintf (fp,"Electronic Codebook (ECB) Mode\n");
  fprintf (fp,"Variable Key Known Answer Tests\n\n");
  fprintf (fp,"Algorithm Name: %s\n",ALG_NAME);
  fprintf (fp,"Principal Submitter: %s\n\n", SUBMITTER);
}


void
outputHeaderKAT2 (FILE *fp, char *filename)
{
  fprintf (fp,"=========================\n\n");
  fprintf (fp,"FILENAME:  \"%s\"\n\n", filename);
  fprintf (fp,"Electronic Codebook (ECB) Mode\n");
  fprintf (fp,"Variable Text Known Answer Tests\n\n");
  fprintf (fp,"Algorithm Name: %s\n",ALG_NAME);
  fprintf (fp,"Principal Submitter: %s\n\n", SUBMITTER);
}


void
outputHeaderMCT1 (FILE *fp, char *filename)
{
  fprintf (fp,"=========================\n\n");
  fprintf (fp,"FILENAME:  \"%s\"\n\n", filename);
  fprintf (fp,"Electronic Codebook (ECB) Mode - ENCRYPTION\n");
  fprintf (fp,"Monte Carlo Test\n\n");
  fprintf (fp,"Algorithm Name: %s\n",ALG_NAME);
  fprintf (fp,"Principal Submitter: %s\n\n", SUBMITTER);
}


void
outputHeaderMCT2 (FILE *fp, char *filename)
{
  fprintf (fp,"=========================\n\n");
  fprintf (fp,"FILENAME:  \"%s\"\n\n", filename);
  fprintf (fp,"Electronic Codebook (ECB) Mode - DECRYPTION\n");
  fprintf (fp,"Monte Carlo Test\n\n");
  fprintf (fp,"Algorithm Name: %s\n",ALG_NAME);
  fprintf (fp,"Principal Submitter: %s\n\n", SUBMITTER);
}


void
outputHeaderMCT3 (FILE *fp, char *filename)
{
  fprintf (fp,"=========================\n\n");
  fprintf (fp,"FILENAME:  \"%s\"\n\n", filename);
  fprintf (fp,"Cipher Block Chaining (CBC) Mode - ENCRYPTION\n");
  fprintf (fp,"Monte Carlo Test\n\n");
  fprintf (fp,"Algorithm Name: %s\n",ALG_NAME);
  fprintf (fp,"Principal Submitter: %s\n\n", SUBMITTER);
}


void
outputHeaderMCT4 (FILE *fp, char *filename)
{
  fprintf (fp,"=========================\n\n");
  fprintf (fp,"FILENAME:  \"%s\"\n\n", filename);
  fprintf (fp,"Cipher Block Chaining (CBC) Mode - DECRYPTION\n");
  fprintf (fp,"Monte Carlo Test\n\n");
  fprintf (fp,"Algorithm Name: %s\n",ALG_NAME);
  fprintf (fp,"Principal Submitter: %s\n\n", SUBMITTER);
}



/* Variable key known answer tests
   (b = key bytes)
 */
void
KAT1 (FILE *fp, int b)
{
  char *K;
  keyInstance S;
  int k, i;
  BYTE pt[BLOCKSIZE/8], ct[BLOCKSIZE/8];
  cipherInstance ci;

  K = (char *) malloc (2*b);

  /* set the plaintext to all 0's */
  for (k=0; k<BLOCKSIZE/8; ++k)
    pt[k] = 0;

  /* set the key to all 0's */
  memset (K, '0', 2*b);

  fprintf (fp, "==========\n\n");
  fprintf (fp, "KEYSIZE=%d\n\n", 8*b);
  fprintf (fp, "PT=");
  outputBlock (fp, pt);
  fprintf (fp, "\n\n");

  for (i=0; i < 8*b; ++i) {

    K[i/4] = HEX (1 << (3 - (i&3)));
    fprintf (fp, "I=%d\n",i+1);
    fprintf (fp, "KEY=");
    outputKey (fp, K, 2*b);

    makeKey (&S, DIR_ENCRYPT, b*8, K);
    cipherInit (&ci, MODE_ECB, "");

    blockEncrypt (&ci, &S, pt, 128, ct);

    fprintf (fp, "\nCT=");
    outputBlock (fp, ct);

    fprintf (fp, "\n\n");

    K[i/4] = '0';

  }

  free (K);
}


/* Variable text known answer tests
   (b = key bytes)
 */
void
KAT2 (FILE *fp, int b)
{
  char *K;
  keyInstance S;
  int i, k;
  BYTE pt[BLOCKSIZE/8], ct[BLOCKSIZE/8];
  cipherInstance ci;

  K = (char *) malloc (2*b);

  /* set the plaintext to all 0's */
  for (k=0; k<BLOCKSIZE/8; ++k)
    pt[k] = 0;

  /* set the key to all 0's */
  memset (K, '0', 2*b);

  fprintf (fp, "==========\n\n");
  fprintf (fp, "KEYSIZE=%d\n\n", 8*b);
  fprintf (fp, "KEY=");
  outputKey (fp, K, 2*b);
  fprintf (fp, "\n\n");

  makeKey (&S, DIR_ENCRYPT, b*8, K);
  cipherInit (&ci, MODE_ECB, "");

  for (i=0; i < BLOCKSIZE; ++i) {

    fprintf (fp, "I=%d\n",i+1);
    pt[i/8] = (BYTE) (1 << (7 - (i&7)));
    fprintf (fp, "PT=");
    outputBlock (fp, pt);

    blockEncrypt (&ci, &S, pt, 128, ct);

    fprintf (fp, "\nCT=");
    outputBlock (fp, ct);
    fprintf (fp, "\n\n");
    pt[i/8] = 0;
  }

  free (K);

}


/* this function is used for computing the new key in the Monte Carlo tests.
   K is the current key (hexadecimal string)
   b is half the number of bytes of K (which is the same as the number of
     bytes of K after K is converted to a binary string)
   secondToLast is the second to last plaintext or ciphertext from the
     innermost loop of the Monte Carlo test (binary string)
   last is the last plaintext or ciphertext from the innermost loop of
     the Monte Carlo test (binary string)
 */
void
FormNewKey (char *K, int b, BYTE *secondToLast, BYTE *last)
{
  BYTE bsK[32]; /* binary string K */
  int k;

  /* first convert K to a binary string */
  for (k=0; k < b; ++k) {
    bsK[k] = HEX_TO_DIGIT (K[2*k]);
    bsK[k] <<= 4;
    bsK[k] |= HEX_TO_DIGIT (K[2*k+1]);
  }

  /* now combine bsK with secondToLast and Last */
  if (b >= 16 && b <= 32) {
    for (k=0; k < b-16; ++k)
      bsK[k] ^= secondToLast[k+32-b];
    for (; k < b; ++k)
      bsK[k] ^= last[k-(b-16)];
  }
  else if (b < 16) {
    for (k=0; k < b; ++k)
      bsK[k] ^= last[k+16-b];
  }
  else {
    printf ("ERROR!  MCT requies b <= 32\n");
    exit(1);
  }

  /* Now convert the new key back to a hexadecimal string */
  for (k=0; k < b; ++k) {
    K[2*k] = HEX (((bsK[k]>>4)&15));
    K[2*k+1] = HEX (bsK[k]&15);
  }

}



/* Monte Carlo Test - ECB Encryption
   (b = key bytes)
 */
void
MCT1 (FILE *fp, int b)
{
  char *K;
  keyInstance S;
  int i, j, k;
  BYTE pt[BLOCKSIZE/8], ct[BLOCKSIZE/8], ib[BLOCKSIZE/8];
  cipherInstance ci;

  K = (char *) malloc (2*b);

  /* set the plaintext to all 0's */
  for (k=0; k<BLOCKSIZE/8; ++k)
    pt[k] = 0;

  /* set the key to all 0's */
  memset (K, '0', 2*b);
  
  fprintf (fp, "==========\n\n");
  fprintf (fp, "KEYSIZE=%d\n\n", 8*b);

  for (i=0; i < 400; ++i) {
    fprintf (fp, "I=%d\n",i);
    fprintf (fp, "KEY=");
    outputKey (fp, K, 2*b);
    fprintf (fp, "\n");
    fprintf (fp, "PT=");
    outputBlock (fp, pt);
    fprintf (fp, "\n");

    makeKey (&S, DIR_ENCRYPT, b*8, K);
    cipherInit (&ci, MODE_ECB, "");

    for (j = 0; j < 10000; ++j) {

      for (k=0; k < BLOCKSIZE/8; ++k)
        ib[k] = pt[k];

      blockEncrypt (&ci, &S, ib, 128, ct);

      for (k=0; k < BLOCKSIZE/8; ++k)
        pt[k] = ct[k];
    }

    /* at end of loop:
        pt has the last ciphertext
        ib has second to last ciphertext
     */
    fprintf (fp, "CT=");
    outputBlock (fp, pt);
    fprintf (fp, "\n\n");

    /* form new key
     */
    FormNewKey (K, b, ib, pt);

    /* The plaintext for the next loop is the ciphertext that
       was just output.  This is already stored in pt.
     */
  }

  free (K);
}


/* Monte Carlo Test - ECB Decryption
   (b = key bytes)
 */
void
MCT2 (FILE *fp, int b)
{
  char *K;
  keyInstance S;
  int i, j, k;
  BYTE pt[BLOCKSIZE/8], ct[BLOCKSIZE/8], ib[BLOCKSIZE/8];
  cipherInstance ci;

  K = (char *) malloc (2*b);

  /* set the plaintext to all 0's */
  for (k=0; k<BLOCKSIZE/8; ++k)
    ct[k] = 0;

  /* set the key to all 0's */
  memset (K, '0', 2*b);

  fprintf (fp, "==========\n\n");
  fprintf (fp, "KEYSIZE=%d\n\n", 8*b);

  for (i=0; i < 400; ++i) {
    fprintf (fp, "I=%d\n",i);
    fprintf (fp, "KEY=");
    outputKey (fp, K, 2*b);
    fprintf (fp, "\n");
    fprintf (fp, "CT=");
    outputBlock (fp, ct);
    fprintf (fp, "\n");

    makeKey (&S, DIR_DECRYPT, b*8, K);
    cipherInit (&ci, MODE_ECB, "");

    for (j = 0; j < 10000; ++j) {

      for (k=0; k < BLOCKSIZE/8; ++k)
        ib[k] = ct[k];

      blockDecrypt (&ci, &S, ct, 128, pt);
 
      for (k=0; k < BLOCKSIZE/8; ++k)
        ct[k] = pt[k]; 

    }

    fprintf (fp, "PT=");
    outputBlock (fp, pt);
    fprintf (fp, "\n\n");

    /* form new key
     */
    FormNewKey (K, b, ib, pt);

    /* The ciphertext for the next loop is the plaintext that
       was just output.  This is already stored in ct.
     */
  }

  free (K);

}



/* Monte Carlo Test - CBC Encryption
   (b = key bytes)
 */
void
MCT3 (FILE *fp, int b)
{
  char *K;
  keyInstance S;
  int i, j, k;
  BYTE pt[BLOCKSIZE/8], ct[BLOCKSIZE/8], ib[BLOCKSIZE/8];
  BYTE cv[BLOCKSIZE/8], iv[BLOCKSIZE/8];
  cipherInstance ci;

  /* choose an initial value */
  for (k=0; k < BLOCKSIZE/8; ++k)
    iv[k] = 0x0;

  K = (char *) malloc (2*b);

  /* set the plaintext to all 0's */
  for (k=0; k<BLOCKSIZE/8; ++k)
    pt[k] = 0;

  /* set the key to all 0's */
  memset (K, '0', 2*b);
  
  fprintf (fp, "==========\n\n");
  fprintf (fp, "KEYSIZE=%d\n\n", 8*b);

  for (i=0; i < 400; ++i) {

    if (i==0) {
      for (k=0; k < BLOCKSIZE/8; ++k)
        cv[k] = iv[k];
    }

    fprintf (fp, "I=%d\n",i);
    fprintf (fp, "KEY=");
    outputKey (fp, K, 2*b);
    fprintf (fp, "\n");
    fprintf (fp, "IV=");
    outputBlock (fp, cv);
    fprintf (fp, "\n");
    fprintf (fp, "PT=");
    outputBlock (fp, pt);
    fprintf (fp, "\n");

    makeKey (&S, DIR_ENCRYPT, b*8, K);
    cipherInit (&ci, MODE_ECB, "");

    for (j = 0; j < 10000; ++j) {
      for (k=0; k < BLOCKSIZE/8; ++k)
        ib[k] = (BYTE) (pt[k] ^ cv[k]);

      blockEncrypt (&ci, &S, ib, 128, ct);

      if (j==0) {
        for (k=0; k < BLOCKSIZE/8; ++k)
          pt[k] = cv[k];
      }
      else {
        /* cv holds the ciphertext from the previous round */
        for (k=0; k < BLOCKSIZE/8; ++k)
          pt[k] = cv[k];
      }

      for (k=0; k < BLOCKSIZE/8; ++k)
        cv[k] = ct[k];

    }

    fprintf (fp, "CT=");
    outputBlock (fp, ct);
    fprintf (fp, "\n\n");

    /* form new key
     */
    FormNewKey (K, b, pt, ct);

    for (k=0; k < BLOCKSIZE/8; ++k) {
      cv[k] = ct[k];
    }

  }

  free (K);
}


/* Monte Carlo Test - CBC Decryption
   (b = key bytes)
 */
void
MCT4 (FILE *fp, int b)
{
  char *K;
  keyInstance S;
  int i, j, k;
  BYTE pt[BLOCKSIZE/8], ct[BLOCKSIZE/8], ib[BLOCKSIZE/8];
  BYTE cv[BLOCKSIZE/8], iv[BLOCKSIZE/8], ob[BLOCKSIZE/8];
  cipherInstance ci;

  /* choose an initial value */
  for (k=0; k < BLOCKSIZE/8; ++k)
    iv[k] = 0x0;

  K = (char *) malloc (2*b);

  /* set the plaintext to all 0's */
  for (k=0; k<BLOCKSIZE/8; ++k)
    ct[k] = 0;

  /* set the key to all 0's */
  memset (K, '0', 2*b);
  
  fprintf (fp, "==========\n\n");
  fprintf (fp, "KEYSIZE=%d\n\n", 8*b);

  for (i=0; i < 400; ++i) {

    if (i==0) {
      for (k=0; k < BLOCKSIZE/8; ++k)
        cv[k] = iv[k];
    }

    fprintf (fp, "I=%d\n",i);
    fprintf (fp, "KEY=");
    outputKey (fp, K, 2*b);
    fprintf (fp, "\n");
    fprintf (fp, "IV=");
    outputBlock (fp, cv);
    fprintf (fp, "\n");
    fprintf (fp, "CT=");
    outputBlock (fp, ct);
    fprintf (fp, "\n");

    makeKey (&S, DIR_DECRYPT, b*8, K);
    cipherInit (&ci, MODE_ECB, "");

    for (j = 0; j < 10000; ++j) {
      for (k=0; k < BLOCKSIZE/8; ++k)
        ib[k] = ct[k];

      blockDecrypt (&ci, &S, ib, 128, ob);

      for (k=0; k < BLOCKSIZE/8; ++k)
        pt[k] = (BYTE) (ob[k] ^ cv[k]);

      for (k=0; k < BLOCKSIZE/8; ++k)
        cv[k] = ct[k];

      /* cv holds the ciphertext from the previous round */
      for (k=0; k < BLOCKSIZE/8; ++k)
        ct[k] = pt[k];
    }

    fprintf (fp, "PT=");
    outputBlock (fp, pt);
    fprintf (fp, "\n\n");

    FormNewKey (K, b, cv, pt);

  }

  free (K);

}







