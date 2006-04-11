/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/pkcs7.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/*-----------------------------------------------------------------------*/
/*  INCLUDE FILE  pkcs7.h  (PKCS #7 Standard)                                */
/*  Definition of structures and types for new PKCS #7 API              */
/*-----------------------------------------------------------------------*/
#ifndef _PKCS7_
#define _PKCS7_

#include <secude/pkcs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define DEF_DIGEST_ALG sha1
#define DEF_DATAENCR_ALG desCBC

typedef SET_OF(void) SET_OF_void;
typedef struct Digests Digests;

typedef struct PKCS7_PRS PKCS7_PRS;
typedef struct PKCS7_CRT PKCS7_CRT;
typedef struct PKCS7_FWD PKCS7_FWD;

typedef sec_int4  	( SEC_API_CALLING_CONV ADD_FUNC2 ) 		SEC_PROTOTYPE_3( PKCS7_PRS * , handle, char * , buf, sec_int4 , len );
typedef sec_int4  	( SEC_API_CALLING_CONV ADD_FUNC ) 		SEC_PROTOTYPE_3( void * , handle, char * , buf, sec_int4 , len );
typedef sec_int4  	( SEC_API_CALLING_CONV END_FUNC ) 		SEC_PROTOTYPE_1( void * , handle);

#if 1
/* Normally, the following data structure should be inside the
   file <secude/private/pkcs7_i.h>, but it is used somewhere in
   FileSafe/seccore in some way, I don't have the time to analyse
   right now, so it stays in the external headers, until these
   minor problems are solved.
   This data structure should not be used and may vanish from
   the external headers without further notification... */

/***** Structure Digests *****/
/** @ingroup header_pkcs7
  */
struct Digests {
	AlgId *alg;       /**< The digest algorithm */
	void  *ctx;       /**< The context of the hash function */
	OctetString dig;  /**< The calculated digest. */
	Digests *next;    /**< The next element */
};
#endif /* 1 */

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_data_init SEC_PROTOTYPE_5(
	void **, handle,
	OctetStream * , stream,
	OctetStream *	, ext_body,
	Boolean , canon,
	Boolean , base64
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_data_init SEC_PROTOTYPE_6(
	void **, handle,
	OctetStream * , stream,
	SET_OF_AlgId * , dig_algs,
	OctetStream *	, ext_body,
	Boolean , canon,
	Boolean , base64
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_enveloped_data_init SEC_PROTOTYPE_7(
	void **, handle,
	OctetStream * , stream,
	Key * , key,
	PKList * , recipients,
	OctetStream *	, ext_body,
	Boolean , canon,
	Boolean , base64
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_enveloped_data_init SEC_PROTOTYPE_8(
	void **, handle,
	OctetStream * , stream,
	SET_OF_AlgId * , dig_algs,
	Key * , key,
	PKList * , recipients,
	OctetStream *	, ext_body,
	Boolean , canon,
	Boolean , base64
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_enveloped_data_init2 SEC_PROTOTYPE_8(
	void **, handle,
	OctetStream * , stream,
	SET_OF_AlgId * , dig_algs,
	Key * , key,
	RecipientInfos * , recipients,
	OctetStream *	, ext_body,
	Boolean , canon,
	Boolean , base64
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_digested_data_init SEC_PROTOTYPE_6(
	void **, handle,
	OctetStream * , stream,
	AlgId * , dig_alg,
	OctetStream *	, ext_body,
	Boolean , canon,
	Boolean , base64
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_encrypted_data_init SEC_PROTOTYPE_6(
	void **, handle,
	OctetStream * , stream,
	Key * , key,
	OctetStream *	, ext_body,
	Boolean , canon,
	Boolean , base64
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_input SEC_PROTOTYPE_3(
	void *, handle,
	char * , buf,
	sec_int4 , length
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_end SEC_PROTOTYPE_1(
	void **, handle
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_add_signer_info SEC_PROTOTYPE_4(
	void *, handle,
	SignerInfo * , info,
	SET_OF_CRL *, crls,
	ExtendedCertificatesAndCertificates *, certs
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_get_digest SEC_PROTOTYPE_3(
	void *, handle,
	AlgId *, alg,
	OctetString ** , dig
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_sign_digest_with_key SEC_PROTOTYPE_9(
	
	Key		*  	, digestencKey,
	
	OctetString	* 	, digest,
	
	AlgId		* 	, digestAI,
	
	AlgId		* 	, signAI,
	
	SET_OF_Attr	* 	, authAttrs,
	
	SET_OF_Attr	* 	, unauthAttrs,
	
	SignerInfo	**	, signer_info,
	
	DName 		* 	, issuer,
	
	OctetString 	* 	, serialnumber

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_sign_digest SEC_PROTOTYPE_8(	
	PSE		  	, pse,	
	OctetString	* 	, digest,	
	AlgId		* 	, digestAI,	
	SET_OF_Attr	* 	, authAttrs,	
	SET_OF_Attr	* 	, unauthAttrs,	
	ExtendedCertificatesAndCertificates **, certs,	
	SignerInfo	**	, signer_info,
	int 		, cert_no
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_data SEC_PROTOTYPE_5(
	OctetStream *	, in,
	OctetStream *	, out,
	OctetStream *	, ext_body,
	Boolean		, canon,
	Boolean		, base64

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_data SEC_PROTOTYPE_11(
	PSE		, pse,
	OctetStream *	, in,
	OctetStream *	, out,
	AlgId	*	, dig_alg,
	SET_OF_Attr *	, authattrs,
	SET_OF_Attr *	, unauthattrs,
	OctetStream *	, ext_body,
	Boolean		, canon,
	Boolean		, base64,
	int		, cert_no,
	Boolean		, crl

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_enveloped_data SEC_PROTOTYPE_13(
	PSE		, pse,
	OctetStream *	, in,
	OctetStream *	, out,
	AlgId	*	, dig_alg,
	SET_OF_Attr *	, authattrs,
	SET_OF_Attr *	, unauthattrs,
	Key	 *	, key,
	PKList *	, recipients,
	OctetStream *	, ext_body,
	Boolean		, canon,
	Boolean		, base64,
	int		, cert_no,
	Boolean		, crl

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_enveloped_data SEC_PROTOTYPE_7(
	OctetStream *	, in,
	OctetStream *	, out,
	Key	 *	, key,
	PKList *	, recipients,
	OctetStream *	, ext_body,
	Boolean		, canon,
	Boolean		, base64

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_encrypted_data SEC_PROTOTYPE_6(
	OctetStream *	, in,
	OctetStream *	, out,
	Key	 *	, key,
	OctetStream *	, ext_body,
	Boolean		, canon,
	Boolean		, base64

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_digested_data SEC_PROTOTYPE_6(
	OctetStream *	, in,
	OctetStream *	, out,
	AlgId	*	, dig_alg,
	OctetStream *	, ext_body,
	Boolean		, canon,
	Boolean		, base64

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_create_and_add_signer_info SEC_PROTOTYPE_7(
	void	*	, handle,
	PSE		, pse,
	AlgId	*	, dig_alg,
	SET_OF_Attr *	, authattrs,
	SET_OF_Attr *	, unauthattrs,
	int		, cert_no,
	Boolean		, crl

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_data_certs_and_crls SEC_PROTOTYPE_4(
	OctetStream * , stream,
	Boolean , base64,
	ExtendedCertificatesAndCertificates * , certs,
	SET_OF_CRL * , crls
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_data_certs SEC_PROTOTYPE_4(
	OctetStream * , stream,
	Boolean , base64,
	PSE , pse,
	int , cert_no
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7e_signed_data_crls SEC_PROTOTYPE_3(
	OctetStream * , stream,
	Boolean , base64,
	PSE , pse
);









RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_data_init SEC_PROTOTYPE_2(
	void **, handle,
	OctetStream * , stream
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_signed_data_init SEC_PROTOTYPE_2(
	void **, handle,
	OctetStream * , stream
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_enveloped_data_init SEC_PROTOTYPE_2(
	void **, handle,
	OctetStream * , stream
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_signed_enveloped_data_init SEC_PROTOTYPE_2(
	void **, handle,
	OctetStream * , stream
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_digested_data_init SEC_PROTOTYPE_2(
	void **, handle,
	OctetStream * , stream
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_encrypted_data_init SEC_PROTOTYPE_3(
	void **, handle,
	OctetStream * , stream,
	Key	* , key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_verify_digest SEC_PROTOTYPE_5(
	PSE , pse,
	SignerInfo * , info,
	Digests *, digests,
	ExtendedCertificatesAndCertificates *, certs,
	SET_OF_CRL * , crls
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_verify_digest_at_time SEC_PROTOTYPE_6(
	PSE , pse,
	SignerInfo * , info,
	Digests *, digests,
	ExtendedCertificatesAndCertificates *, certs,
	SET_OF_CRL * , crls,
	UTCTime * , vtime
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_data_end SEC_PROTOTYPE_1(
	void **, handle
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_signed_data_end SEC_PROTOTYPE_5(
	void **, handle,
	SignerInfos ** , infos,
	Digests **, digests,
	ExtendedCertificatesAndCertificates **, certs,
	SET_OF_CRL ** , crls
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_signed_enveloped_data_end SEC_PROTOTYPE_5(
	void **, handle,
	SignerInfos ** , infos,
	Digests **, digests,
	ExtendedCertificatesAndCertificates **, certs,
	SET_OF_CRL ** , crls
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_enveloped_data_end SEC_PROTOTYPE_1(
	void **, handle
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_digested_data_end SEC_PROTOTYPE_1(
	void **, handle
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_encrypted_data_end SEC_PROTOTYPE_1(
	void **, handle
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_input SEC_PROTOTYPE_3(
	void *, handle,
	char * , buf,
	sec_int4 , length
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_input_ext SEC_PROTOTYPE_5(
	void *, handle,
	char * , buf,
	sec_int4 , length,
	SET_OF_AlgId *, dig_algs,
	Boolean	, canon
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Digests SEC_PROTOTYPE_1(
	Digests	**	, p
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_eval_content_type SEC_PROTOTYPE_5(
	OctetStream	*	, input,
	ContentTypeId	*	, type,
	Boolean		*	, content,
	ContentTypeId	*	, inner_type,
	Boolean		*	, inner_content

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_data SEC_PROTOTYPE_4(
	OctetStream *, ext_body,
	OctetStream *, in,
	OctetStream *, out,
	Boolean , canon
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_signed_data SEC_PROTOTYPE_8(
	OctetStream *, ext_body,
	OctetStream *, in,
	OctetStream *, out,
	Boolean , canon,
	SignerInfos ** , infos,
	Digests **, digests,
	ExtendedCertificatesAndCertificates **, certs,
	SET_OF_CRL ** , crls
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_signed_enveloped_data SEC_PROTOTYPE_9(
	PSE	 , pse,
	OctetStream *, ext_body,
	OctetStream *, in,
	OctetStream *, out,
	Boolean , canon,
	SignerInfos ** , infos,
	Digests **, digests,
	ExtendedCertificatesAndCertificates **, certs,
	SET_OF_CRL ** , crls
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_enveloped_data SEC_PROTOTYPE_5(
	PSE	 , pse,
	OctetStream *, ext_body,
	OctetStream *, in,
	OctetStream *, out,
	Boolean , canon
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_digested_data SEC_PROTOTYPE_4(
	OctetStream *, ext_body,
	OctetStream *, in,
	OctetStream *, out,
	Boolean , canon
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_encrypted_data SEC_PROTOTYPE_5(
	OctetStream *, ext_body,
	OctetStream *, in,
	OctetStream *, out,
	Boolean , canon,
	Key 	    *, key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_decrypt_content_key_with_key SEC_PROTOTYPE_6(
	Key	*	 , key,
	RecipientInfos *, recp_infos,
	AlgId	* , alg,
	DName	* , issuer,
	SerialNumber	*, serialnumber,
	Key **, content_key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_decrypt_content_key SEC_PROTOTYPE_4(
	PSE	 , pse,
	RecipientInfos *, recp_infos,
	AlgId	* , alg,
	Key **, key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_set_content_key SEC_PROTOTYPE_2(
	void *, handle,
	Key *, key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_get_RecipientInfos SEC_PROTOTYPE_3(
	void *, handle,
	AlgId	** , alg,
	RecipientInfos **, recp_infos
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_decrypt_key SEC_PROTOTYPE_2(
	void *, handle,
	PSE , pse
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_input SEC_PROTOTYPE_3(
	void  *, handle,
	char * , buf,
	sec_int4			, length
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_init SEC_PROTOTYPE_2(
	void **, handle,
	OctetStream * , stream
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_end SEC_PROTOTYPE_1(
	void  *, handle
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f SEC_PROTOTYPE_5(
	OctetStream *	, in,
	OctetStream *	, out,
	PSE		, pse,
	PKList *		, recips,
	Boolean			, add

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_get_RecipientInfos SEC_PROTOTYPE_2(
	void *, handle,
	RecipientInfos ***, recp_infos
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_decrypt_content_key_with_key SEC_PROTOTYPE_5(
	Key	*	 , key,
	RecipientInfos *, recp_infos,
	DName	* , issuer,
	SerialNumber	*, serialnumber,
	Key **, content_key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_decrypt_content_key SEC_PROTOTYPE_3(
	PSE	 , pse,
	RecipientInfos *, recp_infos,
	Key **, key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_decrypt_key SEC_PROTOTYPE_4(
	void *, handle,
	PSE , pse,
	RecipientInfos ***, recp_infos,
	Key ** , key
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_crt_recipient_infos SEC_PROTOTYPE_4(
	PKList *	, recips,
	Key * , datakey,
	RecipientInfos **, recip_infos,
	Boolean , add

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7f_continue SEC_PROTOTYPE_1(
	void  *, handle
);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_any_init SEC_PROTOTYPE_1(
	void **, handle
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_any_end SEC_PROTOTYPE_11(
	void **, handle,
	ContentTypeId	*	, type,
	Boolean		*	, content,
	ContentTypeId	*	, inner_type,
	Boolean		*	, inner_content,
	SignerInfos ** , infos,
	ExtendedCertificatesAndCertificates **, certs,
	SET_OF_CRL ** , crls,
	RecipientInfos	  **, recp_infos,
	AlgId			**, enc_alg,
	SET_OF_AlgId **, dig_algs
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV p7d_any SEC_PROTOTYPE_11(
	OctetStream		*, in,
	ContentTypeId	*	, type,
	Boolean			*	, content,
	ContentTypeId	*	, inner_type,
	Boolean			*	, inner_content,
	SignerInfos		** , infos,
	ExtendedCertificatesAndCertificates **, certs,
	SET_OF_CRL		** , crls,
	RecipientInfos	**, recp_infos,
	AlgId			**, enc_alg,
	SET_OF_AlgId	**, dig_algs
);
Digests SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_Digests SEC_PROTOTYPE_1(Digests* , pDigests);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV blind_sign_blinded_hash SEC_PROTOTYPE_3(
    PSE,  pse,
    OctetString * ,blinded_hash,
    OctetString ** ,signed_blinded_hash
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV blind_create_blinded_hash SEC_PROTOTYPE_5(
    OctetString * , data,
    Certificate * , certificate,
    OctetString **, r,
    OctetString **, blinded_hash,
    OctetString **, hash_value
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV blind_create_p7_from_blinded_hash SEC_PROTOTYPE_6(
    OctetString * ,data,
    OctetString * ,hash_value, 
    Certificate * ,certificate,
    OctetString * ,r,
    OctetString * ,signed_blinded_hash,
    OctetString **,p7m_signature
);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* _PKCS7_ */

