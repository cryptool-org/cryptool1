/* This files  version number is v0 */


/*

/* s_ecppta.c -- Functions for initializing and freeing  memory for points (affine coordinates) on E.
              -- setting point coordinates.
              -- compressing and decompressing points on E.
*/

/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */

#include "arithmet.h"
#include "s_ecconv.h"
#include "s_ecFp.h" /* header file for this sourcecode */
#include "s_bithdl.h"
#include "s_ecmath.h"
#include <stdlib.h>
#include "ECsecude.h"

/*************************************************************************************************/
/*
/*    Some functions for initializing and clearing memory for points on elliptic curves over GF(p).
/*
/*************************************************************************************************/ 

/*************************************************************************************************/
/*                               ecFp_point_init_set_ac_ln()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
ecFp_point_ac_t ecFp_point_init_set_ac_ln(L_NUMBER *x, L_NUMBER *y, const int inf)
#else
ecFp_point_ac_t ecFp_point_init_set_ac_ln(x, y, inf)
                              L_NUMBER *x;
                              L_NUMBER *y;
                              const int inf;
 #endif                             
{
	ecFp_point_ac_t S;

	S = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if ( S == NULL ) return NULL; /* memory allocation failed! */;
	trans(x, S->x);
	trans(y, S->y);
	S->infinity = inf;

	return S;
}

/*************************************************************************************************/
/*                                 ecFp_point_init_set_ac_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
ecFp_point_ac_t ecFp_point_init_set_ac_str (int *ret,  char *x,  char *y, const int inf)
#else
ecFp_point_ac_t ecFp_point_init_set_ac_str (ret, x, y, inf)
                               int *ret;
                               char *x;
                               char *y;						
                               const int inf;
#endif
{
	int x_err = 0;
	int y_err = 0;
	
	ecFp_point_ac_t S;

	S = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if ( S == NULL ) return NULL; /* memory allocation failed! */;
	if ( string_to_ln(x, S->x) )
	{
		/* x is not a correct number in the base given by the prefix */
		 x_err = 1;
	}
	if ( string_to_ln(y, S->y) )
	{
		/* y is not a correct number in the base given by the prefix */
		 y_err = 2;
	}
	S->infinity = inf;

	*ret = x_err + y_err; 
	/* If the integer ret is greater 0, then at least one of the two strings is not a correct number in the base given
	   by the prefix.*/
	/* The value of ret indicates, which of them it is.*/
	/* S is initialized,  if ret > 0 it has to be resetted */ 
	if (*ret >0)
	 {	
	 	free(S);
	 	return  NULL; /* error: S could not be initialized because of wrong strings */
	 } 
	 
	return S;
}

/*************************************************************************************************/
/*                                ecFp_point_setall_ac_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_point_setall_ac_str (ecFp_point_ac_destptr S,  char *x, char *y, const int inf)
#else
int ecFp_point_setall_ac_str (S, x, y, inf)
          ecFp_point_ac_destptr S;
          char *x;
          char *y;
          const int inf;
#endif
{
	int x_err = 0;
	int y_err = 0;

	if ( string_to_ln(x, S->x) )
	{
		/* x is not a correct number in the base given by the prefix */
		x_err = 1;
	}
	if ( string_to_ln(y, S->y) )
	{
		/* y is not a correct number in the base given by the prefix */
		y_err = 2;
	}
	S->infinity = inf;

	/* If the integer ret is greater 0, then at least one of the two strings is not a correct number in the base 
	   given by the prefix.*/
	/* The return value indicates, which of them it is. */ 
	return  x_err + y_err;
}
	                              
/*************************************************************************************************/
/*                                         ecFp_point_clear_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_clear_ac(ecFp_point_ac_destptr S)
#else
void ecFp_point_clear_ac(S)
              ecFp_point_ac_destptr S;
#endif              
{		
	free(S);
}

/*************************************************************************************************/
/*                                     ecFp_point_set_xcoord_ac_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_point_set_xcoord_ac_str (ecFp_point_ac_destptr S, char *x)
#else
int ecFp_point_set_xcoord_ac_str (S, x)
        ecFp_point_ac_destptr S;
        char *x;
#endif
{	
	if ( string_to_ln(x, S->x) ) return 0;
	else return (-1); 
	/* If  0, then x is  a correct number in the base given by the prefix and everything worked well. */
	/* If -1 then x is not a valid number in the base given by the prefix and the caller should react.*/
}

/*************************************************************************************************/
/*                                 ecFp_point_set_ycoord_ac_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_point_set_ycoord_ac_str (ecFp_point_ac_destptr S, char *y)
#else
int ecFp_point_set_ycoord_ac_str (S, y)
        ecFp_point_ac_destptr S;
        char *y;
#endif
{
	if ( string_to_ln(y, S->y) ) return 0;
	else return (-1); 
	/* If  0, then y is  a correct number in base base and everything worked well. */
	/* If -1 then y is not a valid number in base base and the caller should react.*/
}



/*************************************************************************************************/
/*                                  ecFp_point_getstr_xcoord_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char *ecFp_point_getstr_xcoord_ac(ecFp_point_ac_srcptr S, const int base)
#else
char *ecFp_point_getstr_xcoord_ac(S, base)
        ecFp_point_ac_srcptr S;
        const int base;
#endif
{
	 char *temp;
	 if ( ln_to_string(S->x,&temp,base) ) temp=NULL;
	 return(temp);
}

/*************************************************************************************************/
/*                                  ecFp_point_getstr_ycoord_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char *ecFp_point_getstr_ycoord_ac(ecFp_point_ac_srcptr S, const int base)
#else
char *ecFp_point_getstr_ycoord_ac(S, base)
        ecFp_point_ac_srcptr S;
        const int base;
#endif
{
	 char *temp;
	 if ( ln_to_string(S->y,&temp,base) ) temp=NULL;
	 return(temp);
}





/*************************************************************************************************/
/*                                  ecFp_point_set_xcoord_ac_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_set_xcoord_ac_si (ecFp_point_ac_destptr S, const signed long int x)
#else
void ecFp_point_set_xcoord_ac_si (S, x)
        ecFp_point_ac_destptr S;
        const signed long int x;
#endif
{
	sint_to_ln(x, S->x);
}

/*************************************************************************************************/
/*                                    ecFp_point_set_ycoord_ac_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_set_ycoord_ac_si (ecFp_point_ac_destptr S, const signed long int y)
#else
void ecFp_point_set_ycoord_ac_si (S, y)
        ecFp_point_ac_destptr S;
        const signed long int y;
#endif
{
	sint_to_ln(y, S->y);
}

/*************************************************************************************************/
/*                               ecFp_point_set_xcoord_ac_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_set_xcoord_ac_ui (ecFp_point_ac_destptr S, const unsigned long int x)
#else
void ecFp_point_set_xcoord_ac_ui (S, x)
        ecFp_point_ac_destptr S;
        const unsigned long int x;
#endif
{
	inttoln(x, S->x);
}

/*************************************************************************************************/
/*                                  ecFp_point_set_ycoord_ac_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_set_ycoord_ac_ui (ecFp_point_ac_destptr S, const unsigned long int y)
#else
void ecFp_point_set_ycoord_ac_ui (S, y)
        ecFp_point_ac_destptr S;
        const unsigned long int y;
#endif
{
	inttoln(y, S->y);
}

/*************************************************************************************************/
/*                                     ecFp_point_set_infinity_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_set_infinity_ac (ecFp_point_ac_destptr S)
#else
void ecFp_point_set_infinity_ac (S)
           ecFp_point_ac_destptr S;
#endif
{
	S->infinity = 1; /* S is now the point at infinity (null element of the Group E) */
	inttoln(0,S->x);
	inttoln(0,S->y);
	/* x and y coordinates are set to 0, but this is not really necessary*/
}
    
/*************************************************************************************************/
/*                                   ecFp_point_check_infinity_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_point_check_infinity_ac (ecFp_point_ac_srcptr S)
#else
int ecFp_point_check_infinity_ac (S)
          ecFp_point_ac_srcptr S;
#endif
{
	return S->infinity;
	/* return 0 if S is not point at infinity */
	/* return 1 otherwise (S is point at infinity) */
}

/*************************************************************************************************/
/*                                      ecFp_point_copy_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_copy_ac (ecFp_point_ac_destptr S, ecFp_point_ac_srcptr P)
#else
void ecFp_point_copy_ac (S, P)
            ecFp_point_ac_destptr S;
            ecFp_point_ac_srcptr P;
#endif
{
	trans(P->x, S->x);
	trans(P->y, S->y);
	S->infinity = P->infinity;
	/* S and P have the same x and y coordinates or they both represend the point at infinity */
}


/*************************************************************************************************/
/*                                    ecFp_point_compress_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_compress_ac (ecFp_point_cmprs_ac_destptr S, ecFp_point_ac_srcptr P)
#else
void ecFp_point_compress_ac (S,  P)
         ecFp_point_cmprs_ac_destptr S;
         ecFp_point_ac_srcptr P;
#endif
{
	trans(P->x, S->x);
	S->y = _get_last_bit(P->y);  
	S->infinity = P->infinity;
}

/*************************************************************************************************/
/*                                       ecFp_point_decompress_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_point_decompress_ac (ecFp_point_ac_destptr S, ecFp_curve_srcptr E, ecFp_point_cmprs_ac_srcptr P)
#else
int ecFp_point_decompress_ac (S, E, P)
      ecFp_point_ac_destptr S;
      ecFp_curve_srcptr E;
      ecFp_point_cmprs_ac_srcptr P;
#endif
{
	L_NUMBER g[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER z[MAXLGTH];

	if ( P->infinity ) 
	{
		S->infinity  = 1;
		return 0; /* ok: P is point at infinity, and so S is point at infinity too. */
		/* x and y coordinates are not important in this case. */
	}

	
	trans(P->x, S->x);
	S->infinity = P->infinity;

	SECUDE(mmult)(P->x, P->x, g, E->p);
	SECUDE(mmult)(P->x, g, g, E->p);/* g = x^3 (mod p) */
	SECUDE(mmult)(E->a, P->x, temp, E->p); /* temp = a*x (mod p)*/

	SECUDE(madd)(g, temp, g, E->p); /* g = x^3 + ax (mod p) */
	SECUDE(madd)(g, E->b, g, E->p); /* g = x^3 + ax + b (mod p) */

	if ( !_mod_sqrt(z, g, E->p) )
	{
		return -1; /* error: can not find z such that z^2 = x^3 + ax + b (mod p) */
	}

	if ( _get_last_bit(z) == P->y )
	{
		trans(z, S->y);
	}
	else SECUDE(sub)(E->p, z, S->y); 

	return 0; /* ok: S is the decompressed point P */
}



/*************************************************************************************************************/
/*	Transforms an elliptic curve point (x,y) into an L_NUMBER_ARRAY			ecFp_X9_compress_point_ac()
/*  following X9.62 4.3.6
/*************************************************************************************************************/
#if defined (__STDC__) || defined (__cplusplus)
void ecFp_X9_compress_point_ac(L_NUMBER *c, ecFp_point_ac_destptr G, L_NUMBER *p)
#else
void ecFp_X9_compress_point_ac(c, G, p)
	ecFp_point_ac_destptr G;
	L_NUMBER *c;
	L_NUMBER *p;
#endif
{	int length,bit,help,len_p;
	unsigned int i;
	L_NUMBER index;

	if (G->infinity!=0){
		inttoln(0,c);
		return;
	}
	bit= _get_last_bit(G->y);
	if (bit==0) index=2;
	else index=3;

	trans(G->x,c);
	for (i=p[0];i>c[0];c[i]=0,i--);
	c[0]=p[0];
	/* put index in c in the position of the next higher free octet of p*/
	len_p=SECUDE(lngtouse)(p)+1;
	length=p[0];
	help=len_p%WLNG;
	if ( help==0 ){
		c[0]=c[0]+1;
		c[length+1]=index;
	}
	else{
		help= 8*(help/8+1);
		if ( help>=WLNG ){
			c[0]=c[0]+1;
			c[length+1]=index;
		}
		else{
		index=index<<(help);
		c[length]=c[length]+index;
		}
	}

}

/******************************************************************************************************************/
/*	Transforms an L_NUMBER_ARRAY into an point (x,y) on the elliptic				ecFp_X9_decompress_point_ac()
/*  curve E following X9.62 4.3.7																					
/******************************************************************************************************************/
/*tested, 31.3.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
int ecFp_X9_decompress_point_ac(ecFp_point_ac_destptr G, ecFp_curve_srcptr E,L_NUMBER *compr)
#else
int ecFp_X9_decompress_point_ac(G, E, compr)
	ecFp_point_ac_destptr G;
	ecFp_curve_srcptr E;
	L_NUMBER *compr;
#endif
{ 
	int length, len_c, bit, h;
	L_NUMBER temp[MAXLGTH], help[MAXLGTH], c[MAXLGTH];
	L_NUMBER index, h1,i;

	trans(compr,c);
	inttoln(0,temp);
	if (SECUDE(comp)(c,temp)==0){
		G->infinity=1;
		return 0; /*decompression successful*/
	}
	
	G->infinity=0;
	/*extract the highest octet*/
	len_c=SECUDE(lngtouse)(c)+1;
	length=len_c/WLNG;
	index=c[length+1];
	h=len_c%WLNG;
	h=8*(h/8);
	index=index>>h;
	h1=index<<h;
	c[length+1]=c[length+1]-h1;
	i=length+1;
	while ( c[i]==0 ){
		c[0]=c[0]-1;
		i=i-1;
	}
	switch (index){
		case 2:  
			bit=0;
			break;
		case 3:
			bit=1;
			break;
		default:
			return (-1);/* decompression failed because c was not a compressed point*/
	}
	trans(c,G->x);
	SECUDE(mmult)(G->x,G->x, temp, E->p);
	SECUDE(mmult)(temp,G->x,temp,E->p); /*temp=x^3 (mod p)*/
	SECUDE(mmult)(E->a,G->x, help, E->p);  /*help=ax (mod p)*/
	SECUDE(madd)(help,E->b, help, E->p); /*help = ax +b (mod p)*/
	SECUDE(madd)(temp,help, temp, E->p); /* temp =x^3+ax+b (mod p)*/
	if (_mod_sqrt(temp,temp, E->p)==0) return (-1); /*decompression failed because c was not a compressed point*/
	
	h= _get_last_bit(temp);
	if (h!=bit) SECUDE(msub)(E->p, temp, temp, E->p);
	trans(temp,G->y);
	return 0;/*decompression successfuly executed*/
}



/********************************************** EOF **********************************************/