/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////

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