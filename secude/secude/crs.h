/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/crs.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#ifndef _CRS_
#define _CRS_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



#include <secude/pkcs7.h>

typedef struct {
	CertificationRequest		*cert_req;
	SignedPublicKeyAndChallenge	*signed_key;
} EndEntityInfo;

typedef struct {
	EndEntityInfo	*end_entity_info;
	OctetString		*reg_info;
} PKCSReq;

typedef struct {
	DName			*issuer;
	GeneralTime		*time;
} GetCRL;

typedef struct {
	DName			*issuer;
	SerialNumber	*serial;
} GetCert;

typedef struct {
	ContentInfo		*ci;
	OctetString		*rep_info;
} CertRep;

typedef struct {
	DName			*issuer;
	SerialNumber	*serial;
	ReasonFlags		*reason;
	OctetString		*passphrase;
	char			*comment;
} RevReq;



/*
Create a Certification Request

  There are two types known: 
	PKCS #10 Certification Request         (certreq = TRUE)
		keytype				Type of key to create Request for
		attr				Optional Attributes
		cert_req_name		Suggestion for Subject Name
		alg					Signature Algorithm
		reg_info_name		Request Information String
	NetScape's SignedPublicKeyAndChallenge (certreq = FALSE)
		keytype				Type of key to create Request for
		challenge			Challenge ???
		alg					Signature Algorithm
		reg_info_name		Request Information String


*/
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV crs_crt_PKCSReq SEC_PROTOTYPE_9(
	PSE		  , pse,
	Boolean  , certreq,
	KeyType	   , keytype,
	SET_OF_Attr * , attr,
	DName * , cert_req_name,
	char * , challenge,
	char * , reg_info_name,
	AlgId * , alg,
	PKCSReq ** , preq
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV crs_verify_and_develope SEC_PROTOTYPE_6(
	PSE		  , pse,
	OctetString ** , cont,
	SET_OF_Attr ** , authenticated_Attrs,
	SET_OF_Attr ** , unauthenticated_Attrs,
	Certificates ** , certs,
	ContentInfo * , ci
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV crs_sign_and_envelope SEC_PROTOTYPE_8(
	PSE		  , pse,
	SET_OF_Certificate *	   , recipients,
	OctetString * , cont,
	AlgId * , dig_alg,
	AlgId * , enc_alg,
	SET_OF_Attr * , authenticated_Attrs,
	SET_OF_Attr * , unauthenticated_Attrs,
	ContentInfo ** , ci
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV crs_crt_signed_ReqReq SEC_PROTOTYPE_12(
	PSE		  , pse,
	SET_OF_Certificate *	   , recipients,
	AlgId * , dig_alg,
	AlgId * , enc_alg,
	DName	* , issuer,
	SerialNumber * , serial,
	ReasonFlags * , reason,
	OctetString * , passphrase,
	char * , comment,
	sec_int4 , tid,
	OctetString *, nonce,
	ContentInfo ** , ci
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV crs_crt_signed_GetCRL SEC_PROTOTYPE_9(
	PSE		  , pse,
	SET_OF_Certificate *	   , recipients,
	AlgId * , dig_alg,
	AlgId * , enc_alg,
	DName	* , issuer,
	GeneralTime * , gtime,
	OctetString * , tid,
	OctetString *, nonce,
	ContentInfo ** , ci
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV crs_crt_signed_GetCert SEC_PROTOTYPE_9(
	PSE		  , pse,
	SET_OF_Certificate *	   , recipients,
	AlgId * , dig_alg,
	AlgId * , enc_alg,
	DName	* , issuer,
	SerialNumber * , serial,
	sec_int4 , tid,
	OctetString *, nonce,
	ContentInfo ** , ci
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_PKCSReq SEC_PROTOTYPE_1(	
	PKCSReq	 *	, infostruct
);
PKCSReq SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_PKCSReq SEC_PROTOTYPE_1(	
	OctetString	 *	, asn1_string
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_PKCSReq SEC_PROTOTYPE_1(
	PKCSReq ** , str
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_GetCRL SEC_PROTOTYPE_1(	
	GetCRL	 *	, infostruct
);
GetCRL SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_GetCRL SEC_PROTOTYPE_1(	
	OctetString	 *	, asn1_string
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_GetCRL SEC_PROTOTYPE_1(
	GetCRL ** , str
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_GetCert SEC_PROTOTYPE_1(	
	GetCert	 *	, infostruct
);
GetCert SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_GetCert SEC_PROTOTYPE_1(	
	OctetString	 *	, asn1_string
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_GetCert SEC_PROTOTYPE_1(
	GetCert ** , str
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_CertRep SEC_PROTOTYPE_1(	
	CertRep	 *	, infostruct
);
CertRep SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_CertRep SEC_PROTOTYPE_1(	
	OctetString	 *	, asn1_string
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_CertRep SEC_PROTOTYPE_1(
	CertRep ** , str
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_RevReq SEC_PROTOTYPE_1(	
	RevReq	 *	, infostruct
);
RevReq SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_RevReq SEC_PROTOTYPE_1(	
	OctetString	 *	, asn1_string
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free_RevReq SEC_PROTOTYPE_1(
	RevReq ** , str
);


void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_EndEntityInfo SEC_PROTOTYPE_1(
	EndEntityInfo   * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_PKCSReq SEC_PROTOTYPE_1(
	PKCSReq * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_GetCRL SEC_PROTOTYPE_1(
	GetCRL * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_GetCert SEC_PROTOTYPE_1(
	GetCert * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_CertRep SEC_PROTOTYPE_1(
	CertRep * , str
);
void SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_free2_RevReq SEC_PROTOTYPE_1(
	RevReq * , str
);

AUX_PRINT_PROTOTYPE(PKCSReq)
AUX_PRINT_PROTOTYPE(GetCert)
AUX_PRINT_PROTOTYPE(CertRep)
AUX_PRINT_PROTOTYPE(GetCRL)
AUX_PRINT_PROTOTYPE(RevReq)
ASN1_en_de_PROTO(EndEntityInfo)
ASN1_en_de_PROTO(PKCSReq)
ASN1_en_de_PROTO(GetCRL)
ASN1_en_de_PROTO(GetCert)
ASN1_en_de_PROTO(CertRep)
ASN1_en_de_PROTO(RevReq)

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _CRS_ */

