#ifndef _CRACK_H_WIN32_
#define _CRACK_H_WIN32_

/*
 * Crack library header file.  Use this file to include Cracklib 
 * support in your windows 32 application
 *
 * Copyright (C) 2002, Joseph Tate <jtate@mi-corporation.com>
 * //TODO: Work on copyright notice
 */

#include <stdio.h>
#include <ctype.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned long int int32;

#ifndef NUMWORDS
#define NUMWORDS	16
#endif
#define MAXWORDLEN	32

struct pi_header
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
} PWDICT;


PWDICT *PWOpen();
char *Mangle();
char *FascistCheck();
char * FascistLook(pwp, instring);

char * Trim(string);
int PMatch(control, string);
int32 FindPW(pwp, string);
int PWClose(pwp);
int PutPW(pwp, string);
char * GetPW(pwp, number);
char Chop(string);

#endif /*_CRACK_H_WIN32_*/
