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

/* Support code for the zip/unzip code - just handles error messages.  To
   get exact errors, define ZIPDEBUG */


#include <stdio.h>
#include <stdlib.h>
#include "usuals.h"
#include "fileio.h"
#include "zip.h"
#include "ziperr.h" /* for ZE_MEM (and errors[] if ZIPDEBUG defined) */

/* Clean error exit: c is a ZE_-class error, *msg is an error message.
   Issue a message for the error, clean up files and memory, and exit */

void err(int c, char *msg)
{
#ifdef ZIPDEBUG
	if (PERR(c))
		perror("zip error");
	fprintf(stderr, "zip error: %s (%s)\n", errors[c-1], msg);
#endif /* ZIPDEBUG */

	/* Complain and return and out of memory error code */
	if(c==ZE_MEM) {
		err_txt = "Out of memory";
		longjmp( err_exit, 7 );
	} else {
		err_txt = "Compression/decompression error";
		longjmp( err_exit, 23 );
	}
}

/* Internal error, should never happen */
void error(char *msg)
{
	err(-1, msg);
}

