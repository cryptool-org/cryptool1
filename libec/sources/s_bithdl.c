/* This files  version number is v0*/


/*

s_bithdl.c -- Functions for getting information about bits of L_NUMBER_ARREYs.


*/

/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */


 #include "arithmet.h"
 #include "s_bithdl.h"


/***********************************************************************************************
/*					_get_last_bit()
/***********************************************************************************************/
/* get the least significant bit of a number stored in an L_NUMBER_ARRAY*/
#if defined (__STDC__) || defined (__cplusplus)
int _get_last_bit(L_NUMBER *arg)
#else
int _get_last_bit(arg)
            L_NUMBER *arg;
#endif
{
	unsigned long int result;
	
	result=arg[1];
	result=result%2;

	return( (int) result);
}



/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int _get_ith_bit(L_NUMBER *k, const unsigned long int i)
#else
int _get_ith_bit(k, i)
               L_NUMBER *k;
               const unsigned long int i;
#endif
/* return the i-th bit in the binary representation of k.
  The lowest Bit has Index 0 ==> i.e. _get_ith_bit(even_number,0) == 0
  If i > Pos(Highest Bit of k) no errormessage! */ 
{
	return ( k[(i / WLNG)+1] & ( 1 << (i % WLNG) )  ) != 0;
}


/******************************************** EOF ************************************************/
/******************************************** EOF ************************************************/
/******************************************** EOF ************************************************/
