/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


#ifndef GSSAPI_H_
#define GSSAPI_H_




#include "sec_glob.h"


/*
 * First, define the platform-dependent types.
 */
typedef unsigned int gss_uint32;
typedef void * gss_ctx_id_t;
typedef void * gss_cred_id_t;
typedef void * gss_name_t;

/*
 * Note that a platform supporting the xom.h X/Open header file
 * may make use of that header for the definitions of OM_uint32
 * and the structure to which gss_OID_desc equates.
 */
typedef gss_uint32 OM_uint32;

typedef struct gss_OID_desc_struct {
      OM_uint32 length;
      void      *elements;
} gss_OID_desc, *gss_OID;


typedef struct gss_OID_set_desc_struct  {
      size_t     count;
      gss_OID elements;
} gss_OID_set_desc, *gss_OID_set;

typedef struct gss_buffer_desc_struct {
      size_t length;
      void *value;
} gss_buffer_desc, *gss_buffer_t;

typedef struct gss_channel_bindings_struct {
      OM_uint32 initiator_addrtype;
      gss_buffer_desc initiator_address;
      OM_uint32 acceptor_addrtype;
      gss_buffer_desc acceptor_address;
      gss_buffer_desc application_data;
} *gss_channel_bindings_t;

      /*
       * For now, define a QOP-type as an OM_uint32 (pending resolution
       * of ongoing discussions).
       */
      typedef OM_uint32 gss_qop_t;

      typedef int gss_cred_usage_t;


/*
 * Six independent flags each of which indicates that a context
 * supports a specific service option.
 */
#define GSS_C_DELEG_FLAG 1
#define GSS_C_MUTUAL_FLAG 2
#define GSS_C_REPLAY_FLAG 4
#define GSS_C_SEQUENCE_FLAG 8
#define GSS_C_CONF_FLAG 16
#define GSS_C_INTEG_FLAG 32
#define GSS_C_ANON_FLAG 64
#define GSS_C_PROT_READY_FLAG 128
#define GSS_C_TRANS_FLAG 256


/*
 * Credential usage options
 */
#define GSS_C_BOTH 0
#define GSS_C_INITIATE 1
#define GSS_C_ACCEPT 2

/*
 * Status code types for gss_display_status
 */
#define GSS_C_GSS_CODE 1
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

#define GSS_C_NO_BUFFER ((gss_buffer_t) 0)
#define GSS_C_NULL_OID ((gss_OID) 0)
#define GSS_C_NULL_OID_SET ((gss_OID_set) 0)
#define GSS_C_NO_OID ((gss_OID) 0)
#define GSS_C_NO_OID_SET ((gss_OID_set) 0)
#define GSS_C_NO_CONTEXT ((gss_ctx_id_t) 0)
#define GSS_C_NO_CREDENTIAL ((gss_cred_id_t) 0)
#define GSS_C_NO_CHANNEL_BINDINGS ((gss_channel_bindings_t) 0)
#define GSS_C_EMPTY_BUFFER {0, NULL}

/*
 * Define the default Quality of Protection for per-message
 * services.  Note that an implementation that offers multiple
 * levels of QOP may either reserve a value (for example zero,
 * as assumed here) to mean "default protection", or alternatively
 * may simply equate GSS_C_QOP_DEFAULT to a specific explicit QOP
 * value.
 */
#define GSS_C_QOP_DEFAULT 0
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
#define GSS_C_INDEFINITE (unsigned long)0xffffffff

      /*
       * The implementation must reserve static storage for a
       * gss_OID_desc object containing the value
       * {4, (void *)"}, and GSS_C_NAMETYPE_ANONYMOUS
       * should be initialized to point to that gss_OID_desc.
       */
extern gss_OID GSS_C_NAMETYPE_ANONYMOUS;




/* Major status codes */

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
#define GSS_CALLING_ERROR(x) \
  (x & (GSS_C_CALLING_ERROR_MASK << GSS_C_CALLING_ERROR_OFFSET))
#define GSS_ROUTINE_ERROR(x) \
  (x & (GSS_C_ROUTINE_ERROR_MASK << GSS_C_ROUTINE_ERROR_OFFSET))
#define GSS_SUPPLEMENTARY_INFO(x) \
  (x & (GSS_C_SUPPLEMENTARY_MASK << GSS_C_SUPPLEMENTARY_OFFSET))
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
#define GSS_S_CONTINUE_NEEDED ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 0))
#define GSS_S_DUPLICATE_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 1))
#define GSS_S_OLD_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 2))
#define GSS_S_UNSEQ_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 3))
#define GSS_S_GAP_TOKEN ((unsigned long)1 << (GSS_C_SUPPLEMENTARY_OFFSET + 4))



#include "gssapi_p.h"


#endif /* GSSAPI_H_ */

