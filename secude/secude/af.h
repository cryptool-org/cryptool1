/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/af.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*-----------------------------------------------------------------------*/
/*  INCLUDE FILE  af.h  (Authentication Framework Interface)             */
/*  Definition of structures and types for Authentication Framework      */
/*-----------------------------------------------------------------------*/

#ifndef _AF_
#define _AF_



#include <secude/secure.h>

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

/***** Typedef SEC_AttributeType *****/
/** Attribute type
  * @ingroup header_af
  */
typedef ObjId                       SEC_AttributeType;
/***** Typedef SEC_AttributeValue *****/
/** Attribute value
  * @ingroup header_af
  */
typedef OctetString                 SEC_AttributeValue;
typedef struct Attr                 Attr;
/***** Typedef AttrType *****/
/** Attribute type
  * @ingroup header_af
  */
typedef SEC_AttributeType    	    AttrType;
typedef struct AttrValues           AttrValues;
typedef struct AttrValueAssertion   AttrValueAssertion;
typedef struct DName                DName;
typedef struct RDName               RDName;

/***** Typedef SET_OF_AttrType *****/
/** a set of attribute type
  * identifiers
  * @ingroup header_af
  */
typedef SET_OF(AttrType)                	       SET_OF_AttrType;
/***** Typedef SET_OF_Attr *****/
/** a set of attributes
  * @ingroup header_af
  */
typedef SET_OF(Attr)                	               SET_OF_Attr;

/***** Enumeration SEC_attr_encoding *****/
/** Used value of ASN.1 tag
  * @ingroup header_af
  */
enum SEC_attr_encoding { /* used value of ASN.1 tag... */
    attr_t61_latin1 = -20,  /**< <tt>=-20</tt> */
    attr_unknown = -1,      /**< <tt>=-1</tt> */
    attr_detect = 0,        /**< <tt>=0</tt> */
    attr_utf8 = 12,         /**< <tt>=12</tt> */
    attr_printable = 19,    /**< <tt>=19</tt> */
    attr_t61 = 20,          /**< <tt>=20</tt> */
    attr_ia5 = 22,          /**< <tt>=22</tt> */
    attr_unicode = 30       /**< <tt>=30</tt> */
};
#ifndef DOXYGEN_EXCLUDE
typedef enum SEC_attr_encoding SEC_attr_encoding;
#endif


/***** Structure AttrValueAssertion *****/
/** @ingroup header_af
  */
struct AttrValueAssertion {
/** type of attribute */
    SEC_AttributeType   * element_IF_0;
/** value of attribute */
    SEC_AttributeValue  * element_IF_1;
    SEC_attr_encoding	  attr_encoding;
};

/***** Structure DName *****/
/** Distinguished Names (DName) are used
  * in SECUDE in order to uniquely
  * identify users or CAs. A Distinguished
  * Name is defined as a sequence of
  * relative Distinguished Names.
  * 
  * @ingroup header_af
  */
struct DName {
/** Relative Distinguished %Name */
    RDName   * element_IF_2;
/** linkage */
    DName    * next;
};

/***** Structure RDName *****/
/** Relative Distinguished Names (RDName)
  * are sets of {attribute
  * type / attribute value} pairs.
  * 
  * @ingroup header_af
  */
struct RDName {
/** attribute type/value pair */
    AttrValueAssertion  * member_IF_0;
/** linkage */
    RDName              * next;
};

/***** Structure AttrValues *****/
/** @ingroup header_af
  */
struct AttrValues {
/** single attribute value */
    SEC_AttributeValue     * member_IF_1;
/** linkage */
    AttrValues         * next;
};

/***** Structure Attr *****/
/** @ingroup header_af
  */
struct Attr {
/** type of attribute */
    AttrType    * type;
/** all the values of the attribute */
    AttrValues  * values;
};


/*-----------------------------------------------------------------------*/
/*    T y p e d e f ' s   f o r   A F                                    */
/*-----------------------------------------------------------------------*/

typedef struct ToBeSigned                       ToBeSigned;
/***** Typedef CertificateTBS *****/
/** to be signed part of a certificate
  * @ingroup header_af
  */
typedef struct ToBeSigned                       CertificateTBS;
/***** Structure Certificate *****/
/** Represents a Certificate.
  *
  * Parameters:<BR>
  * @em tbs_DERcode: the return parameter of #e_ToBeSigned.<BR>
  * @em tbs: to be signed part of the certificate<BR>
  * @em sig: issuer's signature
  *
  * @ingroup header_af
  */                      
typedef ASN1signed_TEMPLATE(ToBeSigned)         Certificate;
typedef struct Certificates                     Certificates;
/***** Typedef SET_OF_Certificate *****/
/** set of certificates
  * @ingroup header_af
  */
typedef SET_OF(Certificate)                     SET_OF_Certificate;
/***** Typedef SET_OF_ToBeSigned *****/
/** set of ToBeSigned structures
  * @ingroup header_af
  */
typedef SET_OF(ToBeSigned)                      SET_OF_ToBeSigned;
typedef struct AFPSEObjects                     AFPSEObjects;
/***** Typedef KeyType *****/
/** Key type
  * @ingroup header_af
  */
typedef enum { SIGNATURE, ENCRYPTION }          KeyType;
/***** Typedef CrossCertificates *****/
/** cross certificates
  * @ingroup header_af
  */
typedef SET_OF_Certificate                      CrossCertificates;
typedef struct Attribute                        Attribute;
typedef struct Serial                           Serial;
typedef struct CRLEntry                         CRLEntry;
/***** Typedef SEQUENCE_OF_CRLEntry *****/
/** sequence of %CRL entries
  * @ingroup header_af
  */
typedef SEQUENCE_OF(CRLEntry)                   SEQUENCE_OF_CRLEntry;
typedef struct CertificatePair                  CertificatePair;
/***** Typedef SEQUENCE_OF_CertificatePair *****/
/** sequence of certificate pairs
  * @ingroup header_af
  */
typedef SEQUENCE_OF(CertificatePair)            SEQUENCE_OF_CertificatePair;
/***** Typedef SET_OF_CertificatePair *****/
/** set of certificate pairs
  * @ingroup header_af
  */
typedef SET_OF(CertificatePair)                 SET_OF_CertificatePair;
typedef struct Crl                              Crl;
/***** Typedef SET_OF_Crl *****/
/** set of simplified revocation
  * lists
  * @ingroup header_af
  */
typedef SET_OF(Crl)                             SET_OF_Crl;
/***** Typedef CertificateType *****/
/** certificate type
  * @ingroup header_af
  */
typedef enum { userCertificate, cACertificate } CertificateType;
typedef struct CertificationPath                CertificationPath;
typedef struct CertificatePairs                 CertificatePairs;
typedef struct VerificationResult               VerificationResult;
typedef struct VerificationStep                 VerificationStep;
typedef struct Validity                         Validity;

#define NULLCERTIFICATE                         ((Certificate *) 0)


typedef struct CRLTBS                           CRLTBS;
/***** Structure CRL *****/
/** Represents a %Certificate Revocation List (CRL).
  *
  * Parameters:<BR>
  * @em tbs_DERcode: the return parameter of #e_CRLTBS.<BR>
  * @em tbs: to be signed part of the CRL<BR>
  * @em sig: issuing CA's signature
  *
  * @ingroup header_af
  */              
typedef ASN1signed_TEMPLATE(CRLTBS)             CRL;
/***** Typedef SET_OF_CRL *****/
/** set of %CRLs
  * @ingroup header_af
  */
typedef SET_OF(CRL)                             SET_OF_CRL;
typedef struct CRLWithCertificates              CRLWithCertificates;    
/***** Typedef SET_OF_CRLWithCertificates *****/
/** set of %CRLs with certificates
  * @ingroup header_af
  */
typedef SET_OF(CRLWithCertificates)             SET_OF_CRLWithCertificates;


/*    P S E - O b j e c t s      */

typedef struct FCPath            FCPath;
typedef struct PKRoot            PKRoot; 
/***** Typedef PKList *****/
/** AF PSE object PKList
  * @ingroup header_af
  */
typedef SET_OF_ToBeSigned        PKList;
/***** Typedef CrlSet *****/
/** AF PSE object CrlSet
  * @ingroup header_af
  */
typedef SET_OF_Crl               CrlSet;
/***** Typedef SerialNumber *****/
/** AF PSE object SerialNumber - for CA-PSEs only
  * @ingroup header_af
  */
typedef OctetString              SerialNumber;
/***** Typedef QuipuPWD *****/
/** AF PSE object QuipuPWD
  * @ingroup header_af
  */
typedef char 			*QuipuPWD;

#define NULLSERIALNUMBER                         ((SerialNumber *) 0)

/*    DistinguishedName - H a n d l i n g   */

/***** Typedef Name *****/
/** Name
  * @ingroup header_af
  */
typedef char                                       Name;
typedef struct Attrlist                            AttrList;
/***** Typedef SET_OF_DName *****/
/** set of DName
  * @ingroup header_af
  */
typedef SET_OF(DName)                              SET_OF_DName;

typedef struct NAME				   NAME;
/***** Typedef SET_OF_NAME *****/
/** set of struct %NAME
  * @ingroup header_af
  */
typedef SET_OF(NAME)				   SET_OF_NAME;
/***** Structure NAME *****/
/** @ingroup header_af
  */
struct NAME {
/** Alias */
	Name  *alias;
/** Name */
        Name  *name;
/** Distinguished  %Name */
        DName *dname;
};

#define NULLDNAME ((DName *) 0)
#define NULLRDNAME ((RDName *) 0)

#ifdef X509v3

#define NULLGENERALNAME ((GeneralName *) 0)

#include <secude/x509v3.h>    /* extensions for x509v3-Certificates */

enum AddExt_BitValues { 
    /* common bit values for every field */
    addExt_Present = 1,
    addExt_Critical = 2,
    addExt_Suppress = 4,
	addExt_NoFallback = 8
    /*...
    addExt_another = 16,
    addExt_dontknow = 32
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
typedef void CRLNumber;
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


/***** Structure Validity *****/
/** @ingroup header_af
  */
struct Validity {
/** date since certificate is valid; */
        char *notbefore;
/** date until certificate is valid; */
        char *notafter;
};
#ifdef SECUDE_DEBUG
/* for each DName element in an AF structure a printable string element
   representing this dname is added. This element is set by the ASN.1 decoding function. */ 
#define PRINTABLE_DNS(dname,name) 	{ char *printable = aux_DName2Name(dname);if(printable) { if(strlen(printable) > 511) printable[511] = 0;strcpy(name, printable);free(printable);}}
#endif

/***** Structure ToBeSigned *****/
/** @ingroup header_af
  */
struct ToBeSigned {
		/* Certificate v1 fields */
/** version of certificate */
        int             version;
/** %Serial number */
        OctetString    *serialnumber;
/** algorithm of issuer's signature */
        AlgId          *signatureAI;  /* algorithm of issuer's signature */
/** issuer's Distinguished %Name */
        DName          *issuer;
/** %Validity */
        Validity       *valid;
/** subject's Distinguished %Name */
        DName          *subject;
/** subject's public key */
        KeyInfo        *subjectPK;

/*************************************/
/* extensions for v2/v3 certificates */ 
/*************************************/

		/* Certificate v2 fields */
/** X509v2 - OPTIONAL */
	BitString	*issuerUId;   /* OPTIONAL */
/** X509v2 - OPTIONAL */
	BitString	*subjectUId;  /* OPTIONAL */

		/* Certificate v3 fields */
/** X509v3 extensions - OPTIONAL */
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

/***** Structure FCPath *****/
/** @ingroup header_af
  */
struct FCPath {
/** set of (cross-)certificates at one
  * level, has to contain at least one
  * certificate, the <I>hierarchy</I>
  * certificate
  */
        SET_OF_Certificate *liste;
/** (linkage information)
  * next (higher) level in the forward
  * certification path (see also
  * <A href="af_path.htm">FCPath</A>)
  */
        FCPath         *next_forwardpath;
};

/***** Structure Certificates *****/
/** @ingroup header_af
  */
struct Certificates {
/** certificate of the signer */
        Certificate    *usercertificate;
/** <A HREF="af_path.htm">Forward Certification Path</A> */
        FCPath         *forwardpath;
};

/***** Structure CertificationPath *****/
/** @ingroup header_af
  */
struct CertificationPath {
/** User's key */
        OctetString        * userKeyId;
/** User's certificate */
        Certificate        * userCertificate;
/** ??? */
        OctetString        * verifKeyId;
/** ??? */
        Certificate        * userVerifCertificate;
/** ??? */
        CertificatePairs   * theCACertificates;
};

/***** Structure CertificatePairs *****/
/** @ingroup header_af
  */
struct CertificatePairs {
/** ??? */
        SEQUENCE_OF_CertificatePair * liste;
/** ??? */
        CertificatePairs   * superior;
};

/*-----------------------------------------------------------------------*/
/*     Revoked Certificates, according to PEM                            */
/*-----------------------------------------------------------------------*/

/***** Structure CRLEntry *****/
/** @ingroup header_af
  */
struct CRLEntry {
/** %Serial number of revoked certificate */
        OctetString        *serialnumber;
/** date of revocation */
        UTCTime            *revocationDate;
/** X509v3 extensions */
        CRLEntryExtensions *extensions; /* v3 extensions */
};

/***** Structure CRLTBS *****/
/** @ingroup header_af
  */
struct  CRLTBS {
/** version of %CRL - not until X509v3 */
        int                       version; /* only since v3 */
/** Algorithm used for signing the %CRL */
        AlgId                    *signatureAI;
/** Distinguished %Name of the issuer */
        DName                    *issuer;
/** revoked certificates */
        SEQUENCE_OF_CRLEntry     *revokedCertificates;
/** last update of the %CRL */
        UTCTime                  *lastUpdate;
/** next update of the %CRL */
        UTCTime                  *nextUpdate;
/** X509v3 extensions */
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

/***** Structure CRLWithCertificates *****/
/** @ingroup header_af
  */
struct CRLWithCertificates {
/** CertificateRevocationList */
        CRL             * crl;
/** %Certificates. */
        Certificates    * certificates;
};



/*-----------------------------------------------------------------------*/
/*     Structures used for Verification of Certification Paths           */
/*-----------------------------------------------------------------------*/


/***** Structure VerificationResult *****/
/** Values of VerificationResult->trustedKey.
  * @anchor VerRes_TrustedKeys <CODE><PRE>
  * success == TRUE:
  * <B>TRUSTED_NEW_PKROOT</B>		Successful verification with %PKRoot
  * <B>TRUSTED_OLD_PKROOT</B>		Successful verification with old %PKRoot
  * <B>TRUSTED_PROVIDED_PKROOT</B>		Successful verification with a %PKRoot provided by the signer
  * instead of the own trusted %PKRoot - this verification result may 
  * only be trusted if this %PKRoot has been checked by other means !
  * <B>TRUSTED_PKList</B>			Successful verification with trusted key found in %PKList
  * <B>TRUSTED_FCPATH</B>			Successful verification with trusted key found in %FCPath
  * <B>TRUSTED_SIGCERT</B>			Successful verification with key of own signature certificate
  * <B>TRUSTED_PCA</B>			Successful verification with trusted key found in %PCAList
  * success == FALSE:
  * <B>FAILED_NEW_PKROOT</B>		Failed verification with %PKRoot
  * <B>FAILED_OLD_PKROOT</B>		Failed verification with old %PKRoot
  * <B>FAILED_PROVIDED_PKROOT</B>		Failed verification with %PKRoot provided by signer
  * <B>FAILED_PKList</B>			No trusted key found in %PKList
  * <B>FAILED_FCPATH</B>			No trusted key found in %FCPath
  * <B>FAILED_NEXT_CERT</B>			Unable to verify next certificate in path
  * <B>FAILED_NEXT_EXPIRED</B>		Next certificate in path is expired
  * <B>FAILED_NEXT_MISSING</B>		Unable to find next certificate in path
  * <B>FAILED_LAST_ROOT</B>			Verification with root certificate failed
  * </PRE></CODE>
  * 
  * @ingroup header_af
  */
struct VerificationResult {
/** NULL terminated array of verification steps */
        VerificationStep     ** verifstep;
/** verification finished with trusted key
  * found in %PKList, %FCPath, %PCAList, %PKRoot
  * or own SIGNATURE certificate 
  * (@ref VerRes_TrustedKeys "suitable defines").
  */
        int                     trustedKey;
/** verification successful or not in terms of cryptography and completeness.<BR>
  * <B><I>Important:</B> The validation in terms of evaluating the boundary conditions
  * that caused the success flag status has to be done by the application by checking
  * the values of <B>trustedKey</B> and optionally <B>verifstep</B></I>
  */
        Boolean                 success;
/** text verification has been done. (i.e. calling function is #af_verify)
  * or not (i.e. calling function is #af_verify_Certificates)<BR>
  * This flag is used by print routines and <B>must not be used for validation
  * result evaluation</B>.
  */
        Boolean                 textverified;
/** name of the last processed certificate
  * in the chain, where the verification
  * failed or succeeded
  */
        Name                  * top_name;
/** subject name of usercertificate or
  * - if not existent - name of %PKRoot
  */
        Name                  * originator;
/** validity of %PKRoot's certificate */
        Validity              * valid;
/** serial number of the last processed
  * certificate in the chain, where the
  * verification failed or succeeded
  */
        OctetString           * top_serial;
/** public key of the last processed
  * certificate in the chain, where the
  * verification failed or succeeded
  */
        KeyInfo               * top_key;
};


/***** Structure VerificationStep *****/
/** @ingroup header_af
  */
struct VerificationStep {

        /*
         * version mechanism was introduced late...
         *
         * everything before the "version" field is "version 0" :-)
         */

/** %Certificate, part of the originator's
  * certification path
  */
        Certificate           * cert;
/** cert checked against
  * revocation list <I>crl</I>
  */
        CRL                   * crl;
/** <I>cert</I> checked against its
  * issuer's revocation list
  */
        int                     crlcheck;
/** revocation date if <I>cert</I>
  * has been revoked or
  * next scheduled date of issue if
  * CRL is obsolete
  */
        UTCTime               * date;
/** validity time frame of <I>cert</I> */
        Validity              * valid;
/** <I>cert</I> supplied or retrieved
  * from a Directory.
  * <B>Possible values of <I>supplied</I>:<BR></B>
  * <B>0</B> = provided within received certification path
  * <BR>
  * <B>1</B> = retrieved from Directory (.af-db or LDAP / X.500)
  * <BR>
  * <B>2</B> = retrieved from PSE (PSE-object CrossCSet)
  * <BR>
  * <B>3</B> = retrieved via HTTP or FTP (according to URI in IssuerAltNames extension)
  */
        int                     supplied;
/** <I>cert</I> issued by a Policy CA */
        Boolean                 policy_CA;
/** name subordination rule violated */
        Boolean                 dn_subordination_violation;

/**********************************/ 
/* extensions for v3 certificates */ 
/**********************************/ 
/** basic constraints violated.
  * <B>1</B> = NOT ALLOWED TO ACT as a CA
  * <BR>
  * <B>2</B> = extension is NOT PRESENT <BR>
  */
        int                     basic_constraints_violation;
/** certificate policy not trusted */
        Boolean                 certificate_policy_violation;
/** critical extension encountered that can
  * not be evaluated.
  */
        int                     critical_ext_violation;
/** keyCertSign / cRLSign bit set in keyUsage not in line with type of certificate (USER / CA) */
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

/***** Structure CertificatePair *****/
/** @ingroup header_af
  */
struct CertificatePair {
/** ??? */
        Certificate     *forward;
/** ??? */
        Certificate     *reverse;
};

/*-----------------------------------------------------------------------*/
/*     P S E  -  O b j e c t s                                           */
/*-----------------------------------------------------------------------*/


/*
 *      Names of PSE Objects (File-Names in the PSE)
 */


#define PSE_MAXOBJ      30           /* number of objects defined within af */


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

/***** Structure PKRoot *****/
/** @ingroup header_af
  */
struct PKRoot {
/** Distinguished name of the CA */
        DName              *ca;
/** new / currently used public key */
        struct Serial      *newkey;
/** old public key in cases of key exchange */
        struct Serial      *oldkey;
                /* Certificate v3 fields */
/** X509v3 extensions - OPTIONAL */
        CertExtensions  *extensions;  /* OPTIONAL */
#ifdef PRINTABLE_DNS
	char		 printable_ca[512];
#endif
};

/***** Structure Serial *****/
/** @ingroup header_af
  */
struct Serial {           /* Public Key and serial number */
/** Serial number */
        OctetString   *serial;
/** version of the certificate */
        int            version;
/** Public %Key certified */
        KeyInfo       *key;
/** %Validity of the certificate */
        Validity      *valid;
/** %Signature */
        Signature     *sig;
};



/*      CrlSet          */
/*      ==========      */


/***** Structure Crl *****/
/** @ingroup header_af
  */
struct Crl {
/** version of Crl - not until X509v3 */
        int                      version; /* only since v3 */
/** issuer of the %CRL */
        DName                   *issuer;
/** expiring date of the %CRL */
        UTCTime                 *nextUpdate;
/** revoked certificates in this %CRL */
        SEQUENCE_OF_CRLEntry    *revcerts;
/** X509v3 extensions */
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
/***** Typedef SET_OF_IssuedCertificate *****/
/** set of IssuedCertificate (for
  * AF-DB use)
  * @ingroup header_af
  */
typedef SET_OF(IssuedCertificate)       SET_OF_IssuedCertificate;
/***** Typedef SET_OF_Name *****/
/** set of names
  * @ingroup header_af
  */
typedef SET_OF(Name)                    SET_OF_Name;


/***** Structure IssuedCertificate *****/
/** @ingroup header_af
  */
struct IssuedCertificate {
/** serial number (of issued %Certificate) */
        OctetString *serial;
/** date of issue (of issued %Certificate) */
        UTCTime     *date_of_issue;
};


/*-----------------------------------------------------------------------*/
/*    Aliases                                                            */
/*-----------------------------------------------------------------------*/

/***** Typedef AliasFile *****/
/** alias file
  * @ingroup header_af
  */
typedef enum { useralias, systemalias, notstored } AliasFile;

/***** Structure aliases *****/
/** @ingroup header_af
  */
struct aliases {
/** alias name */
        char          *aname; /* alias names */
/** SYSTEM or USER Alias File */
        AliasFile  aliasfile; /* SYSTEM or USER Alias File */
/** pointer to the next alias */
        struct aliases *next;
};

/***** Structure aliaslist *****/
/** @ingroup header_af
  */
struct aliaslist {
/** alias for <I>dname</I> */
        struct aliases *a;
/** Distinguished %Name */
        Name    *dname;               /* distinguished name */
/** pointer to the next alias in the list */
        struct aliaslist *next;
};
/***** Typedef AliasList *****/
/** AliasList
  * @ingroup header_af
  */
typedef struct aliaslist AliasList;
/***** Typedef Aliases *****/
/** aliases
  * @ingroup header_af
  */
typedef struct aliases Aliases;

/* Aliastypes */

/***** Typedef AliasType *****/
/** alias type
  * @ingroup header_af
  */
typedef enum { 
        ANYALIAS,
        RFCMAIL, 
        X400MAIL, 
        LOCALNAME
} AliasType;

#define GROUP_PREFIX "GROUP-ALIAS>"
#define GROUP_PREFIX_LENGTH 12


#ifdef ASN1_NETSCAPE_STUFF

/***** Structure PublicKeyAndChallenge *****/
/** @ingroup header_af
  */
struct PublicKeyAndChallenge {
    KeyInfo *spki;
    char *challenge;
};
/***** Typedef PublicKeyAndChallenge *****/
/** @ingroup header_af
  */
typedef struct PublicKeyAndChallenge PublicKeyAndChallenge;

/***** Typedef SignedPublicKeyAndChallenge *****/
/** @ingroup header_af
  */
typedef ASN1signed_TEMPLATE(PublicKeyAndChallenge) SignedPublicKeyAndChallenge;

#endif /* ASN1_NETSCAPE_STUFF */

#define CERT_FINGERPRINT_ALG  md5	/* Netscape style Certificate Fingerprint */


/*-----------------------------------------------------------------------*/
/*    PIN Policy                                                         */
/*-----------------------------------------------------------------------*/

/***** Structure PINPolicy *****/
/** main data structure with external and internal representation.
  *
  * The <B>PIN policy</B> is a data structure, that describes a
  * security policy for the PIN protection of the SECUDE <a
  * href=afpse.htm>PSE</a>. Applications based on SECUDE can
  * enforce the PIN policy by using <a href=afpin.htm>set of
  * functions</a> in the SECUDE API.
  * 
  * <p>PIN policy features (all optional):
  * <ul>
  * <li>defines an <b>expire time</b> for PINs to force
  *     periodical change
  * <li>permits a settable number of <b>grace logins</b> after
  *     the PIN has expired, before it really has to be changed.
  * <li>defines the number of old PINs for which MD5 hashes are
  *     stored to <b>prevent</b> users from <b>re-using previous
  * 		PINs</b>.
  * <li>defines a set of <b>PIN quality rules</b> to prevent
  *     users from choosing bad PINs. These quality rules
  *     feature:
  *     <ul>
  *     <li>a mini language with boolean expression, string and
  * 	integer comparison and calculations
  *     <li>provides a message for each rule that explains why
  * 	the the PIN was rejected
  *     <li>can check number off characters, (non-)alphabetic
  * 	character, capital character, digits and mixed case.
  *     <li>can compare proposed password with previous ones
  *     <li>can compare with environmental information like user
  * 	name, machine name, telephone number etc. (if provided
  * 	by the application)
  *     </ul>
  * <li>provides a hook for GUI applications, that want to hide
  *     the PIN rule language behind a simple user interface. The
  *     application can store custom settings in this hook.
  * </ul>
  * 
  * <h4>@anchor PINPolicy_external External representation</h4>
  * 
  * The external PIN policy representation consists of lines of
  * characters (ISO 8859-1). The lines are separated with NL, CR
  * or CRNL.
  * 
  * The representation consist of three parts:
  * <ol>
  *   <li>format identifier and version
  *   <li>settings (optional)
  *   <li>PIN rules (optional)
  * </ol>
  * 
  * The first part identifies the format and its version. It
  * consists of a single line. There are two types of PIN
  * policies: `normal policy' and `link to policy' which are
  * identified by the strings `<b>SecudePINPolicy:</b>' and
  * `<b>SecudePINPolicyLink:</b>'. The identifier is followed by
  * possible white space and a version number of the form
  * `<i>x.y</i>' (with <i>x</i> and <i>y</i> natural numbers).
  * 
  * <p>The second part consists of a number of lines of the form
  * `<b>keyword: value</b>'.
  * 
  * @anchor PINPolicy_rules The third part is separated from the
  * second by an empty line. Every line has the form
  * `<b>rule</b> <i>TAB</i> <b>message</b>', as detailed
  * @ref PINPolicy_rulesdetail "below".
  * 
  * <h5>Normal Policies</h5>
  * 
  * <ol>
  *   <li><b>SecudePINPolicy: 1.0</b>
  *   <li>any of the following lines in any order:
  *     <ul>
  * 		<li><b>ExpireTime:</b> <i>number of days or</i>
  * 	<b>never</b>
  * 		<li><b>GraceLogins:</b> <i>number of grace logins to
  * 	  grant</i>
  * 		<li><b>OldPINCompare:</b> <i>number of hashes of old
  * 	  PINs that should be stored</i>. This parameter
  * 	does <em>not</em> (despite the name) trigger that
  * 	new proposed PINs are compared with old ones. This
  * 	has to be done with a rule like `"%p" = old' (see
  * 	  @ref PINPolicy_rulesdetail "below"). 
  * 		<li><b>@anchor PINPolicy_guisettings GUISettings:</b>
  * 	<i>any string</i> This is for
  * 	applications, that generate PIN rules automatically
  * 	instead of letting the user provide them. It is
  * 	intended to store some information like the
  * 	following: `<b>SSSOn6.3 6,12,1,0</b>' (program and
  * 	version identifier followed by an encoding of
  * 	minimal, maximal length, mixed case resp. non
  * 	alphabetic characters required, e. g.). This should
  * 	solve the problem, that PIN rules can be easily
  * 	generated, but are much harder to analyze for
  * 	presentation in a user interface.
  *     </ul>
  *   <li>@anchor PINPolicy_rulesdetail the <a
  * 		href="afpin101.htm">format of the PIN rules</a> is derived
  *     from the Linux-PAM package (Pluggable Authentication
  *     Module, passwd+), which is derived from the passwd+
  *     package from Dartmouth University. In SECUDE regular
  *     expression matching and user variables have been
  *     disabled. The rule syntax has been extended in order to
  *     compare proposed pins with several older ones.
  * 
  *     Every rule line has the form
  * 		`<b>rule</b> <i>TAB</i> <b>message</b>', where
  * 		<i>message</i> should explain what is wrong with PINs
  * 		that are catched by this rule. Examples:
  * 
  * 		<table border=0>
  * 		<tr><td>"\%\#p" \< 6</td><td><i>TAB</i></td><td>
  * 	  PIN must be at least 6 characters long! 
  * 		<tr><td>"\%\#p" \> 16</td><td><i>TAB</i></td><td>
  * 	  PIN must not be longer than 16 characters!
  * 		<tr><td>"\%d" \< 2</td><td><i>TAB</i></td><td>
  * 	  PIN must contain at least 2 digits
  * 		<tr><td>\%v==0  \&\& \%-b==0</td><td><i>TAB</i></td><td>
  * 	  PIN must contain mixed case or non-alpha. chars!
  * 		<tr><td>"\%p" == old</td><td><i>TAB</i></td><td>
  * 	  PIN must be different from last n PINs!
  * 		<tr><td>"\%p" == \%u</td><td><i>TAB</i></td><td>
  * 	  PIN must be different from user name!
  *     </table>
  * </ol>
  * 
  * <h5>Link Policies</h5>
  * 
  * The second format of PIN policies serves as a link to the
  * real policy or a to another link. In this case the three
  * parts are:
  * <ol>
  *   <li><b>SecudePINPolicyLink: 1.0</b>
  *   <li><b>URL:</b> <i>some URL that is understood by the
  * 		application.</i>
  *   <li>the PIN rule part must be empty
  * </ol>
  *
  * <B>Synopsis:</B> <TT>\#include "%af.h"</TT>
  * 	  
  * @sa <a href="afpin101.htm">format of the PIN %rules</a><BR>PINState
  * @anchor PINPolicy_internal
  * @ingroup af_pin
  */
typedef struct PINPolicy {
  int islink;           /**< != 0 iff the first union variant is used */
  union {
    char *url;          /**< URL indicating where the policy can be found */
    struct {
      int expiretime;   /**< time in days after which a PIN is
                             regarded as expired and the user has
                             to be prompted for a new one. */
      int gracelogins;  /**< number of grace logins to be granted 
                             after a PIN has expired before a new 
                             one must be chosen. */
      int oldpincomp;   /**< number of hashes of old PINs that 
                             should be stored in the PINState. */
      char *guisettings;/**< a custom string chosen by the
                             application as described
                             @ref PINPolicy_guisettings "above" */
      char *rules;      /**< PIN quality rules as described
                             @ref PINPolicy_rules "above". */
    } p;
  } un;  /**< Union members documented @ref PINPolicy_internal "here". */
} PINPolicy;

/***** Structure PINState *****/
/** State information stored in the PSE.
  *
  * The <B>PIN state</B> is a data structure, that captures all
  * state information for one PIN that must be stored in order
  * to enforce a PIN policy:
  * <ul>
  *  <li>the date when the PIN expires and the user has to choose a new one
  *  <li>the number of grace logins left
  *  <li>some hashes of old PINs that can be used to prevent
  *      users from re-using PINs too often
  * </ul>
  * <I>It is not manipulated directly by applications normally.</I>
  * <h4>@anchor PINState_external External representation</h4>
  * The external PIN state representation consists of lines of
  * characters (ISO 8859-1). The lines are separated with NL, CR
  * or CRNL.
  *
  * The representation consists of four parts:
  * <ol>
  *  <li>format identifier and version
  *  <li>expire date
  *  <li>grace logins left
  *  <li>hashes of old PINs
  * </ol>
  * All lines follow the format `<b>keyword: value</b>'.
  * 
  * <h5>Concrete Syntax</h5>
  * <ol>
  *  <li><b>SecudePINState: 1.0</b>
  *  <li><b>LoginTime:</b> <i>unix time stamp encoded as a decimal
  * 	 number</i>
  *  <li><b>GraceLogins:</b> <i>number of logins since PIN has expired</i>
  *  <li><b>P</b><i>n</i><b>:</b> <i>16 bytes MD5 hash encoded
  * 	hexadecimally</i> - where <i>n</i> is a decimal number
  *    <br><i>n = 0, ..., k</i> for some <i>k</i>
  *    <br>the first line starts with <b>P0:</b>, the second with
  *    <b>P1:</b>, etc.
  *    <br><b>P0:</b> gives the hash for the youngest PIN
  * </ol>
  *
  * <B>Synopsis:</B> <TT>\#include "%af.h"</TT>
  * @anchor PINState_internal
  * @ingroup af_pin
  */
typedef struct PINState {
  time_t logintime;   /**< last login time */
  int gracelogins;    /**< number of logins since PIN has expired */
  int npin;           /**< number of PIN hashes stored in <i>pin</i> */
  OctetString **pin;  /**< hashes of old PINs; NULL if <i>npin = 0</i> */
} PINState;

/***** Structure PINContext *****/
/** Context information for checking new PINs.
  * 
  * The <B>PIN context</B> data structure can be used by
  * applications to provide environmental information to #af_pin_checknew,
  * such as user name, machine name, telephone number, etc. This information
  * can be referenced in PIN policy rules in order to prevent
  * users from choosing easily guessable PINs.
  * 
  * <B>Synopsis:</B> <TT>\#include "%af.h"</TT>
  * 
  * @ingroup af_pin
  */
typedef struct PINContext {
  char *domain_name;   /**< Domain name (DNS or NT) of the used host <b>(\%d)</b> */
  char *first_name;    /**< User's first name <b>(\%f)</b> */
  char *group_name;    /**< Unix group name of the users primary group <b>(\%g)</b> */
  char *host_name;     /**< Name host the application is running on <b>(\%h)</b> */
  char *middle_name;   /**< User's middle name <b>(\%m)</b> */
  char *office;        /**< Name of the user's office (C5.15, e.g.) <b>(\%o)</b> */
  char *last_name;     /**< User's last name <b>(\%s)</b> */
  char *extension;     /**< Number of user's telephone extension <b>(\%t)</b> */
  char *user_name;     /**< user's login name <b>(\%u)</b> */
  char *home_phone;    /**< user's home telephone number <b>(\%x)</b> */
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
/***** Structure AF_options *****/
/** @ingroup header_af
  */
struct AF_options {
/** Don't verify system alias list */
	Boolean accept_alias_without_verification;
/** deal the the own %FCPath as trusted
  * during validation process
  */
	Boolean af_FCPath_is_trusted;
/** Access Directory when missing
  * certificates or %CRL's
  */
	Boolean af_access_directory;
/** Check vaditity during validation process */
	Boolean af_check_Validity;
/** Check revocation lists during
  * validation process
  */
	Boolean af_chk_crl;
/** Check vaditity of own certificate
  * when signing
  */
	Boolean af_sign_check_Validity;
/** check for %aliases e.g. when printing
  * names
  */
	Boolean af_use_alias;
/** verbose level */
	Boolean af_verbose;
/** check the PEM subordination rule
  * during validation process
  */
	Boolean chk_PEM_subordination;
/** the name of the Directory System
  * Agent (DSA) for X.500 access OR
  * the name and port of the LDAP server
  */
	char    af_dir_dsaname[512];
/** the name of the tailor file for
  * X.500 access OR
  * a string controlling the type of access
  * for LDAP operations.
  */
	char    af_dir_tailor[512];
/** the binding type for X.500 or LDAP
  * operations
  */
	int     af_dir_authlevel;
/** Directory System Agent (DSA)
  * is bound. Not used for LDAP
  * operations.
  */
	Boolean af_dir_dsabound;
/** Distinguished name used
  * for authentication to the
  * Directory System Agent (DSA)
  * or LDAP server respectively.
  */
	DName  *directory_user_dname;

/* for v3 certificates: */

        /* A set of subtree specifications within which ALL subject names must fall */
/** <B>Verification of X.509 v3 certificates:</B>
  * A set of subtree specifications within
  * which ALL subject names must fall.
  */
        GeneralSubtrees *permittedSubtrees;
 
        /* A set of subtree specifications within which NO subject name may fall */
/** <B>Verification of X.509 v3 certificates:</B>
  * A set of subtree specifications within
  * which NO subject name may fall.
  */
        GeneralSubtrees	 *excludedSubtrees;
 
        /* if an acceptable policy needs to explicitly appear in the
           certificate policies extension field of all certificates in the path */
/** <B>Verification of X.509 v3 certificates:</B>
  * If an acceptable policy needs to explicitly appear
  * in the certificate policies extension field of all
  * certificates in the path.
  */
        Boolean           explicitPolicy;
 
        /* if policy mapping is inhibited in the certification path */
/** <B>Verification of X.509 v3 certificates:</B>
  * If policy mapping is inhibited in the
  * certification path.
  */
        Boolean           inhibitPolicyMapping;
 
        /* Details of explicitPolicy and/or inhibitPolicyMapping constraints which
           have been stipulated but are yet to take effect. SkipCert gives the number
           of certificates yet to skip before the constraint takes effect */
        /* If -1 they are unset */
/** <B>Verification of X.509 v3 certificates:</B>
  * Details of explicitPolicy constraints which
  * have been stipulated but are yet to take effect.
  * SkipCert gives the number of certificates yet to
  * skip before the constraint takes effect.
  * If -1 they are unset.
  */
        SkipCerts         explicitPolicyPending;
/** <B>Verification of X.509 v3 certificates:</B>
  * Details of inhibitPolicyMapping constraints which
  * have been stipulated but are yet to take effect.
  * SkipCert gives the number of certificates yet to
  * skip before the constraint takes effect.
  * If -1 they are unset.
  */
        SkipCerts         PolicyMappingInhibitPending;

/** If the public keys stored in the PKList are trusted
  * during verification, i.e. the process may stop at any
  * PK/certificate found in the PKList. The normal value
  * is TRUE. If used in a mode conformant to German
  * signature law (SigG), this flag has to be set to FALSE.
  */
	Boolean af_PKList_is_trusted;
/** If the public keys stored in the PCAList are trusted
  * during verification, i.e. the process may stop at any
  * PK/certificate found in the PKList.
  * The PCAList is normally used to store root keys of other
  * hierarchies.
  * The normal value
  * is TRUE. If used in a mode conformant to German
  * signature law (SigG), this flag has to be set to FALSE.
  */
	Boolean af_PCAList_is_trusted;
/** If the own certificate is trusted <I>per se</I> during
  * verification. The normal value
  * is TRUE. If used in a mode conformant to German
  * signature law (SigG), this flag has to be set to FALSE.
  */
	Boolean af_Cert_is_trusted;
/** If the data of the %PKRoot object inside the PSE may be
  * cached at any place in the SECUDE runtime system or not.
  * For enhanced performance some data is cached in various
  * places (card plug-in, AF layer, etc.) For that, the
  * normal value is FALSE (i.e. allow caching).
  * If used in a mode conformant to German
  * signature law (SigG), this flag has to be set to TRUE.
  */
	Boolean af_never_cache_PKRoot;
    /* to be able to sign with 'Encryption' Cert */
/** Use authentication key pair for signature and encryption purpose instead of the normal key pair */
    Boolean          use_authentication_cert;
/** Use encryption key pair for signature purpose instead of signature key pair */
    Boolean          use_enc_cert_for_signature;
};

/***** Typedef AF_DEF_OPTIONS *****/
/** @ingroup header_af
  */

#define AF_DEF_OPTIONS {FALSE,FALSE,FALSE,TRUE,FALSE,TRUE,TRUE,FALSE,FALSE,{ '\0' },{ '\0' },0,FALSE,(DName *)0,UNBOUNDED,EMPTY,TRUE,TRUE,-1,-1, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE}


typedef struct AF_ctx AF_ctx;
/***** Structure AF_ctx *****/
/** @ingroup header_af
  */
struct AF_ctx {
/** see #AF_DEF_OPTIONS */
	AF_options		 options;
	
/** Handle used by the SECURE API */
	PSESel			*psesel;

/** PSE restricted to one RSA key pair */
	Boolean 		 onekeypaironly;		 
/** Name of the PSE */
	char 			*pse_name;
/** CA directory */
	char 			*ca_dir;
/** Database of certificates for a CA */
	char 			*cert_db;
/** Database of users for a CA */
	char 			*user_db;
/** Database of %CRLs for a CA */
	char 			*crl_db;
/** Name of a logfile for a CA */
	char 			*ca_log_file_name;
/** Logfile for a CA */
	FILE 			*ca_log_file;
/** Result of last verification process */
	VerificationResult 	*verifresult;
	Boolean			 call_af_verify;
	
/** Cache of PSE object SignCert or NULL if
  * not existent
  */
	Certificate 		*SignCert_cache;
/** Cache of PSE object EncCert or NULL if
  * not existent
  */
	Certificate 		*EncCert_cache;
/** Cache of PSE object Cert or NULL if
  * not existent
  */
	Certificate 		*Cert_cache;
/** Cache of PSE object SignCSet or NULL if
  * not existent
  */
	SET_OF_Certificate 	*SignCSet_cache;
/** Cache of PSE object EncCSet or NULL if
  * not existent
  */
	SET_OF_Certificate 	*EncCSet_cache;
/** Cache of PSE object CSet or NULL if
  * not existent
  */
	SET_OF_Certificate 	*CSet_cache;
/** Cache of PSE object SignSK or NULL if
  * not existent
  */
	KeyInfo 		*SignSK_cache;
/** Cache of PSE object DecSKnew or NULL if
  * not existent
  */
	KeyInfo 		*DecSKnew_cache;
/** Cache of PSE object DecSKold or NULL if
  * not existent
  */
	KeyInfo 		*DecSKold_cache;
/** Cache of PSE object SKnew or NULL if
  * not existent
  */
	KeyInfo 		*SKnew_cache;
/** Cache of PSE object SKold or NULL if
  * not existent
  */
	KeyInfo 		*SKold_cache;
/** Cache of PSE object %FCPath or NULL if
  * not existent
  */
	FCPath 			*FCPath_cache;
/** Cache of PSE object %PKRoot or NULL if
  * not existent
  */
	PKRoot 			*PKRoot_cache;
/** Cache of PSE object PKList or NULL if
  * not existent
  */
	PKList 			*PKList_cache;
/** Cache of PSE object EKList or NULL if
  * not existent
  */
	PKList 			*EKList_cache;
/** Cache of PSE object PCAList or NULL if
  * not existent
  */
	PKList 			*PCAList_cache;
/** Cache of PSE object CrossCSet or NULL if
  * not existent
  */
	SET_OF_CertificatePair 	*CrossCSet_cache;
/** Cache of PSE object CrlSet or NULL if
  * not existent
  */
	CrlSet 			*CrlSet_cache;
/** Cache of PSE object SerialNumber or
  * NULL if not existent
  */
	SerialNumber 		*SerialNumber_cache;
/** Cache of PSE object AliasList or NULL if
  * not existent
  */
	AliasList 		*AliasList_cache;
/** Cache of PSE object SignCert or NULL if
  * not existent
  */
	QuipuPWD		 QuipuPWD_cache;
/** Cache of PSE object DHparam or NULL if
  * not existent
  */
	AlgId 			*DHparam_cache;
/* for v3 certificates: */
/** Cache of PSE object policies or NULL if
  * not existent
  */
	PolicyList 		*policies_cache;
	
/** TRUE if PSE object SignCert is read and
  * saved in SignCert_cache, otherwise
  * FALSE
  */
	Boolean			 SignCert_read;
/** TRUE if PSE object EncCert is read and
  * saved in EncCert_cache, otherwise
  * FALSE
  */
	Boolean			 EncCert_read;
/** TRUE if PSE object Cert is read and
  * saved in Cert_cache, otherwise
  * FALSE
  */
	Boolean			 Cert_read;
/** TRUE if PSE object SignCSet is read and
  * saved in SignCSet_cache, otherwise
  * FALSE
  */
	Boolean			 SignCSet_read;
/** TRUE if PSE object SignCSet is read and
  * saved in SignCSet_cache, otherwise
  * FALSE
  */
	Boolean			 EncCSet_read;
/** TRUE if PSE object CSet is read and
  * saved in CSet_cache, otherwise
  * FALSE
  */
	Boolean			 CSet_read;
/** TRUE if PSE object CSet is read and
  * saved in CSet_cache, otherwise
  * FALSE
  */
	Boolean			 SignSK_read;
/** TRUE if PSE object DecSKnew is read and
  * saved in DecSKnew_cache, otherwise
  * FALSE
  */
	Boolean			 DecSKnew_read;
/** TRUE if PSE object DecSKold is read and
  * saved in DecSKold_cache, otherwise
  * FALSE
  */
	Boolean			 DecSKold_read;
/** TRUE if PSE object SKnew is read and
  * saved in SKnew_cache, otherwise
  * FALSE
  */
	Boolean			 SKnew_read;
/** TRUE if PSE object SKold is read and
  * saved in SKold_cache, otherwise
  * FALSE
  */
	Boolean			 SKold_read;
/** TRUE if PSE object %FCPath is read and
  * saved in FCPath_cache, otherwise
  * FALSE
  */
	Boolean			 FCPath_read;
/** TRUE if PSE object %FCPath is read and
  * saved in FCPath_cache, otherwise
  * FALSE
  */
	Boolean			 PKRoot_read;
/** TRUE if PSE object PKList is read and
  * saved in PKList_cache, otherwise
  * FALSE
  */
	Boolean			 PKList_read;
/** TRUE if PSE object EKList is read and
  * saved in EKList_cache, otherwise
  * FALSE
  */
	Boolean			 EKList_read;
/** TRUE if PSE object PCAList is read and
  * saved in PCAList_cache, otherwise
  * FALSE
  */
	Boolean			 PCAList_read;
/** TRUE if PSE object CrossCSet is read
  * and saved in CrossCSet_cache, otherwise
  * FALSE
  */
	Boolean			 CrossCSet_read;
/** TRUE if PSE object CrlSet is read and
  * saved in CrlSet_cache, otherwise
  * FALSE
  */
	Boolean			 CrlSet_read;
/** TRUE if PSE object SerialNumber is read
  * and saved in SerialNumber_cache,
  * otherwise FALSE
  */
	Boolean			 SerialNumber_read;
/** TRUE if PSE object AliasList is read
  * and saved in AliasList_cache,
  * otherwise FALSE
  */
	Boolean			 AliasList_read;
/** TRUE if PSE object QuipuPWD is read
  * and saved in QuipuPWD_cache,
  * otherwise FALSE
  */
	Boolean			 QuipuPWD_read;
/** TRUE if PSE object DHparam is read
  * and saved in DHparam_cache,
  * otherwise FALSE
  */
	Boolean			 DHparam_read;

/* for v3 certificates: */
/** TRUE if PSE object policies is read
  * and saved in policies_cache,
  * otherwise FALSE
  */
	Boolean 		 policies_read;
	
/** ??? */
	Boolean			 got_system_aliases_once;
/** ??? */
	Boolean			 got_user_aliases_once;
/** ??? */
	Boolean			 kill_aliases_without_reading;
	
/** ??? */
	AliasList 		*aliaslist;
/** ??? */
	AliasList 		*last_aliaslist;
/** ??? */
	Boolean     		 systemfile_write_protection;
/** alias filter setting: systemalias, useralis, notstored */
	AliasFile		 filter_aliases;
/** USER alias file selected */
	Boolean     		 filter_user_aliases;
/** SYSTEM alias file selected */
	Boolean     		 filter_system_aliases;
/** list of %aliases */
	AliasList		*la;

/** smartcard used */
	Boolean     		 is_sc;

#ifdef LDAP_WITH_DL_OPEN
/*********************************************** 
 * Here we have LDAP stuff for loading the ldap shared lib
 ***********************************************/
	void			*ldap_library;
#endif
    /* to work with a 3rd Key Pair for authentication */
	Certificate 	*AuthCert_cache;
	Boolean			 AuthCert_read;
	KeyInfo 		*AuthSK_cache;
	Boolean			 AuthSK_read;

    CRLNumber       *CRLNumber_cache;
    Boolean          CRLNumber_read;

    char            *abs_psename; /* stores the PSE locator, e.g. "p11sc:5:extension" (as given to af_open) */
    PKList			*bridge_certs;
};


/***** Typedef PSE *****/
/** Personal Security Environment
  * @ingroup header_af
  */
typedef AF_ctx *PSE;

/***** Typedef AF_HANDLE *****/
/** @ingroup header_af
  */
typedef void *AF_HANDLE;


#define CRED_GSS NULL
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

/***** Structure RDNalias *****/
/** @ingroup header_af
  */
struct RDNalias {
	ObjId		*type   ;
	char		*value  ;
	char		*replacement  ;
};
/***** Typedef RDNalias *****/
/** @ingroup header_af
  */
typedef struct RDNalias RDNalias;

/***** Typedef SET_OF_RDNalias *****/
/** @ingroup header_af
  */
typedef SET_OF(RDNalias) SET_OF_RDNalias;

/***** Enumeration eRevocationCheckType *****/
/** Used within OcspCheck
  * @ingroup header_af
  */
enum eRevocationCheckType
{
    e_NotAvailableYet = 0 /** no settings have been evaluated yet for the given certificate(s) */
    , e_NoRevocationCheck /** There is no revocation check to be performed */
    , e_CheckCRL          /** CRL checking is to be done for the given user certificate */
    , e_CheckOCSP         /** OCSP checking is to be done for the given user certificate */
};
/***** Typedef eRevocationCheckType *****/
/** @ingroup header_af
  */
typedef enum eRevocationCheckType eRevocationCheckType;

/***** Enumeration e_ocsp_auth_scheme *****/
/** Used within @ref OcspCheck.
  * @sa af_set_RevocationCheckOptions
  * @ingroup header_af
  */
enum e_ocsp_auth_scheme
{
    ocsp_auth_RFC = 0     /* default authorization scheme according to RFC 2560 */
    , ocsp_auth_ISIS_MTT  /* ISIS-MTT like authorization: In order to ensure SigG conformity,
                             the responder must have a certificate issued by a RegTP root.
                             We check, if the issuer is self signed and trusted. Its the responsibility of the 
                             user-application to ensure that only RegTP certs were installed as trust anchors */
};

/***** Typedef eRevocationCheckType *****/
/** @ingroup header_af
  */
typedef enum e_ocsp_auth_scheme e_ocsp_auth_scheme;

#include <secude/ocsp.h>
#include <secude/urlref.h>

/***** Typedef OcspCheck *****/
/** This is a handle to any information/context 
  * about the revocation checking process
  * of a given certificate.
  * 
  * @ingroup header_af
  */
typedef struct OcspCheck OcspCheck;

/***** Typedef H_OCSP_CHECK *****/
/** This is a handle to any information/context 
  * about the revocation checking process
  * of a given certificate.
  * 
  * @ingroup header_af
  */
typedef OcspCheck * H_OCSP_CHECK;

#include <secude/ocsp.h>

/***** Structure OcspCheckResults *****/
/** This is a handle to any information/context 
  * about the revocation checking process
  * of a given certificate.
  * 
  * @ingroup header_af
  */
struct OcspCheckResults;
struct OcspCheckResults
{
    /** Gives a summary of 
      * the entire revocation check.
      * TRUE means that the certificate was not revoked and the CRL DP or OCSP reponder
      * is authorized to give information about the queried certificate.
      */
    Boolean                  m_bCertOK;

    /** More detailed information about the OCSP check.
      */
    OCSPQueryCertStatusInfo  mQueryCertStatus;
    /** If certificate of the revocation check authority (i.e. OCSP responder or CRL DP)
      * was verified, results can be found here.
      */
    VerificationResult     * m_p_responder_verif_res;
    /** If certificate of the revocation check authority (i.e. OCSP responder or CRL DP)
      * was checked for revocation itself, results can be found here.
      */
    struct OcspCheckResults * m_pCheckOfAuthortity;
                                        /* Contains the result of a revocation check of the certificate of the authority itself.
                                        (e.g. CRL check of OCSP responder */

    OCSPQuery              * m_p_query; /* OCSP Query handle. If not NULL,
                                       an OCSP query was launched and the handle gives access to
                                       certificate status, certificate of responder etc.
                                        */
};
typedef struct OcspCheckResults OcspCheckResults;

typedef struct PCAList_IF PCAList_IF;
struct PCAList_IF
{
    RC (*m_if)(PCAList_IF*, const Certificate*, const PKList **);
};

#define SECUDE_AF_INCLUDE 1
#include <secude/af_p.h>
#undef SECUDE_AF_INCLUDE
#include <secude/isode.h>

#endif /* _AF_*/



