/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

/*-----------------------------------------------------------------------*/
/*  INCLUDE FILE  af.h  (Authentication Framework Interface)             */
/*  Definition of structures and types for Authentication Framework      */
/*-----------------------------------------------------------------------*/

#ifndef _AF_
#define _AF_



#include "secure.h"
/*
 *   secure.h defines:
 *
 *          AlgId               (typedef struct AlgId)
 *          ObjId               (typedef struct ObjId)
 *          OctetString         (typedef struct OctetString)
 *          BitString           (typedef struct BitString)
 *          ENCRYPTED           (typedef struct BitString)
 *          UTCTime             (typedef char)
 *          KeyInfo             (typedef struct KeyInfo) 
 *          Signature           (typedef struct Signature)
 */



    /*#define NULLVP ((char **) 0)*/
#define NOTOK           (-1)
    /*#define NULLIP          ((IP) 0)*/

typedef ObjId                       SEC_AttributeType;
typedef OctetString                 SEC_AttributeValue;
typedef struct Attr                 Attr;
typedef SEC_AttributeType    	    AttrType;
typedef struct AttrValues           AttrValues;
typedef struct AttrValueAssertion   AttrValueAssertion;
typedef struct DName                DName;
typedef struct RDName               RDName;

typedef SET_OF(AttrType)                	       SET_OF_AttrType;
typedef SET_OF(Attr)                	               SET_OF_Attr;

typedef enum SEC_attr_encoding { /* used value of ASN.1 tag... */
    attr_t61_latin1 = -20,
    attr_unknown = -1,
    attr_detect = 0,
    attr_utf8 = 12,
    attr_printable = 19,
    attr_t61 = 20,
    attr_ia5 = 22,
    attr_unicode = 30
} SEC_attr_encoding;


struct AttrValueAssertion {
    SEC_AttributeType   * element_IF_0;
    SEC_AttributeValue  * element_IF_1;
    SEC_attr_encoding	  attr_encoding;
};

struct DName {
    RDName   * element_IF_2;
    DName    * next;
};

struct RDName {
    AttrValueAssertion  * member_IF_0;
    RDName              * next;
};

struct AttrValues {
    SEC_AttributeValue     * member_IF_1;
    AttrValues         * next;
};

struct Attr {
    AttrType    * type;
    AttrValues  * values;
};


/*-----------------------------------------------------------------------*/
/*    T y p e d e f ' s   f o r   A F                                    */
/*-----------------------------------------------------------------------*/

typedef struct ToBeSigned                       ToBeSigned;
typedef struct ToBeSigned                       CertificateTBS;
typedef ASN1signed_TEMPLATE(ToBeSigned)         Certificate;
typedef struct Certificates                     Certificates;
typedef SET_OF(Certificate)                     SET_OF_Certificate;
typedef SET_OF(ToBeSigned)                      SET_OF_ToBeSigned;
typedef struct AFPSEObjects                     AFPSEObjects;
typedef enum { SIGNATURE, ENCRYPTION }          KeyType;
typedef SET_OF_Certificate                      CrossCertificates;
typedef struct Attribute                        Attribute;
typedef struct Serial                           Serial;
typedef struct CRLEntry                         CRLEntry;
typedef SEQUENCE_OF(CRLEntry)                   SEQUENCE_OF_CRLEntry;
typedef struct CertificatePair                  CertificatePair;
typedef SEQUENCE_OF(CertificatePair)            SEQUENCE_OF_CertificatePair;
typedef SET_OF(CertificatePair)                 SET_OF_CertificatePair;
typedef struct Crl                              Crl;
typedef SET_OF(Crl)                             SET_OF_Crl;
typedef enum { userCertificate, cACertificate } CertificateType;
typedef struct CertificationPath                CertificationPath;
typedef struct CertificatePairs                 CertificatePairs;
typedef struct VerificationResult               VerificationResult;
typedef struct VerificationStep                 VerificationStep;
typedef struct Validity                         Validity;

#define NULLCERTIFICATE                         ((Certificate *) 0)


typedef struct CRLTBS                           CRLTBS;
typedef ASN1signed_TEMPLATE(CRLTBS)             CRL;
typedef SET_OF(CRL)                             SET_OF_CRL;
typedef struct CRLWithCertificates              CRLWithCertificates;    
typedef SET_OF(CRLWithCertificates)             SET_OF_CRLWithCertificates;


/*    P S E - O b j e c t s      */

typedef struct FCPath            FCPath;
typedef struct PKRoot            PKRoot; 
typedef SET_OF_ToBeSigned        PKList;
typedef SET_OF_Crl               CrlSet;
typedef OctetString              SerialNumber;
typedef char 			*QuipuPWD;

#define NULLSERIALNUMBER                         ((SerialNumber *) 0)

/*    DistinguishedName - H a n d l i n g   */

typedef char                                       Name;
typedef struct Attrlist                            AttrList;
typedef SET_OF(DName)                              SET_OF_DName;

typedef struct NAME				   NAME;
typedef SET_OF(NAME)				   SET_OF_NAME;
struct NAME {
	Name  *alias;
        Name  *name;
        DName *dname;
};

#define NULLDNAME ((DName *) 0)
#define NULLRDNAME ((RDName *) 0)

#ifdef X509v3

#define NULLGENERALNAME ((GeneralName *) 0)

#include "x509v3.h"    /* extensions for x509v3-Certificates */

enum AddExt_BitValues { 
    /* common bit values for every field */
    addExt_Present = 1,
    addExt_Critical = 2
    /*...
    addExt_dontknow = 4,
    addExt_another = 8
    */
};
enum AddExt_FieldIndices {
    addExt_AuthorityKeyId = 0,
    addExt_BasicConstraints,
    addExt_CertificatePolicies,
    addExt_IssuerAltName,
    addExt_KeyUsage,
    addExt_SubjectKeyId,
    /* current "version" for AddExt_Feedback structure */
    addExt_CurrentVersion /* == 6 */
};
typedef struct AddExt_Feedback {
    int number_of_fields; /* [in]:  "version" of this struct, the app can handle
                             [out]: 0, if no feedback is returned */
    int field[addExt_CurrentVersion];
} AddExt_Feedback;

#else

#define NULLGENERALNAME NULL

#ifdef X509v3_ed_only
typedef OctetString CertExtensions;
typedef OctetString CRLExtensions;
typedef OctetString CRLEntryExtensions;
#else
typedef void CertExtensions;
typedef void CRLExtensions;
typedef void CRLEntryExtensions;
#endif

typedef void KeyUsage;
typedef void GeneralNames;
typedef void KeyIdentifier;
typedef void PolicyList;
typedef void GeneralSubtrees;
typedef int SkipCerts;
typedef void AddExt_Feedback;
#endif


#ifdef X500
#define DBA_AUTH_NONE 0
#define DBA_AUTH_SIMPLE 1
#define DBA_AUTH_STRONG 2
#endif

typedef SET_OF(char)    SET_OF_char;

/*-----------------------------------------------------------------------*/
/*     SET_OF, Attribute                                                 */
/*-----------------------------------------------------------------------


struct Attribute {
        ObjId           type;
        SET_OF_char    *value;
};

*/

/*-----------------------------------------------------------------------*/
/*     Certificate and Certificates                                      */
/*-----------------------------------------------------------------------*/


struct Validity {
        char *notbefore;
        char *notafter;
};
#ifdef SECUDE_DEBUG
/* for each DName element in an AF structure a printable string element
   representing this dname is added. This element is set by the ASN.1 decoding function. */ 
#define PRINTABLE_DNS(dname,name) 	{ char *printable = aux_DName2Name(dname);if(printable) { if(strlen(printable) > 511) printable[511] = 0;strcpy(name, printable);free(printable);}}
#endif

struct ToBeSigned {
		/* Certificate v1 fields */
        int             version;
        OctetString    *serialnumber;
        AlgId          *signatureAI;  /* algorithm of issuer's signature */
        DName          *issuer;
        Validity       *valid;
        DName          *subject;
        KeyInfo        *subjectPK;

/*************************************/
/* extensions for v2/v3 certificates */ 
/*************************************/

		/* Certificate v2 fields */
	BitString	*issuerUId;   /* OPTIONAL */
	BitString	*subjectUId;  /* OPTIONAL */

		/* Certificate v3 fields */
	CertExtensions	*extensions;  /* OPTIONAL */
#ifdef PRINTABLE_DNS
	char		 printable_subject[512];
	char		 printable_issuer[512];
#endif
};

/*************************************/
/*          end extensions           */  
/*************************************/
 
/*
 *** replaced by ASN1signed_TEMPLATE(ToBeSigned)
struct Certificate {
        OctetString    *tbs_DERcode; 
        ToBeSigned     *tbs;
        Signature      *sig;                       
};
*/

struct FCPath {
        SET_OF_Certificate *liste;
        FCPath         *next_forwardpath;
};

struct Certificates {
        Certificate    *usercertificate;
        FCPath         *forwardpath;
};

struct CertificationPath {
        OctetString        * userKeyId;
        Certificate        * userCertificate;
        OctetString        * verifKeyId;
        Certificate        * userVerifCertificate;
        CertificatePairs   * theCACertificates;
};

struct CertificatePairs {
        SEQUENCE_OF_CertificatePair * liste;
        CertificatePairs   * superior;
};

/*-----------------------------------------------------------------------*/
/*     Revoked Certificates, according to PEM                            */
/*-----------------------------------------------------------------------*/

struct CRLEntry {
        OctetString        *serialnumber;
        UTCTime            *revocationDate;
        CRLEntryExtensions *extensions; /* v3 extensions */
};

struct  CRLTBS {
        int                       version; /* only since v3 */
        AlgId                    *signatureAI;
        DName                    *issuer;
        SEQUENCE_OF_CRLEntry     *revokedCertificates;
        UTCTime                  *lastUpdate;
        UTCTime                  *nextUpdate;
        CRLExtensions            *extensions; /* v3 extensions */
#ifdef PRINTABLE_DNS
	char		 printable_issuer[512];
#endif
};

/*
 *** replaced by ASN1signed_TEMPLATE(CRLTBS)
struct  CRL {
        OctetString     *tbs_DERcode;  
        CRLTBS          *tbs;
        Signature       *sig;                  
};
*/

struct CRLWithCertificates {
        CRL             * crl;
        Certificates    * certificates;
};



/*-----------------------------------------------------------------------*/
/*     Structures used for Verification of Certification Paths           */
/*-----------------------------------------------------------------------*/


struct VerificationResult {
        VerificationStep     ** verifstep;
        int                     trustedKey;
        Boolean                 success;
        Boolean                 textverified;
        Name                  * top_name;
        Name                  * originator;
        Validity              * valid;
        OctetString           * top_serial;
        KeyInfo               * top_key;
};


struct VerificationStep {

        /*
         * version mechanism was introduces late...
         *
         * everything before the "version" field is "version 0" :-)
         */

        Certificate           * cert;
        CRL                   * crl;
        int                     crlcheck;
        UTCTime               * date;
        Validity              * valid;
        int                     supplied;
        Boolean                 policy_CA;
        Boolean                 dn_subordination_violation;

/**********************************/ 
/* extensions for v3 certificates */ 
/**********************************/ 
        int                     basic_constraints_violation;
        Boolean                 certificate_policy_violation;
        int                     critical_ext_violation;
        Boolean                 keyUsage_violation;
/**********************************/
/*         end extensions         */
/**********************************/

        /*
         * Gives the version of VerificationStep structure.
         * For any access to a member that follows the version field,
         * it is necessary to test if version has the right value!
         */
        int version;

        /* version == 1 */
        CRLEntryExtensions  * entryExtensions; /* is NULL if not present, else contains e.g. reasonCode */
};


/*
 * to be used for VerificationResult->trustedKey:
 * ----------------------------------------------
 *
 * Trusted Key flags for SUCCESSFUL verification
 */
#define TRUSTED_NEW_PKROOT		 0
#define TRUSTED_OLD_PKROOT		 1
#define TRUSTED_PROVIDED_PKROOT		 2
#define TRUSTED_PKLIST			 3
#define TRUSTED_FCPATH			 4
#define TRUSTED_SIGCERT			 5
#define TRUSTED_PCA			 6
/*
 * Trusted Key flags for FAILED verification
 */
#define FAILED_NEW_PKROOT		 0
#define FAILED_OLD_PKROOT		 1
#define FAILED_PROVIDED_PKROOT		 2
#define FAILED_PKLIST			 3
#define FAILED_FCPATH			 4
#define FAILED_NEXT_CERT		-1
#define FAILED_NEXT_EXPIRED		-2
#define FAILED_NEXT_MISSING		-3
#define FAILED_LAST_ROOT		-4


/*
      - pse_handle->verifresult->success = TRUE

	Verification of "Certificates" succeeded ...

		... with PKRoot(new) 
                    (pse_handle->verifresult->trustedKey = 0)

		... with PKRoot(old) 
                    (pse_handle->verifresult->trustedKey = 1)

		... with provided PKRoot
                    (pse_handle->verifresult->trustedKey = 2)

		... with PKList
                    (pse_handle->verifresult->trustedKey = 3)

		... with FCPath      
                    (pse_handle->verifresult->trustedKey = 4)

		... with own SIGNATURE certificate      
                    (pse_handle->verifresult->trustedKey = 5)

		... with PCAList
                    (pse_handle->verifresult->trustedKey = 6)

      - pse_handle->verifresult->success = FALSE

	Verification of "Certificates" failed ...

		... with PKRoot(new) 				
                    (pse_handle->verifresult->trustedKey = 0  ->  cryptographical verification failure)

		    (pse_handle->verifresult->trustedKey = 0 + pse_handle->verifresult->date is set  
					          -> Signature creation date does not lie 
						     within validity time frame of PKRoot(new) )

		... with PKRoot(old) 				
		    (pse_handle->verifresult->trustedKey = 1  ->  cryptographical verification failure)

		    (pse_handle->verifresult->trustedKey = 1 + pse_handle->verifresult->date is set  
					          -> Signature creation date does not lie 
						     within validity time frame of PKRoot(old) )

		... with provided PKRoot
                    (pse_handle->verifresult->trustedKey = 2)

		... with PKList      				
		    (pse_handle->verifresult->trustedKey = 3)

		... with FCPath      				
                    (pse_handle->verifresult->trustedKey = 4)

		... with certificate at next level above (verification failure)	
		    (pse_handle->verifresult->trustedKey = - 1, crlcheck = 0)

		... as certificate at next level above was revoked	
		    (pse_handle->verifresult->trustedKey = - 1, crlcheck = REVOKED)

		... as certificate provided at next level was expired
		    (pse_handle->verifresult->trustedKey = - 2)

		... as there was no certificate available at next level
		    (pse_handle->verifresult->trustedKey = - 3)	

		... certificate at last level is root certificate
		    (pse_handle->verifresult->trustedKey = - 4)	



		A certificate forming part of the VerificationResult structure may be 
		provided as follows: 

		supplied = 0 -> certificate provided within received certification path
		supplied = 1 -> certificate retrieved from Directory (.af-db or X.500)
		supplied = 2 -> certificate retrieved from PSE (PSE-object CrossCSet)

*/






/*
 * CRL handling
 */
#define REVOKED 1
#define NOT_REVOKED 2
#define CRL_NOT_AVAILABLE 3
#define CRL_OUT_OF_DATE 4
#define NOT_REQUESTED 5



/*--------------------------------------------------------------------------*/
/*       CertificatePair, according to X.509                                */
/*--------------------------------------------------------------------------*/

struct CertificatePair {
        Certificate     *forward;
        Certificate     *reverse;
};

/*-----------------------------------------------------------------------*/
/*     P S E  -  O b j e c t s                                           */
/*-----------------------------------------------------------------------*/


/*
 *      Names of PSE Objects (File-Names in the PSE)
 */


#define PSE_MAXOBJ      29           /* number of objects defined within af */


/*
 *     List of all PSE Objects
 */

struct AFPSEObjects {
            char *name;
            ObjId *oid;
};


/*
 *      Formats of other PSE Objects
 */

/*      PKRoot          */
/*      ======          */

struct PKRoot {
        DName              *ca;
        struct Serial      *newkey;
        struct Serial      *oldkey;
                /* Certificate v3 fields */
        CertExtensions  *extensions;  /* OPTIONAL */
#ifdef PRINTABLE_DNS
	char		 printable_ca[512];
#endif
};

struct Serial {           /* Public Key and serial number */
        OctetString   *serial;
        int            version;
        KeyInfo       *key;
        Validity      *valid;
        Signature     *sig;
};



/*      CrlSet          */
/*      ==========      */


struct Crl {
        int                      version; /* only since v3 */
        DName                   *issuer;
        UTCTime                 *nextUpdate;
        SEQUENCE_OF_CRLEntry    *revcerts;
        CRLExtensions           *extensions; /* v3 extensions */
#ifdef PRINTABLE_DNS
	char		 printable_issuer[512];
#endif
};


/*-----------------------------------------------------------------------*/
/*       DistinguishedName - Handling                                    */
/*-----------------------------------------------------------------------*/

struct Attrlist {
        char			*abbrev;
        char			*keyword;
        ObjId			*objid;
        ObjId			*syntax_oid;
	SEC_attr_encoding 	 preferred_encoding;
};



/*-----------------------------------------------------------------------*/
/*       CA Database - Handling  (cadb)                                  */
/*-----------------------------------------------------------------------*/

typedef struct IssuedCertificate        IssuedCertificate;
typedef SET_OF(IssuedCertificate)       SET_OF_IssuedCertificate;
typedef SET_OF(Name)                    SET_OF_Name;


struct IssuedCertificate {
        OctetString *serial;
        UTCTime     *date_of_issue;
};


/*-----------------------------------------------------------------------*/
/*    Aliases                                                            */
/*-----------------------------------------------------------------------*/

typedef enum { useralias, systemalias, notstored } AliasFile;

struct aliases {
        char          *aname; /* alias names */
        AliasFile  aliasfile; /* SYSTEM or USER Alias File */
        struct aliases *next;
};

struct aliaslist {
        struct aliases *a;
        Name    *dname;               /* distinguished name */
        struct aliaslist *next;
};
typedef struct aliaslist AliasList;
typedef struct aliases Aliases;

/* Aliastypes */

typedef enum { 
        ANYALIAS,
        RFCMAIL, 
        X400MAIL, 
        LOCALNAME
} AliasType;

#define GROUP_PREFIX "GROUP-ALIAS>"
#define GROUP_PREFIX_LENGTH 12

#if defined(X500) && (defined(ICR1) || defined(ICR2))

#define OK             0


typedef enum { DAP_BIND, DAP_UNBIND, DAP_ENTER, DAP_DELETE, DAP_RETRIEVE} DapOperation;
typedef enum { NOTYPE, USERCERTIFICATE, CACERTIFICATE, CERTIFICATEPAIR, REVLIST, AREVLIST} AttributeTYPE;

#ifdef ICR1

#ifdef bcopy
#undef bcopy
#endif
#ifdef bzero
#undef bzero
#endif
#ifdef bcmp
#undef bcmp
#endif

#include "quipu/config.h"
#include "ll/isoaddrs.h"
#include "ul/psap.h"
#include "asn1/UNIV-types.h"
#include "quipu/common.h"
#include "quipu/attr.h"
#include "quipu/sequence.h"
#include "quipu/dua.h"
#include "quipu/name.h"
#include "quipu/nrs_info.h"
#include "quipu/oid.h"
#include "quipu/AF-types.h"
#include "quipu/DAS-types.h"   /*for specifying the S T R O N G argument type*/
#include "quipu/af-cdefs.h"
#include "quipu/if-cdefs.h"
#include "quipu/nrs-cdefs.h"
#include "quipu/attrvalue.h"
#include "quipu/authen.h"

#ifndef ICR2
#include "quipu/qu-cdefs.h"
#endif /** ICR2 **/

#include "quipu/syntaxes.h"

#endif

#ifdef ICR2 /* ICR2 */

#include "config.h"
#include "isoaddrs.h"
#include "psap.h"
#include "UNIV-types.h"
#include "common.h"
#include "attr.h"
#include "sequence.h"
#include "dua.h"
#include "name.h"
#include "nrs_info.h"
#include "oid.h"
#include "AF-types.h"
#include "DAS-types.h"   /*for specifying the S T R O N G argument type*/
#include "af-cdefs.h"
#include "if-cdefs.h"
#include "nrs-cdefs.h"
#include "qu-cdefs.h"
#include "syntaxes.h"
#include "attrvalue.h"

#endif /* ICR2 */

#ifdef STRONG

#include "osisec-stub.h"
#include "secude-stub.h"
#include "cadb.h"   	/* definition of DEF_ISSUER_ALGID */

#endif /* STRONG */

#include "afquipui.h"

#ifdef index
#undef index
#endif
#endif /* X500 && (ICR1||ICR2), == ISODE */


#ifdef ASN1_NETSCAPE_STUFF

typedef struct PublicKeyAndChallenge {
    KeyInfo *spki;
    char *challenge;
} PublicKeyAndChallenge;

typedef ASN1signed_TEMPLATE(PublicKeyAndChallenge) SignedPublicKeyAndChallenge;

#endif /* ASN1_NETSCAPE_STUFF */

#define CERT_FINGERPRINT_ALG  md5	/* Netscape style Certificate Fingerprint */


/*-----------------------------------------------------------------------*/
/*    PIN Policy                                                         */
/*-----------------------------------------------------------------------*/

typedef struct PINPolicy {
  int islink;
  union {
    char *url;
    struct {
      int expiretime;
      int gracelogins;
      int oldpincomp;
      char *guisettings;
      char *rules;
    } p;
  } un;
} PINPolicy;

typedef struct PINState {
  time_t logintime;
  int gracelogins;
  int npin;
  OctetString **pin;
} PINState;

typedef struct PINContext {
  char *domain_name;
  char *first_name;
  char *group_name;
  char *host_name;
  char *middle_name;
  char *office;
  char *last_name;
  char *extension;
  char *user_name;
  char *home_phone;
} PINContext;




/*********************************************** 
 * Here comes the new reentrant stuff 
 ***********************************************/


#ifdef X509v3
#define UNBOUNDED	(GeneralSubtrees*)NULL
#define EMPTY		(GeneralSubtrees*)NULL
#else
#define UNBOUNDED	NULL
#define EMPTY		NULL
#endif
	
typedef struct AF_options AF_options;
struct AF_options {
	Boolean accept_alias_without_verification;
	Boolean af_FCPath_is_trusted;
	Boolean af_access_directory;
	Boolean af_check_Validity;
	Boolean af_chk_crl;
	Boolean af_sign_check_Validity;
	Boolean af_use_alias;
	Boolean af_verbose;
	Boolean chk_PEM_subordination;
	char    af_dir_dsaname[512];
	char    af_dir_tailor[512];
	int     af_dir_authlevel;
	Boolean af_dir_dsabound;
	DName  *directory_user_dname;

/* for v3 certificates: */

        /* A set of subtree specifications within which ALL subject names must fall */
        GeneralSubtrees *permittedSubtrees;
 
        /* A set of subtree specifications within which NO subject name may fall */
        GeneralSubtrees	 *excludedSubtrees;
 
        /* if an acceptable policy needs to explicitly appear in the
           certificate policies extension field of all certificates in the path */
        Boolean           explicitPolicy;
 
        /* if policy mapping is inhibited in the certification path */
        Boolean           inhibitPolicyMapping;
 
        /* Details of explicitPolicy and/or inhibitPolicyMapping constraints which
           have been stipulated but are yet to take effect. SkipCert gives the number
           of certificates yet to skip before the constraint takes effect */
        /* If -1 they are unset */
        SkipCerts         explicitPolicyPending;
        SkipCerts         PolicyMappingInhibitPending;

};

#define AF_DEF_OPTIONS {FALSE,FALSE,FALSE,TRUE,FALSE,TRUE,TRUE,FALSE,FALSE,{ '\0' },{ '\0' },0,FALSE,(DName *)0,UNBOUNDED,EMPTY,TRUE,TRUE,-1,-1}


typedef struct AF_ctx AF_ctx;
struct AF_ctx {
	AF_options		 options;
	
	PSESel			*psesel;

	Boolean 		 onekeypaironly;		 
	char 			*pse_name;
	char 			*ca_dir;
	char 			*cert_db;
	char 			*user_db;
	char 			*crl_db;
	char 			*ca_log_file_name;
	FILE 			*ca_log_file;
	VerificationResult 	*verifresult;
	Boolean			 call_af_verify;
	
	Certificate 		*SignCert_cache;
	Certificate 		*EncCert_cache;
	Certificate 		*Cert_cache;
	SET_OF_Certificate 	*SignCSet_cache;
	SET_OF_Certificate 	*EncCSet_cache;
	SET_OF_Certificate 	*CSet_cache;
	KeyInfo 		*SignSK_cache;
	KeyInfo 		*DecSKnew_cache;
	KeyInfo 		*DecSKold_cache;
	KeyInfo 		*SKnew_cache;
	KeyInfo 		*SKold_cache;
	FCPath 			*FCPath_cache;
	PKRoot 			*PKRoot_cache;
	PKList 			*PKList_cache;
	PKList 			*EKList_cache;
	PKList 			*PCAList_cache;
	SET_OF_CertificatePair 	*CrossCSet_cache;
	CrlSet 			*CrlSet_cache;
	SerialNumber 		*SerialNumber_cache;
	AliasList 		*AliasList_cache;
	QuipuPWD		 QuipuPWD_cache;
	AlgId 			*DHparam_cache;
/* for v3 certificates: */
	PolicyList 		*policies_cache;
	
	Boolean			 SignCert_read;
	Boolean			 EncCert_read;
	Boolean			 Cert_read;
	Boolean			 SignCSet_read;
	Boolean			 EncCSet_read;
	Boolean			 CSet_read;
	Boolean			 SignSK_read;
	Boolean			 DecSKnew_read;
	Boolean			 DecSKold_read;
	Boolean			 SKnew_read;
	Boolean			 SKold_read;
	Boolean			 FCPath_read;
	Boolean			 PKRoot_read;
	Boolean			 PKList_read;
	Boolean			 EKList_read;
	Boolean			 PCAList_read;
	Boolean			 CrossCSet_read;
	Boolean			 CrlSet_read;
	Boolean			 SerialNumber_read;
	Boolean			 AliasList_read;
	Boolean			 QuipuPWD_read;
	Boolean			 DHparam_read;

/* for v3 certificates: */
	Boolean 		 policies_read;
	
	Boolean			 got_system_aliases_once;
	Boolean			 got_user_aliases_once;
	Boolean			 kill_aliases_without_reading;
	
	AliasList 		*aliaslist;
	AliasList 		*last_aliaslist;
	Boolean     		 systemfile_write_protection;
	AliasFile		 filter_aliases;
	Boolean     		 filter_user_aliases;
	Boolean     		 filter_system_aliases;
	AliasList		*la;

	Boolean     		 is_sc;

#ifdef LDAP_WITH_DL_OPEN
/*********************************************** 
 * Here we have LDAP stuff for loading the ldap shared lib
 ***********************************************/
	void			*ldap_library;
#endif
    /* to work with a 3rd Key Pair for authentication */
    Boolean          use_authentication_cert;
	Certificate 	*AuthCert_cache;
	Boolean			 AuthCert_read;
	KeyInfo 		*AuthSK_cache;
	Boolean			 AuthSK_read;

    /* to be able to sign with 'Encryption' Cert */
    Boolean          use_enc_cert_for_signature;


};


typedef AF_ctx *PSE;

typedef void *AF_HANDLE;


#define CRED_GSS "GSS"
#define CRED_OPTIONS_LIFETIME "LIFETIME="
#define CRED_OPTIONS_DIRACCESS "DIRACCESS="
#define CRED_OPTIONS_CRLCHECK "CRLCHECK="

typedef struct  {
	char		*name   ;
	char		*cadir  ;
	char		*psename;
	char		*app    ;
	char		*pin    ;
	SET_OF_Name	*options;
} Cred;

typedef struct  {
	char		*name   ;
	char		*cadir  ;
	char		*psename;
	char		*app    ;
	BitString   *encr   ;
} EncrCred;

typedef SEQUENCE_OF(EncrCred)            Creds;

typedef struct  {
	ObjId		*type   ;
	char		*value  ;
	char		*replacement  ;
} RDNalias;
typedef SET_OF(RDNalias) SET_OF_RDNalias;



#include "af_p.h" 
#include "isode_p.h"



#endif /* _AF_*/



