/*
 *   MIRACL cryptographic strong random number generator 
 *   mrstrong.c
 *
 *   Copyright (c) 1988-1998 Shamus Software Ltd.
 *
 *   Unguessable seed -> SHA -> PRNG internal state -> SHA -> random numbers
 *   Slow - but secure
 *
 *   See ftp://ftp.rsasecurity.com/pub/pdfs/bull-1.pdf for a justification
 */

#include <stdio.h>
#include <miracl.h>

static void fill_pool(_MIPDO_ )
{ /* hash down output of RNG to re-fill the pool */
    int i;
    sha_r sh;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    shs_init(&sh);
    for (i=0;i<128;i++) shs_process(&sh,(int)brand(_MIPPO_ ));
    shs_hash(&sh,mr_mip->pool);
    mr_mip->pool_ptr=0;
}

void strong_init(_MIPD_ int rawlen,char *raw,mr_unsign32 tod)
{ /* initialise from at least 128 byte string of raw  *
   * random (keyboard?) input, and 32-bit time-of-day */
    int i;
    mr_unsign32 hash[MR_HASH_BYTES/4];
    sha_r sh;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    mr_mip->pool_ptr=0;
    shs_init(&sh);
    for (i=0;i<rawlen;i++)
        shs_process(&sh,raw[i]);
    shs_hash(&sh,(char *)hash);

/* initialise PRNG from distilled randomness */
    irand(_MIPP_ tod);
    for (i=0;i<MR_HASH_BYTES/4;i++) irand(_MIPP_ hash[i]);

    fill_pool(_MIPPO_ );

}

void strong_rng(_MIPD_ int bytes,char *ran)
{ 
    int i;
#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    for (i=0;i<bytes;i++)
    {
        ran[i]=mr_mip->pool[mr_mip->pool_ptr++];
        if (mr_mip->pool_ptr>=MR_HASH_BYTES) fill_pool(_MIPPO_ );
    }    
}

void strong_bigrand(_MIPD_ big w, big x)
{
    unsigned int ran;
    unsigned char ch;

#ifndef MR_GENERIC_MT
    miracl *mr_mip=get_mip();
#endif
    if (mr_mip->ERNUM) return;
    MR_IN(139)
    zero(mr_mip->w1);
    do
    {
        if (mr_mip->ERNUM) break;
        ch=(unsigned char)mr_mip->pool[mr_mip->pool_ptr++];
        if (mr_mip->pool_ptr>=MR_HASH_BYTES) fill_pool(_MIPPO_ );
        ran=ch;
        premult(_MIPP_ mr_mip->w1,256,mr_mip->w1);
        incr(_MIPP_ mr_mip->w1,(int)ran,mr_mip->w1);
    } while (compare(mr_mip->w1,w)<0);
    divide(_MIPP_ mr_mip->w1,w,w);
    copy(mr_mip->w1,x);
    MR_OUT
}


/* test main program 

#include <stdio.h>
#include <miracl.h>
#include <time.h>

void main()
{
    int i;
    char raw[256],bytes[25];
    big x,w;
    long seed;
    miracl *mip=mirsys(200,256);
    x=mirvar(0);
    w=mirvar(0);
    printf("Enter Raw random string= ");
    scanf("%s",raw);
    getchar();
    time(&seed);
    strong_init(strlen(raw),raw,seed);
    mip->IOBASE=16;
    expint(2,256,w);
    cotnum(w,stdout);
    for (i=0;i<20;i++)
    {
        strong_bigrand(w,x);
        cotnum(x,stdout);
    }
}

*/

