/* This files  version number is v0*/


/*

s_ecmath.c  -- Various mathematical functions which are needed in the package.


*/

/* Bartol Filipovic,Deutsche Bank AG(IT Security)
   and Anna-Barbara Berger, Secude GmbH , 1999 */



#include "arithmet.h"
#include "s_ecmath.h"
#include "s_bithdl.h"
#include "s_prng.h"
#include "ECsecude.h"

/*************************************************************************************************/
/*                                      _mod_div2()
/*************************************************************************************************/
/*tested, 26.3.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
void _mod_div2(L_NUMBER *d, L_NUMBER *n, L_NUMBER *p)
#else
void _mod_div2(d,  n, p)
         L_NUMBER *d;
         L_NUMBER *n; 
         L_NUMBER *p;
#endif         
{

	if ( _get_last_bit(n) == 0 )
	{
		/* n is even */
		SECUDE(shift)(n,-1,d); /*d=n/2 (mod p) */
	}
	else
	{
		/* n is odd ==> n + p is even */ 
		SECUDE(add)(n, p, d); /* d = n + p */
		SECUDE(shift)(d,-1,d); /* d = (n+p)/2 (mod p) */
	}
}

/*************************************************************************************************/
/*                                         _lucas_seq()
/*************************************************************************************************/
/*tested, 26.3.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
void _lucas_seq(L_NUMBER *U, L_NUMBER *V, L_NUMBER *k,L_NUMBER *P, L_NUMBER *Q, L_NUMBER *p) /* Attn. p is not P */
#else
void _lucas_seq(U, V, k, P, Q, p)  /* Attn. p is not P */
         L_NUMBER *U;
         L_NUMBER *V;
         L_NUMBER *k;
         L_NUMBER *P;
         L_NUMBER *Q;
         L_NUMBER *p;
#endif
{
	unsigned long int r;
	long int i;
	
	L_NUMBER delta[MAXLGTH];
	L_NUMBER temp[MAXLGTH];
	L_NUMBER temp2[MAXLGTH];

	SECUDE(mmult)(P, P, delta, p);
	inttoln(4,temp);
	SECUDE(mmult)(temp, Q, temp, p);
	SECUDE(msub)(delta, temp, delta, p); /*delta=P^2-4Q (mod p)*/
 
	r = SECUDE(lngtouse)(k); 

	inttoln(1, U);
	trans(P, V);

	for ( i=r-1 ; i >= 0 ; i-- )
	{
		SECUDE(mmult)( U, V, temp2, p ); /* temp2 = U*V (mod p) */

		SECUDE(mmult)(V, V, V, p);
		SECUDE(mmult)(U, U, temp, p);
		SECUDE(mmult)(temp, delta, temp, p);
		SECUDE(madd)(V, temp, V, p);
		_mod_div2(V, V, p); /* V = (V^2 + delta * U^2) / 2 (mod p) */

		trans(temp2, U); /* U = U*V (mod p) */

		if ( _get_ith_bit(k, i) == 1 )
		{
			SECUDE(mmult)(P, U, temp, p);
			SECUDE(madd)(temp, V, temp, p);
			_mod_div2(temp, temp, p); /* temp = (P*U + V)/2 mod p */ 
            
			SECUDE(mmult)(V, P, V, p);
			SECUDE(mmult)(delta, U, temp2, p);
			SECUDE(madd)(V, temp2, V,p);
			_mod_div2(V, V, p); /* V = (P*V + delta*U) / 2 (mod p) */

			trans(temp, U); /* U = (P*U + V)/2 mod p */
		}
	}
}

/*************************************************************************************************/
/*                                       _mod_congruent()
/*************************************************************************************************/
/*tested, 29.3.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
int _mod_congruent(L_NUMBER *k, L_NUMBER *p, const unsigned long int j, const unsigned long int r)
#else
int _mod_congruent(k, p,  j,  r)
         L_NUMBER *k;
         L_NUMBER *p;
         const unsigned long int j;
         const unsigned long int r;
#endif
{
	/* calculate k such that:  p = j*k + r */

	L_NUMBER temp[MAXLGTH];
	L_NUMBER quot[MAXLGTH];
	L_NUMBER rem[MAXLGTH];
	L_NUMBER help[MAXLGTH];

	inttoln(r,temp);
	SECUDE(sub)(p, temp, temp); /* temp = p - r */
	inttoln(j,help);
	SECUDE(div)(temp, help, quot, rem);
	
	/*   quot = [temp/j]            */
	/*   rem = temp - [temp/j] * j  */
	if ( rem[0] == 0 )
	{
		/*  j | (p-r)  */

		trans(quot, k);
		return 1; /* p = r (mod j) <==> there exists a k such that:  p = j*k + r */
	}

	/*  not( j | (p-r) )  */
	return 0;  /* p != r (mod j) <==> there is no  k such that:  p = j*k + r */
}

/*************************************************************************************************/
/*                                          _mod_sqrt()
/*************************************************************************************************/

#if defined (__STDC__) || defined (__cplusplus)
int _mod_sqrt(L_NUMBER *z, L_NUMBER *g, L_NUMBER *p)
#else
int _mod_sqrt( z, g , p)
         L_NUMBER *z;
         L_NUMBER *g;
         L_NUMBER *p;
#endif
{
        L_NUMBER k[MAXLGTH];
        L_NUMBER help[MAXLGTH];
        L_NUMBER help1[MAXLGTH];

        trans(g, help);
        
        if ( _mod_congruent(k, p, 4, 3) )
        {
                /* p = 3 (mod 4) */
                
                inttoln(1,help1);
                SECUDE(add)(k, help1 , k);
                SECUDE(mexp)(help, k, z, p);
				
                SECUDE(mmult)(z,z,k,p); /* Is z really a square root of g?*/                 
                if ( SECUDE(comp)(k,help) == 0 ) return 1;  /* z is a square root modulo p */                
                else return 0; /* There is no solution */                
        }

        if ( _mod_congruent(k, p, 8, 5) )
        {
                /* p = 5 (mod 8) */

                L_NUMBER gamma[MAXLGTH];
                L_NUMBER i[MAXLGTH];
                L_NUMBER temp[MAXLGTH];
                
                inttoln(2,temp);
                SECUDE(mmult)(g, temp, gamma, p);
                SECUDE(mexp)(gamma, k, gamma, p);   /* gamma = (2*g)^k (mod p) */

                SECUDE(mmult)(g, temp, i, p);
                SECUDE(mmult)(gamma, gamma, temp, p); /* temp = gamma^2 (mod p) */
                SECUDE(mmult)(i, temp, i, p);  /* i = 2*g*(gamma^2) (mod p) */
                inttoln(1, temp);
                SECUDE(sub)(i, temp, i);
                SECUDE(mmult)(g, gamma, z, p);
                SECUDE(mmult)(z, i, z, p); /* z = g*gamma*(i-1) (mod p) */
                
                SECUDE(mmult)(z,z,k,p);   /* Is z really a square root of g?*/
                if ( SECUDE(comp)(k,help) == 0 ) return 1; /* z is a square root modulo p */                
                else return 0;  /* There is no solution */
        }

        if ( _mod_congruent(k, p, 4, 1) )
        {
                /* p = 1 (mod 4) */

                L_NUMBER U[MAXLGTH];
                L_NUMBER V[MAXLGTH];
                L_NUMBER Q[MAXLGTH];
                L_NUMBER P[MAXLGTH];
                L_NUMBER temp[MAXLGTH],temp1[MAXLGTH];
                
                int not_finished=1;
                
                trans(g,Q);
                
                while (not_finished)
                {
                	 inttoln(0, P);
                	 while ( P[0]==0) 
                	 {
                	 	_rand_int(P, p);  /* choose a random integer 0<P<p */
                	 }
                	 inttoln(2,temp);
                	 SECUDE(mult)(temp, k, temp);
                	 inttoln(1,temp1);
                	 SECUDE(add)(temp, temp1, temp); /*temp=2k+1*/
                	 
                	 _lucas_seq(U, V, temp, P, Q, p);
                	 
                	 if ( U[0] == 0 )
                	 {
                	 	_mod_div2(z, V, p); /* z^2 = g (mod p) */
                	 	return 1; /* z is a square root modulo p */
                	 }
                	 
                	 if ( V[0] == 0 ) return 0; /* No square roots exist */
                }
        }

		return 0; /* this return is not really needed */
}

/*************************************************************************************************/
/*                                      _log2_z()
/*************************************************************************************************/
/*tested, 29.3.99, ABB*/
#if defined (__STDC__) || defined (__cplusplus)
int _log2_z(L_NUMBER *n)
#else
int _log2_z(n)
        L_NUMBER *n;
#endif
{
	int i;
	L_NUMBER z[MAXLGTH];

	inttoln(1, z);
	i = 0;
   
	do
	{
		SECUDE(shift)(z,1,z);  
		i++;
	}
	while (SECUDE(comp)(z,n) <= 0);

	return i;
}
/*************************************************EOF*********************************************/