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

// passwordchecker.h

// ****************************************************************************
//
// 06.11.2007 Florian Marchal
// Integration des mit Henrik Koy entwickelten Passwort-Checkers in CrypTool
//
// ****************************************************************************
//
// ATTENTION:
//
//   If you plan on extending this password checker, keep one thing in mind: 
//   We're using an untouched version of the Win32 cracklib. And under certain 
//   circumstances (i.e. when the dictionary is not found), the library exits 
//   with "exit(-1)". In turn, the CrypTool application exits WITHOUT any 
//   information for the user.
//
//   For now, we only use a few cracklib functions and errors/exceptions are 
//   handled properly. But this behaviour might change if you extend the 
//   functionality.
//

#ifndef _PASSWORDCHECKER_H_
#define _PASSWORDCHECKER_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "resource.h"

// *** BEGIN CRACKLIB SPECIFIC DECLARATIONS ***********************************
#define STRINGSIZE		1024
#define TRUNCSTRINGSIZE	(STRINGSIZE/4)
#define MINDIFF			3
#define MINLEN			8
#define MAXSTEP			2
#define NUMWORDS		16
#define MAXWORDLEN		32

#define CRACK_TOLOWER(a)	(MyIsUpper(a)?MyToLower(a):(a)) 
#define CRACK_TOUPPER(a)	(MyIsLower(a)?MyToUpper(a):(a)) 
#define STRCMP(a,b) 	strcmp((a),(b))

struct pi_header {
	unsigned long int pih_magic;
	unsigned long int pih_numwords;
	unsigned short int pih_blocklen;
	unsigned short int pih_pad;
};

struct PWDICT {
	FILE *ifp;
    FILE *dfp;
	FILE *wfp;
    unsigned long int flags;
    #define PFOR_WRITE	0x0001
    #define PFOR_FLUSH	0x0002
    #define PFOR_USEHWMS	0x0004
    unsigned long int hwms[256];
    struct pi_header header;
    int count;
    char data[NUMWORDS][MAXWORDLEN];
};

#define PW_WORDS(x) ((x)->header.pih_numwords)

extern "C" {
	unsigned long int FindPW(PWDICT *pwp, char *password);
	int PMatch(char *pattern, char *password);
	char *Trim(char *password);
	int PWClose(PWDICT *pwp);
	PWDICT *PWOpen(char *prefix, char *mode);
}
// *** END CRACKLIB SPECIFIC DECLARATIONS *************************************

#define IDS_PWD_POLICY_COMPLIANT				0
#define IDS_PWD_POLICY_TOOSHORT					1
#define IDS_PWD_POLICY_TOOFEWDIGITS				2
#define IDS_PWD_POLICY_TOOFEWSPECIALCHARACTERS	4

// this function checks a password against patterns
char *checkPasswordAgainstPatterns(char *password);
// this function checks a password against sequences
char *checkPasswordAgainstSequences(char *password);
// this function checks a password against keyboard sequences
char *checkPasswordAgainstKeyboardSequences(char *password);
// this function checks a password against a cracklib dictionary
char *checkPasswordAgainstCracklibDictionary(char *password, PWDICT *pwp, unsigned long int notfound);
// this function checks a password for compliance
int checkPasswordForCompliance(char *password);
// this function checks a password's charset
int checkPasswordCharset(char *password);

// this is the main password checking function; it returns 0 if the given path 
// for the cracklib dictionary is invalid; if the last two parameters are specified,
// a more sophisticated password check is executed: the determined entropy and the found password 
// components (substrings) are stored in the last two parameters
char *checkPassword(char *password, char *path, int hidePassword, double *determinedPasswordEntropy = 0, std::string *determinedPasswordComponents = 0);

#endif