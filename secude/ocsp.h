/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#ifndef OCSP_H_
#define OCSP_H_

#include "af.h"
#include "x509v3.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum OCSPQueryStatus {
	OCSPQRsuccessful = 0,
	OCSPQmalformedRequest,
	OCSPQinternalError,
	OCSPQtryLater,
	OCSPQsigRequired = 5,
	OCSPQunautorized,
	OCSPQnoresponse, /* no response */
	OCSPQerror, /* decoding or internal error */
	OCSPQunsupported, /* there are critical extensions that I don't understand */
	OCSPQillegal, /* illegal query (check parameters) */
	OCSPQsigFailed, /* cannot find signature key */
	OCSPQnonceFailed, /* nonce does not match */
	OCSPQaged, /* producedAt is too old (or in the future) */
	OCSPQnoAuthorization, /* can't find valid authorization for this response */
	OCSPQcertKey, /* response authorized by included Certificate */
	OCSPQissuerKey, /* response signed by CA key */
	OCSPQtrustedKey /* response signed by trusted key */
} OCSPQueryStatus;

typedef enum OCSPQueryCertStatusInfo {
	OCSPQCgood,
	OCSPQCrevoked,
	OCSPQCunknown,
	OCSPQCnoResponse, /* no response */
	OCSPQCunauthorized, /* can't find valid authorization for this response */
	OCSPQCerror, /* decoding or internal error */
	OCSPQCillegal, /* illegal certificate (check issuer) */
	OCSPQCaged, /* thisUpdate too old or in future or nextUpdate in past */
	OCSPQCunsupported, /* there are critical extensions that I don't understand */
	OCSPQCmismatch /* certificates in request and response do not match */
} OCSPQueryCertStatusInfo;

typedef struct OCSPVerifyCertStatus {
	int version;
	OCSPQueryCertStatusInfo certStatus;
	OCSPQueryCertStatusInfo receivedStatus;
	GeneralTime *thisUpdate;
	GeneralTime *nextUpdate; /* OPTIONAL */
	GeneralTime *archiveCutoff; /* Extension */
	GeneralTime *certInDirSince; /* ISIS Extension */
	GeneralTime *revocationTime;
	CRLReason *revocationReason; /* OPTIONAL */
	Certificate *requestedCertificate; /* ISIS Extension */
	SEQUENCE_OF_Extension *extensions; /* OPTIONAL */
} OCSPVerifyCertStatus;


typedef SEQUENCE_OF(OCSPVerifyCertStatus) SEQUENCE_OF_OCSPVerifyCertStatus;

typedef struct OCSPVerifyResult {
	int version;
	int transportStatus;
	char *transportMessage;
	OCSPQueryStatus queryStatus;
	GeneralTime *producedAt;
	GeneralTime *receivedAt;
	Certificate *responderCert;
	SEQUENCE_OF_OCSPVerifyCertStatus *certStatus;
	SEQUENCE_OF_Extension *extensions;
} OCSPVerifyResult;

typedef SEQUENCE_OF(Certificate) SEQUENCE_OF_Certificate;

typedef struct OCSPVerifyOptions {
	int version; /* must be 1 */
	KeyInfo *trustedOCSPCAKey; /* default NULL */
	DName *trustedOCSPCAName; /* default NULL */
	KeyInfo *trustedOCSPResponderKey; /* default NULL */
	Boolean requireNonce; /* default TRUE */
	Boolean requireCertHash; /* default FALSE */
	Boolean includeServiceLocator; /* default FALSE */
	Boolean checkExtensions; /* default TRUE */
	Boolean signRequest; /* default TRUE */
	Boolean brokenResponder; /* default TRUE */
	SEQUENCE_OF_Certificate *requestCerts; /* default NULL */
	AlgId *hashAlgorithm;
	OctetString **savedResponse;
} OCSPVerifyOptions;

typedef int (OCSPQueryFunc)(
	OctetString *in,
	OctetString **out,
	char **status,
	const char *responderuri,
	void *context);

typedef struct OCSPIssuerId {
	AlgId *hashAlgorithm;
	OctetString *nameHash;
	OctetString *keyHash;
} OCSPIssuerId;

typedef struct OCSPCertId {
	OCSPIssuerId issuer;
	CertificateSerialNumber *serialNumber;
} OCSPCertId;

typedef struct OCSPSignature {
	Signature sig;
	SEQUENCE_OF_Certificate *certs; /* OPTIONAL */
} OCSPSignature;

typedef struct RevokedInfo {
	GeneralTime *revocationTime;
	CRLReason *revocationReason; /* OPTIONAL */
} RevokedInfo;

typedef enum OCSPCertStatusInfo {
	OCSPCgood = 0,
	OCSPCrevoked,
	OCSPCunknown
} OCSPCertStatusInfo;

typedef struct OCSPCertStatus {
	OCSPCertStatusInfo type;
	union {
	/* void good */
	RevokedInfo *revoked;
	/* void unknown */
	} value;
} OCSPCertStatus;

typedef struct OCSPCertHash {
	AlgId *hashAlgorithm;
	OctetString *certificateHash;
} OCSPCertHash;

typedef struct SingleOCSPResponse {
	OCSPCertId *certID;
	OCSPCertStatus *certStatus;
	GeneralTime *thisUpdate;
	GeneralTime *nextUpdate; /* OPTIONAL */
	GeneralTime *archiveCutoff; /* Extension */
	GeneralTime *certInDirSince; /* ISIS Extension */
	OCSPCertHash *certHash; /* ISIS Extension */
	Certificate *requestedCertificate; /* ISIS Extension */
	SEQUENCE_OF_Extension *singleResponseExtensions; /* OPTIONAL */
} SingleOCSPResponse;

typedef struct OCSPResponderId {
	int type; /* enum {responderIDbyName, responderIDbyKey} */
	union {
		DName *byName;
		OctetString *byKey;
	} value;
} OCSPResponderId;

typedef SEQUENCE_OF(SingleOCSPResponse) SEQUENCE_OF_SingleOCSPResponse;

typedef struct TBSOCSPResponse {
	int version;
	OCSPResponderId *responderId;
	GeneralTime *producedAt;
	SEQUENCE_OF_SingleOCSPResponse *responseList;
	OctetString *nonce; /* OPTIONAL EXTENSION */
	SEQUENCE_OF_Extension *responseExtensions; /* OPTIONAL */
} TBSOCSPResponse;

typedef struct BasicOCSPResponse {
	OctetString *tbsResponse_DERcode;
	OCSPSignature *signature;
} BasicOCSPResponse;

typedef struct ServiceLocator {
	DName *issuer;
	AuthInfoAccess *locator;
} ServiceLocator;

typedef struct SingleOCSPRequest {
	OCSPCertId *certID;
	OCSPCertHash *certHash; /* ISIS Extension */
	Boolean retrieveIfAllowed; /* ISIS Extension, critical */
	SEQUENCE_OF_Extension *singleRequestExtensions; /* OPTIONAL */
} SingleOCSPRequest;

typedef SEQUENCE_OF(SingleOCSPRequest) SEQUENCE_OF_SingleOCSPRequest;

typedef struct TBSOCSPRequest {
	int version;  /* DEFAULT v1(0) */
	GeneralName *requestorName; /* OPTIONAL */
	SEQUENCE_OF_SingleOCSPRequest *requestList;
	OctetString *nonce; /* OPTIONAL EXTENSION */
	SEQUENCE_OF_Extension *requestExtensions; /* OPTIONAL */
} TBSOCSPRequest;

typedef struct SingleOCSPQuery {
	SingleOCSPRequest *request;
	SingleOCSPResponse *response;
	Certificate *queriedCert;
	DName *issuerName;
	KeyInfo *issuerKey;
	Certificate *responderCert;
	OCSPQueryCertStatusInfo status;
	Boolean authorized;
	struct SingleOCSPQuery *next;
} SingleOCSPQuery;

typedef enum OCSPTraceLevel {
	OCSP_TRACENONE = 0,
	OCSP_TRACEERROR,
	OCSP_TRACEWARNING,
	OCSP_TRACELOG,
	OCSP_TRACEALL
} OCSPTraceLevel;

typedef void (OCSPTraceFunc)(
	const char *header,
	const char *msg,
	void *context
);

typedef struct OCSPQuery {
	SingleOCSPQuery *queries;
	TBSOCSPRequest *tbsRequest;
	BasicOCSPResponse *basicResponse;
	TBSOCSPResponse *tbsResponse;
	GeneralName *authorityInfoAccessLocation;
	int transportStatus;
	char *transportMessage;
	OCSPQueryStatus queryStatus;
	Certificate *responderCert;
	GeneralTime *receivedAt;
	AlgId *hashAlgorithm;
	Boolean requireNonce;
	Boolean signRequest;
	Boolean requireCertHash;
	Boolean checkExtensions;
	Boolean includeServiceLocator;
	Boolean exGeneralNameBug; /* default TRUE */
	OCSPTraceFunc *traceFunc;
	void *traceFuncContext;
	OCSPTraceLevel traceLevel;
} OCSPQuery;

typedef enum OCSPLockType {
	OCSPLockNone,
	OCSPLockShared,
	OCSPLockExclusive,
	OCSPLockFree
} OCSPLockType;

typedef Boolean (OCSPLockFunc)(
	OCSPLockType lock,
	void *context
);

/* OCSP cache */

#define OCSP_RESPONSEFILELEN 4
#define OCSP_CAFILELEN 4

typedef struct OCSPCacheResponse {
	CertificateSerialNumber *serialNumber;
	time_t validity;
	OctetString *cachedResponse;
	struct OCSPCacheResponse *next;
	char file[OCSP_RESPONSEFILELEN];
	Boolean updated;
} OCSPCacheResponse;

typedef struct OCSPCacheCA {
	OCSPIssuerId issuer;
	struct OCSPCacheResponse *responselist;
	struct OCSPCacheCA *next;
	char file[OCSP_CAFILELEN];
	Boolean updated;
} OCSPCacheCA;

typedef struct OCSPResponseCache {
	unsigned long cacheTime; /* maximal time to cache */
	unsigned long maxAge; /* maximal age of update */
	struct OCSPCacheCA *calist;
	OCSPLockFunc *lockfunc;
	void *lockfunccontext;
	char *directory;
	Boolean updated;
} OCSPResponseCache;

/* OCSPRequest ------------------------------------------------------------- */

typedef struct OCSPRequest {
	OctetString *tbsRequest_DERcode;
	OCSPSignature *optionalSignature; /* OPTIONAL */
} OCSPRequest;

/* OCSPResponse --------------------------------------------------------- */

typedef struct OCSPResponseBytes {
	ObjId *responseType;
	OctetString *response;
} OCSPResponseBytes;

typedef enum OCSPResponseStatus {
	OCSPRsuccessful = 0,
	OCSPRmalformedRequest,
	OCSPRinternalError,
	OCSPRtryLater,
	OCSPRsigRequired = 5,
	OCSPRunautorized
} OCSPResponseStatus;

typedef struct OCSPResponse {
	int responseStatus; /* OCSPResponseStatus */
	OCSPResponseBytes * responseBytes; /* OPTIONAL */
} OCSPResponse;

/* OCSPReply ------------------------------------------------------------- */

typedef struct OCSPReply {
	OCSPRequest *ocspRequest;
	TBSOCSPRequest *tbsRequest;
	OCSPResponseStatus responseStatus;
	TBSOCSPResponse *tbsResponse;
	SEQUENCE_OF_SingleOCSPRequest *requestList;
	OCSPCertId *matchedCertID;
	Boolean checkExtensions;
	Boolean respondUnknown;
	OCSPTraceFunc *traceFunc;
	void *traceFuncContext;
	OCSPTraceLevel traceLevel;
} OCSPReply;

#define OCSP_DEFAULT_HASHALG sha1_aid

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#include "ocsp_p.h"

#define OCSP_VERSION 2

#endif /* OCSP_H_ */

