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
 *  zipup.c by Mark Adler. Includes modifications by Jean-loup Gailly.
 */

#define NOCPYRT         /* this is not a main module */
#include <ctype.h>
#ifdef __QNX__
#include <unistd.h>
#endif
#include <io.h>
#include "zip.h"
#include "zrevisio.h"


#pragma warning(disable : 4996)

/* Use the raw functions for MSDOS and Unix to save on buffer space.
   They're not used for VMS since it doesn't work (raw is weird on VMS).
   (This sort of stuff belongs in fileio.c, but oh well.) */
#ifdef VMS
   typedef FILE *ftype;
#  define fhow FOPR
#  define fbad NULL
#  define zopen(n,p) fopen(n,p)
#  define zread(f,b,n) fread(b,1,n,f)
#  define zclose(f) fclose(f)
#  define zerr(f) ferror(f)
#  define zrew(f) rewind(f)
#  define zstdin stdin
#else /* !VMS */
#  ifdef MSDOS
#    include <io.h>
#    include <fcntl.h>
#    define fhow (O_RDONLY|O_BINARY)
#  else /* !MSDOS */
#if !(defined(AMIGA) || defined(__NetBSD__))
//     long lseek();
#endif /* AMIGA */
#    define fhow 0
#  endif /* ?MSDOS */
   typedef int ftype;
#  define fbad (-1)
#  define zopen(n,p) open(n,p)
#  define zread(f,b,n) read(f,b,n)
#  define zclose(f) close(f)
#  define zerr(f) (k==(extent)(-1L))
#  define zrew(f) lseek(f,0L,0)
#  define zstdin 0
#endif /* ?VMS */

/* Local data */

local ftype ifile;		/* file to compress */

void lm_free();
void ct_free();

/* Compress the file fileName and write it to the file *y. Return an error
   code in the ZE_ class.  Also, update tempzn by the number of bytes written.
*/
int zipup(FILE *inFile, FILE *y)
/* ??? Does not yet handle non-seekable y */
{
  int m;				/* method for this entry */
  long q = -1L;			/* size returned by filetime */
  ush att;			/* internal file attributes (dummy only) */
  ush flg;				/* gp compresion flags (dummy only) */

  /* error exit via longjmp */
  m=setjmp(err_exit);
  if(m) return m;

	/* Set input file and find its size */
#ifdef VMS
	ifile = inFile;
	fseek(ifile, 0L, SEEK_END);
	q = ftell(ifile);
	fseek(ifile, 0L, SEEK_SET);
#else
	ifile = fileno( inFile );
	q = lseek(ifile, 0L, SEEK_END);
	lseek(ifile, 0L, SEEK_SET);
#endif /* VMS */

	m = (q == 0) ? STORE : DEFLATE;

  if (m == DEFLATE) {
	 bi_init(y);
	 att = UNKNOWN;
	 ct_init(&att, &m);
	 lm_init(level, &flg);
	 /* s = */ deflate();
  }
  lm_free();
  ct_free();

  return(0);
}

int read_buf(buf, size)
  char far *buf;
  unsigned size;
/* Read a new buffer from the current input file, and update the crc and
 * input file size.
 * IN assertion: size >= 2 (for end-of-line translation) */
{
  unsigned len;

  len = zread(ifile, buf, size);
  if (len == (unsigned)EOF || len == 0) return len;
  return len;
}
