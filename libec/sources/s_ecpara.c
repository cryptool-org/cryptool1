/* This files  version number is v0 */


/*

s_ecpara.c  -- Functions for adding, subtracting and multiplying points in affine coordinates  on E


*/

/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */


#include "arithmet.h"
#include "s_ecFp.h" /* header file for this sourcecode */
#include "s_bithdl.h"
#include "s_ecconv.h"
#include "ECsecude.h"


/*************************************************************************************************/
/*                                           ecFp_add_ac ()
/*************************************************************************************************/
/*last change 30.3.99*/
#if defined (__STDC__) || defined (__cplusplus)
int ecFp_add_ac(ecFp_point_ac_destptr R, ecFp_curve_srcptr E, ecFp_point_ac_srcptr P, ecFp_point_ac_srcptr Q)
#else
int ecFp_add_ac (R,  E, P, Q)
        ecFp_point_ac_destptr R;
        ecFp_curve_srcptr E;
        ecFp_point_ac_srcptr P;
        ecFp_point_ac_srcptr Q;
#endif
{
	ecFp_point_ac_t S;

	L_NUMBER lambda[MAXLGTH];
	L_NUMBER temp1[MAXLGTH];
	L_NUMBER temp2[MAXLGTH];
	L_NUMBER one[]={1,1}, zero[]={0};

	inttoln(1,one);
	if (P->infinity) 
	{	
		if (Q->infinity) return 0; /*status ok*/
		trans(Q->x, R->x);
		trans(Q->y, R->y);
		R->infinity = Q->infinity;

		return 0; /* status ok */
	}
	
	if (Q->infinity)
	{
		trans(P->x, R->x);
		trans(P->y, R->y);
		R->infinity = P->infinity;

		return 0; /* status ok */
	}

	S = ecFp_point_init_ac;
	if ( S==NULL ) return -1; /* error: memory allocation failed */

	if (SECUDE(comp)(P->x, Q->x) != 0) /* if (P->x != Q->x) */
	{
		SECUDE(msub)(P->y, Q->y, temp1, E->p); /* temp1 = P->y - Q->y (mod p)*/
		SECUDE(msub)(P->x, Q->x, temp2, E->p); /* temp2 = P->x - Q->x (mod p)*/
		SECUDE(mdiv)(temp1, temp2, lambda, E->p); /* lambda = (P->y - Q->y) / (P->x - Q->x) mod p */
        	
		/* calculate x coordinate of (x,y) = S = P + Q */
		SECUDE(mmult)(lambda, lambda, temp1, E->p);/*temp1=lambda^2 (mod p)*/
		SECUDE(msub)(temp1, P->x, S->x, E->p);
		SECUDE(msub)(S->x, Q->x, S->x, E->p);/* S->x = lambda^2 - P->x - Q->x (mod p) */

		/* calculate y coordinate of (x,y) = S = P + Q */
		SECUDE(msub)(Q->x, S->x, S->y, E->p);
		SECUDE(mmult)(S->y, lambda, S->y, E->p);
		SECUDE(msub)(S->y, Q->y, S->y, E->p);

		/* Return S = (x,y) */

		R->infinity = 0; /*R is not point at infinity*/
		trans(S->x, R->x);
		trans(S->y, R->y);

		ecFp_point_clear_ac(S);

		return 0; /* status ok */
	}

	if (SECUDE(comp)(P->y, Q->y) != 0)
	{
		R->infinity = 1;
		ecFp_point_clear_ac(S);
		return 0; /* status ok */
	}

	if (SECUDE(comp)(Q->y, zero) == 0)
	{
		R->infinity = 1;
		ecFp_point_clear_ac(S);
		return 0; /* status ok */
	}
		
	SECUDE(mmult)(Q->x,Q->x,temp1,E->p);
	inttoln(3,temp2);
	SECUDE(mmult)(temp1,temp2,temp1,E->p);
	SECUDE(madd)(temp1,E->a,temp1,E->p); /*temp1=3(Q->x)^2 + a (mod p)*/
	inttoln(2,temp2);
	SECUDE(mmult)(temp2,Q->y,temp2,E->p);/*temp2= 2(Q->y) (mod p)*/
	SECUDE(mdiv)(temp1,temp2,lambda,E->p);/*lambda= (3(Q->x)^2 + a)/(2(Q->y)) (mod p)*/
	
	/* calculate x coordinate of (x,y) = S = P + Q */
	SECUDE(mmult)(lambda,lambda,temp1,E->p);
	SECUDE(msub)(temp1,P->x,S->x,E->p);
	SECUDE(msub)(S->x,Q->x,S->x,E->p);/* S->x = lambda^2 - P->x - Q->x (mod p) */

	/* calculate y coordinate of (x,y) = S = P + Q */
	SECUDE(msub)(Q->x, S->x, S->y, E->p);
	SECUDE(mmult)(S->y, lambda, S->y, E->p);
	SECUDE(msub)(S->y, Q->y, S->y, E->p);

	/* Return S = (x,y) */
	R->infinity = 0; /*R is not point at infinity*/
	trans(S->x, R->x);
	trans(S->y, R->y);

	ecFp_point_clear_ac(S);
	
	return 0; /* status ok */
}

/*************************************************************************************************/
/*                                         ecFp_sub_ac ()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_sub_ac(ecFp_point_ac_destptr R, ecFp_curve_srcptr E, ecFp_point_ac_srcptr P, ecFp_point_ac_srcptr Q)
#else
int ecFp_sub_ac(R, E,  P, Q)
       ecFp_point_ac_destptr R;
       ecFp_curve_srcptr E;
       ecFp_point_ac_srcptr P;
       ecFp_point_ac_srcptr Q;
#endif
{
	ecFp_point_ac_t S;

	S = ecFp_point_init_ac;

	if (S == NULL) return -1; /* error: memory allocation failed! */

	trans(Q->x, S->x);
	SECUDE(msub)(E->p, Q->y, S->y, E->p);
	S->infinity = Q->infinity;   /* S = -Q */

	if ( ecFp_add_ac(R , E , P , S) )  /* R = P + S = P - Q */
	{
		/* Error: memory allocation failure in ecFp_add_ac() */
		ecFp_point_clear_ac(S);
		return -2; /* Error: memory allocation failure in subroutine ecFp_add_ac() */
	}

	ecFp_point_clear_ac(S);
	return 0; /* status o.k. */
}

/*************************************************************************************************/
/*                                      ecFp_mult_ac ()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_mult_ac(ecFp_point_ac_destptr R, ecFp_curve_srcptr E, L_NUMBER *n, ecFp_point_ac_srcptr P)
#else
int ecFp_mult_ac( R,  E,  n,  P)
        ecFp_point_ac_destptr R;
        ecFp_curve_srcptr E;
        L_NUMBER *n;
        ecFp_point_ac_srcptr P;
#endif
{
	ecFp_point_ac_t Q;
	ecFp_point_ac_t S;

	unsigned long int l;
	unsigned long int m;
	unsigned long int i;

	L_NUMBER k[MAXLGTH];
	L_NUMBER k3[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[]={0};

	if (SECUDE(comp)(n,zero) == 0)
	{
		R->infinity = 1;
		return 0; /* function terminates correctly. R is point at infinity */
	}

	Q = ecFp_point_init_ac;
	S = ecFp_point_init_ac;
	
	if ( (Q==NULL) || (S==NULL) ) return -1; /* error: memory allocation failed */
	

	/* n is a positive number */
		
	trans(P->x, Q->x);
	trans(P->y, Q->y);
	Q->infinity = P->infinity; /* Q = P */
	trans(n, k);  /* k = n */
	

	trans(Q->x, S->x);
	trans(Q->y, S->y);
	S->infinity = Q->infinity; /* S = Q */
	
	inttoln(3,temp);
	SECUDE(mult)(k,temp,k3);

	l = SECUDE(lngtouse)(k3); /* l is the position of the most significant set bit of k3 (in binary represantation) */
	
	m = SECUDE(lngtouse)(k); /* m is the position of the most significant set bit of k (in binary represantation) */

	for ( i = l-1 ; i>m ; i-- )
	{
		if ( ecFp_add_ac(S, E, S, S) ) /* S = S + S */
		{
			/* Not enough memory for subroutine ecFp_add_ac() */
			ecFp_point_clear_ac(Q);
			ecFp_point_clear_ac(S);
				
			return -2; 
			/* Function terminates with error. Not enough memory for subroutine ecFp_add_ac() */
		}				
	}

	for ( i=m ; i > 0 ; i-- )
	{
		if ( ecFp_add_ac(S, E, S, S) ) /* S = S + S */
		{
			/* Not enough memory for subroutine ecFp_add_ac() */
			ecFp_point_clear_ac(Q);
			ecFp_point_clear_ac(S);
				
			return -2; 
			/* Function terminates with error. Not enough memory for subroutine ecFp_add_ac() */
		}				
			
		if ( (_get_ith_bit(k3,i) == 1) && (_get_ith_bit(k,i) == 0) )
		{
			if ( ecFp_add_ac(S, E, S, Q) ) /* S = S + Q */
			{
				/* Not enough memory for subroutine ecFp_add_ac() */
				ecFp_point_clear_ac(Q);
				ecFp_point_clear_ac(S);
				
				return -2; 
				/* Function terminates with error. Not enough memory for subroutine ecFp_add_ac() */
			}				
		}
		if ( (_get_ith_bit(k3,i) == 0) && (_get_ith_bit(k,i) == 1) )
		{
			if ( ecFp_sub_ac(S, E, S, Q) ) /* S = S - Q */
			{
				/* Not enough memory for subroutine ecFp_sub_ac() */
				ecFp_point_clear_ac(Q);
				ecFp_point_clear_ac(S);
				
				return -3; 
				/* Function terminates with error. Not enough memory for subroutine ecFp_sub_ac() */
			}								
		}
	}

	trans(S->x, R->x);
	trans(S->y, R->y);
	R->infinity = S->infinity;

	ecFp_point_clear_ac(Q);
	ecFp_point_clear_ac(S);

	return 0; /*function terminates correctly */
}

/*************************************************************************************************/
/*                                        ecFp_mult_ac_str ()
/*
/*    Note: The only difference between this function and the function ecFp_mult_ac() is 
/*	    that the parameter n is passed as a string instead of an L_NUMBER_ARRAY
/*	    The prefix of the string indicates the base (prefix 0: base 8, 0X: base 16, none: base 10)
/*************************************************************************************************/


#if defined (__STDC__) || defined (__cplusplus)
int ecFp_mult_ac_str(ecFp_point_ac_destptr R, ecFp_curve_srcptr E, const char *n_str, ecFp_point_ac_srcptr P)
#else
int ecFp_mult_ac_str( R,  E,  n_str,  P)
        ecFp_point_ac_destptr R;
        ecFp_curve_srcptr E;
        const char *n_str;
        ecFp_point_ac_srcptr P;
#endif
{
	ecFp_point_ac_t Q;
	ecFp_point_ac_t S;

	unsigned long int l;
	unsigned long int m;
	unsigned long int i;
	int n_str_status;

	L_NUMBER n[MAXLGTH];
	L_NUMBER k[MAXLGTH];
	L_NUMBER k3[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[]={0};
	
	n_str_status = string_to_ln(n_str, n);
	if  ( n_str_status == -1 ) return(-1);/* error: n_str is not a correct number in the base given by the prefix */
	if (SECUDE(comp)(n, zero) == 0)
	{
		R->infinity = 1;
		return 0; /* everything fine (function terminates correctly): R is point at infinity */
	}

	Q = ecFp_point_init_ac;
	S = ecFp_point_init_ac;

	if ( (Q == NULL) || (S == NULL) ) return -1; /* memory allocation for Q or S failed */

	if ( n_str_status == -2) 
	{
		/* n_str contains a negative number (-n)*/			
		trans(P->x, Q->x);
		SECUDE(msub)(E->p,P->y,Q->y,E->p);
		Q->infinity = P->infinity; /* Q = (-P) */
		trans(n,k); /* k = n = -n_str  */
	}
	else
	{
		/* n is not a negative number */	
		trans(P->x, Q->x);
		trans(P->y, Q->y);
		Q->infinity = P->infinity; /* Q = P */
		trans(n,k);  /* k = n */
	}

	trans(Q->x, S->x);
	trans(Q->y, S->y);
	S->infinity = Q->infinity; /* S = Q */

	inttoln(3,temp);
	SECUDE(mult)(k,temp,k3);

	l = SECUDE(lngtouse)(k3); /* l is the position of the most significant set bit of k3 (in binary represantation) */
	
	m = SECUDE(lngtouse)(k); /* m is the position of the most significant set bit of k (in binary represantation) */

	for ( i = l-1 ; i>m ; i-- )
	{
		if ( ecFp_add_ac(S, E, S, S) ) /* S = S + S */
		{
			/* Not enough memory for subroutine ecFp_add_ac() */
			ecFp_point_clear_ac(Q);
			ecFp_point_clear_ac(S);
				
			return -2; 
			/* Function terminates with error. Not enough memory for subroutine ecFp_add_ac() */
		}				
	}

	for ( i=m ; i > 0 ; i-- )
	{
		if ( ecFp_add_ac(S, E, S, S) ) /* S = S + S */
		{
			/* Not enough memory for subroutine ecFp_add_ac() */
			ecFp_point_clear_ac(Q);
			ecFp_point_clear_ac(S);
				
			return -2; 
			/* Function terminates with error. Not enough memory for subroutine ecFp_add_ac() */
		}				
			
		if ( (_get_ith_bit(k3,i) == 1) && (_get_ith_bit(k,i) == 0) )
		{
			if ( ecFp_add_ac(S, E, S, Q) ) /* S = S + Q */
			{
				/* Not enough memory for subroutine ecFp_add_ac() */
				ecFp_point_clear_ac(Q);
				ecFp_point_clear_ac(S);
				
				return -2; 
				/* Function terminates with error. Not enough memory for subroutine ecFp_add_ac() */
			}				
		}
		if ( (_get_ith_bit(k3,i) == 0) && (_get_ith_bit(k,i) == 1) )
		{
			if ( ecFp_sub_ac(S, E, S, Q) ) /* S = S - Q */
			{
				/* Not enough memory for subroutine ecFp_sub_ac() */
				ecFp_point_clear_ac(Q);
				ecFp_point_clear_ac(S);
				
				return -3; 
				/* Function terminates with error. Not enough memory for subroutine ecFp_sub_ac() */
			}						
		}
	}
	
	trans(S->x, R->x);
	trans(S->y, R->y);
	R->infinity = S->infinity;

	ecFp_point_clear_ac(Q);
	ecFp_point_clear_ac(S);

	return 0; /*function terminates correctly */
}

/********************************************** EOF **********************************************/