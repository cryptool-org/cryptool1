/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#ifndef X509V3_H_
#define X509V3_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    /* used for GeneralNames(otherName), but "useful" ASN.1 type in general! */
typedef struct TYPE_IDENTIFIER {
    ObjId	*type_id;
    OctetString	*value; /* contains DER code */
} TYPE_IDENTIFIER;


typedef ObjId   ExtnId;

#if defined MACRO_SEP_LIKE_STDC
#define EXTENSION(t) struct Ext_##t {       \
        Boolean         critical;                   \
        t               *extnValue;                 \
        int         seqnum; \
}
#else
#define EXTENSION(t) struct Ext_/**/t {     \
        Boolean         critical;                   \
        t               *extnValue;                 \
        int         seqnum; \
}
#endif

typedef EXTENSION(void) Ext_void;

typedef struct v3Extension {
    ExtnId       *extnId;
    Boolean       critical;
    OctetString  *extnDERcode;
    int		  mmode; /* for internal use only, not encoded */
    int         seqnum; /* to save the sequence of the extensions */
} v3Extension;

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

typedef enum { GNany = -1,
	       GNotherName = 0, 
	       GNrfc822Name,
	       GNdNSName,
	       GNx400Address,
	       GNdirectoryName,
	       GNediPartyName,
	       GNuRI,
	       GNiPAddress,
	       GNregisteredID,
	       GNUPPERLIMIT,
	       GNunknown = 31
} GeneralName_number;

extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX GeneralName_descr[];

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

typedef OctetString GeneralName;

typedef SEQUENCE_OF(GeneralName) GeneralNames;


        /********************************************************/
        /*              KEY and POLICY Information              */
        /********************************************************/
 
                /****************************/
                /* Authority Key Identifier */
                /****************************/


typedef OctetString     KeyIdentifier;
typedef OctetString     CertificateSerialNumber;   /* Long */
  
typedef struct AuthorityKeyId{
        KeyIdentifier           *authorityKeyIdentifier;    /* OPTIONAL */
        GeneralNames            *authorityCertIssuer;       /* OPTIONAL */
        CertificateSerialNumber *authorityCertSerialNumber; /* OPTIONAL */
}AuthorityKeyId;

/* characteristics of Extension:
   certificate and CRL extension
   both CA- and end-entity certificates
   always non-critical
*/
typedef EXTENSION(AuthorityKeyId)       Ext_AuthorityKeyId;
 

                /***************************/
                /* Subject Key Identifier: */
                /***************************/

typedef KeyIdentifier SubjectKeyId;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
typedef EXTENSION(SubjectKeyId)       Ext_SubjectKeyId;

		/**************/
                /* Key Usage: */
                /**************/
                
typedef enum { digitalSignature = 0,
               nonRepudiation,
               keyEncipherment,
               dataEncipherment,
               keyAgreement,
               keyCertSign,
               cRLSign,
	       encipherOnly,
	       decipherOnly
} KeyUsageTypes; 

typedef struct KeyUsage {
        Boolean         digitalSignature;
        Boolean         nonRepudiation;
        Boolean         keyEncipherment;
        Boolean         dataEncipherment;
        Boolean         keyAgreement;
        Boolean         keyCertSign;
        Boolean         cRLSign;
        Boolean         encipherOnly;
        Boolean         decipherOnly;
}KeyUsage;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates (*Sign bits CA only)
   critical at the option of the issuer
*/
typedef EXTENSION(KeyUsage)       Ext_KeyUsage;

		/**************/
                /* Extended Key Usage: */
                /**************/
typedef ObjId KeyPurposeId;
typedef SEQUENCE_OF(KeyPurposeId) ExtKeyUsage;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates 
   critical at the option of the issuer
*/
typedef EXTENSION(ExtKeyUsage)       Ext_ExtKeyUsage;
                
                /*****************************/
                /* Private Key Usage Period: */
                /*****************************/

typedef struct PrivateKeyUsagePeriod{
        GeneralTime           *notBefore;    /* OPTIONAL */
        GeneralTime           *notAfter;     /* OPTIONAL */
}PrivateKeyUsagePeriod;
 
/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
typedef EXTENSION(PrivateKeyUsagePeriod)       Ext_PrivateKeyUsagePeriod;
 	

 
                /************************/
                /* Certificate Policies */
                /************************/
 
/* HRS 18.10.99 */

enum DisplayText_Types { DTT_visibleString = 26, DTT_ia5String = 22, DTT_bmpString = 30, DTT_utf8String = 12 };

typedef struct DisplayText {
	int choice;
	union {
	   char *visibleString;
	   char *ia5String;
	   OctetString *bmpString;
	   char *utf8String;
	} un;
} DisplayText;

typedef SEQUENCE_OF(Integer) SEQUENCE_OF_Integer;

typedef struct NoticeReference {
	DisplayText *organization;
	SEQUENCE_OF_Integer *noticeNumbers;
} NoticeReference;

typedef struct UserNotice {
	NoticeReference *noticeRef; /* OPTIONAL */
	DisplayText *explicitText; /* OPTIONAL */
} UserNotice;


typedef struct PolicyQualifierInfo {
    ObjId       * qualifierId;
    OctetString * qualifierDERcode; /* OPTIONAL */
	int           seqnum; /* internal: ordering of PQIs (is not encoded) */
    int	          mmode; /* for internal use only, not encoded/copied */
} PolicyQualifierInfo;

typedef SEQUENCE_OF(PolicyQualifierInfo) PolicyQualifierInfos;

typedef ObjId CertPolicyId;

typedef struct PolicyInformation {
    CertPolicyId           * policyIdentifier;
    PolicyQualifierInfos   * policyQualifiers; /* OPTIONAL */

	/* changed 28.10.99 HRS:
	 * the standard PKIX qualifiers CPS and UserNotice are stored
	 * separately from the above policyQualifiers... */
	char *pkix_cps; /* "OPTIONAL" */
	UserNotice *pkix_unotice; /* "OPTIONAL" */
	int pkix_cps_seqnum, pkix_unotice_seqnum; /* internal: ordering... */
} PolicyInformation;

typedef SEQUENCE_OF(PolicyInformation) CertificatePolicies;
 
/* for use in af.h ??? */

typedef SET_OF(PolicyQualifierInfo)	CertQualifierSet;


/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
typedef EXTENSION(CertificatePolicies)    Ext_CertificatePolicies;
 
                /********************/
                /* Policy Mappings  */
                /********************/

typedef struct MappingElement {
        CertPolicyId            * issuerDomainPolicy;
        CertPolicyId            * subjectDomainPolicy;
} MappingElement;
 
typedef SEQUENCE_OF(MappingElement)     PolicyMappings;
 
/* characteristics of Extension:
   only certificate extension
   only CA certificates
   always non-critical
*/
typedef EXTENSION(PolicyMappings)         Ext_PolicyMappings;
  
 
        /********************************************************/
        /*              SUBJECT and ISSUER attributes           */
        /********************************************************/


 
                /****************************/
                /* Subject alternative name */
                /****************************/
  
typedef GeneralNames SubjectAltName;
 
/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
typedef EXTENSION(SubjectAltName)             Ext_SubjectAltName;

 
                /****************************/
                /* Issuer alternative name */
                /****************************/
 
typedef GeneralNames IssuerAltName;

/* characteristics of Extension:
   both certificate and CRL extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
typedef EXTENSION(IssuerAltName)             Ext_IssuerAltName;
 
 
                /********************************/
                /* Subject Directory Attributes */
                /********************************/
 
typedef SEQUENCE_OF(Attr)  DirectoryAttributes;
 
/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
typedef EXTENSION(DirectoryAttributes)     Ext_DirectoryAttributes;
 
 
        /********************************************************/
        /*          CERTIFICATION PATH constraints              */
        /********************************************************/
 
                /*********************/
                /* Basic Constraints */
                /*********************/
  
typedef struct BasicConstraints{
	Boolean               cA;		      /* DEFAULT FALSE */
        int                   pathLenConstraint;      /* OPTIONAL */
                                       /* negative if not present */
}BasicConstraints;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
typedef EXTENSION(BasicConstraints)       Ext_BasicConstraints;
 
  
                /********************/
                /* Name Constraints */
                /********************/

typedef int    BaseDistance;
 
typedef struct GeneralSubtree{
        GeneralName     *base;       /* ...Name not ...Names !!! */
        BaseDistance     minimum;  /* DEFAULT 0 */ 
        BaseDistance     maximum;  /* OPTIONAL */      
                    /* negative if not present */
}GeneralSubtree;

typedef SEQUENCE_OF(GeneralSubtree)    GeneralSubtrees;
  
typedef struct NameConstraints{
   	GeneralSubtrees  *permittedSubtrees;  /* OPTIONAL */
        GeneralSubtrees  *excludedSubtrees;   /* OPTIONAL */    
}NameConstraints;
  
/* characteristics of Extension:
   only certificate extension
   only CA certificates
   critical at the option of the issuer
*/
typedef EXTENSION(NameConstraints)          Ext_NameConstraints;

 
                /**********************/
                /* Policy Constraints */
                /**********************/

typedef int	                       SkipCerts;

typedef struct PolicyConstraint {
        SkipCerts               requireExplicitPolicy;   /* OPTIONAL */
                                          /* negative if not present */
        SkipCerts               inhibitPolicyMapping;  /* OPTIONAL */
                                        /* negative if not present */
} PolicyConstraint;

typedef SEQUENCE_OF(PolicyConstraint) PolicyConstraints;

/* characteristics of Extension:
   only certificate extension
   only CA certificates
   critical at the option of the issuer
*/
typedef EXTENSION(PolicyConstraints)         Ext_PolicyConstraints;


                /********************************/
                /* Authority Information Access */
                /********************´***********/
typedef struct AccessDescription {
	ObjId	      	* accessMethod;
	GeneralName	* accessLocation;  /* ...Name not ...Names !!! */
}AccessDescription;	

typedef SEQUENCE_OF(AccessDescription)    AuthInfoAccess;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   always non-critical
*/
typedef EXTENSION(AuthInfoAccess)          Ext_AuthInfoAccess;


/************************/
/* Basic CRL Extensions */
/************************/

/* CRL number */

typedef OctetString CRLNumber;

/* characteristics of Extension:
   only CRL extension
   always non-critical
*/
typedef EXTENSION(CRLNumber) Ext_CRLNumber;

/* CRLReason */

typedef enum { CRLRunspecified = 0,
	       CRLRkeyCompromise,
	       CRLRcACompromise,
	       CRLRaffiliationChanged,
	       CRLRsuperseded,
	       CRLRcessationOfOperation,
	       CRLRcertificateHold,
	       CRLRremoveFromCRL = 8
} CRLReason;

/* characteristics of Extension:
   only CRL entry extension
   always non-critical
*/
typedef EXTENSION(CRLReason) Ext_CRLReason;

/* HoldInstruction */

typedef ObjId HoldInstruction;

/* characteristics of Extension:
   only CRL entry extension
   always non-critical
*/
typedef EXTENSION(HoldInstruction)         Ext_HoldInstruction;

/* InvalidityDate */

typedef GeneralTime InvalidityDate;

/* characteristics of Extension:
   only CRL entry extension
   always non-critical
*/
typedef EXTENSION(InvalidityDate)         Ext_InvalidityDate;


                /***************************/
                /* CRL Distribution Points */
                /***************************/

typedef struct DistributionPointName{ /* CHOICE ... how ? */
        GeneralNames	   *fullName; 
        RDName	           *nameRelativeToCRLIssuer; 
        /* exactly one must be filled out, the other is NULL */
}DistributionPointName;

typedef struct ReasonFlags{
        Boolean		  unused; 
        Boolean           keyCompromise;
        Boolean           cACompromise;  
        Boolean           affiliationChanged; 
        Boolean           superseded;
        Boolean           cessationOfOperation;
        Boolean           certificateHold;
}ReasonFlags;

typedef struct DistributionPoint{
        DistributionPointName   *distributionPoint; /* OPTIONAL */
        ReasonFlags             *reasons;   	    /* OPTIONAL */
        GeneralNames	  	*cRLIssuer;	    /* OPTIONAL */
}DistributionPoint;

typedef SEQUENCE_OF(DistributionPoint)    CRLDistPoints;

/* characteristics of Extension:
   only certificate extension
   both CA- and end-entity certificates
   critical at the option of the issuer
*/
typedef EXTENSION(CRLDistPoints)          Ext_CRLDistPoints;

/*
 *     PSE object containing all trusted policies
 */

typedef struct policy2name{
        DName              *dname;
        SubjectAltName	   *alt_name;
        ObjId		   *policyId;
}policy2name;

typedef SEQUENCE_OF(policy2name) PolicyList;



/***********************/
/* more CRL extensions */
/***********************/

/* IssuingDistPoint */

typedef struct IssuingDistPoint {
    DistributionPointName  * distributionPoint;          /* OPTIONAL */
    Boolean                  onlyContainsUserCerts;      /* DEFAULT FALSE */
    Boolean                  onlyContainsCACerts;        /* DEFAULT FALSE */
    ReasonFlags            * onlySomeReasons;            /* OPTIONAL */
    Boolean                  indirectCRL;                /* DEFAULT FALSE */
} IssuingDistPoint;

/* characteristics of Extension:
   only CRL extension
   always critical
*/
typedef EXTENSION(IssuingDistPoint)          Ext_IssuingDistPoint;


/* CertificateIssuer */

typedef GeneralNames CertificateIssuer;

/* characteristics of Extension:
   only CRL entry extension
   always critical
*/
typedef EXTENSION(CertificateIssuer)          Ext_CertificateIssuer;


/* DeltaCRLIndicator */

typedef CRLNumber BaseCRLNumber;

/* characteristics of Extension:
   only CRL extension
   always critical
*/
typedef EXTENSION(BaseCRLNumber)          Ext_BaseCRLNumber;


typedef EXTENSION(OctetString)	Ext_OctetString;
#ifdef TeSECUDE
typedef Ext_OctetString 	Ext_TelesecCertificate;
#endif

 
                /* Non supported Extensions */
/* It's necessary to have all the fields in the ToBeSigned structure;
   nonSupported will prevent a minimal process on non supported fields;
   so it'll be possible to know if a nonSupported Extension is critical or not
*/
 
typedef struct CertExtensions{
 
        /* Key and policy information extension */
        Ext_AuthorityKeyId          *authorityKeyId;
        Ext_SubjectKeyId            *subjectKeyId;
        Ext_KeyUsage	            *keyUsage;
        Ext_ExtKeyUsage	            *extKeyUsage;
        Ext_PrivateKeyUsagePeriod   *privateKeyUsagePeriod;
        Ext_CertificatePolicies     *certificatePolicies;
        Ext_PolicyMappings          *policyMappings;
 
        /* Subject and issuer attributes extensions */
        Ext_SubjectAltName          *subjectAltName;
        Ext_IssuerAltName           *issuerAltName;
        Ext_DirectoryAttributes     *subjectDirectoryAttr;
 
        /* Certification path constraints extensions */
        Ext_BasicConstraints        *basicConstraints;
        Ext_NameConstraints         *nameConstraints;
        Ext_PolicyConstraints       *policyConstraints;
        
        /* CRL distribution points */        
        Ext_CRLDistPoints           *cRLDistributionPoints;
        
        /* Authority Information Access */
        Ext_AuthInfoAccess	    *authorityInfoAccess;

#ifdef TeSECUDE
        Ext_TelesecCertificate	    *telesecCertificate;
#endif

        SEQUENCE_OF_Extension       *nonSupported;
 
} CertExtensions;

typedef struct CRLExtensions{
 
        /* Key and policy information extension */
        Ext_AuthorityKeyId          *authorityKeyId;
 
        /* Subject and issuer attributes extensions */
        Ext_IssuerAltName           *issuerAltName;
 
        /* basic CRL extensions */
        Ext_CRLNumber               *cRLNumer;

        Ext_IssuingDistPoint        *issuingDistPoint;
        Ext_BaseCRLNumber           *deltaCRLIndicator;

        SEQUENCE_OF_Extension       *nonSupported;
 
} CRLExtensions;

typedef struct CRLEntryExtensions{
 
        /* basic CRL extensions */
        Ext_CRLReason               *reasonCode;
        Ext_HoldInstruction         *holdInstructionCode;
        Ext_InvalidityDate          *invalidityDate;

        Ext_CertificateIssuer       *certificateIssuer;
    
        SEQUENCE_OF_Extension       *nonSupported;
 
} CRLEntryExtensions;

#define NONSTANDARD_EXTENSION 10000

typedef enum { UnknownExtension_n = -1,
	       DirectoryAttributes_n = 9,
	       SubjectKeyId_n = 14,
	       KeyUsage_n,
	       PrivateKeyUsagePeriod_n,
	       SubjectAltName_n,
	       IssuerAltName_n,
	       BasicConstraints_n,
	       CRLNumber_n,
	       CRLReason_n,
	       HoldInstruction_n = 23,
	       InvalidityDate_n,
	       BaseCRLNumber_n = 27,
	       IssuingDistPoint_n,
	       CertificateIssuer_n,
	       NameConstraints_n,
	       CRLDistPoints_n,
	       CertificatePolicies_n,
	       PolicyMappings_n,
	       AuthorityKeyId_n = 35,
	       PolicyConstraints_n,
	       ExtKeyUsage_n
#ifdef TeSECUDE
	       ,
	       TelesecCertificate_n = NONSTANDARD_EXTENSION + 0
#endif
	       ,
	       AuthInfoAccess_n = NONSTANDARD_EXTENSION + 1
} Extension_number;

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* X509V3_H_ */

