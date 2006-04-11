/* saux.h */
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


#ifndef SSL_AUX_H 
#define SSL_AUX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <secude/af.h>


AF_options* SEC_API_CALLING_CONV aux_get_configured_options (char* reg_key);


#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* SSL_AUX_H */

