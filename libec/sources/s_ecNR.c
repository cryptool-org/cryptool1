/*This files version is v0.4*/
/*last change, 17.3.2000, Bartol Filipovic*/


/* s_ecNR.c	-- Definitions for the Elliptc Curve Signature and Verification Primitives, NR version
				IEEE1363 7.2.5 and 7.2.6

			1999 Anna-Barbara Berger, Secude GmbH
			Corrections by Bartol Filipovic - Aug. 1999, March 2000


*/


#include "arithmet.h"
#include "s_ecFp.h"
#include "s_prng.h"
#include "s_ecDSA.h"    /* for key generation */
#include "ECsecude.h"






/**********************************************************************************************************************
/* ECSP-NR(IEEE 1363, 7.2.5) for prime fields	(affine coordinates)				ecFp_ecsp_nr_ac()
/**********************************************************************************************************************/
#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecsp_nr_ac(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r, L_NUMBER *f)
#else
int ecFp_ecsp_nr_ac(c,d,s,E,G,r,f)   /* 0<=f<r */
	L_NUMBER *c, *d;
	L_NUMBER *s, *r, *f;
	ecFp_curve_srcptr E;
	ecFp_point_ac_srcptr G;	
#endif
{
	int not_sufficient=1;
	L_NUMBER u[MAXLGTH], i[MAXLGTH];
	ecFp_point_ac_t V;
	unsigned int k;

	V=ecFp_point_init_ac;
	if (V==NULL) return (-1); /*point allocation error*/
	V->infinity = 0; /* OK ? */

	while (not_sufficient){	
		ecFp_generate_key_ac(u, V, E, G, r);
		trans(V->x, i);
		SECUDE(madd)(i,f,c,r);
		if (c[0]!= 0) not_sufficient=0;
	}
	SECUDE(mmult)(s,c,d,r);
	SECUDE(msub)(u,d,d,r);
	for (k=1; k<=u[0]; u[k]=0,k++);  /*delete any trace of (u,V)*/
	u[0]=0;
	for (k=1; k<=V->x[0]; V->x[0]=0, k++);
	V->x[0]=0;
	for (k=1; k<=V->y[0]; V->y[0]=0, k++);
	V->y[0]=0;	
	ecFp_point_clear_ac(V);
	return 0;
}



/**********************************************************************************************************************
/* ECSP-NR(IEEE 1363, 7.2.5) for prime fields	(projective coordinates)				ecFp_ecsp_nr_pc()
/**********************************************************************************************************************/
#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecsp_nr_pc(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G, L_NUMBER *r, L_NUMBER *f)
#else
int ecFp_ecsp_nr_pc(c,d,s,E,G,r,f)   /* 0<=f<r */
	L_NUMBER *c, *d;
	L_NUMBER *s, *r, *f;
	ecFp_curve_srcptr E;
	ecFp_point_pc_srcptr G;	
#endif
{
	int not_sufficient=1;
	L_NUMBER u[MAXLGTH], i[MAXLGTH];
	ecFp_point_pc_t V;
	ecFp_point_ac_t V_ac;
	unsigned int k;

	V=ecFp_point_init_pc;
	if (V==NULL) return (-1); /*point allocation error*/
	V_ac=ecFp_point_init_ac;
	if (V_ac==NULL)
	{
		ecFp_point_clear_pc(V);
		return (-1); /*point allocation error*/
	}
	V->infinity = 0; /* OK ? */

	while (not_sufficient){	
		ecFp_generate_key_pc(u, V, E, G, r);
		ecFp_point_pc_to_ac(V_ac,V,E);
		trans(V_ac->x, i);
		SECUDE(madd)(i,f,c,r);
		if (c[0]!= 0) not_sufficient=0;
	}
	SECUDE(mmult)(s,c,d,r);
	SECUDE(msub)(u,d,d,r);
	for (k=1; k<=u[0]; u[k]=0,k++);  /*delete any trace of (u,V)*/
	u[0]=0;
	for (k=1; k<=V->x[0]; V->x[0]=0, k++);
	V->x[0]=0;
	for (k=1; k<=V->y[0]; V->y[0]=0, k++);
	V->y[0]=0;	
	ecFp_point_clear_pc(V);
	for (k=1; k<=V_ac->x[0]; V_ac->x[0]=0, k++);
	V_ac->x[0]=0;
	for (k=1; k<=V_ac->y[0]; V_ac->y[0]=0, k++);
	V_ac->y[0]=0;
	ecFp_point_clear_ac(V_ac);
	return 0;
}


/****************************************************************************************************
/* functions for extracting the hash value out of an NR-signature
/***************************************************************************************************/

/*********************************************************************************************************************
/* ECVP-NR (IEEE 1363, 7.2.6) for prime fields		(affine coordinates)			ecFp_ecvp_nr_ac()
/**********************************************************************************************************************/

#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecvp_nr_ac(L_NUMBER *c, L_NUMBER *d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r, L_NUMBER *f)
#else
int ecFp_ecvp_nr_ac(c,d,W,E,G,r,f)
	L_NUMBER *c,*d,*r;
	L_NUMBER *f;
	ecFp_curve_srcptr E;
	ecFp_point_ac_srcptr W,G;
	
#endif
{
	L_NUMBER h[MAXLGTH];
	ecFp_point_ac_destptr P,temp_point;
	L_NUMBER one[MAXLGTH];
	L_NUMBER zero[MAXLGTH];
	inttoln(1,one);
	inttoln(0,zero);

	if (c[0]==0) return 1; /*invalid signature*/
	if (d[0]==0) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(c,one)) < 0 ) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(c,r)) >= 0) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(d,zero)) < 0 ) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(d,r)) >= 0) return 1; /*invalid signature*/

	P=ecFp_point_init_ac;
	if (P==NULL) return (-1);/*point allocation error*/
	temp_point=ecFp_point_init_ac;
	if (temp_point==NULL)
	{
		ecFp_point_clear_ac(P);
		return -1; /*point allocation error*/
	}

	P->infinity = 0;
	temp_point->infinity = 0;

	ecFp_mult_ac(P,  E,  d,  G);
	ecFp_mult_ac(temp_point,  E,  c,  W);
	ecFp_add_ac(P, E, P, temp_point);
	if ((P->infinity)!=0){
		ecFp_point_clear_ac(P);
		ecFp_point_clear_ac(temp_point);
		return 1; /*invalid signature*/
	}
	trans(P->x,h);
	SECUDE(msub)(c,h,f,r);
	ecFp_point_clear_ac(P);
	ecFp_point_clear_ac(temp_point);
	return 0;  
	/* compare f to the hash value of the message to find out if
	   the signature is valid*/
}


/*********************************************************************************************************************
/* ECVP-NR (IEEE 1363, 7.2.6) for prime fields		(projective coordinates)			ecFp_ecvp_nr_pc()
/**********************************************************************************************************************/

#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecvp_nr_pc(L_NUMBER *c, L_NUMBER *d, ecFp_point_pc_srcptr W, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G,L_NUMBER *r, L_NUMBER *f)
#else
int ecFp_ecvp_nr_pc(c,d,W,E,G,r,f)
	L_NUMBER *c,*d,*r;
	L_NUMBER *f;
	ecFp_curve_srcptr E;
	ecFp_point_pc_srcptr W,G;
	
#endif
{
	L_NUMBER h[MAXLGTH];
	ecFp_point_pc_destptr P,temp_point;
	ecFp_point_ac_t P_ac;
	L_NUMBER one[MAXLGTH];
	L_NUMBER zero[MAXLGTH];
	inttoln(1,one);
	inttoln(0,zero);

	if (c[0]==0) return 1; /*invalid signature*/
	if (d[0]==0) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(c,one)) < 0 ) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(c,r)) >= 0) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(d,zero)) < 0 ) return 1; /*invalid signature*/
	if ( (SECUDE(comp)(d,r)) >= 0) return 1; /*invalid signature*/

	P=ecFp_point_init_pc;
	if (P==NULL) return (-1);/*point allocation error*/
	P_ac=ecFp_point_init_ac;
	if (P_ac==NULL)
	{
		ecFp_point_clear_pc(P);
		return (-1);/*point allocation error*/
	}
	temp_point=ecFp_point_init_pc;
	if (temp_point==NULL)
	{
		ecFp_point_clear_pc(P);
		ecFp_point_clear_ac(P_ac);
		return (-1); /*point allocation error*/
	}

	P->infinity = 0;
	temp_point->infinity = 0;

	ecFp_mult_pc(P,  E,  d,  G);
	ecFp_mult_pc(temp_point,  E,  c,  W);
	ecFp_add_pc(P, E, P, temp_point);
	if ((P->infinity)!=0){
		ecFp_point_clear_pc(P);
		ecFp_point_clear_ac(P_ac);
		ecFp_point_clear_pc(temp_point);
		return 1; /*invalid signature*/
	}
	ecFp_point_pc_to_ac(P_ac,P,E);
	trans(P_ac->x,h);
	SECUDE(msub)(c,h,f,r);
	ecFp_point_clear_pc(P);
	ecFp_point_clear_ac(P_ac);
	ecFp_point_clear_pc(temp_point);
	return 0;  
	/* compare f to the hash value of the message to find out if
	   the signature is valid*/
}



/********************************************** EOF ****************************************************/