/* This files  version number is v0 */

/* s_ecvali.c		-- Functions for validating EC domain parameters ( so far only for prime fields)*/


/*Anna-Barbara Berger, Secude GmbH*/

#include "s_ecFp.h"
#include "arithmet.h"
#include "s_ecvali.h" /* header file for this sourcecode */
#include "s_bithdl.h"
#include "ECsecude.h"

/*************************************************************************************************/
/*
/*    Some functions for validating EC domain parameters
/*
/*************************************************************************************************/ 

/***********************************************************************************************/
/*				ecFp_is_point_on_curve_ac()
/***********************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int  ecFp_is_point_on_curve_ac( ecFp_point_ac_srcptr G, ecFp_curve_srcptr curve)
#else
int  ecFp_is_point_on_curve_ac(G, curve)
      ecFp_point_ac_srcptr G;
	  ecFp_curve_srcptr curve;
#endif            
{
	L_NUMBER temp[MAXLGTH], help[MAXLGTH];

	SECUDE(mmult)(G->x,G->x, temp,curve->p);
	SECUDE(mmult)(temp,G->x,temp,curve->p); /*temp=x^3 (mod p)*/
	SECUDE(mmult)(curve->a,G->x, help,curve->p);  /*help=ax (mod p)*/
	SECUDE(madd)(help,curve->b, help,curve->p); /*help = ax +b (mod p)*/
	SECUDE(madd)(temp,help, temp,curve->p); /* temp =x^3+ax+b (mod p)*/
	SECUDE(mmult)(G->y,G->y,help,curve->p); /* help = y^2 (mod p)*/
	if ( SECUDE(comp)(temp,help) ) return (-1);
	else return (0);
}

/*************************************************************************************************/
/*                                     ecFp_curve_param_check()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_curve_param_check (ecFp_curve_srcptr E) /* E must be initialized */
#else
int ecFp_curve_param_check (E)
         ecFp_curve_srcptr E;
#endif
{
	L_NUMBER temp1[MAXLGTH];
	L_NUMBER temp2[MAXLGTH];
	L_NUMBER temp3[MAXLGTH];
	
	SECUDE(mmult)(E->a, E->a, temp1, E->p);
	SECUDE(mmult)(E->a, temp1, temp1, E->p);/* temp1 = a^3 (mod p) */
	inttoln(4,temp2);
	SECUDE(mmult)(temp1, temp2, temp1, E->p); /* temp1 = 4*a^3 (mod p) */

	SECUDE(mmult)(E->b, E->b, temp2, E->p); /* temp2 = b^2 (mod p) */
	inttoln(27,temp3);
	SECUDE(mmult)(temp2, temp3, temp2, E->p); /* temp2 = 27*b^2 (mod p) */
	
	SECUDE(madd)(temp1, temp2, temp1, E->p); /* temp1 = 4*a^3 + 27*b^2 (mod p) */
	if (temp1[0] == 0) return(-1); /* error: 4*a^3 + 27*b^2 (mod p) = 0 , choose new parameters a and b for E */
	else return 0; /* 4*a^3 + 27*b^2 (mod p) != 0 , parameters are ok */	
}

/*************************************************************************************************/
/*                                                                          ecFp_mov_cond()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int ecFp_mov_cond(const unsigned int B, L_NUMBER *r, L_NUMBER *q)
#else
int ecFp_mov_cond(B, r, q)
        const unsigned int B;
        L_NUMBER *r;
        L_NUMBER *q;
#endif
{
	unsigned int i;
	L_NUMBER t[MAXLGTH], one[]={1,1};

	inttoln(1,t);

	for ( i=1 ; i<=B ; i++ )
	{
		SECUDE(mmult)(t, q, t, r); /* t = t * q (mod r) */
		if ( SECUDE(comp)(t,one) == 0 )	return (-1); 
			/* Elliptic Curve over GF(q) with a base point of order r is vulnerable */
			/* to the reduction attack of Menezes, Okamoto, Vanstone. */
	}
	return 0; 
	/* Elliptic Curve over GF(q) with a base point of order r is NOT */
	/* vulnerable to the reduction attack of Menezes, Okamoto, Vanstone. */
}


/**************************************************************************************************
/*																			ecFp_domainpar_valid()
/**************************************************************************************************/
/* Elliptic curve domain parameter validation over Fp following 5.1.1.2 of the X9.62-standard*/

#if defined (__STDC__) || defined (__cplusplus)
int  ecFp_domainpar_valid( ecFp_curve_srcptr curve, ecFp_point_ac_srcptr G, L_NUMBER *order)
#else
int  ecFp_domainpar_valid(curve, G, order)
       ecFp_curve_srcptr curve;
	   ecFp_point_ac_srcptr G;
	   L_NUMBER *order;
#endif                           
{
	const int MOV_threshold=25; /*according to X9.62 any number >20 is sufficient*/ 
	const int min_length=160; /*according to X9.62 the minimal length in bits for the order 
							   of the base point is 160*/
	L_NUMBER temp[MAXLGTH], zero[MAXLGTH], help[MAXLGTH];
	ecFp_point_ac_t  W;
	char *proc="ecFp_domainpar_verify";

	if ( _get_last_bit(curve->p)==0 ) return (-1); /*p is not odd=>invalid*/
	if ( rabinstest(curve->p)==-1 ) return (-1); /*p is not prime=>invalid*/
	
	inttoln(0,zero);
	if ( SECUDE(comp)(curve->a,zero)<0 ) return (-1);/*invalid*/
	if ( SECUDE(comp)(curve->b,zero)<0 ) return (-1);/*invalid*/
	if ( SECUDE(comp)(curve->a, curve->p)>=0 ) return (-1);/*invalid*/
	if ( SECUDE(comp)(curve->b, curve->p)>=0 ) return (-1);/*invalid*/


	if ( SECUDE(comp)(G->x,zero)<0 ){
		global_add_error(EINVALID, "G->x", CNULL, 0, proc);
		return(-1);/*invalid*/
	}
	if ( SECUDE(comp)(G->y,zero)<0 ){
		global_add_error(EINVALID, "G->y", CNULL, 0, proc);
		return(-1);/*invalid*/
	}
	if ( SECUDE(comp)(G->x, curve->p)>=0 ){
		global_add_error(EINVALID, "G->x", CNULL, 0, proc);
		return(-1);/*invalid*/
	}
	if ( SECUDE(comp)(G->y, curve->p)>=0 ){
		global_add_error(EINVALID, "G->y", CNULL, 0, proc);
		return(-1);/*invalid*/
	}
    if ( ecFp_curve_param_check(curve)<0 ){
		global_add_error(EINVALID, "curve_param_check", CNULL, 0, proc);
		return(-1);/*invalid*/
	}
	if ( ecFp_is_point_on_curve_ac(G,curve)< 0 ){
		global_add_error(EINVALID, "base not on curve", CNULL, 0, proc);
		return(-1);/*invalid*/
	};
	if ( rabinstest(order)<0 ){
		global_add_error(EINVALID, "order not prime", CNULL, 0, proc);
		return(-1);/*the order of the base point is not prime=>invalid*/
	} 
	if ( SECUDE(lngtouse)(order)<=min_length ){
		global_add_error(EINVALID, "order too small", CNULL, 0, proc);
		return(-1);/* the order of the base point is too small => invalid*/
	}
	inttoln(16, help);
	SECUDE(mult)(curve->p,help,temp); /*temp= (4sqrt(p))^2*/
	SECUDE(mult)(order,order,help); /*help= order^2*/
	if ( (SECUDE(comp)(temp,help)) >= 0 ){
		global_add_error(EINVALID, "order too small(2)", CNULL, 0, proc);
		return(-1);/* order<=4sqrt(p) => invalid*/
	} 

	W=ecFp_point_init_ac;
	if (!W){
		global_add_error(EMALLOC, "W", CNULL, 0, proc);
		return(-2);/*Memory allocation error*/
	}
	ecFp_mult_ac(W,curve,order,G);
	if ( W->infinity==0 ){
		global_add_error(EINVALID, "not order of G", CNULL, 0, proc);
		ecFp_point_clear_ac(W);
		return(-1);/*invalid*/
	}
	ecFp_point_clear_ac(W);

	/* the optional cofactor verification is not done */
	
	if ( ecFp_mov_cond(MOV_threshold, order, curve->p)==-1 ){
		global_add_error(EINVALID, "MOV condition violated", CNULL, 0, proc);
		return(-1);/*invalid*/
	}
	
	/*We test the anomalous condition by comparing the order of the base point  
	to the prime p. This is sufficient: if #E(Fp)=p then the order of the base
	point devides p. So it has to be equal to p as p is prime).*/
	if ( SECUDE(comp)(order,curve->p)==0 ){ 
		global_add_error(EINVALID, "anomalous curve", CNULL, 0, proc);
		ecFp_point_clear_ac(W);
		return(-1);/*invalid*/
	}
	
	return 0; /* The ECParameters are valid*/
}




/**************************************************************************************************
/*					ecFp_pubkey_valid()
/**************************************************************************************************/
/* Public key validation over Fp following 5.2.2 of the X9.62-standard*/

#if defined (__STDC__) || defined (__cplusplus)
int  ecFp_pubkey_valid( ecFp_point_ac_srcptr Pkey, ecFp_curve_srcptr curve, ecFp_point_ac_srcptr G, L_NUMBER *order)
#else
int  ecFp_pubkey_valid(Pkey,curve, G, order)
       ecFp_curve_srcptr curve;
	   ecFp_point_ac_srcptr Pkey,G;
	   L_NUMBER *order;
#endif                           
{	 
	ecFp_point_ac_t W;	

	if (Pkey->infinity!=0) return (-1); /*pubkey invalid*/
	if (SECUDE(comp)(Pkey->x, curve->p)>=0) return (-1); /*pubkey invalid*/
	if (SECUDE(comp)(Pkey->y, curve->p)>=0) return (-1); /*pubkey invalid*/
	if (ecFp_is_point_on_curve_ac(Pkey,curve)<0) return (-1); /*pubkey invalid*/
	W=ecFp_point_init_ac;
	ecFp_mult_ac(W,curve,order, Pkey);
	if ( W->infinity == 0 ){
		ecFp_point_clear_ac(W);
			return (-1); /*pubkey invalid*/
	}
	ecFp_point_clear_ac(W);
	return 0; /*pubkey valid*/
}


/********************************************** EOF **********************************************/