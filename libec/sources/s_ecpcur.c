/* This files  version number is v0 */



/* s_ecpcur.c  -- Functions for initalizing memory for elliptic curve E.
               -- Functions for setting and getting curve parameters a, b and p.
*/


/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */


#include <stdlib.h>
#include "s_ecFp.h" /* header file for this sourcecode */
#include "arithmet.h"
#include "s_ecconv.h"
#include <string.h>

/*************************************************************************************************/
/*
 *   Functions for intializing and clearing memory for an elliptic curve over GF(p) and setting curve parameters a, b and p.
 *                              Elliptic curve E over GF(p) is defined through the set 
 *                            E = {(x,y) in GF(p) : y^2=x^3+ax+b, 4a^3+27b^2 != 0 (mod p)}
 */
/*************************************************************************************************/


/*************************************************************************************************/
/*                                      ecFp_curve_init_set_ln()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
ecFp_curve_t ecFp_curve_init_set_ln( L_NUMBER *a, L_NUMBER *b, L_NUMBER *p)
#else
ecFp_curve_t ecFp_curve_init_set_ln( a, b, p)
                           L_NUMBER *a;
                           L_NUMBER *b; 
                           L_NUMBER *p;
#endif                           
{
	ecFp_curve_t E;

	E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
	if ( E == NULL ) return NULL; /* memory allocation failed! */
	trans(a, E->a);
	trans(b, E->b);
	trans(p, E->p);

	return E;
}

/*************************************************************************************************/
/*                                     ecFp_curve_init_set_str()
/*************************************************************************************************/

#if  defined (__STDC__) || defined (__cplusplus)
ecFp_curve_t  ecFp_curve_init_set_str (int *ret,  char* a, char* b,  char* p)
#else
ecFp_curve_t  ecFp_curve_init_set_str (ret, a, b, p)
                             int *ret;
                             char* a;
                             char* b;
                             char* p;
#endif
{
	int a_err = 0;
	int b_err = 0;
	int p_err = 0;

	ecFp_curve_t E;

	E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
	if ( E == NULL ) return NULL; /* memory allocation failed! */
	if ( string_to_ln(a, E->a) ) a_err = 1; /* a is not correct number in the base indicated*/
	if ( string_to_ln(b, E->b) ) b_err = 2; /* b is not correct number in the base indicated */
	if ( string_to_ln(p, E->p) ) p_err = 4; /* p is not correct number in the base indicated */

	*ret = a_err + b_err + p_err; 
	/* the integer ret indicates if any (and indirectly which) of the three strings */
	/* represented by a,b, and p is not a correct number in the base given by the prefix. */
	/* if ret > 0 then error (you should check strings a,b,p) */ 
	if (*ret >0){
		free(E);
	 	return  NULL; /* error: E could not be initialized because of wrong strings */
	 } 
                   
	return E;
}

/*************************************************************************************************/
/*                                     ecFp_curve_setall_str()
/*************************************************************************************************/

#if  defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_setall_str (ecFp_curve_destptr E, char* a, char* b, char* p)
#else
int ecFp_curve_setall_str (E, a,  b, p)
         ecFp_curve_destptr E;
         char* a;
         char* b;
         char* p;
#endif
{
	int a_err = 0;
	int b_err = 0;
	int p_err = 0;

	if ( string_to_ln(a, E->a) ) a_err = 1; /* a is not correct number in the base given by the prefix*/
	if ( string_to_ln(b, E->b) ) b_err = 2; /* b is not correct number in the base given by the prefix*/
	if ( string_to_ln(p, E->p) ) p_err = 4; /* p is not correct number in the base given by the prefix*/

	/* the returned integer indicates if any (and indirectly which) of the three strings */
	/* represented by a,b and p is not a correct number in the base given by the prefix. */
	return a_err + b_err + p_err;
	/* if return > 0 then error (you should check strings a,b,p) */
}

        
/*************************************************************************************************/
/*                                     ecFp_curve_set_a_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_set_a_str (ecFp_curve_destptr E, char* a)
#else
int ecFp_curve_set_a_str (E, a)
           ecFp_curve_destptr E;
           char* a;
#endif
{
	return (string_to_ln(a, E->a)); 
	/* if not 0 is returned, then the string represented by char *a is not a correct number in the base given by the prefix. */
}

/*************************************************************************************************/
/*                                         ecFp_curve_set_b_str()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_set_b_str (ecFp_curve_destptr E, char* b)
#else
int ecFp_curve_set_b_str (E, b)
           ecFp_curve_destptr E;
           char* b;          
#endif
{
	return (string_to_ln(b, E->b)); 
	/* if not 0 is returned, then the string represented by char *b is not a correct number in the base given by the prefix. */
}

/*************************************************************************************************/
/*                                          ecFp_curve_set_p_str()
/*************************************************************************************************/


#if defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_set_p_str (ecFp_curve_destptr E, char* p)
#else
int ecFp_curve_set_p_str (E, p)
           ecFp_curve_destptr E;
           char* p;          
#endif
{
	return (string_to_ln(p, E->p)); 
	/* if not 0 is returned, then the string represented by char *b is not a correct number in the base given by the prefix. */
}

/*************************************************************************************************
/*			                     ecFp_curve_getstr_a ()
/**************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char *ecFp_curve_getstr_a (ecFp_curve_srcptr E, const int base)
#else
char *ecFp_curve_getstr_a (E, base)
		   ecFp_curve_srcptr E;
           const int base;          
#endif		
{
	 char *temp;
	 if ( ln_to_string(E->a,&temp,base) ) temp=NULL;
	 return(temp);
}

/*************************************************************************************************
/*		                         ecFp_curve_getstr_b ()
/**************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char *ecFp_curve_getstr_b (ecFp_curve_srcptr E, const int base)
#else
char *ecFp_curve_getstr_b (E, base)
		   ecFp_curve_srcptr E;
           const int base;          
#endif		
{
	 char *temp;
	 if ( ln_to_string(E->b,&temp,base) ) temp=NULL;
	 return(temp);
}


/*************************************************************************************************
/*				   ecFp_curve_getstr_p ()
/**************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
char *ecFp_curve_getstr_p (ecFp_curve_srcptr E, const int base)
#else
char *ecFp_curve_getstr_p (E, base)
		   ecFp_curve_srcptr E;
           const int base;          
#endif		
{
	 char *temp;
	 if ( ln_to_string(E->p,&temp,base) ) temp=NULL;
	 return(temp);
}




/*************************************************************************************************/
/*                                         ecFp_curve_set_a_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_curve_set_a_ui (ecFp_curve_destptr E, const unsigned int a)
#else
void ecFp_curve_set_a_ui (E, a)
           ecFp_curve_destptr E;
           const unsigned int a;
#endif
{
	inttoln(a, E->a);
}

/*************************************************************************************************/
/*                                          ecFp_curve_set_b_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_curve_set_b_ui (ecFp_curve_destptr E, const unsigned int b)
#else
void ecFp_curve_set_b_ui (E, b)
            ecFp_curve_destptr E;
            const unsigned int b;
#endif
{
	inttoln(b, E->b);
}

/*************************************************************************************************/
/*                                          ecFp_curve_set_p_ui()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_curve_set_p_ui (ecFp_curve_destptr E, const unsigned int p)
#else
void ecFp_curve_set_p_ui (E, p)
            ecFp_curve_destptr E;
            const unsigned int p;
#endif
{
	inttoln(p, E->p);
}

/*************************************************************************************************/
/*                                        ecFp_curve_set_a_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_set_a_si (ecFp_curve_destptr E, const signed long int a)
#else
int ecFp_curve_set_a_si (E, a)
           ecFp_curve_destptr E;
           const signed long int a;
#endif
{	
	return (sint_to_ln(a, E->a) );
}

/*************************************************************************************************/
/*                                        ecFp_curve_set_b_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_set_b_si (ecFp_curve_destptr E, const signed long int b)
#else
int ecFp_curve_set_b_si (E, b)
           ecFp_curve_destptr E;
           const signed long int b;
#endif
{	
	return (sint_to_ln(b, E->b));
}

/*************************************************************************************************/
/*                                        ecFp_curve_set_p_si()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_set_p_si (ecFp_curve_destptr E, const signed long int p)
#else
int ecFp_curve_set_p_si (E, p)
           ecFp_curve_destptr E;
           const signed long int p;
#endif
{	
	return (sint_to_ln(p, E->p));
}

/*************************************************************************************************/
/*                                           ecFp_curve_clear()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_curve_clear(ecFp_curve_destptr E)
#else
void ecFp_curve_clear(E)
         ecFp_curve_destptr E;
#endif
{
		free (E);
}

/*************************************************************************************************/
/*                                             ecFp_curve_copy()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_curve_copy (ecFp_curve_destptr E, ecFp_curve_srcptr K)
#else
void ecFp_curve_copy (E, K)
            ecFp_curve_destptr E;
            ecFp_curve_srcptr K;
#endif
{
	trans(K->a, E->a);
	trans(K->b, E->b);
	trans(K->p, E->p);
	
	/* E and K are now two curves defined through the same parameters */
}



/****************************************************************************************************************/
/*																							X9_62_init_curve_Fp()
/***************************************************************************************************************/

/* Function to initialize the sample curves given in J.5 of the X9.62 standard*/
#if defined (__STDC__) || defined (__cplusplus)
int X9_62_init_curve_Fp(ecFp_curve_destptr E, ecFp_point_ac_destptr G,L_NUMBER *cofactor, L_NUMBER *primefactor, char *curve_ID)
#else
int X9_62_init_curve_Fp(E, G, cofactor, primefactor, curve_ID)
	ecFp_curve_destptr E;
	ecFp_point_ac_destptr G;
	L_NUMBER *cofactor, *primefactor;
	char *curve_ID;
#endif
{	
	int help;
	L_NUMBER G_compressed[MAXLGTH];

	if (strcmp( curve_ID, "prime192v1")==0) {
		help=string_to_ln( "0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 64210519 E59C80E7 0FA7E9AB 72243049 FEB8DEEC C146B9B1" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("627 71017 35386 68076 38357 89423 20766 64160 83908 70039 03249 61279" ,E->p);
		if (help == -1) return (-1);
		help=string_to_ln("0X 3 188DA80E B03090F6 7CBF20EB 43A18800 F4FF0AFD 82FF1012",G_compressed);
		if (help == -1) return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1)	return (-1);
		help=string_to_ln("0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	99DEF836 	146BC9B1 B4D22831" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}

	if (strcmp( curve_ID, "prime192v2")==0) {
		help=string_to_ln( "0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X CC22D6DF B95C6B25 	E49C0D63 	64A4E598 	0C393AA2 1668D953" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("627 71017 35386 68076 38357 89423 20766 64160 83908 70039 03249 61279" ,E->p);
		if (help == -1) return (-1);
		help=string_to_ln("0X 3 EEA2BAE7 E1497842 F2DE7769 CFE9C989 C072AD69 6F48034A",G_compressed);
		if (help == -1)	return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return (-1);
		help=string_to_ln("0X FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	5FB1A724 	DC804186 48D8DD31" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}
	if (strcmp( curve_ID, "prime192v3")==0) {
		help=string_to_ln( "0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	FFFFFFFE 	FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 22123DC2 	395A05CA 	A7423DAE 	CCC94760 	A7D46225 6BD56916" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("627 71017 35386 68076 38357 89423 20766 64160 83908 70039 03249 61279 " ,E->p);
		if (help == -1) return 1;
		help=string_to_ln("0X 2 7D297781 00C65A1D A1783716 588DCE2B 8B4AEE8E 228F1896",G_compressed);
		if (help == -1)	return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return (-1);
		help=string_to_ln("0X FFFFFFFF 	FFFFFFFF 	FFFFFFFF 	7A62D031 	C83F4294 F640EC13" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}

	if (strcmp( curve_ID, "prime239v1")==0) {
	help=string_to_ln( "0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FFFFFFFF 80000000 00007FFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 6B01 6C3BDCF1 8941D0D6 54921475 CA71A9DB 2FB27D1D 37796185 C2942C0A" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("883423532389192164791648750360308885314476597252960362 792450860609699839" ,E->p);
		if (help == -1) return (-1);
		help=string_to_ln("0X 20FFA 963CDCA8 816CCC33 B8642BED F905C3D3 58573D3F 27FBBD3B 3CB9AAAF",G_compressed);
		if (help == -1) return (-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return (-1);
		help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FF9E5E9A 9F5D9071 FBD15226 88909D0B" ,primefactor);
		if (help == -1) return (-1);
		return 0;
	}

	if (strcmp( curve_ID, "prime239v2")==0) {
	help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FFFFFFFF 80000000 00007FFF FFFFFFFC",E->a);
		if (help == -1) return (-1);
		help=string_to_ln("0X 617F AB683257 6CBBFED5 0D99F024 9C3FEE58 B94BA003 8C7AE84C 8C832F2C" ,E->b);
		if (help == -1) return (-1);
		help=string_to_ln("883423532389192164791648750360308885314476597252960362 792450860609699839" ,E->p);
		if (help == -1) return(-1);
		help=string_to_ln("0X 238AF 09D98727 705120C9 21BB5E9E 26296A3C DCF2F357 57A0EAFD 87B830E7",G_compressed);
		if (help == -1)	return(-1);		
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return(-1);
		help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF8000 00CFA7E8 594377D4 14C03821 BC582063" ,primefactor);
		if (help == -1) return(-1);
		return 0;
	}
	if (strcmp( curve_ID, "prime239v3")==0) {
	help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FFFFFFFF 80000000 00007FFF FFFFFFFC",E->a);
		if (help == -1) return(-1);
		help=string_to_ln("0X 2557 05FA2A30 6654B1F4 CB03D6A7 50A30C25 0102D498 8717D9BA 15AB6D3E" ,E->b);
		if (help == -1) return(-1);
		help=string_to_ln("883423532389192164791648750360308885314476597252960362 792450860609699839" ,E->p);
		if (help == -1) return(-1);
		help=string_to_ln("0X 36768 AE8E18BB 92CFCF00 5C949AA2 C6D94853 D0E660BB F854B1C9 505FE95A",G_compressed);
		if (help == -1)	return(-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01" ,cofactor);
		if (help == -1) return(-1);
		help=string_to_ln("0X 7FFF FFFFFFFF FFFFFFFF FFFF7FFF FF975DEB 41B3A605 7C3C4321 46526551" ,primefactor);
		if (help == -1) return(-1);
		return 0;
	}
	if (strcmp( curve_ID, "prime256v1")==0) {
	help=string_to_ln("0X FFFFFFFF 00000001 00000000 00000000 00000000 FFFFFFFF FFFFFFFF FFFFFFFC",E->a);
		if (help == -1) return(-1);
		help=string_to_ln("0X 5AC635D8 AA3A93E7 B3EBBD55 769886BC 651D06B0 CC53B0F6 3BCE3C3E 27D2604B" ,E->b);
		if (help == -1) return(-1);
		help=string_to_ln("11579208921035624876269744694940757353008614341529031419 5533631308867097853951 " ,E->p);
		if (help == -1) return(-1);
		help=string_to_ln("0X 3 6B17D1F2 E12C4247 F8BCE6E5 63A440F2 77037D81 2DEB33A0 F4A13945 D898C296",G_compressed);
		if (help == -1)	return(-1);
		ecFp_X9_decompress_point_ac(G,E,G_compressed);
		help=string_to_ln("01",cofactor);
		if (help == -1) return(-1);
		help=string_to_ln("0X FFFFFFFF 00000000 FFFFFFFF FFFFFFFF BCE6FAAD A7179E84 F3B9CAC2 FC632551" ,primefactor);
		if (help == -1) return(-1);
		return 0;	
	}
	return (-1); // the curve with the name indicated is not defined in this file 
}


/********************************************** EOF **********************************************/