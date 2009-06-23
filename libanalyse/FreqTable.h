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

#ifndef _FREQTABLE_H
#define _FREQTABLE_H 1

// FreqTable.h definiert folgende Klassen:
// ***************************************
// FreqTable
// FreqCountTable


#ifndef _DEFAULT_H
#include "Default.h"
#endif
#ifndef _String_h
#include "la_string.h"
#endif
#ifndef _ARRAY_H
#include "Array.h"
#endif

///////////////////////////////////////////////////////////////////
//  FreqTable

class FreqTable : public NTuple<double>
{
protected:
	typedef NTuple<double> baseclass;
public:
	typedef unsigned long hcount;
// Constructors
	EXPLICIT FreqTable(int rows=1, int columns=1);
// Accessors
	int GetSize() const {return m_hcount.GetSize();}
	int GetRows() const {return m_Rows;}
	int GetColumns() const {return m_Columns;}

	hcount GetCount(int i) const;
	hcount GetCount(int i, int j) const;
	hcount GetTotalCount() const;
	double GetFrequency(int i) const;
	double operator[](int i) const; // = GetFrequency

// Operations
	void Set(int i);
	void Set(int i, int j);
	void Set2(int i);	// does not increment totalcount
	void IncrementTotalCount();
	// I/O
	void Load(istream& stream); 
	void Save(ostream& stream) const; 
	void Show(OStream& out=DefaultOStream) const;
// Implementation
private:
	FreqTable(const FreqTable&);
	FreqTable operator=(const FreqTable&);
protected:	
	int m_Rows;
	int m_Columns;
	hcount m_TotalCount;
	Array<hcount,hcount> m_hcount;
};


///////////////////////////////////////////////////////////////////
//  FreqCountTable
//  macht aus einem FreqTable einen NTuple<long>
//  der die Anzahl der Treffer (statt deren Haeufigkeit) zurueckgibt

class FreqCountTable : public NTuple<long>
{
public:
// Constructors
	FreqCountTable(const FreqTable& HVec) : m_HVec(HVec) {}
// Accessors
	int GetSize() const {return m_HVec.GetSize();}
	long operator[](int i) const;
// Implementation
private:
	FreqCountTable(const FreqCountTable&);
	FreqCountTable operator=(const FreqCountTable&);
	// Data
private:	
	const FreqTable& m_HVec;
};


/////////////////////////////////////////////////////////////////////
// FreqTable inline functions

inline FreqTable::hcount FreqTable::GetCount(int i) const 
{
	//ASSERT(i>=0 && i<m_hcount.GetSize());
	return m_hcount[i];
}
inline FreqTable::hcount FreqTable::GetCount(int i, int j) const 
{
	//ASSERT((i*m_Rows+j)>=0 && (i*m_Rows+j)<m_hcount.GetSize());
	return m_hcount[i*m_Rows+j];
}
inline FreqTable::hcount FreqTable::GetTotalCount() const 
{
	return m_TotalCount;
}
inline double FreqTable::GetFrequency(int i) const 
{
	//ASSERT(i>=0 && i<m_hcount.GetSize());
	if (m_TotalCount==0) return 0.0;
	return (double)m_hcount[i]/m_TotalCount;
}
inline double FreqTable::operator[](int i) const 
{
	return GetFrequency(i);
}

inline void FreqTable::Set(int i) 
{
	//ASSERT(i>=0 && i<m_hcount.GetSize());
	m_TotalCount++;
	m_hcount[i]++;
}
inline void FreqTable::Set(int i, int j) 
{
	//ASSERT((i*m_Rows+j)>=0 && (i*m_Rows+j)<m_hcount.GetSize());
	m_TotalCount++;
	m_hcount[i*m_Rows+j]++;
}
inline void FreqTable::Set2(int i) 
{
	//ASSERT(i>=0 && i<m_hcount.GetSize());
	m_hcount[i]++;
}

inline void FreqTable::IncrementTotalCount() 
{
	m_TotalCount++;
}


/////////////////////////////////////////////////////////////////////
// FreqCountTable inline functions

inline long FreqCountTable::operator[](int i) const 
{
	return m_HVec.GetCount(i);
}

#endif /* _FREQTABLE_H */
