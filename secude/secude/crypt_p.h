/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/crypt_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#if !defined(SECUDE_CRYPT_INCLUDE) || !SECUDE_CRYPT_INCLUDE
#error do not include this file, include <secude/crypt.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_check_ticket  SEC_PROTOTYPE_1(
	char ** , rcIdOrError
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_initialize_no_default SEC_PROTOTYPE_1(void * , unused);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_initialize SEC_PROTOTYPE_1(	void * , unused);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_finalize SEC_PROTOTYPE_0();
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_set_mutex_functions_Application SEC_PROTOTYPE_1(SECUDE_Mutex_Functions *, functions);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_set_mutex_functions_PTHREADS SEC_PROTOTYPE_0();
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_set_mutex_functions_WIN32 SEC_PROTOTYPE_0();
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_set_mutex_functions_TEST SEC_PROTOTYPE_0();
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_create_mutex SEC_PROTOTYPE_2(char *,modul, char *,resource);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_destroy_mutex SEC_PROTOTYPE_2(char *,modul, char *,resource);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_destroy_mutex_all SEC_PROTOTYPE_0();
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_lock_mutex SEC_PROTOTYPE_2(char *,modul, char *,resource);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_unlock_mutex SEC_PROTOTYPE_2(char *,modul, char *,resource);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_get_API SEC_PROTOTYPE_3(
	char *,module, 
	DLL_TYPE ,type, 
	void **, API);
/*RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_unload_DLL SEC_PROTOTYPE_1(char *,name);*/
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_release_APIs SEC_PROTOTYPE_0();
/*RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_get_DLL SEC_PROTOTYPE_2(char *,name, void **, hdl);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_check_DLL SEC_PROTOTYPE_1(void, * hdl);*/
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_close_all SEC_PROTOTYPE_0();
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_close SEC_PROTOTYPE_1(char *, name);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_open SEC_PROTOTYPE_7(
	char *, name, 
	SECUDE_LOG_T *, f, 
	SECUDE_LOG_OPEN_T *, open_f, 
	SECUDE_LOG_CLOSE_T * , close_f, 
	void *, param1, 
	void *, param2, 
	char * ,moduls);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_log1 (
	char *modul, 
	char *object, 
	LOG_TYPE type, 
	int   level, 
	char *text, 
	...);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_log1_test SEC_PROTOTYPE_4(
	char *, modul, 
	char *, object, 
	LOG_TYPE , type, 
	int   , level);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_file_internal SEC_PROTOTYPE_6(
	void * ,param,
	char * ,modul, 
	char * ,object, 
	LOG_TYPE ,type, 
	int    ,level, 
	char ** ,text);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_file_internal_open SEC_PROTOTYPE_3(
	void *, p1,
	void *, p2,
	void **,hdl);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_log_file_internal_close SEC_PROTOTYPE_1(
	void **,hdl);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_info SEC_PROTOTYPE_3(
	SECUDE_INFO , attr,
	void **, info,
	SECUDE_FREE_T **, free_f);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV light_version SEC_PROTOTYPE_0();

#ifdef USE_NEW_ARITHMETIC
#include "alg_type.h"
 

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EC_char2field SEC_PROTOTYPE_1(
	EC_char2field	*	, c2f
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EC_char2field SEC_PROTOTYPE_1(
	EC_char2field	**	, c2f
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EC_FieldID SEC_PROTOTYPE_1(
	EC_FieldID *	, fid
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EC_FieldID SEC_PROTOTYPE_1(
	EC_FieldID **	, fid
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EC_Parameters SEC_PROTOTYPE_1(
	EC_Parameters *	, ecp
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EC_Parameters SEC_PROTOTYPE_1(
	EC_Parameters **	, ecp
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_EC_KeyParameter SEC_PROTOTYPE_1(
	EC_KeyParameter *	, eckp
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_EC_KeyParameter SEC_PROTOTYPE_1(
	EC_KeyParameter **	, eckp
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_EC_Parameters SEC_PROTOTYPE_2(
	EC_Parameters	 *	, dup_ecp,
	EC_Parameters	 *	, ecp
);

EC_Parameters SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_EC_Parameters SEC_PROTOTYPE_1(
	EC_Parameters	 *	, ecp
);

EC_KeyParameter SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_EC_KeyParameter SEC_PROTOTYPE_1(
	EC_KeyParameter	 *	, eckp
);

#else /* USE_NEW_ARITHMETIC */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_char2field SEC_PROTOTYPE_1(
	char2field	*	, c2f
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_char2field SEC_PROTOTYPE_1(
	char2field	**	, c2f
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_char2field SEC_PROTOTYPE_2(
	
	char2field	 *	, dup_c2f,
	char2field	 *	, c2f

);

char2field SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_char2field SEC_PROTOTYPE_1(
	
	char2field	 *	, c2f

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_FieldID SEC_PROTOTYPE_1(
	FieldID *	, fid
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_FieldID SEC_PROTOTYPE_1(
	FieldID **	, fid
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_FieldID SEC_PROTOTYPE_2(
	
	FieldID	 *	, dup_fid,
	FieldID	 *	, fid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_Curve SEC_PROTOTYPE_1(
	Curve *	, curve
);


FieldID SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_FieldID SEC_PROTOTYPE_1(
	
	FieldID	 *	, fid

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ECParameters SEC_PROTOTYPE_1(
	ECParameters *	, ecp
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ECParameters SEC_PROTOTYPE_1(
	ECParameters **	, ecp
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ECKeyParameter SEC_PROTOTYPE_1(
	ECKeyParameter *	, eckp
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ECKeyParameter SEC_PROTOTYPE_1(
	ECKeyParameter **	, eckp
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_ECParameters SEC_PROTOTYPE_2(
	ECParameters	 *	, dup_ecp,
	ECParameters	 *	, ecp
);

ECParameters SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_ECParameters SEC_PROTOTYPE_1(
	
	ECParameters	 *	, ecp

);

ECKeyParameter SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_ECKeyParameter SEC_PROTOTYPE_1(
	
	ECKeyParameter	 *	, eckp

);

#endif /* USE_NEW_ARITHMETIC */

#ifdef USE_NEW_ARITHMETIC
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_pentanomial SEC_PROTOTYPE_2(
	EC_pentanomial	 *	, p1,
	EC_pentanomial	 *	, p2
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_char2field SEC_PROTOTYPE_2(
	EC_char2field	 *	, f1,
	EC_char2field	 *	, f2
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_FieldID SEC_PROTOTYPE_2(
	EC_FieldID	 *	, f1,
	EC_FieldID	 *	, f2
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_Curve SEC_PROTOTYPE_2(
	EC_curve	 *	, c1,
	EC_curve	 *	, c2
);
#else
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_pentanomial SEC_PROTOTYPE_2(
	pentanomial	 *	, p1,
	pentanomial	 *	, p2
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_char2field SEC_PROTOTYPE_2(
	char2field	 *	, f1,
	char2field	 *	, f2
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_FieldID SEC_PROTOTYPE_2(
	FieldID	 *	, f1,
	FieldID	 *	, f2
);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_Curve SEC_PROTOTYPE_2(
	Curve	 *	, c1,
	Curve	 *	, c2
);
#endif
 #ifdef USE_NEW_ARITHMETIC

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_EC_KeyParameter SEC_PROTOTYPE_2(
	
	EC_KeyParameter	 *	, eckp1,
	EC_KeyParameter	 *	, eckp2

);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_EC_Parameters SEC_PROTOTYPE_2(
	
	EC_Parameters	 *	, eckp1,
	EC_Parameters	 *	, eckp2

);

 #else /* USE_NEW_ARITHMETIC */

RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_ECKeyParameter SEC_PROTOTYPE_2(
	
	ECKeyParameter	 *	, eckp1,
	ECKeyParameter	 *	, eckp2

);
RC SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV aux_cmp_ECParameters SEC_PROTOTYPE_2(
	
	ECParameters	 *	, eckp1,
	ECParameters	 *	, eckp2

);

ECParameters SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV set_ECParameters_name SEC_PROTOTYPE_1(
	
	char	*	, name																									

);
ECParameters SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV get_ECParameters_name SEC_PROTOTYPE_4(
	
	char	*	, name,
	ObjId * , oid,
	int , keysize,
	ObjId **, usedoid																									
);

 #endif /* USE_NEW_ARITHMETIC */

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV parse_keyword_as_objid1 SEC_PROTOTYPE_1(
	char	*	, keyword
);


#ifdef USE_NEW_ARITHMETIC
EC_Parameters SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV get_EC_Parameters_name SEC_PROTOTYPE_4(
	
	char	*	, name,
	ObjId * , oid,
	int , keysize,
	ObjId **, usedoid																									
);

EC_Parameters SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV set_EC_Parameters_name SEC_PROTOTYPE_1(
	char	*	, name																									
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ecdsa_gen_key SEC_PROTOTYPE_3(
	
	OctetString	** , skey,
	
	OctetString	** , pkey,
	
	EC_Parameters	*	, common

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ecdsa_sign SEC_PROTOTYPE_4(
	
	OctetString	 *	, hash,
	
	KeyBits	 	 *	, sign,
	
	OctetString	 *	, key,
		
	EC_Parameters	*	, ecparameter

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ecdsa_verify SEC_PROTOTYPE_4(
	
	OctetString	 *	, hash,
	
	KeyBits	 	 *	, sign,
	
	OctetString	 *	, key,
		
	EC_Parameters	*	, ecparameter

);
#else /* USE_NEW_ARITHMETIC */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ecdsa_gen_key SEC_PROTOTYPE_3(
	
	OctetString	** , skey,
	
	OctetString	** , pkey,
	
	ECParameters	*	, common

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ecdsa_sign SEC_PROTOTYPE_4(
	
	OctetString	 *	, hash,
	
	KeyBits	 	 *	, sign,
	
	OctetString	 *	, key,
		
	ECParameters	*	, ecparameter

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ecdsa_verify SEC_PROTOTYPE_4(
	
	OctetString	 *	, hash,
	
	KeyBits	 	 *	, sign,
	
	OctetString	 *	, key,
		
	ECParameters	*	, ecparameter

);

#endif /* USE_NEW_ARITHMETIC */


sec_uint4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_time_used SEC_PROTOTYPE_0();

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV mkdir_user_only SEC_PROTOTYPE_1(
	char * , path);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV open_user_only SEC_PROTOTYPE_2(
	char * , path, int, mode);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV chmodUserOnly SEC_PROTOTYPE_1(
		char * , DirName);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV open_with_mode SEC_PROTOTYPE_3(
	const char * , path, int, flags, int, mode);


void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_init SEC_PROTOTYPE_0();
void  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_exit SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_dl_open SEC_PROTOTYPE_2(
	void	**, hdl,
	char	* , filename
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_dl_open_with_verify SEC_PROTOTYPE_3(
	void	**, p_hdl,
	char	* , filename,
    Boolean   , verify
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_dl_close SEC_PROTOTYPE_1(
	void	**, hdl
);
 
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_dl_symbol SEC_PROTOTYPE_3(
	void	**, hdl,
	char	* , symbol_name,
	void	**, symbol
);
 
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV th_add_error SEC_PROTOTYPE_5(
	
	int		  	, number,
	
	char		 *	, text,
	
	char		 *	, addr,
	
	Struct_No	  	, addrtype,
	
	char		 *	, proc

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV th_last_error SEC_PROTOTYPE_0();

struct ErrStack SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV th_get_last_error SEC_PROTOTYPE_0();

struct ErrStack SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV th_get_err_malloc SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV th_get_last_error_text SEC_PROTOTYPE_0();

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV th_get_last_error_addr SEC_PROTOTYPE_0();

Struct_No SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV th_get_last_error_type SEC_PROTOTYPE_0();

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV th_free_error SEC_PROTOTYPE_0();

struct ErrStack SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV th_remove_last_error SEC_PROTOTYPE_0();

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV th_add_warning SEC_PROTOTYPE_5(
	
	int		  	, number,
	
	char		 *	, text,
	
	char		 *	, addr,
	
	Struct_No	  	, addrtype,
	
	char		 *	, proc

);



int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secure_delete SEC_PROTOTYPE_3(
 char * , filename,

 int , mode,

 long int , blocksize); 

/* 
 *	src/crypt
 */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_create_OctetStream SEC_PROTOTYPE_8(
	OctetStream ** , stream,
	Boolean , write, 
	char *, file_name, 
	DataStore *, data_store,
	OctetString *, ostr,
	FILE *, file_ptr,
	IO_Function *, io_func,
	int , file_hdl 
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OctetStream SEC_PROTOTYPE_1(
	OctetStream ** ,stream 
);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_pre_read_OctetStream SEC_PROTOTYPE_3(
	OctetStream * ,stream, 
	char * , buf,
	sec_int4 , length);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_seek_OctetStream SEC_PROTOTYPE_3(
	OctetStream * ,stream ,
	long		, offset,
	int			, origin
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_allow_seek_OctetStream SEC_PROTOTYPE_1(
	OctetStream * ,stream
);


sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_read_OctetStream SEC_PROTOTYPE_3(
	OctetStream * ,stream, 
	char * , buf,
	sec_int4 , length);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_write_OctetStream SEC_PROTOTYPE_3(
	OctetStream * ,stream, 
	char * , buf,
	sec_int4 , length);
DataStore SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_DataStore SEC_PROTOTYPE_1(
	
	DataStore	 *	, store

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_DataStore SEC_PROTOTYPE_1(
	
	DataStore	 **	, store

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_DataStore2OctetString SEC_PROTOTYPE_1(
	
	DataStore	 *	, store

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_strtok SEC_PROTOTYPE_4(
	char	*, input_str,
	char	*, delimiter,
	char	**, token,
	char	**, ctx
);
 
FILE_Type SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_file_type SEC_PROTOTYPE_1(
	
	char *	, path

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free SEC_PROTOTYPE_1(
	
	void	 *	, ptr

);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_malloc SEC_PROTOTYPE_1(
	
	size_t	, size

);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_calloc SEC_PROTOTYPE_2(
	
	size_t	, nr,
	size_t	, size

);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_realloc SEC_PROTOTYPE_2(
	
	void *	, ptr,
	size_t	, size

);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_struct SEC_PROTOTYPE_2(
	SECUDE_STRUCTURE,type, 
	void ** , structure);
	
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_encode SEC_PROTOTYPE_3(
	SECUDE_STRUCTURE,type, 
	void * , structure, 
	OctetString ** , asn1);
	
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy SEC_PROTOTYPE_3(
	SECUDE_STRUCTURE,type, 
	void * , structure, 
	void ** , cpy);
	
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_decode SEC_PROTOTYPE_3(
	SECUDE_STRUCTURE,type, 
	OctetString * , asn1, 
	void ** , structure);



int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_strncasecmp SEC_PROTOTYPE_3(
	
	char	 *	, s1,
	
	char	 *	, s2,
	
	int		, n

);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_strcasecmp SEC_PROTOTYPE_2(
	
	char	 *	, s1,
	
	char	 *	, s2

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD2Init SEC_PROTOTYPE_1(
	
	SEC_MD2_CTX	 *	, context

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD2Update SEC_PROTOTYPE_3(
	
	SEC_MD2_CTX		 *	, context,
	
	unsigned char	 *	, input,
	
	sec_uint4	  	, inputLen

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD2Final SEC_PROTOTYPE_2(
	
	unsigned char	 * 	, digest,
	
	SEC_MD2_CTX		 *	, context

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD4Init SEC_PROTOTYPE_1(
	
	SEC_MD4_CTX	 *	, context

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD4Update SEC_PROTOTYPE_3(
	
	SEC_MD4_CTX		 *	, context,
	
	unsigned char	 *	, input,
	
	sec_uint4	  	, inputLen

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD4Final SEC_PROTOTYPE_2(
	
	unsigned char	 * 	, digest,
	
	SEC_MD4_CTX		 *	, context

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD5Init SEC_PROTOTYPE_1(
	
	SEC_MD5_CTX	 *	, context

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD5Update SEC_PROTOTYPE_3(
	
	SEC_MD5_CTX		 *	, context,
	
	unsigned char	 *	, input,
	
	sec_uint4	  	, inputLen

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_MD5Final SEC_PROTOTYPE_2(
	
	unsigned char	 * 	, digest,
	
	SEC_MD5_CTX		 *	, context

);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV primzahl SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY 	, primzahl_,
	
	L_NUMBER_ARRAY 	, fakt,
	
	int		  	, length

);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV nextprime SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY 	, start,
	
	L_NUMBER_ARRAY 	, factor,
	
	int		  	, version

);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV optimize SEC_PROTOTYPE_2(
	
	L_NUMBER_ARRAY 	, zahl,
	
	int		  	, version

);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rabinstest SEC_PROTOTYPE_1(
         
        L_NUMBER_ARRAY  , zahl
 
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV lngtouse SEC_PROTOTYPE_1(
	
	L_NUMBER_ARRAY 	, modul

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV octetstoln SEC_PROTOTYPE_4(
	
	OctetString	 *	, octs,
	
	L_NUMBER_ARRAY 	, lnum,
	
	int		  	, offset,
	
	int		  	, size

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV lntoctets SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY 	, lnum,
	
	OctetString	 *	, octs,
	
	int		  	, size

);

#ifndef __cplusplus
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV xor SEC_PROTOTYPE_3(
	L_NUMBER_ARRAY	,  	op1,
	
	L_NUMBER_ARRAY	,  	op2,
	
	L_NUMBER_ARRAY	,  	erg

);
#endif


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV mult SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY	  	, A,
	
	L_NUMBER_ARRAY	  	, B,
	
	L_NUMBER_ARRAY	  	, erg

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV add SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY	, Ap,
	
	L_NUMBER_ARRAY	, Bp,
	
	L_NUMBER_ARRAY	, Sum

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sub SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY	, Ap,
	
	L_NUMBER_ARRAY	, Bp,
	
	L_NUMBER_ARRAY	, Diff

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV div SEC_PROTOTYPE_4(
	
	L_NUMBER_ARRAY	  	, A,
	
	L_NUMBER_ARRAY	  	, B,
	
	L_NUMBER_ARRAY	  	, Q,
	
	L_NUMBER_ARRAY	  	, R

);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cadd SEC_PROTOTYPE_4(
	
	L_NUMBER		  	, opa,
	
	L_NUMBER		  	, opb,
	
	L_NUMBER_ARRAY	 	, opa_b,
	
	L_NUMBER	  	, carry

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV shift SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY	  	, A,
	
	int		  	, exp2b,
	
	L_NUMBER_ARRAY	  	, S

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dmult SEC_PROTOTYPE_4(
	
	L_NUMBER	  	, a,
	
	L_NUMBER	  	, b,
	
	L_NUMBER_ARRAY	, high,
	
	L_NUMBER_ARRAY	, low

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_LN2BitString SEC_PROTOTYPE_2(
	
	L_NUMBER_ARRAY		, lnum,
	
	int		  	, size

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_LN2OctetString SEC_PROTOTYPE_2(
	
	L_NUMBER_ARRAY	, lnum,
	
	int		  	, size

);


L_NUMBER SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_OctetString2LN SEC_PROTOTYPE_1(
	
	OctetString	  *	, ostr

);

L_NUMBER SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_BitString2LN SEC_PROTOTYPE_1(
	
	BitString	  *	, bstr

);

KeyBits SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV rsa_convert_private_key SEC_PROTOTYPE_2 (

	KeyBits 	 *      , d_key,
 
	KeyBits 	 *      , e_key

);
RSAPrivateKey SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV rsa_convert_to_RSAPrivateKey SEC_PROTOTYPE_2 (

	KeyBits 	 *      , d_key,
 
	KeyBits 	 *      , e_key

);
#ifdef RSA_INSTALLED

#ifndef USE_NEW_ARITHMETIC

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV genrsa SEC_PROTOTYPE_3(
	
	Skeys		 *	, schlusr,
	
	int		  	, laenge,
	
	rndmstart	 *	, zufall

);

#else /* USE_NEW_ARITHMETIC */

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV genrsa SEC_PROTOTYPE_3(
	
	S_keys		 *	, schlusr,
	
	int		  	, laenge,
	
	rndmstart	 *	, zufall

);

#endif /*USE_NEW_ARITHMETIC */


#endif /* RSA_INSTALLED */

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV comp SEC_PROTOTYPE_2(
	
	L_NUMBER	 *	, Ap,
	
	L_NUMBER	 *	, Bp

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV intlog2 SEC_PROTOTYPE_1(
	
	sec_uint4	  	, v

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV bitstoln SEC_PROTOTYPE_4(
	
	BitString	 *	, bits,
	
	L_NUMBER_ARRAY 	, lnum,
	
	int		  	, offset,
	
	int		  	, size

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV lntobits SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY	, lnum,
	
	BitString	 *	, bits,
	
	int		  	, size

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_LN2BitString2 SEC_PROTOTYPE_3(
	
	BitString	 *	, bitstring,
	
	L_NUMBER_ARRAY 	, lnum,
	
	int		  	, size

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_LN2OctetString2 SEC_PROTOTYPE_3(
	
	OctetString	 *	, octetstring,
	
	L_NUMBER_ARRAY 	, lnum,
	
	int		  	, size

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_OctetString2LN2 SEC_PROTOTYPE_2(
	
	L_NUMBER    	  *	, lnum,
	
	OctetString	  *	, ostr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_BitString2LN2 SEC_PROTOTYPE_2(
	
	L_NUMBER    	  *	, lnum,
	
	BitString	  *	, bstr

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV madd SEC_PROTOTYPE_4(
	
	L_NUMBER_ARRAY  	, op1,
	
	L_NUMBER_ARRAY  	, op2,
	
	L_NUMBER_ARRAY  	, erg,
	
	L_NUMBER_ARRAY  	, modul

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV msub SEC_PROTOTYPE_4(
	
	L_NUMBER_ARRAY  	, op1,
	
	L_NUMBER_ARRAY  	, op2,
	
	L_NUMBER_ARRAY  	, erg,
	
	L_NUMBER_ARRAY  	, modul

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV mmult SEC_PROTOTYPE_4(
	
	L_NUMBER_ARRAY  	, op1,
	
	L_NUMBER_ARRAY  	, op2,
	
	L_NUMBER_ARRAY  	, erg,
	
	L_NUMBER_ARRAY  	, modul

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV mdiv SEC_PROTOTYPE_4(
	
	L_NUMBER_ARRAY	, op1,
	
	L_NUMBER_ARRAY	, op2,
	
	L_NUMBER_ARRAY	, erg,
	
	L_NUMBER_ARRAY	, modul

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV mexp SEC_PROTOTYPE_4(
	
	L_NUMBER_ARRAY  	, bas,
	
	L_NUMBER_ARRAY  	, exp,
	
	L_NUMBER_ARRAY  	, erg,
	
	L_NUMBER_ARRAY  	, modul

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV mexp2 SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY  	, exp,
	
	L_NUMBER_ARRAY  	, erg,
	
	L_NUMBER_ARRAY  	, modul

);



int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rndm SEC_PROTOTYPE_3(
	
	int		  	, lgth,
	
	L_NUMBER_ARRAY  	, zahl,
	
	int 			, version

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rndm_file SEC_PROTOTYPE_3(
	
	int		  	, lgth,
	
	L_NUMBER_ARRAY  	, zahl,
	
	int 			, version

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rndm_keyb SEC_PROTOTYPE_3(
	
	int		  	, lgth,
	
	L_NUMBER_ARRAY  	, zahl,
	
	int 			, version

);

#ifdef DES_INSTALLED
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV setkey0 SEC_PROTOTYPE_2(
	
        sec_uint4 * , kn,
	
	char	 *	, key

);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV endes SEC_PROTOTYPE_2(
	
        sec_uint4 * , kn,
	
	unsigned char	 *	, block

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dedes SEC_PROTOTYPE_2(
	
        sec_uint4 * , kn,
	
	unsigned char	 *	, block

);



char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  string_to_key SEC_PROTOTYPE_1(
	
	char	 *	, asckey

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  string_to_any_key SEC_PROTOTYPE_2(
	
	char	 *	, asckey,
	int		, size

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV endes_ecb_ctx SEC_PROTOTYPE_2(
	
        struct DES_CTX *	, ctx,
	
	unsigned char	 *	, outblock

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV endes_cbc_ctx SEC_PROTOTYPE_2(
	
        struct DES_CTX *	, ctx,
	
	unsigned char	 *	, outblock

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dedes_ecb_ctx SEC_PROTOTYPE_2(
	
        struct DES_CTX *	, ctx,
	
	unsigned char	 *	, outblock

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dedes_cbc_ctx SEC_PROTOTYPE_2(
	
        struct DES_CTX *	, ctx,
	
	unsigned char	 *	, outblock

);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_key_CBC SEC_PROTOTYPE_2(

        char *  , key,

        struct DES_CTX * , ctx

);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_key_CBC3 SEC_PROTOTYPE_2(

        char *  , key,

        struct DES_CTX * , ctx

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_crypt_init SEC_PROTOTYPE_5(
	
	void		**	, context,
	BitString		 *	, key,
	PAD_Func		* , pad,
	AlgMode	 , algmode,
	OctetString * ,iv_ostr

);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_encrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_encrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	OctetString	 *	, in,
	
	BitString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_encrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	BitString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_encrypt_all SEC_PROTOTYPE_3(
	
	OctetString	 *	, in,
	
	BitString	 *	, out,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_decrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_decrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	BitString	 *	, in,
	
	OctetString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_decrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV des_decrypt_all SEC_PROTOTYPE_3(
	
	BitString	 *	, in,
	
	OctetString	 *	, out,
	
	KeyInfo		 *	, keyinfo

);

#endif

#ifdef SECUDE_IMPLEMENTS_AES

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_crypt_init SEC_PROTOTYPE_6(
	void		**	, context,
	BitString    *	, key,
	PAD_Func     *  , pad,
	AlgMode         , algmode,
	OctetString  *  , iv_ostr,
    Boolean         , decrypt
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_encrypt_init SEC_PROTOTYPE_2(
	void		**	, context,
	KeyInfo		 *	, keyinfo
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_encrypt_more SEC_PROTOTYPE_3(
	void		**	, context,
	OctetString	 *	, in,
	BitString	 *	, out
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_encrypt_end SEC_PROTOTYPE_2(
	void		**	, context,
	BitString	 *	, out
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_encrypt_all SEC_PROTOTYPE_3(
	OctetString	 *	, in,
	BitString	 *	, out,
	KeyInfo		 *	, keyinfo
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_decrypt_init SEC_PROTOTYPE_2(
	void		**	, context,
	KeyInfo		 *	, keyinfo
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_decrypt_more SEC_PROTOTYPE_3(
	void		**	, context,
	BitString	 *	, in,
	OctetString	 *	, out
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_decrypt_end SEC_PROTOTYPE_2(
	void		**	, context,
	OctetString	 *	, out
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aes_decrypt_all SEC_PROTOTYPE_3(
	BitString	 *	, in,
	OctetString	 *	, out,
	KeyInfo		 *	, keyinfo
);

#endif /* SECUDE_IMPLEMENTS_AES */

AlgId	SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dhinit SEC_PROTOTYPE_2(
	
	int	  	, size_of_p,
	
	int	  	, private_value_length

);

AlgId	SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dh_init SEC_PROTOTYPE_2(
	
	int	  	, size_of_p,
	
	int	  	, private_value_length

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dhphase1 SEC_PROTOTYPE_3(
	
	AlgId	 *	, dhparam,
	
	KeyInfo	 **	, keyinfo_x,
	
	Boolean	  	, with_pg

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dh_phase1 SEC_PROTOTYPE_3(
	
	AlgId	 *	, dhparam,
	
	KeyInfo	 **	, keyinfo_x,
	
	Boolean	  	, with_pg

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dh_phase2 SEC_PROTOTYPE_3(
	
	AlgId    *	, dhparam,
	
	KeyInfo	 *	, own_x,
	
	KeyInfo	 *	, peer_y

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dhphase2 SEC_PROTOTYPE_3(
	
	AlgId    *	, dhparam,
	
	KeyInfo	 *	, own_x,
	
	KeyInfo	 *	, peer_y

);


RC	 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dh_start SEC_PROTOTYPE_5(
	
	void **	, dh_ctx,
	
	int	  	, size_of_p,
	
	int	  	, private_value_length,
	
	int	  	, dh_parm_mode,
	
	int	  	, enc_mode

);

OctetString	SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dh_connect SEC_PROTOTYPE_1(
	
	void **	, dh_ctx

);

OctetString	 SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dh_reply SEC_PROTOTYPE_2(
	
	void **	, dh_ctx,
	
	OctetString	  *	, in_buf

);

RC	 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dh_accept SEC_PROTOTYPE_2(
	
	void **	, dh_ctx,
	
	OctetString	  *	, buf

);

OctetString	SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dh_encrypt SEC_PROTOTYPE_2(
	
	void **	, dh_ctx,
	
	OctetString	  *	, in_buf

);

OctetString	SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dh_decrypt SEC_PROTOTYPE_2(
	
	void **	, dh_ctx,
	
	OctetString	  *	, in_buf

);

RC	 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dh_end SEC_PROTOTYPE_1(
	
	void **	, dh_ctx

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dsa_sign_all SEC_PROTOTYPE_4(
	
	OctetString	 *	, hash,
	
	KeyBits	 	 *	, sign,
	
	OctetString	 *	, key,
		
	KeyBits		 *	, common

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dsa_verify_all SEC_PROTOTYPE_4(
	
	OctetString	 *	, hash,
	
	KeyBits	 	 *	, sign,
	
	OctetString	 *	, key,
		
	KeyBits		 *	, common

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ln_ggt SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY 	, ln1,
	
	L_NUMBER_ARRAY	, ln2,
	
	L_NUMBER_ARRAY	, ggt

);


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ln_inv SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY  	, ln,
	
	L_NUMBER_ARRAY  	, modul,
	
	L_NUMBER_ARRAY 	, res

);

#ifdef USE_NEW_ARITHMETIC

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dsa_signblock SEC_PROTOTYPE_3(
	
	INTEGER 	, in,
	
	DSAsig			 *	, sig,
	
	DSASkeys		 *	, key

);



int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dsa_verifyblock SEC_PROTOTYPE_3(
	
	INTEGER	, in,
	
	DSAsig			 *	, sig,
	
	DSAPkeys		 *	, key

);

#else

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dsa_signblock SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY 	, in,
	
	DSA_sig			 *	, sig,
	
	DSA_Skeys		 *	, key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dsa_verifyblock SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY	, in,
	
	DSA_sig			 *	, sig,
	
	DSA_Pkeys		 *	, key

);

#endif


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rndm_trace SEC_PROTOTYPE_2(
	
	int		  	, lgth,
	
	L_NUMBER_ARRAY  	, zahl

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV dsa_gen_key SEC_PROTOTYPE_3(
	
	OctetString	**	, skey,
	
	OctetString	**	, pkey,
	
	KeyBits		 *	, common

);


KeyBits SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  dsa_gen_common SEC_PROTOTYPE_1(
	
	int		  	, keysize

);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_file2OctetString SEC_PROTOTYPE_1(
	
	char	 *	, fn

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_get_bytes_from_file SEC_PROTOTYPE_3(
	char		* , fn,
	long		  , offset,
	int		  , number
);

int	 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_OctetString2file	 SEC_PROTOTYPE_3(
	
	OctetString 	*	, ostr,
	
	char 		*	, fn,
	
	int 		 	, flag

);

int	 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_OctetString2file_mode SEC_PROTOTYPE_4(
	OctetString 	*	, ostr,
	char 		*	, fn,
	int 		 	, flag,
	int			, wmode
);

AUX_PRINT_PROTOTYPE(RSAPrivateKey)

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_OctetString SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	OctetString	 *	, ostr

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_BitString SEC_PROTOTYPE_2(
	
	char		 *	, string,
	
	BitString	 *	, bstr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_OctetString SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	OctetString	 *	, ostr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_BitString SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	BitString	 *	, bstr

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_KeyBits SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	KeyBits	 *	, keybits

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_ObjId SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	ObjId	 *	, objid

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_AlgId SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	AlgId	 *	, aid

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sprint_algorithm SEC_PROTOTYPE_3(
	
	char	 *	, string,
	
	ObjId	 *	, oid,
	
	char	 *	, name

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_KeyBits SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	KeyBits	 *	, keybits

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_ObjId SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	ObjId	 *	, objid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_AlgId SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	AlgId	 *	, aid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fprint_algorithm SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	ObjId	*	, oid

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  global_sprint_error SEC_PROTOTYPE_2(
	
	char	 *	, string,
	
	int	  	, verbose

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV global_fprint_error SEC_PROTOTYPE_2(
	
	FILE	*	, ff,
	
	int	  	, verbose

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_OctetString SEC_PROTOTYPE_1(
	
	OctetString	 *	, ostr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_BitString SEC_PROTOTYPE_1(
	
	BitString	 *	, bstr

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_KeyBits SEC_PROTOTYPE_1(
	
	KeyBits	 *	, keybits

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_ObjId SEC_PROTOTYPE_1(
	
	ObjId	 *	, objid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_AlgId SEC_PROTOTYPE_1(
	
	AlgId	 *	, aid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_algorithm SEC_PROTOTYPE_1(
	
	ObjId	 *	, oid

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV global_print_error SEC_PROTOTYPE_1(
	
	int	  	, verbose

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_OctetString SEC_PROTOTYPE_1(
	
	OctetString	**	, ostr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_OctetString SEC_PROTOTYPE_1(
	
	OctetString	 *	, ostr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_BitString SEC_PROTOTYPE_1(
	
	BitString	**	, bstr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_BitString SEC_PROTOTYPE_1(
	
	BitString	 *	, bstr

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_ObjId SEC_PROTOTYPE_1(
	
	ObjId	**	, oid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_ObjId SEC_PROTOTYPE_1(
	
	ObjId	 *	, oid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_KeyInfo SEC_PROTOTYPE_1(
	
	KeyInfo	 *	, p

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_KeyInfo SEC_PROTOTYPE_1(
	
	KeyInfo	**	, keyinfo

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_KeyBits SEC_PROTOTYPE_1(
	
	KeyBits	**	, keybits

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_RSAPrivateKey SEC_PROTOTYPE_1(
	
	RSAPrivateKey	**	, key

);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_RSAPrivateKey SEC_PROTOTYPE_1(
	RSAPrivateKey	*	, p
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_KeyBits SEC_PROTOTYPE_1(
	
	KeyBits	 *	, p

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PKCS1_OAEP_Parameter SEC_PROTOTYPE_1(
	PKCS1_OAEP_Parameter	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PKCS1_OAEP_Parameter SEC_PROTOTYPE_1(
	PKCS1_OAEP_Parameter	**	, parm
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PKCS1_PSS_Parameter SEC_PROTOTYPE_1(
	PKCS1_PSS_Parameter	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PKCS1_PSS_Parameter SEC_PROTOTYPE_1(
	PKCS1_PSS_Parameter	**	, parm
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_PKCS1_SaltedHash_Parameter SEC_PROTOTYPE_1(
	PKCS1_SaltedHash_Parameter	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_PKCS1_SaltedHash_Parameter SEC_PROTOTYPE_1(
	PKCS1_SaltedHash_Parameter	**	, parm
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_CFBParameter SEC_PROTOTYPE_1(
	CFBParameter	*	, p
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_CFBParameter SEC_PROTOTYPE_1(
	CFBParameter	**	, parm
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_AlgId SEC_PROTOTYPE_1(
	
	AlgId	**	, algid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_AlgId SEC_PROTOTYPE_1(
	
	AlgId	 *	, algid

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV global_free_error SEC_PROTOTYPE_0();




OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  sec_random_ostr SEC_PROTOTYPE_2(
	
	sec_uint4	  	, noctets,
	int			, security

);


BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  sec_random_bstr SEC_PROTOTYPE_1(
	
	sec_uint4	  	, nbits

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  sec_random_str SEC_PROTOTYPE_2(
	
	int	  	, nchars,
	
	char	 *	, chars

);



int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_BitString SEC_PROTOTYPE_2(
	
	BitString	 *	, bitstring1,
	
	BitString	 *	, bitstring2

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_new_OctetString SEC_PROTOTYPE_1(
	
	int	  	, length

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_OctetString SEC_PROTOTYPE_2(
	
	OctetString	 *	, octetstring1,
	
	OctetString	 *	, octetstring2

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_OctetString2int SEC_PROTOTYPE_1(
	
	OctetString	 *	, ostr_repr

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_KeyBits SEC_PROTOTYPE_2(
	
	KeyBits	 *	, keybits1,
	
	KeyBits	 *	, keybits2

);

KeyBits SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_KeyBits SEC_PROTOTYPE_1(
	
	KeyBits	 *	, keybits

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_ObjId SEC_PROTOTYPE_2(
	
	ObjId	 *	, dup_oid,
	
	ObjId	 *	, oid

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_ObjId SEC_PROTOTYPE_2(
	
	ObjId	 *	, oid1,
	
	ObjId	 *	, oid2

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_AlgId SEC_PROTOTYPE_2(
	
	AlgId	 *	, dup_aid,
	
	AlgId	 *	, aid

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_AlgId SEC_PROTOTYPE_1(
	
	AlgId	 *	, aid

);
SET_OF_AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_SETOFAlgId SEC_PROTOTYPE_1(
	SET_OF_AlgId	 * , algs
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_AlgId SEC_PROTOTYPE_2(
	
	AlgId	 *	, aid1,
	
	AlgId	 *	, aid2

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_KeyInfo SEC_PROTOTYPE_1(
	
	KeyInfo	 *	, keyinfo

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_KeyInfo SEC_PROTOTYPE_2(
	
	KeyInfo	 *	, dup_ki,
	
	KeyInfo	 *	, keyinfo

);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_ObjId SEC_PROTOTYPE_1(
	
	ObjId	 *	, oid

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_OctetString SEC_PROTOTYPE_2(
	
	OctetString	 *	, dup_ostr,
	
	OctetString	 *	, ostr

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cpy2_BitString SEC_PROTOTYPE_2(
	
	BitString	 *	, dup_bstr,
	
	BitString	 *	, bstr

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_OctetString SEC_PROTOTYPE_1(
	
	OctetString	 *	, ostr

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_BitString SEC_PROTOTYPE_1(
	
	BitString	 *	, bstr

);

BitString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_OctetString2BitString SEC_PROTOTYPE_1(
	OctetString	 *	, ostr
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_cpy_BitString2OctetString SEC_PROTOTYPE_1(
	BitString	 *	, bstr
);

ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_Name2ObjId SEC_PROTOTYPE_1(
	
	char	 *	, name

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_Name2AlgId SEC_PROTOTYPE_1(
	
	char	 *	, name

);

AlgType SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_Name2AlgType SEC_PROTOTYPE_1(
	
	char	 *	, name

);

AlgEnc SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_Name2AlgEnc SEC_PROTOTYPE_1(
	
	char	 *	, name

);

AlgHash SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_Name2AlgHash SEC_PROTOTYPE_1(
	
	char	 *	, name

);

AlgMode SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_Name2AlgMode SEC_PROTOTYPE_1(
	
	char	 *	, name

);

AlgSpecial SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_Name2AlgSpecial SEC_PROTOTYPE_1(
	
	char	 *	, name

);

ParmType SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_Name2ParmType SEC_PROTOTYPE_1(
	
	char	 *	, name

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_ObjId2Name SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

AlgType SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2AlgType SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

AlgEnc SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2AlgEnc SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

AlgHash SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2AlgHash SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

AlgSpecial SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2AlgSpecial SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

AlgMode SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2AlgMode SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_ObjId2AlgId SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

ParmType SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_ObjId2ParmType SEC_PROTOTYPE_1(
	
	ObjId	 *	, given_objid

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_cpy_String SEC_PROTOTYPE_1(
	
	char	 *	, str

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free_String SEC_PROTOTYPE_1(
	char	**	, ptr
);


#if defined(USE_STDARG)
int SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV   PRINTF(char *format, ...);
int SEC_GLOBAL_FUNC_PREFIX  SEC_API_CALLING_CONV   FPRINTF(FILE *ff, char *format, ...);
#else
int SEC_GLOBAL_FUNC_PREFIX   SEC_API_CALLING_CONV  PRINTF();
int SEC_GLOBAL_FUNC_PREFIX   SEC_API_CALLING_CONV  FPRINTF();
#endif

#if defined(USE_STDARG)
char SEC_GLOBAL_FUNC_PREFIX   * SEC_API_CALLING_CONV CATSPRINTF(char *string, char *format, ...);
#else
char SEC_GLOBAL_FUNC_PREFIX   * SEC_API_CALLING_CONV CATSPRINTF();
#endif


char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  CATNSTR SEC_PROTOTYPE_3(
	
	char	  *	, string,
	
	char      *	, append,
	
	int        	, chars

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV global_add_error SEC_PROTOTYPE_5(
	
	int		  	, number,
	
	char		 *	, text,
	
	char		 *	, addr,
	
	Struct_No	  	, addrtype,
	
	char		 *	, proc

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV global_add_warning SEC_PROTOTYPE_5(
	int		  	, number,
	char		 *	, text,
	char		 *	, addr,
	Struct_No	  	, addrtype,
	char		 *	, proc
);

HTONL_TYPE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_htonl SEC_PROTOTYPE_1(
	
	HTONL_TYPE	  	, x

);

HTONL_TYPE SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_ntohl SEC_PROTOTYPE_1(
	
	HTONL_TYPE	  	, x

);

KeyInfo SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_BitString2EncryptionKey SEC_PROTOTYPE_2(
	
	AlgId	 *	, alg,
	
	BitString *	, bstr

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sxdumpp SEC_PROTOTYPE_5(
	
	char	 *	, string,
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type,
	
	Boolean	  	, printable

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fxdumpp SEC_PROTOTYPE_5(
	
	FILE	 *	, dump_file,
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type,
	
	Boolean	  	, printable

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fxdump SEC_PROTOTYPE_4(
	
	FILE	 *	, dump_file,
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sxdump SEC_PROTOTYPE_4(
	
	char	 *	, string,
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_sxdump2 SEC_PROTOTYPE_4(
	
	char	 *	, string,
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_fxdump2 SEC_PROTOTYPE_4(
	
	FILE	 *	, dump_file,
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_xdump SEC_PROTOTYPE_3(
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_xdump2 SEC_PROTOTYPE_3(
	
	char	 *	, buffer,
	
	sec_int4	  	, len,
	
	sec_int4	  	, addr_type

);

/* from idea/idea_if.c : */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV cip_octets SEC_PROTOTYPE_2(
	unsigned char	*	, outblock,
	IDEA_KEY_STRUCT		, Z);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc2_version2effectivekeysize SEC_PROTOTYPE_1(
	sec_int4 , version
);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc2_effectivekeysize2version SEC_PROTOTYPE_1(
	sec_int4 , effectivekeysize
);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_crypt_init SEC_PROTOTYPE_7(
	
	void		**	, context,
	int			, mode,
	BitString		 *	, key,
	PAD_Func		* , pad,
	AlgMode	 , algmode,
	OctetString * ,iv_ostr,
	int , eff_keysize

);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_encrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_encrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	OctetString	 *	, in,
	
	BitString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_encrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	BitString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_encrypt_all SEC_PROTOTYPE_3(
	
	OctetString	 *	, in,
	
	BitString	 *	, out,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_decrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_decrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	BitString	 *	, in,
	
	OctetString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_decrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rc_decrypt_all SEC_PROTOTYPE_3(
	
	BitString	 *	, in,
	
	OctetString	 *	, out,
	
	KeyInfo		 *	, keyinfo

);


sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_encrypt_init2 SEC_PROTOTYPE_5(
	
	void		**	, context,
	BitString		 *	, key,
	PAD_Func		* , pad,
	AlgMode	 , algmode,
	OctetString * ,iv_ostr

);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_decrypt_init2 SEC_PROTOTYPE_5(
	
	void		**	, context,
	BitString		 *	, key,
	PAD_Func		* , pad,
	AlgMode	 , algmode,
	OctetString * ,iv_ostr

);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_encrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_encrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	OctetString	 *	, in,
	
	BitString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_encrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	BitString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_encrypt_all SEC_PROTOTYPE_3(
	
	OctetString	 *	, in,
	
	BitString	 *	, out,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_decrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyInfo		 *	, keyinfo

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_decrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	BitString	 *	, in,
	
	OctetString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_decrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV idea_decrypt_all SEC_PROTOTYPE_3(
	
	BitString	 *	, in,
	
	OctetString	 *	, out,
	
	KeyInfo		 *	, keyinfo

);

/* from idea/idea.c : */  
 
typedef void SEC_API_CALLING_CONV FP_Idea_ExpandUserKey SEC_PROTOTYPE_2(
	  char *, userKey_string, 
	  Idea_Key , key);
extern FP_Idea_ExpandUserKey *fp_Idea_ExpandUserKey;

typedef void SEC_API_CALLING_CONV FP_Idea_InvertKey SEC_PROTOTYPE_2(
	  Idea_Key , key, 
	  Idea_Key , invKey);
extern FP_Idea_InvertKey *fp_Idea_InvertKey;

typedef void SEC_API_CALLING_CONV FP_Idea_Crypt SEC_PROTOTYPE_2(
	  unsigned char * , data,
	  Idea_Key , key);
extern FP_Idea_Crypt *fp_Idea_Crypt;

typedef void SEC_API_CALLING_CONV FP_Idea_Crypt2 SEC_PROTOTYPE_3(
	  unsigned char	 * , dataIn,
	  unsigned char	 * , dataOut,
	  Idea_Key , key);
extern FP_Idea_Crypt2 *fp_Idea_Crypt2;

/* from ? : */

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV md2_hash SEC_PROTOTYPE_3(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result,
	
	More		  	, more

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV md4_hash SEC_PROTOTYPE_3(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result,
	
	More		  	, more

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV md5_hash SEC_PROTOTYPE_3(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result,
	
	More		  	, more

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV md_hash_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	char		  	, version

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV md_hash_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV md_hash_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, hash_result

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV md_hash_all SEC_PROTOTYPE_3(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result,
	
	char		  	, version

);


#ifdef RSA_INSTALLED
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_key_size SEC_PROTOTYPE_1(
	
	KeyBits	 *	, d_key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_key_size_PK SEC_PROTOTYPE_1(
	
	KeyBits	 *	, d_key

);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_key_size_SK SEC_PROTOTYPE_1(
	
	KeyBits	 *	, d_key

);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_crypt_get_keysize SEC_PROTOTYPE_1(
	
	void		**	, context

);



sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyBits		 *	, key

);

 
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	OctetString	 *	, in,
	
	BitString	 *	, out

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	BitString	 *	, out

);


sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encrypt_all SEC_PROTOTYPE_3(
	
	OctetString	 *	, in,
	
	BitString	 *	, out,
	
	KeyBits		 *	, key

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_context_free SEC_PROTOTYPE_1(

        void **        , ctx

);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_decrypt_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyBits		 *	, key

);

 
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_decrypt_more SEC_PROTOTYPE_3(
	
	void		**	, context,
	
	BitString	 *	, in,
	
	OctetString	 *	, out

);


sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_decrypt_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, out

);


sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_decrypt_all SEC_PROTOTYPE_3(
	
	BitString	 *	, in,
	
	OctetString	 *	, out,
	
	KeyBits		 *	, key

);
#endif /* RSA_INSTALLED */

#ifdef SQMODN_INSTALLED
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sqmodn_hash_init SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	KeyBits		 *	, key

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sqmodn_hash_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sqmodn_hash_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, hash_result

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sqmodn_hash_all SEC_PROTOTYPE_3(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result,
	
	KeyBits		 *	, key

);
#endif /* SQMODN_INSTALLED */

#ifdef RSA_INSTALLED
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_sign_all SEC_PROTOTYPE_3(
	
	OctetString	 *	, hash,
	
	BitString	 *	, sign,
	
	KeyBits		 *	, key

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_verify_all SEC_PROTOTYPE_4(
	
	OctetString	 *	, hash,
	
	BitString	 *	, sign,
	
	OctetString	 *	, decr_hash,
	
	KeyBits		 *	, key

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encblock2OctetString SEC_PROTOTYPE_3(
	
	KeyBits	 	 *	, d_key,
	
	BitString	 *	, sign,
	
	OctetString	 *	, hash

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encblock2_OctetString SEC_PROTOTYPE_3(
	
	KeyBits	 	 *	, d_key,
	
	BitString	 *	, sign,
	
	OctetString	 *	, hash

);




#ifdef USE_NEW_ARITHMETIC
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encblock_elements SEC_PROTOTYPE_3(
	
	void *  /* el_Context */ 	    , in,
	
	void ** /* el_Context* */	    , enc,
	
	INTEGER	    	, e

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encblock SEC_PROTOTYPE_3(
	
	INTEGER 	    , in,
	
	INTEGER	    , enc,
	
	P_keys	    *	, pk

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_decblock_elements SEC_PROTOTYPE_3(
	
	void        *  /* ln_Context*/  	, in,
	
	void        ** /* ln_Context* */	, enc,
	
	S_keys		*	, sk

);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_decblock SEC_PROTOTYPE_3(
	
	INTEGER  	, in,
	
	INTEGER	, enc,
	
	S_keys		*	, sk

);

#else /* USE_NEW_ARITHMETIC */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_encblock SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY  	, in,
	
	L_NUMBER_ARRAY 	, enc,
	
	Pkeys			 *	, pk

);



void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_decblock SEC_PROTOTYPE_3(
	
	L_NUMBER_ARRAY 	, in,
	
	L_NUMBER_ARRAY 	, dec,
	
	Skeys		 *	, sk

);


#endif /* USE_NEW_ARITHMETIC */



RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rsa_gen_key SEC_PROTOTYPE_3(
	
	int		  	, keysize,
	
	KeyBits		**	, skey,
	
	KeyBits		**	, pkey

);
 
#endif /* RSA_INSTALLED */

/* Original SHA */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV shsInit SEC_PROTOTYPE_1(
	 SHS_INFO       *       , shsInfo 
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV SHSTransform SEC_PROTOTYPE_2(
	 sec_uint4           *	, digest,
	 sec_uint4           *       , data 	 
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV longReverse SEC_PROTOTYPE_2(
	 sec_uint4           *	, buffer,
	 sec_int4                , byteCount 
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV shsUpdate SEC_PROTOTYPE_3(
	 SHS_INFO       *	, shsInfo,
	 unsigned char           *	, buffer,
	 sec_int4                , count
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV shsFinal SEC_PROTOTYPE_1(
	 SHS_INFO       *       , shsInfo 
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha_hash_init SEC_PROTOTYPE_1(
	
	void		**	, context

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha_hash_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha_hash_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, hash_result

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha_hash_all SEC_PROTOTYPE_2(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result

);

/* Modified SHA, i.e. SHA1 */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV shs1Init SEC_PROTOTYPE_1(
	 SHS_INFO       *       , shsInfo 
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV SHS1Transform SEC_PROTOTYPE_2(
	 sec_uint4           *	, digest,
	 sec_uint4           *       , data 	 
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV shs1Update SEC_PROTOTYPE_3(
	 SHS_INFO       *	, shsInfo,
	 unsigned char           *	, buffer,
	 sec_int4                , count
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV shs1Final SEC_PROTOTYPE_1(
	 SHS_INFO       *       , shsInfo 
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha1_hash_init SEC_PROTOTYPE_1(
	
	void		**	, context

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha1_hash_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha1_hash_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, hash_result

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sha1_hash_all SEC_PROTOTYPE_2(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result

);

/* RIPEMD160 */


void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV RMDcompress SEC_PROTOTYPE_2(
	 sec_uint4           *	, digest,
	 sec_uint4           *  , data 	 
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV RMDfinish SEC_PROTOTYPE_4(
	 sec_uint4           *	, MDbuf,
	 sec_uint1          *	, buffer,
	 sec_uint4              , lswlen,
	 sec_uint4		, mswlen
);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rmd160_hash_init SEC_PROTOTYPE_1(
	
	void		**	, context

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rmd160_hash_more SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, in_octets

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rmd160_hash_end SEC_PROTOTYPE_2(
	
	void		**	, context,
	
	OctetString	 *	, hash_result

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV rmd160_hash_all SEC_PROTOTYPE_2(
	
	OctetString	 *	, in_octets,
	
	OctetString	 *	, hash_result

);


RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_parity_bstr SEC_PROTOTYPE_2(
	
	BitString      *	, bitstring,
	Parity			, parity

);



/* from  global/time.c :   */
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_is_UTCTime SEC_PROTOTYPE_1(
	char * , time );
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_get_timezone SEC_PROTOTYPE_0();
 

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_check_UTCTime SEC_PROTOTYPE_1(
        UTCTime *       , utc
);
 
time_t SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_UTCTime2time_t SEC_PROTOTYPE_1(
        UTCTime *       , utc
);
 
UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_time_t2UTCTime SEC_PROTOTYPE_1(
        time_t  , seconds  
);
 

UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_current_UTCTime SEC_PROTOTYPE_0();
 
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_readable_UTCTime SEC_PROTOTYPE_1(
         
        UTCTime  *      , utc

);
 
UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_delta_UTCTime SEC_PROTOTYPE_2(
         
        UTCTime  *      , time,
         
        time_t          , delta


);
 
UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_delta_UTCTime_T_REC SEC_PROTOTYPE_2(
         
        UTCTime  *      , time,
         
        T_REC    *      , delta
 
 
);
 
UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_T_REC2UTCTime SEC_PROTOTYPE_1(
         
        T_REC    *      , tr
 
 
);
 
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_interval_UTCTime SEC_PROTOTYPE_3(
         
        UTCTime  *      , time,
         
        UTCTime  *      , notbefore,
         
        UTCTime  *      , notafter
 
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_interval2_UTCTime SEC_PROTOTYPE_3(
         
        UTCTime  *      , time,
         
        UTCTime  *      , notbefore,
         
        UTCTime  *      , notafter
 
);
 
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_UTCTime SEC_PROTOTYPE_2(
         
        UTCTime  *      , time1,
         
        UTCTime  *      , time2
 
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_check_GeneralTime SEC_PROTOTYPE_1(
        GeneralTime *       , utc
);
 
time_t SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_GeneralTime2time_t SEC_PROTOTYPE_1(
        GeneralTime *       , utc
);
 
GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_time_t2GeneralTime SEC_PROTOTYPE_1(
        time_t  , seconds  
);
 

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_current_GeneralTime SEC_PROTOTYPE_0();
 
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_readable_GeneralTime SEC_PROTOTYPE_1(
         
        GeneralTime  *      , utc

);
 
GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_delta_GeneralTime SEC_PROTOTYPE_2(
         
        GeneralTime  *      , time,
         
        time_t          , delta


);
 
GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_delta_GeneralTime_T_REC SEC_PROTOTYPE_2(
         
        GeneralTime  *      , time,
         
        T_REC    *      , delta
 
 
);
 
GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_T_REC2GeneralTime SEC_PROTOTYPE_1(
         
        T_REC    *      , tr
 
 
);
 
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_interval_GeneralTime SEC_PROTOTYPE_3(
         
        GeneralTime  *      , time,
         
        GeneralTime  *      , notbefore,
         
        GeneralTime  *      , notafter
 
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_interval2_GeneralTime SEC_PROTOTYPE_3(
         
        GeneralTime  *      , time,
         
        GeneralTime  *      , notbefore,
         
        GeneralTime  *      , notafter
 
);
 
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_cmp_GeneralTime SEC_PROTOTYPE_2(
         
        GeneralTime  *      , time1,
         
        GeneralTime  *      , time2
 
);

GeneralTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_UTCTime2GeneralTime SEC_PROTOTYPE_1(
	UTCTime	*	, utc
);



/*
 * call this function from applications (no locking of SECUDE
 */
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV SECUDE_HasValidTicket  SEC_PROTOTYPE_1(
	char ** , rcIdOrError
);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV SECUDE_HasValidTicket20  SEC_PROTOTYPE_5(
	char ** , rcIdOrError,   /* here you get back the error string */
	char * ,application,     /* the name of the application to check */
	char * ,versionstring,   /* the release of the applications to check */
	int * ,restriction,      /* you get back 0 for full, 1 for light version */
	char ** , userid         /* you get back the id of the ticket */
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV SECUDE_IsValidApplicationTicket20  SEC_PROTOTYPE_6(
    char * , ticket,         /* ticket string to check */
	char ** , rcIdOrError,   /* here you get back the error string */
	char * ,application,     /* the name of the application to check */
	char * ,versionstring,   /* the release of the applications to check */
	int * ,restriction,      /* you get back 0 for full, 1 for light version */
	char ** , userid         /* you get back the id of the ticket */
);

/*
 * call this function from SECUDE APIs (locking of SECUDE is done)
 */
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV secude_license_check SEC_PROTOTYPE_0();

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV SECUDE_CheckApplicationTicket SEC_PROTOTYPE_3(
    char *,name, char *,application, char **,error);

/* DO NOT CALL THIS FUNCTION ANYMORE!!!!
 * obsolete secude_check_license() is replaced by SECUDE_HasValidTicket()
 */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV secude_check_license SEC_PROTOTYPE_0();



UTCTime SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV secude_get_expiration SEC_PROTOTYPE_0();

/* from  global/ pkcs.c :   */
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_PKCSBlock SEC_PROTOTYPE_3(

        char                    , BT,

        OctetString      *      , D,
	
	int			, public_modulus_length

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_PKCS_MIC_D SEC_PROTOTYPE_2(

        OctetString      *      , hash_result,

        AlgId            *      , signatureAlgorithm

);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_t SEC_PROTOTYPE_1(
        int ,  number
);

#ifdef AF2
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_error_text SEC_PROTOTYPE_1(
        int ,  number
);
#endif
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_text SEC_PROTOTYPE_2(
        int ,  number,
        struct TextList *, tlist);
RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV set_language SEC_PROTOTYPE_1(
	sec_uint4, lang
);
sec_uint4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV get_language SEC_PROTOTYPE_0();

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  get_tmp_file SEC_PROTOTYPE_0();

/* externals from sec_global.h */



/* each block IN ALPHABETICAL ORDER */

/* AlgId addresses */


extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC3;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC3_ISO0;  
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC3_ISO1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC3_pad;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC_ISO0;   
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC_ISO1;   
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desCBC_pad;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desECB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desEDE;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	desEDE3CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dhKeyAgreement;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dhWithCommonModulus;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_dsa_with_sha1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_dsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dsaCommon;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dsaCommonWithSHA;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dsaCommonWithSHA1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dsaSK;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dsaWithSHA;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	dsaWithSHA1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	NullEncryption;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	idea;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	ideaCBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md2;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md2WithRsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md2WithRsaEncryption;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md2WithRsaTimeDate;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md4;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md4WithRsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md4WithRsaEncryption;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md4WithRsaTimeDate;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5WithRsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5WithRsaEncryption;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5WithRsaTimeDate;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5WithRsa_TelesecSig;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5WithdesCBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5WithdesCBC3;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	md5Withidea;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithMD2AnddesCBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithMD5AnddesCBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithSHA1And128BitRC4;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithSHA1And40BitRC4;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithSHA1AndDES3xCBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithSHA1AndDES3CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithSHA1And128BitRC2CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	pbeWithSHA1And40BitRC2CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	rc2CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	rc4;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	ripemd160;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	ripemd160WithRSASignature;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	rsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	rsaEncryption;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	rsa_B1; 
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sha;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sha1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sha1WithRsaEncryption;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sha1WithRSASignature;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	rsaSignatureWithsha1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	shaWithRSASignature;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sqmodn;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sqmodnWithRsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX encISO9796_2Withrsa;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sigS_ISO9796_2Withsha1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sigS_ISO9796_2Withripemd160;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sigS_ISO9796_2rndWithsha1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	sigS_ISO9796_2rndWithripemd160;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_ecPublicKey;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	ecdsa_with_SHA1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_RSAES_OAEP;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_PKCS1_mgf1;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_PKCS1_pSpecified;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_RSASSA_PSS;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	id_PKCS1_salted_hash;

extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes128ECB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes128CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes192ECB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes192CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes256ECB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes256CBC;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes128OFB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes128CFB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes192OFB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes192CFB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes256OFB;
extern AlgId SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX	aes256CFB;



/* ObjectIdentifier for X.509V3 extensions */
extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX

		AuthorityKeyID_oid,
		BasicConstraints_oid,
		CRLDistributionPoints_oid,
		CertificatePolicies_oid,
		IssuerAltName_oid,
		KeyUsage_oid,
		NameConstraints_oid,
		PolicyConstraints_oid,
		PolicyMappings_oid,
		PrivateKeyUsagePeriod_oid,
		SubjectAltName_oid, 
		SubjectDirectoryAttributes_oid,
		SubjectKeyID_oid,
		SupportedAlgorithms_oid;


extern AlgList SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX   alglist[];

extern int SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  no_of_algorithms;


/*
 *  Bad DES keys  (initialized in sec_init.c)
 */

extern unsigned char SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX bad_des_keys[];
extern int SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  no_of_bad_des_keys;



extern Boolean SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  sec_verbose;     /* if FALSE, RSA stuff is silent          */
extern Boolean SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  sec_gen_verbose; /* if FALSE, key generation is silent     */

extern unsigned char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   print_keyinfo_flag; /* controls aux_fprint_KeyInfo() : 
                                            ALGID:   AlgId
                                            ALGINFO: Algorithm characteristics from alglist
                                            BITSTRING:    DER-Code of BitString 
                                                     subjectkey
                                            KEYBITS: Components of subjectKey 
                                                     in case of RSA, DSA, DH
                                            SK, PK:  */



extern sec_uint4 SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  print_cert_flag;    /* controls aux_fprint_Certificate() :           */
extern sec_uint4 SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  print_indent;

extern FILE SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX secude_trace_file;

extern struct timeval SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   sec_tp1, sec_tp2;
extern struct timezone SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   sec_tzp1, sec_tzp2;
extern long SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   hash_sec, hash_usec, rsa_sec, rsa_usec, dsa_sec, dsa_usec, des_sec, des_usec, idea_sec, idea_usec, rc_sec, rc_usec, aes_sec, aes_usec;

extern UTCTime SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  sec_SignatureTimeDate[];
extern struct TextList SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   text_list[];
#ifdef AF2
extern struct TextList SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   text_list2[];
#endif
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX algparmtype_name[];
extern char SEC_GLOBAL_FUNC_PREFIX * SEC_GLOBAL_VAR_PREFIX algtype_name[];
extern char SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX algenc_name[];
extern char SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX algmode_name[];
extern char SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX alghash_name[];
extern char SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX algspecial_name[];


extern char SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX proc;

extern AlgId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX

		desCBC_aid,
		desCBC3_aid,
		desCBC3_ISO0_aid,  
		desCBC3_ISO1_aid,
		desCBC3_pad_aid,
		desCBC_ISO0_aid,   
		desCBC_ISO1_aid,   
		desCBC_pad_aid,
		desECB_aid,
		desEDE_aid,
		desEDE3CBC_aid,
		dhKeyAgreement_aid,
		dhWithCommonModulus_aid,
		dsa_aid,
		dsaCommon_aid,
		dsaCommonWithSHA_aid,
		dsaCommonWithSHA1_aid,
		dsaSK_aid,
		dsaWithSHA_aid,
		dsaWithSHA1_aid,
		NullEncryption_aid,
		idea_aid,
		ideaCBC_aid,
		md2_aid,
		md2WithRsa_aid,
		md2WithRsaEncryption_aid,
		md2WithRsaTimeDate_aid,
		md4_aid,
		md4WithRsa_aid,
		md4WithRsaEncryption_aid,
		md4WithRsaTimeDate_aid,
		md5_aid,
		md5WithRsa_aid,
		md5WithRsaEncryption_aid,
		md5WithRsaTimeDate_aid,
		md5WithRsa_TelesecSig_aid,
		md5WithdesCBC_aid,
		md5WithdesCBC3_aid,
		md5Withidea_aid,
		pbeWithMD2AnddesCBC_aid,
		pbeWithMD5AnddesCBC_aid,
		pbeWithSHA1And128BitRC4_aid,
		pbeWithSHA1And40BitRC4_aid,
		pbeWithSHA1AndDES3xCBC_aid,
		pbeWithSHA1AndDES3CBC_aid,
		pbeWithSHA1And128BitRC2CBC_aid,
		pbeWithSHA1And40BitRC2CBC_aid,
		rc2CBC_aid,
		rc4_aid,
		ripemd160_aid,
		ripemd160WithRSASignature_aid,
		rsa_aid,
		rsaEncryption_aid,
		rsa_B1_aid, 
		sha_aid,
		sha1_aid,
		sha1WithRsaEncryption_aid,
		sha1WithRSASignature_aid,
		RSASignatureWithsha1_aid,
		shaWithRSASignature_aid,
		sqmodn_aid,
		sqmodnWithRsa_aid,
/* added for PKCS#11 */
		rc2CBC_nopad_aid,
		desEDE3CBC_nopad_aid,
		desCBC3_nopad_aid,
		ssl3_pre_master_gen_aid,
		ssl3_master_gen_aid,
		ssl3_key_and_mac_derive_aid,
		ssl3_md5_mac_aid,
		ssl3_sha1_mac_aid,
		encISO9796_2Withrsa_aid,
		sigS_ISO9796_2Withsha1_aid,
		sigS_ISO9796_2Withripemd160_aid,
		sigS_ISO9796_2rndWithsha1_aid,
		sigS_ISO9796_2rndWithripemd160_aid,
		id_ecPublicKey_aid,
		ecdsa_with_SHA1_aid,
/* end */
        id_RSAES_OAEP_aid,
        id_PKCS1_mgf1_aid,
        id_PKCS1_pSpecified_aid,
        id_RSASSA_PSS_aid,
        id_PKCS1_salted_hash_aid,
        aes128ECB_aid,
        aes128CBC_aid,
        aes192ECB_aid,
        aes192CBC_aid,
        aes256ECB_aid,
        aes256CBC_aid,
        aes128OFB_aid,
        aes128CFB_aid,
        aes192OFB_aid,
        aes192CFB_aid,
        aes256OFB_aid,
        aes256CFB_aid;



extern ObjId SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX

		desCBC_oid,
		desCBC3_oid,
		desCBC3_ISO0_oid,  
		desCBC3_ISO1_oid,
		desCBC3_pad_oid,
		desCBC_ISO0_oid,   
		desCBC_ISO1_oid,   
		desCBC_pad_oid,
		desECB_oid,
		desEDE_oid,
		desEDE3CBC_oid,
		dhKeyAgreement_oid,
		dhWithCommonModulus_oid,
		dsa_oid,
		dsaCommon_oid,
		dsaCommonWithSHA_oid,
		dsaCommonWithSHA1_oid,
		dsaSK_oid,
		dsaWithSHA_oid,
		dsaWithSHA1_oid,
		NullEncryption_oid,
		idea_oid,
		ideaCBC_oid,
		md2_oid,
		md2WithRsa_oid,
		md2WithRsaEncryption_oid,
		md2WithRsaTimeDate_oid,
		md4_oid,
		md4WithRsa_oid,
		md4WithRsaEncryption_oid,
		md4WithRsaTimeDate_oid,
		md5_oid,
		md5WithRsa_oid,
		md5WithRsaEncryption_oid,
		md5WithRsaTimeDate_oid,
		md5WithRsa_TelesecSig_oid,
		md5WithdesCBC_oid,
		md5WithdesCBC3_oid,
		md5Withidea_oid,
		pbeWithMD2AnddesCBC_oid,
		pbeWithMD5AnddesCBC_oid,
		pbeWithSHA1And128BitRC4_oid,
		pbeWithSHA1And40BitRC4_oid,
		pbeWithSHA1AndDES3xCBC_oid,
		pbeWithSHA1AndDES3CBC_oid,
		pbeWithSHA1And128BitRC2CBC_oid,
		pbeWithSHA1And40BitRC2CBC_oid,
		rc2CBC_oid,
		rc4_oid,
		ripemd160_oid,
		ripemd160WithRSASignature_oid,
		rsa_oid,
		rsaEncryption_oid,
		rsa_B1_oid, 
		sha_oid,
		sha1_oid,
		sha1WithRsaEncryption_oid,
		sha1WithRSASignature_oid,
		RSASignatureWithsha1_oid,
		shaWithRSASignature_oid,
		sqmodn_oid,
		sqmodnWithRsa_oid,
		encISO9796_2Withrsa_oid,
		sigS_ISO9796_2Withsha1_oid,
		sigS_ISO9796_2Withripemd160_oid,
		sigS_ISO9796_2rndWithsha1_oid,
		sigS_ISO9796_2rndWithripemd160_oid,
		id_ecPublicKey_oid,
		ecdsa_with_SHA1_oid,
        id_RSAES_OAEP_oid,
        id_PKCS1_mgf1_oid,
        id_PKCS1_pSpecified_oid,
        id_RSASSA_PSS_oid,
        id_PKCS1_salted_hash_oid,
        aes128ECB_oid,
        aes128CBC_oid,
        aes192ECB_oid,
        aes192CBC_oid,
        aes256ECB_oid,
        aes256CBC_oid,
        aes128OFB_oid,
        aes128CFB_oid,
        aes192OFB_oid,
        aes192CFB_oid,
        aes256OFB_oid,
        aes256CFB_oid,

		prime_field_oid,
		characteristic_two_field_oid,
		gnBasis_oid,
		tpBasis_oid,
		ppBasis_oid;


extern L_NUMBER SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   lz_null[];
extern L_NUMBER SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   lz_eins[];
extern L_NUMBER SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   lz_zwei[];
extern L_NUMBER SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   lz_drei[];
extern L_NUMBER SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   lz_fermat5[];
extern L_NUMBER SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  *lz_public_exponent;
extern sec_uint4 SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX   primes[];

#ifdef ARITHMETIC_TEST
extern  FILE SEC_GLOBAL_FUNC_PREFIX  * SEC_GLOBAL_VAR_PREFIX arithmetic_trace;
extern  int SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX   arithmetic_trace_counter;
#endif

#ifdef RSA_INSTALLED
extern int SEC_GLOBAL_FUNC_PREFIX  SEC_GLOBAL_VAR_PREFIX  RSAgenCountDown;
#endif

extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  gssapi_installed;
extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  pem_installed;
extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  pkcs_installed;

#ifdef ENABLE_GENERIC_CIPHER_MODES
void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV crypt_create_keyschedule_des SEC_PROTOTYPE_2(
    char    *   , key_material,
    Boolean     , decrypt
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_destroy_keyschedule_des SEC_PROTOTYPE_1(
    void    *   , schedule
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_enc_block_des SEC_PROTOTYPE_3(
    void    *   , key,
    char    *   , in_block,
    char    *   , out_block
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_dec_block_des SEC_PROTOTYPE_3(
    void    *   , key,
    char    *   , in_block,
    char    *   , out_block
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV crypt_create_keyschedule_3des SEC_PROTOTYPE_2(
    char    *   , key_material,
    Boolean     , decrypt
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_destroy_keyschedule_3des SEC_PROTOTYPE_1(
    void    *   , schedule
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_enc_block_3des SEC_PROTOTYPE_3(
    void    *   , key,
    char    *   , in_block,
    char    *   , out_block
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_dec_block_3des SEC_PROTOTYPE_3(
    void    *   , key,
    char    *   , in_block,
    char    *   , out_block
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV crypt_create_keyschedule_idea SEC_PROTOTYPE_2(
    char    *   , key_material,
    Boolean     , decrypt
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_destroy_keyschedule_idea SEC_PROTOTYPE_1(
    void    *   , schedule
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_enc_block_idea SEC_PROTOTYPE_3(
    void    *  , key,
    char    *  , in_block,
    char    *  , out_block
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_dec_block_idea SEC_PROTOTYPE_3(
    void    *  , key,
    char    *  , in_block,
    char    *  , out_block
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV crypt_create_keyschedule_rc2 SEC_PROTOTYPE_4(
    char    *   , key_material,
    Boolean     , decrypt,
    int         , actual_length,
    int         , restricted_length
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_destroy_keyschedule_rc2 SEC_PROTOTYPE_1(
    void    *   , schedule
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_enc_block_rc2 SEC_PROTOTYPE_3(
    void    *  , key,
    char    *  , in_block,
    char    *  , out_block
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_dec_block_rc2 SEC_PROTOTYPE_3(
    void    *  , key,
    char    *  , in_block,
    char    *  , out_block
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV crypt_create_keyschedule_aes SEC_PROTOTYPE_3(
    char    *   , key_material,
    Boolean     , decrypt,
    int         , key_length
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_destroy_keyschedule_aes SEC_PROTOTYPE_1(
    void    *   , schedule
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_enc_block_aes SEC_PROTOTYPE_3(
    void    *  , key,
    char    *  , in_block,
    char    *  , out_block
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV crypt_dec_block_aes SEC_PROTOTYPE_3(
    void    *  , key,
    char    *  , in_block,
    char    *  , out_block
);
#endif /* ENABLE_GENERIC_CIPHER_MODES */







#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


