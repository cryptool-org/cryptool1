/* This files  version number is v0.2 */


/*

ecFp_point_convert.c -- Functions for converting points in affine coordinates to points in projectve coordinates and vice versa.

                        Bartol Filipovic, Deutsche Bank AG - IT Security, 1999-2000
						Copyright Bartol Filipovic and Deutsche Bank AG

*/

#include "arithmet.h"
#include "s_ecFp.h" /* header file for this sourcecode */
#include "ECsecude.h"

/*************************************************************************************************/
/*                                       ecFp_point_ac_to_pc ()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_ac_to_pc(ecFp_point_pc_destptr S, ecFp_point_ac_srcptr P)
#else
void ecFp_point_ac_to_pc (S,  P)
           ecFp_point_pc_destptr S;
           ecFp_point_ac_srcptr P;
#endif
{
	trans(P->x, S->x);
	trans(P->y, S->y);
	inttoln(1,S->z);

	S->infinity = P->infinity;
}

/*************************************************************************************************/
/*                                       ecFp_point_pc_to_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_point_pc_to_ac(ecFp_point_ac_destptr S, ecFp_point_pc_srcptr P, ecFp_curve_srcptr E)
#else
void ecFp_point_pc_to_ac( S,  P,  E)
            ecFp_point_ac_destptr S;
            ecFp_point_pc_srcptr P;
            ecFp_curve_srcptr E;
#endif
{
	L_NUMBER temp[MAXLGTH], z_inv[MAXLGTH];
	L_NUMBER one[2]={1,1};

	S->infinity = P->infinity;

	if (P->infinity) return;
	
	SECUDE(mdiv)(one, P->z, z_inv, E->p); /* z_inv = (P->z)^(-1) (mod E->p) */

	/* calculate affine x-coordinate */

	SECUDE(mmult)(z_inv,z_inv, temp, E->p);
	SECUDE(mmult)(P->x, temp, S->x, E->p); /*S->x= (P->x)/(P->z)^2 (mod E->p)*/

	/* calculate affine y-coordinate */

	SECUDE(mmult)(temp,z_inv, temp, E->p); /*temp= (P->z)^(-3) (mod E->p)*/
	SECUDE(mmult)(P->y, temp, S->y, E->p); /*S->y= (P->y)/(P->z)^3*/

}

/*************************************************************************************************/
/*                                       ecFp_DomParam_pc_to_ac()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_DomParam_pc_to_ac (EcDomParam_ac_ptr dp_ac, EcDomParam_pc_ptr dp_pc)
#else
void ecFp_DomParam_pc_to_ac (dp_ac, dp_pc)
	EcDomParam_ac_ptr dp_ac;
	EcDomParam_pc_ptr dp_pc;
#endif
{
	trans(dp_pc->r, dp_ac->r);
	trans(dp_pc->k, dp_ac->k);
	trans(dp_pc->privKey, dp_ac->privKey);

	trans(dp_pc->E->a, dp_ac->E->a);
	trans(dp_pc->E->b, dp_ac->E->b);
	trans(dp_pc->E->p, dp_ac->E->p);

	ecFp_point_pc_to_ac(dp_ac->G, dp_pc->G, dp_ac->E);
	ecFp_point_pc_to_ac(dp_ac->pubKey, dp_pc->pubKey, dp_ac->E);
}

/*************************************************************************************************/
/*                                       ecFp_DomParam_ac_to_pc()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
void ecFp_DomParam_ac_to_pc (EcDomParam_pc_ptr dp_pc, EcDomParam_ac_ptr dp_ac)
#else
void ecFp_DomParam_ac_to_pc (dp_pc, dp_ac)
	EcDomParam_pc_ptr dp_pc;
	EcDomParam_ac_ptr dp_ac;
#endif
{
	trans(dp_ac->r, dp_pc->r);
	trans(dp_ac->k, dp_pc->k);
	trans(dp_ac->privKey, dp_pc->privKey);

	trans(dp_ac->E->a, dp_pc->E->a);
	trans(dp_ac->E->b, dp_pc->E->b);
	trans(dp_ac->E->p, dp_pc->E->p);

	ecFp_point_ac_to_pc(dp_pc->G, dp_ac->G);
	ecFp_point_ac_to_pc(dp_pc->pubKey, dp_ac->pubKey);	
}

/********************************************** EOF **********************************************/