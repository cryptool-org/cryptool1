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

#ifndef _STDINC_H
#define _STDINC_H 1
// include all the commonly needed include files
// simply include this file

#ifndef _String_h
#include "la_string.h"
#endif

#ifndef _DEFAULT_H
#include "Default.h"
#endif

#ifndef _ITERATOR_H
#include "Iterator.h"
#endif

#ifndef _SYMBOL_H
#include "Symbol.h"
#endif

#ifndef _SUBARRAY_H
#include "SubArray.h"
#endif

#ifndef _SORTEDARRAY_H
#include "SortedArray.h"
#endif

#ifndef _SYMBOLARRAY_H
#include "SymbolArray.h"
#endif

#ifndef _NGRAM_H
#include "NGram.h"
#endif

#ifndef _LFSR_H
#include "LFSR.h"
#endif

#ifndef _SBOX_H
#include "SBox.h"
#endif

#ifndef _PERMUTATION_H
#include "Permutation.h"
#endif

#ifndef _CORRELATION_H
#include "Correlation.h"
#endif

#ifndef _CHI2_H
#include "Chi2.h"
#endif

/* falls benoetigt, von Hand includen!
#ifndef _DES_H
#include "Des.h"
#endif
*/

/////////////////////////////////////////////////////////////////////

//#ifdef INSTANTIIATE // nur zum Instantiieren benoetigt

#ifndef _ITERATOR2_H
#include "Iterator2.h"
#endif

#ifndef _CORRELATION2_H
#include "Correlation2.h"
#endif

//#endif // INSTANTIIATE


/////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <fstream.h>
#if (!defined(_MSC_VER))
#include <strstream.h>
#else
#include <strstrea.h>
#endif

#endif /*_STDINC_H */
