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
#define _DEFAULT_H 1

// fast ueberall benutzt, deshalb hier...
class OStream;
extern OStream DefaultOStream;

// Debugging...
#ifdef _DEBUG
#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif
#else /*_DEBUG*/
#undef ASSERT
#define ASSERT(x) ;
#endif


// GNU specific

#ifdef __GNUC__
#define EXPLICIT explicit
#define NOSTATICTAMPLES
#else
#define EXPLICIT
#endif


#define GCC_WORKAROUND
// Dies ist notwendig, um einige Probleme zu beheben, die GCC
// (vorallem) mit templates hat. So will GCC immer alle Member
// Funktionen instantiieren - selbst die nicht benoetigten.

#ifdef __GNUC__
#define GCC_WORKAROUND2	
#endif

// MSC specific

#if (defined(_MSC_VER))
#pragma warning( disable : 4250 )
#pragma warning( disable : 4114 )
#endif



#endif /* _DEFAULT_H */

