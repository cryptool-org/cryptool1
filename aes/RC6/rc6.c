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

/* This file contains an optimized implementation of RC6 in C. */




#include <string.h>


#include "RC6.h"


/* Define some rotation macros */

/* Left- and right-rotation with a "variable" 32.  When the shift count
 * is not a constant, these seem to work faster than the macros below.
 * Make sure the value of the variable thirtytwo is set to a multiple of
 * 32 before using them!  These macros assume Intel-style handling of
 * shifts: when shifting a [32-bit] dword, the shift count is treated as
 * a number modulo 32. */
#define ROTL(x,count) \
  (((x) >> (thirtytwo-(count))) | ((x) << (count)))

#define ROTR(x,count) \
  (((x) << (thirtytwo-(count))) | ((x) >> (count)))



/* Left- and right-rotation with a "constant" 32.  These macros assume
 * Intel-style handling of shifts: when shifting a dword, the shift
 * count is treated as a number modulo 32. */
#define CONST_ROTL(x,count) \
  (((x) >> (32-(count))) | ((x) << (count)))

#define CONST_ROTR(x,count) \
  (((x) << (32-(count))) | ((x) >> (count)))



/* A table of values and macro for converting an ASCII hexadecimal digit
 * to a number. */
static const unsigned short digitValue[256] = {
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007,
  0x0008, 0x0009, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
  0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff
};

#define ConvertDigitToNumber(c) \
  (digitValue[(c)])



/*
 * Rc6ComputeKeySchedule() computes a key schedule from a variable-length
 * key.  It does *not* properly test the length of the key in advance, so
 * a key passed to it should not have an out-of-range length.  Valid key
 * lengths are 0-255 bytes.
 *
 * Rc6ComputeKeySchedule() places the schedule it computes in an array
 * of 2+2*ROUNDS+2 = 44 dwords specified by a pointer, S, supplied as input.
 *
 * This function should really be have static linkage, except that we
 * may use it to get some better (more realistic) timing figures on key
 * schedule setup than are available through the NIST API.  This is
 * because the NIST C API forces one to supply keys as ASCII material.
 */
void Rc6ComputeKeySchedule(BYTE* key, int keyLengthInBytes,
                           unsigned long* S)
{
  unsigned long L[(255+4-1)/4];
  int count;
  unsigned long i,j;
  unsigned long A,B;
  unsigned long thirtytwo = 32;
  static const unsigned char nextKeyScheduleDword[] = {
     1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,  0
  };

  unsigned char nextKeyDword[((255+4-1)/4)*4];

  static const unsigned long initialKeySchedule[] = {
    0xb7e15163, 0x5618cb1c,  /* Pseudo-round #0 */
    0xf45044d5, 0x9287be8e,  /* Round #1 */
    0x30bf3847, 0xcef6b200,  /* Round #2 */
    0x6d2e2bb9, 0x0b65a572,  /* Round #3 */
    0xa99d1f2b, 0x47d498e4,  /* Round #4 */
    0xe60c129d, 0x84438c56,  /* Round #5 */
    0x227b060f, 0xc0b27fc8,  /* Round #6 */
    0x5ee9f981, 0xfd21733a,  /* Round #7 */
    0x9b58ecf3, 0x399066ac,  /* Round #8 */
    0xd7c7e065, 0x75ff5a1e,  /* Round #9 */
    0x1436d3d7, 0xb26e4d90,  /* Round #10 */
    0x50a5c749, 0xeedd4102,  /* Round #11 */
    0x8d14babb, 0x2b4c3474,  /* Round #12 */
    0xc983ae2d, 0x67bb27e6,  /* Round #13 */
    0x05f2a19f, 0xa42a1b58,  /* Round #14 */
    0x42619511, 0xe0990eca,  /* Round #15 */
    0x7ed08883, 0x1d08023c,  /* Round #16 */
    0xbb3f7bf5, 0x5976f5ae,  /* Round #17 */
    0xf7ae6f67, 0x95e5e920,  /* Round #18 */
    0x341d62d9, 0xd254dc92,  /* Round #19 */
    0x708c564b, 0x0ec3d004,  /* Round #20 */
    0xacfb49bd, 0x4b32c376   /* Pseudo-round #21 */
  };

  /* Compute number of dwords taken up by key */
  unsigned long c = ((keyLengthInBytes+4-1) >> 2)
                   +((((unsigned long) keyLengthInBytes)-1) >> 31);


  /* Set up table of indices of next element in original key array.
   * We'll make use of the fact that Intels are little-endian. */
  *((unsigned long*) &(nextKeyDword[0])) = 0x04030201;
  *((unsigned long*) &(nextKeyDword[4])) = 0x08070605;

  count = 4;
#pragma warning( disable : 4018)
  while ((count += 4) < c) {
    *((unsigned long*) &(nextKeyDword[count])) =
      (count*0x01010101UL)+0x04030201;
  }

  nextKeyDword[c-1] = 0;


  /* Zero out last element of array of key dwords */
  L[c-1] = 0;


  /* Load all the key bytes into the array of key dwords.  This method
   * of performing this task requires a little-endian CPU. */
  memcpy((void*) L, (void*) key, keyLengthInBytes);


  /* Initialize key schedule array */
  memcpy((void*) S, (void*) initialKeySchedule, 4*(2+2*ROUNDS+2));


  count = ((c <= (2+2*ROUNDS+2)) ? (2+2*ROUNDS+2) : c);
  A = B = i = j = 0;

  /* Mix the key into the key schedule array */
  do {
    unsigned long sum;

    S[i] += A+B;
    A = S[i] = CONST_ROTL(S[i], 3);
    i = nextKeyScheduleDword[i];

    sum = A+B;
    L[j] += sum;
    B = L[j] = ROTL(L[j], sum);
    j = nextKeyDword[j];


    S[i] += A+B;
    A = S[i] = CONST_ROTL(S[i], 3);
    i = nextKeyScheduleDword[i];

    sum = A+B;
    L[j] += sum;
    B = L[j] = ROTL(L[j], sum);
    j = nextKeyDword[j];


    S[i] += A+B;
    A = S[i] = CONST_ROTL(S[i], 3);
    i = nextKeyScheduleDword[i];

    sum = A+B;
    L[j] += sum;
    B = L[j] = ROTL(L[j], sum);
    j = nextKeyDword[j];
  } while (--count > 0);
}



/* The ENCRYPT_ROUND macro performs a single round of RC6 encryption. */
#define ENCRYPT_ROUND(SSS,offset,AAA,BBB,CCC,DDD) \
  do { \
    t = (BBB+BBB+1)*BBB; \
    u = (DDD+DDD+1)*DDD; \
    t = CONST_ROTL(t, 5); \
    u = CONST_ROTL(u, 5); \
    \
    AAA ^= t; \
    CCC ^= u; \
    AAA = ROTL(AAA, u)+SSS[offset]; \
    CCC = ROTL(CCC, t)+SSS[offset+1]; \
  } while (0)



/* The ENCRYPT_MIDDLE macro performs rounds 2-18 of an RC6 encryption. */
#define ENCRYPT_MIDDLE(SS,AA,BB,CC,DD) \
  do { \
    ENCRYPT_ROUND(SS, 4, BB, CC, DD, AA); \
    ENCRYPT_ROUND(SS, 6, CC, DD, AA, BB); \
    ENCRYPT_ROUND(SS, 8, DD, AA, BB, CC); \
    ENCRYPT_ROUND(SS, 10, AA, BB, CC, DD); \
    ENCRYPT_ROUND(SS, 12, BB, CC, DD, AA); \
    ENCRYPT_ROUND(SS, 14, CC, DD, AA, BB); \
    ENCRYPT_ROUND(SS, 16, DD, AA, BB, CC); \
    ENCRYPT_ROUND(SS, 18, AA, BB, CC, DD); \
    ENCRYPT_ROUND(SS, 20, BB, CC, DD, AA); \
    ENCRYPT_ROUND(SS, 22, CC, DD, AA, BB); \
    ENCRYPT_ROUND(SS, 24, DD, AA, BB, CC); \
    ENCRYPT_ROUND(SS, 26, AA, BB, CC, DD); \
    ENCRYPT_ROUND(SS, 28, BB, CC, DD, AA); \
    ENCRYPT_ROUND(SS, 30, CC, DD, AA, BB); \
    ENCRYPT_ROUND(SS, 32, DD, AA, BB, CC); \
    ENCRYPT_ROUND(SS, 34, AA, BB, CC, DD); \
    ENCRYPT_ROUND(SS, 36, BB, CC, DD, AA); \
  } while (0)



/*
 * Rc6EncryptEcb() encrypts a specified number of blocks in ECB mode.
 */
static void Rc6EncryptEcb(unsigned long* keySchedule, int numberOfBlocks,
                          unsigned long* plaintext, unsigned long* ciphertext)
{
  unsigned long thirtytwo = 32;
  unsigned long S[2+2*ROUNDS+2];


  if (numberOfBlocks == 0)
    return;


  /* Let's put our key schedule conveniently in this stack frame */
  memcpy((void*) S, (void*) keySchedule, 4*(2+2*ROUNDS+2));


  do {
    unsigned long A, B, C, D;
    unsigned long t,u;

    /* Perform pseudo-round #0 and round #1 */
    B = plaintext[1]+S[0];
    D = plaintext[3]+S[1];

    t = (B+B+1)*B;
    u = (D+D+1)*D;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    A = plaintext[0] ^ t;
    A = ROTL(A, u)+S[2];
    C = plaintext[2] ^ u;
    C = ROTL(C, t)+S[3];


    /* Perform rounds #2-18 */
    ENCRYPT_MIDDLE(S, A, B, C, D);


    /* Perform round #19 */
    ENCRYPT_ROUND(S, 38, C, D, A, B);


    /* Perform round #20 and pseudo-round #21 */
    t = (A+A+1)*A;
    u = (C+C+1)*C;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    D ^= t;
    ciphertext[0] = A+S[42];
    ciphertext[3] = ROTL(D, u)+S[40];
    B ^= u;
    ciphertext[2] = C+S[43];
    ciphertext[1] = ROTL(B, t)+S[41];


    /* Update text pointers */
    plaintext += 4;
    ciphertext += 4;

  } while (--numberOfBlocks > 0);
}



/*
 * Rc6EncryptCbc() encrypts a specified number of blocks in CBC mode.
 * In the process, it alters the 16-byte value pointed to by ivBytes.
 */
static void Rc6EncryptCbc(unsigned long* keySchedule, int numberOfBlocks,
                          unsigned long* ivDwords,
                          unsigned long* plaintext, unsigned long* ciphertext)
{
  unsigned long thirtytwo = 32;
  unsigned long IV[4];
  unsigned long S[2+2*ROUNDS+2];


  if (numberOfBlocks == 0)
    return;


  /* Let's put our IV and key schedule conveniently in this stack frame */
  IV[0] = ivDwords[0];
  IV[1] = ivDwords[1];
  IV[2] = ivDwords[2];
  IV[3] = ivDwords[3];
  memcpy((void*) S, (void*) keySchedule, 4*(2+2*ROUNDS+2));


  do {
    unsigned long A, B, C, D;
    unsigned long t,u;

    /* XOR in IV and perform pseudo-round #0 and round #1 */
    B = (plaintext[1] ^ IV[1])+S[0];
    D = (plaintext[3] ^ IV[3])+S[1];

    t = (B+B+1)*B;
    u = (D+D+1)*D;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    A = (plaintext[0] ^ IV[0]) ^ t;
    A = ROTL(A, u)+S[2];
    C = (plaintext[2] ^ IV[2]) ^ u;
    C = ROTL(C, t)+S[3];


    /* Perform rounds #2-18 */
    ENCRYPT_MIDDLE(S, A, B, C, D);


    /* Perform round #19 */
    ENCRYPT_ROUND(S, 38, C, D, A, B);


    /* Perform round #20 and pseudo-round #17 and save IV */
    t = (A+A+1)*A;
    u = (C+C+1)*C;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    D ^= t;
    IV[0] = ciphertext[0] = A+S[42];
    IV[3] = ciphertext[3] = ROTL(D, u)+S[40];
    B ^= u;
    IV[2] = ciphertext[2] = C+S[43];
    IV[1] = ciphertext[1] = ROTL(B, t)+S[41];


    /* Update text pointers */
    plaintext += 4;
    ciphertext += 4;

  } while (--numberOfBlocks > 0);

  /* Save IV for next call */
  ivDwords[0] = IV[0];
  ivDwords[1] = IV[1];
  ivDwords[2] = IV[2];
  ivDwords[3] = IV[3];
}



/* The DECRYPT_ROUND macro performs a single round of RC6 decryption. */
#define DECRYPT_ROUND(SSS,offset,AAA,BBB,CCC,DDD) \
  do { \
    t = (BBB+BBB+1)*BBB; \
    u = (DDD+DDD+1)*DDD; \
    t = CONST_ROTL(t, 5); \
    u = CONST_ROTL(u, 5); \
    \
    AAA -= SSS[offset]; \
    CCC -= SSS[offset+1]; \
    AAA = ROTR(AAA, u)^t; \
    CCC = ROTR(CCC, t)^u; \
  } while (0)



/* The DECRYPT_MIDDLE macro undoes rounds 19-2 of an RC6 encryption. */
#define DECRYPT_MIDDLE(SS,AA,BB,CC,DD) \
  do { \
    DECRYPT_ROUND(SS, 38, CC, DD, AA, BB); \
    DECRYPT_ROUND(SS, 36, BB, CC, DD, AA); \
    DECRYPT_ROUND(SS, 34, AA, BB, CC, DD); \
    DECRYPT_ROUND(SS, 32, DD, AA, BB, CC); \
    DECRYPT_ROUND(SS, 30, CC, DD, AA, BB); \
    DECRYPT_ROUND(SS, 28, BB, CC, DD, AA); \
    DECRYPT_ROUND(SS, 26, AA, BB, CC, DD); \
    DECRYPT_ROUND(SS, 24, DD, AA, BB, CC); \
    DECRYPT_ROUND(SS, 22, CC, DD, AA, BB); \
    DECRYPT_ROUND(SS, 20, BB, CC, DD, AA); \
    DECRYPT_ROUND(SS, 18, AA, BB, CC, DD); \
    DECRYPT_ROUND(SS, 16, DD, AA, BB, CC); \
    DECRYPT_ROUND(SS, 14, CC, DD, AA, BB); \
    DECRYPT_ROUND(SS, 12, BB, CC, DD, AA); \
    DECRYPT_ROUND(SS, 10, AA, BB, CC, DD); \
    DECRYPT_ROUND(SS, 8, DD, AA, BB, CC); \
    DECRYPT_ROUND(SS, 6, CC, DD, AA, BB); \
    DECRYPT_ROUND(SS, 4, BB, CC, DD, AA); \
  } while (0)



/*
 * Rc6DecryptEcb() decrypts a specified number of blocks in ECB mode.
 */
static void Rc6DecryptEcb(unsigned long* keySchedule, int numberOfBlocks,
                          unsigned long* ciphertext, unsigned long* plaintext)
{
  unsigned long thirtytwo = 32;
  unsigned long S[2+2*ROUNDS+2];


  if (numberOfBlocks == 0)
    return;


  /* Let's put our key schedule conveniently in this stack frame */
  memcpy((void*) S, (void*) keySchedule, 4*(2+2*ROUNDS+2));


  do {
    unsigned long A, B, C, D;
    unsigned long t,u;

    /* Undo pseudo-round #21 and round #20 */
    A = ciphertext[0]-S[42];
    C = ciphertext[2]-S[43];

    t = (A+A+1)*A;
    u = (C+C+1)*C;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    D = ciphertext[3]-S[40];
    B = ciphertext[1]-S[41];
    D = ROTR(D, u) ^ t;
    B = ROTR(B, t) ^ u;


    /* Undo rounds #19-2 */
    DECRYPT_MIDDLE(S, A, B, C, D);


    /* Undo round #1 and pseudo-round #0 */
    t = (B+B+1)*B;
    u = (D+D+1)*D;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    A -= S[2];
    C -= S[3];
    plaintext[0] = ROTR(A, u) ^ t;
    plaintext[2] = ROTR(C, t) ^ u;
    plaintext[1] = B-S[0];
    plaintext[3] = D-S[1];


    /* Update text pointers */
    ciphertext += 4;
    plaintext += 4;

  } while (--numberOfBlocks > 0);
}



/*
 * Rc6DecryptCbc() decrypts a specified number of blocks in CBC mode.
 * In the process, it alters the 16-byte value pointed to by ivBytes.
 */
static void Rc6DecryptCbc(unsigned long* keySchedule, int numberOfBlocks,
                          unsigned long* ivDwords,
                          unsigned long* ciphertext, unsigned long* plaintext)
{
  unsigned long thirtytwo = 32;
  unsigned long IV[8];
  unsigned long S[2+2*ROUNDS+2];
  unsigned long thisIv = 0;
  unsigned long nextIv;


  if (numberOfBlocks == 0)
    return;


  /* Let's put our IV and key schedule conveniently in this stack frame */
  IV[0] = ivDwords[0];
  IV[1] = ivDwords[1];
  IV[2] = ivDwords[2];
  IV[3] = ivDwords[3];
  memcpy((void*) S, (void*) keySchedule, 4*(2+2*ROUNDS+2));


  do {
    unsigned long A, B, C, D;
    unsigned long t,u;

    /* Save ciphertext as future IV */
    nextIv = thisIv ^ 4;
    IV[nextIv] = ciphertext[0];
    IV[nextIv+1] = ciphertext[1];
    IV[nextIv+2] = ciphertext[2];
    IV[nextIv+3] = ciphertext[3];


    /* Undo pseudo-round #21 and round #20 */
    A = ciphertext[0]-S[42];
    C = ciphertext[2]-S[43];

    t = (A+A+1)*A;
    u = (C+C+1)*C;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    D = ciphertext[3]-S[40];
    B = ciphertext[1]-S[41];
    D = ROTR(D, u) ^ t;
    B = ROTR(B, t) ^ u;


    /* Undo rounds #19-2 */
    DECRYPT_MIDDLE(S, A, B, C, D);


    /* Undo round #1 and pseudo-round #0 */
    t = (B+B+1)*B;
    u = (D+D+1)*D;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    A -= S[2];
    C -= S[3];
    plaintext[0] = (ROTR(A, u) ^ t) ^ IV[thisIv];
    plaintext[2] = (ROTR(C, t) ^ u) ^ IV[thisIv+2];
    plaintext[1] = (B-S[0]) ^ IV[thisIv+1];
    plaintext[3] = (D-S[1]) ^ IV[thisIv+3];


    /* Update text pointers and IV location */
    plaintext += 4;
    ciphertext += 4;

    thisIv = nextIv;
  } while (--numberOfBlocks > 0);


  /* Save IV for future calls */
  ivDwords[0] = IV[thisIv];
  ivDwords[1] = IV[thisIv+1];
  ivDwords[2] = IV[thisIv+2];
  ivDwords[3] = IV[thisIv+3];
}



/*
 * Rc6Cfb1() encrypts or decrypts a specified number of bits (*not* blocks)
 * in 1-bit CFB mode.  In the process, it alters the 16-byte value pointed
 * to by ivDwords.
 *
 * If the argument encryptOrDecrypt has bit 7 set to 1, then encryption
 * will be performed.  If that bit has the value 0, then decryption will
 * be performed.
 */
static void Rc6Cfb1(unsigned long* keySchedule, int numberOfBits,
                    unsigned long* ivDwords,
                    BYTE* in, BYTE* out, unsigned int encryptOrDecrypt)
{
  unsigned long thirtytwo = 32;
  unsigned long IV[4];
  unsigned long S[38];
  int bitIndex = 0;
  unsigned long s39PlusS42 = keySchedule[39]+keySchedule[42];


  if (numberOfBits == 0)
    return;


  /* Adjust text pointers for looping */
  in--;
  out--;


  /* Let's put our IV and the bulk of our key schedule conveniently in
   *this stack frame */
  IV[0] = ivDwords[0];
  IV[1] = ivDwords[1];
  IV[2] = ivDwords[2];
  IV[3] = ivDwords[3];
  memcpy((void*) S, (void*) keySchedule, 4*38);


  do {
    unsigned long A, B, C, D;
    unsigned long t, u;
    unsigned long inDword, outDword;
    unsigned long feedback;


    if ((bitIndex & 0x7) == 0) {
      inDword = *(++in);
      ++out;
    }


    /* Perform pseudo-round #0 and round #1 */
    B = IV[1]+S[0];
    D = IV[3]+S[1];

    t = (B+B+1)*B;
    u = (D+D+1)*D;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    A = IV[0] ^ t;
    A = ROTL(A, u)+S[2];
    C = IV[2] ^ u;
    C = ROTL(C, t)+S[3];


    /* Perform rounds #2-18 */
    ENCRYPT_MIDDLE(S, A, B, C, D);


    /* Perform what we need of rounds #19-20 and pseudo-round #21.
     * We'll end up with the masking bit from the encrypted IV in
     * bit 7 of A. */
    t = (D+D+1)*D;
    u = (B+B+1)*B;
    t = CONST_ROTL(t, 5);
    u = CONST_ROTL(u, 5);

    A ^= u;
    A = ROTL(A, t)+s39PlusS42;


    /* Update output byte */
    outDword = inDword ^ A;
    (*out) = (BYTE) ((*out << 1) | (((BYTE) outDword) >> 7));


    /* Get feedback bit in bit position 7 */
    feedback = inDword ^ (A & encryptOrDecrypt);


    /* Shift next input bit into place */
    inDword <<= 1;


    /* Left-shift the whole IV by 1 bit and add feedback bit */
    IV[0] = (2*(IV[0] & 0x7f7f7f7f))
          | ((IV[0] & 0x80808000) >> 15)
          | ((IV[1] & 0x80) << 17);
    IV[1] = (2*(IV[1] & 0x7f7f7f7f))
          | ((IV[1] & 0x80808000) >> 15)
          | ((IV[2] & 0x80) << 17);
    IV[2] = (2*(IV[2] & 0x7f7f7f7f))
          | ((IV[2] & 0x80808000) >> 15)
          | ((IV[3] & 0x80) << 17);
    IV[3] = (2*(IV[3] & 0x7f7f7f7f))
          | ((IV[3] & 0x80808000) >> 15)
          | ((feedback & 0x80) << 17);
  } while (++bitIndex < numberOfBits);


  /* Adjust the bit-positioning of the final block of output */
  *out <<= ((-numberOfBits) & 0x7);


  /* Save IV for future calls */
  ivDwords[0] = IV[0];
  ivDwords[1] = IV[1];
  ivDwords[2] = IV[2];
  ivDwords[3] = IV[3];
}




/*
 * Below, we implement all the functions that have actually been specified
 * by NIST for the C API that they first announced on 1998 April 9.
 */



/*
 * makeKey() initializes a keyInstance.
 */
int makeKeyRC6(keyInstanceRC6 * key, BYTE direction, int keyLen, char* keyMaterial)
{
  BYTE keyBytes[255];
  short keyByte;
  short hexProblem = 0;
  int keyLengthInBytes = keyLen >> 3;
  int i;


  if ((direction != DIR_ENCRYPT) && (direction != DIR_DECRYPT))
    return BAD_KEY_DIR;
  key -> direction = direction;


  /* Deal with the key length.  RC6 can use keys of length 0-255 bytes
   * (0-2040 bits, in multiples of 8). */
  if ((keyLen < 0) || (keyLen > 2040) || ((keyLen & 0x7) != 0))
    return BAD_KEY_MAT;


  /* Get key as a sequence of bytes */
  for (i = keyLengthInBytes; --i >= 0; ) {
    keyBytes[i] = (BYTE) (
      keyByte = (short) (
        ((ConvertDigitToNumber((BYTE) keyMaterial[i+i]) << 4)
       | (ConvertDigitToNumber((BYTE) keyMaterial[i+i+1])))));
    hexProblem |= keyByte;
  }


  /* The ConvertDigitToNumber() macro has been designed so that the
   * following test will correctly determine if the supplied ASCII key
   * was not a valid hexadecimal string. */
  if (hexProblem & 0xff00)
    return BAD_KEY_MAT;


  /* Copy ASCII key */
  memcpy(key -> keyMaterial, keyMaterial, keyLengthInBytes << 1);
  key -> keyLen = keyLen;


  Rc6ComputeKeySchedule(keyBytes, keyLengthInBytes, key -> S);


  return TRUE;
}



/*
 * cipherInit() initializes a cipherInstance.
 */
int cipherInitRC6(cipherInstanceRC6* cipher, BYTE mode, char* IV)
{
  short ivByte;
  short hexProblem = 0;
  int i;


  if ((mode != MODE_ECB) && (mode != MODE_CBC) && (mode != MODE_CFB1))
    return BAD_CIPHER_MODE;
  cipher -> mode = mode;


  /* Get IV, if appropriate */
  if (IV != NULL) {
    for (i = 16; --i >= 0; ) {
      ((BYTE*) (cipher -> IV))[i] = (BYTE) (
        ivByte = (short) (
          ((ConvertDigitToNumber((BYTE) IV[i+i]) << 4)
         | (ConvertDigitToNumber((BYTE) IV[i+i+1])))));
      hexProblem |= ivByte;
    }


    /* The ConvertDigitToNumber() macro has been designed so that the
     * following test will correctly determine if the supplied ASCII IV
     * was not a valid hexadecimal string. */
    if (hexProblem & 0xff00)
      return BAD_IV_MAT;
  }


  return TRUE;
}



/*
 * blockEncrypt() encrypts some plaintext.
 */
int blockEncryptRC6(cipherInstanceRC6 *cipher, keyInstanceRC6 *key,
                 BYTE *input, int inputLen, BYTE *outBuffer)
{
  if (key -> direction != DIR_ENCRYPT)
    return BAD_KEY_MAT;
    /* The API document says that BAD_KEY_MATERIAL should be returned
     * in this situation; however, there is no such error code.  It
     * appears that BAD_KEY_MAT (maybe BAD_KEY_DIR?) is appropriate
     * here. */


  switch(cipher -> mode) {

    case MODE_ECB: {
      int numberOfBlocks = inputLen >> 7;

      Rc6EncryptEcb(key -> S, numberOfBlocks,
                    (unsigned long*) input, (unsigned long*) outBuffer);

      /* Note that we completely ignore partial blocks of plaintext */
      return (numberOfBlocks << 7);

      /* No fall-through to next case possible */
    }


    case MODE_CBC: {
      int numberOfBlocks = inputLen >> 7;

      Rc6EncryptCbc(key -> S, numberOfBlocks, (unsigned long*) cipher -> IV,
                    (unsigned long*) input, (unsigned long*) outBuffer);

      /* Note that we completely ignore partial blocks of plaintext */
      return (numberOfBlocks << 7);

      /* No fall-through to next case possible */
    }


    case MODE_CFB1: {
      /* The 0x80 argument indicates that the operation is encryption */
      Rc6Cfb1(key -> S, inputLen, (unsigned long*) cipher -> IV,
              input, outBuffer, 0x80);

      return inputLen;

      /* No fall-through to next case possible */
    }


    default: {
      return BAD_CIPHER_STATE;
    }
  }
}



/*
 * blockDecrypt() decrypts some ciphertext.
 */
int blockDecryptRC6(cipherInstanceRC6 *cipher, keyInstanceRC6 *key,
                 BYTE *input, int inputLen, BYTE *outBuffer)
{
  if (key -> direction != DIR_DECRYPT)
    return BAD_KEY_MAT;
    /* The API document says that BAD_KEY_MATERIAL should be returned
     * in this situation; however, there is no such error code.  It
     * appears that BAD_KEY_MAT (maybe BAD_KEY_DIR?) is appropriate
     * here. */


  switch(cipher -> mode) {

    case MODE_ECB: {
      int numberOfBlocks = inputLen >> 7;

      Rc6DecryptEcb(key -> S, numberOfBlocks,
                    (unsigned long*) input, (unsigned long*) outBuffer);

      /* Note that we completely ignore partial blocks of ciphertext */
      return (numberOfBlocks << 7);

      /* No fall-through to next case possible */
    }


    case MODE_CBC: {
      int numberOfBlocks = inputLen >> 7;

      Rc6DecryptCbc(key -> S, numberOfBlocks, (unsigned long*) cipher -> IV,
                    (unsigned long*) input, (unsigned long*) outBuffer);

      /* Note that we completely ignore partial blocks of ciphertext */
      return (numberOfBlocks << 7);

      /* No fall-through to next case possible */
    }


    case MODE_CFB1: {
      /* The 0x00 argument indicates that the operation is decryption */
      Rc6Cfb1(key -> S, inputLen, (unsigned long*) cipher -> IV,
        input, outBuffer, 0x00);

      return inputLen;

      /* No fall-through to next case possible */
    }


    default: {
      return BAD_CIPHER_STATE;
    }
  }
}



