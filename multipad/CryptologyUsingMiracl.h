// CryptologyUsingMiracl.h: Schnittstelle für die Klasse evaluate.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BIG.H"	// Hinzugefügt von der Klassenansicht

#define TIMES '*'
#define RAISE '^'
#define LIMIT1 10000

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
public:
	void GetFactor2Str( CString &Factor2 );
	void GetFactor1Str( CString &Factor1 );
	void SetN( CString &NStr );
	BOOL BruteForce();
	BOOL QuadraticSieve();
	BOOL Lenstra();
	BOOL Williams();
	BOOL Pollard();
	BOOL Brent();
	TutorialFactorisation();
	virtual ~TutorialFactorisation();
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
	long     randBit();

};


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

#endif // !defined(AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_)
