/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/filename.h
 *###
 *### global functions:
 *###
 *###*****************************************/
 
#ifndef _SEC_FILENAMES_
#define _SEC_FILENAMES_

/*
 *      F i l e n a m e s
 */
#define PATH_LENGTH 128

#ifdef SAPSECULIB
#define SECUDE_HOME_DIR "sec"
#else
#define SECUDE_HOME_DIR "secude"
#endif

#ifdef _MAC
#define INPUT_DEVICE "CON"
#define PATH_SEPARATION_STRING ":"
#define PATH_SEPARATION_CHAR   ':'
#define SEARCH_PATH_SEP_STRING /* ???*/
#define SEARCH_PATH_SEP_CHAR   /* ???*/
#else   /* non-MAC */

#ifdef SEC_PC

#define INPUT_DEVICE "CON"
#define PATH_SEPARATION_STRING "\\"
#define PATH_SEPARATION_CHAR   '\\'
#define SEARCH_PATH_SEP_STRING ";"
#define SEARCH_PATH_SEP_CHAR   ';'

#else  /* UNIX */

#define INPUT_DEVICE "/dev/tty"
#define PATH_SEPARATION_STRING "/"
#define PATH_SEPARATION_CHAR   '/'
#define SEARCH_PATH_SEP_STRING ":"
#define SEARCH_PATH_SEP_CHAR   ':'

#endif  /* SEC_PC */

#endif  /* _MAC */

#define DEF_PSE             "pse"        /* Default PSE Name                */
#define DEF_PSE_SUFFIX	    ".pse"	 /* Default PSE Suffix		    */
#define DEF_CADIR           "ca"         /* default CA directory            */
#define DEF_CAPSE           "capse"      /* Default PSE Name                */
#define DEF_CAPSE_SUFFIX    ".cse"	 /* Default CA-PSE Suffix	    */

#define VIRTUALPSE_name     "<virtual>"

#define SAPSECUPSE_name	    "SAPSYS.pse"
#define SAPdefault_name     "SAPdefault"
#ifdef SAPSECULIB
#undef DEF_PSE
#define DEF_PSE SAPSECUPSE_name
#endif

#define SECdefault_name     "__SEC_AC__"

/*
 *      Names of PSE Objects (File-Names in the PSE)
 */
#define Toc_name       	    "Toc"   	 /* Table of contents		                           */
#define PW_name       	    "pse.pw"   	 /* Password    		                           */
#define SignCert_name       "SignCert"   /* Cert for Public Signature Key                          */
#define AuthCert_name       "AuthCert"   /* Cert for Public Authentication Key                          */
#define EncCert_name        "EncCert"    /* Cert for Public Encryption Key                         */
#define Cert_name           "Cert"       /* Cert for Public Signature/Encryption Key               */
#define SignCSet_name       "SignCSet"   /* Set of CrossCertificates for own Public Signature Key  */
#define EncCSet_name        "EncCSet"    /* Set of CrossCertificates for own Public Encryption Key */
#define CSet_name           "CSet"       /* Set of CrossCertificates for own Public Sign./Encr.Key */
#define AuthSK_name         "AuthSK"     /* Secret Authentication Key                                   */
#define SignSK_name         "SignSK"     /* Secret Signature Key                                   */
#define DecSKnew_name       "DecSKnew"   /* Secret Decrypt. Key (new)                              */
#define DecSKold_name       "DecSKold"   /* Secret Decrypt. Key (old)                              */
#define SKnew_name          "SKnew"      /* Secret Key (new)                                       */
#define SKold_name          "SKold"      /* Secret Key (old)                                       */
#define FCPath_name         "FCPath"     /* Forward Certification Path                             */
#define PKRoot_name         "PKRoot"     /* PK of Top-Level Ca (old/new)                           */
#define PKList_name         "PKList"     /* Trusted Public Verific. Keys  (SET_OF ToBeSigned)      */
#define EKList_name         "EKList"     /* Trusted Public Encrypt. Keys  (SET_OF ToBeSigned)      */
#define PCAList_name        "PCAList"    /* Trusted PCA Keys   (SET_OF ToBeSigned)                 */
#define CrossCSet_name      "CrossSet"  /* Set of CrossCertificatePairs                           */
#define CrlSet_name         "CrlSet"     /* Revocation lists of known CAs                          */
#define SerialNumber_name   "SerialNo"   /* Serial number (for CA's only)                          */
#define CRLNumber_name      "CRLSerNo"   /* CRLNumber (monotonically increasing) (for CA's only)   */
#define EDBKey_name         "EDBKey"     /* Symmetric Key for EDB encryption (for DSA's only)      */
#define AliasList_name      "AliasLst"   /* User's AliasList                                       */
#define QuipuPWD_name       "QuipuPWD"   /* User's X.500 password                                  */
#define DHparam_name        "DHparam"    /* Prime p and base g for Diffie-Hellman key agreement    */
#define DSAcommon_name      "DSAcomm"    /* Primes p,q and base g for DSA algorithm                */
#define Random_name         "Random"     /* Random seed                                            */
#define TelesecCert_name    "TelesecCert" /* has to be longer than 8 characters, because this is its name on the smartcard! */

#define PSE_tmpSignatureSK  "SgnSKtmp"   /* temporary PSE object */
#define PSE_tmpDecryptionSK "DecSKtmp"   /* temporary PSE object */
#define PSE_tmpSK           "SKtmp"      /* temporary PSE object */

#define PPolicy_name        "PPolicy"    /* PSE PIN policy */
#define PState_name         "PState"     /* PSE PIN state */
#define RDNAlias_name       "RDNAlias"   /* RDN Aliases for GSS */

#define KEY_POOL            "key_pool"

#define GENPSE_DIR          "genpse"

#define X500_name           "X500"

#define AFDBDIR             "af-db"

#define OBJID_LIST          "objids"

#define CRED_FILE           "cred_v2"

#define EXT_FILE            "CA_exts"
#define CRL_EXT_FILE        "CRL_exts"

#define NO_DEF_EXTS_LABEL   "__NO_DEFAULT_EXTS__"

#define ALIASFILE           "af-alias"
#define AFDB_RDN_ALIAS_FILE "rdntable"

#define policies_name	    "policies"

#define BlindingFactor_name "BlindVal"
#define BlindSigCert_name   "BlindCrt"
#define BlindSigHash_name   "BlindHsh"


#define TESTKEYS "testkeys"

#define ALGS_EC_PK_name    "E-PK"       /* not more than 4 chars */
#define ALGS_EC_SK_name    "E-SK"       /* not more than 4 chars */
#define ALGS_RSA_PK_name    "R-PK"       /* not more than 4 chars */
#define ALGS_RSA_SK_name    "R-SK"       /* not more than 4 chars */
#define ALGS_DSA_PK_name    "D-PK"       /* not more than 4 chars */
#define ALGS_DSA_SK_name    "D-SK"       /* not more than 4 chars */


#define EXT_ENCRYPTION_FILE ".enc"
#define EXT_ENCRYPTION_KEY  ".key"
#define EXT_HASH            ".hsh"
#define EXT_SIGNATURE       ".sig"
#define EXT_CERTIFICATE     ".ctf"
#define EXT_BACKUP          ".BAK"

#define USERDB	 "user"
#define CERTDB	 "cert"
#define CRLDB    "crls"

#define SC_CONFIG_name   "cardrc"	/* Name of the SC-PSE configuration file*/
#define SCT_CONFIG_name  "sctda"      	/* Name of the SCT process data file   	*/
#define SCT_INST_name    "sctrc"        /* Name of the SCT installation file    */


#endif /* _SEC_FILENAMES_ */




