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

#ifndef __CRYPTOOL_TOOLS_H
#define __CRYPTOOL_TOOLS_H

#include "stdafx.h"
#include "CrypToolApp.h"

BOOL CheckAlphabet (int minSize = 1);
BOOL CheckTextSize (SymbolArray &text, int Threshold = 1);
void LoadText      (const char *infile, SymbolArray &text);
void GetNewDocTitle(const char* keyStr, const char* OldTitle, 
					int IDS_STRING_ID, char* title, long titleLength, BOOL Decrypt = FALSE, 
					int KeyType = SCHLUESSEL_LINEAR );

void OpenNewDoc    (const char *outfile, const char* keyStr, const char* OldTitle, 
					int IDS_STRING_ID, BOOL Decrypt = FALSE, int KeyType = SCHLUESSEL_LINEAR );

char* itoa_fmt(int i_num, char *c_buffer = NULL, int i_base = 10 );
char* itoa_fmt(__int64 i_num, char *c_buffer = NULL, int i_base = 10 );
char* double_fmt(double d_num, char *c_buffer, int prec = 2);

unsigned long CT_OPEN_REGISTRY_SETTINGS	(unsigned long MODE_ACCESS, int ID_REGISTRY_PATH, const char *SUB_FOLDER = 0);
void CT_CLOSE_REGISTRY();
BOOL CT_READ_REGISTRY			(unsigned long &value,		 const char *ID);
BOOL CT_READ_REGISTRY			(char *value,               const char *ID, unsigned long &length);
BOOL CT_READ_REGISTRY_DEFAULT	(unsigned long &value,		 const char *ID, const unsigned long default_value);
BOOL CT_READ_REGISTRY_DEFAULT	(char *value,               const char *ID, 
                               const char *default_value, unsigned long &length ); 
BOOL CT_WRITE_REGISTRY			(const unsigned long value, const char *ID);
BOOL CT_WRITE_REGISTRY			(const char *value,         const char *ID);

// see implementation
CString extractValueFromStringByKey(CString _key, CString _string);

// see implementation
std::vector<CString> splitString(const CString &_string, const CString &_separator);

// see implementation
bool isAppDataDirectoryDefined();
// see implementation
bool isJavaAvailable(const CString &_version);
// see implementation
void ShellExecuteJava(const CString &_javaProgram, const CString &_javaProgramCompleteCall, const CString &_path);

// see implementation
CString adaptKeyToAlphabet(const CString _key);

// see implementation(s)
char getIntegralNumberSeparator();
char getFractionalNumberSeparator();
CString createStringNumberWithDigitGrouping(const int &_number);
CString createStringNumberWithDigitGrouping(const unsigned int &_number);
CString createStringNumberWithDigitGrouping(const long &_number);
CString createStringNumberWithDigitGrouping(const unsigned long &_number);
CString createStringNumberWithDigitGrouping(const float &_number, const unsigned int &_numberOfDecimalPlaces = 2);
CString createStringNumberWithDigitGrouping(const double &_number, const unsigned int &_numberOfDecimalPlaces = 2);
CString createStringNumberWithDigitGrouping(const CString &_number);

// see implementation
CString removeNonAlphabetCharacters(CString &_text, const CString &_alphabet);

#endif


