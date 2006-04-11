/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/ocsp_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef OCSP_P_H_
#define OCSP_P_H_

#if !defined(SECUDE_OCSP_INCLUDE) || !SECUDE_OCSP_INCLUDE
#error do not include this file, include <secude/ocsp.h>
#endif


#include "secude/f_macros.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* monolithic verify/retrieve */

OCSPVerifyOptions SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPVerifyOptions SEC_PROTOTYPE_0();

AUX_FREE_PROTOTYPE(OCSPVerifyOptions)

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_verify_Certificates SEC_PROTOTYPE_8(
	PSE, pse,
	KeyInfo *, cakey,
	SEQUENCE_OF_Certificate *, certs,
	OCSPVerifyResult **, result,
	OCSPVerifyOptions *, options,
	OCSPQueryFunc *, ocspqueryfunc,
	const char *, responderuri,
	void *, ocspquerycontext);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_retrieve_Certificates SEC_PROTOTYPE_8(
	PSE, pse,
	DName *, issuer,
	SEQUENCE_OF_OctetString *, serialnumbers,
	OCSPVerifyResult **, result,
	OCSPVerifyOptions *, options,
	OCSPQueryFunc *, ocspqueryfunc,
	const char *, responderuri,
	void *, ocspquerycontext);

AUX_FREE_PROTOTYPE(OCSPVerifyResult)

/* object oriented query */

struct OCSPQuery SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPQuery SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_init_OCSPQuery SEC_PROTOTYPE_1(
	struct OCSPQuery *, query);

struct SingleOCSPQuery SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_add_SingleOCSPQuery SEC_PROTOTYPE_3(
	struct OCSPQuery *, query,
	KeyInfo *, cakey,
	Certificate *, cert);

struct SingleOCSPQuery SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_add2_SingleOCSPQuery SEC_PROTOTYPE_4(
	struct OCSPQuery *, query,
	DName *, issuer,
	KeyInfo *, issuerPK,
	OctetString *, serialnumber);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_sign_OCSPQuery SEC_PROTOTYPE_5(
	struct OCSPQuery *, query,
	PSE, pse,
	SEQUENCE_OF_Certificate *, requestCerts,
	OCSPLockFunc *, lockfunc,
	void *, lockfunccontext);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_do_OCSPQuery SEC_PROTOTYPE_8(
	struct OCSPQuery *, query,
	PSE, pse,
	SEQUENCE_OF_Certificate *, requestCerts,
	OCSPQueryFunc *, queryfunc,
	const char *, responderuri,
	void *, queryfunccontext,
	OCSPLockFunc *, lockfunc,
	void *, lockfunccontext);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_save_OCSPResponse SEC_PROTOTYPE_1(
	 const struct OCSPQuery *, query);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_restore_OCSPResponse SEC_PROTOTYPE_3(
	struct OCSPQuery *, query,
	OctetString *, response,
	GeneralTime *, receivedAt);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_decode_OCSPResponse SEC_PROTOTYPE_2(
	struct OCSPQuery *, query,
	OctetString *, response);

OCSPResponse SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV
d_OCSPResponse SEC_PROTOTYPE_1(
    OctetString *, asn1_string);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OCSPResponse SEC_PROTOTYPE_1(OCSPResponse **, pp);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV
aux_sprint_OCSPResponse SEC_PROTOTYPE_2(
    char *, string,
    OCSPResponse *, response);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV 
ocsp_sprint_OCSPResponse SEC_PROTOTYPE_2(
    char *, sz,
    OCSPQuery *, p_query);

extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX OCSP_Response_OID;

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_encode_OCSPResponse SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_encode_OCSPRequest SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_match_OCSPQuery SEC_PROTOTYPE_4(
	struct OCSPQuery *, query,
	KeyInfo *, trustedOCSPCAKey,
	DName *, trustedOCSPCAName,
	KeyInfo *, trustedOCSPKey);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_OCSPQuery SEC_PROTOTYPE_1(
	struct OCSPQuery *, query);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OCSPQuery SEC_PROTOTYPE_1(
	struct OCSPQuery **, query);

/* cache */

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_init_OCSPResponseCache SEC_PROTOTYPE_5(
	struct OCSPResponseCache *, cache,
	unsigned long, cacheTime,
	unsigned long, maxAge,
	OCSPLockFunc *, lockfunc,
	void *, lockfunccontext);

struct OCSPResponseCache SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPResponseCache SEC_PROTOTYPE_4(
	unsigned long, cacheTime,
	unsigned long, maxAge,
	OCSPLockFunc *, lockfunc,
	void *, lockfunccontext);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_OCSPResponseCache SEC_PROTOTYPE_1(
	struct OCSPResponseCache *, cache);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OCSPResponseCache SEC_PROTOTYPE_1(
	struct OCSPResponseCache **, cache);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_clean_OCSPResponseCache SEC_PROTOTYPE_2(
	struct OCSPResponseCache *, cache,
	GeneralTime *, when);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_retrieve_OCSPResponse SEC_PROTOTYPE_3(
	struct OCSPQuery *, query,
	struct OCSPResponseCache *, cache,
	GeneralTime *, when);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_cache_OCSPResponse SEC_PROTOTYPE_2(
	struct OCSPQuery *, query,
	struct OCSPResponseCache *, cache);

/* reply */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  aux_free2_OCSPReply SEC_PROTOTYPE_1(
	struct OCSPReply *, reply);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OCSPReply SEC_PROTOTYPE_1(
	struct OCSPReply **, reply);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_init_OCSPReply SEC_PROTOTYPE_1(
	struct OCSPReply *, reply);

struct OCSPReply SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPReply SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_decode_OCSPReply SEC_PROTOTYPE_2(
	struct OCSPReply *, reply,
	OctetString *, in);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_encode_OCSPReply SEC_PROTOTYPE_2(
	struct OCSPReply *, reply,
	PSE, pse);

struct SingleOCSPRequest SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_find_SingleOCSPRequest SEC_PROTOTYPE_3(
	struct OCSPReply *, reply,
	DName *, issuer,
	KeyInfo *, issuerPK);

struct SingleOCSPResponse SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_add_SingleOCSPReply SEC_PROTOTYPE_7(
	struct OCSPReply *, reply,
	OCSPCertStatusInfo, type,
	GeneralTime *, revocationTime,
	CRLReason *, revocationReason,
	GeneralTime *, thisUpdate,
	GeneralTime *, nextUpdate,
	GeneralTime *, archiveCutoff);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_match_OCSPResponseCert SEC_PROTOTYPE_2(
	struct SingleOCSPRequest *, request,
	Certificate *, cert);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_OCSPResponseCert SEC_PROTOTYPE_5(
	struct SingleOCSPResponse *, response,
	Certificate *, cert,
	AlgId *, hashAlgorithm,
	Boolean, retrieve,
	GeneralTime *, certInDirSince);

/* misc */

v3Extension SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_add_Extension SEC_PROTOTYPE_4(
	SEQUENCE_OF_Extension **, to,
	const ExtnId *, extnId,
	const OctetString *, extnDERcode,
	Boolean, critical);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_OCSPauthInfoURI SEC_PROTOTYPE_1(
	const Certificate *, cert);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_TCauthInfoURI SEC_PROTOTYPE_1(
	const Certificate *, cert);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_check_OCSPNocheck SEC_PROTOTYPE_1(
	const Certificate *, cert);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_add_Certificate SEC_PROTOTYPE_2(
	SEQUENCE_OF_Certificate **, to,
	const Certificate *, cert);

AUX_FREE_PROTOTYPE(SEQUENCE_OF_Certificate)

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SEQUENCE_OF_Certificate SEC_PROTOTYPE_1(
	SEQUENCE_OF_Certificate *, certificates
);

/* ..._oid ----------------------------------------------------------- */

extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_Basic_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_Nonce_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_Crl_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_Response_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_Nocheck_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ArchiveCutoff_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ServiceLocator_oid;

extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_OCSPSigning_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISDirectoryService_oid;

extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISRetrieveIfAllowed_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISRequestedCertificate_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISCertInDirSince_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISCertHash_oid;

extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX TC_oid;

/* accessor functions */

struct OCSPResponderId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_responderId SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

SEQUENCE_OF_Extension SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_responseExtensions SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_add_requestExtension SEC_PROTOTYPE_4(
	struct OCSPQuery *, query,
	const ExtnId *, extnId,
	Boolean, critical,
	const OctetString *, extnDERcode);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_get_transportStatus SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_transportMessage SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

OCSPQueryStatus SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_get_queryStatus SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_responderCert SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_receivedAt SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_producedAt SEC_PROTOTYPE_1(
	const struct OCSPQuery *, query);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_requestorName SEC_PROTOTYPE_2(
	struct OCSPQuery *, query,
	const GeneralName *, requestorName);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_hashAlgorithm SEC_PROTOTYPE_2(
	struct OCSPQuery *, query,
	const AlgId *, hashAlgorithm);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_queryFlag SEC_PROTOTYPE_3(
	struct OCSPQuery *, query,
	OCSPQueryFlag, flag,
	Boolean, val);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_TraceFunc SEC_PROTOTYPE_4(
	struct OCSPQuery *, query,
	OCSPTraceFunc *, traceFunc,
	void *, traceFuncContext,
	OCSPTraceLevel, traceLevel);

#ifdef AUTHORITY_CHECKER_INTERFACE
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_ResponderVerifier SEC_PROTOTYPE_2(
	struct OCSPQuery *, query,
	ResponderVerifier *, pVerifier);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_ResponderAuthorityChecker SEC_PROTOTYPE_2(
	struct OCSPQuery *, query,
	ResponderAuthorityChecker *, pAuthorizer);
#endif /* AUTHORITY_CHECKER_INTERFACE */

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_singleResponderCert SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

OCSPQueryCertStatusInfo SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_get_certStatus SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

OCSPQueryCertStatusInfo SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_get_receivedCertStatus SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_revocationTime SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

CRLReason SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_revocationReason SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_thisUpdate SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_nextUpdate SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_archiveCutoff SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_certInDirSince SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_requestedCertificate SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

SEQUENCE_OF_Extension SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_singleResponseExtensions SEC_PROTOTYPE_1(
	const struct SingleOCSPQuery *, singlequery);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_add_singleRequestExtension SEC_PROTOTYPE_4(
	struct SingleOCSPQuery *, singlequery,
	ExtnId *, extnId,
	Boolean, critical,
	OctetString *, extnDERcode);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_retrieveIfAllowed SEC_PROTOTYPE_2(
	struct SingleOCSPQuery *, singlequery,
	Boolean, val);


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* OCSP_P_H_ */

