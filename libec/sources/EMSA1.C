/* This files version is v0.1 */
/* last change 20.03.2000, BF */

/* April 1999 - Bartol Filipovic - Deutsche Bank AG, IT Security*/
/* Copyright Bartol Filipovic and Deutsche Bank AG */

#include <string.h>
#include <math.h>
#include "arithmet.h"
#include "s_ecconv.h"
#include "s_bithdl.h"
#include "emsa1.h"
#include "pkcs.h"
#include "ECsecude.h"


/***************************************************************************************/

int emsa1_encoding_operation(/*out*/ L_NUMBER *f,
                             /*in */ OctetString *M,
                                     unsigned int l,
                                     char *hash_id) /* "SHA-1" or "RIPEMD-160" */
{	
	/* I do not check if the length of M is greater than the length
	   limitation: 2^(61)-1 octets for SHA-1 or RIPEMD-160. I assume 
	   that the length of M is not that big.
	*/
	
	int n;
	int higher_bits;
	unsigned char bitmask = 255;
	
	BitString bitstr_hash;
	
	OctetString hash;
	hash.noctets = 0;
		
	hash.octets = (char*)malloc(20+1); /* 160-bits (20 bytes) */
	if (!hash.octets) return (-1); /* error: memory allocation failed */ 

	if (strcmp(hash_id, "SHA-1") == 0)
	{
		SECUDE(sec_hash_all)(M, &hash, SECUDE_DATA_PTR(sha1_aid), NULL);
	}
	else if (strcmp(hash_id, "RIPEMD-160") == 0)
	{
		SECUDE(sec_hash_all)(M, &hash, SECUDE_DATA_PTR(ripemd160_aid), NULL);
	}
	else 
	{
		free (hash.octets);
		return (-2); /* error: the selected Hash Algorithm is not supported */
	}
		
	if (l < (8*hash.noctets))
	{
		bitstr_hash = *(SECUDE(aux_OString2BString)(&hash));

		/* The 160-bits (20 bytes) representing Hash(M) are stored in the char-field:
		   bitstr_hash.bits[0], bitstr_hash.bits[0], ..., bitstr_hash.bits[20]
		   where bitstr_hash.bits[20] = NULL is the string-termination.
		   bitstr_hash.bits[0] is the char containing the most significant byte */
		
		/* Keep the l most significant bits (MSB) of Hash(M) = hash */

		n = (int) ceil(l/8.0); /* the first n char's of bitstr_bits* contain the l MSB's */
		bitstr_hash.bits[n] = (char) NULL; /* cut off the rest */

		/* if n < 20 :
		   I don't free the memory occupied by bitstr_hash.bits[n+1] ... bitstr_hash.bits[20] */

		higher_bits = l%8; /* keep the (l mod 8) higher bits of bitstr_hash.bits[n-1], that means:       */
		if (higher_bits)   /* set the 8-(l mod 8) less significant bits in bitstr_hash.bits[n-1] to zero */
			(bitstr_hash.bits[n-1] = bitstr_hash.bits[n-1] & (bitmask << ((unsigned char) 8-(higher_bits))));
		bitstr_hash.nbits = l; /* bitstr_hash contains now l bits */

		SECUDE(aux_BitString2LN2)(f, &bitstr_hash); /* f is the message representative */
		return 0;
	}
	else
	{
		/* convert the octet hash into the L_NUMBER f */

		//if (string_to_ln(strcat("0", hash.octets), f)) return (-2); /* if error then return -2 */
		SECUDE(aux_OctetString2LN2)(f, &hash); /* f is the message representative */
		return 0;
	}
}

/*****************************************************************************************/

int emsa1_verfication_operation(/* in */ L_NUMBER *f,
					 OctetString *M,
					 unsigned int l,
					 char *hash_id) /* "SHA-1" or "RIPEMD-160" */
{
	L_NUMBER g[MAXLGTH];

	if (emsa1_encoding_operation(g, M, l, hash_id)) return (-1); /* error executing emsa1_encoding_operation */
	if (SECUDE(comp)(g, f) == 0) return 0; /* f is a correct representative of M */
	return -2; /* f is an invalid representative of M */

}

/*****************************************************************************************/


/****************************************** EOF *********************************************/