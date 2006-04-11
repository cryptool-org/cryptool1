/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/asn1.h
 *###
 *### global functions:
 *###
 *###*****************************************/


#ifndef ASN1_H_
#define ASN1_H_

#include <secude/sec_glob.h>

/*typedef char PrintableString;*/
/*typedef char IA5String;*/
/*typedef char VisibleString;*/
typedef OctetString BMPString;
typedef OctetString Long;
typedef OctetString DERcode;
/***** Typedef Integer *****/
/** @ingroup header_asn1
  */
typedef int Integer;
typedef unsigned int UInteger;

typedef char UTF8String; /* should work; 0x00 == end-of-string, only length not through strlen!!! */

/***** Typedef sec_byte *****/
/** @ingroup header_asn1
  */
typedef unsigned char sec_byte;


#define ASN1universal   (sec_byte)0x00
#define ASN1application (sec_byte)0x40
#define ASN1context     (sec_byte)0x80
#define ASN1private     (sec_byte)0xc0
#define ASN1class       (sec_byte)0xc0

#define ASN1primitive   (sec_byte)0x00
#define ASN1constructed (sec_byte)0x20

#define ASN1SEQUENCE    (sec_byte)0x10
#define ASN1SET         (sec_byte)0x11

#define ASN1UNKNOWN ((unsigned int)-1)

#define ASN1dump_sloppy             0x00000001
#define ASN1dump_disp_o_b_str       0x00000002
#define ASN1dump_clear_o_b_str      0x00000004
#define ASN1dump_recurse_encaps     0x00000008
#define ASN1dump_verbose_OID        0x00000010
#define ASN1dump_full_OID           0x00000020
#define ASN1dump_detail             0x00000040
#define ASN1dump_check_DER          0x00000080
#define ASN1dump_no_length_limit    0x00000100
#define ASN1dump_multiple_PDU       0x00000200
#define ASN1dump_force_recursive    0x00000400
#define ASN1dump_comp_number        0x00000800
#define ASN1dump_bitstring          0x00001000
#define ASN1dump_scan               0x00002000
#define ASN1dump_std_tags_only      0x00004000
#define ASN1dump_hexcode            0x00008000
#define ASN1dump_show_offset        0x00010000
#define ASN1dump_BMP_o_b_str        0x00020000
#define ASN1dump_pretty_tags        0x00040000
#define ASN1dump_no_infos           0x00080000
#define ASN1dump_ms_little_endian   0x00100000

#define ASN1error_none                  0x0000
#define ASN1error_tag_overflow          0x0001
#define ASN1warning_tag_leading_zero    0x0002
#define ASN1warning_length_leading_zero 0x0003
#define ASN1warning_length_not_in_one   0x0004
#define ASN1error_no_more_bytes         0x0005
#define ASN1error_length_overflow       0x0006
#define ASN1error_length_ff_is_reserved 0x0007

#define ASN1extract_content	   0x0001

#define ASN1bufferindescriptor 10
typedef struct ASN1descriptor {
    int descriptors;  /* 0: normal descriptor, else constructed, in this */
		       /* case contains number of descriptors in content */
    char hlength;                     /* number of valid bytes in header */
    char header[ASN1bufferindescriptor];
    int length;          /* number of bytes in content (i.e. in DER code */
    char *content;           /* DER code or field of descriptors (resp.) */
    Boolean allocated;              /* is content allocated (by myself)? */
} ASN1descriptor;

/***** Enumeration ASN1memorymode *****/
/** used in ASN1global
  *
  * When the ASN.1 encoder calls the respective encode_XXX() function,
  * it only builds an internal structure, but no final encoding.
  * This is a rather efficient method, because it saves a lot of memory
  * allocation and copying.
  * A problem arises, when more than simple encoding calls (i.e. memory
  * allocation) is done in the encode_XXX() function. In this case this
  * memory has to be freed before leaving the function (to avoid leakage)
  * but that might leave the encoder with dangling pointers, so we have
  * to introduce some kind of "memory management" for the encode
  * function... et voila.
  *
  * @ingroup header_asn1
  */
enum ASN1memorymode {
    ASN1memory_undef = 0, /** <tt>=0</tt> */
    ASN1memory_link,      /**< standard (old) behaviour: simply point to memory */
    ASN1memory_new,       /**< allocate new memory and copy the content bytes */
    ASN1memory_inherit    /**< inherit the memory, i.e. set a pointer to it and free it after use */
};
#ifndef DOXYGEN_EXCLUDE
typedef enum ASN1memorymode ASN1memorymode;
#endif

/***** Enumeration ASN1encodertuning *****/
/** used by ASN1global
  *
  * The world is not perfect. Not all ASN.1 encoders or applications,
  * resp, are producing correctly encoded PDUs. Mostly it is sufficient
  * to recognize the bad encoding and ignore it, but lately we stepped
  * over a lot of stuff, that requires us to produce bad encoding
  * ourselves just to be interoperable with the other bad encoders.
  * This is a very sad thing. To cheer up our lives a little bit, we
  * will not always encode bad ASN.1, but only when required!
  * This is done by setting some ASN1encodertuning value in the 
  * ASN1global structure, so that each recursively called encode_XXX()
  * function is able to see this value and produce the respective bad
  * encoding in response.
  *
  * @ingroup header_asn1
  */
enum ASN1encodertuning {
	   /** <tt>=0</tt>. Let's make our best effort to produce correct encodings
      * (old behavior)
      */
    ASN1tuning_normal = 0,
	   /** tells functions to use the override field in the
      * data-to-be-encoded (where appropriate)
      */
    ASN1tuning_override
};
#ifndef DOXYGEN_EXCLUDE
typedef enum ASN1encodertuning ASN1encodertuning;
#endif

/* ASN1global
 *
 * A value of this type is passed to all recursively called encode_XXX()
 * functions. It contains internal management values (status of 
 * descriptor array), as well as tweaking values for memory management
 * and the tuning parameter.
 *
 * Later, there might be added further values, to force the encoder to
 * implement other encoding rules (like CER, for example).
 * In the moment it produces DER, when not "tuned" differently
 */
typedef struct ASN1global {
    ASN1descriptor *descriptor;
    int dsize;
    int dpos;
    ASN1memorymode mode; /* how to handle large memory given to encoding */
                      /* functions: just point to it, copy it or inherit */
    ASN1encodertuning tuning;
} ASN1global;

typedef struct ASN1sortable {
    ASN1global *glob;
    int pos;
} ASN1sortable;

typedef struct ASN1econtext {
    ASN1global *glob;
    ASN1sortable *field;
    int siz;
    int num;
} ASN1econtext;

/* general structure for all SEQUENCE_OF(), SET_OF() constructs,
   also used for FCPath, CertificatePairs, DName, RDName, AttrValues etc. */
typedef SEQUENCE_OF(void) ASN1gen_List;

/* general structure for all SIGNED types 
   (Certificate, CRL, and some PKCS types) */
#define ASN1signed_TEMPLATE2(type,name) \
struct {\
    OctetString  *tbs_DERcode;\
    type         *name;\
    Signature    *sig;\
}
#define ASN1signed_TEMPLATE(type) ASN1signed_TEMPLATE2(type,tbs)

typedef ASN1signed_TEMPLATE(void) ASN1signed;

/* not the ideal solution, but... well */
#ifdef SEC_BCC
#define SEC_API_CC
#else
#define SEC_API_CC SEC_API_CALLING_CONV
#endif

/***** Typedef e_function *****/
/** @ingroup header_asn1
  */
typedef OctetString * SEC_API_CC e_function(
#if defined(USE_ANSI_PROTOTYPES)
	void *
#endif
);
/***** Typedef d_function *****/
/** @ingroup header_asn1
  */
typedef void * SEC_API_CC d_function(
#if defined(USE_ANSI_PROTOTYPES)
	OctetString *
#endif
);

typedef struct ASN1SIGNED_info {
    e_function * encoder;
    d_function * decoder;
} ASN1SIGNED_info;

struct ASN1info_type;

/***** Typedef encode_function *****/
/** @ingroup header_asn1
  */
typedef int SEC_API_CC encode_function(
#if defined(USE_ANSI_PROTOTYPES)
	struct ASN1info_type *, ASN1global *, void *
#endif
);
/***** Typedef decode_function *****/
/** @ingroup header_asn1
  */
typedef void * SEC_API_CC decode_function(
#if defined(USE_ANSI_PROTOTYPES)
	struct ASN1info_type *, char **, char *, void *
#endif
);

/***** Typedef free_function *****/
/** This is of of the aux_free2_TYPE()-like functions.
  *
  * I.e., one that doesn't free the pointer itself!
  * @ingroup header_asn1
  */
typedef void SEC_API_CC free_function(
#if defined(USE_ANSI_PROTOTYPES)
	void *
#endif
);


typedef struct ASN1info_type {
    encode_function * encoder;
    decode_function * decoder;
    struct ASN1info_type *content;
    Boolean sort;
    sec_byte tagcl;
    unsigned int tagnum;
    char *name;
    free_function * free_fn; /* this is used in case of decode error */
} ASN1info_type;

#define NOTOK (-1)

#ifndef ASN1NEW
#define ASN1NEW(type) (type *)aux_calloc(1, sizeof(type))
#endif

#define ASN1n_NEW(into, type, desc) \
    if ( !(into = ASN1NEW(type)) ) {\
	aux_add_error( EMALLOC, desc, CNULL, 0, proc);\
	return NULL;\
    }

#define ASN1g_NEW(into, type, desc) \
    if ( !(into = ASN1NEW(type)) ) {\
	global_add_error( EMALLOC, desc, CNULL, 0, proc);\
	return NULL;\
    }

#define ASN1d_NEW(into, type, desc) \
    if ( !(into = ASN1NEW(type)) ) ASN1d_ERROR(desc)

#define SECUDE_ASN1_INCLUDE 1
#include <secude/asn1_p.h>
#undef SECUDE_ASN1_INCLUDE

#endif

