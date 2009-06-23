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

#ifndef _SBOX_H
#define _SBOX_H 1

// SBox.h definiert folgende Klassen:
// **********************************
// SBox
//		SBoxTable
//		SBoxPerm
//		SBoxPerm2
// DifferenceDistributionTable
// DependenceTable
// LinearDistributionTable

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
#ifndef _PERMUTATION_H
#include "Permutation.h"
#endif
#ifndef _FREQTABLE_H
#include "FreqTable.h"
#endif
#ifndef _SYMBOLARRAY_H
#include "SymbolArray.h"
#endif

/////////////////////////////////////////////////////////////////////
// SBox: Abstrakte Klasse einer Substitutions-Box (u. StromChiffre)

class SBox : public BlockCipher
{
public:
// Accessors
	virtual int InBits() const=0; 
	virtual int OutBits() const=0;
	virtual range InRange() const {return 1<<InBits();}
	virtual range OutRange() const {return 1<<OutBits();}
// Operations
	virtual int invert()=0; // return 1 if ok, 0 if inversion failed (partly)
	// Show
	void Show(OStream& out=DefaultOStream) const;
};


/////////////////////////////////////////////////////////////////////
// SBoxTable: Implementation einer SBox anhand einer Tabelle

class SBoxTable : public SBox
{
	typedef SBox baseclass;
	typedef Array<domain,domain> arraytype;
public:
// Constructors
	EXPLICIT SBoxTable(int inrange, int outrange, domain table[]);
	EXPLICIT SBoxTable(const SymbolArray& Vec);
	EXPLICIT SBoxTable(Permutation& Perm); // constructs a SBox where the bits are permutated
	EXPLICIT SBoxTable(const NTuple<long>& Vec, int outrange=0);
	EXPLICIT SBoxTable(const NTuple<unsigned long>& Vec, int outrange=0);
// Accessors
	range InRange() const {return m_SourceRange;}
	range OutRange() const {return m_DestRange;}
	int InBits() const {return ilog2(InRange());}
	int OutBits() const {return ilog2(OutRange());}
	//
	BLOCKCIPHER_WITH_SIZE_1
	domain operator()(codomain x, int mode=Encrypt) const {return m_SBoxTable[x];}
// Operations
	int invert();
// Implementation
protected:
	range m_SourceRange;
	range m_DestRange;
	arraytype m_SBoxTable;
};

/////////////////////////////////////////////////////////////////////
// SBoxPerm: SBox, bei der die Bits permutiert werden
// Im Gegensatz zu SBoxTable(Permutation) (siehe oben) wird hier
// (jedesmal!) bei Aufruf des Operators() permutiert - und keine 
// Tabelle erzeugt. Dies ist also langsamer, aber speicherplatzsparend

// Varianten
// i)  Bitreihenfolge 31...0   63...32 ...
// ii) Bitreihenfolge 0...31   32...63 ...
// a)  Permutation[Encrypt]: i->Perm(i)  Bit i wird auf Bit Perm(i) abgebildet
// b)  Permutation[Decrypt]: Perm(i)->i  Bit i erhaelt wird vom Bit Perm(i)  

class SBoxPerm : public SBox
{
	typedef SBox baseclass;
public:
// Constructors
	SBoxPerm(Permutation& Perm) : m_Perm(Perm), m_size((Perm.GetSize()-1)/SymbolArray::MaxBits()+1) {} 
// Accessors
	range InRange() const {return 1<<m_Perm.GetSize();}
	range OutRange() const {return 1<<m_Perm.GetSize();}
	int InBits() const {return m_Perm.GetSize();}
	int OutBits() const {return m_Perm.GetSize();}
	//
	int GetSize() const {return m_size;}
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) const;
	domain operator()(codomain x, int mode=Encrypt) const;
// Operations
	int invert() {m_Perm.invert(); return 1;} // NOTE: changes m_Perm!
// Implementation
protected:
	Permutation& m_Perm;
	int m_size;
};

class SBoxPerm2 : public SBoxPerm
{
public:
// Constructors
	SBoxPerm2(Permutation& Perm) : SBoxPerm(Perm) {} 
// Accessors
	void operator()(NTupleRW<symbol>& Vec, int mode=Encrypt) const;
	domain operator()(codomain x, int mode=Encrypt) const;
};


///////////////////////////////////////////////////////////////////
//  DifferenceDistributionTable

class DifferenceDistributionTable : public FreqTable
{
	typedef FreqTable baseclass;
public:
// Constructors
	DifferenceDistributionTable(const SBox& sbox);
	// Analysis
	//TODO(int din, int dout) const; // liefert {s} mit SBox(s)^SBox(s^din)==dout
// Operations
	void Show(OStream& out=DefaultOStream) const;
// Implemention
private:
	const SBox& m_SBox;
};

///////////////////////////////////////////////////////////////////
//  DependenceTable

class DependenceTable : public FreqTable
{
	typedef FreqTable baseclass;
public:
// Constructors
	DependenceTable(const SBox& sbox, int mode=0); //0=automatisch, 1=vollstaendig, n=Anzahl Zufallsversuche
// Operations
	void Show(OStream& out=DefaultOStream) const;
};

///////////////////////////////////////////////////////////////////
//  LinearDistributionTable

class LinearDistributionTable : public FreqTable
{
	typedef FreqTable baseclass;
public:
// Constructors
	LinearDistributionTable(const SBox& sbox);
// Operations
	void Show(OStream& out=DefaultOStream) const;
// Implemention
private:
	const SBox& m_SBox;
};



#endif /* _SBOX_H */