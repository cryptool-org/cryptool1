/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


#ifndef ASN1_H_
#define ASN1_H_

#include "sec_glob.h" 

/*typedef char PrintableString;*/
/*typedef char IA5String;*/
/*typedef char VisibleString;*/
typedef OctetString BMPString;
typedef OctetString Long;
typedef OctetString DERcode;
typedef int Integer;
typedef unsigned int UInteger;

typedef char UTF8String; /* should work; 0x00 == end-of-string, only length not through strlen!!! */

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

typedef enum ASN1memorymode {
    ASN1memory_undef = 0,
    ASN1memory_link,
    ASN1memory_new,
    ASN1memory_inherit
} ASN1memorymode;

typedef struct ASN1global {
    ASN1descriptor *descriptor;
    int dsize;
    int dpos;
    ASN1memorymode mode; /* how to handle large memory given to encoding */
                      /* functions: just point to it, copy it or inherit */
              /* inherit it (set a pointer to it and free it (after use) */
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

typedef OctetString * SEC_API_CC e_function(
#if defined(USE_ANSI_PROTOTYPES)
	void *
#endif
);
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

typedef int SEC_API_CC encode_function(
#if defined(USE_ANSI_PROTOTYPES)
	struct ASN1info_type *, ASN1global *, void *
#endif
);
typedef void * SEC_API_CC decode_function(
#if defined(USE_ANSI_PROTOTYPES)
	struct ASN1info_type *, char **, char *, void *
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
} ASN1info_type;
    
#define NOTOK (-1)

#define ASN1NEW(type) (type *)calloc(1, sizeof(type))

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

#endif

