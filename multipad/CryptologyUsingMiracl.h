// CryptologyUsingMiracl.h: Schnittstelle für die Klasse evaluate.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern volatile long ExitFactorisationCode;



#include "BIG.H"	// Hinzugefügt von der Klassenansicht
#include <monty.h>

#define BASE_BIN 2
#define BASE_OCT 8
#define BASE_DEC 10
#define BASE_HEX 16

#define MAX_8BIT_LENGTH 256
#define MAX_BIT_LENGTH  2048


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

#define INCREASE_THE_BASE     1
#define SPLIT_NUMBERS_VSMODUL 2
#define SPLIT_NUMBERS_VSFLOOR 4
#define FORMAT_MODULO         8

////////////////////////////////////////////////////////////////////////////////
// Nur temporär  definiert
// 

////////////////////////////////////////////////////////////////////////////////
//
// diese defines in eine globale HeaderDatei unterbringen
//
#define IDS_STRINGLENGTH 256
#define VALID_FORMULA "0..9^+-*/()"
#define VALID_BIN     "01"
#define VALID_OCT     "0..7"
#define VALID_DEC     "0..9"
#define VALID_HEX     "0..9a..fA..F"
#define WHITESPACE    " \t\r\n"
#define NUMBER_SEPARATOR " \r\n#,;:"
#define SEPARATOR     " # "

BOOL isCharOf( const char ch, const char *expr );
BOOL Whitespace( char ch );
BOOL IsNumber( char ch, int base );
int  NeededBase( char ch );
char DigitToNum( char ch );
int  IsNumberStream( CString &CStr, int numberBase, CString Modul, int flagList = 0 );
BOOL IsHexDump( CString &CStr );
char ToHex( const char ch );
void dataToHexDump( const char* data, int len, char* hexDump );
void dataToHexDump( const char* data, int len, CString& hexDump );
int  HexDumpToData( const char *hexDump, char *data );
int  HexDumpToData( CString &hexDump, char *data );

BOOL CStringFormulaToBig(CString &CStrNumber, Big &t);
int  StringToBig( const char* StrNumber, Big &t, int base );
int  CStringToBig( CString &CStrNumber, Big &t, int base );
int  decode( const char *StrNumber, char *data, int blockLength, int numberBase, BOOL basisSystem, const char *alphabet );
int  decode( CString &CStringNumber, char *data, int blockLength, int numberBase, BOOL BasisSystem, const char *alphabet );
void encode( const char *data, char *numStr, int blockLength, int numberBase, BOOL basisSystem, const char *alphabet );
void encode( const char *data, CString &numCStr, int blockLength, int numberBase, BOOL basisSystem, const char *alphabet );
void BigToString (const Big &t, char *   NumStr,  int base = BASE_DEC, int OutLength = 0);
void BigToCString(const Big &t, CString &NumCStr, int base = BASE_DEC, int OutLength = 0);
void RandRepr( CString &StrNum,         int Modul, int numberBase, int randInterval = 20, int ofs = 0 ); 
void RandRepr( CString &StrNum, CString StrModul, int numberBase, int randInterval = 20, int ofs = 0 );
void ModRepr ( CString &StrNum, CString StrModul, int numberBase, int ofs = 0 ); 
void ModRepr ( CString &StrNum, int        Modul, int numberBase, int ofs = 0 ); 

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


//////////////////////////////////////////////////////////////////////////////////
#define ERR_P_NOT_PRIME 1
#define ERR_Q_NOT_PRIME 2
#define ERR_P_EQUALS_Q  4

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
	int  InitParameter( CString &pStr, CString &qStr, int base = 10 );
	BOOL SetPublicKey ( CString &eStr, int base = 10 );
	BOOL SetPrivateKey();
	int  GetBlockLength();
	double GetLog2RSAModul();
	BOOL GetParameter( CString &NStr, CString &phiOfNStr, CString &eStr, CString &dStr, int base = 10 );

	BOOL IsInitialized()
		{	return  ( isInitialized_N && isInitialized_e && isInitialized_d ); }
	void Encrypt( CString &Plaintext,  CString &Ciphertext, int base = 10, BOOL DlgOfSisters = FALSE);
	void Decrypt( CString &Ciphertext, CString &Plaintext,  int base = 10, BOOL DlgOfSisters = FALSE);

private:
	BOOL SetPublicKey ( Big &e );
	BOOL InitParameter( Big &p, Big &q );
	BOOL Encrypt( Big &PlaintextBlock,  Big &CiphertextBlock );
	BOOL Decrypt( Big &CiphertextBlock, Big &PlaintextBlock );
};


class CTutorialFactorisationBase  
{
public:
	miracl *m_old_mip;
	miracl *mip;
	CTutorialFactorisationBase();
	virtual ~CTutorialFactorisationBase();

};


class TutorialFactorisation : public CTutorialFactorisationBase
{
	Big N;
	Big factor1;
	Big factor2;
public:
	int status;
	int m_iterations;
	TutorialFactorisation(int ordinal, CString name);
	CWinThread *m_Thread;
	CString m_Name;
	int m_Ordinal;
	bool factorized;
private:
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
public:
//	static BOOL IsPrime( CString & Num );
	BOOL IsPrime( CString & Num );
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
//	miracl *mip;
private:
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
	virtual long     randBit() = 0;

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
	long     randBit();
};


class LinearCongruenceGenerator : public PseudoRandomGenerator  
{
	Big a, b, N;
public:
	void randomize();
	BOOL SetParameter( CString &aStr, CString &bStr, CString &NStr );
	LinearCongruenceGenerator();
	virtual ~LinearCongruenceGenerator();
	long     randBit();
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
	long     randBit();
};

#endif // !defined(AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_)
