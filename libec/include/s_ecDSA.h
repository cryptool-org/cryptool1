/* This files version is v0*/

/* s_ecDSA.h	--	Declarations for the Elliptc Curve Signature and Verification Primitives, DSA version
				IEEE1363 7.2.7 and 7.2.8

				1999 Anna-Barbara Berger, Secude GmbH


*/
#ifndef s_ecFp_h
#define s_ecFp_h
#endif
#include "arithmet.h"




/*************************************************************************************************/
/*                           Compiler specific function-prototype declaration
/*************************************************************************************************/

#ifndef  _PROTO
#if defined (__STDC__) || defined (__cplusplus)
#define  _PROTO(x) x  /* ANSI C Prototypes */
#else
#define  _PROTO(x) () /* Pre ANSI  C Prototypes */
#endif
#endif


/*****************************************************************************************************
/* functions for generating a key pair ecFp_generate_key_ac()
/* for prime fields
/*****************************************************************************************************/

/*affine coordinates*/
void ecFp_generate_key_ac _PROTO((L_NUMBER *private_key, ecFp_point_ac_destptr public_key, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r)); 

/*projective coordinates*/
void ecFp_generate_key_pc _PROTO((L_NUMBER *private_key, ecFp_point_pc_destptr public_key, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G, L_NUMBER *r)); 




/*****************************************************************************************************
/* functions for signing a message, ECSP-DSA,IEEE 7.2.7	for prime fields	
/*****************************************************************************************************/

/*affine coordinates*/
int ecFp_ecsp_dsa_ac _PROTO((L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r, L_NUMBER *f));

/*projective coordinates*/
int ecFp_ecsp_dsa_pc _PROTO((L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G, L_NUMBER *r, L_NUMBER *f));

/****************************************************************************************************
/* functions for verifying a signature, returns 0 if the verification is succesful,	
/* 1 if the signature does not verify, and -1 if there is an point allocation error   
/* ECVP-DSA, IEEE 7.2.8 for prime fields
/***************************************************************************************************/

/*affine coordinates*/
int ecFp_ecvp_dsa_ac _PROTO((L_NUMBER *c, L_NUMBER * d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r,L_NUMBER *f));

/*projective coordinates*/
int ecFp_ecvp_dsa_pc _PROTO((L_NUMBER *c, L_NUMBER * d, ecFp_point_pc_srcptr W, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G,L_NUMBER *r,L_NUMBER *f));

/*************************************************EOF***************************************************/