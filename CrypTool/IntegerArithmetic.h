/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


// CryptologyUsingMiracl.h: Schnittstelle f�r die Klasse evaluate.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_)
#define AFX_CRYPTOLOGYUSINGMIRACL_H__7EFC6C40_6316_11D5_BB4A_000777640932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define __DEVELOP_CRYPTOOL

extern volatile long ExitFactorisationCode;

#include "BIG.H"	// Hinzugef�gt von der Klassenansicht
#include <monty.h>
#include "ChrTools.h"


#define MAX_8BIT_LENGTH 256
#define MAX_BIT_LENGTH  1024

#define EVAL_ERR_OPERATOR_INVALID 6
#define EVAL_ERR_NUMBER_INVALID 5
#define EVAL_ERR_STR_NUMBER  4
#define EVAL_ERR_POW 1
#define EVAL_ERR_MUL 2
#define EVAL_ERR_SUM 3
#define EVAL_ERR 0
#define EVAL_NEG 1
#define EVAL_NULL 2
#define EVAL_EINS 3
#define EVAL_OK 4
#define ERROR_SPEICHER 7


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


/* Mark Santiago --- Signatur-Demo */
#define ERR_P_NOT_PRIME			1
#define ERR_Q_NOT_PRIME			2
#define ERR_E_TO_BIG			4
#define ERR_P_EQUALS_Q			8
#define ERR_P_TO_BIG			16
#define ERR_Q_TO_BIG			32

#define ERR_MAX_BIT_LENGTH		64
#define ERR_P_LESS_THAN_TWO		128
#define ERR_Q_LESS_THAN_TWO		256
#define ERR_PQ_NOT_PRIME		512

#define ERR_ON_MODUL_N			1024
#define ERR_ON_PUBLIC_KEY		2048
#define ERR_ON_INITIALIZE_E		4096

/***********************************/


////////////////////////////////////////////////////////////////////////////////
//
// diese defines in eine globale HeaderDatei unterbringen
//
#define VALID_FORMULA "0..9^+-*/()"
#define NUMBER_SEPARATOR " \r\n#,;:"
#define SEPARATOR     " # "

BOOL GetNumber( CString &number, CString &Formula, int base, int &ndx );
BOOL CheckFormula(CString &Formula, int base, CString &UpnFormula, int &ndx);
BOOL EvalFormula(CString &CStrExpr, int &ndx, BOOL EvalNumber = FALSE);
double BitLength(CString &number, int base = 10);
int  IsNumberStream( CString &CStr, int numberBase, CString Modul, int flagList = 0 );
BOOL IsHexDump( CString &CStr );
BOOL CStringFormulaToBig(CString &CStrNumber, Big &t);
int  StringToBig( const char* StrNumber, Big &t, int base );
int  CStringToBig( CString &CStrNumber, Big &t, int base );
int  decode( const char *StrNumber, char *data, int blockLength, int numberBase, BOOL basisSystem, const char *CPlayfairAlphabet );
int  decode( CString &CStringNumber, char *data, int blockLength, int numberBase, BOOL BasisSystem, const char *CPlayfairAlphabet );
void encode( const char *data, char *numStr, int blockLength, int numberBase, BOOL basisSystem, const char *CPlayfairAlphabet );
void encode( const char *data, CString &numCStr, int blockLength, int numberBase, BOOL basisSystem, const char *CPlayfairAlphabet );
void BigToString (const Big &t, char *   NumStr,  int base = BASE_DEC, size_t OutLength = 0);
void BigToCString(const Big &t, CString &NumCStr, int base = BASE_DEC, size_t OutLength = 0);
void RandRepr( CString &StrNum,         int Modul, int numberBase, int randInterval = 20, int ofs = 0 ); 
void RandRepr( CString &StrNum, CString StrModul, int numberBase, int randInterval = 20, int ofs = 0 );
void ModRepr ( CString &StrNum, CString StrModul, int numberBase, int ofs = 0 ); 
void ModRepr ( CString &StrNum, int        Modul, int numberBase, int ofs = 0 ); 
void BaseRepr( CString &StrNum, int baseFrom, int baseTo); 
bool IsDecimalNumber(CString expression);

class eval_err { // CEvalIntExpr errror class
	int err;
public:
	eval_err(int e) { err = e; }
	int get() { return err; }
};

class evaluate  
{
public:
	static BOOL CEvalIntExpr( Big& value, const char * Str );

private:
	static BOOL CEvalIntExpr();
	static void eval_product(Big &oldn, Big &n, char op);
	static void eval_sum(Big &oldn, Big &n, char op);
	static void eval_power(Big& oldn, Big& n, char op);
};

#define GP_ERROR_EVAL 0
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
	int SetLimits( CString &LowerLimitStr, CString &UpperLimitStr );

	BOOL SetLimits( const Big &LowerLimit, const Big&UpperLimit ); 
	BOOL GetPrime( Big& prime );
	void SetP( Big &Number );
};


//////////////////////////////////////////////////////////////////////////////////

class CRSADemo  
{
protected: //private: // ge�ndert f�r abgeleitete Klasse CPSEDemo
	Big phiOfN;
	Big d;
	BOOL isInitialized_N, isInitialized_d, isInitialized_e;
//protected: // ge�ndert f�r abgeleitete Klasse CPSEDemo
	Big N;
	Big e;

public:
	CRSADemo();
	virtual ~CRSADemo();
	int  GetBlockLength();
	double GetLog2RSAModul();

// Public and private key Parameter
	int  InitParameter( CString &pStr, CString &qStr, int base = 10 );
	int  SetPublicKey ( CString &eStr, int base = 10 );
	BOOL SetPrivateKey();	
	BOOL GetParameter( CString &NStr, CString &phiOfNStr, CString &eStr, CString &dStr, int base = 10 );
	BOOL GetParameter( Big	&NBig, Big &phiOfNBig, Big &eBig, Big &dBig );

	BOOL IsInitialized()
		{	return  ( isInitialized_N && isInitialized_e && isInitialized_d ); }

// Only public key parameter ...
	BOOL IsInitializedPublicParameter()
		{	return ( isInitialized_N && isInitialized_e ); }
	int  SetPublicParameter( CString &NStr, CString &eStr );
	BOOL GetPublicParameter( CString &NStr, CString &eStr );

	BOOL Encrypt( CString &Plaintext,  CString &Ciphertext, int base = 10, BOOL DlgOfSisters = FALSE);
	BOOL Decrypt( CString &Ciphertext, CString &Plaintext,  int base = 10, BOOL DlgOfSisters = FALSE);
	BOOL PreCheckInput( CString &Input, int base = 10, BOOL DlgOfSisters = FALSE );

protected: //private: // ge�ndert f�r abgeleitete Klasse CPSEDemo
	int InitParameter( Big &p, Big &q );
	int SetPublicKey ( Big &e );
private:
	int  Encrypt( Big &PlaintextBlock,  Big &CiphertextBlock );
	int  Decrypt( Big &CiphertextBlock, Big &PlaintextBlock );
};


class CTutorialFactorisationBase  
{
public:
	miracl *m_old_mip;
	miracl *mip;
	CTutorialFactorisationBase();
	virtual ~CTutorialFactorisationBase();

};


class CTutorialFactorisation : public CTutorialFactorisationBase
{
	Big N;
	Big factor1;
	Big factor2;
public:
	int status;
	int m_iterations;
	CTutorialFactorisation(int ordinal, CString name);
	int bitlength() { return bits(N); }
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

	// Variablen f�r Pollard und Williams
	long p;
	int iv;
	ZZn b,bw,bvw,bd,q,bu[1+MULT/2];//Pollard
	ZZn fvw, fd, fp, fn, fu[1+MULT/2]; //Williams
	BOOL cp[1+MULT/2],plus[1+MULT/2],minus[1+MULT/2];
	ZZn ak, x, y, z, x1,x2, z1, z2, xt, zt;
	
	//Variablen f�r QSieve

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
	int SetN( CString &NStr );
	BOOL BruteForce();
	BOOL QuadraticSieve();
	BOOL Lenstra();
	BOOL Williams();
	BOOL Pollard();
	BOOL Brent();
	CTutorialFactorisation();
	virtual ~CTutorialFactorisation();
//	miracl *mip;
private:
	BOOL Precheck();
};



class CRandomGenerator  
{
protected:
	Big Seed;
	Big RandNo;

public:
	virtual void randomize() = 0;
	BOOL setSeed( CString &SeetStr );
	CRandomGenerator();
	virtual ~CRandomGenerator();
	virtual long     randBit() = 0;

};

/////////////////////////////////////////////////////////////////////////////
// Standardparameter

#define STANDARD_X2MOD_N_MODUL "245438302030331732360701189397045881523"
#define STANDARD_X2MOD_N_MODUL_BIG 245438302030331732360701189397045881523

class CX2ModNGenerator : public CRandomGenerator  
{
	Big Modul_N;
public:
	void randomize();
	BOOL setModul( CString &NStr );
	CX2ModNGenerator();
	virtual ~CX2ModNGenerator();
	long     randBit();
};


class LinearCongruenceGenerator : public CRandomGenerator  
{
	Big a, b, N;
public:
	void randomize();
	BOOL SetParameter( CString &aStr, CString &bStr, CString &NStr );
	LinearCongruenceGenerator();
	virtual ~LinearCongruenceGenerator();
	long     randBit();
};


class InverseCongruenceGenerator : public CRandomGenerator  
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
