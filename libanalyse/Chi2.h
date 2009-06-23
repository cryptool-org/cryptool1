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

#ifndef _CHI2_H
#define _CHI2_H 1

#ifndef _ITERATOR_H
#include "Iterator.h"
#endif

/////////////////////////////////////////////////////////////////////
// Chi2: Klasse zur Chi-Quadrat-Analyse

class Chi2 {
public:
// Constructors
	Chi2(const NTuple<long>& H);
	Chi2(const NTuple<long>& H, const NTuple<double>& P);
	Chi2(const NTuple<double>& H, long totalcount=100000);
// Accessors
	int Test(double niveau) {return m_V<=GetChi2(niveau,m_r-1);}
	double GetV() const {return m_V;}
	double GetAlpha() const {return (double)GetAlpha(m_V,m_r-1)/1000.0;}
	double operator()() const {return GetAlpha();}
// Static Functions
public:
	static double GetChi2(double x, int v);
	static int GetAlpha(double x, int v);	// returns 0..1000
	static int Check();
// Implementation
	// Data
private:
	double m_V;
	long m_r;
// Static Implementation
private:
	// Helpers
	static void PrepareTable(int v);
	// Data
private:
	static const int alphacount;
	static const int lines;
	static int quantile30; 
	static long quantiletable[30+2][14]; // see Chi2.cpp!
};


#endif /* _CHI2_H */
