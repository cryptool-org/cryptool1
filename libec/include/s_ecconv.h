/* This files version number is v0*/

/* s_ecconv.h	-- contains the declarations of various functions to convert
		   numbers from a representation into another.
		   Header file of s_ecconv.c
*/



/* Anna-Barbara Berger, Secude GmbH */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "arithmet.h"

/***************************************************************************
/*                   some conversion routines
/**************************************************************************/
/***************************************************************************

/**************************************************************************/
/*            Compiler specific function-prototype declaration
/**************************************************************************/

#ifndef  _PROTO
#if defined (__STDC__) || defined (__cplusplus)
#define  _PROTO(x) x  /* ANSI C Prototypes */
#else
#define  _PROTO(x) () /* Pre ANSI  C Prototypes */
#endif
#endif

/**************************************************************************
/*                      conversion routines
/**************************************************************************/

/* the conversion has failed if and only if the return value is negative*/

int char_to_int _PROTO((char argument, int *result, const int base));
/* Supported bases are 8,10,16 */

int string_to_ln _PROTO((const char *argument, L_NUMBER *result));
/* The prefix of the string indicates the representation of the integer 
   contained in the string. 0x:hexadecimal, 0: octal, no prefix: 10*/

int string_to_int _PROTO((const char *argument, int *result));
/* The prefix of the string indicates the representation of the integer 
   contained in the string. 0x:hexadecimal, 0: octal, no prefix: 10*/

int ln_to_string _PROTO((L_NUMBER *argument, char **result, int base));
/* Supported bases are 8,10,16 */

void uint_to_char _PROTO((unsigned int argument, char *result));

/***********************************************************************************************
/*                                  sint_to_ln()
/***********************************************************************************************/
/* transform a positive signed int into a L_NUMBER, return (-1) if the signed int is not positive,
    0 otherwise */
int sint_to_ln _PROTO((const signed long int arg, L_NUMBER *res));



/************************************************************************************************/

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

/***************************************EOF*****************************************************/
/***************************************EOF*****************************************************/
/***************************************EOF*****************************************************/
