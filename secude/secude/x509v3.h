/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/x509v3.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef X509V3_H_
#define X509V3_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    /* used for GeneralNames(otherName), but "useful" ASN.1 type in general! */
/***** Structure TYPE_IDENTIFIER *****/
/** Type identifier.
  * Used for GeneralNames(otherName), but "useful" ASN.1 type in general!
  * @ingroup header_x509v3
  */
struct TYPE_IDENTIFIER {
    ObjId	*type_id;
    OctetString	*value; /**< contains DER code */
};
/***** Typedef TYPE_IDENTIFIER *****/
/** @ingroup header_x509v3
  */
typedef struct TYPE_IDENTIFIER TYPE_IDENTIFIER;

/***** Typedef ExtnId *****/
/** extension object identifier
  * @ingroup header_x509v3
  */
typedef ObjId   ExtnId;

#if defined MACRO_SEP_LIKE_STDC
/***** Define EXTENSION *****/
/** Macro to generate extension structures.
  * @ingroup header_x509v3
  */
#define EXTENSION(t) struct Ext_##t {                            \
        Boolean         critical;                   \
        t               *extnValue;                 \
        int         seqnum;                         \
}
#else
#define EXTENSION(t) struct Ext_/**/t {     \
        Boolean         critical;                   \
        t               *extnValue;                 \
        int         seqnum; \
}
#endif

/***** Typedef Ext_void *****/
/** x509v1 and v2 do not contain
  * extensions
  * @ingroup header_x509v3
  */
typedef EXTENSION(void) Ext_void;

/***** Structure v3Extension *****/
/** @ingroup header_x509v3
  */
struct v3Extension {
/** Object Identifier of the extension */
    ExtnId       *extnId;
/** criticality flag */
    Boolean       critical;
/** encoded extension */
    OctetString  *extnDERcode;
/** for internal use only, not encoded */
    int		  mmode; /* for internal use only, not encoded */
    int         seqnum; /* to save the sequence of the extensions */
};
/***** Typedef v3Extension *****/
/** @ingroup header_x509v3
  */
typedef struct v3Extension v3Extension;

#if defined FOR_DOCUMENTATION
#include <secude/sec_glob.h>
#endif
/***** Typedef SEQUENCE_OF_Extension *****/
/** sequence of extensions
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(v3Extension) SEQUENCE_OF_Extension;

/* EXTENSIONS */

/* 
typedef char    	DirectoryString;    ??????? 
typedef char    	IA5String;
typedef char    	ORAddress;
 
typedef struct TypeIdentifier{
        ObjId                   *id;
        OctetString             *type;  ANY identified by id 
}TypeIdentifier;
 
typedef TypeIdentifier  OtherName;

typedef struct EDIPartyName{
        DirectoryString         *nameAssigner;	OPTIONAL
        DirectoryString         *partyName;  
}EDIPartyName;

typedef struct GeneralNames{
        OtherName         	*otherName;
        IA5String               *rfc822Name;
        IA5String               *dNSName;
        ORAddress               *x400Address;
        Name                    *directoryName;
        EDIPartyName            *ediPartyName;
        IA5String               *url;       
        OctetString             *ipAddress; 
        ObjId                   *registeredID;
}GeneralNames;
*/

/***** Enum GeneralName_number *****/
/** Each name form is associated with a number.
  * @ingroup header_x509v3
  */
typedef enum { GNany = -1,  /**< <TT>=-1</TT> */
	       GNotherName = 0,    /**< <TT>=0</TT> */
	       GNrfc822Name,
	       GNdNSName,
	       GNx400Address,
	       GNdirectoryName,
	       GNediPartyName,
	       GNuRI,
	       GNiPAddress,
	       GNregisteredID,
	       GNUPPERLIMIT,
	       GNunknown = 31      /**< <TT>=31</TT> */
} GeneralName_number;

/* Documentation: Initialization of GeneralName_descr should agree with afinit.c */
/***** External GeneralName_descr *****/
/** Name forms, array indexed by #GeneralName_number.
  * The array <B>%GeneralName_descr</B> is initialized as:
  * <PRE>
  * char *<b>GeneralName_descr</b>[] = {'other','RFC822', 'DNS', 'X.400',
  *  '%DName', 'EDI Party', 'URI', 'IP Address', 'reg. ID'};
  * </PRE> 
  * @ingroup header_x509v3
  */
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX GeneralName_descr[];

/* Documentation: Initialization of GeneralName_supported should agree with afinit.c */
/***** External GeneralName_supported *****/
/** Supported name forms, array indexed by #GeneralName_number.
  * The array <B>%GeneralName_supported</B> is initialized as:
  * <PRE>
  * char *<b>GeneralName_supported</b>[] = {'TRUE','TRUE', 'TRUE', 'FALSE',
  *  'TRUE', 'FALSE', 'TRUE', 'TRUE', 'TRUE' };
  * </PRE> 
  * @ingroup header_x509v3
  */
extern Boolean SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  GeneralName_supported[];

/* in afinit.c:

char  *GeneralName_descr[] = {
        'other',
	'RFC822',
	'DNS',
	'X.400',
	'DName',
	'EDI Party',
	'URI',
	'IP Address',
	'reg. ID'
};

Boolean  GeneralName_supported[] = {
        FALSE, 
	TRUE,   
	TRUE,
	FALSE,
	TRUE,
	FALSE,
	TRUE,
	TRUE,
	TRUE
};
*/

/***** Typedef GeneralName *****/
/** general name form.
  * This type stores the internal
  * representation of a GeneralName (ASN.1
  * encoded). Beware of the difference
  * of GeneralName and
  * #GeneralNames
  * (singular and plural).
  * @ingroup header_x509v3
  */
typedef OctetString GeneralName;

/***** Typedef GeneralNames *****/
/** sequence of general names. Please
  * use the <A href="afgna.htm">
  * methods that operate on
  * GeneralNames</A>
  * instead of directly manipulating
  * these structure
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(GeneralName) GeneralNames;


        /********************************************************/
        /*              KEY and POLICY Information              */
        /********************************************************/
 
                /****************************/
                /* Authority Key Identifier */
                /****************************/


/***** Typedef KeyIdentifier *****/
/** key identifier
  * @ingroup header_x509v3
  */
typedef OctetString     KeyIdentifier;
/***** Typedef CertificateSerialNumber *****/
/** serial number of a certificate
  * @ingroup header_x509v3
  */
typedef OctetString     CertificateSerialNumber;   /* Long */
  
/***** Structure AuthorityKeyId *****/
/** @ingroup header_x509v3
  */
struct AuthorityKeyId{
/** key identifier of the issuing CA */
        KeyIdentifier           *authorityKeyIdentifier;    /* OPTIONAL */
/** general names of the issuing CA */
        GeneralNames            *authorityCertIssuer;       /* OPTIONAL */
/** serial number of the issuing CA's certificate */
        CertificateSerialNumber *authorityCertSerialNumber; /* OPTIONAL */
};
/***** Typedef AuthorityKeyId *****/
/** @ingroup header_x509v3
  */
typedef struct AuthorityKeyId AuthorityKeyId;

/* characteristics of Extension:
   certificate and CRL extension
   both CA- and end-entity certificates
   always non-critical
*/
/***** Typedef Ext_AuthorityKeyId *****/
/** certificate and %CRL extension;
  * both CA- and end-entity certificates;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(AuthorityKeyId)       Ext_AuthorityKeyId;
 

                /***************************/
                /* Subject Key Identifier: */
                /***************************/

/***** Typedef SubjectKeyId *****/
/** subject's key identifier
  * @ingroup header_x509v3
  */
typedef KeyIdentifier SubjectKeyId;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
/***** Typedef Ext_SubjectKeyId *****/
/** only certificate extension;
  * both CA- and end-entity certificates;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(SubjectKeyId)       Ext_SubjectKeyId;

		/**************/
                /* Key Usage: */
                /**************/
                
/***** Enum KeyUsageTypes *****/
/** Each KeyUsage type is associated with a number.
  * @ingroup header_x509v3
  */
typedef enum { digitalSignature = 0,   /**< <TT>=0</TT> */
               nonRepudiation,
               keyEncipherment,
               dataEncipherment,
               keyAgreement,
               keyCertSign,
               cRLSign,
	       encipherOnly,
	       decipherOnly
} KeyUsageTypes; 

/***** Structure KeyUsage *****/
/** @ingroup header_x509v3
  */
struct KeyUsage {
/** if TRUE, key may be used for signing */
        Boolean         digitalSignature;
/** if TRUE, key may be used for nonRepudiation */
        Boolean         nonRepudiation;
/** if TRUE, key may be used to encrypt  other keys */
        Boolean         keyEncipherment;
/** if TRUE, key may be used for data encryption */
        Boolean         dataEncipherment;
/** if TRUE, key may be used for key agreement */
        Boolean         keyAgreement;
/** if TRUE, key may be used to issue certificates */
        Boolean         keyCertSign;
/** if TRUE, key may be used to issue CRLs */
        Boolean         cRLSign;
/** if TRUE and <I>keyAgreement</I> bit is also set,
  * key may be used to encipher data while performing key agreement
  */
        Boolean         encipherOnly;
/** if TRUE and <I>keyAgreement</I> bit is also set,
  * key may be used to decipher data while performing key agreement
  */
        Boolean         decipherOnly;
};
/***** Typedef KeyUsage *****/
/** @ingroup header_x509v3
  */
typedef struct KeyUsage KeyUsage;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates (*Sign bits CA only)
   critical at the option of the issuer
*/
/***** Typedef Ext_KeyUsage *****/
/** certificate and %CRL extension;
  * both CA- and end-entity certificates (*Sign bits CA only);
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(KeyUsage)       Ext_KeyUsage;

		/**************/
                /* Extended Key Usage: */
                /**************/
/***** Typedef KeyPurposeId *****/
/** @ingroup header_x509v3
  */
typedef ObjId KeyPurposeId;
/***** Typedef ExtKeyUsage *****/
/** @ingroup header_x509v3
  */
typedef SEQUENCE_OF(KeyPurposeId) ExtKeyUsage;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates 
   critical at the option of the issuer
*/
/***** Typedef Ext_ExtKeyUsage *****/
/** @ingroup header_x509v3
  */
typedef EXTENSION(ExtKeyUsage)       Ext_ExtKeyUsage;
                
                /*****************************/
                /* Private Key Usage Period: */
                /*****************************/

/***** Structure PrivateKeyUsagePeriod *****/
/** @ingroup header_x509v3
  */
struct PrivateKeyUsagePeriod{
/** validity of the private key begins;  OPTIONAL  */
        GeneralTime           *notBefore;    /* OPTIONAL */
/** validity of the private key ends;  OPTIONAL  */
        GeneralTime           *notAfter;     /* OPTIONAL */
};
/***** Typedef PrivateKeyUsagePeriod *****/
/** @ingroup header_x509v3
  */
typedef struct PrivateKeyUsagePeriod PrivateKeyUsagePeriod;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
/***** Typedef Ext_PrivateKeyUsagePeriod *****/
/** only certificate extension;
  * both CA- and end-entity certificates;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(PrivateKeyUsagePeriod)       Ext_PrivateKeyUsagePeriod;
 	

 
                /************************/
                /* Certificate Policies */
                /************************/
 
/* HRS 18.10.99 */

enum DisplayText_Types { DTT_visibleString = 26, DTT_ia5String = 22, DTT_bmpString = 30, DTT_utf8String = 12 };

/***** Structure DisplayText *****/
/** Display text.
  * @ingroup header_x509v3
  */
struct DisplayText {
	int choice;
	union {
	   char *visibleString;
	   char *ia5String;
	   OctetString *bmpString;
	   char *utf8String;
	} un;
};
/***** Typedef DisplayText *****/
/** @ingroup header_x509v3
  */
typedef struct DisplayText DisplayText;

/***** Typedef SEQUENCE_OF_Integer *****/
/** @ingroup header_x509v3
  */
typedef SEQUENCE_OF(Integer) SEQUENCE_OF_Integer;

/***** Structure NoticeReference *****/
/** @ingroup header_x509v3
  */
struct NoticeReference {
	DisplayText *organization;
	SEQUENCE_OF_Integer *noticeNumbers;
};
/***** Typedef NoticeReference *****/
/** @ingroup header_x509v3
  */
typedef struct NoticeReference NoticeReference;

/***** Structure UserNotice *****/
/** @ingroup header_x509v3
  */
struct UserNotice {
	NoticeReference *noticeRef; /* OPTIONAL */
	DisplayText *explicitText; /* OPTIONAL */
};
/***** Typedef UserNotice *****/
/** @ingroup header_x509v3
  */
typedef struct UserNotice UserNotice;


/***** Structure PolicyQualifierInfo *****/
/** @ingroup header_x509v3
  */
struct PolicyQualifierInfo {
/** policy qualifier */
    ObjId       * qualifierId;
/** encoded policy qualifier;  OPTIONAL  */
    OctetString * qualifierDERcode; /* OPTIONAL */
	int           seqnum; /* internal: ordering of PQIs (is not encoded) */
    int	          mmode; /* for internal use only, not encoded/copied */
};
/***** Typedef PolicyQualifierInfo *****/
/** @ingroup header_x509v3
  */
typedef struct PolicyQualifierInfo PolicyQualifierInfo;

/***** Typedef PolicyQualifierInfos *****/
/** certificate policy qualifier
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(PolicyQualifierInfo) PolicyQualifierInfos;

/***** Typedef CertPolicyId *****/
/** certificate policy identifier
  * @ingroup header_x509v3
  */
typedef ObjId CertPolicyId;

/***** Structure PolicyInformation *****/
/** @ingroup header_x509v3
  */
struct PolicyInformation {
/** policy identifier */
    CertPolicyId           * policyIdentifier;
/** policy qualifier;  OPTIONAL  */
    PolicyQualifierInfos   * policyQualifiers; /* OPTIONAL */

	/* changed 28.10.99 HRS:
	 * the standard PKIX qualifiers CPS and UserNotice are stored
	 * separately from the above policyQualifiers... */
	char *pkix_cps; /* "OPTIONAL" */
	UserNotice *pkix_unotice; /* "OPTIONAL" */
	int pkix_cps_seqnum, pkix_unotice_seqnum; /* internal: ordering... */
};
/***** Typedef PolicyInformation *****/
/** @ingroup header_x509v3
  */
typedef struct PolicyInformation PolicyInformation;

/***** Typedef CertificatePolicies *****/
/** certificate policies
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(PolicyInformation) CertificatePolicies;
 
/* for use in af.h ??? */

/***** Typedef CertQualifierSet *****/
/** set of policy qualifiers
  * @ingroup header_x509v3
  */
typedef SET_OF(PolicyQualifierInfo)	CertQualifierSet;


/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
/***** Typedef Ext_CertificatePolicies *****/
/** only certificate extension;
  * both CA- and end-entity certificates;
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(CertificatePolicies)    Ext_CertificatePolicies;
 
                /********************/
                /* Policy Mappings  */
                /********************/

/***** Structure MappingElement *****/
/** @ingroup header_x509v3
  */
struct MappingElement {
/** policy ID of issuer's domain */
        CertPolicyId            * issuerDomainPolicy;
/** policy ID of subject's domain */
        CertPolicyId            * subjectDomainPolicy;
};
/***** Typedef MappingElement *****/
/** @ingroup header_x509v3
  */
typedef struct MappingElement MappingElement;

/***** Typedef PolicyMappings *****/
/** contains mapped policy IDs
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(MappingElement)     PolicyMappings;
 
/* characteristics of Extension:
   only certificate extension
   only CA certificates
   always non-critical
*/
/***** Typedef Ext_PolicyMappings *****/
/** only certificate extension;
  * only CA certificates;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(PolicyMappings)         Ext_PolicyMappings;
  
 
        /********************************************************/
        /*              SUBJECT and ISSUER attributes           */
        /********************************************************/


 
                /****************************/
                /* Subject alternative name */
                /****************************/
  
/***** Typedef SubjectAltName *****/
/** subject's alternative name
  * @ingroup header_x509v3
  */
typedef GeneralNames SubjectAltName;
 
/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
/***** Typedef Ext_SubjectAltName *****/
/** only certificate extension;
  * both CA- and end-entity certificates;
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(SubjectAltName)             Ext_SubjectAltName;

 
                /****************************/
                /* Issuer alternative name */
                /****************************/
 
/***** Typedef IssuerAltName *****/
/** issuer's alternative name
  * @ingroup header_x509v3
  */
typedef GeneralNames IssuerAltName;

/* characteristics of Extension:
   both certificate and CRL extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
/***** Typedef Ext_IssuerAltName *****/
/** both certificate and %CRL extension;
  * both CA- and end-entity certificates;
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(IssuerAltName)             Ext_IssuerAltName;
 
 
                /********************************/
                /* Subject Directory Attributes */
                /********************************/
 
/***** Typedef DirectoryAttributes *****/
/** any attributes
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(Attr)  DirectoryAttributes;
 
/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
/***** Typedef Ext_DirectoryAttributes *****/
/** only certificate extension;
  * both CA- and end-entity certificates;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(DirectoryAttributes)     Ext_DirectoryAttributes;
 
 
        /********************************************************/
        /*          CERTIFICATION PATH constraints              */
        /********************************************************/
 
                /*********************/
                /* Basic Constraints */
                /*********************/
  
/***** Structure BasicConstraints *****/
/** @ingroup header_x509v3
  */
struct BasicConstraints{
/** if TRUE, certificate subject is allowed to act as a CA;  DEFAULT: FALSE  */
	Boolean               cA;		      /* DEFAULT FALSE */
/** to constrain the number of CAs in a path;  OPTIONAL; (negative if not present) */
        int                   pathLenConstraint;      /* OPTIONAL */
                                       /* negative if not present */
};
/***** Typedef BasicConstraints *****/
/** @ingroup header_x509v3
  */
typedef struct BasicConstraints BasicConstraints;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
/***** Typedef Ext_BasicConstraints *****/
/** only certificate extension;
  * both CA- and end-entity certificates;
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(BasicConstraints)       Ext_BasicConstraints;
 
  
                /********************/
                /* Name Constraints */
                /********************/

/***** Typedef BaseDistance *****/
/** distance within a %FCPath
  * @ingroup header_x509v3
  */
typedef int    BaseDistance;
 
/***** Structure GeneralSubtree *****/
/** @ingroup header_x509v3
  */
struct GeneralSubtree{
/** top of the subtree */
        GeneralName     *base;       /* ...Name not ...Names !!! */
/**  DEFAULT: 0  */
        BaseDistance     minimum;  /* DEFAULT 0 */ 
/**  OPTIONAL; negative if not present */
        BaseDistance     maximum;  /* OPTIONAL */      
                    /* negative if not present */
};
/***** Typedef GeneralSubtree *****/
/** @ingroup header_x509v3
  */
typedef struct GeneralSubtree GeneralSubtree;

/***** Typedef GeneralSubtrees *****/
/** subtree of a hierarchie
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(GeneralSubtree)    GeneralSubtrees;
  
/***** Structure NameConstraints *****/
/** @ingroup header_x509v3
  */
struct NameConstraints{
/**  OPTIONAL  */
   	GeneralSubtrees  *permittedSubtrees;  /* OPTIONAL */
/**  OPTIONAL  */
        GeneralSubtrees  *excludedSubtrees;   /* OPTIONAL */    
};
/***** Typedef NameConstraints *****/
/** @ingroup header_x509v3
  */
typedef struct NameConstraints NameConstraints; 
  
/* characteristics of Extension:
   only certificate extension
   only CA certificates
   critical at the option of the issuer
*/
/***** Typedef Ext_NameConstraints *****/
/** only certificate extension;
  * only CA certificates;
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(NameConstraints)          Ext_NameConstraints;

 
                /**********************/
                /* Policy Constraints */
                /**********************/

/***** Typedef SkipCerts *****/
/** number of certificates to skip
  * @ingroup header_x509v3
  */
typedef int	                       SkipCerts;

/***** Structure PolicyConstraints *****/
/** Policy constraints. 
  * @ingroup header_x509v3
  */
struct PolicyConstraints {
        SkipCerts               requireExplicitPolicy;   /* OPTIONAL */
                                          /* negative if not present */
        SkipCerts               inhibitPolicyMapping;  /* OPTIONAL */
                                        /* negative if not present */
};
/***** Typedef PolicyConstraints *****/
/** @ingroup header_x509v3
  */
typedef struct PolicyConstraints PolicyConstraints;

/* characteristics of Extension:
   only certificate extension
   only CA certificates
   critical at the option of the issuer
*/
/***** Typedef Ext_PolicyConstraints *****/
/** only certificate extension;
  * only CA certificates;
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(PolicyConstraints)         Ext_PolicyConstraints;


                /********************************/
                /* Authority Information Access */
                /********************´***********/
/***** Structure AccessDescription *****/
/** Access description. 
  * @ingroup header_x509v3
  */
struct AccessDescription {
	ObjId	      	* accessMethod;
	GeneralName	* accessLocation;  /* ...Name not ...Names !!! */
};
/***** Typedef AccessDescription *****/
/** @ingroup header_x509v3
  */	
typedef struct AccessDescription AccessDescription;

/***** Typedef AuthInfoAccess *****/
/** @ingroup header_x509v3
  */
typedef SEQUENCE_OF(AccessDescription)    AuthInfoAccess;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
/***** Typedef Ext_AuthInfoAccess *****/
/** @ingroup header_x509v3
  */
typedef EXTENSION(AuthInfoAccess)          Ext_AuthInfoAccess;


/************************/
/* Basic CRL Extensions */
/************************/

/* CRL number */

/***** Typedef CRLNumber *****/
/** %CRL number
  * @ingroup header_x509v3
  */
typedef OctetString CRLNumber;

/* characteristics of Extension:
   only CRL extension
   always non-critical
*/
/***** Typedef Ext_CRLNumber *****/
/** only %CRL extension;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(CRLNumber) Ext_CRLNumber;

/* CRLReason */

/***** Enum CRLReason *****/
/** Different %CRL types depending on the reason for revocation.
  * @ingroup header_x509v3
  */
typedef enum { CRLRunspecified = 0,   /**< <TT>=0</TT> */
	       CRLRkeyCompromise,
	       CRLRcACompromise,
	       CRLRaffiliationChanged,
	       CRLRsuperseded,
	       CRLRcessationOfOperation,
	       CRLRcertificateHold,
	       CRLRremoveFromCRL = 8         /**< <TT>=8</TT> */
} CRLReason;

/* characteristics of Extension:
   only CRL entry extension
   always non-critical
*/
/***** Typedef Ext_CRLReason *****/
/** only %CRL extension;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(CRLReason) Ext_CRLReason;

/* HoldInstruction */

/***** Typedef HoldInstruction *****/
/** @ingroup header_x509v3 */
typedef ObjId HoldInstruction;

/* characteristics of Extension:
   only CRL entry extension
   always non-critical
*/
/***** Typedef Ext_HoldInstruction *****/
/** only %CRL entry extension;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(HoldInstruction)         Ext_HoldInstruction;

/* InvalidityDate */

/***** Typedef InvalidityDate *****/
/** expiration date
  * @ingroup header_x509v3
  */
typedef GeneralTime InvalidityDate;

/* characteristics of Extension:
   only CRL entry extension
   always non-critical
*/
/***** Typedef Ext_InvalidityDate *****/
/** only %CRL  extension;
  * always non-critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(InvalidityDate)         Ext_InvalidityDate;


                /***************************/
                /* CRL Distribution Points */
                /***************************/

/***** Structure DistributionPointName *****/
/** @ingroup header_x509v3
  */
struct DistributionPointName{ /* CHOICE ... how ? */
/** exactly one component must be filled out, the other is NULL */
        GeneralNames	   *fullName; 
/** exactly one component must be filled out, the other is NULL */
        RDName	           *nameRelativeToCRLIssuer; 
        /* exactly one must be filled out, the other is NULL */
};
/***** Typedef DistributionPointName *****/
/** @ingroup header_x509v3
  */
typedef struct DistributionPointName DistributionPointName;

/***** Structure ReasonFlags *****/
/** @ingroup header_x509v3
  */
struct ReasonFlags{
        Boolean		  unused; 
        Boolean           keyCompromise;
        Boolean           cACompromise;  
        Boolean           affiliationChanged; 
        Boolean           superseded;
        Boolean           cessationOfOperation;
        Boolean           certificateHold;
};
/***** Typedef ReasonFlags *****/
/** @ingroup header_x509v3
  */
typedef struct ReasonFlags ReasonFlags;

/***** Structure DistributionPoint *****/
/** @ingroup header_x509v3
  */
struct DistributionPoint{
/**  OPTIONAL  */
        DistributionPointName   *distributionPoint; /* OPTIONAL */
/**  OPTIONAL  */
        ReasonFlags             *reasons;   	    /* OPTIONAL */
/**  OPTIONAL  */
        GeneralNames	  	*cRLIssuer;	    /* OPTIONAL */
};
/***** Typedef DistributionPoint *****/
/** @ingroup header_x509v3
  */
typedef struct DistributionPoint DistributionPoint;

/***** Typedef CRLDistPoints *****/
/** distribution points of %CRLs
  * @ingroup header_x509v3
  */
typedef SEQUENCE_OF(DistributionPoint)    CRLDistPoints;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
/***** Typedef Ext_CRLDistPoints *****/
/** only certificate extension;
  * both CA- and end-entity certificates;
  * critical at the option of the issuer
  * @ingroup header_x509v3
  */
typedef EXTENSION(CRLDistPoints)          Ext_CRLDistPoints;

/*
 *     PSE object containing all trusted policies
 */

/***** Structure policy2name *****/
/** @ingroup header_x509v3
  */
struct policy2name{
/** Disting.\ name of the CA */
        DName              *dname;
/** alternative names of the CA */
        SubjectAltName	   *alt_name;
/** policy used by the CA */
        ObjId		   *policyId;
};
/***** Typedef policy2name *****/
/** @ingroup header_x509v3
  */
typedef struct policy2name policy2name;

/***** Typedef PolicyList *****/
/** @ingroup header_x509v3 */
typedef SEQUENCE_OF(policy2name) PolicyList;



/***********************/
/* more CRL extensions */
/***********************/

/* IssuingDistPoint */

/***** Structure IssuingDistPoint *****/
/** @ingroup header_x509v3
  */
struct IssuingDistPoint {
/**  OPTIONAL  */
    DistributionPointName  * distributionPoint;          /* OPTIONAL */
/**  DEFAULT: FALSE  */
    Boolean                  onlyContainsUserCerts;      /* DEFAULT FALSE */
/**  DEFAULT: FALSE  */
    Boolean                  onlyContainsCACerts;        /* DEFAULT FALSE */
/**  OPTIONAL  */
    ReasonFlags            * onlySomeReasons;            /* OPTIONAL */
/**  DEFAULT: FALSE  */
    Boolean                  indirectCRL;                /* DEFAULT FALSE */
};
/***** Typedef IssuingDistPoint *****/
/** @ingroup header_x509v3
  */
typedef struct IssuingDistPoint IssuingDistPoint;

/* characteristics of Extension:
   only CRL extension
   always critical
*/
/***** Typedef Ext_IssuingDistPoint *****/
/** only %CRL  extension;
  * always critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(IssuingDistPoint)          Ext_IssuingDistPoint;


/* CertificateIssuer */

/***** Typedef CertificateIssuer *****/
/** issuer's general names
  * @ingroup header_x509v3
  */
typedef GeneralNames CertificateIssuer;

/* characteristics of Extension:
   only CRL entry extension
   always critical
*/
/***** Typedef Ext_CertificateIssuer *****/
/** only %CRL entry extension;
  * always critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(CertificateIssuer)          Ext_CertificateIssuer;


/* DeltaCRLIndicator */

/***** Typedef BaseCRLNumber *****/
/** @ingroup header_x509v3 */
typedef CRLNumber BaseCRLNumber;

/* characteristics of Extension:
   only CRL extension
   always critical
*/
/***** Typedef Ext_BaseCRLNumber *****/
/** only %CRL extension;
  * always critical
  * @ingroup header_x509v3
  */
typedef EXTENSION(BaseCRLNumber)          Ext_BaseCRLNumber;


/***** Typedef Ext_OctetString *****/
/** any extension
  * @ingroup header_x509v3
  */
typedef EXTENSION(OctetString)	Ext_OctetString;
#ifdef TeSECUDE
typedef Ext_OctetString 	Ext_TelesecCertificate;
#endif
#ifdef FOR_DOCUMENTATION
/***** Typedef Ext_TelesecCertificate *****/
/** TeSECUDE private extension
  * @ingroup header_x509v3
  */
typedef Ext_OctetString 	Ext_TelesecCertificate;
#endif

 
                /* Non supported Extensions */
/* It's necessary to have all the fields in the ToBeSigned structure;
   nonSupported will prevent a minimal process on non supported fields;
   so it'll be possible to know if a nonSupported Extension is critical or not
*/
 
/***** Structure CertExtensions *****/
/** @ingroup header_x509v3
  */
struct CertExtensions{
 
        /* Key and policy information extension */
/** %Key and policy information */
        Ext_AuthorityKeyId          *authorityKeyId;
/** %Key and policy information */
        Ext_SubjectKeyId            *subjectKeyId;
/** %Key and policy information */
        Ext_KeyUsage	            *keyUsage;
        Ext_ExtKeyUsage	            *extKeyUsage;
/** %Key and policy information */
        Ext_PrivateKeyUsagePeriod   *privateKeyUsagePeriod;
/** %Key and policy information */
        Ext_CertificatePolicies     *certificatePolicies;
/** %Key and policy information */
        Ext_PolicyMappings          *policyMappings;
 
        /* Subject and issuer attributes extensions */
/** Subject and issuer attributes */
        Ext_SubjectAltName          *subjectAltName;
/** Subject and issuer attributes */
        Ext_IssuerAltName           *issuerAltName;
/** Subject and issuer attributes */
        Ext_DirectoryAttributes     *subjectDirectoryAttr;
 
        /* Certification path constraints extensions */
/** Certification path constraints */
        Ext_BasicConstraints        *basicConstraints;
/** Certification path constraints */
        Ext_NameConstraints         *nameConstraints;
/** Certification path constraints */
        Ext_PolicyConstraints       *policyConstraints;
        
        /* CRL distribution points */        
/** %CRL distribution points */
        Ext_CRLDistPoints           *cRLDistributionPoints;
        
        /* Authority Information Access */
        Ext_AuthInfoAccess	    *authorityInfoAccess;

#ifdef TeSECUDE
/** TeSECUDE private extension */
        Ext_TelesecCertificate	    *telesecCertificate;
#endif

/** private extensions */
        SEQUENCE_OF_Extension       *nonSupported;
 
};
/***** Typedef CertExtensions *****/
/** @ingroup header_x509v3
  */
typedef struct CertExtensions CertExtensions;

/***** Structure CRLExtensions *****/
/** @ingroup header_x509v3
  */
struct CRLExtensions{
 
        /* Key and policy information extension */
/** %Key and policy information */
        Ext_AuthorityKeyId          *authorityKeyId;
 
        /* Subject and issuer attributes extensions */
/** issuer attributes */
        Ext_IssuerAltName           *issuerAltName;
 
        /* basic CRL extensions */
/** basic %CRL extensions */
        Ext_CRLNumber               *cRLNumer;

        Ext_IssuingDistPoint        *issuingDistPoint;
        Ext_BaseCRLNumber           *deltaCRLIndicator;

/** private extensions */
        SEQUENCE_OF_Extension       *nonSupported;
 
};
/***** Typedef CRLExtensions *****/
/** @ingroup header_x509v3
  */
typedef struct CRLExtensions CRLExtensions;

/***** Structure CRLEntryExtensions *****/
/** @ingroup header_x509v3
  */
struct CRLEntryExtensions{
 
        /* basic CRL extensions */
/** reason for revocation */
        Ext_CRLReason               *reasonCode;
        Ext_HoldInstruction         *holdInstructionCode;
/** expiration date */
        Ext_InvalidityDate          *invalidityDate;

/** issuer of revoked certificate */
        Ext_CertificateIssuer       *certificateIssuer;
    
/** private extensions */
        SEQUENCE_OF_Extension       *nonSupported;
 
};
/***** Typedef CRLEntryExtensions *****/
/** @ingroup header_x509v3
  */
typedef struct CRLEntryExtensions CRLEntryExtensions;

#define NONSTANDARD_EXTENSION 10000

/***** Enum Extension_number *****/
/** Each extension is associated with a number.
  * @ingroup header_x509v3
  */
typedef enum { UnknownExtension_n = -1,  /**< <TT>=-1</TT> */
	       DirectoryAttributes_n = 9,       /**< <TT>=9</TT> */
	       SubjectKeyId_n = 14,             /**< <TT>=14</TT> */
	       KeyUsage_n,
	       PrivateKeyUsagePeriod_n,
	       SubjectAltName_n,
	       IssuerAltName_n,
	       BasicConstraints_n,
	       CRLNumber_n,
	       CRLReason_n,
	       HoldInstruction_n = 23,          /**< <TT>=23</TT> */
	       InvalidityDate_n,
	       BaseCRLNumber_n = 27,            /**< <TT>=27</TT> */
	       IssuingDistPoint_n,
	       CertificateIssuer_n,
	       NameConstraints_n,
	       CRLDistPoints_n,
	       CertificatePolicies_n,
	       PolicyMappings_n,
	       AuthorityKeyId_n = 35,           /**< <TT>=35</TT> */
	       PolicyConstraints_n,
	       ExtKeyUsage_n
#ifdef TeSECUDE
	       ,
	       TelesecCertificate_n = NONSTANDARD_EXTENSION + 0
#endif
	       ,
        /** <TT>= NONSTANDARD_EXTENSION + 1 */
	       AuthInfoAccess_n = NONSTANDARD_EXTENSION + 1
} Extension_number;


/* Here comes some structures for nonSupported extensions */

/* QCStatement */
typedef struct 
{
    /* choice of (use numeric if alphabetic == NULL */
    char *alphabetic;
    int numeric;
} Iso4217CurrencyCode;

typedef struct 
{
    Iso4217CurrencyCode *currency;
    int amount;
    int exponent;
} MonetaryValue;

typedef struct 
{
    ObjId *semanticsIdentifier; /* optional */
    GeneralNames *nameRegistrationAuthorities; /* optional */
} SemanticsInformation;

typedef struct 
{
    ObjId *statementId; 
    OctetString *statementInfo; /* DERcode, optional */
} QSStatement;

typedef SEQUENCE_OF(QSStatement) QCStatements;





#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* X509V3_H_ */

