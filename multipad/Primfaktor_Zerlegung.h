// Primfaktor_Zerlegung.h: Schnittstelle für die Klasse Primfaktor_Zerlegung.
//
//////////////////////////////////////////////////////////////////////
#include "..\LIBMIRACL\INCLUDE\BIG.H"	// Hinzugefügt von der Klassenansicht
#include <big.h>
#include <monty.h>
#include <iostream.h>
#include <iomanip.h>




#if !defined(AFX_PRIMFAKTOR_ZERLEGUNG_H__2F4A1B71_13B1_11D5_889F_00062919F268__INCLUDED_)
#define AFX_PRIMFAKTOR_ZERLEGUNG_H__2F4A1B71_13B1_11D5_889F_00062919F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define LIMIT1 10000     /* must be int, and > MULT/2 */
#define LIMIT2 1000000L  /* may be long */
#define LIMIT3 2000000L  /*may be long */
#define MULT   2310      /* must be int, product of small primes 2.3... */
#define NEXT   13           /* next small prime */
#define NCURVES 20      /* number of curves to try */

#define LIMIT4 500000L  // may be long : für williams-Verfahren
#define NTRYS  3        // number of attempts : für Williams-Verfahren

#define SSIZE 1000000     // Maximum sieve size        Für QSieve

#define min(a,b) ((a) < (b)? (a) : (b))

#define TIMES '*'
#define RAISE '^'

struct PrimListe
	{
		Big prime[100];
		int exp[100];
		int lastprime;
		void reset()
		{ for (int i=0; i<100; i++) prime[i] = 0; }
	}; 

	struct CoFaktorListe
	{
		Big CoFaktor[100];
		int lastcofaktor;
		void reset()
		{ for (int i=0; i<100; i++) CoFaktor[i] = 0; }
	}; 

class Primfaktor_Zerlegung  
{
public:// Für QSieve notwendige Variablen
	int lp;
	Big *ww;
	Big *zz;
	Big *yy;
	Big *xx;
	int *pr;
	int nbts;
	int *e;
	Big VV;
	Big IG;
	Big PP;
	Big BB;
	Big AA;
	int *r2;
	int *r1;
	unsigned char *logp;
	unsigned char *sieve;
	Big DG;
	Big RR;
	int nlp;
	int jj;
	int *epr;
	Big DD;
	int *rp;
	int mmm;
	int *hash;
	int hmod2;
	Big TT;
	int mlf;
	int hmod;
	Big NN;
	int *bb; //roger
	unsigned int **G;
	unsigned int **EE;
	bool partial;

	// Ende QSieve relevante Variablen

	void new_poly(); //QSieve
	bool factored (long lptr, Big& T);//QSieve
	bool gotcha (Big& NN, Big& P);//QSieve
	int knuth(int mm, int *epr, Big& N, Big& D);//QSieve
	int initv();//QSieve
	int QSieve (CString Eingabe);//QSieve
	int exp2;
	CoFaktorListe CFL;
	PrimListe PL;
	int Williams (CString Eingabe);
	int giant_step_williams();
	void next_phase_williams();
	void marks_williams (long start);
//	void new_poly();
//	bool factored(long lptr,Big& T);
//	bool gotcha(Big& NN,Big& P);
//	int initv();
//	int knuth(int mm,int *epr,Big& N,Big& D);
//	int QSieve (CString Eingabe);
	void marks_pollard (long start);
	int giant_step_pollard();
	void next_phase_pollard();
	int Pollard(CString Eingabe);
	int brute(CString Eingabe);
	int brent(CString Eingabe);
//	void SetIOBASE(int);
	int lenstra_fakt(CString Eingabe);
	int giant_step();
	void next_phase();
	void ellipse(ZZn x,ZZn z,int r,ZZn& x1,ZZn& z1,ZZn& x2,ZZn& z2);
	void addition(ZZn xd,ZZn zd,ZZn sm1,ZZn df1,ZZn sm2,ZZn df2,ZZn& x,ZZn& z);
	void duplication(ZZn sum,ZZn diff,ZZn& x,ZZn& z);
	void marks (long start);

	char line[256];
	char* s;


	Big temp;

	ZZn fd,fp,fn;
	ZZn b,bw,bvw,bd,qq,bu[1+MULT/2]; // Für Pollard
	ZZn ak,q,x,z,x1,z1,x2,z2,xt,zt,fvw,fu[1+MULT/2];
	BOOL cp[1+MULT/2],plus[1+MULT/2],minus[1+MULT/2];

	int iv;
	long p;
	
	Primfaktor_Zerlegung();
	virtual ~Primfaktor_Zerlegung();
private:

	miracl *mip;
};

#endif // !defined(AFX_PRIMFAKTOR_ZERLEGUNG_H__2F4A1B71_13B1_11D5_889F_00062919F268__INCLUDED_)
