/* This files  version number is v0 */


/*

ecFp_randpoint.c -- Functions for choosing randomly points (both coordinate - affine and projective -  representation) on E.
                 -- Choosing randomly points (both coordinate - affine and projective -  representation) with large prime order on E.
                 -- NOTE: the routines in this file use the PRNG of prng.c, so you should check if the used PRNG are secure enough.

                 Bartol Filipovic, Deutsche Bank AG - IT Security, 1999
				 Copyright Bartol Filipovic and Deutsche Bank AG

*/

#include "arithmet.h"
#include "s_ecFp.h" /* header file for this sourcecode */
#include "s_ecmath.h"
#include "s_prng.h"
#include "ECsecude.h"

/*************************************************************************************************/
/*                                  ecFp_rp_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_rp_ac(ecFp_point_ac_destptr S, ecFp_curve_srcptr E)
#else
void ecFp_rp_ac(S,  E)
           ecFp_point_ac_destptr S;
           ecFp_curve_srcptr E;
#endif 
{
	L_NUMBER alpha[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[1]={0};


again:

	_rand_int(S->x, E->p); /* choose random x coordinate of S on E */

	SECUDE(mmult)(S->x, S->x, alpha, E->p);
	SECUDE(mmult)(alpha, S->x, alpha, E->p); /* alpha = (S->x)^3 (mod E->p) */
	SECUDE(mmult)(E->a, S->x, temp, E->p);
	SECUDE(madd)(temp, E->b, temp, E->p);
	SECUDE(madd)(alpha, temp, alpha, E->p);

	if ( SECUDE(comp)(alpha, zero) == 0 )
	{
		inttoln(0, S->y);

		return;
	}

	if ( !_mod_sqrt(S->y, alpha, E->p) ) goto again; 
	/* if S->y = sqrt(alpha) (mod p) not exist choose another random x-coordinate of S */

	/* Generate a random bit m and calculate S = (-1)^m * S */

	if ( _rand_bit() == 1 ) SECUDE(msub)(zero, S->y, S->y, E->p); /* S->y = -S->y */
	S->infinity=0;
	return;
}

/*************************************************************************************************/
/*                                       ecFp_rp_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_rp_pc(ecFp_point_pc_destptr S, ecFp_curve_srcptr E)
#else
void ecFp_rp_pc(S, E)
           ecFp_point_pc_destptr S;
           ecFp_curve_srcptr E;
#endif
{		
/*
	ecFp_point_ac_t Q;
	ecFp_point_init_ac(Q);	
	if ( Q == NULL ) return -1; // error: memory allocation failed 
	ecFp_rp_ac(Q, E); // choose random Q in affine coordinates on elliptic curve E
	ecFp_point_ac_to_pc(S, Q); // transform Q in projective coordinates 
	ecFp_point_clear_ac(Q);	
	return 0; // exit without error 
*/
	/* The following is a "direct" version of the method above, but it is a little bit faster */

	L_NUMBER alpha[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[1];

	inttoln(0, zero);
	
	inttoln(1, S->z); /* the z coordinate is 1 */

again:

	_rand_int(S->x, E->p); /* choose random x coordinate of S on E */

	SECUDE(mmult)(S->x, S->x, alpha, E->p);
	SECUDE(mmult)(alpha, S->x, alpha, E->p); /* alpha = (S->x)^3 (mod E->p) */
	SECUDE(mmult)(E->a, S->x, temp, E->p);
	SECUDE(madd)(temp, E->b, temp, E->p);
	SECUDE(madd)(alpha, temp, alpha, E->p);

	if ( SECUDE(comp)(alpha, zero) == 0 )
	{
		inttoln(0, S->y);

		return;
	}

	if ( !_mod_sqrt(S->y, alpha, E->p) ) goto again; 
	/* if S->y = sqrt(alpha) (mod p) not exist choose another random x-coordinate of S */

	/* Generate a random bit m and calculate S = (-1)^m * S */

	if ( _rand_bit() == 1 ) SECUDE(msub)(zero, S->y, S->y, E->p); /* S->y = -S->y */
	S->infinity=0;
	
	return;
}

/*************************************************************************************************/
/*                                      ecFp_rp_lpo_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_rp_lpo_ac(ecFp_point_ac_destptr G, ecFp_curve_srcptr E, L_NUMBER *p, L_NUMBER *k)
#else
int ecFp_rp_lpo_ac(G,  E,  p,  k)
         ecFp_point_ac_destptr G;
         ecFp_curve_srcptr E;
         L_NUMBER *p;
		 L_NUMBER *k;
#endif
{
	ecFp_point_ac_t P;
	ecFp_point_ac_t Q;

	P=ecFp_point_init_ac;
	Q=ecFp_point_init_ac;
	
	if ( (P==NULL) || (Q==NULL) ) 
	{
		/* at least one of the two points P and Q could not be initialized */
		
		if (P) ecFp_point_clear_ac(P);
		if (Q) ecFp_point_clear_ac(Q);
		
		return -1; /* error: memory allocation failed */
	}
	
	do
	{
		ecFp_rp_ac(P, E); /* Generate random point P on E */
		if ( ecFp_mult_ac(G, E, k, P) ) /* G = k*P */
		{
			ecFp_point_clear_ac(P);
			ecFp_point_clear_ac(Q);
			
			return -2; /* error in the subroutine ecFp_mult_ac() */
		}			
	}
	while ( G->infinity );
	
	if ( ecFp_mult_ac(Q, E, p, G) ) /* Q = p*G */
	{
		ecFp_point_clear_ac(P);
		ecFp_point_clear_ac(Q);
		
		return -2; /* error in the subroutine ecFp_mult_ac() */
	}
		
	if ( !Q->infinity )
	{
		ecFp_point_clear_ac(P);
		ecFp_point_clear_ac(Q);

		return -3; /* wrong order of E (choose new elliptic curve  E) */
	}

	ecFp_point_clear_ac(P);
	ecFp_point_clear_ac(Q);

	return 0; /*no errors. G is a point on E of order p, #E = kp */
}

/*************************************************************************************************/
/*                                        ecFp_rp_lpo_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_rp_lpo_pc(ecFp_point_pc_destptr G, ecFp_curve_srcptr E,  L_NUMBER *p, L_NUMBER *k)
#else
int ecFp_rp_lpo_pc(G, E, p, k)
          ecFp_point_pc_destptr G;
          ecFp_curve_srcptr E;
          L_NUMBER *p;
          L_NUMBER *k;
#endif
{
	ecFp_point_pc_t P;
	ecFp_point_pc_t Q;

	P=ecFp_point_init_pc;
	Q=ecFp_point_init_pc;
	
	if ( (P == NULL) || (Q == NULL) )
	{
		/* at least one of the two points P and Q could not be initialized */
		
		if (P) ecFp_point_clear_pc(P);
		if (Q) ecFp_point_clear_pc(Q);
		
		return -1; /* error: memory allocation failed */
	}

	do
	{
		ecFp_rp_pc(P, E); /* choose random point P on E */
		
		if ( ecFp_mult_pc(G, E, k, P) ) /* G = k*P */
		{
			ecFp_point_clear_pc(P);
			ecFp_point_clear_pc(Q);
			
			return -2; /* error in the subroutine ecFp_mult_pc() */
		}						
	}
	while ( G->infinity );
	
	if ( ecFp_mult_pc(Q, E, p, G) )  /* Q = p*G */
	{
		ecFp_point_clear_pc(P);
		ecFp_point_clear_pc(Q);
			
		return -2; /* error in the subroutine ecFp_mult_pc() */
	}						

	if ( !Q->infinity )
	{
		ecFp_point_clear_pc(P);
		ecFp_point_clear_pc(Q);

		return -3; /* wrong order of E */
	}

	ecFp_point_clear_pc(P);
	ecFp_point_clear_pc(Q);

	return 0; /*no error:  G is a point on E of order p, #E = kp */
}

/********************************************** EOF **********************************************/