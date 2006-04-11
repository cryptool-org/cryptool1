/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/ocsp.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef OCSP_H_
#define OCSP_H_

#include <secude/af.h>
#include <secude/x509v3.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***** Enumeration OCSPQueryStatus *****/
/** The value of queryStatus (in OCSPVerifyResult) describes the status
  * of the performed query. 
  * The answer should be considered authoritative only if its status is
  * OCSPQcertKey, OCSPQissuerKey, oder OCSPQtrustedKey. If the answer is OCSPQcertKey
  * you may check the responder certificate in responderCert (in OCSPVerifyResult)
  * according to <a href="ocsp/rfc2560.htm#4.2.2.2.1">RFC2560, section 4.2.2.2.1</a>.<br>
  * The calling code may decide to accept the answer if the status is OCSPQnoAuthorization
  * and the certificate in responderCert matches a local configuration of OCSP signing authority,
  * see <a href="ocsp/rfc2560.htm#4.2.2.2">RFC2560, section 4.2.2.2</a>, but this may be a security threat.
  * @ingroup header_ocsp
  */
enum OCSPQueryStatus {
/** A valid response has been received, but no further processing has been done.\  This should never happen. */
	OCSPQRsuccessful = 0,
/** The OCSP responder cannot parse the request, see <a href="ocsp/rfc2560.htm#2.3">RFC2560, section 2.3</a>.\  */
	OCSPQmalformedRequest,
/** Internal error in the OCSP responder, see <a href="ocsp/rfc2560.htm#2.3">RFC2560, section 2.3</a>.\  */
	OCSPQinternalError,
/** The OCSP responder is unable to respond to the request now, see <a href="ocsp/rfc2560.htm#2.3">RFC2560, section 2.3</a>.\  */
	OCSPQtryLater,
/** The server requires a signed request, see <a href="ocsp/rfc2560.htm#2.3">RFC2560, section 2.3</a>.\  */
	OCSPQsigRequired = 5,
/** The server refuses to respond to this request, see <a href="ocsp/rfc2560.htm#2.3">RFC2560, section 2.3</a>.\  */
	OCSPQunautorized,
/** No response from the OCSP responder, try examining <i>transportStatus</i> in OCSPVerifyResult.\  */
	OCSPQnoresponse = 128, /* no response */
/** An unspecified error occurred.\  */
	OCSPQerror, /* decoding or internal error */
/** The response is of unknown type (see <a href="ocsp/rfc2560.htm#4.2.1">RFC2560, section 4.2.1</a>) or contains
  * an unsupported extension marked as critical.\  If checkExtensions (in OCSPVerifyOptions) is
  * FALSE the calling code has to check the extensions.
  */
	OCSPQunsupported, /* there are critical extensions that I don't understand */
/** This query cannot be proccessed.\  Check the parameters. */
	OCSPQillegal, /* illegal query (check parameters) */
/** Unable to verify the signature of the response.\  */
	OCSPQsigFailed, /* cannot find signature key */
/** The returned nonce in the response does not match the supplied one in the request.\  */
	OCSPQnonceFailed, /* nonce does not match */
/** The response is from the future. 
  */
	OCSPQaged, /* producedAt is too old (or in the future) */
/** The OCSP responder that signed the response is not a proper responder for the CA that issued
  * the certificates in question (see <a href="ocsp/rfc2560.htm#2.6">RFC2560, section 2.6</a>).\  The calling code may accept the response
  * if the certificate supplied in responderCert (in OCSPVerifyResult)
  * matches a local configuration of OCSP signing authority for the certificates in question
  * (see <a href="ocsp/rfc2560.htm#4.2.2.2">RFC2560, section 4.2.2.2</a>).
  */
	OCSPQnoAuthorization, /* can't find valid authorization for this response */
/** The response is signed by an OCSP responder whose certificate is
  * issued by the CA that issued the certificates in question or an CA with the public
  * key trustedOCSPCAKey  (in OCSPVerifyOptions).\ 
  * The certificate is returned in responderCert (in OCSPVerifyResult)
  * and may be verified further, see <a href="ocsp/rfc2560.htm#4.2.2.2.1">RFC2560, section 4.2.2.2.1</a>.
  */
	OCSPQcertKey, /* response authorized by included Certificate */
/** The response is signed by the CA that issued the certificates in question, see <a href="ocsp/rfc2560.htm#2.2">RFC2560, section 2.2</a>.\  */
	OCSPQissuerKey, /* response signed by CA key */
/** The response is signed by the key trustedKey (in OCSPVerifyOptions).\  */
	OCSPQtrustedKey, /* response signed by trusted key */
/** The signature of the response was not checked.\  */
	OCSPQsigIgnored, /* response signature ignored */
/** The response is signed by a key that was certified by the trusted responder CA trustedKey (in OCSPVerifyOptions).\  */
	OCSPQtrustedCAKey /* response signed using key certified by trusted responder CA */
};
#ifndef DOXYGEN_EXCLUDE
typedef enum OCSPQueryStatus OCSPQueryStatus;
#endif

/***** Enumeration OCSPQueryCertStatusInfo *****/
/** The value of certStatus (in OCSPVerifyCertStatus) describes the status
  * of the certificate in question. Its value is either the response from the responder or an error state.
  * @ingroup header_ocsp
  */
enum OCSPQueryCertStatusInfo {
/** The certificate is not known as revoked (but may not exist), see <a href="ocsp/rfc2560.htm#2.2">RFC2560, section 2.2</a>.\  */
	OCSPQCgood = 0,
/** The certificate is revoked, see <a href="ocsp/rfc2560.htm#2.2">RFC2560, section 2.2</a>.\  */
	OCSPQCrevoked,
/** The state of the certificate is unknown to the responder, see <a href="ocsp/rfc2560.htm#2.2">RFC2560, section 2.2</a>.\  */
	OCSPQCunknown,
/** The response contained no status information for the certificate in question.\  */
	OCSPQCnoResponse = 128, /* no response */
/** The OCSP responder that signed the response is not a proper responder for the CA that issued
  * the certificates in question (see <a href="ocsp/rfc2560.htm#2.6">RFC2560, section 2.6</a>) and does not
  * matche a local configuration of OCSP signing authority for the certificates in question
  * (see <a href="ocsp/rfc2560.htm#4.2.2.2">RFC2560, section 4.2.2.2</a>).\ 
  */
	OCSPQCunauthorized, /* can't find valid authorization for this response */
/** An internal error occured */
	OCSPQCerror, /* decoding or internal error */
/** The query contained illegal parameters, perhaps the certificate was not issued by the supplied CA.\  */
	OCSPQCillegal, /* illegal certificate (check issuer) */
/** ThisUpdate is after producedAt or nextUpdate before producedAt. 
  */
	OCSPQCaged, /* thisUpdate too old or in future or nextUpdate in past */
/** The status is of unknown type or contains an unsupported extension marked as critical.\ 
  * If checkExtensions (in OCSPVerifyOptions) is FALSE the calling code
  * has the responsibility to check for extensions marked as critical.
  */
	OCSPQCunsupported, /* there are critical extensions that I don't understand */
/** The certHash from the responder does not match the hash of the certificate 
  * in question. If requireCertHash (in OCSPVerifyOptions) is TRUE the a
  * certHash in the answer is required.
  */
	OCSPQCmismatch /* certificates in request and response do not match */
};
#ifndef DOXYGEN_EXCLUDE
typedef enum OCSPQueryCertStatusInfo OCSPQueryCertStatusInfo;
#endif

/***** Structure OCSPVerifyCertStatus *****/
/** The <b>OCSPVerifyCertStatus</b> structure mirrors the returned <a href="ocsp/rfc2560.htm#SingleResponse">SingleResponse</a> for a certificate.
  * They are sorted in the same order as the certificates in parameter certs in #ocsp_verify_Certificates.
  * @ingroup header_ocsp
  */
struct OCSPVerifyCertStatus {
/** The Version of this structure. */
	int version;
/** Status of the certificate in question, see #OCSPQueryCertStatusInfo. */
	OCSPQueryCertStatusInfo certStatus;
/** The certificate status as given in the responders answer, for debugging purposes only (due to popular demand). 
  */
	OCSPQueryCertStatusInfo receivedStatus;
/** The time at which the status being indicated is known to be correct, see <a href="ocsp/rfc2560.htm#2.4">RFC2560, section 2.4</a>. */
	GeneralTime *thisUpdate;
/** Optional: The time at or before which newer information will be available about the status of the certificate, see <a href="ocsp/rfc2560.htm#2.4">RFC2560, section 2.4</a>. */
	GeneralTime *nextUpdate; /* OPTIONAL */
/** Optional: date revocation information is retained beyond a certificate's expiration, see <a href="ocsp/rfc2560.htm#4.4.4">RFC2650, section 4.4.4</a>.
  */
	GeneralTime *archiveCutoff; /* Extension */
/** Optional: date since the certificate is known by the OCSP responder, ISIS extension.
  */
	GeneralTime *certInDirSince; /* ISIS Extension */
/** If the certificate is revoked: time since which the certificate is revoked, see <a href="ocsp/rfc2560.htm#RevokedInfo">RFC2650</a>. NULL otherwise.
  */
	GeneralTime *revocationTime;
/** If the certificate is revoked, an optional CRLReason (defined in  AuthenticationFramework { joint-iso-itu-t ds(5) module(1) authenticationFramework(7) 3 },
  * see <a href="ocsp/rfc2560.htm#RevokedInfo">RFC2560</a>.
  */
	CRLReason *revocationReason; /* OPTIONAL */
/** the certificate requestet by #ocsp_retrieve_Certificates if it is retrievable.
  * NULL otherwise.
  */
	Certificate *requestedCertificate; /* ISIS Extension */
/** Returned singleExtensions, see <a href="ocsp/rfc2560.htm#4.4">RFC2560, section 4.4</a>.
  * If checkExtensions (in OCSPVerifyOptions) is
  * FALSE the calling code has to check for extensions marked as critical.
  */
	SEQUENCE_OF_Extension *extensions; /* OPTIONAL */
};
/***** Typedef OCSPVerifyCertStatus *****/
/** @ingroup header_ocsp
  */
typedef struct OCSPVerifyCertStatus OCSPVerifyCertStatus;

/***** Typedef SEQUENCE_OF_OCSPVerifyCertStatus *****/
/** @ingroup header_ocsp
  */
typedef SEQUENCE_OF(OCSPVerifyCertStatus) SEQUENCE_OF_OCSPVerifyCertStatus;

/***** Structure OCSPVerifyResult *****/
/** This structure describes the result of the OCSP query including the certificates in question.
  * The memory for the <b>OCSPVerifyResult</b> structure is allocated by #ocsp_verify_Certificates
  * or #ocsp_retrieve_Certificates. The calling code has to free the memory by calling
  * #aux_free_OCSPVerifyResult.
  *
  * @ingroup header_ocsp
  */
struct OCSPVerifyResult {
/** Version of this structure. */
	int version;
/** Return value of the @ref OCSPQueryFunc "transport function". */
	int transportStatus;
/** Optional text message of the @ref OCSPQueryFunc "transport function". */
	char *transportMessage;
/** Validity of the Result, see #OCSPQueryStatus. */
	OCSPQueryStatus queryStatus;
/** The time at which the OCSP responder signed the response, see <a href="ocsp/rfc2560.htm#2.4">RFC2560, section 2.4</a>. */
	GeneralTime *producedAt;
/** The time at which the response was received (system time). */
	GeneralTime *receivedAt;
/** Returned certificate of the responder, see OCSPQcertKey in #OCSPQueryStatus */
	Certificate *responderCert;
/** List of OCSPVerifyCertStatus structures which indicate the state
  * of the certificates in question. The list has the same length and order as the supplied list with
  * certificates certs in #ocsp_verify_Certificates or #ocsp_retrieve_Certificates.
  */
	SEQUENCE_OF_OCSPVerifyCertStatus *certStatus;
/** Returned responseExtensions, see <a href="ocsp/rfc2560.htm#ResponseData">RFC2560</a>.
  * If checkExtensions (in OCSPVerifyOptions) is
  * FALSE the calling code has to check for extensions marked as critical.
  */
	SEQUENCE_OF_Extension *extensions;
};
/***** Typedef OCSPVerifyResult *****/
/** @ingroup header_ocsp
  */
typedef struct OCSPVerifyResult OCSPVerifyResult;

/***** Typedef SEQUENCE_OF_Certificate *****/
/** @ingroup header_ocsp
  */
typedef SEQUENCE_OF(Certificate) SEQUENCE_OF_Certificate;

 /* This prototype function is documented in the description of group
  * header_ocsp due to difficulties with doxygen.
  * Refer to it using '@ref OCSPTraceFunc'
  */
typedef SEC_CALLBACK(void, OCSPTraceFunc) SEC_PROTOTYPE_3(
	const char *, header,
	const char *, msg,
	void *, context
);

typedef struct OCSPResponse OCSPResponse;

/***** Enumeration OCSPTraceLevel *****/
/** @ingroup header_ocsp
  */
enum OCSPTraceLevel {
	OCSP_TRACENONE = 0,  /**< <tt>=0</tt> */
	OCSP_TRACEERROR,
	OCSP_TRACEWARNING,
	OCSP_TRACELOG,
	OCSP_TRACEALL
};
#ifndef DOXYGEN_EXCLUDE
typedef enum OCSPTraceLevel OCSPTraceLevel;
#endif

/***** Structure OCSPVerifyOptions *****/
/** This structure allows to pass additional parameters in <i>options</i> to
  * #ocsp_verify_Certificates or #ocsp_retrieve_Certificates.
  * A default structure should be created by #ocsp_create_OCSPVerifyOptions.
  * It is only necessary if the defaults are not sufficient, else NULL may be
  * used.
  *
  * @ingroup header_ocsp
  */
struct OCSPVerifyOptions {
/** Version of the option structure. */
	int version;
/** The public key of a trusted OCSP responder CA. Responders with a Certificate issued by this CA are authorized
  * to answer queries to every Certificate, this is a local configuration of an OCSP signing authority in the sense of
  * <a href="ocsp/rfc2560.htm#4.2.2.2">RFC2560, section 4.2.2.2</a>, an extendedKeyUsage of id-kp-OCSPSigning is still required.
  * Default: NULL, trust only responder issued by the CA who issued the certificates in question.
  */
	KeyInfo *trustedOCSPCAKey; /* default NULL */
/** The Name of a trusted OCSP responder CA. Only used if trustedOCSPCAKey is given.
  * Default: NULL, do not check OCSP responder CA name.
  */
	DName *trustedOCSPCAName; /* default NULL */
/** The public key of a trusted OCSP responder, see <a href="ocsp/rfc2560.htm#2.2">RFC2560, section 2.2</a>. Every
  * response signed with this key will be trusted. Mainly for testing purposes or if your responder does not send its certificate.
  * Default: NULL, no trusted OCSP responder.
  */
	KeyInfo *trustedOCSPResponderKey; /* default NULL */
/** A nonce should be included in the request and is required in the response. See <a href="ocsp/rfc2560.htm#4.4.1">RFC2560, section 4.4.1</a>.
  * Default: TRUE.
  */
	Boolean requireNonce; /* default TRUE */
/** Require the ISIS certHash extension in the response. Default: FALSE.
  */
	Boolean requireCertHash; /* default FALSE */
/** The authority information access extensions should be copied from the certificates to the OCSP request,
  * see <a href="ocsp/rfc2560.htm#4.4.6">RFC2560, section 4.4.6</a>.
  * Default: FALSE.
  */
	Boolean includeServiceLocator; /* default FALSE */
/** The reply and all status informations should be checked for unsupported extensions marked
  * as critical. If one is found the reply is marked as invalid. Default: TRUE. If set to false the calling function
  * has the reponsibility to check the extensions.
  */
	Boolean checkExtensions; /* default TRUE */
/** The request should be signed if the pse parameter is not NULL,
  * see <a href="ocsp/rfc2560.htm#4.1.2">RFC2560, section 4.1.2</a>. Default: TRUE.
  */
	Boolean signRequest; /* default TRUE */
/** Accept an extended key usage of CRLSign instead of OCSPSigning. Only needed if the OCSP CA
  * is unable to issue standard conforming certificates. Default: FALSE.
  */
	Boolean acceptCRLSign; /* default FALSE */
/** send an ISIS certHash extension with the request. Default: FALSE.
  */
	Boolean sendCertHash; /* default FALSE */
/** Encode all ASN.1 field even if they have there default values. This is a braindead protocol violation,
  * but at least one responder needs it. Support for this parameter hopefully will be removed in the future.
  * Default: FALSE.
  */
	Boolean defaultCodingBug; /* default FALSE */
/** Certificates that should be added to the signed request to help the OCSP reponder to verify the
  * signature. See <a href="ocsp/rfc2560.htm#4.1.2">RFC2560, section 4.1.2</a>. Default: NULL, include your own Certificate.
  */
	SEQUENCE_OF_Certificate *requestCerts; /* default NULL */
/** The Algorithm used to calculate the CertID, see <a href="ocsp/rfc2560.htm#CertID">RFC2560, section 4.1.1</a>.
  * Default: NULL, use SHA1, see <a href="ocsp/rfc2560.htm#4.3">RFC2560, section 4.3</a>.
  */
	AlgId *hashAlgorithm;
	OctetString **savedResponse;
/** Tracing function, should be NULL. See @ref OCSPTraceFunc.
  */
	OCSPTraceFunc *traceFunc;
/** Context parameter for the tracing function.
  */
	void *traceFuncContext;
/** Trace level, one of OCSP_TRACENONE, OCSP_TRACEERROR, OCSP_TRACEWARNING, OCSP_TRACELOG, OCSP_TRACEALL.
  * Set to OCSP_TRACENONE.
  */
	OCSPTraceLevel traceLevel;
};
/***** Typedef OCSPVerifyOptions *****/
/** @ingroup header_ocsp
  */
typedef struct OCSPVerifyOptions OCSPVerifyOptions;

 /* This prototype function is documented in the description of group
  * header_ocsp due to difficulties with doxygen.
  * Refer to it using '@ref OCSPQueryFunc'
  */
typedef SEC_CALLBACK(int, OCSPQueryFunc) SEC_PROTOTYPE_5(
	OctetString *, in,
	OctetString **, out,
	char **, status,
	const char *, responderuri,
	void *, context
);

/***** Enumeration OCSPCertStatusInfo *****/
/** @ingroup header_ocsp
  */
enum OCSPCertStatusInfo {
	OCSPCgood = 0,
	OCSPCrevoked,
	OCSPCunknown
};
#ifndef DOXYGEN_EXCLUDE
typedef enum OCSPCertStatusInfo OCSPCertStatusInfo;
#endif

/***** Enumeration OCSPLockType *****/
/** @ingroup header_ocsp
  */
enum OCSPLockType {
	OCSPLockNone,
	OCSPLockShared,
	OCSPLockExclusive,
	OCSPLockFree
};
#ifndef DOXYGEN_EXCLUDE
typedef enum OCSPLockType OCSPLockType;
#endif

#ifndef DOXYGEN_EXCLUDE
 /* This function macro cannot be documented directly with doxygen.
  * Instead, it is described in group header_ocsp.
  * Refer to it using '@ref OCSPLockFunc'
  */
typedef SEC_CALLBACK(Boolean, OCSPLockFunc) SEC_PROTOTYPE_2(
	OCSPLockType, lock,
	void *, context
);
#endif

typedef enum OCSPQueryFlag {
	ocsp_query_requireNonce = 0x4F51726EUL,
	ocsp_query_signRequest = 0x4F517372UL,
	ocsp_query_requireCertHash = 0x4F517268UL,
	ocsp_query_checkExtensions = 0x4F516365UL,
	ocsp_query_includeServiceLocator = 0x4F51696CUL,
	ocsp_query_acceptCRLSign = 0x4F516163UL,
	ocsp_query_sendCertHash = 0x4F517368UL,
	ocsp_query_encodeDefault = 0x4F516563UL,
	ocsp_query_ignoreSignature = 0x4F516973UL
} OCSPQueryFlag;

/***** Typedef OCSPQuery *****/
/** @ingroup header_ocsp
  */
typedef struct OCSPQuery OCSPQuery;

typedef struct SingleOCSPQuery SingleOCSPQuery;

typedef struct OCSPResponseCache OCSPResponseCache;

typedef struct OCSPReply OCSPReply;

#define OCSP_DEFAULT_HASHALG sha1_aid

#ifdef AUTHORITY_CHECKER_INTERFACE
/* Interface types for application specific responder certificate verification
   and responder authorization check
*/
/*::Don't care about this section, it is still under construction.*/
typedef struct VerifierFunctions VerifierFunctions;
typedef struct ResponderVerifier
{
    const VerifierFunctions* fn;
} ResponderVerifier;

typedef struct AuthorityCheckerFunctions AuthorityCheckerFunctions;
typedef struct ResponderAuthorityChecker
{
    const AuthorityCheckerFunctions* fn;
} ResponderAuthorityChecker;

/* Typedefs for authority checker methods */
typedef RC FP_CheckResponderAuthority
(
 Certificate * pResponderSigningCert
 , Certificates * pResponderCerts
 , Boolean * bResponderIsAuthorized
 );

/* By calling this method, the default ResponderAuthorityChecker demands to know, if standard conform
   OCSP responders are accepted as well. If true is returned, standard conform OCSP responders are 
   accepted even if they do not meet the requirements of the proprietary ResponderAuthorityChecker.
   If false is returned, any responder that does not meet these requirements is disapproved.
 */
typedef RC FP_AcceptPKIXScheme
(
 Certificate * pResponderSigningCert
 , Certificates * pResponderCerts
 );

struct AuthorityCheckerFunctions
{
    FP_CheckResponderAuthority * fp_CheckResponderAuthority;
    FP_AcceptPKIXScheme        * fp_AcceptPKIXScheme;
};

#endif /* AUTHORITY_CHECKER_INTERFACE */

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#define SECUDE_OCSP_INCLUDE 1
#include <secude/ocsp_p.h>
#undef SECUDE_OCSP_INCLUDE

#define OCSP_VERSION 3

#define SENF_API_OCSP			(0x4F435350UL) /* 'OCSP' */

#endif /* OCSP_H_ */

