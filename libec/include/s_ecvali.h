/* This files  version number is v0 */

/* s_ecvali.h		--	Declarations of functions for validating EC domain parameters 
						( so far only for prime fields)*/


/*Anna-Barbara Berger, Secude GmbH*/


/*************************************************************************************************/
/*
/*    Some functions for validating EC domain parameters
/*
/*************************************************************************************************/ 

#ifndef _ecvali_ 
	#define _ecvali_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************/
/*						ecFp_is_point_on_curve_ac()
/***********************************************************************************************/

int  ecFp_is_point_on_curve_ac _PROTO(( ecFp_point_ac_srcptr G, ecFp_curve_srcptr curve));


/*************************************************************************************************/
/*						 ecFp_curve_param_check()
/*************************************************************************************************/
/* checks that 4a^3+27b^2 (mod p) !=0 , returns 0 if this is true, -1 otherwise*/
int ecFp_curve_param_check _PROTO((ecFp_curve_srcptr E)); 
/*************************************************************************************************/
/*                                                                          ecFp_mov_cond()
/*************************************************************************************************/

/* checks if an elliptic Curve over GF(q) with a base point of order r is vulnerable */
/* to the reduction attack of Menezes, Okamoto, Vanstone. */
int ecFp_mov_cond _PROTO((const unsigned int B, L_NUMBER *r, L_NUMBER *q));

/**************************************************************************************************
/*						ecFp_domainpar_valid()
/**************************************************************************************************/
/* Elliptic curve domain parameter validation over Fp following 5.1.1.2 of the X9.62-standard*/
/* return value 0: ECParameters are valid*/
int  ecFp_domainpar_valid _PROTO(( ecFp_curve_srcptr curve, ecFp_point_ac_srcptr G, L_NUMBER *order));


/**************************************************************************************************
/*						ecFp_pubkey_valid()
/**************************************************************************************************/
/* Public key validation over Fp following 5.2.2 of the X9.62-standard*/
/* return value 0: Public key is valid*/
int  ecFp_pubkey_valid _PROTO(( ecFp_point_ac_srcptr Pkey, ecFp_curve_srcptr curve, ecFp_point_ac_srcptr G, L_NUMBER *order));

/************************************************************************************************/

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* #ifndef _ecvali_ */

/********************************************** EOF **********************************************/