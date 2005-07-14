/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssysteme GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2001
 *
 ******************************************/

#ifndef _SECUDE_CAPREGEN_H
#define _SECUDE_CAPREGEN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include <secude/af.h>


/* types */

typedef struct RSAKeyWithParams RSAKeyWithParams;
struct RSAKeyWithParams {
    RSAPrivateKey *rsakey;
    SEQUENCE_OF_Integer *exponentFactors; /* OPTIONAL */
    SEQUENCE_OF_Integer *exponentAddends; /* OPTIONAL */
    OctetString *random; /* OPTIONAL */
};


typedef SEQUENCE_OF(RSAKeyWithParams) SEQUENCE_OF_RSAKeyWithParams;

typedef struct PregeneratedRSAKeys PregeneratedRSAKeys;
struct PregeneratedRSAKeys {
    int keyLength;
    Boolean multSplitting;
    Boolean addSplitting;
    int randomLength;
    int numberOfKeys; /* number of elements in "keys" */
    SEQUENCE_OF_RSAKeyWithParams *keys;
};

typedef struct PregeneratedKeys PregeneratedKeys;
struct PregeneratedKeys {
    int version;
    ObjId *keyAlgorithm;
    void *keys; /* might be NULL, when keyAlgorithm is unknown to e/d functions */
    OctetString *keysDERcode; /* is used, when keyAlgorithm is unknown to e/d functions */
};



/* prototypes */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PregeneratedKeys SEC_PROTOTYPE_1(
    PregeneratedKeys	 *	, pgKeys
);
PregeneratedKeys SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_PregeneratedKeys SEC_PROTOTYPE_1(
    OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_RSAKeyWithParams SEC_PROTOTYPE_1(
    RSAKeyWithParams	 *	, rsaKey
);
RSAKeyWithParams SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_RSAKeyWithParams SEC_PROTOTYPE_1(
    OctetString	 *	, asn1_string
);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* _SECUDE_CAPREGEN_H */

