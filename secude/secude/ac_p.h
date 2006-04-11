/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/ac_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/
#ifndef _SECUDE_AC_H
#define _SECUDE_AC_H

#if !defined(SECUDE_AUTHENTICODE_INCLUDE) || !SECUDE_AUTHENTICODE_INCLUDE
#error do not include this file, include <secude/ac.h>
#endif

#include <secude/af.h> /* oder so... */

typedef struct authenticode_infos {
    Boolean commercial;
    char *friendlyname;
    char *url;
    Boolean add_signingtime;
} AuthenticodeInfo_struct;

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV authenticode_hash_file SEC_PROTOTYPE_3(
    char *          , filename, 
    AlgId *         , algid, 
    OctetString **  , phash_result
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV authenticode_extract_auth SEC_PROTOTYPE_2(
    char *          , filename, 
    OctetString **  , pauth_block
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV authenticode_append_auth SEC_PROTOTYPE_2(
    char *          , filename,
    OctetString *   , auth_block
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV authenticode_verify_file SEC_PROTOTYPE_2(
    PSE     , pse,
    char *  , filename
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV authenticode_sign_file SEC_PROTOTYPE_4(
    PSE                         , pse, 
    char *                      , filename, 
    AlgId *                     , digest_AI, 
    AuthenticodeInfo_struct *   , acinfo
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV authenticode_countersign_file SEC_PROTOTYPE_3(
    PSE     , pse, 
    char *  , filename, 
    AlgId * , digest_AI
);



#endif /* _SECUDE_AC_H */

