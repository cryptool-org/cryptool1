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


#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef UNIX
#if !defined(HAVE_UNISTD_H) && !defined(MACH) && !defined(_BSD)
#define HAVE_UNISTD_H
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#else
#include <stdio.h>
#include <sys/types.h>
#endif

int getch();
int kbhit();

/* replacement function for obsolete clock(), just provides random data */
long Clock();

#endif /* UNIX */

#if defined(UNIX) || defined(AMIGA) || defined(VMS)
void ttycbreak();
void ttynorm();
#else
#define ttycbreak()	/* nothing */
#define ttynorm()	/* nothing */
#endif

#if !defined(MSDOS) && !defined(ATARI)
//char *strlwr(char *);
#endif

void breakHandler(int);

#endif /* SYSTEM_H */
