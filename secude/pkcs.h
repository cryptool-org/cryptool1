/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

/*-----------------------------------------------------------------------*/
/*  INCLUDE FILE  pkcs.h  (PKCS Standard)                                */
/*  Definition of structures and types for PKCS#1 - PKCS#10              */
/*-----------------------------------------------------------------------*/

#ifndef _PKCS_
#define _PKCS_

#include "af.h" 

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 *   pkcs.h defines:
 *
 *      ExtendedCertificateOrCertificate    (typedef struct ExtendedCertificateOrCertificate)
 *      ExtendedCertificatesAndCertificates (typedef struct ExtendedCertificatesAndCertificates)
 *      ExtendedCertificateInfo 	    (typedef struct ExtendedCertificateInfo)
 *      ExtendedCertificate 		    (typedef struct ExtendedCertificate)
 *      IssuerAndSerialNumber 		    (typedef struct IssuerAndSerialNumber)
 *      ContentInfo 			    (typedef struct ContentInfo)
 *      SignerInfo 			    (typedef struct SignerInfo)
 *      SignerInfos 			    (typedef SET_OF(SignerInfo))
 *      RecipientInfo 			    (typedef struct RecipientInfo)
 *      RecipientInfos 			    (typedef SET_OF(RecipientInfo))
 *      EncryptedContentInfo 		    (typedef struct EncryptedContentInfo)
 *      SignedData 			    (typedef struct SignedData)
 *      EnvelopedData 			    (typedef struct EnvelopedData)
 *      SignedAndEnvelopedData 		    (typedef struct SignedAndEnvelopedData)
 *      DigestedData 			    (typedef struct DigestedData)
 *      EncryptedData 			    (typedef struct EncryptedData)
 *      CertificationRequestInfo 	    (typedef struct CertificationRequestInfo)
 *      CertificationRequest 		    (typedef struct CertificationRequest)
 *
 *
 */



typedef struct ExtendedCertificateOrCertificate 	ExtendedCertificateOrCertificate;
typedef SET_OF(ExtendedCertificateOrCertificate)        ExtendedCertificatesAndCertificates;
typedef struct ExtendedCertificateInfo 			ExtendedCertificateInfo;
/*typedef struct ExtendedCertificate 			ExtendedCertificate;*/
typedef struct IssuerAndSerialNumber 			IssuerAndSerialNumber;
typedef struct ContentInfo 				ContentInfo;
typedef struct SignerInfo 				SignerInfo;
typedef SET_OF(SignerInfo)                          	SignerInfos;
typedef struct RecipientInfo 				RecipientInfo;
typedef SET_OF(RecipientInfo) 				RecipientInfos;
typedef struct EncryptedContentInfo 			EncryptedContentInfo;
typedef struct SignedData				SignedData;
typedef struct EnvelopedData				EnvelopedData;
typedef struct SignedAndEnvelopedData			SignedAndEnvelopedData;
typedef struct DigestedData				DigestedData;
typedef struct EncryptedData				EncryptedData;
typedef struct CertificationRequestInfo			CertificationRequestInfo;
/*typedef struct CertificationRequest			CertificationRequest;*/

typedef OctetString 		data_type;
typedef SignedData 		signedData_type;
typedef EnvelopedData 		envelopedData_type;
typedef SignedAndEnvelopedData  signedAndEnvelopedData_type;
typedef DigestedData 		digestedData_type;
typedef EncryptedData 		encryptedData_type;


/* TIME STAMP Stuff */
#ifdef X509v3


/* Structs */


/* Struct MessageImprint */

struct MessageImprint
{
  AlgId *hashAlgorithm;
  OctetString *hashedMessage;
};


typedef struct MessageImprint MessageImprint;

/* *********************************************************************** */
/* VERSION 1                                                               */
/* *********************************************************************** */


/* Struct TimeStampRequest */

struct TimeStampReq_1
{
  int version;
   
  int nonce;
  
  MessageImprint *messageImprint;
};

typedef struct TimeStampReq_1 TimeStampReq_1;


/* Struct TSTTime */

struct TSTTime 
{
  UTCTime *genTime;
  int milliseconds;
};

typedef struct TSTTime TSTTime;                        

struct PKIStatusInfo
{
  int PKIStatus;
  /*
  PKIStatus ::= INTEGER { 
      granted                (0), 
      -- you got exactly what you asked for 
      grantedWithMods        (1), 
      -- you got something like what you asked for; the 
      -- requester is responsible for ascertaining the differences 
      rejection              (2), 
      -- you don't get it, more information elsewhere in the message
      waiting                (3), 
      -- the request body part has not yet been processed, 
      -- expect to hear more later 
      revocationWarning      (4), 
      -- this message contains a warning that a revocation is 
      -- imminent 
      revocationNotification (5), 
      -- notification that a revocation has occurred 
      keyUpdateWarning       (6)
      -- update already done for the oldCertId specified in 
      -- CertReqMsg
  }
  */
};

typedef struct PKIStatusInfo PKIStatusInfo;


struct TSTInfo_1
{
  int version;
  /* PolicyInformation *policy; */
  PKIStatusInfo *status;
  GeneralName *tsa;
  TSTTime *tstTime;
  int nonce;
  MessageImprint *messageImprint;

};

typedef struct TSTInfo_1 TSTInfo_1;


/* *********************************************************************** */
/* VERSION 0                                                               */
/* *********************************************************************** */


struct TimeStampReq_0
{
  int version;
  int nonce;
  MessageImprint *messageImprint;
};

typedef struct TimeStampReq_0 TimeStampReq_0;

struct TSTInfo_0
{
  int version;
  PolicyInformation *policy;
  PKIStatusInfo *status;
  GeneralName *tsa;
  UTCTime *genTime;
  int nonce;
  MessageImprint *messageImprint;
};

typedef struct TSTInfo_0 TSTInfo_0;

struct TimeStampToken_0
{
  TSTInfo_0 *tstInfo;
};
  
typedef struct TimeStampToken_0 TimeStampToken_0;


struct TimeStampToken_1
{
  ContentInfo *tstInfo; /* bis pkcs7-Ergaenzung in SECUDE */
};

typedef struct TimeStampToken_1 TimeStampToken_1;

/* *********************************************************************** */
/* VERSION X                                                               */
/* *********************************************************************** */

/* Struct TimeStampRequest */

struct TimeStampReq
{
  GeneralName *requester;
  /* PolicyInformation *reqPolicy; */
 
  GeneralName *tsa;
  MessageImprint *messageImprint;
};

typedef struct TimeStampReq TimeStampReq;



struct TSTInfo 
{
  GeneralName* requester;
  GeneralName* tsa;
  AlgId* signatureAlgorithm;
  UTCTime *genTime;
  /* int CertId; */
  MessageImprint *messageImprint;
};

typedef struct TSTInfo TSTInfo;


/* Struct TimeStampToken */ 

struct TimeStampToken
{
  BitString *signature;
  TSTInfo *tstinfo;
};

typedef struct TimeStampToken TimeStampToken;

typedef TSTInfo_0 TSTInfo_0DataType;
typedef TSTInfo_1 TSTInfo_1DataType;

#endif






struct ExtendedCertificateInfo {
	int 		version;
	Certificate   * cert;
	SET_OF_Attr   * attributes;
};

/*
struct ExtendedCertificate {
        OctetString    		* tbs_DERcode;   Return-Parameter of e_ExtendedCertificateInfo 
        ExtendedCertificateInfo * extcertinfo;
        Signature      		* sig;
};
*/
typedef ASN1signed_TEMPLATE2(ExtendedCertificateInfo, extcertinfo) ExtendedCertificate;


struct ExtendedCertificateOrCertificate {
	int     choice;
        union {
                Certificate         * cert;
                ExtendedCertificate * extcert;
        } un;
};



struct IssuerAndSerialNumber {
  	DName       * issuer; 
	OctetString * serialnumber;
};


struct ContentInfo {
	ObjId * contentType;
	void  * content;
/*        union {
		OctetString            * data;
		SignedData             * signedData;
		EnvelopedData          * envelopedData;
		SignedAndEnvelopedData * signedAndEnvelopedData;
		DigestedData 	       * digestedData;
		EncryptedData 	       * encryptedData;
	    TSTInfo_0              * tstInfo0;
	    TSTInfo_1              * tstInfo1;
        } un;
        int     contentchoice;*/
};


struct SignerInfo {
  	int 			  version;  
	IssuerAndSerialNumber 	* issuerandserial;
	AlgId		      	* digestAI;
  	SET_OF_Attr	        * authAttributes;
	AlgId 			* digencAI;
	OctetString 		* encryptedDigest;
	SET_OF_Attr	        * unauthAttributes;
	SubjectKeyId        * keyid;
};


struct RecipientInfo {
  	int 			version;
	IssuerAndSerialNumber * issuerandserial;
	AlgId		      * keyencAI;
	OctetString 	      * encryptedKey;
};


struct EncryptedContentInfo {
	ObjId       * contentType;
	AlgId       * contentencAI;
	OctetString encryptedContent;
};


struct SignedData {
  	int 	       			      version;
	SET_OF_AlgId 			    * digestAlgorithms;
	ContentInfo  			    * contentInfo;
	ExtendedCertificatesAndCertificates * certificates;
	SET_OF_CRL 			    * crls;
	SignerInfos 			    * signerInfos;
};


struct EnvelopedData {
  	int 		       version;
	RecipientInfos       * recipientInfos;
	EncryptedContentInfo * encryptedContInfo;
};


struct SignedAndEnvelopedData {
  	int				      version;
	RecipientInfos 			    * recipientInfos;
	SET_OF_AlgId 			    * digestAIs;
	EncryptedContentInfo 		    * encryptedContInfo;
	ExtendedCertificatesAndCertificates * certificates;
	SET_OF_CRL 			    * crls;
	SignerInfos 			    * signerInfos;
};


struct DigestedData {
  	int 		  version;
	AlgId 		* digestAI;
	ContentInfo 	* contentInfo;
	OctetString 	* digest;
};


struct EncryptedData {
  	int		       version; 
	EncryptedContentInfo * encryptedContInfo;
};


struct CertificationRequestInfo {
  	int	  	   version;
	DName   	 * subject;
	KeyInfo 	 * subjectPK;
	SET_OF_Attr      * attributes;
};

/*
struct CertificationRequest {
        OctetString    		 * tbs_DERcode;   Return-Parameter of e_CertificationRequestInfo 
	CertificationRequestInfo * certreqinfo;
        Signature      		 * sig;           issuer's signature 
};
*/
typedef ASN1signed_TEMPLATE2(CertificationRequestInfo, certreqinfo) CertificationRequest;



/***********************************************************
 *
 * PKCS#7
 *
 **********************************************************/

#define PKCS_VERSION			1

typedef struct ContentTypeList		ContentTypeList;
typedef struct AttributeTypeTable	AttributeTypeTable;

typedef ExtendedCertificatesAndCertificates	ExtCertsAndCerts;
typedef ExtendedCertificateOrCertificate	ExtCertOrCert;


#ifdef OS2
#ifdef DATA_TYPE
#undef DATA_TYPE
#endif
#ifdef SIGNED_DATA_TYPE
#undef SIGNED_DATA_TYPE
#endif
#ifdef ENVELOPED_DATA_TYPE
#undef ENVELOPED_DATA_TYPE
#endif
#ifdef SIGNED_ENVELOPED_DATA_TYPE
#undef SIGNED_ENVELOPED_DATA_TYPE
#endif
#endif

enum ContentTypeId {
/*#ifdef PKCS_FOR_AUTHENTICODE*/
	AUTHENTICODE_DATA_TYPE = 311,
/*#endif*/
	DATA_TYPE = 1 ,
	SIGNED_DATA_TYPE,
	ENVELOPED_DATA_TYPE,
	SIGNED_ENVELOPED_DATA_TYPE,
	DIGESTED_DATA_TYPE,
	ENCRYPTED_DATA_TYPE,
    TSTInfo_0_DATA_TYPE,
    TSTInfo_1_DATA_TYPE,
	UNKNOWN_TYPE = -1
};

enum CertificateSelector {
	Certificate_SELECTOR = 1,
	ExtendedCertificate_SELECTOR
};

enum ASN1EncodingRule {
	DL_BER_ENCODING,
	DER_ENCODING
};

typedef enum   ContentTypeId		ContentTypeId;
typedef enum   CertificateSelector	CertificateSelector;
typedef enum   ASN1EncodingRule		ASN1EncodingRule;


struct ContentTypeList {
        char		*ct_name;
        ObjId		*ct_oid;
        ContentTypeId	 ct_nid;
};

struct AttributeTypeTable {
        char	*at_name;
        ObjId	*at_oid;
        e_function * av_enc;
        d_function * av_dec;
	void	(*av_free)();
	char*	(*av_sprint)();
	char	at_prt_flag;
};

#define	END_NEWLINE	0x01	




/* controls aux_fprint_ContentInfo() */

#define PTYPE		1	
#define PCONTENT	2	
#define PDATA		4
#define PENCCONTENT	8
#define PENCDIGEST	16		
#define PENCKEY		32



/*
 * This definition should be moved to ./src/include/filename.h
 */
/* #define EXT_CONTENTINFO ".cif"*/

/* SEC-1 (for use in PKCS#8) */
/* from "Standards for Efficient Cryptography" (Certicom) */
typedef struct ECPrivateKey {
    int version; /* ecPrivkeyVer1(1) */
    OctetString privateKey;
    ECKeyParameter *parameters; /* OPTIONAL: NULL */
    BitString *publicKey; /* OPTIONAL: NULL */
} ECPrivateKey;

/* PKCS#8 */
typedef struct PrivateKeyInfo {
    int version;
    AlgId *privateKeyAlgorithm;
    OctetString *privateKey; /* contains BER of struct defined by algid */
    SET_OF_Attr *attributes; /* OPTIONAL: NULL */
} PrivateKeyInfo;

typedef struct EncryptedPrivateKeyInfo {
    AlgId *encryptionAlgorithm; /* e.g. PKCS#5's pbeWithMD5AnddesCBC */
    OctetString *encryptedData; /* encrypted BER-encoding */
} EncryptedPrivateKeyInfo;

/* PKCS#12 */
typedef struct MacData {
    DigestInfo *mac;
    OctetString *macSalt;
    int macIterationCount; /* DEFAULT 1 */
} MacData;

typedef struct CCSBag { /* same struct for: CertBag / CRLBag / SecretBag */
    ObjId *ccsType;
    OctetString *ccs; /* contains DER code of ANY DEFINED BY ccsType */
} CCSBag;

typedef struct PFX {
    int version; /* this structures correspond to version == 3 
		    as current at end of february 98 */
    ContentInfo *authSafes;
    MacData *macData; /* OPTIONAL */
} PFX;

typedef SEQUENCE_OF(ContentInfo) AuthenticatedSafes;

typedef struct SafeBag {
    ObjId *bagType;
    void *bagContent;
    /* union {
	PrivateKeyInfo *keyBag;
	EncryptedPrivateKeyInfo *pkcs8ShroudedKeyBag;
	CCSBag *certBag;
	CCSBag *crlBag;
	CCSBag *secretBag;
	SafeContents *safeContents;
    } bagContent; */
    SET_OF_Attr *bagAttributes; /* OPTIONAL */
} SafeBag;

typedef SEQUENCE_OF(SafeBag) SafeContents;

/* global lists */
typedef enum PKCS12_BagType {
    PKCS12_bt_unknown = -1,
    PKCS12_bt_KeyBag,
    PKCS12_bt_PKCS8ShroudedKeyBag,
    PKCS12_bt_CertBag,
    PKCS12_bt_CRLBag,
    PKCS12_bt_SecretBag,
    PKCS12_bt_SafeContentsBag
} PKCS12_BagType;

typedef struct PKCS12_BagTypeList {
    char		*bt_name;
    ObjId		*bt_oid;
    PKCS12_BagType	 bt_nid;
} PKCS12_BagTypeList;

typedef enum PKCS12_CCSType {
    PKCS12_ccs_unknown = -1,
    PKCS12_ccs_X509Cert,
    PKCS12_ccs_SDSICert,
    PKCS12_ccs_X509Crl
} PKCS12_CCSType;

typedef struct PKCS12_CCSTypeList {
    char		*ccs_name;
    ObjId		*ccs_oid;
    PKCS12_CCSType	 ccs_nid;
    PKCS12_BagType	 bt_nid;
} PKCS12_CCSTypeList;

/* P12 high level structs */
/* (formerly: internal helper structs for PKCS#12 import/export) */
typedef enum P12_BagContent {
    P12_bc_already_processed = -2,
    P12_bc_unknown = -1,
    P12_bc_key,
    P12_bc_cert,
    P12_bc_secret
} P12_BagContent;

typedef struct P12_Bag {
    P12_BagContent	 type;
    union {
        PrivateKeyInfo *key;
        Certificate *cert; /* assumes X.509 */
        CCSBag *secret;
        /* ??? CRL *crl; ???
           !!! SafeContents not supported right now... */
    } content;
    Boolean int_encryption; /* for keys: internal vs. external encryption 
                               for data: encrypted vs. plain */
    BMPString *friendlyName; /* OPTIONAL / Unicode! */
    OctetString *localKeyID; /* only for Key/Cert pairs */
    SET_OF_Attr *additionalAttr; /* should be NULL in most cases */

    /* internal linking structure... */
    struct P12_Bag *next;
} P12_Bag;

typedef struct P12_Safe {
    int version; /* should be 3 */
    P12_Bag *bags;
    struct {
        /* these assume password mode for integrity and encryption */
        ObjId *mac;	/* for MAC */
        ObjId *enc;	/* for internal encryption */
        ObjId *espvk;   /* for external shrouded pvt key */
    } alg_oid;
    int iterationCount; /* when decoding: lowest of mac/enc counts */
} P12_Safe;


/* this should be the last statement in this file */
#include "pkcs_p.h"

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _PKCS_ */

