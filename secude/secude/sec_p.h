/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/sec_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#if !defined(SECUDE_SECURE_INCLUDE) || !SECUDE_SECURE_INCLUDE
#error do not include this file, include <secude/secure.h>
#endif


#include <secude/asn1.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern unsigned char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  ASCII2EBCDIC_table[];
extern unsigned char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  EBCDIC2ASCII_table[];

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV secsc_check_sct SEC_PROTOTYPE_5(
	
	int	, sct_id,
	char	 **	, sct,
	Boolean * , card,
	OctetString	 **	, atr,
	char **	, sc_plugin

);

RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_delete_file_or_dir SEC_PROTOTYPE_1(
	
	char *	, path

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_str_ASCII2EBCDIC SEC_PROTOTYPE_2(
	unsigned char *, str,
	int , len
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_str_EBCDIC2ASCII SEC_PROTOTYPE_2(
	unsigned char *, str,
	int , len
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_get_SC_DATA SEC_PROTOTYPE_3(

	char	 	*	, psename,

	SC_DATA  	**	, sc_data,

	int	 		, sct_id

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_need_PIN SEC_PROTOTYPE_1(
	char	 *	, psename
);
PSEtype SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_get_PSEtype SEC_PROTOTYPE_3(
	char	 *	, psename,
	char	**	, filename,
	int	 *	, mpse_selector
);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_release_SCT SEC_PROTOTYPE_1(
	
	int  	, sct_id

);

RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_control SEC_PROTOTYPE_4(
	PSESel * , pse,
	int	, cmd,
	void * , input,
	void ** , output
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_user_profile SEC_PROTOTYPE_2(
	char * , path, char * , attr);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_etc_dir_static SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_etc_dir SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_testkeys_path SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_afdb_path SEC_PROTOTYPE_0();


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_pse_home SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_pse_home_static SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_pse_home_with_vars  SEC_PROTOTYPE_1( char ** , vars);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_alias_path SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_scconf_path SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_get_sctinst_path SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_local_path SEC_PROTOTYPE_1(char *, fname);



RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_parse_psestring SEC_PROTOTYPE_7(
	char	 *	, psename,
	char	 **	, abs_psename,
	char	 **	, sc,
	char	 **	, scparm,
	char	 **	, sct,
	char	 **	, sctparm,
	char	 **	, idx
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_build_psestring SEC_PROTOTYPE_7(
	char	 **	, psename,
	char	 *	, abs_psename,
	char	 *	, sc,
	char	 *	, scparm,
	char	 *	, sct,
	char	 *	, sctparm,
	char	 *	, idx
);

/*
 *	src/secure
 */



#ifdef SCA
/* prototypes from  secure/secsc.c :  */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsc_get_SCTRC SEC_PROTOTYPE_4(

	char	 *	, name,

	char  **	, port,

	char  **	, lib,

	char  **	, lib_parm

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsc_read_SCTRC SEC_PROTOTYPE_1(
 TERMINAL **, sctrc );
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsc_write_SCTRC SEC_PROTOTYPE_1(
 TERMINAL *, sctrc );
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsc_free_SCTRC SEC_PROTOTYPE_1(
 TERMINAL **, sctrc );

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsc_get_SC_DATA SEC_PROTOTYPE_3(

	char	 *	, psename,

	SC_DATA  **	, sc_data,

	int	 	, sct_id

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_get_int_param SEC_PROTOTYPE_3(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    int *       , pResult
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_set_int_param SEC_PROTOTYPE_3(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    int         , value
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_get_int_array_param SEC_PROTOTYPE_4(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    int **      , pResult,
    Boolean     , return_copy
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_set_int_array_param SEC_PROTOTYPE_3(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    int *       , value
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_get_Boolean_param SEC_PROTOTYPE_3(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    Boolean *   , pResult
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_set_Boolean_param SEC_PROTOTYPE_3(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    Boolean     , value
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_get_String_param SEC_PROTOTYPE_4(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    char **     , pResult,
    Boolean     , return_copy
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_set_String_param SEC_PROTOTYPE_3(
    SC_DATA *   , sc_data,
    sec_uint4   , parm_id,
    char *      , value
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_get_CB_param SEC_PROTOTYPE_4(
    SC_DATA *       , sc_data,
    sec_uint4       , parm_id,
    SECUDE_CB_T **  , pcb_func,
    void        **  , pcb_parm
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_SC_DATA_set_CB_param SEC_PROTOTYPE_4(
    SC_DATA *       , sc_data,
    sec_uint4       , parm_id,
    SECUDE_CB_T *   , cb_func,
    void        *   , cb_parm
);

int SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV secsc_main SEC_PROTOTYPE_4(
	char *, psename,
	int , sct_id,
	char 	*	, cmd,
	IO_CB *, io_cb
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_unblock_pin SEC_PROTOTYPE_3(
	
	char	 *	, psename,

	char	 *	, pin,

	SC_DATA  *	, sc_data

);

#endif /* ifdef SCA */


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_chpin SEC_PROTOTYPE_3(
	
	PSESel	 *	, pse_sel,
	
	char	 *	, oldpin,
	
	char	 *	, newpin

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_chpin SEC_PROTOTYPE_3(
	
	PSESel	 *	, pse_sel,
	
	char	 *	, oldpin,
	
	char	 *	, newpin


);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_close SEC_PROTOTYPE_1(
	
	PSESel	 *	, pse_sel

);

extern int DIRMASK;
extern int OBJMASK;

PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  sec_create SEC_PROTOTYPE_4(
	
	char	 *	, psename,
	char	 *	, pin,
	SC_DATA  *	, sc_data,
	Boolean		, onekeypaironly

);
PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  secsw_create SEC_PROTOTYPE_4(
	
	char	 *	, psename,
	char	 *	, pin,
	SC_DATA  *	, sc_data,
	Boolean		, onekeypaironly

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_delete_object SEC_PROTOTYPE_1(
	
	PSESel	 *	, pse_sel

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_delete_object SEC_PROTOTYPE_1(
	
	PSESel	 *	, pse_sel

);

	
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_delete_PSE SEC_PROTOTYPE_3(
	
	char	 *	, psename,

	char	 *	, pin,

	SC_DATA  *	, sc_data

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_delete_object_in_toc SEC_PROTOTYPE_2(
	
	char	 *	, name,
	PSEToc * , toc

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV sec_prepare_PSEInfo_cont SEC_PROTOTYPE_2(
	PSE_Info	* , info,
	PSELocation	  , where
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_parse_PSEInfo_cont SEC_PROTOTYPE_3(
	PSE_Info	* , info,
	OctetString	* , in_ostr,
	PSELocation	  , where
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_delete_PSE SEC_PROTOTYPE_3(
	
	char	 *	, psename,

	char	 *	, pin,

	SC_DATA  *	, sc_data

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_rename SEC_PROTOTYPE_2(
	
	PSESel	 *	, pse_sel,
	
	char	 *	, objname

);

/* prototype from  secure/secure.c : */

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_onekeypaironly SEC_PROTOTYPE_1(

	PSESel *, pse_sel

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_sc_eject SEC_PROTOTYPE_1(
	
	int		, sct_id

);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_parse_OAEPBlock SEC_PROTOTYPE_2(
    AlgId       *   , algid_with_params,
    OctetString *   , EM
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_create_OAEPBlock SEC_PROTOTYPE_3(
	AlgId       *   , algid_with_params,
	OctetString *   , data,
	int	            , emLen
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_PKCS1_gen_mask SEC_PROTOTYPE_3(
	AlgId       *   , mgf_algid,
	OctetString *   , seed,
	unsigned int    , mask_len
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_PKCS1_hash_length SEC_PROTOTYPE_1(
	AlgId       *   , algid_with_params
);
AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_PKCS1_hash_alg SEC_PROTOTYPE_1(
	AlgId       *   , algid_with_params
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_create_PSSBlock SEC_PROTOTYPE_3(
	AlgId       *   , algid_with_params,
	OctetString *   , saltedHash,
	int	            , emLen
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_parse_PSSBlock SEC_PROTOTYPE_3(
    AlgId        *  , algid_with_params,
    OctetString  *  , EM,
    OctetString **  , pSalt
);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_init SEC_PROTOTYPE_2(
	void **	, context,
	 Key *	, key
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_more SEC_PROTOTYPE_3(
	void **	, context,
	 BitString *	, in_bits,
	 OctetString *	, out_octets
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_end SEC_PROTOTYPE_2(
	void **	, context,
	 OctetString *	, out_octets
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_decrypt_init SEC_PROTOTYPE_2(
	void **	, context,
	 Key *	, key
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_decrypt_more SEC_PROTOTYPE_3(
	void **	, context,
	 BitString *	, in_bits,
	 OctetString *	, out_octets
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_decrypt_end SEC_PROTOTYPE_2(
	void **	, context,
	 OctetString *	, out_octets
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_all SEC_PROTOTYPE_3(
	BitString *	, in_bits,
	 OctetString *	, out_octets,
	 Key *	, key
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_crypt_init SEC_PROTOTYPE_9(
	void **	, context,
	Boolean , decrypt,
	AlgEnc	 , algenc,
	BitString *	, key,
	PAD_Func		* , pad,
	AlgMode	 , algmode,
	OctetString * ,iv_ostr,
	int , restr,
	void * , rfu
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_init SEC_PROTOTYPE_2(
	void **	, context,
	 Key *	, key
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_more SEC_PROTOTYPE_3(
	void **	, context,
	 OctetString *	, in_octets,
	 BitString *	, out_bits
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_end SEC_PROTOTYPE_2(
	void **	, context,
	 BitString *	, out_bits
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_all SEC_PROTOTYPE_3(
	OctetString *	, in_octets,
	 BitString *	, out_bits,
	 Key *	, key
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gen_key SEC_PROTOTYPE_2(
	
	Key	 *	, key,
	
	Boolean	  	, replace

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_gen_key SEC_PROTOTYPE_2(
	
	Key	 *	, key,
	
	Boolean	  	, replace

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_key SEC_PROTOTYPE_3(
	
	EncryptedKey	 *	, encrypted_key,
	
	Key		 *	, plain_key,
	
	Key		 *	, encryption_key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_get_key SEC_PROTOTYPE_2(
	
	KeyInfo	 *	, keyinfo,
	
	Key	 *	, key

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  sec_fingerprint SEC_PROTOTYPE_2(
	
	KeyInfo  *	, keyinfo,
	
	int       	, sep

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_hash_init SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	AlgId		 *	, alg_id,
	
	HashInput	 *	, hash_input

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_hash_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_hash_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, hash_result

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_hash_all SEC_PROTOTYPE_4(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result,
	
	AlgId		 *	, alg_id,
	
	HashInput	 *	, hash_input

);

PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  sec_open SEC_PROTOTYPE_3(
	
	char	 *	, pse_name,
	char	 *	, pin,
	SC_DATA  *	, sc_data


);

PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  secsw_open SEC_PROTOTYPE_3(
	
	char	 *	, pse_name,
	char	 *	, pin,
	SC_DATA  *	, sc_data


);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_open_pse_or_extension SEC_PROTOTYPE_1(
	PSESel * , pse_sel
);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_is_in_toc SEC_PROTOTYPE_1(
	
	PSESel	 *	, pse_sel

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_print_toc_to_stderr SEC_PROTOTYPE_1(
	
	PSESel	 *	, pse_sel

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_print_toc SEC_PROTOTYPE_2(
	
	FILE	 *	, ff,
	
	PSESel	 *	, pse_sel

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_read_tocs SEC_PROTOTYPE_3(
	
	PSESel	 *	, pse_sel,
	
	PSEToc	**	, SCtoc,
	
	PSEToc	**	, PSEtoc

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_key SEC_PROTOTYPE_3(
	
	EncryptedKey	 *	, encrypted_key,
	
	Key		 *	, plain_key,
	
	Key		 *	, decryption_key

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_read SEC_PROTOTYPE_2(
	
	PSESel		 *	, pse_sel,
	
	OctetString	 *	, content

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_read_object_from_toc SEC_PROTOTYPE_3(
	
	char		 *	, object,
	PSEToc		 *	, toc,
	
	OctetString	 *	, content

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_read SEC_PROTOTYPE_2(
	
	PSESel		 *	, pse_sel,
	
	OctetString	 *	, content

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_read_PSE SEC_PROTOTYPE_2(
	
	PSESel		 *	, pse_sel,
	
	OctetString	 *	, value

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_write_toc SEC_PROTOTYPE_2(
	
	PSESel	 *	, pse_sel,
	
	PSEToc	 *	, toc

);

PSELocation SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_psetest SEC_PROTOTYPE_2(
	
	char	 *	, pse_name,

	int		, sct_id

);

PSEConfig SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_pse_config SEC_PROTOTYPE_2(
	
	char	 *	, pse_name,

	char	 *	, object

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_sign_init SEC_PROTOTYPE_4(
	
	void		**	, context,
	
	Signature	 *	, signature,
	
	Key		 *	, key,
	
	HashInput	 *	, hash_input

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_sign_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_sign_end SEC_PROTOTYPE_1(
	
	void		**	, context

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_sign_init SEC_PROTOTYPE_4(
	
	void		**	, context,
	
	Signature	 *	, signature,
	
	Key		 *	, key,
	
	HashInput	 *	, hash_input

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_sign_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_sign_end SEC_PROTOTYPE_1(
	
	void		**	, context

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_Digest SEC_PROTOTYPE_5(
	Key		*	, key,
	BitString	*	, signature,
	OctetString	*	, hash_result,
	AlgSpecial		, algspecial,
	AlgId		*	, hash_alg
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_encrypt_Digest SEC_PROTOTYPE_5(
	Key		*	, key,
	BitString	*	, signature,
	OctetString	*	, hash_result,
	AlgSpecial		, algspecial,
	AlgId		*	, hash_alg
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_sign_all SEC_PROTOTYPE_4(
	
	OctetString	 *	, in_octets,
	
	Signature	 *	, signature,
	
	Key		 *	, key,
	
	HashInput	 *	, hash_input

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_string_to_key SEC_PROTOTYPE_2(
	
	char	 *	, pin,
	
	Key	 *	, des_key

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_verify_init SEC_PROTOTYPE_4(
	
	void		**	, context,
	
	Signature	 *	, signature,
	
	Key		 *	, key,
	
	HashInput	 *	, hash_input

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_verify_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_verify_end SEC_PROTOTYPE_1(
	
	void		**	, context

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_Digest SEC_PROTOTYPE_5(
	
	Key		*	, key,
	BitString	*	, signature,
	OctetString	*	, hash_result,
	AlgSpecial	 	, algspecial,
	AlgId		*	, hash_alg

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_verify_all SEC_PROTOTYPE_4(
	
	OctetString	 *	, in_octets,
	
	Signature	 *	, signature,
	
	Key		 *	, key,
	
	HashInput	 *	, hash_input

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_checkSK SEC_PROTOTYPE_2(
	
	Key	 *	, sk,
	
	KeyInfo	 *	, pkinfo

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_checkSK_enc SEC_PROTOTYPE_2(
	
	Key	 *	, sk,
	
	KeyInfo	 *	, pkinfo

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_add_object_to_toc SEC_PROTOTYPE_6(
	
	char		 *	, name,
	PSEToc		 *	, toc,
	OctetString	 *	, content,
	int		 	, id,
	AlgId		 *	, alg,
	int		 	, size

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_add_object_to_toc_old SEC_PROTOTYPE_7(
	
	char		 *	, name,
	PSEToc		 *	, toc,
	OctetString	 *	, content,
	int		 	, id,
	AlgId		 *	, alg,
	int		 	, size,
	OctetString ** , old

);
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_init_PSE_TOC_with_args SEC_PROTOTYPE_10(
	
	PSEToc **	, p_toc,
	char	*	, pin,
	Boolean		, onekeypaironly,
	int		, version,
	int		, comp,
	int		, encr,
	AlgId	*	, encAlg,
	AlgId	*	, micAlg,
	char	*	, extpath,
	char	*	, extpin

);
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_init_PSE_TOC SEC_PROTOTYPE_2(
	
	PSE_Info *	, info,
	Boolean		, onekeypaironly

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_write SEC_PROTOTYPE_2(
	
	PSESel		 *	, pse_sel,
	
	OctetString	 *	, content

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secsw_write SEC_PROTOTYPE_2(
	
	PSESel		 *	, pse_sel,
	
	OctetString	 *	, content

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_write_PSE SEC_PROTOTYPE_2(
	
	PSESel		 *	, pse_sel,
	
	OctetString	 *	, value

);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_pin_check SEC_PROTOTYPE_3(
	
	PSESel	 *	, pse_sel,
	
	char	 *	, obj,
	
	char	 *	, pin

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_keyinfo_from_key SEC_PROTOTYPE_1(
	
	Key	 *	, key

);

#if defined(MAC)
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_unixname SEC_PROTOTYPE_0();
#else
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_unixname SEC_PROTOTYPE_0();
#endif


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV put_keyinfo_according_to_key SEC_PROTOTYPE_2(
	
	KeyInfo	 *	, keyinfo,
	
	Key	 *	, key

);

PSEToc SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  chk_toc SEC_PROTOTYPE_2(
	
	PSESel	 *	, pse_sel,
	
	Boolean	  	, create

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strzfree SEC_PROTOTYPE_1(
	
	char	**	, str

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV strrep SEC_PROTOTYPE_2(
	
	char	**	, str1,
	
	char	 *	, str2

);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV read_dec SEC_PROTOTYPE_4(
         
        char     *      , name,
         
        char     **     , buf,
         
        unsigned int      *      , len,
         
        char     *      , key
 
 
);
 
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV write_enc SEC_PROTOTYPE_5(
        
        char     *      , name,
        
        char     *      , buf,
        
        int             , len,
        
        char     *      , key,
        
        int		, flags
 
);
 
 



int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV inst_pse SEC_PROTOTYPE_7(
	
	int		  	, sct_id,
	
	OctetString	 *	, appl_id,
	
	int		  	, n_des,
	
	int		  	, n_rsa,
	
	char		 *	, pin,
	
	char		 *	, puk,
	
	char		 *	, pse_pin

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV inst_MF SEC_PROTOTYPE_2(
	
	int	  	, sct_id,
	
	Boolean	  	, close

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV close_MF SEC_PROTOTYPE_1(
	
	int		  	, sct_id

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV del_MF SEC_PROTOTYPE_1(
	
	int	  	, sct_id

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV del_pse SEC_PROTOTYPE_3(
	
	int		  	, sct_id,
	
	Boolean		  	, select,
	
	OctetString	 *	, appl_id

);



/* prototypes from  secure/tcos_man.c : */

#ifdef SCA

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV del_TCOSpse SEC_PROTOTYPE_2(
	
	int		  	, sct_id,
	
	OctetString	 *	, appl_id

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV inst_TCOSpse SEC_PROTOTYPE_7(
	
	int		  	, sct_id,
	
	OctetString	 *	, appl_id,
	
	int		  	, n_des,
	
	int		  	, n_rsa,
	
	char		 *	, pin,
	
	char		 *	, puk,
	
	char		 *	, pse_pin

);


#else


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV tcos_man_dummy SEC_PROTOTYPE_0();


#endif   /* SCA */


/* prototypes from  secure/pkos_man.c : */

#ifdef SCA

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV del_PKOSpse SEC_PROTOTYPE_3(
         
        int                     , sct_id,

        Boolean                 , select,

        OctetString      *      , appl_id
 
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV inst_PKOSpse SEC_PROTOTYPE_7(
        
        int                     , sct_id,
        
        OctetString      *      , appl_id,
        
        int                     , n_des,
        
        int                     , n_rsa,
        
        char             *      , pin,
        
        char             *      , puk,
        
        char             *      , pse_pin
 
);


#else


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV pkos_man_dummy SEC_PROTOTYPE_0();


#endif   /* SCA */


/* from  secure/sec_util.c : */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_int2OctetString SEC_PROTOTYPE_1(
	
	int	 	, int_repr

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_KeyInfo SEC_PROTOTYPE_1(
	
	KeyInfo	 *	, pki

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_KeyInfo SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	KeyInfo	 *	, pki

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_PSEToc SEC_PROTOTYPE_3(
	
	FILE	*	, ff,
	
	PSEToc	 *	, toc1,
	
	PSEToc	 *	, toc2

);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_DigestInfo SEC_PROTOTYPE_2(
	
	DigestInfo	 *	, dup_dig,
	
	DigestInfo	 *	, dig

);

DigestInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_DigestInfo SEC_PROTOTYPE_1(
	
	DigestInfo	 *	, dig

);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_Signature SEC_PROTOTYPE_2(
	
	Signature	 *	, dup_sig,
	
	Signature	 *	, sig

);

Signature SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Signature SEC_PROTOTYPE_1(
	
	Signature	 *	, sig

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Key SEC_PROTOTYPE_1(
	
	Key	 *	, key

);
void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PSESel SEC_PROTOTYPE_1(
	
	PSESel	**	, pse_sel

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Key SEC_PROTOTYPE_1(
	
	Key	**	, key

);

Key SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_Key SEC_PROTOTYPE_1(
	
	Key	 *	, key

);

PSESel SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_PSESel SEC_PROTOTYPE_1(
	
	PSESel	 *	, pse_sel

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Signature SEC_PROTOTYPE_1(
	
	Signature	 *	, p

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_Signature SEC_PROTOTYPE_1(
	
	Signature	**	, signature

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_DigestInfo SEC_PROTOTYPE_1(
	
	DigestInfo	 *	, p

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DigestInfo SEC_PROTOTYPE_1(
	
	DigestInfo	**	, digestinfo

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EncryptedKey SEC_PROTOTYPE_1(
	
	EncryptedKey	 *	, enki

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EncryptedKey SEC_PROTOTYPE_1(
	
	EncryptedKey	**	, enki

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PSEToc SEC_PROTOTYPE_1(
	
	PSEToc	 *	, p

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PSEToc SEC_PROTOTYPE_1(
	
	PSEToc	**	, psetoc

);

#ifdef NEW_PSE_STRUCT
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_MPSEFileEntry SEC_PROTOTYPE_1(
	MPSEFileEntry	*	, mpe
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SEQ_OF_MPSEFileEntry SEC_PROTOTYPE_1(
	SEQ_OF_MPSEFileEntry	*	, seq
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_MPSEFile SEC_PROTOTYPE_1(
	MPSEFile	*	, mp
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_MPSEFile SEC_PROTOTYPE_1(
	MPSEFile	**	, mp
);
void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PSEKeyStruct SEC_PROTOTYPE_1(
	PSEKeyStruct	 **	, ks
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PSEKeyStruct SEC_PROTOTYPE_1(
	PSEKeyStruct	 *	, ks
);
void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PSEObjValue SEC_PROTOTYPE_1(
	PSEObjValue	 **	, v
);
void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PSEObj SEC_PROTOTYPE_1(
	PSEObj	 **	, o
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PSEObj SEC_PROTOTYPE_1(
	PSEObj	 *	, o
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SET_OF_PSEObj SEC_PROTOTYPE_1(
	SET_OF_PSEObj	 *	, set
);
#endif

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SC_DATA SEC_PROTOTYPE_1(
	
	SC_DATA *	, sc_data

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_SC_DATA SEC_PROTOTYPE_1(
	
	SC_DATA	**	, sc_data

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_add_error SEC_PROTOTYPE_5(

        int                     , number,

        char             *      , text,

        char             *      , addr,

        Struct_No               , addrtype,

        char             *      , proc

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_last_error SEC_PROTOTYPE_0();

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_free_error SEC_PROTOTYPE_0();

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_add_warning SEC_PROTOTYPE_5(

        int                     , number,

        char             *      , text,

        char             *      , addr,

        Struct_No               , addrtype,

        char             *      , proc

);

#ifdef WIN32

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_fgets_pin SEC_PROTOTYPE_5(
	
	char 		 *	, prompt,
	
	char 		 *	, answ,
	
	int		  	, answ_len,
	
	FILE		 *	, out,
	
	FILE		 *	, in

);

#endif


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_getpass SEC_PROTOTYPE_1(
	
	char *	, output

);

char	 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cat_paths SEC_PROTOTYPE_2(
	
	char	 *	, first,
	
	char	 *	, second

);



int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_EncryptedKey SEC_PROTOTYPE_2(
	
	EncryptedKey	 *	, dup_enki,
	
	EncryptedKey	 *	, enki

);

EncryptedKey SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_EncryptedKey SEC_PROTOTYPE_1(
	
	EncryptedKey	 *	, enki

);

PSEToc SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PSEToc SEC_PROTOTYPE_1(
	
	PSEToc	 *	, pse

);

#ifdef NEW_PSE_STRUCT
MPSEFile SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_MPSEFile SEC_PROTOTYPE_1(
	MPSEFile	 *	, mp
);
PSEKeyStruct SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_PSEKeyStruct SEC_PROTOTYPE_1(
	PSEKeyStruct	 *	, ks
);
PSEObjValue SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_PSEObjValue SEC_PROTOTYPE_1(
	PSEObjValue	 *	, ov
);
PSEObj SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_PSEObj SEC_PROTOTYPE_1(
	PSEObj	 *	, obj
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_read_PSEFile SEC_PROTOTYPE_2(
	char	*	, fname,
	Boolean	*	, encoded_p
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_write_PSEFile SEC_PROTOTYPE_3(
	char		*	, fname,
	OctetString	*	, ostr,
	Boolean			, do_encode
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_update_in_MPSEFile SEC_PROTOTYPE_4(
	OctetString	**	, mpse_str_p, /* IN-OUT */
	int			, selector,
	char		*	, label,
	OctetString	*	, psef_str
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_from_MPSEFile SEC_PROTOTYPE_3(
	OctetString	*	, mpse_str,
	int			, selector,
	char		**	, label_p
);


#endif

struct PSE_Objects SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_PSEObjects SEC_PROTOTYPE_1(
	
	struct PSE_Objects	 *	, pse

);

PSEObject SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_PSEObject SEC_PROTOTYPE_1(
	
	PSEObject	 *	, pse

);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_AlgId SEC_PROTOTYPE_1(
	
	AlgId	 *	, algid

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_AlgId SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV d2_AlgId SEC_PROTOTYPE_2(
	
	OctetString	 *	, asn1_string,
	
	AlgId		 *	, algid

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_KeyInfo SEC_PROTOTYPE_1(
	
	KeyInfo	 *	, ki

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_KeyInfo SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV d2_KeyInfo SEC_PROTOTYPE_2(
	
	OctetString	 *	, asn1_string,
	
	KeyInfo		 *	, ki

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_EncryptedKey SEC_PROTOTYPE_1(
	
	EncryptedKey	 *	, enki

);

EncryptedKey SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_EncryptedKey SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV d2_EncryptedKey SEC_PROTOTYPE_2(
	
	OctetString	 *	, asn1_string,
	
	EncryptedKey	 *	, enki

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Signature SEC_PROTOTYPE_1(
	
	Signature	 *	, sig

);

Signature SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_Signature SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV d2_Signature SEC_PROTOTYPE_2(
	
	OctetString	 *	, asn1_string,
	
	Signature	 *	, sig

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_KeyBits SEC_PROTOTYPE_1(
	
	KeyBits	 *	, kb

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV e2_KeyBits SEC_PROTOTYPE_2(
	
	KeyBits		 *	, kb,
	
	BitString	 *	, bstr

);

KeyBits SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_KeyBits SEC_PROTOTYPE_1(
	
	BitString	 *	, asn1_bstr

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PSEToc SEC_PROTOTYPE_1(
	
	PSEToc	 *	, toc

);

PSEToc SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PSEToc SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

#ifdef NEW_PSE_STRUCT
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PSEFile SEC_PROTOTYPE_1(
	PSEFile	 *	, toc
);
PSEFile SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PSEFile SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_MPSEFile SEC_PROTOTYPE_1(
	MPSEFile	 *	, mpse
);
MPSEFile SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_MPSEFile SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
#if 0
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PSEFile_v1 SEC_PROTOTYPE_1(
	PSEFile	 *	, toc
);
#endif
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PSECont SEC_PROTOTYPE_1(
	PSECont	 *	, toc
);
PSECont SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PSECont SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV d2_PSECont SEC_PROTOTYPE_2(
	OctetString	 *	, asn1_string,
	PSEFile		 *	, pse
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_CmpPSECont SEC_PROTOTYPE_1(
	CmpPSECont	 *	, toc
);
CmpPSECont SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_CmpPSECont SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV d2_CmpPSECont SEC_PROTOTYPE_2(
	OctetString	 *	, asn1_string,
	PSEFile		 *	, pse
);
#endif

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PSEObject SEC_PROTOTYPE_2(
	
	ObjId		 *	, objectType,
	
	OctetString	 *	, objectValue

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PSEObject SEC_PROTOTYPE_2(
	
	ObjId		 *	, objectType,
	
	OctetString	 *	, asn1_string

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_integer SEC_PROTOTYPE_1(
	
	OctetString	 *	, ostr

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_integer SEC_PROTOTYPE_1(
	
	BitString	 *	, asn1_bstr

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Long SEC_PROTOTYPE_1(
	
	OctetString	 *	, ostr

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_Long SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_bstr

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_OctetString SEC_PROTOTYPE_1(
	
	OctetString	 *	, ostr

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_OctetString SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_BitString SEC_PROTOTYPE_1(
	
	BitString	 *	, bstr

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_BitString SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

/* from secure/sec_ed.c : */
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_DigestInfo SEC_PROTOTYPE_1(
	
	DigestInfo	 *	, di

);

DigestInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_DigestInfo SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV d2_DigestInfo SEC_PROTOTYPE_2(
	
	OctetString	 *	, asn1_string,
	
	DigestInfo	 *	, di

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Boolean SEC_PROTOTYPE_1(
	Boolean	* , infostruct
);
Boolean SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_Boolean SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_Integer SEC_PROTOTYPE_1(
	int	* , infostruct
);
int SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_Integer SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_integer SEC_PROTOTYPE_1(
	OctetString	 *	, ostr
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_integer SEC_PROTOTYPE_1(
	BitString	 *	, asn1_bstr
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_PrintableString SEC_PROTOTYPE_1(
	char	*	, infostruct
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_PrintableString SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_T61String SEC_PROTOTYPE_1(
	char	*	, infostruct
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_T61String SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_IA5String SEC_PROTOTYPE_1(
	char	*	, infostruct
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_IA5String SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_UTCTime SEC_PROTOTYPE_1(
	char	*	, infostruct
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_UTCTime SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GeneralTime SEC_PROTOTYPE_1(
	char	*	, infostruct
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GeneralTime SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_GRAPHICString SEC_PROTOTYPE_1(
	
	char	 *	, string

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_GRAPHICString SEC_PROTOTYPE_1(
	
	OctetString	 *	, asn1_string

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_KeyInfo SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	KeyInfo	 *	, pki

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_string SEC_PROTOTYPE_2(
	char		 *	, string,
	
	char	 	*	, str

);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_simple_DERcode SEC_PROTOTYPE_2(
	char		 *	, string,
	
	OctetString	 *	, der

);

/*
 *      Object Identifiers of PSE Objects (extern: af-init.c)
 */

/* for v3 certificates: */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX policies_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX RDNAlias_OID;

extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX AuthCert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SignCert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX EncCert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX Cert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SignCSet_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX EncCSet_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CSet_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SignSK_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX AuthSK_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DecSKnew_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DecSKold_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SKnew_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SKold_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX FCPath_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX PKRoot_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX PKList_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX EKList_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX PCAList_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CrossCSet_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CrlSet_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX Name_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SerialNumber_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX EDBKey_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX Random_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX AliasList_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX QuipuPWD_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DHparam_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DSAcommon_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DHprivate_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DHkey_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX KeyInfo_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX BitString_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX ToBeSigned_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX RSA_SK_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX RSA_PK_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DSA_SK_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DSA_PK_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DES_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX DES3_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX IDEA_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX Uid_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TelesecCert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TeleTrustCert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX X509UserCert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX X509CACert_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX TelesecCertList_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX CRLNumber_OID;

/* for EC */
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  prime_field_OID;
extern ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX  characteristic_two_field_OID;
 
/* for v3 certificates: */
extern ObjId SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX policies_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX RDNAlias_oid;

extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  AuthCert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  SignCert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  EncCert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  Cert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  SignCSet_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  EncCSet_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  CSet_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  SignSK_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  AuthSK_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DecSKnew_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DecSKold_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  SKnew_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  SKold_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  FCPath_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PKRoot_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PKList_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  EKList_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  PCAList_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  CrossCSet_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  CrlSet_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  Name_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  SerialNumber_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  EDBKey_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  Random_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  AliasList_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  QuipuPWD_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DHparam_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DSAcommon_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DHprivate_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DHkey_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  KeyInfo_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  BitString_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  ToBeSigned_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  RSA_SK_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  RSA_PK_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DSA_SK_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DSA_PK_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DES_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  DES3_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  IDEA_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  Uid_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  TelesecCert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  TeleTrustCert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  X509UserCert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  X509CACert_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  TelesecCertList_oid;
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  CRLNumber_oid;



/*
 * from secure.h : 
 */
extern Boolean SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  sec_time;
extern Boolean SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  sec_sca;

/*
 * from secsc.h : 
 */
 

extern Boolean SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   SC_verify, SC_encrypt;

/*
 *  External initialization of SC_timer:
 *
  int           SC_timer =      SC_WAITTIME;
 */

extern int SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   SC_timer;
				/* During this time interval (in seconds) the 	*/
				/* SCT accepts the insertion of an SC.		*/
				/* The timer starts after the user has been 	*/
				/* requested to insert the SC.			*/
				/* If the variable is set to 0, no timer is     */
				/* specified.					*/
 



/* from seed.c: */

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  e_ObjId SEC_PROTOTYPE_1(
	ObjId	*	, infostruct
);
ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  d_ObjId SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);

/* from seasn1.c: */
ASN1_en_de_PROTO(EncPSECont)
ASN1_en_de_PROTO(SigPSECont)
ASN1_en_de_PROTO(MPSEFileEntry)

ASN1_en_de_PROTO(PSEToc)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSEToc;
ASN1_en_de_PROTO(PSEObjects)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSEObjects;
ASN1_en_de_PROTO(PSEObject)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSEObject;

#ifdef USE_COMPONENTS_OF_FOR_OLD_TYPES
typedef Signature COMPONENTS_OF_Signature;
ASN1_en_de_PROTO(COMPONENTS_OF_Signature)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_COMPONENTS_OF_Signature;
#endif /* USE_COMPONENTS_OF_FOR_OLD_TYPES */

ASN1_en_de_PROTO(Signature)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Signature;
ASN1_en_de_PROTO(DigestInfo)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DigestInfo;
ASN1_en_de_PROTO(EncryptedKey)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_EncryptedKey;
ASN1_en_de_PROTO(RSAPrivateKey)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_RSAPrivateKey;

ASN1_en_de_PROTO(TIMEType)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_TIMEType;


#ifdef NEW_PSE_STRUCT
ASN1_en_de_PROTO(PSEKeyStruct)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSEKeyStruct;
ASN1_en_de_PROTO(PSEObjValue)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSEObjValue;
ASN1_en_de_PROTO(PSEObj)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSEObj;
#define encode_SET_OF_PSEObj ASN1e_gen_List
#define decode_SET_OF_PSEObj ASN1d_gen_List
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SET_OF_PSEObj;
ASN1_en_de_PROTO(PSECont)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSECont;
ASN1_en_de_PROTO(CmpPSECont)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_CmpPSECont;
ASN1_en_de_PROTO(PSEFile)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PSEFile;
ASN1_en_de_PROTO(MPSEFile)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_MPSEFile;

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_get_encPin_from_PSEFile SEC_PROTOTYPE_2(
	OctetString	 * , from,
	OctetString	** , into
);

Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_use_PSEFile SEC_PROTOTYPE_0();

#endif

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_same_object_time SEC_PROTOTYPE_2(
	UTCTime		* , base,
	UTCTime		* , other
);

/*RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_compress_zlib09 SEC_PROTOTYPE_2(
	OctetString * , dec,
	OctetString * , enc
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_decompress_zlib09 SEC_PROTOTYPE_2(
	OctetString * , enc,
	OctetString * , dec
);*/

#ifdef SAPSECULIB
extern OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SAPdefault_ostr;
#endif /* SAPSECULIB */

#ifdef SEC_USE_AUTHENTICODE
extern OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX SECdefault_ostr;
#endif /* SEC_USE_AUTHENTICODE */


#ifdef ENABLE_GENERIC_CIPHER_MODES

/* WORK IN PROGRESS... */

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_crypt_init_generic SEC_PROTOTYPE_9(
    void        **  , context,
    Boolean         , decrypt,
    AlgEnc          , algenc,
    BitString   *   , key,
    PAD_Func    *   , pad,
    int             , algmode,
    OctetString *   , iv_ostr,
    int             , restr,
    void        *   , rfu
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_crypt_free_generic SEC_PROTOTYPE_1(
    void        **  , context
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_more_generic SEC_PROTOTYPE_3(
	void		**	, context,
	OctetString	 *	, in,
	BitString	 *	, out
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_encrypt_end_generic SEC_PROTOTYPE_2(
    void        **	, context,
    BitString   *	, out_bits
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_more_generic SEC_PROTOTYPE_3(
    void         **	, context,
    BitString 	 *	, in,
    OctetString  *	, out
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_decrypt_end_generic SEC_PROTOTYPE_2(
    void        **	, context,
    OctetString  *	, out
);

/* WORK IN PROGRESS... */

#endif /* ENABLE_GENERIC_CIPHER_MODES */

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



