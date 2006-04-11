/* ssl.h */ 
/********************************************************************************
 * This SSL implementation is based on the SSL implementation of Eric Young.	*
 * The implementation was written so as to conform with Netscape's SSL.			*
 * Copyright (C) 1995-1997 Eric Young (eay@cryptsoft.com)						*
 * All rights reserved.															*
 *																				*
 * In the process of integrating the security technology of SECUDE into the		*
 * SSL protocol, the original implementation by Eric Young was completely		*
 * rewritten, restructured and complemented by new features.					*
 * SECUDE is registered trademark of SECUDE IT Security GmbH.								*
 * Copyright (c) 2004										*
 * All rights reserved.															*
 *																				*
 *																				*
 *									NOTICE										*
 * Acquisition, use, and distribution of this module and related materials are	*
 * subject to restrictions mentioned in each volume of the documentation.		*
 * This software is provided ``as is'' without express or implied warranty.		*
 *																				*
 ********************************************************************************/


#ifndef HEADER_SSL_H 
#define HEADER_SSL_H 

#ifdef  __cplusplus
extern "C" {
#endif


/*------------------------------ the typedefs ------------------------------*/

/***** Typedef SSL_Alert *****/
/** SSL_ALERT
  * @ingroup header_ssl
  */
typedef int							SSL_ALERT;

/***** Typedef H_SSL_CIPHER_SUITE *****/
/** Cipher Suite handle
  * @ingroup header_ssl
  */
typedef struct SSL_CIPHER_SUITE*	H_SSL_CIPHER_SUITE;

/***** Typedef H_SSL_SESSION *****/
/** SSL Session handle
  * @ingroup header_ssl
  */
typedef struct SSL_SESSION*			H_SSL_SESSION;

#ifndef HEADER_BIO_H
/***** Typedef H_SSL *****/
/** SSL handle
  * @ingroup header_ssl
  */
typedef struct SSL*					H_SSL;
/***** Typedef H_SSL_CTX *****/
/** SSL Context handle
  * @ingroup header_ssl
  */
typedef struct SSL_CTX*				H_SSL_CTX;
#endif


/*------------------------------ the includes ------------------------------*/


#include <secude/af.h>
#include <secude/s3.h>
#include <secude/s23.h>
#include <secude/bio.h>

/*------------------------------ the constants ------------------------------*/


/***** Define SSL_ALERT_NONE *****/
/**
  * @ingroup header_ssl
  */
#define SSL_ALERT_NONE							0x0000FFFF

/* aliases for use with the SSL_CTX_set_default_cipher_suites and SSL_set_cipher_suites functions				*
 * a		- authentication with...																			*
 * d		- authentication with DSA																			*
 * r		- authentication with RSA																			*
 * e		- encryption with...																				*
 * k		- key exchange with...																				*
 * m		- MAC with...																						*
 * ALL		- all availbale cipher suites																		*
 * EXPORT	- all available cipher suites that use keys of size 40 bits for encryption or no encryption at all	*
 * LOW		- all available cipher suites that use keys of size <= 64 bits for encryption (security grade low)	*
 * MEDIUM	- all available cipher suites that use keys of size 128 bits for encryption (security grade medium)	*
 * HIGH		-  all available cipher suites that use keys of size 192 bits for encryption (security grade high)	*
 * SSLv3	- all availbale cipher suites that are defined in SSLv3												*/
#define	SSL_TXT_aDH								"aDH"
#define	SSL_TXT_aDSS							"aDSS"
#define	SSL_TXT_aFZA							"aFZA"
#define	SSL_TXT_aNULL							"aNULL"
#define	SSL_TXT_aRSA							"aRSA"

#define SSL_TXT_kDHd							"kDHd"
#define SSL_TXT_kDHr							"kDHr"
#define SSL_TXT_kDHE							"kDHE"
#define SSL_TXT_kFZA							"kFZA"
#define SSL_TXT_kRSA							"kRSA"

#define SSL_TXT_eDES							"eDES"
#define SSL_TXT_e3DES							"e3DES"
#define SSL_TXT_eFZA							"eFZA"
#define SSL_TXT_eIDEA							"eIDEA"
#define	SSL_TXT_eNULL							"eNULL"
#define SSL_TXT_eRC2							"eRC2"
#define SSL_TXT_eRC4							"eRC4"

#define SSL_TXT_mMD5							"mMD5"
#define SSL_TXT_mSHA1							"mSHA1"

#define SSL_TXT_ALL								"ALL"
#define SSL_TXT_EXPORT							"EXPORT"
#define SSL_TXT_LOW								"LOW"
#define SSL_TXT_MEDIUM							"MEDIUM"
#define SSL_TXT_HIGH							"HIGH"
#define SSL_TXT_SSLV3							"SSLv3"

/* this is the list of default cipher suites for every new SSL_CTX; you can use the alias		*
 * "DEFAULT" to use the SSL_DEFAULT_CIPHER_SUITES with the SSL_CTX_set_default_cipher_suites and	*
 * SSL_set_cipher_suites functions - but only at the beginning of your cipher_suites parameter	*/

/*
#ifdef RSA_INSTALLED
#define SSL_DEFAULT_CIPHER_SUITES_				"!aNULL:eRC4+aRSA:HIGH:MEDIUM:LOW:EXPORT:+EXPORT"
#else
#define SSL_DEFAULT_CIPHER_SUITES				"HIGH:MEDIUM:LOW:aNULL+kDHE+e3DES:aNULL+kDHE+eRC4:aNULL+kDHE+eDES:+EXPORT"
#endif
*/
#define SSL_DEFAULT_CIPHER_SUITES (char*) SSL_API_get_default_cipher_suites()
/* boolean constants */
#define SSL_FALSE								0
#define SSL_TRUE								1

/* return values for functions */
/***** Define SSL_FAILURE *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_FAILURE								0
/***** Define SSL_SUCCESS *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_SUCCESS								1

/* constants to use with the version parameter of the SSL_CTX_new function to obtain a handle	*
 * to the SSLv3 or the SSLv3 with backward compatibility to SSLv2 version specific methods,		*
 * respectively. The former perform a plain SSLv3 handshake, the latter perform a SSLv3			*
 * handshake as well, but sends and accepts the SSL client hello handshake messages in SSLv2	*
 * format.																						*/
#define SSL_VERSION_SSL_3						0x0300
#define SSL_VERSION_SSL_3_BC_MODE				0x0203

/* constants for use with ssl->type to indicate whether a SSL handle is used as the	*
 * client or the server in a SSL handshake; use the SSL_set_type function with		*
 * SSL_TYPE_CLIENT or SSL_TYPE_SERVER to assign the role of the client or the		*
 * server to a SSL handle. All three constants can be used with the type parameter	*
 * of the SSL_CTX_new function to get a handle to all, the client-sided or the		*
 * server-sided version specific methods, respectively, that determine the SSL		*
 * version of a performed SSL handshake.											*/
#define SSL_TYPE_BOTH							1
#define SSL_TYPE_CLIENT							2
#define SSL_TYPE_SERVER							3

/* constants for use with ssl->state to indicate the progress of the SSL handshake;		*
 * use the SSL_is_after_handshake, SSL_is_before_handshake, SSL_is_in_handshake,		*
 * SSL_is_in_handshake_accept, SSL_is_in_handshake_connect and SSL_get_state functions	*
 * to access and inquire this member, which can be helpful in evaluating why a			*
 * connection failed or when using non-blocking IO										*/
 /***** Define SSL_ST_ACCEPT *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_ST_ACCEPT							0x1000
/***** Define SSL_ST_CONNECT *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_ST_CONNECT							0x2000
/***** Define SSL_ST_BEFORE *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_ST_BEFORE							0x4000
/***** Define SSL_ST_HANDSHAKE *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_ST_HANDSHAKE						(SSL_ST_ACCEPT | SSL_ST_CONNECT)
/***** Define SSL_ST_MASK *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_ST_MASK								0x0FFF
/***** Define SSL_ST_OK *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_ST_OK								0x0300
/***** Define SSL_ST_RENEGOTIATE *****/
/** return value
  * @ingroup header_ssl
  */
#define SSL_ST_RENEGOTIATE						(0x0400 | SSL_ST_HANDSHAKE)

/* constants for use with ssl->rstate to indicate where we left off,	*
 * in case the reading of a SSL record fails - mainly for internal use	*/
#define SSL_ST_READ_HEADER						0xF0
#define SSL_ST_READ_BODY						0xF1
#define SSL_ST_READ_DONE						0xF2

/* constants for use with ctx->session_cache_mode to indicate the session caching	*
 * mode; use the SSL_CTX_set_session_cache_mode and SSL_CTX_get_session_cache_mode	*
 * functions to access and manipulate this member									*/
#define SSL_SESSION_CACHE_OFF					0x00
#define SSL_SESSION_CACHE_CLIENT				0x01
#define SSL_SESSION_CACHE_SERVER				0x02
#define SSL_SESSION_CACHE_BOTH					(SSL_SESSION_CACHE_CLIENT | SSL_SESSION_CACHE_SERVER)
#define SSL_SESSION_CACHE_NO_AUTO_CLEAR			0x80

/* constants for use with ssl->verify_mode and ctx->default_verify_mode to indicate the requirements for	*
 * the authentication phase of the SSL handshake; use the SSL_set_verify_mode, SSL_get_verify_mode,			*
 * SSL_CTX_set_default_verify_mode and SSL_CTX_get_default_verify_mode functions to access and manipulate	*
 * this member - use either SSL_VERIFY_NONE or SSL_VERIFY_PEER. SSL_VERIFY_FAIL_IF_NO_PEER_CERT and			*
 * SSL_VERIFY_CLIENT_ONCE are logically ORed with SSL_VERIFY_PEER, if desired.								*
 * SSL_VERIFY_IGNORE_CERT_REQUEST is logically ORed with SSL_VERIFY_NONE or SSL_VERIFY_PEER, if desired.	*/
#define SSL_VERIFY_NONE							0x00
#define SSL_VERIFY_PEER							0x01
#define SSL_VERIFY_FAIL_IF_NO_PEER_CERT			0x02
#define SSL_VERIFY_CLIENT_ONCE					0x04
#define SSL_VERIFY_IGNORE_CERT_REQUEST			0x08

/* constants for use with ssl->shutdown to indicate whether the SSL connection is still	*
 * open, we have received a close notify or fatal alert, we have sent a close notify	*
 * alert or the peer has aborted the connection while we were waiting for a close		*
 * notify alert; SSL_SHUTDOWN_SENT can be logically ORed with SSL_SHUTDOWN_RECEIVED and	*
 * with SSL_SHUTDOWN_ABORTED_BY_PEER, but not at the same time. Use the					*
 * SSL_set_shutdown and and SSL_get_shutdown functions to access and manipulate this	*
 * member, which is usually of internal interest only; use the SSL_shutdown function	*
 * if you want to shutdown the connection and be able to resume the session				*/
#define SSL_SHUTDOWN_NO							0
#define SSL_SHUTDOWN_RECEIVED					1
#define SSL_SHUTDOWN_SENT						2
#define SSL_SHUTDOWN_ABORTED_BY_PEER			4

/* constants for use with ssl->shutdown_mode and ctx->default_shutdown_mode to indicate	*
 * whether we want to send a close notify alert when we shut down the connection; use	*
 * the SSL_get_shutdown_mode, SSL_set_shutdown_mode, SSL_CTX_get_default_shutdown_mode	*
 * and SSL_CTX_set_default_shutdown_mode functions to access and manipulate this member	*/
#define SSL_SHUTDOWN_DONT_SEND_CLOSE_NOTIFY		0
#define SSL_SHUTDOWN_SEND_CLOSE_NOTIFY			1

/* constants for use with ssl->read_ahead_mode and ctx->default_read_ahead_mode to indicate	*
 * whether we want to read as many bytes as possible from the I/O mechanism's buffer into	*
 * the internal buffer; use the SSL_get_read_ahead_mode, SSL_set_read_ahead_mode,			*
 * SSL_CTX_get_default_read_ahead_mode and SSL_CTX_set_default_read_ahead_mode functions to	*
 * access and manipulate this member														*/
#define SSL_READ_AHEAD_OFF						0
#define SSL_READ_AHEAD_ON						1

/* constants for use with ssl->single_step_mode to indicate whether you want to send the	*
 * handshake messages one by one instead of in big chunks; use the SSL_set_single_step_mode	*
 * and SSL_get_single_step_mode functions to access and manipulate this member				*/
#define SSL_SINGLE_STEP_OFF						0
#define SSL_SINGLE_STEP_ON						1

/* constants for use with ssl->nbio_state to indicate whether we should read/write more	*
 * when a non-blocking I/O fails; use the SSL_get_nbio_state function to access this	*
 * member, which is mainly for internal use; rather use the SSL_check_last_io function	*
 * to inquire the reason for failure of a failed non-blocking I/O operation				*/
#define SSL_SHOULD_NOTHING						1
#define SSL_SHOULD_READ							2
#define SSL_SHOULD_WRITE						3

/* constants to specify the purpose for which you want to (de)register/retrieve an			*
 * external random number generator with the SSL_CTX_set_random_number_generator_callback	*
 * and SSL_CTX_get_random_number_generator_callback functions								*/
#define SSL_RNG_ALL								0xFFFFFFFFL
#define SSL_RNG_HELLO_RANDOM					0x00000001L
#define SSL_RNG_PRE_MASTER_SECRET				0x00000002L
#define SSL_RNG_SESSION_ID						0x00000004L
 
 /* constants for use with ctx->options to make your SSL implementation		*
 * compliant to bugs found in other vendors' past and present SSL			*
 * implementations; use the SSL_CTX_set_options function to set this member	*/
#define SSL_OP_ALL								0xFFFFFFFFL
#define SSL_OP_CERT_REQ_EMPTY_CA_DN_BUG_AUTH	0x00000001L
#define SSL_OP_CERT_REQ_EMPTY_CA_DN_BUG_NO_AUTH	0x00000400L
#define SSL_OP_CLIENT_KEY_EXCHANGE_VERSION_BUG	0x00000002L
#define SSL_OP_EPHEMERAL_RSA					0x00000004L
#define SSL_OP_MICROSOFT_BIG_SSLV3_BUFFER		0x00000008L
#define SSL_OP_NETSCAPE_CA_DN_BUG				0x00000010L
#define SSL_OP_NETSCAPE_CHALLENGE_BUG			0x00000020L
#define SSL_OP_NETSCAPE_DEMO_CIPHER_CHANGE_BUG	0x00000040L
#define SSL_OP_NETSCAPE_REUSE_CIPHER_CHANGE_BUG	0x00000080L
#define SSL_OP_SESSION_RESUMPTION_ONLY			0x00000800L
#define SSL_OP_SINGLE_DEFAULT_DHE_USE			0x00000100L
#define SSL_OP_SSLEAY_080_CLIENT_DH_BUG			0x00000200L
#define SSL_OP_SKIP_EXPIRED_CERTS_IN_FCPATH		0x00001000L

/* location constants passed as the second parameter to the handshake_callback */
/***** #Define SSL_CB_LOOP *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_LOOP								0x01
/***** Define SSL_CB_EXIT *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_EXIT								0x02
/***** Define SSL_CB_READ *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_READ								0x04
/***** Define SSL_CB_WRITE *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_WRITE							0x08
/***** Define SSL_CB_ALERT *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_ALERT							0x4000
/***** Define SSL_CB_READ_ALERT *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_READ_ALERT						(SSL_CB_ALERT | SSL_CB_READ)
/***** Define SSL_CB_WRITE_ALERT *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_WRITE_ALERT						(SSL_CB_ALERT | SSL_CB_WRITE)
/***** Define SSL_CB_ACCEPT_LOOP *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_ACCEPT_LOOP						(SSL_ST_ACCEPT | SSL_CB_LOOP)
/***** Define SSL_CB_ACCEPT_EXIT *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_ACCEPT_EXIT						(SSL_ST_ACCEPT | SSL_CB_EXIT)
/***** Define SSL_CB_CONNECT_LOOP *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_CONNECT_LOOP						(SSL_ST_CONNECT | SSL_CB_LOOP)
/***** Define SSL_CB_CONNECT_EXIT *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_CONNECT_EXIT						(SSL_ST_CONNECT | SSL_CB_EXIT)
/***** Define SSL_CB_HANDSHAKE_START *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_HANDSHAKE_START					0x10
/***** Define SSL_CB_HANDSHAKE_DONE *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_HANDSHAKE_DONE					0x20
/***** Define SSL_CB_HANDSHAKE_PROXY_FAILED *****/
/**
  * @ingroup header_ssl
  */
#define SSL_CB_HANDSHAKE_PROXY_FAILED			0x40

/* return values of the SSL_check_last_io function */
#define SSL_ERROR_NONE							0
#define SSL_ERROR_CONNECTION_LOST				1
#define SSL_ERROR_RECEIVED_CLOSE_NOTIFY			2
#define SSL_ERROR_SHOULD_HANDSHAKE				3
#define SSL_ERROR_SHOULD_READ					4
#define SSL_ERROR_SHOULD_WRITE					5
#define SSL_ERROR_SSL							6
#define SSL_ERROR_UNKNOWN						7

/* constant for the default value of maximum message sizes
 that are to be accepted for incoming messages */
#if defined(MSDOS) && !defined(WIN32)
#define SSL_MAX_CERT_LIST_DEFAULT 1024*30 /* 30k max cert list :-) */
#else
#define SSL_MAX_CERT_LIST_DEFAULT 1024*100 /* 100k max cert list :-) */
#endif


/*------------------------------ the functions ------------------------------*/


/* SSL API handling */
int SEC_API_CALLING_CONV SSL_API_cleanup(void);
int	SEC_API_CALLING_CONV SSL_API_get_last_error (int* last_error);
#ifdef USE_STDARG
int	SEC_API_CALLING_CONV SSL_API_log(char* function_name , char* output_string , ...);
#else
int	SEC_API_CALLING_CONV SSL_API_log();
#endif /* USE_STDARG */
int	SEC_API_CALLING_CONV SSL_API_print_error(H_BIO hBio , int last_error_only);
int	SEC_API_CALLING_CONV SSL_API_set_logfile(char* logfile);
int SEC_API_CALLING_CONV SSL_API_startup(void);
const char * SEC_API_CALLING_CONV SSL_API_get_default_cipher_suites();

/* SSL handling */
int	SEC_API_CALLING_CONV SSL_accept(H_SSL hSsl);
int	SEC_API_CALLING_CONV SSL_check_last_io(H_SSL hSsl , int last_io , int* result);
int	SEC_API_CALLING_CONV SSL_clear(H_SSL hSsl);
int	SEC_API_CALLING_CONV SSL_connect(H_SSL hSsl);
int	SEC_API_CALLING_CONV SSL_do_handshake(H_SSL hSsl);
int	SEC_API_CALLING_CONV SSL_duplicate(H_SSL hOrg , H_SSL* hDup);
int	SEC_API_CALLING_CONV SSL_free(H_SSL hSsl);
int	SEC_API_CALLING_CONV SSL_get_alert(H_SSL hSsl , SSL_ALERT* alert);
int	SEC_API_CALLING_CONV SSL_get_app_data(H_SSL hSsl , void** app_data);
int	SEC_API_CALLING_CONV SSL_get_bio_read(H_SSL hSsl , H_BIO* hBio);
int	SEC_API_CALLING_CONV SSL_get_bio_write(H_SSL hSsl , H_BIO* hBio);
int	SEC_API_CALLING_CONV SSL_get_certificate_request_ca_dnames(H_SSL hSsl , SET_OF_DName** ca_dnames);
int	SEC_API_CALLING_CONV SSL_get_cipher_suites(H_SSL hSsl , H_SSL_CIPHER_SUITE* hCipher_suites , int* num_cipher_suites);
int	SEC_API_CALLING_CONV SSL_get_cipher_suites_no_n(H_SSL hSsl , int n , H_SSL_CIPHER_SUITE* hCipher_suite);
int	SEC_API_CALLING_CONV SSL_get_cipher_suites_peer(H_SSL hSsl , char* buf , int len);
int	SEC_API_CALLING_CONV SSL_get_cipher_suites_total(H_SSL hSsl , int* total);
int	SEC_API_CALLING_CONV SSL_get_cipher_suite_used(H_SSL hSsl , H_SSL_CIPHER_SUITE* hCipher_suite);
int	SEC_API_CALLING_CONV SSL_get_ctx(H_SSL hSsl , H_SSL_CTX* hCtx);
int	SEC_API_CALLING_CONV SSL_get_fd_read(H_SSL hSsl , unsigned int* file_descriptor);
int	SEC_API_CALLING_CONV SSL_get_fd_write(H_SSL hSsl , unsigned int* file_descriptor);
int	SEC_API_CALLING_CONV SSL_get_handshake_callback(H_SSL hSsl , void(**cb)(H_SSL , int , int));
int	SEC_API_CALLING_CONV SSL_get_nbio_state(H_SSL hSsl , int* state);
int	SEC_API_CALLING_CONV SSL_get_peer_certificates(H_SSL hSsl , Certificates** certificates);
int	SEC_API_CALLING_CONV SSL_get_pse_pin_callback(H_SSL hSsl , int(**cb)(void* , void*));
int	SEC_API_CALLING_CONV SSL_get_read_ahead_mode(H_SSL hSsl , int* mode);
int	SEC_API_CALLING_CONV SSL_get_rstate_description(H_SSL hSsl , char** rstate);
int	SEC_API_CALLING_CONV SSL_get_rstate_description_long(H_SSL hSsl , char** rstate);
int	SEC_API_CALLING_CONV SSL_get_session(H_SSL hSsl , H_SSL_SESSION* hSession);
int	SEC_API_CALLING_CONV SSL_get_shutdown(H_SSL hSsl , int* shutdown);
int	SEC_API_CALLING_CONV SSL_get_shutdown_mode(H_SSL hSsl , int* mode);
int	SEC_API_CALLING_CONV SSL_get_single_step_mode(H_SSL hSsl , int* mode);
int	SEC_API_CALLING_CONV SSL_get_state(H_SSL hSsl , int* state);
int	SEC_API_CALLING_CONV SSL_get_state_description(H_SSL hSsl , char** state);
int	SEC_API_CALLING_CONV SSL_get_state_description_long(H_SSL hSsl , char** state);
int	SEC_API_CALLING_CONV SSL_get_timeout(H_SSL hSsl , long* timeout);
int	SEC_API_CALLING_CONV SSL_get_verify_mode(H_SSL hSsl , int* mode);
int	SEC_API_CALLING_CONV SSL_get_version(H_SSL hSsl , int* version);
int	SEC_API_CALLING_CONV SSL_get_version_info(H_SSL hSsl , char** version);
int	SEC_API_CALLING_CONV SSL_is_after_handshake(H_SSL hSsl , int* true_false);
int	SEC_API_CALLING_CONV SSL_is_before_handshake(H_SSL hSsl , int* true_false);
int	SEC_API_CALLING_CONV SSL_is_in_handshake(H_SSL hSsl , int* true_false);
int	SEC_API_CALLING_CONV SSL_is_in_handshake_accept(H_SSL hSsl , int* true_false);
int	SEC_API_CALLING_CONV SSL_is_in_handshake_connect(H_SSL hSsl , int* true_false);
int	SEC_API_CALLING_CONV SSL_is_session_resumed(H_SSL hSsl , int* is_resumed);
int	SEC_API_CALLING_CONV SSL_new(H_SSL* hSsl , H_SSL_CTX hCtx);
int	SEC_API_CALLING_CONV SSL_peek(H_SSL hSsl , char* buf , int len , int* amount);
int	SEC_API_CALLING_CONV SSL_pending(H_SSL hSsl , int* amount);
int	SEC_API_CALLING_CONV SSL_read(H_SSL hSsl , char* buf , int len);
int	SEC_API_CALLING_CONV SSL_renegotiate(H_SSL hSsl);
int	SEC_API_CALLING_CONV SSL_send_alert(H_SSL hSsl , SSL_ALERT alert);
int	SEC_API_CALLING_CONV SSL_set_app_data(H_SSL hSsl , void* app_data);
int	SEC_API_CALLING_CONV SSL_set_bio(H_SSL hSsl , H_BIO hBio_read , H_BIO hBio_write);
int	SEC_API_CALLING_CONV SSL_set_cipher_suites(H_SSL hSsl , char* cipher_suites);
#ifndef NO_SOCK
#if defined(SEC_OPEN_TRANSPORT) && SEC_OPEN_TRANSPORT
int	SEC_API_CALLING_CONV SSL_set_ep(H_SSL hSsl , EndpointRef ep);
int	SEC_API_CALLING_CONV SSL_set_ep_read(H_SSL hSsl , EndpointRef ep);
int	SEC_API_CALLING_CONV SSL_set_ep_write(H_SSL hSsl , EndpointRef ep);
#endif
int	SEC_API_CALLING_CONV SSL_set_fd(H_SSL hSsl , unsigned int fd);
int	SEC_API_CALLING_CONV SSL_set_fd_read(H_SSL hSsl , unsigned int fd);
int	SEC_API_CALLING_CONV SSL_set_fd_write(H_SSL hSsl , unsigned int fd);
#endif
int	SEC_API_CALLING_CONV SSL_set_handshake_callback(H_SSL hSsl , void(*cb)(H_SSL , int , int));
int	SEC_API_CALLING_CONV SSL_set_options(H_SSL hSsl , unsigned long options);
int	SEC_API_CALLING_CONV SSL_set_pse_by_name(H_SSL hSsl , char* pse_name , AF_options* af_options , int sct_id , void* cb_arg);
int	SEC_API_CALLING_CONV SSL_set_pse_by_pse(H_SSL hSsl , PSE pse);
int	SEC_API_CALLING_CONV SSL_set_pse_pin_callback(H_SSL hSsl , int(*cb)(void* , void*));
int	SEC_API_CALLING_CONV SSL_set_read_ahead_mode(H_SSL hSsl , int mode);
int	SEC_API_CALLING_CONV SSL_set_session_by_session(H_SSL hSsl , H_SSL_SESSION hSession);
int	SEC_API_CALLING_CONV SSL_set_session_by_session_id(H_SSL hSsl , unsigned char* session_id , int len);
int	SEC_API_CALLING_CONV SSL_set_session_by_ssl(H_SSL hTo , H_SSL hFrom);
int	SEC_API_CALLING_CONV SSL_set_shutdown(H_SSL hSsl , int shutdown);
int	SEC_API_CALLING_CONV SSL_set_shutdown_mode(H_SSL hSsl , int mode);
int	SEC_API_CALLING_CONV SSL_set_single_step_mode(H_SSL hSsl , int mode);
int	SEC_API_CALLING_CONV SSL_set_type(H_SSL hSsl , int type);
int	SEC_API_CALLING_CONV SSL_set_verify_mode(H_SSL hSsl , int mode);
int	SEC_API_CALLING_CONV SSL_shutdown(H_SSL hSsl , int* shutdown_state);
int	SEC_API_CALLING_CONV SSL_write(H_SSL hSsl , const char* buf , int len);
int SEC_API_CALLING_CONV SSL_write_ex(H_SSL hSsl , char type , const char* buf , int len);

/* descriptive functions for SSL alerts*/
int SEC_API_CALLING_CONV SSL_ALERT_create(int description , int level , SSL_ALERT* alert);
int	SEC_API_CALLING_CONV SSL_ALERT_get_description(SSL_ALERT alert , int* description);
int	SEC_API_CALLING_CONV SSL_ALERT_get_description_info(SSL_ALERT alert , char** description);
int	SEC_API_CALLING_CONV SSL_ALERT_get_description_info_long(SSL_ALERT alert , char** description);
int	SEC_API_CALLING_CONV SSL_ALERT_get_level(SSL_ALERT alert , int* level);
int	SEC_API_CALLING_CONV SSL_ALERT_get_level_info(SSL_ALERT alert , char** level);
int	SEC_API_CALLING_CONV SSL_ALERT_get_level_info_long(SSL_ALERT alert , char** level);

/* descriptive functions for SSL cipher suites */
int	SEC_API_CALLING_CONV SSL_CIPHER_SUITE_get_info(H_SSL_CIPHER_SUITE hCipher_suite , char* buf , int len);
int	SEC_API_CALLING_CONV SSL_CIPHER_SUITE_get_name_info(H_SSL_CIPHER_SUITE hCipher_suite , char** name);
int	SEC_API_CALLING_CONV SSL_CIPHER_SUITE_get_sym_key_size(H_SSL_CIPHER_SUITE hCipher_suite , int* key_size);
int	SEC_API_CALLING_CONV SSL_CIPHER_SUITE_get_version_info(H_SSL_CIPHER_SUITE hCipher_suite , char** version);

/* SSL_CTX handling */
int	SEC_API_CALLING_CONV SSL_CTX_add_session(H_SSL_CTX hCtx , H_SSL_SESSION hSession , int* update);
int	SEC_API_CALLING_CONV SSL_CTX_flush_session_cache(H_SSL_CTX hCtx , long threshold);
int	SEC_API_CALLING_CONV SSL_CTX_free(H_SSL_CTX hCtx);
int	SEC_API_CALLING_CONV SSL_CTX_get_app_data(H_SSL_CTX hCtx , void** app_data);
int	SEC_API_CALLING_CONV SSL_CTX_get_data_preprocessor_callback(H_SSL_CTX hCtx , int(**cb)(H_SSL , char , char* , int , int*));
int	SEC_API_CALLING_CONV SSL_CTX_get_default_cipher_suites(H_SSL_CTX hCtx , H_SSL_CIPHER_SUITE* hCipher_suites , int* num_cipher_suites);
int	SEC_API_CALLING_CONV SSL_CTX_get_default_handshake_callback(H_SSL_CTX hCtx , void(**cb)(H_SSL , int , int));
int	SEC_API_CALLING_CONV SSL_CTX_get_default_pse_pin_callback(H_SSL_CTX hCtx , int(**cb)(void* , void*));
int	SEC_API_CALLING_CONV SSL_CTX_get_default_read_ahead_mode(H_SSL_CTX hCtx , int* mode);
int	SEC_API_CALLING_CONV SSL_CTX_get_default_shutdown_mode(H_SSL_CTX hCtx , int* mode);
int	SEC_API_CALLING_CONV SSL_CTX_get_default_verify_mode(H_SSL_CTX hCtx , int* mode);
int	SEC_API_CALLING_CONV SSL_CTX_get_random_number_generator_callback(H_SSL_CTX hCtx , int purpose , int(**cb)(H_SSL , char* , int));
int SEC_API_CALLING_CONV SSL_CTX_get_reference_counter(H_SSL_CTX hCtx , int* reference_counter);
int	SEC_API_CALLING_CONV SSL_CTX_get_session_cache_add_callback(H_SSL_CTX hCtx , int(**cb)(H_SSL , H_SSL_SESSION));
int	SEC_API_CALLING_CONV SSL_CTX_get_session_cache_get_callback(H_SSL_CTX hCtx , H_SSL_SESSION(**cb)(H_SSL , unsigned char* , int , int*));
int	SEC_API_CALLING_CONV SSL_CTX_get_session_cache_max_items(H_SSL_CTX hCtx, int* max_items);
int	SEC_API_CALLING_CONV SSL_CTX_get_session_cache_mode(H_SSL_CTX hCtx , int* mode);
int	SEC_API_CALLING_CONV SSL_CTX_get_session_cache_number(H_SSL_CTX hCtx , int* number_of_sessions);
int	SEC_API_CALLING_CONV SSL_CTX_get_session_cache_remove_callback(H_SSL_CTX hCtx , void(**cb)(H_SSL_CTX , H_SSL_SESSION));
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_accept_attempt(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_accept_success(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_connect_attempt(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_connect_success(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_session_resumption_attempt(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_session_resumption_failure_denial(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_session_resumption_failure_lookup(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_session_resumption_failure_timeout(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_session_resumption_lookup_callback(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_stats_session_resumption_success(H_SSL_CTX hCtx , int* stats);
int	SEC_API_CALLING_CONV SSL_CTX_get_used_default_dhe(H_SSL_CTX hCtx , int* used);
int	SEC_API_CALLING_CONV SSL_CTX_new(H_SSL_CTX* hCtx , unsigned short version , int type);
int	SEC_API_CALLING_CONV SSL_CTX_remove_session(H_SSL_CTX hCtx , H_SSL_SESSION hSession , int* update);
int	SEC_API_CALLING_CONV SSL_CTX_set_app_data(H_SSL_CTX hCtx , void* app_data);
int	SEC_API_CALLING_CONV SSL_CTX_set_data_preprocessor_callback(H_SSL_CTX hCtx , int(*cb)(H_SSL , char , char* , int , int*));
int	SEC_API_CALLING_CONV SSL_CTX_set_default_cipher_suites(H_SSL_CTX hCtx , char* cipher_suites);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_dhe(H_SSL_CTX hCtx , AlgId* dhe);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_handshake_callback(H_SSL_CTX hCtx , void(*cb)(H_SSL , int , int));
int	SEC_API_CALLING_CONV SSL_CTX_set_default_pse_by_name(H_SSL_CTX hCtx , char* pse_name , AF_options* af_options , int sct_id, void* cb_arg);
int SEC_API_CALLING_CONV SSL_CTX_set_default_pse_by_pse(H_SSL_CTX hCtx , PSE pse);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_pse_pin_callback(H_SSL_CTX hCtx , int(*cb)(void* , void*));
int	SEC_API_CALLING_CONV SSL_CTX_set_default_read_ahead_mode(H_SSL_CTX hCtx , int mode);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_rsae(H_SSL_CTX hCtx , Key* rsae);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_shutdown_mode(H_SSL_CTX hCtx , int mode);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_size_for_dhe(H_SSL_CTX hCtx , int key_size);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_size_for_rsae(H_SSL_CTX hCtx , int key_size);
int	SEC_API_CALLING_CONV SSL_CTX_set_default_verify_mode(H_SSL_CTX hCtx , int mode);
int	SEC_API_CALLING_CONV SSL_CTX_set_options(H_SSL_CTX hCtx , unsigned long options);
int	SEC_API_CALLING_CONV SSL_CTX_set_random_number_generator_callback(H_SSL_CTX hCtx , int purpose , int(*cb)(H_SSL , char* , int));
int	SEC_API_CALLING_CONV SSL_CTX_set_session_cache_add_callback(H_SSL_CTX hCtx , int(*cb)(H_SSL , H_SSL_SESSION));
int	SEC_API_CALLING_CONV SSL_CTX_set_session_cache_get_callback(H_SSL_CTX hCtx , H_SSL_SESSION(*cb)(H_SSL , unsigned char* , int , int*));
int	SEC_API_CALLING_CONV SSL_CTX_set_session_cache_max_items(H_SSL_CTX hCtx, int max_items);
int	SEC_API_CALLING_CONV SSL_CTX_set_session_cache_mode(H_SSL_CTX hCtx , int mode);
int	SEC_API_CALLING_CONV SSL_CTX_set_session_cache_remove_callback(H_SSL_CTX hCtx , void(*cb)(H_SSL_CTX , H_SSL_SESSION));

/* SSL_SESSION handling */
int	SEC_API_CALLING_CONV SSL_SESSION_decode(H_SSL_SESSION* hSession, OctetString* encoded_session);
int	SEC_API_CALLING_CONV SSL_SESSION_encode(H_SSL_SESSION hSession , OctetString** encoded_session);
int	SEC_API_CALLING_CONV SSL_SESSION_free(H_SSL_SESSION hSession);
int	SEC_API_CALLING_CONV SSL_SESSION_get_app_data(H_SSL_SESSION hSession , void** app_data);
int	SEC_API_CALLING_CONV SSL_SESSION_get_session_id(H_SSL_SESSION hSession , char* session_id , int* len);
int	SEC_API_CALLING_CONV SSL_SESSION_get_time(H_SSL_SESSION hSession , long* time_value);
int	SEC_API_CALLING_CONV SSL_SESSION_get_timeout(H_SSL_SESSION hSession , long* timeout_value);
int SEC_API_CALLING_CONV SSL_SESSION_new(H_SSL_SESSION* hSession , long timeout_value);
int	SEC_API_CALLING_CONV SSL_SESSION_print(H_SSL_SESSION hSession , H_BIO hBio);
int	SEC_API_CALLING_CONV SSL_SESSION_print_fp(H_SSL_SESSION hSession , FILE* fp);
int	SEC_API_CALLING_CONV SSL_SESSION_set_app_data(H_SSL_SESSION hSession , void* app_data);
int	SEC_API_CALLING_CONV SSL_SESSION_set_time(H_SSL_SESSION hSession , long time_value);
int	SEC_API_CALLING_CONV SSL_SESSION_set_timeout(H_SSL_SESSION hSession , long timeout_value);


/*------------------------------ the error codes ------------------------------*/


/* legend:							*
 * AP - Alert Protocol				*
 * CP - Change cipher spec Protocol	*
 * HP - Handshake Protocol			*
 * RP - Record Protocol				*/

#define ESSL_API_BAD_WRITE_RETRY							(0x500 | SECUDE_SSL_API)
#define ESSL_API_BUFFER_TOO_SMALL							(0x501 | SECUDE_SSL_API)
#define ESSL_API_FUNCTIONALITY_NOT_AVAILABLE				(0x502 | SECUDE_SSL_API)
#define ESSL_API_HANDSHAKE_FAILURE							(0x503 | SECUDE_SSL_API)
#define ESSL_API_INCOMPATIBLE_SSL_VERSION					(0x504 | SECUDE_SSL_API)
#define ESSL_API_HSSL_HAS_NO_BIO_READ						(0x505 | SECUDE_SSL_API)
#define ESSL_API_HSSL_HAS_NO_BIO_WRITE						(0x506 | SECUDE_SSL_API)
#define ESSL_API_HSSL_HAS_NO_CTX							(0x507 | SECUDE_SSL_API)
#define ESSL_API_HSSL_HAS_NO_PEER_CERTIFICATES				(0x508 | SECUDE_SSL_API)
#define ESSL_API_HSSL_HAS_NO_SESSION						(0x509 | SECUDE_SSL_API)
#define ESSL_API_HSSL_HAS_NO_TYPE							(0x50A | SECUDE_SSL_API)
#define ESSL_API_HSSL_IS_CLOSED								(0x50B | SECUDE_SSL_API)
#define ESSL_API_HSSL_IS_NOT_CLOSED							(0x50C | SECUDE_SSL_API)
#define ESSL_API_NOT_INITIALIZED							(0x50D | SECUDE_SSL_API)
#define ESSL_API_NO_BIO_OF_REQUESTED_TYPE					(0x50E | SECUDE_SSL_API)
#define ESSL_API_NO_CERTIFICATE_REQUEST_RECEIVED			(0x50F | SECUDE_SSL_API)
#define ESSL_API_NO_CIPHER_SUITES_AVAILABLE					(0x510 | SECUDE_SSL_API)
#define ESSL_API_NO_CIPHER_SUITE_N							(0x511 | SECUDE_SSL_API)
#define ESSL_API_RENEGOTIATION_DISABLED						(0x512 | SECUDE_SSL_API)
#define ESSL_API_SESSION_LOOKUP_FAILED						(0x513 | SECUDE_SSL_API)
#define ESSL_API_UNSUPPORTED_SSL_VERSION					(0x514 | SECUDE_SSL_API)

#define ESSL_AP_BAD_FORMAT									(0x100 | SECUDE_SSL_API)
#define ESSL_AP_BAD_LEVEL									(0x101 | SECUDE_SSL_API)
#define ESSL_AP_BAD_DESCRIPTION								(0x102 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_CLOSE_NOTIFY					(0x1000 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_UNEXPECTED_MESSAGE				(0x1010 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_BAD_RECORD_MAC					(0x1020 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_DECOMPRESSION_FAILURE			(0x1030 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_HANDSHAKE_FAILURE				(0x1040 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_NO_CERTIFICATE					(0x1041 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_BAD_CERTIFICATE					(0x1042 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_UNSUPPORTED_CERTIFICATE			(0x1043 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_CERTIFICATE_REVOKED				(0x1044 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_CERTIFICATE_EXPIRED				(0x1045 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_CERTIFICATE_UNKNOWN				(0x1046 | SECUDE_SSL_API)
#define ESSL_AP_SSLV3_ALERT_ILLEGAL_PARAMETER				(0x1047 | SECUDE_SSL_API)

#define ESSL_CP_BAD_FORMAT									(0x200 | SECUDE_SSL_API)
#define ESSL_CP_TOO_EARLY									(0x201 | SECUDE_SSL_API)

#define ESSL_HP_APP_DATA_IN_HANDSHAKE						(0x300 | SECUDE_SSL_API)
#define ESSL_HP_BAD_FORMAT									(0x301 | SECUDE_SSL_API)
#define ESSL_HP_CERTIFICATE_VERIFY_BAD_SIGNATURE			(0x302 | SECUDE_SSL_API)
#define ESSL_HP_CERTIFICATE_WRONG_CERT_TYPE					(0x303 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_HELLO_NO_NULL_COMPRESSION			(0x304 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_HELLO_NO_SHARED_CIPHER_SUITE			(0x305 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_HELLO_NO_SUPPORTED_CIPHER_SUITE		(0x306 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_HELLO_UNSUPPORTED_CLIENT_VERSION		(0x307 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_HELLO_BAD_CIPHER_SUITE				(0x308 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_KEY_EXCHANGE_BAD_CLIENT_VERSION		(0x309 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_KEY_EXCHANGE_NO_DHE					(0x30A | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_KEY_EXCHANGE_NO_RSAE					(0x30B | SECUDE_SSL_API)
#define ESSL_HP_FINISHED_HASH_CHECK_FAILED					(0x30C | SECUDE_SSL_API)
#define ESSL_HP_NO_PSE_FOR_NEGOTIATED_CIPHER_SUITE			(0x30D | SECUDE_SSL_API)
#define ESSL_HP_SERVER_HELLO_BAD_CIPHER_SUITE				(0x30E | SECUDE_SSL_API)
#define ESSL_HP_SERVER_HELLO_BAD_SERVER_VERSION				(0x30F | SECUDE_SSL_API)
#define ESSL_HP_SERVER_HELLO_UNSUPPORTED_COMPRESSION_METHOD	(0x310 | SECUDE_SSL_API)
#define ESSL_HP_SERVER_HELLO_UNSUPPORTED_SERVER_VERSION		(0x311 | SECUDE_SSL_API)
#define ESSL_HP_UNEXPECTED_MESSAGE							(0x312 | SECUDE_SSL_API)
#define ESSL_HP_UNSUPPORTED_CIPHER_SUITE_NEGOTIATED			(0x313 | SECUDE_SSL_API)
#define ESSL_HP_CLIENT_HELLO_NO_SESSION_TO_RESUME			(0x314 | SECUDE_SSL_API)

#define ESSL_RP_BAD_FORMAT									(0x420 | SECUDE_SSL_API)
#define ESSL_RP_BAD_MAC										(0x421 | SECUDE_SSL_API)
#define ESSL_RP_BAD_VERSION									(0x422 | SECUDE_SSL_API)
#define ESSL_RP_UNEXPECTED_RECORD							(0x423 | SECUDE_SSL_API)

#ifdef  __cplusplus
}
#endif
#endif



