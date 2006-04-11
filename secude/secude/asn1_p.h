/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/asn1_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/
/***************************************************************************
 *                                                                         *
 * universal ASN.1 prototypes                                              *
 *                                                                         *
 ***************************************************************************/

#ifndef ASN1_PROTOTYPES_H_
#define ASN1_PROTOTYPES_H_

#if !defined(SECUDE_ASN1_INCLUDE) || !SECUDE_ASN1_INCLUDE
#error do not include this file, include <secude/asn1.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1e_dummyf SEC_PROTOTYPE_3(
        ASN1info_type   *    , info,
        ASN1global      *    , glob,
        void            *    , from
);
void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1d_dummyf SEC_PROTOTYPE_4(
        ASN1info_type   *    , info,
        char            **   , from,
	char            *    , endptr,
	void            *    , ret
);
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1f_dummyf SEC_PROTOTYPE_1(
    void    *   , ret
);


/*
  ASN1putlength (elementary)
  put correct encoding of length field into byte stream at target,
  return new position in byte stream
  */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1putlength SEC_PROTOTYPE_2(
        char               *    , target ,
	unsigned int            , length
);

/*
  ASN1getlength (elementary)
  extract length field from byte stream at source,
  return new position in byte stream
  */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1getlength SEC_PROTOTYPE_4(
        char               *     , source,
	char               *     , endptr,
	unsigned int       *     , length,
	int		   *	 , retval
);

/*
  ASN1puttag (elementary)
  put correct encoding of tag field into byte stream at targat,
  return new position in byte stream
  */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1puttag SEC_PROTOTYPE_3(
        char               *     , target,
	sec_byte                     , cl,
	unsigned int             , tagnum
);

/*
  ASN1gettag (elementary)
  extract tag field from byte stream at source,
  return new position in byte stream
  */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1gettag SEC_PROTOTYPE_5(
        char               *    , source,
	char               *    , endptr,
	sec_byte               *    , cl,
	unsigned int       *    , tagnum,
	int		   *	, retval
);

/*
  ASN1expecttag (elementary)
  compare actual tag field in byte stream at source with supplied values
  return either new position in byte stream or NULL when not equal
  */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1expecttag SEC_PROTOTYPE_4(
        char               *     , source,
	char               *     , endptr,
	sec_byte                     , cl,
	unsigned int             , tagnum
);

/*
  ASN1initglobal (auxiliary)
  initialize ASN1global structure with initially size entries
  return FALSE if no memory available
  */
/*Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1initglobal SEC_PROTOTYPE_2(
        ASN1global         *      , glob,
	int                       , size
);*/

/*
  ASN1assemble (auxiliary, recursive)
  assemble the pre-encoded contents of ASN1descriptor into a fully
  (DER-)encoded byte stream. *target is dynamically increased
  */
/*int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1assemble SEC_PROTOTYPE_2(
        ASN1descriptor    *      , descr,
	char              **     , target
);*/

/*
  ASN1getdescriptor (auxiliary)
  get the index of a new ASN1descriptor, make an entry in ASN1global and
  expand it if it was to small
  return negative value if problems with alloc
  */
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1getdescriptor SEC_PROTOTYPE_1(
        ASN1global        *      , glob
);

/*
  compare_ASN1descriptors (auxiliary)
  compare two descriptors (in fact ASN1sortables)
  needed for qsort
  */
/*int SEC_GLOBAL_FUNC_PREFIX SEC_CDECL compare_ASN1descriptors SEC_PROTOTYPE_2(
        const void        *     , a,
	const void        *     , b
);*/

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1e_generic SEC_PROTOTYPE_3(
        ASN1info_type           *    , info,
	void                    *    , pvalue,
	int                          , initial_size
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ASN1e_generic_with_tuning SEC_PROTOTYPE_4(
    ASN1info_type           *    , info,
    void                    *    , pvalue,
    int                          , initial_size,
    ASN1encodertuning            , tuning
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1d_generic SEC_PROTOTYPE_3(
        ASN1info_type           *    , info,
	OctetString      	*    , asn1_string,
	char			*    , proc
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1e_gen_explicit SEC_PROTOTYPE_5(
        ASN1info_type           *    , info,
        ASN1global              *    , glob,
	sec_byte                         , tagcl,
	unsigned int                 , tagnum,
	void                    *    , pvalue
);
void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1d_gen_explicit SEC_PROTOTYPE_6(
        ASN1info_type           *    , info,
	char                    **   , from,
	char                    *    , endptr,
	sec_byte                         , tagcl,
	unsigned int                 , tagnum,
	void                    *    , pvalue
);

ASN1info_type SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1info_implicit SEC_PROTOTYPE_4(
        ASN1info_type             *    , info,
	ASN1info_type             *    , target,
	sec_byte                           , tagcl,
	unsigned int                   , tagnum
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1e_gen_ExpWrapper SEC_PROTOTYPE_3(
    ASN1info_type        *  , info,
    ASN1global           *  , glob,
    void                 *  , from
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ASN1d_gen_ExpWrapper SEC_PROTOTYPE_4(
    ASN1info_type        *    , info,
    char                 **   , from,
    char                 *    , endptr,
    void                 *    , ret
);

/* work on (ASN1gen_List *), but changed to (void *) to avoid warnings */
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1e_gen_List SEC_PROTOTYPE_3(
        ASN1info_type        *  , info,
        ASN1global           *  , glob,
        void                 *  , vfrom
);

void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  ASN1d_gen_List SEC_PROTOTYPE_4(
        ASN1info_type        *    , info,
        char                 **   , from,
	char                 *    , endptr,
	void                 *    , vret
);

char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  sdumpasn SEC_PROTOTYPE_3(
        OctetString        *    , ostr,
	int                     , options,
	int		       ,  displayed_offset
);

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_adump SEC_PROTOTYPE_4(
        char             *     ,  from,
	int                    ,  num,
	int                    ,  options,
	int		       ,  displayed_offset
);

RC SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_extract_asn_static SEC_PROTOTYPE_4(
        OctetString        *    , ostr,
	OctetString	   *	, into,
	ObjId		   *	, target,
	int			, options
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_extract_asn SEC_PROTOTYPE_3(
        OctetString        *    , ostr,
	ObjId		   *	, target,
	int			, options
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_asn_merge_multipart SEC_PROTOTYPE_2(
        OctetString        *    , asn1_str,
	int			, options
);

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1e_gen_part SEC_PROTOTYPE_2(
        ASN1econtext      *  ,  ecp,
	int                  ,  newpos
);

/*----------------------------------------------------------------------*/
/*   universal ASN.1 types                                              */
/*----------------------------------------------------------------------*/

#ifdef MACRO_SEP_LIKE_STDC
#define ASN1_en_de_PROTO(type) \
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_##type SEC_PROTOTYPE_3(\
        ASN1info_type     *    , info,\
        ASN1global        *    , glob ,\
        type              *    , from\
);\
type SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  decode_##type SEC_PROTOTYPE_4(\
        ASN1info_type     *    , info,\
        char              **   , from ,\
        char              *    , endptr ,\
        type              *    , ret\
);
#else
#define ASN1_en_de_PROTO(type) \
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_/**/type SEC_PROTOTYPE_3(\
        ASN1info_type     *    , info,\
        ASN1global        *    , glob ,\
        type              *    , from\
);\
type SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  decode_/**/type SEC_PROTOTYPE_4(\
        ASN1info_type     *    , info,\
        char              **   , from ,\
        char              *    , endptr ,\
        type              *    , ret\
);
#endif

ASN1_en_de_PROTO(OctetString)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OctetString;

ASN1_en_de_PROTO(BitString)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_BitString;

ASN1_en_de_PROTO(ObjId)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_ObjId;

ASN1_en_de_PROTO(DERcode)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_DERcode;

ASN1_en_de_PROTO(Long)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Long;

ASN1_en_de_PROTO(Integer)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Integer;

ASN1_en_de_PROTO(UInteger)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_UInteger;

#define encode_Enumerated(i, g, f) encode_Integer(i, g, (int *)f)
#define decode_Enumerated(i, f, e, r) (void *)decode_Integer(i, f, e, (void *)r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Enumerated;

ASN1_en_de_PROTO(Boolean)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Boolean;


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_Null SEC_PROTOTYPE_3(
        ASN1info_type     *    , info,
        ASN1global        *    , glob ,
        void              *    , dummy
);
void SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  decode_Null SEC_PROTOTYPE_4(
        ASN1info_type     *    , info,
        char              **   , from ,
        char              *    , endptr ,
        void              *    , ret
);
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_Null;

int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_xyzString_with_EBCDIC SEC_PROTOTYPE_3(
        ASN1info_type     *    , info,
        ASN1global        *    , glob,
	char              *    , from
);
int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV encode_xyzString SEC_PROTOTYPE_3(
        ASN1info_type     *    , info,
        ASN1global        *    , glob,
	char              *    , from
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  decode_xyzString_with_EBCDIC SEC_PROTOTYPE_4(
        ASN1info_type     *    , info,
        char              **   , from,
	char              *    , endptr,
	char              *    , ret
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV  decode_xyzString SEC_PROTOTYPE_4(
        ASN1info_type     *    , info,
        char              **   , from,
	char              *    , endptr,
	char              *    , ret
);
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_xyzString;

#define encode_PrintableString(i, g, f) encode_xyzString_with_EBCDIC(i, g, f)
#define decode_PrintableString(i, f, e, r) decode_xyzString_with_EBCDIC(i, f, e, r)
#define decode_PrintableString_without_EBCDIC(i, f, e, r) decode_xyzString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_PrintableString;

#define encode_UTCTime(i, g, f) encode_xyzString_with_EBCDIC(i, g, f)
#define decode_UTCTime(i, f, e, r) decode_xyzString_with_EBCDIC(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_UTCTime;

#define encode_IA5String(i, g, f) encode_xyzString_with_EBCDIC(i, g, f)
#define decode_IA5String(i, f, e, r) decode_xyzString_with_EBCDIC(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_IA5String;

#define encode_GeneralTime(i, g, f) encode_xyzString_with_EBCDIC(i, g, f)
#define decode_GeneralTime(i, f, e, r) decode_xyzString_with_EBCDIC(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GeneralTime;

#define encode_T61String(i, g, f) encode_xyzString(i, g, f)
#define decode_T61String(i, f, e, r) decode_xyzString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_T61String;

#define encode_GRAPHICString(i, g, f) encode_xyzString_with_EBCDIC(i, g, f)
#define decode_GRAPHICString(i, f, e, r) decode_xyzString_with_EBCDIC(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_GRAPHICString;

#define encode_OSstr_Impl_PrintableString(i, g, f) encode_OctetString(i, g, f)
#define decode_OSstr_Impl_PrintableString(i, f, e, r) decode_OctetString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_PrintableString;

#define encode_OSstr_Impl_T61String(i, g, f) encode_OctetString(i, g, f)
#define decode_OSstr_Impl_T61String(i, f, e, r) decode_OctetString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_T61String;

#define encode_OSstr_Impl_IA5String(i, g, f) encode_OctetString(i, g, f)
#define decode_OSstr_Impl_IA5String(i, f, e, r) decode_OctetString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_IA5String;

#define encode_BMPString(i, g, f) encode_OctetString(i, g, f)
#define decode_BMPString(i, f, e, r) decode_OctetString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_BMPString;

/* UTF8String is output encoding, not localized => no WITH_EBCDIC */
#define encode_UTF8String(i, g, f) encode_xyzString(i, g, f)
#define decode_UTF8String(i, f, e, r) decode_xyzString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_UTF8String;

#define encode_OSstr_Impl_UTF8String(i, g, f) encode_OctetString(i, g, f)
#define decode_OSstr_Impl_UTF8String(i, f, e, r) decode_OctetString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_UTF8String;

/* VisibleString */
#define encode_VisibleString(i, g, f) encode_xyzString_with_EBCDIC(i, g, f)
#define decode_VisibleString(i, f, e, r) decode_xyzString_with_EBCDIC(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_VisibleString;

#define encode_OSstr_Impl_VisibleString(i, g, f) encode_OctetString(i, g, f)
#define decode_OSstr_Impl_VisibleString(i, f, e, r) decode_OctetString(i, f, e, r)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_OSstr_Impl_VisibleString;


#ifdef TRACE_ASN1
Boolean SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1_do_trace SEC_PROTOTYPE_0();
#endif
void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1_log_time SEC_PROTOTYPE_1(
    FILE *  , trace_file
);

unsigned int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1getlength_of_first SEC_PROTOTYPE_1(
        OctetString  * , ostr
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_latin1_to_unicode SEC_PROTOTYPE_2(
	char	 *	, latin_string,
	Boolean		, termination
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_unicode_to_latin1 SEC_PROTOTYPE_1(
	OctetString	* , bmp
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_BMPString SEC_PROTOTYPE_1(
	BMPString	 *	, infos
);
BMPString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_BMPString SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_utf8_to_unicode SEC_PROTOTYPE_1(
	char	 *	, utf8_str
);
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_unicode_to_utf8 SEC_PROTOTYPE_1(
	OctetString	* , bmp_str
);
OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV e_UTF8String SEC_PROTOTYPE_1(
	UTF8String	 *	, infos
);
UTF8String SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV d_UTF8String SEC_PROTOTYPE_1(
	OctetString	 *	, asn1_string
);


int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1_string2tag SEC_PROTOTYPE_3(
	char		* , str,
	sec_byte	* , tagcl,
	unsigned int	* , tagnum
);

OctetString SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV ASN1parse SEC_PROTOTYPE_1(
	char		* , str
);

unsigned int SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV ASN1nontrailing_bits SEC_PROTOTYPE_1(
	BitString	* , bstr
);


/* OID stuff */
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_asn_ObjId2Name SEC_PROTOTYPE_1(
	ObjId *		, oid
);
ObjId SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_asn_Name2ObjId SEC_PROTOTYPE_1(
	char *		, name
);


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif

