/* This files  version number is v0 */


/*

s_ecmath.h -- headerfile for s_ecmath.c  
           -- Various mathematical functions which are needed in the package.
*/
/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */

#include "arithmet.h"

/*************************************************************************************************/
/*                         Compiler specific function-prototype declaration
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
     #define  _PROTO(x) x  /* ANSI C Prototypes */
#else
     #define  _PROTO(x) () /* Pre ANSI  C Prototypes */
#endif

/************************************************************************************************/

/* some needfull maths functions */

int _log2_z _PROTO((L_NUMBER *n)); 
    /* calculate i = min {x | 2^x > n }. returns i */

void _mod_div2 _PROTO((L_NUMBER *d, L_NUMBER *n, L_NUMBER *p)); 
     /*input:  0 <= n < p, p prim, 
        ouput: d = n/2 (mod p) */

void _lucas_seq _PROTO((L_NUMBER *U, L_NUMBER *V, L_NUMBER *k, L_NUMBER *P, L_NUMBER *Q, L_NUMBER *p)); 
     /* ATTN. P is not p */
     /* Generate the k-th number U(k) and V(k) of the Lucas sequences */
     /* See A.2.4 in IEEE P1363/D8 */

int _mod_congruent _PROTO((L_NUMBER *k,L_NUMBER *p, const unsigned long int j, const unsigned long int r));
       /* needed in _mod_sqrt() */
       /* calculate k such that:  p = j*k + r */
       /* returns 0 if such a k does not exist */
       /* returns 1 if such a k exist */

int _mod_sqrt _PROTO((L_NUMBER *z, L_NUMBER *g, L_NUMBER *p)); 
      /* A.2.5 in IEEE P1363 / D8 */
      /* calculate z such that z^2 = g (mod p) */
      /* returns 0 if z does not exist */      
      /* returns 1 is z exist */

/********************************************** EOF **********************************************/