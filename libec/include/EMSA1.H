/* This files version is v0 */
/* Message Encoding Methods - This follows IEEE P1363 Draft 8, Section 12.1.1 */

/* April 1999 - Bartol Filipovic - Deutsche Bank AG, IT Security */
/* Copyright Bartol Filipovic and Deutsche Bank AG */

/*****************************************************************************************/

int emsa1_encoding_operation(/* out */ L_NUMBER *f,
			     /* in  */ OctetString *M,
				       unsigned int l,
				       char *hash_id);

int emsa1_verfication_operation(/* in  */ L_NUMBER *f,
					OctetString *M,
					unsigned int l,
					char *hash_id);

/**************************************** EOF ********************************************/
