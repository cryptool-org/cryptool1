//////////////////////////////////////////////////////////////////////
// CryptologyUsingMiracl.cpp: Implementierung der Klasse evaluate.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CryptologyUsingMiracl.h"
#include <monty.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static Miracl g_precision=50;


BOOL CStringFormulaToBig( CString &CStrNumber, Big &t )
{
	t = 0;
	if ( false==evaluate::eval(t, CStrNumber.GetBuffer( CStrNumber.GetLength()+1 ) ) ) 
	{	
		t = 0;
		return false;
	}
	else 
	{
		return true;
	}
}

void CStringToBig( CString &CStrNumber, Big &t, int base )
{
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = base;
	t = CStrNumber.GetBuffer(CStrNumber.GetLength()+1);
	mip->IOBASE = oldBase;
}

void CStringToASCII( CString &CStringNumber, CString &ASCIIStr, int base )
{
	Big t;
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = base;
	t = CStringNumber.GetBuffer(CStringNumber.GetLength()+1);
	int len = bits(t)/8;
	if (bits(t) % 8) len++;
	if (0 == len)
	{
		ASCIIStr = "";
	}
	else
	{
		char asciiStr[256];
		asciiStr[len--] = 0;
		while ( t != 0 )
		{
			asciiStr[len--] = (char)(t % 256);
			t /= 256;
		}
		ASCIIStr = asciiStr;
	}
}

void CStringToAlphabet( CString &CStringNumber, CString &AlphabetStr, CString &Alphabet, int base )
{
	Big t;
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = base;
	t = CStringNumber.GetBuffer(CStringNumber.GetLength()+2);
	if ( t != 0 ) t = t-1;
	else          t = Alphabet.GetLength()-1;
	int i = t % Alphabet.GetLength();
	AlphabetStr = "";
	AlphabetStr.Insert( 0, Alphabet[i] );
/*
	AlphabetStr = "";
	int s = Alphabet.GetLength();
	if ( !bits(t))
	{
		AlphabetStr = "";
	}
	else
	{
		while ( 0 != t )
		{
			if ( t % s )
				AlphabetStr.Insert(0, Alphabet[(int)(t%s)]);
			// else
			// 	AlphabetStr.Insert(0,'#');
			t = t/s;
		}
	}
*/
}

void BigToCString(const Big &t, CString &CStrNumber, int base)
{
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = base;
	CStrNumber.GetBuffer(500) << t;
	mip->IOBASE = oldBase;
}


void CharToNumStr(const char *in, CString &NumStr, int len, int OutBase, int InBase)
{
	Big tmp = 0;
	for (int i=0; i<len && in[i] != 0; i++ )
	{
		tmp *= InBase;
		tmp = tmp + (unsigned char)in[i];
	}
	BigToCString( tmp, NumStr, OutBase );
}

void AlphabetToNumStr(const char *in, CString &NumStr, int len, CString &Alphabet, int OutBase )
{
	Big tmp = 0;
	int modulo = Alphabet.GetLength();

	int j = 0;	
	while ( j < modulo && in[0] != Alphabet[j] ) j++;
	if ( j < modulo )
	{
		tmp = j +1 + (rand() % 32)*modulo;
	}
	BigToCString( tmp, NumStr, OutBase );
}


//////////////////////////////////////////////////////////////////////
// Private Funktionen
//////////////////////////////////////////////////////////////////////
void RandomWithLimits(Big &r, const Big &lower, const Big &upper)
{
	r=lower;
	if ( upper > lower )
		r=rand(upper-(lower+1))+(lower-1);
}

//////////////////////////////////////////////////////////////////////
// EVALUATE
//////////////////////////////////////////////////////////////////////
static char *s;
static Big  temp;

BOOL evaluate::eval( Big& value, const char * Str )
{
	miracl *mip = &g_precision;
	mip->IOBASE=10;
    s = (char*)Str;
	if ( eval() ) {
		value = temp;
		return TRUE;
	}
	value = 0;
	return FALSE;
}

void evaluate::eval_power(Big &oldn, Big &n, char op)
{
	if (op) n=pow(oldn,toint(n));    // power(oldn,size(n),n,n);
}

void evaluate::eval_sum(Big &oldn, Big &n, char op)
{
	switch (op)
        {
        case '+':
                n+=oldn;
                break;
        case '-':
                n=oldn-n;
		}
}

void evaluate::eval_product(Big &oldn, Big &n, char op)
{
	switch (op)
        {
        case TIMES:
                n*=oldn; 
                break;
        case '/':
                n=oldn/n;
                break;
        case '%':
                n=oldn%n;
        }
}

BOOL evaluate::eval()
{
	Big oldn[3];
    Big n;
    int i;
    char oldop[3];
    char op;
    char minus;
    for (i=0;i<3;i++)
    {
        oldop[i]=0;
    }
LOOP:
    while (*s==' ')
		s++;
    if (*s=='-')    /* Unary minus */
		{
		s++;
		minus=1;
		}
    else
	    minus=0;
    while (*s==' ')
		s++;
    if (*s=='(' || *s=='[' || *s=='{')    /* Number is subexpression */
		{
		s++;
		eval ();
		n=temp;
		}
    else            /* Number is decimal value */
    {
	
    for (i=0;s[i]>='0' && s[i]<='9';i++)
           ;
		if (!i)         /* No digits found */
		{
//				Error - invalid number
				return(false);
		}
		op=s[i];
		s[i]=0;
		n=s;

		s+=i;
		*s=op;
	}
    if (minus) n=-n;
    do
		op=*s++;
		while (op==' ');
    if (op==0 || op==')' || op==']' || op=='}')
		{
		eval_power (oldn[2],n,oldop[2]);
		eval_product (oldn[1],n,oldop[1]);
		eval_sum (oldn[0],n,oldop[0]);
		temp=n;
		return(true);
		}
    else
    {
		if (op==RAISE)
			{
					eval_power (oldn[2],n,oldop[2]);
					oldn[2]=n;
					oldop[2]=RAISE;
			}
		else
		{
				if (op==TIMES || op=='/' || op=='%')
				{
				eval_power (oldn[2],n,oldop[2]);
				oldop[2]=0;
				eval_product (oldn[1],n,oldop[1]);
				oldn[1]=n;
				oldop[1]=op;
				}
				else
					{
					if (op=='+' || op=='-')
						{
								eval_power (oldn[2],n,oldop[2]);
								oldop[2]=0;
								eval_product (oldn[1],n,oldop[1]);
								oldop[1]=0;
								eval_sum (oldn[0],n,oldop[0]);
								oldn[0]=n;
								oldop[0]=op;
						}
					else    /* Error - invalid operator */
						{
//								Error - invalid operator
								return(false);
						}
					}
		}
	}
	goto LOOP;

}


//////////////////////////////////////////////////////////////////////
// GeneratePrimes Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

GeneratePrimes::GeneratePrimes()
{
	Error = GP_ERROR_NOPRIME;
	p = 0;
	lowerBound = 1;
	upperBound = 1000000;
}

GeneratePrimes::~GeneratePrimes()
{
}


BOOL GeneratePrimes::SetLimits(const Big &LowerLimit, const Big &UpperLimit )
{
	if ( UpperLimit < LowerLimit )
	{
		Error |= GP_ERROR_LIMIT;
	}
	else
	{	
		Error &= 0xFFFFFFFF ^ GP_ERROR_LIMIT;
	}
	lowerBound=LowerLimit;
	upperBound=UpperLimit;
	return ( 0 == (Error &= GP_ERROR_LIMIT) );
}

BOOL GeneratePrimes::SetLimits( CString &LowerLimitStr, CString &UpperLimitStr )
{
	Big UpperLimit, LowerLimit;
	evaluate::eval( LowerLimit, LowerLimitStr.GetBuffer( 256 ) );
	evaluate::eval( UpperLimit, UpperLimitStr.GetBuffer( 256 ) );

	return SetLimits( LowerLimit, UpperLimit );
}


/* 
BOOL TemplatePrimeNumberTest(unsigned long probabilityThreshold)
{
	if ( p <= 10 )
	{
		if ( 2 == p || 3 == p || 5 == p || 7 == p ) Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		else                                        Error |= GP_ERROR_NOPRIME;
	}
	else
	{
		Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
	
		// PrimeNumberTest coding .....

	}
	return ( Error &= GP_ERROR_NOPRIME );
}
*/


BOOL GeneratePrimes::SolvayStrassenTest(unsigned long probabilityThreshold)
{

	if ( p <= 10 )
	{
		if ( 2 == p || 3 == p || 5 == p || 7 == p ) Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		else                                        Error |= GP_ERROR_NOPRIME;
	}
	else
	{
		Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		Big a, r, r1, _s;

		for (unsigned long i=1; i<=probabilityThreshold; i++)
		{
			RandomWithLimits (a, (Big)2,(Big)(p-2));
			_s = jacobi(a,p);
			r = pow( a, (Big)((p-1)/2), p );
			if( (1!=r) && ((p-1)!=r) )
			{
				Error |= GP_ERROR_NOPRIME;
				break;
			}
			if(_s<0)
			{
				_s = p-1;
			}						
			if((_s%p)!=r)
			{
				Error |= GP_ERROR_NOPRIME;
				break;
			}
		}
	}
	return ( 0 == (Error &= GP_ERROR_NOPRIME) );
}


BOOL GeneratePrimes::MillerRabinTest(unsigned long probabilityThreshold)
{
	if ( p <= 40 )
	{
		if ( 2 == p || 3 == p  || 5 == p || 7 == p || 11 == p || 13 == p || 17 == p || 
			19 == p || 23 == p || 29 == p || 31 == p || 37 ==  p ) Error = (Error & 0xFFFFFFFF) ^ GP_ERROR_NOPRIME;
		else                                        Error |= GP_ERROR_NOPRIME;
	}
	else
	{
		Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		long i, v = 0;
		Big a, b, w = p-1;
		while(0==w%2)
		{
			v++;
			w/=2;
		}
		for(unsigned long j=1;j<=probabilityThreshold;)
		{
			RandomWithLimits (a,1,(p-1));
			b = pow(a, w, p );
			if((1==b)||((p-1)==b))
			{
				goto nextj;
			}
			for(i=1;i<=v-1;)
			{
				b = pow(b, (Big)2, p );
				if((p-1)==b)
				{
					goto nextj;
				}
				if(1==b)
				{
					Error |= GP_ERROR_NOPRIME;
					break;
				}
				i++;
			}
			Error |= GP_ERROR_NOPRIME;
			break;
			nextj: j++;
		}
	}
	return ( (0 == (Error &= GP_ERROR_NOPRIME)) );
}


BOOL GeneratePrimes::FermatTest(unsigned long probabilityThreshold)
{
	if ( p <= 10 )
	{
		if ( 2 == p || 3 == p || 5 == p || 7 == p ) Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		else                                        Error |= GP_ERROR_NOPRIME;
	}
	else
	{
		Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		Big a, r;
		for(unsigned long i=1;i<=probabilityThreshold;i++)
		{
			RandomWithLimits(a,2,p-2);
			r = pow(a, (Big)(p-1), p);
			if(1!=r)
			{
				Error |= GP_ERROR_NOPRIME;
				break;
			}
		}
	}
	return ( 0 == (Error &= GP_ERROR_NOPRIME) );
}

BOOL GeneratePrimes::GetPrime(Big &prime)
{
	if (! Error ) prime = p;
	else		  prime = 1;
	return ( 0 == Error );
}

BOOL GeneratePrimes::GetPrime(CString &primeStr)
{
	if (! Error ) BigToCString(p, primeStr);
	else		  primeStr = "1";
	return ( 0 == Error );
}


void GeneratePrimes::SetP(Big &Number)
{
	p=Number;
	Error &= GP_ERROR_NOPRIME;
}

void GeneratePrimes::SetP(CString &NumberStr)
{
	evaluate::eval( p, NumberStr.GetBuffer( 256 ) );
	Error &= GP_ERROR_NOPRIME;
}

BOOL GeneratePrimes::RandP()
{
	if ( Error &= GP_ERROR_LIMIT )
	{
		return false;
	}
	else
	{
		RandomWithLimits(p,lowerBound, upperBound);
		Error &= GP_ERROR_NOPRIME;
		return true;		
	}
}


BOOL GeneratePrimes::IsBlumNumber()
{
	if (Error &= GP_ERROR_NOPRIME )
	{
		return false;
	}
	else
	{
		return (p % 4 == 3);
	}
}



//////////////////////////////////////////////////////////////////////
// TutorialRSA Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

TutorialRSA::TutorialRSA()
{
	isInitialized_N = isInitialized_d = isInitialized_e = false;
}

TutorialRSA::~TutorialRSA()
{

}

BOOL TutorialRSA::InitParameter( Big &p, Big &q )
{
	isInitialized_N = isInitialized_e = isInitialized_d = false;
	GeneratePrimes P; P.SetP( p );
	if ( !P.SolvayStrassenTest() /* || !P.MillerRabinTest() */ ) return false;
	GeneratePrimes Q; Q.SetP( q );
	if ( !Q.SolvayStrassenTest() /* || !Q.MillerRabinTest() */ ) return false;
	N = p*q;
	phiOfN = (p-1)*(q-1);
	isInitialized_N = true;
	return true;
}

BOOL TutorialRSA::InitParameter( CString &pStr, CString &qStr, int base )
{
	Big p, q;
	CStringToBig( pStr, p, base );
	CStringToBig( qStr, q, base );
	return InitParameter( p, q );
}


BOOL TutorialRSA::SetPublicKey ( Big &E )
{
	isInitialized_e = isInitialized_d = false;
	if ( !isInitialized_N ) return false;
	if ( 1 == gcd( E, phiOfN ) )
	{
		e = E;
		isInitialized_e = true;
	}
	return isInitialized_e;
}

BOOL TutorialRSA::SetPublicKey ( CString &eStr, int base )
{
	Big E;
	CStringFormulaToBig( eStr, E );
	return SetPublicKey( E );
}

BOOL TutorialRSA::GetParameter( CString &NStr, CString &phiOfNStr, CString &eStr, CString &dStr, int base )
{
	BigToCString( N, NStr, base );
	BigToCString( phiOfN, phiOfNStr, base );
	BigToCString( e, eStr, base );
	BigToCString( d, dStr, base );
	return IsInitialized();
}

BOOL TutorialRSA::SetPrivateKey()
{
	isInitialized_d = false;
	if ( isInitialized_N && isInitialized_e )
	{
		d = inverse( e, phiOfN );
		isInitialized_d = true;
	}
	else
	{
		d = 0;
	}
	return isInitialized_d;
}

int  TutorialRSA::GetBlockLength()
{
	return bits(N)-1;
}

BOOL TutorialRSA::Encrypt( Big &PlaintextBlock,  Big &CiphertextBlock )
{
	PlaintextBlock = PlaintextBlock % N;
	if ( IsInitialized() /* && PlaintextBlock < N */ )
	{
		CiphertextBlock = pow(PlaintextBlock,e,N);
		return true;
	}
	else
	{
		return false;
	}
}

BOOL TutorialRSA::Decrypt( Big &CiphertextBlock, Big &PlaintextBlock )
{
	CiphertextBlock = CiphertextBlock % N;
	if ( IsInitialized() /* && CiphertextBlock < N */ )
	{
		PlaintextBlock = pow( CiphertextBlock, d, N);
		return true;
	}
	else
	{
		return false;
	}
}

BOOL TutorialRSA::CheckInput( CString &Input, int base, int base2 )
{	
	int i1 = 0, i2 = 0;
	CString newInput = "";
	CString oldInput = Input;
	Big tmp, tmpN=1;
	CString tmpStr;
	if (base2) while ( tmpN*base2 < N ) tmpN *= base2;
	else tmpN = N;
	Input.MakeUpper();

	while ( i1 < Input.GetLength() )
	{
		bool flag = false;
		if ( i2 >= Input.GetLength() )
		{
			flag = true;
			if ( i2 == i1 )
				break;
		}
		else
			if ( Input[i2] >= '0' && Input[i2] <= '0' + (char)(min(10,base) -1) )
			{
				i2++; 
			}
			else 
				if ( ( 10 < base ) && 
				     ( Input[i2] >= 'A' && Input[i2] <= 'A' + (char)(base-11) ) )
				{
					i2++;
				}
				else
					if ( Input[i2] == ' ' || Input[i2] == '#'  )
					{
						if ( i2 > i1 && Input[i2] == '#' ) flag = true;
						Input.Delete(i2);
					}
					else 
						if ( Input[i2] == 0 )
						{
							flag = true;
						}
						else
						{
							Input = oldInput;
							return false;
						}

		if ( i2 > i1 )
		{
			tmpStr = Input.Mid(i1, i2-i1);
			CStringToBig( tmpStr, tmp, base );
			if ( flag == true /* || tmp >= tmpN */ )
			{
				// tmp = tmp % N;
				// if ( tmp >= N )
				// {
				//	i2--;
				//	tmpStr = Input.Mid(i1, i2-i1);
				//	CStringToBig( tmpStr, tmp, base );
				// }
				if ( newInput.GetLength() > 0 ) 
				{
					newInput.Insert(newInput.GetLength(), " # "); // = newInput + " # ";
				}
				BigToCString( tmp, tmpStr, base );
				newInput.Insert(newInput.GetLength(), tmpStr); //  = newInput + tmpStr;
				i1 = i2;
			}
		}
	}
	Input = newInput;
	return true;
}

void TutorialRSA::Encrypt( CString &Plaintext,  CString &Ciphertext, int base)
{
	Big plain, cipher;
	CString plainStr, cipherStr;

	int i1, i2; 
	i1 = 0;
	Ciphertext = "";

	while (i1 < Plaintext.GetLength() && (Plaintext[i1] == ' ' || Plaintext[i1] == '#') ) i1++;
		
	while ( i1 < Plaintext.GetLength() )
	{
		i2 = Plaintext.Find(" ", i1);
		if (i2 < 0) 
		{
			if ( i1 < Plaintext.GetLength() ) i2 = Plaintext.GetLength();
			else break;
		}
		plainStr = Plaintext.Mid(i1, i2-i1);
		CStringToBig( plainStr, plain, base );
		Encrypt( plain, cipher );
		BigToCString( cipher, cipherStr, base );
		while ((i2 < Plaintext.GetLength()) && (Plaintext[i2] == ' ' || Plaintext[i2] == '#')) i2++;
		i1 = i2;
		Ciphertext += cipherStr.GetBuffer(cipherStr.GetLength()+1);
		if ( i1 < Plaintext.GetLength() )
			Ciphertext += " # ";
	}
}

void TutorialRSA::EncryptAlphabet( CString &Plaintext,  CString &Ciphertext, CString &Alphabet, int base)
{
	Big plain, cipher;
	CString plainStr, cipherStr;

	int i1, i2; 
	i1 = 0;
	Ciphertext = "";

	while (i1 < Plaintext.GetLength() && (Plaintext[i1] == ' ' || Plaintext[i1] == '#') ) i1++;
		
	while ( i1 < Plaintext.GetLength() )
	{
		i2 = Plaintext.Find(" ", i1);
		if (i2 < 0) 
		{
			if ( i1 < Plaintext.GetLength() ) i2 = Plaintext.GetLength();
			else break;
		}
		plainStr = Plaintext.Mid(i1, i2-i1);
		CStringToBig( plainStr, plain, base );
		plain = (plain-1) % Alphabet.GetLength()+1;
		Encrypt( plain, cipher );
		cipher = cipher + (rand() % 20)*N;
		BigToCString( cipher, cipherStr, base );
		while ((i2 < Plaintext.GetLength()) && (Plaintext[i2] == ' ' || Plaintext[i2] == '#')) i2++;
		i1 = i2;
		Ciphertext += cipherStr.GetBuffer(cipherStr.GetLength()+1);
		if ( i1 < Plaintext.GetLength() )
			Ciphertext += " # ";
	}
}

void TutorialRSA::DecryptAlphabet( CString &Ciphertext, CString &Plaintext, CString &Alphabet, int base)
{
	Big plain, cipher;
	CString plainStr, cipherStr;

	int i1, i2; 
	i1 = 0;
	Plaintext = "";

	while (i1 < Ciphertext.GetLength() && (Ciphertext[i1] == ' ' || Ciphertext[i1] == '#') ) i1++;
		
	while ( i1 < Ciphertext.GetLength() )
	{
		i2 = Ciphertext.Find(" ", i1);
		if (i2 < 0) 
		{
			if ( i1 < Ciphertext.GetLength() ) i2 = Ciphertext.GetLength();
			else break;
		}
		cipherStr = Ciphertext.Mid(i1, i2-i1);
		CStringToBig( cipherStr, cipher, base );
		cipher = (cipher-1) % Alphabet.GetLength()+1;
		Decrypt( cipher, plain );
		plain = plain + (rand() % 20)*N;
		BigToCString( plain, plainStr, base );
		while ((i2 < Ciphertext.GetLength()) && (Ciphertext[i2] == ' ' || Ciphertext[i2] == '#')) i2++;
		i1 = i2;
		Plaintext += plainStr.GetBuffer(plainStr.GetLength()+1);
		if ( i1 < Ciphertext.GetLength() )
			Plaintext += " # ";
	}
}


void TutorialRSA::Decrypt( CString &Ciphertext, CString &Plaintext,  int base)
{
	Big plain, cipher;
	CString plainStr, cipherStr;

	int i1, i2; 
	i1 = 0;
	Plaintext = "";

	while ( (i1 < Ciphertext.GetLength()) && (Ciphertext[i1] == ' ' || Ciphertext[i1] == '#')) i1++;
		
	while ( i1 < Ciphertext.GetLength() )
	{
		i2 = Ciphertext.Find(" ", i1);
		if (i2 < 0) 
		{
			if ( i1 < Ciphertext.GetLength() ) i2 = Ciphertext.GetLength();
			else break;
		}
		cipherStr = Ciphertext.Mid(i1, i2-i1);
		CStringToBig( cipherStr, cipher, base );
		Decrypt( cipher, plain );
		BigToCString( plain, plainStr, base );
		while ( (i2 < Ciphertext.GetLength()) && (Ciphertext[i2] == ' ' || Ciphertext[i2] == '#') ) i2++;
		i1 = i2;
		Plaintext += plainStr.GetBuffer(plainStr.GetLength()+1);
		if ( i1 < Ciphertext.GetLength() )
			Plaintext += " # ";
	}
}


//////////////////////////////////////////////////////////////////////
// TutorialFactorisation Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

TutorialFactorisation::TutorialFactorisation()
{

}

TutorialFactorisation::~TutorialFactorisation()
{

}

BOOL TutorialFactorisation::Precheck()
{
	factor1 = 0;
	factor2 = 0;

	if ( 1 >= N  )
	{
		return true;
	}

    if ( prime( N ) )
	{
		return true;
	}

	if ( 0 == N % 2 )
	{
		factor1 = 2;
		factor2 = N / 2;
		return true;
	}
	return false;
}

BOOL TutorialFactorisation::BruteForce()
{    
	if ( Precheck() ) return true;

	gprime(LIMIT1); /* generate all primes < LIMIT */

	int index;
	int n,p;
	miracl *mip = &g_precision;

	index=0;
	n=0;
	p=mip->PRIMES[0];
    forever
    { // try division by each prime 
        if (N%p==0)
        { // factor found 
            factor1 = p;
			factor2 = N/p;
			return true;
        }
        if ((N/p)<=p)
        { // must be prime 
			return true;
        }
		p=mip->PRIMES[++n];
        if (p==0) break;
    }
	// brute force didn't succeed
	return false;	
}


BOOL TutorialFactorisation::Brent()
{
	if ( Precheck() ) return true;

    long k,r,i,m,iter;
    Big z;
    ZZn x,y,q,ys;

    m=10L;
    r=1L;
    iter=0L;
    z=0;
    modulo(N);    // ZZn arithmetic done mod n 
    y=z;          // convert back to ZZn (n has changed!) 
                  // note:- a change of modulus is tricky for
                  // for n-residue representation used in Montgomery
                  // arithmetic 
    q=1;
    do
    {
        x=y;
        for (i=1L;i<=r;i++) y=(y*y+3);
        k=0;
        do
        {
            iter++;
            ys=y;
            for (i=1L;i<=min(m,r-k);i++)
            {   
                y=(y*y+3);
                q=((y-x)*q);
            }
            z=gcd(q,N);
            k+=m;
        } while (k<r && z==1);
        r*=2;
    } while (z==1);
    if (z==N) do 
    { // back-track 
        ys=(ys*ys+3);
        z=gcd(ys-x,N);
    } while (z==1);

	if (z==N) 
	{
		return false;
	}

	factor1 = z;
	factor2 = N/z;
	return true;
}


BOOL TutorialFactorisation::Pollard()
{
	if ( Precheck() ) return true;

	return false;
}

BOOL TutorialFactorisation::Williams()
{
	if ( Precheck() ) return true;

	return false;
}


BOOL TutorialFactorisation::Lenstra()
{
	if ( Precheck() ) return true;

	return false;
}

BOOL TutorialFactorisation::QuadraticSieve()
{
	if ( Precheck() ) return true;

	return false;
}


void TutorialFactorisation::SetN(CString &NStr)
{
	evaluate::eval( N, NStr.GetBuffer( 256 ) );
}


void TutorialFactorisation::GetFactor1Str(CString &Factor1)
{
	BigToCString( factor1, Factor1 );
}


void TutorialFactorisation::GetFactor2Str(CString &Factor2)
{
	BigToCString( factor2, Factor2 );
}
