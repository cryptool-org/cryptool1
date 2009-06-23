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

/////////////////////////////////////////////////////////////////
//
// Diese Datei ist Bestandteil der Diplomarbeit
// "Eine C++-Bibliothek zur informationstheoretischen Kryptanalyse 
// von Stromchiffren und PZ-Folgen" am Europaeischen Institut fuer
// Systemsicherheit, Prof. Dr. Th. Beth
//
// von und (c) 1997-98 Michael Friedrich
//
/////////////////////////////////////////////////////////////////

#ifndef _MYMATH_H
#define _MYMATH_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#ifndef _MYTEMPLATES_H
#include "mytemplates.h"
#endif

// Diese Datei definiert die folgenden (mathematischen) Funktionen:

// in mymath.c
long pow(long a, int b);
int ilog2(unsigned long l);
long gcd(long x, long y);
long minverse(long x, long n);
char* ToString(int n);

// inline hier:
// log2, mod, kgv, sqr
// testbit, setbit
// RANDOM
// stol


/////////////////////////////////////////////////////////////////////
// Implementation

inline double log2(double a) {return log(a)/log((double)2);}
inline long mod(long a, long n) {long t=a%n; return (t>=0)?t:(t+n);}
inline long kgv(long a, long b) {return a*b/gcd(a,b);}
inline double sqr(double x) {return x*x;}
inline long sqr(long x) {return x*x;}

// testbit, setbit
inline int testbit(unsigned long l, int p) { return (l&(1<<p));}
inline void setbit(unsigned long &l, int p) {l|=1<<p;}

// RANDOM(max): Zufallszahl r mit 0<=<max
inline int RANDOM(int max) { // returns: 0<=r<max
	int r; 
	do r= rand()/(RAND_MAX/max); while (r>=max);
	return r;
}

/////////////////////////////////////////////////////////////////////

inline long stol(const char*& s) 
{
	while (isspace(*s)) s++;
	long r=atol(s); 
	while (isdigit(*s)) s++;
	return r;
}


/////////////////////////////////////////////////////////////////////


#endif /* _MYMATH_H */
