/* This files version is v0.3*/
/*last change, 17.3.2000, Bartol Filipovic*/


/* s_ecDSA.c	--	Definitions for the Elliptc Curve Signature and Verification Primitives, DSA version
				IEEE1363 7.2.7 and 7.2.8

				1999 Anna-Barbara Berger, Secude GmbH
				Corrections by Bartol Filipovic March 2000


*/


#include "arithmet.h"
#include "s_ecFp.h"
#include "s_prng.h"
#include "s_ecDSA.h"
#include "ECsecude.h"


/**********************************************************************************************************************
/*    Function to generate a key pair	(private key, public key)  ecFp_generate_key_ac()
/**********************************************************************************************************************/
#if defined(__STDC__) || defined (__cplusplus)
void ecFp_generate_key_ac(L_NUMBER *private_key, ecFp_point_ac_destptr public_key, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r) 
#else
void ecFp_generate_key_ac(private_key, public_key,E,G,r)
	L_NUMBER *private_key;
	L_NUMBER *r;
	ecFp_curve_srcptr E;
	ecFp_point_ac_srcptr G;
	ecFp_point_ac_destptr public_key;
#endif
{	
	private_key[0]=0;
	while (private_key[0]==0){
		_rand_int(private_key, r);
	}
	ecFp_mult_ac(public_key,  E,  private_key,  G);
}


/**********************************************************************************************************************
/*    Function to generate a key pair	(private key, public key)  ecFp_generate_key_pc()
/**********************************************************************************************************************/
#if defined(__STDC__) || defined (__cplusplus)
void ecFp_generate_key_pc(L_NUMBER *private_key, ecFp_point_pc_destptr public_key, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G,L_NUMBER *r) 
#else
void ecFp_generate_key_pc(private_key, public_key,E,G,r)
	L_NUMBER *private_key;
	L_NUMBER *r;
	ecFp_curve_srcptr E;
	ecFp_point_pc_srcptr G;
	ecFp_point_pc_destptr public_key;
#endif
{	
	private_key[0]=0;
	while (private_key[0]==0){
		_rand_int(private_key, r);
	}
	ecFp_mult_pc(public_key,  E,  private_key,  G);
}



/**********************************************************************************************************************
/* ECSP-DSA (IEEE 1363, 7.2.7) for prime fields				ecFp_ecsp_dsa_ac()
/**********************************************************************************************************************/
#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecsp_dsa_ac(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r, L_NUMBER *f)
#else
int ecFp_ecsp_dsa_ac(c,d,s,E,G,r,f)
	L_NUMBER *c,*d;
	L_NUMBER *s,*r,*f;
	ecFp_curve_srcptr E;
	ecFp_point_ac_srcptr G;	
#endif
{
	L_NUMBER  u[MAXLGTH],i[MAXLGTH], temp[MAXLGTH];
	ecFp_point_ac_t V;
	int no_result=1;
	unsigned int k;

	V=ecFp_point_init_ac;
	if (V==NULL) return (-1); /*point allocation error*/
	while (no_result)
	{
		ecFp_generate_key_ac(u, V, E, G, r);
		trans(V->x, i); 
		SECUDE(div)(i,r,temp,c); /*c=i mod r*/
		if ( c[0]!=0 ) no_result=0;
		if ( !(no_result) ){
			SECUDE(mmult)(s,c,d,r);
			SECUDE(madd)(d,f,d,r);
			inttoln(1,temp);
			SECUDE(mdiv)(temp,u,temp,r); /* temp = 1/u (mod r)*/
			SECUDE(mmult)(d,temp,d,r); /*=u^(-1)(f+sc) mod r*/
			if ( d[0]!=0) no_result=0;
			else no_result=1;
		}
	}
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
/* ECSP-DSA (IEEE 1363, 7.2.7) for prime fields (projective coordinates)				ecFp_ecsp_dsa_pc()
/**********************************************************************************************************************/
#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecsp_dsa_pc(L_NUMBER *c, L_NUMBER *d, L_NUMBER *s, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G, L_NUMBER *r, L_NUMBER *f)
#else
int ecFp_ecsp_dsa_pc(c,d,s,E,G,r,f)
	L_NUMBER *c,*d;
	L_NUMBER *s,*r,*f;
	ecFp_curve_srcptr E;
	ecFp_point_pc_srcptr G;	
#endif
{
	L_NUMBER  u[MAXLGTH],i[MAXLGTH], temp[MAXLGTH];
	ecFp_point_pc_t V;
	ecFp_point_ac_t V_ac;
	int no_result=1;
	unsigned int k;

	V=ecFp_point_init_pc;
	if (V==NULL) return (-1); /*point allocation error*/
	V_ac=ecFp_point_init_ac;
	if (V_ac==NULL)
	{
		ecFp_point_clear_pc(V);
		return (-1); /*point allocation error*/
	}
	while (no_result)
	{
		ecFp_generate_key_pc(u, V, E, G, r);
		ecFp_point_pc_to_ac(V_ac,V,E);
		trans(V_ac->x, i); 
		SECUDE(div)(i,r,temp,c); /*c=i mod r*/
		if ( c[0]!=0 ) no_result=0;
		if ( !(no_result) ){
			SECUDE(mmult)(s,c,d,r);
			SECUDE(madd)(d,f,d,r);
			inttoln(1,temp);
			SECUDE(mdiv)(temp,u,temp,r); /* temp = 1/u (mod r)*/
			SECUDE(mmult)(d,temp,d,r); /*=u^(-1)(f+sc) mod r*/
			if ( d[0]!=0) no_result=0;
			else no_result=1;
		}
	}
	for (k=1; k<=u[0]; u[k]=0,k++);  /*delete any trace of (u,V)*/
	u[0]=0;
	for (k=1; k<=V->x[0]; V->x[0]=0, k++);
	V->x[0]=0;
	for (k=1; k<=V->y[0]; V->y[0]=0, k++);
	V->y[0]=0;
	for (k=1; k<=V->z[0]; V->z[0]=0, k++);
	V->z[0]=0;
	ecFp_point_clear_pc(V);
	for (k=1; k<=V_ac->x[0]; V_ac->x[0]=0, k++);
	V_ac->x[0]=0;
	for (k=1; k<=V_ac->y[0]; V_ac->y[0]=0, k++);
	V_ac->y[0]=0;
	ecFp_point_clear_ac(V_ac);
	return 0;
}


/**********************************************************************************************************************
/* ECVP-DSA (IEEE 1363, 7.2.8)	for prime fields			ecFp_ecvp_dsa_ac()
/**********************************************************************************************************************/
/*last change, 30.3.99,*/
#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecvp_dsa_ac( L_NUMBER *c, L_NUMBER *d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r,L_NUMBER *f)
#else
int ecFp_ecvp_dsa_ac(c,d,W,E,G,r,f)
	L_NUMBER *c,*d,*r,*f;
	ecFp_curve_srcptr E;
	ecFp_point_ac_srcptr W,G;	
#endif
{
	L_NUMBER h[MAXLGTH],h1[MAXLGTH],h2[MAXLGTH];
	ecFp_point_ac_destptr P, temp_point;

	if (c[0]== 0) return (-1); /*signature verification failed*/
	if (d[0]== 0) return (-1); /*signature verification failed*/
	if ( SECUDE(comp)(c,r) >= 0) return(-1); /*signature verification failed*/
	if ( SECUDE(comp)(d,r) >= 0) return (-1); /*signature verification failed*/
	P=ecFp_point_init_ac;
	if (P==NULL) return (-2); /*point allocation error*/
	temp_point=ecFp_point_init_ac;
	if (temp_point==NULL){
		ecFp_point_clear_ac(P);
		return (-2); /*point allocation error*/
	}
	inttoln(1,h1);
	SECUDE(mdiv)(h1,d,h,r);  /* h=1/d */
	SECUDE(mmult)(h,f,h1,r); /* h1=fh mod r */
	SECUDE(mmult)(h,c,h2,r); /* h2=ch mod r */
	ecFp_mult_ac(P,  E,  h1,  G);
	ecFp_mult_ac(temp_point,  E,  h2,  W);
	ecFp_add_ac(P, E, P, temp_point);
	if ((P->infinity)!=0){
		ecFp_point_clear_ac(P);
		ecFp_point_clear_ac(temp_point);
		return (-1); /*signature verification failed*/
	}
	SECUDE(div)(P->x,r,h1,h); /* h = P->x (mod r) */
	ecFp_point_clear_ac(P);
	ecFp_point_clear_ac(temp_point);
	if ( (SECUDE(comp)(c,h)) != 0 ) return (-1); /*signature verification failed*/
	else return 0;	/*signature verification successful*/
}	


/**********************************************************************************************************************
/* ECVP-DSA (IEEE 1363, 7.2.8)	for prime fields			ecFp_ecvp_dsa_pc()
/**********************************************************************************************************************/

#if defined(__STDC__) || defined (__cplusplus)
int ecFp_ecvp_dsa_pc( L_NUMBER *c, L_NUMBER *d, ecFp_point_pc_srcptr W, ecFp_curve_srcptr E, ecFp_point_pc_srcptr G, L_NUMBER *r,L_NUMBER *f)
#else
int ecFp_ecvp_dsa_pc(c,d,W,E,G,r,f)
	L_NUMBER *c,*d,*r,*f;
	ecFp_curve_srcptr E;
	ecFp_point_pc_srcptr W,G;	
#endif
{
	L_NUMBER h[MAXLGTH],h1[MAXLGTH],h2[MAXLGTH];
	ecFp_point_pc_destptr P, temp_point;
	ecFp_point_ac_destptr P_ac;

	if (c[0]== 0) return (-1); /*signature verification failed*/
	if (d[0]== 0) return (-1); /*signature verification failed*/
	if ( SECUDE(comp)(c,r) >= 0) return(-1); /*signature verification failed*/
	if ( SECUDE(comp)(d,r) >= 0) return (-1); /*signature verification failed*/
	P=ecFp_point_init_pc;
	if (P==NULL) return (-2); /*point allocation error*/
	temp_point=ecFp_point_init_pc;
	if (temp_point==NULL){
		ecFp_point_clear_pc(P);
		return (-2); /*point allocation error*/
	}
	inttoln(1,h1);
	SECUDE(mdiv)(h1,d,h,r);  /* h=1/d */
	SECUDE(mmult)(h,f,h1,r); /* h1=fh mod r */
	SECUDE(mmult)(h,c,h2,r); /* h2=ch mod r */
	ecFp_mult_pc(P,  E,  h1,  G);
	ecFp_mult_pc(temp_point,  E,  h2,  W);
	ecFp_add_pc(P, E, P, temp_point);
	if ((P->infinity)!=0){
		ecFp_point_clear_pc(P);
		ecFp_point_clear_pc(temp_point);
		return (-1); /*signature verification failed*/
	}
	P_ac=ecFp_point_init_ac;
	if (P_ac == NULL)
	{
		ecFp_point_clear_pc(P);
		ecFp_point_clear_pc(temp_point);
		return (-2); /*point allocation error*/
	}
	ecFp_point_pc_to_ac(P_ac,P,E);
	SECUDE(div)(P_ac->x,r,h1,h); /* h = P_ac->x (mod r) */
	ecFp_point_clear_pc(P);
	ecFp_point_clear_ac(P_ac);
	ecFp_point_clear_pc(temp_point);
	if ( (SECUDE(comp)(c,h)) != 0 ) return (-1); /*signature verification failed*/
	else return 0;	/*signature verification successful*/
}	





/*************************************************EOF***************************************************/