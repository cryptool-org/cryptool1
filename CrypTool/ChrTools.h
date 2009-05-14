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

#ifndef __CHRTOOLS_H
#define __CHRTOOLS_H

BOOL MyIsLower(char c);
BOOL MyIsUpper(char c);
BOOL MyIsAlpha(char c);
char MyToUpper(char c);
char MyToLower(char c);
char *MyToUpper(char *str);
char *MyToLower(char *str);
void MyToUpper(CString &str);
void MyToLower(CString &str);


#define BASE_BIN 2
#define BASE_OCT 8
#define BASE_DEC 10
#define BASE_HEX 16
#define VALID_BIN     "01"
#define VALID_OCT     "0..7"
#define VALID_DEC     "0..9"
#define VALID_HEX     "0..9a..fA..F"

BOOL isCharOf     ( const char ch, const char *expr );
BOOL IsNumber     ( char ch, int base );
int  NeededBase   ( char ch );
char DigitToNum   ( char ch );
char ToHex        ( const char ch );

void dataToHexDump( const char* data, int len, char* hexDump );
void dataToHexDump( const char* data, int len, CString& hexDump );
int  HexDumpToData( const char *hexDump, char *data );
int  HexDumpToData( CString &hexDump, char *data );


int  encodeASCII(char *strOut, int &strOutPtr, const int strOutSize, const char chrIn, const char* filter);
int  encodeASCII(char *strOut, int &strOutPtr, const int strOutSize, const char *strIn,  
				  const int  strInPtr,  const int length, const char* filter);
int  decodeASCII(char *strOut, int &strOutPtr, const int strOutSize, const char *strIn,  
				  int strInPtr,   const int length );
int codedASCIIBlockLength( CString &StrIn, const int start, const int length );


#endif