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

#ifndef _PERMUTATION_H
#define _PERMUTATION_H 1

// Permutation.h definiert folgende Klassen:
// *****************************************
// Permutation
//		PermTable

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _String_h
#include "la_string.h"
#endif
#ifndef _CIPHER_H
#include "Cipher.h"
#endif
#ifndef _ARRAY_H
#include "Array.h"
#endif

class String;

/////////////////////////////////////////////////////////////////////
// Permutation: Abstrakte Klasse einer Permutations-Box (u. Block-Chiffre)

class Permutation : public BlockCipher
{
public:
// Accessors
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) const;
	virtual long operator()(int x) const=0;
// Operations
	virtual void invert()=0;
	// Show
	void Show(OStream& out=DefaultOStream) const;

// Analysis
	int FixPunkte() const;
	int FixTupel() const;
	int IFixTupel() const;
	double MittlererAbstand() const;
	double MittlererAbstand2() const;
	// Output
	String GetPerm() const;
};

/////////////////////////////////////////////////////////////////////
// PermTable: Implementation einer Permutation anhand einer Tabelle

class PermTable : public Permutation
{
	typedef Permutation baseclass;
	typedef Array<long,long> arraytype;
public:
// Constructors	
	EXPLICIT PermTable(int len=1); // identity
	EXPLICIT PermTable(int len, long table[]) : m_PermTable(len,table), m_Length(len) {}
	EXPLICIT PermTable(const NTuple<long>& Vec);
	EXPLICIT PermTable(const NTuple<unsigned long>& Vec);
	EXPLICIT PermTable(const char* s);
	EXPLICIT PermTable(const Permutation& p1, const Permutation& p2);
// Accessors
	int GetSize() const {return m_Length;}
	long operator()(int x) const { return m_PermTable[x];}
	domain operator()(codomain x, int mode=Encrypt) const { return m_PermTable[x];}
// Operations
	int next(); //next in lexicographical order
	void invert();
// Implementation
	// Helpers
private:
	void ReadString(const char* s);
	// Data
protected:
	arraytype m_PermTable;
	int m_Length;
};


#endif /* _PERMUTATION_H */