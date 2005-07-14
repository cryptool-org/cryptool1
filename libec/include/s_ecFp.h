/* This files  version number is v0.4 */

/* Januar-May 1999, March 2000 - Bartol Filipovic - Deutsche Bank AG, IT Security 
                                 and Anna-Barbara Berger - Secude GmbH */


/*

s_ecFp.h     -- Declarations of various types and functions for implementing ECC primitives. 
             -- types and functions for handling with elliptic curves E over GF(p)
             -- types for points (affine or projective coordinates) and point handling on E.
             -- arithmetic on E (affine and projective coordinate representation of Points supported).
             -- We follow the unapproved IEEE P1363 Standards Draft Version 8 (IEEE P1363/D8) 


Definition: Elliptic curve E over GF(p) is defined through the set 
            E = {(x,y) in GF(p)^2 : y^2=x^3+ax+b, with a and b such that 4a^3+27b^2 != 0 (mod p)} + point at infinity.
            The point at infinity is the identity element of the group.
                 
Definition: A point P (which is not the point at infinity) on E has in affine coordinate representation two coordinates 
            P=(x,y) with x,y in {0, 1, 2, ..., p-1}.
                 
Definition: A compressed point (only points with affine coordinates) is a point P with only one bit for his y coordinate.
            P=(x,y) with x in {0, 1, 2, ..., p-1} and y in {0,1}. (Remark: such a compressed point could be decompressed
            in a point P=(x,y´) with x,y´ in {0, 1, 2, ..., p-1}.)

Definition: A point P (other than point at infinity) on E has in projective coordinate representation three coordinates 
            P=(x,y,z) with x,y,z in {0, 1, 2, ..., p-1}. (Remark: This type of points should lead to faster arithmetic than 
            points in affine coordinates.)

To this headerfile (s_ecFp.h)  belong the following C sourcecode files (and other headerfiles):

   -- s_ecpara.c       Functions for arithmetic (points in affine coordinates representation) on an elliptic curve E.
   -- s_ecparp.c       Functions for arithmetic (points in projective coordinates representation) on an elliptic curve E.
   -- s_ecpcur.c       Functions for initializing elliptic curves (that means setting the parameters a, b and p).
   -- s_ecppta.c       Supports handling of points in affine coordinates on E.
   -- s_ecpptp.c       Supports handling with points in projective coordinates on E.
   -- s_ecpptc.c       Routines for converting a point on E from affine to projective coordinates and vice versa.
   -- s_ecprpt.c       Routines for choosing random points on E. The user should check the used pseudo-random
                       number generator (see files prng.h and prng.c) for security.
   -- s_bithdl.c       Functions for getting information about bits of L_NUMBER_ARRAYs. 
   -- s_bithdl.h
   -- s_ecmath.c       Some mathematical functions which are needed by other functions in this package.
   -- s_ecmath.h                                                        
   -- s_prng.c         Pseudorandom number generation adapted to this package.
   -- s_prng.h

*/

#ifndef _s_ecFp_ 
	#define _s_ecFp_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "asn1.h"
#include "arithmet.h"

/*************************************************************************************************/
/*                            Compiler specific function-prototype declaration
/*************************************************************************************************/

#ifndef  _PROTO
#if defined (__STDC__) || defined (__cplusplus)
#define  _PROTO(x) x  /* ANSI C Prototypes */
#else
#define  _PROTO(x) () /* Pre ANSI C Prototypes */
#endif
#endif

/*************************************************************************************************/
/*                            Basic objects declaration: elliptic curve E, points on E
/*************************************************************************************************/

/* Elliptic curve E = {(x,y) | y^2 = x^3 + ax + b (modulo p)} */

typedef struct
{
	   L_NUMBER a[MAXLGTH];
	   L_NUMBER b[MAXLGTH];
	   L_NUMBER p[MAXLGTH];
} __CurveFp_struct; /* parameters a, b and p define E with equation  y^2 = x^3 + ax + b (modulo p) */

/* Point, represented in affine coordinates, on elliptic curve E */

typedef struct  
{
	L_NUMBER x[MAXLGTH];
	L_NUMBER y[MAXLGTH];
	int infinity; /* Boolean value. If not zero then the point  is the identity of the group E */
} __PointAc_struct; /* Affine coordinates. Point P = (x, y) on elliptic curve E */

/* Point, represented in affine coordinates with compressed y-coordinate on elliptic curve E */

typedef struct  
{
	L_NUMBER x[MAXLGTH]; 
	int y; /* the y coordinate is compressible. y is either 0 or 1 */
	int infinity; /* Boolean value. If not zero then the point  is the identity of the group E */
} __CompressedPointAc_struct; /* Affine coordinates. Point P = (x, y) on elliptic curve E */

/* Point, represented in projective  coordinates, on elliptic curve E */

typedef struct
{
	L_NUMBER x[MAXLGTH];
	L_NUMBER y[MAXLGTH];
	L_NUMBER z[MAXLGTH];
	int infinity;  /* Boolean value. If not zero then the point  is the identity of the group E */
} __PointPc_struct;  /* Projective coordinates. Point P = (x,y,z) on elliptic curve E */



/*************************************************************************************************/
/*                    The DomainParam struct is used in ecssa.c/.h
/*************************************************************************************************/

/* The set of domain parameters specifies:
    - ecFp_curve_t E (the elliptic curve E over GF(p))
    - a positive prime integer r dividing the number of points on E (primefactor of #E)
    - curve point G of order r (the generator of the subgroup of order r)
   (- implicitly it also specifies the cofactor k = #E/r)
   
   Some domain parameters are defined in the file s_ecpX9c.c.

   Public keys and private keys are associated with the domain parameters E,G and r.
*/

typedef struct
{
	__CurveFp_struct *E;
	__PointAc_struct *G;
	L_NUMBER r[MAXLGTH]; /* r is the order of G */
	L_NUMBER k[MAXLGTH]; /* k is the cofactor k = #E/r */
	L_NUMBER privKey[MAXLGTH]; /* privKey is the private Key which is associated with this domain parameter set */
   	__PointAc_struct *pubKey; /* pubKey points to the public key of this domain parameter set */
} __DomParamAc_struct;

typedef struct
{
	__CurveFp_struct *E;
	__PointPc_struct *G;
	L_NUMBER r[MAXLGTH]; /* r is the order of G */
	L_NUMBER k[MAXLGTH]; /* k is the cofactor k = #E/r */
	L_NUMBER privKey[MAXLGTH]; /* privKey is the private Key which is associated with this domain parameter set */
    __PointPc_struct *pubKey; /* pubKey points to the public key of this domain parameter set */
} __DomParamPc_struct;

/*************************************************************************************************/
/*                                         Typedefinitions
/*************************************************************************************************/

typedef __DomParamAc_struct     *EcDomParam_ac_ptr;
typedef __DomParamPc_struct     *EcDomParam_pc_ptr;


#if defined (__STDC__) || defined (__cplusplus)
     #define __srcptr_const /*"const" deleted, due to problems with L_NUMBER types */
#else
    #define __srcptr_const
#endif

/* User visible types */

typedef __CurveFp_struct           *ecFp_curve_t;
typedef __PointAc_struct           *ecFp_point_ac_t;
typedef __CompressedPointAc_struct *ecFp_point_cmprs_ac_t;
typedef __PointPc_struct           *ecFp_point_pc_t;

/* intern types */
/* Suffix "_srcptr" indicates that the object to which the pointer points to will remain unchanged after function call. */
/* Suffix "_destptr" indicates that the object to which the pointer points to is the return value of the function. */

typedef __srcptr_const __CurveFp_struct           *ecFp_curve_srcptr;
typedef                __CurveFp_struct           *ecFp_curve_destptr;
typedef __srcptr_const __PointAc_struct           *ecFp_point_ac_srcptr;
typedef                __PointAc_struct           *ecFp_point_ac_destptr;
typedef __srcptr_const __CompressedPointAc_struct *ecFp_point_cmprs_ac_srcptr;
typedef                __CompressedPointAc_struct *ecFp_point_cmprs_ac_destptr;
typedef __srcptr_const __PointPc_struct           *ecFp_point_pc_srcptr; 
typedef                __PointPc_struct           *ecFp_point_pc_destptr;

/*************************************************************************************************/
/*
 *   Functions for intializing and clearing memory for an elliptic curve over GF(p) and setting curve parameters a, b and p.
 *                                                 Elliptic curve E over GF(p) is defined through the set 
 *                               E = {(x,y) in GF(p)^2 : y^2=x^3+ax+b, with a and b such that 4a^3+27b^2 != 0 (mod p)}
 */
/*************************************************************************************************/

#define ecFp_curve_init (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
   /* initialize memory for a elliptic curve. Returns a pointer to the reserved memory */

ecFp_curve_t  ecFp_curve_init_set_ln _PROTO(( L_NUMBER *a, L_NUMBER *b,  L_NUMBER *p));
   /* 
      initialize memory for a elliptic curve E and sets the parameters a, b, p which define E.
      Returns a pointer to the reserved memory 
   */

ecFp_curve_t  ecFp_curve_init_set_str _PROTO((int *ret,  char* a,  char* b,  char* p));
   /* 
      initialize memory for a elliptic curve E and sets the parameters a, b, p which define E.
      Returns a pointer to the reserved memory.
      The strings are interpreted in the common C sense:
      prefix 0x means: hexadecimal-number, prefix O means: octet-number, no prefix: decimal number.
      If the integer that ret points to is bigger than 0,  an error occured during the attempt to set one 
      or more of the curve parameters a, b, p. At least one of the three strings is not a correct number in 
      in the chosen base. Which of them can be determined by the value of ret:
      "a" is not a number in base base: binary_representation(ret) = ...00001 (least significant bit is set to one)
      "b" is not a number in base base: binary_representation(ret) = ...00010 (second bit is set to one)
      "p" is not a number in base base: binary_representation(ret) = ...00100 (third bit is set to one)
      You see:  ret can have 8 diffrent values (0,1, ..., 7), with the value of ret it is possible to recognize which
      string(s) are wrong (maybe the prefix was not chosen correctly).
   */

int ecFp_curve_setall_str _PROTO((ecFp_curve_destptr E, char* a, char* b, char* p));

int ecFp_curve_set_a_str _PROTO((ecFp_curve_destptr E, char* a));

int ecFp_curve_set_b_str _PROTO((ecFp_curve_destptr E, char* b));

int ecFp_curve_set_p_str _PROTO((ecFp_curve_destptr E, char* p));

char *ecFp_curve_getstr_a _PROTO((ecFp_curve_srcptr E, const int base)); 

char *ecFp_curve_getstr_b _PROTO((ecFp_curve_srcptr E, const int base)); 

char *ecFp_curve_getstr_p _PROTO((ecFp_curve_srcptr E, const int base)); 

void ecFp_curve_set_a_ui _PROTO((ecFp_curve_destptr E, const unsigned int a));

void ecFp_curve_set_b_ui _PROTO((ecFp_curve_destptr E, const unsigned int b));

void ecFp_curve_set_p_ui _PROTO((ecFp_curve_destptr E, const unsigned int p));

int ecFp_curve_set_a_si _PROTO((ecFp_curve_destptr E, const signed long int a));

int ecFp_curve_set_b_si _PROTO((ecFp_curve_destptr E, const signed long int b));

int ecFp_curve_set_p_si _PROTO((ecFp_curve_destptr E, const signed long int p));

void ecFp_curve_clear _PROTO((ecFp_curve_destptr E));

void ecFp_curve_copy _PROTO((ecFp_curve_destptr E, ecFp_curve_srcptr K));

int X9_62_init_curve_Fp _PROTO((ecFp_curve_destptr E, ecFp_point_ac_destptr G,L_NUMBER *cofactor, L_NUMBER *primefactor, char *curve_ID));


/*************************************************************************************************/
/*
 *  Some functions for initializing and clearing memory of points on elliptic curves over GF(p) and
 *		functions for setting, copy points, (de)compress points in affine coordinates.
 */
/*************************************************************************************************/ 

/* affine coordinates */

#define ecFp_point_init_ac  (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));

ecFp_point_ac_t ecFp_point_init_set_ac_ln _PROTO((L_NUMBER *x, L_NUMBER *y, const int inf));

ecFp_point_ac_t ecFp_point_init_set_ac_str _PROTO((int *ret, char *x, char *y, const int inf));

int ecFp_point_setall_ac_str _PROTO((ecFp_point_ac_destptr S, char *x, char *y, const int inf));

int ecFp_point_set_xcoord_ac_str _PROTO((ecFp_point_ac_destptr S, char *x));

int ecFp_point_set_ycoord_ac_str _PROTO((ecFp_point_ac_destptr S, char *y));

char *ecFp_point_getstr_xcoord_ac _PROTO((ecFp_point_ac_srcptr S, const int base));

char *ecFp_point_getstr_ycoord_ac _PROTO((ecFp_point_ac_srcptr S, const int base));

void ecFp_point_set_xcoord_ac_si _PROTO((ecFp_point_ac_destptr S, const signed long int x));

void ecFp_point_set_ycoord_ac_si _PROTO((ecFp_point_ac_destptr S, const signed long int y));

void ecFp_point_set_xcoord_ac_ui _PROTO((ecFp_point_ac_destptr S, const unsigned long int x));

void ecFp_point_set_ycoord_ac_ui _PROTO((ecFp_point_ac_destptr S, const unsigned long int y));

void ecFp_point_set_infinity_ac _PROTO((ecFp_point_ac_destptr S));

int ecFp_point_check_infinity_ac _PROTO((ecFp_point_ac_srcptr S));

void ecFp_point_clear_ac _PROTO((ecFp_point_ac_destptr S));

void ecFp_point_copy_ac _PROTO((ecFp_point_ac_destptr S, ecFp_point_ac_srcptr P));

void ecFp_point_compress_ac _PROTO((ecFp_point_cmprs_ac_destptr S, ecFp_point_ac_srcptr P));  /* A.9.6 in IEEE P1363/D8 */

int ecFp_point_decompress_ac _PROTO((ecFp_point_ac_destptr S, ecFp_curve_srcptr E,  ecFp_point_cmprs_ac_srcptr P)); /* A.12.8 in IEEE P1363/D8 */

void ecFp_X9_compress_point_ac _PROTO((L_NUMBER *compr_pt, ecFp_point_ac_destptr G, L_NUMBER *p)); /*X9.62 4.3.6*/

int  ecFp_X9_decompress_point_ac _PROTO((ecFp_point_ac_destptr G, ecFp_curve_srcptr E,L_NUMBER *compr_pt)); /*X9.62 4.3.7*/

/* projective coordinates */

#define ecFp_point_init_pc  (ecFp_point_pc_t) malloc(sizeof(__PointPc_struct));

ecFp_point_pc_t ecFp_point_init_set_pc_ln _PROTO((L_NUMBER *x, L_NUMBER *y, L_NUMBER *z, const int inf));

ecFp_point_pc_t ecFp_point_init_set_pc_str _PROTO((int *ret, const char *x, const char *y, const char *z, const int inf));

int ecFp_point_setall_pc_str _PROTO((ecFp_point_pc_destptr S, const char *x, const char *y, const char *z, const int inf));

int ecFp_point_set_xcoord_pc_str _PROTO((ecFp_point_pc_destptr S, const char *x));

int ecFp_point_set_ycoord_pc_str _PROTO((ecFp_point_pc_destptr S, const char *y));

int ecFp_point_set_zcoord_pc_str _PROTO((ecFp_point_pc_destptr S, const char *z));

char *ecFp_point_getstr_xcoord_pc _PROTO((ecFp_point_pc_srcptr S, const int base));

char *ecFp_point_getstr_ycoord_pc _PROTO((ecFp_point_pc_srcptr S, const int base));

char *ecFp_point_getstr_zcoord_pc _PROTO((ecFp_point_pc_srcptr S, const int base));

void ecFp_point_set_xcoord_pc_si _PROTO((ecFp_point_pc_destptr S, const signed long int x));

void ecFp_point_set_ycoord_pc_si _PROTO((ecFp_point_pc_destptr S, const signed long int y));

void ecFp_point_set_zcoord_pc_si _PROTO((ecFp_point_pc_destptr S, const signed long int z));

void ecFp_point_set_xcoord_pc_ui _PROTO((ecFp_point_pc_destptr S, const unsigned long int x));

void ecFp_point_set_ycoord_pc_ui _PROTO((ecFp_point_pc_destptr S, const unsigned long int y));

void ecFp_point_set_zcoord_pc_ui _PROTO((ecFp_point_pc_destptr S, const unsigned long int z));

void ecFp_point_set_infinity_pc _PROTO((ecFp_point_pc_destptr S));

int ecFp_point_check_infinity_pc _PROTO((ecFp_point_pc_destptr S, ecFp_curve_srcptr E));

void ecFp_point_clear_pc _PROTO((ecFp_point_pc_destptr S));

void ecFp_point_copy_pc _PROTO((ecFp_point_pc_destptr S, ecFp_point_pc_srcptr P));

/*************************************************************************************************/
/*
 *            Some functions for generating random points on an elliptic curve E over GF(p)
 */
/*************************************************************************************************/ 

/* A.11.1  in IEEE P1363 / D8 */

void ecFp_rp_ac _PROTO((ecFp_point_ac_destptr S, ecFp_curve_srcptr E)); /* S in affine coordinates */

void ecFp_rp_pc _PROTO((ecFp_point_pc_destptr S, ecFp_curve_srcptr E)); /* S in projective coordinates */

/* A.11.3  in IEEE P1363 / D8 */

int ecFp_rp_lpo_ac _PROTO((ecFp_point_ac_destptr G, ecFp_curve_srcptr E, L_NUMBER *p, L_NUMBER *k)); /* G in affine coordinates */

int ecFp_rp_lpo_pc _PROTO((ecFp_point_pc_destptr G, ecFp_curve_srcptr E, L_NUMBER *p, L_NUMBER *k)); /* G in projective coordinates */

/*************************************************************************************************/
/*
 *                  Converting a point P=(x1,y1) in affine coordinates on E over GF(p) to 
 *                    the point P=(x2,y2,z2) in projective coordinates, and vice versa.
 */
/*************************************************************************************************/ 

/* see A.9.6 in IEEE P1363 / D8 */

void ecFp_point_pc_to_ac _PROTO((ecFp_point_ac_destptr S, ecFp_point_pc_srcptr P, ecFp_curve_srcptr E));

void ecFp_point_ac_to_pc _PROTO((ecFp_point_pc_destptr S, ecFp_point_ac_srcptr P));

void ecFp_DomParam_pc_to_ac _PROTO((EcDomParam_ac_ptr dp_ac, EcDomParam_pc_ptr dp_pc));

void ecFp_DomParam_ac_to_pc _PROTO((EcDomParam_pc_ptr dp_pc, EcDomParam_ac_ptr dp_ac));

/*************************************************************************************************/
/*
 *                           Functions for arithmetic on an elliptic curve over GF(p).
 */
/*************************************************************************************************/ 

/* affine coordinates */

/* A.10.1 in IEEE P1363 / D8 */

int ecFp_add_ac _PROTO((ecFp_point_ac_destptr R, ecFp_curve_srcptr E, ecFp_point_ac_srcptr P, ecFp_point_ac_srcptr Q));

int ecFp_sub_ac _PROTO((ecFp_point_ac_destptr R, ecFp_curve_srcptr E, ecFp_point_ac_srcptr P, ecFp_point_ac_srcptr Q));

/* A.10.3 in IEEE P1363 / D8 */

int ecFp_mult_ac _PROTO((ecFp_point_ac_destptr R, ecFp_curve_srcptr E, L_NUMBER *n, ecFp_point_ac_srcptr P)); 

int ecFp_mult_ac_str _PROTO((ecFp_point_ac_destptr R, ecFp_curve_srcptr E, const char *n_str, ecFp_point_ac_srcptr P));

/* projective coordinates */

/* A.10.8 in IEEE P1363 / D8 */

void ecFp_add_pc _PROTO((ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P, ecFp_point_pc_srcptr Q)); 

int ecFp_sub_pc _PROTO((ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P, ecFp_point_pc_srcptr Q));

/* A.10.9 in IEEE P1363 / D8 */

int ecFp_mult_pc _PROTO((ecFp_point_pc_destptr R, ecFp_curve_srcptr E, L_NUMBER *n, ecFp_point_pc_srcptr P));

int ecFp_mult_pc_str _PROTO((ecFp_point_pc_destptr R, ecFp_curve_srcptr E, const char *n, ecFp_point_pc_srcptr P));

/* subroutines, normally not called directly by an user. */

/* A.10.4 in IEEE P1363 / D8 */

void _ellip_double_pc _PROTO((ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P));

/* A.10.5 in IEEE P1363 / D8 */

int _ellip_add_pc _PROTO((ecFp_point_pc_destptr R, ecFp_curve_srcptr E, ecFp_point_pc_srcptr P, ecFp_point_pc_srcptr Q));

/************************************************************************************************/

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* #ifndef _s_ecFp_ */

/************************************************ EOF ********************************************/
/************************************************ EOF ********************************************/
/************************************************ EOF ********************************************/
