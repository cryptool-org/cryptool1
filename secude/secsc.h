/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/

/*-----------------------------------------------------------------------*/
/* INCLUDE FILE  secsc.h                                                 */
/* Definition of structures and types for the 				 */
/* SEC-IF - SCA-IF interface module (secsc).				 */
/*-----------------------------------------------------------------------*/

#ifndef _SECSC_
#define _SECSC_

#include "secure.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/*
 *
 *   secure.h defines:
 *          AlgId               (typedef struct AlgId)
 *          BitString           (typedef struct Bitstring)
 *          Boolean             (typedef char)
 *          EncryptedKey        (typedef struct EncryptedKey)
 *          ENCRYPTED           (typedef struct BitString)
 *          EncryptedKey        (typedef struct EncryptedKey) 
 *          KeyBits             (typedef struct KeyBits)
 *          More                (typedef enum { SEC_END, SEC_MORE })
 *          ObjId               (typedef struct ObjId)
 *          OctetString         (typedef struct Octetstring)
 *          Signature           (typedef struct Signature)
 *
 *   sca.h defines:
 *           Structures and types of the SCA-IF
 */

typedef struct {
	char *id;
	char *port;
	char *lib;
	char *parms;
	char *comment;
} TERMINAL;

#define CMD_INFO_V1 13

typedef struct {
	int   id;
	char *cmd;
	int   pin_offset1;
	int   pin_offset2;
	int   pin_length;
	int   time;
	char *rfu1s;
	char *rfu2s;
	int   rfu1i;
	int   rfu2i;
	char *text[8];
} CMD_INFO;

#define PSE_PIN_CHARS	 "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define PSE_PIN_L 8
#define SC_WAITTIME 20
   
#define SCT_SYM_NAME_ATR   "atr"
#ifdef WIN32
#define SCT_SYM_NAME_SETDRIVERS   "_sc_sct_set_drivers@4"
#define SCT_SYM_NAME_GETPORTS   "_sc_sct_get_ports@4"
#define SCT_SYM_NAME_INIT   "_sc_sct_init@12"
#define SCT_SYM_NAME_DATA_SCT   "_sc_sct_data_SCT@32"
#define SCT_SYM_NAME_DATA   "_sc_sct_data@24"
#define SCT_SYM_NAME_CLOSE   "_sc_sct_close@4"
#define SCT_SYM_NAME_INFO   "_sc_sct_info@28"
#define SCT_SYM_NAME_GET_INPUT   "_sc_sct_get_input@16"
#define SCT_SYM_NAME_DISPLAY   "_sc_sct_display@8"
#define SCT_SYM_NAME_EJECT   "_sc_sct_eject@4"
#define SCT_SYM_NAME_CHECK_PIN   "_sc_sct_check_pin@8"
#define SCT_SYM_NAME_CREATE_PIN   "_sc_sct_create_pin@8"
#define SCT_SYM_NAME_CHANGE_PIN   "_sc_sct_change_pin@8"
#define SCT_SYM_NAME_REQCARD   "_sc_sct_reqcard@4"
#define SCT_SYM_NAME_UNLOCK   "_sc_sct_unlock@4"
#define SCT_SYM_NAME_LOCK   "_sc_sct_lock@4"

#define SECSC_SYM_NAME_CREATE   "_sec_sc_create@16"
#define SECSC_SYM_NAME_MAIN   "_sec_sc_main@8"
#define SECSC_SYM_NAME_OPEN   "_sec_sc_open@12"
#define SECSC_SYM_NAME_CLOSE   "_sec_sc_close@4"
#define SECSC_SYM_NAME_READ   "_sec_sc_read@8"
#define SECSC_SYM_NAME_WRITE   "_sec_sc_write@8"
#define SECSC_SYM_NAME_GET_PRODUCT_INFO   "_sec_sc_get_product_info@4"
#define SECSC_SYM_NAME_GET_STATE   "_sec_sc_get_state@44"
#define SECSC_SYM_NAME_CHPIN   "_sec_sc_chpin@12"
#define SECSC_SYM_NAME_UNBLOCK_PIN   "_sec_sc_unblock_pin@12"
#define SECSC_SYM_NAME_DELETE_PSE   "_sec_sc_delete_PSE@12"
#define SECSC_SYM_NAME_DELETE_OBJECT   "_sec_sc_delete_object@4"
#define SECSC_SYM_NAME_DECRYPT_INIT   "_sec_sc_decrypt_init@8"
#define SECSC_SYM_NAME_DECRYPT_MORE   "_sec_sc_decrypt_more@12"
#define SECSC_SYM_NAME_DECRYPT_END   "_sec_sc_decrypt_end@8"
#define SECSC_SYM_NAME_GEN_KEY   "_sec_sc_gen_key@8"
#define SECSC_SYM_NAME_SIGN_INIT   "_sec_sc_sign_init@16"
#define SECSC_SYM_NAME_SIGN_MORE   "_sec_sc_sign_more@8"
#define SECSC_SYM_NAME_SIGN_END   "_sec_sc_sign_end@4"
#define SECSC_SYM_NAME_ENCRYPT_DIGEST   "_sec_sc_encrypt_Digest@20"
#define SECSC_SYM_NAME_CONTROL   "_sec_sc_control@16"
#else
#define SCT_SYM_NAME_SETDRIVERS   "sc_sct_set_drivers"
#define SCT_SYM_NAME_GETPORTS   "sc_sct_get_ports"
#define SCT_SYM_NAME_INIT   "sc_sct_init"
#define SCT_SYM_NAME_DATA_SCT   "sc_sct_data_SCT"
#define SCT_SYM_NAME_DATA   "sc_sct_data"
#define SCT_SYM_NAME_CLOSE   "sc_sct_close"
#define SCT_SYM_NAME_INFO   "sc_sct_info"
#define SCT_SYM_NAME_GET_INPUT   "sc_sct_get_input"
#define SCT_SYM_NAME_DISPLAY   "sc_sct_display"
#define SCT_SYM_NAME_EJECT   "sc_sct_eject"
#define SCT_SYM_NAME_CHECK_PIN   "sc_sct_check_pin"
#define SCT_SYM_NAME_CREATE_PIN   "sc_sct_create_pin"
#define SCT_SYM_NAME_CHANGE_PIN   "sc_sct_create_pin"
#define SCT_SYM_NAME_REQCARD   "sc_sct_reqcard"
#define SCT_SYM_NAME_UNLOCK   "sc_sct_unlock"
#define SCT_SYM_NAME_LOCK   "sc_sct_lock"


#define SECSC_SYM_NAME_MAIN   "sec_sc_main"
#define SECSC_SYM_NAME_CREATE   "sec_sc_create"
#define SECSC_SYM_NAME_OPEN   "sec_sc_open"
#define SECSC_SYM_NAME_CLOSE   "sec_sc_close"
#define SECSC_SYM_NAME_READ   "sec_sc_read"
#define SECSC_SYM_NAME_WRITE   "sec_sc_write"
#define SECSC_SYM_NAME_GET_PRODUCT_INFO   "sec_sc_get_product_info"
#define SECSC_SYM_NAME_GET_STATE   "sec_sc_get_state"
#define SECSC_SYM_NAME_CHPIN   "sec_sc_chpin"
#define SECSC_SYM_NAME_UNBLOCK_PIN   "sec_sc_unblock_pin"
#define SECSC_SYM_NAME_DELETE_PSE   "sec_sc_delete_PSE"
#define SECSC_SYM_NAME_DELETE_OBJECT   "sec_sc_delete_object"
#define SECSC_SYM_NAME_DECRYPT_INIT   "sec_sc_decrypt_init"
#define SECSC_SYM_NAME_DECRYPT_MORE   "sec_sc_decrypt_more"
#define SECSC_SYM_NAME_DECRYPT_END   "sec_sc_decrypt_end"
#define SECSC_SYM_NAME_GEN_KEY   "sec_sc_gen_key"
#define SECSC_SYM_NAME_SIGN_INIT   "sec_sc_sign_init"
#define SECSC_SYM_NAME_SIGN_MORE   "sec_sc_sign_more"
#define SECSC_SYM_NAME_SIGN_END   "sec_sc_sign_end"
#define SECSC_SYM_NAME_ENCRYPT_DIGEST   "sec_sc_encrypt_Digest"
#define SECSC_SYM_NAME_CONTROL   "sec_sc_control"
#endif

typedef int ( SEC_API_CALLING_CONV IO_CB )	        SEC_PROTOTYPE_4( char * , prompt, char *  , inp, int * , size, Boolean  , visible);
typedef PSESel* ( SEC_API_CALLING_CONV SECSC_CREATE_T )	        SEC_PROTOTYPE_4( char * , pse_name, char * , pin, SC_DATA * , sc_data ,
						Boolean  , onekeypaironly);
typedef PSESel* ( SEC_API_CALLING_CONV SECSC_MAIN_T )	        SEC_PROTOTYPE_2( char * ,  cmd, IO_CB * , io_cb);
typedef PSESel* ( SEC_API_CALLING_CONV SECSC_OPEN_T )	        SEC_PROTOTYPE_3( char * , pse_name, char * , pin, SC_DATA * , sc_data );
typedef RC  	( SEC_API_CALLING_CONV SECSC_CLOSE_T )    	        SEC_PROTOTYPE_1( PSESel *  , pse_sel );
typedef RC  	( SEC_API_CALLING_CONV SECSC_READ_T )    	        SEC_PROTOTYPE_2( PSESel *  , pse_sel, OctetString	 *	 , content );
typedef RC  	( SEC_API_CALLING_CONV SECSC_WRITE_T )    	        SEC_PROTOTYPE_2( PSESel * ,  pse_sel, OctetString	 * , 	content );
typedef RC      ( SEC_API_CALLING_CONV SECSC_GET_PRODUCT_INFO_T )    SEC_PROTOTYPE_1( char ** ,  info );
typedef RC      ( SEC_API_CALLING_CONV SECSC_GET_STATE_T )           SEC_PROTOTYPE_11( char * , psename, SC_DATA * , sc_data , char ** , SCT_TYPE, char ** , SC_TYPE,
							int * , enter_pin_on_SCT, int * , enter_pin_on_SCT_on_install, int * , enter_pin_on_SCT_on_change, int * , need_SC, int * , need_pin, char ** , serial, int ** , supported_algs_and_sizes );
typedef RC      ( SEC_API_CALLING_CONV SECSC_CHPIN_T )               SEC_PROTOTYPE_3( PSESel *  , pse_sel, char * , oldpin, char * , newpin );
typedef RC      ( SEC_API_CALLING_CONV SECSC_UNBLOCK_PIN_T )          SEC_PROTOTYPE_3( char * , psename, char * , pin, SC_DATA * , sc_data );
typedef RC      ( SEC_API_CALLING_CONV SECSC_DELETE_PSE_T )          SEC_PROTOTYPE_3( char * , psename, char * , pin, SC_DATA * , sc_data );
typedef RC      ( SEC_API_CALLING_CONV SECSC_DELETE_OBJECT_T )       SEC_PROTOTYPE_1( PSESel *  , pse_sel );
typedef RC      ( SEC_API_CALLING_CONV SECSC_DECRYPT_INIT_T )        SEC_PROTOTYPE_2( void ** ,  context, Key * , key);
typedef int     ( SEC_API_CALLING_CONV SECSC_DECRYPT_MORE_T )        SEC_PROTOTYPE_3( void **  , context, BitString * , in_bits, OctetString * , out_octets );
typedef int     ( SEC_API_CALLING_CONV SECSC_DECRYPT_END_T )         SEC_PROTOTYPE_2( void **  , context, OctetString * , out_octets );
typedef RC      ( SEC_API_CALLING_CONV SECSC_GEN_KEY_T )             SEC_PROTOTYPE_2( Key * , key, Boolean  , replace );
typedef RC      ( SEC_API_CALLING_CONV SECSC_SIGN_INIT_T )           SEC_PROTOTYPE_4( void ** ,  context, Signature * , signature,
							Key * , key, HashInput * , hash_input );
typedef RC      ( SEC_API_CALLING_CONV SECSC_SIGN_MORE_T )           SEC_PROTOTYPE_2( void **  , context, OctetString * , in_octets );
typedef RC      ( SEC_API_CALLING_CONV SECSC_SIGN_END_T )            SEC_PROTOTYPE_1( void **  , context );
typedef RC      ( SEC_API_CALLING_CONV SECSC_ENCRYPT_DIGEST_T )      SEC_PROTOTYPE_5( Key * , key, BitString * , signature, OctetString * , hash_result,
							AlgSpecial  , algspecial, AlgId * , hash_alg );
typedef RC      ( SEC_API_CALLING_CONV SECSC_CONTROL_T )      SEC_PROTOTYPE_4( PSESel *  , pse_sel, int  , cmd, void * , input,
							void ** , output );

typedef struct {
	void *handle;
	SECSC_CREATE_T		* secsc_create_ptr;
	SECSC_OPEN_T		* secsc_open_ptr;
	SECSC_CLOSE_T		* secsc_close_ptr;
	SECSC_READ_T		* secsc_read_ptr;
	SECSC_WRITE_T		* secsc_write_ptr;
        SECSC_GET_PRODUCT_INFO_T* secsc_get_product_info_ptr;
        SECSC_GET_STATE_T       * secsc_get_state_ptr;
        SECSC_CHPIN_T           * secsc_chpin_ptr;
        SECSC_UNBLOCK_PIN_T     * secsc_unblock_pin_ptr;
        SECSC_DELETE_PSE_T      * secsc_delete_PSE_ptr;
        SECSC_DELETE_OBJECT_T   * secsc_delete_object_ptr;
        SECSC_DECRYPT_INIT_T    * secsc_decrypt_init_ptr;
        SECSC_DECRYPT_MORE_T    * secsc_decrypt_more_ptr;
        SECSC_DECRYPT_END_T     * secsc_decrypt_end_ptr;
        SECSC_GEN_KEY_T         * secsc_gen_key_ptr;
        SECSC_SIGN_INIT_T       * secsc_sign_init_ptr;
        SECSC_SIGN_MORE_T       * secsc_sign_more_ptr;
        SECSC_SIGN_END_T        * secsc_sign_end_ptr;
        SECSC_ENCRYPT_DIGEST_T  * secsc_encrypt_Digest_ptr;
        SECSC_CONTROL_T  * secsc_control_ptr;
} SECSC_FUNCTIONS;

typedef RC ( SEC_API_CALLING_CONV SCT_SETDRIVERS_T )	        SEC_PROTOTYPE_1( char * , drivers);
typedef RC ( SEC_API_CALLING_CONV SCT_GETPORTS_T )	        SEC_PROTOTYPE_1( char *** , ports);
typedef RC ( SEC_API_CALLING_CONV SCT_INIT_T )	        SEC_PROTOTYPE_3( char * , port, char * , type, void ** , hdl);
typedef RC ( SEC_API_CALLING_CONV SCT_DATA_T )	        SEC_PROTOTYPE_6( void * , hdl, int  , buf_len, unsigned char * , buf,
								int * , resp_len, unsigned char * , resp,
							  	char * , comment);
typedef RC ( SEC_API_CALLING_CONV SCT_DATA_SCT_T )	        SEC_PROTOTYPE_8( void * , hdl, int * ,pdad, int * , psad, int  , buf_len, unsigned char * , buf,
								int * , resp_len, unsigned char * , resp,
							  	char * , comment);
typedef RC ( SEC_API_CALLING_CONV SCT_CLOSE_T )	        SEC_PROTOTYPE_1( void ** , hdl);
typedef RC ( SEC_API_CALLING_CONV SCT_INFO_T )	        SEC_PROTOTYPE_7( void * , hdl, char ** , type, int * , display, int * , pin_create, int * , pin_verify, int * , pin_change, int * , pin_get);
typedef RC ( SEC_API_CALLING_CONV SCT_GET_INPUT_T )	SEC_PROTOTYPE_4( void * , hdl, char * , text, char  , visible, char ** , pin);
typedef RC ( SEC_API_CALLING_CONV SCT_DISPLAY_T )	SEC_PROTOTYPE_2( void * , hdl, char * , text);
typedef RC ( SEC_API_CALLING_CONV SCT_EJECT_T )	        SEC_PROTOTYPE_1( void * , hdl);
typedef RC ( SEC_API_CALLING_CONV SCT_CHANGE_PIN_T )	SEC_PROTOTYPE_2( void * , hdl, void * , cmd_info);
typedef RC ( SEC_API_CALLING_CONV SCT_CREATE_PIN_T )	SEC_PROTOTYPE_2( void * , hdl, void * , cmd_info);
typedef RC ( SEC_API_CALLING_CONV SCT_CHECK_PIN_T )	SEC_PROTOTYPE_2( void * , hdl, void * , cmd_info);
typedef RC ( SEC_API_CALLING_CONV SCT_REQCARD_T )	SEC_PROTOTYPE_1( void * , hdl);
typedef RC ( SEC_API_CALLING_CONV SCT_UNLOCK_T )	SEC_PROTOTYPE_1( void * , hdl);
typedef RC ( SEC_API_CALLING_CONV SCT_LOCK_T )	SEC_PROTOTYPE_1( void * , hdl);

typedef struct {
	void *handle;
	SCT_INIT_T		* sct_init_ptr;
	SCT_DATA_T		* sct_data_ptr;
	SCT_CLOSE_T		* sct_close_ptr;
	SCT_INFO_T		* sct_info_ptr;
	SCT_GET_INPUT_T		* sct_get_input_ptr;
	SCT_DISPLAY_T		* sct_display_ptr;
	SCT_EJECT_T		* sct_eject_ptr;
	SCT_CREATE_PIN_T	* sct_create_pin_ptr;
	SCT_CHANGE_PIN_T	* sct_change_pin_ptr;
	SCT_CHECK_PIN_T		* sct_check_pin_ptr;
	SCT_REQCARD_T		* sct_reqcard_ptr;
	SCT_UNLOCK_T		* sct_unlock_ptr;
	SCT_LOCK_T		* sct_lock_ptr;
	OctetString		* sct_atr;
} SCT_FUNCTIONS;

typedef struct {
	char			*lib_name;
	SECSC_FUNCTIONS      secsc;
} PLUGIN_DATA;


#define SECSC_CREATE(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_create_ptr)
#define SECSC_OPEN(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_open_ptr)
#define SECSC_CLOSE(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_close_ptr)
#define SECSC_READ(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_read_ptr)
#define SECSC_WRITE(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_write_ptr)
#define SECSC_GET_PRODUCT_INFO(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_get_product_info_ptr)
#define SECSC_GET_STATE(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_get_state_ptr)
#define SECSC_CHPIN(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_chpin_ptr)
#define SECSC_DELETE_PSE(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_delete_PSE_ptr)
#define SECSC_UNBLOCK_PIN(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_unblock_pin_ptr)
#define SECSC_DELETE_OBJECT(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_delete_object_ptr)
/*#define SECSC_SC_EJECT(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_sc_eject_ptr)
#define SECSC_RELEASE_SCT(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_release_SCT_ptr)
*/
#define SECSC_DECRYPT_INIT(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_decrypt_init_ptr)
#define SECSC_DECRYPT_MORE(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_decrypt_more_ptr)
#define SECSC_DECRYPT_END(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_decrypt_end_ptr)
#define SECSC_GEN_KEY(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_gen_key_ptr)
#define SECSC_SIGN_INIT(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_sign_init_ptr)
#define SECSC_SIGN_MORE(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_sign_more_ptr)
#define SECSC_SIGN_END(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_sign_end_ptr)
#define SECSC_ENCRYPT_DIGEST(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_encrypt_Digest_ptr)
#define SECSC_CONTROL(sc_data) (((PLUGIN_DATA *)(sc_data->func))->secsc.secsc_control_ptr)






#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */



#endif /* _SECSC_ */

