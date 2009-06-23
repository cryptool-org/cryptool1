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

#ifndef _SORTPAIR_H
#define _SORTPAIR_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif

#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

/////////////////////////////////////////////////////////////////////
// SortPair 
// speichert Tupel <Data,Index> - wird von SortedArray benutzt

template<class TYPE> struct SortPair
{
	TYPE data;
	int index;
//
	int operator<(const SortPair<TYPE>& s) const;
	friend ostream& operator<<(ostream& os, const SortPair<TYPE>& sp);
};

template<class TYPE>
inline int SortPair<TYPE>::operator<(const SortPair<TYPE>& s) const
{
	if (data<s.data) return 1;
	return 0;
}

#ifdef GCC_WORKAROUND
// the next two are for GCC only, as it insists on creating all class members
// (by template) - even the unused ones.

template<class TYPE>
inline ostream& operator<<(ostream& out, const SortPair<TYPE>& sp)
{
	out << "(" << sp.index << "," << sp.data << ")";
	return out;
}

template<class TYPE>
inline istream& operator>>(istream& out,SortPair<TYPE>& sp)
{return out;}
#endif // GCC_WORKAROUND

#endif /* _SORTPAIR_H */