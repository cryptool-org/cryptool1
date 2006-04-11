/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/gssapi_p.h
 *###
 *### global functions:
 *###
 *###*****************************************/

#if !defined(SECUDE_GSS_INCLUDE) || !SECUDE_GSS_INCLUDE
#error do not include this file, include <secude/gssapi.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


extern gss_OID SEC_GLOBAL_FUNC_PREFIX SEC_GLOBAL_VAR_PREFIX  SECUDE_0, SPKM_1, SPKM_2;

/* from GSSAPI routines : */

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_accept_sec_context SEC_PROTOTYPE_11
           (OM_uint32*,       minor_status,
            gss_ctx_id_t*,    context_handle,
            gss_cred_id_t,    verifier_cred_handle,
            gss_buffer_t,     input_token_buffer,
            gss_channel_bindings_t,
                              input_chan_bindings,
            gss_name_t*,      src_name,
            gss_OID*,         mech_type,
            gss_buffer_t,     output_token,
            OM_uint32*,       ret_flags,
            OM_uint32*,       time_rec,
            gss_cred_id_t*,    delegated_cred_handle
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_acquire_cred SEC_PROTOTYPE_8
           (OM_uint32*,       minor_status,
            gss_name_t,       desired_name,
            OM_uint32,        time_req,
            gss_OID_set,      desired_mechs,
            gss_cred_usage_t, cred_usage,
            gss_cred_id_t*,   output_cred_handle,
            gss_OID_set*,     actual_mechs,
            OM_uint32*,        time_rec
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_add_cred SEC_PROTOTYPE_11(
            OM_uint32 *,        minor_status,
            gss_cred_id_t,      input_cred_handle,
            gss_name_t,         desired_name,
            gss_OID,            desired_mech,
            gss_cred_usage_t,   cred_usage,
            OM_uint32,          initiator_time_req,
            OM_uint32,          acceptor_time_req,
            gss_cred_id_t *,    output_cred_handle,
            gss_OID_set *,      actual_mechs,
            OM_uint32 *,        initiator_time_rec,
            OM_uint32 *,         acceptor_time_rec
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_add_oid_set_member SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_OID,            member_oid,
                  gss_OID_set *,       oid_set
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_canonicalize_name SEC_PROTOTYPE_4(
                  OM_uint32 *,        minor_status,
                  gss_name_t,         input_name,
                  gss_OID,            mech_type,
                  gss_name_t *,       output_name
		 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_compare_name SEC_PROTOTYPE_4
           (OM_uint32*,       minor_status,
            gss_name_t,       name1,
            gss_name_t,       name2,
            int*,              name_equal
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_context_time SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            OM_uint32*,        time_rec
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_create_empty_oid_set SEC_PROTOTYPE_2(
                  OM_uint32 *,        minor_status,
                  gss_OID_set *,       oid_set
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_delete_sec_context SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            gss_ctx_id_t*,    context_handle,
            gss_buffer_t,      output_token
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_display_name SEC_PROTOTYPE_4
           (OM_uint32*,      minor_status,
            gss_name_t,      input_name,
            gss_buffer_t,     output_name_buffer,
            gss_OID*,         output_name_type
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_display_status SEC_PROTOTYPE_6
           (OM_uint32*,       minor_status,
            OM_uint32,        status_value,
            int,              status_type,
            gss_OID,          mech_type,
            OM_uint32*,       message_context,
            gss_buffer_t,      status_string
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_duplicate_name SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            gss_name_t,       src_name,
            gss_name_t *,      dest_name
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_export_name SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_name_t,         input_name,
                  gss_buffer_t,       exported_name
		 );
 
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_export_sec_context SEC_PROTOTYPE_3
           (OM_uint32 *,      minor_status,
            gss_ctx_id_t *,   context_handle,
            gss_buffer_t,      interprocess_token
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_get_mic SEC_PROTOTYPE_5
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            gss_qop_t,        qop_req,
            gss_buffer_t,     message_buffer,
            gss_buffer_t,      message_token
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_import_name SEC_PROTOTYPE_4
           (OM_uint32*,       minor_status,
            gss_buffer_t,     input_name_buffer,
            gss_OID,          input_name_type,
            gss_name_t*,       output_name
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_import_sec_context SEC_PROTOTYPE_3
           (OM_uint32 *,      minor_status,
            gss_buffer_t,     interprocess_token,
            gss_ctx_id_t *,    context_handle
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_indicate_mechs SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_OID_set*,      mech_set
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_init_sec_context SEC_PROTOTYPE_13
           (OM_uint32*,       minor_status,
            gss_cred_id_t,    claimant_cred_handle,
            gss_ctx_id_t*,    context_handle,
            gss_name_t,       target_name,
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

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_inquire_context SEC_PROTOTYPE_9(
                  OM_uint32 *,        minor_status,
                  gss_ctx_id_t,       context_handle,
                  gss_name_t *,       src_name,
                  gss_name_t *,       targ_name,
                  OM_uint32 *,        lifetime_rec,
                  gss_OID *,          mech_type,
                  OM_uint32 *,        ctx_flags,
                  int *,              locally_initiated,
                  int *,               open
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_inquire_cred SEC_PROTOTYPE_6
           (OM_uint32 *,      minor_status,
            gss_cred_id_t,    cred_handle,
            gss_name_t *,     name,
            OM_uint32 *,      lifetime,
            int *,            cred_usage,
            gss_OID_set *,     mechanisms
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_inquire_cred_by_mech SEC_PROTOTYPE_7(
                  OM_uint32  *,       minor_status,
                  gss_cred_id_t,      cred_handle,
                  gss_OID,            mech_type,
                  gss_name_t *,       name,
                  OM_uint32 *,        initiator_lifetime,
                  OM_uint32 *,        acceptor_lifetime,
                  gss_cred_usage_t *,  cred_usage
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_inquire_mechs_for_name SEC_PROTOTYPE_3(
                  OM_uint32  *,       minor_status,
                  gss_name_t,        input_name,
                  gss_OID_set *,  mech_types
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_inquire_names_for_mech SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_OID,            mechanism,
                  gss_OID_set *,       name_types
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_process_context_token SEC_PROTOTYPE_3
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            gss_buffer_t,      token_buffer
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_release_buffer SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_buffer_t,      buffer
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_release_cred SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_cred_id_t*,    cred_handle
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_release_name SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_name_t*,       input_name
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_release_oid_set SEC_PROTOTYPE_2
           (OM_uint32*,       minor_status,
            gss_OID_set*,      set
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_seal SEC_PROTOTYPE_7
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            int,              conf_req_flag,
            int,        qop_req,
            gss_buffer_t,     input_message_buffer,
            int*,             conf_state,
            gss_buffer_t,      output_message_buffer
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_sign SEC_PROTOTYPE_5
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            int,        qop_req,
            gss_buffer_t,     message_buffer,
            gss_buffer_t,      message_token
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_test_oid_set_member SEC_PROTOTYPE_4(
                  OM_uint32 *,        minor_status,
                  gss_OID,            member,
                  gss_OID_set,        set,
                  int *,               present
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_unseal SEC_PROTOTYPE_6
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            gss_buffer_t,     input_message_buffer,
            gss_buffer_t,     output_message_buffer,
            int*,             conf_state,
            int*,        qop_state
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_unwrap SEC_PROTOTYPE_6
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            gss_buffer_t,     input_message_buffer,
            gss_buffer_t,     output_message_buffer,
            int*,             conf_state,
            gss_qop_t*,        qop_state
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_verify SEC_PROTOTYPE_5
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            gss_buffer_t,     message_buffer,
            gss_buffer_t,     token_buffer,
            int *,        qop_state
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_verify_mic SEC_PROTOTYPE_5
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            gss_buffer_t,     message_buffer,
            gss_buffer_t,     token_buffer,
            gss_qop_t*,        qop_state
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_wrap SEC_PROTOTYPE_7
           (OM_uint32*,       minor_status,
            gss_ctx_id_t,     context_handle,
            int,              conf_req_flag,
            gss_qop_t,        qop_req,
            gss_buffer_t,     input_message_buffer,
            int*,             conf_state,
            gss_buffer_t,      output_message_buffer
           );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_wrap_size_limit SEC_PROTOTYPE_6(
                  OM_uint32 *,        minor_status,
                  gss_ctx_id_t,       context_handle,
                  int,                conf_req_flag,
                  gss_qop_t,          qop_req,
                  OM_uint32,          req_output_size,
                  OM_uint32 *,         max_input_size
                 );




/*********************************************** 
 * SPKM function
 ***********************************************/
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV spkm_parse_token SEC_PROTOTYPE_5
			(OM_uint32*,		minor_status, 
			gss_buffer_t,		input_token, 
			gss_OID *,	   	mech_type, 
			OM_uint32 *,  		token_type, 
			gss_ctx_id_t*,		context_handle 
           );

/*********************************************** 
 * OLD GSS V1 functions
 ***********************************************/
OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_release_oid SEC_PROTOTYPE_2(
                  OM_uint32 *,        minor_status,
                  gss_OID *,           oid
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_str_to_oid SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_buffer_t,       oid_str,
                  gss_OID *,           oid
                 );

OM_uint32 SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV gss_oid_to_str SEC_PROTOTYPE_3(
                  OM_uint32 *,        minor_status,
                  gss_OID,            oid,
                  gss_buffer_t,        oid_str
                 );



/******************************************* 
 * functions needed for internal interface *
 *******************************************/

struct SECGSSCTX;

void SEC_GLOBAL_FUNC_PREFIX SEC_API_CALLING_CONV aux_free2_SECGSSCTX SEC_PROTOTYPE_1(
    struct SECGSSCTX   *   , ptr
);

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */
 
 

