/* This files version is v0.2 */
/* Signature Schemes, this follows IEEE P1363 Draft 8, Section 10.2.1 */

/* May 1999, March 2000 - Bartol Filipovic - Deutsche Bank AG, IT Security*/
/* Copyright Bartol Filipovic and Deutsche Bank AG */

#include <string.h>
#include "s_ecFp.h"
#include "ecssa.h"
#include "s_bithdl.h"
#include "emsa1.h"
#include "s_ecNR.h"
#include "s_ecDSA.h"
#include "arithmet.h"
#include "ECsecude.h"


/******************************************************************************************************/


int ecssa_sign_gen_op_ac(/*out*/ L_NUMBER *c, L_NUMBER *d,
			/*in */ OctetString *M,
				EcDomParam_ac_ptr Key,
				char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				char *hash_id) /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */
{   
	unsigned int l;
	L_NUMBER f[MAXLGTH];

	/* select signature primitiv */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		l = SECUDE(lngtouse)(Key->r); /* l = (length of r in bits)-1 */
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		l = SECUDE(lngtouse)(Key->r)+1; /* l = (length of r in bits) */
	}

	if (emsa1_encoding_operation(f, M, l, hash_id)) return (-1); /* error */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		return ecFp_ecsp_nr_ac(c, d, Key->privKey, Key->E, Key->G, Key->r, f);
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		return ecFp_ecsp_dsa_ac(c, d, Key->privKey, Key->E, Key->G, Key->r, f);
	}

	return (-5); /* error: function doesn't anything */
}

/******************************************************************************************************/

int ecssa_sign_gen_op_pc(/*out*/ L_NUMBER *c, L_NUMBER *d,
			/*in */ OctetString *M,
				EcDomParam_pc_ptr Key,
				char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				char *hash_id) /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */
{   
	unsigned int l;
	L_NUMBER f[MAXLGTH];

	/* select signature primitiv */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		l = SECUDE(lngtouse)(Key->r); /* l = (length of r in bits)-1 */
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		l = SECUDE(lngtouse)(Key->r)+1; /* l = (length of r in bits) */
	}

	if (emsa1_encoding_operation(f, M, l, hash_id)) return (-1); /* error */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		return ecFp_ecsp_nr_pc(c, d, Key->privKey, Key->E, Key->G, Key->r, f);
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		return ecFp_ecsp_dsa_pc(c, d, Key->privKey, Key->E, Key->G, Key->r, f);
	}

	return (-5); /* error: function doesn't anything */
}

/******************************************************************************************************/

// validate_pub_key_dompar_ac(Key)

/******************************************************************************************************/

int ecssa_sign_verif_op_ac( /* in */ L_NUMBER *c,
				     L_NUMBER *d,
				     OctetString *M,
				     EcDomParam_ac_ptr Key,
				     char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				     char *hash_id) /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */
{
	unsigned int l;
	L_NUMBER f[MAXLGTH];

	/*if (validate_pub_key_dompar_ac(Key)) return 1;*/ /* validation of public key and its associated set of domain
											parameters failed! */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		if (ecFp_ecvp_nr_ac(c, d, Key->pubKey, Key->E, Key->G, Key->r, f)) return -3; /* error */
		l = SECUDE(lngtouse)(Key->r); /* l = (length of r in bits)-1 */
        return emsa1_verfication_operation(f,M,l,hash_id);
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		l = SECUDE(lngtouse)(Key->r)+1; /* l = (length of r in bits) */
		if (emsa1_encoding_operation(f, M, l, hash_id)) return -4; // calculate f
		// delete this: if (emsa1_verfication_operation(f,M,l,hash_id)) return -5; /* error */
		return ecFp_ecvp_dsa_ac(c, d, Key->pubKey, Key->E, Key->G, Key->r, f);
	}

	return (-5); /* error: function doesn't anything */
}

/******************************************************************************************************/

int ecssa_sign_verif_op_pc( /* in */ L_NUMBER *c,
				     L_NUMBER *d,
				     OctetString *M,
				     EcDomParam_pc_ptr Key,
				     char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
				     char *hash_id) /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */
{
	unsigned int l;
	L_NUMBER f[MAXLGTH];

	/*if (validate_pub_key_dompar_ac(Key)) return 1;*/ /* validation of public key and its associated set of domain
											parameters failed! */

	if (strcmp(sign_primitiv_id, "ECSP-NR") == 0){
		if (ecFp_ecvp_nr_pc(c, d, Key->pubKey, Key->E, Key->G, Key->r, f)) return -3; /* error */
		l = SECUDE(lngtouse)(Key->r); /* l = (length of r in bits)-1 */
        return emsa1_verfication_operation(f,M,l,hash_id);
	}

	if (strcmp(sign_primitiv_id, "ECSP-DSA") == 0){
		l = SECUDE(lngtouse)(Key->r)+1; /* l = (length of r in bits) */
		if (emsa1_encoding_operation(f, M, l, hash_id)) return -4; // calculate f
		// delete this: if (emsa1_verfication_operation(f,M,l,hash_id)) return -5; /* error */
		return ecFp_ecvp_dsa_pc(c, d, Key->pubKey, Key->E, Key->G, Key->r, f);
	}

	return (-5); /* error: function doesn't anything */
}

/************************************************ EOF *************************************************/
/************************************************ EOF *************************************************/
/************************************************ EOF *************************************************/
