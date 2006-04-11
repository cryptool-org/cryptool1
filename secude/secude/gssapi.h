/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/gssapi.h
 *###
 *### global functions:
 *###
 *###*****************************************/


#ifndef GSSAPI_H_
#define GSSAPI_H_




#include <secude/sec_glob.h>


/*
 * First, define the platform-dependent types.
 */
/***** Typedef gss_uint32 *****/
/** @ingroup header_gss
  */
typedef unsigned int gss_uint32;
/***** Typedef gss_ctx_id_t *****/
/** value is a context handle
  * @ingroup header_gss
  */
typedef void * gss_ctx_id_t;
/***** Typedef gss_cred_id_t *****/
/** value is a credential handle
  * @ingroup header_gss
  */
typedef void * gss_cred_id_t;
/***** Typedef gss_name_t *****/
/** value is a C-String
  * @ingroup header_gss
  */
typedef void * gss_name_t;

/*
 * Note that a platform supporting the xom.h X/Open header file
 * may make use of that header for the definitions of OM_uint32
 * and the structure to which gss_OID_desc equates.
 */
/***** Typedef OM_uint32 *****/
/** value is a 32 bit unsigned integer 
  * @ingroup header_gss
  */
typedef gss_uint32 OM_uint32;

/***** Structure gss_OID_desc_struct *****/
/** GSS-API structure.
  * <B>Typedef:</B> <TT>typedef struct gss_OID_desc_struct #gss_OID_desc;</TT><BR>
  * <B>Typedef:</B> <TT>typedef struct gss_OID_desc_struct *#gss_OID;</TT>
  * @ingroup header_gss
  */
struct gss_OID_desc_struct {
/** The length of the buffer */
      OM_uint32 length;
/** The buffer containing the ASN.1 encoded object identifier */
      void      *elements;
};
/***** Typedef gss_OID_desc *****/
/** @ingroup header_gss
  */
typedef struct gss_OID_desc_struct gss_OID_desc;
/***** Typedef gss_OID *****/
/** @ingroup header_gss
  */
typedef struct gss_OID_desc_struct *gss_OID;


/***** Structure gss_OID_set_desc_struct *****/
/** GSS-API structure.
  * <B>Typedef:</B> <TT>typedef struct gss_OID_set_desc_struct #gss_OID_set_desc;</TT><BR>
  * <B>Typedef:</B> <TT>typedef struct gss_OID_set_desc_struct *#gss_OID_set;</TT>
  * @ingroup header_gss
  */
struct gss_OID_set_desc_struct  {
/** The number of object identifiers */
      size_t     count;
/** The array of object identifiers */
      gss_OID elements;
};
/***** Typedef gss_OID_set_desc *****/
/** @ingroup header_gss
  */
typedef struct gss_OID_set_desc_struct gss_OID_set_desc;
/***** Typedef gss_OID_set *****/
/** @ingroup header_gss
  */
typedef struct gss_OID_set_desc_struct *gss_OID_set;

/***** Structure gss_buffer_desc_struct *****/
/** GSS-API structure.
  * <B>Typedef:</B> <TT>typedef struct gss_buffer_desc_struct #gss_buffer_desc;</TT><BR>
  * <B>Typedef:</B> <TT>typedef struct gss_buffer_desc_struct *#gss_buffer_t;</TT>
  * @ingroup header_gss
  */
struct gss_buffer_desc_struct {
/** The length of the buffer in octets */
      size_t length;
/** The buffer */
      void *value;
};
/***** Typedef gss_buffer_desc *****/
/** @ingroup header_gss
  */
typedef struct gss_buffer_desc_struct gss_buffer_desc;
/***** Typedef gss_buffer_t *****/
/** @ingroup header_gss
  */
typedef struct gss_buffer_desc_struct *gss_buffer_t;

/***** Structure gss_channel_bindings_struct *****/
/** GSS-API structure.
  * <B>Typedef:</B> <TT>typedef struct gss_channel_bindings_struct *#gss_channel_bindings_t;</TT>
  * @ingroup header_gss
  */
struct gss_channel_bindings_struct {
      OM_uint32 initiator_addrtype;
      gss_buffer_desc initiator_address;
      OM_uint32 acceptor_addrtype;
      gss_buffer_desc acceptor_address;
      gss_buffer_desc application_data;
};
/***** Typedef gss_channel_bindings_t *****/
/** @ingroup header_gss
  */
typedef struct gss_channel_bindings_struct *gss_channel_bindings_t;

      /*
       * For now, define a QOP-type as an OM_uint32 (pending resolution
       * of ongoing discussions).
       */
/***** Typedef gss_qop_t *****/
/** @ingroup header_gss
  */
      typedef OM_uint32 gss_qop_t;

/***** Typedef gss_cred_usage_t *****/
/** @ingroup header_gss
  */
      typedef int gss_cred_usage_t;


/*
 * Six independent flags each of which indicates that a context
 * supports a specific service option.
 */
/***** #define GSS_C_DELEG_FLAG *****/
/** <B>This feature is not supported by SecuDE</B><BR>
  * True - Credentials were delegated from
  * the initiator to the acceptor<BR>
  * False - No credentials were delegated
  * @ingroup header_gss
  */
#define GSS_C_DELEG_FLAG 1
/***** #define GSS_C_MUTUAL_FLAG *****/
/** True - The acceptor was authenticated
  * to the initiator<BR>
  * False - The acceptor did not authenticate
  * itself
  * @ingroup header_gss
  */
#define GSS_C_MUTUAL_FLAG 2
/***** #define GSS_C_REPLAY_FLAG *****/
/** True - replay of protected messages
  * will be detected<BR>
  * False - replayed messages will not be
  * detected
  * @ingroup header_gss
  */
#define GSS_C_REPLAY_FLAG 4
/***** #define GSS_C_SEQUENCE_FLAG *****/
/** True - out-of-sequence protected
  * messages will be detected<BR>
  * False - out-of-sequence messages will not
  * be detected
  * @ingroup header_gss
  */
#define GSS_C_SEQUENCE_FLAG 8
/***** #define GSS_C_CONF_FLAG *****/
/** True - Confidentiality service may be invoked
  * by calling #gss_wrap routine<BR>
  * False - No confidentiality service (via
  * gss_wrap) available.\  gss_wrap will
  * provide message encapsulation,
  * data-origin authentication and
  * integrity services only
  * @ingroup header_gss
  */
#define GSS_C_CONF_FLAG 16
/***** #define GSS_C_INTEG_FLAG *****/
/** True - Integrity service may be invoked by
  * calling either #gss_get_mic or #gss_wrap
  * routines<BR>
  * False - Per-message integrity service
  * unavailable
  * @ingroup header_gss
  */
#define GSS_C_INTEG_FLAG 32
/***** #define GSS_C_ANON_FLAG *****/
/** <B>This feature is not supported by SecuDE</B><BR>
  * True - The initiator's identity will not
  * be revealed to the acceptor.\ 
  * The src_name parameter (if
  * requested) contains an anonymous
  * internal name<BR>
  * False - Per-message integrity service
  * unavailable
  * @ingroup header_gss
  */
#define GSS_C_ANON_FLAG 64
#define GSS_C_PROT_READY_FLAG 128
#define GSS_C_TRANS_FLAG 256


/*
 * Credential usage options
 */
/***** #define GSS_C_BOTH *****/
/** Credentials may be used
  * either to initiate or accept
  * security contexts
  * @ingroup header_gss
  */
#define GSS_C_BOTH 0
/***** #define GSS_C_INITIATE *****/
/** Credentials will only be
  * used to initiate security
  * contexts
  * @ingroup header_gss
  */
#define GSS_C_INITIATE 1
/***** #define GSS_C_ACCEPT *****/
/** Credentials will only be used to
  * accept security contexts
  * @ingroup header_gss
  */
#define GSS_C_ACCEPT 2

/*
 * Status code types for gss_display_status
 */
/***** #define GSS_C_GSS_CODE *****/
/** status_value is a GSS status
  * code
  * @ingroup header_gss
  */
#define GSS_C_GSS_CODE 1
/***** #define GSS_C_MECH_CODE *****/
/** status_value is a mechanism
  * status code
  * @ingroup header_gss
  */
#define GSS_C_MECH_CODE 2

/*
 * The constant definitions for channel-bindings address families
 */
#define GSS_C_AF_UNSPEC     0;
#define GSS_C_AF_LOCAL      1;
#define GSS_C_AF_INET       2;
#define GSS_C_AF_IMPLINK    3;
#define GSS_C_AF_PUP        4;
#define GSS_C_AF_CHAOS      5;
#define GSS_C_AF_NS         6;
#define GSS_C_AF_NBS        7;
#define GSS_C_AF_ECMA       8;
#define GSS_C_AF_DATAKIT    9;
#define GSS_C_AF_CCITT      10;
#define GSS_C_AF_SNA        11;
#define GSS_C_AF_DECnet     12;
#define GSS_C_AF_DLI        13;
#define GSS_C_AF_LAT        14;
#define GSS_C_AF_HYLINK     15;
#define GSS_C_AF_APPLETALK  16;
#define GSS_C_AF_BSC        17;
#define GSS_C_AF_DSS        18;
#define GSS_C_AF_OSI        19;
#define GSS_C_AF_X25        21;

#define GSS_C_AF_NULLADDR   255;

/***** #define GSS_C_NO_BUFFER *****/
/** NULL pointer
  * @ingroup header_gss
  */
#define GSS_C_NO_BUFFER ((gss_buffer_t) 0)
/***** #define GSS_C_NULL_OID *****/
/** NULL pointer
  * @ingroup header_gss
  */
#define GSS_C_NULL_OID ((gss_OID) 0)
/***** #define GSS_C_NULL_OID_SET *****/
/** NULL pointer
  * @ingroup header_gss
  */
#define GSS_C_NULL_OID_SET ((gss_OID_set) 0)
#define GSS_C_NO_OID ((gss_OID) 0)
#define GSS_C_NO_OID_SET ((gss_OID_set) 0)
/***** #define GSS_C_NO_CONTEXT *****/
/** Value for no context
  * @ingroup header_gss
  */
#define GSS_C_NO_CONTEXT ((gss_ctx_id_t) 0)
/***** #define GSS_C_NO_CREDENTIAL *****/
/** Value for no credential
  * @ingroup header_gss
  */
#define GSS_C_NO_CREDENTIAL ((gss_cred_id_t) 0)
#define GSS_C_NO_CHANNEL_BINDINGS ((gss_channel_bindings_t) 0)
/***** #define GSS_C_EMPTY_BUFFER *****/
/** Value for empty buffer
  * @ingroup header_gss
  */
#define GSS_C_EMPTY_BUFFER {0, NULL}

/*
 * Define the default Quality of Protection for per-message
 * services.  Note that an implementation that offers multiple
 * levels of QOP may either reserve a value (for example zero,
 * as assumed here) to mean "default protection", or alternatively
 * may simply equate GSS_C_QOP_DEFAULT to a specific explicit QOP
 * value.
 */
/***** #define GSS_C_QOP_DEFAULT *****/
/** default quality of protection
  * @ingroup header_gss
  */
#define GSS_C_QOP_DEFAULT 0
#define GSS_C_QOP_AES256 6
#define GSS_C_QOP_AES192 5
#define GSS_C_QOP_AES128 4
#define GSS_C_QOP_DES 3
#define GSS_C_QOP_DES3 2
#define GSS_C_QOP_IDEA 1
#define GSS_C_QOP_MD5 0
#define GSS_C_QOP_SHA1 1
#define GSS_C_QOP_RIPEMD160 2
#define GSS_C_QOP_INTERNAL_DEFAULT GSS_C_QOP_DES 

/*
 * Expiration time of 2^32-1 seconds means infinite lifetime for a
 * credential or security context
 */
/***** #define GSS_C_INDEFINITE *****/
/** infinite lifetime
  * @ingroup header_gss
  */
#define GSS_C_INDEFINITE (unsigned long)0xffffffff

      /*
       * The implementation must reserve static storage for a
       * gss_OID_desc object containing the value
       * {4, (void *)"}, and GSS_C_NAMETYPE_ANONYMOUS
       * should be initialized to point to that gss_OID_desc.
       */
extern gss_OID GSS_C_NAMETYPE_ANONYMOUS;




/* Major status codes */

/***** #define GSS_S_COMPLETE *****/
/** Return code for success
  * @ingroup header_gss
  */
#define GSS_S_COMPLETE 0

/*
 * Some "helper" definitions to make the status code macros obvious.
 */
#define GSS_C_CALLING_ERROR_OFFSET 24
#define GSS_C_ROUTINE_ERROR_OFFSET 16
#define GSS_C_SUPPLEMENTARY_OFFSET 0
#define GSS_C_CALLING_ERROR_MASK (unsigned long)0377
#define GSS_C_ROUTINE_ERROR_MASK (unsigned long)0377
#define GSS_C_SUPPLEMENTARY_MASK (unsigned long)0177777

/*
 * The macros that test status codes for error conditions
 */
/***** #define GSS_CALLING_ERROR(x) *****/
/** Returns the calling error part of x
  * @ingroup header_gss
  */
#define GSS_CALLING_ERROR(x) \
  (x & (GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET))
/***** #define GSS_ROUTINE_ERROR(x) *****/
/** Returns the routine error part of x
  * @ingroup header_gss
  */
#define GSS_ROUTINE_ERROR(x) \
  (x & (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))
/***** #define GSS_SUPPLEMENTARY_INFO(x) *****/
/** Returns the supplementary info part of x
  * @ingroup header_gss
  */
#define GSS_SUPPLEMENTARY_INFO(x) \
  (x & (GSS_C_SUPPLEMENTARY_MASK << GSS_C_SUPPLEMENTARY_OFFSET))
/***** #define GSS_ERROR(x) *****/
/** True - x is an error<BR>
  * False - x is no error
  * @ingroup header_gss
  */
#define GSS_ERROR(x) \
  ((GSS_CALLING_ERROR(x) != 0) || (GSS_ROUTINE_ERROR(x) != 0))


/*
 * Now the actual status code definitions
 */

/*
 * Calling errors:
 */
#define GSS_S_CALL_INACCESSIBLE_READ \
                             ((unsigned long)1 << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_INACCESSIBLE_WRITE \
                             ((unsigned long)2 << GSS_C_CALLING_ERROR_OFFSET)
#define GSS_S_CALL_BAD_STRUCTURE \
                             ((unsigned long)3 << GSS_C_CALLING_ERROR_OFFSET)

/*
 * Routine errors:
 */
#define GSS_S_BAD_MECH ((unsigned long)1 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAME ((unsigned long)2 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_NAMETYPE ((unsigned long)3 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_BINDINGS ((unsigned long)4 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_STATUS ((unsigned long)5 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_SIG ((unsigned long)6 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NO_CRED ((unsigned long)7 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_NO_CONTEXT ((unsigned long)8 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_TOKEN ((unsigned long)9 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_DEFECTIVE_CREDENTIAL ((unsigned long)10 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CREDENTIALS_EXPIRED ((unsigned long)11 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_CONTEXT_EXPIRED ((unsigned long)12 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_FAILURE ((unsigned long)13 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_BAD_QOP ((unsigned long)14 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_UNAUTHORIZED ((unsigned long)15 << GSS_C_ROUTINE_ERROR_OFFSET)
#define GSS_S_UNAVAILABLE ((unsigned long)16 << GSS_C_ROUTINE_ERROR_OFFSET)

/*
 * Supplementary info bits:
 */
/***** #define GSS_S_CONTINUE_NEEDED *****/
/** Return code for necessary continuation of context establishment
  * @ingroup header_gss
  */
#define GSS_S_CONTINUE_NEEDED ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 0))
#define GSS_S_DUPLICATE_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 1))
#define GSS_S_OLD_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 2))
#define GSS_S_UNSEQ_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 3))
#define GSS_S_GAP_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 4))


#define SECUDE_GSS_INCLUDE 1
#include <secude/gssapi_p.h>
#undef SECUDE_GSS_INCLUDE


#endif /* GSSAPI_H_ */

