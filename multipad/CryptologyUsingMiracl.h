// CryptologyUsingMiracl.h: Schnittstelle für die Klasse evaluate.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern long ExitFactorisationCode;



#include "BIG.H"	// Hinzugefügt von der Klassenansicht
#include <monty.h>

#define TIMES '*'
#define RAISE '^'
#define BTRIES 1000
#define LIMIT1 10000   /* must be int, and > MULT/2 */
#define LIMIT2 2000000L /* may be long */
#define MULT   2310     /* must be int, product of small primes 2.3.. */
#define NEXT   13           /* next small prime */
#define NTRYS  3         /* number for attempts */
#define NCURVES 20      /* number of curves to try */
#define SSIZE 1000000     /* Maximum sieve size            */

BOOL CStringFormulaToBig(CString &CStrNumber, Big &t);
void CStringToBig(CString &CStrNumber, Big &t, int base );
void CStringToASCII( CString &CStringNumber, CString &ASCIIStr, int base );
void CStringToAlphabet( CString &CStringNumber, CString &AlphabetStr, CString &Alphabet, int base );
void AlphabetToNumStr(const char *in, CString &NumStr, int len, CString &Alphabet, int OutBase );

void BigToCString(const Big &t, CString &CStrNumber, int base = 10);
void CharToNumStr(const char *in, CString &NumStr, int len, int OutBase = 10, int Inbase = 256);
 
class evaluate  
{
public:
	static BOOL eval( Big& value, const char * Str );

private:
	static BOOL eval();
	static void eval_product(Big &oldn, Big &n, char op);
	static void eval_sum(Big &oldn, Big &n, char op);
	static void eval_power(Big& oldn, Big& n, char op);
};

#define GP_ERROR_LIMIT 1
#define GP_ERROR_NOPRIME 2

class GeneratePrimes  
{
	int Error;
	Big p;
	Big upperBound;
	Big lowerBound;
public:
	BOOL IsBlumNumber();
	BOOL RandP();
	void SetP( CString &NumberStr );
	BOOL GetPrime( CString &primeStr );
	BOOL FermatTest        ( unsigned long probabilityThreshold = 20 );
	BOOL MillerRabinTest   ( unsigned long probabilityThreshold = 20 );
	BOOL SolvayStrassenTest( unsigned long probabilityThreshold = 20 );
	GeneratePrimes();
	virtual ~GeneratePrimes();
	int Bitlength() { return bits(p); }
	BOOL SetLimits( CString &LowerLimitStr, CString &UpperLimitStr );

	BOOL SetLimits( const Big &LowerLimit, const Big&UpperLimit ); 
	BOOL GetPrime( Big& prime );
	void SetP( Big &Number );
};


class TutorialRSA  
{
	Big phiOfN;
	Big d;
	BOOL isInitialized_N, isInitialized_d, isInitialized_e;
protected:
	Big N;
	Big e;

public:
	TutorialRSA();
	virtual ~TutorialRSA();
	BOOL InitParameter( CString &pStr, CString &qStr, int base = 10 );
	BOOL SetPublicKey ( CString &eStr, int base = 10 );
	BOOL SetPrivateKey();
	int  GetBlockLength();
	BOOL GetParameter( CString &NStr, CString &phiOfNStr, CString &eStr, CString &dStr, int base = 10 );

	BOOL IsInitialized()
		{	return  ( isInitialized_N && isInitialized_e && isInitialized_d ); }
	void Encrypt( CString &Plaintext,  CString &Ciphertext, int base = 10);
	void EncryptAlphabet( CString &Plaintext,  CString &Ciphertext, CString &Alphabet, int base);
	void Decrypt( CString &Ciphertext, CString &Plaintext,  int base = 10);
	void DecryptAlphabet( CString &Plaintext,  CString &Ciphertext, CString &Alphabet, int base);
	BOOL CheckInput( CString &Input, int base, int base2 = 0 );

private:
	BOOL SetPublicKey ( Big &e );
	BOOL InitParameter( Big &p, Big &q );
	BOOL Encrypt( Big &PlaintextBlock,  Big &CiphertextBlock );
	BOOL Decrypt( Big &CiphertextBlock, Big &PlaintextBlock );
};

class TutorialFactorisation  
{
	Big N;
	Big factor1;
	Big factor2;
	bool isFactorized;
public:
	bool isItFactorized() { return isFactorized; }
	bool gotcha(Big& NN, Big& P);
	bool factored(long lptr, Big& T);
	void new_poly();
	int knuth(int mmm, int *epr, Big& N, Big& D);
	int initv();
	int giant_step_lenstra();
	void next_phase_lenstra();
	void ellipse(ZZn x,ZZn z,int r,ZZn& x1,ZZn& z1,ZZn& x2,ZZn& z2);
	void addition(ZZn xd,ZZn zd,ZZn sm1,ZZn df1,ZZn sm2,ZZn df2,ZZn& x,ZZn& z);
	void duplication(ZZn sum, ZZn diff, ZZn& x, ZZn& z);
	int giant_step_williams();
	void next_phase_williams();
	int giant_step_pollard();
	void next_phase_pollard();

	// Variablen für Pollard und Williams
	long p;
	int iv;
	ZZn b,bw,bvw,bd,q,bu[1+MULT/2];//Pollard
	ZZn fvw, fd, fp, fn, fu[1+MULT/2]; //Williams
	BOOL cp[1+MULT/2],plus[1+MULT/2],minus[1+MULT/2];
	ZZn ak, x, y, z, x1,x2, z1, z2, xt, zt;
	
	//Variablen für QSieve

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

	//Methoden
	void marks(long start);
	static BOOL IsPrime( CString & Num );
	void GetFactor2Str( CString &Factor2 );
	void GetFactor1Str( CString &Factor1 );
	//void SetN( CString &NStr );
	bool SetN( CString &NStr );
	BOOL BruteForce();
	BOOL QuadraticSieve();
	BOOL Lenstra();
	BOOL Williams();
	BOOL Pollard();
	BOOL Brent();
	TutorialFactorisation();
	virtual ~TutorialFactorisation();
private:
	miracl *mip;
	BOOL Precheck();
};



class PseudoRandomGenerator  
{
protected:
	Big Seed;
	Big RandNo;

public:
	virtual void randomize() = 0;
	BOOL setSeed( CString &SeetStr );
	PseudoRandomGenerator();
	virtual ~PseudoRandomGenerator();
	long     randBit();

};

/////////////////////////////////////////////////////////////////////////////
// Standardparameter

#define STANDARD_X2MOD_N_MODUL "245438302030331732360701189397045881523"


class x2modN_generator : public PseudoRandomGenerator  
{
	Big Modul_N;
public:
	void randomize();
	BOOL setModul( CString &NStr );
	x2modN_generator();
	virtual ~x2modN_generator();
};


class LinearCongruenceGenerator : public PseudoRandomGenerator  
{
	Big a, b, N;
public:
	void randomize();
	BOOL SetParameter( CString &aStr, CString &bStr, CString &NStr );
	LinearCongruenceGenerator();
	virtual ~LinearCongruenceGenerator();
};


class InverseCongruenceGenerator : public PseudoRandomGenerator  
{
	Big a, b, N;
	long count;
public:
	void randomize();
	BOOL SetCount( long n );
	BOOL SetParameter( CString &aStr, CString &bStr, CString &NStr );
	InverseCongruenceGenerator();
	virtual ~InverseCongruenceGenerator();

};

#endif // !defined(AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_)
