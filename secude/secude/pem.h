/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/pem.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*-----------------------------------------------------------------------*/
/*  INCLUDE FILE  pem.h  (Privacy Enhanced Mail Interface)               */
/*  Definition of structures and types for PEM                           */
/*-----------------------------------------------------------------------*/

#ifndef _PEM_
#define _PEM_

#include <secude/af.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 *  P E M : Privacy Enhanced Mail (RFC 1421 - 1424) interface definition
 *
 */

#define DEFAULT_MSG_ENC_ALG  "DES-CBC"
#define DEFAULT_MIC_ALG      "RSA-MD5"
#define DEFAULT_MIC_ENC_ALG  "RSA"
#define DEFAULT_DEK_ENC_ALG  "RSA"


/*
 * External initialization of PEM RFC 1421 - 1424 Definitions (pem_init.c):
 *
 *
 *
 * struct SKW  proc_type_t[] = {
 *         { "ENCRYPTED",  PEM_ENC        },
 *         { "CRL",        PEM_CRL        },
 *         { "CRL-RETRIEVAL-REQUEST",  PEM_CRL_RETRIEVAL_REQUEST        },
 *         { "MIC-ONLY",   PEM_MCO        },
 *         { "MIC-CLEAR",  PEM_MCC        },
 *         { "MIC-BIN",  PEM_MIC_BIN        },
 *         { "ENCRYPTED-BIN",  PEM_ENC_BIN        },
 *         { "PKLIST",  PEM_PKLIST        },
 *         { 0,            NO_PEM         }
 * };
 * 
 * struct SKW content_domain[] = {
 *         { "RFC822",     PEM_RFC822     },
 *         { "MIME",       PEM_MIME       },
 *         { 0,            0              }
 * };
 * 
 * 
 * struct SKW  rXH_kwl[] =  { 
 *         { "Proc-Type",                PEM_PROC_TYPE           },
 *         { "CRL",                      PEM_CRL_                },
 *         { "Content-Domain",           PEM_CONTENT_DOMAIN      },
 *         { "DEK-Info",                 PEM_DEK_INFO            },
 *         { "Originator-ID-Asymmetric", PEM_SENDER_ID           },
 *         { "Originator-ID-Symmetric",  PEM_SENDER_IDS          },
 *         { "Originator-Certificate",   PEM_CERTIFICATE         },
 *         { "Issuer-Certificate",       PEM_ISSUER_CERTIFICATE  },
 *         { "MIC-Info",                 PEM_MIC_INFO            },
 *         { "Recipient-ID-Asymmetric",  PEM_RECIPIENT_ID        },
 *         { "Recipient-ID-Symmetric",   PEM_ID_SYMMETRIC        },
 *         { "Key-Info",                 PEM_KEY_INFO            },
 *         { "Issuer",                   PEM_ISSUER              },
 *         { 0,                          0                       }
 * };                           
 * 
 * char    PEM_Boundary_Begin[] = "-----BEGIN PRIVACY-ENHANCED MESSAGE-----";
 * char    PEM_Boundary_End[]   = "-----END PRIVACY-ENHANCED MESSAGE-----";
 * char    PEM_Boundary_Com[]   = "PRIVACY-ENHANCED MESSAGE-----";
 * char    PEM_Boundary_BB[]    = "-----BEGIN ";
 * char    PEM_Boundary_EB[]    = "-----END ";
 * 
 *
 *       Default Algorithms:
 *
 * 
 * char  *DEK_ENC_ALG = DEFAULT_DEK_ENC_ALG;    "RSA"    
 * char  *MIC_ALG     = DEFAULT_MIC_ALG;        "RSA-MD5"
 * char  *MIC_ENC_ALG = DEFAULT_MIC_ENC_ALG;    "RSA"   
 * char  *MSG_ENC_ALG = DEFAULT_MSG_ENC_ALG;    "DES-CBC"
 * 
 */


struct SKW {
        char           *name;
        int             value;
};



typedef enum {
        RXH_empty,
        RXH_PROC_TYPE,
        RXH_CRL_,
        RXH_CONTENT_DOMAIN,
        RXH_DEK_INFO,
        RXH_SENDER_ID,
        RXH_SENDER_IDS,
        RXH_CERTIFICATE,
        RXH_ISSUER_CERTIFICATE,
        RXH_MIC_INFO,
        RXH_RECIPIENT_ID,
        RXH_ID_SYMMETRIC,
        RXH_KEY_INFO,
        RXH_ISSUER
}               RXH_Header_Fields;

typedef enum {
        PEM_PROC_TYPE,
        PEM_CRL_,
        PEM_CONTENT_DOMAIN,
        PEM_DEK_INFO,
        PEM_SENDER_ID,
        PEM_SENDER_IDS,
        PEM_CERTIFICATE,
        PEM_ISSUER_CERTIFICATE,
        PEM_MIC_INFO,
        PEM_RECIPIENT_ID,
        PEM_ID_SYMMETRIC,
        PEM_KEY_INFO,
        PEM_ISSUER
}               PEM_Header_Fields;

typedef enum {
        PEM_STD = 4,
        PEM_MTT_1 = 4711,			/*** MTT Proc-Type extension ***/
        PEM_EXTENDED_1 = 4812			/*** SECUDE Proc-Type extension ***/
}               PEM_Proc_Type_values;

#define PEM_EXTENDED_1_STRING "SECUDE-1"
#define PEM_MTT_1_STRING "MTT-1"

/***** Enum PEM_Proc_Types *****/
/** PEM Proc-Type Identifier.
  * @ingroup header_pem
  */
typedef enum {
        PEM_ENC,
        PEM_CRL,
        PEM_CRL_RETRIEVAL_REQUEST,
        PEM_MCO,
        PEM_MCC,
        PEM_MIC_BIN,
        PEM_MIC_RAW,
        PEM_ENC_BIN,
        PEM_ENC_RAW,
        PEM_PKLIST,
        NO_PEM
}               PEM_Proc_Types;

/***** Enumeration PEM_Content_Domains *****/
/** @ingroup header_pem
  */
typedef enum {
        PEM_RFC822,
        PEM_MIME,
        PEM_MTT
}               PEM_Content_Domains;


typedef enum {
        PEM_NO_RFC822_HEADER,
        PEM_RFC822_HEADER,
        PEM_RFC822_HEADER_INTERACTIVE
}               PEM_RFC822_Header;


typedef enum         {
        NO_CRL_MESSAGE, 
        CRL_MESSAGE, 
        CRL_RETRIEVAL_REQUEST_MESSAGE 
}        PEM_CRL_Mode;

typedef enum         {
        UPDATE_ASK,
        UPDATE_NO,
        UPDATE_CADB,
        UPDATE_PSE,
        UPDATE_YES,
        UPDATE_ERROR
}        UPDATE_Mode;
typedef enum {
        PEM_error,
        PEM_help,
        PEM_scan,
        PEM_mic_clear,
        PEM_mic_only,
        PEM_encrypted,
        PEM_cert_req,
        PEM_certify,
        PEM_crl,
        PEM_crl_rr,
        PEM_mic_bin,
        PEM_mic_raw,
        PEM_enc_bin,
        PEM_enc_raw,
        PEM_request,
        PEM_pklist
} PemOperation;


#define ONCE_MAX      4   /* number of header fields which appear only  */
                          /* once in a message                          */
                          /* these have to be declared at first in the  */
                          /* rXH_kwl structure (see pem_init.c)         */

#define ELEVEL      302
#define EPSEOPEN    303
#define EPROCT      304
#define EORIGCERT   305
#define EISSCERTF   306
#define EMICINFO    307
#define EDEKINFO    308
#define ERECID      309
#define EKEYINF     310
#define ERIFILE     311
#define ECODE       312
#define ESYMM       313

#define CERTIFY     1
#define SCAN        0


typedef struct PemMessageCanon    PemMessageCanon;
typedef struct PemHeaderCanon     PemHeaderCanon;
typedef struct PemDekCanon        PemDekCanon;
typedef struct PemOriginatorCanon PemOriginatorCanon;
typedef struct PemRecCanon        PemRecCanon;
typedef struct PemMicCanon        PemMicCanon;
typedef struct PemCrlCanon        PemCrlCanon;
/***** Typedef SET_OF_PemCrlCanon *****/
/** @ingroup header_pem
  */
typedef SET_OF(PemCrlCanon)       SET_OF_PemCrlCanon;
/***** Typedef SET_OF_PemRecCanon *****/
/** @ingroup header_pem
  */
typedef SET_OF(PemRecCanon)       SET_OF_PemRecCanon;
/***** Typedef SET_OF_PemMessageCanon *****/
/** @ingroup header_pem
  */
typedef SET_OF(PemMessageCanon)   SET_OF_PemMessageCanon;

typedef struct PemMessageLocal    PemMessageLocal;
typedef struct PemHeaderLocal     PemHeaderLocal;
typedef struct PemDekLocal        PemDekLocal;
typedef struct PemMicLocal        PemMicLocal;
typedef struct PemRecLocal        PemRecLocal;
/***** Typedef SET_OF_PemRecLocal *****/
/** @ingroup header_pem
  */
typedef SET_OF(PemRecLocal)       SET_OF_PemRecLocal;
/***** Typedef SET_OF_PemMessageLocal *****/
/** @ingroup header_pem
  */
typedef SET_OF(PemMessageLocal)   SET_OF_PemMessageLocal;

/***** Typedef ValidationResult *****/
/** @ingroup header_pem
  */
typedef struct ValidationResult   ValidationResult;


/***** Structure PemMessageCanon *****/
/** @ingroup header_pem
  */
struct PemMessageCanon {
/** The header field parameters of a PEM message or NULL. */
        PemHeaderCanon            *header;
/** The body of a PEM message. */
        DataStore                 *body;
};

/***** Structure PemHeaderCanon *****/
/** @ingroup header_pem
  */
struct PemHeaderCanon {
        char                      *rfc_version,
                                  *proctype,
                                  *content_domain,
                                  *content_domain_ext1,
                                  *content_domain_ext2,
                                  *content_domain_ext3;
        PemDekCanon               *dek_fields;
        PemOriginatorCanon        *orig_fields;
        SET_OF_Name               *issuer_fields;
        PemMicCanon               *mic_fields;
        SET_OF_PemCrlCanon        *crl_fields;
        SET_OF_Name               *crl_rr_fields;
        
};
/***** Structure PemDekCanon *****/
/** @ingroup header_pem
  */
struct PemDekCanon {
        char                      *dekinfo_enc_alg,
                                  *dekinfo_param,
                                  *keyinfo_enc_alg,
                                  *keyinfo_dek;
        SET_OF_PemRecCanon        *recipients;
        
};
/***** Structure PemRecCanon *****/
/** @ingroup header_pem
  */
struct PemRecCanon {
        char                      *enc_alg,
                                  *dek,
/** Issuer %DName part of Originator ID Asymmetric */
                                  *issuer,                /* Originator ID Asymmetric        */
/** %SerialNumber part of Originator ID Asymmetric */
                                  *serialnumber;          /* Originator ID Asymmetric        */
        
};

/***** Structure PemOriginatorCanon *****/
/** @ingroup header_pem
  */
struct PemOriginatorCanon {
        char                      *certificate,
/** Issuer %DName part of Originator ID Asymmetric */
                                  *issuer,                /* Originator ID Asymmetric        */
/** %SerialNumber part of Originator ID Asymmetric */
                                  *serialnumber;          /* Originator ID Asymmetric        */
        
};
/***** Structure PemMicCanon *****/
/** @ingroup header_pem
  */
struct PemMicCanon {
        char                      *mic_alg,
                                  *micenc_alg,
                                  *mic;
        
};
/***** Structure PemCrlCanon *****/
/** @ingroup header_pem
  */
struct PemCrlCanon {
        char                      *crl,
                                  *certificate;        
        SET_OF_Name               *issuer_certificate;
};




/***** Structure PemMessageLocal *****/
/** @ingroup header_pem
  */
struct PemMessageLocal {
/** The header field parameters of a PEM message or NULL. */
        PemHeaderLocal            *header;
/** The body of a PEM message or simple clear text. */
        DataStore                 *body;
/** The validation result of a call of #pem_validate. */
        VerificationResult        *validation_result;
/** Error recognized by #pem_validate. */
        char                      *error;
/** Comments generated by #pem_validate. */
        char                      *comment;
};
/***** Structure PemHeaderLocal *****/
/** @ingroup header_pem
  */
struct PemHeaderLocal {
/** The header field parameters of a PEM message or NULL. */
        int                        rfc_version;
        PEM_Proc_Types             proctype;
        PEM_Content_Domains        content_domain;
        char                       *content_domain_mtt0,
                                   *content_domain_mtt1,
                                   *content_domain_mtt2,
                                   *content_domain_mtt3;
        PemDekLocal                *dek_fields;
        Certificates               *certificates;
        Certificate                *root_certificate;
        PemMicLocal                *mic_fields;
        SET_OF_CRLWithCertificates *crl_fields;
        SET_OF_DName               *crl_rr_fields;
};

/***** Structure PemDekLocal *****/
/** @ingroup header_pem
  */
struct PemDekLocal {
        AlgId                      *dekinfo_enc_alg;
        AlgId                      *keyinfo_enc_alg;
        BitString                  *keyinfo_dek;
        SET_OF_PemRecLocal         *recipients;
        
};
/***** Structure PemRecLocal *****/
/** @ingroup header_pem
  */
struct PemRecLocal {
        AlgId                      *enc_alg;
        BitString                  *dek;
        Certificate                *certificate;
        
};
/***** Structure PemMicLocal *****/
/** @ingroup header_pem
  */
struct PemMicLocal {
        AlgId                      *signAI;
        BitString                  *mic;
        Boolean                    PEM_conformant;
        
};


/***** Structure ValidationResult *****/
/** PEM validation result structure. 
  * <B>Typedef:</B> <TT>typedef struct ValidationResult #ValidationResult;</TT> 
  * @ingroup header_pem
  */
struct ValidationResult {
        VerificationResult         *verification_result;
};


/***** Enumeration MISSING_RECIPIENT_KEY *****/
/** @ingroup header_pem
  */
typedef enum { MRK_IGNORE, MRK_ERROR } MISSING_RECIPIENT_KEY;

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#define SECUDE_PEM_INCLUDE 1
#include <secude/pem_p.h>
#undef SECUDE_PEM_INCLUDE

#endif /* _PEM_ */


