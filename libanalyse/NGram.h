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

#ifndef _NGRAM_H
#define _NGRAM_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _String_h
#include "la_string.h"
#endif
#ifndef _FREQTABLE_H
#include "FreqTable.h"
#endif
#ifndef _SYMBOL_H
#include "Symbol.h"
#endif

class SymbolArray;
class Converter;

///////////////////////////////////////////////////////////////////
//  NGram

class NGram : public FreqTable
{
	typedef FreqTable baseclass;
public:
	typedef Symbol symbol;
public:
// Constructors
	EXPLICIT NGram(int d=2, int n=1);
	EXPLICIT NGram(const SymbolArray& Vec, int n=1, int step=1);	
	NGram(int d, const NTuple<symbol>& Vec, int n=1, int step=1);
	~NGram();
// Accessors
	// Statistics
	double Entropie() const;	// der Quelle
	double NEntropie(const NGram& ng) const;	// der Nachricht
	double NEntropie(const SymbolArray &s) const;
	double Redundanz() const; 
	double Gleichverteilt() const; 
	double Koinzidenz() const;

// Operations
	void Load(istream& stream); 
	void Save(ostream& stream) const; 
	void Show(OStream& out=DefaultOStream) const;
// Implementation
	// Helpers
private:
	void Init(int d, int n);
	void Calc(const NTuple<symbol>& Vec, int step=1); 
	// Data
private:	
	int m_dim;
	int m_N;
	Converter *m_Converter; // if not NULL use to output the data TODO
};



///////////////////////////////////////////////////////////////////
//  RunTable TODO put somewhere else...
class RunTable : public FreqTable
{
	typedef FreqTable baseclass;
public:
	typedef Symbol symbol;
// Constructors
	enum RunMode {Aufsteigend=0, Absteigend=1, Gleich=2};
	RunTable(const NTuple<symbol>& Vec, int mode=0, int maxrun=0);
// Operations
	void Show(OStream& out=DefaultOStream) const;
};


/////////////////////////////////////////////////////////////////////
// NGram inline functions
// Damit koennen die NGram Member Functions auch wie normale Funktionen
// aufgerufen werden

inline double Entropie(const NGram& ng) {return ng.Entropie();}
inline double Redundanz(const NGram& ng) {return ng.Redundanz();}
inline double Gleichverteilt(const NGram& ng) {return ng.Gleichverteilt();}
inline double Koinzidenz(const NGram& ng) {return ng.Koinzidenz();}


// dito fuer den direkten Aufruf mit einem SymbolArray
// NGram wird temporaer erzeugt

inline double Entropie(const SymbolArray& Vec, int n=1) 
{return NGram(Vec,n).Entropie();}
inline double Redundanz(const SymbolArray& Vec, int n=1) 
{return NGram(Vec,n).Redundanz();}
inline double Gleichverteilt(const SymbolArray& Vec, int n=1) 
{return NGram(Vec,n).Gleichverteilt();}
inline double Koinzidenz(const SymbolArray& Vec, int n=1) 
{return NGram(Vec,n).Koinzidenz();}

#endif /* _NGRAM_H */