/* This files  version number is v0*/


/*

s_prng.c -- Implemetation of two functions for returning pseudorandom integers.
         -- NOTE: The cryptographical security of the generated numbers
            depends on the used PRNG.

*/

/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */


#include <stdlib.h>

#include "s_prng.h"
#include "arithmet.h"
#include "ECsecude.h"

/*************************************************************************************************/
/*                                     _rand_bit()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int _rand_bit(void)
#else
int _rand_bit(void)
#endif
{	
	L_NUMBER temp[MAXLGTH];
	unsigned long int rand_nb;
	SECUDE(rndm)(1,temp,0);
	rand_nb=lntoint(temp);
	return ((int) rand_nb);  /* return 0 or 1 */
}

/*************************************************************************************************/
/*                                   _rand_int()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void _rand_int(L_NUMBER *n, L_NUMBER *range)
#else
void _rand_int(n, range)
            L_NUMBER *n;
            L_NUMBER *range;
#endif
{
	int number_of_bits;
	L_NUMBER temp[MAXLGTH];
	number_of_bits = SECUDE(lngtouse)(range)+1;
	SECUDE(rndm)(number_of_bits, n,  0);
	SECUDE(div)(n, range, temp , n); /* n is now a number in the intervall [0, range-1] */
}

/********************************************** EOF **********************************************/