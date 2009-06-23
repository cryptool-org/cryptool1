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
 
#ifndef _DEFAULT_H
#include "Default.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// Array3.h enhaelt folgende Template-Hilfsfunktionen, die vom 
// Template Array<..> aus Array.h verwendet werden.
// Diese koennen fuer spezielle Typen ggf. explizit implementiert werden
//
// ConstructObjects
// DestructObjects
// CopyObjects
// LoadObject
// SaveObject
// (R)CompareObjects

#include <memory.h>
#include <new.h>
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

/////////////////////////////////////////////////////////////////////////////
// special (faster) version for long, unsigned long

#define COPYOBJECTS(TYPE) \
	inline void CopyObjects(TYPE* Dest, const TYPE* Src, int Count) \
	{ memcpy(Dest, Src, Count*sizeof(TYPE)); }

COPYOBJECTS(long)
COPYOBJECTS(unsigned long)

#undef COPYOBJECTS
/////////////////////////////////////////////////////////////////////////////

template<class TYPE>
inline void ConstructObjects(TYPE* Objects, int Count)
{
	memset((void*)Objects, 0, Count*sizeof(TYPE));
	for (; Count--; Objects++)
		::new((void*)Objects) TYPE;
}

template<class TYPE>
inline void DestructObjects(TYPE* Objects, int Count)
{
	for (; Count--; Objects++)
		Objects->~TYPE();
}

template<class TYPE>
inline void CopyObjects(TYPE* Dest, const TYPE* Src, int Count)
{
	// memcpy(Dest, Src, Count*sizeof(TYPE));
	for (; Count--; Src++,Dest++)
		*Dest=*Src;
}

// Serialize...
template<class TYPE>
inline void LoadObject(TYPE& Object, istream& stream)
{
	stream >> Object;
}
template<class TYPE>
inline void SaveObject(const TYPE& Object, ostream& stream)
{
	stream << Object << endl;
}

// die folgenden beiden Funktionen werden fuer Sort benutzt
template<class TYPE>
int CompareObjects(const TYPE* Object1, const TYPE* Object2)
{
	if (*Object1 < *Object2) return 1;
	if (*Object2 < *Object1) return -1;
	return 0;
}
template<class TYPE>
int RCompareObjects(const TYPE* Object1, const TYPE* Object2)
{
	//return -CompareObjects(Object1,Object2);
	//this way it should be faster...
	if (*Object1 < *Object2) return -1;
	if (*Object2 < *Object1) return 1;
	return 0;
}

