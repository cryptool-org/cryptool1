/* This files version is v0.2 */
/* Signature Schemes, this follows IEEE P1363 Draft 8, Section 10.2.1 */

/* May 1999, March 2000 - Bartol Filipovic - Deutsche Bank AG, IT Security*/
/* Copyright Bartol Filipovic and Deutsche Bank AG */

#ifndef _ecssa_ 
	#define _ecssa_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "s_ecFp.h"


/******************************************************************************************************/


int ecssa_sign_gen_op_ac(/*out*/ L_NUMBER *c, L_NUMBER *d,
			/*in */ OctetString *M,
				EcDomParam_ac_ptr Key,
				char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				char *hash_id); /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */

/******************************************************************************************************/


int ecssa_sign_gen_op_pc(/*out*/ L_NUMBER *c, L_NUMBER *d,
			 /*in */ OctetString *M,
			  	 EcDomParam_pc_ptr Key,
				 char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				 char *hash_id); /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */
/******************************************************************************************************/

int ecssa_sign_verif_op_ac( /* in */ L_NUMBER *c,
				     L_NUMBER *d,
				     OctetString *M,
				     EcDomParam_ac_ptr Key,
				     char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				     char *hash_id); /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */

/******************************************************************************************************/

int ecssa_sign_verif_op_pc( /* in */ L_NUMBER *c,
				     L_NUMBER *d,
				     OctetString *M,
				     EcDomParam_pc_ptr Key,
				     char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				     char *hash_id); /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */

/******************************************************************************************************/

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* #ifndef _ecssa_ */

/*********************************************** EOF ***************************************************/
