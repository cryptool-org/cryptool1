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

#ifndef _CORRELATION_H
#define _CORRELATION_H 1

#ifndef _DEFAULT_H
#include "Default.h"
#endif

#ifndef _SYMBOL_H
#include "Symbol.h"
#endif

#ifndef _ARRAY_H
#include "Array.h"
#endif

/////////////////////////////////////////////////////////////////////
// Correlation

struct CorMode
{
	enum {delta=1,cyclic=2,store=4,fft=8,covariance=256,normalize=512} cmode;
};

template<class TYPE, int mode>
class Correlation : public NTuple<double>
{
	typedef NTuple<double> baseclass;
public:
// Constructors
	Correlation(const NTuple<TYPE>& Vec, int size=0);
	Correlation(const NTuple<TYPE>& Vec1, const NTuple<TYPE>& Vec2, int size=0);
// Accessors
	int GetSize() const {return m_size;}
	// Correlation
	double GetCorrelation(int n=0) const;
	double operator[](int i) const {return GetCorrelation(i);}
	double operator()(int i=0) const {return GetCorrelation(i);}
	// Statistic
	double Mittelwert() const {return m_Mittelwert;}
	double Varianz() const {return m_Varianz;}
	double Mittelwert2() const {return m_Mittelwert2;}
	double Varianz2() const {return m_Varianz2;}

	int FindPeak(int start=0, int len=0) const;
// Attributes
	void SetSize(int size);		// legt Groesse des NTuples fest
// Operations
	// I/O
	//void Load(istream& stream); 
	//void Save(ostream& stream) const; 
	void Show(OStream& out=DefaultOStream) const;

// Implementation
private:
	// Helpers
	void Init(int size);
	// Data
	int m_size;			// Groesse des NTuples (0..m_size-1)
	int m_N,m_NX,m_NY;	// Groesse der zu korrelierenden Folgen
	NTuple<TYPE> const* m_X,*m_Y;
	double m_Mittelwert,m_Varianz;
	double m_Mittelwert2,m_Varianz2;
	Array<double,double> m_corr;
	//
	double m_mu,m_sigma;
};

/////////////////////////////////////////////////////////////////////
// Correlation - inline functions

template<class TYPE, int mode>
inline int Correlation<TYPE, mode>::FindPeak(int start /*=0*/, int len /*=0*/) const
{
	return GetMaxPos(start, len);
}

typedef Correlation<double,(CorMode::cyclic)> DCorrelation;
typedef Correlation<double,(CorMode::fft|CorMode::cyclic)> FCorrelation;
typedef Correlation<Symbol,(CorMode::delta|CorMode::store)> SCorrelation;
typedef Correlation<Symbol,(CorMode::delta|CorMode::cyclic)> SCyclicCorrelation;

#endif */ _CORRELATION_H */
