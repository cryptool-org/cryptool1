/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

/*-----------------------------------------------------------------------*/
/*  INCLUDE FILE  pkcs7.h  (PKCS #7 Standard)                                */
/*  Definition of structures and types for new PKCS #7 API              */
/*-----------------------------------------------------------------------*/
#ifndef _PKCS7_
#define _PKCS7_

#include "pkcs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define DEF_DIGEST_ALG sha1
#define DEF_DATAENCR_ALG desCBC
#define PKCS7_READ_BUF_LEN MAX_STACK_ARRAY_LEN

typedef SET_OF(void) SET_OF_void;
typedef struct Digests Digests;
struct Digests {
	AlgId *alg;
	void  *ctx;
	OctetString dig;
	Digests *next;
};
#define TAG_END 0
#define TAG_OSTR 4
#define TAG_SEQ 0x10
#define TAG_SET 0x11
#define TAG_EXPL 0x80
#define TAG_CONSTR 0x20

typedef struct PKCS7_PRS PKCS7_PRS;

typedef sec_int4  	( SEC_API_CALLING_CONV ADD_FUNC2 ) 		SEC_PROTOTYPE_3( PKCS7_PRS * , handle, char * , buf, sec_int4 , len );
typedef sec_int4  	( SEC_API_CALLING_CONV ADD_FUNC ) 		SEC_PROTOTYPE_3( void * , handle, char * , buf, sec_int4 , len );
typedef sec_int4  	( SEC_API_CALLING_CONV END_FUNC ) 		SEC_PROTOTYPE_1( void * , handle);


typedef struct {
	ContentTypeId				 id;
	OctetStream 				*stream;
	sec_int4				 input_length;
	sec_int4				 length;
	SET_OF_AlgId 				*dig_algs;
	SET_OF_AlgId 				 def_dig_algs;
	SET_OF_CRL 				*crls;
	ExtendedCertificatesAndCertificates 	*certs;
	Digests 				*digs;
	Key	 				*key;
	RecipientInfos 				*recp_infos;
	void	 				*encr_ctx;
	SignerInfos 				*infos;
	OctetStream 				*ext_body;
	Boolean					 canon;
	Boolean					 base64;
	char 					*enc_buf;
	sec_int4				 enc_buf_len;
	char 					 out_cache[100];
	sec_int4				 out_cache_len;
	char 					 in_cache[100];
	sec_int4				 in_cache_len;
} PKCS7_CRT;

typedef enum { FWD_START, FWD_HAVE_TYPE, FWD_HAVE_RECIPS, FWD_ADDED_RECIPS, FWD_WROTE_RECIPS, FWD_NEED_NULL, FWD_FINISHED} FWD_STATES;
typedef struct {
	ContentTypeId			 id;
	FWD_STATES				 state;
	int						 action;
	OctetString				 buf;
	sec_int4				 buf_alloc_len;
	Boolean					 decode_null_needed_info;
	Boolean					 decode_null_needed_expl_cont;
	Boolean					 decode_null_needed_cont;
	PKCS7_CRT				 hdl;
	
	RecipientInfos 			*recp_infos;

} PKCS7_FWD;

typedef enum { PS_START, PS_PARSE_OSTR_CONTENT, PS_PARSE_OSTR_BLOCKS, PS_END_OF_INNER_CI} PARSE_STATES;

struct PKCS7_PRS {
	ContentTypeId	 id;
	OctetStream 	*stream;
	OctetString	 buf;
	sec_int4	 buf_alloc_len;
	Digests 	*digs;
	SignerInfos 	*infos;
	PARSE_STATES	 state;
	int		 rem_len_of_ci;
	Boolean		 decode_null_needed_info;
	Boolean		 decode_null_needed_expl_cont;
	Boolean		 decode_null_needed_cont;
	Boolean		 decode_null_needed_inner_info;
	Boolean		 decode_null_needed_inner_expl_cont;
	Boolean		 decode_null_needed_inner_cont;
	Boolean		 decode_null_needed_encr_info;
	Boolean		 decode_null_needed_encr_cont;
	sec_int4	 cont_length;
	char 		 in_cache[100];
	sec_int4	 in_cache_len;
	AlgId		*decr_alg;
	void		*decr_ctx;
	char 		*enc_buf;
	sec_int4	 enc_buf_len;
	RecipientInfos	*recp_infos;
	Key			*key;
	char		 b64cache[70];
	ADD_FUNC2	*b64;

	ContentTypeId type;
	Boolean		 content;
	ContentTypeId inner_type;
	Boolean		 inner_content;
	ExtendedCertificatesAndCertificates *certs;
	SET_OF_CRL	*crls;
	SET_OF_AlgId *dig_algs;
	Boolean		 found;
} ;


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

