/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/pem_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#if !defined(SECUDE_PEM_INCLUDE) || !SECUDE_PEM_INCLUDE
#error do not include this file, include <secude/pem.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 *	src/pem
 */


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV BitStringtorfc64 SEC_PROTOTYPE_2(
	
	BitString	 *	, bstr,
	
	int		  	, ind
	
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV OctetStringtorfc64 SEC_PROTOTYPE_2(
	
	OctetString	 *	, ostr,
	
	int		  	, ind
	
);

Key SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pem_get_decryption_key SEC_PROTOTYPE_2(
	
	PSE    , pse_handle,
	
	PemMessageLocal  *	, local

);

DataStore SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_prepend_dash_ SEC_PROTOTYPE_1(
	
	DataStore	 *	, store

);

DataStore  SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_strip_dash_ SEC_PROTOTYPE_1(
	
	DataStore	 *	, store

);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_Local2Clear SEC_PROTOTYPE_2(
	
	PemMessageLocal	 *	, local,
	
	Boolean		  	, insert_boundaries

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  pem_stream_Local2Clear SEC_PROTOTYPE_3(
	OctetStream *		, stream,
	PemMessageLocal	 *	, local,
	
	Boolean		  	, insert_boundaries

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  pem_stream_LocalSet2Clear SEC_PROTOTYPE_3(
	OctetStream *		, stream,
	
	SET_OF_PemMessageLocal	 *	, local_mess,
	
	Boolean			  	, insert_boundaries

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_LocalSet2Clear SEC_PROTOTYPE_2(
	
	SET_OF_PemMessageLocal	 *	, local_mess,
	
	Boolean			  	, insert_boundaries

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  pem_stream_mic_clear_bodys SEC_PROTOTYPE_2(
	OctetStream *		, stream,
	
	SET_OF_PemMessageLocal	 *	, local_mess

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_mic_clear_bodys SEC_PROTOTYPE_1(
	
	SET_OF_PemMessageLocal	 *	, local_mess

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_build_header SEC_PROTOTYPE_2(
	OctetString      *      , res_ostr,
	PemHeaderCanon	 *	, header
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  pem_stream_build_one SEC_PROTOTYPE_2(
	OctetStream *		, stream,
	
	PemMessageCanon	 *	, message

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  pem_stream_build SEC_PROTOTYPE_2(
	OctetStream *		, stream,
	
	SET_OF_PemMessageCanon	 *	, canon_mess

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_build_one SEC_PROTOTYPE_1(
	
	PemMessageCanon	 *	, message

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_build SEC_PROTOTYPE_1(
	
	SET_OF_PemMessageCanon	 *	, canon_mess

);

int SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_proctypes SEC_PROTOTYPE_1(
	
	SET_OF_PemMessageLocal	 *	, local

);


PemMessageCanon SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_Local2Canon SEC_PROTOTYPE_1(
	
	PemMessageLocal	 *	, local

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_Canon2Local SEC_PROTOTYPE_1(
	
	PemMessageCanon	 *	, canon

);

SET_OF_PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_CanonSet2LocalSet SEC_PROTOTYPE_1(
	
	SET_OF_PemMessageCanon	 *	, canon

);

SET_OF_PemMessageCanon SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_LocalSet2CanonSet SEC_PROTOTYPE_1(
	
	SET_OF_PemMessageLocal	 *	, local

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PemMessageLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	PemMessageLocal	 *	, local

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PemDekLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	PemDekLocal	 *	, dek

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PemRecLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	PemRecLocal	 *	, rec

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PemMicLocal SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	PemMicLocal	 *	, mic

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_PemHeaderLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	char		 *	, string,
	
	PemHeaderLocal	 *	, hd

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PemMessageLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE		 *	, ff,
	
	PemMessageLocal	 *	, local

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PemDekLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE		 *	, ff,
	
	PemDekLocal	 *	, dek

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PemRecLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE		 *	, ff,
	
	PemRecLocal	 *	, rec

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PemMicLocal SEC_PROTOTYPE_2(
	
	FILE		 *	, ff,
	
	PemMicLocal	 *	, mic

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PemHeaderLocal SEC_PROTOTYPE_3(
        PSE ,  pse_handle,
	
	FILE		 *	, ff,
	
	PemHeaderLocal	 *	, hd

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PemMessageLocal SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PemMessageLocal	 *	, local

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PemDekLocal SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PemDekLocal	 *	, dek

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PemRecLocal SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PemRecLocal	 *	, rec

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PemMicLocal SEC_PROTOTYPE_1(
	
	PemMicLocal	 *	, mic

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_PemHeaderLocal SEC_PROTOTYPE_2(
        PSE ,  pse_handle,
	
	PemHeaderLocal	 *	, hd

);


SET_OF_PemMessageCanon SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_stream_parse SEC_PROTOTYPE_1(
	
	OctetStream	 *	, text

);
SET_OF_PemMessageCanon SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_parse SEC_PROTOTYPE_1(
	
	OctetString	 *	, text

);



RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pem_fill_Certificate SEC_PROTOTYPE_3(
	
	PSE    , pse_handle,
	
	KeyType		  	, type,
	
	Certificate	 *	, certificate

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pem_look_for_Certificate SEC_PROTOTYPE_3(
	
	PSE    , pse_handle,
	
	KeyType		  	, type,
	
	Certificate	 *	, certificate

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pem_accept_certification_reply SEC_PROTOTYPE_3(
	
	PSE    , pse_handle,
	
	PemMessageLocal	 *	, local,
	
	KeyType		, key_type

);

/* prototypes for pem_cadb_store_crlset() and pem_pse_store_crlset() moved to af_p.h */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_reply_crl_request SEC_PROTOTYPE_2(
	
	PSE    , pse_handle,
	
	PemMessageLocal	 *	, local_mess

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  pem_stream_reply_crl_request SEC_PROTOTYPE_3(
	OctetStream *, stream,
	
	PSE    , pse_handle,
	
	PemMessageLocal	 *	, local_mess

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pem_certify SEC_PROTOTYPE_4(
	PSE    , pse_handle,
	
	PemMessageLocal	 *	, local_mess,
	
	Validity	 *	, validity,
	
	DName		 *	, name

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_validate SEC_PROTOTYPE_2(
	
	PSE    , pse_handle,
	
	PemMessageLocal	 *	, local_mess

);

SET_OF_PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_validateSet SEC_PROTOTYPE_2(
	
	PSE			  	, pse_handle,
	
	SET_OF_PemMessageLocal	 *	, message

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_reply_crl_requestSet SEC_PROTOTYPE_2(
	
	PSE			  	, pse_handle,
	
	SET_OF_PemMessageLocal	 *	, local_message

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV  pem_stream_reply_crl_requestSet SEC_PROTOTYPE_3(
	OctetStream *, stream,
	
	PSE    , pse_handle,
	
	SET_OF_PemMessageLocal	 *	, local_mess

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_crl SEC_PROTOTYPE_2(
	
	PSE    , pse_handle,
	
	SET_OF_NAME	 *	, issuers

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_crl_rr SEC_PROTOTYPE_2(
	
	PSE    , pse_handle,
	
	SET_OF_NAME	 *	, issuers

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_enhance SEC_PROTOTYPE_10(
	
	PSE    			, pse_handle,
	
	PEM_Proc_Types	  	, proc_type,
	
	OctetString	 *	, text,
	
	int		  	, no_of_certs,
	
	SET_OF_NAME	 *	, recipients,
	
	MISSING_RECIPIENT_KEY 	, mrk,
	
	Boolean			, verify_cert,
	
	AlgId		*	, sig_alg,
	
	AlgId		*	, enc_alg,
	
	AlgId		*	, dek_enc_alg

);
PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_stream_enhance SEC_PROTOTYPE_12(
	
	PSE    			, pse_handle,
	
	PEM_Proc_Types	  	, proc_type,
	
	OctetStream	 *	, text,
	
	int		  	, no_of_certs,
	
	SET_OF_NAME	 *	, recipients,
	
	MISSING_RECIPIENT_KEY 	, mrk,
	
	Boolean			, verify_cert,
	
	AlgId		*	, sig_alg,
	
	AlgId		*	, enc_alg,
	
	AlgId		*	, dek_enc_alg,
	
	char		*	, ext_body_file_name,
	
	OctetStream	*	, ext_body

);
PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pem_stream_enhance_PKL SEC_PROTOTYPE_10(
	PSE    , pse_handle,
	PEM_Proc_Types	  	, proc_type,
	OctetStream	 *	, text,
	int		  	, no_of_certs,
	PKList		*	, recip_certs,
	AlgId		*	, sig_alg,
	AlgId		*	, enc_alg,
	AlgId		*	, dek_enc_alg,
	char		*	, ext_body_file_name,
	OctetStream	*	, ext_body

);
SET_OF_PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_stream_parse_mail_header SEC_PROTOTYPE_2(
	
	OctetStream	 *	, text,
	
	SET_OF_Name	 **	, recipients

);

SET_OF_PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pem_certification_request SEC_PROTOTYPE_2(
	
	PSE			, pse_handle,
	AlgId		*	, sig_alg
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pem_check_name SEC_PROTOTYPE_2(
	
	PSE	  	, pse_handle,
	
	NAME	 *	, name

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_forward SEC_PROTOTYPE_9(
	PSE			  	, pse_handle,
	PemMessageLocal	 	 *	, message,
	PEM_Proc_Types	 	  	, proc_type,
	SET_OF_NAME		 *	, recipients,
	MISSING_RECIPIENT_KEY 		, mrk,
	Boolean				, verify_cert,
	AlgId			*	, enc_alg,
	AlgId			*	, dek_enc_alg,
	char			*	, ext_body
);
PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pem_forward_PKL SEC_PROTOTYPE_8(
	PSE			  	, pse_handle,
	PemMessageLocal	 	 *	, message,
	PEM_Proc_Types	 	  	, proc_type,
	PKList			*	, recip_certs,
	Boolean				, append_recip_certs,
	AlgId			*	, enc_alg,
	AlgId			*	, dek_enc_alg,
	char			*	, ext_body
);
SET_OF_PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV pem_forwardSet_PKL SEC_PROTOTYPE_8(
	PSE			  	, pse_handle,
	SET_OF_PemMessageLocal	 *	, message,
	PEM_Proc_Types	 	  	, proc_type,
	PKList			*	, recip_certs,
	Boolean				, append_recip_certs,
	AlgId			*	, enc_alg,
	AlgId			*	, dek_enc_alg,
	char			*	, ext_body
);

SET_OF_PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_forwardSet SEC_PROTOTYPE_9(
	PSE			  	, pse_handle,
	SET_OF_PemMessageLocal	 *	, message,
	PEM_Proc_Types	 	  	, proc_type,
	SET_OF_NAME		 *	, recipients,
	MISSING_RECIPIENT_KEY 		, mrk,
	Boolean				, verify_cert,
	AlgId			*	, enc_alg,
	AlgId			*	, dek_enc_alg,
	char			*	, ext_body
);

SET_OF_Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  pem_scan822hdr SEC_PROTOTYPE_1(
	
	char	 *	, buffer

);



SET_OF_PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_PemMessageLocal SEC_PROTOTYPE_1(
	
	SET_OF_PemMessageLocal	 *	, old

);

PemHeaderLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PemHeaderLocal SEC_PROTOTYPE_1(
	
	PemHeaderLocal	 *	, old

);

SET_OF_PemRecLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_SET_OF_PemRecLocal SEC_PROTOTYPE_1(
	
	SET_OF_PemRecLocal	 *	, old

);

PemMessageLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PemMessageLocal SEC_PROTOTYPE_1(
	
	PemMessageLocal	 *	, old

);

PemDekLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PemDekLocal SEC_PROTOTYPE_1(
	
	PemDekLocal	 *	, old

);

PemRecLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PemRecLocal SEC_PROTOTYPE_1(
	
	PemRecLocal	 *	, old

);

PemMicLocal SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PemMicLocal SEC_PROTOTYPE_1(
	
	PemMicLocal	 *	, old

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_PemMessageCanon SEC_PROTOTYPE_1( 

SET_OF_PemMessageCanon	**,    obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemMessageCanon SEC_PROTOTYPE_1(
	
	PemMessageCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemHeaderCanon SEC_PROTOTYPE_1(
	
	PemHeaderCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemDekCanon SEC_PROTOTYPE_1(
	
	PemDekCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_PemRecCanon SEC_PROTOTYPE_1(
	
	SET_OF_PemRecCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_PemCrlCanon SEC_PROTOTYPE_1(
	
	SET_OF_PemCrlCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemRecCanon SEC_PROTOTYPE_1(
	
	PemRecCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemOriginatorCanon SEC_PROTOTYPE_1(
	
	PemOriginatorCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemMicCanon SEC_PROTOTYPE_1(
	
	PemMicCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemCrlCanon SEC_PROTOTYPE_1(
	
	PemCrlCanon	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemHeaderLocal SEC_PROTOTYPE_1(
	
	PemHeaderLocal	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemDekLocal SEC_PROTOTYPE_1(
	
	PemDekLocal	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemMicLocal SEC_PROTOTYPE_1(
	
	PemMicLocal	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_PemRecLocal SEC_PROTOTYPE_1(
	
	SET_OF_PemRecLocal	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SET_OF_PemMessageLocal SEC_PROTOTYPE_1(
	
	SET_OF_PemMessageLocal	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemMessageLocal SEC_PROTOTYPE_1(
	
	PemMessageLocal	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PemRecLocal SEC_PROTOTYPE_1(
	
	PemRecLocal	**	, obj

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_int_array SEC_PROTOTYPE_1(
	int	**	, arr
);



SET_OF_Name SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alloc_SET_OF_Name SEC_PROTOTYPE_0();

SET_OF_NAME SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alloc_SET_OF_NAME SEC_PROTOTYPE_0();

SET_OF_PemMessageLocal 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alloc_SET_OF_PemMessageLocal SEC_PROTOTYPE_0();

PemMessageLocal 
SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alloc_PemMessageLocal SEC_PROTOTYPE_0();

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alloc_OctetString SEC_PROTOTYPE_0();

NAME SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_alloc_NAME SEC_PROTOTYPE_0();


/*
 *   externals
 */
extern struct SKW SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  content_domain[];  /* valid content domains            */ 
extern struct SKW SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  proc_type_v[];     /* valid Proc-Type values           */ 
extern struct SKW SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  proc_type_t[];     /* valid Proc-Type types            */ 
extern struct SKW SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  rXH_kwl[];         /* header field specifiers          */ 

extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PEM_Boundary_Begin[];  /* PEM Boundary line Pre-EB         */ 
extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PEM_Boundary_End[];    /* PEM Boundary line Post-EB        */ 
extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PEM_Boundary_Com[];    /* equal portion of boundary line   */ 
extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PEM_Boundary_BB[];     /* begin portion of boundary begin line*/
extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PEM_Boundary_EB[];     /* begin portion of boundary end line  */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV set_pem_verbose_level SEC_PROTOTYPE_1(
	
	int , level

);
extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  pem_verbose_level;




#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



