//////////////////////////////////////////////////////////////////////
// CryptologyUsingMiracl.cpp: Implementierung der Klasse evaluate.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CryptologyUsingMiracl.h"
#include <monty.h>
#include "DlgRuntime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static Miracl g_precision=50;

#ifndef MULTITHREAD
extern CDlgRuntime dlg;
#define THREAD_START 	if(dlg.EnterSchedule(m_Ordinal)) {dlg.ExitSchedule(m_Ordinal); return false; }\
if ( Precheck() ) { dlg.ExitSchedule(m_Ordinal); return true;}
#define THREAD_CHECK if(dlg.Schedule(m_Ordinal)) {dlg.ExitSchedule(m_Ordinal);return false;}
#define THREAD_END dlg.ExitSchedule(m_Ordinal);
#else
#define THREAD_DEFINE
#define THREAD_START
#define THREAD_CHECK if ( ExitFactorisationCode ) { \
	ExitFactorisationCode = 1; return false; }
#endif


double approxLog2(Big &N)
{
	int b = bits(N);
	Big num = N;
	Big dom = 1;
	if (b > 16)
	{	
		num >>= b-16;
		dom <<= 16;
	}
	else
		dom <<= b;
	double d_num = (double)(num % INT_MAX);
	double d_dom = (double)(dom % INT_MAX);

	double ret_val = log(d_num/d_dom)/log(2) + double(b);
	return ret_val;
}


double  BitLength( CString &number, int base )
{
	Big t;
	CStringToBig( number, t, base );
	return approxLog2(t);
}

/////////////////////////////////////////////////////////////////////////////////
//
//
//

BOOL GetNumber( CString &number, CString &Formula, int base, int &ndx )
{
	int i=ndx, flag = 0;
	while (i<Formula.GetLength() && !flag)
	{
		switch (base)
		{
			case 2: if (Formula[i] >= '0' && Formula[i] <= '1') i++; else flag = 1;
			break;
			case 8: if (Formula[i] >= '0' && Formula[i] <= '7') i++; else flag = 1;
			break;
			case 10: if (Formula[i] >= '0' && Formula[i] <= '9') i++; else flag = 1;
			break;
			case 16: if (Formula[i] >= '0' && Formula[i] <= '9' || 
						 Formula[i] >= 'A' && Formula[i] <= 'F' ||
						 Formula[i] >= 'a' && Formula[i] <= 'f'   ) i++; else flag = 1;
			break;
			default: return FALSE;
		}
	}
	if (i>ndx) number = Formula.Mid(ndx, i-ndx);
	if ( i == ndx ) return FALSE;
	else
	{
		ndx = i;
		return TRUE;
	}
}


BOOL CheckFormula(CString &Formula, int base, CString &UpnFormula, int &ndx)
{
	char stack[1024];
	long stack_i;
	BOOL NumFlag = FALSE;
	ndx     = 0; 
	stack_i = -1;
	CString f_formula, number;
	f_formula = UpnFormula = _T("");
	while (ndx < Formula.GetLength())
	{
		if ( Formula[ndx] == ' ' || Formula[ndx] == '\t' ) ndx++;
		else 
		{
			if ( GetNumber(number, Formula, base, ndx) )
			{
				if ( NumFlag ) return FALSE;
				f_formula += number;
				UpnFormula = UpnFormula + ' ' + number;			  
				NumFlag = TRUE;
			}
			else 
			{
				switch ( Formula[ndx++] )
				{
					case '+':
						if (!NumFlag)
						{
							if (stack_i != -1 || stack[stack_i] != '+' || stack[stack_i] != '-' || stack[stack_i] != '(' ) 
							return FALSE;
						}
						else
						{
							while (stack_i > -1 && 
							stack[stack_i] == '*' || stack[stack_i] == '/' ||
							stack[stack_i] == '^' || stack[stack_i] == '!' ) 
							{
								UpnFormula += stack[stack_i--];
							}
							stack[++stack_i] = '+';
							f_formula += '+';
							NumFlag = FALSE;
						}
					break;
					case '-': 
						if (!NumFlag) 
						{
							if (stack_i == -1 || stack[stack_i] == '(' || stack[stack_i] == '*' /* ||  stack[stack_i] == '/' */) 
							{ 
								stack[++stack_i] = '!'; 
								f_formula += '-'; 
							}
							else if (stack[stack_i] == '+') 
							{ 
								stack[stack_i] = '-'; 
								f_formula.SetAt(f_formula.GetLength()-1,'-'); 
							}
							else if (stack[stack_i] == '-') 
							{ 
								stack[stack_i]   = '+'; 
								f_formula.SetAt(f_formula.GetLength()-1,'+'); 
							}
							else if (stack[stack_i] == '!') 
							{ 
								stack_i--;  
								f_formula.Delete(f_formula.GetLength()-1);
							} // TODO 
							else return FALSE;
  						}
						else 
						{
							while (stack_i > -1 && 
							stack[stack_i] == '*' || stack[stack_i] == '/' ||
							stack[stack_i] == '^' || stack[stack_i] == '!' ) 
							{
								UpnFormula += stack[stack_i--];						
							}
							stack[++stack_i] = '-'; 
							f_formula += '-';
							NumFlag = FALSE;
						}
					break;
					case '*':
						if (!NumFlag) return FALSE;
						else 
						{
							while (stack_i > -1 && 
								   stack[stack_i] == '^' || stack[stack_i] == '!') 
							{
								UpnFormula += stack[stack_i--];
							}
							stack[++stack_i] = '*';
							f_formula += '*';
							NumFlag = FALSE;
						}	  
					break;
		//	        case '/': if (!NumFlag) return FALSE;
		//	                  else {
		//                           stack[++stack_i] = '/';
		//		 	     f_formula += '/';
		//		          }	  
		//	        break;
					case '^':
						if (!NumFlag) return FALSE;
						else 
						{
							stack[++stack_i] = '^';
							f_formula += '^';
							NumFlag = FALSE;
						}	  
					break;
					case '(':
						if (!NumFlag) 
						{
							stack[++stack_i] = '('; f_formula += '('; 
						}
						else
						{
							return FALSE;
						}	  
					break;
					case ')':
						if (!NumFlag) 
						{
							if (f_formula[f_formula.GetLength()-1] == '(') 
							{
								return FALSE;							   							  
							}
							else return FALSE;
						}
						else
						{
							while (stack_i > -1 && stack[stack_i] != '(') 
							{
		  						UpnFormula += stack[stack_i--];
							}
							f_formula += ')';
							if (stack_i == -1) return FALSE;
							stack_i--;
							NumFlag = TRUE;
						}
					break;
					default: 
					return FALSE;
				}
			}
		}
	}
	if ( NumFlag == FALSE ) return FALSE;
	while (stack_i > -1) 
	{
		if ( stack[stack_i] != '(' )
			UpnFormula += stack[stack_i--];
		else
		{
			f_formula += ')';
			stack_i--;
		}
	}
	if ( stack_i > -1 ) return FALSE;
	Formula = f_formula;
	ndx = -1;
	return TRUE;
}

BOOL isCharOf( const char ch, const char *expr )
{
	int len = strlen(expr);
	for (int i=0; i<len; i++) 
        if ( i+3 < len && expr[i+1] == '.' && expr[i+2] == '.' && expr[i] < expr[i+3] )
		{
			if ( ch >= expr[i] && ch <= expr[i+3] ) return TRUE;
               i += 3;
		}
        else if ( ch == expr[i] ) return TRUE;
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
BOOL CStringFormulaToBig(CString &CStrNumber, Big &t )
{
	int i=0;
	while ( i < CStrNumber.GetLength() ) 
	{
		if ( isCharOf(CStrNumber[i], VALID_FORMULA) ) i++;
		else CStrNumber.Delete(i);
	}

	t = 0;
	char *tmp;
	tmp = new char[CStrNumber.GetLength()+1];
	strcpy(tmp, CStrNumber.GetBuffer( CStrNumber.GetLength()+1));
	BOOL success=evaluate::eval(t, tmp); 
	if ( !success ) t = 0;	
	delete []tmp;
	return success;
}

BOOL EvalFormula(CString &CStrExpr, int &ndx, BOOL EvalNumber)
{
	CString upnExpr;
	if ( !CheckFormula(CStrExpr, 10, upnExpr, ndx) )
	{
		return FALSE;
	}
	Big tmp;
	if ( CStringFormulaToBig( CStrExpr, tmp ))
	{
		if ( TRUE == EvalNumber ) BigToCString( tmp, CStrExpr );
		return TRUE;
	}
	else
		return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
// Nur temporär & lokal definiert

BOOL Whitespace( char ch )
{
	return isCharOf( ch, WHITESPACE);
}

BOOL IsNumber( char ch, int base )
{
	  switch (base) {
	  case BASE_BIN: return isCharOf(ch, VALID_BIN);
					break;
	  case BASE_OCT: return isCharOf(ch, VALID_OCT);
					break;
	  case BASE_DEC: return isCharOf(ch, VALID_DEC);
					break;
	  case BASE_HEX: return isCharOf(ch, VALID_HEX); 
					break;
	  default: return isCharOf(ch, VALID_DEC);
	  }
}

int NeededBase( char ch )
{
	if ( IsNumber( ch, BASE_BIN ) ) return (BASE_BIN);
	if ( IsNumber( ch, BASE_BIN ) ) return (BASE_OCT);
	if ( IsNumber( ch, BASE_BIN ) ) return (BASE_DEC);
	if ( IsNumber( ch, BASE_BIN ) ) return (BASE_HEX);
	return 0;
}

char DigitToNum( char ch )
{
	if ( ch >= '0' && ch <= '9' ) return ch - '0';
	if ( ch >= 'A' && ch <= 'F' ) return ch - 'A' + 10;
	if ( ch >= 'a' && ch <= 'f' ) return ch - 'a' + 10;
	return -1;
}


/////////////////////////////////////////////////////////////////////////////////
//
// return true if the INPUT is a stream of Numbers + formats the INPUT
//

int IsNumberStream( CString &CStr, int numberBase, CString Modul, int flagList )
{
	Big modul;
	Big myModul;
	Big num;
	int start, end = 0;

// have to consider a modul ?
	if (Modul.GetLength()) {
		CStringToBig( Modul, modul, numberBase );
		myModul = modul;
		if ( flagList & SPLIT_NUMBERS_VSFLOOR )
		{
			myModul = 1;
			int k = bits(modul);
			myModul <<= (bits(modul) - (bits(modul)%8));
		}
	}
	else // ... no!
	{
		modul = 0;
	}

// must we increase the base of numbers ?
	int newNumberBase = numberBase;	
	if ( flagList & INCREASE_THE_BASE )
	{	
		int b;
		for (int i=0; i<CStr.GetLength(); i++ )
		{
			b = NeededBase(CStr[end]);
			if ( b > newNumberBase ) newNumberBase = b;
		}
	}

	CString fmt = _T("");
	CString tmp;

// ... the check and formatting the number Streams
	while ( end < CStr.GetLength() && isCharOf(CStr[end], NUMBER_SEPARATOR) ) end++;
   	while ( TRUE )
	{
		start = end;
		while ( end < CStr.GetLength() )
		{
			if ( isCharOf(CStr[end], NUMBER_SEPARATOR) ) break;
			if ( !IsNumber(CStr[end], newNumberBase) ) return FALSE;
			end++;
		}

		tmp = CStr.Mid(start, end-start);
		if ( 0 != modul ) CStringToBig( tmp, num, newNumberBase );
		if ( 0 != modul && num > myModul )
		{			
			if ( flagList & (SPLIT_NUMBERS_VSFLOOR + SPLIT_NUMBERS_VSMODUL) )
			{ // split the numbers (mod myModul)
				Big t;
				int ndx = fmt.GetLength();
				while ( num != 0 ) 
				{
					t   %= myModul;
					num /= myModul;
					BigToCString( t, tmp, newNumberBase );					
					if ( 0 != num ) fmt.Insert( ndx, tmp + SEPARATOR ); 
					else            fmt.Insert( ndx, tmp );
				}
			}
			else // just consider the numbers (mod modul)
			{ 
				if ( FORMAT_MODULO )
					num = num % myModul;
				BigToCString( num, tmp, newNumberBase );
				fmt = fmt + tmp;
			}
		}
		else // no modulo or number < myModul
		{
			fmt = fmt + tmp;
		}
		while ( end < CStr.GetLength() && isCharOf(CStr[end], NUMBER_SEPARATOR ) ) end++;
		if ( end >= CStr.GetLength() ) break;
		else                           fmt = fmt + SEPARATOR;
	}
	CStr = fmt;
	return newNumberBase;
}

////////////////////////////////////////////////////////////////////////////////
//
// return true if the INPUT is a HEX-dump + formats the INPUT
//

BOOL IsHexDump( CString &CStr )
{
	CString fmt = _T("");
	int twoStep = 0;
	for (int i=0; i<CStr.GetLength(); i++ ) {
		if ( !Whitespace( CStr[i] ) )
		{
			if ( IsNumber( CStr[i], BASE_HEX ) )
			{
				fmt += CStr[i];
				twoStep++;
				if ( 2 == twoStep ) {
					fmt += ' ';
					twoStep = 0;
					if ( i+1 < CStr.GetLength() && !Whitespace( CStr[i+1] ) )
						return FALSE;
				}
			}
			else 
				return FALSE;
		}
	}
	if (twoStep != 0) return FALSE;
	else              return TRUE;
}

char ToHex( const char ch )
{
	if ( ch % BASE_HEX < BASE_DEC ) return ('0' + (ch % BASE_HEX));
	else                            return ('A' + ((ch % BASE_HEX) -10));
}

void dataToHexDump( const char* data, int len, char* hexDump )
{
	int j=0;
    	for (int i=0; i<len; i++) 
	{
		hexDump[j++] = ToHex(((unsigned char)data[i]) / 16);
		hexDump[j++] = ToHex(((unsigned char)data[i]) % 16);
		if ( i+1 < len ) hexDump[j++] = ' ';
		else             hexDump[j++] = '\0';
	}
}

void dataToHexDump( const char* data, int len, CString& hexDump )
{
	char *tmp;
	tmp = new char[3*len];
	dataToHexDump(data, len, tmp);
	hexDump = tmp;
	delete []tmp;
}

int HexDumpToData( const char *hexDump, char *data )
{
	int twoStep = 0;
	char ch;
    	int i,j = 0;
    	for ( i=0; hexDump[i] != 0; i++ )
	{
		if ( IsNumber(hexDump[i], BASE_HEX) )
		{
			char res;
			if (twoStep++)
			{
				res = ( ch << 4 ) + DigitToNum( hexDump[i] );
				data[j++] = res;
				twoStep = 0;
			}
			else
				ch = DigitToNum( hexDump[i] );
		}
		else
		{
			if ( !Whitespace( hexDump[i] ) )
				return -1; // error: no HEX-Dump
		}
	}
	return j;
}

int HexDumpToData( CString &hexDump, char *data )
{
	char *tmp;
	tmp = new char[hexDump.GetLength()+1];
	strcpy( tmp, hexDump.GetBuffer(0) );
	int retVal = HexDumpToData( tmp, data );
	hexDump = tmp;
	delete []tmp;
	return retVal;
}

////////////////////////////////////////////////////////////////////////////////
// 
// converts DigitString to a Big Number
// 
int StringToBig( const char* StrNumber, Big &t, int base )
{
	char *tmp;
	tmp = new char[strlen(StrNumber)+1];
	int i = 0,j;
	while ( Whitespace(StrNumber[i]) && StrNumber[i] ) i++;
	for ( j=0; StrNumber[i] != 0; i++) {
		if ( IsNumber(StrNumber[i], base) ) tmp[j++] = StrNumber[i];
		else /* if (!Whitespace(StrNumber[i])) */ break;
	}
	tmp[j] = '\0';
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = base;
	t = tmp;
	mip->IOBASE = oldBase;
	delete []tmp;
	return i;
}

int CStringToBig( CString &CStrNumber, Big &t, int base )
{
	return StringToBig( CStrNumber.GetBuffer( CStrNumber.GetLength()+1), t, base );
}

///////////////////////////////////////////////////////////////////////////////////////////////
//
// decodes a number to a block of ascii-characters / characters of an selected Alphabet
// 

int decode( const char *StrNumber, char *data, int blockLength, int numberBase, BOOL basisSystem, const char *alphabet )
{
	Big t;
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = numberBase;
	StringToBig( StrNumber, t, numberBase);

	char tmp[MAX_8BIT_LENGTH];
	int i, modul, digits, alphabetLength;
	alphabetLength = ( alphabet == NULL ) ? 256 : strlen(alphabet);
    digits = (int)ceil(log(alphabetLength)/log(numberBase));
    if ( basisSystem )
	{
        modul  = numberBase;
        for (i=1; i<digits; i++) modul *= numberBase;
	}
    else   modul = alphabetLength;

	for ( i=0; i < blockLength || t != 0; i++ )
	{
 	   	char ch = (alphabet == NULL) ? (t % modul) % alphabetLength : alphabet[(t % modul) % alphabetLength];
	   	t = t / modul;
       	tmp[MAX_8BIT_LENGTH-(i+1)] = ch;
	}
	for (int j=MAX_8BIT_LENGTH-i; j<MAX_8BIT_LENGTH; j++ )
	{
	    data[j-(MAX_8BIT_LENGTH-i)] = tmp[j];
	}
    data[j-(MAX_8BIT_LENGTH-i)] = '\0';
	return i;
}

int decode( CString &CStringNumber, char *data, int blockLength, int numberBase, BOOL BasisSystem, const char *alphabet )
{
    return decode(CStringNumber.GetBuffer(CStringNumber.GetLength()+1), data, blockLength, numberBase, BasisSystem, alphabet );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  converts a Big Number to a string 
// 

void BigToString(const Big&t, char *NumStr, int base, int OutLength)
{
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = base;
	char tmpStr[MAX_BIT_LENGTH];
	tmpStr << t;
	int i,diff;
    	diff = ( OutLength > strlen(tmpStr) ) ? OutLength - strlen(tmpStr) : 0;
    	if (diff > 0) for(i=0; i<diff; i++) NumStr[i] = '0';
    	strcpy(NumStr+diff, tmpStr);
	mip->IOBASE = oldBase;
}

void BigToCString(const Big &t, CString &NumCStr, int base, int OutLength )
{
    char tmpStr[MAX_BIT_LENGTH];
    BigToString( t, tmpStr, base, OutLength );
    NumCStr = tmpStr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  encode an ASCII string of length "blockLength" into a Number represented as character string
// 

void encode( const char *data, char *numStr, int blockLength, int numberBase, BOOL basisSystem, const char *alphabet )
{
	Big tmp = 0;
	int outLength = 0;

	int i,j, modul, digits, alphabetLength;
	alphabetLength = ( alphabet == NULL ) ? 256 : strlen(alphabet);
   	digits = (int)ceil(log(alphabetLength)/log(numberBase));
   	if ( basisSystem )
	{
    	modul = numberBase;
       	for (i=1; i<digits; i++) modul *= numberBase;
		outLength = digits * blockLength;
	} 
   	else    
	{
		outLength = (int)ceil((log(alphabetLength)/log(numberBase))*blockLength);
		modul = alphabetLength;
	}
   	for ( i=0; i<blockLength; i++ )
	{
    	if ( alphabet ) for ( j=0; j < modul && data[i] != alphabet[j]; ) j++;
       	else            j = (unsigned char)data[i];
    	tmp *=modul;
       	tmp += j;
   	}
	BigToString( tmp, numStr, numberBase, outLength );
}

void encode( const char *data, CString &numCStr, int blockLength, int numberBase, BOOL basisSystem, const char *alphabet )
{
    char *tmp;
    tmp = new char[MAX_BIT_LENGTH];
    encode ( data, tmp, blockLength, numberBase, basisSystem, alphabet );
    numCStr = tmp;
    delete []tmp;
}

void RandRepr( CString &StrNum, int Modul, int numberBase, int randInterval, int ofs )
{
	Big t;
	CStringToBig( StrNum, t, numberBase );
	t = t + ofs + ((rand() % randInterval)*Modul);
	BigToCString( t, StrNum, numberBase );
}


void RandRepr( CString &StrNum, CString StrModul, int numberBase, int randInterval, int ofs )
{
	Big t, Modul;
	CStringToBig( StrNum, t, numberBase );
	CStringToBig( StrModul, Modul, numberBase );
	t = t + ofs + ((rand() % randInterval)*Modul);
	BigToCString( t, StrNum, numberBase );
}

void ModRepr ( CString &StrNum, CString StrModul, int numberBase, int ofs )
{
	Big t, Modul;
	CStringToBig( StrNum, t, numberBase );
	CStringToBig( StrModul, Modul, numberBase );
	t = (t % Modul) + ofs;
	BigToCString( t, StrNum, numberBase );
}

void ModRepr ( CString &StrNum, int Modul, int numberBase, int ofs )
{
	Big t;
	CStringToBig( StrNum, t, numberBase );
	t =  (t % Modul) + ofs;
	BigToCString( t, StrNum, numberBase );
}

//////////////////////////////////////////////////////////////////////
// Private Funktionen
//////////////////////////////////////////////////////////////////////
void RandomWithLimits(Big &r, const Big &lower, const Big &upper)
{
	r=lower;
	if ( upper > lower )
	{
		r=rand(upper-(lower-1))+(lower-0);
	}
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
	try {
		if ( eval() ) {
			value = temp;
			return true;
		}
		else
		{
			value = 0;
			return false;
		}
	}
	catch ( ... )
	{
		value = 0;
		// throw;
	}
	return false;
}

void evaluate::eval_power(Big &oldn, Big &n, char op)
{
	if (op) {
		if ( n    == 0 ) { n = 1; return; }
		if ( oldn == 0 ) { n = 0; return; }
		int i_n = toint(n);
		double d = approxLog2(oldn);
		if ( (int)floor(d*i_n) > MAX_BIT_LENGTH ) throw eval_err( EVAL_ERR_POW );
		n=pow(oldn,toint(n));    // power(oldn,size(n),n,n);
	}
}

void evaluate::eval_sum(Big &oldn, Big &n, char op)
{
	int l1, l2;
	l1 = bits(oldn);
	l2 = bits(n);
	if ( l1+1 > MAX_BIT_LENGTH || l2+1 > MAX_BIT_LENGTH ) throw eval_err( EVAL_ERR_SUM );
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
				{
					int l1, l2;
					l1 = bits(oldn);
					l2 = bits(n);
					if (l1 + l2 > MAX_BIT_LENGTH ) throw eval_err( EVAL_ERR_MUL );
					n*=oldn; 
				}
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
//			Error - invalid number
			throw eval_err( EVAL_ERR_NUMBER_INVALID );
			//return(false);
		}
		op=s[i];
		s[i]=0;

		if ( log(10.0)/log(2.0)*i > MAX_BIT_LENGTH ) throw eval_err( EVAL_ERR_STR_NUMBER );
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
//					Error - invalid operator
					throw eval_err( EVAL_ERR_OPERATOR_INVALID );
					//return(false);
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

int GeneratePrimes::SetLimits( CString &LowerLimitStr, CString &UpperLimitStr )
{
	Big UpperLimit, LowerLimit;
	if ( evaluate::eval( LowerLimit, LowerLimitStr.GetBuffer( 256 ) ) == false )
	{
		//LowerLimit hat mehr als 1024 bit
		return 3;
	}
	if ( evaluate::eval( UpperLimit, UpperLimitStr.GetBuffer( 256 ) ) == false )
	{
		//UpperLimit hat mehr als 1024 bit
		return 2;
	}
	BOOL Out_Set_Lim;
	Out_Set_Lim = SetLimits( LowerLimit, UpperLimit );
		
	//Eingabe sind OK
	if (Out_Set_Lim) return 1;
	//UpperLimit>LowerLimit
	else return 0;
}

BOOL GeneratePrimes::SolvayStrassenTest(unsigned long probabilityThreshold)
{
	if ( p <= 10 )
	{
		if ( 2 == p || 3 == p || 5 == p || 7 == p ) Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		else                                        Error |= GP_ERROR_NOPRIME;
	}
	else
	{
		if ( 0 == p % 2 || 0 == p % 3 ||
			 0 == p % 5 || 0 == p % 7 ||
			 0 == p % 11 || 0 == p % 13 ||
			 0 == p % 17 || 0 == p % 19 ||
			 0 == p % 23 || 0 == p % 29 ||
			 0 == p % 31 || 0 == p % 37 ) return FALSE;
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
			19 == p || 23 == p || 29 == p || 31 == p || 37 ==  p ) Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME;
		else                                        Error |= GP_ERROR_NOPRIME;
	}
	else
	{
		if ( 0 == p % 2 || 0 == p % 3 ||
			 0 == p % 5 || 0 == p % 7 ||
			 0 == p % 11 || 0 == p % 13 ||
			 0 == p % 17 || 0 == p % 19 ||
			 0 == p % 23 || 0 == p % 29 ||
			 0 == p % 31 || 0 == p % 37 ) return FALSE;
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
		if ( 0 == p % 2 || 0 == p % 3 ||
			 0 == p % 5 || 0 == p % 7 ||
			 0 == p % 11 || 0 == p % 13 ||
			 0 == p % 17 || 0 == p % 19 ||
			 0 == p % 23 || 0 == p % 29 ||
			 0 == p % 31 || 0 == p % 37 ) return FALSE;
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

/*
int TutorialRSA::InitParameter( Big &p, Big &q )
{
	isInitialized_N = isInitialized_e = isInitialized_d = false;
	if ( !prime( p ) ) return ERR_P_NOT_PRIME;
	if ( !prime( q ) ) return ERR_Q_NOT_PRIME;
	if (p==q) return ERR_P_EQUALS_Q;
	int l1,l2;
	l1=bits(p);
	l2=bits(q);
	if (l1+l2-1 > MAX_BIT_LENGTH) 
	{
	//	IsInitialised_N=false
		return 1;
	}
	N = p*q;
	phiOfN = (p-1)*(q-1);
	isInitialized_N = true;
	return 0;
}
*/

int TutorialRSA::InitParameter( Big &p, Big &q )
{
	int ePrime(0);
	isInitialized_N = isInitialized_e = isInitialized_d = false;
	if ( p<2 ) ePrime |= ERR_P_LESS_THAN_TWO;	
	if ( q<2 ) ePrime |= ERR_Q_LESS_THAN_TWO;
	if ( !prime( p ) ) ePrime |= ERR_P_NOT_PRIME;
	if ( !prime( q ) ) ePrime |= ERR_Q_NOT_PRIME;
	if ( p==q ) ePrime |= ERR_P_EQUALS_Q;	
	int l1,l2;
	l1=bits( p );
	l2=bits( q );
	if (l1+l2-1 > MAX_BIT_LENGTH) ePrime |= ERR_MAX_BIT_LENGTH;
	if ( ePrime ) return ePrime;
	N = p*q;
	phiOfN = (p-1)*(q-1);
	isInitialized_N = true;
	return 0;
}



int TutorialRSA::InitParameter( CString &pStr, CString &qStr, int base )
{
	Big p, q;
	BOOL p_ok,q_ok;
	p_ok = CStringFormulaToBig( pStr, p );
	q_ok = CStringFormulaToBig( qStr, q );
	if (p_ok == false) return ERR_P_TO_BIG;
	if (q_ok == false) return ERR_Q_TO_BIG;
	return InitParameter( p, q );
}


int TutorialRSA::SetPublicKey ( Big &E )
{
	int ausgabe;
	isInitialized_e = isInitialized_d = false;
	ausgabe = 0;
	if ( !isInitialized_N ) return 0;
	if ( 1 == gcd( E, phiOfN ) )
	{
		e = E;
		isInitialized_e = true;
		ausgabe = 1;
	}
	//return isInitialized_e;
	return ausgabe;
}

int TutorialRSA::SetPublicKey ( CString &eStr, int base )
{
	Big E;
	// Noch ...
	BOOL e_ok;
	e_ok = CStringFormulaToBig( eStr, E );
	if (e_ok == FALSE) return ERR_E_TO_BIG;
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

double TutorialRSA::GetLog2RSAModul()
{
	return approxLog2(N);
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

void TutorialRSA::Encrypt( CString &Plaintext,  CString &Ciphertext, int base, BOOL DlgOfSisters )
{
	Big plain, cipher;
	CString plainStr, cipherStr;
	int OutLength = (int)ceil(GetBlockLength() / (log(base)/log(2)));

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
		// Besonderheit: Dialog der Schwestern
		if ( DlgOfSisters ) cipher = cipher + (rand() % 20 )*N;
		BigToCString( cipher, cipherStr, base, OutLength );
		while ((i2 < Plaintext.GetLength()) && (Plaintext[i2] == ' ' || Plaintext[i2] == '#')) i2++;
		i1 = i2;
		Ciphertext += cipherStr.GetBuffer(cipherStr.GetLength()+1);
		if ( i1 < Plaintext.GetLength() )
			Ciphertext += " # ";
	}
}

void TutorialRSA::Decrypt( CString &Ciphertext, CString &Plaintext, int base, BOOL DlgOfSisters)
{
	Big plain, cipher;
	CString plainStr, cipherStr;
	int OutLength = (int)ceil(GetBlockLength() / (log(base)/log(2)));

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
		// Besonderheit: Dialog der Schwestern
		if ( DlgOfSisters ) plain = plain + (rand() % 20 )*N;
		BigToCString( plain, plainStr, base, OutLength );
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
//	mip = &g_precision;
	ww = NULL;
	zz = NULL;
	yy = NULL;
	xx = NULL;
	pr = NULL;
	e = NULL;
	r2=NULL;
	r1=NULL;
	logp = NULL;
	sieve = NULL;
	epr = NULL;
	rp = NULL;
	hash = NULL;
	bb = NULL; 
	G = NULL;
	EE = NULL;

	status = 0;
	factorized = false;
}


TutorialFactorisation::TutorialFactorisation(int ordinal, CString name)
{
	ww = NULL;
	zz = NULL;
	yy = NULL;
	xx = NULL;
	pr = NULL;
	e = NULL;
	r2=NULL;
	r1=NULL;
	logp = NULL;
	sieve = NULL;
	epr = NULL;
	rp = NULL;
	hash = NULL;
	bb = NULL;
	G = NULL;
	EE = NULL;

	m_Ordinal = ordinal;
	m_Name = name;
//	mip = &g_precision;
	status = 0;
	factorized = false;
}



TutorialFactorisation::~TutorialFactorisation()
{
	int i;
#define FREE(x)	if(x) { mr_free(x); x = NULL; }
	FREE(r1);
	FREE(r2);
	FREE(epr);
	FREE(rp);
	FREE(bb);
	FREE(e);
	FREE(logp);
	FREE(pr);
	FREE(hash);
	FREE(sieve);
	if(EE) {
		for(i=0;i<=mmm;i++) mr_free(EE[i]);
		FREE(EE);
	}
	if(G) {
		for(i=0;i<=mlf;i++) mr_free(G[i]);
		FREE(G);
	}
	set_mip(mip);
	if(ww)
		delete[mlf] ww;
	if(xx)
		delete[mmm] xx;
	if(yy)
		delete[mmm] yy;
	if(zz)
		delete[mlf] zz;
	ww = xx = yy = zz = NULL;
}

BOOL TutorialFactorisation::IsPrime(CString &Num)
{
	set_mip(mip);
	Big tmpN;
	CStringFormulaToBig( Num, tmpN );
	return ( prime( tmpN ) );
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
		status |= THREAD_FACTORIZED;
		return true;
	}

	if ( 0 == N % 2 )
	{
		factor1 = 2;
		factor2 = N / 2;
		status |= THREAD_FACTORIZED;
		factorized = true;
		return true;
	}
	return false;
}

BOOL TutorialFactorisation::BruteForce()
{    
	set_mip(mip);
	if ( Precheck() ) return true;

	gprime(LIMIT1); /* generate all primes < LIMIT */

	int n,p;
//	miracl *
//	mip = &g_precision;

	n=0;
	p=mip->PRIMES[0];
    forever
    { // try division by each prime 
        if (N%p==0)
        { // factor found 
            factor1 = p;
			factor2 = N/p;
			status |= THREAD_FACTORIZED;
			factorized = true;
			return true;
        }
        if ((N/p)<=p)
        { // must be prime 
			factorized = true;
			status |= THREAD_FACTORIZED;
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
	THREAD_START;

    long k,r,i,m;
    Big z;
    ZZn x,y,q,ys;

    m=10L;
    r=1L;
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
			m_iterations++;
			THREAD_CHECK;
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
		THREAD_END;
		return false;
	}

	factor1 = z;
	factor2 = N/z;

	status |= THREAD_FACTORIZED;
	factorized = TRUE;
	THREAD_END;
	return true;
}

void TutorialFactorisation::marks(long start)
{
	/* mark non-primes in this interval. Note    *
   * that those < NEXT are dealt with already  */
    int i,pr,j,k;
    for (j=1;j<=MULT/2;j+=2) plus[j]=minus[j]=TRUE;
    for (i=0;;i++)
    { /* mark in both directions */
        pr=mip->PRIMES[i];
        if (pr<NEXT) continue;
        if ((long)pr*pr>start) break;
        k=pr-start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            plus[j]=FALSE;
        k=start%pr;
        for (j=k;j<=MULT/2;j+=pr)
            minus[j]=FALSE;
    } 
}

void TutorialFactorisation::next_phase_pollard()
{
	/* now changing gear */
    ZZn bp,t;
    long interval;
    bw=pow(b,8);
    t=1;
    bp=bu[1]=b;
    for (int m=3;m<=MULT/2;m+=2)
    { /* store bu[m] = b^(m*m) */
        t*=bw;
        bp*=t;
        if (cp[m]) bu[m]=bp;
    }
    t=pow(b,MULT);
    t=pow(t,MULT);
    bd=t*t;            /* bd = b^(2*MULT*MULT) */
    iv=p/MULT;
    if (p%MULT>MULT/2) iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks(interval);
    bw=pow(t,(2*iv-1));
    bvw=pow(t,iv);
    bvw=pow(bvw,iv);   /* bvw = b^(MULT*MULT*iv*iv) */
    q=bvw-bu[p%MULT];
}


int TutorialFactorisation::giant_step_pollard()
{
	/* increment giant step */
    long interval;
    iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks(interval);
    bw*=bd;
    bvw*=bw;
    return 1;
}


BOOL TutorialFactorisation::Pollard()
{
	THREAD_START;
	
	/*  factoring program using Pollards (p-1) method */
    int phase,m,pos,btch;
    long i,pa;
    Big t;
	//Big n;
    //mip=&precision;
    gprime(LIMIT1);
    for (m=1;m<=MULT/2;m+=2)
        if (igcd(MULT,m)==1) cp[m]=TRUE;
        else                 cp[m]=FALSE;
    //cout << "input number to be factored\n";
    //cin >> n;
    //if (prime(N))
    //{
        //cout << "this number is prime!\n";
        //return true;
    //}
    modulo(N);                    /* do all arithmetic mod n */
    phase=1;
    p=0;
    btch=50;
    i=0;
    b=2;
    //cout << "phase 1 - trying all primes less than " << LIMIT1;
    //cout << "\nprime= " << setw(8) << p;
    forever
    { /* main loop */
		m_iterations++;
		THREAD_CHECK;

        if (phase==1)
        { /* looking for all factors of (p-1) < LIMIT1 */
            p=mip->PRIMES[i];
            if (mip->PRIMES[i+1]==0)
            {
                phase=2;
                //cout << "\nphase 2 - trying last prime less than ";
                //cout  << LIMIT2 << "\nprime= " << setw(8) << p;
                next_phase_pollard();
                btch*=100;
                i++;
                continue;
            }
            pa=p;
            while ((LIMIT1/p) > pa) pa*=p;
            b=pow(b,(int)pa);      /* b = b^pa mod n */
            q=b-1;
        }
        else
        { /* looking for last prime factor of (p-1) < LIMIT2 */
            p+=2;
            pos=p%MULT;
            if (pos>MULT/2) pos=giant_step_pollard();

        /* if neither interval+/-pos is prime, don't bother */
                if (!plus[pos] && !minus[pos]) continue;
            if (!cp[pos]) continue;
            q*=(bvw-bu[pos]);        /* batch gcd's in q */
        }
        if (i++%btch==0)
        { /* try for a solution */
            cout << "\b\b\b\b\b\b\b\b" << setw(8) << p << flush;
            t=gcd((Big)q,N);
            if (t==1)
            {
                if (p>LIMIT2) break;
                else continue;
            }
            if (t==N)
            {
                //cout << "\ndegenerate case";
                break;
            }
            //if (prime(t))   cout << "\nprime factor      " << t;
            //else            cout << "\ncomposite factor  " << t;
            N/=t;
			factor1=t;
			factor2=N;
            //if (prime(N)) cout << "\nprime factor      " << n;
            //else          cout << "\ncomposite factor  " << n;
			factorized = true;
			status |= THREAD_FACTORIZED;
			THREAD_END;
            return true;
        }
    } 
    //"\nfailed to factor\n";
	THREAD_END;
    return false;
}


void TutorialFactorisation::next_phase_williams()
{
	/* now change gear */
    ZZn t;
    long interval;
    fp=fu[1]=b;
    fd=b*b-2;
    fn=fd*b-b;
    for (int m=5;m<=MULT/2;m+=2)
    { /* store fu[m] = Vm(b) */
        t=fn*fd-fp;
        fp=fn;
        fn=t;
        if (!cp[m]) continue;
        fu[m]=t;
    }
    fd=luc(b,MULT);
    iv=p/MULT;
    if (p%MULT>MULT/2) iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks(interval);
    fvw=luc(fd,iv,&fp);
    q=fvw-fu[p%MULT];
}


int TutorialFactorisation::giant_step_williams()
{
	/* increment giant step */
    long interval;
    ZZn t;
    iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks(interval);
    t=fvw;
    fvw=fvw*fd-fp;
    fp=t;
    return 1;
}


BOOL TutorialFactorisation::Williams()
{
	THREAD_START;

	/*  factoring program using Williams (p+1) method */
    int k,phase,m,nt,pos,btch;
    long i,pa;
    Big t;
	//Big n;
    //mip=&precision;
    gprime(LIMIT1);
    for (m=1;m<=MULT/2;m+=2)
        if (igcd(MULT,m)==1) cp[m]=TRUE;
        else                 cp[m]=FALSE;
    //cout << "input number to be factored\n";
    //cin >> n;
    //if (prime(n))
    //{
        //cout << "this number is prime!\n";
        //return 0;
    //}
    modulo(N);                     /* do all arithmetic mod N */
    for (nt=0,k=3;k<10;k++)
    { /* try more than once for p+1 condition (may be p-1) */
        b=k;                       /* try b=3,4,5..        */
        nt++;
        phase=1;
        p=0;
        btch=50;
        i=0;
        //cout << "phase 1 - trying all primes less than " << LIMIT1;
        //cout << "\nprime= " << setw(8) << p;
        forever
        { /* main loop */
			m_iterations++;
			THREAD_CHECK;

            if (phase==1)
            { /* looking for all factors of p+1 < LIMIT1 */
                p=mip->PRIMES[i];
                if (mip->PRIMES[i+1]==0)
                { /* now change gear */
                    phase=2;
                    //cout << "\nphase 2 - trying last prime less than ";
                    //cout << LIMIT2 << "\nprime= " << setw(8) << p;
                    next_phase_williams();
                    btch*=100;
                    i++;
                    continue;
                }
                pa=p;
                while ((LIMIT1/p) > pa) pa*=p;
                q=luc(b,(int)pa);
                b=q;
                q-=2;
            }
            else
            { /* looking for last large prime factor of (p+1) */
                p+=2;
                pos=p%MULT;
                if (pos>MULT/2) pos=giant_step_williams();
                if (!cp[pos]) continue;

        /* if neither interval+/-pos is prime, don't bother */

                if (!plus[pos] && !minus[pos]) continue;
                q*=(fvw-fu[pos]);  /* batching gcds */
            }
            if (i++%btch==0)
            { /* try for a solution */
                //cout << "\b\b\b\b\b\b\b\b" << setw(8) << p << flush;
                t=gcd(q,N);
                if (t==1)
                {
                    if (p>LIMIT2) break;
                    else continue;
                }
                if (t==N)
                {
                    //cout << "\ndegenerate case";
                    break;
                }
                //if (prime(t)) cout << "\nprime factor     " << t;
                //else          cout << "\ncomposite factor " << t;
                N/=t;
                //if (prime(n)) cout << "\nprime factor     " << n;
                //else          cout << "\ncomposite factor " << n;
				factor1=t;
				factor2=N;
				factorized = true;
				status |= THREAD_FACTORIZED;
				THREAD_END;
                return true;
            }
        } 
        if (nt>=NTRYS) break;
        //cout << "\ntrying again\n";
    }
    //cout << "\nfailed to factor\n";
    //return 0;
	THREAD_END;
	return false;
}


void TutorialFactorisation::duplication(ZZn sum, ZZn diff, ZZn &x, ZZn &z)
{
	/* double a point on the curve P(x,z)=2.P(x1,z1) */
    ZZn t;
    t=sum*sum;
    z=diff*diff;
    x=z*t;        /* x = sum^2.diff^2 */
    t-=z;         /* t = sum^2-diff^2 */
    z+=ak*t;      /* z = ak*t +diff^2 */
    z*=t;	
}


void TutorialFactorisation::addition(ZZn xd, ZZn zd, ZZn sm1, ZZn df1, ZZn sm2, ZZn df2, ZZn &x, ZZn &z)
{
	/* add two points on the curve P(x,z)=P(x1,z1)+P(x2,z2) */
    /* given their difference P(xd,zd)                      */
    ZZn t;
    x=df2*sm1;
    z=df1*sm2;
    t=z+x;
    z-=x;
    x=t*t;
    x*=zd;   /* x = zd.[df1.sm2+sm1.df2]^2 */
    z*=z;
    z*=xd;   /* z = xd.[df1.sm2-sm1.df2]^2 */
}



void TutorialFactorisation::ellipse(ZZn x, ZZn z, int r, ZZn &x1, ZZn &z1, ZZn &x2, ZZn &z2)
{
	/* calculate point r.P(x,z) on curve */ 
    int k,rr;
    k=1;
    rr=r;
    x1=x;
    z1=z;
    duplication(x1+z1,x1-z1,x2,z2);  /* generate 2.P */
    while ((rr/=2)>1) k*=2;
    while (k>0)
    { /* use binary method */
        if ((r&k)==0)
        { /* double P(x1,z1) mP to 2mP */
            addition(x,z,x1+z1,x1-z1,x2+z2,x2-z2,x2,z2);
            duplication(x1+z1,x1-z1,x1,z1);
        }
        else
        { /* double P(x2,z2) (m+1)P to (2m+2)P */
            addition(x,z,x1+z1,x1-z1,x2+z2,x2-z2,x1,z1);
            duplication(x2+z2,x2-z2,x2,z2);
        }    
        k/=2;
    }
}


void TutorialFactorisation::next_phase_lenstra()
{
	/* now change gear */
    ZZn s1,d1,s2,d2;
    long interval;
    xt=x;
    zt=z;
    s2=x+z;
    d2=x-z;                    /* P = (s2,d2) */
    duplication(s2,d2,x,z);
    s1=x+z;
    d1=x-z;                    /* 2.P = (s1,d1) */
    fu[1]=x1/z1;
    addition(x1,z1,s1,d1,s2,d2,x2,z2);  /* 3.P = (x2,z2) */
    for (int m=5;m<=MULT/2;m+=2)
    { /* calculate m.P = (x,z) and store fu[m] = x/z */ 
        addition(x1,z1,x2+z2,x2-z2,s1,d1,x,z);
        x1=x2;
        z1=z2;
        x2=x;
        z2=z;
        if (!cp[m]) continue;
        fu[m]=x2/z2;        
    }
    ellipse(xt,zt,MULT,x,z,x2,z2);
    xt=x+z;
    zt=x-z;                           /* MULT.P = (xt,zt) */
    iv=p/MULT;
    if (p%MULT>MULT/2) iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    ellipse(x,z,iv,x1,z1,x2,z2);      /* (x1,z1) = iv.MULT.P */
    fvw=x1/z1;
    marks(interval);
    q=fvw-fu[p%MULT];  
}


int TutorialFactorisation::giant_step_lenstra()
{
	/* increment giant step */
    long interval;
    iv++;
    interval=(long)iv*MULT;
    p=interval+1;
    marks(interval);
    fvw=x2/z2;
    addition(x1,z1,x2+z2,x2-z2,xt,zt,x,z);
    x1=x2;
    z1=z2;
    x2=x;
    z2=z;
    return 1;   
}


BOOL TutorialFactorisation::Lenstra()
{
	 /*  factoring program using Lenstras Elliptic Curve method */
	THREAD_START;
	
    int phase,m,k,nc,pos,btch;
    long i,pa;
    Big t;
	//Big n;
    ZZn tt,u,v;
    //mip=&precision;
    gprime(LIMIT1);
    for (m=1;m<=MULT/2;m+=2) 
        if (igcd(MULT,m)==1) cp[m]=TRUE;
        else                 cp[m]=FALSE;
    //cout << "input number to be factored\n";
    //cin >> n;
    //if (prime(N))
    //{
        //cout << "this number is prime!\n";
        //return 0;
    //}
    modulo(N);                 /* do all arithmetic mod n */
    for (nc=1,k=6;k<100;k++)
    { /* try a new curve */
        u=k*k-5;
        v=4*k;
        x=u*u*u;
        z=v*v*v;

        ak=((v-u)*(v-u)*(v-u)*(3*u+v))/(16*u*u*u*v);

        phase=1;
        p=0;
        i=0;
        btch=50;
        //cout << "phase 1 - trying all primes less than " << LIMIT1;
        //cout << "\nprime= " << setw(8) << p;
        forever
        { /* main loop */
			m_iterations++;
			THREAD_CHECK;

            if (phase==1)
            {
                p=mip->PRIMES[i];
                if (mip->PRIMES[i+1]==0)
                { /* now change gear */
                    phase=2;
                    //cout << "\nphase 2 - trying last prime less than ";
                    //cout << LIMIT2 << "\nprime= " << setw(8) << p;
                    next_phase_lenstra();
                    btch*=100;
                    i++;
                    continue;
                }
                pa=p;
                while ((LIMIT1/p) > pa) pa*=p;
                ellipse(x,z,(int)pa,x1,z1,x2,z2);
                x=x1;
                q=z=z1;
            }
            else
            { /* looking for last large prime factor of (p+1+d) */
                p+=2;
                pos=p%MULT;
                if (pos>MULT/2) pos=giant_step_lenstra();
                if (!cp[pos]) continue;
        /* if neither interval +/- pos is prime, don't bother */
                if (!plus[pos] && !minus[pos]) continue;
                q*=(fvw-fu[pos]);        /* batch gcds */
            }
            if (i++%btch==0)
            { /* try for a solution */
                //cout << "\b\b\b\b\b\b\b\b" << setw(8) << p << flush;
                t=gcd(q,N);
                if (t==1)
                {
                    if (p>LIMIT2) break;
                    else continue;
                }
                if (t==N)
                {
                    //cout << "\ndegenerate case";
                    break;
                }
                //if (prime(t)) cout << "\nprime factor     " << t;
                //else          cout << "\ncomposite factor " << t;
                N/=t;
                //if (prime(N)) cout << "\nprime factor     " << N;
                //else          cout << "\ncomposite factor " << N;
				factor1=t;
				factor2=N;
				factorized = true;
				status |= THREAD_FACTORIZED;
				THREAD_END;
                return true;
            }
        }
        if (nc>NCURVES) break;
        //cout << "\ntrying a different curve " << nc << "\n";
    } 
    //cout << "\nfailed to factor\n";
	THREAD_END;
	return false;
}


//////////////////////////////////////////////////////////////////////////////////
//
// quadratic sieve
//

#define QS_INT_OVERFLOW     -114473
#define QS_ALLOCATING_ERROR -314159
#define QS_WARNING          -783264

int TutorialFactorisation::initv()
{
    /* debug */
	double memory_used = 0.0;
	/* initialize */
    Big T;
    double dp;
    int i,k,digits,pak,maxp;
	//int j;
    nbts=8*sizeof(int);

    if (prime(NN))
    {
        
		//this number is prime
        return (-1);
    }
	

    T=NN;
    digits=1;                   /* digits in N */
    while ((T/=10)>0) digits++;
	int bt = bits(NN);

    if (digits<10) mmm=digits;               
    else mmm=25;
	{
		double d_mmm = (digits*digits*digits*digits)/4096.0;
		double d = (double)(INT_MAX/2)/max(sizeof(Big), sizeof(int*));
		if ( d_mmm > (double)(INT_MAX/2)/max(sizeof(Big), sizeof(int*)) )
		{
			return -1;
		}
	}
    if (digits>20) mmm=(digits/4096)*digits*digits*digits;

    dp=(double)2*(mmm+100);          /* number of primes to generate */

    maxp=(int)(dp*(log(dp*log(dp)))); /* Rossers upper bound */
    gprime(maxp);

    if ( mmm < 0 )         return QS_INT_OVERFLOW;
    // if ( mmm > 268435456 ) return QS_WARNING; 
    epr=(int *)mr_alloc(mmm+1,sizeof(int));
    if ( epr == NULL )
    {
        return QS_ALLOCATING_ERROR;
    }	    
	memory_used += double((mmm+1)*sizeof(int));

    k=knuth(mmm,epr,NN,DD);

    RR=sqrt(DD);

    if (RR*RR==DD)
    {
        // N is a perfect square!"
		// factors are
        if (prime(RR)) 
		{
			// N has a perfect prime-square!" Sollte also sollen die zwei Faktoren schwarz markiert werden!!
		}
        else
		{
			// N has a perfect composite-square!" Sollte also sollen die zwei Faktoren rot markiert werden!!
		}

        NN=NN/RR;
		if (prime(NN)) 
		{
			// N is a perfect prime-square!" Sollte also sollen die zwei Faktoren schwarz markiert werden!!
		}
		 else
		{
			// N is a perfect composite-square!" Sollte also sollen die zwei Faktoren rot markiert werden!!
		}

        return (-2);
    }
//    cout << "using multiplier k= " << k;
//    cout << "\nand " << mmm << " small primes as factor base\n";
    gprime(0);   /* reclaim PRIMES space */

    mlf=2*mmm;    

    r1=(int *)mr_alloc((mmm+1),sizeof(int));
    r2=(int *)mr_alloc((mmm+1),sizeof(int));
    rp=(int *)mr_alloc((mmm+1),sizeof(int));
    bb=(int *)mr_alloc((mmm+1),sizeof(int));
	//bb=(unsigned int *) mr_alloc((mmm+1),sizeof(int));
    e=(int *)mr_alloc((mmm+1),sizeof(int));

    logp=(unsigned char *)mr_alloc(mmm+1,1);

    pr=(int *)mr_alloc((mlf+1),sizeof(int));
    hash=(int *)mr_alloc(2*mlf+1,sizeof(int));

    sieve=(unsigned char *)mr_alloc(SSIZE+1,1);

    if ( r1 == NULL || r2 == NULL || rp == NULL || e == NULL 
	  || logp == NULL || pr == NULL || hash == NULL || sieve == NULL )
    {
        return QS_ALLOCATING_ERROR;
    }	    
	memory_used += double(6*(mmm+1)*sizeof(int)+(3*mlf+1)*sizeof(int) + SSIZE+1);

    xx=new Big[mmm+1];
    yy=new Big[mmm+1];
    zz=new Big[mlf+1];
    ww=new Big[mlf+1];
	memory_used += double(2*(mmm+mlf+4)*sizeof(Big));

	if ( xx == NULL || yy == NULL || zz == NULL || ww == NULL )
	{
		return QS_ALLOCATING_ERROR;
	}

	EE=(unsigned int **)mr_alloc(mmm+1,sizeof(unsigned int *));
    G=(unsigned int **) mr_alloc(mlf+1,sizeof(unsigned int *));
	if ( EE == NULL || G == NULL )
    {
        return QS_ALLOCATING_ERROR;
    }
	memory_used += double((mmm+mlf+2)*sizeof(int*));

    pak=1+mmm/(8*sizeof(int));
	memory_used += double((mmm+mlf+2)*sizeof(int)*pak);
    for (i=0;i<=mmm;i++)
    { 
		THREAD_CHECK;
        xx[i]=0;
        yy[i]=0;
        bb[i]=(-1);
        EE[i]=(unsigned int *)mr_alloc(pak,sizeof(int)); //Roger
		if ( EE[i] == NULL )
		{
			return QS_ALLOCATING_ERROR;
		}
    }
    for (i=0;i<=mlf;i++)
    {
		THREAD_CHECK;
        zz[i]=0;
        ww[i]=0;
        G[i]=(unsigned int *)mr_alloc(pak,sizeof(int)); //Roger
		if ( G[i] == NULL )
		{
			return QS_ALLOCATING_ERROR;
		}
    }
    return 1;
}

int TutorialFactorisation::knuth(int mmm, int *epr, Big &N, Big &D)
{
	/* Input number to be factored N, find best multiplier k  */
    /* set D=k.N */
    Big T;
    double fks,dp,top;
    BOOL found;
    int i,j,bk,nk,kk,rem,p;
	static int pk[]={0,1,2,3,5,6,7,10,11,13,14,15,17,0};

    top=(-10.0e0);
    found=FALSE;
    nk=0;
    bk=0;
    epr[0]=1;
    epr[1]=2;

    do
    { /* search for best Knuth-Schroepel multiplier */
	//	THREAD_CHECK; //Roger:05.12.2001 -- wegen Speicherplatz des QSieb
        
		kk=pk[++nk];
        if (kk==0)
        { /* finished */
            kk=pk[bk];
            found=TRUE;
        }
        D=kk*N;
        fks=log(2.0e0)/(2.0e0);
        rem=D%8;
        if (rem==1) fks*=(4.0e0);
        if (rem==5) fks*=(2.0e0);
        fks-=log((double)kk)/(2.0e0);
        i=0;
        j=1;

        while (j<mmm)
        { /* select small primes */
			//THREAD_CHECK; //Roger:05.12.2001 -- wegen Speicherplatz des QSieb
            p=mip->PRIMES[++i];
            rem=D%p;
            if (spmd(rem,(p-1)/2,p)<=1) /* x = spmd(a,b,c) = a^b mod c */
            { /* use only if Jacobi symbol = 0 or 1 */
                epr[++j]=p;
                dp=(double)p;
                if (kk%p==0) fks+=log(dp)/dp;
                else         fks+=2*log(dp)/(dp-1.0e0);
            }
        }
        if (fks>top)
        { /* find biggest fks */
            top=fks;
            bk=nk;
        }
    } while (!found);
    return kk;	
}

void TutorialFactorisation::new_poly()
{
	/* form the next polynomial */
    int i,r,s,s1,s2;
   
    r=mip->NTRY;        /* MR_NTRY is global - number of trys at proving */
    mip->NTRY=1;        /* a probable prime  */
    do
    { /* looking for suitable prime DG = 3 mod 4 */
        do DG+=4; while(!prime(DG));
        TT=(DG-1)/2;
        TT=pow(DD,TT,DG);  /*  check DD is quad residue */
    } while (TT!=1);
    mip->NTRY=r;
    TT=(DG+1)/4;
    BB=pow(DD,TT,DG);
    TT=(DD-BB*BB)/DG;
    AA=inverse(2*BB,DG);
    AA=(AA*TT)%DG;
    BB=AA*DG+BB;       /* BB^2 = DD mod DG^2  */
    AA=DG*DG;
    IG=inverse(DG,DD); /*  IG = 1/DG mod DD  */ 
    r1[0]=r2[0]=0;
    for (i=1;i<=mmm;i++) 
    { /* find roots of quadratic mod each prime */
        s=BB%epr[i];
        r=AA%epr[i];
        r=invers(r,epr[i]);      /* r = 1/AA mod p */
        s1=(-s+rp[i]);
        s2=(-s-rp[i]);
        r1[i]=smul(s1,r,epr[i]);  /* s1 = s1*r mod epr[i] */
        r2[i]=smul(s2,r,epr[i]);  
    }
}

bool TutorialFactorisation::factored(long lptr, Big &T)
{
	/* factor quadratic residue T */
    bool facted;
    int i,j,r,st;  
    partial=false;
    facted=false;
    for (j=1;j<=mmm;j++)
    { /* now attempt complete factorisation of T */
        r=lptr%epr[j];
        if (r<0) r+=epr[j];
        if (r!=r1[j] && r!=r2[j]) continue;
        while (T%epr[j]==0)
        { /* cast out epr[j] */
            e[j]++;
            T/=epr[j];
        }
        st=toint(T);      /*  st = T as an int; st=TOOBIG if too big */
        if (st==1)
        {
           facted=true;
           break;
        }
        if ((T/epr[j])<=epr[j])
        { /* st is prime < epr[mmm]^2 */
            if (st==MR_TOOBIG || (st/epr[mmm])>(1+mlf/50)) break;
            if (st<=epr[mmm])
                for (i=j;i<=mmm;i++)
                if (st==epr[i])
                {
                    e[i]++;
                    facted=true;
                    break;
                }
            if (facted) break;
            lp=st;  /* factored with large prime */
            partial=true;
            facted=true;
            break;
        }
    }
    return facted;
}

bool TutorialFactorisation::gotcha(Big &NN, Big &P)
{
	/* use new factorisation */
    Big XX,YY,T;
    int r,j,i,k,n,rb,had,hp;
    bool found;
    found=true;
    if (partial)
    { /* check partial factorisation for usefulness */
        had=lp%hmod;
        forever
        { /* hash search for matching large prime */
            hp=hash[had];
            if (hp<0)
            { /* failed to find match */
                found=false;
                break;
            }
            if (pr[hp]==lp) break; /* hash hit! */
            had=(had+(hmod2-lp%hmod2))%hmod;
        }
        if (!found && nlp>=mlf) return false;
    }
    XX=P;
    YY=1;
    for (k=1;k<=mmm;k++)
    { /* build up square part in YY  *
       * reducing e[k] to 0s and 1s */
        if (e[k]<2) continue;
        r=e[k]/2;
        e[k]%=2;
        T=epr[k];
        YY*=pow(T,r);
    }
    if (partial)
    { /* factored with large prime */
        if (!found)
        { /* store new partial factorization   */
            hash[had]=nlp;
            pr[nlp]=lp;
            zz[nlp]=XX;
            ww[nlp]=YY;
            for (n=0,rb=0,j=0;j<=mmm;j++)
            {
                G[nlp][n]|=((e[j]&1)<<rb); //roger
                if (++rb==nbts) n++,rb=0;
            }
            nlp++;         
        }
        if (found)
        { /* match found so use as factorization  */
            cout << "\b\b\b\b\b*";
            XX=(XX*zz[hp])%NN;
            YY=(YY*ww[hp])%NN;
            for (n=0,rb=0,j=0;j<=mmm;j++)
            {
                e[j]+=((G[hp][n]>>rb)&1);
                if (e[j]==2)
                {
                    YY=(YY*epr[j])%NN;
                    e[j]=0;
                }
                if (++rb==nbts) n++,rb=0;
            }
            YY=(YY*lp)%NN; 
        }
    }
    
    
	if (found)
    {
        for (k=mmm;k>=0;k--)
        { /* use new factorization in search for solution */
            if (e[k]%2==0) continue;
            if (bb[k]<0)
            { /* no solution this time */
                found=false;
                break;
            }
            i=bb[k];
            YY=(YY*yy[i])%NN;    /* There must be a better way! */
			XX=(XX*xx[i])%NN;    /* This is very inefficient -  */
            //YY=(YY*yy[i])%NN;    /* There must be a better way! */
            for (n=0,rb=0,j=0;j<=mmm;j++)
            { /* Gaussian elimination */
                e[j]+=((EE[i][n]>>rb)&1);//roger
                if (++rb==nbts) n++,rb=0;
            }
        }
        for (j=0;j<=mmm;j++)
        { /* update YY */
            if (e[j]<2) continue;
            T=epr[j];
            YY=(YY*pow(T,e[j]/2,NN))%NN;  /* x = pow(a,b,c) = a^b mod c */
        }
        if (!found)
        { /* store details in EE, x and y for later  */
            bb[k]=jj;
            xx[jj]=XX;
            yy[jj]=YY;
            for (n=0,rb=0,j=0;j<=mmm;j++)
            {
                EE[jj][n]|=((e[j]&1)<<rb);//roger
                if (++rb==nbts) n++,rb=0;
            }
            jj++;
            cout << setw(4) << jj; 
        }
    }
    if (found)
    { /* check for false alarm */
        P=XX+YY;
//        cout << "\ntrying...\n";
        if (XX==YY || P==NN) found=false;
//        if (!found) cout << "working... " << setw(4) << jj << flush;
    }
    return found;
}


BOOL TutorialFactorisation::QuadraticSieve()
{
	THREAD_START;

	/* factoring via quadratic sieve */
	
	int i;
    unsigned int j,a,*SV;
    unsigned char logpi;
    int S,r,s1,s2,NS,logm,ptr,threshold,epri;
    long M,la,lptr;

	NN=N;    
	
	int result_initv;
	result_initv=initv();

	if ( result_initv == QS_ALLOCATING_ERROR || result_initv == QS_INT_OVERFLOW )
	{
               factorized = false;
	       THREAD_END;
	       return false;
	}
	if (result_initv==-1)
	{
		//this number is prime
		factorized = true;
		status |= THREAD_FACTORIZED;
		THREAD_END;
		return true;
	}

	if (result_initv==-2)
	{
		//this number is a perfect square! <-----Ob diese stimmt, bin ich am zweifeln ----Roger 30.10.2001
		factor1=NN;
		factor2=RR;
		factorized = true;
		status |= THREAD_FACTORIZED;
		THREAD_END;
		return true;
	}

    hmod=2*mlf+1;               /* set up hash table */
    TT=hmod;
    while (!prime(TT)) TT-=2;
    hmod=toint(TT);
    hmod2=hmod-2;
    for (i=0;i<hmod;i++) hash[i]=(-1);

    M=50*(long)mmm;
    NS=M/SSIZE;
    if (M%SSIZE!=0) NS++;
    M=SSIZE*(long)NS;
    logm=0;
    la=M;
    while ((la/=2)>0) logm++;   /* logm = log(M) */

    rp[0]=0;
	logp[0]=0;
    for (i=1;i<=mmm;i++)
    { /* find root mod each prime, and approx log of each prime */
		THREAD_CHECK;

        r=DD%epr[i];
        rp[i]=sqrmp(r,epr[i]);     /* = square root of r mod epr[i] */
        logp[i]=0;
        r=epr[i];
        while((r/=2)>0) logp[i]++;
    }
    r=DD%8;             /* take special care of 2  */
    if (r==5) logp[1]++;
    if (r==1) logp[1]+=2;
    threshold=logm-2*logp[mmm];
 
    jj=0;
    nlp=0;

    TT=RR;
    while ((TT/=2)>0) threshold++;   /*  add in number of bits in RR */
    DG=sqrt(DD*2);
    DG=sqrt(DG/M);
    if (DG%2==0) ++DG;
    if (DG%4==1) DG+=2;

    forever
    { /* try a new polynomial  */
		m_iterations++;
		THREAD_CHECK;

        new_poly();

        for (ptr=(-NS);ptr<NS;ptr++)
        { /* sieve over next period */
			THREAD_CHECK;

            la=(long)ptr*SSIZE;
            SV=(unsigned int *)sieve;
            for (i=0;i<SSIZE/sizeof(int);i++) *SV++=0;
            for (i=1;i<=mmm;i++)
            { /* sieving with each prime */
                epri=epr[i];
                logpi=logp[i];
                r=la%epri;
                s1=(r1[i]-r)%epri;
                if (s1<0) s1+=epri;
                s2=(r2[i]-r)%epri;
                if (s2<0) s2+=epri;
                for (j=s1;j<SSIZE;j+=epri) sieve[j]+=logpi;
                if (s1==s2) continue;
                for (j=s2;j<SSIZE;j+=epri) sieve[j]+=logpi;
            }

            for (a=0;a<SSIZE;a++)
            {  /* main loop - look for fully factored residues */
                if (sieve[a]<threshold) continue;
                lptr=la+a;
                S=0;
                TT=AA*lptr+BB;
                PP=(TT*IG)%DD;             /*  PP = (AAx + BB)/G */
                if (PP<0) PP+=DD;
                VV=(PP*PP)%DD;             /*  VV = PP^2 mod kN  */
                if (TT<0) TT=(-TT);
                if (TT<RR) S=1;            /*  check for -ve VV  */
                if (S==1) VV=DD-VV;
                e[0]=S;
                for (i=1;i<=mmm;i++) e[i]=0;
                if (!factored(lptr,VV)) continue;
                if (gotcha(NN,PP))
                { /* factors found! */
                    PP=gcd(PP,NN);
	                //factors are";
                    if (prime(PP))
					{
						// PP ist ein Primfaktor von N, sollte deshalb sschwarz markiert sein!
					}
                    else
					{
						// PP ist ein zusammengesetztes Faktor von N, sollte also rot markiert werden!
					}
                    NN/=PP;
                    if (prime(NN))
					{
						// NN ist ein Primfaktor von N, sollte deshalb sschwarz markiert sein!
					}
                    else
					{
						// NN ist ein zusammengesetztes Faktor von N, sollte also rot markiert werden!
					}
                    					
					factor1=PP;
					factor2=NN;
					factorized = true;
					status |= THREAD_FACTORIZED;
					THREAD_END;
					return true;
                }
            }
        }
    }
	THREAD_END;
	return false;
}


//void TutorialFactorisation::SetN(CString &NStr)
int TutorialFactorisation::SetN(CString &NStr)
{
	BOOL output;
	set_mip(mip);
	output=evaluate::eval( N, NStr.GetBuffer( 256 ));
	if (output==false)  return EVAL_ERR; // Zahl mit Bitlänge >= 1024, oder sonstige Miracl-Fehler
	else if ( N < 0 ) return EVAL_NEG; //Da wir nur mit positiven ganzen Zahlen arbeiten!! (oder villeicht nicht??!!)
	else if ( N == 0 ) return EVAL_NULL;
	else if ( N == 1 ) return EVAL_EINS;
	else return EVAL_OK; 
}


void TutorialFactorisation::GetFactor1Str(CString &Factor1)
{
	set_mip(mip);
	BigToCString( factor1, Factor1 );
}


void TutorialFactorisation::GetFactor2Str(CString &Factor2)
{
	set_mip(mip);
	BigToCString( factor2, Factor2 );
}



//////////////////////////////////////////////////////////////////////
// PseudoRandomGenerator Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

PseudoRandomGenerator::PseudoRandomGenerator()
{
	Seed = 314159;
	RandNo = Seed;
}

PseudoRandomGenerator::~PseudoRandomGenerator()
{
}

BOOL PseudoRandomGenerator::setSeed(CString &SeetStr)
{
	BOOL retValue = CStringFormulaToBig( SeetStr, Seed );
	RandNo = Seed;
	return retValue;
}


//////////////////////////////////////////////////////////////////////
// x2modN_generator Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

x2modN_generator::x2modN_generator()
{
	CString tmp = STANDARD_X2MOD_N_MODUL;
	CStringFormulaToBig( tmp, Modul_N );
}

x2modN_generator::~x2modN_generator()
{

}

BOOL x2modN_generator::setModul( CString &NStr )
{
	return CStringFormulaToBig( NStr, Modul_N );
}

void x2modN_generator::randomize()
{
	Big two = 2;
	Big tmp = RandNo;
	RandNo  = pow( tmp, two, Modul_N );
}


long x2modN_generator::randBit()
{
	randomize();
	return RandNo % 2;
}


//////////////////////////////////////////////////////////////////////
// LlinearCongruenceGenerator Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

LinearCongruenceGenerator::LinearCongruenceGenerator()
{
	N = 100000001;
	a = 23; 
	b = 0;
}

LinearCongruenceGenerator::~LinearCongruenceGenerator()
{
}

BOOL LinearCongruenceGenerator::SetParameter(CString &aStr, CString &bStr, CString &NStr)
{
	return ( CStringFormulaToBig( aStr, a ) && CStringFormulaToBig( bStr, b ) &&
		     CStringFormulaToBig( NStr, N ) );
}

void LinearCongruenceGenerator::randomize()
{
	RandNo = (a*RandNo + b) % N;
}

long LinearCongruenceGenerator::randBit()
{
	randomize();
	return (RandNo > N/2) ? 1 : 0;
}


//////////////////////////////////////////////////////////////////////
// InverseCongruenceGenerator Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

InverseCongruenceGenerator::InverseCongruenceGenerator()
{
	N = 2147483053;
	a = 22211;
	b = 11926380;
	count = 0;
}

InverseCongruenceGenerator::~InverseCongruenceGenerator()
{
}

BOOL InverseCongruenceGenerator::SetParameter( CString &aStr, CString &bStr, CString &NStr )
{
	return ( CStringFormulaToBig( aStr, a ) && CStringFormulaToBig( bStr, b ) && 
			 CStringFormulaToBig( NStr, N ) );
}

void InverseCongruenceGenerator::randomize()
{
	RandNo = inverse( a * ( Seed + count ) + b, N) % N;
}

BOOL InverseCongruenceGenerator::SetCount( long n )
{
	return ( count = n );
}

long InverseCongruenceGenerator::randBit()
{
	randomize();
	return (RandNo >  N/2) ? 1 : 0;
}


//////////////////////////////////////////////////////////////////////
// CTutorialFactorisationBase Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CTutorialFactorisationBase::CTutorialFactorisationBase()
{
	m_old_mip = get_mip();
	mirsys(50,0);
	mip = get_mip();
	set_mip(m_old_mip);
}

CTutorialFactorisationBase::~CTutorialFactorisationBase()
{
	set_mip(mip);
	mirexit();
	set_mip(m_old_mip);
}
