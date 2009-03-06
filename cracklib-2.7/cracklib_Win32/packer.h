/*
 * This program is copyright Alec Muffett 1993. The author disclaims all 
 * responsibility or liability with respect to it's usage or its effect 
 * upon hardware or computer systems, and maintains copyright as set out 
 * in the "LICENCE" document which accompanies distributions of Crack v4.0 
 * and upwards.
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>

#ifdef _WIN32
#define CRACKLIB_WIN32_API __declspec(dllexport)
#else
#define CRACKLIB_WIN32_API
#endif

#define STRINGSIZE	1024
#define TRUNCSTRINGSIZE (STRINGSIZE/4)

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned long int int32;
#ifndef NUMWORDS
#define NUMWORDS	16
#endif
#define MAXWORDLEN	32
#define MAXBLOCKLEN 	(MAXWORDLEN * NUMWORDS)

struct CRACKLIB_WIN32_API pi_header
{
	int32 pih_magic;
	int32 pih_numwords;
	int16 pih_blocklen;
	int16 pih_pad;
};

typedef struct
{
	FILE *ifp;
	FILE *dfp;
	FILE *wfp;

	int32 flags;
#define PFOR_WRITE	0x0001
#define PFOR_FLUSH	0x0002
#define PFOR_USEHWMS	0x0004

	int32 hwms[256];

	struct pi_header header;

	int count;
	char data[NUMWORDS][MAXWORDLEN];
} CRACKLIB_WIN32_API PWDICT;

#define PW_WORDS(x) ((x)->header.pih_numwords)
#define PIH_MAGIC 0x70775631

extern CRACKLIB_WIN32_API PWDICT *PWOpen();
extern CRACKLIB_WIN32_API char *Mangle();
extern CRACKLIB_WIN32_API char *FascistCheck();
extern CRACKLIB_WIN32_API char * FascistLook(pwp, instring);
extern CRACKLIB_WIN32_API char * Trim(string);
extern CRACKLIB_WIN32_API int PMatch(control, string);
extern CRACKLIB_WIN32_API int32 FindPW(pwp, string);
extern CRACKLIB_WIN32_API int PWClose(pwp);
extern CRACKLIB_WIN32_API int PutPW(pwp, string);
extern CRACKLIB_WIN32_API char * GetPW(pwp, number);
extern CRACKLIB_WIN32_API char Chop(string);

#define CRACK_TOLOWER(a)	(isupper(a)?tolower(a):(a)) 
#define CRACK_TOUPPER(a)	(islower(a)?toupper(a):(a)) 
#define STRCMP(a,b) 	strcmp((a),(b))

/*Added for Windows 32 support */
#ifdef WIN32
#define CRACKLIB_DICTPATH "../words/cracklib_dict" /* Edit this line to match your own */
#include <stdlib.h>
#include <string.h>


#endif
