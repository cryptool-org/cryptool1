/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/


//////////////////////////////////////////////////////////////////////
// CryptologyUsingMiracl.cpp: Implementierung der Klasse evaluate.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "IntegerArithmetic.h"

#include <monty.h>
#include "DlgProgressFactorisation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static Miracl g_precision=MAX_BIT_LENGTH/32;

#ifndef MULTITHREAD
extern CDlgProgressFactorisation dlg;
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


//////////////////////////////////////////////////////////////////////
// Approximiert den Logarithmus zur Basis 2 der Zahl N mit Hilfe der 
// Bitlängen-Funktion bits(N) 
//

double approxLog2(Big &N)
{
	if ( N <= 0 )  // FIXME
		return bits(N);
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

	double ret_val = log((double) d_num/d_dom)/log((double) 2) + double(b);
	return ret_val;
}


/////////////////////////////////////////////////////////////////////////
// Logarithmus zur Basis 2 für eine als String repräsentierte Zahl
// Siehe obige Funktion approxLog2()
//

double  BitLength( CString &number, int base )
{
	Big t;
	CStringToBig( number, t, base );
	return approxLog2(t);
}


/////////////////////////////////////////////////////////////////////////////////
// GetNumber extrahiert aus dem CString Formula ab dem Index "ndx" einen 
// Zahlenstring zur Basis base. Danach wird der Index "ndx" um die Anzahl der
// ausgewerteten Ziffern erhöht. Der Zahlenstring wird im CString number 
// zurückgegeben

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


////////////////////////////////////////////////////////////////////////////////
// CheckFormula überprüft die Formeldarstellung für eine Zahl auf syntaktische 
// Korrektheit und vereinfacht ausdrücke wie "++-" nach "-". Wenn sich aus der 
// Formel eine Zahl berechnen lässt, wird der neu formatierte String in der 
// variablen Formula mit dem Funktionswert TRUE zurückgegeben. 
// Andernfalls ist der Funktionswert FALSE, und die Poition, wo der Fehler 
// bei der Auswertung aufgetreten ist, wird in der Variablen ndx (Fehlerindex)
// übergeben. 

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
		if (stack_i + 2 >= sizeof(stack))
			return FALSE;
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


////////////////////////////////////////////////////////////////////////////////
// Wandelt eine als CString repräsentierte Zahl in eine Big-Zahl um.
// 

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
	BOOL success=evaluate::CEvalIntExpr(t, tmp); 
	if ( !success ) t = 0;	
	delete []tmp;
	return success;
}


/////////////////////////////////////////////////////////////////////////////////
// Berechnet den Formelausdruck für eine Zahl (Variable CStrExpr) und speichert 
// diese Zahl als CString in der Variablen CStrExpr. 

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
// Nur temporär & lokal definiert, check auf ch \in {<SPACE>, <TAB>, <NL>, <CR>}

inline
BOOL NewLineTabSpace( char ch )
{
	return isCharOf( ch, " \t\r\n");
}


/////////////////////////////////////////////////////////////////////////////////
// Rückgabe ist TRUE, wenn die Eingabe eine Folge (getrennt durch <Space>, "," 
// oder "#") von Zahlen ist. Die Eingabe CStr wird formatiert:
// "Zahl_1 # Zahl_1 # .... # Zahl_n" 
//
// Beipiel: Eingabe "32DFE4 4EA5,445 67EF45a", 16
//          Ausgabe "32DFE4 # 4EA5 # 445 # 67EF45A"

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
				if ( FORMAT_MODULO == (FORMAT_MODULO & flagList) )
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
// Konvertiert eine char* repräsentierte Zahl in eine Big-Zahl
// 

int StringToBig( const char* StrNumber, Big &t, int base )
{
	char *tmp;
	tmp = new char[strlen(StrNumber)+1];
	int i = 0,j;
	while ( NewLineTabSpace(StrNumber[i]) && StrNumber[i] ) i++;
	for ( j=0; StrNumber[i] != 0; i++) {
		if ( IsNumber(StrNumber[i], base) ) tmp[j++] = StrNumber[i];
		else break;
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

BOOL HexDumpToNumstr( CString &CSHexDump, CString &CSOutNum, int base_outnum, CString &CSModul, int base_modul  )
{
	Big b_num, b_modul;
	int i = 0;

	CSOutNum = CSHexDump;
	CStringToBig( CSModul, b_modul, base_modul );
	do {
		if ( CSOutNum[i] == ' ' )
			CSOutNum.Delete(i);
		else
		{
			if ( CSOutNum[i] == '#' )
				break;
			if ( !IsNumber( CSOutNum[i], 16 ) )
				return FALSE;
			i++;
		}
	} while ( i < CSOutNum.GetLength() );
	
	CStringToBig( CSOutNum, b_num, 16 );
	if ( b_modul > 1 && b_num >= b_modul )
		return FALSE;
	
	BigToCString( b_num, CSOutNum, base_outnum );
	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Dekodiert eine als char* repräsentierte Zahl in eine Folge von Zeichen aus dem Buchstaben-
// Vorrat des des übergebenen Alphabetes und speichert das bestimmte Wort in der Variablen
// Data ab. Da bei der Kodierung auch in die Zahl Null kodiert wird, ist für die korrekte 
// Dekodierung die Variable blockLength nötig.
// 

int decode( const char *StrNumber, char *data, size_t datalen, int blockLength, int numberBase, BOOL basisSystem, const char *CPlayfairAlphabet )
{
	Big t;
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = numberBase;
	StringToBig( StrNumber, t, numberBase);

	char tmp[MAX_BIT_LENGTH/8+1];
	int i, modul, digits, alphabetLength;
	alphabetLength = ( CPlayfairAlphabet == NULL ) ? 256 : strlen(CPlayfairAlphabet);
    digits = (int)ceil(log((double)alphabetLength)/log((double)numberBase));
    if ( basisSystem )
	{
        modul  = numberBase;
        for (i=1; i<digits; i++) modul *= numberBase;
	}
    else   modul = alphabetLength;

	for ( i=0; i < blockLength || t != 0; i++ )
	{
 	   	char ch = (CPlayfairAlphabet == NULL) ? (t % modul) % alphabetLength : CPlayfairAlphabet[(t % modul) % alphabetLength];
	   	t = t / modul;
       	tmp[sizeof(tmp)-(i+1)] = ch;
	}
	ASSERT((unsigned int)(i + 1) < datalen);

	int j;
	for (j=sizeof(tmp)-i; j<sizeof(tmp); j++ )
	{
	    data[j-(sizeof(tmp)-i)] = tmp[j];
	}
    data[j-(sizeof(tmp)-i)] = '\0';
	return i;
}

int decode( CString &CStringNumber, char *data, size_t datalen, int blockLength, int numberBase, BOOL BasisSystem, const char *CPlayfairAlphabet )
{
    return decode(CStringNumber.GetBuffer(CStringNumber.GetLength()+1), data, datalen, blockLength, numberBase, BasisSystem, CPlayfairAlphabet );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Konvertiert eine Big-Zahl in die char* Darstellung (Zahlen zur Basis base).
// Die Ausgabe wird mit Nullen bis zur Länge OutLength aufgefüllt
// 

void BigToString(const Big&t, char *NumStr, size_t NumStrLen, int base, size_t OutLength)
{
	miracl *mip = &g_precision;
	int oldBase = mip->IOBASE;
	mip->IOBASE = base;
	if (mip->IOBSIZ < MAX_BIT_LENGTH + 1)
		set_io_buffer_size(MAX_BIT_LENGTH + 1);
	char tmpStr[MAX_BIT_LENGTH + 1];
	tmpStr << t;
	size_t i;
	size_t diff;
	size_t tmpStrLen = strlen(tmpStr);
    diff = ( OutLength > tmpStrLen ) ? OutLength - strlen(tmpStr) : 0;
	ASSERT(tmpStrLen+diff+1 < NumStrLen);
    if (diff > 0) for(i=0; i<diff; i++) NumStr[i] = '0';
    strcpy(NumStr+diff, tmpStr);
	mip->IOBASE = oldBase;
}

void BigToCString(const Big &t, CString &NumCStr, int base, size_t OutLength )
{
    char tmpStr[MAX_BIT_LENGTH + 1];
    BigToString( t, tmpStr, sizeof(tmpStr), base, OutLength );
    NumCStr = tmpStr;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Wechselt die Basisdarstellung der Zahlen von baseFrom nach baseTo
//

void BaseRepr( CString &StrNum, int baseFrom, int baseTo)
{
	Big t;
	CStringToBig(StrNum, t, baseFrom );
	BigToCString(t, StrNum, baseTo);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Kodiert die Eingabe data: ein Octet-String oder einen Text mit Zeichen aus 
// CPlayfairAlphabet in eine Zahlenfolge ("Zahl_1 # Zahl_2 # ... # Zahl_n"). 
// Die Eingabe wird dabei Zunächst in Segmenten der Länge blockLength aufgeteilt.

void encode( const char *data, char *numStr, size_t numStrLen, int blockLength, int numberBase, 
			 BOOL basisSystem, const char *CPlayfairAlphabet )
{
	Big tmp = 0;
	size_t outLength = 0;

	int i,j, modul, digits, alphabetLength;
	alphabetLength = ( CPlayfairAlphabet == NULL ) ? 256 : strlen(CPlayfairAlphabet);
   	digits = (int)ceil(log((double)alphabetLength)/log((double)numberBase));
   	if ( basisSystem )
	{
    	modul = numberBase;
       	for (i=1; i<digits; i++) modul *= numberBase;
		outLength = digits * blockLength;
	} 
   	else    
	{
		outLength = (int)ceil((log((double)alphabetLength)/log((double)numberBase))*blockLength);
		modul = alphabetLength;
	}
   	for ( i=0; i<blockLength; i++ )
	{
    	if ( CPlayfairAlphabet )
		{
			for ( j=0; j < modul && data[i] != CPlayfairAlphabet[j]; ) j++;
		}
       	else            
		{
			j = (unsigned char)data[i];
		}
    	tmp *=modul;
       	tmp += j;
   	}
	BigToString( tmp, numStr, numStrLen, numberBase, outLength );
}

void encode( const char *data, CString &numCStr, int blockLength, int numberBase, 
			 BOOL basisSystem, const char *CPlayfairAlphabet )
{
    char tmp[MAX_BIT_LENGTH + 1];
    encode ( data, tmp, sizeof(tmp), blockLength, numberBase, basisSystem, CPlayfairAlphabet );
    numCStr = tmp;
}

////////////////////////////////////////////////////////////////////////////////////
// Wählt randomisiert eine zu StrNum (mod Modul) äquivalente Zahl. 
//

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

///////////////////////////////////////////////////////////////////////////////////
// Umkehrung von RandRepr(..)
// 

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
// Berechnet eine Zufallszahl aus dem Bereich [lower, upper]
//

void RandomWithLimits(Big &r, const Big &lower, const Big &upper)
{
	r=lower;
	if ( upper > lower )
	{
		r=rand(upper-(lower-1))+(lower-0);
	}
}


//////////////////////////////////////////////////////////////////////
// Berechnet die Zahl zur Formeldarstellung Str
//

static char *s;
static Big  temp;

BOOL evaluate::CEvalIntExpr( Big& value, const char * Str )
{
	miracl *mip = &g_precision;
	mip->IOBASE=10;
    s = (char*)Str;
	try {
		if ( CEvalIntExpr() ) {
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
		if (n < 0) throw eval_err( EVAL_ERR_POW );
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

BOOL evaluate::CEvalIntExpr()
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
		CEvalIntExpr ();
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
		}
		op=s[i];
		s[i]=0;

		if ( log(10.0)/log(2.0)*i > MAX_BIT_LENGTH ) 
		{
			throw eval_err( EVAL_ERR_STR_NUMBER );
		}
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
				}
			}
		}
	}
	goto LOOP;

}


//////////////////////////////////////////////////////////////////////
// GeneratePrimes Klasse
//////////////////////////////////////////////////////////////////////
// Primzahlen mit Hilfe von Zufallstests bestimmen ...
// 
// Die Klaesse GeneratePrimes hat verschiedene randomisierte Tests 
// für Primzahelen implementiert

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

///////////////////////////////////////////////////////////////////////////////
// Setzt den Wertebereich, wo Primzahlen gefunden werden 
//

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
	if ( evaluate::CEvalIntExpr( LowerLimit, LowerLimitStr.GetBuffer( 256 ) ) == false )
	{
		//LowerLimit hat mehr als 1024 bit
		return 3;
	}
	if ( evaluate::CEvalIntExpr( UpperLimit, UpperLimitStr.GetBuffer( 256 ) ) == false )
	{
		//UpperLimit hat mehr als 1024 bit
		return 2;
	}
	BOOL Out_Set_Lim;
	Out_Set_Lim = SetLimits( LowerLimit, UpperLimit );
		
	if (Out_Set_Lim) return 1;
	//UpperLimit>LowerLimit
	else return 0;  //Eingabe sind OK
}


///////////////////////////////////////////////////////////////////////////////
// Solvay-Strassen Test

BOOL GeneratePrimes::SolvayStrassenTest(unsigned long probabilityThreshold)
{
	if (!PrimalityKnownAfterTrialDivision(p))
	{	
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


///////////////////////////////////////////////////////////////////////////////
// Miller-Rabin Test
//

BOOL GeneratePrimes::MillerRabinTest(unsigned long probabilityThreshold)
{
	if (!PrimalityKnownAfterTrialDivision(p))
	{	
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

//////////////////////////////////////////////////////////////////////////////////////
// Test primality of p by trial division with some small factors and set Error & GP_ERROR_NOPRIME 
// accordingly.
// Return TRUE if (non-)primality of p is known
BOOL GeneratePrimes::PrimalityKnownAfterTrialDivision(const Big& p)
{
	Error &= 0xFFFFFFFF ^ GP_ERROR_NOPRIME; // clear GP_ERROR_NOPRIME;
	if (2 == p  || 3 == p  || 5 == p  || 7 == p || 
			11 == p || 13 == p || 17 == p || 19 == p || 
			23 == p || 29 == p || 31 == p || 37 == p) {
		return TRUE; // primality of p is known (p is a prime)
	}
	if (p <= 1 || 0 == p % 2  || 0 == p % 3  || 0 == p % 5  || 0 == p % 7 ||
			 0 == p % 11 || 0 == p % 13 || 0 == p % 17 || 0 == p % 19 ||
			 0 == p % 23 || 0 == p % 29 || 0 == p % 31 || 0 == p % 37 ) {
		Error |= GP_ERROR_NOPRIME; // p is not prime
		return TRUE; // primality of p is known (p is not prime)
	}
	return (p <= 37*37); // primality of p is known if it is smaller the the square of the largest factor tested
}
//////////////////////////////////////////////////////////////////////////////////////
// Fermat Test
//

BOOL GeneratePrimes::FermatTest(unsigned long probabilityThreshold)
{
	if (!PrimalityKnownAfterTrialDivision(p))
	{	
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


//////////////////////////////////////////////////////////////////////////////////
// Rückgabe der gefundenen Primzahl (FALSE, wenn keine PZ bestimmte werden konnte.
//

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


//////////////////////////////////////////////////////////////////////////////////
// Zahlenwert P (von aussen/randomisiert) Setzen (für PZ-Test)
//

void GeneratePrimes::SetP(Big &Number)
{
	p=Number;
	Error &= GP_ERROR_NOPRIME;
}

void GeneratePrimes::SetP(CString &NumberStr)
{
	evaluate::CEvalIntExpr( p, NumberStr.GetBuffer( 256 ) );
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


////////////////////////////////////////////////////////////////////////////////////
// Test ob P eine Blum-Zahl ist.
//

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
// CRSADemo Klasse
//////////////////////////////////////////////////////////////////////
// RSA-Berechnungen mit integer-Zahlen ausführen
//


CRSADemo::CRSADemo()
{
	isInitialized_N = isInitialized_d = isInitialized_e = false;
}

CRSADemo::~CRSADemo()
{

}

/////////////////////////////////////////////////////////////////////////////////////
// RSA mit eigenen Parametern: 
// Das Kryptosystem mit den Primzahlen p und q unitialisieren
// ACHTUNG entsprechende Fehlerrückgabe

int CRSADemo::InitParameter( Big &p, Big &q )
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

int CRSADemo::InitParameter( CString &pStr, CString &qStr, int base )
{
	Big p, q;
	BOOL p_ok,q_ok;
	CString p_str = pStr;
	CString q_str = qStr;
	p_ok = CStringFormulaToBig( p_str, p );
	q_ok = CStringFormulaToBig( q_str, q );
	if (p_ok == false) return ERR_P_TO_BIG;
	if (q_ok == false) return ERR_Q_TO_BIG;
	return InitParameter( p, q );
}


/////////////////////////////////////////////////////////////////////////////////
// Nachdem da RSA-ystem mit dem Primzahlen p und q initialisert wurde fehlt
// noch der öffentliche Schlüssel, der Teilerfremd zu Phi(N) = (p-1)*(q-1) sein 
// muss.
// 
int CRSADemo::SetPublicKey ( Big &E )
{
	int ausgabe;
	isInitialized_e = isInitialized_d = false;
	if ( !isInitialized_N ) return 0;
	if ( E <= 1 ) return 0;
	ausgabe = 0;
	if ( 1 == gcd( E, phiOfN ) )
	{
		e = E;
		isInitialized_e = true;
		ausgabe = 1;
	}
	return ausgabe;
}

int CRSADemo::SetPublicKey ( CString &eStr, int base )
{
	Big E;
	// Noch ...
	BOOL e_ok;
	CString e_str = eStr;
	e_ok = CStringFormulaToBig( eStr, E );
	if (e_ok == FALSE) return ERR_E_TO_BIG;
	return SetPublicKey( E );
}


////////////////////////////////////////////////////////////////////////////////////
// Berechnen des geheimen RSA-Schlüssels aus phi(N) und e
//
BOOL CRSADemo::SetPrivateKey()
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

/////////////////////////////////////////////////////////////////////////////////////
// RSA mit dem veröffentlichten öffentlichen Schlüssel
//

int CRSADemo::SetPublicParameter( CString &NStr, CString &eStr )
{
	Big loc_E, loc_N;
	BOOL e_ok, N_ok;

	CString e_str = eStr;
	CString N_str = NStr;
	e_ok = CStringFormulaToBig( e_str, loc_E );
	N_ok = CStringFormulaToBig( N_str, loc_N );
	if (e_ok == FALSE || N_ok == FALSE) return ERR_E_TO_BIG;
	if ( loc_E > 1 && loc_N > 2 )
	{
		isInitialized_e = true;
		isInitialized_N = true;
		N = loc_N;
		e = loc_E;
	}
	else
	{
		return ERR_E_TO_BIG;
	}
	isInitialized_d = false;
	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////
// Parameter zu dem aktuell gewählten RSA-Schlüsel
//

BOOL CRSADemo::GetPublicParameter( CString &NStr, CString &eStr )
{
	BigToCString( N, NStr );
	BigToCString( e, eStr );
	return IsInitializedPublicParameter();
}

BOOL CRSADemo::GetParameter( CString &NStr, CString &phiOfNStr, CString &eStr, CString &dStr, int base )
{
	BigToCString( N, NStr, base );
	BigToCString( phiOfN, phiOfNStr, base );
	BigToCString( e, eStr, base );
	BigToCString( d, dStr, base );
	return IsInitialized();
}

BOOL CRSADemo::GetParameter( Big	&NBig, Big &phiOfNBig, Big &eBig, Big &dBig )
{
	NBig = N;
	phiOfNBig = phiOfN;
	eBig = e;
	dBig = d;
	return IsInitialized();
}

BOOL CRSADemo::GetParameterN(CString &_N) {
	if(isInitialized_N) {
		char charN[MAX_BIT_LENGTH + 1];
		BigToString(N, charN, sizeof(charN));
		_N = charN;
		return true;
	}
	return false;
}

BOOL CRSADemo::GetParameterPhiOfN(CString &_phiOfN) {
	if(isInitialized_N) {
		char charPhiOfN[MAX_BIT_LENGTH + 1];
		BigToString(phiOfN, charPhiOfN, sizeof(charPhiOfN));
		_phiOfN = charPhiOfN;
		return true;
	}
	return false;
}


int  CRSADemo::GetBlockLength()
{
	return bits(N)-1;
}

double CRSADemo::GetLog2RSAModul()
{
	return approxLog2(N);
}


//////////////////////////////////////////////////////////////////////////////////////
// RSA-Verschlüsseln mit den Öffentlichen Parametern e und N
//

BOOL CRSADemo::Encrypt( Big &PlaintextBlock,  Big &CiphertextBlock )
{
	// PlaintextBlock = PlaintextBlock % N;
	if ( (IsInitialized() || IsInitializedPublicParameter()) && PlaintextBlock < N )
	{
		CiphertextBlock = pow(PlaintextBlock,e,N);
		return true;
	}
	else
	{
		return false;
	}
}


///////////////////////////////////////////////////////////////////////////////////////
// RSA-Verschlüsselung von einer Sequenz von Zahlen
//

int  CRSADemo::Encrypt( CString &Plaintext,  CString &Ciphertext, int base, BOOL DlgOfSisters )
{
	Big plain, cipher;
	CString plainStr, cipherStr;
	int OutLength = (int)ceil(GetBlockLength() / (log((double)base)/log((double)2)));

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
		if ( DlgOfSisters ) 
			plain %= N;
		if ( !Encrypt( plain, cipher ) )
		{
			Ciphertext ="";
			if ( plain >= N )
				return 2;
			else 
				return 1;
		}
		// Besonderheit: Dialog der Schwestern
		if ( DlgOfSisters ) cipher = cipher + (rand() % 20 )*N;
		BigToCString( cipher, cipherStr, base, OutLength );
		while ((i2 < Plaintext.GetLength()) && (Plaintext[i2] == ' ' || Plaintext[i2] == '#')) i2++;
		i1 = i2;
		Ciphertext += cipherStr.GetBuffer(cipherStr.GetLength()+1);
		if ( i1 < Plaintext.GetLength() )
			Ciphertext += " # ";
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// RSA Entschlüsseln mit dem Modul N und dem geheimen Schlüssel d
//

int  CRSADemo::Decrypt( Big &CiphertextBlock, Big &PlaintextBlock )
{
	// CiphertextBlock = CiphertextBlock % N;
	if ( IsInitialized() && CiphertextBlock < N )
	{
		PlaintextBlock = pow( CiphertextBlock, d, N);
		return true;
	}
	else
	{
		return false;
	}
}


///////////////////////////////////////////////////////////////////////////////////////
// RSA-Entschlüsselung von einer Sequenz von Zahlen
//

BOOL CRSADemo::Decrypt( CString &Ciphertext, CString &Plaintext, int base, BOOL DlgOfSisters)
{
	Big plain, cipher;
	CString plainStr, cipherStr;
	int OutLength = (int)ceil(GetBlockLength() / (log((double)base)/log((double)2)));

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

		if ( DlgOfSisters ) 
			cipher %= N;

		if ( !Decrypt( cipher, plain ) )
		{
			Plaintext = "";
			if ( cipher >= N )
				return 2;
			else
				return 1;
		}
		// Besonderheit: Dialog der Schwestern
		if ( DlgOfSisters ) plain = plain + (rand() % 20 )*N;
		BigToCString( plain, plainStr, base, OutLength );
		while ( (i2 < Ciphertext.GetLength()) && (Ciphertext[i2] == ' ' || Ciphertext[i2] == '#') ) i2++;
		i1 = i2;
		Plaintext += plainStr.GetBuffer(plainStr.GetLength()+1);
		if ( i1 < Ciphertext.GetLength() )
			Plaintext += " # ";
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// Wenn nicht die RSA-Variante "Dialog der Schwestern" benutzt wird, dann
// müssen alle Zahlen die mit RSA ver- oder entschlüsselt werden kleiner als
// der RSA-Modul N sein.

BOOL CRSADemo::PreCheckInput( CString &Input, int base, BOOL DlgOfSisters  )
{
	Big plain, cipher;
	CString plainStr, cipherStr;
	int OutLength = (int)ceil(GetBlockLength() / (log((double)base)/log((double)2)));

	int i1, i2; 
	i1 = 0;

	while (i1 < Input.GetLength() && (Input[i1] == ' ' || Input[i1] == '#') ) i1++;
		
	while ( i1 < Input.GetLength() )
	{
		i2 = Input.Find(" ", i1);
		if (i2 < 0) 
		{
			if ( i1 < Input.GetLength() ) i2 = Input.GetLength();
			else break;
		}
		plainStr = Input.Mid(i1, i2-i1);
		CStringToBig( plainStr, plain, base );
		if ( !DlgOfSisters )
		{
			if ( plain >= N )
				return 2;
		}
		i1 = i2;
		while (i1 < Input.GetLength() && (Input[i1] == ' ' || Input[i1] == '#') ) i1++;
		// Besonderheit: Dialog der Schwestern
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// CTutorialFactorisation Klasse
//////////////////////////////////////////////////////////////////////
// Algorithmen zur Faktorisierung von Zahlen. Die Algorithmen wurden
// von den Beispielimplementierungen der MIRACL Bibliothek übernommen
// und für die MFC CrypTool-Implementierung angepasst.
// Die Klasse ist "multithread"-implementiert. Wobei manuell ein
// Zeitscheibenmanagement implementiert wurde (siehe 
// DlgProgressFactorisation.{cpp|h}).

CTutorialFactorisation::CTutorialFactorisation()
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

	status = 0;
	factorized = false;
}


CTutorialFactorisation::CTutorialFactorisation(int ordinal, CString name)
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
	status = 0;
	factorized = false;
}


CTutorialFactorisation::~CTutorialFactorisation()
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


////////////////////////////////////////////////////////////////////////
// Test, ob die als String (Zahl zur Basis 10) repräsentierte Zahl prim 
// ist.

BOOL CTutorialFactorisation::IsPrime(CString &Num)
{
	primeChecker.SetP( Num );
	return ( primeChecker.FermatTest(30) );
}

BOOL CTutorialFactorisation::IsPrime(Big &Num)
{
	Big N;
	N = Num;
	primeChecker.SetP( N );
	return ( primeChecker.FermatTest(30) );
}


//////////////////////////////////////////////////////////////////////////
// Rückgabe ist TRUE, wenn N aus {0,1, {Primzahlen}, {gerade Zahlen}}
// Im Fall gerader Zahlen wird die Faktorisierung N = (N/2)*2 berechnet.

BOOL CTutorialFactorisation::Precheck()
{
	factor1 = 0;
	factor2 = 0;

	if ( 1 >= N  )
	{
		return true;
	}

    if ( IsPrime( N ) )
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


//////////////////////////////////////////////////////////////////////
// Brute-Force auf Primzahlen kleiner als LIMIT. 

BOOL CTutorialFactorisation::BruteForce()
{    
	set_mip(mip);
	if ( Precheck() ) return true;

	gprime(LIMIT1); /* generate all primes < LIMIT */

	int n,p;

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


//////////////////////////////////////////////////////////////
// Faktorisierung nach dem Brent-Verfahren
//

BOOL CTutorialFactorisation::Brent()
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
		THREAD_CHECK;
		for (i=1L;i<=r;i++)
		{
			y=(y*y+3);
			if ( !(i  % 1000) ) THREAD_CHECK;
		}
		k=0;
		do
		{
			m_iterations++;			
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


////////////////////////////////////////////////////////////////////////
// Faktorisierung nach Pollard

void CTutorialFactorisation::marks(long start)
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

void CTutorialFactorisation::next_phase_pollard()
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


int CTutorialFactorisation::giant_step_pollard()
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


BOOL CTutorialFactorisation::Pollard()
{
	THREAD_START;
	
	/*  factoring program using Pollards (p-1) method */
    int phase,m,pos,btch;
    long i,pa;
    Big t;
    gprime(LIMIT1);
    for (m=1;m<=MULT/2;m+=2)
        if (igcd(MULT,m)==1) cp[m]=TRUE;
        else                 cp[m]=FALSE;
    modulo(N);                    /* do all arithmetic mod n */
    phase=1;
    p=0;
    btch=50;
    i=0;
    b=2;
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
            t=gcd((Big)q,N);
            if (t==1)
            {
                if (p>LIMIT2) break;
                else continue;
            }
            if (t==N)
            {
                break;
            }
            N/=t;
			factor1=t;
			factor2=N;
			factorized = true;
			status |= THREAD_FACTORIZED;
			THREAD_END;
            return true;
        }
    } 
	THREAD_END;
    return false;
}


///////////////////////////////////////////////////////////////////
// Faktorisierung nach der Williams-Methode

void CTutorialFactorisation::next_phase_williams()
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


int CTutorialFactorisation::giant_step_williams()
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


BOOL CTutorialFactorisation::Williams()
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
    modulo(N);                     /* do all arithmetic mod N */
    for (nt=0,k=3;k<10;k++)
    { /* try more than once for p+1 condition (may be p-1) */
        b=k;                       /* try b=3,4,5..        */
        nt++;
        phase=1;
        p=0;
        btch=50;
        i=0;
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
                t=gcd(q,N);
                if (t==1)
                {
                    if (p>LIMIT2) break;
                    else continue;
                }
                if (t==N)
                {
                    break;
                }
                N/=t;
				factor1=t;
				factor2=N;
				factorized = true;
				status |= THREAD_FACTORIZED;
				THREAD_END;
                return true;
            }
        } 
        if (nt>=NTRYS) break;
    }
	THREAD_END;
	return false;
}


//////////////////////////////////////////////////////////////////////////
// Faktorisierungsmethode nach Lenstra
//

void CTutorialFactorisation::duplication(ZZn sum, ZZn diff, ZZn &x, ZZn &z)
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


void CTutorialFactorisation::addition(ZZn xd, ZZn zd, ZZn sm1, ZZn df1, ZZn sm2, ZZn df2, ZZn &x, ZZn &z)
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



void CTutorialFactorisation::ellipse(ZZn x, ZZn z, int r, ZZn &x1, ZZn &z1, ZZn &x2, ZZn &z2)
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


void CTutorialFactorisation::next_phase_lenstra()
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


int CTutorialFactorisation::giant_step_lenstra()
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


BOOL CTutorialFactorisation::Lenstra()
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
                t=gcd(q,N);
                if (t==1)
                {
                    if (p>LIMIT2) break;
                    else continue;
                }
                if (t==N)
                {
                    break;
                }
                N/=t;
				factor1=t;
				factor2=N;
				factorized = true;
				status |= THREAD_FACTORIZED;
				THREAD_END;
                return true;
            }
        }
        if (nc>NCURVES) break;
    } 
	THREAD_END;
	return false;
}


//////////////////////////////////////////////////////////////////////////////////
// Faktorisierung nach der Methode Quadratisches Sieb
//

#define QS_INT_OVERFLOW     -114473
#define QS_ALLOCATING_ERROR -314159
#define QS_WARNING          -783264

int CTutorialFactorisation::initv()
{

	/* initialize */
    Big T;
    double dp;
    int i,k,digits,pak,maxp;
	
    nbts=8*sizeof(int);

    if (IsPrime(NN))
    {      
		//this number is prime
        return (-1);
    }
	
    T=NN;
    digits=1;                   /* digits in N */
    while ((T/=10)>0) digits++;
	
    if (digits<10) mmm=digits;               
    else mmm=25;
	if (digits>20) mmm=(digits*digits*digits*digits)/4096;
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

    k=knuth(mmm,epr,NN,DD);

    RR=sqrt(DD);

    if (RR*RR==DD)
    {
        // N is a perfect square!"
		// factors are
        if (IsPrime(RR)) 
		{
			// N has a perfect prime-square!" Sollte also sollen die zwei Faktoren schwarz markiert werden!!
		}
        else
		{
			// N has a perfect composite-square!" Sollte also sollen die zwei Faktoren rot markiert werden!!
		}

        NN=NN/RR;
		if (IsPrime(NN)) 
		{
			// N is a perfect prime-square!" Sollte also sollen die zwei Faktoren schwarz markiert werden!!
		}
     	else
		{
			// N is a perfect composite-square!" Sollte also sollen die zwei Faktoren rot markiert werden!!
		}

        return (-2);
    }
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

    xx=new Big[mmm+1];
    yy=new Big[mmm+1];
    zz=new Big[mlf+1];
    ww=new Big[mlf+1];

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

    pak=1+mmm/(8*sizeof(int));
    for (i=0;i<=mmm;i++)
    { 
		THREAD_CHECK;
        xx[i]=0;
        yy[i]=0;
        bb[i]=(-1);
        EE[i]=(unsigned int *)mr_alloc(pak,sizeof(int)); //Roger
    }
    for (i=0;i<=mlf;i++)
    {
		THREAD_CHECK;
        zz[i]=0;
        ww[i]=0;
        G[i]=(unsigned int *)mr_alloc(pak,sizeof(int)); //Roger
    }
	for (i=0; i<=mmm; i++) if ( EE[i] == NULL )
		return QS_ALLOCATING_ERROR;
	for (i=0; i<=mlf; i++) if ( G[i] == NULL )
		return QS_ALLOCATING_ERROR;
	return 1;
}

int CTutorialFactorisation::knuth(int mmm, int *epr, Big &N, Big &D)
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
		//FIXME: funktioniert nur wenn QuadraticSieve sich beendet, falls THREAD_CHECK false liefert
        
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
			//FIXME: funktioniert nur wenn QuadraticSieve sich beendet, falls THREAD_CHECK false liefert
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

void CTutorialFactorisation::new_poly()
{
	/* form the next polynomial */
    int i,r,s,s1,s2;
   
    r=mip->NTRY;        /* MR_NTRY is global - number of trys at proving */
    mip->NTRY=1;        /* a probable prime  */
    do
    { /* looking for suitable prime DG = 3 mod 4 */
        do DG+=4; while(!IsPrime(DG));
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

bool CTutorialFactorisation::factored(long lptr, Big &T)
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

bool CTutorialFactorisation::gotcha(Big &NN, Big &P)
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
        if (XX==YY || P==NN) found=false;
    }
    return found;
}


BOOL CTutorialFactorisation::QuadraticSieve()
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
	if (result_initv == false)
		return false;
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
    while (!IsPrime(TT)) TT-=2;
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
                    if (IsPrime(PP))
					{
						// PP ist ein Primfaktor von N, sollte deshalb sschwarz markiert sein!
					}
                    else
					{
						// PP ist ein zusammengesetztes Faktor von N, sollte also rot markiert werden!
					}
                    NN/=PP;
                    if (IsPrime(NN))
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


//void CTutorialFactorisation::SetN(CString &NStr)
int CTutorialFactorisation::SetN(CString &NStr)
{
	BOOL output;
	set_mip(mip);
	output=evaluate::CEvalIntExpr( N, NStr.GetBuffer( 256 ));
	if (output==false)  return EVAL_ERR; // Zahl mit Bitlänge >= 1024, oder sonstige Miracl-Fehler
	else if ( N < 0 ) return EVAL_NEG; //Da wir nur mit positiven ganzen Zahlen arbeiten!! (oder villeicht nicht??!!)
	else if ( N == 0 ) return EVAL_NULL;
	else if ( N == 1 ) return EVAL_EINS;
	else return EVAL_OK; 
}


void CTutorialFactorisation::GetFactor1Str(CString &Factor1)
{
	set_mip(mip);
	BigToCString( factor1, Factor1 );
}


void CTutorialFactorisation::GetFactor2Str(CString &Factor2)
{
	set_mip(mip);
	BigToCString( factor2, Factor2 );
}



//////////////////////////////////////////////////////////////////////
// CRandomGenerator Klasse
//////////////////////////////////////////////////////////////////////
// Pseudo-Zufalls Generatoren
//

CRandomGenerator::CRandomGenerator()
{
	Seed = 314159;
	RandNo = Seed;
}

CRandomGenerator::~CRandomGenerator()
{
}

BOOL CRandomGenerator::setSeed(CString &SeetStr)
{
	BOOL retValue = CStringFormulaToBig( SeetStr, Seed );
	RandNo = Seed;
	return retValue;
}

void CRandomGenerator::randIntStr(CString & IntStr, int base )
{
	BigToCString(RandNo, IntStr, base);
}


//////////////////////////////////////////////////////////////////////
// X^2 (mod N) Generator
//

CX2ModNGenerator::CX2ModNGenerator()
{
	CString tmp = STANDARD_X2MOD_N_MODUL;
	setModul(tmp);
}

CX2ModNGenerator::~CX2ModNGenerator()
{
}

BOOL CX2ModNGenerator::setModul( CString &NStr )
{
	return CStringFormulaToBig( NStr, Modul_N );
}

void CX2ModNGenerator::randomize()
{
	Big two = 2;
	Big tmp = RandNo;
	RandNo  = pow( tmp, two, Modul_N );
}

long CX2ModNGenerator::randBit()
{
	return RandNo % 2;
}

//////////////////////////////////////////////////////////////////////
// Linear Kongruenz Generator 
//

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
	return (RandNo > N/2) ? 1 : 0;
}

//////////////////////////////////////////////////////////////////////
// Inverse Kongruenz Generator
//

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
	return (RandNo >  N/2) ? 1 : 0;
}

////////////////////////////////////////////////////////////////////////
// Rahmen für die Klasse CTutorialFactorisation (Lösung zur Realsierung
// der Faktorisierung multithreaded).

CTutorialFactorisationBase::CTutorialFactorisationBase()
{
	m_old_mip = get_mip();
	mirsys(MAX_BIT_LENGTH/32+128,0);
	mip = get_mip();
	set_io_buffer_size(MAX_BIT_LENGTH + 1);
	set_mip(m_old_mip);
}

CTutorialFactorisationBase::~CTutorialFactorisationBase()
{
	set_mip(mip);
	mirexit();
	set_mip(m_old_mip);
}


// Gibt TRUE zurück, sofern der übergebene Ausdruck eine dezimale Zahl ist
bool IsDecimalNumber(CString expression)
{
	for(int i=0; i<expression.GetLength(); i++)
	{
		if(expression[i] < '0' || expression[i] > '9') return false;
	}

	return true;
}

// see declaration for details
void removeInvalidCharactersFromFormula(CString &_formula, int &_selectionStart, int &_selectionEnd)
{
	const CString validCharacters = "0123456789-+*^()";
	CString validFormula;
	for(int i=0; i<_formula.GetLength(); i++) {
		if(validCharacters.Find(_formula[i]) != -1) {
			validFormula.AppendChar(_formula[i]);
		}
		else {
			_selectionStart--;
			_selectionEnd--;
		}
	}
	_formula = validFormula;
}
