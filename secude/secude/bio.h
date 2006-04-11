/* bio.h */
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


#ifndef HEADER_BIO_H
#define HEADER_BIO_H

#ifdef  __cplusplus
extern "C" {
#endif


/*------------------------------ the typedefs ------------------------------*/

/***** Typedef H_BIO *****/
/** BIO handle
  * @ingroup header_bio
  */
typedef struct BIO*		H_BIO;
typedef struct BUF_MEM*	H_BUF_MEM;

#ifndef HEADER_SSL_H
typedef struct SSL*		H_SSL;
typedef struct SSL_CTX*	H_SSL_CTX;
#endif


/*------------------------------ the includes ------------------------------*/


#include <stdio.h>

/* ANSI version for variable length args */
#ifndef __STDARG_H__
#include <stdarg.h>
#endif /* __STDARG_H__ */

#include <secude/af.h>

#if defined(SEC_OPEN_TRANSPORT) && SEC_OPEN_TRANSPORT
#include <CoreServices/CoreServices.h>
#endif

/*------------------------------ the constants ------------------------------*/


#define SECUDE_SSL_API 0x20000000


/* return values for functions */
#define BIO_FAILURE					0
#define BIO_SUCCESS					1

/* boolean constants */
#define BIO_FALSE					0
#define BIO_TRUE					1

/* These are the 'types' of BIOs */
#define BIO_TYPE_ACCEPT_SOCKET		(1 | 0x0400|0x0100)
#define BIO_TYPE_BUFFER				(2 | 0x0200)
#define BIO_TYPE_CONNECT_SOCKET		(3 | 0x0400|0x0100)
#define BIO_TYPE_FD					(4 | 0x0400|0x0100)
#define BIO_TYPE_FILE				(5 | 0x0400)
#define BIO_TYPE_MEM				(6 | 0x0400)
#define BIO_TYPE_NULL				(7 | 0x0400)
#define BIO_TYPE_SOCKET				(8 | 0x0400|0x0100)
#define BIO_TYPE_SSL				(9 | 0x0200)
#ifdef WIN32
#define BIO_TYPE_WSP_SOCKET			(10| 0x0400|0x0100)
#endif
#if defined(SEC_OPEN_TRANSPORT) && SEC_OPEN_TRANSPORT
#define BIO_TYPE_EP					(11| 0x0400)
#endif

#define BIO_TYPE_DESCRIPTOR			0x0100	/* fd, socket, accept_socket, connect_socket, wsp_socket */
#define BIO_TYPE_FILTER				0x0200
#define BIO_TYPE_SOURCE_SINK		0x0400

/* The callback is called before and after the underlying operation. The		*
 * BIO_CB_RETURN flag is used to distinguish between before and after the call	*/
#define BIO_CB_RETURN				0x80

/* These are passed by the BIO callback */
#define BIO_CB_FREE					0x01
#define BIO_CB_READ					0x02
#define BIO_CB_WRITE				0x03
#define BIO_CB_PUTS					0x04
#define BIO_CB_GETS					0x05
#define BIO_CB_CTRL					0x06

#define BIO_FLAGS_READ				0x01
#define BIO_FLAGS_WRITE				0x02
#define BIO_FLAGS_IO_SPECIAL		0x04
#define BIO_FLAGS_RWS				(BIO_FLAGS_READ | BIO_FLAGS_WRITE | BIO_FLAGS_IO_SPECIAL)
#define BIO_FLAGS_SHOULD_RETRY		0x08

/* The next constant is used in conjunction with the BIO_should_retry_io_special function.	*
 * If this function returns BIO_TRUE, the BIO_get_retry_reason_and_bio function will walk	*
 * the BIO stack and return the reason and the offending BIO. Given a BIO, the				*
 * BIO_get_retry_reason function will return the code.										*/
#define BIO_RR_CONNECT				0x01 /* returned from the connect BIO when a connect would have blocked */

/* shall the underlying I/O mechanism be closed/freed if the BIO is destroyed? */
#define BIO_NOCLOSE					0x00
#define BIO_CLOSE					0x01

/* I/O modes for BIO_TYPE_ACCEPT_SOCKET */
#define BIO_BLOCKING				0
#define BIO_NON_BLOCKING			1

/* modifiers for BIO_TYPE_FILE */
#define BIO_FP_READ					0x02
#define BIO_FP_WRITE				0x04
#define BIO_FP_APPEND				0x08
#define BIO_FP_TEXT					0x10

/* send and recv modifiers for BIO_TYPE_WSP_SOCKET */
#define	BIO_SRT_PLAIN				0
#define BIO_SRT_DISCONNECT			1
#define BIO_SRT_TO_FROM				2
#define BIO_SRT_ACK					3 /* to acknowledge that BIO_SRT_DISCONNECT was executed */


/*------------------------------ the functions ------------------------------*/


int	SEC_API_CALLING_CONV BIO_callback_is_post(int cmd , int* is_post);
int	SEC_API_CALLING_CONV BIO_callback_is_pre(int cmd , int* is_pre);
int	SEC_API_CALLING_CONV BIO_callback_sample(H_BIO hBio , int cmd , void* argp , int argi , long argl , int* ret);
int	SEC_API_CALLING_CONV BIO_callback_set_cmd_to_post(int* cmd);
int	SEC_API_CALLING_CONV BIO_dump(H_BIO hBio , char* buf , int len);
int	SEC_API_CALLING_CONV BIO_dup_chain(H_BIO hOrg , H_BIO* hDup);
int	SEC_API_CALLING_CONV BIO_dup_state(H_BIO hOrg , H_BIO hDup);
int	SEC_API_CALLING_CONV BIO_find_type(H_BIO hBio , int bio_type , H_BIO* hBio_found);
int	SEC_API_CALLING_CONV BIO_flush(H_BIO hBio);
int	SEC_API_CALLING_CONV BIO_free(H_BIO hBio);
int	SEC_API_CALLING_CONV BIO_free_all(H_BIO hBio);
int	SEC_API_CALLING_CONV BIO_gets(H_BIO hBio , char* buf , int len , int* amount);
int	SEC_API_CALLING_CONV BIO_get_amount_read(H_BIO hBio , unsigned long* amount);
int	SEC_API_CALLING_CONV BIO_get_amount_written(H_BIO hBio , unsigned long* amount);
int	SEC_API_CALLING_CONV BIO_get_app_data(H_BIO hBio , void** app_data);
int	SEC_API_CALLING_CONV BIO_get_callback(H_BIO hBio , int(**cb)(H_BIO , int , void* , int , long , int*));
int	SEC_API_CALLING_CONV BIO_get_callback_arg(H_BIO hBio , void** cb_arg);
int	SEC_API_CALLING_CONV BIO_get_close_mode(H_BIO hBio , int* close_mode);
int	SEC_API_CALLING_CONV BIO_get_internals(H_BIO hBio , int* amount_pos , void** bio_mem);
int	SEC_API_CALLING_CONV BIO_get_retry_reason(H_BIO hBio , int* reason);
int SEC_API_CALLING_CONV BIO_get_retry_reason_and_bio(H_BIO hBio , H_BIO* hRetry_bio , int* reason);
int	SEC_API_CALLING_CONV BIO_get_retry_type(H_BIO hBio , int* type);
int	SEC_API_CALLING_CONV BIO_get_type(H_BIO hBio , int* type);
int	SEC_API_CALLING_CONV BIO_get_type_name(H_BIO hBio , char** name);
int	SEC_API_CALLING_CONV BIO_new(H_BIO* hBio , int type);
int	SEC_API_CALLING_CONV BIO_pending_read(H_BIO hBio , int* amount);
int	SEC_API_CALLING_CONV BIO_pending_write(H_BIO hBio , int* amount);
int	SEC_API_CALLING_CONV BIO_pop(H_BIO* hBio_stack , H_BIO* hBio_popped);
int	SEC_API_CALLING_CONV BIO_printf(H_BIO hBio , ...);
int	SEC_API_CALLING_CONV BIO_push(H_BIO* hBio_stack , H_BIO hBio_push);
int	SEC_API_CALLING_CONV BIO_puts(H_BIO hBio , char* buf , int* amount);
int	SEC_API_CALLING_CONV BIO_read(H_BIO hBio , char* buf , int len);
int	SEC_API_CALLING_CONV BIO_reset(H_BIO hBio);
int	SEC_API_CALLING_CONV BIO_set_app_data(H_BIO hBio , void* app_data);
int	SEC_API_CALLING_CONV BIO_set_callback(H_BIO hBio , int(*cb)(H_BIO , int , void* , int , long , int*));
int	SEC_API_CALLING_CONV BIO_set_callback_arg(H_BIO hBio , void* argp);
int	SEC_API_CALLING_CONV BIO_set_close_mode(H_BIO hBio , int close_mode);
int	SEC_API_CALLING_CONV BIO_should_retry(H_BIO hBio , int* true_false);
int	SEC_API_CALLING_CONV BIO_should_retry_io_special(H_BIO hBio , int* true_false);
int	SEC_API_CALLING_CONV BIO_should_retry_read(H_BIO hBio , int* true_false);
int	SEC_API_CALLING_CONV BIO_should_retry_write(H_BIO hBio , int* true_false);
int	SEC_API_CALLING_CONV BIO_write(H_BIO hBio , char* buf , int len);


/* BIO_TYPE_ACCEPT_SOCKET */
int	SEC_API_CALLING_CONV BIO_accept_socket_do_accept(H_BIO hBio);
int	SEC_API_CALLING_CONV BIO_accept_socket_get_fd(H_BIO hBio , unsigned int* fdp);
int	SEC_API_CALLING_CONV BIO_accept_socket_is_non_fatal_error(int error , int* true_false);
int	SEC_API_CALLING_CONV BIO_accept_socket_new(H_BIO* hBio , char* host_port);
int	SEC_API_CALLING_CONV BIO_accept_socket_set_bio(H_BIO hBio , H_BIO hBio_new);
int	SEC_API_CALLING_CONV BIO_accept_socket_set_nbio(H_BIO hBio , int mode);
int	SEC_API_CALLING_CONV BIO_accept_socket_set_port(H_BIO hBio , char* portp);
int	SEC_API_CALLING_CONV BIO_accept_socket_should_retry(int last_io , int* true_false);


/* BIO_TYPE_BUFFER */
int	SEC_API_CALLING_CONV BIO_buf_get_num_lines(H_BIO hBbio , int* num_lines);
int	SEC_API_CALLING_CONV BIO_buf_new(H_BIO* hBio);
int	SEC_API_CALLING_CONV BIO_buf_set_read_size(H_BIO hBio , int size);
int	SEC_API_CALLING_CONV BIO_buf_set_size(H_BIO hBio , int size);
int	SEC_API_CALLING_CONV BIO_buf_set_write_size(H_BIO hBio , int size);

/* BIO_TYPE_CONNECT_SOCKET */
int	SEC_API_CALLING_CONV BIO_connect_socket_do_connect(H_BIO hBio);
int	SEC_API_CALLING_CONV BIO_connect_socket_get_fd(H_BIO hBio , unsigned int* fdp);
int	SEC_API_CALLING_CONV BIO_connect_socket_is_non_fatal_error(int error , int* true_false);
int	SEC_API_CALLING_CONV BIO_connect_socket_new(H_BIO* hBio , char* host_port);
int	SEC_API_CALLING_CONV BIO_connect_socket_set_hostname(H_BIO hBio , char* name);
int	SEC_API_CALLING_CONV BIO_connect_socket_set_nbio(H_BIO hBio , int mode);
int	SEC_API_CALLING_CONV BIO_connect_socket_set_port(H_BIO hBio , char* portp);
int	SEC_API_CALLING_CONV BIO_connect_socket_should_retry(int last_io , int* true_false);

/* BIO_TYPE_FD */
int	SEC_API_CALLING_CONV BIO_fd_get_fd(H_BIO hBio , unsigned int* fdp);
int	SEC_API_CALLING_CONV BIO_fd_is_non_fatal_error(int error , int* true_false);
int	SEC_API_CALLING_CONV BIO_fd_new(H_BIO* hBio , unsigned int fd , int close_mode);
int	SEC_API_CALLING_CONV BIO_fd_set_fd(H_BIO hBio , unsigned int fd , int close_mode);
int	SEC_API_CALLING_CONV BIO_fd_should_retry(int last_io , int* true_false);


/* BIO_TYPE_FILE */
int	SEC_API_CALLING_CONV BIO_file_eof(H_BIO hBio , int* true_false);
int	SEC_API_CALLING_CONV BIO_file_new_by_filename(H_BIO* hBio , char* filename , char* mode);
int	SEC_API_CALLING_CONV BIO_file_new_by_filep(H_BIO* hBio , FILE* stream , int close_mode);
int	SEC_API_CALLING_CONV BIO_file_get_filep(H_BIO hBio , FILE** fpp);
int	SEC_API_CALLING_CONV BIO_file_set_filename_append(H_BIO hBio , char* filename);
int	SEC_API_CALLING_CONV BIO_file_set_filename_read(H_BIO hBio , char* filename);
int	SEC_API_CALLING_CONV BIO_file_set_filename_write(H_BIO hBio , char* filename);
int	SEC_API_CALLING_CONV BIO_file_set_filep(H_BIO hBio , FILE* fp , int close_mode);


/* BIO_TYPE_MEM */
int	SEC_API_CALLING_CONV BIO_mem_eof(H_BIO hBio , int* true_false);
int	SEC_API_CALLING_CONV BIO_mem_get_mem(H_BIO hBio , void** mempp);
int	SEC_API_CALLING_CONV BIO_mem_new(H_BIO* hBio);
int	SEC_API_CALLING_CONV BIO_mem_set_mem(H_BIO hBio , void* memp , long close_mode);


/* BIO_TYPE_NULL */
int SEC_API_CALLING_CONV BIO_null_new(H_BIO* hBio);


/* BIO_TYPE_SOCKET */
int	SEC_API_CALLING_CONV BIO_socket_get_fd(H_BIO hBio , unsigned int* fdp);
int	SEC_API_CALLING_CONV BIO_socket_is_non_fatal_error(int error , int* true_false);
int	SEC_API_CALLING_CONV BIO_socket_new(H_BIO* hBio , unsigned int sock , int close_mode);
int	SEC_API_CALLING_CONV BIO_socket_set_fd(H_BIO hBio , unsigned int fd , int close_mode);
int	SEC_API_CALLING_CONV BIO_socket_should_retry(int last_io , int* true_false);


/* BIO_TYPE_SSL */
int	SEC_API_CALLING_CONV BIO_ssl_copy_session_id(H_BIO hTo , H_BIO hFrom);
int	SEC_API_CALLING_CONV BIO_ssl_do_handshake(H_BIO hBbio);
int	SEC_API_CALLING_CONV BIO_ssl_get_ssl(H_BIO hBio , H_SSL* hSsl);
int	SEC_API_CALLING_CONV BIO_ssl_new(H_BIO* hBio , H_SSL_CTX hCtx , int type);
int	SEC_API_CALLING_CONV BIO_ssl_set_ssl(H_BIO hBio , H_SSL hSsl , int close_mode);
int	SEC_API_CALLING_CONV BIO_ssl_set_type(H_BIO hBio , int type);
int	SEC_API_CALLING_CONV BIO_ssl_shutdown(H_BIO hBio);


#if ((defined _WINSOCK2API_) && (defined _WINSOCK2SPI_))

/* BIO_TYPE_WSP_SOCKET */
int	SEC_API_CALLING_CONV BIO_wsp_socket_get_fd(H_BIO hBio , unsigned int* fdp);
int	SEC_API_CALLING_CONV BIO_wsp_socket_new(H_BIO* hBio , unsigned int sock);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_fd(H_BIO hBio , unsigned int fd , int close_mode);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_params(H_BIO hBio , char SRType , DWORD dwFlags , LPDWORD lpFlags ,
												   LPWSAOVERLAPPED lpOverlapped ,
												   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine ,
												   LPWSATHREADID lpThreadId , LPINT lpErrno);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_recv(H_BIO hBio , LPWSPRECV funcp);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_recv_disconnect(H_BIO hBio , LPWSPRECVDISCONNECT funcp);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_recv_from(H_BIO hBio , LPWSPRECVFROM funcp);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_send(H_BIO hBio , LPWSPSEND funcp);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_send_disconnect(H_BIO hBio , LPWSPSENDDISCONNECT funcp);
int	SEC_API_CALLING_CONV BIO_wsp_socket_set_send_to(H_BIO hBio , LPWSPSENDTO funcp);

#endif /* (defined _WINSOCK2API_) && (defined _WINSOCK2SPI_) */

#if defined(SEC_OPEN_TRANSPORT) && SEC_OPEN_TRANSPORT
/* BIO_TYPE_FD */
int	SEC_API_CALLING_CONV BIO_ep_get_ep(H_BIO hBio , EndpointRef* epp);
int	SEC_API_CALLING_CONV BIO_ep_is_non_fatal_error(OSStatus error , int* true_false);
int	SEC_API_CALLING_CONV BIO_ep_new(H_BIO* hBio , EndpointRef ep , int close_mode);
int	SEC_API_CALLING_CONV BIO_ep_set_ep(H_BIO hBio , EndpointRef ep , int close_mode);
int	SEC_API_CALLING_CONV BIO_ep_should_retry(OTResult last_io , int* true_false);
#endif  /* defined(SEC_OPEN_TRANSPORT) && SEC_OPEN_TRANSPORT */


/*------------------------------ helper functions for message timing in socket (for testing only) ------------------------------*/

#ifdef SSL_TST_ATT
int SEC_API_CALLING_CONV BIO_socket_get_last_read_timer_start(H_BIO bio, LARGE_INTEGER * p_lInt);
int SEC_API_CALLING_CONV BIO_socket_start_read_timer(H_BIO b);
int SEC_API_CALLING_CONV BIO_socket_reset_read_timer(H_BIO b);
#endif

/*------------------------------ the error codes ------------------------------*/


#define EBIO_ACCEPT_ERROR							(0x000 | SECUDE_SSL_API)
#define EBIO_BAD_FOPEN_MODE							(0x001 | SECUDE_SSL_API)
#define EBIO_BAD_HOSTNAME_LOOKUP					(0x002 | SECUDE_SSL_API)
#define EBIO_CONNECT_ERROR							(0x003 | SECUDE_SSL_API)
#define EBIO_CTRL_FAILURE							(0x004 | SECUDE_SSL_API)
#define EBIO_ERROR_SETTING_NBIO						(0x005 | SECUDE_SSL_API)
#define EBIO_ERROR_SETTING_NBIO_ON_ACCEPTED_SOCKET	(0x006 | SECUDE_SSL_API)
#define EBIO_ERROR_SETTING_NBIO_ON_ACCEPT_SOCKET	(0x007 | SECUDE_SSL_API)
#define EBIO_FUNCTIONALITY_NOT_AVAILABLE			(0x008 | SECUDE_SSL_API)
#define EBIO_GETHOSTBYNAME_ADDR_IS_NOT_AF_INET		(0x009 | SECUDE_SSL_API)
#define EBIO_INVALID_IP_ADDRESS						(0x00A | SECUDE_SSL_API)
#define EBIO_NBIO_CONNECT_ERROR						(0x00B | SECUDE_SSL_API)
#define EBIO_NO_ACCEPT_PORT_SPECIFIED				(0x00C | SECUDE_SSL_API)
#define EBIO_NO_HOSTNAME_SPECIFIED					(0x00D | SECUDE_SSL_API)
#define EBIO_NO_PORT_DEFINED						(0x00E | SECUDE_SSL_API)
#define EBIO_NO_PORT_SPECIFIED						(0x00F | SECUDE_SSL_API)
#define EBIO_TYPE_NOT_FOUND							(0x010 | SECUDE_SSL_API)
#define EBIO_UNABLE_TO_BIND_SOCKET					(0x011 | SECUDE_SSL_API)
#define EBIO_UNABLE_TO_CREATE_SOCKET				(0x012 | SECUDE_SSL_API)
#define EBIO_UNABLE_TO_LISTEN_SOCKET				(0x013 | SECUDE_SSL_API)
#define EBIO_UNINITIALIZED							(0x014 | SECUDE_SSL_API)
#define EBIO_UNSUPPORTED_CTRL						(0x015 | SECUDE_SSL_API)
#define EBIO_WSASTARTUP								(0x016 | SECUDE_SSL_API)


#ifdef  __cplusplus
}
#endif
#endif



