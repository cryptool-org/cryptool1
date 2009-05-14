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
 *  globals.c by Mark Adler.
 */

#define GLOBALS         /* include definition of errors[] in zip.h */
#include <setjmp.h>
#include "zip.h"

/* Argument processing globals */
int method = BEST;      /* one of BEST, DEFLATE (only), or STORE (only) */
int level = 9;          /* 0=fastest compression, 9=best compression */
char *special = (char *)NULL;   /* List of special suffixes */
jmp_buf err_exit;
char *err_txt=NULL;