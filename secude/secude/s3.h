/* ssl3.h */
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


#ifndef HEADER_SSL3_H 
#define HEADER_SSL3_H 

#ifdef  __cplusplus
extern "C" {
#endif

#include <secude/ssl.h>


/*------------------------------ the constants ------------------------------*/


#define SSL3_VERSION						0x0300
#define SSL3_VERSION_MAJOR					0x03
#define SSL3_VERSION_MINOR					0x00

/* SSL cipher suite IDs: 4 Bytes, first Byte is SSL version */
#define SSL3_CK_RSA_NULL_MD5				0x03000001
#define SSL3_CK_RSA_NULL_SHA				0x03000002
#define SSL3_CK_RSA_RC4_40_MD5 				0x03000003
#define SSL3_CK_RSA_RC4_128_MD5				0x03000004
#define SSL3_CK_RSA_RC4_128_SHA				0x03000005
#define SSL3_CK_RSA_RC2_40_MD5				0x03000006
#define SSL3_CK_RSA_IDEA_128_SHA			0x03000007
#define SSL3_CK_RSA_DES_40_CBC_SHA			0x03000008
#define SSL3_CK_RSA_DES_64_CBC_SHA			0x03000009
#define SSL3_CK_RSA_DES_192_CBC3_SHA		0x0300000A

#define SSL3_CK_DH_DSS_DES_40_CBC_SHA		0x0300000B
#define SSL3_CK_DH_DSS_DES_64_CBC_SHA		0x0300000C
#define SSL3_CK_DH_DSS_DES_192_CBC3_SHA 	0x0300000D
#define SSL3_CK_DH_RSA_DES_40_CBC_SHA		0x0300000E
#define SSL3_CK_DH_RSA_DES_64_CBC_SHA		0x0300000F
#define SSL3_CK_DH_RSA_DES_192_CBC3_SHA 	0x03000010

#define SSL3_CK_DHE_DSS_DES_40_CBC_SHA		0x03000011
#define SSL3_CK_DHE_DSS_DES_64_CBC_SHA		0x03000012
#define SSL3_CK_DHE_DSS_DES_192_CBC3_SHA	0x03000013
#define SSL3_CK_DHE_RSA_DES_40_CBC_SHA		0x03000014
#define SSL3_CK_DHE_RSA_DES_64_CBC_SHA		0x03000015
#define SSL3_CK_DHE_RSA_DES_192_CBC3_SHA	0x03000016

#define SSL3_CK_ADH_RC4_40_MD5				0x03000017
#define SSL3_CK_ADH_RC4_128_MD5				0x03000018
#define SSL3_CK_ADH_DES_40_CBC_SHA			0x03000019
#define SSL3_CK_ADH_DES_64_CBC_SHA			0x0300001A
#define SSL3_CK_ADH_DES_192_CBC_SHA			0x0300001B

#define SSL3_CK_FZA_DMS_NULL_SHA			0x0300001C
#define SSL3_CK_FZA_DMS_FZA_SHA				0x0300001D
#define SSL3_CK_FZA_DMS_RC4_SHA				0x0300001E

/* names of the SSL cipher suites */
#define SSL3_TXT_RSA_NULL_MD5				"SSL_RSA_WITH_NULL_MD5"
#define SSL3_TXT_RSA_NULL_SHA				"SSL_RSA_WITH_NULL_SHA"
#define SSL3_TXT_RSA_RC4_40_MD5 			"SSL_RSA_EXPORT_WITH_RC4_40_MD5"
#define SSL3_TXT_RSA_RC4_128_MD5			"SSL_RSA_WITH_RC4_128_MD5"
#define SSL3_TXT_RSA_RC4_128_SHA			"SSL_RSA_WITH_RC4_128_SHA"
#define SSL3_TXT_RSA_RC2_40_MD5				"SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5"
#define SSL3_TXT_RSA_IDEA_128_SHA			"SSL_RSA_WITH_IDEA_CBC_SHA"
#define SSL3_TXT_RSA_DES_40_CBC_SHA			"SSL_RSA_EXPORT_WITH_DES40_CBC_SHA"
#define SSL3_TXT_RSA_DES_64_CBC_SHA			"SSL_RSA_WITH_DES_CBC_SHA"
#define SSL3_TXT_RSA_DES_192_CBC3_SHA		"SSL_RSA_WITH_3DES_EDE_CBC_SHA"

#define SSL3_TXT_DH_DSS_DES_40_CBC_SHA		"SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA"
#define SSL3_TXT_DH_DSS_DES_64_CBC_SHA		"SSL_DH_DSS_WITH_DES_CBC_SHA"
#define SSL3_TXT_DH_DSS_DES_192_CBC3_SHA 	"SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA"
#define SSL3_TXT_DH_RSA_DES_40_CBC_SHA		"SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA"
#define SSL3_TXT_DH_RSA_DES_64_CBC_SHA		"SSL_DH_RSA_WITH_DES_CBC_SHA"
#define SSL3_TXT_DH_RSA_DES_192_CBC3_SHA 	"SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA"

#define SSL3_TXT_DHE_DSS_DES_40_CBC_SHA		"SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA"
#define SSL3_TXT_DHE_DSS_DES_64_CBC_SHA		"SSL_DHE_DSS_WITH_DES_CBC_SHA"
#define SSL3_TXT_DHE_DSS_DES_192_CBC3_SHA	"SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA"
#define SSL3_TXT_DHE_RSA_DES_40_CBC_SHA		"SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA"
#define SSL3_TXT_DHE_RSA_DES_64_CBC_SHA		"SSL_DHE_RSA_WITH_DES_CBC_SHA"
#define SSL3_TXT_DHE_RSA_DES_192_CBC3_SHA	"SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA"

#define SSL3_TXT_ADH_RC4_40_MD5				"SSL_DH_anon_EXPORT_WITH_RC4_40_MD5"
#define SSL3_TXT_ADH_RC4_128_MD5			"SSL_DH_anon_WITH_RC4_128_MD5"
#define SSL3_TXT_ADH_DES_40_CBC_SHA			"SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA"
#define SSL3_TXT_ADH_DES_64_CBC_SHA			"SSL_DH_anon_WITH_DES_CBC_SHA"
#define SSL3_TXT_ADH_DES_192_CBC_SHA		"SSL_DH_anon_WITH_3DES_EDE_CBC_SHA"

#define SSL3_TXT_FZA_DMS_NULL_SHA			"SSL_FORTEZZA_DMS_WITH_NULL_SHA"
#define SSL3_TXT_FZA_DMS_FZA_SHA			"SSL_FORTEZZA_DMS_WITH_FORTEZZA_CBC_SHA"
#define SSL3_TXT_FZA_DMS_RC4_SHA			"SSL_FORTEZZA_DMS_WITH_RC4_128_SHA"

/* extra state */
#define SSL3_ST_CW_FLUSH					(0x100 | SSL_ST_CONNECT) /* SSL3 client handshake state */
/* write to server */
#define SSL3_ST_CW_CLNT_HELLO_A				(0x110 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_CLNT_HELLO_B				(0x111 | SSL_ST_CONNECT) /* SSL3 client handshake state */
/* read from server */
#define SSL3_ST_CR_SRVR_HELLO_A				(0x120 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_SRVR_HELLO_B				(0x121 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_CERT_A					(0x130 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_CERT_B					(0x131 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_KEY_EXCH_A				(0x140 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_KEY_EXCH_B				(0x141 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_CERT_REQ_A				(0x150 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_CERT_REQ_B				(0x151 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_SRVR_DONE_A				(0x160 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_SRVR_DONE_B				(0x161 | SSL_ST_CONNECT) /* SSL3 client handshake state */
/* write to server */
#define SSL3_ST_CW_CERT_A					(0x170 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_CERT_B					(0x171 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_CERT_C					(0x172 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_KEY_EXCH_A				(0x180 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_KEY_EXCH_B				(0x181 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_CERT_VRFY_A				(0x190 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_CERT_VRFY_B				(0x191 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_CHANGE_A					(0x1A0 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_CHANGE_B					(0x1A1 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_FINISHED_A				(0x1B0 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CW_FINISHED_B				(0x1B1 | SSL_ST_CONNECT) /* SSL3 client handshake state */
/* read from server */
#define SSL3_ST_CR_CHANGE_A					(0x1C0 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_CHANGE_B					(0x1C1 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_FINISHED_A				(0x1D0 | SSL_ST_CONNECT) /* SSL3 client handshake state */
#define SSL3_ST_CR_FINISHED_B				(0x1D1 | SSL_ST_CONNECT) /* SSL3 client handshake state */

/* extra state */
#define SSL3_ST_SW_FLUSH					(0x100 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
/* read from client */
#define SSL3_ST_SR_CLNT_HELLO_A				(0x110 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_CLNT_HELLO_B				(0x111 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
/* write to client */
#define SSL3_ST_SW_HELLO_REQ_A				(0x120 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_HELLO_REQ_B				(0x121 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_HELLO_REQ_C				(0x122 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_SRVR_HELLO_A				(0x130 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_SRVR_HELLO_B				(0x131 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_CERT_A					(0x140 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_CERT_B					(0x141 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_KEY_EXCH_A				(0x150 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_KEY_EXCH_B				(0x151 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_CERT_REQ_A				(0x160 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_CERT_REQ_B				(0x161 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_SRVR_DONE_A				(0x170 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_SRVR_DONE_B				(0x171 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
/* read from client */
#define SSL3_ST_SR_CERT_A					(0x180 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_CERT_B					(0x181 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_KEY_EXCH_A				(0x190 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_KEY_EXCH_B				(0x191 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_CERT_VRFY_A				(0x1A0 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_CERT_VRFY_B				(0x1A1 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_CHANGE_A					(0x1B0 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_CHANGE_B					(0x1B1 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_FINISHED_A				(0x1C0 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SR_FINISHED_B				(0x1C1 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
/* write to client */
#define SSL3_ST_SW_CHANGE_A					(0x1D0 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_CHANGE_B					(0x1D1 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_FINISHED_A				(0x1E0 | SSL_ST_ACCEPT) /* SSL3 server handshake state */
#define SSL3_ST_SW_FINISHED_B				(0x1E1 | SSL_ST_ACCEPT) /* SSL3 server handshake state */

/* SSL3 alert levels */
#define SSL3_AL_WARNING						1
#define SSL3_AL_FATAL						2
#define SSL3_AL_ALERT_NONE					255

/* SSL3 alert descriptions */
#define SSL3_AD_CLOSE_NOTIFY				0	/* warning */
#define SSL3_AD_UNEXPECTED_MESSAGE			10	/* fatal */
#define SSL3_AD_BAD_RECORD_MAC				20	/* fatal */
#define SSL3_AD_DECOMPRESSION_FAILURE		30	/* fatal */
#define SSL3_AD_HANDSHAKE_FAILURE			40	/* fatal */
#define SSL3_AD_NO_CERTIFICATE				41	/* warning */
#define SSL3_AD_BAD_CERTIFICATE				42	/* warning */
#define SSL3_AD_UNSUPPORTED_CERTIFICATE		43	/* warning */
#define SSL3_AD_CERTIFICATE_REVOKED			44	/* warning */
#define SSL3_AD_CERTIFICATE_EXPIRED			45	/* warning */
#define SSL3_AD_CERTIFICATE_UNKNOWN			46	/* warning */
#define SSL3_AD_ILLEGAL_PARAMETER			47	/* fatal */
#define SSL3_AD_ALERT_NONE					255 /* no alert */

/* constants for use with the SSL_set_options function */
#define SSL3_OP_NO_RENEGOTIATE_CIPHERS		0x0001L /* ignore renegotiation attempts of the cipher suite */
#define SSL3_OP_DELAY_CLIENT_FINISHED		0x0002L /* send Client Finished message together with the first application data in session resumptions		*/
#define SSL3_OP_POP_BUFFER					0x0004L /* set internally, if SSL3_OP_DELAY_CLIENT_FINISHED is set */

#ifdef  __cplusplus
}
#endif
#endif

