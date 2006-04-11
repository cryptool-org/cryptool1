/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/mscrypto.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef _MSCRYPTO_H
#define _MSCRYPTO_H

#include <secude/af.h>

#ifdef WIN32

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Function to interoperate with MS CryptoAPI */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_convert_RSAPrivateKey_to_PVKBLOB SEC_PROTOTYPE_2(
	RSAPrivateKey	*	, rsapvk,
	KeyType				, keytype
);


/* soon in this theater: Authenticode functions */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WIN32 */
#endif /* _MSCRYPTO_H */

