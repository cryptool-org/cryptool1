/* This files  version number is v0 */


/*

s_bithdl.h  
          -- headerfile for the functions implemented in s_bithdl.c

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

/*************************************************************************************************/
/*                                      Functions
/*************************************************************************************************/

/* The function lngtouse in crlnutil.c gets (length in bits -1) of a number stored in an L_NUMBER_ARRAY */


int _get_last_bit _PROTO((L_NUMBER *arg));
/* get the least significant bit of a number stored in an L_NUMBER_ARRAY*/


int _get_ith_bit _PROTO((L_NUMBER *k, const unsigned long int i));
   /* return the i-th bit in the binary representation of k.
   The lowest Bit has Index 0 ==> i.e. _get_ith_bit(even_number,0) == 0
    If i > Position(Highest Bit of k) no errormessage! */ 

/********************************************** EOF **********************************************/