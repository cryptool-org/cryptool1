/* This files  version number is v0 */


/*

ecFp_arithmetic_pc.c  -- Functions for adding, subtracting and multiplying points in projective coordinates  on E

                         Bartol Filipovic, Deutsche Bank AG - IT Security, 1999
                         Copyright Bartol Filipovic and Deutsche Bank AG
*/

#include "s_ecFp.h" /* header file for this sourcecode */
#include "s_ecmath.h"
#include "s_bithdl.h"
#include "s_ecconv.h" /* needed in ecFp_mult_pc_str() */
#include "arithmet.h"
#include "ECsecude.h"

/*************************************************************************************************/
/*                                  _ellip_double_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void _ellip_double_pc(ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P)
#else
void _ellip_double_pc(R,  E,  P)
         ecFp_point_pc_destptr R;
         ecFp_curve_srcptr E;
         ecFp_point_pc_srcptr P;
#endif
{	
	L_NUMBER T1[MAXLGTH];
	L_NUMBER T2[MAXLGTH];
	L_NUMBER T3[MAXLGTH];
	L_NUMBER T4[MAXLGTH];
	L_NUMBER T5[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[1];
	L_NUMBER three[2];
	
	inttoln(0, zero);
	inttoln(3, three);

	trans(P->x, T1);
	trans(P->y, T2);
	trans(P->z, T3);
	
	if ( (SECUDE(comp)(T2,zero) == 0) || (SECUDE(comp)(T3,zero) == 0) )
	{
		inttoln(1,R->x);
		inttoln(1,R->y);
		inttoln(0,R->z);
		R->infinity = 1;
		
		return; /* no error: 2P = Point at infinity */
	}

	SECUDE(msub)(E->p, three, temp, E->p); /* temp = p-3 */

	if ( SECUDE(comp)(E->a,temp) == 0 )
	{
		SECUDE(mmult)(T3, T3, T4, E->p);  /* T4 = T3^2 (mod p) */
		SECUDE(msub)(T1, T4, T5, E->p);  /* T5 = T1 - T4 */
		SECUDE(madd)(T1, T4, T4, E->p); /* T4 = T1 + T4 */
		SECUDE(mmult)(T4, T5, T5, E->p); /* T5 = T4 * T5 */
		SECUDE(mmult)(three, T5, T4, E->p);  /* T4 = 3 * T5  */
	}
	else
	{
		trans(E->a, T4);  /* T4 = a */
		SECUDE(mmult)(T3, T3, T5, E->p); /* T5 = T3^2 (mod p) */
		SECUDE(mmult)(T5, T5, T5, E->p); /* T5 = T5^2 (mod p) */
		SECUDE(mmult)(T4, T5, T5, E->p);   /* T5 = T4 * T5 */
		SECUDE(mmult)(T1, T1, T4, E->p); /* T4 = T1^2 (mod p) */
		SECUDE(mmult)(three, T4, T4, E->p);  /* T4 = 3 * T4 */
		SECUDE(madd)(T4, T5, T4, E->p); /* T4 = T4 + T5 */
	}

	SECUDE(mmult)(T2, T3, T3, E->p);  /* T3 = T2 * T3 */
	SECUDE(madd)(T3, T3, T3, E->p); /* T3 = 2 * T3 */
	SECUDE(mmult)(T2, T2, T2, E->p); /* T2 = T2^2 (mod p) */
	SECUDE(mmult)(T1, T2, T5, E->p);  /* T5 = T1 * T2 */
	SECUDE(madd)(T5, T5, T5, E->p); 
	SECUDE(madd)(T5, T5, T5, E->p); /* T5 = 4 * T5 */
	SECUDE(mmult)(T4, T4, T1, E->p); /* T1 = T4^2 (mod p) */
	SECUDE(madd)(T5, T5, temp, E->p); /* temp = 2 * T5 */
	SECUDE(msub)(T1, temp, T1, E->p); /* T1 = T1 - (2 * T5) */
	SECUDE(mmult)(T2, T2, T2, E->p);  /* T2 = T2^2 (mpd p) */
	SECUDE(madd)(T2, T2, T2, E->p);
	SECUDE(madd)(T2, T2, T2, E->p);
	SECUDE(madd)(T2, T2, T2, E->p);   /* T2 = 8 * T2 */
	SECUDE(msub)(T5, T1, T5, E->p); /* T5 = T5 - T1 */
	SECUDE(mmult)(T5, T4, T5, E->p);  /* T5 = T5 * T4 */
	SECUDE(msub)(T5, T2, T2, E->p); /* T2 = T5 - T2 */
	
	trans(T1, R->x);
	trans(T2, R->y);
	trans(T3, R->z);
	R->infinity = 0;
	
	return; /* no errors */
}

/*************************************************************************************************/
/*                                          _ellip_add_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int _ellip_add_pc(ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P, ecFp_point_pc_srcptr Q)
#else
int _ellip_add_pc( R,  E,  P, Q)
         ecFp_point_pc_destptr R;
         ecFp_curve_srcptr E;
         ecFp_point_pc_srcptr P;
         ecFp_point_pc_srcptr Q;
#endif
{
	L_NUMBER T1[MAXLGTH];
	L_NUMBER T2[MAXLGTH];
	L_NUMBER T3[MAXLGTH];
	L_NUMBER T4[MAXLGTH];
	L_NUMBER T5[MAXLGTH];
	L_NUMBER T6[MAXLGTH];
	L_NUMBER T7[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[1];
	L_NUMBER one[2];
	
	inttoln(0, zero);
	inttoln(1, one);
	
	trans(P->x, T1);
	trans(P->y, T2);
	trans(P->z, T3);
	trans(Q->x, T4);
	trans(Q->y, T5);

	if ( SECUDE(comp)(Q->z, one) != 0 )
	{
		/* z coordinate of Q is not 1 */
		
		trans(Q->z, T6);
		SECUDE(mmult)(T6, T6, T7, E->p);
		SECUDE(mmult)(T1, T7, T1, E->p);
		SECUDE(mmult)(T6, T7, T7, E->p);
		SECUDE(mmult)(T2, T7, T2, E->p);
	}

	SECUDE(mmult)(T3, T3, T7, E->p);
	SECUDE(mmult)(T4, T7, T4, E->p);
	SECUDE(mmult)(T3, T7, T7, E->p);
	SECUDE(mmult)(T5, T7, T5, E->p);
	SECUDE(msub)(T1, T4, T4, E->p);
	SECUDE(msub)(T2, T5, T5, E->p);

	if ( SECUDE(comp)(T4,zero) == 0 )
	{
		if ( SECUDE(comp)(T5,zero) == 0 )
		{
			return 1; 
			/* P = Q : this return value indicates that ecFp_double_pc() should be used */
		}
		
		inttoln(1,R->x);
		inttoln(1,R->y);
		inttoln(0,R->z);
		R->infinity = 1;
		
		return 0; /* No errors. This only indicates that P + Q is the point at infinity */
	}

	SECUDE(madd)(T1, T1, T1, E->p);
	SECUDE(msub)(T1, T4, T1, E->p);
    
	SECUDE(madd)(T2, T2, T2 , E->p);
	SECUDE(msub)(T2, T5, T2 , E->p);

	if ( SECUDE(comp)(Q->z, one) != 0)
	{
		SECUDE(mmult)(T3, T6, T3, E->p);
	}

	SECUDE(mmult)(T3, T4, T3, E->p);
	SECUDE(mmult)(T4, T4, T7, E->p);
	SECUDE(mmult)(T4, T7, T4, E->p);
	SECUDE(mmult)(T1, T7, T7, E->p);
	SECUDE(mmult)(T5, T5, T1, E->p);
	SECUDE(msub)(T1, T7, T1, E->p);
	SECUDE(madd)(T1, T1, temp, E->p);
	SECUDE(msub)(T7, temp, T7, E->p);
	SECUDE(mmult)(T5, T7, T5, E->p);
	SECUDE(mmult)(T2, T4, T4, E->p);
	SECUDE(msub)(T5, T4, T2, E->p);

	_mod_div2(T2, T2, E->p); /* Set T2 = T2/2 (mod p) */

	trans(T1, R->x);
	trans(T2, R->y);
	trans(T3, R->z);
	R->infinity = 0;

	return 0; /* no errors occured */
}

/*************************************************************************************************/
/*                                           ecFp_add_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_add_pc(ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P, ecFp_point_pc_srcptr Q)
#else
void ecFp_add_pc(R,  E,  P,  Q)
       ecFp_point_pc_destptr R;
       ecFp_curve_srcptr E;
       ecFp_point_pc_srcptr P;
       ecFp_point_pc_srcptr Q;
#endif
{
	L_NUMBER zero[1];
	
	inttoln(0, zero);
		
	if ( SECUDE(comp)(P->z, zero) == 0 )
	{
		trans(Q->x, R->x);
		trans(Q->y, R->y);
		trans(Q->z, R->z);
		R->infinity = Q->infinity;

		return; /* no error */
	}

	if ( SECUDE(comp)(Q->z, zero) == 0 )
	{
		trans(P->x, R->x);
		trans(P->y, R->y);
		trans(P->z, R->z);
		R->infinity = P->infinity;

		return; /* no error */
	}
		
	if ( _ellip_add_pc(R, E, P, Q)  )
	{
		/* P = Q */
		/* The return value of _ellip_add_pc() indicates that the function _ellip_double_pc() should be used.*/
		
		_ellip_double_pc(R, E, P);
		
		/* R = 2P */
	}
	
	return; /* No error */
}

/*************************************************************************************************/
/*                                      ecFp_sub_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_sub_pc(ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P, ecFp_point_pc_srcptr Q)
#else
int ecFp_sub_pc( R,  E,  P, Q)
       ecFp_point_pc_destptr R;
       ecFp_curve_srcptr E;
       ecFp_point_pc_srcptr P;
       ecFp_point_pc_srcptr Q;
#endif
{
	ecFp_point_pc_t S;

	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[1];
	
	inttoln(0, zero);
	
	S=ecFp_point_init_pc;
	
	if ( S == NULL ) return -1; /* error: memory allocation failed */
	
	trans(Q->x, S->x);
	trans(Q->z, S->z);
	S->infinity = Q->infinity;

	SECUDE(msub)(zero, Q->y, temp, E->p); /* Q->y = -Q->y */

	trans(temp, S->y); /* S = -Q */
	
	ecFp_add_pc(R, E, P, S); /* R = P + S = P - Q */

	ecFp_point_clear_pc(S);

	return 0;
}

/*************************************************************************************************/
/*                                        ecFp_mult_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_mult_pc(ecFp_point_pc_destptr R, ecFp_curve_srcptr E, L_NUMBER *n, ecFp_point_pc_srcptr P)
#else
int ecFp_mult_pc( R,  E,  n,  P)
       ecFp_point_pc_destptr R;
       ecFp_curve_srcptr E;
       L_NUMBER *n;
       ecFp_point_pc_srcptr P;
#endif
{
	ecFp_point_pc_t S;

	L_NUMBER k[MAXLGTH];
	L_NUMBER k3[MAXLGTH];
	L_NUMBER zero[1]={0};
	L_NUMBER one[2]={1,1};
	
	unsigned long int l;
	unsigned long int m;
	unsigned long int i;



	if ( (SECUDE(comp)(n, zero) == 0) || (SECUDE(comp)(P->z, zero) == 0) )
	{
		inttoln(1, R->x);
		inttoln(1, R->y);
		inttoln(0, R->z);
		R->infinity=1;	
		return 0; /* exit without error */
	}
	R->infinity=P->infinity;
	trans(P->x, R->x);
	trans(P->z, R->z);

	S=ecFp_point_init_pc;
	
	if ( S == NULL ) return -1; /*error: memory allocation failed */ 

	inttoln(1, S->z);
	S->infinity = 0;

	trans(n, k); /* k = n */
	trans(P->y, R->y); /* R->y = P->y */

	if ( SECUDE(comp)(R->z, one) == 0 )
	{
		trans(R->x, S->x);
		trans(R->y, S->y);
	}
	else
	{
		SECUDE(mmult)(R->z, R->z, S->x, E->p); /* S->x = (R->z)^2 (mod p) */
		SECUDE(mdiv)(one, S->x, S->x, E->p); 
		SECUDE(mmult)(R->x, S->x, S->x, E->p);

		SECUDE(mmult)(R->z, R->z, S->y, E->p);
		SECUDE(mmult)(S->y, R->z, S->y, E->p); /* S->y = (R->z)^3 (mod p) */
		SECUDE(mdiv)(one, S->y, S->y, E->p);
		SECUDE(mmult)(R->y, S->y, S->y, E->p);
	}

	SECUDE(add)(k, k, k3);
	SECUDE(add)(k3, k, k3); /* k3 = 3*k */

	l = SECUDE(lngtouse)(k3); /* l is the position of the most significant set bit of k3 (in binary represantation) */
	m = SECUDE(lngtouse)(k); /* m is the position of the most significant set bit of k (in binary represantation) */

	for ( i=l-1 ; i>m ; i-- )
	{
		_ellip_double_pc(R, E, R); /* No return value */
	}
	for ( i=m ; i>0 ; i-- )
	{
		_ellip_double_pc(R, E, R); /* No return value */

		if ( (_get_ith_bit(k3, i) == 1) && (_get_ith_bit(k, i) == 0) )
		{
			ecFp_add_pc(R, E, R, S); /* No return value */
		}
		if ( (_get_ith_bit(k3, i) == 0) && (_get_ith_bit(k, i) == 1) )
		{
			if ( ecFp_sub_pc(R, E, R, S) )
			{
				/* not enough memory for function ecFp_sub_pc() */
								
				ecFp_point_clear_pc(S);
				
				return -2; /* error: subroutine failure */
			}
		}
	}
    
	ecFp_point_clear_pc(S);

	return 0; /* exit, no errors occured */
}

/*************************************************************************************************/
/*                                         ecFp_mult_pc_str()
 *
 *  Note: This function is (nearly) the same as ecFp_mult_pc(). The only difference is that 
 *                the parameter n is passed as an string instead of a L_NUMBER.
 */
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_mult_pc_str(ecFp_point_pc_destptr R, ecFp_curve_srcptr E, const char *n_str, ecFp_point_pc_srcptr P)
#else
int ecFp_mult_pc_str( R,  E,  n_str,  P, base)
       ecFp_point_pc_destptr R;
       ecFp_curve_srcptr E;
       const char *n_str;
       ecFp_point_pc_srcptr P;
#endif
{
	L_NUMBER n[MAXLGTH];

	if ( string_to_ln(n_str, n) ) return -1; /* error n_str is not a correct number in base {8,10,16} */

	return ecFp_mult_pc(R, E, n, P);
}

/********************************************** EOF **********************************************/