/* tests.c reference code - copyright(c) 1998 IBM 
 *
 * This code implements basic tests, as well as the NIST defined
 * KAT and MCT tests for the mars cipher.
 */

/* Revisions log:
 *
 *   Apr 1998, Dave Safford - created
 */
 
/* Compilation using pcg's version of gcc:
 *    gcc -Wall -pedantic -O6 -fomit-frame-pointer -mcpu=pentiumpro 
 *        -o tests -DKAT tests.c mars.c
 * 
 * Compilation using xlc on AIX:
 *    xlc -O3 -o tests -DKAT tests.c mars.c
 *
 * Compilation using Borland C++ 5.0 from a DOS command line:
 *    bcc32 -Oi -6 -v -A -a4 -O2 -DKAT tests.c mars.c
 *
 * Useful compilation defines:
 *    DIEHARD    - add code to write out diehard data for encrypt
 *    IVT        - add code to write out NIST intermediate values test
 *    KAT        - add code to write out NIST KAT data files
 *    MCT        - add code to write out NIST MCT data files
 * Note: for IVT to work, the mars code must also be compiled with -DIVT,
 * and doing so slows down encryption/decryption significantly.
 */
  
#include "aes.h"
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

/*************************************************************************
 *
 *   test main() for the high and low level routines 
 *
 ************************************************************************/

#ifdef IVT
#ifndef TESTS
#define TESTS
#endif
#endif
#ifdef KAT
#ifndef TESTS
#define TESTS
#endif
#endif
#ifdef MCT
#ifndef TESTS
#define TESTS
#endif
#endif

int main()
{
    keyInstance keyin;
    cipherInstance encipher,decipher;
    WORD pt_in[NUM_DATA], ct[NUM_DATA], pt_out[NUM_DATA];
    WORD key[EKEY_WORDS];
    WORD e[EKEY_WORDS];
    BYTE ctbuf[32], outbuf[32];
    clock_t clock1,clock2;
    float ttime1;
    int i;
#   ifdef DIEHARD
        int fd;
#   endif
#   ifdef IVT
        extern int ivt_debug;
        extern FILE *ivt_fp;
        extern int ivt_l;
#   endif 
#ifdef MCT
        extern BYTE hex[];
        BYTE ivbuf[16];
#endif
#ifdef KAT
        WORD S[16] = {0xf20b4862, 0xcd79bde4, 0x498f7a5b, 0xcfc31f4c, 
                      0x354d61f3, 0x2e31fa47, 0x8c18da7f, 0xe14e831d, 
                      0x5de9d8d6, 0x68843750, 0xa2e71b63, 0xeff8e372,
                      0x8792349d, 0x8a58369a, 0x2e9382ba, 0xa72b988f}; 
#endif
#   ifdef TESTS
        FILE *fp;
        BYTE ptbuf[16];
        char akey[MAX_KEY_SIZE+1];
        char tohex[16] = { '0','1','2','3','4','5','6','7','8',
                           '9','A','B','C','D','E','F' };
        int j,k;
#   endif /* TESTS */

    /* do simple CBC encrypt/decrypt test for the high level stuff first */
    makeKey(&keyin,DIR_ENCRYPT,128,"000102030405060708090a0b0c0d0e0f");
    cipherInit(&encipher,MODE_CBC,"00000000000000000000000000000000");
    cipherInit(&decipher,MODE_CBC,"00000000000000000000000000000000");
    blockEncrypt(&encipher, &keyin, 
                 (BYTE *)"This is a two block test of CBC",256, ctbuf);
    blockDecrypt(&decipher, &keyin, ctbuf, 256, outbuf);
    printf("\nHigh level output test: \n %s\n", (char *)outbuf); 

    /* try the CFB-1 mode */
    makeKey(&keyin,DIR_ENCRYPT,128,"000102030405060708090a0b0c0d0e0f");
    cipherInit(&encipher,MODE_CFB1,"00000000000000000000000000000000");
    cipherInit(&decipher,MODE_CFB1,"00000000000000000000000000000000");
    for(i=0;i<8;i++){
        outbuf[0] = (i&1);
        blockEncrypt(&encipher, &keyin, outbuf, 1, ctbuf);
        blockDecrypt(&decipher, &keyin, ctbuf, 1, outbuf);
        printf(" CFB-1 bit %d bitin %d ctbit %d bitout %d \n",
                i,i&1,ctbuf[0],outbuf[0]);
    }
    printf("\n");
    
    /* do simple encrypt/decrypt test for the low level stuff */
    printf("Low level block tests:\n");
    for (i=0;i<4;i++) {
	pt_in[i] = 0x01020304;
	key[i] = 0x01020304;
    }
    (void)mars_setup(4,key,e);
    mars_encrypt(pt_in,ct,e);
    mars_decrypt(ct,pt_out,e);
    printf(" in     %.8lX %.8lX %.8lX %.8lX\n",
        pt_in[0], pt_in[1], pt_in[2], pt_in[3]);
    printf(" cipher %.8lX %.8lX %.8lX %.8lX\n",
        ct[0], ct[1], ct[2], ct[3]);
    printf(" out    %.8lX %.8lX %.8lX %.8lX\n",
        pt_out[0], pt_out[1], pt_out[2], pt_out[3]);
    if (pt_in[0]!=pt_out[0] || pt_in[1]!=pt_out[1] ||
        pt_in[2]!=pt_out[2] || pt_in[3]!=pt_out[3])
        printf("Decryption Error!\n");
    fflush(stdout);

    /* Do low level timing tests */
    printf("\nLow level block timing tests:\n");
    clock1 = clock();
    for (i=1;i<40000;i++) {
        (void)mars_setup(4,key,e);
	key[0]++;
    }
    clock2 = clock();
    ttime1 = (clock2 - clock1)/(double)CLOCKS_PER_SEC;
    printf ("\nTime for 40K 128 bit setups:  %f \n", ttime1);
    printf (" %fMbit/sec\n",5.12/ttime1);

    (void)mars_setup(4,key,e); 
    clock1 = clock();
    for (i=1;i<400000;i++)
        mars_encrypt(pt_in,ct,e);
    clock2 = clock();
    ttime1 = (clock2 - clock1)/(float)CLOCKS_PER_SEC;
    printf ("\nTime for encrypting 400K 128 bit blocks:  %f \n", ttime1);
    printf (" %fMbit/sec\n",51.2/ttime1);

    clock1 = clock();
    for (i=1;i<400000;i++)
        mars_decrypt(pt_in,ct,e);
    clock2 = clock();
    ttime1 = (clock2 - clock1)/(float)CLOCKS_PER_SEC;
    printf ("\nTime for decrypting 400K 128 bit blocks:  %f \n", ttime1);
    printf (" %fMbit/sec\n",51.2/ttime1);

#ifdef DIEHARD
    /* write file for diehard randomness stress tests */
    fd = creat("mars.dat",S_IRUSR|S_IRGRP|S_IROTH);
    (void)mars_setup(4,key,e); 
    for (i=0;i<1024*1024;i++) {
        pt_in[0] = i;
        mars_encrypt(pt_in, ct, e);
        write(fd,(unsigned char *)ct, 16);
    }
    close(fd);
#endif /* DIEHARD */

#ifdef IVT
    /*************************************************************************
     *
     * Intermediate Value Test -> ecb_ivt.txt 
     *
     ************************************************************************/
    fp = fopen("ecb_ivt.txt","w");
    ivt_fp = fp;
    ivt_l = 0;
    ivt_debug=1; 
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"ecb_ivt.txt\"\n\n");
    fprintf(fp,"Electronic Codebook (ECB) Mode\n");
    fprintf(fp,"Intermediate Values Tests\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");
    /* the input plaintext and key are all zeros */
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    /* 128 bit keys */
    for(i=0;i<32;i++)
        akey[i] = '0';
    akey[32] = '\0';
    fprintf(fp,"\n\n==========\n\nEncryption: KEYSIZE=128\n\n");
    fprintf(fp,"KEY=%s\n",akey);
    fprintf(fp,"PT=00000000000000000000000000000000\n");
    makeKey(&keyin,DIR_ENCRYPT,128,akey);
    cipherInit(&encipher,MODE_ECB,NULL);
    cipherInit(&decipher,MODE_ECB,NULL);
    blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
    fprintf(fp,"CT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
    fprintf(fp,"\n\n==========\n\nDecryption: KEYSIZE=128\n\n");
    fprintf(fp,"KEY=%s\n",akey);
    fprintf(fp,"CT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
    ivt_l = 0;
    fprintf(fp,"\n");
    blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
    fprintf(fp,"PT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[outbuf[k]>>4],tohex[outbuf[k]&0x0f]); 
    /* 192 bit keys */
    for(i=0;i<48;i++)
        akey[i] = '0';
    akey[48] = '\0';
    fprintf(fp,"\n\n==========\n\nEncryption: KEYSIZE=192\n\n");
    fprintf(fp,"KEY=%s\n",akey);
    fprintf(fp,"PT=00000000000000000000000000000000\n");
    makeKey(&keyin,DIR_ENCRYPT,192,akey);
    cipherInit(&encipher,MODE_ECB,NULL);
    cipherInit(&decipher,MODE_ECB,NULL);
    ivt_l = 0;
    blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
    fprintf(fp,"CT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
    fprintf(fp,"\n\n==========\n\nDecryption: KEYSIZE=192\n\n");
    fprintf(fp,"KEY=%s\n",akey);
    fprintf(fp,"CT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
    ivt_l = 0;
    fprintf(fp,"\n");
    blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
    fprintf(fp,"PT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[outbuf[k]>>4],tohex[outbuf[k]&0x0f]); 
    /* 256 bit keys */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    fprintf(fp,"\n\n==========\n\nEncryption: KEYSIZE=256\n\n");
    fprintf(fp,"KEY=%s\n",akey);
    fprintf(fp,"PT=00000000000000000000000000000000\n");
    makeKey(&keyin,DIR_ENCRYPT,256,akey);
    cipherInit(&encipher,MODE_ECB,NULL);
    cipherInit(&decipher,MODE_ECB,NULL);
    ivt_l = 0;
    blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
    fprintf(fp,"CT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
    fprintf(fp,"\n\n==========\n\nDecryption: KEYSIZE=256\n\n");
    fprintf(fp,"KEY=%s\n",akey);
    fprintf(fp,"CT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
    ivt_l = 0;
    fprintf(fp,"\n");
    blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
    fprintf(fp,"PT=");
    for(k=0;k<16;k++)
        fprintf(fp,"%c%c",tohex[outbuf[k]>>4],tohex[outbuf[k]&0x0f]); 
    fprintf(fp,"\n");
    fclose(fp);
    ivt_debug=0;
    j = 0;  /* make Wall happy */
#endif /* IVT */

#ifdef KAT
    /*************************************************************************
     *
     * Variable Key KAT -> ecb_vk.txt 
     *
     ************************************************************************/
    fp = fopen("ecb_vk.txt","w");
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"ecb_vk.txt\"\n\n");
    fprintf(fp,"Electronic Codebook (ECB) Mode\n");
    fprintf(fp,"Variable Key Known Answer Tests\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");
    /* the input plaintext is all zeros */
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    /* 128 bit keys */
    akey[32] = '\0';
    fprintf(fp,"\n\n==========\n\nKEYSIZE=128\n\n");
    fprintf(fp,"PT=00000000000000000000000000000000");
    for(i=0;i<32;i++) {
        for(j=3;j>=0;j--){
            for (k=0;k<32;k++)
                akey[k] = '0';
            akey[i] = '0' + (1<<j); 
            makeKey(&keyin,DIR_ENCRYPT,128,akey);
            cipherInit(&encipher,MODE_ECB,NULL);
            cipherInit(&decipher,MODE_ECB,NULL);
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
            fprintf(fp,"\n\nI=%d\n",i*4+4-j);
            fprintf(fp,"KEY=%s\n",akey);
            fprintf(fp,"CT=");
            for(k=0;k<16;k++){
                if(outbuf[k] != 0)
                    fprintf(fp,"*decyrption error*\n");
                else
                    fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
            }
        }
    }
    /* 192 bit keys */
    akey[48] = '\0';
    fprintf(fp,"\n\n==========\n\nKEYSIZE=192\n\n");
    fprintf(fp,"PT=00000000000000000000000000000000");
    for(i=0;i<48;i++) {
        for(j=3;j>=0;j--){
            for (k=0;k<48;k++)
                akey[k] = '0';
            akey[i] = '0' + (1<<j); 
            makeKey(&keyin,DIR_ENCRYPT,192,akey);
            cipherInit(&encipher,MODE_ECB,NULL);
            cipherInit(&decipher,MODE_ECB,NULL);
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
            fprintf(fp,"\n\nI=%d\n",i*4+4-j);
            fprintf(fp,"KEY=%s\n",akey);
            fprintf(fp,"CT=");
            for(k=0;k<16;k++){
                if(outbuf[k] != 0)
                    fprintf(fp,"*decyrption error*\n");
                else
                    fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
            }
        }
    }
    /* 256 bit keys */
    akey[64] = '\0';
    fprintf(fp,"\n\n==========\n\nKEYSIZE=256\n\n");
    fprintf(fp,"PT=00000000000000000000000000000000");
    for(i=0;i<64;i++) {
        for(j=3;j>=0;j--){
            for (k=0;k<64;k++)
                akey[k] = '0';
            akey[i] = '0' + (1<<j); 
            makeKey(&keyin,DIR_ENCRYPT,256,akey);
            cipherInit(&encipher,MODE_ECB,NULL);
            cipherInit(&decipher,MODE_ECB,NULL);
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
            fprintf(fp,"\n\nI=%d\n",i*4+4-j);
            fprintf(fp,"KEY=%s\n",akey);
            fprintf(fp,"CT=");
            for(k=0;k<16;k++){
                if(outbuf[k] != 0)
                    fprintf(fp,"*decyrption error*\n");
                else
                    fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
            }
        }
    }
    fprintf(fp,"\n==========\n");
    fclose(fp);

    /*************************************************************************
     *
     * Variable Text KAT -> ecb_vt.txt 
     *
     ************************************************************************/
    fp = fopen("ecb_vt.txt","w");
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"ecb_vt.txt\"\n\n");
    fprintf(fp,"Electronic Codebook (ECB) Mode\n");
    fprintf(fp,"Variable Text Known Answer Tests\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");
    /* the input key is all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    /* 128 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=128\n\n");
    fprintf(fp,"KEY=00000000000000000000000000000000");
    for(i=0;i<16;i++) {
        for(j=7;j>=0;j--){
            for (k=0;k<16;k++)
                ptbuf[k] = 0;
            ptbuf[i] = (1<<j); 
            makeKey(&keyin,DIR_ENCRYPT,128,akey);
            cipherInit(&encipher,MODE_ECB,NULL);
            cipherInit(&decipher,MODE_ECB,NULL);
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
            fprintf(fp,"\n\nI=%d\n",i*8+8-j);
            fprintf(fp,"PT=");
            for(k=0;k<16;k++)
                fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
            fprintf(fp,"\nCT=");
            for(k=0;k<16;k++){
                if(outbuf[k] != ptbuf[k])
                    fprintf(fp,"*decyrption error*\n");
                else
                    fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
            }
        }
    }
    /* 192 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=192\n\n");
    fprintf(fp,"KEY=000000000000000000000000000000000000000000000000");
    for(i=0;i<16;i++) {
        for(j=7;j>=0;j--){
            for (k=0;k<16;k++)
                ptbuf[k] = 0;
            ptbuf[i] = (1<<j); 
            makeKey(&keyin,DIR_ENCRYPT,192,akey);
            cipherInit(&encipher,MODE_ECB,NULL);
            cipherInit(&decipher,MODE_ECB,NULL);
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
            fprintf(fp,"\n\nI=%d\n",i*8+8-j);
            fprintf(fp,"PT=");
            for(k=0;k<16;k++)
                fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
            fprintf(fp,"\nCT=");
            for(k=0;k<16;k++){
                if(outbuf[k] != ptbuf[k])
                    fprintf(fp,"*decyrption error*\n");
                else
                    fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
            }
        }
    }
    /* 256 bit key */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=256\n\n");
    fprintf(fp,"KEY=00000000000000000000000000000000");
    fprintf(fp,"00000000000000000000000000000000");
    for(i=0;i<16;i++) {
        for(j=7;j>=0;j--){
            for (k=0;k<16;k++)
                ptbuf[k] = 0;
            ptbuf[i] = (1<<j); 
            makeKey(&keyin,DIR_ENCRYPT,256,akey);
            cipherInit(&encipher,MODE_ECB,NULL);
            cipherInit(&decipher,MODE_ECB,NULL);
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, outbuf);
            fprintf(fp,"\n\nI=%d\n",i*8+8-j);
            fprintf(fp,"PT=");
            for(k=0;k<16;k++)
                fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
            fprintf(fp,"\nCT=");
            for(k=0;k<16;k++){
                if(outbuf[k] != ptbuf[k])
                    fprintf(fp,"*decyrption error*\n");
                else
                    fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
            }
        }
    }
    fprintf(fp,"\n==========\n");
    fclose(fp);

    /*************************************************************************
     * Tables KAT -> ecb_tbl.txt 
     * To test all Sbox entries, we fix the key to be zero, start 
     * with some initial plaintext, and iterate, setting each
     * next plaintext to the last ciphertext output.  We instrumented
     * the sbox lookups, and found that after 40 such iterations, all
     * sboxes had been used at least once for each key length.
     ************************************************************************/
    fp = fopen("ecb_tbl.txt","w");
    fprintf(fp,"/*  This tests all 512 entries in the fixed Sbox  */\n\n");
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"ecb_tbl.txt\"\n\n");
    fprintf(fp,"Electronic Codebook (ECB) Mode\n");
    fprintf(fp,"Tables Known Answer Tests\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");
    /* the input key is all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';

    /* 128 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=128");
    makeKey(&keyin,DIR_ENCRYPT,128,akey);
    cipherInit(&encipher,MODE_ECB,NULL);
    /* set some interesting starting text */
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    for(i=1;i<41;i++) {
        blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=00000000000000000000000000000000\n");
        fprintf(fp,"PT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        }
        for(j=0;j<16;j++)
            ptbuf[j] = ctbuf[j];
    }
    /* 192 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=192");
    makeKey(&keyin,DIR_ENCRYPT,192,akey);
    cipherInit(&encipher,MODE_ECB,NULL);
    /* set some interesting starting text */
    for(i=0;i<16;i++)
        ptbuf[i] = 0xaa;
    for(i=1;i<41;i++) {
        blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=00000000000000000000000000000000");
        fprintf(fp,"0000000000000000\n");
        fprintf(fp,"PT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        }
        for(j=0;j<16;j++)
            ptbuf[j] = ctbuf[j];
    }
    /* 256 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=256");
    makeKey(&keyin,DIR_ENCRYPT,256,akey);
    cipherInit(&encipher,MODE_ECB,NULL);
    /* set some interesting starting text */
    for(i=0;i<16;i++)
        ptbuf[i] = S[i]&0xff;
    for(i=1;i<41;i++) {
        blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=00000000000000000000000000000000");
        fprintf(fp,"00000000000000000000000000000000\n");
        fprintf(fp,"PT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        }
        for(j=0;j<16;j++)
            ptbuf[j] = ctbuf[j];
    }
    fprintf(fp,"\n==========\n");
    fclose(fp);
#endif /* KAT */

#ifdef MCT
    /*************************************************************************
     *
     * ECB Encrypt MCT -> ecb_e_m.txt 
     *
     ************************************************************************/
    fp = fopen("ecb_e_m.txt","w");
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"ecb_e_m.txt\"\n\n");
    fprintf(fp,"Electronic Codebook (ECB) Mode - ENCRYPTION\n");
    fprintf(fp,"Monte Carlo Test\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");

    /* 128 bit keys */
    fprintf(fp,"\n\n=========================\n\nKEYSIZE=128");
    /* the starting key and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,128,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<32;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<5000;k++){
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockEncrypt(&encipher, &keyin, ctbuf, 128, ptbuf);
        }
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        for(k=0;k<16;k++){
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ptbuf[k]>>4)];
            akey[2*k+1] = tohex[(int)hex[(int)akey[2*k+1]] ^ (ptbuf[k] & 0x0f)];
        }
    }
    /* 192 bit keys */
    fprintf(fp,"\n\n=========================\n\nKEYSIZE=192");
    /* the starting key and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,192,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<48;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<5000;k++){
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockEncrypt(&encipher, &keyin, ctbuf, 128, ptbuf);
        }
        /* ptbuf contains the last CT, and ctbuf has the prior... */
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        /* the first 64 bits come from the end of ctbuf, and
         * the remaining 128 bits from ptbuf (CT9999, and CT9998)
         */
        for(k=0;k<8;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ctbuf[k+8]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ctbuf[k+8] & 0x0f)];
        }
        for(k=0;k<16;k++){
            akey[2*k+16] = tohex[hex[(int)akey[2*k+16]]^(ptbuf[k]>>4)];
            akey[2*k+17] = tohex[(int)hex[(int)akey[2*k+17]]^(ptbuf[k]&0x0f)];
        }
    }
    /* 256 bit keys */
    fprintf(fp,"\n\n=========================\n\nKEYSIZE=256");
    /* the starting key and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,256,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<64;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<5000;k++){
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            blockEncrypt(&encipher, &keyin, ctbuf, 128, ptbuf);
        }
        /* ptbuf contains the last CT, and ctbuf has the prior... */
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        /* the first 128 bits come from ctbuf, and
         * the remaining 128 bits from ptbuf (CT9999, and CT9998)
         */
        for(k=0;k<16;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ctbuf[k]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ctbuf[k] & 0x0f)];
            akey[2*k+32] = tohex[hex[(int)akey[2*k+32]]^(ptbuf[k]>>4)];
            akey[2*k+33] = tohex[(int)hex[(int)akey[2*k+33]]^(ptbuf[k]&0x0f)];
        }
    }
    fprintf(fp,"\n==========\n");
    fclose(fp);

    /*************************************************************************
     *
     * ECB Decrypt MCT -> ecb_d_m.txt
     *
     ************************************************************************/
    fp = fopen("ecb_d_m.txt","w");
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"ecb_d_m.txt\"\n\n");
    fprintf(fp,"Electronic Codebook (ECB) Mode - DECRYPTION\n");
    fprintf(fp,"Monte Carlo Test\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");

    /* 128 bit keys */
    fprintf(fp,"\n\n=========================\n\nKEYSIZE=128");
    /* the starting key and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    cipherInit(&decipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_DECRYPT,128,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<32;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<5000;k++){
            blockDecrypt(&decipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, ptbuf);
        }
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        for(k=0;k<16;k++){
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ptbuf[k]>>4)];
            akey[2*k+1] = tohex[(int)hex[(int)akey[2*k+1]] ^ (ptbuf[k] & 0x0f)];
        }
    }
    /* 192 bit keys */
    fprintf(fp,"\n\n=========================\n\nKEYSIZE=192");
    /* the starting key and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    cipherInit(&decipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_DECRYPT,192,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<48;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<5000;k++){
            blockDecrypt(&decipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, ptbuf);
        }
        /* ptbuf contains the last CT, and ctbuf has the prior... */
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        /* the first 64 bits come from the end of ctbuf, and
         * the remaining 128 bits from ptbuf (CT9999, and CT9998)
         */
        for(k=0;k<8;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ctbuf[k+8]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ctbuf[k+8] & 0x0f)];
        }
        for(k=0;k<16;k++){
            akey[2*k+16] = tohex[hex[(int)akey[2*k+16]]^(ptbuf[k]>>4)];
            akey[2*k+17] = tohex[(int)hex[(int)akey[2*k+17]]^(ptbuf[k]&0x0f)];
        }
    }
    /* 256 bit keys */
    fprintf(fp,"\n\n=========================\n\nKEYSIZE=256");
    /* the starting key and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++)
        ptbuf[i] = 0;
    cipherInit(&decipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_DECRYPT,256,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<64;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<5000;k++){
            blockDecrypt(&decipher, &keyin, ptbuf, 128, ctbuf);
            blockDecrypt(&decipher, &keyin, ctbuf, 128, ptbuf);
        }
        /* ptbuf contains the last CT, and ctbuf has the prior... */
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        /* the first 128 bits come from ctbuf, and
         * the remaining 128 bits from ptbuf (CT9999, and CT9998)
         */
        for(k=0;k<16;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ctbuf[k]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ctbuf[k] & 0x0f)];
            akey[2*k+32] = tohex[hex[(int)akey[2*k+32]]^(ptbuf[k]>>4)];
            akey[2*k+33] = tohex[(int)hex[(int)akey[2*k+33]]^(ptbuf[k]&0x0f)];
        }
    }
    fprintf(fp,"\n==========\n");
    fclose(fp);

    /*************************************************************************
     *
     * CBC Encrypt MCT -> cbc_e_m.txt
     *
     ************************************************************************/
    fp = fopen("cbc_e_m.txt","w");
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"cbc_e_m.txt\"\n\n");
    fprintf(fp,"Cipher Block Chaining (CBC) Mode - ENCRYPTION\n");
    fprintf(fp,"Monte Carlo Test\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");

    /* 128 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=128");
    /* the starting key, IV, and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++){
        ptbuf[i] = 0;
        ivbuf[i] = 0;
    }
    /* we will do CBC manually */
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,128,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<32;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nIV=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ivbuf[k]>>4],tohex[ivbuf[k]&0x0f]); 
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<10000;k++){
            for(j=0;j<16;j++)
                ptbuf[j] ^= ivbuf[j];
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            for(j=0;j<16;j++){
                ptbuf[j] = ivbuf[j];
                ivbuf[j] = ctbuf[j];
            }
        }
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        }
        for(k=0;k<16;k++){
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ctbuf[k]>>4)];
            akey[2*k+1] = tohex[(int)hex[(int)akey[2*k+1]] ^ (ctbuf[k] & 0x0f)];
        }
    }
    /* 192 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=192");
    /* the starting key, IV, and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++){
        ptbuf[i] = 0;
        ivbuf[i] = 0;
    }
    /* we will do CBC manually */
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,192,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<48;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nIV=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ivbuf[k]>>4],tohex[ivbuf[k]&0x0f]); 
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<10000;k++){
            for(j=0;j<16;j++)
                ptbuf[j] ^= ivbuf[j];
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            for(j=0;j<16;j++){
                ptbuf[j] = ivbuf[j];
                ivbuf[j] = ctbuf[j];
            }
        }
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        }
        /* the first 64 bits come from the end of ivbuf, and
         * the remaining 128 bits from ctbuf (CT9999, and CT9998)
         */
        for(k=0;k<8;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ptbuf[k+8]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ptbuf[k+8] & 0x0f)];
        }
        for(k=0;k<16;k++){
            akey[2*k+16] = tohex[hex[(int)akey[2*k+16]]^(ctbuf[k]>>4)];
            akey[2*k+17] = tohex[(int)hex[(int)akey[2*k+17]]^(ctbuf[k]&0x0f)];
        }
    }
    /* 256 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=256");
    /* the starting key, IV, and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++){
        ptbuf[i] = 0;
        ivbuf[i] = 0;
    }
    /* we will do CBC manually */
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,256,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<64;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nIV=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ivbuf[k]>>4],tohex[ivbuf[k]&0x0f]); 
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        for(k=0;k<10000;k++){
            for(j=0;j<16;j++)
                ptbuf[j] ^= ivbuf[j];
            blockEncrypt(&encipher, &keyin, ptbuf, 128, ctbuf);
            for(j=0;j<16;j++){
                ptbuf[j] = ivbuf[j];
                ivbuf[j] = ctbuf[j];
            }
        }
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        }
        /* the first 128 bits come from ctbuf, and
         * the remaining 128 bits from ptbuf (CT9999, and CT9998)
         */
        for(k=0;k<16;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ptbuf[k]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ptbuf[k] & 0x0f)];
            akey[2*k+32] = tohex[hex[(int)akey[2*k+32]]^(ctbuf[k]>>4)];
            akey[2*k+33] = tohex[(int)hex[(int)akey[2*k+33]]^(ctbuf[k]&0x0f)];
        }
    }
    fprintf(fp,"\n==========\n");
    fclose(fp);

    /*************************************************************************
     *
     * CBC Decrypt MCT -> cbc_d_m.txt
     *
     ************************************************************************/
    fp = fopen("cbc_d_m.txt","w");
    fprintf(fp,"=========================\n\n");
    fprintf(fp,"FILENAME:  \"cbc_d_m.txt\"\n\n");
    fprintf(fp,"Cipher Block Chaining (CBC) Mode - DECRYPTION\n");
    fprintf(fp,"Monte Carlo Test\n\n");
    fprintf(fp,"Algorithm Name: Mars\n");
    fprintf(fp,"Principle Submitter: IBM");

    /* 128 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=128");
    /* the starting key, IV, and CT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++){
        ctbuf[i] = 0;
        ivbuf[i] = 0;
    }
    /* we will do CBC manually */
    cipherInit(&decipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_DECRYPT,128,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<32;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nIV=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ivbuf[k]>>4],tohex[ivbuf[k]&0x0f]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        for(k=0;k<10000;k++){
            blockDecrypt(&decipher, &keyin, ctbuf, 128, ptbuf);
            for(j=0;j<16;j++)
                ptbuf[j] ^= ivbuf[j];
            for(j=0;j<16;j++){
                ivbuf[j] = ctbuf[j];
                ctbuf[j] = ptbuf[j];
            }
        }
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        for(k=0;k<16;k++){
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ptbuf[k]>>4)];
            akey[2*k+1] = tohex[(int)hex[(int)akey[2*k+1]] ^ (ptbuf[k] & 0x0f)];
        }
    }
    /* 192 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=192");
    /* the starting key, IV, and CT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++){
        ctbuf[i] = 0;
        ivbuf[i] = 0;
    }
    /* we will do CBC manually */
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,192,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<48;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nIV=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ivbuf[k]>>4],tohex[ivbuf[k]&0x0f]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        for(k=0;k<10000;k++){
            blockDecrypt(&decipher, &keyin, ctbuf, 128, ptbuf);
            for(j=0;j<16;j++)
                ptbuf[j] ^= ivbuf[j];
            for(j=0;j<16;j++){
                ivbuf[j] = ctbuf[j];
                ctbuf[j] = ptbuf[j];
            }
        }
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        /* the first 64 bits come from the end of ivbuf, and
         * the remaining 128 bits from ctbuf (CT9999, and CT9998)
         */
        for(k=0;k<8;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ivbuf[k+8]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ivbuf[k+8] & 0x0f)];
        }
        for(k=0;k<16;k++){
            akey[2*k+16] = tohex[hex[(int)akey[2*k+16]]^(ptbuf[k]>>4)];
            akey[2*k+17] = tohex[(int)hex[(int)akey[2*k+17]]^(ptbuf[k]&0x0f)];
        }
    }
    /* 256 bit keys */
    fprintf(fp,"\n\n==========\n\nKEYSIZE=256");
    /* the starting key, IV, and PT are all zeros */
    for(i=0;i<64;i++)
        akey[i] = '0';
    akey[64] = '\0';
    for(i=0;i<16;i++){
        ctbuf[i] = 0;
        ivbuf[i] = 0;
    }
    /* we will do CBC manually */
    cipherInit(&encipher,MODE_ECB,NULL);
    for(i=0;i<400;i++) {
        makeKey(&keyin,DIR_ENCRYPT,256,akey);
        fprintf(fp,"\n\nI=%d\n",i);
        fprintf(fp,"KEY=");
        for(k=0;k<64;k++)
            fprintf(fp,"%c",akey[k]); 
        fprintf(fp,"\nIV=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ivbuf[k]>>4],tohex[ivbuf[k]&0x0f]); 
        fprintf(fp,"\nCT=");
        for(k=0;k<16;k++)
            fprintf(fp,"%c%c",tohex[ctbuf[k]>>4],tohex[ctbuf[k]&0x0f]); 
        for(k=0;k<10000;k++){
            blockDecrypt(&decipher, &keyin, ctbuf, 128, ptbuf);
            for(j=0;j<16;j++)
                ptbuf[j] ^= ivbuf[j];
            for(j=0;j<16;j++){
                ivbuf[j] = ctbuf[j];
                ctbuf[j] = ptbuf[j];
            }
        }
        fprintf(fp,"\nPT=");
        for(k=0;k<16;k++){
            fprintf(fp,"%c%c",tohex[ptbuf[k]>>4],tohex[ptbuf[k]&0x0f]); 
        }
        /* the first 128 bits come from ctbuf, and
         * the remaining 128 bits from ptbuf (CT9999, and CT9998)
         */
        for(k=0;k<16;k++) {
            akey[2*k] = tohex[hex[(int)akey[2*k]] ^ (ivbuf[k]>>4)];
            akey[2*k+1] = tohex[hex[(int)akey[2*k+1]] ^ (ivbuf[k] & 0x0f)];
            akey[2*k+32] = tohex[hex[(int)akey[2*k+32]]^(ptbuf[k]>>4)];
            akey[2*k+33] = tohex[(int)hex[(int)akey[2*k+33]]^(ptbuf[k]&0x0f)];
        }
    }
    fprintf(fp,"\n==========\n");
    fclose(fp);

#endif /* MCT */

    return(0);
}





