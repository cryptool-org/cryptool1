/*This files version is v0*/

/* s_ecNR.h	-- Declarations for the Elliptc Curve Signature and Verification Primitives, NR version
				IEEE1363 7.2.5 and 7.2.6

				1999 Anna-Barbara Berger, Secude GmbH


*/

#ifndef s_ecFp_h
#define s_ecFp_h
#endif
#include "arithmet.h"
#include "s_ecDSA.h"  /* for key generation */

/*************************************************************************************************/
/*                                  Compiler specific function-prototype declaration
/*************************************************************************************************/

#ifndef  _PROTO
#if defined (__STDC__) || defined (__cplusplus)
#define  _PROTO(x) x  /* ANSI C Prototypes */
#else
#define  _PROTO(x) () /* Pre ANSI  C Prototypes */
#endif
#endif

/*****************************************************************************************************
/* functions for signing a message, ECSP-NR,IEEE 7.2.5, for prime fields			ecFp_ecsp_nr()
/*****************************************************************************************************/

/* affine coordinates */
int ecFp_ecsp_nr_ac _PROTO((L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r,L_NUMBER *f));

/* projective coordinates */
int ecFp_ecsp_nr_pc _PROTO((L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G, L_NUMBER *r, L_NUMBER *f));


/****************************************************************************************************
/* functions for extracting the hash value out of an NR-signature
/***************************************************************************************************/

/* affine coordinates */
int ecFp_ecvp_nr_ac _PROTO((L_NUMBER *c, L_NUMBER *d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r,L_NUMBER *f));

/* projective coordinates */
int ecFp_ecvp_nr_pc _PROTO((L_NUMBER *c, L_NUMBER *d, ecFp_point_pc_srcptr W, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G,L_NUMBER *r, L_NUMBER *f));

/**************************************************** EOF ********************************************/