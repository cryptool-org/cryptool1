/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

#ifndef OCSP_P_H_
#define OCSP_P_H_

#include <f_macros.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* simple verify */
OCSPVerifyOptions SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPVerifyOptions SEC_PROTOTYPE_0(
);

AUX_FREE_PROTOTYPE(OCSPVerifyOptions)

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_verify_Certificates SEC_PROTOTYPE_8(
	PSE, pse,
	KeyInfo *, cakey,
	SEQUENCE_OF_Certificate *, certs,
	OCSPVerifyResult **, result,
	OCSPVerifyOptions *, options,
	OCSPQueryFunc *, ocspqueryfunc,
	const char *, responderuri,
	void *, ocspquerycontext
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_retrieve_Certificates SEC_PROTOTYPE_8(
	PSE, pse,
	DName *, issuer,
	SEQUENCE_OF_OctetString *, serialnumbers,
	OCSPVerifyResult **, result,
	OCSPVerifyOptions *, options,
	OCSPQueryFunc *, ocspqueryfunc,
	const char *, responderuri,
	void *, ocspquerycontext
);

AUX_FREE_PROTOTYPE(OCSPVerifyResult)

/* query */

OCSPQuery SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPQuery SEC_PROTOTYPE_0(
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_init_OCSPQuery SEC_PROTOTYPE_1(
	OCSPQuery *, query
);

SingleOCSPQuery SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_add_SingleOCSPQuery SEC_PROTOTYPE_3(
	OCSPQuery *, query,
	KeyInfo *, cakey,
	Certificate *, cert
);

SingleOCSPQuery SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_add2_SingleOCSPQuery SEC_PROTOTYPE_4(
	OCSPQuery *, query,
	DName *, issuer,
	KeyInfo *, issuerPK,
	OctetString *, serialnumber
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_do_OCSPQuery SEC_PROTOTYPE_8(
	OCSPQuery *, query,
	PSE, pse,
	SEQUENCE_OF_Certificate *, requestCerts,
	OCSPQueryFunc *, queryfunc,
	const char *, responderuri,
	void *, queryfunccontext,
	OCSPLockFunc *, lockfunc,
	void *, lockfunccontext
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_save_OCSPResponse SEC_PROTOTYPE_1(
	 const OCSPQuery *, query
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_restore_OCSPResponse SEC_PROTOTYPE_3(
	OCSPQuery *, query,
	OctetString *, response,
	GeneralTime *, receivedAt
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_decode_OCSPResponse SEC_PROTOTYPE_2(
	OCSPQuery *, query,
	OctetString *, response
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_match_OCSPQuery SEC_PROTOTYPE_4(
	OCSPQuery *, query,
	KeyInfo *, trustedOCSPCAKey,
	DName *, trustedOCSPCAName,
	KeyInfo *, trustedOCSPKey
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_OCSPQuery SEC_PROTOTYPE_1(
	OCSPQuery *, query
);

AUX_FREE_PROTOTYPE(OCSPQuery)

/* cache */

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_init_OCSPResponseCache SEC_PROTOTYPE_5(
	OCSPResponseCache *, cache,
	unsigned long, cacheTime,
	unsigned long, maxAge,
	OCSPLockFunc *, lockfunc,
	void *, lockfunccontext
);

OCSPResponseCache SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPResponseCache SEC_PROTOTYPE_4(
	unsigned long, cacheTime,
	unsigned long, maxAge,
	OCSPLockFunc *, lockfunc,
	void *, lockfunccontext
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_OCSPResponseCache SEC_PROTOTYPE_1(
	OCSPResponseCache *, cache
);

AUX_FREE_PROTOTYPE(OCSPResponseCache)

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_clean_OCSPResponseCache SEC_PROTOTYPE_2(
	OCSPResponseCache *, cache,
	GeneralTime *, when
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_retrieve_OCSPResponse SEC_PROTOTYPE_3(
	OCSPQuery *, query,
	OCSPResponseCache *, cache,
	GeneralTime *, when
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_cache_OCSPResponse SEC_PROTOTYPE_2(
	OCSPQuery *, query,
	OCSPResponseCache *, cache
);

/* reply */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  aux_free2_OCSPReply SEC_PROTOTYPE_1(
	OCSPReply *, reply
);

AUX_FREE_PROTOTYPE(OCSPReply)

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_init_OCSPReply SEC_PROTOTYPE_1(
	OCSPReply *, reply
);

OCSPReply SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_create_OCSPReply SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_decode_OCSPReply SEC_PROTOTYPE_2(
	OCSPReply *, reply,
	OctetString *, in
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_encode_OCSPReply  SEC_PROTOTYPE_2(
	OCSPReply *, reply,
	PSE, pse
);

SingleOCSPRequest SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_find_SingleOCSPRequest SEC_PROTOTYPE_3(
	OCSPReply *, reply,
	DName *, issuer,
	KeyInfo *, issuerPK
);

SingleOCSPResponse SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_add_SingleOCSPReply SEC_PROTOTYPE_7(
	OCSPReply *, reply,
	OCSPCertStatusInfo, type,
	GeneralTime *, revocationTime,
	CRLReason *, revocationReason,
	GeneralTime *, thisUpdate,
	GeneralTime *, nextUpdate,
	GeneralTime *, archiveCutoff
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_match_OCSPResponseCert SEC_PROTOTYPE_2(
	SingleOCSPRequest *, request,
	Certificate *, cert
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_set_OCSPResponseCert SEC_PROTOTYPE_5(
	SingleOCSPResponse *, response,
	Certificate *, cert,
	AlgId *, hashAlgorithm,
	Boolean, retrieve,
	GeneralTime *, certInDirSince
);

/* misc */

v3Extension SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_add_Extension SEC_PROTOTYPE_4(
	SEQUENCE_OF_Extension **, to,
	ExtnId *, extnId,
	OctetString *, extnDERcode,
	Boolean, critical
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ocsp_get_OCSPauthInfoURI SEC_PROTOTYPE_1(
	Certificate *, cert
);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ocsp_check_OCSPNocheck SEC_PROTOTYPE_1(
	Certificate *, cert
);

Certificate SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_add_Certificate SEC_PROTOTYPE_2(
	SEQUENCE_OF_Certificate **, to,
	Certificate *, cert
);

AUX_FREE_PROTOTYPE(SEQUENCE_OF_Certificate)

/* e_... / d_... ----------------------------------------------------------- */

E_PROTOTYPE(request, TBSOCSPRequest)
D_PROTOTYPE(request, TBSOCSPRequest)
E_PROTOTYPE(response, BasicOCSPResponse)
D_PROTOTYPE(response, BasicOCSPResponse)
E_PROTOTYPE(response, TBSOCSPResponse)
D_PROTOTYPE(response, TBSOCSPResponse)

E_PROTOTYPE(serviceLocator, ServiceLocator)
D_PROTOTYPE(serviceLocator, ServiceLocator)

E_PROTOTYPE(certHash, OCSPCertHash)
D_PROTOTYPE(certHash, OCSPCertHash)

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

extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISRetrieveIfAllowed_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISRequestedCertificate_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISCertInDirSince_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX OCSP_ISISCertHash_oid;

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* OCSP_P_H_ */

