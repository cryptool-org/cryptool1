//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ctype.h>
#include "ChrTools.h"
#include "fileutil.h"

//static char lowercase[]="abcdefghijklmnopqrstuvwxyz‰ˆ¸·‡‚ÈËÍÌÏÓÛÚÙ˙˘˚˝";
//static char uppercase[]="ABCDEFGHIJKLMNOPQRSTUVWXYZƒ÷‹¡¿¬…» ÕÃŒ”“‘⁄Ÿ€›";

BOOL MyIsLower(char c)
{
	return islower(c);
}

BOOL MyIsUpper(char c)
{
	return isupper(c);
}

char MyToUpper(char c)
{
	return toupper(c);
}

char MyToLower(char c)
{
	return tolower(c);
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
	return done;
}