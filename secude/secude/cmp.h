/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/cmp.h
 *###
 *### global functions:
 *###
 *###*****************************************//* cmp.h */
/* external */



/*-----------------------------------------------------------------------*/
/*  INCLUDE FILE  cmp.h  (Certificate Management Protocol)               */
/*																	     */
/*-----------------------------------------------------------------------*/

/** 
  * CMP API SECUDE SDK
  * 
  * this api implements the asn.1 coding and decoding for CMP protocol
  * how it is described in the rfc 2510 of the ietf
  * 
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 

#ifndef _CMP_H_
#define _CMP_H_

/*
 * typedefs
 */

typedef struct CMP_PKIMessage CMP_PKIMessage;
typedef struct CMP_PKIHeader CMP_PKIHeader;
typedef struct CMP_PKICertTempl CMP_PKICertTempl;
typedef struct CMP_PKICertReqMsg CMP_PKICertReqMsg;
typedef struct CMP_PKICertReq CMP_PKICertReq;
typedef struct CMP_PKIBody_CertRequest CMP_PKIBody_CertRequest;
typedef struct CMP_PKIBody_CertResponse CMP_PKIBody_CertResponse;
typedef struct CMP_PKI_PKMACValue CMP_PKI_PKMACValue;
typedef struct CMP_PKIPOPOPrivKey CMP_PKIPOPOPrivKey;
typedef struct CMP_PKIPOPOSigningKey CMP_PKIPOPOSigningKey;
typedef struct CMP_PKIPOPOSigningKeyInput CMP_PKIPOPOSigningKeyInput;
typedef struct CMP_SeqofInfoType CMP_SeqofInfoType;
typedef struct SeqCert SeqCert;
typedef struct Extensions Extensions;
typedef struct Extension Extension;
typedef struct CMP_ProofOP CMP_ProofOP;
typedef struct CMP_PKIBody CMP_PKIBody;
typedef struct CMP_SubPubKeyInfo CMP_SubPubKeyInfo;
typedef struct CMP_PKICertRespMsg CMP_PKICertRespMsg;
typedef struct CMP_PKIStatusInfo CMP_PKIStatusInfo;
typedef struct CMP_PKICertKeyPair CMP_PKICertKeyPair;
typedef struct EncryptedValue EncryptedValue;
typedef struct CMP_PKIPubInfo CMP_PKIPubInfo;
typedef struct SeqPubInfo SeqPubInfo;
typedef struct CMP_PKISinglePubInfo CMP_PKISinglePubInfo;
typedef struct CMP_PKICertOrEncCert CMP_PKICertOrEncCert;
typedef struct SeqofRevDetails SeqofRevDetails;
typedef struct CMP_PKIBody_RevReq CMP_PKIBody_RevReq;
typedef struct CMP_PKIRevDetails CMP_PKIRevDetails;
typedef struct SeqStatusInfo SeqStatusInfo;
typedef struct CMP_PKIBody_RevResp CMP_PKIBody_RevResp;
typedef struct CMP_PKICertId CMP_PKICertId;
typedef struct SeqCRL SeqCRL;
typedef struct SeqCertId SeqCertId;
typedef struct SeqValueAttr SeqValueAttr;
typedef struct SeqCertRespMsg SeqCertRespMsg;
typedef struct CMP_PKIBody_GenMsgReq CMP_PKIBody_GenMsgReq;
typedef struct CMP_PKIBody_GenMsgResp CMP_PKIBody_GenMsgResp;
typedef struct CMP_PKIBody_ErrorMessage CMP_PKIBody_ErrorMessage;
typedef struct CMP_PKIBody_GeneralMessage CMP_PKIBody_GeneralMessage;
typedef struct CMP_PKIValuePair CMP_PKIValuePair;
typedef struct SeqValuePair SeqValuePair;

/*
 * structures
 */

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * InfoTypeAndValue ::= SEQUENCE {
  *        infoType           OBJECT IDENTIFIER,
  *        infoValue          ANY DEFINED BY infoType OPTIONAL
  * }
  * </pre>
  * 
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_SeqofInfoType {
   /** this infoTypAndValue */
	struct AlgId						* element;
   /** pointer to the next one */
	struct CMP_SeqofInfoType			* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * PKIHeader ::= SEQUENCE {
  *    pvno                INTEGER     { ietf-version2 (1) },
  *    sender              GeneralName,
  *    recipient           GeneralName,
  *    messageTime     [0] GeneralizedTime         OPTIONAL,
  *    protectionAlg   [1] AlgorithmIdentifier     OPTIONAL,
  *    senderKID       [2] KeyIdentifier           OPTIONAL,
  *    recipKID        [3] KeyIdentifier           OPTIONAL,
  *    transactionID   [4] OCTET STRING            OPTIONAL,
  *    senderNonce     [5] OCTET STRING            OPTIONAL,
  *    recipNonce      [6] OCTET STRING            OPTIONAL,
  *    freeText        [7] PKIFreeText             OPTIONAL,
  *    generalInfo     [8] SEQUENCE SIZE(1..MAX) OF
  *                           InfoTypeAndValue     OPTIONAL
  * }
  * </pre>
  * 
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIHeader {
   /** the cmp version number */
	int							  m_nVersion;
   /** the sender dname */
	GeneralName					* m_pSender;
   /** the recipient dname */
	GeneralName					* m_pRecipient;
	/*DName						* m_pSender;
	DName						* m_pRecipient;*/
   /** the timestamp when the message was sent */
	GeneralTime					* m_pMessageTime;	/*optional*/
   /** the protection algorithm */
	AlgId						* m_pProtectionAlg;	/*optional*/
   /** the sender key identifier */
	OctetString					* m_pSenderKID;		/*optional*/
   /** the recipient key identifier */
	OctetString					* m_pRecipKID;		/*optional*/
   /** a identifying transaction code */
	OctetString					* m_pTransactionID;	/*optional*/
   /** a random sender number */
	OctetString					* m_pSenderNonce;	/*optional*/
   /** a random recipient number */
	OctetString					* m_pRecipNonce;	/*optional*/
   /** a free text */
	char						* m_szFreeText;		/*optional*/
   /** additional place for additional infomation */
	struct CMP_SeqofInfoType	* m_pGeneralInfo;	/*optional*/
};


/*----------------------------- PKI Bodys ----------------------------*/

/* ---------------------- PKI Body Certification Request ----------------------------- */

/** 
  * an enum to specify the type of proof of possession
  * 
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
enum CMP_PKIProofofPossType {
	CMP_PKI_POP_None = 0,
	CMP_PKI_POP_Verified,
	CMP_PKI_POP_Signature,
	CMP_PKI_POP_KeyEncipherment,
	CMP_PKI_POP_KeyAgreement
};

/** 
  * an enum to specify the proof of possession input signing key type
  * 
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
enum CMP_PKIPOPOSigningKeyInputType {
   /** general name sender */
	CMP_PKIPOPOSKTSender = 0,
   /** public key mac value */
	CMP_PKIPOPOSKTPublicKeyMAC,
   /** public key info */
	CMP_PKIPOPOSKTPublicKey
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * POPOSigningKeyInput ::= SEQUENCE {
  *    authInfo            CHOICE {
  *           sender              [0] GeneralName,
  *           publicKeyMAC        PKMACValue ,
  *                            PKMACValue ::= SEQUENCE {
  *                                   algId  AlgorithmIdentifier,
  *                                   value  BIT STRING
  *                            }
  *    }
  *    publicKey           SubjectPublicKeyInfo
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIPOPOSigningKeyInput {
   /** witch type of the choice should be used */
	enum CMP_PKIPOPOSigningKeyInputType		  m_cnPKIPOPOSKIType;
   /** pointer to the selected type */
	void									* m_pAuthInfo;
	/* values for m_pAuthInfo:
	DName						* m_pSender;			Choice [0]
	KeyInfo						* m_pPublicKeyMAC;		Choice 1
	KeyInfo						* m_pPublicKeyInfo;     Choice 2*/
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * POPOSigningKey ::= SEQUENCE {
  *        poposkInput         [0] POPOSigningKeyInput OPTIONAL,
  *        algorithmIdentifier     AlgorithmIdentifier,
  *        signature               BIT STRING
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIPOPOSigningKey { /* POP Type [1] */
   /** the substructure signing key input */
	struct CMP_PKIPOPOSigningKeyInput		* m_pPOPOSSKInput;		/*optional*/
   /** algorithm of siging */
	AlgId									* m_pAlgId;				
   /** the signature */
	BitString								* m_pSignature;
};

/** 
  * an enum to specify the proof of possession private key type  
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
enum CMP_PKIPOPPrivKeyType {
   /** proof of private key in message */
	CMP_PKI_POPPrivKeyThisMessage = 0,
   /** proof of private key over encrypted certificate or the response */
	CMP_PKI_POPPrivKeySubMessage,
   /** proof of private key over DH MAC */
	CMP_PKI_POPPrivKeyDHMAC
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * POPOPrivKey ::= CHOICE {
  *      thisMessage       [0] BIT STRING,
  *      subsequentMessage [1] SubsequentMessage,
  *                subsequentMessage ::= INTEGER {
  *                         encrCert (0),
  *                         challengeResp (1)
  *                }									       
  *      dhMAC             [2] BIT STRING
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIPOPOPrivKey { /* POP Type [2] and [3] */
   /** witch choice type was selected */
	enum CMP_PKIPOPPrivKeyType	  m_cnPOPPKType;
   /** the choice type substructure */
	void						* m_pValue;
    /* Values for m_pValue: */
	/*  BitString * m_pThisMessage;		   */ /*Choice [0]*/
	/*  int		  * m_pnSubsequentMessage; */ /*Choice [1]  Values (0-encrypt Cert,1-challange Resp.)*/
	/*  BitString * m_pDhMAC;		   */ /*Choice [2] for Key agreement only*/
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * Extension  ::=  SEQUENCE  {
  *       extnID      OBJECT IDENTIFIER,
  *       critical    BOOLEAN DEFAULT FALSE,
  *       extnValue   OCTET STRING
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct Extension {
	ObjId			* m_pExtnID;
	Boolean			  m_bCritical;
	OctetString		* m_pExtnValue;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct Extensions {
	struct Extension		* element;
	struct Extensions		* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * certTemplate  CertTemplate,  -- Selected fields of cert to be issued
  *         certTemplate ::= SEQUENCE {
  *                    version      [0] Version               OPTIONAL,
  *                    serialNumber [1] INTEGER               OPTIONAL,
  *                    signingAlg   [2] AlgorithmIdentifier   OPTIONAL,
  *                    issuer       [3] Name                  OPTIONAL,
  *                    validity     [4] OptionalValidity      OPTIONAL,
  *                          OptionalValidity ::= SEQUENCE {
  *                                           notBefore  [0] Time OPTIONAL,
  *                                           notAfter   [1] Time OPTIONAL
  *                          }
  *                    subject      [5] Name                  OPTIONAL,
  *                    publicKey    [6] SubjectPublicKeyInfo  OPTIONAL,
  *                          SubjectPublicKeyInfo  ::=  SEQUENCE  {
  *                                           algorithm            AlgorithmIdentifier,
  *                                           subjectPublicKey     BIT STRING
  *                          }
  *                    issuerUID    [7] UniqueIdentifier      OPTIONAL,
  *                          UniqueIdentifier  ::=  BIT STRING
  *                    subjectUID   [8] UniqueIdentifier      OPTIONAL,
  *                          UniqueIdentifier  ::=  BIT STRING
  *                    extensions   [9] Extensions            OPTIONAL
  *                          Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension
  *                                  Extension  ::=  SEQUENCE  {
  *                                                extnID      OBJECT IDENTIFIER,
  *                                                critical    BOOLEAN DEFAULT FALSE,
  *                                                extnValue   OCTET STRING
  *                                  }
  *         }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKICertTempl {
   /** the version of the certificate */
	int						   m_nVersion;					/* Tag [0] */ /* Values 0,1,2 */ /*optional*/
   /** a unique serial number */
	OctetString				*  m_pSerialNumber;				/* Tag [1] */ /*optional*/
   /** the algorith of the key */
	AlgId					*  m_pAlgId;					/* Tag [2] */ /*optional*/
   /** the issuer */
	DName					*  m_pIssuer;					/* Tag [3] */ /*optional*/
   /** the begin of the certificate period */
	PrivateKeyUsagePeriod	*  m_pOptValidity;				/* Tag [4] */ /*optional*/
   /** the subject */
	DName					*  m_pSubject;					/* Tag [5] */ /*optional*/
   /** the public key */	
   KeyInfo					*  m_pSubjectPublicKeyInfo;		/* Tag [6] */ /*optional*/
   /** an unique id */
	BitString				*  m_pIssuerUID;				/* Tag [7] */ /*optional*/
   /** an unique id */
	BitString				*  m_pSubjectUID;				/* Tag [8] */ /*optional*/
   /** the extensions of the certificate */
	struct Extensions		*  m_pExtensions;				/* Tag [9] */ /*optional*/
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertRequest ::= SEQUENCE {
  *            certReqId     INTEGER,          -- ID for matching request and reply
  *            certTemplate  CertTemplate,  -- Selected fields of cert to be issued
  *            controls      Controls OPTIONAL -- Attributes affecting issuance
  *                     Controls  ::= SEQUENCE SIZE(1..MAX) OF AttributeTypeAndValue
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKICertReq {
	long						  m_nCertReqId;
	struct CMP_PKICertTempl		* m_pCertTempl;
	struct CMP_SeqofInfoType	* m_pControls;			/*optional*/
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * POPOPrivKey ::= CHOICE {
  *      thisMessage       [0] BIT STRING,
  *      subsequentMessage [1] SubsequentMessage,
  *                subsequentMessage ::= INTEGER {
  *                         encrCert (0),
  *                         challengeResp (1)
  *                }									       
  *      dhMAC             [2] BIT STRING
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_ProofOP {
   /** type of proof of possession */
	enum CMP_PKIProofofPossType		   m_cnPOPType;		/* Type of Proof of Possession */
   /** pointer to the data structure */
	void							*  m_pProofofPoss;	/* Proof of Possession */  /*optional*/
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * SEQUENCE SIZE(1..MAX) of AttributeTypeAndValue OPTIONAL
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqValueAttr {
   /** the structure of AttributeTypeAndValue */
	AttrValueAssertion		* element;
   /** pointer to the next structure */
	SeqValueAttr			* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertReqMsg ::= SEQUENCE {
  *               certReq   CertRequest,
  *               pop       ProofOfPossession  OPTIONAL,
  *               regInfo   SEQUENCE SIZE(1..MAX) of AttributeTypeAndValue OPTIONAL
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKICertReqMsg {
   /** the request structure */
	struct CMP_PKICertReq			*  m_pCertReq;		/* Certification Request information */
   /** the structure for proof of possession data */
	struct CMP_ProofOP				*  m_pProofofPoss;	/* Proof of Possession */  /*optional*/
   /** a data structure for additional data */
	CMP_SeqofInfoType				*  m_pRegInfo;		/* Additional infos over the request*/ /*optional*/

	/* old */
	/*struct CMP_SeqofInfoType		*  m_pRegInfo;	*/ /* Additional infos over the request*/ /*optional*/
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertReqMessages ::= SEQUENCE SIZE (1..MAX) OF CertReqMsg
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIBody_CertRequest {
   /** the actual certificate request */
	struct CMP_PKICertReqMsg		* element;
   /** the next one */
	struct CMP_PKIBody_CertRequest	* next;
};

/* ---------------------- PKI Body Certification Response ----------------------------- */

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * PKIStatusInfo ::= SEQUENCE {
  *              status        PKIStatus,
  *                    PKIStatus ::= INTEGER {
  *                          granted                (0),
  *                          grantedWithMods        (1),
  *                          rejection              (2),
  *                          waiting                (3),
  *                          revocationWarning      (4),
  *                          revocationNotification (5),
  *                          keyUpdateWarning       (6)
  *                    }						         
  *              statusString  PKIFreeText     OPTIONAL,
  *                    PKIFreeText ::= SEQUENCE SIZE (1..MAX) OF UTF8String
  *              failInfo      PKIFailureInfo  OPTIONAL
  *                    PKIFailureInfo ::= BIT STRING {
  *                          badAlg           (0),
  *                          badMessageCheck  (1),
  *                          badRequest       (2),
  *                          badTime          (3),
  *                          badCertId        (4),
  *                          badDataFormat    (5),
  *                          wrongAuthority   (6),
  *                          incorrectData    (7),
  *                          missingTimeStamp (8),
  *                          badPOP           (9)
  *                    }								         
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIStatusInfo {
   /** the status value */
	int					  m_nStatus;			/* Status of the request */
   /** a free status text */
	char				* m_szStatusString;		/* optional Freetext */
   /** a special coding about the failure reason; values see above */
	BitString			* m_pFailInfo;			/* optional Failure Info */
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * status       SEQUENCE SIZE (1..MAX) OF PKIStatusInfo
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqStatusInfo {
   /** the actual status info struture */
	CMP_PKIStatusInfo		* element;
   /** the next one */
	SeqStatusInfo			* next;
};

/** 
  * an enum type for publishing or not publishing
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
enum PKIPIAction {
	dontPublish = 0,
	pleasePublish
};

/** 
  * an enum type to specify the publishing method
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
enum PKIPubMethod {
	dontCare = 0,
	x500,
	web,
	ldap
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * SinglePubInfo ::= SEQUENCE {
  *        pubMethod    INTEGER {
  *               dontCare    (0),
  *               x500        (1),
  *               web         (2),
  *               ldap        (3) },
  *        pubLocation  GeneralName OPTIONAL
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKISinglePubInfo {
   /** on of the above values */
	enum PKIPubMethod		  m_cnPubMethod;
   /** a general name */
	GeneralName				* m_pPubLocation;	/* opt. */
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * pubInfos  SEQUENCE SIZE (1..MAX) OF SinglePubInfo OPTIONAL
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqPubInfo {
   /** the actual single publication info */
	struct CMP_PKISinglePubInfo		* element;
   /** the next one */
	struct SeqPubInfo				* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * publicationInfo [1] PKIPublicationInfo  OPTIONAL
  *        PKIPublicationInfo ::= SEQUENCE {
  *                    action     INTEGER {dontPublish (0),pleasePublish (1) },
  *                    pubInfos  SEQUENCE SIZE (1..MAX) OF SinglePubInfo OPTIONAL				  
  *        }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIPubInfo {
   /** the publish action */
	enum PKIPIAction		  m_cnAction;
   /** the publish data structure */
	struct SeqPubInfo		* m_pPubInfos;		/* opt. */
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * EncryptedValue ::= SEQUENCE {
  *             intendedAlg   [0] AlgorithmIdentifier  OPTIONAL,
  *             symmAlg       [1] AlgorithmIdentifier  OPTIONAL,
  *             encSymmKey    [2] BIT STRING           OPTIONAL,
  *             keyAlg        [3] AlgorithmIdentifier  OPTIONAL,
  *             valueHint     [4] OCTET STRING         OPTIONAL,
  *             encValue       BIT STRING
  * }								      																	      
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct EncryptedValue {
	AlgId				* m_pIntendedAlg;		/* opt. */
	AlgId				* m_pSymmAlg;			/* opt. */
	BitString			* m_pEncSymmKey;		/* opt. */
	AlgId				* m_pKeyAlg;			/* opt. */
	OctetString			* m_pValueHint;			/* opt. */
	BitString			* m_pEncValue;
};

/** 
  * an enum for specify a certificate or a encrypted value
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
enum CMP_PKICOECType {
	COECCertificate = 0,
	COECEncrypted
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertOrEncCert ::= CHOICE {
  *        certificate     [0] Certificate,
  *        encryptedCert   [1] EncryptedValue
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKICertOrEncCert {
   /** specify what will be found here */
	enum CMP_PKICOECType  m_cnCOECType;
   /** contains a certificate of a encrypted certificate */
	void				* m_pCert;		/* Certificate or EncryptedValue */
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertifiedKeyPair ::= SEQUENCE {
  *           certOrEncCert       CertOrEncCert,
  *           privateKey      [0] EncryptedValue      OPTIONAL,
  *           publicationInfo [1] PKIPublicationInfo  OPTIONAL
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKICertKeyPair {
   /** Certificate or Encrypted Value */
	struct CMP_PKICertOrEncCert	* m_pCertOrEncCert;
   /** opt. priv. key if necessary */
	struct EncryptedValue		* m_pPrivKey;
   /** opt. publication infos */
	struct CMP_PKIPubInfo		* m_pPubInfo;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertResponse ::= SEQUENCE {
  *       certReqId           INTEGER,
  *       status              PKIStatusInfo,
  *       certifiedKeyPair    CertifiedKeyPair    OPTIONAL,
  *       rspInfo             OCTET STRING        OPTIONAL
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKICertRespMsg {
   /** Id from the Request */
	long							  m_nCertReqId;
   /** Status informations */
	struct CMP_PKIStatusInfo		* m_pStatus;
   /** optional */
	struct CMP_PKICertKeyPair		* m_pCertKeyPair;
   /** optional, similar to the ReqInfo */
	OctetString						* m_pRspInfo;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * response            SEQUENCE OF CertResponse
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqCertRespMsg {
   /** actual cert response message */
	struct CMP_PKICertRespMsg		* element;
   /** next one */
	struct SeqCertRespMsg			* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertRepMessage ::= SEQUENCE {
  *           caPubs          [1] SEQUENCE SIZE (1..MAX) OF Certificate OPTIONAL,
  *           response            SEQUENCE OF CertResponse
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIBody_CertResponse {
   /** optional Certificates */
	struct SeqCert				* m_pCaPubs;
   /** sequence 0..max of CertRespMsg */
	struct SeqCertRespMsg		* m_pResponse;
};

/* ---------------------- PKI Body Revocation Request ----------------------------- */

/** 
  * an enum to specify the revocation reason
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
enum CMP_CRLReason {
	CRLUnspecified = 0,
	CRLKeyCompromise,
	CRLCACompromise,
	CRLAffiliationChanged,
	CRLSuperseded,
	CRLCertificateHold,
	CRLRemoveFromCRL
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * RevDetails ::= SEQUENCE {
  *     certDetails         CertTemplate,
  *     revocationReason    ReasonFlags      OPTIONAL,
  *           ReasonFlags ::= BIT STRING {
  *                  unused                  (0),
  *                  keyCompromise           (1),
  *                  cACompromise            (2),
  *                  affiliationChanged      (3),
  *                  superseded              (4),
  *                  cessationOfOperation    (5),
  *                  certificateHold         (6)
  *           }
  *     badSinceDate        GeneralizedTime  OPTIONAL,
  *     crlEntryDetails     Extensions       OPTIONAL
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIRevDetails {
   /** certificate details */
	struct CMP_PKICertTempl		* m_pCertDetails;
   /** the revocation reason */
	BitString					* m_pReasonFlags;	/* optional */
   /** the revocation timestamp */
	GeneralTime					* m_pBadSinceDate;	/* optional */
   /** CRL extensions */
	struct Extensions			* m_pCrlEntryDetails;/* optional */
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * RevReqContent ::= SEQUENCE OF RevDetails
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqofRevDetails {
   /** the actual revocation */
	struct CMP_PKIRevDetails	* element;
   /** the next one */
	struct SeqofRevDetails		* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * RevReqContent ::= SEQUENCE OF RevDetails
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIBody_RevReq {
   /** a pointer to the sequence structure */
	struct SeqofRevDetails		* m_pRevDetails;
};

/* ---------------------- PKI Body Revocation Response ----------------------------- */

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * CertId ::= SEQUENCE {
  *     issuer           GeneralName,
  *     serialNumber     INTEGER
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKICertId {
   /** the issuer general name */
	GeneralName					* m_pIssuer;
   /** a serial number */
	OctetString					* m_pSerialNumber;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * revCerts [0] SEQUENCE SIZE (1..MAX) OF CertId OPTIONAL
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqCertId {
   /** the actual Cert id */
	CMP_PKICertId			* element;
   /** the next one */ 
	SeqCertId				* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * crls     [1] SEQUENCE SIZE (1..MAX) OF CertificateList  OPTIONAL
  *         CertificateList  ::=  SEQUENCE  {
  *                    tbsCertList          TBSCertList,
  *                             TBSCertList  ::=  SEQUENCE  {
  *                                 version                 Version OPTIONAL,
  *                                 signature               AlgorithmIdentifier,
  *                                 issuer                  Name,
  *                                 thisUpdate              Time,
  *                                 nextUpdate              Time OPTIONAL,
  *                                 revokedCertificates     SEQUENCE OF SEQUENCE  {
  *                                                       userCertificate         CertificateSerialNumber,
  *                                                       revocationDate          Time,
  *                                                       crlEntryExtensions      Extensions OPTIONAL
  *                                 }  OPTIONAL,
  *                             crlExtensions           [0]  EXPLICIT Extensions OPTIONAL
  *                    }
  *         signatureAlgorithm   AlgorithmIdentifier,
  *         signatureValue       BIT STRING
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqCRL {
   /** the actual revocation list */
	CRL							* element;
   /** the next one */
	SeqCRL						* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * RevRepContent ::= SEQUENCE {
  *      status       SEQUENCE SIZE (1..MAX) OF PKIStatusInfo,
  *      revCerts [0] SEQUENCE SIZE (1..MAX) OF CertId OPTIONAL,
  *      crls     [1] SEQUENCE SIZE (1..MAX) OF CertificateList  OPTIONAL
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIBody_RevResp {
   /** the returned status */
	SeqStatusInfo				* m_pStatus;
   /** the revoked certificate ids */
	SeqCertId					* m_pRevCerts;		/* optional */
   /** several certificate revocation lists */
	SeqCRL						* m_pCrls;			/* optional */
};

/* ---------------------- PKI Body Error Message ----------------------------- */

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * ErrorMsgContent ::= SEQUENCE {
  *       pKIStatusInfo          PKIStatusInfo,
  *       errorCode              INTEGER           OPTIONAL,
  *       errorDetails           PKIFreeText       OPTIONAL
  *                  PKIFreeText ::= SEQUENCE SIZE (1..MAX) OF UTF8String
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIBody_ErrorMessage {
   /** the status ot the error */
	CMP_PKIStatusInfo			* m_pStatusInfo;
   /** the error code */
	int							  m_nErrorCode;		/* optional */
   /** a free error text */
	char						* m_pFreeText;		/* optional */
};

/*------------------------ PKI Message  --------------------------------------------------*/

/* PKIMessage body types */
/** 
  * an enum to specify the pki message type
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
typedef enum CMP_PKIBodyType {
	CMPInitRequest = 0,
	CMPInitResponse = 1,
	CMPCertRequest = 2,				/*phase 1*/
	CMPCertResponse = 3,			/*phase 1*/
	CMPPKCS10CertRequest = 4,
	CMPPopChallenge = 5,			
	CMPPopResponse = 6,				
	CMPKeyUpdateRequest = 7,
	CMPKeyUpdateResponse = 8,
	CMPKeyRecoveryRequest = 9,	
	CMPKeyRecoveryResponse = 10,
	CMPKeyRevocationRequest = 11,	/*phase 1*/
	CMPKeyRevocationResponse = 12,	/*phase 1*/
	CMPCrossCertRequest = 13,
	CMPCrossCertResponse = 14,
	CMPCAKeyUpdateAnn = 15,
	CMPCertAnn = 16,
	CMPRevocationAnn = 17,
	CMPCRLAnn = 18,
	CMPConf = 19,
	CMPNestedMess = 20,
	CMPGeneralMess = 21,			/*phase 1*/
	CMPGeneralResp = 22,			/*phase 1*/
	CMPErrorMess = 23				/*phase 1*/
} CMP_PKIBodyType;

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * PKIBody ::= CHOICE {       -- message-specific body elements
  *          ir      [0]  CertReqMessages,        --Initialization Request
  *          ip      [1]  CertRepMessage,         --Initialization Response
  *          cr      [2]  CertReqMessages,        --Certification Request
  *          cp      [3]  CertRepMessage,         --Certification Response
  *          p10cr   [4]  CertificationRequest,   --PKCS #10 Cert. Req.
  *          popdecc [5]  POPODecKeyChallContent, --pop Challenge
  *          popdecr [6]  POPODecKeyRespContent,  --pop Response
  *          kur     [7]  CertReqMessages,        --Key Update Request
  *          kup     [8]  CertRepMessage,         --Key Update Response
  *          krr     [9]  CertReqMessages,        --Key Recovery Request
  *          krp     [10] KeyRecRepContent,       --Key Recovery Response
  *          rr      [11] RevReqContent,          --Revocation Request
  *          rp      [12] RevRepContent,          --Revocation Response
  *          ccr     [13] CertReqMessages,        --Cross-Cert. Request
  *          ccp     [14] CertRepMessage,         --Cross-Cert. Response
  *          ckuann  [15] CAKeyUpdAnnContent,     --CA Key Update Ann.
  *          cann    [16] CertAnnContent,         --Certificate Ann.
  *          rann    [17] RevAnnContent,          --Revocation Ann.
  *          crlann  [18] CRLAnnContent,          --CRL Announcement
  *          conf    [19] PKIConfirmContent,      --Confirmation
  *          nested  [20] NestedMessageContent,   --Nested Message
  *          genm    [21] GenMsgContent,          --General Message
  *          genp    [22] GenRepContent,          --General Response
  *          error   [23] ErrorMsgContent         --Error Message
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIBody {
   /** the message body type */
	enum CMP_PKIBodyType	  m_cnBodyType;	/* extra information for message type */
   /** the pointer to the body type substructure */
	void					* m_pBody;      /* Pointer to Body type */
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * extraCerts   [1] SEQUENCE SIZE (1..MAX) OF Certificate OPTIONAL
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqCert {
   /** the actual certificate */
	Certificate				* element;
   /** the next one */
	struct SeqCert			* next;
};

/** 
  * this is a c-structure for the asn.1 structure:<br>
  * <pre>
  * PKIMessage ::= SEQUENCE {
  *        header           PKIHeader,
  *        body             PKIBody,
  *        protection   [0] PKIProtection OPTIONAL,
  *                    PKIProtection ::= BIT STRING
  *        extraCerts   [1] SEQUENCE SIZE (1..MAX) OF Certificate OPTIONAL
  * }
  * </pre>
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIMessage {
   /** Header structure of Message */
   struct CMP_PKIHeader	*  m_pHeader;
   /** Body structure of Message */
   CMP_PKIBody				*  m_pBody;
   /** Optional PKI Protection */
	Boolean					   m_bProtect;
   /** Signature of the message */
	BitString				*  m_pProtection;
   /** Optional extra certificates */
	struct SeqCert			*  m_pExtraCerts;
   /** is necessary for the protection: the signer PSE */
	PSE						   m_pOwnPSE;
};

/* End : PKIMessage ------------------------------------------------------------- */

/* Extra Structures for the functions Get/Set RegInfo structure */

/** 
  * this is the first c-structure to build a url like parameter string<br>
  * the key/value-pair structure
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct CMP_PKIValuePair {
	char*	szName;
	char*	szValue;
};

/** 
  * this is second the  c-structure is to build a url like parameter string<br>
  * the linked list structure
  *
  * <p> 
  * @author  Stephan Klein
  * @version $Revision$ 
  */ 
struct SeqValuePair {
	CMP_PKIValuePair *	element;
	SeqValuePair *		next;
};


#define SECUDE_CMP_INCLUDE 1
#include <secude/cmp_p.h>
#undef SECUDE_CMP_INCLUDE

#endif /* _CMP_H_ */

