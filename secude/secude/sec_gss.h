/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/sec_gss.h
 *###
 *### global functions:
 *###
 *###*****************************************/


#ifndef SEC_GSS_H_
#define SEC_GSS_H_

#include <secude/af.h>
#include <secude/gssapi.h>
#include <secude/asn1.h>







typedef struct SECGSSCTX SECGSSCTX;
typedef enum {
	SEC_GSS_ESTABLISHED_INI, 
	SEC_GSS_ESTABLISHED_ACC, 
	SEC_GSS_INIT_STATE, 
	SEC_GSS_BUILD_REQ, 
	SEC_GSS_PARSE_REQ, 
	SEC_GSS_BUILD_REPTI, 
	SEC_GSS_PARSE_REPTI, 
	SEC_GSS_BUILD_REPIT, 
	SEC_GSS_PARSE_REPIT,
	SEC_GSS_BUILD_ERROR_ACC,
	SEC_GSS_BUILD_ERROR_INI
} SEC_GSS_STATE;

#define SYM_KEY_MAX_LENGTH 36

#define SECUDE_0_ID    0
#define SPKM_1_ID    1
#define SPKM_2_ID    2

#define SPKM_DEF_ID SECUDE_0_ID
#define SPKM_DEF_ASN1 SECUDE_0_ASN1
#define SPKM_DEF SECUDE_0

#define ASN1_OBJID_TAG	  '\006'
#define SECUDE_0_OID      '\053','\044','\003','\001','\045','\001' 
#define SECUDE_NAME_OID   '\053','\044','\003','\001','\046','\001'


#ifdef SPKM_INSTALLED
#include <secude/spkm.h>
#endif

typedef struct  {
	DName *name;
	gss_OID mech;
} GssName;
/*typedef void  GssName;*/

struct SECGSSCTX {
  int 		version;
  char		*algs;
  char		*hashalgs;
  int               state;
  char		   *trace;
  char		   *trace_env;
  int		    trace_lev;
  FILE		   *trc;
  int		    own_seq_num;
  int		    peer_seq_num;
  OctetString      *key;
  char	           *utctime;
  OM_uint32         req_flags;
  OM_uint32         flags;
  DName	           *peer_name;
  OM_uint32         mech_id;
  OctetString      *mech_type;
  Cred			*cred;
  
  ObjId            *own_key_oid;
  KeyInfo          *own_key;
  KeyInfo          *recp_key;
  void    	   *pse;
#ifdef SPKM_INSTALLED
  BitString        *contextid;
  SEQUENCE_OF_SessionKey *c_key;
  SEQUENCE_OF_SessionKey *i_key;
  

  AlgId	           *o_alg;
  ContextData      *context_data;
  KeyInfo          *recp_vkey;
#endif
};

typedef struct QOP_LIST QOP_LIST;
struct QOP_LIST {
	AlgId    *algid;
	int  	  keysize;

};



OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_acquire_cred SEC_PROTOTYPE_8
           (OM_uint32*,       minor_status,
            GssName *,       desired_name,
            OM_uint32,        time_req,
            gss_OID_set,      desired_mechs,
            gss_cred_usage_t, cred_usage,
            gss_cred_id_t*,   output_cred_handle,
            gss_OID_set*,     actual_mechs,
            OM_uint32*,        time_rec
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_add_cred SEC_PROTOTYPE_11(
            OM_uint32 *,        minor_status,
            gss_cred_id_t,      input_cred_handle,
            GssName *,         desired_name,
            gss_OID,            desired_mech,
            gss_cred_usage_t,   cred_usage,
            OM_uint32,          initiator_time_req,
            OM_uint32,          acceptor_time_req,
            gss_cred_id_t *,    output_cred_handle,
            gss_OID_set *,      actual_mechs,
            OM_uint32 *,        initiator_time_rec,
            OM_uint32 *,         acceptor_time_rec
           );
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_release_cred SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_cred_id_t*,    cred_handle
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_init_sec_context SEC_PROTOTYPE_13
           (OM_uint32*,       minor_status,
            gss_cred_id_t,    claimant_cred_handle,
            SECGSSCTX **,    context_handle,
            GssName *,       target_name,
            gss_OID,          mech_type,
            OM_uint32,        req_flags,
            OM_uint32,        time_req,
            gss_channel_bindings_t,
                              input_chan_bindings,
            gss_buffer_t,     input_token,
            gss_OID*,         actual_mech_type,
            gss_buffer_t,     output_token,
            OM_uint32*,       ret_flags,
            OM_uint32*,        time_rec
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_accept_sec_context SEC_PROTOTYPE_11
           (OM_uint32*,       minor_status,
            SECGSSCTX **,    context_handle,
            gss_cred_id_t,    verifier_cred_handle,
            gss_buffer_t,     input_token_buffer,
            gss_channel_bindings_t,
                              input_chan_bindings,
            GssName **,      src_name,
            gss_OID*,         mech_type,
            gss_buffer_t,     output_token,
            OM_uint32*,       ret_flags,
            OM_uint32*,       time_rec,
            gss_cred_id_t*,    delegated_cred_handle
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_process_context_token SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            SECGSSCTX *,     context_handle,
            gss_buffer_t,      token_buffer
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_delete_sec_context SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            SECGSSCTX **,    context_handle,
            gss_buffer_t,      output_token
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_context_time SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            SECGSSCTX *,     context_handle,
            OM_uint32*,        time_rec
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_get_mic SEC_PROTOTYPE_5
           (OM_uint32*,       minor_status,
            SECGSSCTX *,     context_handle,
            gss_qop_t,        qop_req,
            gss_buffer_t,     message_buffer,
            gss_buffer_t,      message_token
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_verify_mic SEC_PROTOTYPE_5
           (OM_uint32*,       minor_status,
            SECGSSCTX *,     context_handle,
            gss_buffer_t,     message_buffer,
            gss_buffer_t,     token_buffer,
            gss_qop_t*,        qop_state
           );
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_wrap SEC_PROTOTYPE_7
           (OM_uint32*,       minor_status,
            SECGSSCTX *,     context_handle,
            int,              conf_req_flag,
            gss_qop_t,        qop_req,
            gss_buffer_t,     input_message_buffer,
            int*,             conf_state,
            gss_buffer_t,      output_message_buffer
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_unwrap SEC_PROTOTYPE_6
           (OM_uint32*,       minor_status,
            SECGSSCTX *,     context_handle,
            gss_buffer_t,     input_message_buffer,
            gss_buffer_t,     output_message_buffer,
            int*,             conf_state,
            gss_qop_t*,        qop_state
           );
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_display_status SEC_PROTOTYPE_6
           (OM_uint32*,       minor_status,
            OM_uint32,        status_value,
            int,              status_type,
            gss_OID,          mech_type,
            OM_uint32*,       message_context,
            gss_buffer_t,      status_string
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_indicate_mechs SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_OID_set*,      mech_set
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_compare_name SEC_PROTOTYPE_4
           (OM_uint32*,       minor_status,
            GssName *,       name1,
            GssName *,       name2,
            int*,             name_equal
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_display_name SEC_PROTOTYPE_4
           (OM_uint32*,      minor_status,
            GssName *,      input_name,
            gss_buffer_t,     output_name_buffer,
            gss_OID*,        output_name_type
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_import_name SEC_PROTOTYPE_4
           (OM_uint32*,       minor_status,
            gss_buffer_t,     input_name_buffer,
            gss_OID,          input_name_type,
            GssName **,       output_name
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_release_name SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            GssName **,       input_name
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_release_buffer SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_buffer_t,      buffer
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_release_oid_set SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_OID_set*,      set
           );
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_release_oid SEC_PROTOTYPE_2(
                  OM_uint32 *,        minor_status,
                  gss_OID *,           oid
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_create_empty_oid_set SEC_PROTOTYPE_2(
                  OM_uint32 *,        minor_status,
                  gss_OID_set *,       oid_set
                 );


OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_add_oid_set_member SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_OID,            member_oid,
                  gss_OID_set *,       oid_set
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_test_oid_set_member SEC_PROTOTYPE_4(
                  OM_uint32 *,        minor_status,
                  gss_OID,            member,
                  gss_OID_set,        set,
                  int *,               present
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_str_to_oid SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_buffer_t,       oid_str,
                  gss_OID *,           oid
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_oid_to_str SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_OID,            oid,
                  gss_buffer_t,        oid_str
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_inquire_names_for_mech SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_OID,            mechanism,
                  gss_OID_set *,       name_types
                 );


OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_inquire_cred SEC_PROTOTYPE_6
           (OM_uint32 *,      minor_status,
            gss_cred_id_t,    cred_handle,
            GssName * *,     name,
            OM_uint32 *,      lifetime,
            int *,            cred_usage,
            gss_OID_set *,     mechanisms
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_export_sec_context SEC_PROTOTYPE_3
           (OM_uint32 *,      minor_status,
            SECGSSCTX **,   context_handle,
            gss_buffer_t,      interprocess_token
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_import_sec_context SEC_PROTOTYPE_3
           (OM_uint32 *,      minor_status,
            gss_buffer_t,     interprocess_token,
            SECGSSCTX **,    context_handle
           );


OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_inquire_context SEC_PROTOTYPE_9(
                  OM_uint32 *,        minor_status,
                  SECGSSCTX *,       context_handle,
                  GssName * *,       src_name,
                  GssName * *,       targ_name,
                  OM_uint32 *,        lifetime_rec,
                  gss_OID *,          mech_type,
                  OM_uint32 *,        ctx_flags,
                  int *,              locally_initiated,
                  int *,               open
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_wrap_size_limit SEC_PROTOTYPE_6(
                  OM_uint32 *,        minor_status,
                  SECGSSCTX *,       context_handle,
                  int,                conf_req_flag,
                  gss_qop_t,          qop_req,
                  OM_uint32,          req_output_size,
                  OM_uint32 *,         max_input_size
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_inquire_cred_by_mech SEC_PROTOTYPE_7(
                  OM_uint32  *,       minor_status,
                  gss_cred_id_t,      cred_handle,
                  gss_OID,            mech_type,
                  GssName * *,       name,
                  OM_uint32 *,        initiator_lifetime,
                  OM_uint32 *,        acceptor_lifetime,
                  gss_cred_usage_t *,  cred_usage
                 );
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_export_name SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  GssName *,         input_name,
                  gss_buffer_t,       exported_name
		 );
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_canonicalize_name SEC_PROTOTYPE_4(
                  OM_uint32 *,        minor_status,
                  GssName *,         input_name,
                  gss_OID,            mech_type,
                  GssName * *,       output_name
		 );
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_duplicate_name SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            GssName *,       src_name,
            GssName * *,      dest_name
           );
char SEC_GLOBAL_FUNC_PREFIX * SEC_API_CALLING_CONV aux_sprint_Options SEC_PROTOTYPE_2(
	char *, string,
	int, data
);
RC  SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_print_SECGSSCTX SEC_PROTOTYPE_1(
	SECGSSCTX	 *	, gssctx
);
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV sec_gss_inquire_mechs_for_name SEC_PROTOTYPE_3(
                  OM_uint32  *,       minor_status,
                  GssName *,        input_name,
                  gss_OID_set *,  mech_types
                 );

D_PROTOTYPE(GSS,SECGSSCTX)
E_PROTOTYPE(GSS,SECGSSCTX)

ASN1_en_de_PROTO(SECGSSCTX)
extern ASN1info_type SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX ASN1info_SECGSSCTX;

RC gss_init(OM_uint32 *maj, OM_uint32 *min);
#define INITGSS {OM_uint32 maj;if(gss_init(&maj, minor_status) < 0) return(maj);}

extern RC gss_verify_Certificates
(
 PSE pse
 , Certificates * p_certs
 , UTCTime * szTime
 , PKRoot * pRoot
 );

#endif /* SEC_GSS_H_ */

