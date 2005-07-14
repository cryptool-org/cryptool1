/* This files  version number is v0*/


/*

s_prng.h  
          -- headerfile for the functions implemented in prng.c
          -- Look at s_prng.c to decide about the cryptographical security of the generated numbers.
*/

/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */

#ifndef _prng_ 
	#define _prng_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "asn1.h"
#include "arithmet.h"

/*************************************************************************************************/
/*                          Compiler specific function-prototype declaration
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
     #define  _PROTO(x) x  /* ANSI C Prototypes */
#else
     #define  _PROTO(x) () /* Pre ANSI  C Prototypes */
#endif

/*************************************************************************************************/

int _rand_bit _PROTO((void)); 
     /* returns randomly a bit (that means a 0 or 1) */

void _rand_int _PROTO((L_NUMBER *n, L_NUMBER *range)); 
     /* returns n. n is a randomly choosen number in the intervall [0,range-1] */
/************************************************************************************************/

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* #ifndef _prng_ */
     
/********************************************** EOF **********************************************/