/* This files  version number is v0 */


/*

ecFp_point_pc.c -- Functions for initializing and freeing  memory for points (projective coordinates) on E.
                -- setting and getting point coordinates.

                   Bartol Filipovic,  Deutsche Bank AG - IT Security, 1999
				   Copyright Bartol Filipovic and Deutsche Bank AG

*/

#include "arithmet.h"
#include "s_ecFp.h" /* header file for this sourcecode */
#include "s_ecconv.h"
#include "s_ecmath.h" /* needed in ecFp_point_check_infinity_pc() */
#include <stdlib.h>
#include "ECsecude.h"

/*************************************************************************************************/
/*                                     ecFp_point_init_pc()
/*************************************************************************************************/

/* Makrodefinition in "s_ecFp.h" */


/*************************************************************************************************/
/*                           ecFp_point_init_set_pc_ln()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
ecFp_point_pc_t ecFp_point_init_set_pc_ln(L_NUMBER *x, L_NUMBER *y, L_NUMBER *z, const int inf)
#else
ecFp_point_pc_t ecFp_point_init_set_pc_ln( x, y, z, inf)
                               L_NUMBER *x;
                               L_NUMBER *y;
                               L_NUMBER *z;
                               const int inf;
#endif                               
{
	ecFp_point_pc_t S;

	S = (ecFp_point_pc_t) malloc(sizeof(__PointPc_struct));
	if ( S == NULL ) return NULL; /* memory allocation failed! */;
	trans(x, S->x);
	trans(y, S->y);
	trans(z, S->z);
	S->infinity = inf;

	return S;
}

/*************************************************************************************************/
/*                                  ecFp_point_init_set_pc_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
ecFp_point_pc_t ecFp_point_init_set_pc_str (int *ret, const char *x, const char *y, const char *z, const int inf)
#else
ecFp_point_pc_t ecFp_point_init_set_pc_str (ret, x, y, z, inf)
                                int *ret;
                                const char *x;
                                const char *y;
                                const char *z;
                                const int inf;
#endif                                
{
	int x_err = 0;
	int y_err = 0;
	int z_err = 0;

	ecFp_point_pc_t S;

	S = (ecFp_point_pc_t) malloc(sizeof(__PointPc_struct));
	if ( S == NULL ) return NULL; /* memory allocation failed */
	if ( string_to_ln(x, S->x) )
	{
		/* x is not a correct number in base {8,10,16}*/
		x_err = 1;
	}
	if ( string_to_ln(y, S->y) )
	{
		/* y is not a correct number in base {8,10,16}*/
		y_err = 2;
	}
	if ( string_to_ln(z, S->z) )
	{
		/* z is not a correct number in base {8,10,16} */
		z_err = 4;
	}
	S->infinity = inf;

	*ret = x_err + y_err + z_err; 
	/* If the integer ret is greater 0, then at least one of the three strings is not a correct number in base {8,10,16}.*/
	/* It is possible to see by the value of ret, which of them it is / they are. */ 
	
	 if (*ret >0)
	 {
	 	/* at least one of the strings x, y, z was not a correct number in  base {8,10,16} */
	 		 	
	 	free(S);
	 	
	 	return  NULL; /* error: S could not be initialized cause of wrong strings */
	 } 


	return S;
}

/*************************************************************************************************/
/*                                        ecFp_point_setall_pc_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_point_setall_pc_str (ecFp_point_pc_destptr S,  const char *x, const char *y, const char *z, const int inf)
#else
int ecFp_point_setall_pc_str (S, x, y, z, inf)
          ecFp_point_pc_destptr S;
          const char *x;
          const char *y;
          const char *z;
          const int inf;
#endif
{
	int x_err = 0;
	int y_err = 0;
	int z_err = 0;

	if ( string_to_ln(x, S->x) )
	{
		/* x is not a correct number in base {8,10,16} */
		x_err = 1;
	}
	if ( string_to_ln(y, S->y) )
	{
		/* y is not a correct number in base {8,10,16} */
		y_err = 2;
	}
	if ( string_to_ln(z, S->z) )
	{
		/* z is not a correct number in base {8,10,16} */
		z_err = 4;
	}
	S->infinity = inf;

	/* If the integer ret is greater 0, then at least one of the three strings is not a correct number in base {8,10,16}.*/
	/* It is possible to see by the return-value which of them it is. */ 
	return  x_err + y_err + z_err;
}

/*************************************************************************************************/
/*                                     ecFp_point_set_xcoord_pc_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
int ecFp_point_set_xcoord_pc_str (ecFp_point_pc_destptr S, const char *x)
#else
int ecFp_point_set_xcoord_pc_str (S, x)
              ecFp_point_pc_destptr S;
              const char *x;
#endif
{
	return string_to_ln(x, S->x);
	/* return 0 or -2 if everything worked well (x is a correct number in base {8,10,16}) */
	/* return -1 if x is not a correct number in base {8,10,16} */
}

/*************************************************************************************************/
/*                                       ecFp_point_set_ycoord_pc_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
int ecFp_point_set_ycoord_pc_str (ecFp_point_pc_destptr S, const char *y)
#else
int ecFp_point_set_ycoord_pc_str (S, y)
          ecFp_point_pc_destptr S;
          const char *y;
#endif
{
	return string_to_ln(y, S->y);
	/* return 0 or -2 if everything worked well (y is a correct number in base {8,10,16}) */
	/* return -1 if y is not a correct number in base {8,10,16} */	
}

/*************************************************************************************************/
/*                                ecFp_point_set_zcoord_pc_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
int ecFp_point_set_zcoord_pc_str (ecFp_point_pc_destptr S, const char *z)
#else
int ecFp_point_set_zcoord_pc_str (S, z)
        ecFp_point_pc_destptr S;
        const char *z;
#endif
{
	return string_to_ln(z, S->z);
	/* return 0 or -2 if everything worked well (z is a correct number in base {8,10,16}) */
	/* return -1 if z is not a correct number in base {8,10,16} */	
}

/*************************************************************************************************/
/*                                    ecFp_point_getstr_xcoord_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char *ecFp_point_getstr_xcoord_pc (ecFp_point_pc_srcptr S, const int base)
#else
char *ecFp_point_getstr_xcoord_pc (S, base)
           ecFp_point_pc_srcptr S;
           const int base;
#endif
{
	char *result;
	
	if ( ln_to_string(S->x, &result, base) ) return NULL; /* NULL indicates that base was wrong choosen*/
	
	return result;
	/* result is a string which contains the x coordinate of S as a base {8,10,16} number */
}
           
/*************************************************************************************************/
/*                                 ecFp_point_getstr_ycoord_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char * ecFp_point_getstr_ycoord_pc (ecFp_point_pc_srcptr S, const int base)
#else
char * ecFp_point_getstr_ycoord_pc (S, base)
              ecFp_point_pc_srcptr S;
              const int base;
#endif
{
	char *result;
	
	if ( ln_to_string(S->y, &result, base) ) return NULL; /* NULL indicates that base was wrong choosen*/
	
	return result;
	/* result is a string which contains the y coordinate of S as a base {8,10,16} number */
}

/*************************************************************************************************/
/*                                ecFp_point_getstr_zcoord_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char *ecFp_point_getstr_zcoord_pc (ecFp_point_pc_srcptr S, const int base)
#else
char *ecFp_point_getstr_zcoord_pc (S, base)
            ecFp_point_pc_srcptr S;
            const int base;
#endif
{
	char *result;
	
	if ( ln_to_string(S->z, &result, base) ) return NULL; /* NULL indicates that base was wrong choosen*/
	
	return result;
	/* result is a string which contains the z coordinate of S as a base {8,10,16} number */
}

/*************************************************************************************************/
/*                                        ecFp_point_set_xcoord_pc_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
void ecFp_point_set_xcoord_pc_si  (ecFp_point_pc_destptr S, const signed long int x)
#else
void ecFp_point_set_xcoord_pc_si  (S, x)
            ecFp_point_pc_destptr S;
            const signed long int x;
#endif
{
	sint_to_ln(x, S->x);
}

/*************************************************************************************************/
/*                                          ecFp_point_set_ycoord_pc_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
void ecFp_point_set_ycoord_pc_si (ecFp_point_pc_destptr S, const signed long int y)
#else
void ecFp_point_set_ycoord_pc_si (S, y)
          ecFp_point_pc_destptr S;
          const signed long int y;
#endif
{
	sint_to_ln(y, S->y);
}

/*************************************************************************************************/
/*                                    ecFp_point_set_zcoord_pc_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
void ecFp_point_set_zcoord_pc_si (ecFp_point_pc_destptr S, const signed long int z)
#else
void ecFp_point_set_zcoord_pc_si (S, z)
           ecFp_point_pc_destptr S;
           const signed long int z;
#endif
{
	sint_to_ln(z, S->z);
}

/*************************************************************************************************/
/*                                        ecFp_point_set_xcoord_pc_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
void ecFp_point_set_xcoord_pc_ui (ecFp_point_pc_destptr S, const unsigned long int x)
#else
void ecFp_point_set_xcoord_pc_ui (S, x)
            ecFp_point_pc_destptr S;
            const unsigned long int x;
#endif
{
	inttoln(x, S->x);
}

/*************************************************************************************************/
/*                                        ecFp_point_set_ycoord_pc_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
void ecFp_point_set_ycoord_pc_ui (ecFp_point_pc_destptr S, const unsigned long int y)
#else
void ecFp_point_set_ycoord_pc_ui (S, y)
            ecFp_point_pc_destptr S;
            const unsigned long int y;
#endif
{
	inttoln(y, S->y);
}

/*************************************************************************************************/
/*                                        ecFp_point_set_zcoord_pc_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
void ecFp_point_set_zcoord_pc_ui (ecFp_point_pc_destptr S, const unsigned long int z)
#else
void ecFp_point_set_zcoord_pc_ui (S, z)
           ecFp_point_pc_destptr S;
           const unsigned long int z;
#endif
{
	inttoln(z, S->z);
}

/*************************************************************************************************/
/*                                     ecFp_point_set_infinity_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)	
void ecFp_point_set_infinity_pc (ecFp_point_pc_destptr P)
#else
void ecFp_point_set_infinity_pc (P)
            ecFp_point_pc_destptr P;
#endif
{
	inttoln(0, P->x);
	inttoln(0, P->y);
	inttoln(0, P->z); /* all coordinates are set to 0 (not really nessesary) |:-)  */
	P->infinity = 1; /* P is now marked as point at infinity */
}

/*************************************************************************************************/
/*                                          ecFp_point_check_infinity_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_point_check_infinity_pc(ecFp_point_pc_destptr P, ecFp_curve_srcptr E)
#else
int ecFp_point_check_infinity_pc( P,  E)
          ecFp_point_pc_srcptr P;
          ecFp_curve_srcptr E;
#endif
{
	L_NUMBER lambda[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER zero[1];

	inttoln(0, zero);

	/* check if P represents the point at infinity on E */
	
	if (P->infinity == 1) return 1; /* P is still Point at infinity on E */
	
	if ( _mod_sqrt (lambda, P->x, E->p) )
	{
		/*  P->x is a perfect square modulo E->p */
		SECUDE(mmult)(lambda, lambda, temp, E->p);
		SECUDE(mmult)(lambda, temp, temp, E->p); /* temp = lambda^3 */
		if ( (SECUDE(comp)(lambda, P->y) == 0) && (SECUDE(comp)(zero, P->z) == 0)  )
		{
			/* P = ( lambda^2 , lambda^3 , 0 ) , that meens P is point at infinity */
			
			P->infinity = 1; /* P is Point at infinity on E */
			
			return 1; /* P is Point at infinity on E */
		}
	}
	
	P->infinity = 0; /* P is not Point at infinity on E */
	
	return 0;
}

/*************************************************************************************************/
/*                                             ecFp_point_clear_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_clear_pc(ecFp_point_pc_destptr S)
#else
void ecFp_point_clear_pc( S)
           ecFp_point_pc_destptr S;
#endif
{	
	free(S);
}

/*************************************************************************************************/
/*                                            ecFp_point_copy_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_copy_pc (ecFp_point_pc_destptr S, ecFp_point_pc_srcptr P)
#else
void ecFp_point_copy_pc (S, P)
            ecFp_point_pc_destptr S;
            ecFp_point_pc_srcptr P;
#endif
{
	trans(P->x, S->x);
	trans(P->y, S->y);
	trans(P->z, S->z);
	S->infinity = P->infinity;
	/* Now S and P represent the same points */
}

/********************************************** EOF **********************************************/