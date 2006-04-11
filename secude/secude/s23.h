/* ssl23.h */
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


#ifndef HEADER_SSL23_H 
#define HEADER_SSL23_H 

#ifdef  __cplusplus
extern "C" {
#endif

#include <secude/ssl.h>


/*------------------------------ the constants ------------------------------*/


/* write to server */
#define SSL23_ST_CW_CLNT_HELLO_A	(0x210 | SSL_ST_CONNECT) /* SSL23 client handshake state */
#define SSL23_ST_CW_CLNT_HELLO_B	(0x211 | SSL_ST_CONNECT) /* SSL23 client handshake state */
/* read from server */
#define SSL23_ST_CR_SRVR_HELLO_A	(0x220 | SSL_ST_CONNECT) /* SSL23 client handshake state */
#define SSL23_ST_CR_SRVR_HELLO_B	(0x221 | SSL_ST_CONNECT) /* SSL23 client handshake state */

/* read from client */
#define SSL23_ST_SR_CLNT_HELLO_A	(0x210 | SSL_ST_ACCEPT) /* SSL23 server handshake state */
#define SSL23_ST_SR_CLNT_HELLO_B	(0x211 | SSL_ST_ACCEPT) /* SSL23 server handshake state */


#ifdef  __cplusplus
}
#endif
#endif


