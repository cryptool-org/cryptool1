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

#ifndef _MYTEMPLATES_H
#define _MYTEMPLATES_H 1


// Diese Datei definiert einige oft benoetigte Templates:
// swap, min, max, abs
// Vergleiche mit '<' und '=='
// operator+,... mit +=,...

// templates for swap, min and max, abs
template <class T> inline void swap(T& a, T& b) { T tmp = a; a = b; b = tmp; }
#if !defined(_MSC_VER) || _MSC_VER <= 1200
template <class T> inline T min(T a, T b) {return ( a < b ) ? a : b;}
template <class T> inline T max(T a, T b) {return ( a > b ) ? a : b;}
template <class T> inline T min(T a, T b, T c) {return min(min(a,b),c);}
template <class T> inline T max(T a, T b, T c) {return max(max(a,b),c);}
#endif
//template <class T> inline T abs(T a) {return ( a >= (T)0 ) ? a : -a;} //roger 05.04.2001

//template <class T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
//template <class T> inline const T& max(const T& a, const T& b) { return (b > a) ? b : a; }


// templates that define all comparations using '<' and '=='
///////////////////////////////////////////////////////////////////////////////////////
// Beginn Aenderung Jens Liebehenschel, 30.12.1998
///////////////////////////////////////////////////////////////////////////////////////
// Die Fehlermeldung des Compilers warning C4666: 
// "... Funktion weicht nur bezueglich der Aufrufkonvention von ... ab"
// tauchte haufig beim Uebersetzen des Projektes auf. 
//
// Jetzt wurde die Aufrufkonvention von (default) __cdecl in __stdcall bei den 
// entsprechenden Funktionen (fuenf Mal) ge�ndert, damit die Warnungen nicht beim 
// Uebersetzen der Toolkit-Dateien kommen, sondern beim Uebersetzen der Dateien
// der Analyse Bibliothek (libanalyse), die selten neu uebersetzt wird.
// 
// (Aufrufkonventionen sind bei Inline-Funktionen sowieso unerheblich, falls diese
// Funktionen nicht aufgrund der Groesse vom Compiler nicht als Inline-Funktion 
// behnadelt werden, sondern doch als Aufruf). 
///////////////////////////////////////////////////////////////////////////////////////


#pragma warning( push )
#pragma warning( disable : 4666 )


/* Roger L�schung 23.02.2001
template <class T> inline int __stdcall operator!=(const T& x, const T& y) 
{ return !(x == y); }
template <class T> inline int __stdcall operator>(const T& x, const T& y) 
{ return y < x; }
template <class T> inline int __stdcall operator<=(const T& x, const T& y) 
{ return !(y < x); }
template <class T> inline int __stdcall operator>=(const T& x, const T& y) 
{ return !(x < y); }
*/

#pragma warning( pop )

// templates defining operator +,-,*,/,^,% using +=,... and initializing constructor
template <class T, class A> inline T __stdcall operator+(const T& x, A& y) 
{ T tmp(x); tmp+=y; return tmp; }
///////////////////////////////////////////////////////////////////////////////////////
// Ende Aenderung Jens Liebehenschel, 30.12.1998
///////////////////////////////////////////////////////////////////////////////////////


/* Roger L�schung 23.02.2001
template <class T, class A> inline T operator-(const T& x, A& y) 
{ T tmp(x); tmp-=y; return tmp; }
template <class T, class A> inline T operator*(const T& x, A& y) 
{ T tmp(x); tmp*=y; return tmp; }
template <class T, class A> inline T operator/(const T& x, A& y) 
{ T tmp(x); tmp/=y; return tmp; }
template <class T, class A> inline T operator^(const T& x, A& y) 
{ T tmp(x); tmp^=y; return tmp; }
template <class T, class A> inline T operator%(const T& x, A& y) 
{ T tmp(x); tmp%=y; return tmp; }
template <class T, class A> inline T operator|(const T& x, A& y) 
{ T tmp(x); tmp|=y; return tmp; }
template <class T, class A> inline T operator&(const T& x, A& y) 
{ T tmp(x); tmp&=y; return tmp; }
*/

#endif /* _MYTEMPLATES_H */
