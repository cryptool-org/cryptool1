/*
 *  MIRACL P1363 header file
 *  DL - Discrete Logarithm
 *  ECp - GF(p) Elliptic Curve
 *  EC2 - GF(2^m) Elliptic Curve
 *  IF - Integer factorisation-based methods
 *  Copyright (c) 2000 Shamus Software Ltd.
 */

#ifndef P1363_H
#define P1363_H

#include <miracl.h>

#ifdef MR_P1363_DLL

#ifdef P1363_DLL
#define P1363_API __declspec(dllexport)
#else
#define P1363_API __declspec(dllimport)
#endif

#else
#define P1363_API
#endif

#define MR_P1363_OK                     0
#define MR_P1363_DOMAIN_ERROR          -1
#define MR_P1363_INVALID_PUBLIC_KEY    -2
#define MR_P1363_ERROR                 -3
#define MR_P1363_INVALID               -4
#define MR_P1363_DOMAIN_NOT_FOUND      -5
#define MR_P1363_OUT_OF_MEMORY         -6
#define MR_P1363_DIV_BY_ZERO           -7
#define MR_P1363_BAD_ASSUMPTION        -8

/* portable representation of a big positive number */

typedef struct
{
    short len;
    char *val;
} octet;

/* Discrete Log. domain parameters */

typedef struct
{
    int words;
    octet Q;
    octet R;
    octet G;
    octet K;
    octet IK;
    int H;
    brick PC;
} dl_domain;

/* ECp domain parameters */

typedef struct
{
    int words;
    octet Q;
    octet A;
    octet B;
    octet R;
    octet Gx;
    octet Gy;
    octet K;
    octet IK;
    int H;
    ebrick PC;
} ecp_domain;

/* EC2 domain parameters */

typedef struct
{
    int words;
    int M;
    octet A;
    octet B;
    octet R;
    octet Gx;
    octet Gy;
    octet K;
    octet IK;
    int H;
    int a,b,c;
    ebrick2 PC;
} ec2_domain;

/* IF Public Key */

typedef struct
{
    int words;
    int e;
    octet N;
} if_public_key;

/* IF Private Key */

typedef struct
{
    int words;
    octet P;
    octet Q;
    octet DP;
    octet DQ;
    octet C;
} if_private_key;

/* Octet string handlers */

extern P1363_API BOOL OCTET_INIT(octet *,int);
extern P1363_API void OCTET_CLEAR(octet *);
extern P1363_API void OCTET_COPY(octet *,octet *);
extern P1363_API int  OCTET_COMPARE(octet *,octet *);
extern P1363_API BOOL OCTET_PAD(octet *,int);
extern P1363_API void OCTET_JOIN(octet *,octet *);
extern P1363_API void OCTET_OUTPUT(octet *);
extern P1363_API void OCTET_KILL(octet *);

/* P1363 Auxiliary Functions */

extern P1363_API void MGF1(octet *,int,octet *);
extern P1363_API BOOL EMSA1(octet *,char *,int,octet *);
extern P1363_API BOOL EMSA2(octet *,char *,int,octet *);
extern P1363_API BOOL EME1_ENCODE(octet *,octet *,int,octet *,octet *);
extern P1363_API BOOL EME1_DECODE(octet *,int,octet *,octet *);
extern P1363_API void KDF1(octet *,octet *,octet *);
extern P1363_API void RANDOM_START(int,char *,octet *);

/* DL primitives - support functions */

extern P1363_API void DL_DOMAIN_KILL(dl_domain *);
extern P1363_API int  DL_DOMAIN_INIT(dl_domain *,char *,char **,int,BOOL);
extern P1363_API int  DL_DOMAIN_VALIDATE(BOOL (*)(void),dl_domain *);
extern P1363_API int  DL_KEY_PAIR_GENERATE(BOOL (*)(void),dl_domain *,octet *,octet *,octet *);
extern P1363_API int  DL_PUBLIC_KEY_VALIDATE(BOOL (*)(void),dl_domain *,BOOL,octet *);

/* P1363 DL Primitives */

extern P1363_API int DLSVDP_DH(BOOL (*)(void),dl_domain *,octet *,octet *,octet *);
extern P1363_API int DLSVDP_DHC(BOOL (*)(void),dl_domain *,octet *,octet *,BOOL,octet *);
extern P1363_API int DLSVDP_MQV(BOOL (*)(void),dl_domain *,octet *,octet *,octet *,octet *,octet *,octet *);
extern P1363_API int DLSVDP_MQVC(BOOL (*)(void),dl_domain *,octet *,octet *,octet *,octet *,octet *,BOOL,octet *);
extern P1363_API int DLVP_NR(BOOL (*)(void),dl_domain *,octet *,octet *,octet *,octet *);
extern P1363_API int DLSP_NR(BOOL (*)(void),dl_domain *,octet *,octet *,octet *,octet *,octet *);
extern P1363_API int DLVP_DSA(BOOL (*)(void),dl_domain *,octet *,octet *,octet *,octet *);
extern P1363_API int DLSP_DSA(BOOL (*)(void),dl_domain *,octet *,octet *,octet *,octet *,octet *);

/* ECP primitives - support functions */

extern P1363_API void ECP_DOMAIN_KILL(ecp_domain *);
extern P1363_API int  ECP_DOMAIN_INIT(ecp_domain *,char *,char **,int,BOOL);
extern P1363_API int  ECP_DOMAIN_VALIDATE(BOOL (*)(void),ecp_domain *);
extern P1363_API int  ECP_KEY_PAIR_GENERATE(BOOL (*)(void),ecp_domain *,octet *,octet *,octet *,octet *);
extern P1363_API int  ECP_PUBLIC_KEY_VALIDATE(BOOL (*)(void),ecp_domain *,BOOL,octet *,octet *,int);

/* P1363 ECP primitives */

extern P1363_API int ECPSVDP_DH(BOOL (*)(void),ecp_domain *,octet *,octet *,octet *,int,octet *);
extern P1363_API int ECPSVDP_DHC(BOOL (*)(void),ecp_domain *,octet *,octet *,octet *,int,BOOL,octet *);
extern P1363_API int ECPSVDP_MQV(BOOL (*)(void),ecp_domain *,octet *,octet *,octet *,octet *,octet *,int,octet *,octet *,int,octet *);
extern P1363_API int ECPSVDP_MQVC(BOOL (*)(void),ecp_domain *,octet *,octet *,octet *,octet *,octet *,int,octet *,octet *,int,BOOL,octet *);
extern P1363_API int ECPSP_NR(BOOL (*)(void),ecp_domain *,octet *,octet *,octet *,octet *,octet *);
extern P1363_API int ECPVP_NR(BOOL (*)(void),ecp_domain *,octet *,octet *,int,octet *,octet *,octet *);
extern P1363_API int ECPSP_DSA(BOOL (*)(void),ecp_domain *,octet *,octet *,octet *,octet *,octet *);
extern P1363_API int ECPVP_DSA(BOOL (*)(void),ecp_domain *,octet *,octet *,int,octet *,octet *,octet *);

/* EC2 primitives - support functions */

extern P1363_API void EC2_DOMAIN_KILL(ec2_domain *);
extern P1363_API int  EC2_DOMAIN_INIT(ec2_domain *,char *,char **,int,BOOL);
extern P1363_API int  EC2_DOMAIN_VALIDATE(BOOL (*)(void),ec2_domain *);
extern P1363_API int  EC2_KEY_PAIR_GENERATE(BOOL (*)(void),ec2_domain *,octet *,octet *,octet *,octet *);
extern P1363_API int  EC2_PUBLIC_KEY_VALIDATE(BOOL (*)(void),ec2_domain *,BOOL,octet *,octet *,int);

/* P1363 ECP primitives */

extern P1363_API int EC2SVDP_DH(BOOL (*)(void),ec2_domain *,octet *,octet *,octet *,int,octet *);
extern P1363_API int EC2SVDP_DHC(BOOL (*)(void),ec2_domain *,octet *,octet *,octet *,int,BOOL,octet *);
extern P1363_API int EC2SVDP_MQV(BOOL (*)(void),ec2_domain *,octet *,octet *,octet *,octet *,octet *,int,octet *,octet *,int,octet *);
extern P1363_API int EC2SVDP_MQVC(BOOL (*)(void),ec2_domain *,octet *,octet *,octet *,octet *,octet *,int,octet *,octet *,int,BOOL,octet *);
extern P1363_API int EC2SP_NR(BOOL (*)(void),ec2_domain *,octet *,octet *,octet *,octet *,octet *);
extern P1363_API int EC2VP_NR(BOOL (*)(void),ec2_domain *,octet *,octet *,int,octet *,octet *,octet *);
extern P1363_API int EC2SP_DSA(BOOL (*)(void),ec2_domain *,octet *,octet *,octet *,octet *,octet *);
extern P1363_API int EC2VP_DSA(BOOL (*)(void),ec2_domain *,octet *,octet *,int,octet *,octet *,octet *);

/* RSA/RW primitives - support functions */

extern P1363_API void IF_PUBLIC_KEY_KILL(if_public_key *);
extern P1363_API void IF_PRIVATE_KEY_KILL(if_private_key *);
extern P1363_API int  IF_KEY_PAIR(BOOL (*)(void),octet *,int,int,if_private_key *,if_public_key *);

/* P1363 RSA/RW primitives */

extern P1363_API int IFEP_RSA(BOOL (*)(void),if_public_key *,octet *,octet *);
extern P1363_API int IFDP_RSA(BOOL (*)(void),if_private_key *,octet *,octet *);
extern P1363_API int IFSP_RSA1(BOOL (*)(void),if_private_key *,octet *,octet *);
extern P1363_API int IFVP_RSA1(BOOL (*)(void),if_public_key *,octet *,octet *);
extern P1363_API int IFSP_RSA2(BOOL (*)(void),if_private_key *,octet *,octet *);
extern P1363_API int IFVP_RSA2(BOOL (*)(void),if_public_key *,octet *,octet *);
extern P1363_API int IFSP_RW(BOOL (*)(void),if_private_key *,octet *,octet *);
extern P1363_API int IFVP_RW(BOOL (*)(void),if_public_key *,octet *,octet *);

#endif

