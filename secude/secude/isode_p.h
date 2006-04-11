/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/isode_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#if !defined(SECUDE_ISODE_INCLUDE) || !SECUDE_ISODE_INCLUDE
#error do not include this file, include <secude/isode.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 *	src/encode
 */
 



/* from  encode/aux_time.c :   */
/*
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
*/

 
 
/* from  encode/ ?   */


/* encode/ ? */

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV advise SEC_PROTOTYPE_2(
	
	char	 *	, str1,
	
	char	 *	, str2

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_canon SEC_PROTOTYPE_1(
	
	OctetString	 *	, text

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_decanon SEC_PROTOTYPE_1(
	
	OctetString	 *	, canform

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_64 SEC_PROTOTYPE_2(
	
	OctetString	 *	, text,
	
	OctetString	 *	, indent

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_de64 SEC_PROTOTYPE_2(
	
	OctetString	 *	, form64,
	
	int		  	, indentlen

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_elim_whitespace SEC_PROTOTYPE_1(
	OctetString	 *	, form64
);

sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_base64 SEC_PROTOTYPE_4(
	
	char	 *	, in,
	sec_int4 	, len,
	char	 *	, out,
	char	 *	, lf
	

);
sec_int4 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_dec_base64 SEC_PROTOTYPE_4(
	
	char	 *	, in,
	sec_int4 	, len,
	char	 *	, out,
	char	 *  , rem
	

);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_encrfc SEC_PROTOTYPE_1(
	
	OctetString	 *	, in
	
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_encrfc SEC_PROTOTYPE_1(
	
	OctetString	 *	, in
	
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_decrfc SEC_PROTOTYPE_1(
	
	OctetString	 *	, in

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_enchex SEC_PROTOTYPE_1(
	
	OctetString	 *	, in

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_dechex SEC_PROTOTYPE_1(
	
	OctetString	 *	, in

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_dechex0 SEC_PROTOTYPE_1(
	
	OctetString	 *	, in

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_encap SEC_PROTOTYPE_1(
	
	OctetString	 *	, in

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_decap SEC_PROTOTYPE_1(
	
	OctetString	 *	, in

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_is_base64_encoded SEC_PROTOTYPE_1(
	OctetString	* , ostr
);


OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_OctetString SEC_PROTOTYPE_1(
	
	char	 *	, text

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_append_OctetString SEC_PROTOTYPE_2(
	
	OctetString	 *	, to,
	
	OctetString	 *	, append

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_append_BitString SEC_PROTOTYPE_2(
	
	BitString	 *	, to,
	
	BitString	 *	, append

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_append_char SEC_PROTOTYPE_2(
	
	OctetString	 *	, to,
	
	char		 *	, append

);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_searchitem SEC_PROTOTYPE_3(
	
	OctetString	 *	, bst,
	
	char		 *	, item,
	
	int	 	 *	, pos

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_SerialNo SEC_PROTOTYPE_1(
	
	char		 *	, number

);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_String2SerialNumber SEC_PROTOTYPE_1(
	
	char	 *	, ostr_repr

);


/* externals : */

extern char SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  chrcnv[], nochrcnv[];
extern int SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  sec_asn1_length_encoding;




/* from  encode/ aux_PKCS.c :   */
/*
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  aux_create_PKCS_MIC_D SEC_PROTOTYPE_2(

        OctetString      *      , hash_result,

        AlgId            *      , signatureAlgorithm

);

*/


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



