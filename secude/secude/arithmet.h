/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/arithmet.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*------------------------------------------------------------+-----*/
/*                                                            ! GMD */
/*   ARITHMETIC for LONG INTEGER    V2.0                      +-----*/
/*                                                                  */
/*------------------------------------------------------------------*/
/*                                                                  */
/*    INCLUDE  <arithmetic.h>                                       */
/*                                        DATE 01.06.90             */
/*                                                                  */
/*    Note:                                                         */
/*      arithmetic.h uses option                                    */
/*      -DWLNGxx (xx = 16 bzw 32) (word length of the processor)    */
/*                                                                  */
/*------------------------------------------------------------------*/
#ifndef _ARITHMETIC_
#define _ARITHMETIC_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <secude/sec_glob.h>

/*------------------------------------------------------------------*
 * Definitions of constants depending on the worg length            *
 *------------------------------------------------------------------*/

#define  BYTEL          8       /* bits per byte                    */

#if SIZEOF_L_NUMBER == 16             /* word length 16 bits              */

typedef sec_uint2  L_NUMBER;
typedef sec_uint1  L_NUMBER2;

#define  WBYTES         2       /* bytes per word                   */
#define  WLNG           16      /* word length in bits              */
#define  SWBITS         4       /* LOG2(WLNG)                       */
#define  HSBIT  0x8000
#define  HSBYTE 0xFF00
#define  LSHALF 0xFF

#define   LZ_FERMAT5  { 2, 1, 1 }
#else                           /* word length 32 bits              */

typedef sec_uint4  L_NUMBER;
typedef sec_uint2  L_NUMBER2;
 
#define  WBYTES         4       /* bytes per word                   */
#define  WLNG           32      /* word length in bits              */
#define  SWBITS         5       /* LOG2(WLNG)     G                 */
#define  HSBIT  0x80000000
#define  HSBYTE 0xFF000000
#define  LSHALF 0xFFFF

#define   LZ_FERMAT5  { 1, 0x10001 }
#endif

#ifndef MAXKEYLENGTH
#ifdef SAPSECULIB
#   ifdef DSA_INSTALLED
#       define MAXKEYLENGTH     1024
#   else
#	define MAXKEYLENGTH	512
#   endif
#else
#	define MAXKEYLENGTH	2048
#endif
#endif


/* the additional 4 words are just a precautionary measure;
   if these additional words are too less, there could be 
   inexplanatory crashes (found under Win95 WinNT...)
   translated freely from a text originally from: "-hg- 21.10.96" */

/* Maximum L_NUMBER under normal conditions */
#define MAXLGTH		(((MAXKEYLENGTH) / (WLNG)) + 4)
#define MAXLGTHB (MAXKEYLENGTH/8+4)
/* Maximum L_NUMBER used during key generation (in words) */
#define  MAXGENL        (2 * (MAXLGTH))
#define MAXGENLB (MAXKEYLENGTH/4+4)



#define DEF_ASYM_KEYSIZE 512
#define MIN_ASYM_KEYSIZE 50
#define MAX_ASYM_KEYSIZE MAXKEYLENGTH
#define RSA_PARM(x) (( x ? *(int *)(x) : (DEF_ASYM_KEYSIZE)))

/*------------------------------------------------------------------*
 * L_NUMBER definition                                              *
 *------------------------------------------------------------------*

 *      A multi-precision integer number is stored and processed in *
 *      an array of unsigned long integers. The maximum length of   *
 *      the array is MAXLGTH.                                       *
 *                                                                  *
 *      MP Integer ::=  L_NUMBER [MAXLGTH]                          *
 *                                                                  *
 *      The first element (L_NUMBER[0]) indicates the number of     *
 *      following words which contain the MP integer, starting with *
 *      with least significant integer left (first).                *
 *------------------------------------------------------------------*/

typedef L_NUMBER L_NUMBER_ARRAY[];


#define   LNUMBER



/*---------------------------------------------------------------*
 *  Global L_NUMBERs                                             *
 *---------------------------------------------------------------*/

#define   LZ_NULL     { 0 }
#define   LZ_EINS     { 1, 1 }
#define   LZ_ZWEI     { 1, 2 }
#define   LZ_DREI     { 1, 3 }



/*
 *      L_NUMBER addition/subtraction/division
 *
 */

/* only I >= 0 supported with these macros! */
#define inttoln(I,LI)   ( (I)? ( *(LI) = 1, *((LI)+1) = (I) ) : (*(LI) = 0) )
#define lntoint(L)      (*(L)? ( *((L)+1) ) : 0)
#define checkln(L)      (*(L)? (-(*((L)+*(L))==0) : 0)
#define lngofln(L)      (*(L))
#define lntoINTEGER(L,I)        lntoctets(L,I,0)
#define INTEGERtoln(I,L)        octetstoln(I,L,0,(*(I)).noctets)


#define LNMIN(a,b) (((a)<(b))?(a):(b))
#define LNMAX(a,b) (((a)<(b))?(b):(a))
#define NEG(a) ((~a)+1)

#ifndef SIGN
#define SIGN_BIT  (~(~(L_NUMBER)0 >> 1))
#define SIGN(a) (((a) & SIGN_BIT)?1:0)
#define LNABS(a) (SIGN(a)?NEG(a):(a))
#endif


/*
 *	Several types for SecuDE's algorithm interfaces (needed for crypt prototypes)
 */


struct DES_CTX {
	sec_uint4 iv[2];
	char   padding;
	char des3;
	char des_type;

        sec_uint4 kn[32],kn1[32],kn2[32];

	char 	 	  rem_octets[8];
	int 	 	  rem_noctets;
	PAD_Func *pad;
};


/* types for elliptic curves: */
typedef struct    
{
	int k1;
	int k2;
	int k3;
} pentanomial;

typedef enum { ECP_NONE, ECP_ECPARAMETERS, ECP_NAMEDCURVE, ECP_IMPLICITLYCA} ECPType;

#ifndef USE_NEW_ARITHMETIC

typedef struct
{ 
	int m;                      
	ObjId *basis; 
	union {
		int Trinomial;
		pentanomial Pentanomial;
	} parms;/*(basis->oid_elements)[7]: 1=no parameters, 2=Trinomial, 3=Pentanomial*/
}  char2field;
typedef struct
{
	ObjId *fieldType;  
	union{
		L_NUMBER	Prime_p[MAXLGTH]; 
		char2field  Char_two;
	} parms; /*(fieldType->oid_elements)[5]: 1=Prime_p, 2=Characteristic_two*/
} FieldID;
typedef struct
{
	L_NUMBER a[MAXLGTH];
	L_NUMBER b[MAXLGTH];
	BitString *seed;  /*optional*/
} Curve;
typedef struct
{
	FieldID fieldID;
	int		KeyLength;
	Curve	curve;
	L_NUMBER base[MAXLGTH];
	L_NUMBER order[MAXLGTH];  
	int cofactor;
    int version; /* should be here... */
} ECParameters;

typedef struct {
	ECPType type;
	union {
		ECParameters *ecp;
		ObjId *name;
	} un;
} ECKeyParameter;

typedef ECKeyParameter      		id_ecPublicKey_parm_type;
typedef ECKeyParameter      		ecdsa_with_SHA1_parm_type;

#else /* USE_NEW_ARITHMETIC */

#include "alg_type.h"
typedef struct {
	ECPoint pkey;			/* public key */
	ECPoint skey;			/* private key */
	EC_Parameters param;	/* EC domain parameters */
	BitString * shData1;	/* optional shared data */
	BitString * shData2;	/* optional shared data */
} ECAES_CRYPT_CTX;

typedef EC_KeyParameter      		id_ecPublicKey_parm_type;
typedef EC_KeyParameter      		ecdsa_with_SHA1_parm_type;

#endif /* USE_NEW_ARITHMETIC */

typedef struct
{
	L_NUMBER r[MAXLGTH];  /* r,s > 10^50*/
	L_NUMBER s[MAXLGTH];
} ECDSA_Sig_Value;


#define MAXMODULUSL	MAXKEYLENGTH	/*	maximum length of prim p 	*/
#define MINMODULUSL	320	/*	minimum length of prim p	*/
#define MODULUSSTEPS	8	/*	length of p must be dividable by 64	*/
#define HASHOCTETS	20	/*	length of sha hash bitstring	*/
#define HASHWORDS	(HASHOCTETS/WBYTES)	/*	length of sha hash bitstring	*/
#define HASHBITS	(BYTEL*HASHOCTETS)	/*	length of sha hash bitstring	*/
#define SEEDOCTETS	20	/*	length of random number	*/
#define SEEDWORDS	(SEEDOCTETS/WBYTES)	/*	length of random number	*/
#define SEEDBITS	(BYTEL*SEEDOCTETS)	/*	length of random number	*/

#ifndef USE_NEW_ARITHMETIC
	
typedef	struct	{
	L_NUMBER        x[MAXLGTH];
	L_NUMBER        p[MAXLGTH];
	L_NUMBER        q[MAXLGTH];
	L_NUMBER        g[MAXLGTH];
	}       DSA_Skeys;

typedef	struct	{
	L_NUMBER        y[MAXLGTH];
	L_NUMBER        p[MAXLGTH];
	L_NUMBER        q[MAXLGTH];
	L_NUMBER        g[MAXLGTH];
	}       DSA_Pkeys;

typedef union {
	DSA_Skeys   sk;
	DSA_Pkeys   pk;
	}       DSA_keys;

typedef struct {
	L_NUMBER   r[MAXLGTH];
	L_NUMBER   s[MAXLGTH];
	}       DSA_sig;

typedef	struct	{
	L_NUMBER        p[MAXLGTH];
	L_NUMBER        q[MAXLGTH];
	L_NUMBER        g[MAXLGTH];
	}       DSA_public_part;

#else /* USE_NEW_ARITHMETIC */

typedef	struct	{
	INTEGER       x;
	INTEGER       p;
	INTEGER		  q;
	INTEGER       g;
	}       DSASkeys;

typedef	struct	{
	INTEGER       y;
	INTEGER       p;
	INTEGER       q;
	INTEGER       g;
	}       DSAPkeys;

typedef union {
	DSASkeys   sk;
	DSAPkeys   pk;
	}       DSAkeys;

typedef struct {
	INTEGER   r;
	INTEGER   s;
	}       DSAsig;

typedef	struct	{
	INTEGER       p;
	INTEGER       q;
	INTEGER       g;
	}       DSApublic_part;

#endif /* USE_NEW_ARITHMETIC */



#define  MINKEYL    64       /* Minimale Key Laenge           */
#define  MAXRNDM    521      /*Maximale laenge einer Zufallsz.*/
#define  GEN_N_D 0x01000000
#define _GEN_N_D 0x00FFFFFF

typedef struct	 {
	      L_NUMBER   modul[MAXGENL],
		    p[MAXGENL],
		    q[MAXGENL];
	      }
	      rndmstart;

#ifndef USE_NEW_ARITHMETIC


typedef	struct	{
	L_NUMBER        p[MAXLGTH];
	L_NUMBER        q[MAXLGTH];
	L_NUMBER        sp[MAXLGTH];
	L_NUMBER        sq[MAXLGTH];
	L_NUMBER        u[MAXLGTH];
	L_NUMBER        n[MAXLGTH];
	L_NUMBER        d[MAXLGTH];
	}       Skeys;

typedef	struct	{
	L_NUMBER        n[MAXLGTH];
	L_NUMBER        e[MAXLGTH];
	}       Pkeys;

typedef union {
	Skeys   sk;
	Pkeys   pk;
	}       RSAkeys;


#else /* USE_NEW_ARITHMETIC */


typedef	struct	{
	INTEGER        p;
	INTEGER        q;
	INTEGER        sp;
	INTEGER        sq;
	INTEGER        u;
	INTEGER        n;
	INTEGER        d;
	}       S_keys;

typedef	struct	{
	INTEGER        n;
	INTEGER        e;
	}       P_keys;

typedef union {
	S_keys   sk;
	P_keys   pk;
	}       RSA_keys;


#endif /* USE_NEW_ARITHMETIC */



#ifndef USE_NEW_ARITHMETIC



struct RSA_CRYPT_CTX {
	RSAkeys  K;              /* RSA key fields */
	L_NUMBER ACC[MAXLGTH];   /* residual value */
	int      freesize;       /* free bitlen in ACC */
	int      keysize;       /*  */
	int      blocksize;       /*  */
};

struct SQMODN_CTX {
	RSAkeys  K;              /* RSA key fields */
	L_NUMBER ACC[MAXLGTH];   /* residual value */
	L_NUMBER X[MAXLGTH];   /* hash */
	int      freesize;       /* free bitlen in ACC */
	int      keysize;       /*  */
	int      blocksize;       /*  */
};


#else /* USE_NEW_ARITHMETIC */

struct RSACRYPT_CTX {
	RSA_keys  K;              /* RSA key fields */
	L_NUMBER ACC[MAXLGTH];   /* residual value */
	int      freesize;       /* free bitlen in ACC */
	int      keysize;       /*  */
	int      blocksize;       /*  */
};


struct SQ_MODN_CTX {
	RSA_keys  K;              /* RSA key fields */
	L_NUMBER  ACC[MAXLGTH];   /* residual value */
	L_NUMBER  X[MAXLGTH];   /* hash */
	int      freesize;       /* free bitlen in ACC */
	int      keysize;       /*  */
	int      blocksize;       /*  */
};

#endif /* USE_NEW_ARITHMETIC */



typedef struct {
               sec_uint4 digest[ 5 ];            /* Message digest */
                sec_uint4 len;   
                sec_uint4 noctets;   
                char    octets[64];          
               sec_uint4 data[ 16 ];             /* RMD data buffer */
               } RMD_INFO;


typedef struct {
               sec_uint4 digest[ 5 ];            /* Message digest */
               sec_uint4 countLo, countHi;       /* 64-bit bit count */
               sec_uint4 data[ 16 ];             /* SHS data buffer */
               } SHS_INFO;



typedef struct {
  unsigned char state[16];                                 /* state */
  unsigned char checksum[16];                           /* checksum */
  unsigned int count;                 /* number of bytes, modulo 16 */
  unsigned char buffer[16];                         /* input buffer */
} SEC_MD2_CTX;

typedef struct {
  sec_uint4 state[4];                                   /* state (ABCD) */
  sec_uint4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} SEC_MD4_CTX;

typedef struct {
  sec_uint4 state[4];                                   /* state (ABCD) */
  sec_uint4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} SEC_MD5_CTX;




#ifndef USE_NEW_ARITHMETIC

struct DH_CTX {
	L_NUMBER 	 p[MAXGENL];
	L_NUMBER 	 g[MAXGENL];
	L_NUMBER 	 X[MAXGENL];
	L_NUMBER 	 Y[MAXGENL];
	int	  	 private_value_length;
	int	  	 enc_mode;
	KeyInfo		 keyinfo;
	OctetString	 octetstring;
	BitString	 bitstring;
	char		*buf;
	int	  	 bufsize;
};

#else /* USE_NEW_ARITHMETIC */

struct DFH_CTX {
	INTEGER	 p;
	INTEGER  g;
	INTEGER	 X;
	INTEGER	 Y;
	int	  	 private_value_length;
	int	  	 enc_mode;
	KeyInfo		 keyinfo;
	OctetString	 octetstring;
	BitString	 bitstring;
	char		*buf;
	int	  	 bufsize;
};

#endif /* USE_NEW_ARITHMETIC */

typedef struct {
	sec_uint4 state[ 256 ];
	sec_uint4 x, y;
} RC4KEY;

struct RC_CTX {
	int		  mode;
	unsigned char 	  ivbuf[8];
	unsigned char 	  *iv;
	char 	 	  rem_octets[8];
	int 	 	  rem_noctets;
	unsigned int 	  rc2key[64];
	RC4KEY		  rc4key;
	PAD_Func *pad;
	AlgMode	  algmode;
};





/*	begin of idea.h   */
#define Idea_nofRound                 8 /* number of rounds                   */
#define Idea_userKeyLen               8 /* user key length (8 or larger)      */

/******************************************************************************/
/* Do not change the lines below.                                             */

#define Idea_dataLen                       4 /* plain-/ciphertext block length*/
#define Idea_keyLen    (Idea_nofRound * 6 + 4) /* en-/decryption key length   */

#define Idea_dataSize       (Idea_dataLen * 2) /* 8 bytes = 64 bits           */
#define Idea_userKeySize (Idea_userKeyLen * 2) /* 16 bytes = 128 bits         */
#define Idea_keySize         (Idea_keyLen * 2) /* 104 bytes = 832 bits        */

typedef sec_uint2 Idea_Data[Idea_dataLen];
typedef sec_uint2 Idea_UserKey[Idea_userKeyLen];
typedef sec_uint2 Idea_Key[Idea_keyLen];

typedef Idea_Key	IDEA_KEY_STRUCT;
struct IDEA_CTX {
	char 	 	  rem_octets[8];
	int 	 	  rem_noctets;
	IDEA_KEY_STRUCT 	  key;
	sec_uint1 ivbuf[8];
	sec_uint1 *iv;
	PAD_Func *pad;
	sec_uint1 *included_iv;
};
/*	end of idea.h   */




#ifdef div
#undef div
#endif

#define div	arithmetic_div


#define madd	arithmetic_madd
#define msub	arithmetic_msub
#define mmult	arithmetic_mmult
#define mdiv	arithmetic_mdiv
#define mexp	arithmetic_mexp
#define mexp2	arithmetic_mexp2

#define cadd	arithmetic_cadd
#define add	arithmetic_add
#define sub	arithmetic_sub
#define mult	arithmetic_mult
#define dmult	arithmetic_dmult

#define shift	arithmetic_shift
#define wshift	arithmetic_wshift

#define comp	arithmetic_comp


#define cadd	arithmetic_cadd
#define dmult	arithmetic_dmult
#ifndef __cplusplus
/* xor is an operator in C++ ! */
#define xor	arithmetic_xor
#endif

#define normalize(N)	{ L_NUMBER zero = 0; sub(N,&zero,N); }
/*      define _trans macro inline expanded */
#define trans(src,dst) { register L_NUMBER *stop,*dp = (dst), *sp = (src), len = LNABS(*sp); \
                          if( sp != dp ) {stop = sp;    \
                          for( dp = dp+len, sp = sp+len; sp != stop; ) *dp-- = *sp--; \
                          *dp = *sp; \
                        } }

enum { DH_ENC_ALG_IDEA = 0, DH_ENC_ALG_DES_CBC, DH_ENC_ALG_DES_CBC3, DH_ENC_ALG_MASK = 7, DH_HASH = 8 };


#define SIZEOF_SEC_SIGNATURETIMEDATE 26

#include <secude/crypt.h>



#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* _ARITHMETIC_ */


