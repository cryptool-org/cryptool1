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


/*

 Copyright (C) 1990,1991 Mark Adler, Richard B. Wales, and Jean-loup Gailly.
 Permission is granted to any individual or institution to use, copy, or
 redistribute this software so long as all of the original files are included
 unmodified, that it is not sold for profit, and that this copyright notice
 is retained.

*/

/*
 *  ziperr.h by Mark Adler.
 */

/* Error return values.  The values 0..4 and 12..18 follow the conventions
   of PKZIP.   The values 4..10 are all assigned to "insufficient memory"
   by PKZIP, so the codes 5..10 are used here for other purposes. */
#define ZE_MISS         -1      /* used by procname(), zipbare() */
#define ZE_OK           0       /* success */
#define ZE_EOF          2       /* unexpected end of zip file */
#define ZE_FORM         3       /* zip file structure error */
#define ZE_MEM          4       /* out of memory */
#define ZE_LOGIC        5       /* internal logic error */
#define ZE_BIG          6       /* entry too large to split */
#define ZE_NOTE         7       /* invalid comment format */
#define ZE_ABORT        9       /* user interrupt or termination */
#define ZE_TEMP         10      /* error using a temp file */
#define ZE_READ         11      /* read or seek error */
#define ZE_NONE         12      /* nothing to do */
#define ZE_NAME         13      /* missing or empty zip file */
#define ZE_WRITE        14      /* error writing to a file */
#define ZE_CREAT        15      /* couldn't open to write */
#define ZE_PARMS        16      /* bad command line */
#define ZE_OPEN         18      /* could not open a specified file to read */
/* Macro to determine whether to call perror() or not */
#define PERR(e) (e==ZE_READ||e==ZE_WRITE||e==ZE_CREAT||e==ZE_TEMP||e==ZE_OPEN)

#ifdef GLOBALS
/* Error messages for the err() function in the zip programs */
char *errors[] = {
/*  1 */  "",
/*  2 */  "Unexpected end of zip file",
/*  3 */  "Zip file structure invalid",
/*  4 */  "Out of memory",
/*  5 */  "Internal logic error",
/*  6 */  "Entry too big to split",
/*  7 */  "Invalid comment format",
/*  8 */  "",
/*  9 */  "Interrupted",
/* 10 */  "Temporary file failure",
/* 11 */  "Input file read failure",
/* 12 */  "Nothing to do!",
/* 13 */  "Missing or empty zip file",
/* 14 */  "Output file write failure",
/* 15 */  "Could not create output file",
/* 16 */  "Invalid command arguments",
/* 17 */  "",
/* 18 */  "File not found or no read permission",
};
#else /* !GLOBALS */
extern char *errors[];          /* Error messages for err() */
#endif /* ?GLOBALS */
