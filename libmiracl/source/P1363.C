/* 
 * MIRACL-based implementation of the P1363 draft standard 
 * Version 0.98 December 2000
 *
 * Implements all the cryptographic primitives, message encoding methods, key 
 * derivation functions and auxiliary functions necessary for realising the 
 * recommended methods. Note that GF(p) and GF(2^m) Elliptic curves are
 * treated seperately.
 *
 * See the IEEE P1363 documentation for details
 * http://grouper.ieee.org/groups/1363/index.html
 * This IS the documentation for this implementation. Each P1363 function
 * has the same name, and same inputs/outputs as those described in the 
 * official P1363 documentation.
 *
 * The user is responsible for the initialisation and maintainance of 
 * "Octet strings" which store Cryptographic keys and application info.
 * These octet strings store big numbers in binary, from MSB down to LSB
 * NOTE:- Leading zeros are suppressed! Use OCTET_PAD() to insert leading
 * zeros to make an octet a particular length, e.g. 20 bytes, 160 bits.
 * 
 * A special random octet called SEED, must be initialised by the user with
 * raw random data. This doesn't have to be high quality (e.g. mouse movement 
 * coordinates), but there must be enough of it for it to be unguessable. 
 * It is subsequently maintained internally by the system
 * The secure random number generation method used is based on that described 
 * in http://www.rsa.com/rsalabs/pubs/updates/bull-1.pdf
 *
 * The above is the recommended approach. 
 * Alternatvely when generating a key pair a random number can be specified 
 * directly as a private key, and this internal system by-passed. 
 * 
 * Domain and Public/Private key data is stored in structures defined in 
 * p1363.h. The first parameter in each function is a pointer to a function 
 * which will be called during time-consuming calculations - e.g. a Windows 
 * message pump. Negative return values indicate an error - see p1363.h for 
 * definitions. Most common MIRACL errors are mapped to these values.
 * Unlikely MIRACL errors are returned as -(1000+MEC), where MEC
 * is the MIRACL Error Code (see miracl.h)
 *
 * Recommended for use with a (32-bit) MIRACL library built 
 * from a mirdef.h file that looks something like this:-
 *
 * #define MIRACL 32
 * #define MR_LITTLE_ENDIAN
 * #define mr_utype int
 * #define MR_IBITS 32
 * #define MR_LBITS 32
 * #define mr_unsign32 unsigned int
 * #define MR_STRIPPED_DOWN
 * #define MR_GENERIC_MT
 * #define MR_NO_STANDARD_IO
 *
 * Note that this is a multi-threaded build, ideal for a Cryptographic DLL
 * The compiler may need a multithreaded flag set (/MT ??) 
 * The miracl instance variable ERCON is set to TRUE in each routine, so 
 * MIRACL does not attempt to report an error. Instead the variable ERNUM 
 * latches the last error, and if set causes each subsequent routine to 
 * "fall through".  
 *
 * Octet strings are not tested for overflow. To avoid problems its best to 
 * initialise the length of each to that recommended and returned by the  
 * XXX_DOMAIN_INIT() routines.
 *
 * A test driver main() function is provided in test1363.c to test all the 
 * functions, and to implement one of the recommended methods, IFSSA.
 * In Win32 MS C:-
 * cl /O2 /MT test1363.c p1363.c miracl.lib  /link /NODEFAULTLIB:libc.lib
 * and run the executable
 *
 * test1363         ; 
 * test1363 -c      ; uses EC point compression
 * test1363 -p      ; uses precomputation for signature
 * test1363 -c -p   ; uses both precomputation and EC point compression
 * test1363 -r 56   ; uses different random number seed 
 *
 * To create a Windows P1363 DLL, uncomment the MR_P1363_DLL definition below, 
 * and compile as 
 * cl /O2 /W3 /MT /LD p1363.c miracl.lib /link /NODEFAULTLIB:libc.lib
 * To run the test program to use the DLL, uncomment the MR_P1363_DLL
 * definition at the start of test1363.c, and compile as
 * cl /O2 /MT test1363.c p1363.lib
 * 
 * Discrete Logarithm/GF(p) Elliptic Curve/GF(2^m) Elliptic Curve Domain 
 * details are read from the files common.dss, common.ecs and common2.ecs 
 * respectively. Suitable files are included in the standard MIRACL 
 * distribution. You can generate your own using for example the utilities 
 * dssetup.cpp, schoof.cpp and schoof2.cpp. But make sure that the group order
 * in each case is at least 160-bits, or the demo may fail.
 *
 * Note that for a full P1363 implementation various simple message-encoding 
 * regimes must be also implemented, as described in the P1363 documentation. 
 * These are now implemented here. Also a suitable hashing function must 
 * be available. The SHA1 algorithm is recommended, and implemented in MIRACL 
 * (see RANDOM_START() for an example of its use.)
 *
 * Copyright (c) 2000 Shamus Software Ltd.
 */

/* define this next to create Windows DLL */   

/* #define MR_P1363_DLL */

#ifdef MR_P1363_DLL
#define P1363_DLL
#endif

#include <stdio.h>
#include <stdlib.h>
#include "p1363.h"

static void convert_octet_big(_MIPD_ octet *s,big w)
{ /* internal:- converts from octet to big format */
    bytes_to_big(_MIPP_ s->len,s->val,w);
}

static void convert_big_octet(_MIPD_ big w,octet *s)
{ /* internal:- converts from big to octet format */
    int i;
    for (i=0;i<s->len;i++) s->val[i]=0;
    s->len=(short)big_to_bytes(_MIPP_ 0,w,s->val);
}

/*** Basic Octet string maintaianance routines ***/
/* initialize an octet string */

P1363_API BOOL OCTET_INIT(octet *w,int bytes)
{
    w->len=0;
    w->val=(char *)malloc(bytes);
    if (w->val!=NULL) return TRUE;
    else              return FALSE; 
}

/* clear an octet string */

P1363_API void OCTET_CLEAR(octet *w)
{
    int i;
    for (i=0;i<w->len;i++) w->val[i]=0;
    w->len=0;
}

/* copy an octet string */

P1363_API void OCTET_COPY(octet *x,octet *y)
{
    int i;
    OCTET_CLEAR(y);
    y->len=x->len;
    for (i=0;i<y->len;i++) y->val[i]=x->val[i];
}

/* compare 2 octet strings. 
 * If x>y return 1, if x==y return 0, if x<y return -1 */ 

P1363_API int OCTET_COMPARE(octet *x,octet *y)
{
    int i;
    if (x->len>y->len) return 1;
    if (x->len<y->len) return -1;
    for (i=0;i<x->len;i++)
    {
        if (x->val[i]>y->val[i]) return 1;
        if (x->val[i]<y->val[i]) return -1;
    }
    return 0;
}

/* Pads an octet with leading zeros - returns FALSE if not enough room */

P1363_API BOOL OCTET_PAD(octet *x,int len)
{
    int i,d;
    if (x->len>len) return FALSE;
    d=len - x->len;
    for (i=len-1;i>=d;i--)
        x->val[i]=x->val[i-d];

    for (i=0;i<d;i++) x->val[i]=0;
    x->len=(short)len;
    return TRUE;
}

/* Concatenates two octet strings */

P1363_API void OCTET_JOIN(octet *x,octet*y)
{ /* y=y || x */
    int i;
    for (i=0;i<x->len;i++)
        y->val[y->len+i]=x->val[i];
    y->len+=x->len;
}

/* Output an octet string (Debug Only) */

P1363_API void OCTET_OUTPUT(octet *w)
{
    int i;
    unsigned char ch;
    for (i=0;i<w->len;i++)
    {
        ch=w->val[i];
        printf("%02x",ch);
    }
    printf("\n");
}

/* Kill an octet string */

P1363_API void OCTET_KILL(octet *w)
{
    int i;
    for (i=0;i<w->len;i++) w->val[i]=0;
    w->len=0;
    free(w->val);
}

/*** P1363 Auxiliary Functions ***/ 
/* Mask Generation Function */

P1363_API void MGF1(octet *z,int olen,octet *mask)
{
    sha_r sh;
    char h[20];
    int counter,cthreshold;
    int i,hlen=20;
    cthreshold=olen/hlen;
    if (olen%20 !=0 ) cthreshold++;
    OCTET_CLEAR(mask);
    for (counter=0;counter<cthreshold;counter++)
    {
        shs_init(&sh);
        for (i=0;i<z->len;i++) shs_process(&sh,z->val[i]);
        shs_process(&sh,(counter>>24)&0xff);
        shs_process(&sh,(counter>>16)&0xff);
        shs_process(&sh,(counter>>8)&0xff);
        shs_process(&sh,counter&0xff);
        shs_hash(&sh,h);
        for (i=0;i<hlen;i++)
            mask->val[mask->len+i]=h[i];
        mask->len+=hlen;
    }
    while (mask->len>olen)
    {
        mask->len--;
        mask->val[mask->len]=0;
    }        
}

/*** P1363 recommended Message Encoding Methods ***/
/* message encoding methods for signatures with Appendix */

P1363_API BOOL EMSA1(octet *x,char *fname,int bits,octet *w)
{ /* w is a bits-length representative of the    * 
   * octet string message x (if x!=NULL)         *
   * or of the file fname (if fname!=NULL)       *
   * w must be initialised for at least 20 bytes */
    int i,ch;
    unsigned char c1,c2;
    FILE *fp;
    sha_r sh;
    if (x!=NULL && fname!=NULL) return FALSE;
    OCTET_CLEAR(w);
    shs_init(&sh);

    if (x!=NULL)
    {
        for (i=0;i<x->len;i++) shs_process(&sh,x->val[i]);    
    }
    if (fname!=NULL)
    {
        fp=fopen(fname,"r");
        if (fp==NULL) return FALSE;
        while ((ch=fgetc(fp))!=EOF) shs_process(&sh,ch); 
        fclose(fp);
    }
    w->len=20;
    shs_hash(&sh,w->val);
    if (bits<160)
    { 
        for (i=19;i>bits/8;i--) 
        { /* remove bytes off the end */
            w->val[i]=0;
            w->len--;
        }    
        bits=bits%8;
        if (bits!=0)
        {
            for (i=w->len-1;i>=0;i--)
            {
                c1=(unsigned char)w->val[i];
                c1>>=(8-bits);               
                if (i>0)
                {
                    c2=(unsigned char)w->val[i-1];
                    c2<<=bits;
                    c1|=c2;
                }
                w->val[i]=(char)c1;
            }
        }
    }
    return TRUE;
}

P1363_API BOOL EMSA2(octet *x,char *fname,int bits,octet *w)
{ /* w is a bits-length representative of the    * 
   * octet string message x (if x!=NULL)         *
   * or of the file fname (if fname!=NULL)       *
   * w must be initialised for at least 1+bits/8 *
   * bytes                                       */
    int i,ch,lp;
    char h[20],p1;
    FILE *fp;
    sha_r sh;
    if (bits<191 || (x!=NULL && fname!=NULL)) return FALSE;
    shs_init(&sh);
    if (x!=NULL)
    {
        for (i=0;i<x->len;i++) shs_process(&sh,x->val[i]);    
    }
    if (fname!=NULL)
    {
        i=0;
        fp=fopen(fname,"r");
        if (fp==NULL) return FALSE;
        while ((ch=fgetc(fp))!=EOF) 
        {
            shs_process(&sh,ch); 
            i++;
        } 
        fclose(fp);
    }
    shs_hash(&sh,h);
    p1=0x4b;
    if (i>0) p1=0x6b;
    lp=((bits+1)/8)-24;
    OCTET_CLEAR(w);
    w->len=24+lp;
    w->val[0]=p1;
    for (i=1;i<=lp;i++) w->val[i]=(char)0xbb;
    w->val[lp+1]=(char)0xba;
    for (i=0;i<20;i++) w->val[lp+2+i]=h[i];
    w->val[lp+22]=(char)0x33;
    w->val[lp+23]=(char)0xcc;
    return TRUE;
}

/* OAEP Message Encoding for Encryption */

P1363_API BOOL EME1_ENCODE(octet *m,octet *SEED,int bits,octet *p,octet *f)
{
    sha_r sh;
    int i,slen,olen=bits/8;
    int mlen=m->len;
    int hlen,seedlen;
    octet dbmask;
       
    hlen=seedlen=20;
    if (mlen>olen-hlen-seedlen-1) return FALSE;
    OCTET_CLEAR(f);

    shs_init(&sh);
    if (p!=NULL) for (i=0;i<p->len;i++) shs_process(&sh,p->val[i]);
    shs_hash(&sh,f->val);
 
    slen=olen-mlen-hlen-seedlen-1;      
    for (i=0;i<slen;i++) f->val[hlen+i]=0;
    f->val[hlen+slen]=1;
    for (i=0;i<mlen;i++) f->val[slen+hlen+1+i]=m->val[i];
    f->len=olen-seedlen;

    OCTET_INIT(&dbmask,olen-seedlen);
    
    MGF1(SEED,olen-seedlen,&dbmask);
    for (i=0;i<f->len;i++) dbmask.val[i]^=f->val[i];
    MGF1(&dbmask,seedlen,f);
    for (i=0;i<seedlen;i++) f->val[i]^=SEED->val[i];
    for (i=0;i<olen-seedlen;i++) f->val[seedlen+i]=dbmask.val[i];
    f->len=olen;
    OCTET_KILL(&dbmask);

    return TRUE;
}

/* OAEP Message Decoding for Decryption */

P1363_API BOOL EME1_DECODE(octet *f,int bits,octet *p,octet *m)
{
    sha_r sh;
    int i,j,olen=bits/8;
    int hlen,seedlen;
    char h[20];
    octet dbmask,seed;
    seedlen=hlen=20;
    if (olen<seedlen+hlen+1) return FALSE;

    OCTET_INIT(&dbmask,olen-seedlen);
    OCTET_INIT(&seed,seedlen);
    for (i=seedlen;i<olen;i++)
        dbmask.val[i-seedlen]=f->val[i];

    dbmask.len=olen-seedlen;
    MGF1(&dbmask,seedlen,&seed);
    for (i=0;i<seedlen;i++) seed.val[i]^=f->val[i];
    MGF1(&seed,olen-seedlen,m);
    for (i=0;i<olen-seedlen;i++) dbmask.val[i]^=m->val[i];
    shs_init(&sh);
    if (p!=NULL) for (i=0;i<p->len;i++) shs_process(&sh,p->val[i]);
    shs_hash(&sh,h);
    for (i=0;i<hlen;i++) 
        if (dbmask.val[i]!=h[i]) return FALSE;
    for (i=hlen;i<olen-seedlen;i++)
    {
        if (dbmask.val[i]==0) continue;
        if (dbmask.val[i]!=0x01) return FALSE;
        break; 
    }
    if (i>=olen-seedlen) return FALSE;
    i++;
    OCTET_CLEAR(m);
    for (j=i;j<olen-seedlen;j++)
        m->val[j-i]=dbmask.val[j]; 
    m->len=j-i;

    OCTET_KILL(&seed);
    OCTET_KILL(&dbmask);
    return TRUE;
}

/*** P1363 Key Derivation Function ***/

P1363_API void KDF1(octet *z,octet *p,octet *k)
{
    int i;
    sha_r sh;
    shs_init(&sh);
    OCTET_CLEAR(k);
    for (i=0;i<z->len;i++) shs_process(&sh,z->val[i]);
    if (p!=NULL) for (i=0;i<p->len;i++) shs_process(&sh,p->val[i]);    
    k->len=20;
    shs_hash(&sh,k->val);
}


/* initialise the random octet string from raw random data */ 

P1363_API void RANDOM_START(int len,char *raw,octet *SEED)
{ /* uses Standard Hash Algorithm (SHA1)      *
   * NOTE! The octet SEED is initialised here */
    int i;
    sha_r sh;
    shs_init(&sh);
    for (i=0;i<len;i++)
        shs_process(&sh,raw[i]);

    OCTET_INIT(SEED,20);
    SEED->len=20;
    shs_hash(&sh,SEED->val);
}

/*** DL primitives - support functions ***/
/* Destroy the DL Domain structure */

P1363_API void DL_DOMAIN_KILL(dl_domain *DOM)
{
    miracl *mr_mip=NULL;
    OCTET_KILL(&DOM->Q);
    OCTET_KILL(&DOM->R);
    OCTET_KILL(&DOM->G);
    OCTET_KILL(&DOM->K);
    OCTET_KILL(&DOM->IK);

    if (DOM->PC.store!=0) 
        brick_end(_MIPP_ &DOM->PC);        
    DOM->words=0; DOM->H=0;
}

/* Initialise the DL domain structure
 * It is assumed that the DL domain details are obtained from a file
 * or from an array of strings 
 * multi-precision numbers are read in to the specified base (normally 16)
 * A suitable file can be generated offline by the MIRACL example program
 * dssetup.c   
 * Set precompute=TRUE if a precomputed table is to be used to 
 * speed up the calculation g^x mod p 
 * Returns recommended number of bytes for use with octet strings */

P1363_API int DL_DOMAIN_INIT(dl_domain *DOM,char *fname,char **params,int base,BOOL precompute)
{ /* get domain details from specified file, OR from an array of strings   *
   * If input from a file, params=NULL, if input from strings, fname=NULL  *
   * returns max size in bytes of octet strings                            */ 
    FILE *fp;
    BOOL fileinput=TRUE;
    miracl *mr_mip;
    big q,r,g,k;
    int bits,bytes,rbytes,err,res=0;

    if (fname==NULL && params==NULL) return MR_P1363_DOMAIN_NOT_FOUND;
    if (fname==NULL) fileinput=FALSE;

    if (fileinput)
    {
        fp=fopen(fname,"r");
        if (fp==NULL) return MR_P1363_DOMAIN_NOT_FOUND;
        fscanf(fp,"%d\n",&bits);
    }
    else
        sscanf(params[0],"%d\n",&bits); 

    DOM->words=24+(bits/MIRACL);
        
    mr_mip=mirsys(DOM->words,0);
    if (mr_mip==NULL) 
    {
        if (fileinput) fclose(fp);
        return MR_P1363_OUT_OF_MEMORY;
    }

    mr_mip->ERCON=TRUE;
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    if (base<2 || base>60) base=10;
    mr_mip->IOBASE=base;
    if (mr_mip->ERNUM) 
    {
        if (fileinput) fclose(fp);
        res=MR_P1363_OUT_OF_MEMORY;
    }

    if (res==0)
    {
        bytes=2+bits/8;
        if (fileinput)
        {
            cinnum(_MIPP_ q,fp);
            cinnum(_MIPP_ r,fp);
            cinnum(_MIPP_ g,fp);
            
            fclose(fp);
        }
        else
        {
            cinstr(_MIPP_ q,params[1]);
            cinstr(_MIPP_ r,params[2]);
            cinstr(_MIPP_ g,params[3]);
        } 
        rbytes=3+logb2(_MIPP_ r)/8;       /* r is usually much smaller than q */
        OCTET_INIT(&DOM->Q,bytes);
        OCTET_INIT(&DOM->R,rbytes);
        OCTET_INIT(&DOM->G,bytes);
        OCTET_INIT(&DOM->K,bytes);
        OCTET_INIT(&DOM->IK,rbytes);
        DOM->H=(1+logb2(_MIPP_ r))/2;
        decr(_MIPP_ q,1,k);
        divide(_MIPP_ k,r,k);    /* k=(q-1)/r */

        convert_big_octet(_MIPP_ q,&DOM->Q);
        convert_big_octet(_MIPP_ r,&DOM->R);
        convert_big_octet(_MIPP_ g,&DOM->G);
        convert_big_octet(_MIPP_ k,&DOM->K);
        xgcd(_MIPP_ k,r,k,k,k);
        convert_big_octet(_MIPP_ k,&DOM->IK);
        DOM->PC.store=0;
        if (precompute) brick_init(_MIPP_ &DOM->PC,g,q,logb2(_MIPP_ r));
    }

    mirkill(_MIPP_ k);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);
    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );

    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    if (res<0) return res;
    else return bytes;
}

/* validate DL domain details - good idea if you got them from
 * some-one else! */

P1363_API int DL_DOMAIN_VALIDATE(BOOL (*idle)(void),dl_domain *DOM)
{ /* do domain checks - IEEE P1363 A16.2 */
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,g,t;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;

    mr_mip->ERCON=TRUE;
    mr_mip->NTRY=50;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->G,g);
        if (size(g)<2 || size(q)<=2 || size(r)<=2) res=MR_P1363_DOMAIN_ERROR; 
        if (compare(g,q)>=0) res=MR_P1363_DOMAIN_ERROR;
    }
    if (res==0)
    {
        gprime(_MIPP_ 10000);
        if (!isprime(_MIPP_ q)) res=MR_P1363_DOMAIN_ERROR;
    }
    if (res==0) 
    {
        if (!isprime(_MIPP_ r)) res=MR_P1363_DOMAIN_ERROR;
    }
    if (res==0)
    { /* is g of order r? */
       powmod(_MIPP_ g,r,q,t);
       if (size(t)!=1) res=MR_P1363_DOMAIN_ERROR;
    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);
    err=mr_mip->ERNUM;

    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* Calculate a public/private DL key pair. W=g^S mod p 
 * where S is the private key and W the public key 
 * If SEED is NULL then the private key is provided externally in S
 * otherwise it is generated randomly internally
 */

P1363_API int DL_KEY_PAIR_GENERATE(BOOL (*idle)(void),dl_domain *DOM,octet *SEED, octet *S,octet *W)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,g,s,w;
    int err,res=0;

    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    w=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->G,g);
        if (SEED!=NULL)
        {
            strong_init(_MIPP_ SEED->len,SEED->val,0L);
            strong_bigrand(_MIPP_ r,s);
        }
        else
        {
            convert_octet_big(_MIPP_ S,s);
            divide(_MIPP_ s,r,r);
        }
        if (DOM->PC.store==0) 
            powmod(_MIPP_ g,s,q,w);
        else
            pow_brick(_MIPP_ &DOM->PC,s,w);

        if (SEED!=NULL)
        { 
            strong_rng(_MIPP_ SEED->len,SEED->val);
            convert_big_octet(_MIPP_ s,S);
        }
        convert_big_octet(_MIPP_ w,W);
    }
    mirkill(_MIPP_ w);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* validate a DL public key. Set full=TRUE for fuller, 
 * but more time-consuming test */

P1363_API int DL_PUBLIC_KEY_VALIDATE(BOOL (*idle)(void),dl_domain *DOM,BOOL full,octet *W)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,w,t;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    w=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ W,w);
        if (size(w)<2 || compare(w,q)>=0) res=MR_P1363_INVALID_PUBLIC_KEY;
    }
    if (res==0 && full) 
    {
        powmod(_MIPP_ w,r,q,t);
        if (size(t)!=1) res=MR_P1363_INVALID_PUBLIC_KEY;
    }   

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ w);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/*** P1363 DL primitives ***/
/* See P1363 documentation for specification */

P1363_API int DLSVDP_DH(BOOL (*idle)(void),dl_domain *DOM,octet *S,octet *WD,octet *Z) 
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,s,wd,z;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wd=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ WD,wd);

        powmod(_MIPP_ wd,s,q,z);

        convert_big_octet(_MIPP_ z,Z);
    }
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ wd);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ q);
    err=mr_mip->ERNUM;

    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int DLSVDP_DHC(BOOL (*idle)(void),dl_domain *DOM,octet *S,octet *WD,BOOL compatible,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,k,ik,s,wd,t,z;
    int sz;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    ik=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wd=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->K,k);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ WD,wd);

        if (compatible)
        {
            convert_octet_big(_MIPP_ &DOM->IK,ik);
            mad(_MIPP_ ik,s,ik,r,r,t);   /* t=s/k mod r */
        }
        else copy(s,t);
        mad(_MIPP_ t,k,t,r,r,t);       /* kt mod r */
        powmod(_MIPP_ wd,t,q,z);

        sz=size(z);
        if (sz==0 || sz==1) res=MR_P1363_INVALID_PUBLIC_KEY;
        else convert_big_octet(_MIPP_ z,Z);
    }
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ wd);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ ik);
    mirkill(_MIPP_ k);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int DLSVDP_MQV(BOOL (*idle)(void),dl_domain *DOM,octet *S,octet *U,octet *V,octet *WD,octet *VD,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    int h;
    int err,res=0;
    big q,r,s,u,v,wd,vd,e,t,td,z;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    v=mirvar(_MIPP_ 0);
    wd=mirvar(_MIPP_ 0);
    vd=mirvar(_MIPP_ 0);
    e=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    td=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ U,u);
        convert_octet_big(_MIPP_ V,v);
        convert_octet_big(_MIPP_ WD,wd);
        convert_octet_big(_MIPP_ VD,vd);

        h=DOM->H;
        expint(_MIPP_ 2,h,z);

        copy(v,t);
        divide(_MIPP_ t,z,z);
        add_r(_MIPP_ t,z,t);
        copy(vd,td);
        divide(_MIPP_ td,z,z);
        add_r(_MIPP_ td,z,td);

        mad(_MIPP_ t,s,u,r,r,e);
        mad(_MIPP_ e,td,td,r,r,t);
        powmod2(_MIPP_ vd,e,wd,t,q,z);

        if (size(z)==1) res= MR_P1363_ERROR;
        else convert_big_octet(_MIPP_ z,Z);
    }
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ td);
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ e);
    mirkill(_MIPP_ vd);
    mirkill(_MIPP_ wd);
    mirkill(_MIPP_ v);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);
    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );

    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int DLSVDP_MQVC(BOOL (*idle)(void),dl_domain *DOM,octet *S,octet *U,octet *V,octet *WD,octet *VD,BOOL compatible,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    int sz,h;
    big q,r,s,u,v,wd,vd,e,t,td,z,k,ik;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    ik=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    v=mirvar(_MIPP_ 0);
    wd=mirvar(_MIPP_ 0);
    vd=mirvar(_MIPP_ 0);
    e=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    td=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->K,k);
    
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ U,u);
        convert_octet_big(_MIPP_ V,v);
        convert_octet_big(_MIPP_ WD,wd);
        convert_octet_big(_MIPP_ VD,vd);

        h=DOM->H;
        expint(_MIPP_ 2,h,z);

        copy(v,t);
        divide(_MIPP_ t,z,z);
        add_r(_MIPP_ t,z,t);
        copy(vd,td);
        divide(_MIPP_ td,z,z);
        add_r(_MIPP_ td,z,td);

        mad(_MIPP_ t,s,u,r,r,e);
        if (compatible) 
        {
            convert_octet_big(_MIPP_ &DOM->IK,ik);
            mad(_MIPP_ e,ik,e,r,r,e);
        }
        mad(_MIPP_ e,k,e,r,r,e);
        mad(_MIPP_ e,td,td,r,r,t);
        powmod2(_MIPP_ vd,e,wd,t,q,z);

        sz=size(z);      
        if (sz==0 || sz==1) res=MR_P1363_INVALID_PUBLIC_KEY;
        convert_big_octet(_MIPP_ z,Z);
    }
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ td);
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ e);
    mirkill(_MIPP_ vd);
    mirkill(_MIPP_ wd);
    mirkill(_MIPP_ v);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ k);
    mirkill(_MIPP_ ik);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int DLVP_NR(BOOL (*idle)(void),dl_domain *DOM,octet *W,octet *C,octet *D,octet *F)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,g,w,f,c,d;
    int err,res=0;

    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    w=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->G,g);
        convert_octet_big(_MIPP_ W,w);
        convert_octet_big(_MIPP_ C,c);
        convert_octet_big(_MIPP_ D,d);
        if (size(c)<1 || compare(c,r)>=0 || size(d)<0 || compare(d,r)>=0) 
            res=MR_P1363_INVALID;
    }
    if (res==0)
    {
        powmod2(_MIPP_ g,d,w,c,q,f);
        divide(_MIPP_ f,r,r);
        subtract(_MIPP_ c,f,f);
        if (size(f)<0) add_r(_MIPP_ f,r,f);
        convert_big_octet(_MIPP_ f,F);
    }

    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ w);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int DLSP_NR(BOOL (*idle)(void),dl_domain *DOM,octet *SEED,octet *S,octet *F,octet *C,octet *D)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,g,s,f,c,d,u,v;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    v=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->G,g);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ F,f);
        if (compare(f,r)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {
        strong_init(_MIPP_ SEED->len,SEED->val,0L);
        do {
            if (mr_mip->ERNUM) break;
            strong_bigrand(_MIPP_ r,u);

            if (DOM->PC.store==0) 
                powmod(_MIPP_ g,u,q,v);
            else
                pow_brick(_MIPP_ &DOM->PC,u,v);

            add_r(_MIPP_ v,f,c);
            divide(_MIPP_ c,r,r);
        } while (size(c)==0);
        strong_rng(_MIPP_ SEED->len,SEED->val);
    }
    if (res==0)
    {    
        mad(_MIPP_ s,c,s,r,r,d);
        subtract(_MIPP_ u,d,d);
        if (size(d)<0) add_r(_MIPP_ d,r,d);

        convert_big_octet(_MIPP_ c,C);
        convert_big_octet(_MIPP_ d,D);
    }
    mirkill(_MIPP_ v);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int DLVP_DSA(BOOL (*idle)(void),dl_domain *DOM,octet *W,octet *C,octet *D,octet *F)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,g,w,f,c,d,h2;
    int err,res=0;

    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    w=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    h2=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->G,g);
        convert_octet_big(_MIPP_ W,w);
        convert_octet_big(_MIPP_ C,c);
        convert_octet_big(_MIPP_ D,d);
        convert_octet_big(_MIPP_ F,f);
        if (size(c)<1 || size(d)<1 || compare(c,r)>=0 || compare(d,r)>=0) 
            res=MR_P1363_INVALID;
    }
    if (res==0)
    {
        xgcd(_MIPP_ d,r,d,d,d);
        mad(_MIPP_ f,d,f,r,r,f);
        mad(_MIPP_ c,d,c,r,r,h2);
        powmod2(_MIPP_ g,f,w,h2,q,d);
        divide(_MIPP_ d,r,r);
        if (compare(d,c)!=0) res=MR_P1363_INVALID;
    }

    mirkill(_MIPP_ h2);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ w);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int DLSP_DSA(BOOL (*idle)(void),dl_domain *DOM,octet *SEED,octet *S,octet *F,octet *C,octet *D)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,g,s,f,c,d,u,v;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=FALSE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    v=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->G,g);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ F,f);

        strong_init(_MIPP_ SEED->len,SEED->val,0L);
        do {
            if (mr_mip->ERNUM) break;
            strong_bigrand(_MIPP_ r,u);

            if (DOM->PC.store==0) 
                powmod(_MIPP_ g,u,q,v);
            else
                pow_brick(_MIPP_ &DOM->PC,u,v);

            copy(v,c); 
            divide(_MIPP_ c,r,r);
            if (size(c)==0) continue;
            xgcd(_MIPP_ u,r,u,u,u);
            mad(_MIPP_ s,c,f,r,r,d);
            mad(_MIPP_ u,d,u,r,r,d);
        } while (size(d)==0);
        strong_rng(_MIPP_ SEED->len,SEED->val);
        if (res==0)
        {
            convert_big_octet(_MIPP_ c,C);
            convert_big_octet(_MIPP_ d,D);
        }
    }
    mirkill(_MIPP_ v);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/*** EC GF(p) primitives - support functions ***/
/* destroy the EC GF(p) domain structure */

P1363_API void ECP_DOMAIN_KILL(ecp_domain *DOM)
{
    miracl *mr_mip=NULL;
    OCTET_KILL(&DOM->Q);
    OCTET_KILL(&DOM->A);
    OCTET_KILL(&DOM->B);
    OCTET_KILL(&DOM->R);
    OCTET_KILL(&DOM->Gx);
    OCTET_KILL(&DOM->Gy);
    OCTET_KILL(&DOM->K);
    OCTET_KILL(&DOM->IK);

    if (DOM->PC.store!=0) 
        ebrick_end(_MIPP_ &DOM->PC);        

    DOM->words=0; DOM->H=0;
}

/* Initialise the EC GF(p) domain structure
 * It is assumed that the EC domain details are obtained from a file
 * or from an array of strings 
 * multiprecision numbers are read in to the specified base (normally 16)
 * A suitable file can be generated offline by the MIRACL example program
 * schoof.exe   
 * Set precompute=TRUE if a precomputed table is to be used to 
 * speed up the calculation x.G mod EC(p) 
 * Returns recommended number of bytes to use for octet strings */

P1363_API int ECP_DOMAIN_INIT(ecp_domain *DOM,char *fname,char **params,int base,BOOL precompute)
{ /* get domain details from specified file     */
  /* If input from a file, params=NULL, if input from strings, fname=NULL  */
  /* return max. size in bytes of octet strings */
    FILE *fp;
    miracl *mr_mip;
    BOOL fileinput=TRUE;
    big q,r,gx,gy,a,b,k;
    int bits,bytes,err,res=0;

    if (fname==NULL && params==NULL) return MR_P1363_DOMAIN_NOT_FOUND; 
    if (fname==NULL) fileinput=FALSE;

    if (fileinput)
    {
        fp=fopen(fname,"r");
        if (fp==NULL) return MR_P1363_DOMAIN_NOT_FOUND;
        fscanf(fp,"%d\n",&bits);
    }
    else
        sscanf(params[0],"%d\n",&bits);
    
    DOM->words=12+(bits/MIRACL);

    mr_mip=mirsys(DOM->words,0);
    if (mr_mip==NULL) 
    {
        if (fileinput) fclose(fp);
        return MR_P1363_OUT_OF_MEMORY;
    }
    mr_mip->ERCON=TRUE;
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    if (base<2 || base>60) base=10;
    mr_mip->IOBASE=base;

    if (mr_mip->ERNUM) 
    {
        if (fileinput) fclose(fp);
        res=MR_P1363_OUT_OF_MEMORY;
    }

    if (res==0)
    {
        bytes=2+bits/8;
        if (fileinput)
        {
            cinnum(_MIPP_ q,fp);
            cinnum(_MIPP_ a,fp);
            cinnum(_MIPP_ b,fp);
            cinnum(_MIPP_ r,fp);
            cinnum(_MIPP_ gx,fp); 
            cinnum(_MIPP_ gy,fp); 
            fclose(fp);
        }
        else
        {
            cinstr(_MIPP_ q,params[1]);
            cinstr(_MIPP_ a,params[2]);
            cinstr(_MIPP_ b,params[3]);
            cinstr(_MIPP_ r,params[4]);
            cinstr(_MIPP_ gx,params[5]); 
            cinstr(_MIPP_ gy,params[6]); 
        }
        
        OCTET_INIT(&DOM->Q,bytes);
        OCTET_INIT(&DOM->A,bytes);
        OCTET_INIT(&DOM->B,bytes);
        OCTET_INIT(&DOM->R,bytes);
        OCTET_INIT(&DOM->Gx,bytes);
        OCTET_INIT(&DOM->Gy,bytes);
        OCTET_INIT(&DOM->K,bytes);
        OCTET_INIT(&DOM->IK,bytes);
        DOM->H=(1+logb2(_MIPP_ r))/2;

        nroot(_MIPP_ q,2,k);
        premult(_MIPP_ k,2,k);
        add_r(_MIPP_ k,q,k);
        incr(_MIPP_ k,3,k);

        divide(_MIPP_ k,r,k);    /* get co-factor k = (q+2q^0.5+3)/r */
        if (size(a)<0) add_r(_MIPP_ q,a,a);
        if (size(b)<0) add_r(_MIPP_ q,b,b);

        convert_big_octet(_MIPP_ q,&DOM->Q);
        convert_big_octet(_MIPP_ a,&DOM->A);
        convert_big_octet(_MIPP_ b,&DOM->B);
        convert_big_octet(_MIPP_ r,&DOM->R);
        convert_big_octet(_MIPP_ gx,&DOM->Gx);
        convert_big_octet(_MIPP_ gy,&DOM->Gy);
        convert_big_octet(_MIPP_ k,&DOM->K);
        xgcd(_MIPP_ k,r,k,k,k);
        convert_big_octet(_MIPP_ k,&DOM->IK);
        DOM->PC.store=0;
        if (precompute) ebrick_init(_MIPP_ &DOM->PC,gx,gy,a,b,q,logb2(_MIPP_ r));
    }

    mirkill(_MIPP_ k);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    if (res<0) return res;
    else return bytes;
}

/* validate EC GF(p) domain details - good idea if you got them from
 * some-one else! */

P1363_API int ECP_DOMAIN_VALIDATE(BOOL (*idle)(void),ecp_domain *DOM)
{ /* do domain checks - A16.8 */
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,r,gx,gy,t,w;
    epoint *G;
    int i,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    
    mr_mip->ERCON=TRUE;
    mr_mip->NTRY=50;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    w=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);

        nroot(_MIPP_ q,2,t);
        premult(_MIPP_ t,4,t);
        if (compare(r,t)<=0) res=MR_P1363_DOMAIN_ERROR;
        if (compare(b,q)>=0) res=MR_P1363_DOMAIN_ERROR; 
        if (compare(r,q)==0) res=MR_P1363_DOMAIN_ERROR;
        if (size(r)<3 || size(q)<3) res=MR_P1363_DOMAIN_ERROR;
    }

    if (res==0)
    {
        gprime(_MIPP_ 10000);
        if (!isprime(_MIPP_ r)) res=MR_P1363_DOMAIN_ERROR;
    }

    if (res==0)
    {
        if (!isprime(_MIPP_ q)) res=MR_P1363_DOMAIN_ERROR;
    }

    if (res==0)
    { /* check 4a^3+27b^2 !=0 mod q */
        mad(_MIPP_ b,b,b,q,q,t);
        premult(_MIPP_ t,27,t);
        mad(_MIPP_ a,a,a,q,q,w);
        mad(_MIPP_ w,a,a,q,q,w);
        premult(_MIPP_ w,4,w);

        add_r(_MIPP_ t,w,t);
        divide(_MIPP_ t,q,q);
        if (size(t)<0) add_r(_MIPP_ t,q,t);
        if (size(t)==0) res=MR_P1363_DOMAIN_ERROR;  
    }

    if (res==0)
    {
        ecurve_init(_MIPP_ a,b,q,MR_AFFINE);   
        G=epoint_init(_MIPPO_ );
        if (!epoint_set(_MIPP_ gx,gy,0,G)) res=MR_P1363_DOMAIN_ERROR;
        if (G->marker==MR_EPOINT_INFINITY) res=MR_P1363_DOMAIN_ERROR;
        else
        {
            ecurve_mult(_MIPP_ r,G,G);
            if (G->marker!=MR_EPOINT_INFINITY) res=MR_P1363_DOMAIN_ERROR;
        }
        epoint_free(_MIPP_ G);
    }

    if (res==0)
    { /* MOV conditon */
        convert(_MIPP_ 1,t);
        for (i=0;i<50;i++)
        {
            mad(_MIPP_ t,q,q,r,r,t);
            if (size(t)==1)
            {
                res=MR_P1363_DOMAIN_ERROR;
                break;
            }
        }
    }

    mirkill(_MIPP_ w);
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);
    err=mr_mip->ERNUM;

    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* Calculate a public/private EC GF(p) key pair. W=S.g mod EC(p),
 * where S is the secret key and W is the public key
 * Returns a single bit which can be used for "point compression" 
 * If SEED is NULL then the private key is provided externally in S
 * otherwise it is generated randomly internally
 * (Set Wy to NULL if y-coordinate not needed) */

P1363_API int ECP_KEY_PAIR_GENERATE(BOOL (*idle)(void),ecp_domain *DOM,octet *SEED,octet*S,octet *Wx,octet *Wy)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,r,gx,gy,s,wx,wy;
    epoint *G,*W;
    int err,res=0;

    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init(_MIPPO_ );
        W=epoint_init(_MIPPO_ );
        epoint_set(_MIPP_ gx,gy,0,G);

        if (SEED!=NULL)
        {
            strong_init(_MIPP_ SEED->len,SEED->val,0L);
            strong_bigrand(_MIPP_ r,s);
        }
        else
        {
            convert_octet_big(_MIPP_ S,s);
            divide(_MIPP_ s,r,r);
        }
        if (DOM->PC.store==0)
        {
            ecurve_mult(_MIPP_ s,G,W);        
            res=epoint_get(_MIPP_ W,wx,wy);
        }
        else
            res=mul_brick(_MIPP_ &DOM->PC,s,wx,wy);
        if (SEED!=NULL)
        {
            strong_rng(_MIPP_ SEED->len,SEED->val);
            convert_big_octet(_MIPP_ s,S);
        }
        convert_big_octet(_MIPP_ wx,Wx);
        if (Wy!=NULL) convert_big_octet(_MIPP_ wy,Wy);

        epoint_free(_MIPP_ W);
        epoint_free(_MIPP_ G);

    }

    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* validate an EC GF(p) public key. Set full=TRUE for fuller, 
 * but more time-consuming test 
 * provide either both x and y coordinates, or NULL for y 
 * and a single bit LSB */

P1363_API int ECP_PUBLIC_KEY_VALIDATE(BOOL (*idle)(void),ecp_domain *DOM,BOOL full,octet *Wx,octet *Wy,int LSB)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,r,wx,wy;
    epoint *W;
    BOOL valid;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ Wx,wx);
        if (Wy!=NULL) convert_octet_big(_MIPP_ Wy,wy);
        if (compare(wx,q)>=0 || compare (wy,q)>=0) res=MR_P1363_INVALID_PUBLIC_KEY;
    }
    if (res==0)
    {
        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        W=epoint_init(_MIPPO_ );

        if (Wy!=NULL)
             valid=epoint_set(_MIPP_ wx,wy,0,W);
        else valid=epoint_set(_MIPP_ wx,wx,LSB,W);

        if (!valid || W->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID_PUBLIC_KEY;
        if (res==0 && full)
        {
            ecurve_mult(_MIPP_ r,W,W);
            if (W->marker!=MR_EPOINT_INFINITY) res=MR_P1363_INVALID_PUBLIC_KEY; 
        }
        epoint_free(_MIPP_ W);
    }
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/*** P1363 EC GF(p) primitives ***/
/* See P1363 documentation for specification */
/* Note the support for point compression */

P1363_API int ECPSVDP_DH(BOOL (*idle)(void),ecp_domain *DOM,octet *S,octet *WDx,octet *WDy,int LSB,octet *Z)    
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,s,wx,wy,z;
    BOOL valid;
    epoint *W;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ S,s);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        W=epoint_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wx);

        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wy);
             valid=epoint_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint_set(_MIPP_ wx,wx,LSB,W);

        if (!valid) res=MR_P1363_ERROR;
    
        ecurve_mult(_MIPP_ s,W,W);
        if (W->marker==MR_EPOINT_INFINITY) res=MR_P1363_ERROR; 
        else
        {
            epoint_get(_MIPP_ W,z,z);
            convert_big_octet(_MIPP_ z,Z);
        }
        epoint_free(_MIPP_ W);
    }

    mirkill(_MIPP_ z);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int ECPSVDP_DHC(BOOL (*idle)(void),ecp_domain *DOM,octet *S,octet *WDx,octet *WDy,int LSB,BOOL compatible,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,r,s,wx,wy,z,k,ik,t;
    BOOL valid;
    epoint *W;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    ik=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->K,k);
        convert_octet_big(_MIPP_ S,s);

        if (compatible)
        {
            convert_octet_big(_MIPP_ &DOM->IK,ik);
            mad(_MIPP_ ik,s,ik,r,r,t);   /* t=s/k mod r */
        }
        else copy(s,t);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        W=epoint_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wx);

        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wy);
             valid=epoint_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint_set(_MIPP_ wx,wx,LSB,W);
        if (!valid) res=MR_P1363_ERROR;
        else
        {
            mad(_MIPP_ t,k,t,r,r,t);
            ecurve_mult(_MIPP_ t,W,W);
            if (W->marker==MR_EPOINT_INFINITY) res=MR_P1363_ERROR;
            else
            { 
                epoint_get(_MIPP_ W,z,z);
                convert_big_octet(_MIPP_ z,Z);
            }
        } 
        epoint_free(_MIPP_ W);
    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ ik);
    mirkill(_MIPP_ k);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int ECPSVDP_MQV(BOOL (*idle)(void),ecp_domain *DOM,octet *S,octet *U,octet *Vx,octet *WDx,octet *WDy,int LSBWDy,octet *VDx,octet *VDy,int LSBVDy,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,r,s,u,vx,wdx,wdy,vdx,vdy,z,e,t,td;
    epoint *P,*WDP,*VDP;
    BOOL valid;
    int h,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    wdx=mirvar(_MIPP_ 0);
    wdy=mirvar(_MIPP_ 0);
    vdx=mirvar(_MIPP_ 0);
    vdy=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    e=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    td=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ U,u);

        P=epoint_init(_MIPPO_ );
        convert_octet_big(_MIPP_ Vx,vx);
        
        WDP=epoint_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wdx);
        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wdy);
             valid=epoint_set(_MIPP_ wdx,wdy,0,WDP);
        }
        else valid=epoint_set(_MIPP_ wdx,wdx,LSBWDy,WDP);
        if (!valid) res=MR_P1363_ERROR;
        else
        {
            VDP=epoint_init(_MIPPO_ );
            convert_octet_big(_MIPP_ VDx,vdx);
            if (VDy!=NULL)
            {
                convert_octet_big(_MIPP_ VDy,vdy);
                valid=epoint_set(_MIPP_ vdx,vdy,0,VDP);
            }
            else valid=epoint_set(_MIPP_ vdx,vdx,LSBVDy,VDP);
            if (!valid) res=MR_P1363_ERROR;
            else
            {
                h=DOM->H;
                expint(_MIPP_ 2,h,z);
                copy(vx,t);
                divide(_MIPP_ t,z,z);
                add_r(_MIPP_ t,z,t);
                copy (vdx,td);
                divide(_MIPP_ td,z,z);
                add_r(_MIPP_ td,z,td);

                mad(_MIPP_ t,s,u,r,r,e);
                mad(_MIPP_ e,td,td,r,r,t);
                ecurve_mult2(_MIPP_ e,VDP,t,WDP,P); 
                if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_ERROR; 
                else
                { 
                    epoint_get(_MIPP_ P,z,z);
                    convert_big_octet(_MIPP_ z,Z);
                }
            }
        }
        epoint_free(_MIPP_ P);
        epoint_free(_MIPP_ WDP);
        epoint_free(_MIPP_ VDP);
    }

    mirkill(_MIPP_ td);
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ e);
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ vdy);
    mirkill(_MIPP_ vdx);
    mirkill(_MIPP_ wdy);
    mirkill(_MIPP_ wdx);
    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int ECPSVDP_MQVC(BOOL (*idle)(void),ecp_domain *DOM,octet *S,octet *U,octet *Vx,octet *WDx,octet *WDy,int LSBWDy,octet *VDx,octet *VDy,int LSBVDy,BOOL compatible,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,r,s,u,vx,wdx,wdy,vdx,vdy,z,e,t,td,k,ik;
    epoint *P,*WDP,*VDP;
    BOOL valid;
    int h,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    ik=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    wdx=mirvar(_MIPP_ 0);
    wdy=mirvar(_MIPP_ 0);
    vdx=mirvar(_MIPP_ 0);
    vdy=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    e=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    td=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->K,k); 
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ U,u);

        P=epoint_init(_MIPPO_ );
        convert_octet_big(_MIPP_ Vx,vx);
        
        WDP=epoint_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wdx);
        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wdy);
             valid=epoint_set(_MIPP_ wdx,wdy,0,WDP);
        }
        else valid=epoint_set(_MIPP_ wdx,wdx,LSBWDy,WDP);
        if (!valid) res=MR_P1363_ERROR;
        else
        {
            VDP=epoint_init(_MIPPO_ );
            convert_octet_big(_MIPP_ VDx,vdx);
            if (VDy!=NULL)
            {
                 convert_octet_big(_MIPP_ VDy,vdy);
                 valid=epoint_set(_MIPP_ vdx,vdy,0,VDP);
            }
            else valid=epoint_set(_MIPP_ vdx,vdx,LSBVDy,VDP);
            if (!valid) res=MR_P1363_ERROR;
            else
            {
                h=DOM->H;
                expint(_MIPP_ 2,h,z);
                copy(vx,t);
                divide(_MIPP_ t,z,z);
                add_r(_MIPP_ t,z,t);
                copy (vdx,td);
                divide(_MIPP_ td,z,z);
                add_r(_MIPP_ td,z,td);
                mad(_MIPP_ t,s,u,r,r,e);
                if (compatible)
                {
                    convert_octet_big(_MIPP_ &DOM->IK,ik);
                    mad(_MIPP_ e,ik,e,r,r,e);
                }
                mad(_MIPP_ e,k,e,r,r,e);
                mad(_MIPP_ e,td,td,r,r,t);
                ecurve_mult2(_MIPP_ e,VDP,t,WDP,P); 
                if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID_PUBLIC_KEY; 
                else
                {
                    epoint_get(_MIPP_ P,z,z);
                    convert_big_octet(_MIPP_ z,Z);
                }
            }
        }
        epoint_free(_MIPP_ P);
        epoint_free(_MIPP_ WDP);
        epoint_free(_MIPP_ VDP);
    }

    mirkill(_MIPP_ td);
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ e);
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ vdy);
    mirkill(_MIPP_ vdx);
    mirkill(_MIPP_ wdy);
    mirkill(_MIPP_ wdx);
    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ k);
    mirkill(_MIPP_ ik);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);
    err=mr_mip->ERNUM;

    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int ECPSP_NR(BOOL (*idle)(void),ecp_domain *DOM,octet *SEED,octet *S,octet *F,octet *C,octet *D)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,gx,gy,r,s,f,c,d,u,vx;
    epoint *G,*V;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ F,f);
        if (compare(f,r)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {
        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init(_MIPPO_ );
        V=epoint_init(_MIPPO_ );
        epoint_set(_MIPP_ gx,gy,0,G);

        strong_init(_MIPP_ SEED->len,SEED->val,0L);
        do {
            if (mr_mip->ERNUM) break;

            strong_bigrand(_MIPP_ r,u);
            if (DOM->PC.store==0)
            {
                ecurve_mult(_MIPP_ u,G,V);        
                epoint_get(_MIPP_ V,vx,vx);
            }
            else
                mul_brick(_MIPP_ &DOM->PC,u,vx,vx);
              
            divide(_MIPP_ vx,r,r);
            add_r(_MIPP_ vx,f,c);
            divide(_MIPP_ c,r,r);
 
        } while (size(c)==0);
        strong_rng(_MIPP_ SEED->len,SEED->val);

        if (res==0)
        {
            mad(_MIPP_ s,c,s,r,r,d);
            subtract(_MIPP_ u,d,d);
            if (size(d)<0) add_r(_MIPP_ d,r,d);
            convert_big_octet(_MIPP_ c,C);
            convert_big_octet(_MIPP_ d,D);
        }
        epoint_free(_MIPP_ V);
        epoint_free(_MIPP_ G);
    }

    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int ECPVP_NR(BOOL (*idle)(void),ecp_domain *DOM,octet *Wx,octet *Wy,int LSBWy,octet *C,octet *D,octet *F)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,a,b,gx,gy,wx,wy,f,c,d;
    int err,res=0;
    epoint *G,*W,*P;
    BOOL valid; 
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);

    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ C,c);
        convert_octet_big(_MIPP_ D,d);
        if (size(c)<1 || compare(c,r)>=0 || size(d)<0 || compare(d,r)>=0) 
            res=MR_P1363_INVALID;
    }

    if (res==0)
    {
        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init(_MIPPO_ );
        W=epoint_init(_MIPPO_ );
        P=epoint_init(_MIPPO_ );
        epoint_set(_MIPP_ gx,gy,0,G);

        convert_octet_big(_MIPP_ Wx,wx);
        if (Wy!=NULL)
        {
             convert_octet_big(_MIPP_ Wy,wy);
             valid=epoint_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint_set(_MIPP_ wx,wx,LSBWy,W);
        if (!valid) res=MR_P1363_ERROR;
        else
        {         
            ecurve_mult2(_MIPP_ d,G,c,W,P);
            if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID;
            else
            {
                epoint_get(_MIPP_ P,f,f);
                divide(_MIPP_ f,r,r);
                subtract(_MIPP_ c,f,f);
                if (size(f)<0) add_r(_MIPP_ f,r,f);
                convert_big_octet(_MIPP_ f,F);
            }
        }
        epoint_free(_MIPP_ P);
        epoint_free(_MIPP_ W);
        epoint_free(_MIPP_ G);
    }

    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int ECPSP_DSA(BOOL (*idle)(void),ecp_domain *DOM,octet *SEED,octet *S,octet *F,octet *C,octet *D)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,gx,gy,r,s,f,c,d,u,vx;
    epoint *G,*V;
    int err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ F,f);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init(_MIPPO_ );
        V=epoint_init(_MIPPO_ );
        epoint_set(_MIPP_ gx,gy,0,G);

        strong_init(_MIPP_ SEED->len,SEED->val,0L);
        do {
            if (mr_mip->ERNUM) break;
            strong_bigrand(_MIPP_ r,u);
            if (DOM->PC.store==0)
            {
                ecurve_mult(_MIPP_ u,G,V);        
                epoint_get(_MIPP_ V,vx,vx);
            }
            else
                mul_brick(_MIPP_ &DOM->PC,u,vx,vx);

            copy(vx,c); 
            divide(_MIPP_ c,r,r);
            if (size(c)==0) continue;
            xgcd(_MIPP_ u,r,u,u,u);
            mad(_MIPP_ s,c,f,r,r,d);
            mad(_MIPP_ u,d,u,r,r,d);
  
        } while (size(d)==0);
        strong_rng(_MIPP_ SEED->len,SEED->val);
       
        if (res==0)
        {
            convert_big_octet(_MIPP_ c,C);
            convert_big_octet(_MIPP_ d,D);
        }
        epoint_free(_MIPP_ V);
        epoint_free(_MIPP_ G);
    }

    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int ECPVP_DSA(BOOL (*idle)(void),ecp_domain *DOM,octet *Wx,octet *Wy,int LSBWy,octet *C,octet *D,octet *F)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,r,a,b,gx,gy,wx,wy,f,c,d,h2;
    int err,res=0;
    epoint *G,*W,*P;
    BOOL valid; 
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    h2=mirvar(_MIPP_ 0);

    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        convert_octet_big(_MIPP_ &DOM->Q,q);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ C,c);
        convert_octet_big(_MIPP_ D,d);
        convert_octet_big(_MIPP_ F,f);
        if (size(c)<1 || compare(c,r)>=0 || size(d)<1 || compare(d,r)>=0) 
            res=MR_P1363_INVALID;
    }

    if (res==0)
    {
        xgcd(_MIPP_ d,r,d,d,d);
        mad(_MIPP_ f,d,f,r,r,f);
        mad(_MIPP_ c,d,c,r,r,h2);

        ecurve_init(_MIPP_ a,b,q,MR_PROJECTIVE);
        G=epoint_init(_MIPPO_ );
        W=epoint_init(_MIPPO_ );
        P=epoint_init(_MIPPO_ );
        epoint_set(_MIPP_ gx,gy,0,G);

        convert_octet_big(_MIPP_ Wx,wx);
        if (Wy!=NULL)
        {
             convert_octet_big(_MIPP_ Wy,wy);
             valid=epoint_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint_set(_MIPP_ wx,wx,LSBWy,W);
        if (!valid) res=MR_P1363_ERROR;
        else
        {
            ecurve_mult2(_MIPP_ f,G,h2,W,P);
            if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID;
            else
            {
                epoint_get(_MIPP_ P,d,d);
                divide(_MIPP_ d,r,r);
                if (compare(d,c)!=0) res=MR_P1363_INVALID;
                else convert_big_octet(_MIPP_ f,F);
            }
        }
        epoint_free(_MIPP_ P);
        epoint_free(_MIPP_ W);
        epoint_free(_MIPP_ G);
    }

    mirkill(_MIPP_ h2);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/*** EC GF(2^m) primitives - support functions ***/
/* destroy the EC GF(2^m) domain structure */

P1363_API void EC2_DOMAIN_KILL(ec2_domain *DOM)
{
    miracl *mr_mip=NULL;
    OCTET_KILL(&DOM->A);
    OCTET_KILL(&DOM->B);
    OCTET_KILL(&DOM->R);
    OCTET_KILL(&DOM->Gx);
    OCTET_KILL(&DOM->Gy);
    OCTET_KILL(&DOM->K);
    OCTET_KILL(&DOM->IK);

    if (DOM->PC.store!=0) 
        ebrick2_end(_MIPP_ &DOM->PC);        

    DOM->words=0; DOM->H=0;
    DOM->a=0; DOM->b=0; DOM->c=0;
}

/* Initialise the EC GF(2^m) domain structure
 * It is assumed that the EC domain details are obtained from a file 
 * or from an array of strings
 * multiprecision numbers are read in to the specified base (normally 16)
 * A suitable file can be generated offline by the MIRACL example program
 * schoof2.exe   
 * Set precompute=TRUE if a precomputed table is to be used to 
 * speed up the calculation x.G mod EC(2^m) 
 * Returns recommended number of bytes to use for octet strings */

P1363_API int EC2_DOMAIN_INIT(ec2_domain *DOM,char *fname,char **params,int base,BOOL precompute)
{ /* get domain details from specified file     */
  /* If input from a file, params=NULL, if input from strings, fname=NULL  */
  /* return max. size in bytes of octet strings */
    FILE *fp;
    miracl *mr_mip;
    BOOL fileinput=TRUE;
    big q,r,gx,gy,a,b,k;
    int aa,bb,cc,bits,bytes,err,res=0;

    if (fname==NULL && params==NULL) return MR_P1363_DOMAIN_NOT_FOUND;
    if (fname==NULL) fileinput=FALSE;

    if (fileinput)
    {
        fp=fopen(fname,"r");
        if (fp==NULL) return MR_P1363_DOMAIN_NOT_FOUND;
        fscanf(fp,"%d\n",&bits);
    }
    else
        sscanf(params[0],"%d\n",&bits);

    DOM->words=12+(bits/MIRACL);

    mr_mip=mirsys(DOM->words,0);
    if (mr_mip==NULL) 
    {
        if (fileinput) fclose(fp);
        return MR_P1363_OUT_OF_MEMORY;
    }
    mr_mip->ERCON=TRUE;
    q=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    if (base<2 || base>60) base=10;
    mr_mip->IOBASE=base;
    
    if (mr_mip->ERNUM) 
    {
        if (fileinput) fclose(fp);
        res=MR_P1363_OUT_OF_MEMORY;
    }

    if (res==0)
    {
        bytes=2+bits/8;
        if (fileinput)
        {
            cinnum(_MIPP_ a,fp);
            cinnum(_MIPP_ b,fp);
            cinnum(_MIPP_ r,fp);
            cinnum(_MIPP_ gx,fp);
            cinnum(_MIPP_ gy,fp);
            fscanf(fp,"%d\n",&aa);
            fscanf(fp,"%d\n",&bb);
            fscanf(fp,"%d\n",&cc);
            fclose(fp);
        }
        else
        {
            cinstr(_MIPP_ a,params[1]);
            cinstr(_MIPP_ b,params[2]);
            cinstr(_MIPP_ r,params[3]);
            cinstr(_MIPP_ gx,params[4]);
            cinstr(_MIPP_ gy,params[5]);
            sscanf(params[6],"%d\n",&aa);
            sscanf(params[7],"%d\n",&bb);
            sscanf(params[8],"%d\n",&cc);
        }
        DOM->M=bits;
        OCTET_INIT(&DOM->A,bytes);
        OCTET_INIT(&DOM->B,bytes);
        OCTET_INIT(&DOM->R,bytes);
        OCTET_INIT(&DOM->Gx,bytes);
        OCTET_INIT(&DOM->Gy,bytes);
        OCTET_INIT(&DOM->K,bytes);
        OCTET_INIT(&DOM->IK,bytes);
        DOM->H=(1+logb2(_MIPP_ r))/2;
        DOM->a=aa; DOM->b=bb; DOM->c=cc;
        expint(_MIPP_ 2,bits,q);    /* q=2^m */

        nroot(_MIPP_ q,2,k);
        premult(_MIPP_ k,2,k);
        add_r(_MIPP_ k,q,k);
        incr(_MIPP_ k,3,k);

        divide(_MIPP_ k,r,k);        /* gets co-factor k */

        convert_big_octet(_MIPP_ a,&DOM->A);
        convert_big_octet(_MIPP_ b,&DOM->B);
        convert_big_octet(_MIPP_ r,&DOM->R);
        convert_big_octet(_MIPP_ gx,&DOM->Gx);
        convert_big_octet(_MIPP_ gy,&DOM->Gy);
        convert_big_octet(_MIPP_ k,&DOM->K);
        xgcd(_MIPP_ k,r,k,k,k);
        convert_big_octet(_MIPP_ k,&DOM->IK);

        DOM->PC.store=0;
        if (precompute) 
            ebrick2_init(_MIPP_ &DOM->PC,gx,gy,a,b,bits,aa,bb,cc,logb2(_MIPP_ r));
    }
    mirkill(_MIPP_ k);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ q);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    if (res<0) return res;
    else return bytes;
}

/* validate EC GF(2^m) domain details - good idea if you got them from
 * some-one else! */

P1363_API int EC2_DOMAIN_VALIDATE(BOOL (*idle)(void),ec2_domain *DOM)
{ /* do domain checks - A16.8 */
    miracl *mr_mip=mirsys(DOM->words,0);
    big q,a,b,r,gx,gy,t;
    epoint *G;
    int i,aa,bb,cc,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    
    mr_mip->ERCON=TRUE;
    mr_mip->NTRY=50;
    set_user_function(_MIPP_ idle);
    q=mirvar(_MIPP_ 0);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        expint(_MIPP_ 2,DOM->M,q);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        aa=DOM->a;
        bb=DOM->b;
        cc=DOM->c;

        nroot(_MIPP_ q,2,t);
        premult(_MIPP_ t,4,t);

        if (compare(r,t)<=0) res=MR_P1363_DOMAIN_ERROR;
        if (size(r)<3 || size(b)==0) res=MR_P1363_DOMAIN_ERROR;
    }

    if (res==0)
    {
        gprime(_MIPP_ 10000);
        if (!isprime(_MIPP_ r)) res=MR_P1363_DOMAIN_ERROR;
    }
    if (res==0)
    {
        if (!ecurve2_init(_MIPP_ DOM->M,aa,bb,cc,a,b,TRUE,MR_AFFINE))
            res=MR_P1363_DOMAIN_ERROR;
    }
    if (res==0)
    {
        G=epoint2_init(_MIPPO_ );
        if (!epoint2_set(_MIPP_ gx,gy,0,G)) res=MR_P1363_DOMAIN_ERROR;
        if (G->marker==MR_EPOINT_INFINITY) res=MR_P1363_DOMAIN_ERROR;
        else
        { 
            ecurve2_mult(_MIPP_ r,G,G);
            if (G->marker!=MR_EPOINT_INFINITY) res=MR_P1363_DOMAIN_ERROR;
        }
        epoint2_free(_MIPP_ G);
    }                  
       
    if (res==0)
    { /* MOV conditon */
        convert(_MIPP_ 1,t);
        for (i=0;i<50;i++)
        {
            mad(_MIPP_ t,q,q,r,r,t);
            if (size(t)==1)
            {
                res=MR_P1363_DOMAIN_ERROR;
                break;
            }
        }
    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    mirkill(_MIPP_ q);
    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* validate an EC GF(2^m) public key. Set full=TRUE for fuller, 
 * but more time-consuming test 
 * provide either both x and y coordinates, or NULL for y 
 * and a single bit LSB */

P1363_API int EC2_PUBLIC_KEY_VALIDATE(BOOL (*idle)(void),ec2_domain *DOM,BOOL full,octet *Wx,octet *Wy,int LSB)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,r,wx,wy,t;
    epoint *W;
    BOOL valid;
    int M,aa,bb,cc,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a;
        bb=DOM->b;
        cc=DOM->c;
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ Wx,wx);
        if (Wy!=NULL) convert_octet_big(_MIPP_ Wy,wy);
        if (logb2(_MIPP_ wx)>M || logb2(_MIPP_ wy)>M) res=MR_P1363_INVALID_PUBLIC_KEY;
    }
    if (res==0)
    {
        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        W=epoint2_init(_MIPPO_ );

        if (Wy!=NULL)
             valid=epoint2_set(_MIPP_ wx,wy,0,W);
        else valid=epoint2_set(_MIPP_ wx,wx,LSB,W);

        if (!valid || W->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID_PUBLIC_KEY;
        if (res==0 && full)
        {
            ecurve2_mult(_MIPP_ r,W,W);
            if (W->marker!=MR_EPOINT_INFINITY) res=MR_P1363_INVALID_PUBLIC_KEY; 
        }
        epoint2_free(_MIPP_ W);
    }
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/* Calculate a public/private EC GF(2^m) key pair. W=S.g mod EC(2^m),
 * where S is the secret key and W is the public key
 * Returns a single bit which can be used for "point compression" 
 * If SEED is NULL then the private key is provided externally in S
 * otherwise it is generated randomly internally
 * (Set Wy to NULL if y-coordinate not needed) */

P1363_API int EC2_KEY_PAIR_GENERATE(BOOL (*idle)(void),ec2_domain *DOM,octet *SEED,octet*S,octet *Wx,octet *Wy)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,r,gx,gy,s,wx,wy,t;
    epoint *G,*W;
    int M,aa,bb,cc;
    int err,res=0;

    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a;
        bb=DOM->b;
        cc=DOM->c;

        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);

        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        G=epoint2_init(_MIPPO_ );
        W=epoint2_init(_MIPPO_ );
        epoint2_set(_MIPP_ gx,gy,0,G);

        if (SEED!=NULL)
        {
            strong_init(_MIPP_ SEED->len,SEED->val,0L);
            strong_bigrand(_MIPP_ r,s);
        }
        else
        {
            convert_octet_big(_MIPP_ S,s);
            divide(_MIPP_ s,r,r);
        }
        if (DOM->PC.store==0)
        {
            ecurve2_mult(_MIPP_ s,G,W);        
            res=epoint2_get(_MIPP_ W,wx,wy);
        }
        else
            res=mul2_brick(_MIPP_ &DOM->PC,s,wx,wy);
        if (SEED!=NULL) 
        {
            strong_rng(_MIPP_ SEED->len,SEED->val);
            convert_big_octet(_MIPP_ s,S);
        }
        convert_big_octet(_MIPP_ wx,Wx);
        if (Wy!=NULL) convert_big_octet(_MIPP_ wy,Wy);

        epoint2_free(_MIPP_ W);
        epoint2_free(_MIPP_ G);

    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/*** P1363 EC GF(2^m) primitives ***/
/* See P1363 documentation for specification */
/* Note the support for point compression */

P1363_API int EC2SVDP_DH(BOOL (*idle)(void),ec2_domain *DOM,octet *S,octet *WDx,octet *WDy,int LSB,octet *Z)    
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,s,wx,wy,z;
    BOOL valid;
    epoint *W;
    int M,aa,bb,cc,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a;
        bb=DOM->b;
        cc=DOM->c;
        
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ S,s);

        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        W=epoint2_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wx);

        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wy);
             valid=epoint2_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint2_set(_MIPP_ wx,wx,LSB,W);

        if (!valid) res=MR_P1363_ERROR;
        else
        {
            ecurve2_mult(_MIPP_ s,W,W);
            if (W->marker==MR_EPOINT_INFINITY) res=MR_P1363_ERROR; 
            else
            { 
                epoint2_get(_MIPP_ W,z,z);
                convert_big_octet(_MIPP_ z,Z);
            }
        }
        epoint2_free(_MIPP_ W);
    }

    mirkill(_MIPP_ z);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int EC2SVDP_DHC(BOOL (*idle)(void),ec2_domain *DOM,octet *S,octet *WDx,octet *WDy,int LSB,BOOL compatible,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,r,s,wx,wy,z,k,ik,t;
    BOOL valid;
    epoint *W;
    int M,aa,bb,cc,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    ik=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a; bb=DOM->b; cc=DOM->c;
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->K,k);

        convert_octet_big(_MIPP_ S,s);

        if (compatible)
        {
            convert_octet_big(_MIPP_ &DOM->IK,ik);
            mad(_MIPP_ ik,s,ik,r,r,t);   /* t=s/k mod r */
        }
        else copy(s,t);

        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        W=epoint2_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wx);

        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wy);
             valid=epoint2_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint2_set(_MIPP_ wx,wx,LSB,W);

        if (!valid) res=MR_P1363_ERROR;
        else
        {    
            mad(_MIPP_ t,k,t,r,r,t);
            ecurve2_mult(_MIPP_ t,W,W);
            if (W->marker==MR_EPOINT_INFINITY) res=MR_P1363_ERROR; 
            else
            {
                epoint2_get(_MIPP_ W,z,z);
                convert_big_octet(_MIPP_ z,Z);
            }
        }
        epoint2_free(_MIPP_ W);
    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ ik);
    mirkill(_MIPP_ k);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int EC2SVDP_MQV(BOOL (*idle)(void),ec2_domain *DOM,octet *S,octet *U,octet *Vx,octet *WDx,octet *WDy,int LSBWDy,octet *VDx,octet *VDy,int LSBVDy,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,r,s,u,vx,wdx,wdy,vdx,vdy,z,e,t,td;
    epoint *P,*WDP,*VDP;
    BOOL valid;
    int M,aa,bb,cc,h,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    wdx=mirvar(_MIPP_ 0);
    wdy=mirvar(_MIPP_ 0);
    vdx=mirvar(_MIPP_ 0);
    vdy=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    e=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    td=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a; bb=DOM->b;  cc=DOM->c; 
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->A,a);

        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ U,u);

        P=epoint2_init(_MIPPO_ );
        convert_octet_big(_MIPP_ Vx,vx);
        
        WDP=epoint2_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wdx);
        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wdy);
             valid=epoint2_set(_MIPP_ wdx,wdy,0,WDP);
        }
        else valid=epoint2_set(_MIPP_ wdx,wdx,LSBWDy,WDP);
        if (!valid) res=MR_P1363_ERROR;
        else
        {
            VDP=epoint2_init(_MIPPO_ );
            convert_octet_big(_MIPP_ VDx,vdx);
            if (VDy!=NULL)
            {
                convert_octet_big(_MIPP_ VDy,vdy);
                valid=epoint2_set(_MIPP_ vdx,vdy,0,VDP);
            }
            else valid=epoint2_set(_MIPP_ vdx,vdx,LSBVDy,VDP);
            if (!valid) res=MR_P1363_ERROR;
            else
            {
                h=DOM->H;
                expint(_MIPP_ 2,h,z);
                copy(vx,t);
                divide(_MIPP_ t,z,z);
                add_r(_MIPP_ t,z,t);
                copy (vdx,td);
                divide(_MIPP_ td,z,z);
                add_r(_MIPP_ td,z,td);
                mad(_MIPP_ t,s,u,r,r,e);
                mad(_MIPP_ e,td,td,r,r,t);
                ecurve2_mult2(_MIPP_ e,VDP,t,WDP,P); 
                if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_ERROR; 
                else
                {
                    epoint2_get(_MIPP_ P,z,z);
                    convert_big_octet(_MIPP_ z,Z);
                }
            }
        }
        epoint2_free(_MIPP_ P);
        epoint2_free(_MIPP_ WDP);
        epoint2_free(_MIPP_ VDP);
    }

    mirkill(_MIPP_ td);
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ e);
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ vdy);
    mirkill(_MIPP_ vdx);
    mirkill(_MIPP_ wdy);
    mirkill(_MIPP_ wdx);
    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int EC2SVDP_MQVC(BOOL (*idle)(void),ec2_domain *DOM,octet *S,octet *U,octet *Vx,octet *WDx,octet *WDy,int LSBWDy,octet *VDx,octet *VDy,int LSBVDy,BOOL compatible,octet *Z)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,r,s,u,vx,wdx,wdy,vdx,vdy,z,e,t,td,k,ik;
    epoint *P,*WDP,*VDP;
    BOOL valid;
    int M,aa,bb,cc,h,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    ik=mirvar(_MIPP_ 0);
    k=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    wdx=mirvar(_MIPP_ 0);
    wdy=mirvar(_MIPP_ 0);
    vdx=mirvar(_MIPP_ 0);
    vdy=mirvar(_MIPP_ 0);
    z=mirvar(_MIPP_ 0);
    e=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    td=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a; bb=DOM->b; cc=DOM->c; 
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->K,k); 
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->A,a);

        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ U,u);

        P=epoint2_init(_MIPPO_ );
        convert_octet_big(_MIPP_ Vx,vx);
        
        WDP=epoint2_init(_MIPPO_ );
        convert_octet_big(_MIPP_ WDx,wdx);
        if (WDy!=NULL)
        {
             convert_octet_big(_MIPP_ WDy,wdy);
             valid=epoint2_set(_MIPP_ wdx,wdy,0,WDP);
        }
        else valid=epoint2_set(_MIPP_ wdx,wdx,LSBWDy,WDP);
        if (!valid) res=MR_P1363_ERROR;
        else
        { 
            VDP=epoint2_init(_MIPPO_ );
            convert_octet_big(_MIPP_ VDx,vdx);
            if (VDy!=NULL)
            {
                 convert_octet_big(_MIPP_ VDy,vdy);
                 valid=epoint2_set(_MIPP_ vdx,vdy,0,VDP);
            }
            else valid=epoint2_set(_MIPP_ vdx,vdx,LSBVDy,VDP);
            if (!valid) res=MR_P1363_ERROR;
            else
            {
                h=DOM->H;
                expint(_MIPP_ 2,h,z);
                copy(vx,t);
                divide(_MIPP_ t,z,z);
                add_r(_MIPP_ t,z,t);
                copy (vdx,td);
                divide(_MIPP_ td,z,z);
                add_r(_MIPP_ td,z,td);
                mad(_MIPP_ t,s,u,r,r,e);
                if (compatible)
                {
                    convert_octet_big(_MIPP_ &DOM->IK,ik);
                    mad(_MIPP_ e,ik,e,r,r,e);
                }
                mad(_MIPP_ e,k,e,r,r,e);
                mad(_MIPP_ e,td,td,r,r,t);
                ecurve2_mult2(_MIPP_ e,VDP,t,WDP,P); 
                if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID_PUBLIC_KEY; 
                else
                {  
                    epoint2_get(_MIPP_ P,z,z);
                    convert_big_octet(_MIPP_ z,Z);
                }
            }
        }
        epoint2_free(_MIPP_ P);
        epoint2_free(_MIPP_ WDP);
        epoint2_free(_MIPP_ VDP);
    }

    mirkill(_MIPP_ td);
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ e);
    mirkill(_MIPP_ z);
    mirkill(_MIPP_ vdy);
    mirkill(_MIPP_ vdx);
    mirkill(_MIPP_ wdy);
    mirkill(_MIPP_ wdx);
    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ k);
    mirkill(_MIPP_ ik);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);
    err=mr_mip->ERNUM;

    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int EC2SP_NR(BOOL (*idle)(void),ec2_domain *DOM,octet *SEED,octet *S,octet *F,octet *C,octet *D)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,gx,gy,r,s,f,c,d,u,vx;
    epoint *G,*V;
    int M,aa,bb,cc,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a; bb=DOM->b;  cc=DOM->c; 
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ F,f);
        if (compare(f,r)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {
        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        G=epoint2_init(_MIPPO_ );
        V=epoint2_init(_MIPPO_ );
        epoint2_set(_MIPP_ gx,gy,0,G);

        strong_init(_MIPP_ SEED->len,SEED->val,0L);
        do {
            if (mr_mip->ERNUM) break;
            strong_bigrand(_MIPP_ r,u);
            if (DOM->PC.store==0)
            {
                ecurve2_mult(_MIPP_ u,G,V);        
                epoint2_get(_MIPP_ V,vx,vx);
            }
            else
                mul2_brick(_MIPP_ &DOM->PC,u,vx,vx);

            divide(_MIPP_ vx,r,r);
            add_r(_MIPP_ vx,f,c);
            divide(_MIPP_ c,r,r);
 
        } while (size(c)==0);
        strong_rng(_MIPP_ SEED->len,SEED->val);
        if (res==0)
        {
            mad(_MIPP_ s,c,s,r,r,d);
            subtract(_MIPP_ u,d,d);
            if (size(d)<0) add_r(_MIPP_ d,r,d);
            convert_big_octet(_MIPP_ c,C);
            convert_big_octet(_MIPP_ d,D);
        }
        epoint2_free(_MIPP_ V);
        epoint2_free(_MIPP_ G);
    }

    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int EC2VP_NR(BOOL (*idle)(void),ec2_domain *DOM,octet *Wx,octet *Wy,int LSBWy,octet *C,octet *D,octet *F)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big r,a,b,gx,gy,wx,wy,f,c,d;
    int M,aa,bb,cc,err,res=0;
    epoint *G,*W,*P;
    BOOL valid; 
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);

    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a; bb=DOM->b;  cc=DOM->c; 
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ C,c);
        convert_octet_big(_MIPP_ D,d);
        if (size(c)<1 || compare(c,r)>=0 || size(d)<0 || compare(d,r)>=0) 
            res=MR_P1363_INVALID;
    }

    if (res==0)
    {
        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        G=epoint2_init(_MIPPO_ );
        W=epoint2_init(_MIPPO_ );
        P=epoint2_init(_MIPPO_ );
        epoint2_set(_MIPP_ gx,gy,0,G);

        convert_octet_big(_MIPP_ Wx,wx);
        if (Wy!=NULL)
        {
             convert_octet_big(_MIPP_ Wy,wy);
             valid=epoint2_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint2_set(_MIPP_ wx,wx,LSBWy,W);
        if (!valid) res=MR_P1363_ERROR;
        else
        {
            ecurve2_mult2(_MIPP_ d,G,c,W,P);
            if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID;
            else
            {
                epoint2_get(_MIPP_ P,f,f);
                divide(_MIPP_ f,r,r);
                subtract(_MIPP_ c,f,f);
                if (size(f)<0) add_r(_MIPP_ f,r,f);
                convert_big_octet(_MIPP_ f,F);
             }
        }
        epoint2_free(_MIPP_ P);
        epoint2_free(_MIPP_ W);
        epoint2_free(_MIPP_ G);
    }

    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int EC2SP_DSA(BOOL (*idle)(void),ec2_domain *DOM,octet *SEED,octet *S,octet *F,octet *C,octet *D)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big a,b,gx,gy,r,s,f,c,d,u,vx;
    epoint *G,*V;
    int M,aa,bb,cc,err,res=0;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    u=mirvar(_MIPP_ 0);
    vx=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a; bb=DOM->b;  cc=DOM->c; 
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ S,s);
        convert_octet_big(_MIPP_ F,f);

        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        G=epoint2_init(_MIPPO_ );
        V=epoint2_init(_MIPPO_ );
        epoint2_set(_MIPP_ gx,gy,0,G);

        strong_init(_MIPP_ SEED->len,SEED->val,0L);
        do {
            if (mr_mip->ERNUM) break;

            strong_bigrand(_MIPP_ r,u);
            if (DOM->PC.store==0)
            {
                ecurve2_mult(_MIPP_ u,G,V);        
                epoint2_get(_MIPP_ V,vx,vx);
            }
            else
                mul2_brick(_MIPP_ &DOM->PC,u,vx,vx);

            copy(vx,c); 
            divide(_MIPP_ c,r,r);
            if (size(c)==0) continue;

            xgcd(_MIPP_ u,r,u,u,u);
            mad(_MIPP_ s,c,f,r,r,d);
            mad(_MIPP_ u,d,u,r,r,d);
  
        } while (size(d)==0);
        strong_rng(_MIPP_ SEED->len,SEED->val);
        if (res==0)
        {
            convert_big_octet(_MIPP_ c,C);
            convert_big_octet(_MIPP_ d,D);
        }
        epoint2_free(_MIPP_ V);
        epoint2_free(_MIPP_ G);

    }

    mirkill(_MIPP_ vx);
    mirkill(_MIPP_ u);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int EC2VP_DSA(BOOL (*idle)(void),ec2_domain *DOM,octet *Wx,octet *Wy,int LSBWy,octet *C,octet *D,octet *F)
{
    miracl *mr_mip=mirsys(DOM->words,0);
    big r,a,b,gx,gy,wx,wy,f,c,d,h2,t;
    int M,aa,bb,cc,err,res=0;
    epoint *G,*W,*P;
    BOOL valid; 
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    a=mirvar(_MIPP_ 0);
    b=mirvar(_MIPP_ 0);
    gx=mirvar(_MIPP_ 0);
    gy=mirvar(_MIPP_ 0);
    r=mirvar(_MIPP_ 0);
    wx=mirvar(_MIPP_ 0);
    wy=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    d=mirvar(_MIPP_ 0);
    h2=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;

    if (res==0)
    {
        M=DOM->M;
        aa=DOM->a; bb=DOM->b;  cc=DOM->c; 
        convert_octet_big(_MIPP_ &DOM->R,r);
        convert_octet_big(_MIPP_ &DOM->Gx,gx);
        convert_octet_big(_MIPP_ &DOM->Gy,gy);
        convert_octet_big(_MIPP_ &DOM->B,b);
        convert_octet_big(_MIPP_ &DOM->A,a);
        convert_octet_big(_MIPP_ C,c);
        convert_octet_big(_MIPP_ D,d);
        convert_octet_big(_MIPP_ F,f);
        if (size(c)<1 || compare(c,r)>=0 || size(d)<1 || compare(d,r)>=0) 
            res=MR_P1363_INVALID;
    }

    if (res==0)
    {
        xgcd(_MIPP_ d,r,d,d,d);
        mad(_MIPP_ f,d,f,r,r,f);
        mad(_MIPP_ c,d,c,r,r,h2);

        ecurve2_init(_MIPP_ M,aa,bb,cc,a,b,FALSE,MR_PROJECTIVE);
        G=epoint2_init(_MIPPO_ );
        W=epoint2_init(_MIPPO_ );
        P=epoint2_init(_MIPPO_ );
        epoint2_set(_MIPP_ gx,gy,0,G);

        convert_octet_big(_MIPP_ Wx,wx);
        if (Wy!=NULL)
        {
             convert_octet_big(_MIPP_ Wy,wy);
             valid=epoint2_set(_MIPP_ wx,wy,0,W);
        }
        else valid=epoint2_set(_MIPP_ wx,wx,LSBWy,W);
        if (!valid) res=MR_P1363_ERROR;
        else
        {        
            ecurve2_mult2(_MIPP_ f,G,h2,W,P);
            if (P->marker==MR_EPOINT_INFINITY) res=MR_P1363_INVALID;
            else
            {
                epoint2_get(_MIPP_ P,d,d);
                divide(_MIPP_ d,r,r);
                if (compare(d,c)!=0) res=MR_P1363_INVALID;
                else convert_big_octet(_MIPP_ f,F);
            }
        }
        epoint2_free(_MIPP_ P);
        epoint2_free(_MIPP_ W);
        epoint2_free(_MIPP_ G);
    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ h2);
    mirkill(_MIPP_ d);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ wy);
    mirkill(_MIPP_ wx);
    mirkill(_MIPP_ r);
    mirkill(_MIPP_ gy);
    mirkill(_MIPP_ gx);
    mirkill(_MIPP_ b);
    mirkill(_MIPP_ a);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

/*** RSA/RW primitives - support functions ***/
/* destroy the Public Key structure */

P1363_API void IF_PUBLIC_KEY_KILL(if_public_key *PUB)
{
    OCTET_KILL(&PUB->N);
    PUB->words=0; PUB->e=0;
}

/* destroy the Private Key structure */

P1363_API void IF_PRIVATE_KEY_KILL(if_private_key *PRIV)
{
    OCTET_KILL(&PRIV->P);
    OCTET_KILL(&PRIV->Q);
    OCTET_KILL(&PRIV->DP);
    OCTET_KILL(&PRIV->DQ);
    OCTET_KILL(&PRIV->C);
    PRIV->words=0; 
}

/* generate an RSA/RW key pair. The size of the public key in bits
 * is passed as a parameter. If the exponent E is even, then an RW key pair
 * is generated, otherwise an RSA key pair */

P1363_API int IF_KEY_PAIR(BOOL (*idle)(void),octet *SEED,int bits,int E,if_private_key *PRIV,if_public_key *PUB)
{ /* A16.11/A16.12 more or less */
    miracl *mr_mip;
    int hE,m,r,bytes,hbytes,words,err,res=0;
    big p,q,dp,dq,c,n,t,p1,q1;
    BOOL RW;
    words=24+(bits/MIRACL);
    mr_mip=mirsys(words,0);
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    mr_mip->NTRY=50;
    set_user_function(_MIPP_ idle);
    p=mirvar(_MIPP_ 0);
    q=mirvar(_MIPP_ 0);
    dp=mirvar(_MIPP_ 0);
    dq=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);
    p1=mirvar(_MIPP_ 0);
    q1=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    RW=FALSE;
    if (E%2==0)
    {
        RW=TRUE;   /* Rabin-Williams */
        hE=E/2;
    }
    if (res==0)
    {
        strong_init(_MIPP_ SEED->len,SEED->val,0L);

        PRIV->words=words;
        PUB->words=words;
        PUB->e=E;
    
        bytes=2+bits/8;
        OCTET_INIT(&PUB->N,bytes);
        hbytes=2+(bytes/2);
        OCTET_INIT(&PRIV->P,hbytes);
        OCTET_INIT(&PRIV->Q,hbytes);
        OCTET_INIT(&PRIV->DP,hbytes);
        OCTET_INIT(&PRIV->DQ,hbytes);
        OCTET_INIT(&PRIV->C,hbytes);
        gprime(_MIPP_ 10000);
        forever
        {
            if (mr_mip->ERNUM) break;
            m=(bits+1)/2;
            expint(_MIPP_ 2,m,t);
            do
            {
                if (mr_mip->ERNUM) break;
                strong_bigrand(_MIPP_ t,p);
            } while (logb2(_MIPP_ p)<m); 
            if (remain(_MIPP_ p,2)==0) incr(_MIPP_ p,1,p);
            if (RW) 
            { /* make p=3 mod 8 */
                r=remain(_MIPP_ p,8);
                incr(_MIPP_ p,(3-r)%8,p);
            }
            do
            {
                if (mr_mip->ERNUM) break;
                if (RW) incr(_MIPP_ p,6,p);
                incr(_MIPP_ p,1,p);
                if (RW)
                {
                    if (hE==1) r=1;
                    else r=remain(_MIPP_ p,hE);
                } 
                else r=remain(_MIPP_ p,E);
                incr(_MIPP_ p,1,p);
                if (r==0) continue;
            } while (!isprime(_MIPP_ p));
            expint(_MIPP_ 2,bits,t);
            divide(_MIPP_ t,p,t);
            expint(_MIPP_ 2,bits-1,c);
            divide(_MIPP_ c,p,c);
            incr(_MIPP_ c,1,c);
            do
            {
                if (mr_mip->ERNUM) break;
                strong_bigrand(_MIPP_ t,q);
            } while (compare(q,c)<0);
            if (remain(_MIPP_ q,2)==0) incr(_MIPP_ q,1,q);

            if (RW) 
            { /* make q=7 mod 8 */
                r=remain(_MIPP_ q,8);
                incr(_MIPP_ q,(7-r)%8,q);
            }
            do
            {
                if (mr_mip->ERNUM) break;
                if (RW) incr(_MIPP_ q,6,q);
                incr(_MIPP_ q,1,q);
                if (RW)
                {
                    if (hE==1) r=1;
                    else r=remain(_MIPP_ q,hE);
                } 
                else r=remain(_MIPP_ q,E);
                incr(_MIPP_ q,1,q);
                if (r==0) continue;
            } while (!isprime(_MIPP_ q));
            multiply(_MIPP_ p,q,n);
            if (logb2(_MIPP_ n)!=bits) continue;  /* very rare! */
            decr(_MIPP_ p,1,p1);
            decr(_MIPP_ q,1,q1);
            multiply(_MIPP_ p1,q1,c);
            egcd(_MIPP_ p1,q1,t);
            divide(_MIPP_ c,t,c);             /* c=LCM(p-1,q-1) */
            if (RW) subdiv(_MIPP_ c,2,c);
            convert(_MIPP_ E,t);
           
            if (xgcd(_MIPP_ t,c,dp,dp,dp)!=1) continue;
            break;
        }
        copy(dp,dq); 
        divide(_MIPP_ dp,p1,p1);
        divide(_MIPP_ dq,q1,q1);
        xgcd(_MIPP_ q,p,c,c,c);           /* c=1/q mod p */
      
        strong_rng(_MIPP_ SEED->len,SEED->val);
        convert_big_octet(_MIPP_ n,&PUB->N);
        convert_big_octet(_MIPP_ p,&PRIV->P);
        convert_big_octet(_MIPP_ q,&PRIV->Q);
        convert_big_octet(_MIPP_ dp,&PRIV->DP);
        convert_big_octet(_MIPP_ dq,&PRIV->DQ);
        convert_big_octet(_MIPP_ c,&PRIV->C);
    }
       
    mirkill(_MIPP_ t);
    mirkill(_MIPP_ q1);
    mirkill(_MIPP_ p1);
    mirkill(_MIPP_ n);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ dq);
    mirkill(_MIPP_ dp);
    mirkill(_MIPP_ q);
    mirkill(_MIPP_ p);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    if (res<0) return res;
    else return bytes;
}

static void private_key_op(_MIPD_ big p,big q,big dp,big dq,big c,big i,big s)
{ /* internal:- basic RSA/RW decryption operation */
    big jp,jq;
    jp=mirvar(_MIPP_ 0);
    jq=mirvar(_MIPP_ 0);
    powmod(_MIPP_ i,dp,p,jp);
    powmod(_MIPP_ i,dq,q,jq);
    subtract(_MIPP_ jp,jq,jp);
    mad(_MIPP_ c,jp,jp,p,p,s);
    if (size(s)<0) add_r(_MIPP_ s,p,s);
    multiply(_MIPP_ s,q,jp);
    add_r(_MIPP_ jq,jp,s);
    mirkill(_MIPP_ jq);
    mirkill(_MIPP_ jp);
}

/*** P1363 RSA/RW primitives ***/
/* See P1363 documentation for more details */

P1363_API int IFEP_RSA(BOOL (*idle)(void),if_public_key *PUB,octet *F,octet *G)
{
    miracl *mr_mip=mirsys(PUB->words,0);
    int e,err,res=0;
    big f,g,n;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    f=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PUB->N,n);
        convert_octet_big(_MIPP_ F,f);
        if (compare(f,n)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {    
        e=PUB->e;
        power(_MIPP_ f,e,n,g);
        convert_big_octet(_MIPP_ g,G);
    }

    mirkill(_MIPP_ n);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ f);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int IFDP_RSA(BOOL (*idle)(void),if_private_key *PRIV,octet *G,octet *F)
{
    miracl *mr_mip=mirsys(PRIV->words,0);
    int err,res=0;
    big f,g,p,q,dp,dq,c,n;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    f=mirvar(_MIPP_ 0);
    g=mirvar(_MIPP_ 0);
    p=mirvar(_MIPP_ 0);
    q=mirvar(_MIPP_ 0);
    dp=mirvar(_MIPP_ 0);
    dq=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);

    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PRIV->P,p);
        convert_octet_big(_MIPP_ &PRIV->Q,q);
        convert_octet_big(_MIPP_ &PRIV->DP,dp);
        convert_octet_big(_MIPP_ &PRIV->DQ,dq);
        convert_octet_big(_MIPP_ &PRIV->C,c);
        convert_octet_big(_MIPP_ G,g);
        multiply(_MIPP_ p,q,n);
        if (compare(g,n)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {    
        private_key_op(_MIPP_ p,q,dp,dq,c,g,f);
        convert_big_octet(_MIPP_ f,F);
    }

    mirkill(_MIPP_ n);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ dq);
    mirkill(_MIPP_ dp);
    mirkill(_MIPP_ q);
    mirkill(_MIPP_ p);
    mirkill(_MIPP_ g);
    mirkill(_MIPP_ f);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int IFSP_RSA1(BOOL (*idle)(void),if_private_key *PRIV,octet *F,octet *S)
{
    miracl *mr_mip=mirsys(PRIV->words,0);
    int err,res=0;
    big f,s,p,q,dp,dq,c,n;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    p=mirvar(_MIPP_ 0);
    q=mirvar(_MIPP_ 0);
    dp=mirvar(_MIPP_ 0);
    dq=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);

    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PRIV->P,p);
        convert_octet_big(_MIPP_ &PRIV->Q,q);
        convert_octet_big(_MIPP_ &PRIV->DP,dp);
        convert_octet_big(_MIPP_ &PRIV->DQ,dq);
        convert_octet_big(_MIPP_ &PRIV->C,c);
        convert_octet_big(_MIPP_ F,f);
        multiply(_MIPP_ p,q,n);
        if (compare(f,n)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {    
        private_key_op(_MIPP_ p,q,dp,dq,c,f,s);
        convert_big_octet(_MIPP_ s,S);
    }

    mirkill(_MIPP_ n);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ dq);
    mirkill(_MIPP_ dp);
    mirkill(_MIPP_ q);
    mirkill(_MIPP_ p);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int IFVP_RSA1(BOOL (*idle)(void),if_public_key *PUB,octet *S,octet *F)
{
    miracl *mr_mip=mirsys(PUB->words,0);
    int e,err,res=0;
    big f,s,n;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PUB->N,n);
        convert_octet_big(_MIPP_ S,s);
        if (compare(s,n)>=0) res=MR_P1363_INVALID;
    }
    if (res==0)
    {        
        e=PUB->e;
        power(_MIPP_ s,e,n,f);
        convert_big_octet(_MIPP_ f,F);
    }

    mirkill(_MIPP_ n);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int IFSP_RSA2(BOOL (*idle)(void),if_private_key *PRIV,octet *F,octet *S)
{
    miracl *mr_mip=mirsys(PRIV->words,0);
    int err,res=0;
    big f,s,p,q,dp,dq,c,n,t;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    p=mirvar(_MIPP_ 0);
    q=mirvar(_MIPP_ 0);
    dp=mirvar(_MIPP_ 0);
    dq=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);

    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PRIV->P,p);
        convert_octet_big(_MIPP_ &PRIV->Q,q);
        convert_octet_big(_MIPP_ &PRIV->DP,dp);
        convert_octet_big(_MIPP_ &PRIV->DQ,dq);
        convert_octet_big(_MIPP_ &PRIV->C,c);
        convert_octet_big(_MIPP_ F,f);
        multiply(_MIPP_ p,q,n);
        if (remain(_MIPP_ f,16)!=12) res=MR_P1363_BAD_ASSUMPTION;
        if (compare(f,n)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {
        private_key_op(_MIPP_ p,q,dp,dq,c,f,s);
        subtract(_MIPP_ n,s,t);
        if (compare(s,t)>0)
            convert_big_octet(_MIPP_ t,S);
        else
            convert_big_octet(_MIPP_ s,S);

    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ n);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ dq);
    mirkill(_MIPP_ dp);
    mirkill(_MIPP_ q);
    mirkill(_MIPP_ p);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int IFVP_RSA2(BOOL (*idle)(void),if_public_key *PUB,octet *S,octet *F)
{
    miracl *mr_mip=mirsys(PUB->words,0);
    int e,err,res=0;
    big f,s,n;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);
   
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PUB->N,n);
        convert_octet_big(_MIPP_ S,s);
        decr(_MIPP_ n,1,f);
        subdiv(_MIPP_ f,2,f);
        if (compare(s,f)>0) res=MR_P1363_INVALID;
    }
    if (res==0)
    {        
        e=PUB->e;
        power(_MIPP_ s,e,n,f);
        if (remain(_MIPP_ f,16)==12) 
            convert_big_octet(_MIPP_ f,F);
        else
        {
            subtract(_MIPP_ n,f,f);
            if (remain(_MIPP_ f,16)==12) 
                convert_big_octet(_MIPP_ f,F);
            else
                res=MR_P1363_INVALID;
        }
    }

    mirkill(_MIPP_ n);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int IFSP_RW(BOOL (*idle)(void),if_private_key *PRIV,octet *F,octet *S)
{
    miracl *mr_mip=mirsys(PRIV->words,0);
    int err,res=0;
    big f,s,p,q,dp,dq,c,n,t;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    p=mirvar(_MIPP_ 0);
    q=mirvar(_MIPP_ 0);
    dp=mirvar(_MIPP_ 0);
    dq=mirvar(_MIPP_ 0);
    c=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);
    t=mirvar(_MIPP_ 0);

    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PRIV->P,p);
        convert_octet_big(_MIPP_ &PRIV->Q,q);
        convert_octet_big(_MIPP_ &PRIV->DP,dp);
        convert_octet_big(_MIPP_ &PRIV->DQ,dq);
        convert_octet_big(_MIPP_ &PRIV->C,c);
        convert_octet_big(_MIPP_ F,f);
        multiply(_MIPP_ p,q,n);
        if (remain(_MIPP_ f,16)!=12) res=MR_P1363_BAD_ASSUMPTION;
        if (compare(f,n)>=0) res=MR_P1363_BAD_ASSUMPTION;
    }
    if (res==0)
    {
        if (jack(_MIPP_ f,n)!=1)
            subdiv(_MIPP_ f,2,f);
        private_key_op(_MIPP_ p,q,dp,dq,c,f,s);
        subtract(_MIPP_ n,s,t);
        if (compare(s,t)>0)
            convert_big_octet(_MIPP_ t,S);
        else
            convert_big_octet(_MIPP_ s,S);

    }

    mirkill(_MIPP_ t);
    mirkill(_MIPP_ n);
    mirkill(_MIPP_ c);
    mirkill(_MIPP_ dq);
    mirkill(_MIPP_ dp);
    mirkill(_MIPP_ q);
    mirkill(_MIPP_ p);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

P1363_API int IFVP_RW(BOOL (*idle)(void),if_public_key *PUB,octet *S,octet *F)
{
    miracl *mr_mip=mirsys(PUB->words,0);
    int e,err,res=0;
    big f,s,n,t1,t2;
    if (mr_mip==NULL) return MR_P1363_OUT_OF_MEMORY;
    mr_mip->ERCON=TRUE;
    set_user_function(_MIPP_ idle);
    s=mirvar(_MIPP_ 0);
    f=mirvar(_MIPP_ 0);
    n=mirvar(_MIPP_ 0);
    t1=mirvar(_MIPP_ 0);
    t2=mirvar(_MIPP_ 0);
   
    if (mr_mip->ERNUM) res=MR_P1363_OUT_OF_MEMORY;
    if (res==0)
    {
        convert_octet_big(_MIPP_ &PUB->N,n);
        convert_octet_big(_MIPP_ S,s);
        decr(_MIPP_ n,1,f);
        subdiv(_MIPP_ f,2,f);
        if (compare(s,f)>0) res=MR_P1363_INVALID;
    }
    if (res==0)
    {        
        e=PUB->e;
        power(_MIPP_ s,e,n,t1);
        subtract(_MIPP_ n,t1,t2);

        if (remain(_MIPP_ t1,16)==12) 
            convert_big_octet(_MIPP_ t1,F);
        else
        {
            if (remain(_MIPP_ t1,8)==6)
            {
                premult(_MIPP_ t1,2,f);
                convert_big_octet(_MIPP_ f,F);
            }
            else
            { 
                if (remain(_MIPP_ t2,16)==12)
                    convert_big_octet(_MIPP_ t2,F);
                else
                {
                    if (remain(_MIPP_ t2,8)==6)
                    {
                        premult(_MIPP_ t2,2,f);
                        convert_big_octet(_MIPP_ f,F);
                    }
                    else res=MR_P1363_INVALID;

                }  
                    
            }
                
        }
    }

    mirkill(_MIPP_ t2);
    mirkill(_MIPP_ t1);
    mirkill(_MIPP_ n);
    mirkill(_MIPP_ f);
    mirkill(_MIPP_ s);

    err=mr_mip->ERNUM;
    mirexit(_MIPPO_ );
    if (err==MR_ERR_OUT_OF_MEMORY) return MR_P1363_OUT_OF_MEMORY;
    if (err==MR_ERR_DIV_BY_ZERO) return MR_P1363_DIV_BY_ZERO;
    if (err!=0) return -(1000+err);
    return res;
}

