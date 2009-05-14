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

/*

 Copyright (C) 1990,1991 Mark Adler, Richard B. Wales, and Jean-loup Gailly.
 Permission is granted to any individual or institution to use, copy, or
 redistribute this software so long as all of the original files are included
 unmodified, that it is not sold for profit, and that this copyright notice
 is retained.

*/

/*
 *  zip.h by Mark Adler.
 */


/* Set up portability */
#include <setjmp.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "ztailor.h"

#define MIN_MATCH  3
#define MAX_MATCH  258
/* The minimum and maximum match lengths */

#ifndef WSIZE
#  define WSIZE  8192	/* for PGP only use 8192 */
#endif
/* Maximum window size = 32K. If you are really short of memory, compile
 * with a smaller WSIZE but this reduces the compression ratio for files
 * of size > WSIZE.
 */

#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
/* Minimum amount of lookahead, except at the end of the input file.
 * See deflate.c for comments about the MIN_MATCH+1.
 */

#define MAX_DIST  (WSIZE-MIN_LOOKAHEAD)
/* In order to simplify the code, particularly on 16 bit machines, match
 * distances are limited to MAX_DIST instead of WSIZE.
 */

#include <string.h>

/* Define fseek() commands */
#ifndef SEEK_SET
#  define SEEK_SET 0
#endif /* !SEEK_SET */

#ifndef SEEK_CUR
#  define SEEK_CUR 1
#endif /* !SEEK_CUR */

#ifndef SEEK_END
#  define SEEK_END 2
#endif /* !SEEK_END */

/* For setting stdout to binary */
#ifdef MSDOS
#  include <io.h>
#  include <fcntl.h>
#endif /* MSDOS */

/* Types centralized here for easy modification */
#define local static            /* More meaningful outside functions */
typedef unsigned char uch;      /* unsigned 8-bit value */
typedef unsigned short ush;     /* unsigned 16-bit value */
typedef unsigned long ulg;      /* unsigned 32-bit value */


/* Error return codes and PERR macro */
#include "ziperr.h"

/* Internal attributes */
#define UNKNOWN		-1
#define BINARY		0
#define ASCII		1

/* Public globals */
#define BEST -1                 /* Use best method (deflation or store) */
#define STORE 0                 /* Store method */
#define DEFLATE 8               /* Deflation method*/
extern int method;              /* Restriction on compression method */
extern int level;               /* Compression level */
extern jmp_buf err_exit;
extern char *err_txt;

/* Diagnostic functions */
#ifdef DEBUG
  extern char verbose;	/* PGP -l flag */
# ifdef MSDOS
#  undef  stderr
#  define stderr stdout
# endif
#  define diag(where) fprintf(stderr, "zip diagnostic: %s\n", where)
#  define Assert(cond,msg) {if(!(cond)) error(msg);}
#  define Trace(x) fprintf x
#  define Tracev(x) {if (verbose) fprintf x ;}
#  define Tracevv(x) {if (verbose>1) fprintf x ;}
#  define Tracec(c,x) {if (verbose && (c)) fprintf x ;}
#  define Tracecv(c,x) {if (verbose>1 && (c)) fprintf x ;}
#else
#  define diag(where)
#  define Assert(cond,msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c,x)
#  define Tracecv(c,x)
#endif


/* Public function prototypes */

        /* in zip.c, zipcloak.c, or zipsplit.c */
void err   OF((int c, char *h));
void error OF((char *h));

        /* in zipup.c */
//int zipup OF((FILE *inFile, FILE *outFile));
int read_buf OF((char far *buf, unsigned size));

#  define zfwrite fwrite /* ??? far */
#  define zputc putc

        /* in deflate.c */
void lm_init OF((int pack_level, ush *flags));
ulg  deflate OF((void));

        /* in trees.c */
void ct_init     OF((ush *attr, int *Method));
int  ct_tally    OF((int dist, int lc));
ulg  flush_block OF((char *buf, ulg stored_len, int eof));

        /* in bits.c */
void     bi_init    OF((FILE *zipfile));
void     send_bits  OF((int value, int length));
unsigned bi_reverse OF((unsigned value, int length));
void     bi_windup  OF((void));
void     copy_block OF((char far *buf, unsigned len, int header));

#ifdef __cplusplus
	}
#endif

/* end of zip.h */
