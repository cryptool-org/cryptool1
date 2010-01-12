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

#include "stdafx.h"
#include <ctype.h>
#include "ChrTools.h"
#include "FileTools.h"

//static char lowercase[]="abcdefghijklmnopqrstuvwxyz‰ˆ¸·‡‚ÈËÍÌÏÓÛÚÙ˙˘˚˝";
//static char uppercase[]="ABCDEFGHIJKLMNOPQRSTUVWXYZƒ÷‹¡¿¬…» ÕÃŒ”“‘⁄Ÿ€›";

BOOL MyIsLower(char c)
{
	return islower((unsigned char)c);
}

BOOL MyIsUpper(char c)
{
	return isupper((unsigned char)c);
}

BOOL MyIsAlpha(char c)
{
	return isalpha((unsigned char)c);
}

char MyToUpper(char c)
{
	return toupper((unsigned char)c);
}

char MyToLower(char c)
{
	return tolower((unsigned char)c);
}

char *MyToUpper(char *str)
{
	char *p;
	
	for(p=str;*p;p++) *p = MyToUpper(*p);
	return str;
}


char *MyToLower(char *str)
{
	char *p;
	
	for(p=str;*p;p++) *p = MyToLower(*p);
	return str;
}

void MyToUpper(CString &str)
{
	MyToUpper(str.GetBuffer(0));
	str.ReleaseBuffer();
}

void MyToLower(CString &str)
{
	MyToLower(str.GetBuffer(0));
	str.ReleaseBuffer();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
// Nur tempor‰r & lokal definiert

inline
BOOL NewLineTabSpace( char ch )
{
	return isCharOf( ch, " \r\t\n");
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
		if ( !NewLineTabSpace( CStr[i] ) )
		{
			if ( IsNumber( CStr[i], BASE_HEX ) )
			{
				fmt += MyToUpper(CStr[i]);
				twoStep++;
				if ( 2 == twoStep ) {
					fmt += ' ';
					twoStep = 0;
					if ( i+1 < CStr.GetLength() && !NewLineTabSpace( CStr[i+1] ) )
						return FALSE;
				}
			}
			else 
				return FALSE;
		}
	}
	if (twoStep != 0) return FALSE;
	else              
	{
		CStr = fmt; 
		return TRUE;
	}
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
			if ( !NewLineTabSpace( hexDump[i] ) )
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#define codeASCII_MARK_BEGIN '{'
#define codeASCII_MARK_END   '}'


int encodeASCII( char *strOut, int &strOutPtr, const int strOutSize, const char chrIn, const char* filter)
{
	if (filter) 
	{
		for (int i=0 ; i++; ) { 
			if ( filter[i] == '\0' ) break;
			if ( chrIn == filter[i] ) return -1;
		}
	}
	if ( chrIn == codeASCII_MARK_BEGIN ) 
	{
		if ( strOutPtr +2 < strOutSize ) {
			strOut[ strOutPtr++ ] = codeASCII_MARK_BEGIN; 
			strOut[ strOutPtr++ ] = codeASCII_MARK_BEGIN; 
		}
		else {
			return 0;
		}
	}
	else
	{
		if ( IsPrint( (unsigned char)chrIn ) ) {
			if ( strOutPtr +1 < strOutSize ) {
				strOut[ strOutPtr++ ] = chrIn;
			}
			else {
				return 0;
			}
		}
		else {
			if ( strOutPtr +4 < strOutSize ) {
				strOut[ strOutPtr++ ] = codeASCII_MARK_BEGIN;
				unsigned char n = (unsigned char)chrIn;
				char ch;
				if ((n >> 4) >= 10 ) 
					ch = 'A'+((n >> 4) -10); 
				else 
					ch = '0'+(n >> 4);
				strOut[ strOutPtr++ ] = ch;
				if ((n % 16) >= 10 ) 
					ch = 'A'+((n % 16) -10); 
				else 
					ch = '0'+(n % 16);
				strOut[ strOutPtr++ ] = ch;
				strOut[ strOutPtr++ ] = codeASCII_MARK_END;
			}
			else {
				return 0;
			}
		}
	}
	return 1;
}

int  encodeASCII(      char *strOut,       int &strOutPtr, const int strOutSize, 
	  		     const char *strIn,  const int  strInPtr,  const int length, const char* filter)
{
    int done = 0;
	while ( done < length  )
	{
		if (!encodeASCII( strOut, strOutPtr, strOutSize, strIn[strInPtr+done], filter) ) 
			break;
		else
			done++;
	}

	return done;
}


int codedASCIIBlockLength( CString &StrIn, const int start, const int length )
{
   int i = start;
   for (int j=start; j<start+length && i < StrIn.GetLength(); j++)
   {
		if ( StrIn[i++] == codeASCII_MARK_BEGIN )
		{
			if ( i < StrIn.GetLength() && StrIn[i] != codeASCII_MARK_BEGIN )
			{
				if ( i+2 < StrIn.GetLength() && StrIn[i+2] == codeASCII_MARK_END ) 
					i += 3;
			}
			else
			{
				i++;
			}
		}
   }
   return i-start;
}


int decodeASCII(      char *strOut, int &strOutPtr, const int strOutSize, 
			    const char *strIn,  int strInPtr,  const int length )
{
	char * m_outStr;
	m_outStr = new char[length+1];
	int ptr = 0;
	int done = 0;
	while ( done < strOutSize && strInPtr < length ) 
	{
		if ( strIn[strInPtr] == codeASCII_MARK_BEGIN )
		{
			if ( strIn[strInPtr+1] == codeASCII_MARK_BEGIN ) {
				m_outStr[ptr++] = codeASCII_MARK_BEGIN;
				strInPtr += 2;
				done++;
			}
			else
			{
				strInPtr++;
				char ch1, ch2, ch3;
				char ch;
				ch1 = strIn[strInPtr++];
				ch2 = strIn[strInPtr++];
				ch3 = strIn[strInPtr++];
				if ( ch3 != codeASCII_MARK_END ) return ( -1 );
				if ( ch1 >= '0' && ch1 <= '9' || ch1 >= 'A' && ch1 <= 'F' ) {
					if ( ch1 >= '0' && ch1 <= '9' ) 
						ch = ch1 - '0'; 
					else 
						ch = ch1 - 'A'+10;
				} else return (-1);
				if ( ch2 >= '0' && ch2 <= '9' || ch2 >= 'A' && ch2 <= 'F' ) {
					if ( ch2 >= '0' && ch2 <= '9' ) 
						ch = (ch << 4) + (ch2 - '0');
					else 
						ch = (ch << 4) + (ch2 - 'A')+10;
				} else return (-1);
				m_outStr[ptr++] = ch;
				done++;
			}
		}
		else
		{
			m_outStr[ptr++] = strIn[strInPtr++];
			done++;
		}
	}
	m_outStr[ptr] = '\0';
	strcpy( strOut + strOutPtr, m_outStr );
	strOutPtr += ptr;
	delete[] m_outStr;
	return done;
}
